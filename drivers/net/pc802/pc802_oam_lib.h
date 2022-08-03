/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
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
    COMP_METH_GET_REQ,
    COMP_METH_GET_RSP,
    COMP_METH_SET_REQ,
    ETH_MTU_GET_REQ,
    ETH_MTU_GET_RSP,
    TX_RX_GET_REQ,
    TX_RX_GET_RSP,
    TX_RX_SET_REQ,
    ECPRI_RU_GET_REQ,
    ECPRI_RU_GET_RSP,
    ECPRI_RU_SET_REQ,
    ECPRI_DU_LOCAL_GET_REQ,
    ECPRI_DU_LOCAL_GET_RSP,
    ECPRI_DU_GET_REQ,
    ECPRI_DU_GET_RSP,
    ECPRI_DU_SET_REQ,
    ECPRI_DU_KPIS_GET_REQ,
    ECPRI_DU_KPIS_GET_RSP,
    ECPRI_TEST_NTFY,
    ECPRI_ERR_IND,
}EcpriOamType_e;

typedef struct{
    uint8_t pcie_enable;// 1: enable 0: disable
    uint8_t eth_type;// 0: 25Gbps 1: 10Gpbs
    uint8_t max_antenna_cnt;
    uint8_t max_section_cnt;
    uint8_t max_symbol_cnt_per_slot;
    uint8_t cur_antenna_cnt;
    uint8_t cur_section_cnt;
    uint8_t cur_symbol_cnt_per_slot;
    uint8_t pipeline_mode;//0:non-pipeline,1:pipeline
    uint8_t outgoing_core_cnt;
    uint8_t ingoing_core_cnt;// maxium 7
    uint8_t reserved;
    uint32_t eth_pkt_size;
    uint32_t pEcpriNtfyBuf;
    uint32_t pEcpriReqBuf;
    uint32_t om_msg_id;
}BasicCfg_t;


typedef struct EcpriPtpCfg_t{
    uint8_t ptp_enable;// 1: enable 0: disable
    uint8_t ptp_step_mode;// 1: 1step 0: 2 step // startup required------------------------------------------
    uint8_t ecpri_step_mode;// 1: 1step 0: 2 step// startup required------------------------------------------
    uint8_t ptp_domain;// 1: 1step 0: 2 step// startup required------------------------------------------
}EcpriPtpCfg_t;

typedef struct{
    uint8_t isStaticComp;
    uint8_t method;
    uint8_t comIqWidth;
    uint8_t decomIqWidth;
}EcpriCompMethodCfg_t;

typedef struct{
    uint32_t mtu;
}EcpriEthMtuCfg_t;

typedef struct{
    uint32_t maxTxLateThreshold;
}EcpriTxRxCfg_t;

typedef struct{
    uint8_t ru_id;
    uint8_t rev0;
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
    uint16_t rev1;
}EcpriRuCfg_t;

typedef struct{
    uint8_t pipeline_mode;//0:non-pipeline,1:pipeline
    uint8_t m_role;//1--du 0--ru   // startup required------------------------------------------
    uint8_t outgoing_core_cnt;// startup required------------------------------------------
    uint8_t ingoing_core_cnt; // startup required------------------------------------------
}EcpriDuInternalCfg_t;

typedef struct EcpriDuCfg{
    uint8_t cp_enable;
    uint8_t ru_cnt; // startup required------------------------------------------
    uint8_t du_mac[ETH_MAC_ADDR_LEN];
    uint16_t vlan_id;
    uint16_t reserved;
}EcpriDuCfg_t;

typedef struct{
	uint32_t m_rx_total_l;
	uint32_t m_rx_total_h;
	uint32_t m_rx_on_time_l;
	uint32_t m_rx_on_time_h;
	uint32_t m_rx_early_l;
	uint32_t m_rx_early_h;
	uint32_t m_rx_late_l;
	uint32_t m_rx_late_h;
	uint32_t m_rx_seqid_err_l;//optional
	uint32_t m_rx_seqid_err_h;//optional
	uint32_t m_rx_on_time_c_l;
	uint32_t m_rx_on_time_c_h;
	uint32_t m_rx_early_c_l;
	uint32_t m_rx_early_c_h;
	uint32_t m_rx_late_c_l;
	uint32_t m_rx_late_c_h;
	uint32_t m_rx_seqid_err_c_l;//optional
	uint32_t m_rx_seqid_err_c_h;//optional
	uint32_t m_rx_corrupt_l;//optional
	uint32_t m_rx_corrupt_h;//optional
	uint32_t m_rx_err_drop_l;//optional
	uint32_t m_rx_err_drop_h;//optional
	uint32_t m_rx_pkt_dupl_l;//optional
	uint32_t m_rx_pkt_dupl_h;//optional
	uint32_t m_tx_total_l;
	uint32_t m_tx_total_h;
	uint32_t m_tx_total_c_l;
	uint32_t m_tx_total_c_h;
}EcpriPerfKpis_t;

typedef struct{
    uint16_t err_code;	            //0-255	Error code defined in Table 4 31
    uint16_t body_size;             //0-65535	The number of bytes in the body
    uint8_t req_body[0];		    //The body of the original request
}OamErrorInd_t;

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
        EcpriEthMtuCfg_t	mtu_cfg;
        EcpriTxRxCfg_t          tx_rx_cfg;
        EcpriRuCfg_t            ru_cfg;
        EcpriDuInternalCfg_t    du_int_cfg;
        EcpriDuCfg_t            du_cfg;
        EcpriPerfKpis_t         kpis;
        OamErrorInd_t           result;
        uint8_t kpi_rpt_flag;
    }u;
}OamSubMessage_t;

typedef int32_t (*PC802_OAM_CALLBACK_FUNTION)( void *arg, uint16_t dev_index, const OamSubMessage_t **sub_msg, uint32_t msg_num );

int pc802_oam_init(void);
int pc802_oam_register( PC802_OAM_CALLBACK_FUNTION recv_fun, void *arg );
int pc802_oam_unregister(void);
int pc802_oam_sub_msg_register( uint16_t sub_msg_id, PC802_OAM_CALLBACK_FUNTION recv_fun, void *arg );
int pc802_oam_sub_msg_unregister( uint16_t sub_msg_id );
int pc802_oam_send_msg( uint16_t dev_index, const OamSubMessage_t **sub_msg, uint32_t msg_num );

#endif
