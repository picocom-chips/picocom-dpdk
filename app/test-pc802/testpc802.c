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

#include <rte_pmd_pc802.h>
#include <pcxx_ipc.h>

#define TEST_PC802_DISP_LOOP_NUM    10000

int testpc802_data_mode = 0;
int testpc802_exit_loop = 0;

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
            .max_rx_pkt_len = RTE_ETHER_MAX_LEN,
        },
    };

static uint32_t process_ul_ctrl_msg(const char* buf, uint32_t payloadSize);
static uint32_t process_dl_ctrl_msg(const char* buf, uint32_t payloadSize);
static uint32_t process_ul_oam_msg(const char* buf, uint32_t payloadSize);
static uint32_t process_dl_oam_msg(const char* buf, uint32_t payloadSize);
static uint32_t process_ul_data_msg(const char* buf, uint32_t payloadSize);
static uint32_t process_dl_data_msg(const char* buf, uint32_t payloadSize);

static pcxxInfo_s   ctrl_cb_info = {process_ul_ctrl_msg, process_dl_ctrl_msg};
static pcxxInfo_s   oam_cb_info  = {process_ul_oam_msg,  process_dl_oam_msg };
static pcxxInfo_s   data_cb_info = {process_ul_data_msg, process_dl_data_msg};

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

    pcxxDataOpen(&data_cb_info);

    pcxxCtrlOpen(&ctrl_cb_info);

    pcxxOamOpen(&oam_cb_info);

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

static int produce_random_dl_src_data(uint32_t *buf)
{
    //static uint32_t idx = 0;
    uint32_t N, s, d, k;
    do {
        s = (uint32_t)rand();
    } while (s == 0x4b3c2d1e);
    *buf++ = s;
    N = (uint32_t)rand();
    N &= 511;
    if (N < 10) N = 10;
    if (N > 500) N = 500;
    *buf++ = N;
    d = (uint32_t)rand();
    //printf("DL_MSG[1][%3u]: N=%3u S=0x%08X D=0x%08X\n", idx++, N, s, d);
    for (k = 0; k < N; k++) {
        *buf++ = d;
        d += s;
    }
    return 0;
}

static int produce_fixed_dl_src_data_1(uint32_t *buf, uint16_t qId)
{
    //static uint32_t idx = 0;
    uint32_t N, s, d, k;
    s = 0;
    *buf++ = s;
    N = 500;
    *buf++ = N;
    d = 0x11111111 * (1 + qId);
    //printf("DL_MSG[1][%3u]: N=%3u S=0x%08X D=0x%08X\n", idx++, N, s, d);
    for (k = 0; k < N; k++) {
        *buf++ = d;
        d += s;
    }
    return 0;
}

static int produce_fixed_dl_src_data_2(uint32_t *buf, uint16_t qId)
{
    //static uint32_t idx = 0;
    static uint32_t d0[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint32_t N, s, d, k;
    s = 1;
    *buf++ = s;
    N = 500;
    *buf++ = N;
    d = d0[qId];
    d0[qId]++;
    //printf("DL_MSG[1][%3u]: N=%3u S=0x%08X D=0x%08X\n", idx++, N, s, d);
    for (k = 0; k < N; k++) {
        *buf++ = d;
        d += s;
    }
    return 0;
}

static int produce_fixed_dl_src_data_3(uint32_t *buf, uint16_t qId)
{
    static uint32_t d0[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    static uint32_t L = 400;
    uint32_t N, s, d, k;
    s = 1;
    *buf++ = s;
    if (L >= 501) L = 400;
    N = L++;
    *buf++ = N;
    d = d0[qId];
    d0[qId]++;
    for (k = 0; k < N; k++) {
        *buf++ = d;
        d += s;
    }
    return 0;
}

static int produce_dl_src_data(uint32_t *buf, uint16_t qId)
{
    if (0 == testpc802_data_mode) {
        produce_random_dl_src_data(buf);
    } else if (1 == testpc802_data_mode) {
        produce_fixed_dl_src_data_1(buf, qId);
    } else if (2 == testpc802_data_mode) {
        produce_fixed_dl_src_data_2(buf, qId);
    } else {
        produce_fixed_dl_src_data_3(buf, qId);
    }
    return 0;
}

static int check_single_same(uint32_t *a, uint32_t *b)
{
    uint32_t k, N;
    uint32_t err_cnt;
    int res;
    err_cnt = 0;
    res = 0;
    N = a[1] + 2;
    for (k = 0; k < N; k++) {
        if (a[k] != b[k]) {
            res = -1;
            DBLOG("ERROR: a[%3u] = 0x%08X  !=  b[%3u] = 0x%08X\n",
                k, a[k], k, b[k]);
            err_cnt++;
            if (16 == err_cnt)
                return -1;
        }
   }
   return res;
}

static int check_same(uint32_t **a, uint16_t na, uint32_t *b)
{
    uint32_t *pa;
    uint32_t N;
    uint16_t k;
    for (k = 0; k < na; k++) {
        pa = a[k];
        N = pa[1] + 2;
        if (check_single_same(pa, b)) {
            DBLOG("ERROR: k = %hu\n", k);
            return -1;
        }
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
#define QID_OAM     PC802_TRAFFIC_OAM

static union {
    const char *cc;
    uint32_t   *up;
} dl_a[17];
static uint32_t dl_a_num = 0;
static union {
    const char *cc;
    uint32_t   *up;
} dl_oam[32];
static uint32_t dl_oam_num = 0;

static int      atl_test_result;

static uint32_t process_dl_ctrl_msg(const char* buf, uint32_t payloadSize)
{
    payloadSize = payloadSize;
    dl_a[dl_a_num].cc = buf;
    dl_a_num++;
    return 0;
}

static uint32_t process_ul_ctrl_msg(const char* buf, uint32_t payloadSize)
{
    uint64_t addr = (uint64_t)buf;
    uint32_t *ul_msg = (uint32_t *)addr;
    swap_msg(ul_msg, payloadSize);
    uint32_t *dl_msg;
    dl_msg = dl_a[dl_a_num - 1].up;
    if (check_same(&dl_msg, 1, ul_msg)) {
        atl_test_result |= 1;
    }
    dl_a_num = 0;
    return payloadSize;
}

static uint32_t process_dl_oam_msg(const char* buf, uint32_t payloadSize)
{
    buf = buf;
    payloadSize = payloadSize;
    dl_oam[dl_oam_num].cc = buf;
    dl_oam_num++;
    return 0;
}

static uint32_t process_ul_oam_msg(const char* buf, uint32_t payloadSize)
{
    uint64_t addr = (uint64_t)buf;
    uint32_t *ul_msg = (uint32_t *)addr;
    swap_msg(ul_msg, payloadSize);
    uint32_t **dl_msg;
    dl_msg = &dl_oam[0].up;
    if (check_same(dl_msg, dl_oam_num, ul_msg)) {
        atl_test_result |= 4;
    }
    dl_oam_num = 0;
    return payloadSize;
}

static uint32_t process_dl_data_msg(const char* buf, uint32_t payloadSize)
{
    payloadSize = payloadSize;
    dl_a[dl_a_num].cc = buf;
    dl_a_num++;
    return 0;
}

static uint32_t process_ul_data_msg(const char* buf, uint32_t payloadSize)
{
    uint64_t addr = (uint64_t)buf;
    uint32_t *ul_msg = (uint32_t *)addr;
    swap_msg(ul_msg, payloadSize);
    uint32_t **dl_msg;
    dl_msg = &dl_a[0].up;
    if (check_same(dl_msg, dl_a_num - 1, ul_msg)) {
        atl_test_result |= 2;
    }
    return payloadSize;
}

static int case1(void)
{
    int re;
    uint32_t N;
    uint32_t *a = alloc_tx_blk(QID_CTRL);
    if (NULL == a) return -1;

    produce_dl_src_data(a, QID_CTRL);
    N = sizeof(uint32_t) * (a[1] + 2);
    set_blk_attr(a, N, 2, 1);
    tx_blks(QID_CTRL, &a, 1);

    uint32_t *b;
    while (0 == rx_blks(QID_CTRL, &b, 1));
    uint32_t length = 0;
    uint8_t type, eop = 0;
    get_blk_attr(b, &length, &type, &eop);
    if ((type != 2) || (eop != 1))
        return -1;
    swap_msg(b, length);
    //printf("CASE1: UL msg length = %u\n", length);
    //check_ul_dst_data(b, length);
    re = check_single_same(a, b);
    free_blk(a);
    free_blk(b);
    return re;
}

static int case101(void)
{
    char *a;
    uint32_t *A;
    uint32_t N;
    uint32_t avail;

    pcxxSendStart();
    RTE_ASSERT(0 == pcxxCtrlAlloc(&a, &avail));
    A = (uint32_t *)a;
    produce_dl_src_data(A, QID_CTRL);
    N = sizeof(uint32_t) * (A[1] + 2);
    pcxxCtrlSend(a, N);
    pcxxSendEnd();

    while (-1 == pcxxCtrlRecv());
    int re = atl_test_result;
    atl_test_result = 0;
    return re;
}

static int case2(void)
{
    uint32_t N;
    uint32_t *a[2];
    uint32_t *b[2];
    uint32_t length = 0;
    uint8_t type, eop;

    a[0] = alloc_tx_blk(QID_DATA);
    produce_dl_src_data(a[0], QID_DATA);
    N = sizeof(uint32_t) * (a[0][1] + 2);
    set_blk_attr(a[0], N, 0, 1);
    tx_blks(QID_DATA, &a[0], 1);

    a[1] = alloc_tx_blk(QID_CTRL);
    produce_dl_src_data(a[1], QID_CTRL);
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

static int case102(void)
{
    char *a[2];
    uint32_t *A;
    uint32_t length;
    uint32_t offset;
    uint32_t avail;

    uint32_t *tmp = alloc_tx_blk(QID_DATA);

    pcxxSendStart();

    produce_dl_src_data(tmp, QID_DATA);
    length = sizeof(uint32_t) * (tmp[1] + 2);
    RTE_ASSERT(0 == pcxxDataAlloc(length, &a[0], &offset));
    memcpy(a[0], tmp, length);
    pcxxDataSend(offset, length);


    RTE_ASSERT(0 == pcxxCtrlAlloc(&a[1], &avail));
    A = (uint32_t *)a[1];
    produce_dl_src_data(A, QID_CTRL);
    length = sizeof(uint32_t) * (A[1] + 2);
    pcxxCtrlSend(a[1], length);

    pcxxSendEnd();

    while (-1 == pcxxCtrlRecv());

    int re = atl_test_result;
    atl_test_result = 0;
    free_blk(tmp);
    return re;
}

static int case3(void)
{
    uint32_t N;
    uint32_t *a[3];
    uint32_t *b[2];
    uint32_t length = 0;
    uint8_t type, eop;

    a[0] = alloc_tx_blk(QID_DATA);
    produce_dl_src_data(a[0], QID_DATA);
    N = sizeof(uint32_t) * (a[0][1] + 2);
    set_blk_attr(a[0], N, 0, 0);
    tx_blks(QID_DATA, &a[0], 1);

    a[1] = alloc_tx_blk(QID_DATA);
    produce_dl_src_data(a[1], QID_DATA);
    N = sizeof(uint32_t) * (a[1][1] + 2);
    set_blk_attr(a[1], N, 0, 1);
    tx_blks(QID_DATA, &a[1], 1);

    a[2] = alloc_tx_blk(QID_CTRL);
    produce_dl_src_data(a[2], QID_CTRL);
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

static int case103(void)
{
    char *a[3];
    uint32_t *A;
    uint32_t length;
    uint32_t offset;
    uint32_t avail;

    uint32_t *tmp = alloc_tx_blk(QID_DATA);

    pcxxSendStart();

    produce_dl_src_data(tmp, QID_DATA);
    length = sizeof(uint32_t) * (tmp[1] + 2);
    RTE_ASSERT(0 == pcxxDataAlloc(length, &a[0], &offset));
    memcpy(a[0], tmp, length);
    pcxxDataSend(offset, length);

    produce_dl_src_data(tmp, QID_DATA);
    length = sizeof(uint32_t) * (tmp[1] + 2);
    RTE_ASSERT(0 == pcxxDataAlloc(length, &a[1], &offset));
    memcpy(a[1], tmp, length);
    pcxxDataSend(offset, length);


    RTE_ASSERT(0 == pcxxCtrlAlloc(&a[2], &avail));
    A = (uint32_t *)a[2];
    produce_dl_src_data(A, QID_CTRL);
    length = sizeof(uint32_t) * (A[1] + 2);
    pcxxCtrlSend(a[2], length);

    pcxxSendEnd();

    while (-1 == pcxxCtrlRecv());

    int re = atl_test_result;
    atl_test_result = 0;
    free_blk(tmp);
    return re;
}
static int case4(uint16_t D)
{
    uint32_t N;
    uint32_t *a[17];
    uint32_t *b[2];
    int k;
    uint32_t length = 0;
    uint8_t  type, eop;

    if (D > 16) D = 16;

    for (k = 0; k < D; k++) {
        a[k] = alloc_tx_blk(QID_DATA);
        produce_dl_src_data(a[k], QID_DATA);
        N = sizeof(uint32_t) * (a[k][1] + 2);
        eop = k == (D-1);
        set_blk_attr(a[k], N, 0, eop);
        //printf("  Type=0  m=%u  EOP=%1u\n", k, eop);
        tx_blks(QID_DATA, &a[k], 1);
    }
    a[k] = alloc_tx_blk(QID_CTRL);
    produce_dl_src_data(a[k], QID_CTRL);
    N = sizeof(uint32_t) * (a[k][1] + 2);
    set_blk_attr(a[k], N, 1, 1);
    //printf("  Type=1  m=%u  EOP=1\n", k);
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

static int case104(uint16_t D)
{
    char *a[17];
    uint32_t *A;
    uint32_t length;
    uint32_t offset;
    uint32_t avail;
    int k;

    if (D > 16) D = 16;
    uint32_t *tmp = alloc_tx_blk(QID_DATA);

    pcxxSendStart();

    for (k = 0; k < D; k++) {
        produce_dl_src_data(tmp, QID_DATA);
        length = sizeof(uint32_t) * (tmp[1] + 2);
        RTE_ASSERT(0 == pcxxDataAlloc(length, &a[k], &offset));
        memcpy(a[k], tmp, length);
        pcxxDataSend(offset, length);
    }

    RTE_ASSERT(0 == pcxxCtrlAlloc(&a[k], &avail));
    A = (uint32_t *)a[k];
    produce_dl_src_data(A, QID_CTRL);
    length = sizeof(uint32_t) * (A[1] + 2);
    pcxxCtrlSend(a[k], length);

    pcxxSendEnd();

    while (-1 == pcxxCtrlRecv());

    int re = atl_test_result;
    atl_test_result = 0;
    free_blk(tmp);
    return re;
}

static int case5(void)
{
    uint32_t D;
    uint32_t L = (uint32_t)rand();
    L = 16 + (L & 7);

    //printf("Case 5 will execute Case 4 for %u times!\n", L);
    //n = 0;
    while (L) {
        D = (uint32_t)rand();
        D = (D & 15) + 1;
        L--;
        //printf("... Test Case 4 with %u users for No. %u, Left %u times.\n", D, n++, L);
        if (case4(D))
            return -1;
    }
    return 0;
}

static int case105(void)
{
    uint32_t D;
    uint32_t L = (uint32_t)rand();
    L = 16 + (L & 7);

    //printf("Case 105 will execute Case 104 for %u times!\n", L);
    //n = 0;
    while (L) {
        D = (uint32_t)rand();
        D = (D & 15) + 1;
        L--;
        //printf("... Test Case 104 with %u users for No. %u, Left %u times\n", D, n++, L);
        if (case104(D))
            return -1;
    }
    return 0;
}

static int case201(void)
{
    struct rte_mbuf *tx_pkts[16];
    struct rte_mbuf *rx_pkts[16];
    uint32_t n;
    uint32_t N, M;
    uint16_t offset;
    uint8_t *tx_src_addr;
    uint8_t *tx_dst_addr;
    uint8_t *rx_dst_addr;
    uint8_t *rx_src_addr;
    uint16_t *tx_type;
    uint16_t *rx_type;
    uint16_t *tx_sdata;
    uint32_t *tx_data;
    uint8_t  *tx_cdata;
    uint8_t  *rx_cdata;
    uint16_t tx_length;
    uint16_t rx_length;
    uint16_t k;
    uint8_t tdata;
    uint8_t rdata;
    int ret = 0;

    N = (uint32_t)rand();
    N = 1 + (N & 7);
    for (n = 0; n < N; n++) {
        tx_pkts[n] = rte_mbuf_raw_alloc(mpool_pc802_tx);
        rte_pktmbuf_reset_headroom(tx_pkts[n]);

        offset = 0;
        tx_dst_addr = rte_pktmbuf_mtod_offset(tx_pkts[n], uint8_t *, offset);
        offset += 6;
        rte_eth_random_addr(tx_dst_addr);

        tx_src_addr = rte_pktmbuf_mtod_offset(tx_pkts[n], uint8_t *, offset);
        offset += 6;
        rte_eth_random_addr(tx_src_addr);

        tx_type = rte_pktmbuf_mtod_offset(tx_pkts[n], uint16_t *, offset);
        offset += 2;
        *tx_type = (uint16_t)rand();

        tx_length = 46 + ((uint32_t)rand())% 1455;
        tx_sdata = rte_pktmbuf_mtod_offset(tx_pkts[n], uint16_t *, offset);
        offset += 2;
        *tx_sdata = (uint16_t)rand();

        tx_data = rte_pktmbuf_mtod_offset(tx_pkts[n], uint32_t *, offset);
        for (k = 2; k < tx_length; k += sizeof(uint32_t))
            *tx_data++ = (uint32_t)rand();

        tx_pkts[n]->nb_segs = 1;
        tx_pkts[n]->pkt_len = tx_pkts[n]->data_len = 14 + tx_length;
        tx_pkts[n]->next = NULL;
#if 0
        DBLOG("TX-pkt[%u]: DST-Addr = %02X %02X %02X %02X %02X %02X\n",
            n, tx_dst_addr[0], tx_dst_addr[1], tx_dst_addr[2],
            tx_dst_addr[3], tx_dst_addr[4], tx_dst_addr[5]);
        DBLOG("TX-pkt[%u]: SRC-Addr = %02X %02X %02X %02X %02X %02X\n",
            n, tx_src_addr[0], tx_src_addr[1], tx_src_addr[2],
            tx_src_addr[3], tx_src_addr[4], tx_src_addr[5]);
        DBLOG("TX-pkt[%u]: Type = %04X, Data-Len = %u\n", n, *tx_type, tx_length);
#endif
    }
    RTE_ASSERT(N == rte_eth_tx_burst(0, 0, tx_pkts, N));

    k = 0;
    M = N;
    do {
        n = rte_eth_rx_burst(0, 0, &rx_pkts[k], M);
        k += n;
        M -= n;
    } while (M);

    for (n = 0; n < N; n++) {
        if (rx_pkts[n]->pkt_len != tx_pkts[n]->pkt_len) {
            DBLOG("Wrong pkt %u: rx_pkt_len = %u, tx_pkt_len = %u\n",
                n, rx_pkts[n]->pkt_len, tx_pkts[n]->pkt_len);
            ret = -1;
            break;
        }

        offset = 0;
        tx_dst_addr = rte_pktmbuf_mtod_offset(tx_pkts[n], uint8_t *, offset);
        rx_dst_addr = rte_pktmbuf_mtod_offset(rx_pkts[n], uint8_t *, offset);
        offset += 6;

        tx_src_addr = rte_pktmbuf_mtod_offset(tx_pkts[n], uint8_t *, offset);
        rx_src_addr = rte_pktmbuf_mtod_offset(rx_pkts[n], uint8_t *, offset);
        offset += 6;

        for (k = 0; k < 6; k++) {
            if (rx_dst_addr[k] != tx_src_addr[k]) {
                DBLOG("Wrong pkt %u: rx_dst_addr[%hu] = 0x%02X tx_src_addr[%hu] = 0x%02X\n",
                    n, k, rx_dst_addr[k], k, tx_src_addr[k]);
                ret = -2;
                break;
            }
        }
        if (ret) break;

        for (k = 0; k < 6; k++) {
            if (rx_src_addr[k] != tx_dst_addr[k]) {
                DBLOG("Wrong pkt %u: rx_src_addr[%hu] = 0x%02X tx_dst_addr[%hu] = 0x%02X\n",
                    n, k, rx_src_addr[k], k, tx_dst_addr[k]);
                ret = -3;
                break;
            }
        }
        if (ret) break;

        tx_type = rte_pktmbuf_mtod_offset(tx_pkts[n], uint16_t *, offset);
        rx_type = rte_pktmbuf_mtod_offset(rx_pkts[n], uint16_t *, offset);
        offset += 2;
        if (*tx_type != *rx_type) {
            DBLOG("Wrong pkt %u: tx_type = 0x%04X rx_type = 0x%04X\n",
                n, *tx_type, *rx_type);
            ret = -4;
            break;
        }

        tx_cdata = rte_pktmbuf_mtod_offset(tx_pkts[n], uint8_t *, offset);
        rx_cdata = rte_pktmbuf_mtod_offset(rx_pkts[n], uint8_t *, offset);
        k = 0;
        rx_length = rx_pkts[n]->pkt_len - 14;
        if (*tx_type == 0x0008) { //IP
            uint16_t hlen = 20;
            if (tx_cdata[9] == 0x17) //UDP
                hlen += 8;
            for (; k < hlen; k++) {
                if (tx_cdata[k] != rx_cdata[k]) {
                    DBLOG("Wrong pkt %u: IP/UDP Head: tx_data[%hu] = %02X rx_data[%hu] = %02X\n",
                        n, k, tx_cdata[k], k, rx_cdata[k]);
                    ret = -5;
                    break;
                }
            }
        }
        if (ret) break;

        for (; k < rx_length; k++) {
            tdata = tx_cdata[k];
            rdata = rx_cdata[k];
			tdata++;
            if (rdata != tdata) {
                DBLOG("Wrong pkt %u: tx_cdata[%hu] = 0x%02X rx_cdata[%hu] = 0x%02X\n",
                    n, k, tdata, k, rdata);
                ret = -6;
                break;
            }
        }
        if (ret) break;
        rte_pktmbuf_free(rx_pkts[n]);
    }
    for (; n < N; n++)
        rte_pktmbuf_free(rx_pkts[n]);

    return ret;
}

static int case301(void)
{
    char *a;
    uint32_t *A;
    uint32_t N;
    uint32_t avail;

    pcxxSendStart();
    RTE_ASSERT(0 == pcxxOamAlloc(&a, &avail));
    A = (uint32_t *)a;
    produce_dl_src_data(A, QID_OAM);
    N = sizeof(uint32_t) * (A[1] + 2);
    pcxxOamSend(a, N);
    pcxxSendEnd();

    while (-1 == pcxxOamRecv());
    int re = atl_test_result;
    atl_test_result = 0;
    return re;
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

#define disp_test_result(caseNo, result)  \
    if (result) { \
        DBLOG("Case %d --- FAILED\n", caseNo); \
        break; \
    } else { \
        DBLOG("Case %d --- PASSED\n", caseNo); \
    }

#define disp_if_fail(caseNo, result) \
    if (result) { \
        DBLOG("Case %d --- FAILED\n", caseNo); \
        break; \
    }

#define return_if_fail(case, result, looptimes) do {\
        if (result) { \
            DBLOG("Case %d -- FAILED -- Result = %d -- Loop = %u\n", case, result, looptimes); \
            return -case; \
        } \
    } while(0)

static int case_n1(void)
{
    int diag;
    diag = case201();
    return_if_fail(201, diag, 0);
    diag = case201();
    return_if_fail(201, diag, 0);
    diag = case201();
    return_if_fail(201, diag, 0);
    diag = case201();
    return_if_fail(201, diag, 0);
    diag = case201();
    return_if_fail(201, diag, 0);
    diag = case201();
    return_if_fail(201, diag, 0);
    diag = case201();
    return_if_fail(201, diag, 0);
    diag = case201();
    return_if_fail(201, diag, 0);
    diag = case1();
    return_if_fail(1, diag, 0);
    diag = case2();
    return_if_fail(2, diag, 0);
    diag = case3();
    return_if_fail(3, diag, 0);
    diag = case4(16);
    return_if_fail(4, diag, 0);
    diag = case5();
    return_if_fail(5, diag, 0);
    diag = case101();
    return_if_fail(101, diag, 0);
    diag = case102();
    return_if_fail(102, diag, 0);
    diag = case103();
    return_if_fail(103, diag, 0);
    diag = case104(16);
    return_if_fail(104, diag, 0);
    diag = case105();
    return_if_fail(105, diag, 0);
    return 0;
}

static int case_n2(void)
{
    int diag;
    diag = case201();
    return_if_fail(201, diag, 0);
    diag = case301();
    return_if_fail(301, diag, 0);
    diag = case1();
    return_if_fail(1, diag, 0);
    diag = case2();
    return_if_fail(2, diag, 0);
    diag = case3();
    return_if_fail(3, diag, 0);
    diag = case4(16);
    return_if_fail(4, diag, 0);
    return 0;
}

static int case_n800(void)
{
    uint32_t m, k;
    int diag;
    m = 0;
    k = 0;
    while (1) {
        diag = case301();
        return_if_fail(301, diag, k);
        diag = case1();
        return_if_fail(1, diag, k);
        diag = case2();
        return_if_fail(2, diag, k);
        diag = case3();
        return_if_fail(3, diag, k);
        diag = case4(16);
        return_if_fail(4, diag, k);
        m++;
        k++;
        if (TEST_PC802_DISP_LOOP_NUM == m) {
            DBLOG("Case -800 Passed %u Loops.\n", k);
            m = 0;
        }
        pc802_check_dma_timeout(0);
        if (testpc802_exit_loop) {
            DBLOG("Case -800 Passed %u Loops.\n", k+1);
            testpc802_exit_loop = 0;
            return 0;
        }
    }
    return 0;
}

static int case_n1000(void)
{
    uint32_t m, k, N;
    int diag;
    N = 100000;
    m = 0;
    for (k = 0; k < N; k++) {
        diag = case201();
        return_if_fail(201, diag, k);
        diag = case301();
        return_if_fail(301, diag, k);
        diag = case1();
        return_if_fail(1, diag, k);
        diag = case2();
        return_if_fail(2, diag, k);
        diag = case3();
        return_if_fail(3, diag, k);
        diag = case4(16);
        return_if_fail(4, diag, k);
        m++;
        if (TEST_PC802_DISP_LOOP_NUM == m) {
            DBLOG("Case -1000 Passed %u Loops.\n", k+1);
            m = 0;
        }
        pc802_check_dma_timeout(0);
        if (testpc802_exit_loop) {
            DBLOG("Case -1000 Passed %u Loops.\n", k+1);
            testpc802_exit_loop = 0;
            return 0;
        }
    }
    return 0;
}

static int case_n802(void)
{
    uint32_t m, k;
    int diag;
    m = 0;
    k = 0;
    while (1) {
        diag = case201();
        return_if_fail(201, diag, k);
        diag = case301();
        return_if_fail(301, diag, k);
        diag = case1();
        return_if_fail(1, diag, k);
        diag = case2();
        return_if_fail(2, diag, k);
        diag = case3();
        return_if_fail(3, diag, k);
        diag = case4(16);
        return_if_fail(4, diag, k);
        m++;
        k++;
        if (TEST_PC802_DISP_LOOP_NUM == m) {
            DBLOG("Case -802 Passed %u Loops.\n", k);
            m = 0;
        }
        pc802_check_dma_timeout(0);
        if (testpc802_exit_loop) {
            DBLOG("Case -802 Passed %u Loops.\n", k+1);
            testpc802_exit_loop = 0;
            return 0;
        }
    }
    return 0;
}

static int case_n2000(void)
{
    uint32_t m, k, N;
    int diag;
    N = 1000000;
    m = 0;
    for (k = 0; k < N; k++) {
        diag = case1();
        return_if_fail(1, diag, k);
        m++;
        if (TEST_PC802_DISP_LOOP_NUM == m) {
            DBLOG("Case 1 Passed %7d times.\n", k+1);
            m = 0;
        }
        pc802_check_dma_timeout(0);
        if (testpc802_exit_loop) {
            DBLOG("Case -2000 Passed %u Loops.\n", k+1);
            testpc802_exit_loop = 0;
            return 0;
        }
    }
    return 0;
}

static void run_case(int caseNo)
{
    int diag;
    if (0 == caseNo)
        return;
    printf("Begin Test Case %d\n", caseNo);
    switch(caseNo) {
    case 1:
        diag = case1();
        disp_test_result(caseNo, diag);
        break;
    case 2:
        diag = case2();
        disp_test_result(caseNo, diag);
        break;
    case 3:
        diag = case3();
        disp_test_result(caseNo, diag);
        break;
    case 4:
        diag = case4(16);
        disp_test_result(caseNo, diag);
        break;
    case 5:
        diag = case5();
        disp_test_result(caseNo, diag);
        break;
    case 101:
        diag = case101();
        disp_test_result(caseNo, diag);
        break;
    case 102:
        diag = case102();
        disp_test_result(caseNo, diag);
        break;
    case 103:
        diag = case103();
        disp_test_result(caseNo, diag);
        break;
    case 104:
        diag = case104(16);
        disp_test_result(caseNo, diag);
        break;
    case 105:
        diag = case105();
        disp_test_result(caseNo, diag);
        break;
    case 201:
        diag = case201();
        disp_test_result(201, diag);
        break;
    case 301:
        diag = case301();
        disp_test_result(301, diag);
        break;
    case -1:
        diag = case_n1();
        disp_test_result(-1, diag);
        break;
    case -2:
        diag = case_n2();
        disp_test_result(-2, diag);
        break;
    case -800:
        diag = case_n800();
        disp_test_result(-800, diag);
        break;
    case -1000:
        diag = case_n1000();
        disp_test_result(-1000, diag);
        break;
    case -802:
        diag = case_n802();
        disp_test_result(-802, diag);
        break;
   case -2000:
        diag = case_n2000();
        disp_test_result(-2000, diag);
        break;
    default:
        DBLOG("Wrong case number, it should be 1/2/3/4/5/101/102/103/104/105/-1/-2\n");
    }
    test_case_No = 0;
}

int main_stop = 0;

void test_pc802_mem_dump(uint32_t          pc802_mem, uint32_t byte_num);

void test_pc802_mem_dump(uint32_t          pc802_mem, uint32_t byte_num)
{
    uint32_t *pd = (uint32_t *)pc802_get_debug_mem(0);
    uint32_t k, n;
    if (byte_num > ((uint32_t)160 << 20)) {
        DBLOG("The size for mem dump should be <= 160 M bytes !\n");
        return;
    }
    uint64_t *p0 = rte_malloc("test_memdump", byte_num, 8);
    if (NULL == p0) {
        DBLOG("Out of memory!\n");
        return;
    }
    for (n = k = 0; k < byte_num; k += sizeof(uint32_t), n++)
        pd[n] = rand();
    DBLOG("pd = %p p0 = %p\n", pd, p0);
    memcpy(p0, pd, byte_num);
    pc802_access_ep_mem(0, pc802_mem, byte_num, DIR_PCIE_DMA_DOWNLINK);

    PC802_Mem_Block_t *mblk;
    mblk = pc802_alloc_tx_mem_block(0, PC802_TRAFFIC_OAM);
    if (NULL == mblk) {
        DBLOG("Test MemDump Failed !\n");
        return;
    }
    uint32_t *msg = (uint32_t *)&mblk[1];
    msg[0] = 0x4b3c2d1e;
    msg[1] = 0;
    msg[2] = pc802_mem;
    msg[3] = byte_num;
    mblk->pkt_length = 16;
    mblk->pkt_type = 2;
    mblk->eop = 1;
    pc802_tx_mblk_burst(0, PC802_TRAFFIC_OAM, &mblk, 1);

    uint16_t P;
    do {
        P = pc802_rx_mblk_burst(0, PC802_TRAFFIC_OAM, &mblk, 1);
    } while (0 == P);
    msg = (uint32_t *)&mblk[1];
    if (  (msg[0] != 0x4b3c2d1e)
        ||(msg[1] != 0)
        ||(msg[2] != pc802_mem)
        ||(msg[3] != byte_num)) {
        DBLOG("Test MemDump Failed !\n");
        pc802_free_mem_block(mblk);
        return;
    }

    memset(pd, 0, byte_num);

    pc802_access_ep_mem(0, pc802_mem, byte_num, DIR_PCIE_DMA_UPLINK);

    uint8_t *ps = (uint8_t *)p0;
    uint8_t *pt = (uint8_t *)pd;
    for (k = 0; k < byte_num; k++) {
        if (ps[k] != pt[k]) {
            DBLOG("Test MemDump Failed at k = %u !\n", k);
            pc802_free_mem_block(mblk);
            return;
        }
    }

    pc802_free_mem_block(mblk);
    rte_free(p0);

    mblk = pc802_alloc_tx_mem_block(0, PC802_TRAFFIC_OAM);
    if (NULL == mblk) {
        DBLOG("Test MemDump Failed !\n");
        return;
    }
    msg = (uint32_t *)&mblk[1];
    msg[0] = 0x4b3c2d1e;
    msg[1] = 100;
    mblk->pkt_length = 8;
    mblk->pkt_type = 2;
    mblk->eop = 1;
    pc802_tx_mblk_burst(0, PC802_TRAFFIC_OAM, &mblk, 1);

    do {
        P = pc802_rx_mblk_burst(0, PC802_TRAFFIC_OAM, &mblk, 1);
    } while (0 == P);
    msg = (uint32_t *)&mblk[1];
    if (  (msg[0] != 0x4b3c2d1e)
        ||(msg[1] != 100)) {
        DBLOG("Test MemDump Failed !\n");
        pc802_free_mem_block(mblk);
        return;
    }
    pc802_free_mem_block(mblk);
    DBLOG("Test memdump Passed when address = 0x%08X length = %u\n",
        pc802_mem, byte_num);
}

int main(int argc, char** argv)
{
    int diag;

    printf("%s\n", picocom_pc802_version());
    printf("PC802 Driver Tester built AT %s ON %s\n", __TIME__, __DATE__);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    diag = rte_eal_init(argc, argv);
    if (diag < 0)
        rte_panic("Cannot init EAL\n");

    port_init(0);

    rte_eal_remote_launch(prompt, NULL, 1);

    while(!main_stop) {
        usleep(10);
        run_case(test_case_No);
    }

    usleep(5000);

    return 0;
}

