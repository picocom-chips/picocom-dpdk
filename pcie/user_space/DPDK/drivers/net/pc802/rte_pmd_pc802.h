/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */
#ifndef _PC802_ETHDEV_H_
#define _PC802_ETHDEV_H_

#include <stdint.h>
#include <stdio.h>

#define  DBLOG(format, ...) \
    printf("%s : %u : " format, __func__, __LINE__, ##__VA_ARGS__)

#define DIR_PCIE_DMA_DOWNLINK   1
#define DIR_PCIE_DMA_UPLINK     0

typedef enum PC802_Traffic_Type_e {
    PC802_TRAFFIC_ETHERNET,
    PC802_TRAFFIC_5G_EMBB_DATA,
    PC802_TRAFFIC_5G_EMBB_CTRL,
    PC802_TRAFFIC_5G_URLLC,
    PC802_TRAFFIC_4G_LTE_DATA,
    PC802_TRAFFIC_4G_LTE_CTRL,
    PC802_TRAFFIC_OAM,
    PC802_TRAFFIC_NUM
} PC802_Traffic_Type_e;

#if 0
#include "pc802_common.h"

static inline void pc802_write_reg(volatile uint32_t *addr, uint32_t value)
{
    __asm__ volatile ("" : : : "memory");
    *addr = value;
    return;
}

static inline uint32_t pc802_read_reg(volatile uint32_t *addr)
{
    uint32_t val;
    val = *addr;
    __asm__ volatile ("" : : : "memory");
    return val;
}

#define PC802_WRITE_REG(reg, value) \
    pc802_write_reg((volatile uint32_t *)&(reg), (value))
#endif

#define NPU_CACHE_LINE_SZ   64

struct pc802_mem_block {
    struct pc802_mem_block *next;
    struct pc802_mem_block **first;
    uint32_t alloced;
    uint64_t buf_phy_addr;
    uint32_t pkt_length;
    uint8_t  pkt_type;
    uint8_t  eop;
} __attribute__((__aligned__(NPU_CACHE_LINE_SZ)));
typedef struct pc802_mem_block PC802_Mem_Block_t;

#if 0
#define PC802_READ_REG(reg) \
    pc802_read_reg((volatile uint32_t *)&(reg))

PC802_BAR_t * pc802_get_BAR(uint16_t port_id);
#endif

int pc802_get_socket_id(uint16_t port_id);

char * picocom_pc802_version(void);

int pc802_create_rx_queue(uint16_t port_id, uint16_t queue_id, uint32_t block_size, uint32_t block_num, uint16_t nb_desc);
int pc802_create_tx_queue(uint16_t port_id, uint16_t queue_id, uint32_t block_size, uint32_t block_num, uint16_t nb_desc);

PC802_Mem_Block_t * pc802_alloc_tx_mem_block(uint16_t port_id, uint16_t queue_id);
void pc802_free_mem_block(PC802_Mem_Block_t *mblk);

uint16_t pc802_rx_mblk_burst(uint16_t port_id, uint16_t queue_id,
    PC802_Mem_Block_t **rx_blks, uint16_t nb_blks);
uint16_t pc802_tx_mblk_burst(uint16_t port_id, uint16_t queue_id,
    PC802_Mem_Block_t **tx_blks, uint16_t nb_blks);

uint64_t *pc802_get_debug_mem(uint16_t port_id);
void pc802_access_ep_mem(uint16_t port_id, uint32_t startAddr, uint32_t bytesNum, uint32_t cmd);
void pc802_show_pcie_counter(uint16_t port_id);
void pc802_show_tx_info(uint16_t port_id, uint16_t queue_id, uint32_t rc_counter);
void pc802_show_rx_info(uint16_t port_id, uint16_t queue_id, uint32_t rc_counter);
void pc802_show_tx_data(uint16_t port_id, uint16_t queue_id, uint32_t rc_counter);
void pc802_show_rx_data(uint16_t port_id, uint16_t queue_id, uint32_t rc_counter);

int pc802_set_ul_dma_count(uint16_t port, uint32_t n);

#endif /* _PC802_ETHDEV_H_ */
