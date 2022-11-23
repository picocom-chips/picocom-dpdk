/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _RTE_PMD_BHA_H_
#define _RTE_PMD_BHA_H_


#define BHA_ETH_TYPE_FILTER_ID_MAX      4  //ether type filter id max number, first id=0, last 0xff for default queue
#define BHA_ETH_TYPE_FILTER_ID_DFLT     0xFF //default queue filter id


//congestion action type enum
enum congestion_act_e {
    CA_OPS_BLOCKING = 0,
    CA_OPS_DROP,
    CA_OPS_DEFAULT,
};

struct filter_ether_type_conf_s {
    uint32_t filter_id : 8; //ether type filter id
    uint32_t ether_type : 16;
    uint32_t : 6;
    uint32_t congestion_action : 2;
};

struct filter_conf_s {
    struct filter_ether_type_conf_s et_conf; //uint32_t
};

#endif /* _RTE_PMD_BHA_H_ */
