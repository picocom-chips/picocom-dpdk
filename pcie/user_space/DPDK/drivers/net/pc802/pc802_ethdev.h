/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */
#ifndef _PC802_ETHDEV_H_
#define _PC802_ETHDEV_H_

#include <stdint.h>

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

#define PC802_READ_REG(reg) \
    pc802_read_reg((volatile uint32_t *)&(reg))

PC802_BAR_t * pc802_get_BAR(uint16_t port_id);

int pc802_get_socket_id(uint16_t port_id);

char * picocom_pc802_version(void);

/**
* @brief Create control queues for Rx
*
* @param[in] port_id PC802 chip number,   start with 0
* @param[in] queue_id Queue Number for non-ethernet traffic, start with 1
* @param[in] block_size memory block size in byte (buffer header + message body)
* @param[in] block_num number of memory blocks in the pool of the queue
* @param[in] nb_desc number of message descriptors, should be less than block_num
* @return returns 0 if open success, or else return error
*/
int pc802_create_rx_queue(uint16_t port_id, uint16_t queue_id, uint32_t block_size, uint32_t block_num, uint16_t nb_desc);

/**
* @brief Create control queues for Tx
*
* @param[in] port_id PC802 chip number,   start with 0
* @param[in] queue_id Queue Number for non-ethernet traffic, start with 1
* @param[in] block_size memory block size in byte (buffer header + message body)
* @param[in] block_num number of memory blocks in the pool of the queue
* @param[in] nb_desc number of message descriptors, should be less than block_num
* @return returns 0 if open success, or else return error
*/
int pc802_create_tx_queue(uint16_t port_id, uint16_t queue_id, uint32_t block_size, uint32_t block_num, uint16_t nb_desc);

/**
* @brief Allocated one message memory from current block in used for tx.
*
* @param[in] port_id PC802 chip number,start with 0
* @param[in] queue_id Queue Number for non-ethernet traffic, start with 1
* @return return pointer to message body, Null when failure
*/
PC802_Mem_Block_t * pc802_alloc_tx_mem_block(uint16_t port_id, uint16_t queue_id);
void pc802_free_mem_block(PC802_Mem_Block_t *mblk);

/**
* @brief Allocated one message memory from current block in used for rx.
*
* @param[in] port_id PC802 chip number,start with 0
* @param[in] queue_id Queue Number for non-ethernet traffic, start with 1
* @param[in] rx_blks input+output, pointers to message body
* @param[in] nb_blks input, maximum number of messages
* @return return received message numbers
*/
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

int pc802_download_boot_image(uint16_t port_id);
int pc802_check_dma_timeout(uint16_t port);
int pc802_set_ul_dma_count(uint16_t port, uint32_t n);

#endif /* _PC802_ETHDEV_H_ */
