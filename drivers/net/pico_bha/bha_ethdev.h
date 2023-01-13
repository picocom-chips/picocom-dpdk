/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _BHA_ETHDEV_H_
#define _BHA_ETHDEV_H_

#include <stdint.h>
#include <rte_pmd_bha.h>

struct bha_adapter {
    struct rte_eth_dev* dev;
    struct rte_ether_addr eth_addr;
    uint16_t port_id;
    uint16_t max_rxq_nb;

    //hw filter
    int default_qid; //0~4, none is -1
    //hw filter - ethernet type
    int filter_et_qid[BHA_ETH_TYPE_FILTER_ID_MAX]; //0~4, none is -1
    uint16_t filter_et[BHA_ETH_TYPE_FILTER_ID_MAX]; //none is 0

#ifdef RTE_NET_BHA_MODEL_EN
    //bha model tap mode
    char tap_ifname[RTE_ETH_NAME_MAX_LEN];
    bool tap_mode_en;
#endif
};


uint16_t eth_bha_rx_pkt_burst(void* rx_queue, struct rte_mbuf** rx_pkts, uint16_t nb_pkts);
uint16_t eth_bha_tx_pkt_burst(void* tx_queue, struct rte_mbuf** tx_pkts, uint16_t nb_pkts);

int bha_dev_tx_queue_start(struct rte_eth_dev* dev, uint16_t tx_queue_id);
int bha_dev_rx_queue_start(struct rte_eth_dev* dev, uint16_t rx_queue_id);

int eth_bha_rx_queue_setup(struct rte_eth_dev* dev,
    uint16_t queue_idx,
    uint16_t nb_desc,
    unsigned int socket_id,
    const struct rte_eth_rxconf* rx_conf,
    struct rte_mempool* mp);

int eth_bha_tx_queue_setup(struct rte_eth_dev* dev,
    uint16_t queue_idx,
    uint16_t nb_desc,
    unsigned int socket_id,
    const struct rte_eth_txconf* tx_conf);


void eth_bha_rx_queue_release(struct rte_eth_dev* dev, uint16_t qid);
void eth_bha_tx_queue_release(struct rte_eth_dev* dev, uint16_t qid);

#endif /* _BHA_ETHDEV_H_ */
