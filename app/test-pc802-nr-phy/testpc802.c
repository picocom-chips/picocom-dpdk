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

static uint32_t random_dl_msg_length(void)
{
    uint32_t N;
    N = (uint32_t)rand();
    N &= 511;
    if (N < 10) N = 10;
    if (N > 500) N = 500;
    return (N + 2)* sizeof(uint32_t);
}

static int produce_random_dl_src_data(uint32_t *buf, uint32_t msg_length)
{
    //static uint32_t idx = 0;
    uint32_t N, s, d, k;
    do {
        s = (uint32_t)rand();
    } while (s == 0x4b3c2d1e);
    *buf++ = s;
    N = msg_length / sizeof(uint32_t) - 2;
    *buf++ = N;
    d = (uint32_t)rand();
    //printf("DL_MSG[1][%3u]: N=%3u S=0x%08X D=0x%08X\n", idx++, N, s, d);
    for (k = 0; k < N; k++) {
        *buf++ = d;
        d += s;
    }
    return 0;
}

static int produce_dl_src_data(uint32_t *buf, uint16_t qId, uint32_t msg_length)
{
    produce_random_dl_src_data(buf, msg_length);
    return 0;
}

static int check_ul_msg(const char *buf)
{
    uint32_t *msg = (uint32_t *)buf;
    uint32_t d = msg[0];
    uint32_t N = msg[1];
    uint32_t e = msg[2];
    int k;
    int M = (int)N;
    uint32_t *p = &msg[3];
    e += d;

    for (k = 1; k < M; k++) {
        if (p[0] != e)
            return k;
        p++;
        e += d;
    }

    return 0;
}

extern PC802_Traffic_Type_e QID_DATA[];
extern PC802_Traffic_Type_e QID_CTRL[];
#define QID_OAM     PC802_TRAFFIC_OAM

#define VOID(a) a = a

static uint32_t __process_dl_ctrl_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    VOID(buf);
    VOID(payloadSize);
    VOID(dev_index);
    VOID(cell_index);

    return 0;
}

static uint32_t __process_ul_ctrl_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    VOID(payloadSize);
    VOID(dev_index);
    VOID(cell_index);

    int r;
    r = check_ul_msg(buf);
    if (0 != r) {
        printf("ERROR, r = %d\n", r);
    }

    return payloadSize;
}

static uint32_t __process_dl_oam_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, __rte_unused uint16_t cell_index )
{
    VOID(buf);
    VOID(payloadSize);
    VOID(dev_index);
    VOID(cell_index);

    return 0;
}

static uint32_t __process_ul_oam_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    VOID(buf);
    VOID(payloadSize);
    VOID(dev_index);
    VOID(cell_index);

    return payloadSize;
}

static uint32_t __process_dl_data_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    VOID(buf);
    VOID(payloadSize);
    VOID(dev_index);
    VOID(cell_index);

    return 0;
}

static uint32_t __process_ul_data_msg(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index )
{
    VOID(payloadSize);
    VOID(dev_index);
    VOID(cell_index);

    int r;
    r = check_ul_msg(buf);
    if (0 != r) {
        printf("ERROR, r = %d\n", r);
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

int start_flag = 0;
int quit_flag = 0;

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
    int prev_start = start_flag;

    arg  = arg;
    M = N = 0;
    cycle_start = rte_rdtsc();
    do {
        if ((0 != prev_start) && (0 == start_flag)) {
            DBLOG("Have Tx %u slots before stopping \n", M);
            prev_start = 0;
        }
        while (0 == start_flag);
        prev_start = 1;

        PCXX_CALL(pcxxSendStart,g_pc802_index, g_cell_index);

        for (k = 0; k < 16; k++) {
            length = random_dl_msg_length();
            RTE_ASSERT(0 == pcxxDataAlloc(length, (char **)&a[k], &offset, g_pc802_index, g_cell_index));
            produce_dl_src_data(a[k], QID_DATA[g_cell_index], length);
            pcxxDataSend(offset, length, g_pc802_index, g_cell_index);
        }

        RTE_ASSERT(0 == pcxxCtrlAlloc((char **)&a[k], &avail, g_pc802_index, g_cell_index));
        length = random_dl_msg_length();
        produce_dl_src_data(a[k], QID_CTRL[g_cell_index], length);
        pcxxCtrlSend((const char *)a[k], length, g_pc802_index, g_cell_index);

        do {
            cycle_curr = rte_rdtsc();
            cycle_diff = cycle_curr- cycle_start;
        } while (cycle_diff < cycles_of_a_slot);
        cycle_start += cycles_of_a_slot;

        PCXX_CALL(pcxxSendEnd,g_pc802_index, g_cell_index);
        N++;
        M++;
        if (N == 20000) { //10 seconds
            DBLOG("Have Tx %u slots\n", M);
            N = 0;
        }
    }while(0 == quit_flag);
}

static int ul_worker(void *arg)
{
    int prev_start = start_flag;
    uint32_t N;
    uint32_t M;

    M = N = 0;
    arg = arg;
    do {
        if ((0 != prev_start) && (0 == start_flag)) {
            DBLOG("Have Rx %u slots before stopping \n", M);
            prev_start = 0;
        }
        prev_start = start_flag;

        while (-1 == PCXX_CALL(pcxxCtrlRecv,g_pc802_index, g_cell_index));
        N++;
        M++;
        if (N == 20000) { //10 seconds
            DBLOG("Have Rx %u slots\n", M);
            N = 0;
        }
    } while(0 == quit_flag);
    return 0;
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

static unsigned int get_a_isolated_lcore(void)
{
    FILE *fp = NULL;
    char buffer[128] = {0};
    char *ret = NULL;
    static unsigned int min = 0xFFFF;
    static unsigned int max;
    unsigned int lcore;

    if (0xFFFF == min) {
        fp = popen("cat /sys/devices/system/cpu/isolated", "r");
        ret = fgets(buffer, sizeof(buffer), fp);
        pclose(fp);
        sscanf( buffer, "%u-%u", &min, &max);
    }
    if (min <= max) {
        lcore = min;
        min++;
    } else {
        lcore = max;
    }
    return lcore;
}

int main(int argc, char** argv)
{
    int diag;
    int port_id = 0;
    int pc802_index = 0;
    uint64_t hz;
    unsigned int lcore;

    printf("%s\n", picocom_pc802_version());
    printf("PC802 Driver Tester built AT %s ON %s\n", __TIME__, __DATE__);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    diag = rte_eal_init(argc, argv);
    if (diag < 0)
        rte_panic("Cannot init EAL\n");

    hz = rte_get_timer_hz();
    cycles_of_a_slot = hz / 2000;  //0.5ms
    NPU_SYSLOG("NPU cycles_of_a_slot = %u\n", cycles_of_a_slot);

    for ( pc802_index=0; pc802_index<PC802_INDEX_MAX; pc802_index++ )
    {
        port_id = pc802_get_port_id(pc802_index);
        if (port_id < 0)
            break;

        port_init(pc802_index);
    }

    lcore = get_a_isolated_lcore();
    rte_eal_remote_launch(prompt, NULL, rte_lcore_count()-1);
    DBLOG("thread cmdline prompt is running on lcore = %u\n", lcore);

    lcore = get_a_isolated_lcore();
    rte_eal_remote_launch(dl_worker, NULL, lcore);
    DBLOG("thread dl_worker is running on lcore = %u\n", lcore);

    lcore = get_a_isolated_lcore();
    rte_eal_remote_launch(ul_worker, NULL, lcore);
    DBLOG("thread ul_worker is running on lcore = %u\n", lcore);

    while(0 == quit_flag) {
        usleep(10);
    }

    usleep(5000);

    return 0;
}
