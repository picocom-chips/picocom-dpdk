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
static uint32_t cycles_of_a_slot; //0.5ms

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

#ifdef MULTI_PC802
#define PCXX_CALL0(fun,dev) fun(dev)
#define PCXX_CALL(fun,dev,cell) fun(dev,cell)
static uint32_t process_ul_ctrl_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index );
static uint32_t process_dl_ctrl_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index );
static uint32_t process_ul_oam_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index );
static uint32_t process_dl_oam_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index );
static uint32_t process_ul_data_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index );
static uint32_t process_dl_data_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index );
#else
#define PCXX_CALL0(fun,dev) fun()
#define PCXX_CALL(fun,dev,cell) fun()
static uint32_t process_ul_ctrl_msg(const char* buf, uint32_t payloadSize);
static uint32_t process_dl_ctrl_msg(const char* buf, uint32_t payloadSize);
static uint32_t process_ul_oam_msg(const char* buf, uint32_t payloadSize);
static uint32_t process_dl_oam_msg(const char* buf, uint32_t payloadSize);
static uint32_t process_ul_data_msg(const char* buf, uint32_t payloadSize);
static uint32_t process_dl_data_msg(const char* buf, uint32_t payloadSize);
#endif

static pcxxInfo_s   ctrl_cb_info = {process_ul_ctrl_msg, process_dl_ctrl_msg};
static pcxxInfo_s   oam_cb_info  = {process_ul_oam_msg,  process_dl_oam_msg };
static pcxxInfo_s   data_cb_info = {process_ul_data_msg, process_dl_data_msg};
uint16_t g_pc802_index = 0;
uint16_t g_cell_index = 0;

static int port_init( uint16_t pc802_index )
{
    struct rte_mempool *mbuf_pool;
    //const struct rte_eth_conf dev_conf;
    struct rte_eth_dev_info dev_info;
    struct rte_eth_txconf tx_conf;
    //const struct rte_eth_rxconf rx_conf;
    char temp_name[32] = {0};
    int socket_id;
    uint16_t cell;
    int port = pc802_get_port_id(pc802_index);
    if ( port < 0 )
        rte_exit( EXIT_FAILURE, "pc802 %d is notexist !\n", pc802_index );

    rte_eth_dev_info_get(port, &dev_info);
    socket_id = dev_info.device->numa_node;

    sprintf(temp_name, "MBUF_POOL_ETH%d_TX", pc802_index );
    mbuf_pool = rte_pktmbuf_pool_create(temp_name, 2048,
            128, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on Line %d\n", __LINE__);
    mpool_pc802_tx = mbuf_pool;

    sprintf(temp_name, "MBUF_POOL_ETH%d_RX", pc802_index );
    mbuf_pool = rte_pktmbuf_pool_create(temp_name, 2048,
            128 , 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on Line %d\n", __LINE__);

    rte_eth_dev_configure(port, 1, 1, &dev_conf);
    tx_conf = dev_info.default_txconf;
    rte_eth_tx_queue_setup(port, 0, 128, socket_id, &tx_conf);
    rte_eth_rx_queue_setup(port, 0, 128, socket_id, NULL, mbuf_pool);

    for (cell = 0; cell < CELL_NUM_PRE_DEV; cell++)
    {
        pcxxDataOpen(&data_cb_info, pc802_index, cell);
        pcxxCtrlOpen(&ctrl_cb_info, pc802_index, cell);
    }
    pcxxOamOpen(&oam_cb_info, pc802_index);

    rte_eth_dev_start(port);

    printf("Finished %d port_init !\n", pc802_index );

    return 0;
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

extern PC802_Traffic_Type_e QID_DATA[];
extern PC802_Traffic_Type_e QID_CTRL[];
#define QID_OAM     PC802_TRAFFIC_OAM

static union {
    const char *cc;
    uint32_t   *up;
} dl_a[PC802_INDEX_MAX][CELL_NUM_PRE_DEV][17];
static uint32_t dl_a_num[PC802_INDEX_MAX][CELL_NUM_PRE_DEV] = {0};
static union {
    const char *cc;
    uint32_t   *up;
} dl_oam[PC802_INDEX_MAX][32];
static uint32_t dl_oam_num[PC802_INDEX_MAX] = {0};

static int atl_test_result[PC802_INDEX_MAX][CELL_NUM_PRE_DEV] = {0};

static uint32_t __process_dl_ctrl_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    payloadSize = payloadSize;
    dl_a[dev_index][cell_index][dl_a_num[dev_index][cell_index]].cc = buf;
    dl_a_num[dev_index][cell_index]++;
    return 0;
}

static uint32_t __process_ul_ctrl_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    uint64_t addr = (uint64_t)buf;
    uint32_t *ul_msg = (uint32_t *)addr;
    swap_msg(ul_msg, payloadSize);
    uint32_t *dl_msg;
    dl_msg = dl_a[dev_index][cell_index][dl_a_num[dev_index][cell_index] - 1].up;
    if (check_same(&dl_msg, 1, ul_msg)) {
        atl_test_result[dev_index][cell_index] |= 1;
    }
    dl_a_num[dev_index][cell_index] = 0;
    return payloadSize;
}

static uint32_t __process_dl_oam_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, __rte_unused uint16_t cell_index )
{
    buf = buf;
    payloadSize = payloadSize;
    dl_oam[dev_index][dl_oam_num[dev_index]].cc = buf;
    dl_oam_num[dev_index]++;
    return 0;
}

static uint32_t __process_ul_oam_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    uint64_t addr = (uint64_t)buf;
    uint32_t *ul_msg = (uint32_t *)addr;
    swap_msg(ul_msg, payloadSize);
    uint32_t **dl_msg;
    dl_msg = &dl_oam[dev_index][0].up;
    if (check_same(dl_msg, dl_oam_num[dev_index], ul_msg)) {
        atl_test_result[dev_index][cell_index] |= 4;
    }
    dl_oam_num[dev_index] = 0;
    return payloadSize;
}

static uint32_t __process_dl_data_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    payloadSize = payloadSize;
    dl_a[dev_index][cell_index][dl_a_num[dev_index][cell_index]].cc = buf;
    dl_a_num[dev_index][cell_index]++;
    return 0;
}

static uint32_t __process_ul_data_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    uint64_t addr = (uint64_t)buf;
    uint32_t *ul_msg = (uint32_t *)addr;
    swap_msg(ul_msg, payloadSize);
    uint32_t **dl_msg;
    dl_msg = &dl_a[dev_index][cell_index][0].up;
    if (check_same(dl_msg, dl_a_num[dev_index][cell_index] - 1, ul_msg)) {
        atl_test_result[dev_index][cell_index] |= 2;
    }
    return payloadSize;
}

#ifdef MULTI_PC802
static uint32_t process_dl_ctrl_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    return __process_dl_ctrl_msg(buf, payloadSize, dev_index, cell_index);
}

static uint32_t process_ul_ctrl_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    return __process_ul_ctrl_msg(buf, payloadSize, dev_index, cell_index);
}

static uint32_t process_dl_oam_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, __rte_unused uint16_t cell_index )
{
    return __process_dl_oam_msg(buf, payloadSize, dev_index, cell_index );
}

static uint32_t process_ul_oam_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    return __process_ul_oam_msg(buf, payloadSize, dev_index, cell_index);
}

static uint32_t process_dl_data_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    return __process_dl_data_msg(buf, payloadSize, dev_index, cell_index);
}

static uint32_t process_ul_data_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    return __process_ul_data_msg(buf, payloadSize, dev_index, cell_index);
}
#else
static uint32_t process_dl_ctrl_msg(const char* buf, uint32_t payloadSize)
{
    return __process_dl_ctrl_msg(buf, payloadSize, 0, 0);
}

static uint32_t process_ul_ctrl_msg(const char* buf, uint32_t payloadSize)
{
    return __process_ul_ctrl_msg(buf, payloadSize, 0, 0);
}

static uint32_t process_dl_oam_msg(const char* buf, uint32_t payloadSize)
{
    return __process_dl_oam_msg(buf, payloadSize, 0, 0);
}

static uint32_t process_ul_oam_msg(const char* buf, uint32_t payloadSize )
{
    return __process_ul_oam_msg(buf, payloadSize, 0, 0);
}

static uint32_t process_dl_data_msg(const char* buf, uint32_t payloadSize)
{
    return __process_dl_data_msg(buf, payloadSize, 0, 0);
}

static uint32_t process_ul_data_msg(const char* buf, uint32_t payloadSize)
{
    return __process_ul_data_msg(buf, payloadSize, 0, 0);
}
#endif

static int dl_worker(void *arg)
{
    uint32_t *a[17];
    uint32_t length;
    uint32_t offset;
    uint32_t avail;
    int k;
    uint64_t cycle_start;
    uint64_t cycle_curr;
    uint32_t cycle_diff;
    uint32_t N;
    uint32_t M;

    arg  = arg;
    M = N = 0;
    cycle_start = rte_rdtsc();
    do {
        PCXX_CALL(pcxxSendStart,g_pc802_index, g_cell_index);

        for (k = 0; k < 16; k++) {
            RTE_ASSERT(0 == pcxxDataAlloc(length, (char **)&a[k], &offset, g_pc802_index, g_cell_index));
            produce_dl_src_data(a[k], QID_DATA[g_cell_index]);
            length = sizeof(uint32_t) * (a[k][1] + 2);
            pcxxDataSend(offset, length, g_pc802_index, g_cell_index);
        }

        RTE_ASSERT(0 == pcxxCtrlAlloc((char **)&a[k], &avail, g_pc802_index, g_cell_index));
        produce_dl_src_data(a[k], QID_CTRL[g_cell_index]);
        length = sizeof(uint32_t) * (a[k][1] + 2);
        pcxxCtrlSend((const char *)a[k], length, g_pc802_index, g_cell_index);

        PCXX_CALL(pcxxSendEnd,g_pc802_index, g_cell_index);
        N++;
        M++;
        if (N == 20000) { //10 seconds
            DBLOG("Have Tx %u slots\n", M);
            N = 0;
        }

        do {
            cycle_curr = rte_rdtsc();
            cycle_diff = cycle_curr- cycle_start;
        } while (cycle_diff < cycles_of_a_slot);
        cycle_start += cycles_of_a_slot;
    }while(1);
}

static int ul_worker(void *arg)
{
    arg = arg;
    do {
        while (-1 == PCXX_CALL(pcxxCtrlRecv,g_pc802_index, g_cell_index));
    } while(1);
    return 0;
}

int main(int argc, char** argv)
{
    int diag;
    int port_id = 0;
    int pc802_index = 0;

    uint64_t hz = rte_get_timer_hz();
    cycles_of_a_slot = hz / 2000;  //0.5ms

    printf("%s\n", picocom_pc802_version());
    printf("PC802 Driver Tester built AT %s ON %s\n", __TIME__, __DATE__);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    diag = rte_eal_init(argc, argv);
    if (diag < 0)
        rte_panic("Cannot init EAL\n");

    for ( pc802_index=0; pc802_index<PC802_INDEX_MAX; pc802_index++ )
    {
        port_id = pc802_get_port_id(pc802_index);
        if (port_id < 0)
            break;

        port_init(pc802_index);
    }
    rte_eal_remote_launch(dl_worker, NULL, 4);
    rte_eal_remote_launch(ul_worker, NULL, 5);

    while(1) {
        usleep(10);
    }

    usleep(5000);

    return 0;
}
