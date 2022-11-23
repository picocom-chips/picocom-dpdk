/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _PC802_LOGS_H_
#define _PC802_LOGS_H_

#include <rte_log.h>

enum PC802_LOG_TYPE {
	PC802_LOG_EVENT,
	PC802_LOG_MAILBOX,
	PC802_LOG_VEC,
	PC802_LOG_PRINT,
	PC802_LOG_HEAD = 255
};

#define PC802_LOG_PATH        "/var/tmp/pc802log"

extern int pc802_logtype_init;
#define PMD_INIT_LOG(level, fmt, args...) \
	rte_log(RTE_LOG_ ## level, pc802_logtype_init, \
		"%s(): " fmt "\n", __func__, ##args)

#define PMD_INIT_FUNC_TRACE() PMD_INIT_LOG(DEBUG, " >>")

#ifdef RTE_LIBRTE_PC802_DEBUG_RX
#define PMD_RX_LOG(level, fmt, args...) \
	RTE_LOG(level, PMD, "%s(): " fmt "\n", __func__, ## args)
#else
#define PMD_RX_LOG(level, fmt, args...) do { } while(0)
#endif

#ifdef RTE_LIBRTE_PC802_DEBUG_TX
#define PMD_TX_LOG(level, fmt, args...) \
	RTE_LOG(level, PMD, "%s(): " fmt "\n", __func__, ## args)
#else
#define PMD_TX_LOG(level, fmt, args...) do { } while(0)
#endif

#ifdef RTE_LIBRTE_PC802_DEBUG_TX_FREE
#define PMD_TX_FREE_LOG(level, fmt, args...) \
	RTE_LOG(level, PMD, "%s(): " fmt "\n", __func__, ## args)
#else
#define PMD_TX_FREE_LOG(level, fmt, args...) do { } while(0)
#endif

extern int pc802_logtype_driver;
#define PMD_DRV_LOG_RAW(level, fmt, args...) \
	rte_log(RTE_LOG_ ## level, pc802_logtype_driver, "%s(): " fmt, \
		__func__, ## args)

#define PMD_DRV_LOG(level, fmt, args...) \
	PMD_DRV_LOG_RAW(level, fmt "\n", ## args)

/* log init function shared by e1000 and igb drivers */
void pc802_init_log(void);

struct pc802_log_blk {
	uint16_t port;
	uint16_t core;
	uint16_t type;
	uint16_t len;
	uint32_t no;
	union {
		magic_mailbox_t mb;
		uint32_t event;
		char buf[116];
	};
} __rte_cache_aligned;

void log_flush(void);
void log_event(uint16_t port_id, uint32_t core, uint32_t index, uint32_t event);
void log_buf(uint16_t port_id, uint32_t core, const char *fmt, ... );
void log_mb(uint16_t port_id, uint32_t core, uint32_t index,  uint32_t action, uint32_t num, uint32_t *args);

#endif /* _PC802_LOGS_H_ */
