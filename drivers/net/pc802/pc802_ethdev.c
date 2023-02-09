/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <sys/queue.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <rte_common.h>
#include <rte_interrupts.h>
#include <rte_byteorder.h>
#include <rte_debug.h>
#include <rte_pci.h>
#include <rte_telemetry.h>
#include <rte_bus_pci.h>
#include <rte_version.h>
#include <rte_ether.h>
#if RTE_VERSION >= RTE_VERSION_NUM(21, 5, 0, 0)
#include <ethdev_driver.h>
#include <ethdev_pci.h>
#else
#include <rte_ethdev_driver.h>
#include <rte_ethdev_pci.h>
#endif
#include <rte_memory.h>
#include <rte_eal.h>
#include <rte_malloc.h>
#include <rte_dev.h>

#include "pc802_logs.h"
#include "rte_pmd_pc802.h"
#include "pc802_ethdev.h"
#include "pc802_mailbox.h"

#define PCI_VENDOR_PICOCOM          0x1EC4
#define PCI_DEVICE_PICOCOM_PC802_OLD 0x1001
#define PCI_DEVICE_PICOCOM_PC802    0x0802
#define FIFO_PC802_VEC_ACCESS   "/tmp/pc802_vec_access"

#define PC802_TRAFFIC_MAILBOX   PC802_TRAFFIC_NUM

static inline void pc802_write_reg(volatile uint32_t *addr, uint32_t value)
{
    __asm__ volatile ("" : : : "memory");
    *addr = value;
    return;
}

#define PC802_WRITE_REG(reg, value) \
    pc802_write_reg((volatile uint32_t *)&(reg), (value))

static inline uint32_t pc802_read_reg(volatile uint32_t *addr)
{
    uint32_t val;
    val = *addr;
    __asm__ volatile ("" : : : "memory");
    return val;
}

#define PC802_READ_REG(reg) \
    pc802_read_reg((volatile uint32_t *)&(reg))

static uint16_t num_pc802s = 0;
static struct pc802_adapter *pc802_devices[PC802_INDEX_MAX] = {NULL};

static const struct rte_pci_id pci_id_pc802_map[] = {
    { RTE_PCI_DEVICE(PCI_VENDOR_PICOCOM, PCI_DEVICE_PICOCOM_PC802) },
    { RTE_PCI_DEVICE(PCI_VENDOR_PICOCOM, PCI_DEVICE_PICOCOM_PC802_OLD) },
    { .vendor_id = 0, /* sentinel */ },
};

typedef struct PC802_Mem_Pool_t {
    PC802_Mem_Block_t *first;
    uint32_t block_size;
    uint32_t block_num;
} PC802_Mem_Pool_t;

struct pmd_queue_stats {
    uint64_t pkts;
    uint64_t bytes;
    uint64_t err_pkts;
};

/**
 * Structure associated with each descriptor of the RX ring of a RX queue.
 */
struct pc802_rx_entry {
    union {
        struct rte_mbuf *mbuf; /**< mbuf associated with RX descriptor. */
        PC802_Mem_Block_t *mblk;
    };
};

/**
 * Structure associated with each RX queue.
 */
struct pc802_rx_queue {
    struct rte_mempool  *mb_pool;   /**< mbuf pool to populate RX ring. */
    volatile PC802_Descriptor_t *rx_ring; /**< RX ring virtual address. */
    struct pc802_rx_entry *sw_ring;   /**< address of RX software ring. */
    //uint64_t            rx_ring_phys_addr; /**< RX ring DMA address. */
    volatile uint32_t   *rrccnt_reg_addr; /**< RDT register address. */
    volatile uint32_t   *repcnt_mirror_addr;
    //volatile uint32_t   *repcnt_reg_addr; /**< RDH register address. */
    //struct rte_mbuf *pkt_first_seg; /**< First segment of current packet. */
    //struct rte_mbuf *pkt_last_seg;  /**< Last segment of current packet. */
    //uint64_t      offloads;   /**< Offloads of DEV_RX_OFFLOAD_* */
    PC802_Mem_Pool_t    mpool;
    uint32_t            rc_cnt;
    //uint32_t            ep_cnt;
    uint16_t            nb_rx_desc; /**< number of RX descriptors. */
    //uint16_t            rx_tail;    /**< current value of RDT register. */
    uint16_t            nb_rx_hold; /**< number of held free RX desc. */
    uint16_t            rx_free_thresh; /**< max free RX desc to hold. */
    uint16_t            queue_id;   /**< RX queue index. */
    uint16_t            port_id;    /**< Device port identifier. */
    //uint8_t             pthresh;    /**< Prefetch threshold register. */
    //uint8_t             hthresh;    /**< Host threshold register. */
    //uint8_t             wthresh;    /**< Write-back threshold register. */
    //uint8_t             crc_len;    /**< 0 if CRC stripped, 4 otherwise. */
    struct pmd_queue_stats  stats;
};

/**
 * Structure associated with each descriptor of the TX ring of a TX queue.
 */
struct pc802_tx_entry {
    union {
        struct {
            struct rte_mbuf *mbuf; /**< mbuf associated with TX desc, if any. */
            //uint16_t next_id; /**< Index of next descriptor in ring. */
            //uint16_t last_id; /**< Index of last scattered descriptor. */
        };
        PC802_Mem_Block_t *mblk;
   };
};

/**
 * Structure associated with each TX queue.
 */
struct pc802_tx_queue {
    volatile PC802_Descriptor_t *tx_ring; /**< TX ring address */
    //uint64_t               tx_ring_phys_addr; /**< TX ring DMA address. */
    struct pc802_tx_entry    *sw_ring; /**< virtual address of SW ring. */
    volatile uint32_t      *trccnt_reg_addr; /**< Address of TDT register. */
    volatile uint32_t      *tepcnt_mirror_addr;
    //uint32_t               ep_cnt;
    PC802_Mem_Pool_t            mpool;
    uint32_t               rc_cnt;  /**< Current value of TDT register. */
    uint16_t               nb_tx_desc;    /**< number of TX descriptors. */
    /**< Start freeing TX buffers if there are less free descriptors than
         this value. */
    uint16_t               tx_free_thresh;
    /**< Number of TX descriptors to use before RS bit is set. */
    //uint16_t               tx_rs_thresh;
    /** Number of TX descriptors used since RS bit was set. */
    //uint16_t               nb_tx_used;
    /** Total number of TX descriptors ready to be allocated. */
    uint16_t               nb_tx_free;
    uint16_t               queue_id; /**< TX queue index. */
    uint16_t               port_id;  /**< Device port identifier. */
    //uint8_t                pthresh;  /**< Prefetch threshold register. */
    //uint8_t                hthresh;  /**< Host threshold register. */
    //uint8_t                wthresh;  /**< Write-back threshold register. */
    //struct em_ctx_info ctx_cache;
    /**< Hardware context history.*/
    //uint64_t         offloads; /**< offloads of DEV_TX_OFFLOAD_* */
    struct pmd_queue_stats  stats;
};

struct pc802_adapter {
    uint8_t *bar0_addr;
    PC802_Descs_t *pDescs;
    uint64_t descs_phy_addr;
    struct pc802_tx_queue  txq[MAX_DL_CH_NUM];
    struct pc802_rx_queue  rxq[PC802_TRAFFIC_NUM + 1]; //additional rxq for c2h mailbox
    struct rte_ether_addr eth_addr;
    uint16_t port_id;
    uint8_t started;
    uint8_t stopped;

    uint64_t *dbg;
    uint32_t dgb_phy_addrL;
    uint32_t dgb_phy_addrH;
    uint32_t dbg_rccnt;
    uint32_t DEVRDY;
    uint32_t DRVSTATE;

    uint16_t port_index;
    uint16_t log_flag;
};

#define PC802_DEV_PRIVATE(adapter)  ((struct pc802_adapter *)adapter)

#define DIR_PCIE_DMA_DOWNLINK   1
#define DIR_PCIE_DMA_UPLINK     0

static char DEFAULT_IMAGE_PATH[] = "/lib/firmware/pico";
static char CUR_PATH[] = ".";

int pc802_ctrl_thread_create(pthread_t *thread, const char *name, pthread_attr_t *attr,
		void *(*start_routine)(void *), void *arg);
static PC802_BAR_Ext_t * pc802_get_BAR_Ext(uint16_t port);
static int pc802_download_boot_image(uint16_t port);
static uint32_t handle_pfi_0_vec_read(uint16_t port, uint32_t file_id, uint32_t offset, uint32_t address, uint32_t length);
static uint32_t handle_pfi_0_vec_dump(uint16_t port, uint32_t file_id, uint32_t address, uint32_t length);
static uint32_t handle_non_pfi_0_vec_read(uint16_t port, uint32_t file_id, uint32_t offset, uint32_t address, uint32_t length);
static uint32_t handle_non_pfi_0_vec_dump(uint16_t port, uint32_t file_id, uint32_t address, uint32_t length);
static void * pc802_debug(void *data);
static void * pc802_trace_thread(void *data);
static void * pc802_vec_access(void *data);

static PC802_BAR_t * pc802_get_BAR(uint16_t port_id)
{
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    PC802_BAR_t *bar = (PC802_BAR_t *)adapter->bar0_addr;
	return bar;
}

int pc802_get_socket_id(uint16_t port_id)
{
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
	return dev->data->numa_node;
}

uint16_t pc802_get_count(void)
{
#ifdef MULTI_PC802
	return num_pc802s;
#else
    return num_pc802s>0?1:0;
#endif
}

static uint16_t pc802_get_port_index(uint16_t port_id)
{
    return PC802_DEV_PRIVATE(rte_eth_devices[port_id].data->dev_private)->port_index;
}

int pc802_get_port_id(uint16_t pc802_index)
{
    static int32_t port_num = 0;
    static int32_t port_id[PC802_INDEX_MAX] = {-1,-1,-1,-1};
    int index = 0;
    int i;
    struct rte_pci_device *pci_dev;

    RTE_ASSERT(pc802_index < PC802_INDEX_MAX);
    if ( port_num > 0 )
        return port_id[pc802_index];

    RTE_ETH_FOREACH_DEV(i)
    {
        DBLOG( "ETH DEV %d: %s\n", i, rte_eth_devices[i].device->name );
        pci_dev = RTE_ETH_DEV_TO_PCI(&rte_eth_devices[i]);
        if ( (PCI_VENDOR_PICOCOM==pci_dev->id.vendor_id) &&
             ( (PCI_DEVICE_PICOCOM_PC802_OLD==pci_dev->id.device_id) || (PCI_DEVICE_PICOCOM_PC802==pci_dev->id.device_id) ) )
        {
            DBLOG( "PC802 index %d port is %d:%s\n", index, i, rte_eth_devices[i].device->name );
            port_id[index++] = i;
            port_num++;
        }
    }
    return port_id[pc802_index];
}

uint16_t pc802_get_index_by_name(const char *name)
{
    int i;
    int port;

    for (i = 0; i < pc802_get_count(); i++) {
        port = pc802_get_port_id(i);
        if (0 == strcmp(rte_eth_devices[port].device->name, name))
            return i;
    }
    return MBUF_INVALID_PORT;
}

int pc802_create_rx_queue(uint16_t port_id, uint16_t queue_id, uint32_t block_size, uint32_t block_num, uint16_t nb_desc)
{
    if (!isPowerOf2(nb_desc) || (nb_desc > MAX_DESC_NUM) || (nb_desc < MIN_DESC_NUM))
        return -EINVAL;
    if (block_num <= nb_desc)
        return -EINVAL;
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    PC802_BAR_t *bar = (PC802_BAR_t *)adapter->bar0_addr;
    struct pc802_rx_queue *rxq = &adapter->rxq[queue_id];
    volatile PC802_Descriptor_t *rxdp;
    struct pc802_rx_entry *rxep;
    uint32_t mask = NPU_CACHE_LINE_SZ - 1;
    uint32_t k;
    int socket_id = dev->device->numa_node;
    char z_name[RTE_MEMZONE_NAMESIZE];
    const struct rte_memzone *mz;
    PC802_Mem_Block_t *mblk;
    uint32_t rc_rst_cnt;
    uint32_t ep_rst_cnt;
    volatile uint32_t ep_cnt;

    rxq->mpool.block_size = block_size;
    rxq->mpool.block_num = block_num;

    block_size = (block_size + mask) & (~mask);
    //block_size += sizeof(PC802_Mem_Block_t);

    /* Allocate software ring. */
    if (NULL != rxq->sw_ring) {
        rte_free(rxq->sw_ring);
    }
    if ((rxq->sw_ring = rte_zmalloc("rxq->sw_ring",
            sizeof (rxq->sw_ring[0]) * nb_desc,
            RTE_CACHE_LINE_SIZE)) == NULL) {
        DBLOG("ERROR: fail to zmalloc size = %lu for Port %hu Rx queue %hu\n",
            sizeof (rxq->sw_ring[0]) * nb_desc, port_id, queue_id);
        return -ENOMEM;
    }

    rxq->mpool.first = NULL;
    snprintf(z_name, sizeof(z_name), "PC802Rx_%2d_%2d",
            dev->data->port_id, queue_id);
    if (NULL != (mz = rte_memzone_lookup(z_name))) {
        rte_memzone_free(mz);
    }
    mz = rte_memzone_reserve(z_name, block_size*block_num, socket_id, RTE_MEMZONE_IOVA_CONTIG);
    if (mz == NULL) {
        DBLOG("ERROR: fail to memzone reserve size = %u for Port %hu Rx queue %hu block %u\n",
            block_size*block_num, port_id, queue_id, block_num);
        return -ENOMEM;
    }
    DBLOG("UL MZ[%1u]: PhyAddr=0x%lX VirtulAddr=%p\n",
        queue_id, mz->iova, mz->addr);
    for (k = 0; k < block_num; k++) {
        mblk = (PC802_Mem_Block_t *)((char *)mz->addr + block_size*k);
        mblk->buf_phy_addr = mz->iova + block_size*k + sizeof(PC802_Mem_Block_t);
        mblk->pkt_length = 0;
        mblk->next = rxq->mpool.first;
        mblk->first = &rxq->mpool.first;
        mblk->alloced = 0;
        rxq->mpool.first = mblk;
        DBLOG_INFO("UL MBlk[%1u][%3u]: PhyAddr=0x%lX VirtAddr=%p\n",
            queue_id, k, mblk->buf_phy_addr, &mblk[1]);
    }

    rxdp = rxq->rx_ring = adapter->pDescs->ul[queue_id];
    rxep = rxq->sw_ring;
    for (k = 0; k < nb_desc; k++) {
        rxep->mblk = rxq->mpool.first;
        rxq->mpool.first = rxep->mblk->next;
        rxep->mblk->next = NULL;
        rxep->mblk->alloced = 1;
        rxdp->phy_addr = rxep->mblk->buf_phy_addr;
        rxdp->length = 0;
        DBLOG_INFO("UL DESC[%1u][%3u].phy_addr=0x%lX\n", queue_id, k, rxdp->phy_addr);
        rxep++;
        rxdp++;
    }

    rxq->nb_rx_desc = nb_desc;
    rxq->rc_cnt = 0;
    rxq->nb_rx_hold = 0;
    rxq->rx_free_thresh = nb_desc / 4;
    rxq->queue_id = queue_id;
    rxq->port_id = port_id;
    if (PC802_TRAFFIC_MAILBOX == queue_id) {
        PC802_BAR_Ext_t *ext = pc802_get_BAR_Ext(port_id);
        rxq->rrccnt_reg_addr = (volatile uint32_t *)&ext->MB_C2H_RCCNT;
        rxq->repcnt_mirror_addr = (volatile uint32_t *)&adapter->pDescs->mr.MB_C2H_EPCNT;
        PC802_WRITE_REG(bar->MB_C2H_RDNUM, nb_desc);
    } else {
        rxq->rrccnt_reg_addr = (volatile uint32_t *)&bar->RRCCNT[queue_id];
        rxq->repcnt_mirror_addr = &adapter->pDescs->mr.REPCNT[queue_id];
    }

    if ((queue_id < PC802_TRAFFIC_MAILBOX) && (PC802_READ_REG(bar->DEVEN))) {
        PC802_WRITE_REG(bar->RDNUM[queue_id], nb_desc);
        rte_wmb();
        rc_rst_cnt = PC802_READ_REG(bar->RX_RST_RCCNT[queue_id]);
        rc_rst_cnt++;
        PC802_WRITE_REG(bar->RX_RST_RCCNT[queue_id], rc_rst_cnt);
        do {
            ep_rst_cnt = PC802_READ_REG(bar->RX_RST_EPCNT[queue_id]);
        } while (ep_rst_cnt != rc_rst_cnt);
        do {
            ep_cnt = PC802_READ_REG(bar->REPCNT[queue_id]);
        } while (0 != ep_cnt);
        do {
            ep_cnt = *rxq->repcnt_mirror_addr;
        } while (0 != ep_cnt);
        if (0 != PC802_READ_REG(bar->RRCCNT[queue_id])) {
            rc_rst_cnt++;
            PC802_WRITE_REG(bar->RX_RST_RCCNT[queue_id], rc_rst_cnt);
            rte_io_wmb();
            PC802_WRITE_REG(bar->RRCCNT[queue_id], 0);
            do {
                ep_rst_cnt = PC802_READ_REG(bar->RX_RST_EPCNT[queue_id]);
            } while (ep_rst_cnt != rc_rst_cnt);
        }
    }

    DBLOG("Succeed: port %hu queue %hu block_size = %u block_num = %u nb_desc = %hu\n",
        port_id, queue_id, block_size, block_num, nb_desc);
    return 0;
}

int pc802_create_tx_queue(uint16_t port_id, uint16_t queue_id, uint32_t block_size, uint32_t block_num, uint16_t nb_desc)
{
    if (!isPowerOf2(nb_desc) || (nb_desc > MAX_DESC_NUM) || (nb_desc < MIN_DESC_NUM))
        return -EINVAL;
    if (block_num <= nb_desc)
        return -EINVAL;
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    PC802_BAR_t *bar = (PC802_BAR_t *)adapter->bar0_addr;
    struct pc802_tx_queue *txq = &adapter->txq[queue_id];
    struct pc802_tx_entry *txep;
    uint32_t mask = NPU_CACHE_LINE_SZ - 1;
    uint32_t k;
    int socket_id = dev->device->numa_node;
    char z_name[RTE_MEMZONE_NAMESIZE];
    const struct rte_memzone *mz;
    PC802_Mem_Block_t *mblk;
    uint32_t rc_rst_cnt;
    uint32_t ep_rst_cnt;
    volatile uint32_t ep_cnt;

    txq->mpool.block_size = block_size;
    txq->mpool.block_num = block_num;

    block_size = (block_size + mask) & (~mask);
    //block_size += sizeof(PC802_Mem_Block_t);

    /* Allocate software ring. */
    if (NULL != txq->sw_ring) {
        rte_free(txq->sw_ring);
    }
    sprintf(z_name, "txq%d->sw_ring", dev->data->port_id);
    if ((txq->sw_ring = rte_zmalloc( z_name,
            sizeof (txq->sw_ring[0]) * nb_desc,
            RTE_CACHE_LINE_SIZE)) == NULL) {
        DBLOG("ERROR: fail to zmalloc size = %lu for Port %hu Tx queue %hu\n",
            sizeof (txq->sw_ring[0]) * nb_desc, port_id, queue_id);
        return -ENOMEM;
    }

    txq->mpool.first = NULL;
    snprintf(z_name, sizeof(z_name), "PC802Tx_%02d_%02d", dev->data->port_id, queue_id );
    if (NULL != (mz = rte_memzone_lookup(z_name))) {
        rte_memzone_free(mz);
    }
    mz = rte_memzone_reserve(z_name, block_size*block_num, socket_id, RTE_MEMZONE_IOVA_CONTIG);
    if (mz == NULL) {
        DBLOG("ERROR: fail to memzone %s reserve size = %u for Port %hu Tx queue %hu\n", z_name,
            block_size*block_num, port_id, queue_id);
        return -ENOMEM;
    }
    DBLOG("DL MZ[%1u]: PhyAddr=0x%lX VirtulAddr=%p\n",
        queue_id, mz->iova, mz->addr);
    for (k = 0; k < block_num; k++) {
        mblk = (PC802_Mem_Block_t *)((char *)mz->addr+block_size*k);
        mblk->buf_phy_addr = mz->iova + block_size*k + sizeof(PC802_Mem_Block_t);
        mblk->pkt_length = 0;
        mblk->next = txq->mpool.first;
        mblk->first = &txq->mpool.first;
        mblk->alloced = 0;
        txq->mpool.first = mblk;
        DBLOG_INFO("DL MBlk[%1u][%3u]: PhyAddr=0x%lX VirtAddr=%p\n",
            queue_id, k, mblk->buf_phy_addr, &mblk[1]);
    }

    txq->tx_ring = adapter->pDescs->dl[queue_id];
    txep = txq->sw_ring;
    for (k = 0; k < nb_desc; k++) {
        txep->mblk = NULL;
        txep++;
    }

    txq->trccnt_reg_addr = (volatile uint32_t *)&bar->TRCCNT[queue_id];
    txq->tepcnt_mirror_addr = &adapter->pDescs->mr.TEPCNT[queue_id];
    txq->nb_tx_desc = nb_desc;
    txq->rc_cnt = 0;
    txq->nb_tx_free = nb_desc;
    txq->tx_free_thresh = nb_desc / 4;
    txq->queue_id = queue_id;
    txq->port_id = port_id;

    if (PC802_READ_REG(bar->DEVEN)) {
        PC802_WRITE_REG(bar->TDNUM[queue_id], nb_desc);
        rte_io_wmb();
        rc_rst_cnt = PC802_READ_REG(bar->TX_RST_RCCNT[queue_id]);
        rc_rst_cnt++;
        PC802_WRITE_REG(bar->TX_RST_RCCNT[queue_id], rc_rst_cnt);
        do {
            ep_rst_cnt = PC802_READ_REG(bar->TX_RST_EPCNT[queue_id]);
        } while (ep_rst_cnt != rc_rst_cnt);
        do {
            ep_cnt = PC802_READ_REG(bar->TEPCNT[queue_id]);
        } while (0 != ep_cnt);
        do {
            ep_cnt = *txq->tepcnt_mirror_addr;
        } while (0 != ep_cnt);
        if (0 != PC802_READ_REG(bar->TRCCNT[queue_id])) {
            rc_rst_cnt++;
            PC802_WRITE_REG(bar->TX_RST_RCCNT[queue_id], rc_rst_cnt);
            rte_io_wmb();
            PC802_WRITE_REG(bar->TRCCNT[queue_id], 0);
            do {
                ep_rst_cnt = PC802_READ_REG(bar->TX_RST_EPCNT[queue_id]);
            } while (ep_rst_cnt != rc_rst_cnt);
        }
    }

    DBLOG("Succeed: port %hu queue %hu block_size = %u block_num = %u nb_desc = %hu\n",
        port_id, queue_id, block_size, block_num, nb_desc);
    return 0;
}

PC802_Mem_Block_t * pc802_alloc_tx_mem_block(uint16_t port_id, uint16_t queue_id)
{
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    struct pc802_tx_queue *txq = &adapter->txq[queue_id];
    PC802_Mem_Block_t *mblk;
    mblk = txq->mpool.first;
    if (NULL != mblk) {
        txq->mpool.first = mblk->next;
        mblk->next = NULL;
        mblk->alloced = 1;
    }
    return mblk;
}

void pc802_free_mem_block(PC802_Mem_Block_t *mblk)
{
    if (NULL == mblk)
        return;
    if (mblk->alloced == 0)
        return;
    mblk->next = *mblk->first;
    *mblk->first = mblk;
    mblk->alloced = 0;
    return;
}

uint16_t pc802_rx_mblk_burst(uint16_t port_id, uint16_t queue_id,
    PC802_Mem_Block_t **rx_blks, uint16_t nb_blks)
{
    static uint64_t last_tsc[PC802_INDEX_MAX][PC802_TRAFFIC_NUM + 1] = {0};
#if 0
    uint64_t tstart, tend, tdiff;
    tstart = rte_rdtsc();
#endif

    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    struct pc802_rx_queue *rxq = &adapter->rxq[queue_id];
    volatile PC802_Descriptor_t *rx_ring;
    volatile PC802_Descriptor_t *rxdp;
    struct pc802_rx_entry *sw_ring;
    PC802_Mem_Block_t *rxm;
    PC802_Mem_Block_t *nmb;
    uint32_t mask = rxq->nb_rx_desc - 1;
    uint32_t idx;
    uint32_t ep_txed;
    uint32_t rx_id;
    uint16_t nb_rx;
    uint16_t nb_hold;

    nb_rx = 0;
    nb_hold = rxq->nb_rx_hold;
    rx_id = rxq->rc_cnt;
    rx_ring = rxq->rx_ring;
    sw_ring = rxq->sw_ring;
    ep_txed = *rxq->repcnt_mirror_addr - rx_id;
    nb_blks = (ep_txed < nb_blks) ? ep_txed : nb_blks;
    while (nb_rx < nb_blks) {
        idx = rx_id & mask;
        rxdp = &rx_ring[idx];

        nmb = rxq->mpool.first;
        if (nmb == NULL) {
            PMD_RX_LOG(DEBUG, "RX mblk alloc failed port_id=%u "
                   "queue_id=%u",
                   (unsigned) rxq->port_id,
                   (unsigned) rxq->queue_id);
            break;
        }
        rxq->mpool.first = nmb->next;
        nmb->next = NULL;
        nmb->alloced = 1;

        rxm = sw_ring[idx].mblk;
        rte_prefetch0(rxm);

        if ((idx & 0x3) == 0) {
            rte_prefetch0(&rx_ring[idx]);
            rte_prefetch0(&sw_ring[idx]);
        }

        rxm->pkt_length = rxdp->length;
        rxm->pkt_type = rxdp->type;
        rxm->eop = rxdp->eop;
        rte_prefetch0(&rxm[1]);
        //DBLOG("UL DESC[%1u][%3u]: virtAddr=0x%lX phyAddr=0x%lX Length=%u Type=%1u EOP=%1u\n",
        //    queue_id, idx, (uint64_t)&rxm[1], rxdp->phy_addr, rxdp->length, rxdp->type, rxdp->eop);
        rx_blks[nb_rx++] = rxm;

        sw_ring[idx].mblk = nmb;
        rxdp->phy_addr = nmb->buf_phy_addr;
        rxdp->length = 0;

        rx_id++;
        nb_hold++;
    }

    rxq->rc_cnt = rx_id;
    if (nb_hold > rxq->rx_free_thresh) {
        rte_io_wmb();
        *rxq->rrccnt_reg_addr = rxq->rc_cnt;
        if (PC802_TRAFFIC_MAILBOX == queue_id)
            DBLOG("Write Mailbox MB_C2H_RCCNT = %u\n", rxq->rc_cnt);
        nb_hold = 0;
    }
    rxq->nb_rx_hold = nb_hold;
    if (PC802_TRAFFIC_MAILBOX == queue_id)
        return nb_rx;
    if( nb_rx )
        pdump_cb(adapter->port_index, queue_id, PC802_FLAG_RX, rx_blks, nb_blks, last_tsc[adapter->port_index][queue_id]);
    last_tsc[adapter->port_index][queue_id] = rte_rdtsc();

#if 0
    tend = rte_rdtsc();
    tdiff = tend - tstart;
    uint32_t stat_no = 0xFF;
    if (PC802_TRAFFIC_5G_EMBB_CTRL == queue_id) {
        if (nb_rx)
            stat_no = NO_CTRL_BURST_GOT;
        else
            stat_no = NO_CTRL_BURST_NULL;
    } else if (PC802_TRAFFIC_5G_EMBB_DATA == queue_id) {
        if (nb_rx)
            stat_no = NO_DATA_BURST_GOT;
        else
            stat_no = NO_DATA_BURST_NULL;
    }
    if (stat_no < 0xFF) {
        check_proc_time(stat_no, tdiff);
    }
#endif

    return nb_rx;
}

uint16_t pc802_tx_mblk_burst(uint16_t port_id, uint16_t queue_id,
    PC802_Mem_Block_t **tx_blks, uint16_t nb_blks)
{
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    struct pc802_tx_queue *txq = &adapter->txq[queue_id];
    struct pc802_tx_entry *sw_ring = txq->sw_ring;
    struct pc802_tx_entry *txe;
    volatile PC802_Descriptor_t *tx_ring = txq->tx_ring;
    volatile PC802_Descriptor_t *txd;
    PC802_Mem_Block_t     *tx_blk;
    uint32_t mask = txq->nb_tx_desc - 1;
    uint32_t idx;
    uint32_t tx_id = txq->rc_cnt;
    uint16_t nb_tx;

    if ((txq->nb_tx_free < txq->tx_free_thresh) || (txq->nb_tx_free < nb_blks)) {
        txq->nb_tx_free = (uint32_t)txq->nb_tx_desc - txq->rc_cnt + *txq->tepcnt_mirror_addr;
    }

    nb_blks = (txq->nb_tx_free < nb_blks) ? txq->nb_tx_free : nb_blks;
    pdump_cb(adapter->port_index, queue_id, PC802_FLAG_TX, tx_blks, nb_blks, 0);
    for (nb_tx = 0; nb_tx < nb_blks; nb_tx++) {
        tx_blk = *tx_blks++;
        idx = tx_id & mask;
        txe = &sw_ring[idx];
        txd = &tx_ring[idx];

        if ((txe->mblk) && (txd->type)) {
            pc802_free_mem_block(txe->mblk);
        }

        txd->phy_addr = tx_blk->buf_phy_addr;
        txd->length = tx_blk->pkt_length;
        txd->type = tx_blk->pkt_type;
        txd->eop = tx_blk->eop;
        //DBLOG("DL DESC[%1u][%3u]: virtAddr=0x%lX phyAddr=0x%lX Length=%u Type=%1u EOP=%1u\n",
        //    queue_id, idx, (uint64_t)&tx_blk[1], txd->phy_addr, txd->length, txd->type, txd->eop);
        txe->mblk = tx_blk;
        tx_blk->next =  NULL;
        tx_id++;
    }


    PMD_TX_LOG(DEBUG, "port_id=%u queue_id=%u tx_tail=%u nb_tx=%u",
        (unsigned) txq->port_id, (unsigned) txq->queue_id,
        (unsigned) tx_id, (unsigned) nb_tx);
    txq->nb_tx_free -= nb_blks;
    txq->rc_cnt = tx_id;
    rte_wmb();
    *txq->trccnt_reg_addr = tx_id;

#ifdef ENABLE_CHECK_PC802_DL_TIMING
    if (PC802_TRAFFIC_5G_EMBB_CTRL == queue_id) {
        stat_and_check(NO_DL_CTRL_SEND);
    }
#endif

    return nb_tx;
}

static int
eth_pc802_infos_get(struct rte_eth_dev *dev, struct rte_eth_dev_info *dev_info)
{
    //struct e1000_hw *hw = E1000_DEV_PRIVATE_TO_HW(dev->data->dev_private);
    dev = dev;

    dev_info->min_rx_bufsize = 128; /* See BSIZE field of RCTL register. */
    dev_info->max_rx_pktlen = 1500; //em_get_max_pktlen(dev);
    dev_info->max_mac_addrs = 1; //hw->mac.rar_entry_count;

    /*
     * Starting with 631xESB hw supports 2 TX/RX queues per port.
     * Unfortunatelly, all these nics have just one TX context.
     * So we have few choises for TX:
     * - Use just one TX queue.
     * - Allow cksum offload only for one TX queue.
     * - Don't allow TX cksum offload at all.
     * For now, option #1 was chosen.
     * To use second RX queue we have to use extended RX descriptor
     * (Multiple Receive Queues are mutually exclusive with UDP
     * fragmentation and are not supported when a legacy receive
     * descriptor format is used).
     * Which means separate RX routinies - as legacy nics (82540, 82545)
     * don't support extended RXD.
     * To avoid it we support just one RX queue for now (no RSS).
     */

    dev_info->max_rx_queues = 1;
    dev_info->max_tx_queues = 1;

    dev_info->rx_queue_offload_capa = 0;
    dev_info->rx_offload_capa = 0;
    dev_info->tx_queue_offload_capa = 0;
    dev_info->tx_offload_capa = 0;

    dev_info->rx_desc_lim = (struct rte_eth_desc_lim) {
        .nb_max = MAX_DESC_NUM,
        .nb_min = 64,
        .nb_align = 64,
        .nb_seg_max = 1,
        .nb_mtu_seg_max = 1,
    };

    dev_info->tx_desc_lim = (struct rte_eth_desc_lim) {
        .nb_max = MAX_DESC_NUM,
        .nb_min = 64,
        .nb_align = 64,
        .nb_seg_max = 1,
        .nb_mtu_seg_max = 1,
    };

    dev_info->speed_capa = ETH_LINK_SPEED_10M_HD | ETH_LINK_SPEED_10M |
            ETH_LINK_SPEED_100M_HD | ETH_LINK_SPEED_100M |
            ETH_LINK_SPEED_1G;

    /* Preferred queue parameters */
    dev_info->default_rxportconf.nb_queues = 1;
    dev_info->default_txportconf.nb_queues = 1;
    dev_info->default_txportconf.ring_size = 256;
    dev_info->default_rxportconf.ring_size = 256;

    return 0;
}

static int
eth_pc802_configure(struct rte_eth_dev *dev)
{

    PMD_INIT_FUNC_TRACE();

    dev = dev;

    PMD_INIT_FUNC_TRACE();

    return 0;
}

static void
pc802_rx_queue_release_mbufs(struct pc802_rx_queue *rxq)
{
    unsigned i;

    if (rxq->sw_ring != NULL) {
        for (i = 0; i != rxq->nb_rx_desc; i++) {
            if (rxq->sw_ring[i].mbuf != NULL) {
                rte_pktmbuf_free_seg(rxq->sw_ring[i].mbuf);
                rxq->sw_ring[i].mbuf = NULL;
            }
        }
    }
}

static void
pc802_rx_queue_release(struct pc802_rx_queue *rxq)
{
    if (rxq != NULL) {
        pc802_rx_queue_release_mbufs(rxq);
        rte_free(rxq->sw_ring);
    }
}

/* Reset dynamic em_rx_queue fields back to defaults */
static void
pc802_reset_rx_queue(struct pc802_rx_queue *rxq)
{
    //rxq->ep_cnt = 0;
    rxq->nb_rx_hold = 0;
    //rxq->pkt_first_seg = NULL;
    //rxq->pkt_last_seg = NULL;
}

static int
eth_pc802_rx_queue_setup(struct rte_eth_dev *dev,
        uint16_t queue_idx,
        uint16_t nb_desc,
        unsigned int socket_id,
        const struct rte_eth_rxconf *rx_conf,
        struct rte_mempool *mp)
{
    struct pc802_rx_queue *rxq;

    struct pc802_adapter *adapter =
            PC802_DEV_PRIVATE(dev->data->dev_private);
    PC802_BAR_t *bar = (PC802_BAR_t *)adapter->bar0_addr;
    socket_id = socket_id;
    rx_conf = rx_conf;

    if (!isPowerOf2(nb_desc))
            return -(EINVAL);

    /* Free memory prior to re-allocation if needed. */
    if (dev->data->rx_queues[queue_idx] != NULL) {
        pc802_rx_queue_release(dev->data->rx_queues[queue_idx]);
        dev->data->rx_queues[queue_idx] = NULL;
    }

    rxq = &adapter->rxq[queue_idx];

    /* Allocate software ring. */
    if ((rxq->sw_ring = rte_zmalloc("rxq->sw_ring",
            sizeof (rxq->sw_ring[0]) * nb_desc,
            RTE_CACHE_LINE_SIZE)) == NULL) {
        DBLOG("Fail to zmalloc size = %lu for eth Rx queue %hu\n",
            sizeof(rxq->sw_ring[0]) * nb_desc, queue_idx);
        pc802_rx_queue_release(rxq);
        return -ENOMEM;
    }

    rxq->mb_pool = mp;
    rxq->nb_rx_desc = nb_desc;
    rxq->rx_free_thresh = nb_desc / 4;
    rxq->queue_id = queue_idx;
    rxq->port_id = dev->data->port_id;

    rxq->rrccnt_reg_addr = &bar->RRCCNT[queue_idx];
    rxq->repcnt_mirror_addr = &adapter->pDescs->mr.REPCNT[queue_idx];
    rxq->rx_ring = adapter->pDescs->ul[queue_idx];
    //rxq->rx_ring_phys_addr = adapter->descs_phy_addr + get_ul_desc_offset(queue_idx, 0);

    //PMD_INIT_LOG(DEBUG, "sw_ring=%p hw_ring=%p dma_addr=0x%"PRIx64,
    //       rxq->sw_ring, rxq->rx_ring, rxq->rx_ring_phys_addr);

    dev->data->rx_queues[queue_idx] = rxq;
    //pc802_reset_rx_queue(rxq);
    DBLOG("Succeed: port = %1u queue = %1u nb_desc = %u\n", rxq->port_id, queue_idx, nb_desc);
    return 0;
}

static void
pc802_tx_queue_release_mbufs(struct pc802_tx_queue *txq)
{
    unsigned i;

    if (txq->sw_ring != NULL) {
        for (i = 0; i != txq->nb_tx_desc; i++) {
            if (txq->sw_ring[i].mbuf != NULL) {
                rte_pktmbuf_free_seg(txq->sw_ring[i].mbuf);
                txq->sw_ring[i].mbuf = NULL;
            }
        }
    }
}

static void
pc802_tx_queue_release(struct pc802_tx_queue *txq)
{
    if (txq != NULL) {
        pc802_tx_queue_release_mbufs(txq);
        rte_free(txq->sw_ring);
    }
}

/* (Re)set dynamic em_tx_queue fields to defaults */
static void
pc802_reset_tx_queue(struct pc802_tx_queue *txq)
{
    uint16_t i, nb_desc;
    static const PC802_Descriptor_t txd_init = {
        .phy_addr = 0,
        .length = 0,
        .eop = 1,
        .type = 1
    };

    nb_desc = txq->nb_tx_desc;

    /* Initialize ring entries */

    //prev = (uint16_t) (nb_desc - 1);

    for (i = 0; i < nb_desc; i++) {
        txq->tx_ring[i] = txd_init;
        txq->sw_ring[i].mbuf = NULL;
        //txq->sw_ring[i].last_id = i;
        //txq->sw_ring[prev].next_id = i;
        //prev = i;
    }

    txq->nb_tx_free = nb_desc;
    //txq->last_desc_cleaned = (uint16_t)(nb_desc - 1);
    //txq->nb_tx_used = 0;
    //txq->tx_tail = 0;
}

static int
eth_pc802_tx_queue_setup(struct rte_eth_dev *dev,
        uint16_t queue_idx,
        uint16_t nb_desc,
        unsigned int socket_id,
        const struct rte_eth_txconf *tx_conf)
{
    struct pc802_tx_queue *txq;
    //struct e1000_hw     *hw;
    //uint32_t tsize;
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    PC802_BAR_t *bar = (PC802_BAR_t *)adapter->bar0_addr;

    if (!isPowerOf2(nb_desc))
        return -(EINVAL);

    socket_id = socket_id;
    tx_conf = tx_conf;

    /* Free memory prior to re-allocation if needed... */
    if (dev->data->tx_queues[queue_idx] != NULL) {
        pc802_tx_queue_release(dev->data->tx_queues[queue_idx]);
        dev->data->tx_queues[queue_idx] = NULL;
    }

    txq = &adapter->txq[queue_idx];

    /* Allocate software ring */
    if ((txq->sw_ring = rte_zmalloc("txq->sw_ring",
            sizeof(txq->sw_ring[0]) * nb_desc,
            RTE_CACHE_LINE_SIZE)) == NULL) {
        DBLOG("Fail to zmalloc size = %lu for eth Tx queue %hu\n",
            sizeof(txq->sw_ring[0]) * nb_desc, queue_idx);
        pc802_tx_queue_release(txq);
        return -ENOMEM;
    }

    txq->nb_tx_desc = nb_desc;
    txq->nb_tx_free = nb_desc;
    txq->tx_free_thresh = nb_desc / 4;
    txq->queue_id = queue_idx;
    txq->port_id = dev->data->port_id;

    //txq->tx_ring_phys_addr = adapter->descs_phy_addr + get_dl_desc_offset(queue_idx, 0);
    txq->tx_ring = adapter->pDescs->dl[queue_idx];
    txq->trccnt_reg_addr = (volatile uint32_t *)&bar->TRCCNT[queue_idx];
    txq->tepcnt_mirror_addr =(volatile uint32_t *)&adapter->pDescs->mr.TEPCNT[queue_idx];

    //PMD_INIT_LOG(DEBUG, "sw_ring=%p hw_ring=%p dma_addr=0x%"PRIx64,
    //       txq->sw_ring, txq->tx_ring, txq->tx_ring_phys_addr);

    pc802_reset_tx_queue(txq);

    dev->data->tx_queues[queue_idx] = txq;
    DBLOG("Succeed: port = %1u queue = %1u nb_desc = %u\n", txq->port_id, queue_idx, nb_desc);
    return 0;
}

static int
eth_pc802_promiscuous_enable(struct rte_eth_dev *dev)
{
    dev = dev;
    return 0;
}

static void
pc802_dev_clear_queues(struct rte_eth_dev *dev)
{
    uint16_t i;
    struct pc802_tx_queue *txq;
    struct pc802_rx_queue *rxq;

    for (i = 0; i < dev->data->nb_tx_queues; i++) {
        txq = dev->data->tx_queues[i];
        if (txq != NULL) {
            pc802_tx_queue_release_mbufs(txq);
            pc802_reset_tx_queue(txq);
        }
    }

    for (i = 0; i < dev->data->nb_rx_queues; i++) {
        rxq = dev->data->rx_queues[i];
        if (rxq != NULL) {
            pc802_rx_queue_release_mbufs(rxq);
            pc802_reset_rx_queue(rxq);
        }
    }
}

/**
 * Interrupt handler which shall be registered at first.
 *
 * @param handle
 *  Pointer to interrupt handle.
 * @param param
 *  The address of parameter (struct rte_eth_dev *) regsitered before.
 *
 * @return
 *  void
 */
static void
eth_pc802_interrupt_handler(void *param)
{
    struct rte_eth_dev *dev = (struct rte_eth_dev *)param;

    rte_eth_dev_callback_process(dev, RTE_ETH_EVENT_INTR_LSC, NULL);
}

/*********************************************************************
 *
 *  This routine disables all traffic on the adapter by issuing a
 *  global reset on the MAC.
 *
 **********************************************************************/
static int
eth_pc802_stop(struct rte_eth_dev *dev)
{
    //struct pc802_adapter *adapter =
    //        PC802_DEV_PRIVATE(dev->data->dev_private);
    //PC802_BAR_t *bar = (PC802_BAR_t *)adapter->bar0_addr;
    struct rte_eth_link link;
    struct rte_pci_device *pci_dev = RTE_ETH_DEV_TO_PCI(dev);
    struct rte_intr_handle *intr_handle = &pci_dev->intr_handle;

    pc802_dev_clear_queues(dev);

    /* clear the recorded link status */
    memset(&link, 0, sizeof(link));
    rte_eth_linkstatus_set(dev, &link);

    if (!rte_intr_allow_others(intr_handle))
        /* resume to the default handler */
        rte_intr_callback_register(intr_handle,
                       eth_pc802_interrupt_handler,
                       (void *)dev);

    /* Clean datapath event and queue/vec mapping */
    rte_intr_efd_disable(intr_handle);
    if (intr_handle->intr_vec != NULL) {
        rte_free(intr_handle->intr_vec);
        intr_handle->intr_vec = NULL;
    }

    return 0;
}

/*********************************************************************
 *
 *  Enable transmit unit.
 *
 **********************************************************************/
static void
eth_pc802_tx_init(struct rte_eth_dev *dev)
{
    struct pc802_adapter *adapter =
            PC802_DEV_PRIVATE(dev->data->dev_private);
    PC802_BAR_t *bar = (PC802_BAR_t *)adapter->bar0_addr;
    struct pc802_tx_queue *txq;
    uint16_t i;
    uint32_t rc_rst_cnt;
    uint32_t ep_rst_cnt;

    /* Setup the Base and Length of the Tx Descriptor Rings. */
    for (i = 0; i < dev->data->nb_tx_queues; i++) {
        txq = dev->data->tx_queues[i];
        PC802_WRITE_REG(bar->TRCCNT[i], 0);
        PC802_WRITE_REG(bar->TEPCNT[i], 0);
        *txq->tepcnt_mirror_addr = 0;
        PC802_WRITE_REG(bar->TDNUM[i], txq->nb_tx_desc);
        if (PC802_READ_REG(bar->DEVEN)) {
            rc_rst_cnt = PC802_READ_REG(bar->TX_RST_RCCNT[i ]);
            rc_rst_cnt++;
            PC802_WRITE_REG(bar->TX_RST_RCCNT[i], rc_rst_cnt);
            do {
                ep_rst_cnt = PC802_READ_REG(bar->TX_RST_EPCNT[i]);
            } while (ep_rst_cnt != rc_rst_cnt);
        }
    }
}

static int
pc802_alloc_rx_queue_mbufs(struct pc802_rx_queue *rxq)
{
    struct pc802_rx_entry *rxe = rxq->sw_ring;
    uint64_t dma_addr;
    unsigned i;

    /* Initialize software ring entries */
    for (i = 0; i < rxq->nb_rx_desc; i++) {
        volatile PC802_Descriptor_t *rxd;
        struct rte_mbuf *mbuf = rte_mbuf_raw_alloc(rxq->mb_pool);

        if (mbuf == NULL) {
            PMD_INIT_LOG(ERR, "RX mbuf alloc failed "
                     "queue_id=%hu", rxq->queue_id);
            DBLOG("ERROR: RX mbuf alloc failed "
                     "queue_id=%hu for desc %u\n", rxq->queue_id, i);
            return -ENOMEM;
        }

        dma_addr =
            rte_cpu_to_le_64(rte_mbuf_data_iova_default(mbuf));

        /* Clear HW ring memory */
        rxd = &rxq->rx_ring[i];
        rxd->phy_addr = dma_addr;
        rxd->length = 0;
        rxe[i].mbuf = mbuf;
    }

    return 0;
}


/*********************************************************************
 *
 *  Enable receive unit.
 *
 **********************************************************************/
static int
eth_pc802_rx_init(struct rte_eth_dev *dev)
{
    struct pc802_adapter *adapter =
            PC802_DEV_PRIVATE(dev->data->dev_private);
    PC802_BAR_t *bar = (PC802_BAR_t *)adapter->bar0_addr;
    struct pc802_rx_queue *rxq;
    //struct rte_eth_rxmode *rxmode;
    //uint32_t rctl;
    //uint32_t rfctl;
    //uint32_t rxcsum;
    //uint32_t rctl_bsize;
    uint16_t i;
    int ret;
    uint32_t rc_rst_cnt;
    uint32_t ep_rst_cnt;

    //dev->rx_pkt_burst = (eth_rx_burst_t)eth_em_recv_pkts;

    /* Configure and enable each RX queue. */
    for (i = 0; i < dev->data->nb_rx_queues; i++) {
        //uint64_t bus_addr;
        //uint32_t rxdctl;

        rxq = dev->data->rx_queues[i];

        /* Allocate buffers for descriptor rings and setup queue */
        ret = pc802_alloc_rx_queue_mbufs(rxq);
        if (ret)
            return ret;

        rxq->rc_cnt = 0;
        PC802_WRITE_REG(bar->RDNUM[i], rxq->nb_rx_desc);
        PC802_WRITE_REG(bar->RRCCNT[i], 0);
        *rxq->repcnt_mirror_addr = 0;
        PC802_WRITE_REG(bar->REPCNT[i], 0);
        if (PC802_READ_REG(bar->DEVEN)) {
            rc_rst_cnt = PC802_READ_REG(bar->RX_RST_RCCNT[i ]);
            rc_rst_cnt++;
            PC802_WRITE_REG(bar->RX_RST_RCCNT[i], rc_rst_cnt);
            do {
                ep_rst_cnt = PC802_READ_REG(bar->RX_RST_EPCNT[i]);
            } while (ep_rst_cnt != rc_rst_cnt);
        }
    }

    return 0;
}

static int
eth_pc802_start(struct rte_eth_dev *dev)
{
    struct pc802_adapter *adapter =
            PC802_DEV_PRIVATE(dev->data->dev_private);
    PC802_BAR_t *bar = (PC802_BAR_t *)adapter->bar0_addr;
    //struct rte_pci_device *pci_dev = RTE_ETH_DEV_TO_PCI(dev);
    //struct rte_intr_handle *intr_handle = &pci_dev->intr_handle;
    int ret;
    int q;
    //uint32_t intr_vector = 0;
    //uint32_t *speeds;
    //int num_speeds;
    //bool autoneg;

    PMD_INIT_FUNC_TRACE();

    if (RTE_PROC_PRIMARY != rte_eal_process_type()) {
        DBLOG("PC802 has been started by primary process, so bypass by secondary process!\n");
        return 0;
    }

    eth_pc802_stop(dev);

    eth_pc802_tx_init(dev);

    ret = eth_pc802_rx_init(dev);
    if (ret) {
        PMD_INIT_LOG(ERR, "Unable to initialize RX hardware");
        pc802_dev_clear_queues(dev);
        return ret;
    }

    adapter->stopped = 0;

    volatile uint32_t devRdy;
    volatile uint32_t drv_state;
    uint32_t old_devRdy, old_drv_state;

    usleep(1000);
    rte_wmb();
    PC802_WRITE_REG(bar->ULDMAN, 4);
    DBLOG("Set UL DMA Count = 4\n");

    DBLOG("Waiting for PC802 boot(devRdy=5) ...\n");
    do {
        usleep(1);
        devRdy = PC802_READ_REG(bar->DEVRDY);
    } while (devRdy != 5);
    old_drv_state = PC802_READ_REG(bar->DRVSTATE);
    old_devRdy = devRdy;
    DBLOG("DRVSTATE=%u, DEVRDY=%u, BOOTERROR=%u\n", old_drv_state, devRdy,
        PC802_READ_REG(bar->BOOTERROR));

    for (q = 0; q <= PC802_TRAFFIC_OAM; q++) {
        PC802_WRITE_REG(bar->TDNUM[q], adapter->txq[q].nb_tx_desc);
        PC802_WRITE_REG(bar->TRCCNT[q], 0);
        PC802_WRITE_REG(bar->RDNUM[q], adapter->rxq[q].nb_rx_desc);
        PC802_WRITE_REG(bar->RRCCNT[q], 0);
    }

    PC802_WRITE_REG(bar->DEVEN, 1);

    DBLOG("Waiting for PC802 boot(DRVSTATE=3) ...\n");
    do {
        usleep(1);
        drv_state = PC802_READ_REG(bar->DRVSTATE);
        devRdy = PC802_READ_REG(bar->DEVRDY);
        if ((drv_state != old_drv_state) || (devRdy != old_devRdy)) {
            DBLOG("DRVSTATE=%u, DEVRDY=%u\n", drv_state, devRdy);
            old_devRdy = devRdy;
            old_drv_state = drv_state;
        }
    } while (drv_state != 3);
    DBLOG( "DRVSTATE=%d, DEVRDY=%d.\n", drv_state, devRdy);

    volatile uint32_t macAddrL;
    macAddrL = PC802_READ_REG(bar->MACADDRL);
    adapter->eth_addr.addr_bytes[4] |= ((macAddrL >> 8) & 0xF);
    adapter->eth_addr.addr_bytes[5] |= (macAddrL & 0xFF);

    pc802_kni_add_port( adapter->port_id );
    PMD_INIT_LOG(DEBUG, "<<");

    return 0;
}

static uint16_t
eth_pc802_xmit_pkts(void *tx_queue, struct rte_mbuf **tx_pkts,
        uint16_t nb_pkts)
{
    struct pc802_tx_queue *txq;
    struct pc802_tx_entry *sw_ring;
    struct pc802_tx_entry *txe;
    volatile PC802_Descriptor_t *tx_ring;
    volatile PC802_Descriptor_t *txd;
    struct rte_mbuf     *tx_pkt;
    uint32_t mask;
    uint32_t idx;
    uint32_t tx_id;
    uint16_t nb_tx_free;
    uint16_t nb_tx;
    uint16_t mb_pkts;

    txq = tx_queue;
    sw_ring = txq->sw_ring;
    tx_ring = txq->tx_ring;
    mask = txq->nb_tx_desc - 1;
    tx_id   = txq->rc_cnt;

    /* Determine if the descriptor ring needs to be cleaned. */
     if ((txq->nb_tx_free < txq->tx_free_thresh) || (txq->nb_tx_free < nb_pkts)) {
        txq->nb_tx_free = (uint32_t)txq->nb_tx_desc - txq->rc_cnt + *txq->tepcnt_mirror_addr;
     }

    nb_tx_free = txq->nb_tx_free;
    mb_pkts = (nb_tx_free < nb_pkts) ? nb_tx_free : nb_pkts;
    /* TX loop */
    for (nb_tx = 0; nb_tx < mb_pkts; nb_tx++) {
        tx_pkt = *tx_pkts++;
        idx = tx_id & mask;
        txe = &sw_ring[idx];

        if (txe->mbuf) {
            rte_pktmbuf_free_seg(txe->mbuf);
        }
        txd = &tx_ring[idx];
        txd->phy_addr = rte_mbuf_data_iova(tx_pkt);
        txd->length = tx_pkt->data_len;
        txq->stats.bytes += tx_pkt->data_len;
        txd->eop = (tx_pkt->next == NULL);
        txd->type = tx_pkt->packet_type;
        txe->mbuf = tx_pkt;
        tx_id++;
    }
    nb_tx_free -= mb_pkts;

    /*
     * Set the Transmit Descriptor Tail (TDT)
     */
    PMD_TX_LOG(DEBUG, "port_id=%u queue_id=%u tx_tail=%u nb_tx=%u",
        (unsigned) txq->port_id, (unsigned) txq->queue_id,
        (unsigned) tx_id, (unsigned) nb_tx);
    txq->nb_tx_free = nb_tx_free;
    txq->rc_cnt = tx_id;
    rte_wmb();
    *txq->trccnt_reg_addr = tx_id;
    txq->stats.pkts += mb_pkts;
    txq->stats.err_pkts += nb_pkts -  mb_pkts;

    return nb_tx;
}

static uint16_t
eth_pc802_recv_pkts(void *rx_queue, struct rte_mbuf **rx_pkts,
        uint16_t nb_pkts)
{
    struct pc802_rx_queue *rxq;
    volatile PC802_Descriptor_t *rx_ring;
    volatile PC802_Descriptor_t *rxdp;
    struct pc802_rx_entry *sw_ring;
    struct rte_mbuf *rxm;
    struct rte_mbuf *nmb;
    uint32_t mask;
    uint32_t idx;
    uint32_t rx_id;
    uint32_t ep_txed;
    uint16_t pkt_len;
    uint16_t nb_rx;
    uint16_t nb_hold;
    uint16_t mb_pkts;

    rxq = rx_queue;
    mask = rxq->nb_rx_desc - 1;

    nb_rx = 0;
    nb_hold = rxq->nb_rx_hold;
    rx_id = rxq->rc_cnt;
    rx_ring = rxq->rx_ring;
    sw_ring = rxq->sw_ring;
    ep_txed = *rxq->repcnt_mirror_addr - rx_id;
    mb_pkts = (ep_txed < nb_pkts) ? ep_txed : nb_pkts;
    while (nb_rx < mb_pkts) {
        idx = rx_id & mask;
        rxdp = &rx_ring[idx];

        nmb = rte_mbuf_raw_alloc(rxq->mb_pool);
        if (nmb == NULL) {
            PMD_RX_LOG(DEBUG, "RX mbuf alloc failed port_id=%u "
                   "queue_id=%u",
                   (unsigned) rxq->port_id,
                   (unsigned) rxq->queue_id);
            rte_eth_devices[rxq->port_id].data->rx_mbuf_alloc_failed++;
            DBLOG("ERROR: RX mbuf alloc failed port_id=%u "
                   "queue_id=%u",
                   (unsigned) rxq->port_id,
                   (unsigned) rxq->queue_id);
            break;
        }

        /* Prefetch next mbuf while processing current one. */
        rte_prefetch0(sw_ring[idx].mbuf);

        /*
         * When next RX descriptor is on a cache-line boundary,
         * prefetch the next 4 RX descriptors and the next 8 pointers
         * to mbufs.
         */
        if ((idx & 0x3) == 0) {
            rte_prefetch0(&rx_ring[idx]);
            rte_prefetch0(&sw_ring[idx]);
        }

        rxm = sw_ring[idx].mbuf;
        pkt_len = (uint16_t)rte_le_to_cpu_16(rxdp->length);
        rxm->data_off = RTE_PKTMBUF_HEADROOM;
        rte_prefetch0((char *)rxm->buf_addr + rxm->data_off);
        rxm->nb_segs = 1;
        rxm->next = NULL;
        rxm->pkt_len = pkt_len;
        rxm->data_len = pkt_len;
        rxq->stats.bytes += pkt_len;
        rxm->packet_type = rxdp->type;
        rxm->port = rxq->port_id;

        rxm->ol_flags = 0;
        rx_pkts[nb_rx++] = rxm;

        sw_ring[idx].mbuf = nmb;
        rxdp->phy_addr = rte_cpu_to_le_64(rte_mbuf_data_iova_default(nmb));
        rxdp->length = 0;
        rxdp->eop = 1;
        rxdp->type = 1;

        rx_id++;
        nb_hold++;
    }

    rxq->rc_cnt = rx_id;
    if (nb_hold > rxq->rx_free_thresh) {
        rte_io_wmb();
        *rxq->rrccnt_reg_addr = rxq->rc_cnt;
        nb_hold = 0;
    }
    rxq->nb_rx_hold = nb_hold;
    rxq->stats.pkts += nb_rx;
    rxq->stats.err_pkts += nb_pkts - nb_rx;
    return nb_rx;
}

static void
eth_pc802_queue_release(void *q __rte_unused)
{
}

static int
eth_pc802_link_update(struct rte_eth_dev *dev __rte_unused,
        int wait_to_complete __rte_unused)
{
    return 0;
}

static int
eth_pc802_stats_get(struct rte_eth_dev *dev, struct rte_eth_stats *stats)
{
    unsigned long rx_packets_total = 0, rx_bytes_total = 0;
    unsigned long tx_packets_total = 0, tx_bytes_total = 0;
    struct rte_eth_dev_data *data = dev->data;
    unsigned long tx_packets_err_total = 0;
    unsigned int i, num_stats;
    struct pc802_rx_queue *rxq;
    struct pc802_tx_queue *txq;

    num_stats = RTE_MIN((unsigned int)RTE_ETHDEV_QUEUE_STAT_CNTRS,
            data->nb_rx_queues);
    for (i = 0; i < num_stats; i++) {
        rxq = data->rx_queues[i];
        stats->q_ipackets[i] = rxq->stats.pkts;
        stats->q_ibytes[i] = rxq->stats.bytes;
        rx_packets_total += stats->q_ipackets[i];
        rx_bytes_total += stats->q_ibytes[i];
    }

    num_stats = RTE_MIN((unsigned int)RTE_ETHDEV_QUEUE_STAT_CNTRS,
            data->nb_tx_queues);
    for (i = 0; i < num_stats; i++) {
        txq = data->tx_queues[i];
        stats->q_opackets[i] = txq->stats.pkts;
        stats->q_obytes[i] = txq->stats.bytes;
        stats->q_errors[i] = txq->stats.err_pkts;
        tx_packets_total += stats->q_opackets[i];
        tx_bytes_total += stats->q_obytes[i];
        tx_packets_err_total += stats->q_errors[i];
    }

    stats->ipackets = rx_packets_total;
    stats->ibytes = rx_bytes_total;
    stats->opackets = tx_packets_total;
    stats->obytes = tx_bytes_total;
    stats->oerrors = tx_packets_err_total;

    return 0;
}

static int
eth_pc802_stats_reset(struct rte_eth_dev *dev)
{
    struct rte_eth_dev_data *data = dev->data;
    struct pc802_rx_queue *rxq;
    struct pc802_tx_queue *txq;
    unsigned int i;

    for (i = 0; i < data->nb_rx_queues; i++) {
        rxq = data->rx_queues[i];
        rxq->stats.pkts = 0;
        rxq->stats.bytes = 0;
        rxq->stats.err_pkts = 0;
    }
    for (i = 0; i < data->nb_tx_queues; i++) {
        txq = data->tx_queues[i];
        txq->stats.pkts = 0;
        txq->stats.bytes = 0;
        txq->stats.err_pkts = 0;
    }
    return 0;
}

uint64_t *pc802_get_debug_mem(uint16_t port_id)
{
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    return adapter->dbg;
}

void pc802_access_ep_mem(uint16_t port_id, uint32_t startAddr, uint32_t bytesNum, uint32_t cmd)
{
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    PC802_BAR_t *bar = (PC802_BAR_t *)adapter->bar0_addr;
    uint32_t epcnt;

    PC802_WRITE_REG(bar->DBGEPADDR, startAddr);
    PC802_WRITE_REG(bar->DBGBYTESNUM, bytesNum);
    PC802_WRITE_REG(bar->DBGCMD, cmd);
    adapter->dbg_rccnt++;
    PC802_WRITE_REG(bar->DBGRCCNT, adapter->dbg_rccnt);

    do {
        usleep(10);
        epcnt = PC802_READ_REG(bar->DBGEPCNT);
    } while(epcnt != adapter->dbg_rccnt);
    return;
}

void pc802_show_pcie_counter(uint16_t port_id)
{
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    uint16_t queue_id;
    struct pc802_tx_queue *txq;
    struct pc802_rx_queue *rxq;
    static const char *qname[] = {"Ethernet  ", "EMBB_Data ", "EMBB_Ctrl "};
    for (queue_id = 0; queue_id <= PC802_TRAFFIC_5G_EMBB_CTRL; queue_id++) {
        txq = &adapter->txq[queue_id];
        rxq = &adapter->rxq[queue_id];
        printf("DL %s: RC = %3u   EP = %3u\n", qname[queue_id],
            *txq->trccnt_reg_addr, *txq->tepcnt_mirror_addr);
        printf("UL %s: RC = %3u   EP = %3u    RC_HOLD = %3u\n", qname[queue_id],
            *rxq->rrccnt_reg_addr, *rxq->repcnt_mirror_addr, rxq->nb_rx_hold);
    }
}

void pc802_show_tx_info(uint16_t port_id, uint16_t queue_id, uint32_t rc_counter)
{
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    struct pc802_tx_queue *txq = &adapter->txq[queue_id];
    volatile PC802_Descriptor_t *txd;
    PC802_Mem_Block_t     *tx_blk;
    rc_counter &= (txq->nb_tx_desc - 1);
    txd = &txq->tx_ring[rc_counter];
    tx_blk = txq->sw_ring[rc_counter].mblk;
    printf("DL_Desc[%1u][%1u][%3u]: phyAddr=0x%lX Len=%6u Type=%2u EOP=%1u\n",
        port_id, queue_id, rc_counter, txd->phy_addr, txd->length, txd->type, txd->eop);
    printf("DL_Buf: virtAddr=%p phyAddr=0x%lX, Len=%6u Type=%2u EOP=%1u\n",
        &tx_blk[1], tx_blk->buf_phy_addr, tx_blk->pkt_length, tx_blk->pkt_type, tx_blk->eop);
    uint8_t *p = (uint8_t *)&tx_blk[1];
    uint32_t L, C;
    for (L = 0; L < 4; L++) {
        printf("DL_Data[%1u]: ", L);
        for (C = 0; C < 16; C++) {
            printf("%02X ", *p++);
        }
        printf("\n");
    }
}

void pc802_show_rx_info(uint16_t port_id, uint16_t queue_id, uint32_t rc_counter)
{
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    struct pc802_rx_queue *rxq = &adapter->rxq[queue_id];
    volatile PC802_Descriptor_t *rxd;
    PC802_Mem_Block_t     *rx_blk;
    rc_counter &= (rxq->nb_rx_desc - 1);
    rxd = &rxq->rx_ring[rc_counter];
    rx_blk = rxq->sw_ring[rc_counter].mblk;
    printf("UL_Desc[%1u][%1u][%3u]: phyAddr=0x%lX Len=%6u Type=%2u EOP=%1u\n",
        port_id, queue_id, rc_counter, rxd->phy_addr, rxd->length, rxd->type, rxd->eop);
    printf("UL_Buf: virtAddr=%p phyAddr=0x%lX, Len=%6u Type=%2u EOP=%1u\n",
        &rx_blk[1], rx_blk->buf_phy_addr, rx_blk->pkt_length, rx_blk->pkt_type, rx_blk->eop);
    uint8_t *p = (uint8_t *)&rx_blk[1];
    uint32_t L, C;
    for (L = 0; L < 4; L++) {
        printf("UL_Data[%1u]: ", L);
        for (C = 0; C < 16; C++) {
            printf("%02X ", *p++);
        }
        printf("\n");
    }
}

void pc802_show_tx_data(uint16_t port_id, uint16_t queue_id, uint32_t rc_counter)
{
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    struct pc802_tx_queue *txq = &adapter->txq[queue_id];
    volatile PC802_Descriptor_t *txd;
    PC802_Mem_Block_t     *tx_blk;
    rc_counter &= (txq->nb_tx_desc - 1);
    txd = &txq->tx_ring[rc_counter];
    tx_blk = txq->sw_ring[rc_counter].mblk;
    printf("DL_Desc[%1u][%1u][%3u]: phyAddr=0x%lX Len=%6u Type=%2u EOP=%1u\n",
        port_id, queue_id, rc_counter, txd->phy_addr, txd->length, txd->type, txd->eop);
    printf("DL_Buf: virtAddr=%p phyAddr=0x%lX, Len=%6u Type=%2u EOP=%1u\n",
        &tx_blk[1], tx_blk->buf_phy_addr, tx_blk->pkt_length, tx_blk->pkt_type, tx_blk->eop);
    uint8_t *p = (uint8_t *)&tx_blk[1];
    uint32_t LL = (tx_blk->pkt_length + 15) >> 4;
    uint32_t L, C;
    for (L = 0; L < LL; L++) {
        printf("DL_Data[%4u]: ", L);
        for (C = 0; C < 16; C++) {
            printf("%02X ", *p++);
        }
        printf("\n");
    }
}

void pc802_show_rx_data(uint16_t port_id, uint16_t queue_id, uint32_t rc_counter)
{
    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    struct pc802_rx_queue *rxq = &adapter->rxq[queue_id];
    volatile PC802_Descriptor_t *rxd;
    PC802_Mem_Block_t     *rx_blk;
    rc_counter &= (rxq->nb_rx_desc - 1);
    rxd = &rxq->rx_ring[rc_counter];
    rx_blk = rxq->sw_ring[rc_counter].mblk;
    printf("UL_Desc[%1u][%1u][%3u]: phyAddr=0x%lX Len=%6u Type=%2u EOP=%1u\n",
        port_id, queue_id, rc_counter, rxd->phy_addr, rxd->length, rxd->type, rxd->eop);
    printf("UL_Buf: virtAddr=%p phyAddr=0x%lX, Len=%6u Type=%2u EOP=%1u\n",
        &rx_blk[1], rx_blk->buf_phy_addr, rx_blk->pkt_length, rx_blk->pkt_type, rx_blk->eop);
    uint8_t *p = (uint8_t *)&rx_blk[1];
    uint32_t LL = (rx_blk->pkt_length + 15) >> 4;
    uint32_t L, C;
    for (L = 0; L < LL; L++) {
        printf("UL_Data[%4u]: ", L);
        for (C = 0; C < 16; C++) {
            printf("%02X ", *p++);
        }
        printf("\n");
    }
}


static const struct eth_dev_ops eth_pc802_ops = {
    .dev_configure        = eth_pc802_configure,
    .dev_start            = eth_pc802_start,
    .dev_stop             = eth_pc802_stop,
    .promiscuous_enable   = eth_pc802_promiscuous_enable,
    .dev_infos_get        = eth_pc802_infos_get,
    .rx_queue_setup       = eth_pc802_rx_queue_setup,
    .tx_queue_setup       = eth_pc802_tx_queue_setup,
    .rx_queue_release     = eth_pc802_queue_release,
    .tx_queue_release     = eth_pc802_queue_release,
    .link_update          = eth_pc802_link_update,
    .stats_get            = eth_pc802_stats_get,
    .stats_reset          = eth_pc802_stats_reset
};

static const struct rte_eth_link pmd_link = {
        .link_speed = ETH_SPEED_NUM_10G,
        .link_duplex = ETH_LINK_FULL_DUPLEX,
        .link_status = ETH_LINK_DOWN,
        .link_autoneg = ETH_LINK_FIXED,
};

static void pc802_bar_memset(uint32_t *p, uint32_t c, uint32_t u32_cnt)
{
    volatile uint32_t *s;
    s = (volatile uint32_t *)p;
    while (u32_cnt > 0) {
        pc802_write_reg(s, c);
        s++;
        u32_cnt--;
    }
    return;
}

static const cpu_set_t * get_ctrl_cpuset( void )
{
    static rte_cpuset_t ctrl_cpuset;

    if ( 0 == CPU_COUNT(&ctrl_cpuset) ) {
        FILE *fp = NULL;
        char buffer[128] = {0};
        int core=0;
        int min,max;
        char *ret = NULL;

        fp = popen("cat /sys/devices/system/cpu/present", "r");
        ret = fgets(buffer, sizeof(buffer), fp);
        pclose(fp);
        if ( (ret!=NULL) && (2== sscanf( buffer, "%d-%d", &min, &max )) ) {
            DBLOG( "cpu present:%d-%d\n", min, max );
            for( core=min; core<=max; core++ )
                CPU_SET( core, &ctrl_cpuset );
        }

        fp = popen("cat /sys/devices/system/cpu/isolated", "r");
        ret = fgets(buffer, sizeof(buffer), fp);
        pclose(fp);
        if ( (ret!=NULL) && (2== sscanf( buffer, "%d-%d", &min, &max )) ) {
            DBLOG( "cpu isolated:%d-%d\n", min, max );
            for( core=min; core<=max; core++ )
                CPU_CLR( core, &ctrl_cpuset );
        }

        DBLOG( "get ctrl cpu set %lu.\n", *((unsigned long*)&ctrl_cpuset) );
    }

    return &ctrl_cpuset;
}

int pc802_ctrl_thread_create(pthread_t *thread, const char *name, pthread_attr_t *attr,
		void *(*start_routine)(void *), void *arg)
{
	int ret;
    pthread_attr_t l_attr;
    const struct sched_param sp = {
        .sched_priority = sched_get_priority_max(SCHED_OTHER),
    };

    if ( attr == NULL )
    {
        pthread_attr_init(&l_attr);
        attr = &l_attr;
        pthread_attr_setschedparam(attr, &sp);
        pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED);
    }
    pthread_attr_setschedpolicy(attr, SCHED_OTHER);

	ret = pthread_create( thread, attr, start_routine, arg );
	if (ret != 0) {
        DBLOG( "pthread_create %s fail\n", name );
		return ret;
    }

	if (name != NULL) {
		ret = rte_thread_setname(*thread, name);
		if (ret < 0)
			DBLOG( "Cannot set name %s for ctrl thread\n", name );
	}

	ret = pthread_setaffinity_np(*thread, sizeof(cpu_set_t), get_ctrl_cpuset() );
	if (ret != 0)
        DBLOG( "Set affinity for ctrl thread %s fail\n", name );

	return -ret;
}

static int pc802_check_rerun(struct pc802_adapter *adapter)
{
    PC802_BAR_t *bar = pc802_get_BAR(adapter->port_id);
    PC802_BAR_Ext_t *ext = pc802_get_BAR_Ext(adapter->port_id);
    adapter->DEVRDY = PC802_READ_REG(bar->DEVRDY);
    adapter->DRVSTATE = PC802_READ_REG(bar->DRVSTATE);
    DBLOG("Port_Id = %u DEVRDY = %u DRVSTATE = %u\n", adapter->port_id,
        adapter->DEVRDY, adapter->DRVSTATE);
    if (adapter->DEVRDY < 2)
        return 0;
    uint32_t VEC_RCCNT = PC802_READ_REG(ext->VEC_RCCNT);
    uint32_t VEC_EPCNT = PC802_READ_REG(ext->VEC_EPCNT);
    if (VEC_RCCNT != VEC_EPCNT) {
        DBLOG("PFI 0 is doing vec_access (VEC_EPCNT = %u VEC_RCCNT = %u) !\n",
            VEC_EPCNT, VEC_RCCNT);
        DBLOG("Please reset PC802 and NPU driver is exiting !!!\n");
        exit(0);
    }
    uint32_t DBGCMD = PC802_READ_REG(bar->DBGCMD);
    uint32_t DBGEPCNT = PC802_READ_REG(bar->DBGEPCNT);
    uint32_t DBGRCCNT = PC802_READ_REG(bar->DBGRCCNT);
    if (DBGRCCNT != DBGEPCNT) {
        DBLOG("PFI 0 PC802_debug( ) is running (DBGCMD = %u DBGEPCNT = %u DBGRCCNT = %u) !\n",
            DBGCMD, DBGEPCNT, DBGRCCNT);
        DBLOG("It is raised by vec access from some core other than PFI 0 or NPU!\n");
        DBLOG("Please reset PC802 and NPU driver is exiting !!!\n");
        exit(0);
    }

    return 0;
}

static int pc802_init_c2h_mailbox(struct pc802_adapter *adapter)
{
    return pc802_create_rx_queue(adapter->port_id, PC802_TRAFFIC_MAILBOX, 0x4600, 64, 32);
}

static int
eth_pc802_dev_init(struct rte_eth_dev *eth_dev)
{
    struct rte_pci_device *pci_dev = RTE_ETH_DEV_TO_PCI(eth_dev);
    struct rte_eth_dev_data *data = eth_dev->data;
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(eth_dev->data->dev_private);
    PC802_BAR_t *bar;
    uint32_t dsp;
    char temp_name[32] = {0};

    pc802_devices[num_pc802s] = adapter;
    num_pc802s++;
    if (RTE_PROC_PRIMARY != rte_eal_process_type()) {
        uint32_t drv_state;
        bar = (PC802_BAR_t *)adapter->bar0_addr;
        do {
            usleep(1);
            drv_state = PC802_READ_REG(bar->DRVSTATE);
        } while (drv_state != 3);
        DBLOG("Secondary PC802 App detect drv_state = 3 !\n");
        uint32_t DBAH = PC802_READ_REG(bar->DBAH);
        uint32_t DBAL = PC802_READ_REG(bar->DBAL);
        DBLOG("DBA: 0x%08X %08X\n", DBAH, DBAL);
        sprintf(temp_name, "PC802_DESCS_MR%d", data->port_id );
        const struct rte_memzone *mz_s = rte_memzone_lookup(temp_name);
        DBLOG("mz_s->iova = 0x%lX\n", mz_s->iova);
        DBLOG("mz_s->addr = %p\n", mz_s->addr);
        return 0;
    }

    data = eth_dev->data;
    data->nb_rx_queues = 1;
    data->nb_tx_queues = 1;
    data->dev_link = pmd_link;
    data->mac_addrs = &adapter->eth_addr;

    adapter->port_id = data->port_id;
    adapter->eth_addr.addr_bytes[0] = 0x8C;
    adapter->eth_addr.addr_bytes[1] = 0x1F;
    adapter->eth_addr.addr_bytes[2] = 0x64;
    adapter->eth_addr.addr_bytes[3] = 0xB4;
    adapter->eth_addr.addr_bytes[4] = 0xC0;
    adapter->eth_addr.addr_bytes[5] = 0x00;

    eth_dev->dev_ops = &eth_pc802_ops;
    eth_dev->rx_pkt_burst = (eth_rx_burst_t)&eth_pc802_recv_pkts;
    eth_dev->tx_pkt_burst = (eth_tx_burst_t)&eth_pc802_xmit_pkts;

    rte_eth_copy_pci_info(eth_dev, pci_dev);

    adapter->bar0_addr = (uint8_t *)pci_dev->mem_resource[0].addr;
    bar = (PC802_BAR_t *)adapter->bar0_addr;

    pc802_check_rerun(adapter);

    DBLOG("PC802_BAR[0].vaddr = %p\n", pci_dev->mem_resource[0].addr);
    if (adapter->DEVRDY < 2) {
        pc802_bar_memset((uint32_t *)((char *)bar+PC802_CACHE_LINE_SZ), 0, (pci_dev->mem_resource[0].len - PC802_CACHE_LINE_SZ) / sizeof(uint32_t));
        DBLOG("Finish clearing reset of BAR 0\n");
        rte_mb();
    }

    printf( "PC802 Log level: PRINT=%d, EVENT=%d, VEC=%d\n", pc802_log_get_level(PC802_LOG_PRINT),
        pc802_log_get_level(PC802_LOG_EVENT), pc802_log_get_level(PC802_LOG_VEC) );
    adapter->log_flag = 0;
    adapter->port_index = num_pc802s-1;

#if 0
    if ((RTE_LOG_EMERG != pc802_log_get_level(PC802_LOG_PRINT)) && (NULL != pci_dev->mem_resource[1].addr)) {
        DBLOG("PC802_BAR[1].vaddr = %p\n", pci_dev->mem_resource[1].addr);
        if (adapter->DEVRDY < 2) {
            pc802_bar_memset((uint32_t *)pci_dev->mem_resource[1].addr, 0, pci_dev->mem_resource[1].len / sizeof(uint32_t));
            DBLOG("Finish clearing BAR 1\n");
        }
        DBLOG("PC802_BAR[2].vaddr = %p\n", pci_dev->mem_resource[2].addr);
        if (adapter->DEVRDY < 2) {
            pc802_bar_memset((uint32_t *)pci_dev->mem_resource[2].addr, 0, pci_dev->mem_resource[2].len / sizeof(uint32_t));
            DBLOG("Finish clearing BAR 2\n");
        }
        rte_mb();

        adapter->mailbox_info_pfi = (mailbox_info_exclusive *)((uint8_t*)pci_dev->mem_resource[1].addr);
        adapter->mailbox_pfi   = (mailbox_exclusive *)((uint8_t *)pci_dev->mem_resource[1].addr + 0x580);
        adapter->mailbox_ecpri = (mailbox_exclusive *)((uint8_t *)pci_dev->mem_resource[2].addr);
        adapter->mailbox_info_ecpri = (mailbox_info_exclusive *)((uint8_t *)pci_dev->mem_resource[2].addr + sizeof(mailbox_exclusive) * 16);
        for (dsp = 0; dsp < 3; dsp++) {
            adapter->mailbox_dsp[dsp] = (mailbox_exclusive *)((uint8_t *)pci_dev->mem_resource[0].addr + 0x2000 + 0x400 * dsp);
        }
        adapter->log_flag |= (1<<PC802_LOG_PRINT);
    } else {
        PC802_WRITE_REG(bar->MB_ANDES_DIS, 0xFFFFFFFF);
        PC802_WRITE_REG(bar->MB_DSP_DIS, 0x7);
        rte_wmb();
        DBLOG("WARN: No PCIe based printf output !\n");
    }
#else
    adapter->log_flag |= (1<<PC802_LOG_PRINT);
#endif

    int socket_id = eth_dev->device->numa_node;
    uint32_t tsize = PC802_DEBUG_BUF_SIZE;
    const struct rte_memzone *mz;

    sprintf(temp_name, "PC802DBG%d", data->port_id );
    mz = rte_memzone_reserve_aligned(temp_name, tsize, socket_id, RTE_MEMZONE_IOVA_CONTIG, 0x10000);
    if (mz == NULL) {
        DBLOG("ERROR: fail to mem zone reserve size = %u\n", tsize);
        return -ENOMEM;
    }
    adapter->dbg = mz->addr;
    adapter->dgb_phy_addrH = (uint32_t)(mz->iova >> 32);
    adapter->dgb_phy_addrL = (uint32_t)mz->iova;
    PC802_WRITE_REG(bar->DBGRCAL, adapter->dgb_phy_addrL);
    PC802_WRITE_REG(bar->DBGRCAH, adapter->dgb_phy_addrH);
    adapter->dbg_rccnt = PC802_READ_REG(bar->DBGRCCNT);
    DBLOG("DEBUG NPU Memory = 0x%08X %08X\n", bar->DBGRCAH, bar->DBGRCAL);

    PC802_WRITE_REG(bar->SFN_SLOT_0, 0xFFFFFFFF);
    PC802_WRITE_REG(bar->SFN_SLOT_1, 0xFFFFFFFF);

    if (RTE_LOG_EMERG != pc802_log_get_level(PC802_LOG_EVENT)) {
        adapter->log_flag  |= (1<<PC802_LOG_EVENT);
    }

    tsize = sizeof(PC802_Descs_t);
    sprintf(temp_name, "PC802_DESCS_MR%d", data->port_id );
    mz = rte_memzone_reserve_aligned(temp_name, tsize, eth_dev->data->numa_node,
            RTE_MEMZONE_IOVA_CONTIG, 0x10000);
    if (mz == NULL) {
        DBLOG("ERROR: fail to mem zone reserve size = %u\n", tsize);
        return -ENOMEM;
    }
    memset(mz->addr, 0, tsize);
    adapter->pDescs = (PC802_Descs_t *)mz->addr;
    adapter->descs_phy_addr = mz->iova;
    DBLOG("descs_phy_addr  = 0x%lX\n", adapter->descs_phy_addr);
    DBLOG("descs_virt_addr = %p\n", adapter->pDescs);

    uint32_t haddr = (uint32_t)(adapter->descs_phy_addr >> 32);
    uint32_t laddr = (uint32_t)adapter->descs_phy_addr;
    PC802_WRITE_REG(bar->DBAL, laddr);
    PC802_WRITE_REG(bar->DBAH, haddr);
    DBLOG("Descriptor Rings Base = 0x%08X %08X\n", bar->DBAH, bar->DBAL);

    PC802_WRITE_REG(bar->DEVEN, 0);
    DBLOG("NPU clear PC802 prot %d DEVEN = 0\n", adapter->port_id);
    usleep(1000);

    adapter->started = 1;

    PMD_INIT_LOG(DEBUG, "port_id %d vendorID=0x%x deviceID=0x%x",
             eth_dev->data->port_id, pci_dev->id.vendor_id,
             pci_dev->id.device_id);

    pc802_init_c2h_mailbox(adapter);

    if (1 == num_pc802s) {
        pthread_t tid;
        mkfifo(FIFO_PC802_VEC_ACCESS, S_IRUSR | S_IWUSR);
        pc802_ctrl_thread_create(&tid, "PC802-Trace", NULL, pc802_trace_thread, NULL);
        pc802_ctrl_thread_create(&tid, "PC802-Debug", NULL, pc802_debug, NULL);
        pc802_ctrl_thread_create(&tid, "PC802-Vec", NULL, pc802_vec_access, NULL);
        pc802_pdump_init( );
    }

    pc802_download_boot_image(data->port_id);

    if ( pc802_log_get_level(PC802_LOG_VEC)>=(int)RTE_LOG_INFO ) {
        adapter->log_flag  |= (1<<PC802_LOG_VEC);
    }

    return 0;
}

static int
eth_pc802_dev_uninit(struct rte_eth_dev *eth_dev)
{
    //struct rte_pci_device *pci_dev = RTE_ETH_DEV_TO_PCI(eth_dev);
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(eth_dev->data->dev_private);

    PMD_INIT_FUNC_TRACE();

    if (rte_eal_process_type() != RTE_PROC_PRIMARY)
        return -EPERM;

    adapter->started = 0;

    return 0;
}

static int eth_pc802_pci_probe(struct rte_pci_driver *pci_drv __rte_unused,
    struct rte_pci_device *pci_dev)
{
    return rte_eth_dev_pci_generic_probe(pci_dev,
        sizeof(struct pc802_adapter), eth_pc802_dev_init);
}

static int eth_pc802_pci_remove(struct rte_pci_device *pci_dev)
{
    return rte_eth_dev_pci_generic_remove(pci_dev, eth_pc802_dev_uninit);
}

static struct rte_pci_driver rte_pc802_pmd = {
    .id_table = pci_id_pc802_map,
    .drv_flags = RTE_PCI_DRV_NEED_MAPPING | RTE_PCI_DRV_INTR_LSC,
    .probe = eth_pc802_pci_probe,
    .remove = eth_pc802_pci_remove,
};

RTE_PMD_REGISTER_PCI(net_pc802, rte_pc802_pmd);
RTE_PMD_REGISTER_PCI_TABLE(net_pc802, pci_id_pc802_map);
RTE_PMD_REGISTER_KMOD_DEP(net_pc802, "* igb_uio | uio_pci_generic | vfio-pci");

/* see e1000_logs.c */
RTE_INIT(picocom_pc802_init_log)
{
    printf( "%s on NPU side built AT %s ON %s\n", picocom_pc802_version(), __TIME__, __DATE__ );
    pc802_init_log();
}

char * picocom_pc802_version(void)
{
    static char ver[256];
    snprintf(ver, sizeof(ver), "PC802 Driver %s", PC802_UDRIVER_VERSION);
    return ver;
}

static FILE * get_image_file(uint16_t port, const char *image_name)
{
    char *path[] = {DEFAULT_IMAGE_PATH, CUR_PATH};
    char file_name[PATH_MAX];
    uint16_t index = pc802_get_port_index(port);
    uint32_t i;
    FILE *fp = NULL;

    for (i = 0; i < RTE_DIM(path); i++) {
        sprintf(file_name, "%s/pc802_%d/%s", path[i], index, image_name);
        if (NULL != (fp = fopen(file_name, "rb")))
            break;

        sprintf(file_name, "%s/%s", path[i], image_name);
        if (NULL != (fp = fopen(file_name, "rb")))
            break;
    }
    DBLOG("Prepare pc802 %d image file:%s\n", index, file_name);
    return fp;
}

static int pc802_download_boot_image(uint16_t port)
{
    PC802_BAR_t *bar = pc802_get_BAR(port);
    volatile uint32_t *BOOTRCCNT = &bar->BOOTRCCNT;
    volatile uint32_t *BOOTEPCNT = &bar->BOOTEPCNT;
    volatile uint32_t devRdy;

    DBLOG("Begin pc802_download_boot_image,  port = %hu\n", port);
    if (0xFFFFFFFF == *BOOTRCCNT) {
        DBLOG("PC802 ELF image has already been downloaded and is running !\n");
        return 0;
    }

    DBLOG("Wait for BOOTING DEVRDY 1 ...\n");
    do {
        usleep(1);
        devRdy = PC802_READ_REG(bar->DEVRDY);
    } while (devRdy<1);
    DBLOG( "DRVSTATE=%d, DEVRDY=%d. Begin download ssbl(port=%hu) ...\n",
        PC802_READ_REG(bar->DRVSTATE), devRdy, port );

    *BOOTRCCNT = 0;
    const struct rte_memzone *mz;
    uint32_t tsize = 64 * 1024;
    int socket_id = pc802_get_socket_id(port);
    mz = rte_memzone_reserve_aligned("PC802_BOOT", tsize, socket_id,
            RTE_MEMZONE_IOVA_CONTIG, 64);
    if (NULL == mz) {
        DBLOG("ERROR: fail to mem zone reserve size = %u\n", tsize);
        return -ENOMEM;
    }

    uint8_t *pimg = (uint8_t *)mz->addr;

    FILE *fp = get_image_file(port, "pc802.ssbl");
    if (NULL==fp) {
        DBLOG("Failed to open pc802.ssbl .\n");
        return -1;
    }

    bar->BOOTSRCL = (uint32_t)(mz->iova);
    bar->BOOTSRCH = (uint32_t)(mz->iova >> 32);
    bar->BOOTDST  = 0;
    bar->BOOTSZ = 0;
    uint32_t N, sum;
    sum = 0;
    do {
        N = fread(pimg, 1, tsize, fp);
        if (N < 4)
            break;
        rte_wmb();
        (*BOOTRCCNT)++;
        while(*BOOTRCCNT != *BOOTEPCNT)
            usleep(1);
        sum += N;
        printf("\rBAR->BOOTRCCNT = %u  Finish downloading %u bytes", bar->BOOTRCCNT, sum);
        N = 0;
    } while (1);
    printf("\n");

    *BOOTRCCNT = 0xFFFFFFFF; //wrtite BOOTRCCNT=-1 to make FSBL finish downloading SSBL.
    fclose(fp);
    DBLOG("Finish dowloading SSBL !\n");

    DBLOG("Waiting for PC802 SSBL boot(DEVRDY=2) ...\n");
    do {
        devRdy = PC802_READ_REG(bar->DEVRDY);
    } while (devRdy<2);
    *BOOTRCCNT = 0x0;
    DBLOG( "DRVSTATE=%d, DEVRDY=%d.\n", PC802_READ_REG(bar->DRVSTATE), devRdy );

    do {
        usleep(1);
        devRdy = PC802_READ_REG(bar->DEVRDY);
    } while (devRdy<3);
    DBLOG( "DRVSTATE=%d, DEVRDY=%d. Begin download application(port=%hu) ... \n",
        PC802_READ_REG(bar->DRVSTATE), devRdy, port );

    fp = get_image_file(port, "pc802.img");
    if (NULL==fp) {
        DBLOG("Failed to open pc802.img .\n");
        return -1;
    }

    sum = 0;
    do {
        N = fread(pimg, 1, tsize, fp);
        if (N < 4) {
            break;
        }
        rte_wmb();
        (*BOOTRCCNT)++;
        while(*BOOTRCCNT != *BOOTEPCNT)
            usleep(1);
        sum += N;
        printf("\rBAR->BOOTRCCNT = %u  Finish downloading %u bytes", bar->BOOTRCCNT, sum);
        N = 0;
    } while (1);
    *BOOTRCCNT = 0xFFFFFFFF; //write BOOTRCCNT=-1 to notify SSBL complete downaloding the 3rd stage image.
    printf("\nFinish downloading the 3rd stage image !\n");

    rte_memzone_free(mz);
    fclose(fp);

    printf("Finish pc802 download image !\n");
    return 0;
}

int pc802_set_ul_dma_count(uint16_t port, uint32_t n)
{
    PC802_BAR_t *bar = pc802_get_BAR(port);
    if (0 == n)
        n = 1;
    if (n > 4)
        n = 4;
    bar->ULDMAN = n;
    rte_wmb();
    return 0;
}

int pc802_check_dma_timeout(uint16_t port)
{
    static uint32_t timeout_counter[16];
    static const char *head[] = {"PC802 UL Timeout FINISHED:", "PC802 UL Timeout ERROR:",
        "PC802 DL Timeout FINISHED:", "PC802 DL Timeout ERROR:"};
    uint32_t *local_counter;
    uint32_t *bar_counter;
    char buf[1024];
    char *p;
    int flag;
    int m, n;

    flag= 0;
    p = buf;
    local_counter = &timeout_counter[0];
    PC802_BAR_t *bar = pc802_get_BAR(port);
    bar_counter = &bar->ULDMA_TIMEOUT_FINISHED[0];
    for (m = 0; m < 4; m++) {
        flag = 0;
        for (n = 0; n < 4; n++) {
            if (local_counter[0] != bar_counter[0]) {
                local_counter[0] = bar_counter[0];
                if (0 == flag) {
                    p += sprintf(p, "%s", head[m]);
                    flag = 1;
                }
                p += sprintf(p, " [%1d]=%10u", n, bar_counter[0]);
            }
            local_counter++;
            bar_counter++;
        }
        if (flag)
            p += sprintf(p, "\n");
    }
    if (p != buf)
        printf("%s", buf);
    return 0;
}

#define PC802_BAR_EXT_OFFSET  (4 * 1024)

static PC802_BAR_Ext_t * pc802_get_BAR_Ext(uint16_t port)
{
    PC802_BAR_t *bar = pc802_get_BAR(port);
    uint8_t *pu8 = ((uint8_t *)bar) + PC802_BAR_EXT_OFFSET;
    PC802_BAR_Ext_t *ext = (PC802_BAR_Ext_t *)pu8;
    return ext;
}

static char *get_vector_file_name(uint16_t port_id, uint32_t file_id, char *file_name)
{
    char *path[] = {getenv("PC802_TEST_VECTOR_DIR"), DEFAULT_IMAGE_PATH, CUR_PATH};
    uint16_t pc802_index = pc802_get_port_index(port_id);
    uint32_t i;

    for (i = 0; i < RTE_DIM(path); i++) {
        if (NULL != path[i]) {
            sprintf(file_name, "%s/pc802_%d/%u.txt", path[i], pc802_index, file_id);
            if (0 == access(file_name, F_OK))
                return file_name;

            sprintf(file_name, "%s/%u.txt", path[i], file_id);
            if (0 == access(file_name, F_OK))
                return file_name;
        }
    }

    return NULL;
}

static char * get_vector_path(uint16_t port_id, char *file_path)
{
    char *path[] = {getenv("PC802_VECTOR_DUMP_DIR"), DEFAULT_IMAGE_PATH, CUR_PATH};
    uint16_t pc802_index = pc802_get_port_index(port_id);
    uint32_t i;

    for (i = 0; i < RTE_DIM(path); i++) {
        if (NULL != path[i]) {
            sprintf(file_path, "%s/pc802_%d", path[i], pc802_index);
            if (0 == access(file_path, W_OK))
                return file_path;

            sprintf(file_path, "%s", path[i]);
            if (0 == access(file_path, W_OK))
                return file_path;
        }
    }

    strcpy(file_path, ".");
    return file_path;
}

static uint32_t handle_pfi_0_vec_read(uint16_t port_id, uint32_t file_id, uint32_t offset, uint32_t address, uint32_t length)
{
    unsigned int end = offset + length;
    if ((offset & 3) | (length & 3) | (address & 3)) {
        DBLOG("ERROR: VEC_READ address, offset and length must be word aligned!\n");
        return -1;
    }

    char file_name[PATH_MAX];
    if ( NULL == get_vector_file_name(port_id, file_id, file_name) ) {
        DBLOG("ERROR: Vector %d file not found.\n", file_id);
        return -2;
    }

    // Parse the file
    DBLOG("PC802 %d reading vector file %s %u bytes.\n", port_id, file_name, length);
    unsigned int   data       = 0;
    unsigned int   vec_cnt = 0;
    unsigned int   line = 0;
    FILE         * fh_vector  = fopen(file_name, "r");
    char           buffer[2048];
    uint32_t       *pd;
    uint32_t       data_size;
    uint32_t       buf_full;

__next_pfi_0_vec_read:
    pd = (uint32_t *)pc802_get_debug_mem(port_id);
    data_size = 0;
    buf_full = 0;
    while ((0 == buf_full) && (fgets(buffer, sizeof(buffer), fh_vector) != NULL)) {
        // Trim trailing newlines
        buffer[strcspn(buffer, "\r\n")] = 0;
        if (sscanf(buffer, "%x", &data) == 1) {
            // In scope
            if (vec_cnt >= offset && vec_cnt < end) {
                *pd++ = data;
                data_size += sizeof(uint32_t);
                buf_full = (data_size >= PC802_DEBUG_BUF_SIZE);
            }
            vec_cnt += 4;
        } else if (buffer[0] != '#' && strlen(buffer) > 0) { // Allow for comment character '#'
            DBLOG("ERROR: Unexpected entry parsing line %u of %s: %s", line, file_name, buffer);
            return -4;
        }
        // already done
        if (vec_cnt >= end) {
            break;
        }
        // Increment line count
        line++;
    }

    if ((0 == buf_full) && (vec_cnt < end)) {
        DBLOG("ERROR: EOF! of %s line %u\n", file_name, vec_cnt);
        return -5;
    }

    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    PC802_BAR_Ext_t *ext = pc802_get_BAR_Ext(adapter->port_id);
    PC802_WRITE_REG(ext->VEC_BUFADDRH, adapter->dgb_phy_addrH);
    PC802_WRITE_REG(ext->VEC_BUFADDRL, adapter->dgb_phy_addrL);
    PC802_WRITE_REG(ext->VEC_BUFSIZE, data_size);
    uint32_t vec_rccnt;
    volatile uint32_t vec_epcnt;
    vec_rccnt = PC802_READ_REG(ext->VEC_RCCNT);
    vec_rccnt++;
    PC802_WRITE_REG(ext->VEC_RCCNT, vec_rccnt);
    do {
        usleep(1);
        vec_epcnt = PC802_READ_REG(ext->VEC_EPCNT);
    } while (vec_epcnt != vec_rccnt);

    if (vec_cnt < end)
        goto __next_pfi_0_vec_read;

    fclose(fh_vector);

    DBLOG("Loaded a total of %u bytes from %s\n", length, file_name);
    return 0;
}

// -----------------------------------------------------------------------------
// handle_vec_dump: Handle task vector dump requests
// -----------------------------------------------------------------------------
static uint32_t handle_pfi_0_vec_dump(uint16_t port_id, uint32_t file_id, uint32_t address, uint32_t length)
{
    unsigned int offset;
    if ((length & 3) | (address & 3)) {
       DBLOG("ERROR: VEC_DUMP address and length must be word aligned!\n");
       return -1;
    }

    // Check if the golden vector file exists
    char file_path[PATH_MAX];
    char file_name[PATH_MAX+NAME_MAX];
    get_vector_path(port_id, file_path);
    sprintf(file_name, "%s/%u.txt", file_path, file_id);

    DBLOG("PC802 %d dumping to file %s\n", port_id, file_name);
    FILE         * fh_vector  = fopen(file_name, "w");
    fprintf(fh_vector, "#@%08x, length=%d\n", address, length);
    uint32_t left = length;
    uint32_t data_size;

    struct rte_eth_dev *dev = &rte_eth_devices[port_id];
    struct pc802_adapter *adapter =
        PC802_DEV_PRIVATE(dev->data->dev_private);
    PC802_BAR_Ext_t *ext = pc802_get_BAR_Ext(adapter->port_id);
    uint32_t vec_rccnt;
    vec_rccnt = PC802_READ_REG(ext->VEC_RCCNT);
    PC802_WRITE_REG(ext->VEC_BUFADDRH, adapter->dgb_phy_addrH);
    PC802_WRITE_REG(ext->VEC_BUFADDRL, adapter->dgb_phy_addrL);

    uint32_t *pd;
__next_pfi_0_vec_dump:
    pd = (uint32_t *)adapter->dbg;
    data_size = (left < PC802_DEBUG_BUF_SIZE) ? left : PC802_DEBUG_BUF_SIZE;
    PC802_WRITE_REG(ext->VEC_BUFSIZE, data_size);
    vec_rccnt++;
    PC802_WRITE_REG(ext->VEC_RCCNT, vec_rccnt);
    volatile uint32_t vec_epcnt;
    do {
        usleep(1);
        vec_epcnt = PC802_READ_REG(ext->VEC_EPCNT);
    } while (vec_epcnt != vec_rccnt);

    for (offset = 0; offset < data_size; offset += 4) {
        unsigned int mem_data = *pd++;;
        fprintf(fh_vector, "%08x\n", mem_data);
    }
    left -= data_size;

    if (left > 0)
        goto __next_pfi_0_vec_dump;

    fclose(fh_vector);

    // Print a success message
    DBLOG("Dumped %u bytes at address 0x%08x to file %s.\n",
        length, address, file_name);

    return 0;
}

static uint32_t handle_non_pfi_0_vec_read(uint16_t port_id, uint32_t file_id, uint32_t offset, uint32_t address, uint32_t length)
{
    unsigned int end = offset + length;
    if ((offset & 3) | (length & 3) | (address & 3)) {
        DBLOG("ERROR: VEC_READ address, offset and length must be word aligned!\n");
        return -1;
    }

    char file_name[PATH_MAX];
    if ( NULL == get_vector_file_name( port_id, file_id, file_name) ) {
        DBLOG("ERROR: Vector %d file not found.\n", file_id);
        return -2;
    }

    // Parse the file
    DBLOG("PC802 %d reading vector file %s %u bytes.\n", port_id, file_name, length);
    unsigned int   data       = 0;
    unsigned int   vec_cnt = 0;
    unsigned int   line = 0;
    FILE         * fh_vector  = fopen(file_name, "r");
    char           buffer[2048];

    uint32_t *pd;
    uint32_t data_size;
    uint32_t buf_full;

__next_non_pfi_0_vec_read:
    pd = (uint32_t *)pc802_get_debug_mem(port_id);
    data_size = 0;
    buf_full = 0;
    while ((0 == buf_full) && (fgets(buffer, sizeof(buffer), fh_vector) != NULL)) {
        // Trim trailing newlines
        buffer[strcspn(buffer, "\r\n")] = 0;
        if (sscanf(buffer, "%x", &data) == 1) {
            // In scope
            if (vec_cnt >= offset && vec_cnt < end) {
                *pd++ = data;
                data_size += sizeof(uint32_t);
                buf_full = (data_size >= PC802_DEBUG_BUF_SIZE);
            }
            vec_cnt += 4;
        } else if (buffer[0] != '#' && strlen(buffer) > 0) { // Allow for comment character '#'
            DBLOG("ERROR: Unexpected entry parsing line %u of %s: %s", line, file_name, buffer);
            return -4;
        }
        // already done
        if (vec_cnt >= end) {
            break;
        }
        // Increment line count
        line++;
    }

    if ((0 == buf_full) && (vec_cnt < end)) {
        DBLOG("ERROR: EOF! of %s line %u\n", file_name, vec_cnt);
        return -5;
    }

    PC802_BAR_t *bar = pc802_get_BAR(port_id);
    PC802_WRITE_REG(bar->DBGEPADDR, address);
    PC802_WRITE_REG(bar->DBGBYTESNUM, length);
    PC802_WRITE_REG(bar->DBGCMD, DIR_PCIE_DMA_DOWNLINK);
    uint32_t RCCNT = PC802_READ_REG(bar->DBGRCCNT);
    RCCNT++;
    PC802_WRITE_REG(bar->DBGRCCNT, RCCNT);
    volatile uint32_t EPCNT;
    do {
        usleep(1);
        EPCNT = PC802_READ_REG(bar->DBGEPCNT);
    } while (EPCNT != RCCNT);

    if (vec_cnt < end) {
        address += data_size;
        goto __next_non_pfi_0_vec_read;
    }

    fclose(fh_vector);
    DBLOG("Loaded a total of %u bytes from %s\n", length, file_name);
    return 0;
}

// -----------------------------------------------------------------------------
// handle_vec_dump: Handle task vector dump requests
// -----------------------------------------------------------------------------
static uint32_t handle_non_pfi_0_vec_dump(uint16_t port_id, uint32_t file_id, uint32_t address, uint32_t length)
{
    unsigned int offset;
    if ((length & 3) | (address & 3)) {
       DBLOG("ERROR: VEC_DUMP address and length must be word aligned!\n");
       return -1;
    }

    char file_path[PATH_MAX];
    char file_name[PATH_MAX+NAME_MAX];
    get_vector_path(port_id, file_path);
    sprintf(file_name, "%s/%u.txt", file_path, file_id);

    // Parse the file
    DBLOG("PC802 %d dumping to file %s\n", port_id, file_name);
    FILE         * fh_vector  = fopen(file_name, "w");
    fprintf(fh_vector, "#@%08x, length=%d\n", address, length);

    PC802_BAR_t *bar = pc802_get_BAR(port_id);
    uint32_t RCCNT = PC802_READ_REG(bar->DBGRCCNT);

    uint32_t left = length;
    uint32_t data_size;

__next_non_pfi_0_vec_dump:
    PC802_WRITE_REG(bar->DBGEPADDR, address);
    data_size = (left < PC802_DEBUG_BUF_SIZE) ? left : PC802_DEBUG_BUF_SIZE;
    PC802_WRITE_REG(bar->DBGBYTESNUM, data_size);
    PC802_WRITE_REG(bar->DBGCMD, DIR_PCIE_DMA_UPLINK);
    RCCNT++;
    PC802_WRITE_REG(bar->DBGRCCNT, RCCNT);
    volatile uint32_t EPCNT;
    do {
        usleep(1);
        EPCNT = PC802_READ_REG(bar->DBGEPCNT);
    } while (EPCNT != RCCNT);

    uint32_t *pd = (uint32_t *)pc802_get_debug_mem(port_id);
    for (offset = 0; offset < data_size; offset += 4) {
        unsigned int mem_data = *pd++;;
        fprintf(fh_vector, "%08x\n", mem_data);
    }
    left -= data_size;
    if (left > 0) {
        address += data_size;
        goto __next_non_pfi_0_vec_dump;
    }

    fclose(fh_vector);

    // Print a success message
    DBLOG("Dumped %u bytes at address 0x%08x to file %s.\n",
        length, address, file_name);

    return 0;
}

uint32_t pc802_vec_read(uint16_t port_id, uint32_t file_id, uint32_t offset, uint32_t address, uint32_t length)
{
    return handle_non_pfi_0_vec_read(port_id, file_id, offset, address, length);
}

uint32_t pc802_vec_dump(uint16_t port_id, uint32_t file_id, uint32_t address, uint32_t length)
{
    return handle_non_pfi_0_vec_dump(port_id, file_id, address, length);
}

typedef struct stMbVecAccess_t {
    uint32_t command;
    uint32_t file_id;
    uint32_t offset;
    uint32_t address;
    uint32_t length;
    uint16_t port_id;
    uint16_t core;
} MbVecAccess_t;

#define PC802_VEC_ACCESS_IDLE   0
#define PC802_VEC_ACCESS_WORK   1
#define PC802_VEC_ACCESS_DONE   2

static uint8_t pc802_vec_blocked[PC802_INDEX_MAX][36];
union {
    uint32_t rccnts[PC802_INDEX_MAX][9];
    uint8_t  rccnt[PC802_INDEX_MAX][36];
} pc802_mb_rccnt;
#define pc802_mailbox_rc_counter        pc802_mb_rccnt.rccnt
#define pc802_mb_rccnts                 pc802_mb_rccnt.rccnts

static uint32_t pc802_vec_access_msg_send(int fd, MbVecAccess_t *msg)
{
    return (write(fd, msg, sizeof(*msg)));
}

static uint32_t pc802_vec_access_msg_recv(int fd, MbVecAccess_t *msg)
{
    uint8_t *c;
    uint32_t m;
    uint32_t n;

    c = (uint8_t *)msg;
    m = sizeof(MbVecAccess_t);
    while (m > 0) {
        n = read(fd, c, m);
        c += n;
        m -= n;
    }
    return sizeof(MbVecAccess_t);
}

static void pc802_write_mailbox_reg(PC802_BAR_Ext_t *ext, uint16_t core, uint8_t rccnt, uint8_t result)
{
    union {
        uint32_t _mb_pfi[8];
        Mailbox_RC_t MB_PFI[16];
        uint32_t _mb_ecpri[8];
        Mailbox_RC_t MB_eCPRI[16];
        uint32_t _mb_dsp[8];
        Mailbox_RC_t MB_DSP[3];
    } regs;

    uint32_t idx;
    if (core < 16) {
        idx = core / 2;
        regs._mb_pfi[idx] = PC802_READ_REG(ext->_mb_pfi[idx]);
        regs.MB_PFI[core].result = result;
        regs.MB_PFI[core].rccnt = rccnt;
        PC802_WRITE_REG(ext->_mb_pfi[idx], regs._mb_pfi[idx]);
    } else if (core < 32) {
        idx = (core - 16) / 2;
        regs._mb_ecpri[idx] = PC802_READ_REG(ext->_mb_ecpri[idx]);
        regs.MB_eCPRI[core - 16].result = result;
        regs.MB_eCPRI[core - 16].rccnt = rccnt;
        PC802_WRITE_REG(ext->_mb_ecpri[idx], regs._mb_ecpri[idx]);
    } else {
        idx = (core - 32) / 2;
        regs._mb_dsp[idx] = PC802_READ_REG(ext->_mb_dsp[idx]);
        regs.MB_DSP[core - 32].result = result;
        regs.MB_DSP[core - 32].rccnt = rccnt;
        PC802_WRITE_REG(ext->_mb_dsp[idx], regs._mb_dsp[idx]);
    }
}

static void * pc802_vec_access(__rte_unused void *data)
{
    MbVecAccess_t msg;
    int fd;
    uint32_t command;
    uint32_t re;
    uint16_t port_idx;
    uint8_t result;

    (void)data;

    fd = open(FIFO_PC802_VEC_ACCESS, O_RDONLY, 0);
    while (1) {
        pc802_vec_access_msg_recv(fd, &msg);
        PC802_BAR_Ext_t *ext = pc802_get_BAR_Ext(msg.port_id);
        port_idx = pc802_get_port_index(msg.port_id);
        command = msg.command;
        if (0 == msg.core) {
            pc802_mailbox_rc_counter[port_idx][0]++;
            pc802_write_mailbox_reg(ext, 0, pc802_mailbox_rc_counter[port_idx][0], 2);
            if (MB_VEC_READ == command) {
                re = handle_pfi_0_vec_read(msg.port_id, msg.file_id, msg.offset, msg.address, msg.length);
            } else if (MB_VEC_DUMP == command) {
                re = handle_pfi_0_vec_dump(msg.port_id, msg.file_id, msg.address, msg.length);
            }
        } else {
            DBLOG("Bigin vec_access: core = %2u command = %2u file_id = %u offset = %u address = 0x%08X length = %u\n",
                msg.core, command, msg.file_id, msg.offset, msg.address, msg.length);
            if (MB_VEC_READ == command) {
                re = handle_non_pfi_0_vec_read(msg.port_id, msg.file_id, msg.offset, msg.address, msg.length);
            } else if (MB_VEC_DUMP == command) {
                re = handle_non_pfi_0_vec_dump(msg.port_id, msg.file_id, msg.address, msg.length);
            }
            DBLOG("End   vec_access: core = %2u command = %2u file_id = %u\n", msg.core, command, msg.file_id);
            pc802_mailbox_rc_counter[port_idx][msg.core]++;
        }
        result = (0 == re);
        pc802_write_mailbox_reg(ext, msg.core, pc802_mailbox_rc_counter[port_idx][msg.core], result);
        pc802_vec_blocked[pc802_get_port_index(msg.port_id)][msg.core] = PC802_VEC_ACCESS_IDLE;
    }

    return 0;
}

static int trace_action_type[PC802_INDEX_MAX][32];
static uint32_t trace_datas[PC802_INDEX_MAX][32][16];
static uint32_t trace_num_args[PC802_INDEX_MAX][32];
static uint32_t trace_idx[PC802_INDEX_MAX][32];

enum {
    TRACE_ACTION_GENERIC,
    TRACE_ACTION_PRINTF,
    TRACE_ACTION_IDLE = 0xFFFFFFFF
};

static void handle_mb_printf(uint16_t port_id, magic_mailbox_t *mb, uint32_t core, uint32_t cause);

static void handle_trace_printf(uint16_t port_idx, uint32_t core, uint32_t tdata)
{
    int k;
    if (0 == trace_num_args[port_idx][core]) {
        trace_idx[port_idx][core] = 0;
        trace_num_args[port_idx][core] = tdata;
        return;
    }

    trace_datas[port_idx][core][trace_idx[port_idx][core]] = tdata;
    trace_idx[port_idx][core]++;
    if (trace_idx[port_idx][core] == trace_num_args[port_idx][core]) {
        magic_mailbox_t mb;
        mb.num_args = trace_num_args[port_idx][core];
        for (k = 0; k < mb.num_args; k++)
            mb.arguments[k] = trace_datas[port_idx][core][k];
        handle_mb_printf(port_idx, &mb, core, 0);
        trace_num_args[port_idx][core] = 0;
        trace_idx[port_idx][core] = 0;
        trace_action_type[port_idx][core] = TRACE_ACTION_IDLE;
    }
}

static inline void handle_trace_data(uint16_t port_idx, uint32_t core, uint32_t rccnt, uint32_t tdata)
{
    //PC802_LOG( port_idx, core, RTE_LOG_NOTICE, "event[%.5u]: 0x%.8X(0x%.5X, %.4d)\n", rccnt, tdata, tdata>>14, tdata&0x3FFF );
    if (TRACE_ACTION_IDLE == trace_action_type[port_idx][core]) {
        trace_action_type[port_idx][core] = tdata;
        return;
    }

    if (TRACE_ACTION_GENERIC == trace_action_type[port_idx][core]) {
        PC802_LOG(port_idx, core, RTE_LOG_NOTICE, "event[%.5u]: 0x%.8X(0x%.5X, %.4d)\n", rccnt, tdata, tdata>>14, tdata&0x3FFF );
        trace_action_type[port_idx][core] = TRACE_ACTION_IDLE;
        return;
    }

    if (TRACE_ACTION_PRINTF == trace_action_type[port_idx][core]) {
        handle_trace_printf(port_idx, core, tdata);
    }
}

static int pc802_tracer( uint16_t port_index, uint16_t port_id )
{
    static uint32_t rccnt[PC802_INDEX_MAX][32] = {0};
    static PC802_BAR_Ext_t *ext[PC802_INDEX_MAX] = {NULL};
    int num = 0;
    uint32_t core;
    uint32_t idx;
    uint32_t trc_data;
    volatile uint32_t epcnt;

    if (NULL == ext[port_index]) {
        ext[port_index] = pc802_get_BAR_Ext(port_id);
        for (core = 0; core < 32; core++) {
            rccnt[port_index][core] = PC802_READ_REG(ext[port_index]->TRACE_RCCNT[core]);
        }
    }

    for (core = 0; core < 32; core++) {
        epcnt = PC802_READ_REG(ext[port_index]->TRACE_EPCNT[core].v);
        while (rccnt[port_index][core] != epcnt) {
            idx = rccnt[port_index][core] & (PC802_TRACE_FIFO_SIZE - 1);
            trc_data = PC802_READ_REG(ext[port_index]->TRACE_DATA[core].d[idx]);
            handle_trace_data(port_index, core, rccnt[port_index][core], trc_data);
            rccnt[port_index][core]++;
            num++;
        }
        if ( num>0 )
        {
            rte_wmb();
            PC802_WRITE_REG(ext[port_index]->TRACE_RCCNT[core], rccnt[port_index][core]);
        }
    }

    return num;
}

static void handle_mb_printf(uint16_t port_id, magic_mailbox_t *mb, uint32_t core, uint32_t cause)
{
    uint32_t num_args = mb->num_args;
    char str[2048];
    char formatter[16];
    const char *arg0 = mb_get_string(mb->arguments[0], core);
    const char *arg0_bak = arg0;
    char *ps = &str[0];
    uint32_t arg_idx = 1;
    const char *sub_str;
    uint32_t j;

    if (cause) {
        ps += sprintf(ps, "PRINTF: ");
    } else {
        ps += sprintf(ps, "TRCLOG: ");
   }
    while (*arg0) {
        if (*arg0 == '%') {
            formatter[0] = '%';
            arg0++;
            j = 1;
            do {
                assert(j < 15);
                formatter[j] = *arg0++;
                if (isalpha(formatter[j])) {
                    formatter[j+1] = 0;
                    break;
                }
                j++;
            } while (1);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
            if (formatter[j] == 's') {
                sub_str = mb_get_string(mb->arguments[arg_idx++], core);
                ps += snprintf(ps, sizeof(str), formatter, sub_str);
            } else {
                ps += snprintf(ps, sizeof(str), formatter, mb->arguments[arg_idx++]);
            }
#pragma GCC diagnostic pop

        } else {
            *ps++ = *arg0++;
        }
    }
    *ps = 0;
    if (arg_idx != num_args) {
        DBLOG("core %u (arg_idx = %u num_args = %u): format = %s\n",
            core, arg_idx, num_args, arg0_bak);
        DBLOG("PC802 Core %u printf: %s\n", core, str);
        assert(0);
    }
    PC802_LOG( port_id, core, RTE_LOG_INFO, "%s", str );
    return;
}

static void handle_mb_sim_stop(magic_mailbox_t *mb, uint32_t core)
{
    uint32_t num_args = PC802_READ_REG(mb->num_args);
    if (1 == num_args) {
        DBLOG("EXIT(%u): core %u code %u \n", num_args, core, mb->arguments[0]);
    } else if (3 == num_args) {
        const char *func_name = mb_get_string(mb->arguments[1], core);
        DBLOG("EXIT(%u): core %u code %u function: %s() line %u\n",
            num_args, core, mb->arguments[0], func_name, mb->arguments[2]);
    } else {
        DBLOG("EXIT(%u): core %u args:\n", num_args, core);
        DBLOG("  0x%08X  0x%08X  0x%08X  0x%08X\n", mb->arguments[0], mb->arguments[1],
            mb->arguments[2], mb->arguments[3]);
        DBLOG("  0x%08X  0x%08X  0x%08X  0x%08X\n", mb->arguments[4], mb->arguments[5],
            mb->arguments[6], mb->arguments[7]);
    }
    return;
}

static int handle_mailbox(struct pc802_adapter *adapter, magic_mailbox_t *mb, uint32_t core)
{
    static int fd = -1;
    volatile uint32_t action;
    volatile uint32_t num_args;
    MbVecAccess_t msg;
    uint16_t port_idx;
    uint16_t port_id;

    if (fd < 0) {
        fd = open(FIFO_PC802_VEC_ACCESS, O_WRONLY, 0);
    }

    port_id = adapter->port_id;
    port_idx = pc802_get_port_index(port_id);

    if ((0 != core) && (PC802_VEC_ACCESS_WORK == pc802_vec_blocked[port_idx][core])) {
        return 0;
    }

    action = mb->action;
#if 1
    DBLOG("port_id = %1u core = %2u action = %2u num_args = %1u\n", port_id, core, action, mb->num_args);
#else
    DBLOG("  Arg[0] = 0x%08X [1] = 0x%08X [2] = 0x%08X [3] = 0x%08X\n",
        mb->arguments[0], mb->arguments[1], mb->arguments[2], mb->arguments[3]);
    DBLOG("  Arg[4] = 0x%08X [5] = 0x%08X [6] = 0x%08X [7] = 0x%08X\n",
        mb->arguments[4], mb->arguments[5], mb->arguments[6], mb->arguments[7]);
#endif

    if (MB_EMPTY == action ) {
        return 0;
    } else if (MB_PRINTF == action) {
        handle_mb_printf(port_id, mb, core, 1);
    } else if (MB_SIM_STOP == action) {
        handle_mb_sim_stop(mb, core);
    } else if (MB_VEC_READ == action) {
        msg.command = MB_VEC_READ;
        msg.file_id = mb->arguments[0];
        msg.offset = mb->arguments[1];
        msg.address = mb->arguments[2];
        msg.length = mb->arguments[3];
        msg.port_id = port_id;
        msg.core = core;
        pc802_vec_blocked[port_idx][core] = PC802_VEC_ACCESS_WORK;
        pc802_vec_access_msg_send(fd, &msg);
        return 2;
    } else if (MB_VEC_DUMP == action) {
        msg.command = MB_VEC_DUMP;
        msg.file_id = mb->arguments[0];
        msg.address = mb->arguments[1];
        msg.length = mb->arguments[2];
        msg.port_id = port_id;
        msg.core = core;
        pc802_vec_blocked[port_idx][core] = PC802_VEC_ACCESS_WORK;
        pc802_vec_access_msg_send(fd, &msg);
        return 2;
    } else {
        num_args = mb[0].num_args;
        DBLOG("MB[%2u]: action=%u, num_args=%u, args:\n", core, action, num_args);
        DBLOG("  0x%08X  0x%08X  0x%08X  0x%08X\n", mb[0].arguments[0], mb[0].arguments[1],
            mb[0].arguments[2], mb[0].arguments[3]);
        DBLOG("  0x%08X  0x%08X  0x%08X  0x%08X\n", mb[0].arguments[4], mb[0].arguments[5],
            mb[0].arguments[6], mb[0].arguments[7]);
    }

    return 1;
}

static uint8_t pc802_mailbox_get_rccnt(uint8_t *pRccnt, uint8_t epcnt, uint16_t core)
{
    uint8_t rccnt, used;
    rccnt = *pRccnt;
    used = epcnt - rccnt;
    if (used <= MB_MAX_C2H_MAILBOXES)
        return rccnt;
    DBLOG("Adjust Mailbox RC counter: core %2u ep %3u rc %3u -> %3u\n",
        (uint32_t)core, (uint32_t)epcnt, (uint32_t)rccnt, (uint32_t)(uint8_t)(epcnt - 1));
    rccnt = epcnt - 1;
    *pRccnt = rccnt;
    return rccnt;
}

static int pc802_mailbox(void *data)
{
    static struct pc802_adapter *adapter[PC802_INDEX_MAX] = {NULL};

    uint32_t core;
    uint16_t port_index = ((struct pc802_adapter *)data)->port_index;
    int num = 0;
    int re;
    volatile uint32_t mb_idx;

    if ( adapter[port_index] == NULL )
    {
        adapter[port_index] = (struct pc802_adapter *)data;
        mb_string_init();
        pc802_log_flush();
        DBLOG("come here\n");
    }

    mailbox_exclusive *mbs;
    magic_mailbox_t *mb;
    mailbox_counter_t *mb_cnts;

    PC802_Mem_Block_t *blks[8];
    uint8_t *msg;
    uint16_t n, N;
    uint8_t epcnt, rccnt;

    N = pc802_rx_mblk_burst(adapter[port_index]->port_id, PC802_TRAFFIC_MAILBOX, blks, 8);
#if 1
    if (0 != N) {
        DBLOG("Rx mailbox msg N = %u\n", (uint32_t)N);
    }
#endif

    for (n = 0; n < N; n++) {
        DBLOG("Rx mailbox mb_idx = %1u cause = %1u in %1u of %1u\n",
            (uint32_t)blks[n]->pkt_type, (uint32_t)blks[n]->cause, (uint32_t)n, (uint32_t)N);
        msg = (uint8_t *)blks[n] + sizeof(PC802_Mem_Block_t);
        if (0 == blks[n]->pkt_type) { //PFI
            //if (0 != blks[n]->cause)
            //{
            //    DBLOG("Recved PFI mailbox request in %u of %u, cause = %u\n", (uint32_t)n, (uint32_t)N, (uint32_t)blks[n]->cause);
            //}
            mb_cnts = (mailbox_counter_t *)(msg + MAILBOX_COUNTER_OFFSET_PFI);
            DBLOG("PFI   wrs[0] = 0x%08X [1] = 0x%08X [2] = 0x%08X [3] = 0x%08X\n",
                mb_cnts->wrs[0], mb_cnts->wrs[1], mb_cnts->wrs[2], mb_cnts->wrs[3]);
            DBLOG("PFI   rds[0] = 0x%08X [1] = 0x%08X [2] = 0x%08X [3] = 0x%08X\n",
                pc802_mb_rccnts[port_index][0], pc802_mb_rccnts[port_index][1],
                pc802_mb_rccnts[port_index][2], pc802_mb_rccnts[port_index][3]);
            for (core = 0; core < 16; core++) {
                mbs = (mailbox_exclusive *)(msg + 16 * sizeof(mailbox_info_exclusive) + core * sizeof(mailbox_exclusive));
                mb = mbs->m_cpu_to_host;
                epcnt = mb_cnts->wr[core];
                rccnt = pc802_mailbox_get_rccnt(&pc802_mailbox_rc_counter[port_index][core], epcnt, core);
                if (epcnt == rccnt)
                    continue;
                //DBLOG("mailbox core = %u state = %1u epcnt = %u rccnt = %u\n",
                //    core, (uint32_t)pc802_vec_blocked[port_index][core], epcnt, rccnt);
                while (rccnt != epcnt) {
                    re = handle_mailbox(adapter[port_index], &mb[rccnt & 15], core);
                    rccnt++;
                    if (1 == re) {
                        pc802_mailbox_rc_counter[port_index][core] = rccnt;
                    } else if (0 == core) {
                        DBLOG("mailbox re = %d core = %u state = %1u epcnt = %u rccnt = %u\n",
                                re, core, (uint32_t)pc802_vec_blocked[port_index][core], epcnt, rccnt);
                        while (epcnt != pc802_mailbox_rc_counter[port_index][core]) {
                            usleep(1);
                        }
                    }
                }
                //DBLOG("mailbox rccnt[%2u] = %u\n", core, rccnt);
            }
        } else if (1 == blks[n]->pkt_type) { //eCPRI
            //DBLOG("Recved eCPRI mailbox request in %u of %u, cause = %u\n", (uint32_t)n, (uint32_t)N, (uint32_t)blks[n]->cause);
            mb_cnts = (mailbox_counter_t *)(msg + MAILBOX_COUNTER_OFFSET_ECPRI);
            DBLOG("eCPRI wrs[0] = 0x%08X [1] = 0x%08X [2] = 0x%08X [3] = 0x%08X\n",
                mb_cnts->wrs[0], mb_cnts->wrs[1], mb_cnts->wrs[2], mb_cnts->wrs[3]);
            DBLOG("eCPRI rds[0] = 0x%08X [1] = 0x%08X [2] = 0x%08X [3] = 0x%08X\n",
                pc802_mb_rccnts[port_index][4], pc802_mb_rccnts[port_index][5],
                pc802_mb_rccnts[port_index][6], pc802_mb_rccnts[port_index][7]);
            for (core = 0; core < 16; core++) {
                mbs = (mailbox_exclusive *)(msg + core * sizeof(mailbox_exclusive));
                mb = mbs->m_cpu_to_host;
                epcnt = mb_cnts->wr[core];
                rccnt = pc802_mailbox_get_rccnt(&pc802_mailbox_rc_counter[port_index][core + 16], epcnt, core + 16);
                while (rccnt != epcnt) {
                    re = handle_mailbox(adapter[port_index], &mb[rccnt & 15], core + 16);
                    rccnt++;
                    if (1 == re) {
                        pc802_mailbox_rc_counter[port_index][core + 16] = rccnt;
                    }
                }
            }
        } else { //DSPs
            //DBLOG("Recved DSPs mailbox request in %u of %u, cause = %u\n", (uint32_t)n, (uint32_t)N, (uint32_t)blks[n]->cause);
            mb_cnts = (mailbox_counter_t *)(msg + MAILBOX_COUNTER_OFFSET_DSP);
            DBLOG("DSP   wrs[0] = 0x%08X\n", mb_cnts->wrs[0]);
            DBLOG("DSP   rds[0] = 0x%08X\n", pc802_mb_rccnts[port_index][8]);
            for (core = 0; core < 3; core++) {
                mb = (magic_mailbox_t *)(msg + MAILBOX_MEM_SIZE_PER_DSP * core + sizeof(mailbox_registry_t));
                epcnt = mb_cnts->wr[core];
                rccnt = pc802_mailbox_get_rccnt(&pc802_mailbox_rc_counter[port_index][core + 32], epcnt, core + 32);
                while (rccnt != epcnt) {
                    re = handle_mailbox(adapter[port_index], &mb[rccnt & 15], core + 32);
                    rccnt++;
                    if (1 == re) {
                        pc802_mailbox_rc_counter[port_index][core + 32] = rccnt;
                    }
                }
            }
        }
        pc802_free_mem_block(blks[n]);
    }

    return num;
}

static void * pc802_debug(__rte_unused void *data)
{
    int i = 0;
    int num = 0;
    struct timespec req;
    req.tv_sec = 0;
    req.tv_nsec = 250*1000;

    while( 1 )
    {
        num = 0;
        for ( i=0; i<num_pc802s; i++ )
        {
            //if (pc802_devices[i]->log_flag&(1<<PC802_LOG_PRINT))
            num += pc802_mailbox(pc802_devices[i]);
        }
        if ( 0 == num ) {
            pc802_log_flush();
            nanosleep(&req, NULL);
        }
    }
    return NULL;
}

static void * pc802_trace_thread(__rte_unused void *data)
{
    int i = 0;
    int j = 0;
    int num = 0;
    struct timespec req;
    req.tv_sec = 0;
    req.tv_nsec = 250*1000;

    for (i = 0; i < PC802_INDEX_MAX; i++) {
        for (j = 0; j < 32; j++) {
            trace_action_type[i][j] = TRACE_ACTION_IDLE;
        }
    }

    while( 1 )
    {
        num = 0;
        for ( i=0; i<num_pc802s; i++ )
        {
            if (pc802_devices[i]->log_flag&(1<<PC802_LOG_EVENT))
                num += pc802_tracer(i, pc802_devices[i]->port_id);
        }
        if ( 0 == num ) {
            pc802_log_flush();
            nanosleep(&req, NULL);
        }
    }
    return NULL;
}

uint32_t pc802_get_sfn_slot(uint16_t port_id, uint32_t cell_index)
{
    PC802_BAR_t *bar = pc802_get_BAR(port_id);
    uint32_t sfn_slot;
    if (0 == cell_index) {
        sfn_slot = PC802_READ_REG(bar->SFN_SLOT_0);
    } else if (1 == cell_index) {
        sfn_slot = PC802_READ_REG(bar->SFN_SLOT_1);
    } else {
        sfn_slot = 0xFFFFFFFF;
    }
    return sfn_slot;
}

static void pc802_tel_add_reg_array(struct rte_tel_data *d, const char *name, uint32_t *reg_addr, int count)
{
	int i;
	struct rte_tel_data *array = rte_tel_data_alloc();
	rte_tel_data_start_array(array, RTE_TEL_U64_VAL);
	for (i = 0; i < count; i++)
		rte_tel_data_add_array_u64(array, PC802_READ_REG(reg_addr[i]));
	rte_tel_data_add_dict_container(d, name, array, 0);
}

static int pc802_tel_handle_port_list(const char *cmd __rte_unused,
                const char *params __rte_unused, struct rte_tel_data *d)
{
	int i;
	rte_tel_data_start_array(d, RTE_TEL_INT_VAL);
    for ( i=0; i<num_pc802s; i++ )
		rte_tel_data_add_array_int(d, pc802_devices[i]->port_id);
	return 0;
}

static int pc802_rel_handle_regs(const char *cmd __rte_unused,
		const char *params, struct rte_tel_data *d)
{
    #define ADD_DICT_REG(reg) rte_tel_data_add_dict_u64(d, #reg, PC802_READ_REG(bar->reg))
    #define ADD_DICT_ARRAY(reg) pc802_tel_add_reg_array(d, #reg, bar->reg, sizeof(bar->reg)/sizeof(uint32_t))
    struct pc802_adapter *adapter;
    PC802_BAR_t *bar;
	int dev_id=0;

	/* Get dev ID from parameter string */
	if (params == NULL || strlen(params) == 0)
		return -1;

    sscanf( params, "%d", &dev_id);
    if(dev_id >= num_pc802s)
        return -1;

    adapter = pc802_devices[dev_id];
    bar = (PC802_BAR_t *)adapter->bar0_addr;

	rte_tel_data_start_dict(d);
    ADD_DICT_REG(DEVEN);
    ADD_DICT_REG(DEVRDY);
    ADD_DICT_REG(DBAL);
    ADD_DICT_REG(DBAH);
    ADD_DICT_REG(ULDMAN);
    ADD_DICT_ARRAY(TDNUM);

    ADD_DICT_ARRAY(TRCCNT);
    ADD_DICT_ARRAY(TEPCNT);
    ADD_DICT_ARRAY(RDNUM);
    ADD_DICT_ARRAY(RRCCNT);
    ADD_DICT_ARRAY(REPCNT);

    ADD_DICT_REG(BOOTSRCL);
    ADD_DICT_REG(BOOTSRCH);
    ADD_DICT_REG(BOOTDST);
    ADD_DICT_REG(BOOTSZ);
    ADD_DICT_REG(BOOTRCCNT);
    ADD_DICT_REG(BOOTRSPL);
    ADD_DICT_REG(BOOTRSPH);
    ADD_DICT_REG(BOOTEPCNT);
    ADD_DICT_REG(BOOTERROR);
    ADD_DICT_REG(BOOTDEBUG);
    ADD_DICT_REG(MB_HANDSHAKE);
    ADD_DICT_REG(MACADDRL);
    ADD_DICT_REG(DBGRCAL);
    ADD_DICT_REG(DBGRCAH);
    ADD_DICT_REG(MB_ANDES_DIS);
    ADD_DICT_REG(MB_DSP_DIS);
    ADD_DICT_REG(DBGEPADDR);
    ADD_DICT_REG(DBGBYTESNUM);
    ADD_DICT_REG(DBGCMD);
    ADD_DICT_REG(DBGRCCNT);
    ADD_DICT_REG(DBGEPCNT);
    ADD_DICT_REG(DRVSTATE);
    ADD_DICT_REG(MEMCFGADDR);

    ADD_DICT_ARRAY(ULDMA_TIMEOUT_FINISHED);
    ADD_DICT_ARRAY(ULDMA_TIMEOUT_ERROR);
    ADD_DICT_ARRAY(DLDMA_TIMEOUT_FINISHED);
    ADD_DICT_ARRAY(DLDMA_TIMEOUT_ERROR);

	return 0;
}

static int pc802_tel_handle_queue_stats(const char *cmd __rte_unused,
		const char *params, struct rte_tel_data *d)
{
    struct pc802_adapter *adapter;
    struct pc802_tx_queue *txq;
    struct pc802_rx_queue *rxq;
	int dev_id=0, queue_id=0;

	/* Get dev ID from parameter string */
	if (params == NULL || strlen(params) == 0)
		return -1;

    sscanf( params, "%d,%d", &dev_id, &queue_id);
    if( (dev_id >= num_pc802s) || (queue_id >= PC802_TRAFFIC_NUM) )
        return -1;

    adapter = pc802_devices[dev_id];
    txq = &adapter->txq[queue_id];
    rxq = &adapter->rxq[queue_id];

	rte_tel_data_start_dict(d);
    rte_tel_data_add_dict_int(d, "dev", dev_id);
    rte_tel_data_add_dict_int(d, "queue", queue_id);

    rte_tel_data_add_dict_u64(d, "TX_rc_cnt",       txq->rc_cnt);
    rte_tel_data_add_dict_int(d, "nb_tx_desc",      txq->nb_tx_desc);
    rte_tel_data_add_dict_int(d, "tx_free_thresh",  txq->tx_free_thresh);
    rte_tel_data_add_dict_int(d, "nb_tx_free",      txq->nb_tx_free);

    rte_tel_data_add_dict_u64(d, "DL_RC", *txq->trccnt_reg_addr);
    rte_tel_data_add_dict_u64(d, "DL_EP", *txq->tepcnt_mirror_addr);

    rte_tel_data_add_dict_u64(d, "RX_rc_cnt",       rxq->rc_cnt);
    rte_tel_data_add_dict_int(d, "nb_rx_desc",      rxq->nb_rx_desc);
    rte_tel_data_add_dict_int(d, "nb_rx_hold",      rxq->nb_rx_hold);
    rte_tel_data_add_dict_int(d, "rx_free_thresh",  rxq->rx_free_thresh);
    rte_tel_data_add_dict_u64(d, "UL_RC", *rxq->rrccnt_reg_addr);
    rte_tel_data_add_dict_u64(d, "UL_EP", *rxq->repcnt_mirror_addr);

	return 0;
}

static int pc802_tel_handle_read_memory(const char *cmd __rte_unused,
		const char *params, struct rte_tel_data *d)
{
    struct pc802_adapter *adapter;
	int dev_id, ret;
    uint32_t addr, len;
    char file[128] = {0};

	if (params == NULL || strlen(params) == 0)
		return -1;
    ret = sscanf( params, "%d,%x,%d,%s", &dev_id, &addr, &len, file);
    if ((ret < 3) || (dev_id >= num_pc802s) || len<4 )
        return -1;
    adapter = pc802_devices[dev_id];

    pc802_access_ep_mem(adapter->port_id, addr, len, DIR_PCIE_DMA_UPLINK);
    uint32_t *p = (uint32_t *)pc802_get_debug_mem(adapter->port_id);

    rte_tel_data_start_dict(d);
    if(ret==3) {
        uint32_t i;
        char name[16], buf[40];
        for (i = 0; i < len; i+=16 ) {
            sprintf(name, "%08X:", addr+i);
            sprintf(buf, "%08x, %08x, %08x, %08x", p[0], p[1], p[2], p[3]);
            rte_tel_data_add_dict_string(d, name, buf);
        }
    }
    else {
        FILE  *fp = fopen(file, "wb");
        if (fp == NULL) {
            rte_tel_data_add_dict_string( d, "result", "Fopen error!");
            return 0;
        }
        ret = fwrite( (char *)p, 1, len, fp);
        fclose(fp);
        rte_tel_data_add_dict_string( d, "result", "ok" );
        rte_tel_data_add_dict_string( d, "file_name", file );
    }
    return 0;
}

RTE_INIT(pc802_init_telemetry)
{
	rte_telemetry_register_cmd("/pc802/list", pc802_tel_handle_port_list,
			"Returns list of available pc802 dev. no parameters");
	rte_telemetry_register_cmd("/pc802/regs", pc802_rel_handle_regs,
			"Returns the bar0 regs for a pc802. Params: DevID");
	rte_telemetry_register_cmd("/pc802/queue", pc802_tel_handle_queue_stats,
			"Returns the stats for a pc802 queue. Params: DevID,QueueID");
	rte_telemetry_register_cmd("/pc802/read_mem", pc802_tel_handle_read_memory,
			"Read pc802 mem. Params: DevID,HexAddr,len,(file)");
}
