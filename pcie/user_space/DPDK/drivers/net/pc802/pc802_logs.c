/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2020 Picocom Corporation
 */

#include "pc802_logs.h"

/* declared as extern in pc802_logs.h */
int pc802_logtype_init;
int pc802_logtype_driver;

/* only initialize log one time */
static int pc802_log_initialized;

void
pc802_init_log(void)
{
	if (!pc802_log_initialized) {
		pc802_logtype_init = rte_log_register("pmd.net.pc802.init");
		if (pc802_logtype_init >= 0)
			rte_log_set_level(pc802_logtype_init, RTE_LOG_NOTICE);
		pc802_logtype_driver = rte_log_register("pmd.net.pc802.driver");
		if (pc802_logtype_driver >= 0)
			rte_log_set_level(pc802_logtype_driver, RTE_LOG_NOTICE);
		pc802_log_initialized = 1;
	}
}
