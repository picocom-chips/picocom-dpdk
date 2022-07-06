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
#include <semaphore.h>

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
#include <pc802_oam_lib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define TEST_PC802_DISP_LOOP_NUM    10000

int testpc802_data_mode = 0;
int testpc802_exit_loop = 0;

struct rte_mempool *mpool_pc802_tx;

#define MAX_DATA_BUF_SZ (256*1024)

extern void odu_cmd_main(void); 

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
static uint32_t process_ul_data_msg(const char* buf, uint32_t payloadSize);
static uint32_t process_dl_data_msg(const char* buf, uint32_t payloadSize);

static pcxxInfo_s   ctrl_cb_info = {process_ul_ctrl_msg, process_dl_ctrl_msg};
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

    pc802_oam_init( );

    rte_eth_dev_start(port);

    printf("Finished port_init !\n");

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

#define QID_DATA    PC802_TRAFFIC_5G_EMBB_DATA
#define QID_CTRL    PC802_TRAFFIC_5G_EMBB_CTRL
#define QID_OAM     PC802_TRAFFIC_OAM

static union {
    const char *cc;
    uint32_t   *up;
} dl_a[17];
static uint32_t dl_a_num = 0;

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

#ifdef SEND_TEST_MSG 

static int send_test_msg(const OamSubMessage_t *sub_msg)
{
    typedef enum{
        PICO_OAM_MSG=0x00,
        PICO_P19_MSG=0x01,
        PICO_DEBUG_MSG=0x02,
    }OamMessageType_e;

    #define OAM_START_FLAG      0xd1c2b3a4
    #define OAM_END_FLAG        0xa4b3c2d1

    typedef struct{
        uint32_t StartFlag;         //0xd1c2b3a4
        uint32_t MsgType;
        uint32_t SubMsgNum;		    //Message burst
    }OamMessageHeader_t;

    typedef struct{
        OamMessageHeader_t Head;
        OamSubMessage_t SubMsg[0];
        uint32_t EndFlag;           //0xa4b3c2d1
    }OamMessage_t;

    PC802_Mem_Block_t *mbuf;
    OamMessage_t *msg = NULL;
    uint32_t *end = NULL;

    mbuf = pc802_alloc_tx_mem_block(0, PC802_TRAFFIC_OAM);
    msg = (OamMessage_t *)&mbuf[1];

    msg->Head.StartFlag = OAM_START_FLAG;
    msg->Head.MsgType = PICO_OAM_MSG;
    msg->Head.SubMsgNum = 1;

    memcpy(msg->SubMsg, sub_msg, sub_msg->Head.MsgSize+sizeof(OamSubMessageHeader_t));

    end = (uint32_t *)((char *)msg->SubMsg + sub_msg->Head.MsgSize+sizeof(OamSubMessageHeader_t));
    *end = OAM_END_FLAG;

    mbuf->pkt_length = sub_msg->Head.MsgSize+sizeof(OamSubMessageHeader_t) + sizeof(OamMessage_t);
    mbuf->pkt_type = 0xa5;
    mbuf->eop = 1;
    pc802_tx_mblk_burst(0, PC802_TRAFFIC_OAM, &mbuf, 1);

    return 0;
}
#endif

typedef struct {
    sem_t sem;
    OamSubMessage_t msg;
}oam_obj;

static int32_t oam_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf( "Oam %d call back %d sub mesg\n", port_id, msg_num );
    memcpy( &((oam_obj *)arg)->msg, sub_msg[0], sub_msg[0]->Head.MsgSize );
    sem_post( &((oam_obj *)arg)->sem );
    return 0;
}

static int case310(void)
{
#ifdef SEND_TEST_MSG 
    OamSubMessage_t rsp_msg = {0};
    rsp_msg.Head.MsgId=BASIC_CFG_GET_RSP;
    rsp_msg.Head.MsgSize=sizeof(OamErrorInd_t);
    rsp_msg.u.result.err_code = 0;
#endif
    int ret = -1;
    oam_obj obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    //pc802_oam_init();

    sem_init( &obj.sem, 0, 0);

    pc802_oam_sub_msg_register( BASIC_CFG_GET_RSP, oam_rsp, &obj );

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = BASIC_CFG_GET_REQ;
    sub_msg.Head.MsgSize = sizeof(BasicCfg_t);
    sub_msg.u.basic_cfg.pcie_enable = 1;
    sub_msg.u.basic_cfg.eth_type = 1;
    if ( 0== pc802_oam_send_msg( 0, &list, 1 ) ) {
#ifdef SEND_TEST_MSG 
        send_test_msg( &rsp_msg );    //for test
#endif
        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == obj.msg.u.result.err_code ){
                printf( "BASIC_CFG_GET_RSP ok.\n" );
                ret = 0;
            }
            else
                printf( "BASIC_CFG_GET_RSP err(%d)!\n", obj.msg.u.result.err_code );
        }
        else
            printf( "BASIC_CFG_GET_RSP recv timeout!\n" );
    }
    else
        printf( "BASIC_CFG_GET_RSP send err!\n" );

    pc802_oam_sub_msg_unregister( BASIC_CFG_GET_RSP );

    return ret;
}

static int prompt(void* arg)
{

    arg = arg;

    odu_cmd_main();

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

static void run_case(int caseNo)
{
    int diag;
    if (0 == caseNo)
        return;
    printf("Begin Test Case %d\n", caseNo);
    switch(caseNo) {
    case 301:
        diag = case301();
        disp_test_result(301, diag);
        break;
    case 310:
        diag = case310();
        disp_test_result(301, diag);
        break;
    default:
        DBLOG("Wrong case number, it should be 301/310\n");
    }
    test_case_No = 0;
}

int main_stop = 0;


int main(int argc, char** argv)
{
    int diag;

    printf("%s\n", picocom_pc802_version());
    printf("PC802 OAM tester built AT %s ON %s\n", __TIME__, __DATE__);

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
