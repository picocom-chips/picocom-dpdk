/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _PC802_LOGS_H_
#define _PC802_LOGS_H_

#include <syslog.h>
#include <rte_log.h>

enum PC802_LOG_TYPE {
	PC802_LOG_EVENT,
	PC802_LOG_PRINT,
	PC802_LOG_MAILBOX,
	PC802_LOG_VEC
};

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

extern const char* pc802_core_name[];
void pc802_log( uint32_t core, const char *format, ... );
int  pc802_log_get_level( int type );
void pc802_log_set_core( uint32_t core, bool flag);
void pc802_log_change_core( uint32_t core );
void pc802_log_flush(void);
#define PC802_LOG( port, core, type, fmt, args...) \
	do { \
		syslog( type, "PC802_%d %s " fmt, port, pc802_core_name[core], ## args); \
		pc802_log( core, "PC802_%d %s " fmt, port, pc802_core_name[core], ## args); \
	}while (0)

/* log init function shared by e1000 and igb drivers */
void pc802_init_log(void);

#define LOG_MP    "PC802_LOG"

enum log_en_dis {
	DISABLE = 0,
	ENABLE = 1
};

struct pc802_log_request {
	uint16_t ver;
	uint16_t op;
	struct rte_ring *ring;
	struct rte_mempool *pool;
};

struct pc802_log_response {
	uint16_t ver;
	uint16_t res_op;
	int32_t err_value;
};

struct pc802_log_blk {
	uint16_t port;
	uint16_t core;
	uint32_t type;
	uint32_t no;
	union {
		magic_mailbox_t mb;
		uint32_t event;
		char buf[96];
	};
} __rte_cache_aligned;

int log_server_init(void);
void log_event(uint16_t port_id, uint32_t core, uint32_t index, uint32_t event);
void log_buf(uint16_t port_id, uint32_t core, const char *fmt, ... );
void log_mb(uint16_t port_id, uint32_t core, uint32_t index, const magic_mailbox_t *mb);

#endif /* _PC802_LOGS_H_ */
