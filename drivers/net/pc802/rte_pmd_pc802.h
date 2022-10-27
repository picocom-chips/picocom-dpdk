/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */
#ifndef __RTE_PMD_PC802_H__
#define __RTE_PMD_PC802_H__

#include <stdint.h>
#include <stdio.h>

#define  ENABLE_CHECK_PC802_UL_TIMING   1
#define  ENABLE_CHECK_PC802_DL_TIMING   1

#if defined(ENABLE_CHECK_PC802_UL_TIMING) || defined(ENABLE_CHECK_PC802_DL_TIMING)
#define ENABLE_CHECK_PC802_TIMING
#endif

#define  DBLOG(format, ...) \
    printf("%s : %u : " format, __func__, __LINE__, ##__VA_ARGS__)

#define  DBLOG_INFO(format, ...)

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

int pc802_get_socket_id(uint16_t port_id);

char * picocom_pc802_version(void);

/**
* @brief Create Rx queue for queue_id >= 1
*
* @param[in] port_id PC802 chip number, start with 0
* @param[in] queue_id Queue Number for non-ethernet traffic, start with 1
* @param[in] block_size memory block size in byte (buffer header + message body)
* @param[in] block_num number of memory blocks in the pool of the queue
* @param[in] nb_desc number of message descriptors, should be less than block_num
* @return returns 0 if open success, or else return error
*/
int pc802_create_rx_queue(uint16_t port_id, uint16_t queue_id, uint32_t block_size, uint32_t block_num, uint16_t nb_desc);

/**
* @brief Create Tx queue for queue_id >= 1
*
* @param[in] port_id PC802 chip number, start with 0
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

/**
* @brief Free one message memory from current block in used for rx.
*
* @param[in] mblk pointer to message block
* @return void
*/
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
int pc802_check_dma_timeout(uint16_t port);
int pc802_set_ul_dma_count(uint16_t port, uint32_t n);
uint32_t pc802_vec_read(uint16_t port_id, uint32_t file_id, uint32_t offset, uint32_t address, uint32_t length);
uint32_t pc802_vec_dump(uint16_t port_id, uint32_t file_id, uint32_t address, uint32_t length);

#endif /* __RTE_PMD_PC802_H__ */
