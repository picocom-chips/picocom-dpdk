#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <rte_debug.h>
#include <cmdline_parse.h>
#include <cmdline_parse_string.h>
#include <cmdline_parse_num.h>
#include <cmdline_socket.h>
#include <cmdline.h>

#include <rte_pmd_pc802.h>
#include <pc802_oam_lib.h>
#include <semaphore.h>
#include <cmdline_parse_etheraddr.h>
#include <rte_ether.h>



extern int main_stop;
extern int pc802_test_pcie( int len, int time, int ch, int type );
void odu_cmd_main(void);



struct cmd_quit_result {
    cmdline_fixed_string_t quit;
};

static void cmd_quit_parsed(__attribute__((unused)) void *parsed_result,
                struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    main_stop = 1;
    cmdline_quit(cl);
}

cmdline_parse_token_string_t cmd_quit_quit =
    TOKEN_STRING_INITIALIZER(struct cmd_quit_result, quit, "quit");

cmdline_parse_inst_t cmd_quit = {
    .f = cmd_quit_parsed,
    .data = NULL,
    .help_str = "quit: Exit application",
    .tokens = {
        (void *)&cmd_quit_quit,
        NULL,
    },
};

extern int test_case_No;

struct cmd_run_test_case_result {
    cmdline_fixed_string_t test;
    cmdline_fixed_string_t caze;
    int                    caseNo;
};

cmdline_parse_token_string_t cmd_run_test_case_result_test =
    TOKEN_STRING_INITIALIZER(struct cmd_run_test_case_result, test, "test");
cmdline_parse_token_string_t cmd_run_test_case_result_case =
    TOKEN_STRING_INITIALIZER(struct cmd_run_test_case_result, caze, "case");
cmdline_parse_token_num_t cmd_run_test_case_result_caseNo =
    TOKEN_NUM_INITIALIZER(struct cmd_run_test_case_result, caseNo, RTE_INT32);

static void cmd_run_test_case_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_run_test_case_result *res = parsed_result;
    test_case_No = res->caseNo;
}

cmdline_parse_inst_t run_test_case = {
    .f = cmd_run_test_case_parsed,
    .data = NULL,
    .help_str = "test case <case_number>",
    .tokens = {
        (void *)&cmd_run_test_case_result_test,
        (void *)&cmd_run_test_case_result_case,
        (void *)&cmd_run_test_case_result_caseNo,
        NULL,
        },
};


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
        uint32_t SubMsgNum;                 //Message burst
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

    if(sub_msg->Head.MsgSize > sizeof(OamSubMessage_t))
    {
    	memcpy(msg->SubMsg, sub_msg, sizeof(OamSubMessage_t));
    }
    else
    {  
    	memcpy(msg->SubMsg, sub_msg, sub_msg->Head.MsgSize);
    }

    end = (uint32_t *)((char *)msg->SubMsg + sub_msg->Head.MsgSize);
    *end = OAM_END_FLAG;

    mbuf->pkt_length = sub_msg->Head.MsgSize + sizeof(OamMessage_t);
    mbuf->pkt_type = 0xa5;
    mbuf->eop = 1;
    pc802_tx_mblk_burst(0, PC802_TRAFFIC_OAM, &mbuf, 1);

    return 0;
}

static void rsp_msg_test(uint16_t MsgId)
{
    OamSubMessage_t rsp_msg = {0};
    rsp_msg.Head.MsgId = MsgId;
    rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t)+sizeof(OamSubMessageHeader_t);
    rsp_msg.u.result.err_code = 0;
    send_test_msg(&rsp_msg);    //for test
}
#endif


#if 1

typedef struct {
    sem_t sem;
    OamSubMessage_t msg;
}oam_decode_data;

/* oam set ecpri tx rx cfg*/
static int32_t oam_set_ecpri_tx_rx_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int set_ecpri_tx_rx_cfg_handler(uint32_t maxTxLateThreshold)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);

    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_set_ecpri_tx_rx_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = TX_RX_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriTxRxCfg_t);
    sub_msg.u.tx_rx_cfg.maxTxLateThreshold = maxTxLateThreshold;

    if ( 0== pc802_oam_send_msg( 0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
        rsp_msg_test(TX_RX_SET_RSP);
#endif


        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == obj.msg.u.result.err_code )
                printf( "TX_RX_SET_REQ ok.\n" );
            else
                printf( "TX_RX_SET_RSP err(%d)!\n", obj.msg.u.result.err_code );
        }
        else
            printf( "TX_RX_SET_RSP recv timeout!\n" );
    }
    else
        printf( "TX_RX_SET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_ecpri_tx_rx_cfg {
    cmdline_fixed_string_t ecpri_tx_rx_cfg;
    uint32_t maxTxLateThreshold;
};

static void cmd_set_ecpri_tx_rx_cfg_parsed(void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_ecpri_tx_rx_cfg *cfg = (struct cmd_ecpri_tx_rx_cfg *)parsed;
    set_ecpri_tx_rx_cfg_handler(cfg->maxTxLateThreshold);
}

cmdline_parse_token_string_t cmd_set_ecpri_tx_rx_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_tx_rx_cfg, ecpri_tx_rx_cfg, "cfg tx rx");
cmdline_parse_token_num_t cmd_set_ecpri_tx_rx_cfg_maxTxLateThreshold =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_tx_rx_cfg, maxTxLateThreshold, RTE_UINT32);

cmdline_parse_inst_t set_ecpri_tx_rx_cfg = {
    .f = cmd_set_ecpri_tx_rx_cfg_parsed,
    .data = NULL,
    .help_str = "cfg tx rx <maxTxLateThreshold>",
    .tokens = {
	(void*) &cmd_set_ecpri_tx_rx_cfg,
        (void *)&cmd_set_ecpri_tx_rx_cfg_maxTxLateThreshold,
        NULL,
        },
};

/* oam set ecpri ptp cfg*/
static int32_t oam_set_ecpri_ptp_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg : msgid = %d size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgId, sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int set_ecpri_ptp_cfg_handler(uint8_t ptp_enable, uint8_t ptp_step_mode, uint8_t ecpri_step_mode, uint8_t ptp_domain)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_set_ecpri_ptp_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = PTP_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriPtpCfg_t);
    sub_msg.u.ptp_cfg.ptp_domain = ptp_domain;
    sub_msg.u.ptp_cfg.ptp_enable = ptp_enable;
    sub_msg.u.ptp_cfg.ptp_step_mode = ptp_step_mode;
    sub_msg.u.ptp_cfg.ecpri_step_mode = ecpri_step_mode;

    if ( 0== pc802_oam_send_msg(0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
        rsp_msg_test(PTP_SET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == obj.msg.u.result.err_code )
                printf( "PTP_SET_REQ ok.\n" );
            else
                printf( "PTP_SET_RSP err(%d)!\n", obj.msg.u.result.err_code );
        }
        else
            printf( "PTP_SET_RSP recv timeout!\n" );
    }
    else
        printf( "PTP_SET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_ecpri_ptp_cfg {
    cmdline_fixed_string_t ptp_cfg;
    uint8_t ptp_enable;// 1: enable 0: disable
    uint8_t ptp_step_mode;// 1: 1step 0: 2 step
    uint8_t ecpri_step_mode;// 1: 1step 0: 2 step
    uint8_t ptp_domain;
};

cmdline_parse_token_string_t cmd_set_ecpri_ptp_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_ptp_cfg, ptp_cfg, "cfg ptp");
cmdline_parse_token_num_t cmd_set_ecpri_ptp_enable =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ptp_cfg, ptp_enable, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_ptp_step_mode =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ptp_cfg, ptp_step_mode, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_ecpri_step_mode =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ptp_cfg, ecpri_step_mode, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_ptp_domain =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ptp_cfg, ptp_domain, RTE_UINT8);

static void cmd_set_ecpri_ptp_cfg_parsed(void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_ecpri_ptp_cfg *ptp = (struct cmd_ecpri_ptp_cfg *)parsed;
    set_ecpri_ptp_cfg_handler(ptp->ptp_enable, ptp->ptp_step_mode, ptp->ecpri_step_mode, ptp->ptp_domain); 
}

cmdline_parse_inst_t set_ecpri_ptp_cfg = {
    .f = cmd_set_ecpri_ptp_cfg_parsed,
    .data = NULL,
    .help_str = "cfg ptp <ptp_enable> <ptp_step_mode> <ecpri_step_mode> <ptp_domain>",
    .tokens = {
        (void *)&cmd_set_ecpri_ptp_cfg,
        (void *)&cmd_set_ecpri_ptp_enable,
        (void *)&cmd_set_ptp_step_mode,
        (void *)&cmd_set_ecpri_step_mode,
        (void *)&cmd_set_ptp_domain,
        NULL,
        },
};

/* oam set ecpri ru cfg*/
static int32_t oam_set_ecpri_ru_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int set_ecpri_ru_cfg_handler(EcpriRuCfg_t *cfg)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_set_ecpri_ru_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = ECPRI_RU_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriRuCfg_t);
    sub_msg.u.ru_cfg.ru_id = cfg->ru_id;
    sub_msg.u.ru_cfg.s_interval = cfg->s_interval;
    sub_msg.u.ru_cfg.Ta4min = cfg->Ta4min;
    sub_msg.u.ru_cfg.Ta4max = cfg->Ta4max;
    sub_msg.u.ru_cfg.T1amin_cp_ul = cfg->T1amin_cp_ul;
    sub_msg.u.ru_cfg.T1amax_cp_ul = cfg->T1amax_cp_ul;
    sub_msg.u.ru_cfg.T1amin_cp_dl = cfg->T1amin_cp_dl;
    sub_msg.u.ru_cfg.T1amax_cp_dl = cfg->T1amax_cp_dl;
    sub_msg.u.ru_cfg.T1amin_up = cfg->T1amin_up;
    sub_msg.u.ru_cfg.T1amax_up = cfg->T1amax_up;
    memcpy(sub_msg.u.ru_cfg.ru_mac, cfg->ru_mac, ETH_MAC_ADDR_LEN);

    if ( 0== pc802_oam_send_msg( 0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
        rsp_msg_test(ECPRI_RU_SET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == obj.msg.u.result.err_code )
                printf( "ECPRI_RU_SET_REQ ok.\n" );
            else
                printf( "ECPRI_RU_SET_RSP err(%d)!\n", obj.msg.u.result.err_code );
        }
        else
            printf( "ECPRI_RU_SET_RSP recv timeout!\n" );
    }
    else
        printf( "ECPRI_RU_SET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;

}

struct cmd_ecpri_ru_cfg {
    cmdline_fixed_string_t ecpri_ru_cfg;
    uint8_t ru_id;
    uint16_t s_interval;
    uint32_t Ta4min;
    uint32_t Ta4max;
    uint32_t T1amin_cp_ul;
    uint32_t T1amax_cp_ul;
    uint32_t T1amin_cp_dl;
    uint32_t T1amax_cp_dl;
    uint32_t T1amin_up;
    uint32_t T1amax_up;
    struct rte_ether_addr mac_addr;
};

static void cmd_set_ecpri_ru_cfg_parsed(void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_ecpri_ru_cfg *cfg = (struct cmd_ecpri_ru_cfg *)parsed;
    EcpriRuCfg_t ru_cfg;

    ru_cfg.ru_id = cfg->ru_id;
    ru_cfg.s_interval = cfg->s_interval;
    ru_cfg.Ta4min = cfg->Ta4min;
    ru_cfg.Ta4max = cfg->Ta4max;
    ru_cfg.T1amin_cp_ul = cfg->T1amin_cp_ul;
    ru_cfg.T1amax_cp_ul = cfg->T1amax_cp_ul;
    ru_cfg.T1amin_cp_dl = cfg->T1amin_cp_dl;
    ru_cfg.T1amax_cp_dl = cfg->T1amax_cp_dl;
    ru_cfg.T1amin_up = cfg->T1amin_up;
    ru_cfg.T1amax_up = cfg->T1amax_up;
    memcpy(ru_cfg.ru_mac, cfg->mac_addr.addr_bytes, ETH_MAC_ADDR_LEN);

    set_ecpri_ru_cfg_handler(&ru_cfg);
}


cmdline_parse_token_string_t cmd_set_ecpri_ru_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_ru_cfg, ecpri_ru_cfg, "cfg ru");
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_ru_id =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, ru_id, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_s_interval =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, s_interval, RTE_UINT16);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_Ta4min =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, Ta4min, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_Ta4max =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, Ta4max, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_T1amin_cp_ul =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg,T1amin_cp_ul, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cf_T1amax_cp_ul =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, T1amax_cp_ul, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_T1amin_cp_dl =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, T1amin_cp_dl, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_T1amax_cp_dl =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, T1amax_cp_dl, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_T1amin_up =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, T1amin_up, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_T1amax_up =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, T1amax_up, RTE_UINT32);
cmdline_parse_token_etheraddr_t cmd_set_ecpri_ru_cfg_mac_addr =
                TOKEN_ETHERADDR_INITIALIZER(struct cmd_ecpri_ru_cfg, mac_addr);

cmdline_parse_inst_t set_ecpri_ru_cfg = {
    .f = cmd_set_ecpri_ru_cfg_parsed,
    .data = NULL,
    .help_str = "cfg ru <ru_id> <s_interval> <Ta4min> <Ta4max> <T1amin_cp_ul> <T1amax_cp_ul> <T1amin_cp_dl> <T1amax_cp_dl> <T1amin_up> <T1amax_up> <ru_mac>",
    .tokens = {
        (void *)&cmd_set_ecpri_ru_cfg,
        (void *)&cmd_set_ecpri_ru_cfg_ru_id,
        (void *)&cmd_set_ecpri_ru_cfg_s_interval,
        (void *)&cmd_set_ecpri_ru_cfg_Ta4min,
        (void *)&cmd_set_ecpri_ru_cfg_Ta4max,
        (void *)&cmd_set_ecpri_ru_cfg_T1amin_cp_ul,
        (void *)&cmd_set_ecpri_ru_cf_T1amax_cp_ul,
        (void *)&cmd_set_ecpri_ru_cfg_T1amin_cp_dl,
        (void *)&cmd_set_ecpri_ru_cfg_T1amax_cp_dl,
        (void *)&cmd_set_ecpri_ru_cfg_T1amin_up,
        (void *)&cmd_set_ecpri_ru_cfg_T1amax_up,
        (void *)&cmd_set_ecpri_ru_cfg_mac_addr,
        NULL,
        },
};


/*oam set ecpri du cfg*/
static int32_t oam_set_ecpri_du_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int set_ecpri_du_cfg_handler(uint8_t cp_enable, uint8_t ru_cnt, uint16_t vlan_id, uint8_t *addr_bytes)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_set_ecpri_du_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = ECPRI_DU_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriDuCfg_t); 
    sub_msg.u.du_cfg.ru_cnt = ru_cnt;
    sub_msg.u.du_cfg.vlan_id = vlan_id;
    sub_msg.u.du_cfg.cp_enable = cp_enable;
    memcpy(sub_msg.u.du_cfg.du_mac, addr_bytes, ETH_MAC_ADDR_LEN);

    if ( 0== pc802_oam_send_msg( 0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
        rsp_msg_test(ECPRI_DU_SET_RSP);
#endif
        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == obj.msg.u.result.err_code )
                printf( "ECPRI_DU_SET_REQ ok.\n" );
            else
                printf( "ECPRI_DU_SET_RSP err(%d)!\n", obj.msg.u.result.err_code );
        }
        else
            printf( "ECPRI_DU_SET_RSP recv timeout!\n" );
    }
    else
        printf( "ECPRI_DU_SET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_ecpri_du_cfg {
    cmdline_fixed_string_t ecpri_du_cfg;
    uint8_t cp_enable;
    uint8_t ru_cnt;
    uint16_t vlan_id;
    struct rte_ether_addr mac_addr;
};

static void cmd_set_ecpri_du_cfg_parsed(void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_ecpri_du_cfg *cfg = (struct cmd_ecpri_du_cfg *)parsed;
    set_ecpri_du_cfg_handler(cfg->cp_enable, cfg->ru_cnt, cfg->vlan_id, cfg->mac_addr.addr_bytes);
}

cmdline_parse_token_string_t cmd_set_ecpri_du_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_du_cfg, ecpri_du_cfg, "cfg du");
cmdline_parse_token_num_t cmd_set_ecpri_du_cfg_cp_enable =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_du_cfg, cp_enable, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_ecpri_du_cfg_ru_cnt =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_du_cfg, ru_cnt, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_ecpri_du_cfg_vlan_id =
   TOKEN_NUM_INITIALIZER(struct cmd_ecpri_du_cfg, vlan_id, RTE_UINT16);
cmdline_parse_token_etheraddr_t cmd_set_ecpri_du_cfg_mac_addr =
                TOKEN_ETHERADDR_INITIALIZER(struct cmd_ecpri_du_cfg, mac_addr);

cmdline_parse_inst_t set_ecpri_du_cfg = {
    .f = cmd_set_ecpri_du_cfg_parsed,
    .data = NULL,
    .help_str = "cfg du <cp_enable> <vlan_id> <ru_cnt> <mac addr>",
    .tokens = {
        (void *)&cmd_set_ecpri_du_cfg,
        (void *)&cmd_set_ecpri_du_cfg_cp_enable,
        (void *)&cmd_set_ecpri_du_cfg_vlan_id,
        (void *)&cmd_set_ecpri_du_cfg_ru_cnt,
        (void *)&cmd_set_ecpri_du_cfg_mac_addr,
        NULL,
        },
};


/*oam ecpri comp method cfg*/
static int32_t oam_set_ecpri_comp_method_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int set_ecpri_comp_method_cfg_handler(uint8_t isStaticComp, uint8_t method, uint8_t comIqWidth, uint8_t decomIqWidth)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_set_ecpri_comp_method_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = COMP_METH_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriCompMethodCfg_t);
    sub_msg.u.comp_method_cfg.isStaticComp = isStaticComp;
    sub_msg.u.comp_method_cfg.method = method;
    sub_msg.u.comp_method_cfg.comIqWidth = comIqWidth;
    sub_msg.u.comp_method_cfg.decomIqWidth = decomIqWidth;

    if ( 0== pc802_oam_send_msg( 0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
     rsp_msg_test(COMP_METH_SET_RSP);
#endif
        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){

            if ( 0 == obj.msg.u.result.err_code )
                printf( "COMP_METH_SET_REQ ok.\n" );
            else
                printf( "COMP_METH_SET_RSP err(%d)!\n", obj.msg.u.result.err_code );
        }
        else
            printf( "COMP_METH_SET_RSP recv timeout!\n" );
    }
    else
        printf( "COMP_METH_SET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_ecpri_comp_method_cfg {
    cmdline_fixed_string_t set;
    cmdline_fixed_string_t comp_method_cfg;
    uint8_t isStaticComp;
    uint8_t method;
    uint8_t comIqWidth;
    uint8_t decomIqWidth;
};

static void cmd_set_ecpri_comp_method_cfg_parsed(void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
     struct cmd_ecpri_comp_method_cfg *cfg = (struct cmd_ecpri_comp_method_cfg *)parsed;
     set_ecpri_comp_method_cfg_handler(cfg->isStaticComp, cfg->method, cfg->comIqWidth, cfg->decomIqWidth);
}

cmdline_parse_token_string_t cmd_set_comp_method_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_comp_method_cfg, comp_method_cfg, "cfg comp");
cmdline_parse_token_num_t cmd_set_comp_method_cfg_isStaticComp =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_comp_method_cfg, isStaticComp, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_comp_method_cfg_method =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_comp_method_cfg, method, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_comp_method_cfg_comIqWidth =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_comp_method_cfg, comIqWidth, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_comp_method_cfg_decomIqWidth =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_comp_method_cfg, decomIqWidth, RTE_UINT8);

cmdline_parse_inst_t set_comp_method_cfg = {
    .f = cmd_set_ecpri_comp_method_cfg_parsed,
    .data = NULL,
    .help_str = "cfg comp <isStaticComp> <method> <comIqWidth> <decomIqWidth>",
    .tokens = {
        (void *)&cmd_set_comp_method_cfg,
        (void *)&cmd_set_comp_method_cfg_isStaticComp,
        (void *)&cmd_set_comp_method_cfg_method,
        (void *)&cmd_set_comp_method_cfg_comIqWidth,
        (void *)&cmd_set_comp_method_cfg_decomIqWidth,
        NULL,
        },
};


/*oam get ecpri comp method cfg*/
static int32_t oam_get_ecpri_comp_method_cfg_rsp(void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num)
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static void comp_method_cfg_print(EcpriCompMethodCfg_t *cfg)
{
	printf("isStaticComp:		%d\n",  cfg->isStaticComp);
	printf("method:         	%d\n",  cfg->method);
	printf("comIqWidth:		%d\n",  cfg->comIqWidth);
	printf("decomIqWidth:		%d\n",  cfg->decomIqWidth);
}

static void get_ecpri_comp_method_cfg_decode_data(OamSubMessage_t *oam)
{

   if(oam->Head.MsgId == ECPRI_ERR_IND)
   {
	printf("get ecpri comp method %d", oam->u.result.err_code);
   }
   else if(oam->Head.MsgId == COMP_METH_GET_RSP)
   {
	comp_method_cfg_print(&oam->u.comp_method_cfg);
   }
   else
   {
	printf("Line %d, %s msg id %d error \n", __LINE__, __func__, oam->Head.MsgId);
   }
}

static int get_ecpri_comp_method_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;
    
    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(COMP_METH_GET_RSP, oam_get_ecpri_comp_method_cfg_rsp, &obj);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_get_ecpri_comp_method_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = COMP_METH_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
    OamSubMessage_t rsp_msg = {0};
    rsp_msg.u.comp_method_cfg.isStaticComp = 3;
    rsp_msg.u.comp_method_cfg.method = 1;
    rsp_msg.u.comp_method_cfg.comIqWidth = 2;
    rsp_msg.u.comp_method_cfg.decomIqWidth = 0;
    rsp_msg.Head.MsgId = COMP_METH_GET_RSP;
    rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t) + sizeof(OamSubMessageHeader_t) + sizeof(EcpriCompMethodCfg_t);
    send_test_msg(&rsp_msg);    //for test
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
	  get_ecpri_comp_method_cfg_decode_data(&(obj.msg));
        }
        else
            printf( "COMP_METH_SET_RSP recv timeout!\n" );
    }
    else
        printf( "COMP_METH_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(COMP_METH_GET_RSP);
    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_read_ecpri_comp_method_cfg {
    cmdline_fixed_string_t comp_method_cfg;
};

static void cmd_get_ecpri_comp_method_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_comp_method_cfg_handler();
}

cmdline_parse_token_string_t cmd_get_comp_method_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_read_ecpri_comp_method_cfg, comp_method_cfg, "show comp");

cmdline_parse_inst_t get_comp_method_cfg = {
    .f = cmd_get_ecpri_comp_method_cfg_parsed,
    .data = NULL,
    .help_str = "show comp <isStaticComp> <method> <comIqWidth> <decomIqWidth>",
    .tokens = {
        (void *)&cmd_get_comp_method_cfg,
        NULL,
        },
};

/*oam get eth mtu cfg*/
static int32_t oam_get_eth_mtu_cfg_rsp(void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num)
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static void eth_mtu_cfg_print(EcpriEthMtuCfg_t *cfg)
{
	printf("mtu:		%d\n",  cfg->mtu);
}

static void get_eth_mtu_cfg_decode_data(OamSubMessage_t *oam)
{

   if(oam->Head.MsgId == ECPRI_ERR_IND)
   {
	printf("get eth mtu cfg %d", oam->u.result.err_code);
   }
   else if(oam->Head.MsgId == ETH_MTU_GET_RSP)
   {
	eth_mtu_cfg_print(&oam->u.mtu_cfg);
   }
   else
   {
	printf("Line %d, %s msg id %d error \n", __LINE__, __func__, oam->Head.MsgId);
   }
}

static int get_ecpri_eth_mtu_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;
    
    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ETH_MTU_GET_RSP, oam_get_eth_mtu_cfg_rsp, &obj);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_get_eth_mtu_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = ETH_MTU_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
    OamSubMessage_t rsp_msg = {0};
    rsp_msg.u.mtu_cfg.mtu = 500;
    rsp_msg.Head.MsgId = ETH_MTU_GET_RSP;
    rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t) + sizeof(OamSubMessageHeader_t) + sizeof(EcpriEthMtuCfg_t);
    send_test_msg(&rsp_msg);    //for test
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
	  get_eth_mtu_cfg_decode_data(&(obj.msg));
        }
        else
            printf( "ETH_MTU_GET_RSP recv timeout!\n" );
    }
    else
        printf( "ETH_MTU_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ETH_MTU_GET_RSP);
    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_read_eth_mtu_cfg {
    cmdline_fixed_string_t mtu_cfg;
};

static void cmd_get_ecpri_eth_mtu_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_eth_mtu_cfg_handler();
}

cmdline_parse_token_string_t cmd_get_eth_mtu_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_read_eth_mtu_cfg, mtu_cfg, "show mtu");

cmdline_parse_inst_t get_eth_mtu_cfg = {
    .f = cmd_get_ecpri_eth_mtu_cfg_parsed,
    .data = NULL,
    .help_str = "show eth mtu <mtu> ",
    .tokens = {
        (void *)&cmd_get_eth_mtu_cfg,
        NULL,
        },
};


/*oam get ecpri basic cfg*/
static int32_t oam_get_ecpri_basic_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}


static void basic_cfg_print(BasicCfg_t *cfg)
{
	printf("pcie_enable:			%d\n", cfg->pcie_enable); 
	printf("eth_type: 			%d\n", cfg->eth_type);
	printf("max_antenna_cnt: 		%d\n", cfg->max_antenna_cnt);
 	printf("max_section_cnt: 		%d\n", cfg->max_section_cnt);
        printf("max_symbol_cnt_per_slot:  	%d\n", cfg->max_symbol_cnt_per_slot);
        printf("cur_antenna_cnt:  		%d\n", cfg->cur_antenna_cnt);
	printf("cur_section_cnt: 		%d\n", cfg->cur_section_cnt);
	printf("cur_symbol_cnt_per_slot: 	%d\n", cfg->cur_symbol_cnt_per_slot);
	printf("pipeline_mode: 			%d\n", cfg->pipeline_mode);
	printf("outgoing_core_cnt: 		%d\n", cfg->outgoing_core_cnt);
	printf("ingoing_core_cnt: 		%d\n", cfg->ingoing_core_cnt);
	printf("eth_pkt_size: 			%d\n", cfg->eth_pkt_size);
        printf("pEcpriNtfyBuf: 			%d\n", cfg->pEcpriNtfyBuf);
        printf("pEcpriReqBuf: 			%d\n", cfg->pEcpriReqBuf); 
        printf("om_msg_id:  			%d\n", cfg->om_msg_id);
}

static void get_ecpri_basic_cfg_decode(OamSubMessage_t *oam)
{
   if(oam->Head.MsgId == ECPRI_ERR_IND)
   {
	printf("get ecpri basic cfg %d\n", oam->u.result.err_code);
   }
   else if(oam->Head.MsgId == BASIC_CFG_GET_RSP)
   {
	basic_cfg_print(&oam->u.basic_cfg);
   }
   else
   {
	printf("Line %d, %s msg id %d error \n", __LINE__, __func__, oam->Head.MsgId);
   }
}


static int get_ecpri_basic_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(BASIC_CFG_GET_RSP, oam_get_ecpri_basic_cfg_rsp, &obj);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_get_ecpri_basic_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = BASIC_CFG_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
    OamSubMessage_t rsp_msg = {0};
    rsp_msg.u.basic_cfg.pcie_enable = 1;
    rsp_msg.u.basic_cfg.eth_type = 1;
    rsp_msg.u.basic_cfg.max_antenna_cnt = 2;
    rsp_msg.u.basic_cfg.max_section_cnt = 3;
    rsp_msg.u.basic_cfg.max_symbol_cnt_per_slot = 4;
    rsp_msg.u.basic_cfg.cur_antenna_cnt = 5;
    rsp_msg.u.basic_cfg.cur_section_cnt = 6;
    rsp_msg.u.basic_cfg.cur_symbol_cnt_per_slot = 7;
    rsp_msg.u.basic_cfg.pipeline_mode = 1;
    rsp_msg.u.basic_cfg.outgoing_core_cnt = 2;
    rsp_msg.u.basic_cfg.ingoing_core_cnt = 3;
    rsp_msg.u.basic_cfg.eth_pkt_size = 4;
    rsp_msg.u.basic_cfg.pEcpriNtfyBuf = 8;
    rsp_msg.u.basic_cfg.pEcpriReqBuf = 9;
    rsp_msg.u.basic_cfg.om_msg_id = 6;
    rsp_msg.Head.MsgId = BASIC_CFG_GET_RSP;
    rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t) + sizeof(OamSubMessageHeader_t) + sizeof(BasicCfg_t);
    send_test_msg(&rsp_msg);    //for test
#endif


        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
	    get_ecpri_basic_cfg_decode(&(obj.msg));
        }
        else
            printf( "BASIC_CFG_GET_RSP recv timeout!\n" );
    }
    else
        printf( "BASIC_CFG_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(BASIC_CFG_GET_RSP);
    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;

}

struct cmd_ecpri_basic_cfg {
    cmdline_fixed_string_t basic_cfg;
};

static void cmd_get_ecpri_basic_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_basic_cfg_handler();
}

cmdline_parse_token_string_t cmd_get_ecpri_basic_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_basic_cfg, basic_cfg, "show basic cfg");

cmdline_parse_inst_t get_ecpri_basic_cfg = {
    .f = cmd_get_ecpri_basic_cfg_parsed,
    .data = NULL,
    .help_str = "show basic cfg <pcie_enable> <eth_type> <max_antenna_cnt> <max_section_cnt> <max_symbol_cnt_per_slot> <cur_antenna_cnt> <cur_section_cnt> <cur_symbol_cnt_per_slot> <pEcpriNtfyBuf> <pEcpriReqBuf> <om_msg_id>",
    .tokens = {
        (void *)&cmd_get_ecpri_basic_cfg,
        NULL,
        },
};


/*oam get ecpri perf kpis */
static int32_t oam_get_ecpri_perf_kpis_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static void ecpri_kpis_print(EcpriPerfKpis_t *kpis)
{

	if(kpis->m_rx_total_h == 0)
	   printf("m_rx_total:                  %d\n", kpis->m_rx_total_l);
	else
	   printf("m_rx_total:                  %d%032d\n", kpis->m_rx_total_h, kpis->m_rx_total_l);

	if(kpis->m_rx_on_time_h == 0)
	   printf("m_rx_on_time:                %d\n", kpis->m_rx_on_time_l);
	else
	   printf("m_rx_on_time:                %d%032d\n", kpis->m_rx_on_time_h, kpis->m_rx_on_time_l);

	if(kpis->m_rx_early_h == 0)
	   printf("m_rx_early:                  %d\n", kpis->m_rx_early_l);
	else
	   printf("m_rx_early:                  %d%032d\n", kpis->m_rx_early_h, kpis->m_rx_early_l);

	if(kpis->m_rx_late_h == 0)
	   printf("m_rx_late:                   %d\n", kpis->m_rx_late_l);
	else
	   printf("m_rx_late:                   %d%032d\n", kpis->m_rx_late_h, kpis->m_rx_late_l);

	if(kpis->m_rx_seqid_err_h == 0)
	   printf("m_rx_seqid_err:              %d\n", kpis->m_rx_seqid_err_l);
	else
	   printf("m_rx_seqid_err:              %d%032d\n", kpis->m_rx_seqid_err_h, kpis->m_rx_seqid_err_l);

	if(kpis->m_rx_on_time_c_h == 0)
	   printf("m_rx_on_time_c:              %d\n", kpis->m_rx_on_time_c_l);
	else
	   printf("m_rx_on_time_c:              %d%032d\n", kpis->m_rx_on_time_c_h, kpis->m_rx_on_time_c_l);

	if(kpis->m_rx_early_c_h == 0)
	   printf("m_rx_early_c:                %d\n", kpis->m_rx_early_c_l);
	else
	   printf("m_rx_early_c:                %d%032d\n", kpis->m_rx_early_c_h, kpis->m_rx_early_c_l);

	if(kpis->m_rx_late_c_h == 0)
	   printf("m_rx_late_c:                 %d\n", kpis->m_rx_late_c_l);
	else
	   printf("m_rx_late_c:                 %d%032d\n", kpis->m_rx_late_c_h, kpis->m_rx_late_c_l);

	if(kpis->m_rx_seqid_err_c_h == 0)
	   printf("m_rx_seqid_err_c:            %d\n", kpis->m_rx_seqid_err_c_l);
	else
	   printf("m_rx_seqid_err_c:            %d%032d\n", kpis->m_rx_seqid_err_c_h, kpis->m_rx_seqid_err_c_l);

	if(kpis->m_rx_corrupt_h == 0)
	   printf("m_rx_corrupt:                %d\n", kpis->m_rx_corrupt_l);
	else
	   printf("m_rx_corrupt:                %d%032d\n", kpis->m_rx_corrupt_h, kpis->m_rx_corrupt_l);

	if(kpis->m_rx_err_drop_h == 0)
	   printf("m_rx_err_drop:               %d\n", kpis->m_rx_err_drop_l);
	else
	   printf("m_rx_err_drop:               %d%032d\n", kpis->m_rx_err_drop_h, kpis->m_rx_err_drop_l);

	if(kpis->m_rx_pkt_dupl_h == 0)
	   printf("m_rx_pkt_dupl:               %d\n", kpis->m_rx_pkt_dupl_l);
	else
	   printf("m_rx_pkt_dupl:               %d%032d\n", kpis->m_rx_pkt_dupl_h, kpis->m_rx_pkt_dupl_l);

	if(kpis->m_tx_total_h == 0)
	   printf("m_tx_total:                  %d\n", kpis->m_tx_total_l);
	else
	   printf("m_tx_total:                  %d%032d\n", kpis->m_tx_total_h, kpis->m_tx_total_l);

	if(kpis->m_tx_total_c_h == 0)
	   printf("m_tx_total_c:                %d\n", kpis->m_tx_total_c_l);
	else
	   printf("m_tx_total_c:                %d%032d\n", kpis->m_tx_total_c_h, kpis->m_tx_total_c_l);
}

static void get_ecpri_kpis_decode(OamSubMessage_t *oam)
{
   if(oam->Head.MsgId == ECPRI_ERR_IND)
   {
        printf("get ecpri kpis decode %d\n", oam->u.result.err_code);
   }
   else if(oam->Head.MsgId == ECPRI_DU_KPIS_GET_RSP)
   {
	ecpri_kpis_print(&oam->u.kpis);
   }
   else
   {
	printf("Line %d, %s msg id %d error \n", __LINE__, __func__, oam->Head.MsgId);
   }
}


static int get_ecpri_perf_kpis_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_DU_KPIS_GET_RSP, oam_get_ecpri_perf_kpis_rsp, &obj);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_get_ecpri_perf_kpis_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = ECPRI_DU_KPIS_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
    OamSubMessage_t rsp_msg = {0};
    rsp_msg.u.kpis.m_rx_total_h = 9; 
    rsp_msg.u.kpis.m_rx_total_l = 9; 
    rsp_msg.u.kpis.m_rx_on_time_h = 10;
    rsp_msg.u.kpis.m_rx_on_time_l = 10;
    rsp_msg.u.kpis.m_rx_early_h = 11;
    rsp_msg.u.kpis.m_rx_early_l = 11;
    rsp_msg.u.kpis.m_rx_late_h = 12;
    rsp_msg.u.kpis.m_rx_late_l = 12;
    rsp_msg.u.kpis.m_rx_seqid_err_h = 0;
    rsp_msg.u.kpis.m_rx_seqid_err_l = 0;
    rsp_msg.u.kpis.m_rx_on_time_c_h = 13;
    rsp_msg.u.kpis.m_rx_on_time_c_l = 13;
    rsp_msg.u.kpis.m_rx_early_c_h = 14;
    rsp_msg.u.kpis.m_rx_early_c_l = 14;
    rsp_msg.u.kpis.m_rx_late_c_h = 15;
    rsp_msg.u.kpis.m_rx_late_c_l = 15;
    rsp_msg.u.kpis.m_rx_seqid_err_c_h = 16;
    rsp_msg.u.kpis.m_rx_seqid_err_c_l = 16;
    rsp_msg.u.kpis.m_rx_corrupt_h = 17;
    rsp_msg.u.kpis.m_rx_corrupt_l = 17;
    rsp_msg.u.kpis.m_rx_err_drop_h = 18;
    rsp_msg.u.kpis.m_rx_err_drop_l = 18;
    rsp_msg.u.kpis.m_rx_pkt_dupl_h = 19;
    rsp_msg.u.kpis.m_rx_pkt_dupl_l = 19;
    rsp_msg.u.kpis.m_tx_total_h = 23;
    rsp_msg.u.kpis.m_tx_total_l = 23;
    rsp_msg.u.kpis.m_tx_total_c_h = 33;
    rsp_msg.u.kpis.m_tx_total_c_l = 33;
    rsp_msg.Head.MsgId = ECPRI_DU_KPIS_GET_RSP;
    rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t) + sizeof(OamSubMessageHeader_t) + sizeof(EcpriPerfKpis_t); 
    send_test_msg(&rsp_msg);    //for test
#endif
        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 2;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){

	    get_ecpri_kpis_decode(&(obj.msg));
     	}
        else
            printf( "ECPRI_DU_KPIS_GET_RSP recv timeout!\n" );
    }
    else
        printf( "ECPRI_DU_KPIS_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_DU_KPIS_GET_REQ);
    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_ecpri_perf_kpis {
    cmdline_fixed_string_t ecpri_perf_kpis;
};

static void cmd_get_ecpri_perf_kpis_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_perf_kpis_handler();
}

cmdline_parse_token_string_t cmd_get_ecpri_perf_kpis =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_perf_kpis, ecpri_perf_kpis, "show perf kpis");

cmdline_parse_inst_t get_ecpri_perf_kpis = {
    .f = cmd_get_ecpri_perf_kpis_parsed,
    .data = NULL,
    .help_str = "show perf kpis: <m_rx_total> <m_rx_on_time> <m_rx_early> <m_rx_late> <m_rx_seqid_err> <m_rx_on_time_c> <m_rx_early_c> <m_rx_late_c> <m_rx_seqid_err_c> <m_rx_corrupt> <m_rx_err_drop> <m_rx_pkt_dupl> <m_tx_total> <m_tx_total_c>",
    .tokens = {
        (void *)&cmd_get_ecpri_perf_kpis,
        NULL,
        },
};


/*oam get ecpri du cfg*/
static int32_t oam_get_ecpri_du_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static void du_cfg_print(EcpriDuCfg_t *cfg)
{
   printf("cp_enable: 		%d\n", cfg->cp_enable);
   printf("vlan_id: 		%d\n", cfg->vlan_id);
   printf("ru_cnt: 		%d\n", cfg->ru_cnt);
   printf("du_mac: 		%02x:%02x:%02x:%02x:%02x:%02x\n", cfg->du_mac[0], cfg->du_mac[1], cfg->du_mac[2], 	\
	   cfg->du_mac[3], cfg->du_mac[4], cfg->du_mac[5]);
}

static void get_ecpri_du_cfg_decode(OamSubMessage_t *oam)
{
   if(oam->Head.MsgId == ECPRI_ERR_IND)
   {
        printf("get ecpr du cfg decode %d\n", oam->u.result.err_code);
   }
   else if(oam->Head.MsgId == ECPRI_DU_GET_RSP)
   {
	du_cfg_print(&oam->u.du_cfg);
   }
   else
   {
	printf("Line %d, %s msg id %d error \n", __LINE__, __func__, oam->Head.MsgId);
   }
}


static int get_ecpri_du_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_DU_GET_RSP, oam_get_ecpri_du_cfg_rsp, &obj);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_get_ecpri_du_cfg_rsp, &obj);

    memset(&sub_msg, 0, sizeof(sub_msg));
    sub_msg.Head.MsgId = ECPRI_DU_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
    OamSubMessage_t rsp_msg = {0};
    rsp_msg.u.du_cfg.ru_cnt = 6;
    rsp_msg.u.du_cfg.du_mac[0] = 0x01;
    rsp_msg.u.du_cfg.du_mac[1] = 0x11;
    rsp_msg.u.du_cfg.du_mac[2] = 0x21;
    rsp_msg.u.du_cfg.du_mac[3] = 0x31;
    rsp_msg.u.du_cfg.du_mac[4] = 0x41;
    rsp_msg.u.du_cfg.du_mac[5] = 0x51;
    rsp_msg.u.du_cfg.vlan_id = 2;
    rsp_msg.u.du_cfg.cp_enable = 4;
    rsp_msg.Head.MsgId = ECPRI_DU_GET_RSP;
    rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t) + sizeof(OamSubMessageHeader_t) + sizeof(EcpriDuCfg_t);
    send_test_msg(&rsp_msg);    //for test
#endif
        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
	    get_ecpri_du_cfg_decode(&obj.msg);
     	}
        else
            printf( "ECPRI_DU_GET_RSP recv timeout!\n" );
    }
    else
        printf( "ECPRI_DU_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_DU_GET_RSP);
    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_read_ecpri_du_cfg {
    cmdline_fixed_string_t ecpri_du_cfg;
};

static void cmd_get_ecpri_du_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_du_cfg_handler();
}

cmdline_parse_token_string_t cmd_get_ecpri_du_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_read_ecpri_du_cfg, ecpri_du_cfg, "show du cfg");

cmdline_parse_inst_t get_ecpri_du_cfg = {
    .f = cmd_get_ecpri_du_cfg_parsed,
    .data = NULL,
    .help_str = "show du cfg <ru_cnt> <mac addr> <vlan_id>",
    .tokens = {
        (void *)&cmd_get_ecpri_du_cfg,
        NULL,
        },
};

/*oam get ecpri du inernal cfg*/
static int32_t oam_get_ecpri_du_internal_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
        printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t))
    {
        printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
        size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static void du_internal_cfg_print(EcpriDuInternalCfg_t *cfg)
{
	printf("pipeline_mode:		%d\n", cfg->pipeline_mode);
	printf("m_role:			%d\n", cfg->m_role);
	printf("outgoing_core_cnt:	%d\n", cfg->outgoing_core_cnt);
	printf("ingoing_core_cnt:	%d\n", cfg->ingoing_core_cnt);
}

static void get_ecpri_du_internal_cfg_decode(OamSubMessage_t *oam)
{
   if(oam->Head.MsgId == ECPRI_ERR_IND)
   {
        printf("get ecpri du internal decode %d\n", oam->u.result.err_code);
   }
   else if(oam->Head.MsgId == ECPRI_DU_LOCAL_GET_RSP)
   {
	du_internal_cfg_print(&(oam->u.du_int_cfg));
   }
   else
   {
	printf("Line %d, %s msg id %d error \n", __LINE__, __func__, oam->Head.MsgId);
   }
}

static int get_ecpri_du_internal_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_DU_LOCAL_GET_RSP, oam_get_ecpri_du_internal_cfg_rsp, &obj);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_get_ecpri_du_internal_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = ECPRI_DU_LOCAL_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
    OamSubMessage_t rsp_msg = {0};
    rsp_msg.u.du_int_cfg.pipeline_mode = 1;
    rsp_msg.u.du_int_cfg.m_role = 1;
    rsp_msg.u.du_int_cfg.outgoing_core_cnt = 8;
    rsp_msg.u.du_int_cfg.ingoing_core_cnt = 9;
    rsp_msg.Head.MsgId = ECPRI_DU_LOCAL_GET_RSP;
    rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t) + sizeof(OamSubMessageHeader_t) + sizeof(EcpriDuInternalCfg_t);
    send_test_msg(&rsp_msg);    //for test
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
	   get_ecpri_du_internal_cfg_decode(&obj.msg);
     	}
        else
            printf( "ECPRI_DU_LOCAL_GET_RSP recv timeout!\n" );
    }
    else
        printf( "ECPRI_DU_LOCAL_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_DU_LOCAL_GET_RSP);
    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_ecpri_du_internal_cfg {
    cmdline_fixed_string_t cmd_ecpri_du_internal_cfg;
};

static void cmd_get_ecpri_du_internal_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_du_internal_cfg_handler();
}

cmdline_parse_token_string_t cmd_get_ecpri_du_internal_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_du_internal_cfg, cmd_ecpri_du_internal_cfg, "show du internal cfg");

cmdline_parse_inst_t get_ecpri_du_internal_cfg = {
    .f = cmd_get_ecpri_du_internal_cfg_parsed,
    .data = NULL,
    .help_str = "show du internal cfg <pipeline_mode> <m_role> <outgoing_core_cnt> <ingoing_core_cnt>",
    .tokens = {
        (void *)&cmd_get_ecpri_du_internal_cfg,
        NULL,
        },
};

/* oam get ecpri ru cfg*/
static int32_t oam_get_ecpri_ru_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static void ru_cfg_print(EcpriRuCfg_t *cfg)
{
	printf("ru_id:			%d\n", cfg->ru_id);
	printf("s_interval: 		%d\n", cfg->s_interval);
	printf("Ta4min: 		%d\n", cfg->Ta4min);
	printf("Ta4max: 		%d\n", cfg->Ta4max);
	printf("T1amin_cp_ul: 		%d\n", cfg->T1amin_cp_ul);
	printf("T1amax_cp_ul: 		%d\n", cfg->T1amax_cp_ul);
	printf("T1amin_cp_dl: 		%d\n", cfg->T1amin_cp_dl);
	printf("T1amax_cp_dl: 		%d\n", cfg->T1amax_cp_dl);
	printf("T1amin_up: 		%d\n", cfg->T1amin_up);
	printf("T1amax_up: 		%d\n", cfg->T1amax_up);
	printf("ru_mac:			%02x:%02x:%02x:%02x:%02x:%02x\n", 	\
		cfg->ru_mac[0], cfg->ru_mac[1], cfg->ru_mac[2], cfg->ru_mac[3], cfg->ru_mac[4], cfg->ru_mac[5]);
}

static void get_ecpri_ru_cfg_decode(OamSubMessage_t *oam)
{
   if(oam->Head.MsgId == ECPRI_ERR_IND)
   {
        printf("get ecpri ru cfg decode %d\n", oam->u.result.err_code);
   }
   else if(oam->Head.MsgId == ECPRI_RU_GET_RSP)
   {
	ru_cfg_print(&(oam->u.ru_cfg));
   }
   else
   {
	printf("Line %d, %s msg id %d error \n", __LINE__, __func__, oam->Head.MsgId);
   }
}

static int get_ecpri_ru_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_RU_GET_RSP, oam_get_ecpri_ru_cfg_rsp, &obj);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_get_ecpri_ru_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = ECPRI_RU_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
    OamSubMessage_t rsp_msg = {0};
    rsp_msg.u.ru_cfg.ru_id = 1;
    rsp_msg.u.ru_cfg.s_interval = 1;
    rsp_msg.u.ru_cfg.Ta4min = 42;
    rsp_msg.u.ru_cfg.Ta4max = 43;
    rsp_msg.u.ru_cfg.T1amin_cp_ul = 44;
    rsp_msg.u.ru_cfg.T1amax_cp_ul = 45;
    rsp_msg.u.ru_cfg.T1amin_cp_dl = 46;
    rsp_msg.u.ru_cfg.T1amax_cp_dl = 47;
    rsp_msg.u.ru_cfg.T1amin_up = 48;
    rsp_msg.u.ru_cfg.T1amax_up = 49;
    rsp_msg.u.ru_cfg.ru_mac[0] = 0x00;
    rsp_msg.u.ru_cfg.ru_mac[1] = 0x11;
    rsp_msg.u.ru_cfg.ru_mac[2] = 0x22;
    rsp_msg.u.ru_cfg.ru_mac[3] = 0x33;
    rsp_msg.u.ru_cfg.ru_mac[4] = 0x44;
    rsp_msg.u.ru_cfg.ru_mac[5] = 0x55;
    rsp_msg.Head.MsgId = ECPRI_RU_GET_RSP;
    rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t) + sizeof(OamSubMessageHeader_t) + sizeof(EcpriRuCfg_t);
    send_test_msg(&rsp_msg);    //for test
#endif
        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
	  
	    get_ecpri_ru_cfg_decode(&obj.msg);
     	}
        else
            printf( "ECPRI_RU_GET_RSP recv timeout!\n" );
    }
    else
        printf( "ECPRI_RU_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_RU_GET_RSP);
    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;

}

struct cmd_read_ecpri_ru_cfg {
    cmdline_fixed_string_t ecpri_ru_cfg;
};

static void cmd_get_ecpri_ru_cfg_parsed(__attribute__((unused))void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_ru_cfg_handler();
}


cmdline_parse_token_string_t cmd_get_ecpri_ru_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_read_ecpri_ru_cfg, ecpri_ru_cfg, "show ru cfg");

cmdline_parse_inst_t get_ecpri_ru_cfg = {
    .f = cmd_get_ecpri_ru_cfg_parsed,
    .data = NULL,
    .help_str = "show ru cfg <ru_id> <s_interval> <Ta4min> <Ta4max> <T1amin_cp_ul> <T1amax_cp_ul> <T1amin_cp_dl> <T1amax_cp_dl> <T1amin_up> <T1amax_up> <ru_mac>",
    .tokens = {
        (void *)&cmd_get_ecpri_ru_cfg,
        NULL,
        },
};


/* oam get ecpri tx rx cfg*/
static int32_t oam_get_ecpri_tx_rx_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}


static void tx_rx_cfg_print(EcpriTxRxCfg_t * cfg)
{
	printf("maxTxLateThreshold:		%d\n", cfg->maxTxLateThreshold);
}

static void get_ecpri_tx_rx_cfg_decode(OamSubMessage_t *oam)
{
   if(oam->Head.MsgId == ECPRI_ERR_IND)
   {
        printf("get ecpri ru cfg decode %d\n", oam->u.result.err_code);
   }
   else if(oam->Head.MsgId == TX_RX_GET_RSP)
   {
	tx_rx_cfg_print(&oam->u.tx_rx_cfg);
   }
   else
   {
	printf("Line %d, %s msg id %d error \n", __LINE__, __func__, oam->Head.MsgId);
   }
}

static int get_ecpri_tx_rx_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(TX_RX_GET_RSP, oam_get_ecpri_tx_rx_cfg_rsp, &obj);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_get_ecpri_tx_rx_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = TX_RX_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
    OamSubMessage_t rsp_msg = {0};
    rsp_msg.u.tx_rx_cfg.maxTxLateThreshold = 52;
    rsp_msg.Head.MsgId = TX_RX_GET_RSP;
    rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t) + sizeof(OamSubMessageHeader_t) + sizeof(EcpriTxRxCfg_t);
    send_test_msg(&rsp_msg);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
	    get_ecpri_tx_rx_cfg_decode(&obj.msg);	
        }
        else
            printf( "TX_RX_GET_RSP recv timeout!\n" );
    }
    else
        printf( "TX_RX_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(TX_RX_GET_RSP);
    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_read_ecpri_tx_rx_cfg {
    cmdline_fixed_string_t ecpri_tx_rx_cfg;
};

static void cmd_get_ecpri_tx_rx_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_tx_rx_cfg_handler();
}

cmdline_parse_token_string_t cmd_get_ecpri_tx_rx_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_read_ecpri_tx_rx_cfg, ecpri_tx_rx_cfg, "show tx rx cfg");

cmdline_parse_inst_t get_ecpri_tx_rx_cfg = {
    .f = cmd_get_ecpri_tx_rx_cfg_parsed,
    .data = NULL,
    .help_str = "show tx rx cfg <maxTxLateThreshold>",
    .tokens = {
	(void*) &cmd_get_ecpri_tx_rx_cfg,
        NULL,
        },
};


/* oam get ecpri ptp cfg*/
static int32_t oam_get_ecpri_ptp_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    uint32_t size = 0;

    if(msg_num > 1)
    {
    	printf("port_id = %u, msg_num = %u, Line %d, %s\n", port_id, msg_num,  __LINE__, __func__);
    }

    size = sub_msg[0]->Head.MsgSize + sizeof(OamSubMessageHeader_t);
    if(size > sizeof(OamSubMessage_t)) 
    {
    	printf("head msg size = %d, Line %d, %s\n", sub_msg[0]->Head.MsgSize,  __LINE__, __func__);
	size =  sizeof(OamSubMessage_t);
    }

    memcpy( &((oam_decode_data *)arg)->msg, sub_msg[0], size);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;

}

static void ptp_cfg_print(EcpriPtpCfg_t *cfg)
{
        printf("ptp_enable:                   	%d\n", cfg->ptp_enable);
        printf("ptp_step_mode:                	%d\n", cfg->ptp_step_mode);
        printf("ecpri_step_mode:             	%d\n", cfg->ecpri_step_mode);
        printf("ptp_domain:             	%d\n", cfg->ptp_domain);
}

static void get_ecpri_ptp_cfg_decode(OamSubMessage_t *oam)
{
   if(oam->Head.MsgId == ECPRI_ERR_IND)
   {
        printf("get ecpri ru cfg decode %d\n", oam->u.result.err_code);
   }
   else if(oam->Head.MsgId == PTP_GET_RSP)
   {
	ptp_cfg_print(&oam->u.ptp_cfg);
   }
   else
   {
	printf("Line %d, %s msg id %d error \n", __LINE__, __func__, oam->Head.MsgId);
   }
}

static int get_ecpri_ptp_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(PTP_GET_RSP, oam_get_ecpri_ptp_cfg_rsp, &obj);
    pc802_oam_sub_msg_register(ECPRI_ERR_IND, oam_get_ecpri_ptp_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = PTP_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg(0, 0, &list, 1 ) ) {

#ifdef SEND_TEST_MSG
    OamSubMessage_t rsp_msg = {0};
    rsp_msg.u.ptp_cfg.ptp_enable = 1;
    rsp_msg.u.ptp_cfg.ptp_step_mode = 0;
    rsp_msg.u.ptp_cfg.ecpri_step_mode = 1;
    rsp_msg.u.ptp_cfg.ptp_domain = 62;
    rsp_msg.Head.MsgId = PTP_GET_RSP;
    rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t) + sizeof(OamSubMessageHeader_t) + sizeof(EcpriPtpCfg_t);
    send_test_msg(&rsp_msg);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
	  get_ecpri_ptp_cfg_decode(&obj.msg);
        }
        else
            printf( "PTP_SET_RSP recv timeout!\n" );
    }
    else
        printf("PTP_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(PTP_GET_RSP);
    pc802_oam_sub_msg_unregister(ECPRI_ERR_IND);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_read_ecpri_ptp_cfg {
    cmdline_fixed_string_t ptp_cfg;
};

cmdline_parse_token_string_t cmd_get_ecpri_ptp_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_read_ecpri_ptp_cfg, ptp_cfg, "show ptp cfg");

static void cmd_get_ecpri_ptp_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_ptp_cfg_handler(); 
}

cmdline_parse_inst_t get_ecpri_ptp_cfg = {
    .f = cmd_get_ecpri_ptp_cfg_parsed,
    .data = NULL,
    .help_str = "show ptp cfg <ptp_enable> <ptp_step_mode> <ecpri_step_mode> <ptp_domain>",
    .tokens = {
        (void *)&cmd_get_ecpri_ptp_cfg,
        NULL,
        },
};


#endif 


typedef enum {
    OduCmd_e = 1,       
    EcpriCmd_e,       
    PfiCmd_e,       
    QuitCmd_e,       
    OamMsgCmd_e
} OamMsgType_e;

static int run_num = OduCmd_e;


/***** pfi *******/
struct test_get_params {
        cmdline_fixed_string_t cmd;
};

cmdline_parse_token_string_t test_quit_token_cmd =
        TOKEN_STRING_INITIALIZER(struct test_get_params, cmd, "quit");

static void test_quit_callback(__rte_unused void *ptr_params, struct cmdline *ctx, __rte_unused void *ptr_data)
{
	run_num = OduCmd_e;
        cmdline_quit(ctx);
}

cmdline_parse_inst_t test_quit = {
        .f = test_quit_callback,
        .data = NULL,
        .help_str = "quit\n     Exit program",
        .tokens = {(void *)&test_quit_token_cmd, NULL},
};

cmdline_parse_ctx_t pfi_prompt_commands[] = {
        (cmdline_parse_inst_t *)&test_quit,
        NULL
};

static void pfi_main(void)
{
        struct cmdline *ctx_cmdline;

        ctx_cmdline = cmdline_stdin_new(pfi_prompt_commands, "ODU>>PfiApp>> ");
        cmdline_interact(ctx_cmdline);
        cmdline_stdin_exit(ctx_cmdline);
}


/***** ecpri *******/
struct pcmd_get_params {
        cmdline_fixed_string_t cmd;
};

cmdline_parse_token_string_t pcmd_quit_token_cmd =
        TOKEN_STRING_INITIALIZER(struct pcmd_get_params, cmd, "quit");


static void pcmd_quit_callback(__rte_unused void *ptr_params, struct cmdline *ctx, __rte_unused void *ptr_data)
{
	run_num = OduCmd_e;
        cmdline_quit(ctx);
}

cmdline_parse_inst_t ecpri_quit = {
        .f = pcmd_quit_callback,
        .data = NULL,
        .help_str = "quit\n     Exit program",
        .tokens = {(void *)&pcmd_quit_token_cmd, NULL},
};


cmdline_parse_ctx_t ecpri_prompt_commands[] = {
	(cmdline_parse_inst_t *)&set_comp_method_cfg,
    	(cmdline_parse_inst_t *)&set_ecpri_du_cfg,
    	(cmdline_parse_inst_t *)&set_ecpri_ptp_cfg,
    	(cmdline_parse_inst_t *)&set_ecpri_tx_rx_cfg,
    	(cmdline_parse_inst_t *)&set_ecpri_ru_cfg,
    	(cmdline_parse_inst_t *)&get_ecpri_basic_cfg,
    	(cmdline_parse_inst_t *)&get_comp_method_cfg,
    	(cmdline_parse_inst_t *)&get_ecpri_du_cfg,
    	(cmdline_parse_inst_t *)&get_ecpri_du_internal_cfg,
    	(cmdline_parse_inst_t *)&get_ecpri_tx_rx_cfg,
    	(cmdline_parse_inst_t *)&get_ecpri_ptp_cfg,
    	(cmdline_parse_inst_t *)&get_eth_mtu_cfg,
    	(cmdline_parse_inst_t *)&get_ecpri_ru_cfg,
    	(cmdline_parse_inst_t *)&get_ecpri_perf_kpis,
    	(cmdline_parse_inst_t *)&run_test_case,
        (cmdline_parse_inst_t *)&ecpri_quit,
        NULL
};

static void ecpri_main(void)
{
        struct cmdline *ctx_cmdline;

        ctx_cmdline = cmdline_stdin_new(ecpri_prompt_commands, "ODU>>EcpriApp>> ");
        cmdline_interact(ctx_cmdline);
        cmdline_stdin_exit(ctx_cmdline);
}


/***** ODU *******/
struct pfi_get_params {
        cmdline_fixed_string_t cmd;
};

cmdline_parse_token_string_t pfi_token_cmd =
        TOKEN_STRING_INITIALIZER(struct pfi_get_params, cmd, "pfi");

static void pfi_callback(__rte_unused void *ptr_params, struct cmdline *ctx, __rte_unused void *ptr_data)
{
	run_num = PfiCmd_e;
        cmdline_quit(ctx);
}

cmdline_parse_inst_t pfi_cmd = {
        .f = pfi_callback,
        .data = NULL,
        .help_str = "pfi cmd",
        .tokens = {(void *)&pfi_token_cmd, NULL},
};

struct ecpri_get_params {
        cmdline_fixed_string_t cmd;
};

cmdline_parse_token_string_t ecpri_token_cmd =
        TOKEN_STRING_INITIALIZER(struct ecpri_get_params, cmd, "ecpri");

static void ecpri_callback(__rte_unused void *ptr_params, struct cmdline *ctx, __rte_unused void *ptr_data)
{
	run_num = EcpriCmd_e;
        cmdline_quit(ctx);
}

cmdline_parse_inst_t ecpri_cmd = {
        .f = ecpri_callback,
        .data = NULL,
        .help_str = "ecpri cmd",
        .tokens = {(void *)&ecpri_token_cmd, NULL},
};


struct odu_get_params {
        cmdline_fixed_string_t cmd;
};

cmdline_parse_token_string_t  odu_get_quit_token_cmd =
        TOKEN_STRING_INITIALIZER(struct odu_get_params, cmd, "quit");

static void odu_get_quit_callback(__rte_unused void *ptr_params, struct cmdline *ctx, __rte_unused void *ptr_data)
{
 	run_num = QuitCmd_e;
        cmdline_quit(ctx);
        cmdline_stdin_exit(ctx);

}

cmdline_parse_inst_t odu_quit = {
        .f = odu_get_quit_callback,
        .data = NULL,
        .help_str = "quit\n     Exit program",
        .tokens = {(void *)&odu_get_quit_token_cmd, NULL},
};

cmdline_parse_ctx_t odu_prompt_commands[] = {
        (cmdline_parse_inst_t *)&ecpri_cmd,
        (cmdline_parse_inst_t *)&pfi_cmd,
        (cmdline_parse_inst_t *)&odu_quit,
        NULL
};


static void odu_main(void)
{
        struct cmdline *ctx_cmdline;

        ctx_cmdline = cmdline_stdin_new(odu_prompt_commands, "ODU>> ");
        cmdline_interact(ctx_cmdline);
        cmdline_stdin_exit(ctx_cmdline);
}


void odu_cmd_main(void)
{
    while(1)
    {
        if(run_num == OduCmd_e)
        {
          odu_main();
        }
        else if (run_num == EcpriCmd_e)
        {
          ecpri_main();

        }
        else if(run_num == PfiCmd_e)
        {
          pfi_main();
        }

       if(run_num == QuitCmd_e)
       {
         break;
       }
   }
}
