/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2020 Picocom Corporation
 */

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <syslog.h>
#include <rte_version.h>
#if RTE_VERSION >= RTE_VERSION_NUM(21, 5, 0, 0)
#include <eal_log.h>
#else
#include <rte_log.h>
#endif
#include <rte_atomic.h>

#include "pico_log.h"

const char* pico_core_name[] = {
	"PFI 0",
	"PFI 1",
	"PFI 2",
	"PFI 3",
	"PFI 4",
	"PFI 5",
	"PFI 6",
	"PFI 7",
	"PFI 8",
	"PFI 9",
	"PFI 10",
	"PFI 11",
	"PFI 12",
	"PFI 13",
	"PFI 14",
	"PFI 15",
	"ECPRI 0",
	"ECPRI 1",
	"ECPRI 2",
	"ECPRI 3",
	"ECPRI 4",
	"ECPRI 5",
	"ECPRI 6",
	"ECPRI 7",
	"ECPRI 8",
	"ECPRI 9",
	"ECPRI 10",
	"ECPRI 11",
	"ECPRI 12",
	"ECPRI 13",
	"ECPRI 14",
	"ECPRI 15",
	"XC12 0",
	"XC12 1",
	"XC12 2"
};

