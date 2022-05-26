/*
v0.1 initial version
*/
#ifndef __PC802_OAM_LIB_H_
#define __PC802_OAM_LIB_H_

#define ETH_MAC_ADDR_LEN 6

typedef enum{
    BASIC_CFG_GET_REQ=1000,
    BASIC_CFG_GET_RSP,
    PTP_GET_REQ,
    PTP_GET_RSP,
    PTP_SET_REQ,
    PTP_SET_RSP,
    COMP_METH_GET_REQ,
    COMP_METH_GET_RSP,
    COMP_METH_SET_REQ,
    COMP_METH_SET_RSP,
    TX_RX_GET_REQ,
    TX_RX_GET_RSP,
    TX_RX_SET_REQ,
    TX_RX_SET_RSP,
    ECPRI_RU_GET_REQ,
    ECPRI_RU_GET_RSP,
    ECPRI_RU_SET_REQ,
    ECPRI_RU_SET_RSP,
    ECPRI_DU_LOCAL_GET_REQ,
    ECPRI_DU_LOCAL_GET_RSP,
    ECPRI_DU_GET_REQ,
    ECPRI_DU_GET_RSP,
    ECPRI_DU_SET_REQ,
    ECPRI_DU_SET_RSP,
    ECPRI_DU_KPIS_GET_REQ,
    ECPRI_DU_KPIS_GET_RSP,
    ECPRI_TEST_NTFY,
    ECPRI_ERROR_IND,
}EcpriOamType_e;

typedef struct{
    uint8_t pcie_enable:1;// 1: enable 0: disable
    uint8_t eth_type:1;// 0: 25Gbps 1: 10Gpbs
    uint8_t max_antenna_cnt;
    uint8_t max_section_cnt;
    uint8_t max_symbol_cnt_per_slot;
    uint8_t cur_antenna_cnt;
    uint8_t cur_section_cnt;
    uint8_t cur_symbol_cnt_per_slot;
    uint32_t pEcpriNtfyBuf;
    uint32_t pEcpriReqBuf;
    uint32_t om_msg_id;
}BasicCfg_t;

typedef struct EcpriPtpCfg_t{
    uint8_t ptp_enable:1;// 1: enable 0: disable
    uint8_t ptp_step_mode:1;// 1: 1step 0: 2 step
    uint8_t ecpri_step_mode:1;// 1: 1step 0: 2 step
    uint8_t ptp_domain;
}EcpriPtpCfg_t;

typedef struct{
    uint8_t isStaticComp;
    uint8_t method;
    uint8_t comIqWidth;
    uint8_t decomIqWidth;
}EcpriCompMethodCfg_t;

typedef struct{
    uint32_t eth_pkt_size;
    uint16_t maxTxPacketSize;
    uint32_t maxTxLateThreshold;
}EcpriTxRxCfg_t;

typedef struct{
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
    uint8_t ru_mac[ETH_MAC_ADDR_LEN];
}EcpriRuCfg_t;

typedef struct{
    uint8_t pipeline_mode;          //0:non-pipeline,1:pipeline
    uint8_t m_role;                 //1--du 0--ru
    uint8_t outgoing_core_cnt;
    uint8_t ingoing_core_cnt;
}EcpriDuInternalCfg_t;

typedef struct EcpriDuCfg{
    uint8_t ru_cnt;
    uint8_t du_mac[ETH_MAC_ADDR_LEN];
    uint16_t vlan_id;
}EcpriDuCfg_t;

typedef struct{
    uint64_t m_rx_total;
    uint64_t m_rx_on_time;
    uint64_t m_rx_early;
    uint64_t m_rx_late;
    uint64_t m_rx_seqid_err;        //optional
    uint64_t m_rx_on_time_c;
    uint64_t m_rx_early_c;
    uint64_t m_rx_late_c;
    uint64_t m_rx_seqid_err_c;      //optional
    uint64_t m_rx_corrupt;          //optional
    uint64_t m_rx_err_drop;         //optional
    uint64_t m_rx_pkt_dupl;         //optional
    uint64_t m_tx_total;
    uint64_t m_tx_total_c;
}EcpriPerfKpis_t __attribute__((__aligned__(1)));

typedef struct{
    uint16_t err_code;	            //0-255	Error code defined in Table 4 31
    uint16_t body_size;             //0-65535	The number of bytes in the body
    uint8_t req_body[0];		    //The body of the original request
}OamErrorInd_t __attribute__((__aligned__(1)));

typedef struct{
    uint16_t MsgId;
    uint16_t MsgSize;
}OamSubMessageHeader_t;

typedef struct{
    OamSubMessageHeader_t Head;
    union {
        BasicCfg_t              basic_cfg;
        EcpriPtpCfg_t           ptp_cfg;
        EcpriCompMethodCfg_t    comp_method_cfg;
        EcpriTxRxCfg_t          tx_rx_cfg;
        EcpriRuCfg_t            ru_cfg;
        EcpriDuInternalCfg_t    du_int_cfg;
        EcpriDuCfg_t            du_cfg;
        EcpriPerfKpis_t         kpis;
        OamErrorInd_t           result;
        uint8_t kpi_rpt_flag;
    }u;
}OamSubMessage_t;

typedef int32_t (*PC802_OAM_CALLBACK_FUNTION)( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num );

int pc802_oam_init(void);
int pc802_oam_register( PC802_OAM_CALLBACK_FUNTION recv_fun, void *arg );
int pc802_oam_unregister(void);
int pc802_oam_sub_msg_register( uint16_t sub_msg_id, PC802_OAM_CALLBACK_FUNTION recv_fun, void *arg );
int pc802_oam_sub_msg_unregister( uint16_t sub_msg_id );
int pc802_oam_send_msg( uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num );

#endif