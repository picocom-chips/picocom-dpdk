/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <signal.h>
#include <semaphore.h>
#include <unistd.h>

#include <rte_common.h>
#include <rte_ethdev.h>
#include <rte_pmd_pc802.h>
#include <pcxx_ipc.h>
#include <pc802_oam_lib.h>

#include "ecpri_oam_inf.h"

extern void odu_cmd_main(void);

static void signal_handler(int signum)
{
    if ( signum == SIGINT || signum == SIGTERM ) {
        printf( "\n\nSignal %d received, preparing to exit...\n", signum );
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

static int port_init( uint16_t pc802_index )
{
    static pcxxInfo_s   ctrl_cb_info = {NULL, NULL};
    static pcxxInfo_s   data_cb_info = {NULL, NULL};
    struct rte_mempool *mbuf_pool;
    struct rte_eth_dev_info dev_info;
    struct rte_eth_txconf tx_conf;
    char temp_name[32] = {0};
    int socket_id;
    uint16_t cell;
    int port = pc802_get_port_id(pc802_index);
    if ( port < 0 )
        rte_exit( EXIT_FAILURE, "pc802 %d is notexist !\n", pc802_index );

    rte_eth_dev_info_get(port, &dev_info);
    socket_id = dev_info.device->numa_node;

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
    rte_eth_dev_start(port);

    printf("Finished %d port_init !\n", pc802_index );

    return 0;
}

static int32_t oam_rsp( void *arg, uint16_t port_id, uint32_t msg_type, const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num )
{
    const OamSubMessage_t *sub = (const OamSubMessage_t *)sub_msg[0];
    printf( "Dev %d recv oam msg %d include %u sub mesg\n", port_id, msg_type, msg_num );
    if ( ECPRI_ERR_IND == sub->Head.MsgId ) {
        if ( 0 == sub->u.result.err_code )
            printf( "oam rsp ok.\n" );
        else
            printf( "oam rsp err(%d)!\n", sub->u.result.err_code );
    }
    sem_post( (sem_t *)arg );
    return 0;
}

static int case310(void)
{
    int ret = -1;
    sem_t sem;
    OamSubMessage_t sub_msg;
    const pcxx_oam_sub_msg_t *list = (pcxx_oam_sub_msg_t*)&sub_msg;
    struct timespec ts;

    sem_init( &sem, 0, 0);

    pcxx_oam_register( PCXX_OAM_MSG, oam_rsp, &sem );

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = BASIC_CFG_GET_REQ;
    sub_msg.Head.MsgSize = sizeof(BasicCfg_t);
    sub_msg.u.basic_cfg.pcie_enable = 1;
    sub_msg.u.basic_cfg.eth_type = 1;
    if ( 0== pcxx_oam_send_msg(0, PCXX_OAM_MSG, &list, 1 ) ) {
        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 != sem_timedwait(&sem, &ts) )
            printf( "Oam wait rsp msg timeout!\n" );
        ret = 0;
    }
    else
        printf( "Oam send msg err!\n" );

    pcxx_oam_unregister(PCXX_OAM_MSG);
    return ret;
}

static int prompt(void* arg __rte_unused)
{
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
    case 310:
        diag = case310();
        disp_test_result(310, diag);
        break;
    default:
        DBLOG("Wrong case number, it should be 310\n");
    }
    test_case_No = 0;
}

int main_stop = 0;

int main(int argc, char** argv)
{
    int diag;
    int port_id = 0;
    int pc802_index = 0;

    printf("PC802 OAM tester built AT %s ON %s\n", __TIME__, __DATE__);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    diag = rte_eal_init(argc, argv);
    if (diag < 0)
        rte_panic("Cannot init EAL\n");

    pcxx_oam_init();
    for ( pc802_index=0; pc802_index<PC802_INDEX_MAX; pc802_index++ )
    {
        port_id = pc802_get_port_id(pc802_index);
        if (port_id < 0)
            break;
        port_init(pc802_index);
    }

    rte_eal_remote_launch(prompt, NULL, rte_lcore_count()-1);

    while(!main_stop) {
        usleep(10);
        run_case(test_case_No);
    }

	rte_eal_mp_wait_lcore();
	//rte_eal_cleanup();
    return 0;
}
