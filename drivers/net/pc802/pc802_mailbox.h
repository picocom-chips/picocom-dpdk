/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _PC802_MAILBOX_H_
#define _PC802_MAILBOX_H_

#include <stdint.h>

int mb_string_init(void);
const char *mb_get_string(uint32_t addr, uint32_t core);
void mb_set_ssbl_end(void);

#endif
