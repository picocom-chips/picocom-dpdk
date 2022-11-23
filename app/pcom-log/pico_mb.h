/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _PC802_MAILBOX_H_
#define _PC802_MAILBOX_H_

#define MB_NUM_ARGS              8
typedef struct {
    uint32_t action;                  // 0x00
    uint32_t num_args;                // 0x04
    uint32_t retval;                  // 0x08
    uint32_t error;                   // 0x0C
    uint32_t arguments[MB_NUM_ARGS];  // 0x10+
} magic_mailbox_t;

int pico_mb_init(void);
const char *pico_mb_get(uint32_t addr, uint32_t core);

#endif
