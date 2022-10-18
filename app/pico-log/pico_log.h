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

extern const char* pico_core_name[];

#define PC802_LOG( port, core, type, fmt, args...) \
	rte_log( type, RTE_LOGTYPE_USER1, "PC802_%d %s " fmt, port, pico_core_name[core], ##args)

#endif