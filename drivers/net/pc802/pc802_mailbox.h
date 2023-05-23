/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _PC802_MAILBOX_H_
#define _PC802_MAILBOX_H_

#include <stdint.h>

int32_t mb_string_init(uint16_t pc802_index);

int32_t mb_get_ssbl(uint16_t pc802_index, uint8_t **ssbl_buf);
int32_t mb_get_img(uint16_t pc802_index, uint8_t **img_buf);

const char *mb_get_string(uint16_t pc802_index, uint32_t addr, uint32_t core);
void mb_set_ssbl_end(uint16_t pc802_index);

#endif
