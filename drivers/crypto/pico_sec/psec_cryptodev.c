/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <cryptodev_pmd.h>
#include <rte_bus_vdev.h>
#include <rte_common.h>
#include <rte_malloc.h>

#include <bha_ipsec_desc.h>
#include <bha_ipsec_regs.h>
#include <bha_model.h>
#include <bha_ring_regs.h>
#include <psec_cryptodev.h>
#include <psec_log.h>


#define PSEC_PARSE_SALT_FROM_KEY_ARG        ("salt_parse_from_key")

struct psec_pmd_init_params {
    struct rte_cryptodev_pmd_init_params common;
    bool salt_parse_from_key; //separate input salt behind key
};

static uint8_t cryptodev_driver_id;

static uint32_t
psec_ring_incr_ptr(uint16_t total_nb_desc, uint32_t ptr, uint16_t nb_fill)
{
    uint32_t ring_size = (uint32_t)total_nb_desc;
    uint32_t n = (uint32_t)nb_fill;

    if (RING_PTR_PTR(ptr) + n > ring_size - 1) {
        uint32_t round = SET_RING_PTR_ROUND((~RING_PTR_ROUND(ptr)));
        uint32_t ptr_l = RING_PTR_PTR(ptr) + n - ring_size;
        return round | ptr_l;
    } else {
        return ptr + n;
    }
}

static uint32_t
psec_ring_advance_p_n(uint32_t reg_base, uint16_t total_nb_desc, uint16_t n)
{
    volatile uint32_t cur_ptr = bha_ipsec_reg_read(reg_base + RING_REGS_P_PRODUCER_OFFSET);
    volatile uint32_t update_ptr = psec_ring_incr_ptr(total_nb_desc, cur_ptr, n);
    bha_ipsec_reg_write(reg_base + RING_REGS_P_PRODUCER_OFFSET, update_ptr);
    return update_ptr;
}

/* set session parameters */
int psec_crypto_set_session_parameters(
    struct rte_cryptodev* dev,
    struct psec_sym_session* sess,
    const struct rte_crypto_sym_xform* xform)
{
    struct psec_crypto_private* internals = dev->data->dev_private;
#ifdef RTE_CRYPTO_BHA_SEC_MODEL_EN
    uint64_t session_paddr = (uint64_t)sess;
#else
    rte_iova_t session_paddr = rte_mempool_virt2iova(sess);
#endif
    uint32_t i = 0;
    uint32_t iv_len = 0;
    bool is_cipher_key = true; //true is cipher key, false is auth key
    enum psec_hw_cipher_algo cipher_algo = 0;
    enum psec_hw_cipher_mode cipher_mode = 0;
    enum psec_hw_auth_algo auth_algo = 0;

    if (session_paddr == 0 || session_paddr == RTE_BAD_IOVA) {
        PSEC_LOG(ERR, "Session physical address unknown. Bad memory pool.");
        return -EINVAL;
    }

    //init, update it to non-zero if salt valid
    sess->salt = 0;
    sess->salt_len = 0;

    switch (xform->type) {
    case RTE_CRYPTO_SYM_XFORM_AUTH:
        memcpy(sess->key, xform->auth.key.data, xform->auth.key.length);
        sess->key_len = xform->auth.key.length;
        is_cipher_key = false;
        break;

    case RTE_CRYPTO_SYM_XFORM_CIPHER:
        memcpy(sess->key, xform->cipher.key.data, xform->cipher.key.length);
        sess->key_len = xform->cipher.key.length;
        is_cipher_key = true;
        break;

    case RTE_CRYPTO_SYM_XFORM_AEAD:
        memcpy(sess->key, xform->aead.key.data, xform->aead.key.length);
        sess->key_len = xform->aead.key.length;
        if (internals->salt_parse_from_key) {
            memcpy(&sess->salt, &xform->aead.key.data[xform->aead.key.length], 4); //salt(4B) at last of key array
            sess->salt_len = 4; //4B
        } else {
            sess->salt = 0;
            sess->salt_len = 0;
        }
        PSEC_LOG(DEBUG, "psec private sym sess config salt 0x%x\n", sess->salt);
        is_cipher_key = true;
        if (xform->aead.algo == RTE_CRYPTO_AEAD_AES_GCM) {
            cipher_algo = HW_CIPHER_ALGO_AES256;
            cipher_mode = HW_CIPHER_MODE_GCM;
            auth_algo = HW_AUTH_ALGO_NULL;
            iv_len = xform->aead.iv.length - sess->salt_len; //8B if salt valid. if not iv len = 12B
        }
        break;

    default:
        PSEC_LOG(WARNING, "Session get no specific xform");
        break;
    }

    sess->key_phys_addr = session_paddr + offsetof(struct psec_sym_session, key);
    memcpy(&(sess->xform), xform, sizeof(struct rte_crypto_sym_xform));

    //find valid hw session
    for (i = 0; i < PSEC_SESSIONS_MAX_NUM; i++) {
        if (XFORM_CTX_VALID(bha_ipsec_reg_read(SEC_SESSION(CTX, i))) == 0) {
            sess->sess_id = i;
            break;
        }
    }

    if (i >= PSEC_SESSIONS_MAX_NUM) {
        PSEC_LOG(ERR, "Not find valid hw session, max %d and all in used", PSEC_SESSIONS_MAX_NUM);
        return -1;
    }

    //setup hw session
    PSEC_LOG(DEBUG, "Find valid hw session id %d", sess->sess_id);
    //hw session disable
    bha_ipsec_reg_write(SEC_SESSION(CTX, sess->sess_id), bha_ipsec_reg_read(SEC_SESSION(CTX, sess->sess_id)) & ~SET_XFORM_CTX_VALID(1));
    if (is_cipher_key) {
        //cipher key
        bha_ipsec_reg_write(SEC_SESSION(CIPHER_KEY_LO, sess->sess_id), (uint32_t)((uint64_t)(sess->key_phys_addr)));
        bha_ipsec_reg_write(SEC_SESSION(CIPHER_KEY_HI, sess->sess_id), (uint32_t)((uint64_t)(sess->key_phys_addr) >> 32));
    } else {
        //hash key
        bha_ipsec_reg_write(SEC_SESSION(HASH_KEY_LO, sess->sess_id), (uint32_t)((uint64_t)(sess->key_phys_addr)));
        bha_ipsec_reg_write(SEC_SESSION(HASH_KEY_HI, sess->sess_id), (uint32_t)((uint64_t)(sess->key_phys_addr) >> 32));
    }
    //salt conf. support salt valid or invalid
    bha_ipsec_reg_write(SEC_SESSION(SALT, sess->sess_id), sess->salt);
    bha_ipsec_reg_write(SEC_SESSION(CTX, sess->sess_id),
                                    SET_XFORM_CTX_SALT_LEN(sess->salt_len) |
                                    SET_XFORM_CTX_IV_LEN(iv_len) |
                                    SET_XFORM_CTX_CIPHER_ALG(cipher_algo) |
                                    SET_XFORM_CTX_CIPHER_MODE(cipher_mode) |
                                    SET_XFORM_CTX_HMAC_ALG(auth_algo));
    //hw session enable
    bha_ipsec_reg_write(SEC_SESSION(CTX, sess->sess_id), bha_ipsec_reg_read(SEC_SESSION(CTX, sess->sess_id)) | SET_XFORM_CTX_VALID(1));

    return 0;
}

static inline uint64_t
psec_mem_virt2iova(void* addr)
{
#ifdef RTE_CRYPTO_BHA_SEC_MODEL_EN
    return (uint64_t)(addr);
#else
    return rte_mem_virt2iova(addr);
#endif
}

static inline uint64_t
psec_mbuf_iova(const struct rte_mbuf* mb)
{
#ifdef RTE_CRYPTO_BHA_SEC_MODEL_EN
    return (uint64_t)(mb->buf_addr) + mb->data_off;
#else
    return rte_pktmbuf_iova(mb);
#endif
}

static inline uint64_t
psec_mbuf_iova_offset(const struct rte_mbuf* mb, uint16_t offset)
{
#ifdef RTE_CRYPTO_BHA_SEC_MODEL_EN
    return (uint64_t)(mb->buf_addr) + mb->data_off + offset;
#else
    return rte_pktmbuf_iova_offset(mb, offset);
#endif
}

//static void
//dump_mem_content(void *addr, uint32_t len)
//{
//    uint8_t *buf = (uint8_t*)addr;
//    uint32_t i = 0;
//
//    PSEC_LOG(DEBUG, "--- Dump mem content addr 0x%lx, len %d ---", (uint64_t)addr, len);
//    for(i = 0; i < len; i++)
//		PSEC_LOG(DEBUG, "0x%x ", buf[i]);
//    PSEC_LOG(DEBUG, "--- Dump mem content addr 0x%lx, len %d. Done ---", (uint64_t)addr, len);
//}

static inline int
psec_mbuf_to_sclist(const struct rte_mbuf* mb, struct psec_qp* qp, SCBufferEntry** sclist)
{
    SCBufferEntry* sgl_buf = *sclist;
    uint32_t nb_segs = mb->nb_segs;
    uint32_t count = 0;
    const struct rte_mbuf* nseg = mb;

    //PSEC_LOG(DEBUG, "convert mbuf to sc list. nb segs %d", nb_segs);
    if (unlikely(nb_segs > 1)) { //sgl
        sgl_buf = rte_zmalloc_socket("psec_sclist", (sizeof(SCBufferEntry) * nb_segs), RTE_CACHE_LINE_SIZE, qp->socket_id);
        if (sgl_buf == NULL) {
            PSEC_LOG(DEBUG, "psec[%d] qp[%d] alloc sc list memory fail!", qp->dev_id, qp->qp_id);
            return -1;
        }

        while (nseg != NULL) {
            if (count >= nb_segs) {
                PSEC_LOG(DEBUG, "psec[%d] qp[%d] get unexpect segs nb %d >= expect %d", qp->dev_id, qp->qp_id, count, nb_segs);
                return -1;
            }

            sgl_buf[count].addr = psec_mbuf_iova(nseg);
            sgl_buf[count].size = nseg->data_len;
            nseg = nseg->next;
            count++;
        }
    }

    return nb_segs;
}

static uint64_t
psec_aead_get_aad_addr(struct rte_crypto_sym_op* sym_op)
{
#ifdef RTE_CRYPTO_BHA_SEC_MODEL_EN
    return (uint64_t)(sym_op->aead.aad.data);
#else
    return (uint64_t)(sym_op->aead.aad.phys_addr);
#endif
}

static uint64_t
psec_aead_get_digest_addr(struct rte_crypto_sym_op* sym_op)
{
#ifdef RTE_CRYPTO_BHA_SEC_MODEL_EN
    return (uint64_t)(sym_op->aead.digest.data);
#else
    return (uint64_t)(sym_op->aead.digest.phys_addr);
#endif
}

static uint64_t
psec_aead_get_iv_addr(struct rte_crypto_op* op, struct psec_sym_session* sess_priv)
{
#ifdef RTE_CRYPTO_BHA_SEC_MODEL_EN
    return (uint64_t)(rte_crypto_op_ctod_offset(op, void*, sess_priv->xform.aead.iv.offset));
#else
    return (uint64_t)(rte_crypto_op_ctophys_offset(op, sess_priv->xform.aead.iv.offset));
#endif
}

static int
psec_build_pktmbuf_sclist(SCBufferEntry* elt_list, struct rte_mbuf* mbuf, uint32_t offset, uint32_t len)
{
    uint32_t count = 0;
    uint32_t i = 0;
    struct rte_mbuf* nseg = mbuf;
    uint32_t start_offset = offset;
    uint32_t end_offset = len;
    bool find_start_seg = false;
    bool find_end_seg = false;
    uint16_t nb_segs = 0;

    nb_segs = nseg->nb_segs;
    for (i = 0; i < nb_segs; i++) {
        if (nseg != NULL) {
            if (!find_start_seg) {
                if (start_offset >= (nseg->data_len)) {
                    start_offset -= nseg->data_len;
                } else {
                    //find start seg
                    find_start_seg = true;
                    elt_list[count].addr = (uint64_t)(psec_mbuf_iova(nseg)) + start_offset;
                    elt_list[count].size = nseg->data_len - start_offset;
                    if ((start_offset + end_offset) <= nseg->data_len) {
                        //find end seg, same with start seg
                        find_end_seg = true;
                        elt_list[count].size = end_offset;
                    } else {
                        end_offset -= (nseg->data_len - start_offset);
                    }
                    count++;
                }
            } else {
                if (find_end_seg)
                    break;

                elt_list[count].addr = (uint64_t)(psec_mbuf_iova(nseg));
                if (end_offset > (nseg->data_len)) {
                    elt_list[count].size = nseg->data_len;
                    end_offset -= nseg->data_len;
                } else {
                    //find end seg
                    find_end_seg = true;
                    elt_list[count].size = end_offset;
                }
                count++;
            }
            nseg = nseg->next;
        } else {
            PSEC_LOG(ERR, "ERROR:build aead list, pkt mbuf sgl seg NULL illegal");
            return -1;
        }
    }

    return count;
}

static int
psec_build_aead_src_list(SCBufferEntry* elt_list, struct rte_crypto_op* op, struct psec_sym_session* sess_priv, uint32_t *total_size)
{
    struct rte_crypto_sym_op* sym_op = op->sym;
    uint16_t nb_segs = 0;
    uint32_t count = 0;
    uint32_t i = 0;
    int ret_cnt = 0;
    uint32_t calc_size = 0;

    *total_size = 0;
    nb_segs = sym_op->m_src->nb_segs;

    //aad|iv|text|icv
    //aad
    elt_list[count].addr = psec_aead_get_aad_addr(sym_op);
    elt_list[count].size = sess_priv->xform.aead.aad_length;
    *total_size = elt_list[count++].size;
    //iv
    elt_list[count].addr = psec_aead_get_iv_addr(op, sess_priv) + sess_priv->salt_len; //8B if iv exclude salt, or 12B
    elt_list[count].size = sess_priv->xform.aead.iv.length - sess_priv->salt_len;
    *total_size += elt_list[count++].size;

    //pkt mbuf - text
    if (unlikely(nb_segs > 1)) { //sgl
        if ((sym_op->aead.data.offset + sym_op->aead.data.length) > (sym_op->m_src->pkt_len)) {
            PSEC_LOG(ERR, "ERROR:build aead list, offset[%d]+len[%d] > pkt_len[%d]", sym_op->aead.data.offset, sym_op->aead.data.length, sym_op->m_src->pkt_len);
            return -1;
        }

        ret_cnt = psec_build_pktmbuf_sclist(&elt_list[count], sym_op->m_src, sym_op->aead.data.offset, sym_op->aead.data.length);
        if (ret_cnt <= 0) {
            PSEC_LOG(ERR, "ERROR:build aead pkt mbuf sgl list ret %d", ret_cnt);
            return -1;
        }

        for (i = count; i < (count + ret_cnt); i++)
            calc_size += elt_list[i].size;
        if (calc_size != sym_op->aead.data.length) {
            PSEC_LOG(ERR, "ERROR:build aead pkt mbuf sgl list len illegal! ret cnt %d, calc len %d, expect data len %d", ret_cnt, calc_size, sym_op->aead.data.length);
            return -1;
        }

        count += ret_cnt;
    } else { //single
        elt_list[count].addr = (uint64_t)(psec_mbuf_iova(sym_op->m_src)) + sym_op->aead.data.offset;
        elt_list[count++].size = sym_op->aead.data.length;
    }
    *total_size += sym_op->aead.data.length;

    //digest
    elt_list[count].addr = psec_aead_get_digest_addr(sym_op);
    elt_list[count].size = sess_priv->xform.aead.digest_length;
    *total_size += elt_list[count++].size;

    return count;
}

static int
psec_build_aead_req(struct psec_qp* qp, struct rte_crypto_op* in_op, struct psec_sym_session* sess_priv, volatile IpsecReqDesc* req, struct psec_ctx_buf_entry* sw_ctx)
{
    struct rte_crypto_op* op = in_op;
    struct rte_crypto_sym_op* sym_op = op->sym;
    uint32_t hw_sess_id = 0;
    uint32_t iv_inused_len = 0;
    uint32_t in_elt_nb = 0;
    uint32_t out_elt_nb = 0;
    SCBufferEntry* in_list = NULL;
    SCBufferEntry* out_list = NULL;
    uint32_t aad_copy_en = 0;
    uint32_t iv_copy_en = 0;
    uint32_t encrypt_en = 0;
    uint64_t src_phys_addr = 0;
    uint64_t dst_phys_addr = 0;
    uint16_t nb_src = 0;
    uint16_t nb_dst = 0;
    uint8_t src_nb_blks = 0;
    uint8_t dst_nb_blks = 0;
    uint32_t src_total_size = 0;
    uint32_t dst_total_size = 0;
    int ret_cnt = 0;

    if (sess_priv->xform.aead.algo == RTE_CRYPTO_AEAD_AES_GCM) {
        iv_inused_len = sess_priv->xform.aead.iv.length - sess_priv->salt_len; //if salt valid iv len 8B, move cross the first 4B
    } else {
        PSEC_LOG(ERR, "psec[%d] qp[%d] not support aead algo 0x%x", qp->dev_id, qp->qp_id, sess_priv->xform.aead.algo);
        return -1;
    }

    hw_sess_id = sess_priv->sess_id;
    if (sess_priv->xform.aead.op == RTE_CRYPTO_AEAD_OP_ENCRYPT)
        encrypt_en = 1; //encrypt
    else
        encrypt_en = 0; //decrypt

    nb_src = sym_op->m_src->nb_segs;
    in_elt_nb = 3 + nb_src; //aad|iv|text|icv
    in_list = rte_zmalloc_socket("psec_sclist_in", (sizeof(SCBufferEntry) * in_elt_nb), RTE_CACHE_LINE_SIZE, qp->socket_id);
    if (in_list == NULL) {
        PSEC_LOG(DEBUG, "psec[%d] qp[%d] alloc sc in list memory fail!", qp->dev_id, qp->qp_id);
        op->status = RTE_CRYPTO_OP_STATUS_ERROR;
        return -1;
    }

#if 0 //support when need it
    if ((sym_op->m_dst != NULL) && (sym_op->m_dst != sym_op->m_src)) {
        nb_dst = sym_op->m_dst->nb_segs;
        out_elt_nb = 3 + nb_dst; //aad|iv|text|icv.
        out_list = rte_zmalloc_socket("psec_sclist_out", (sizeof(SCBufferEntry) * out_elt_nb), RTE_CACHE_LINE_SIZE, qp->socket_id);
        if (out_list == NULL) {
            PSEC_LOG(DEBUG, "psec[%d] qp[%d] alloc sc out list memory fail!", qp->dev_id, qp->qp_id);
            op->status = RTE_CRYPTO_OP_STATUS_ERROR;
            rte_free(in_list);
            return -1;
        }
    }
    is_sgl = (nb_src > 1) || (nb_dst > 1);
    if (likely(!is_sgl)) {
    } else {}
#endif

    PSEC_LOG(DEBUG, "psec[%d] qp[%d] get in list entry nb %d, and out list entry nb %d", qp->dev_id, qp->qp_id, in_elt_nb, out_elt_nb);
    ret_cnt = psec_build_aead_src_list(in_list, op, sess_priv, &src_total_size);
    if (ret_cnt <= 0) {
        PSEC_LOG(ERR, "psec[%d] qp[%d] build aead src list fail %d", qp->dev_id, qp->qp_id, ret_cnt);
        goto build_req_err;
    }

    src_nb_blks = ret_cnt - 1;
    src_phys_addr = psec_mem_virt2iova(in_list);
    if (unlikely(nb_dst > 0)) { //oop
        PSEC_LOG(WARNING, "Warning:psec[%d] qp[%d] OOP not supported", qp->dev_id, qp->qp_id);
    } else {
        dst_phys_addr = src_phys_addr;
        dst_total_size = src_total_size;
        dst_nb_blks = src_nb_blks;
    }

    //fill req desc
    req->src.addr_lo = (uint32_t)((uint64_t)(src_phys_addr));
    req->src.addr_hi = (uint32_t)((uint64_t)(src_phys_addr) >> 32);
    req->src.total_size = src_total_size;
    req->src.n_blocks = src_nb_blks;

    req->dst.addr_lo = (uint32_t)((uint64_t)(dst_phys_addr));
    req->dst.addr_hi = (uint32_t)((uint64_t)(dst_phys_addr) >> 32);
    req->dst.total_size = dst_total_size;
    req->dst.n_blocks = dst_nb_blks;

    req->cfg.src.aad_offset = 0;
    req->cfg.src.iv_offset = sess_priv->xform.aead.aad_length;
    req->cfg.src.text_offset = sess_priv->xform.aead.aad_length + iv_inused_len;
    req->cfg.src.icv_offset = sess_priv->xform.aead.aad_length + iv_inused_len + sym_op->aead.data.length;

    req->cfg.dst.aad_offset = 0;
    req->cfg.dst.iv_offset = sess_priv->xform.aead.aad_length;
    req->cfg.dst.text_offset = sess_priv->xform.aead.aad_length + iv_inused_len;
    req->cfg.dst.icv_offset = sess_priv->xform.aead.aad_length + iv_inused_len + sym_op->aead.data.length;

    req->cfg.cfg.aad_len = sess_priv->xform.aead.aad_length;
    req->cfg.cfg.session_id = hw_sess_id;
    req->cfg.cfg.text_len = sym_op->aead.data.length;
    req->cfg.cfg.encrypt = encrypt_en;
    req->cfg.cfg.resp_en = 1;
    req->cfg.cfg.aad_copy = aad_copy_en;
    req->cfg.cfg.iv_copy = iv_copy_en;

    //store context for dequeue
    sw_ctx->op = op;
    sw_ctx->in_list = in_list;
    sw_ctx->out_list = out_list;

    return 0;

build_req_err:
    op->status = RTE_CRYPTO_OP_STATUS_ERROR;
    rte_free(in_list);
    rte_free(out_list);
    return -1;
}

static int
psec_sym_build_request(struct psec_qp* qp, struct rte_crypto_op* in_op, struct psec_sym_session* sess_priv, volatile IpsecReqDesc* req, struct psec_ctx_buf_entry* sw_ctx)
{
    if (sess_priv->xform.type == RTE_CRYPTO_SYM_XFORM_AEAD) {
        return psec_build_aead_req(qp, in_op, sess_priv, req, sw_ctx);
    } else {
        PSEC_LOG(ERR, "psec[%d] qp[%d] not support xform type 0x%x", qp->dev_id, qp->qp_id, sess_priv->xform.type);
        return -1;
    }
}

/* enqueue burst */
static uint16_t
psec_cryptodev_sym_enqueue_burst(void* queue_pair, struct rte_crypto_op** ops,
    uint16_t nb_ops)
{
    struct psec_sym_session* sess = NULL;
    struct rte_crypto_sym_op* sym_op;
    struct psec_qp* qp = queue_pair;
    struct psec_queue* queue = &(qp->queue);
    struct rte_crypto_op* op = NULL;
    uint16_t req_id;
    uint16_t req_id_next;
    uint8_t wrap_flag;
    volatile IpsecReqDesc* ring;
    volatile IpsecReqDesc* req;
    union psec_ring_ptr producer_ptr;
    struct psec_ctx_buf_entry* sw_ctx_e;

    uint32_t nb_ops_sent = 0;
    uint16_t nb_ops_possible = nb_ops;

    req_id = queue->p_ptr.idx;
    wrap_flag = queue->p_ptr.wrap;
    //PSEC_LOG(DEBUG, "enqueue[%d] ptr idx %d, wrap flag %d, nb desc free %d, nb ops %d", qp->qp_id, req_id, wrap_flag, queue->nb_desc_free, nb_ops);
    ring = queue->ring;
    req_id_next = 0;

    if (nb_ops_possible > queue->nb_desc_free) {
        nb_ops_possible = queue->nb_desc_free;
        PSEC_LOG(DEBUG, "enqueue[%d] proc nb ops possible %d, expect %d", qp->qp_id, nb_ops_possible, nb_ops);
        if (nb_ops_possible == 0)
            return 0;
    }

    while (nb_ops_sent != nb_ops_possible) {
        op = (struct rte_crypto_op*)(*ops);
        sym_op = op->sym;
        if (op->sess_type == RTE_CRYPTO_OP_WITH_SESSION) {
            if (likely(sym_op->session != NULL))
                sess = (struct psec_sym_session*)get_sym_session_private_data(sym_op->session, cryptodev_driver_id);
        } else {
            op->status = RTE_CRYPTO_OP_STATUS_INVALID_ARGS;
            qp->qp_stats.enqueue_err_count++;
            PSEC_LOG(ERR, "psec does not support sessionless operation");
            goto exit_sym_enqueue;
        }

        req = &(ring[req_id]);
        sw_ctx_e = &(queue->sw_ring[req_id]);
        if (req_id >= (qp->nb_desc - 1)) {
            req_id_next = req_id + 1 - qp->nb_desc;
            wrap_flag = (~(wrap_flag)) & 0x1; //wrap
        } else
            req_id_next = req_id + 1;

        //fill request desc and store sw context for dequeue
        if (0 != psec_sym_build_request(qp, op, sess, req, sw_ctx_e)) {
            op->status = RTE_CRYPTO_OP_STATUS_INVALID_ARGS;
            qp->qp_stats.enqueue_err_count++;
            PSEC_LOG(ERR, "psec build req desc fail!");
            goto exit_sym_enqueue;
        }

        //update
        req_id = req_id_next;
        ops++;
        nb_ops_sent++;
        queue->nb_desc_free--;
    }

exit_sym_enqueue:

    //PSEC_LOG(DEBUG, "enqueue[%d] build all request done. nb_enqueued %d, q nb desc free %d, req id %d", qp->qp_id, nb_ops_sent, queue->nb_desc_free, req_id);
    //update producer ptr
    producer_ptr.ptr = psec_ring_advance_p_n(qp->reg_base, qp->nb_desc, nb_ops_sent);
    queue->p_ptr.idx = req_id;
    queue->p_ptr.wrap = wrap_flag & 0x1;
    if (producer_ptr.ptr != queue->p_ptr.ptr) {
        PSEC_LOG(ERR, "crypto sec[%d] enqueue burst[%d], update producer ptr != sw calc ptr, read back 0x%x, sw update 0x%x", qp->dev_id, qp->qp_id, producer_ptr.ptr, queue->p_ptr.ptr);
        RTE_ASSERT(0);
    }
    qp->qp_stats.enqueued_count += nb_ops_sent;

#ifdef RTE_CRYPTO_BHA_SEC_MODEL_EN
    //polling the bha model complete
    while (0 == RING_STATUS_EMPTY(bha_ipsec_reg_read(qp->reg_base + RING_REGS_STATUS_OFFSET))) {
        //rte_delay_us_sleep(10000);
    }
#endif

    return nb_ops_sent;
}

static inline int
psec_dequeue_desc_avail(struct psec_qp* qp, uint16_t* nb_desc_avail)
{
    volatile union psec_ring_ptr hw_c_ptr;
    struct psec_queue* queue = &(qp->queue);

    hw_c_ptr.ptr = bha_ipsec_reg_read(qp->reg_base + RING_REGS_P_CONSUMER_OFFSET);
    //PSEC_LOG(DEBUG, "psec[%d] qp[%d] get desc avail, hw c_ptr 0x%x, sw c_ptr 0x%x", qp->dev_id, qp->qp_id, hw_c_ptr.ptr, queue->c_ptr.ptr);
    if (hw_c_ptr.ptr == queue->c_ptr.ptr) { //no new desc ready, ret 0
        *nb_desc_avail = 0;
        return 0;
    }

    if (hw_c_ptr.wrap != queue->c_ptr.wrap) {
        if (hw_c_ptr.idx > queue->c_ptr.idx) {
            PSEC_LOG(ERR, "psec[%d] qp[%d] c_ptr 0x%x error, wrap and idx fall after hw c_ptr 0x%x", qp->dev_id, qp->qp_id, queue->c_ptr.ptr, hw_c_ptr.ptr);
            RTE_ASSERT(0);
            return (-1);
        }
        *nb_desc_avail = (qp->nb_desc - queue->c_ptr.idx + hw_c_ptr.idx);
    } else {
        if (queue->c_ptr.idx > hw_c_ptr.idx) {
            PSEC_LOG(ERR, "psec[%d] qp[%d] c_ptr 0x%x error, no wrap and idx go ahead hw c_ptr 0x%x", qp->dev_id, qp->qp_id, queue->c_ptr.ptr, hw_c_ptr.ptr);
            RTE_ASSERT(0);
            return (-1);
        }
        *nb_desc_avail = (hw_c_ptr.idx - queue->c_ptr.idx);
    }

    return 0;
}

/* dequeue burst */
static uint16_t
psec_cryptodev_sym_dequeue_burst(void* queue_pair, struct rte_crypto_op** ops,
    uint16_t nb_ops)
{
    struct psec_qp* qp = queue_pair;
    struct psec_queue* queue = &(qp->queue);
    struct rte_crypto_op* dequeue_op = NULL;
    volatile IpsecResultDesc* ring_rsp;
    volatile IpsecResultDesc* rsp;
    uint16_t nb_dequeued = 0;
    uint16_t nb_desc_avail = 0;
    uint16_t rsp_id = 0;
    uint16_t rsp_id_next = 0;
    uint8_t wrap_flag = 0;
    SCBufferEntry* in_list = NULL;
    SCBufferEntry* out_list = NULL;

    rsp_id = queue->c_ptr.idx;
    wrap_flag = queue->c_ptr.wrap;
    nb_desc_avail = queue->nb_dequeue_valid;
    ring_rsp = queue->ring_rsp;

    while (nb_dequeued < nb_ops) {
        //check valid desc if needed
        if (nb_desc_avail < 1) {
            //check valid desc
            if (psec_dequeue_desc_avail(qp, &nb_desc_avail) != 0) {
                PSEC_LOG(ERR, "psec[%d] qp[%d] get avail desc number fail, nb_avail %d", qp->dev_id, qp->qp_id, nb_desc_avail);
                break;
            } else {
                if (nb_desc_avail < 1)
                    break;
            }
        }

        dequeue_op = queue->sw_ring[rsp_id].op;
        in_list = queue->sw_ring[rsp_id].in_list;
        out_list = queue->sw_ring[rsp_id].out_list;
        rsp = &(ring_rsp[rsp_id]);
        if ((*(volatile uint64_t*)rsp) != 0) {
            PSEC_LOG(ERR, "psec[%d] qp[%d] dequeue response 0x%lx", qp->dev_id, qp->qp_id, (*(volatile uint64_t*)rsp));
            dequeue_op->status = RTE_CRYPTO_OP_STATUS_ERROR;
        } else
            dequeue_op->status = RTE_CRYPTO_OP_STATUS_SUCCESS;

        ops[nb_dequeued] = dequeue_op;

        //clear sw context
        if (in_list != NULL)
            rte_free(in_list);
        if (out_list != NULL)
            rte_free(out_list);
        queue->sw_ring[rsp_id].in_list = NULL;
        queue->sw_ring[rsp_id].out_list = NULL;
        queue->sw_ring[rsp_id].op = NULL;

        //update
        rsp_id_next = rsp_id + 1;
        if (rsp_id_next == qp->nb_desc) { //wrap
            rsp_id_next = 0;
            wrap_flag = (~(wrap_flag)) & 0x1;
        }
        rsp_id = rsp_id_next;

        ops++;
        nb_dequeued++;
        nb_desc_avail--;

        queue->c_ptr.idx = rsp_id;
        queue->c_ptr.wrap = wrap_flag;
        queue->nb_dequeue_valid = nb_desc_avail;
    }

    return nb_dequeued;
}

/* create crypto device */
static int
cryptodev_psec_create(const char* name,
    struct rte_vdev_device* vdev,
    struct psec_pmd_init_params* init_params)
{
    struct rte_cryptodev* dev;
    struct psec_crypto_private* internals;
    dev = rte_cryptodev_pmd_create(name, &vdev->device, &(init_params->common));
    if (dev == NULL) {
        PSEC_LOG(ERR, "failed to create cryptodev vdev");
        return -EFAULT;
    }

    dev->driver_id = cryptodev_driver_id;
    PSEC_LOG(DEBUG, "Get cryptodev driver id %d", dev->driver_id);
    dev->dev_ops = psec_cryptodev_ops;

    /* register rx/tx burst functions for data path */
    dev->dequeue_burst = psec_cryptodev_sym_dequeue_burst;
    dev->enqueue_burst = psec_cryptodev_sym_enqueue_burst;

    dev->feature_flags = RTE_CRYPTODEV_FF_SYMMETRIC_CRYPTO
                       | RTE_CRYPTODEV_FF_HW_ACCELERATED
                       | RTE_CRYPTODEV_FF_IN_PLACE_SGL
                       | RTE_CRYPTODEV_FF_SYM_OPERATION_CHAINING;
                       //| RTE_CRYPTODEV_FF_DIGEST_ENCRYPTED
                       //| RTE_CRYPTODEV_FF_SYM_RAW_DP;
                       //| RTE_CRYPTODEV_FF_OOP_SGL_IN_SGL_OUT
                       //| RTE_CRYPTODEV_FF_OOP_SGL_IN_LB_OUT
                       //| RTE_CRYPTODEV_FF_OOP_LB_IN_SGL_OUT
                       //| RTE_CRYPTODEV_FF_OOP_LB_IN_LB_OUT;

    internals = dev->data->dev_private;

    internals->max_nb_qpairs = init_params->common.max_nb_queue_pairs;
    internals->salt_parse_from_key = init_params->salt_parse_from_key;

#ifdef RTE_CRYPTO_BHA_SEC_MODEL_EN
    bha_ipsec_simulate();
#endif

    rte_cryptodev_pmd_probing_finish(dev);
    PSEC_LOG(DEBUG, "Probe crypto device pico sec done");

    return 0;
}

static int
get_int_val_arg(const char *key __rte_unused,
        const char *value, void *extra_args)
{
    const char *a = value;
    int *arg_int = extra_args;

    //PSEC_LOG(DEBUG, "---parse int value arg func---");
    if ((value == NULL) || (extra_args == NULL))
        return -EINVAL;

    *arg_int = (int)strtol(a, NULL, 0);

    return 0;
}

static int
get_psec_name_arg(const char *key __rte_unused,
           const char *value,
           void *extra_args)
{
    char *name = (char *)extra_args;
    int n = 0;

    //PSEC_LOG(DEBUG, "---parse psec name func---");
    if (value) {
        PSEC_LOG(DEBUG, "get input psec name (%s)", value);
        if (*value == '\0')
            return -EINVAL;

        n = strlcpy(name, value, RTE_CRYPTODEV_NAME_MAX_LEN);
        if (n >= RTE_CRYPTODEV_NAME_MAX_LEN)
            return -EINVAL;
    } else
        return -1;

    return 0;
}

static int
get_salt_parse_arg(const char *key __rte_unused, const char *value, void *extra_args)
{
    bool *flags = (bool *)extra_args;

    if (strstr(value, "yes") != NULL) {
        *flags = true;
    } else if (strstr(value, "no") != NULL) {
        *flags = false;
    } else {
        PSEC_LOG(ERR, "Failed to parse salt parse from key param: %s.", value);
        return -EINVAL;
    }
    return 0;
}

static void
psec_cryptodev_parse_input_params(struct psec_pmd_init_params *init_params, const char *params)
{
    int max_qp_nb = -1;
    int socket_id = -1;
    bool salt_parse = false;
    char* name_psec;
    struct rte_kvargs *kvlist = NULL;
    int ret = 0;
    const char *valid_arguments[] = {
        RTE_CRYPTODEV_PMD_NAME_ARG,
        RTE_CRYPTODEV_PMD_MAX_NB_QP_ARG,
        RTE_CRYPTODEV_PMD_SOCKET_ID_ARG,
        PSEC_PARSE_SALT_FROM_KEY_ARG,
        NULL
    };

    name_psec = init_params->common.name;
    ret = rte_kvargs_process(kvlist,
                RTE_CRYPTODEV_PMD_NAME_ARG,
                &get_psec_name_arg, name_psec);
    if (ret < 0) {
        PSEC_LOG(DEBUG, "psec parse name fail. ret %d", ret);
    } else {
        if (*name_psec != '\0')
            PSEC_LOG(DEBUG, "psec parse name[%s] and update into init params", name_psec);
    }

    kvlist = rte_kvargs_parse(params, valid_arguments);
    if (kvlist != NULL) {
        ret = rte_kvargs_process(kvlist,
                RTE_CRYPTODEV_PMD_MAX_NB_QP_ARG,
                &get_int_val_arg, &max_qp_nb);
        if (ret < 0) {
            PSEC_LOG(ERR, "psec parse max qpair number fail. ret %d", ret);
        } else {
            if (max_qp_nb > 0) {
                PSEC_LOG(DEBUG, "psec parse max qpair number %d, bha model expect <= 4", max_qp_nb);
                if (max_qp_nb <= 4)
                    init_params->common.max_nb_queue_pairs = max_qp_nb;
            }
        }

        ret = rte_kvargs_process(kvlist,
                RTE_CRYPTODEV_PMD_SOCKET_ID_ARG,
                &get_int_val_arg, &socket_id);
        if (ret < 0) {
            PSEC_LOG(ERR, "psec parse socket id fail. ret %d", ret);
        } else {
            if (socket_id >= 0) {
                PSEC_LOG(DEBUG, "psec parse socket id %d", socket_id);
                init_params->common.socket_id = socket_id;
            }
        }

        ret = rte_kvargs_process(kvlist,
                PSEC_PARSE_SALT_FROM_KEY_ARG,
                &get_salt_parse_arg, &salt_parse);
        if (ret < 0) {
            PSEC_LOG(ERR, "psec parse enable salt parse from key fail. ret %d", ret);
        } else {
            PSEC_LOG(DEBUG, "psec parse enable salt parse from key %d", salt_parse);
            init_params->salt_parse_from_key = salt_parse;
        }

        rte_kvargs_free(kvlist);
    }
}

/* initialise crypto device */
static int
cryptodev_psec_probe(struct rte_vdev_device* vdev)
{
    struct psec_pmd_init_params init_params = {
        .common = {
            "",
            sizeof(struct psec_crypto_private),
            rte_socket_id(),
            4 //model up to 4 //RTE_CRYPTODEV_PMD_DEFAULT_MAX_NB_QUEUE_PAIRS
        },
        .salt_parse_from_key = false,
    };
    const char *name, *args;

    name = rte_vdev_device_name(vdev);
    if (name == NULL)
        return -EINVAL;
    PSEC_LOG(DEBUG, "Initializing crypto device pmd for %s", name);

    //vdev set defaut socket id any, update to the real numa node
    vdev->device.numa_node = rte_socket_id();

    args = rte_vdev_device_args(vdev);
    if (args != NULL)
        psec_cryptodev_parse_input_params(&init_params, args);

    return cryptodev_psec_create(name, vdev, &init_params);
}

static int
cryptodev_psec_remove_dev(struct rte_vdev_device* vdev)
{
    struct rte_cryptodev* cryptodev;
    const char* name;

    name = rte_vdev_device_name(vdev);
    if (name == NULL)
        return -EINVAL;

    cryptodev = rte_cryptodev_pmd_get_named_dev(name);
    if (cryptodev == NULL)
        return -ENODEV;

    return rte_cryptodev_pmd_destroy(cryptodev);
}

static struct rte_vdev_driver cryptodev_psec_pmd_drv = {
    .probe = cryptodev_psec_probe,
    .remove = cryptodev_psec_remove_dev,
};

static struct cryptodev_driver psec_crypto_drv;

RTE_PMD_REGISTER_VDEV(crypto_psec, cryptodev_psec_pmd_drv);
RTE_PMD_REGISTER_ALIAS(crypto_psec, cryptodev_psec_pmd);
RTE_PMD_REGISTER_PARAM_STRING(crypto_psec,
    "max_nb_queue_pairs=<int> "
    "socket_id=<int>"
    "salt_parse_from_key=yes|no");
RTE_PMD_REGISTER_CRYPTO_DRIVER(psec_crypto_drv, cryptodev_psec_pmd_drv.driver,
    cryptodev_driver_id);
RTE_LOG_REGISTER_DEFAULT(psec_logtype, NOTICE);
