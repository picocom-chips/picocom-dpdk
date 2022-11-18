/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _BHA_ETHDEV_H_
#define _BHA_ETHDEV_H_

#include <stdint.h>

struct bha_adapter {
    struct rte_eth_dev* dev;
    struct rte_ether_addr eth_addr;
    uint16_t port_id;
};


uint16_t eth_bha_rx_pkt_burst(void* rx_queue, struct rte_mbuf** rx_pkts, uint16_t nb_pkts);
uint16_t eth_bha_tx_pkt_burst(void* tx_queue, struct rte_mbuf** tx_pkts, uint16_t nb_pkts);

int bha_dev_tx_queue_start(struct rte_eth_dev* dev, uint16_t tx_queue_id);
int bha_dev_rx_queue_start(struct rte_eth_dev* dev, uint16_t rx_queue_id);

int eth_bha_rx_queue_setup(struct rte_eth_dev* dev,
    uint16_t queue_idx,
    uint16_t nb_desc,
    unsigned int socket_id,
    const struct rte_eth_rxconf* rx_conf __rte_unused,
    struct rte_mempool* mp);

int eth_bha_tx_queue_setup(struct rte_eth_dev* dev,
    uint16_t queue_idx,
    uint16_t nb_desc,
    unsigned int socket_id,
    const struct rte_eth_txconf* tx_conf __rte_unused);


void eth_bha_rx_queue_release(struct rte_eth_dev* dev, uint16_t qid);
void eth_bha_tx_queue_release(struct rte_eth_dev* dev, uint16_t qid);

#endif /* _BHA_ETHDEV_H_ */
