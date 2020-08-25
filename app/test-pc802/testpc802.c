/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>
#include <stdbool.h>

#include <sys/queue.h>
#include <sys/stat.h>

#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>

#include <rte_common.h>
#include <rte_errno.h>
#include <rte_byteorder.h>
#include <rte_log.h>
#include <rte_debug.h>
#include <rte_cycles.h>
#include <rte_malloc_heap.h>
#include <rte_memory.h>
#include <rte_memcpy.h>
#include <rte_launch.h>
#include <rte_eal.h>
#include <rte_alarm.h>
#include <rte_per_lcore.h>
#include <rte_lcore.h>
#include <rte_atomic.h>
#include <rte_branch_prediction.h>
#include <rte_mempool.h>
#include <rte_malloc.h>
#include <rte_mbuf.h>
#include <rte_mbuf_pool_ops.h>
#include <rte_interrupts.h>
#include <rte_pci.h>
#include <rte_ether.h>
#include <rte_ethdev.h>
#include <rte_dev.h>
#include <rte_string_fns.h>

#include <cmdline_rdline.h>
#include <cmdline_parse.h>
#include <cmdline_socket.h>
#include <cmdline.h>

#include <pc802_ethdev.h>

struct rte_mempool *mpool_pc802_tx;

#define MAX_DATA_BUF_SZ (256*1024)

typedef union {
    uint32_t _d[MAX_DATA_BUF_SZ / sizeof(uint32_t)];
    struct {
        uint32_t s;
        uint32_t N;
        uint32_t d[0];
    };
} DataBuf_t;

int picocom_pc802_startup(void);

static void
signal_handler(int signum)
{
    if (signum == SIGINT || signum == SIGTERM) {
        printf("\n\nSignal %d received, preparing to exit...\n",
                signum);
        //force_quit = true;
        signal(signum, SIG_DFL);
        kill(getpid(), signum);
    }
}

static const struct rte_eth_conf dev_conf = {
	    .rxmode = {
		    .max_rx_pkt_len = ETHER_MAX_LEN,
	    },
    };

static int port_init(uint16_t port)
{
    struct rte_mempool *mbuf_pool;
    //const struct rte_eth_conf dev_conf;
    struct rte_eth_dev_info dev_info;
    struct rte_eth_txconf tx_conf;
    //const struct rte_eth_rxconf rx_conf;
    int socket_id;

    rte_eth_dev_info_get(port, &dev_info);
    socket_id = dev_info.device->numa_node;

    mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL_ETH_TX", 2048,
            128, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on Line %d\n", __LINE__);
    mpool_pc802_tx = mbuf_pool;

    mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL_ETH_RX", 2048,
            128 , 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on Line %d\n", __LINE__);

    rte_eth_dev_configure(port, 1, 1, &dev_conf);
    tx_conf = dev_info.default_txconf;
    rte_eth_tx_queue_setup(port, 0, 128, socket_id, &tx_conf);
    rte_eth_rx_queue_setup(port, 0, 128, socket_id, NULL, mbuf_pool);

    RTE_ASSERT(0 == pc802_create_tx_queue(port, PC802_TRAFFIC_5G_EMBB_DATA, 256*1024, 256, 128));
    RTE_ASSERT(0 == pc802_create_rx_queue(port, PC802_TRAFFIC_5G_EMBB_DATA, 256*1024, 256, 128));

    RTE_ASSERT(0 == pc802_create_tx_queue(port, PC802_TRAFFIC_5G_EMBB_CTRL, 256*1024, 256, 128));
    RTE_ASSERT(0 == pc802_create_rx_queue(port, PC802_TRAFFIC_5G_EMBB_CTRL, 256*1024, 256, 128));

    rte_eth_dev_start(port);

    printf("Finished port_init !\n");

    return 0;
}


static uint32_t * alloc_tx_blk(uint16_t qId)
{
    PC802_Mem_Block_t *mblk;
    mblk = pc802_alloc_tx_mem_block(0, qId);
    if (mblk)
        return (uint32_t *)&mblk[1];
    return NULL;
}

static void free_blk(uint32_t *blk)
{
    char *p = (char *)blk;
    if (p) {
        p -= sizeof(PC802_Mem_Block_t);
        pc802_free_mem_block((PC802_Mem_Block_t *)p);
    }
}

static uint16_t tx_blks(uint16_t qId, uint32_t **blks, uint16_t nb_blks)
{
    uint16_t k;
    PC802_Mem_Block_t *tx_blks[32];
    RTE_ASSERT(nb_blks <= 32);
    for (k = 0; k <nb_blks; k++)
        tx_blks[k] = (PC802_Mem_Block_t *)((char *)blks[k] - sizeof(PC802_Mem_Block_t));
    return pc802_tx_mblk_burst(0, qId, tx_blks, nb_blks);
}

static uint16_t rx_blks(uint16_t qId, uint32_t **blks, uint16_t nb_blks)
{
    uint16_t k;
    nb_blks = pc802_rx_mblk_burst(0, qId, (PC802_Mem_Block_t **)blks, nb_blks);
    for (k = 0; k < nb_blks; k++) {
        blks[k] += (sizeof(PC802_Mem_Block_t) / sizeof(uint32_t));
    }
    return nb_blks;
}

static void set_blk_attr(uint32_t *blk, uint32_t length, uint8_t type, uint8_t eop)
{
    PC802_Mem_Block_t *mblk;
    if (blk) {
        mblk = (PC802_Mem_Block_t *)((char *)blk - sizeof(PC802_Mem_Block_t));
        mblk->pkt_length = length;
        mblk->pkt_type = type;
        mblk->eop = eop;
    }
}

static void get_blk_attr(uint32_t *blk, uint32_t *length, uint8_t *type, uint8_t *eop)
{
    PC802_Mem_Block_t *mblk;
    if (blk) {
        mblk = (PC802_Mem_Block_t *)((char *)blk - sizeof(PC802_Mem_Block_t));
        *length = mblk->pkt_length;
        *type = mblk->pkt_type;
        *eop = mblk->eop;
    }
}

static int produce_dl_src_data(uint32_t *buf)
{
    static uint32_t idx = 0;
    uint32_t N, s, d, k;
    *buf++ = s = (uint32_t)rand();
    N = (uint32_t)rand();
    N &= 511;
    if (N < 10) N = 10;
    *buf++ = N;
    d = (uint32_t)rand();
    printf("DL_MSG[1][%3u]: N=%3u S=0x%08X D=0x%08X\n", idx++, N, s, d);
    for (k = 0; k < N; k++) {
        *buf++ = d;
        d += s;
    }
    return 0;
}

static int check_ul_dst_data(uint32_t *buf, uint32_t msgSz)
{
    uint32_t k, N, s, exp;
    uint32_t *pd;
    uint32_t sz = 0;
    static uint32_t idx = 0;
    uint32_t m = 0;
    int re = 0;

    pd = buf;
    while (sz < msgSz) {
        s = *pd++;
        N = *pd++;
        printf("UL_MSG[1][%3d]: N=%3u S=0x%08X D=0x%08X\n", idx++, N, s, pd[0]);
        exp = s + *pd++;
        for (k = 1; k < N; k++) {
            //printf("UL_MSG_D[%u] = 0x%08X\n", k, pd[0]);
            if (*pd++ != exp) {
                re = -1;
                printf("Msg ERROR: m = %u , k = %u \n", m, k);
            }
            exp += s;
        }
        sz += (N + 2) * sizeof(uint32_t);
        m++;
    }
    return re;
}

static int check_single_same(uint32_t *a, uint32_t *b)
{
    uint32_t k, N;
    static uint32_t idx = 0;
    if (a[1] != b[1]) return -1;
    N = a[1] + 2;
    for (k = 0; k < N; k++) {
        if (a[k] != b[k]) {
            return -2;
        }
   }
   printf("UL_MSG[%u]: N=%u S=0x%08X D=0x%08X\n",
       idx++, N, b[0], b[2]);
   return 0;
}

static int check_same(uint32_t **a, uint16_t na, uint32_t *b)
{
    uint32_t *pa;
    uint32_t N;
    uint16_t k;
    for (k = 0; k < na; k++) {
        pa = a[k];
        N = pa[1] + 2;
        if (check_single_same(pa, b))
            return -k;
        b += N;
    }
    return 0;
}

static void swap_msg(uint32_t *a, uint32_t msgSz)
{
    uint32_t d;
    while (msgSz) {
        d = *a;
        *a++ = ~d;
        msgSz -= sizeof(uint32_t);
    }
    return;
}

#define QID_DATA    PC802_TRAFFIC_5G_EMBB_DATA
#define QID_CTRL    PC802_TRAFFIC_5G_EMBB_CTRL

static int case1(void)
{
    int re;
    uint32_t N;
    uint32_t *a = alloc_tx_blk(QID_CTRL);
    if (NULL == a) return -1;

    produce_dl_src_data(a);
    N = sizeof(uint32_t) * (a[1] + 2);
    set_blk_attr(a, N, 2, 1);
    tx_blks(QID_CTRL, &a, 1);

    uint32_t *b;
    while (0 == rx_blks(QID_CTRL, &b, 1));
    uint32_t length;
    uint8_t type, eop;
    get_blk_attr(b, &length, &type, &eop);
    if ((type != 2) || (eop != 1))
        return -1;
    swap_msg(b, length);
    printf("CASE1: UL msg length = %u\n", length);
    check_ul_dst_data(b, length);
    re = check_single_same(a, b);
    free_blk(a);
    free_blk(b);
    return re;
}

static int case2(void)
{
    uint32_t N;
    uint32_t *a[2];
    uint32_t *b[2];
    uint32_t length;
    uint8_t type, eop;

    a[0] = alloc_tx_blk(QID_DATA);
    produce_dl_src_data(a[0]);
    N = sizeof(uint32_t) * (a[0][1] + 2);
    set_blk_attr(a[0], N, 0, 1);
    tx_blks(QID_DATA, &a[0], 1);

    a[1] = alloc_tx_blk(QID_CTRL);
    produce_dl_src_data(a[1]);
    N = sizeof(uint32_t) * (a[1][1] + 2);
    set_blk_attr(a[1], N, 1, 1);
    tx_blks(QID_CTRL, &a[1], 1);

    uint16_t s;
    do {
        s = rx_blks(QID_DATA, &b[0], 1);
    } while(0 == s);
    do {
        s = rx_blks(QID_CTRL, &b[1], 1);
    } while(0 == s);

    get_blk_attr(b[0], &length, &type, &eop);
    swap_msg(b[0], length);
    if (check_single_same(a[0], b[0]))
        return -1;
    get_blk_attr(b[1], &length, &type, &eop);
    swap_msg(b[1], length);
    if (check_single_same(a[1], b[1]))
        return -2;

    free_blk(a[0]);
    free_blk(a[1]);
    free_blk(b[0]);
    free_blk(b[1]);
    return 0;
}

static int case3(void)
{
    uint32_t N;
    uint32_t *a[3];
    uint32_t *b[2];
    uint32_t length;
    uint8_t type, eop;

    a[0] = alloc_tx_blk(QID_DATA);
    produce_dl_src_data(a[0]);
    N = sizeof(uint32_t) * (a[0][1] + 2);
    set_blk_attr(a[0], N, 0, 0);
    tx_blks(QID_DATA, &a[0], 1);

    a[1] = alloc_tx_blk(QID_DATA);
    produce_dl_src_data(a[1]);
    N = sizeof(uint32_t) * (a[1][1] + 2);
    set_blk_attr(a[1], N, 0, 1);
    tx_blks(QID_DATA, &a[1], 1);

    a[2] = alloc_tx_blk(QID_CTRL);
    produce_dl_src_data(a[2]);
    N = sizeof(uint32_t) * (a[2][1] + 2);
    set_blk_attr(a[2], N, 1, 1);
    tx_blks(QID_CTRL, &a[2], 1);

    uint16_t s;
    do {
        s = rx_blks(QID_DATA, &b[0], 1);
    } while(0 == s);
    do {
        s = rx_blks(QID_CTRL, &b[1], 1);
    } while(0 == s);

    get_blk_attr(b[0], &length, &type, &eop);
    swap_msg(b[0], length);
    if (check_same(&a[0], 2, b[0]))
        return -1;
    get_blk_attr(b[1], &length, &type, &eop);
    swap_msg(b[1], length);
    if (check_single_same(a[2], b[1]))
        return -2;

    free_blk(a[0]);
    free_blk(a[1]);
    free_blk(a[2]);
    free_blk(b[0]);
    free_blk(b[1]);
    return 0;
}

static int case4(uint16_t D)
{
    uint32_t N;
    uint32_t *a[17];
    uint32_t *b[2];
    int k;
    uint32_t length;
    uint8_t  type, eop;

    if (D > 16) D = 16;

    for (k = 0; k < D; k++) {
        a[k] = alloc_tx_blk(QID_DATA);
        produce_dl_src_data(a[k]);
        N = sizeof(uint32_t) * (a[k][1] + 2);
        eop = k == (D-1);
        set_blk_attr(a[k], N, 0, eop);
        printf("  Type=0  m=%u  EOP=%1u\n", k, eop);
        tx_blks(QID_DATA, &a[k], 1);
    }
    a[k] = alloc_tx_blk(QID_CTRL);
    produce_dl_src_data(a[k]);
    N = sizeof(uint32_t) * (a[k][1] + 2);
    set_blk_attr(a[k], N, 1, 1);
    printf("  Type=1  m=%u  EOP=1\n", k);
    tx_blks(QID_CTRL, &a[k], 1);

    uint16_t s;
    do {
        s = rx_blks(QID_DATA, &b[0], 1);
    } while(0 == s);
    do {
        s = rx_blks(QID_CTRL, &b[1], 1);
    } while(0 == s);

    get_blk_attr(b[0], &length, &type, &eop);
    swap_msg(b[0], length);
    if (check_same(&a[0], D, b[0]))
        return -1;
    get_blk_attr(b[1], &length, &type, &eop);
    swap_msg(b[1], length);
    if (check_single_same(a[D], b[1]))
        return -2;

    for (k = 0; k < D; k++)
        free_blk(a[k]);
    free_blk(b[0]);
    free_blk(b[1]);
    return 0;
}

static int case5(void)
{
    uint32_t D, n;
    uint32_t L = (uint32_t)rand();
    L = 16 + (L & 7);

    printf("Case 5 will execute Case 4 for %u times!\n", L);
    n = 0;
    while (L) {
        D = (uint32_t)rand();
        D = (D & 15) + 1;
        printf("... Test Case 4 with %u users for No. %u\n", D, n++);
        if (case4(D))
            return -1;
        L--;
    }
    return 0;
}

static void disp_test_result(int caseNo, int result)
{
    if (result)
        printf("Case %d  ---  FAILED\n", caseNo);
    else
        printf("Case %1d --- PASSED\n", caseNo);
}

extern cmdline_parse_ctx_t main_ctx[];
static int prompt(void* arg)
{
	struct cmdline *cl;
    arg = arg;

	cl = cmdline_stdin_new(main_ctx, "PC802>> ");
	if (cl == NULL) {
		return -1;
	}
	cmdline_interact(cl);
	cmdline_stdin_exit(cl);

	return 0;
}

int test_case_No;

static void run_case1(void)
{
    int diag;
    printf("Begin Test Case 1\n");
    diag = case1();
    disp_test_result(1, diag);
}

static void run_case2(void)
{
    int diag;
    printf("Begin Test Case 2\n");
    diag = case2();
    disp_test_result(2, diag);
}

static void run_case3(void)
{
    int diag;
    printf("Begin Test Case 3\n");
    diag = case3();
    disp_test_result(3, diag);
}

static void run_case4(void)
{
    int diag;
    printf("Begin Test Case 4\n");
    diag = case4(16);
    disp_test_result(4, diag);
}

static void run_case5(void)
{
    int diag;
    printf("Begin Test Case 5\n");
    diag = case5();
    disp_test_result(5, diag);
}

static void run_case_all(void)
{
    run_case1();
    run_case2();
    run_case3();
    run_case4();
    run_case5();
}

int main_stop = 0;

int main(int argc, char** argv)
{
    int diag;

    picocom_pc802_startup();

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    diag = rte_eal_init(argc, argv);
    if (diag < 0)
        rte_panic("Cannot init EAL\n");

    port_init(0);

    rte_eal_remote_launch(prompt, NULL, 1);

    while(!main_stop) {
        usleep(10);
        switch (test_case_No) {
        case 0:
            break;
        case 1:
            run_case1();
            test_case_No = 0;
            break;
        case 2:
            run_case2();
            test_case_No = 0;
            break;
        case 3:
            run_case3();
            test_case_No = 0;
            break;
        case 4:
            run_case4();
            test_case_No = 0;
            break;
        case 5:
            run_case5();
            test_case_No = 0;
            break;
        case -1:
            run_case_all();
            test_case_No = 0;
            break;
        default:
            printf("Wrong case number, it should be 1/2/3/4/5/-1\n");
        }
    }

    usleep(5000);

    return 0;
}

