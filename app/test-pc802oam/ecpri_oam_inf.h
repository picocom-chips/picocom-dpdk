/*
 * PICOCOM PROPRIETARY INFORMATION
 *
 * This software is supplied under the terms of a license agreement or
 * nondisclosure agreement with PICOCOM and may not be copied
 * or disclosed except in accordance with the terms of that agreement.
 *
 * Copyright PICOCOM.
 */
#pragma once

#define ETH_MAC_ADDR_LEN 6
#define MAX_CELL_NUM 2
#define MAX_RU_NUM 4

#define OAM_BASE_NUM      2
#define OAM_ETHERNET_NUM (3+OAM_BASE_NUM)
#define OAM_PTP_NUM      (2+OAM_ETHERNET_NUM)
#define OAM_RU_NUM       (1+OAM_PTP_NUM)
#define OAM_COMP_NUM     (1+OAM_RU_NUM)
#define OAM_TRANSMIT_NUM (2+OAM_COMP_NUM)
#define OAM_CELL_NUM     (3+OAM_TRANSMIT_NUM)

typedef enum ecpri_oam_type{
    ECPRI_OAM_GET_REQ=1000,
    ECPRI_OAM_GET_RESP,
    ECPRI_OAM_SET_REQ,
    ECPRI_OAM_SET_RESP,
    ECPRI_OAM_TEST_NTFY,
    ECPRI_OAM_ERR_IND,
}ecpri_oam_type;

typedef enum ecpri_oam_tag{
    ECPRI_OAM_BASE_CFG=0x1000,//basic msg
    ECPRI_OAM_BASE_INFO,
    ECPRI_OAM_ETHERNET_CFG=0x1100,
    ECPRI_OAM_ETHERNET_INFO,
    ECPRI_OAM_ETHERNET_STATS,
    ECPRI_OAM_PTP_CFG=0x1200,
    ECPRI_OAM_PTP_STATS,
    ECPRI_OAM_RU_CFG=0x1300,
    ECPRI_OAM_UP_COMP_CFG=0x1400,
    ECPRI_OAM_TRANSMISSION_WINDOWS_CFG=0x1500,
    ECPRI_OAM_ONE_WAY_DELAY_MEASUREMENT_STATS,
    ECPRI_OAM_CELL_CFG=0x1600,
    ECPRI_OAM_CELL_STATS,
    ECPRI_OAM_CELL_RESERVED_STATS,
}ecpri_oam_tag;

typedef struct oam_tlvs_t{
    uint16_t tag;
    uint16_t length;
}oam_tlvs_t;

typedef struct oam_get_req_t{
    uint16_t num_tlvs;
    oam_tlvs_t tlvs;
}oam_get_req_t;

typedef struct oam_get_rsp_t{
    uint16_t num_tlvs;
    oam_tlvs_t tlvs;
}oam_get_rsp_t;

typedef struct oam_set_req_t{
    uint16_t num_tlvs;
    oam_tlvs_t tlvs;
}oam_set_req_t;

typedef struct oam_set_rsp_t{
    uint16_t error_number;
    oam_tlvs_t tlvs;
}oam_set_rsp_t;

typedef struct ecpri_base_config_t{
    uint8_t du_port_id_width;
    uint8_t bandsector_id_width;
    uint8_t cc_id_width;
    uint8_t ru_port_id_width;
    uint8_t one_way_delay_enable; //todo
    uint8_t ecpri_step_mode;
    uint8_t reserved[2];
}ecpri_base_config_t;

typedef struct ecpri_base_info_t{
    char version[32];
}ecpri_base_info_t;

typedef struct ecpri_ethernet_config_t{
    uint8_t type;
    uint8_t nic_enable;
    uint8_t du_mac[ETH_MAC_ADDR_LEN];
    uint16_t mtu;
    uint16_t mvlan;//todo
    uint8_t reserved[4];
}ecpri_ethernet_config_t;

typedef struct ecpri_ethernet_status_t{
    uint8_t sfp_status;//todo
    uint8_t sfp_type;//todo
    char sfp_vendor[30];//todo
    float temperature;//todo
    float tx_power;//todo
    float rx_power;//todo
    uint8_t link_status;
    uint8_t reserved[3];
}ecpri_ethernet_status_t;

typedef struct ecpri_ethernet_stats_t{
    uint32_t rx_ecpri_total;
    uint32_t rx_ecpri_err;
    uint32_t rx_ecpri_drop;
    uint32_t rx_ecpri_too_long;
    uint32_t rx_ecpri_too_short;
    uint32_t rx_non_ecpri_total;
    uint32_t rx_non_ecpri_too_long;
    uint32_t rx_non_ecpri_too_short;
    uint32_t tx_ecpri_total;
    uint32_t tx_non_ecpri_total;
    uint32_t reserved[6];
}ecpri_ethernet_stats_t;

typedef struct ecpri_ptp_config_t{
    uint8_t ptp_enable;
    uint8_t ptp_step_mode;
    uint8_t domain;
    uint8_t announce_freq;
    uint8_t sync_freq;
    uint8_t delay_freq;
    uint8_t ptp_grandmaster_class;
    uint8_t ptp_priority1;
    uint8_t ptp_priority2;
    uint8_t reserved[3];    
}ecpri_ptp_config_t;

typedef struct ecpri_ptp_stats_t{
    uint32_t announce;
    uint32_t sync;
    uint32_t follow_up;
    uint32_t delay_request;
    uint32_t delay_response;
    uint32_t unknown;
    uint32_t reserved[2];    
}ecpri_ptp_stats_t;

typedef struct ru_base_config_t{
    uint8_t ru_mac[ETH_MAC_ADDR_LEN];
    uint16_t uvlan;
    uint16_t cvlan;
    uint8_t cp_enable;
    uint8_t reserved[5];    
}ru_base_config_t;

typedef struct ecpri_ru_config_t{
    uint32_t ru_id;
    ru_base_config_t ru_config;
}ecpri_ru_config_t;

typedef struct comp_config_t{
    uint8_t isStaticComp;
    uint8_t method;
    uint8_t comIqWidth;
    uint8_t decomIqWidth;
}comp_config_t;

typedef struct ecpri_comp_config_t{
    uint32_t ru_id;
    comp_config_t comp_config;
}ecpri_comp_config_t;

typedef struct transmission_config_t{
    uint32_t ta4_min;
    uint32_t ta4_max;
    uint32_t tcp_adv_dl;
    uint32_t t1a_min_cp_ul;
    uint32_t t1a_max_cp_ul;
    uint32_t t1a_min_cp_dl;
    uint32_t t1a_max_cp_dl;
    uint32_t t1a_min_up;
    uint32_t t1a_max_up;
}transmission_config_t;

typedef struct ecpri_transmission_config_t{
    uint32_t ru_id;
    transmission_config_t transmission_config;
}ecpri_transmission_config_t;

typedef struct ecpri_one_way_delay_stats_t{
    uint32_t tx_request;
    uint32_t tx_follow_up;
    uint32_t rx_response;
    uint32_t tx_remote_request;
    uint32_t rx_request;
    uint32_t rx_follow_up;
    uint32_t tx_response;
}ecpri_one_way_delay_stats_t;

typedef struct cell_info_t{
    uint32_t ru_id;
    uint8_t tx_ant_mask;
    uint8_t rx_ant_mask;
    uint8_t band_sector_id;
    uint8_t reserved[5];
}cell_info_t;

typedef struct ecpri_cell_config_t{
    uint32_t cell_idx;
    cell_info_t cell_info;
}ecpri_cell_config_t;

typedef struct ecpri_cell_stats_t{
    uint32_t ul_total;
    uint32_t ul_total_cp;
    uint32_t ul_drop;
    uint32_t ul_on_time;
    uint32_t ul_early;
    uint32_t ul_late;
    uint32_t dl_total;
    uint32_t dl_total_cp;
}ecpri_cell_stats_t;

typedef struct ecpri_cell_reserved_stats_t{
    uint32_t ul_total;
    uint32_t ul_total_cp;
    uint32_t ul_drop;
    uint32_t ul_on_time;
    uint32_t ul_early;
    uint32_t ul_late;

    uint32_t ul_slots;
    uint32_t ul_symbols;
    uint32_t ul_prbs;
    uint32_t ul_prbs_err;
    uint32_t ul_cycles_max;
    uint32_t ul_cycles_average;
    uint32_t ul_cycles_min;
    uint32_t ul_ta4_max;
    uint32_t ul_ta4_average;
    uint32_t ul_ta4_min;
    uint32_t ul_cycles_cp_max;
    uint32_t ul_cycles_cp_min;

    uint32_t dl_total;
    uint32_t dl_total_cp;

    uint32_t dl_slots;
    uint32_t dl_symbols;
    uint32_t dl_sections;
    uint32_t dl_cycles_max;
    uint32_t dl_cycles_average;
    uint32_t dl_cycles_min;
    uint32_t dl_t1a_max;
    uint32_t dl_t1a_average;
    uint32_t dl_t1a_min;
    uint32_t dl_cycles_cp_max;
    uint32_t dl_cycles_cp_min;
}ecpri_cell_reserved_stats_t;

typedef struct ru_config_t{
    ru_base_config_t ru_config;
    comp_config_t comp_config;
    transmission_config_t transmission_config;
}ru_config_t;

typedef struct stEcpri_cfg{
    ecpri_base_config_t base_config;
    ecpri_ethernet_config_t ethernet_config;
    ecpri_ptp_config_t ptp_config;
    cell_info_t cell_info[MAX_CELL_NUM];
    ru_config_t ru_config[MAX_RU_NUM];
}__attribute__ ((__packed__,aligned(32))) stEcpri_cfg;
