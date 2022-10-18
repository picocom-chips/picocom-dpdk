/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _PC802_MAILBOX_H_
#define _PC802_MAILBOX_H_

#include <stdint.h>

int pico_mb_init(void);
const char *pico_mb_get(uint32_t addr, uint32_t core);

#endif
