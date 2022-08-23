/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */
#ifndef __PC802_OAM_LIB_H_
#define __PC802_OAM_LIB_H_

typedef struct {
    uint16_t msg_id;
    uint16_t msg_size;
    uint8_t msb_body[0];
} pcxx_oam_sub_msg_t;

typedef enum{
    PCXX_OAM_MSG      = 0x00,
    PCXX_P19_MSG      = 0x01,
    PCXX_DEBUG_MSG    = 0x02,
    PCXX_MSG_TYPE_MAX = 0x10,
}pcxx_oam_msg_type_e;

typedef int (*pcxx_oam_cb_fn)(void *arg, uint16_t dev_index, uint32_t msg_type, const pcxx_oam_sub_msg_t **sub_msg,
                              uint32_t msg_num);
/**< user application callback to be registered for oam msg */

int pcxx_oam_init(void);

int pcxx_oam_register(uint32_t msg_type, pcxx_oam_cb_fn cb_fun, void *arg);
int pcxx_oam_unregister(uint32_t msg_type);

int pcxx_oam_sub_msg_register(uint32_t msg_type, uint16_t sub_msg_id, pcxx_oam_cb_fn cb_fun, void *arg);
int pcxx_oam_sub_msg_unregister(uint32_t msg_type, uint16_t sub_msg_id);

int pcxx_oam_send_msg(uint16_t dev_index, uint32_t msg_type, const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num);

#endif
