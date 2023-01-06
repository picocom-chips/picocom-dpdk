/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _PSEC_CRYPTODEV_H_
#define _PSEC_CRYPTODEV_H_

#include <bha_ipsec_desc.h>
#include <bha_ipsec_regs.h>

#define PSEC_SESSIONS_MAX_NUM SEC_SESSIONS_NUM //max 64

enum psec_hw_cipher_algo {
    HW_CIPHER_ALGO_NULL = 0,
    HW_CIPHER_ALGO_AES128 = 1,
    HW_CIPHER_ALGO_AES256 = 2,
};

enum psec_hw_cipher_mode {
    HW_CIPHER_MODE_CBC = 0,
    HW_CIPHER_MODE_CCM = 1,
    HW_CIPHER_MODE_GCM = 2,
};

enum psec_hw_auth_algo {
    HW_AUTH_ALGO_NULL = 0,
    HW_AUTH_ALGO_SHA1 = 1,
    HW_AUTH_ALGO_SHA256 = 2,
    HW_AUTH_ALGO_SHA512 = 3,
};

struct psec_crypto_private {
    struct rte_cryptodev* dev;
    unsigned int max_nb_qpairs;
};

struct psec_sym_session {
    uint8_t key[64];
    uint16_t key_len;
    uint64_t key_phys_addr;
    uint32_t salt;

    struct rte_crypto_sym_xform xform;

    uint32_t sess_id; //currently max support 64
    uint32_t sess_reg_base; //according to id

} __rte_cache_aligned;

union psec_ring_ptr {
    struct {
        uint32_t idx : 16;
        uint32_t : 15;
        uint32_t wrap : 1;
    };
    uint32_t ptr;
};

struct psec_ctx_buf_entry {
    struct rte_crypto_op* op;
    SCBufferEntry* in_list;
    SCBufferEntry* out_list;
};

struct psec_queue {
    char ring_mz_name[RTE_MEMZONE_NAMESIZE];
    char ring_rsp_mz_name[RTE_MEMZONE_NAMESIZE];
    volatile IpsecReqDesc* ring;
    uint64_t ring_phys_addr;
    volatile IpsecResultDesc* ring_rsp;
    uint64_t ring_rsp_phys_addr;

    union psec_ring_ptr c_ptr;
    union psec_ring_ptr p_ptr;
    uint16_t nb_desc_free;
    uint16_t nb_dequeue_valid;

    struct psec_ctx_buf_entry* sw_ring;
};

struct psec_qp {
    char name[RTE_CRYPTODEV_NAME_MAX_LEN];

    struct psec_queue queue;
    struct rte_cryptodev* dev;
    uint8_t dev_id;
    uint16_t qp_id;
    uint32_t nb_desc;
    int socket_id;

    struct rte_mempool* mp_session;
    struct rte_mempool* mp_session_private;

    struct rte_cryptodev_stats qp_stats;

    uint32_t reg_base;
};

extern int psec_crypto_set_session_parameters(struct psec_sym_session* sess, const struct rte_crypto_sym_xform* xform);

extern struct rte_cryptodev_ops* psec_cryptodev_ops;

#endif /* _PSEC_CRYPTODEV_H_ */
