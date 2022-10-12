/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */
#ifndef __PCXX_OAM_H_
#define __PCXX_OAM_H_

typedef struct {
    uint16_t msg_id;
    uint16_t msg_size;              //only include msb_body size
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
/**< user application callback to be registered for oam messages */

/**
* @brief Initialize the oam function.
*
* @return returns 0 if success, or else return error
*/
int pcxx_oam_init(void);

/**
* @brief Register the callback function received by the oam message.
*
* @param[in] msg_type Oam messages type.
* @param[in] cb_fun User supplied callback function to be called.
* @param[in] arg Pointer to the parameters for the registered callback.
* @return returns 0 if success, or else return error.
*/
int pcxx_oam_register(uint32_t msg_type, pcxx_oam_cb_fn cb_fun, void *arg);

/**
* @brief Unregister the callback function received by the oam message.
*
* @param[in] msg_type Oam messages type
* @return returns 0
*/
int pcxx_oam_unregister(uint32_t msg_type);

/**
* @brief Register the callback function received by the oam submessage.
*
* @param[in] msg_type Oam messages type.
* @param[in] sub_msg_id Oam submessage id.
* @param[in] cb_fun User supplied callback function to be called.
* @param[in] arg Pointer to the parameters for the registered callback.
* @return returns 0 if success, or else return error.
*/
int pcxx_oam_sub_msg_register(uint32_t msg_type, uint16_t sub_msg_id, pcxx_oam_cb_fn cb_fun, void *arg);

/**
* @brief Unregister the callback function received by the oam submessage.
*
* @param[in] msg_type Oam messages type.
* @param[in] sub_msg_id Oam submessage id.
* @return returns 0
*/
int pcxx_oam_sub_msg_unregister(uint32_t msg_type, uint16_t sub_msg_id);

/**
* @brief Send oam messages.
*
* @param[in] dev_index Baseband device index.
* @param[in] msg_type Bam messages type.
* @param[in] sub_msg Send submessage memory pointer.
* @param[in] msg_num Number of submessage.
* @return returns 0 if send success, or else return error.
*/
int pcxx_oam_send_msg(uint16_t dev_index, uint32_t msg_type, const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num);

#endif
