/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _BHA_RXTX_H_
#define _BHA_RXTX_H_

#include <rte_pmd_bha.h>


#define BHA_MIN_DESC_NUM 8
#define BHA_MAX_DESC_NUM 32
#define BHA_DESC_ALIGN_NUM 8 //TODO:calculate

#define BHA_TX_MAX_BURST 32
#define BHA_RX_MAX_BURST 32


//ring index with wrap flag
union bha_ring_ptr {
    struct {
        uint32_t idx : 16;
        uint32_t : 15;
        uint32_t wrap : 1;
    };
    uint32_t ptr;
};

struct bha_rx_entry {
    struct rte_mbuf* mbuf; /**< mbuf associated with RX descriptor. */
};

struct bha_rx_desc {
    uint64_t phy_addr;
};

struct bha_rx_queue {
    struct rte_mempool* mb_pool; /**< mbuf pool to populate RX ring. */
    volatile struct bha_rx_desc* rx_ring; /**< RX ring virtual address. */
    uint64_t rx_ring_phys_addr; /**< RX ring DMA address. */
    struct bha_rx_entry* sw_ring; /**< address of RX software ring. */

    volatile RxResultDesc* rx_ring_rsp; /**< RX ring of response virtual address. */
    uint64_t rx_ring_rsp_phys_addr; /**< RX ring of response DMA address. */

    uint16_t nb_rx_desc; /**< number of RX descriptors. */
    uint16_t rx_nb_avail; /**< nb of pkts ready to ret to app */

    uint16_t queue_id; /**< RX queue index. */
    uint16_t port_id; /**< Device port identifier. */

    uint64_t vlan_flags;
    uint64_t offloads; /**< Rx offloads with DEV_RX_OFFLOAD_* */

    union bha_ring_ptr c_ptr; //hw consumer ptr(ro)
    union bha_ring_ptr p_ptr; //hw producer ptr(rw)

    uint32_t rx_ring_reg_base; /**< adapter rx ring register base addr */
    struct filter_conf_s filter_conf; /**< filter configure info >*/
};

struct bha_tx_entry {
    struct rte_mbuf* mbuf; /**< mbuf associated with TX desc, if any. */
};

struct bha_tx_queue {
    volatile TxReqDesc* tx_ring;
    uint64_t tx_ring_phys_addr; /**< TX ring DMA address. */

    struct bha_tx_entry* sw_ring; /**< address of SW ring for scalar PMD. */

    volatile TxResultDesc* tx_ring_rsp;
    uint64_t tx_ring_rsp_phys_addr; /**< TX ring of response DMA address. */

    uint16_t nb_tx_desc; /**< number of TX descriptors. */
    uint16_t nb_tx_free; /** Total number of TX descriptors ready to be allocated. */

    union bha_ring_ptr c_ptr; //hw consumer ptr(ro)
    union bha_ring_ptr p_ptr; //hw producer ptr(rw)

    uint16_t queue_id; /**< TX queue index. */
    uint16_t port_id; /**< Device port identifier. */

    uint64_t offloads; /**< Tx offload flags of DEV_TX_OFFLOAD_* */

    uint32_t tx_ring_reg_base; /**< adapter tx queue register base addr */
};


void bha_dev_free_queues(struct rte_eth_dev *dev);


#endif /* _BHA_RXTX_H_ */
