#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

#include <rte_debug.h>
#include <cmdline_parse.h>
#include <cmdline_parse_string.h>
#include <cmdline_parse_num.h>
#include <cmdline_socket.h>
#include <cmdline.h>
#include <cmdline_parse_etheraddr.h>
#include <rte_ether.h>

#include <rte_pmd_pc802.h>
#include <pc802_oam_lib.h>
#include "ecpri_oam_inf.h"


void odu_cmd_main(void);

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
static int send_ecpri_sub_msg(OamSubMessage_t *sub_msg, int32_t rsp_sub_id, int32_t ind_sub_id, pcxx_oam_cb_fn rsp_cb_fun, pcxx_oam_cb_fn ind_cb_fun )
{
    sem_t sem;
    const pcxx_oam_sub_msg_t *list = (const pcxx_oam_sub_msg_t *)sub_msg;
    struct timespec ts;

    sem_init(&sem, 0, 0);
    if (rsp_sub_id >= 0)
        pcxx_oam_sub_msg_register(PCXX_OAM_MSG, rsp_sub_id, rsp_cb_fun, &sem);
    if (ind_sub_id >= 0)
        pcxx_oam_sub_msg_register(PCXX_OAM_MSG, ind_sub_id, ind_cb_fun, &sem);

    if (0 == pcxx_oam_send_msg(0, PCXX_OAM_MSG, &list, 1)) {
#ifdef SEND_TEST_MSG
        switch( list->msg_id ){
        case COMP_METH_GET_REQ:
            OamSubMessage_t rsp_msg = {0};
            rsp_msg.u.comp_method_cfg.isStaticComp = 3;
            rsp_msg.u.comp_method_cfg.method = 1;
            rsp_msg.u.comp_method_cfg.comIqWidth = 2;
            rsp_msg.u.comp_method_cfg.decomIqWidth = 0;
            rsp_msg.Head.MsgId = COMP_METH_GET_RSP;
            rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t) + sizeof(OamSubMessageHeader_t) + sizeof(EcpriCompMethodCfg_t);
            send_test_msg(&rsp_msg);
            break;
        case BASIC_CFG_GET_REQ:
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
            send_test_msg(&rsp_msg);
            break;
        case ECPRI_DU_KPIS_GET_REQ:
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
            send_test_msg(&rsp_msg);
            break;
        case ECPRI_DU_GET_REQ:
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
            send_test_msg(&rsp_msg);
            break;
        case ECPRI_DU_LOCAL_GET_REQ:
            OamSubMessage_t rsp_msg = {0};
            rsp_msg.u.du_int_cfg.pipeline_mode = 1;
            rsp_msg.u.du_int_cfg.m_role = 1;
            rsp_msg.u.du_int_cfg.outgoing_core_cnt = 8;
            rsp_msg.u.du_int_cfg.ingoing_core_cnt = 9;
            rsp_msg.Head.MsgId = ECPRI_DU_LOCAL_GET_RSP;
            rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t) + sizeof(OamSubMessageHeader_t) + sizeof(EcpriDuInternalCfg_t);
            send_test_msg(&rsp_msg);
            break;
        case ECPRI_RU_GET_REQ:
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
            send_test_msg(&rsp_msg);
            break;
        case PTP_GET_REQ:
            OamSubMessage_t rsp_msg = {0};
            rsp_msg.u.ptp_cfg.ptp_enable = 1;
            rsp_msg.u.ptp_cfg.ptp_step_mode = 0;
            rsp_msg.u.ptp_cfg.ecpri_step_mode = 1;
            rsp_msg.u.ptp_cfg.ptp_domain = 62;
            rsp_msg.Head.MsgId = PTP_GET_RSP;
            rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t) + sizeof(OamSubMessageHeader_t) + sizeof(EcpriPtpCfg_t);
            send_test_msg(&rsp_msg);
            break;
        default:
            if ( ind_sub_id>=0 )
                rsp_msg_test(ind_sub_id);
            break;
        }
#endif
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 1;
        if (0 != sem_timedwait(&sem, &ts))
            printf("Sub msg=%d wait rsp timeout!\n", list->msg_id);
    } else
        printf("Sub msg=%d send err!\n", list->msg_id);

    if (rsp_sub_id >= 0)
        pcxx_oam_sub_msg_unregister(PCXX_OAM_MSG, rsp_sub_id);
    if (ind_sub_id >= 0)
        pcxx_oam_sub_msg_unregister(PCXX_OAM_MSG, ind_sub_id);

    sem_destroy(&sem);
    return 0;
}

static int32_t oam_ind_rsp( void *arg, uint16_t port_id, __rte_unused uint32_t msg_type, const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num )
{
    const OamSubMessage_t *sub = (const OamSubMessage_t *)sub_msg[0];
    printf( "Dev %d rsp oam msg(%u) include sub msg(%u)\n", port_id, msg_type, msg_num );

    if ( 0 == sub->u.result.err_code )
        printf( "oam rsp ok.\n" );
    else
        printf( "oam rsp err(%d)!\n", sub->u.result.err_code );

    sem_post( (sem_t *)arg );
    return 0;
}

static int send_ecpri_get_msg(int32_t req_sub_id, int32_t rsp_sub_id, pcxx_oam_cb_fn rsp_cb_fun )
{
    OamSubMessage_t sub_msg;
    sub_msg.Head.MsgId = req_sub_id;
    sub_msg.Head.MsgSize = 0;
    return send_ecpri_sub_msg(&sub_msg, rsp_sub_id, ECPRI_ERR_IND, rsp_cb_fun, oam_ind_rsp);
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
    OamSubMessage_t sub_msg;
    sub_msg.Head.MsgId = TX_RX_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriTxRxCfg_t);
    sub_msg.u.tx_rx_cfg.maxTxLateThreshold = cfg->maxTxLateThreshold;
    send_ecpri_sub_msg( &sub_msg, -1, ECPRI_ERR_IND, NULL, oam_ind_rsp);
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

static int set_ecpri_ptp_cfg_handler(uint8_t ptp_enable, uint8_t ptp_step_mode, uint8_t ecpri_step_mode, uint8_t ptp_domain)
{
    OamSubMessage_t sub_msg;
    sub_msg.Head.MsgId = PTP_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriPtpCfg_t);
    sub_msg.u.ptp_cfg.ptp_domain = ptp_domain;
    sub_msg.u.ptp_cfg.ptp_enable = ptp_enable;
    sub_msg.u.ptp_cfg.ptp_step_mode = ptp_step_mode;
    sub_msg.u.ptp_cfg.ecpri_step_mode = ecpri_step_mode;
    send_ecpri_sub_msg( &sub_msg, -1, ECPRI_ERR_IND, NULL, oam_ind_rsp);
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

static int set_ecpri_ru_cfg_handler(EcpriRuCfg_t *cfg)
{
    OamSubMessage_t sub_msg;
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
    send_ecpri_sub_msg( &sub_msg, -1, ECPRI_ERR_IND, NULL, oam_ind_rsp);
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

static int set_ecpri_du_cfg_handler(uint8_t cp_enable, uint8_t ru_cnt, uint16_t vlan_id, uint8_t *addr_bytes)
{
    OamSubMessage_t sub_msg;
    sub_msg.Head.MsgId = ECPRI_DU_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriDuCfg_t);
    sub_msg.u.du_cfg.ru_cnt = ru_cnt;
    sub_msg.u.du_cfg.vlan_id = vlan_id;
    sub_msg.u.du_cfg.cp_enable = cp_enable;
    memcpy(sub_msg.u.du_cfg.du_mac, addr_bytes, ETH_MAC_ADDR_LEN);
    send_ecpri_sub_msg( &sub_msg, -1, ECPRI_ERR_IND, NULL, oam_ind_rsp);
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

static int set_ecpri_comp_method_cfg_handler(uint8_t isStaticComp, uint8_t method, uint8_t comIqWidth, uint8_t decomIqWidth)
{
    OamSubMessage_t sub_msg;
    sub_msg.Head.MsgId = COMP_METH_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriCompMethodCfg_t);
    sub_msg.u.comp_method_cfg.isStaticComp = isStaticComp;
    sub_msg.u.comp_method_cfg.method = method;
    sub_msg.u.comp_method_cfg.comIqWidth = comIqWidth;
    sub_msg.u.comp_method_cfg.decomIqWidth = decomIqWidth;
    send_ecpri_sub_msg( &sub_msg, -1, ECPRI_ERR_IND, NULL, oam_ind_rsp);
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

static void comp_method_cfg_print(const EcpriCompMethodCfg_t *cfg)
{
    printf("isStaticComp:     %d\n",  cfg->isStaticComp);
    printf("method:           %d\n",  cfg->method);
    printf("comIqWidth:       %d\n",  cfg->comIqWidth);
    printf("decomIqWidth:     %d\n",  cfg->decomIqWidth);
}

/*oam get ecpri comp method cfg*/
static int32_t oam_get_ecpri_comp_method_cfg_rsp(void *arg, uint16_t port_id, uint32_t msg_type,  const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num)
{
    printf( "Dev %d rsp oam msg(%u) include sub msg(%u)\n", port_id, msg_type, msg_num );
    const OamSubMessage_t *sub = (const OamSubMessage_t *)sub_msg[0];
    comp_method_cfg_print(&sub->u.comp_method_cfg);
    sem_post( (sem_t *)arg );
    return 0;
}

struct cmd_read_ecpri_comp_method_cfg {
    cmdline_fixed_string_t comp_method_cfg;
};

static void cmd_get_ecpri_comp_method_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    send_ecpri_get_msg(COMP_METH_GET_REQ, COMP_METH_GET_RSP, oam_get_ecpri_comp_method_cfg_rsp);
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
static int32_t oam_get_eth_mtu_cfg_rsp(void *arg, uint16_t port_id, uint32_t msg_type,  const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num)
{
    printf( "Dev %d rsp oam msg(%u) include sub msg(%u)\n", port_id, msg_type, msg_num );
    const OamSubMessage_t *sub = (const OamSubMessage_t *)sub_msg[0];
    printf("mtu:    %d\n", sub->u.mtu_cfg.mtu);
    sem_post( (sem_t *)arg );
    return 0;
}

struct cmd_read_eth_mtu_cfg {
    cmdline_fixed_string_t mtu_cfg;
};

static void cmd_get_ecpri_eth_mtu_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    send_ecpri_get_msg( ETH_MTU_GET_REQ, ETH_MTU_GET_RSP, oam_get_eth_mtu_cfg_rsp );
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

static void basic_cfg_print(const BasicCfg_t *cfg)
{
    printf("eth_type:               %d\n", cfg->eth_type);
    printf("max_antenna_cnt:        %d\n", cfg->max_antenna_cnt);
    printf("max_section_cnt:        %d\n", cfg->max_section_cnt);
    printf("max_symbol_cnt_per_slot:%d\n", cfg->max_symbol_cnt_per_slot);
    printf("cur_antenna_cnt:        %d\n", cfg->cur_antenna_cnt);
    printf("cur_section_cnt:        %d\n", cfg->cur_section_cnt);
    printf("cur_symbol_cnt_per_slot:%d\n", cfg->cur_symbol_cnt_per_slot);
}

/*oam get ecpri basic cfg*/
static int32_t oam_get_ecpri_basic_cfg_rsp( void *arg, uint16_t port_id, uint32_t msg_type __rte_unused,  const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num )
{
    printf( "Dev %d rsp oam msg(%u) include sub msg(%u)\n", port_id, msg_type, msg_num );
    const OamSubMessage_t *sub = (const OamSubMessage_t *)sub_msg[0];
    basic_cfg_print(&sub->u.basic_cfg);
    sem_post( (sem_t *)arg );
    return 0;
}
struct cmd_ecpri_basic_cfg {
    cmdline_fixed_string_t basic_cfg;
};

static void cmd_get_ecpri_basic_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    send_ecpri_get_msg(BASIC_CFG_GET_REQ, BASIC_CFG_GET_RSP, oam_get_ecpri_basic_cfg_rsp);
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

static void ecpri_kpis_print(const EcpriPerfKpis_t *kpis)
{
    if (kpis->m_rx_total_h == 0)
        printf("m_rx_total:                  %d\n", kpis->m_rx_total_l);
    else
        printf("m_rx_total:                  %d%032d\n", kpis->m_rx_total_h, kpis->m_rx_total_l);

    if (kpis->m_rx_on_time_h == 0)
        printf("m_rx_on_time:                %d\n", kpis->m_rx_on_time_l);
    else
        printf("m_rx_on_time:                %d%032d\n", kpis->m_rx_on_time_h, kpis->m_rx_on_time_l);

    if (kpis->m_rx_early_h == 0)
        printf("m_rx_early:                  %d\n", kpis->m_rx_early_l);
    else
        printf("m_rx_early:                  %d%032d\n", kpis->m_rx_early_h, kpis->m_rx_early_l);

    if (kpis->m_rx_late_h == 0)
        printf("m_rx_late:                   %d\n", kpis->m_rx_late_l);
    else
        printf("m_rx_late:                   %d%032d\n", kpis->m_rx_late_h, kpis->m_rx_late_l);

    if (kpis->m_rx_seqid_err_h == 0)
        printf("m_rx_seqid_err:              %d\n", kpis->m_rx_seqid_err_l);
    else
        printf("m_rx_seqid_err:              %d%032d\n", kpis->m_rx_seqid_err_h, kpis->m_rx_seqid_err_l);

    if (kpis->m_rx_on_time_c_h == 0)
        printf("m_rx_on_time_c:              %d\n", kpis->m_rx_on_time_c_l);
    else
        printf("m_rx_on_time_c:              %d%032d\n", kpis->m_rx_on_time_c_h, kpis->m_rx_on_time_c_l);

    if (kpis->m_rx_early_c_h == 0)
        printf("m_rx_early_c:                %d\n", kpis->m_rx_early_c_l);
    else
        printf("m_rx_early_c:                %d%032d\n", kpis->m_rx_early_c_h, kpis->m_rx_early_c_l);

    if (kpis->m_rx_late_c_h == 0)
        printf("m_rx_late_c:                 %d\n", kpis->m_rx_late_c_l);
    else
        printf("m_rx_late_c:                 %d%032d\n", kpis->m_rx_late_c_h, kpis->m_rx_late_c_l);

    if (kpis->m_rx_seqid_err_c_h == 0)
        printf("m_rx_seqid_err_c:            %d\n", kpis->m_rx_seqid_err_c_l);
    else
        printf("m_rx_seqid_err_c:            %d%032d\n", kpis->m_rx_seqid_err_c_h, kpis->m_rx_seqid_err_c_l);

    if (kpis->m_rx_corrupt_h == 0)
        printf("m_rx_corrupt:                %d\n", kpis->m_rx_corrupt_l);
    else
        printf("m_rx_corrupt:                %d%032d\n", kpis->m_rx_corrupt_h, kpis->m_rx_corrupt_l);

    if (kpis->m_rx_err_drop_h == 0)
        printf("m_rx_err_drop:               %d\n", kpis->m_rx_err_drop_l);
    else
        printf("m_rx_err_drop:               %d%032d\n", kpis->m_rx_err_drop_h, kpis->m_rx_err_drop_l);

    if (kpis->m_rx_pkt_dupl_h == 0)
        printf("m_rx_pkt_dupl:               %d\n", kpis->m_rx_pkt_dupl_l);
    else
        printf("m_rx_pkt_dupl:               %d%032d\n", kpis->m_rx_pkt_dupl_h, kpis->m_rx_pkt_dupl_l);

    if (kpis->m_tx_total_h == 0)
        printf("m_tx_total:                  %d\n", kpis->m_tx_total_l);
    else
        printf("m_tx_total:                  %d%032d\n", kpis->m_tx_total_h, kpis->m_tx_total_l);

    if (kpis->m_tx_total_c_h == 0)
        printf("m_tx_total_c:                %d\n", kpis->m_tx_total_c_l);
    else
        printf("m_tx_total_c:                %d%032d\n", kpis->m_tx_total_c_h, kpis->m_tx_total_c_l);
}

/*oam get ecpri perf kpis */
static int32_t oam_get_ecpri_perf_kpis_rsp( void *arg, uint16_t port_id, uint32_t msg_type __rte_unused,  const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num )
{
    printf( "Dev %d rsp oam msg(%u) include sub msg(%u)\n", port_id, msg_type, msg_num );
    const OamSubMessage_t *sub = (const OamSubMessage_t *)sub_msg[0];
    ecpri_kpis_print(&sub->u.kpis);
    sem_post( (sem_t *)arg );
    return 0;
}

struct cmd_ecpri_perf_kpis {
    cmdline_fixed_string_t ecpri_perf_kpis;
};

static void cmd_get_ecpri_perf_kpis_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    send_ecpri_get_msg(ECPRI_DU_KPIS_GET_REQ, ECPRI_DU_KPIS_GET_RSP, oam_get_ecpri_perf_kpis_rsp);
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

static void du_cfg_print(const EcpriDuCfg_t *cfg)
{
    printf("cp_enable:       %d\n", cfg->cp_enable);
    printf("vlan_id:         %d\n", cfg->vlan_id);
    printf("ru_cnt:          %d\n", cfg->ru_cnt);
    printf("du_mac:          %02x:%02x:%02x:%02x:%02x:%02x\n", cfg->du_mac[0], cfg->du_mac[1], cfg->du_mac[2],
           cfg->du_mac[3], cfg->du_mac[4], cfg->du_mac[5]);
}

/*oam get ecpri du cfg*/
static int32_t oam_get_ecpri_du_cfg_rsp( void *arg, uint16_t port_id, uint32_t msg_type __rte_unused,  const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num )
{
    printf( "Dev %d rsp oam msg(%u) include sub msg(%u)\n", port_id, msg_type, msg_num );
    const OamSubMessage_t *sub = (const OamSubMessage_t *)sub_msg[0];
    du_cfg_print(&sub->u.du_cfg);
    sem_post( (sem_t *)arg );
    return 0;
}

struct cmd_read_ecpri_du_cfg {
    cmdline_fixed_string_t ecpri_du_cfg;
};

static void cmd_get_ecpri_du_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    send_ecpri_get_msg(ECPRI_DU_GET_REQ, ECPRI_DU_GET_RSP, oam_get_ecpri_du_cfg_rsp);
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

static void du_internal_cfg_print(const EcpriDuInternalCfg_t *cfg)
{
    printf("pipeline_mode:        %d\n", cfg->pipeline_mode);
    printf("m_role:               %d\n", cfg->m_role);
    printf("outgoing_core_cnt:    %d\n", cfg->outgoing_core_cnt);
    printf("ingoing_core_cnt:     %d\n", cfg->ingoing_core_cnt);
}

/*oam get ecpri du inernal cfg*/
static int32_t oam_get_ecpri_du_internal_cfg_rsp( void *arg, uint16_t port_id, uint32_t msg_type __rte_unused,  const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num )
{
    printf( "Dev %d rsp oam msg(%u) include sub msg(%u)\n", port_id, msg_type, msg_num );
    const OamSubMessage_t *sub = (const OamSubMessage_t *)sub_msg[0];
    du_internal_cfg_print(&sub->u.du_int_cfg);
    sem_post( (sem_t *)arg );
    return 0;
}

struct cmd_ecpri_du_internal_cfg {
    cmdline_fixed_string_t cmd_ecpri_du_internal_cfg;
};

static void cmd_get_ecpri_du_internal_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    send_ecpri_get_msg(ECPRI_DU_LOCAL_GET_REQ, ECPRI_DU_LOCAL_GET_RSP, oam_get_ecpri_du_internal_cfg_rsp);
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

static void ru_cfg_print(const EcpriRuCfg_t *cfg)
{
    printf("ru_id:              %d\n", cfg->ru_id);
    printf("s_interval:         %d\n", cfg->s_interval);
    printf("Ta4min:             %d\n", cfg->Ta4min);
    printf("Ta4max:             %d\n", cfg->Ta4max);
    printf("T1amin_cp_ul:       %d\n", cfg->T1amin_cp_ul);
    printf("T1amax_cp_ul:       %d\n", cfg->T1amax_cp_ul);
    printf("T1amin_cp_dl:       %d\n", cfg->T1amin_cp_dl);
    printf("T1amax_cp_dl:       %d\n", cfg->T1amax_cp_dl);
    printf("T1amin_up:          %d\n", cfg->T1amin_up);
    printf("T1amax_up:          %d\n", cfg->T1amax_up);
    printf("ru_mac:             %02x:%02x:%02x:%02x:%02x:%02x\n", cfg->ru_mac[0], cfg->ru_mac[1], cfg->ru_mac[2],
           cfg->ru_mac[3], cfg->ru_mac[4], cfg->ru_mac[5]);
}

/* oam get ecpri ru cfg*/
static int32_t oam_get_ecpri_ru_cfg_rsp( void *arg, uint16_t port_id, uint32_t msg_type __rte_unused,  const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num )
{
    printf( "Dev %d rsp oam msg(%u) include sub msg(%u)\n", port_id, msg_type, msg_num );
    const OamSubMessage_t *sub = (const OamSubMessage_t *)sub_msg[0];
    ru_cfg_print(&sub->u.ru_cfg);
    sem_post( (sem_t *)arg );
    return 0;
}
struct cmd_read_ecpri_ru_cfg {
    cmdline_fixed_string_t ecpri_ru_cfg;
};

static void cmd_get_ecpri_ru_cfg_parsed(__attribute__((unused))void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    send_ecpri_get_msg(ECPRI_RU_GET_REQ, ECPRI_RU_GET_RSP, oam_get_ecpri_ru_cfg_rsp );
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
static int32_t oam_get_ecpri_tx_rx_cfg_rsp( void *arg, uint16_t port_id, uint32_t msg_type __rte_unused, const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num )
{
    printf( "Dev %d rsp oam msg(%u) include sub msg(%u)\n", port_id, msg_type, msg_num );
    const OamSubMessage_t *sub = (const OamSubMessage_t *)sub_msg[0];
    printf("maxTxLateThreshold:   %u\n", sub->u.tx_rx_cfg.maxTxLateThreshold);
    sem_post( (sem_t *)arg );
    return 0;
}

struct cmd_read_ecpri_tx_rx_cfg {
    cmdline_fixed_string_t ecpri_tx_rx_cfg;
};

static void cmd_get_ecpri_tx_rx_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    send_ecpri_get_msg(TX_RX_GET_REQ, TX_RX_GET_RSP, oam_get_ecpri_tx_rx_cfg_rsp);
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

static void ptp_cfg_print(const EcpriPtpCfg_t *cfg)
{
    printf("ptp_enable:               %d\n", cfg->ptp_enable);
    printf("ptp_step_mode:            %d\n", cfg->ptp_step_mode);
    printf("ecpri_step_mode:          %d\n", cfg->ecpri_step_mode);
    printf("ptp_domain:               %d\n", cfg->ptp_domain);
}

/* oam get ecpri ptp cfg*/
static int32_t oam_get_ecpri_ptp_cfg_rsp( void *arg, uint16_t port_id, uint32_t msg_type __rte_unused, const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num )
{
    printf( "Dev %d rsp oam msg(%u) include sub msg(%u)\n", port_id, msg_type, msg_num );
    const OamSubMessage_t *sub = (const OamSubMessage_t *)sub_msg[0];
    ptp_cfg_print( &sub->u.ptp_cfg );
    sem_post( (sem_t *)arg );
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
    send_ecpri_get_msg(PTP_GET_REQ, PTP_GET_RSP, oam_get_ecpri_ptp_cfg_rsp);
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

cmdline_parse_token_string_t test_quit_token_cmd = TOKEN_STRING_INITIALIZER(struct test_get_params, cmd, "quit");

static void test_quit_callback(__rte_unused void *ptr_params, struct cmdline *ctx, __rte_unused void *ptr_data)
{
    run_num = OduCmd_e;
    cmdline_quit(ctx);
}

cmdline_parse_inst_t test_quit = {
    .f = test_quit_callback,
    .data = NULL,
    .help_str = "quit\n     Exit program",
    .tokens = {
        (void *)&test_quit_token_cmd,
        NULL
    },
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

cmdline_parse_token_string_t pcmd_quit_token_cmd = TOKEN_STRING_INITIALIZER(struct pcmd_get_params, cmd, "quit");

static void pcmd_quit_callback(__rte_unused void *ptr_params, struct cmdline *ctx, __rte_unused void *ptr_data)
{
    run_num = OduCmd_e;
    cmdline_quit(ctx);
}

cmdline_parse_inst_t ecpri_quit = {
    .f = pcmd_quit_callback,
    .data = NULL,
    .help_str = "quit\n     Exit program",
    .tokens = {
        (void *)&pcmd_quit_token_cmd,
        NULL
    },
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

cmdline_parse_token_string_t pfi_token_cmd = TOKEN_STRING_INITIALIZER(struct pfi_get_params, cmd, "pfi");

static void pfi_callback(__rte_unused void *ptr_params, struct cmdline *ctx, __rte_unused void *ptr_data)
{
    run_num = PfiCmd_e;
    cmdline_quit(ctx);
}

cmdline_parse_inst_t pfi_cmd = {
    .f = pfi_callback,
    .data = NULL,
    .help_str = "pfi cmd",
    .tokens = {
        (void *)&pfi_token_cmd,
        NULL
    },
};

struct ecpri_get_params {
    cmdline_fixed_string_t cmd;
};

cmdline_parse_token_string_t ecpri_token_cmd = TOKEN_STRING_INITIALIZER(struct ecpri_get_params, cmd, "ecpri");

static void ecpri_callback(__rte_unused void *ptr_params, struct cmdline *ctx, __rte_unused void *ptr_data)
{
    run_num = EcpriCmd_e;
    cmdline_quit(ctx);
}

cmdline_parse_inst_t ecpri_cmd = {
    .f = ecpri_callback,
    .data = NULL,
    .help_str = "ecpri cmd",
    .tokens = {
        (void *)&ecpri_token_cmd,
        NULL
    },
};

struct odu_get_params {
    cmdline_fixed_string_t cmd;
};

cmdline_parse_token_string_t odu_get_quit_token_cmd = TOKEN_STRING_INITIALIZER(struct odu_get_params, cmd, "quit");

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
    .tokens = {
        (void *)&odu_get_quit_token_cmd,
        NULL
    },
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
    while (1) {
        if (run_num == OduCmd_e)
            odu_main();
        else if (run_num == EcpriCmd_e)
            ecpri_main();
        else if (run_num == PfiCmd_e)
            pfi_main();

        if (run_num == QuitCmd_e) {
            break;
        }
    }
}
