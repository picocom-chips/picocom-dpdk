/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <ethdev_driver.h>
#include <ethdev_vdev.h>
#include <rte_atomic.h>
#include <rte_branch_prediction.h>
#include <rte_bus_vdev.h>
#include <rte_byteorder.h>
#include <rte_common.h>
#include <rte_cycles.h>
#include <rte_debug.h>
#include <rte_errno.h>
#include <rte_ethdev.h>
#include <rte_ip.h>
#include <rte_kvargs.h>
#include <rte_malloc.h>
#include <rte_mbuf.h>
#include <rte_net.h>
#include <rte_string_fns.h>

#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/if_ether.h>
#include <net/if.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>

#include <bha_desc.h>
#include <bha_model.h>
#include <bha_regs.h>

#include <bha_ethdev.h>
#include <bha_rxtx.h>
#include <bha_log.h>



//calculate ring increase produce ptr with round bit[31]
static uint32_t
bha_ring_incr_ptr(uint16_t total_nb_desc, uint32_t ptr, uint16_t nb_fill)
{
    uint32_t ring_size = (uint32_t)total_nb_desc;
    uint32_t n = (uint32_t)nb_fill;

    if (RING_PTR_PTR(ptr) + n > ring_size - 1) {
        uint32_t round = SET_RING_PTR_ROUND((~RING_PTR_ROUND(ptr)));
        uint32_t ptr_l = RING_PTR_PTR(ptr) + n - ring_size;
        return round | ptr_l;
    } else {
        return ptr + n;
    }
}

static uint32_t
bha_ring_advance_p_n(uint32_t reg_base, uint16_t total_nb_desc, uint16_t n)
{
    volatile uint32_t cur_ptr = bha_reg_read(reg_base + RING_REGS_P_PRODUCER_OFFSET);
    volatile uint32_t update_ptr = bha_ring_incr_ptr(total_nb_desc, cur_ptr, n);
    bha_reg_write(reg_base + RING_REGS_P_PRODUCER_OFFSET, update_ptr);
    return update_ptr;
}

static inline uint64_t
rte_mbuf_data_bha_model_iova_default(const struct rte_mbuf *mb)
{
#ifdef RTE_NET_BHA_MODEL_EN
    return (uint64_t)(mb->buf_addr) + RTE_PKTMBUF_HEADROOM;
#else
    return rte_cpu_to_le_64(rte_mbuf_data_iova_default(mb));
#endif
}

static inline uint64_t
rte_mbuf_data_bha_model_iova(const struct rte_mbuf *mb)
{
#ifdef RTE_NET_BHA_MODEL_EN
    return (uint64_t)(mb->buf_addr) + mb->data_off;
#else
    return rte_mbuf_data_iova(mb);
#endif
}


static void __rte_cold
bha_free_scattered_mbuf(struct rte_mbuf* m)
{
    uint16_t i, nb_segs = m->nb_segs;
    struct rte_mbuf* next_seg;

    if (m == NULL)
        return;

    for (i = 0; i < nb_segs; i++) {
        next_seg = m->next;
        rte_pktmbuf_free_seg(m);
        m = next_seg;
    }
}

static void
bha_rx_queue_producer_update(struct bha_rx_queue *rxq, uint16_t nb_desc)
{
    volatile union bha_ring_ptr hw_p_ptr;

    if (nb_desc > 0) {
        if ((rxq->p_ptr.idx + nb_desc) >= rxq->nb_rx_desc) {
            rxq->p_ptr.idx = rxq->p_ptr.idx + nb_desc - rxq->nb_rx_desc;
            rxq->p_ptr.wrap = (~(rxq->p_ptr.wrap)) & 0x1;
        } else {
            rxq->p_ptr.idx = rxq->p_ptr.idx + nb_desc;
        }
        hw_p_ptr.ptr = bha_ring_advance_p_n(rxq->rx_ring_reg_base, rxq->nb_rx_desc, nb_desc);
        BHA_LOG(DEBUG, "ethdev bha[%d] recv update p_ptr, qid[%d], ret p_ptr 0x%x, calc p_ptr 0x%x, and c_ptr 0x%x", rxq->port_id, rxq->queue_id, hw_p_ptr.ptr, rxq->p_ptr.ptr, rxq->c_ptr.ptr);
        if (hw_p_ptr.ptr != rxq->p_ptr.ptr) //double check
            RTE_ASSERT(0);
    }
}

static inline int
bha_recv_desc_avail(struct bha_rx_queue *rxq, uint16_t *nb_rxd_avail)
{
    volatile union bha_ring_ptr hw_c_ptr;
    
    hw_c_ptr.ptr = bha_reg_read(rxq->rx_ring_reg_base + RING_REGS_P_CONSUMER_OFFSET);
    BHA_LOG(DEBUG, "bha[%d] qid[%d] get rx desc avail, hw c_ptr 0x%x, sw c_ptr 0x%x", rxq->port_id, rxq->queue_id, hw_c_ptr.ptr, rxq->c_ptr.ptr);
    if (hw_c_ptr.ptr == rxq->c_ptr.ptr) {  //no new pkts ready, ret 0
        *nb_rxd_avail = 0;
        return 0;
    }

    if (hw_c_ptr.wrap != rxq->c_ptr.wrap) {
        if (hw_c_ptr.idx > rxq->c_ptr.idx) {
            BHA_LOG(ERR, "bha[%d] qid[%d] c_ptr 0x%x error, wrap and idx fall after hw c_ptr 0x%x", rxq->port_id, rxq->queue_id, rxq->c_ptr.ptr, hw_c_ptr.ptr);
            RTE_ASSERT(0);
            return (-1);
        }
        *nb_rxd_avail = (rxq->nb_rx_desc - rxq->c_ptr.idx + hw_c_ptr.idx);
    } else {
        if (rxq->c_ptr.idx > hw_c_ptr.idx) {
            BHA_LOG(ERR, "bha[%d] qid[%d] c_ptr 0x%x error, no wrap and idx go ahead hw c_ptr 0x%x", rxq->port_id, rxq->queue_id, rxq->c_ptr.ptr, hw_c_ptr.ptr);
            RTE_ASSERT(0);
            return (-1);
        }
        *nb_rxd_avail = (hw_c_ptr.idx - rxq->c_ptr.idx);
    }

    return 0;
}

uint16_t
eth_bha_rx_pkt_burst(void* rx_queue, struct rte_mbuf** rx_pkts,
    uint16_t nb_pkts)
{
    struct bha_rx_queue *rxq;
    volatile struct bha_rx_desc *rx_ring;
    volatile RxResultDesc *rx_ring_rsp;
    struct bha_rx_entry *sw_ring;
    uint16_t rx_id;
    uint16_t nb_rx;
    uint16_t nb_rxd_consumed;
    uint16_t nb_rxd_avail;
    uint8_t wrap_flag;

    nb_rx = 0; //record rx pkts relay to app
    nb_rxd_consumed = 0; //record consumed rx desc number = new produced number
    rxq = rx_queue;
    rx_id = rxq->c_ptr.idx; //consumer ptr
    wrap_flag = rxq->c_ptr.wrap; //consumer ptr
    rx_ring = rxq->rx_ring; //only pkt data phy addr
    rx_ring_rsp = rxq->rx_ring_rsp; //resp wb info
    sw_ring = rxq->sw_ring;
    nb_rxd_avail = rxq->rx_nb_avail; //get curr rxq avail rx pkts

    BHA_LOG(DEBUG, "ethdev bha[%d] rxq[%d] rx burst, c_ptr 0x%x, nb desc avail %d", rxq->port_id, rxq->queue_id, rxq->c_ptr.ptr, nb_rxd_avail);


    while (nb_rx < nb_pkts) {
        volatile RxResultDesc rxd_rsp;
        volatile struct bha_rx_desc *rxd_p;
        struct bha_rx_entry *rxe;
        struct bha_rx_entry *next_rxe = NULL;
        struct rte_mbuf *first_seg = NULL;
        struct rte_mbuf *rxm;
        struct rte_mbuf *nmb;
        uint16_t nb_segs = 0;
        uint16_t next_id;
        uint16_t data_len = 0;
        uint16_t pkt_len = 0;
        uint64_t dma_addr;

        //if avail ready pkts number not enough and try to get again
        if (nb_rxd_avail < 1) {
            if (bha_recv_desc_avail(rxq, &nb_rxd_avail) != 0) {
                BHA_LOG(ERR, "bha[%d] qid[%d] recv pkts, get avail desc number fail, nb_avail %d", rxq->port_id, rxq->queue_id, nb_rxd_avail);
                break;
            } else {
                BHA_LOG(DEBUG, "bha[%d] qid[%d] recv pkts, get avail desc number %d", rxq->port_id, rxq->queue_id, nb_rxd_avail);
                if (nb_rxd_avail < 1)
                    break;
            }
        }


next_desc:
        rxd_p = &rx_ring[rx_id]; //rx desc for pkts data
        rxd_rsp = rx_ring_rsp[rx_id]; //rx desc of response for pkts info

        //parse avail pkt info
        if (rxd_rsp.frame.start == 1) {
            if (rxd_rsp.frame.end == 1) {
                nb_segs = 1;
                data_len = rxd_rsp.frame.size;
                pkt_len = data_len;
                BHA_LOG(DEBUG, "bha[%d] qid[%d] recv pkts, get single pkt, data len %d", rxq->port_id, rxq->queue_id, data_len);
            } else {
                nb_segs = rxd_rsp.frame.n_blocks + 1;
                pkt_len = rxd_rsp.frame.total_size;
                data_len = rxd_rsp.frame.size;
                BHA_LOG(DEBUG, "bha[%d] qid[%d] recv pkts, get scattered 1st seg, nb_segs %d, data len %d, pkt len %d", rxq->port_id, rxq->queue_id, nb_segs, data_len, pkt_len);
                if (unlikely(nb_segs > nb_rxd_avail)) {
                    BHA_LOG(ERR, "bha[%d] qid[%d] recv pkts, get scattered segs number %d > rxd avail number %d", rxq->port_id, rxq->queue_id, nb_segs, nb_rxd_avail);
                    break;
                }
            }
            //maybe need extral some info to parse from RxResultDesc, vlan/hash/offloads...
        } else {
            BHA_LOG(DEBUG, "bha[%d] qid[%d] recv pkts, get scattered segs %d", rxq->port_id, rxq->queue_id, rxd_rsp.frame.n_blocks);
            data_len = rxd_rsp.frame.size;
        }

        //alloc new mbuf, the rxq desc always full avail
        nmb = rte_mbuf_raw_alloc(rxq->mb_pool);
        if (nmb == NULL) {
            BHA_LOG(DEBUG, "RX mbuf alloc failed port_id=%u "
                    "queue_id=%u", (unsigned) rxq->port_id,
                    (unsigned) rxq->queue_id);
            rte_eth_devices[rxq->port_id].data->rx_mbuf_alloc_failed++;
            bha_free_scattered_mbuf(first_seg);
            break;
        }

        rxe = &sw_ring[rx_id];
        next_id = rx_id + 1;
        if (next_id == rxq->nb_rx_desc) { //wrap
            next_id = 0;
            wrap_flag = (~(wrap_flag)) & 0x1;
        }

        //prefetch next mbuf when curr one processing
        rte_prefetch0(sw_ring[next_id].mbuf);

        //if ((next_id & 0x3) == 0) {
            rte_prefetch0(&rx_ring_rsp[next_id]);
            rte_prefetch0(&sw_ring[next_id]);
        //}

        rxm = rxe->mbuf; //pick up mbuf for recved pkt
        rxe->mbuf = nmb; //insert new mbuf
        dma_addr = rte_mbuf_data_bha_model_iova_default(nmb);
        //insert new data phy addr into desc in rx ring. move producer ptr ahead
        rxd_p->phy_addr = dma_addr;

        //fill recv info into recved mbuf
        rxm->data_off = RTE_PKTMBUF_HEADROOM;
        rxm->data_len = data_len;

        if (rxd_rsp.frame.end == 0) { //not the last seg
            next_rxe = &sw_ring[next_id];
            rte_prefetch0(next_rxe);
        }

        //update first seg or single pkt info, parse from 1st pkt
        if (first_seg == NULL) {
            first_seg = rxm;
            first_seg->pkt_len = pkt_len;
            first_seg->nb_segs = nb_segs;
            first_seg->port = rxq->port_id;
        }

        //update index
		rx_id = next_id;
        nb_rxd_avail--;

        if (rxd_rsp.frame.end == 0) { //not the last seg
            rxm->next = next_rxe->mbuf; //link segs
            goto next_desc; //processing next seg
        } else
            rxm->next = NULL; //last seg or single pkt

        //segments pkts or single pkt processing done
        //prefetch data of first segment
		rte_prefetch0((char *)first_seg->buf_addr + first_seg->data_off);

        //put segs into rx_pkts
        rx_pkts[nb_rx++] = first_seg;

        //update c_ptr, if not enough valid desc, bha_recv_desc_avail() will use it to check new pkts ready
        rxq->c_ptr.idx = rx_id;
        rxq->c_ptr.wrap = wrap_flag;
        rxq->rx_nb_avail = nb_rxd_avail;
        nb_rxd_consumed += nb_segs;
    }

    rte_wmb();

    //update p_ptr and hw producer reg
    bha_rx_queue_producer_update(rxq, nb_rxd_consumed);

    return nb_rx;
}

static inline int
bha_xmit_desc_free(struct bha_tx_queue *txq)
{
    struct bha_tx_entry *sw_ring = txq->sw_ring;
	//volatile TxReqDesc *txr = txq->tx_ring;
    uint16_t nb_tx_desc = txq->nb_tx_desc;
    union bha_ring_ptr sw_c_ptr = txq->c_ptr;
    volatile union bha_ring_ptr hw_c_ptr;
    uint32_t calc_nb_desc_free;
    uint16_t tx_id;
    uint32_t i;

    //get hw consumer ptr
    hw_c_ptr.ptr = bha_reg_read(txq->tx_ring_reg_base + RING_REGS_P_CONSUMER_OFFSET);

    if (((hw_c_ptr.wrap == sw_c_ptr.wrap) && (sw_c_ptr.idx > hw_c_ptr.idx)) ||
        ((hw_c_ptr.wrap != sw_c_ptr.wrap) && (hw_c_ptr.idx > sw_c_ptr.idx)) ) {
        BHA_LOG(ERR, "ethdev bha[%d] xmit free desc, qid[%d], consumer ptr illegal, hw c_ptr 0x%x, sw c_ptr 0x%x, hw p_ptr 0x%x", txq->port_id, txq->queue_id, hw_c_ptr.ptr, sw_c_ptr.ptr, bha_reg_read(txq->tx_ring_reg_base + RING_REGS_P_PRODUCER_OFFSET));
        RTE_ASSERT(0);
    }

    if (hw_c_ptr.ptr == sw_c_ptr.ptr) {
        BHA_LOG(DEBUG, "ethdev bha[%d] xmit free desc, qid[%d], no any desc need to free, ptr 0x%x", txq->port_id, txq->queue_id, hw_c_ptr.ptr);
        return (-1);
    }

    //calculate number of desc to free
    tx_id = txq->c_ptr.idx;
    if (hw_c_ptr.wrap == sw_c_ptr.wrap) {
        calc_nb_desc_free = hw_c_ptr.idx - sw_c_ptr.idx;
        for (i = tx_id; i < hw_c_ptr.idx; i++)
            rte_pktmbuf_free_seg(sw_ring[i].mbuf);
    } else {
        calc_nb_desc_free = nb_tx_desc - sw_c_ptr.idx + hw_c_ptr.idx;
        for (i = tx_id; i < nb_tx_desc; i++)
            rte_pktmbuf_free_seg(sw_ring[i].mbuf);
        for (i = 0; i < hw_c_ptr.idx; i++)
            rte_pktmbuf_free_seg(sw_ring[i].mbuf);
    }

    //update txq ring info
    BHA_LOG(DEBUG, "ethdev bha[%d] xmit free desc, qid[%d], calc nb desc free %d, old c_ptr 0x%x, new c_ptr 0x%x", txq->port_id, txq->queue_id, calc_nb_desc_free, sw_c_ptr.ptr, hw_c_ptr.ptr);
    txq->nb_tx_free += calc_nb_desc_free;
    txq->c_ptr = hw_c_ptr;

    return 0;
}

uint16_t
eth_bha_tx_pkt_burst(void* tx_queue, struct rte_mbuf** tx_pkts,
    uint16_t nb_pkts)
{
    struct bha_tx_queue *txq;
    struct bha_tx_entry *sw_ring;
    struct bha_tx_entry *txe, *txe_n;
    volatile TxReqDesc *txr;
    volatile TxReqDesc *txd, *txd_1st;
    struct rte_mbuf     *tx_pkt;
    struct rte_mbuf     *m_seg;
    uint64_t buf_dma_addr;
    uint32_t pkt_len;
    uint16_t slen;
    uint16_t nb_tx;
    uint16_t tx_id;
    uint16_t tx_id_next;
    uint16_t nb_segs;
    uint16_t nb_txd_used;
    uint8_t wrap_flag;
    union bha_ring_ptr producer_ptr;


    txq = tx_queue;
    sw_ring = txq->sw_ring;
    txr = txq->tx_ring;
    tx_id = txq->p_ptr.idx; //producer idx
    wrap_flag = txq->p_ptr.wrap; //producer wrap
    txe = &sw_ring[tx_id];
    nb_txd_used = 0;
    BHA_LOG(DEBUG, "ethdev bha[%d] tx burst, qid %d, nb_pkts %d, curr tx index %d, wrap %d", txq->port_id, txq->queue_id, nb_pkts, tx_id, wrap_flag);

    //free desc
    bha_xmit_desc_free(txq);

    rte_prefetch0(&txe->mbuf->pool);
    for (nb_tx = 0; nb_tx < nb_pkts; nb_tx++) {
        tx_pkt = *tx_pkts++;
		pkt_len = tx_pkt->pkt_len;

        //no segments: 1; segments: total number of segs(in the first pkt mbuf)
        nb_segs = tx_pkt->nb_segs;
        BHA_LOG(DEBUG, "ethdev bha tx burst, qid %d, nb segs %d, pkt len %d", txq->queue_id, nb_segs, pkt_len);
        if (nb_segs > txq->nb_tx_desc) {
            BHA_LOG(ERR, "ethdev bha tx burst, qid %d. desc number overflow, max %d, segs %d. return", txq->queue_id, txq->nb_tx_desc, nb_segs);
            //if nb_tx pkts had been ready in tx ring, push to hw and then exit
            if (nb_tx == 0)
                return 0;
            goto end_of_tx;
        }

        //check valid desc number enough, if not then free more desc until enough
        if (nb_segs > txq->nb_tx_free) {
            if (bha_xmit_desc_free(txq) != 0) {
                BHA_LOG(ERR, "ethdev bha tx burst free more desc fail, qid %d. need %d, curr free desc nb %d", txq->queue_id, nb_segs, txq->nb_tx_free);
                if (nb_tx == 0)
                    return 0;
                goto end_of_tx;
            }
        }

        //process current tx pkts. single pkt or segments pkts
        m_seg = tx_pkt;
        txd_1st = &txr[tx_id];
        do {
            txd = &txr[tx_id];
            if (tx_id >= (txq->nb_tx_desc - 1)) {
                tx_id_next = tx_id + 1 - txq->nb_tx_desc;
                wrap_flag = (~(wrap_flag)) & 0x1; //wrap
            } else
                tx_id_next = tx_id + 1;
            txe_n = &sw_ring[tx_id_next];
            rte_prefetch0(&txe_n->mbuf->pool);

            //double confirm to free mbuf
            if (txe->mbuf != NULL)
                rte_pktmbuf_free_seg(txe->mbuf);
            txe->mbuf = m_seg;

            //fill tx desc
            slen = m_seg->data_len;
            buf_dma_addr = rte_mbuf_data_bha_model_iova(m_seg);
            txd->frame.addr_lo = (uint32_t)((uint64_t)buf_dma_addr & 0xffffffff);
            txd->frame.addr_hi = (uint32_t)((((uint64_t)buf_dma_addr)>>32) & 0xffffffff);
            txd->frame.size = slen;
            txd->frame.start = 0; //specific proc for 1st pkt, if no segment it is 1
            txd->frame.end = 0; //specific proc for last pkt, if no segment it is 1

            //update for next round proc
            tx_id = tx_id_next;
            txe = txe_n;
            m_seg = m_seg->next;
            nb_txd_used++;
        } while (m_seg != NULL);

        //update last tx desc
        txd->frame.end = 1;
        //update 1st tx desc
        if (nb_segs > 1) { //segments pkt
            txd_1st->frame.total_size = pkt_len;
            txd_1st->frame.n_blocks = nb_segs - 1;
        } else { //single pkt
            txd_1st->frame.total_size = slen;
            txd_1st->frame.n_blocks = 0;
        }
        txd_1st->ctrl.resp_en = 1; //true for response info feed back
        txd_1st->frame.start = 1;

        //update txq info
        txq->nb_tx_free -= nb_segs;
    }

end_of_tx:
    rte_wmb();

    BHA_LOG(DEBUG, "ethdev bha[%d] tx burst end, qid[%d], nb_tx %d, tx_id %d", txq->port_id, txq->queue_id, nb_tx, tx_id);
    //update producer ptr reg
    producer_ptr.ptr = bha_ring_advance_p_n(txq->tx_ring_reg_base, txq->nb_tx_desc, nb_txd_used);
    BHA_LOG(DEBUG, "ethdev bha burst xmit, txq[%d], after update producer ptr 0x%x, consumer ptr 0x%x", txq->queue_id, bha_reg_read(txq->tx_ring_reg_base + RING_REGS_P_PRODUCER_OFFSET), bha_reg_read(txq->tx_ring_reg_base + RING_REGS_P_CONSUMER_OFFSET));

    //update txq ring producer ptr info
    txq->p_ptr.idx = tx_id;
    txq->p_ptr.wrap = wrap_flag & 0x1;
    BHA_LOG(DEBUG, "ethdev bha[%d] burst xmit, txq[%d], after update producer ptr, read back 0x%x, sw update 0x%x", txq->port_id, txq->queue_id, producer_ptr.ptr, txq->p_ptr.ptr);
    if (producer_ptr.ptr != txq->p_ptr.ptr) {
        BHA_LOG(ERR, "ethdev bha[%d] burst xmit, txq[%d], update producer ptr != sw calc ptr, read back 0x%x, sw update 0x%x", txq->port_id, txq->queue_id, producer_ptr.ptr, txq->p_ptr.ptr);
        RTE_ASSERT(0);
    }

    return nb_tx;
}

int __rte_cold
bha_dev_tx_queue_start(struct rte_eth_dev* dev, uint16_t tx_queue_id)
{
    struct bha_tx_queue* txq;

    txq = dev->data->tx_queues[tx_queue_id];
 
    //adpater enable tx queue
    //adapter config tx ring phys addr
    bha_reg_write(txq->tx_ring_reg_base + RING_REGS_REQ_BASE_L_OFFSET, (uint32_t)((uint64_t)(txq->tx_ring_phys_addr)));
    bha_reg_write(txq->tx_ring_reg_base + RING_REGS_REQ_BASE_H_OFFSET, (uint32_t)((uint64_t)(txq->tx_ring_phys_addr) >> 32));
    //adapter config tx ring of response phys addr
    bha_reg_write(txq->tx_ring_reg_base + RING_REGS_RESP_BASE_L_OFFSET, (uint32_t)((uint64_t)(txq->tx_ring_rsp_phys_addr)));
    bha_reg_write(txq->tx_ring_reg_base + RING_REGS_RESP_BASE_H_OFFSET, (uint32_t)((uint64_t)(txq->tx_ring_rsp_phys_addr) >> 32));

    //adapter config tx ring total desc number
    bha_reg_write(txq->tx_ring_reg_base + RING_REGS_SIZE_OFFSET, (uint32_t)(txq->nb_tx_desc));

    //adapter tx queue control enable
    bha_reg_write(txq->tx_ring_reg_base + RING_REGS_CTRL_OFFSET, SET_RING_CTRL_ENABLE(1));

    BHA_LOG(DEBUG, "txq[%d] before setup tx ring, producer ptr 0x%x, consumer ptr 0x%x", tx_queue_id, bha_reg_read(txq->tx_ring_reg_base + RING_REGS_P_PRODUCER_OFFSET), bha_reg_read(txq->tx_ring_reg_base + RING_REGS_P_CONSUMER_OFFSET));
    ////tx queue init stage all descs are valide, and bit31 is round bit(init val 0), bit[30:0] for desc number
    //bha_ring_advance_p_n(txq->tx_ring_reg_base, txq->nb_tx_desc, txq->nb_tx_desc);
    //BHA_LOG(DEBUG, "txq[%d] after setup tx ring, producer ptr 0x%x, consumer ptr 0x%x", tx_queue_id, bha_reg_read(txq->tx_ring_reg_base + RING_REGS_P_PRODUCER_OFFSET), bha_reg_read(txq->tx_ring_reg_base + RING_REGS_P_CONSUMER_OFFSET));

    //txq status update
    dev->data->tx_queue_state[tx_queue_id] = RTE_ETH_QUEUE_STATE_STARTED;

    return 0;
}

static int __rte_cold
bha_alloc_rx_queue_mbufs(struct bha_rx_queue* rxq)
{
    struct bha_rx_entry* rxe = rxq->sw_ring;
    uint64_t dma_addr;
    unsigned int i;

    /* Initialize software ring entries */
    for (i = 0; i < rxq->nb_rx_desc; i++) {
        volatile struct bha_rx_desc* rxd;
        struct rte_mbuf* mbuf = rte_mbuf_raw_alloc(rxq->mb_pool);

        if (mbuf == NULL) {
            BHA_LOG(ERR, "RX mbuf alloc failed queue_id=%u",
                (unsigned)rxq->queue_id);
            return -ENOMEM;
        }

        mbuf->data_off = RTE_PKTMBUF_HEADROOM;
        mbuf->port = rxq->port_id;

        dma_addr = rte_mbuf_data_bha_model_iova_default(mbuf);
        rxd = &rxq->rx_ring[i];
        rxd->phy_addr = dma_addr;
        rxe[i].mbuf = mbuf;
    }

    return 0;
}

int __rte_cold
bha_dev_rx_queue_start(struct rte_eth_dev* dev, uint16_t rx_queue_id)
{
    struct bha_rx_queue* rxq;
    uint32_t data_len = 0;
    volatile uint32_t hw_p_ptr = 0;

    rxq = dev->data->rx_queues[rx_queue_id];
    /* Allocate buffers for descriptor rings */
    if (bha_alloc_rx_queue_mbufs(rxq) != 0) {
        BHA_LOG(ERR, "Could not alloc mbuf for queue:%d",
            rx_queue_id);
        return -1;
    }

    //reserved headroom(RTE_PKTMBUF_HEADROOM), not reserved tailroom
    data_len = rte_pktmbuf_data_room_size(rxq->mb_pool) - RTE_PKTMBUF_HEADROOM;
    BHA_LOG(DEBUG, "rxq[%d] setup data len:%d", rx_queue_id, data_len);

    //adpater enable rx queue
    //adpater config recv buf len from mbuf
    bha_reg_write(rxq->rx_ring_reg_base + RING_REGS_MEM_SIZE_OFFSET, data_len);
    //adapter config rx ring phys addr
    bha_reg_write(rxq->rx_ring_reg_base + RING_REGS_REQ_BASE_L_OFFSET, (uint32_t)((uint64_t)(rxq->rx_ring_phys_addr)));
    bha_reg_write(rxq->rx_ring_reg_base + RING_REGS_REQ_BASE_H_OFFSET, (uint32_t)((uint64_t)(rxq->rx_ring_phys_addr) >> 32));
    //adapter config rx ring of response phys addr
    bha_reg_write(rxq->rx_ring_reg_base + RING_REGS_RESP_BASE_L_OFFSET, (uint32_t)((uint64_t)(rxq->rx_ring_rsp_phys_addr)));
    bha_reg_write(rxq->rx_ring_reg_base + RING_REGS_RESP_BASE_H_OFFSET, (uint32_t)((uint64_t)(rxq->rx_ring_rsp_phys_addr) >> 32));
    //adapter config rx ring total desc number
    bha_reg_write(rxq->rx_ring_reg_base + RING_REGS_SIZE_OFFSET, (uint32_t)(rxq->nb_rx_desc));

    //adapter rx queue control enable
    bha_reg_write(rxq->rx_ring_reg_base + RING_REGS_CTRL_OFFSET, SET_RING_CTRL_ENABLE(1));

    BHA_LOG(DEBUG, "rxq[%d] before setup rx ring, producer ptr 0x%x, consumer ptr 0x%x", rx_queue_id, bha_reg_read(rxq->rx_ring_reg_base + RING_REGS_P_PRODUCER_OFFSET), bha_reg_read(rxq->rx_ring_reg_base + RING_REGS_P_CONSUMER_OFFSET));
    //rx queue init stage all descs are valide, and bit31 is round bit(init val 0), bit[30:0] for desc idx
    hw_p_ptr = bha_ring_advance_p_n(rxq->rx_ring_reg_base, rxq->nb_rx_desc, rxq->nb_rx_desc);
    BHA_LOG(DEBUG, "rxq[%d] after setup rx ring, producer ptr 0x%x, consumer ptr 0x%x, read ret p_ptr 0x%x", rx_queue_id, bha_reg_read(rxq->rx_ring_reg_base + RING_REGS_P_PRODUCER_OFFSET), bha_reg_read(rxq->rx_ring_reg_base + RING_REGS_P_CONSUMER_OFFSET), hw_p_ptr);
    rxq->p_ptr.ptr = hw_p_ptr; //update producer ptr

    //adapter rx queue filter conf
    bha_reg_write(ET_FILTER(rxq->filter_conf.et_conf.filter_id),
                    SET_ETHER_TYPE_FILTER_ETYPE((uint32_t)(rxq->filter_conf.et_conf.ether_type)) |
                    SET_ETHER_TYPE_FILTER_QUEUE_ID(rxq->queue_id) |
                    SET_ETHER_TYPE_FILTER_CONGESTION_ACTION((uint32_t)(rxq->filter_conf.et_conf.congestion_action)) |
                    SET_ETHER_TYPE_FILTER_EN(1)); 
    BHA_LOG(DEBUG, "adpater et filter id %d, ether type 0x%x, qid %d, ca %d", rxq->filter_conf.et_conf.filter_id, rxq->filter_conf.et_conf.ether_type, rxq->queue_id, rxq->filter_conf.et_conf.congestion_action);

    //rxq status update
    dev->data->rx_queue_state[rx_queue_id] = RTE_ETH_QUEUE_STATE_STARTED;

    return 0;
}


static void __rte_cold
bha_rx_queue_release_mbufs(struct bha_rx_queue* rxq)
{
    unsigned int i;

    if (rxq->sw_ring != NULL) {
        for (i = 0; i < rxq->nb_rx_desc; i++) {
            if (rxq->sw_ring[i].mbuf != NULL) {
                rte_pktmbuf_free_seg(rxq->sw_ring[i].mbuf);
                rxq->sw_ring[i].mbuf = NULL;
            }
        }
    }
}

static void __rte_cold
bha_rx_queue_release(struct bha_rx_queue* rxq)
{
    if (rxq != NULL) {
        bha_rx_queue_release_mbufs(rxq);
        rte_free(rxq->sw_ring);
        rte_free(rxq);
    }
}

static void __rte_cold
bha_reset_rx_queue(struct bha_rx_queue* rxq)
{
    static const struct bha_rx_desc zeroed_desc_req = { 0 };
    static const RxResultDesc zeroed_desc_rsp = { 0 };
    unsigned int i;

    for (i = 0; i < rxq->nb_rx_desc; i++) {
        rxq->rx_ring[i] = zeroed_desc_req;
        rxq->rx_ring_rsp[i] = zeroed_desc_rsp;
        rxq->sw_ring[i].mbuf = NULL;
    }

    rxq->c_ptr.ptr = 0; //init consumer ptr
    rxq->p_ptr.ptr = 0; //init producer ptr
    rxq->rx_nb_avail = 0;
}

int
eth_bha_rx_queue_setup(struct rte_eth_dev* dev,
    uint16_t queue_idx,
    uint16_t nb_desc,
    unsigned int socket_id,
    const struct rte_eth_rxconf* rx_conf,
    struct rte_mempool* mp)
{
    //struct bha_adapter *adapter = dev->data->dev_private;
    struct bha_rx_queue* rxq;
    const struct rte_memzone* rmz;
    const struct rte_memzone* rmz_rsp;
    struct filter_conf_s* filter_conf = (struct filter_conf_s *)rx_conf->reserved_ptrs[0];

    BHA_LOG(DEBUG, "ethdev bha[%d] rx queue[%d] setup, number desc %d, socket id %d", dev->data->port_id, queue_idx, nb_desc, socket_id);

    /* Free memory prior to re-allocation if needed... */
    if (dev->data->rx_queues[queue_idx] != NULL) {
        bha_rx_queue_release(dev->data->rx_queues[queue_idx]);
        dev->data->rx_queues[queue_idx] = NULL;
    }

    rxq = rte_zmalloc_socket("ethdev bha RX queue", sizeof(struct bha_rx_queue),
        RTE_CACHE_LINE_SIZE, socket_id);
    if (rxq == NULL)
        return -ENOMEM;

    rxq->mb_pool = mp;
    rxq->nb_rx_desc = nb_desc;
    rxq->queue_id = queue_idx;
    rxq->port_id = dev->data->port_id;

    //rx ring setup
    rmz = rte_eth_dma_zone_reserve(dev, "rx_ring", queue_idx,
        sizeof(struct bha_rx_desc) * nb_desc,
        RTE_CACHE_LINE_SIZE, socket_id);
    if (rmz == NULL) {
        bha_rx_queue_release(rxq);
        return -ENOMEM;
    }

    //zero init rx ring desc
    memset(rmz->addr, 0, sizeof(struct bha_rx_desc) * nb_desc);

#ifdef RTE_NET_BHA_MODEL_EN
    rxq->rx_ring_phys_addr = (uint64_t)rmz->addr;
#else
    rxq->rx_ring_phys_addr = rmz->iova;
#endif
    rxq->rx_ring = (struct bha_rx_desc*)rmz->addr;


    //rx ring of response setup
    rmz_rsp = rte_eth_dma_zone_reserve(dev, "rx_ring_rsp", queue_idx,
        sizeof(RxResultDesc) * nb_desc,
        RTE_CACHE_LINE_SIZE, socket_id);
    if (rmz_rsp == NULL) {
        bha_rx_queue_release(rxq);
        return -ENOMEM;
    }

    //zero init rx ring rsp desc
    memset(rmz_rsp->addr, 0, sizeof(RxResultDesc) * nb_desc);

#ifdef RTE_NET_BHA_MODEL_EN
    rxq->rx_ring_rsp_phys_addr = (uint64_t)rmz_rsp->addr;
#else
    rxq->rx_ring_rsp_phys_addr = rmz_rsp->iova;
#endif
    rxq->rx_ring_rsp = (RxResultDesc*)rmz_rsp->addr;


    //mbufs ring setup
    rxq->sw_ring = rte_zmalloc_socket("rxq->sw_ring",
        sizeof(struct bha_rx_entry) * nb_desc,
        RTE_CACHE_LINE_SIZE, socket_id);
    if (!rxq->sw_ring) {
        bha_rx_queue_release(rxq);
        return -ENOMEM;
    }

    //update rxq ring hw reg info
    rxq->rx_ring_reg_base = RX_RING(REQ_BASE_L, queue_idx);
    //update rxq filter config
    rxq->filter_conf = *filter_conf;
    BHA_LOG(DEBUG, "et filter id %d, ether type 0x%x, ca %d", filter_conf->et_conf.filter_id, filter_conf->et_conf.ether_type, filter_conf->et_conf.congestion_action);

    dev->data->rx_queues[queue_idx] = rxq;

    bha_reset_rx_queue(rxq);

    return 0;
}

static void __rte_cold
bha_tx_queue_release_mbufs(struct bha_tx_queue* txq)
{
    unsigned int i;

    if (txq->sw_ring != NULL) {
        for (i = 0; i < txq->nb_tx_desc; i++) {
            if (txq->sw_ring[i].mbuf != NULL) {
                rte_pktmbuf_free_seg(txq->sw_ring[i].mbuf);
                txq->sw_ring[i].mbuf = NULL;
            }
        }
    }
}

static void __rte_cold
bha_tx_free_swring(struct bha_tx_queue* txq)
{
    if (txq != NULL && txq->sw_ring != NULL)
        rte_free(txq->sw_ring);
}

static void __rte_cold
bha_tx_queue_release(struct bha_tx_queue* txq)
{
    if (txq != NULL) {
        bha_tx_queue_release_mbufs(txq);
        bha_tx_free_swring(txq);
        rte_free(txq);
    }
}

static void __rte_cold
bha_reset_tx_queue(struct bha_tx_queue* txq)
{
    static const TxReqDesc zeroed_desc_req = { 0 };
    static const TxResultDesc zeroed_desc_rsp = { 0 };
    struct bha_tx_entry* txe = txq->sw_ring;
    uint16_t i;

    /* Zero out HW ring memory */
    for (i = 0; i < txq->nb_tx_desc; i++) {
        txq->tx_ring[i] = zeroed_desc_req;
        txq->tx_ring_rsp[i] = zeroed_desc_rsp;
        txe[i].mbuf = NULL;
    }

    txq->p_ptr.ptr = 0;
    txq->c_ptr.ptr = 0;
    txq->nb_tx_free = txq->nb_tx_desc;
}

int
eth_bha_tx_queue_setup(struct rte_eth_dev* dev,
    uint16_t queue_idx,
    uint16_t nb_desc,
    unsigned int socket_id,
    const struct rte_eth_txconf* tx_conf __rte_unused)
{
    //struct bha_adapter *adapter = dev->data->dev_private;
    struct bha_tx_queue* txq;
    const struct rte_memzone* rmz;
    const struct rte_memzone* rmz_rsp;

    BHA_LOG(DEBUG, "ethdev bha[%d] tx queue[%d] setup, desc number %d, socket id %d", dev->data->port_id, queue_idx, nb_desc, socket_id);

    /* Free memory prior to re-allocation if needed... */
    if (dev->data->tx_queues[queue_idx] != NULL) {
        bha_tx_queue_release(dev->data->tx_queues[queue_idx]);
        dev->data->tx_queues[queue_idx] = NULL;
    }

    /* First allocate the tx queue data structure */
    txq = rte_zmalloc_socket("ethdev bha TX queue", sizeof(struct bha_tx_queue),
        RTE_CACHE_LINE_SIZE, socket_id);
    if (txq == NULL)
        return -ENOMEM;


    //init tx ring
    rmz = rte_eth_dma_zone_reserve(dev, "tx_ring", queue_idx,
        sizeof(TxReqDesc) * nb_desc,
        RTE_CACHE_LINE_SIZE, socket_id);
    if (rmz == NULL) {
        bha_tx_queue_release(txq);
        BHA_LOG(ERR, "ethdev bha[%d] txq[%d] ring alloc memzone failed and exit", dev->data->port_id, queue_idx);
        return -ENOMEM;
    }
    //update tx ring
#ifdef RTE_NET_BHA_MODEL_EN
    txq->tx_ring_phys_addr = (uint64_t)rmz->addr;
#else
    txq->tx_ring_phys_addr = rmz->iova;
#endif
    txq->tx_ring = (TxReqDesc*)rmz->addr;


    //init tx ring of response
    rmz_rsp = rte_eth_dma_zone_reserve(dev, "tx_ring_rsp", queue_idx,
        sizeof(TxResultDesc) * nb_desc,
        RTE_CACHE_LINE_SIZE, socket_id);
    if (rmz_rsp == NULL) {
        bha_tx_queue_release(txq);
        BHA_LOG(ERR, "ethdev bha[%d] txq[%d] ring of response alloc memzone failed and exit", dev->data->port_id, queue_idx);
        return -ENOMEM;
    }
    //update tx ring of response
#ifdef RTE_NET_BHA_MODEL_EN
    txq->tx_ring_rsp_phys_addr = (uint64_t)rmz_rsp->addr;
#else
    txq->tx_ring_rsp_phys_addr = rmz_rsp->iova;
#endif
    txq->tx_ring_rsp = (TxResultDesc*)rmz_rsp->addr;

    txq->nb_tx_desc = nb_desc;
    txq->queue_id = queue_idx;
    txq->port_id = dev->data->port_id;

    /* Allocate software ring */
    txq->sw_ring = rte_zmalloc_socket("txq->sw_ring",
        sizeof(struct bha_tx_entry) * nb_desc,
        RTE_CACHE_LINE_SIZE, socket_id);
    if (txq->sw_ring == NULL) {
        bha_tx_queue_release(txq);
        BHA_LOG(ERR, "ethdev bha[%d] txq[%d] sw ring alloc mem failed and exit", dev->data->port_id, queue_idx);
        return -ENOMEM;
    }

    //init txq to default
    bha_reset_tx_queue(txq);

    //update adapter tx queue register base addr
    txq->tx_ring_reg_base = TX_RING(REQ_BASE_L, queue_idx);

    dev->data->tx_queues[queue_idx] = txq;

    return 0;
}

void
eth_bha_rx_queue_release(struct rte_eth_dev* dev, uint16_t qid)
{
    BHA_LOG(DEBUG, "ethdev bha[%d] rx queue release, qid %d", dev->data->port_id, qid);

	bha_rx_queue_release(dev->data->rx_queues[qid]);
}

void
eth_bha_tx_queue_release(struct rte_eth_dev* dev, uint16_t qid)
{
    BHA_LOG(DEBUG, "ethdev bha[%d] tx queue release, qid %d", dev->data->port_id, qid);

	bha_tx_queue_release(dev->data->tx_queues[qid]);
}

void
bha_dev_free_queues(struct rte_eth_dev *dev)
{
	unsigned int i;

	for (i = 0; i < dev->data->nb_rx_queues; i++) {
		bha_rx_queue_release(dev->data->rx_queues[i]);
		dev->data->rx_queues[i] = NULL;
		rte_eth_dma_zone_free(dev, "rx_ring", i);
		rte_eth_dma_zone_free(dev, "rx_ring_rsp", i);
	}
	dev->data->nb_rx_queues = 0;

	for (i = 0; i < dev->data->nb_tx_queues; i++) {
		bha_tx_queue_release(dev->data->tx_queues[i]);
		dev->data->tx_queues[i] = NULL;
		rte_eth_dma_zone_free(dev, "tx_ring", i);
		rte_eth_dma_zone_free(dev, "tx_ring_rsp", i);
	}
	dev->data->nb_tx_queues = 0;
}

