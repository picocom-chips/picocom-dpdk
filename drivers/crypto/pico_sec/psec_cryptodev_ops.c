/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <string.h>

#include <cryptodev_pmd.h>
#include <rte_common.h>
#include <rte_malloc.h>

#include <bha_ipsec_desc.h>
#include <bha_ipsec_regs.h>
#include <bha_model.h>
#include <psec_cryptodev.h>
#include <psec_log.h>

static const struct rte_cryptodev_capabilities psec_cryptodev_capabilities[] = {
#if 0
	{ /* SHA256 HMAC */
		.op = RTE_CRYPTO_OP_TYPE_SYMMETRIC,
		{.sym = {
			.xform_type = RTE_CRYPTO_SYM_XFORM_AUTH,
			{.auth = {
				.algo = RTE_CRYPTO_AUTH_SHA256_HMAC,
				.block_size = 64,
				.key_size = {
					.min = 1,
					.max = 64,
					.increment = 1
				},
				.digest_size = {
					.min = 1,
					.max = 32,
					.increment = 1
				},
				.aad_size = { 0 },
				.iv_size = { 0 }
			}, },
		}, },
	},

	{ /* AES CBC */
		.op = RTE_CRYPTO_OP_TYPE_SYMMETRIC,
		{.sym = {
			.xform_type = RTE_CRYPTO_SYM_XFORM_CIPHER,
			{.cipher = {
				.algo = RTE_CRYPTO_CIPHER_AES_CBC,
				.block_size = 16,
				.key_size = {
					.min = 16,
					.max = 32,
					.increment = 8
				},
				.iv_size = {
					.min = 16,
					.max = 16,
					.increment = 0
                }
			}, },
		}, }
	},

    { /* AES CCM */
		.op = RTE_CRYPTO_OP_TYPE_SYMMETRIC,
		{.sym = {
			.xform_type = RTE_CRYPTO_SYM_XFORM_AEAD,
			{.aead = {
				.algo = RTE_CRYPTO_AEAD_AES_CCM,
				.block_size = 16,
				.key_size = {
					.min = 16,
					.max = 16,
					.increment = 0
				},
				.digest_size = {
					.min = 4,
					.max = 16,
					.increment = 2
				},
				.aad_size = {
					.min = 0,
					.max = 224,
					.increment = 1
				},
				.iv_size = {
					.min = 7,
					.max = 13,
					.increment = 1
				}
			}, }
		}, }
	},
#endif

    { /* AES GCM */
        .op = RTE_CRYPTO_OP_TYPE_SYMMETRIC,
        {
            .sym = {
                .xform_type = RTE_CRYPTO_SYM_XFORM_AEAD,
                {
                    .aead = {
                        .algo = RTE_CRYPTO_AEAD_AES_GCM,
                        .block_size = 16,
                        .key_size = {
                            .min = 16,
                            .max = 32,
                            .increment = 8 },
                        .digest_size = { .min = 8, .max = 16, .increment = 4 },
                        .aad_size = { .min = 0, .max = 240, .increment = 1 },
                        .iv_size = { .min = 0, .max = 12, .increment = 12 } },
                } },
        } },

    RTE_CRYPTODEV_END_OF_CAPABILITIES_LIST()
};

/** Configure device */
static int
psec_cryptodev_config(__rte_unused struct rte_cryptodev* dev,
    __rte_unused struct rte_cryptodev_config* config)
{
    PSEC_LOG(DEBUG, "psec crypto device config");
    return 0;
}

/** Start device */
static int
psec_cryptodev_start(__rte_unused struct rte_cryptodev* dev)
{
    PSEC_LOG(DEBUG, "psec crypto device start");
    return 0;
}

/** Stop device */
static void
psec_cryptodev_stop(__rte_unused struct rte_cryptodev* dev)
{
    PSEC_LOG(DEBUG, "psec crypto device stop");
}

/** Close device */
static int
psec_cryptodev_close(__rte_unused struct rte_cryptodev* dev)
{
    PSEC_LOG(DEBUG, "psec crypto device close. nb qpairs %d", dev->data->nb_queue_pairs);

    int i, ret;

    for (i = 0; i < dev->data->nb_queue_pairs; i++) {
        ret = dev->dev_ops->queue_pair_release(dev, i);
        if (ret < 0)
            return ret;
    }

    return 0;
}

/** Get device statistics */
static void
psec_cryptodev_stats_get(struct rte_cryptodev* dev,
    struct rte_cryptodev_stats* stats)
{
    int qp_id;

    PSEC_LOG(DEBUG, "psec crypto device status get, nb qpairs %d", dev->data->nb_queue_pairs);
    for (qp_id = 0; qp_id < dev->data->nb_queue_pairs; qp_id++) {
        struct psec_qp* qp = dev->data->queue_pairs[qp_id];

        stats->enqueued_count += qp->qp_stats.enqueued_count;
        stats->dequeued_count += qp->qp_stats.dequeued_count;

        stats->enqueue_err_count += qp->qp_stats.enqueue_err_count;
        stats->dequeue_err_count += qp->qp_stats.dequeue_err_count;
    }
}

/** Reset device statistics */
static void
psec_cryptodev_stats_reset(struct rte_cryptodev* dev)
{
    int qp_id;

    PSEC_LOG(DEBUG, "psec crypto device status reset, nb qpairs %d", dev->data->nb_queue_pairs);
    for (qp_id = 0; qp_id < dev->data->nb_queue_pairs; qp_id++) {
        struct psec_qp* qp = dev->data->queue_pairs[qp_id];

        memset(&qp->qp_stats, 0, sizeof(qp->qp_stats));
    }
}

/** Get device info */
static void
psec_cryptodev_info_get(struct rte_cryptodev* dev,
    struct rte_cryptodev_info* dev_info)
{
    struct psec_crypto_private* internals = dev->data->dev_private;

    PSEC_LOG(DEBUG, "psec crypto device info get");
    if (dev_info != NULL) {
        dev_info->driver_id = dev->driver_id;
        dev_info->max_nb_queue_pairs = internals->max_nb_qpairs;
        dev_info->sym.max_nb_sessions = PSEC_SESSIONS_MAX_NUM; //0: no limit, psec support max 64
        dev_info->feature_flags = dev->feature_flags;
        dev_info->capabilities = psec_cryptodev_capabilities;
    }
}

/** Release queue pair */
static int
psec_cryptodev_qp_release(struct rte_cryptodev* dev, uint16_t qp_id)
{
    PSEC_LOG(DEBUG, "psec crypto device queue pair release");
    if (dev->data->queue_pairs[qp_id] != NULL) {
        struct psec_qp* qp = dev->data->queue_pairs[qp_id];
        const struct rte_memzone* mz;
        int status = 0;

        mz = rte_memzone_lookup(qp->queue.ring_mz_name);
        if (mz != NULL) {
            status = rte_memzone_free(mz);
            if (status != 0)
                PSEC_LOG(ERR, "Error %d on freeing queue ring %s",
                    status, qp->queue.ring_mz_name);
        }

        mz = rte_memzone_lookup(qp->queue.ring_rsp_mz_name);
        if (mz != NULL) {
            status = rte_memzone_free(mz);
            if (status != 0)
                PSEC_LOG(ERR, "Error %d on freeing queue ring rsp %s",
                    status, qp->queue.ring_rsp_mz_name);
        }

        rte_free(qp->queue.sw_ring);
        rte_free(dev->data->queue_pairs[qp_id]);
        dev->data->queue_pairs[qp_id] = NULL;
    }
    return 0;
}

static const struct rte_memzone*
queue_dma_zone_reserve(const char* queue_name, uint32_t queue_size,
    int socket_id)
{
    const struct rte_memzone* mz;

    mz = rte_memzone_lookup(queue_name);
    if (mz != 0) {
        if (((size_t)queue_size <= mz->len) && ((socket_id == SOCKET_ID_ANY) || (socket_id == mz->socket_id))) {
            PSEC_LOG(DEBUG, "re-use memzone already allocated for %s", queue_name);
            return mz;
        }

        PSEC_LOG(ERR, "Incompatible memzone already allocated %s, size %u, socket %d. Requested size %u, socket %u",
            queue_name, (uint32_t)mz->len,
            mz->socket_id, queue_size, socket_id);
        return NULL;
    }

    //PSEC_LOG(DEBUG, "Allocate memzone for %s, size %u on socket %u", queue_name, queue_size, socket_id);
    return rte_memzone_reserve_aligned(queue_name, queue_size,
        socket_id, RTE_MEMZONE_IOVA_CONTIG, queue_size);
}

static int
psec_cryptodev_qp_start(struct rte_cryptodev* dev, uint16_t qp_id)
{
    struct psec_qp* qp;
    struct psec_queue* queue;

    qp = dev->data->queue_pairs[qp_id];
    qp->reg_base = RING(REQ_BASE_L, qp_id);
    queue = &(qp->queue);
    queue->c_ptr.ptr = 0;
    queue->p_ptr.ptr = 0;

    bha_ipsec_reg_write(qp->reg_base + RING_REGS_REQ_BASE_L_OFFSET, (uint32_t)((uint64_t)(queue->ring_phys_addr)));
    bha_ipsec_reg_write(qp->reg_base + RING_REGS_REQ_BASE_H_OFFSET, (uint32_t)((uint64_t)(queue->ring_phys_addr) >> 32));
    bha_ipsec_reg_write(qp->reg_base + RING_REGS_RESP_BASE_L_OFFSET, (uint32_t)((uint64_t)(queue->ring_rsp_phys_addr)));
    bha_ipsec_reg_write(qp->reg_base + RING_REGS_RESP_BASE_H_OFFSET, (uint32_t)((uint64_t)(queue->ring_rsp_phys_addr) >> 32));
    bha_ipsec_reg_write(qp->reg_base + RING_REGS_SIZE_OFFSET, (uint32_t)(qp->nb_desc));
    bha_ipsec_reg_write(qp->reg_base + RING_REGS_CTRL_OFFSET, SET_RING_CTRL_ENABLE(1));

    return 0;
}

/** Setup a queue pair */
static int
psec_cryptodev_qp_setup(struct rte_cryptodev* dev, uint16_t qp_id,
    const struct rte_cryptodev_qp_conf* qp_conf,
    int socket_id)
{
    struct psec_crypto_private* internals = dev->data->dev_private;
    struct psec_qp* qp;
    struct psec_queue* queue;
    const struct rte_memzone* qp_ring_mz;
    const struct rte_memzone* qp_ring_rsp_mz;

    PSEC_LOG(DEBUG, "psec crypto device queue pair setup. qp id %d, dev id %d, socket id %d", qp_id, dev->data->dev_id, socket_id);
    if (qp_id >= internals->max_nb_qpairs) {
        PSEC_LOG(ERR, "Invalid qp_id %u, greater than maximum number of queue pairs supported (%u).",
            qp_id, internals->max_nb_qpairs);
        return (-EINVAL);
    }

    /* Free memory prior to re-allocation if needed. */
    if (dev->data->queue_pairs[qp_id] != NULL)
        psec_cryptodev_qp_release(dev, qp_id);

    /* Allocate the queue pair data structure. */
    //PSEC_LOG(DEBUG, "create qp size %ld - %ld, socket id %d", sizeof(*qp), sizeof(struct psec_qp), socket_id);
    qp = rte_zmalloc_socket("psec_qp", sizeof(struct psec_qp), RTE_CACHE_LINE_SIZE, socket_id);
    if (qp == NULL) {
        PSEC_LOG(ERR, "Failed to allocate queue pair memory");
        return (-ENOMEM);
    }

    queue = &(qp->queue);
    qp->qp_id = qp_id;
    qp->dev = dev;
    qp->dev_id = dev->data->dev_id;
    qp->socket_id = socket_id;
    qp->nb_desc = qp_conf->nb_descriptors;
    qp->mp_session = qp_conf->mp_session;
    qp->mp_session_private = qp_conf->mp_session_private;
    snprintf(qp->name, sizeof(qp->name), "psec_cryptodev_%u_qp_%u", dev->data->dev_id, qp->qp_id);

    /* Allocate the queue pair associate ops */
    queue->sw_ring = rte_zmalloc_socket("qp_sw_ring",
        sizeof(struct psec_ctx_buf_entry) * (qp->nb_desc),
        RTE_CACHE_LINE_SIZE, socket_id);
    if (!queue->sw_ring) {
        rte_free(qp);
        PSEC_LOG(ERR, "Failed to allocate queue pair op buf memory");
        return (-ENOMEM);
    }
    memset(queue->sw_ring, 0, (qp->nb_desc * sizeof(struct psec_ctx_buf_entry)));

    //memzone for ring
    snprintf(queue->ring_mz_name, sizeof(queue->ring_mz_name),
        "psec%d_qp%d_ring_mz",
        dev->data->dev_id, qp->qp_id);
    qp_ring_mz = queue_dma_zone_reserve(queue->ring_mz_name, (qp->nb_desc * sizeof(IpsecReqDesc)), socket_id);
    if (qp_ring_mz == NULL) {
        PSEC_LOG(ERR, "Failed to allocate queue pair ring memzone. dev %d, qp id %d", dev->data->dev_id, qp->qp_id);
        rte_free(qp);
        rte_free(queue->sw_ring);
        return -ENOMEM;
    }
    queue->ring = (IpsecReqDesc*)qp_ring_mz->addr;
#ifdef RTE_CRYPTO_BHA_SEC_MODEL_EN
    queue->ring_phys_addr = (uint64_t)qp_ring_mz->addr;
#else
    queue->ring_phys_addr = qp_ring_mz->iova;
#endif
    memset(qp_ring_mz->addr, 0, (qp->nb_desc * sizeof(IpsecReqDesc)));

    //memzone for ring of response
    snprintf(queue->ring_rsp_mz_name, sizeof(queue->ring_rsp_mz_name),
        "psec%d_qp%d_ring_rsp_mz",
        dev->data->dev_id, qp->qp_id);
    qp_ring_rsp_mz = queue_dma_zone_reserve(queue->ring_rsp_mz_name, (qp->nb_desc * sizeof(IpsecResultDesc)), socket_id);
    if (qp_ring_rsp_mz == NULL) {
        PSEC_LOG(ERR, "Failed to allocate queue pair ring rsp memzone. dev %d, qp id %d", dev->data->dev_id, qp->qp_id);
        rte_free(qp);
        rte_memzone_free(qp_ring_mz);
        return -ENOMEM;
    }
    queue->ring_rsp = (IpsecResultDesc*)qp_ring_rsp_mz->addr;
#ifdef RTE_CRYPTO_BHA_SEC_MODEL_EN
    queue->ring_rsp_phys_addr = (uint64_t)qp_ring_rsp_mz->addr;
#else
    queue->ring_rsp_phys_addr = qp_ring_rsp_mz->iova;
#endif
    memset(qp_ring_rsp_mz->addr, 0, (qp->nb_desc * sizeof(IpsecResultDesc)));

    queue->nb_desc_free = qp->nb_desc;
    queue->nb_dequeue_valid = 0;
    memset(&qp->qp_stats, 0, sizeof(qp->qp_stats));

    dev->data->queue_pairs[qp_id] = qp;

    psec_cryptodev_qp_start(dev, qp_id);

    return 0;
}

/** Returns the size of the NULL crypto session structure */
static unsigned
psec_cryptodev_sym_session_get_private_size(struct rte_cryptodev* dev __rte_unused)
{
    PSEC_LOG(DEBUG, "psec crypto device sym sesssion get size");
    return sizeof(struct psec_sym_session);
}

/** Configure a crypto session from a crypto xform chain */
static int
psec_cryptodev_sym_session_configure(struct rte_cryptodev* dev __rte_unused,
    struct rte_crypto_sym_xform* xform,
    struct rte_cryptodev_sym_session* sess,
    struct rte_mempool* mp)
{
    void* sess_private_data;
    int ret;

    PSEC_LOG(DEBUG, "psec crypto device sym sesssion configure");
    if (unlikely(sess == NULL)) {
        PSEC_LOG(ERR, "invalid session struct");
        return -EINVAL;
    }

    if (rte_mempool_get(mp, &sess_private_data)) {
        PSEC_LOG(ERR,
            "Couldn't get object from session mempool");
        return -ENOMEM;
    }

    ret = psec_crypto_set_session_parameters(sess_private_data, xform);
    if (ret != 0) {
        PSEC_LOG(ERR, "failed configure session parameters");

        /* Return session to mempool */
        rte_mempool_put(mp, sess_private_data);
        return ret;
    }

    set_sym_session_private_data(sess, dev->driver_id,
        sess_private_data);

    return 0;
}

/** Clear the memory of session so it doesn't leave key material behind */
static void
psec_cryptodev_sym_session_clear(struct rte_cryptodev* dev,
    struct rte_cryptodev_sym_session* sess)
{
    uint8_t index = dev->driver_id;
    void* sess_priv = get_sym_session_private_data(sess, index);

    PSEC_LOG(DEBUG, "psec crypto device sym sesssion clear");

    /* Zero out the whole structure */
    if (sess_priv) {
        memset(sess_priv, 0, sizeof(struct psec_sym_session));
        struct rte_mempool* sess_mp = rte_mempool_from_obj(sess_priv);
        set_sym_session_private_data(sess, index, NULL);
        rte_mempool_put(sess_mp, sess_priv);
    }
}

static struct rte_cryptodev_ops psec_ops = {
    .dev_configure = psec_cryptodev_config,
    .dev_start = psec_cryptodev_start,
    .dev_stop = psec_cryptodev_stop,
    .dev_close = psec_cryptodev_close,

    .stats_get = psec_cryptodev_stats_get,
    .stats_reset = psec_cryptodev_stats_reset,

    .dev_infos_get = psec_cryptodev_info_get,

    .queue_pair_setup = psec_cryptodev_qp_setup,
    .queue_pair_release = psec_cryptodev_qp_release,

    .sym_session_get_size = psec_cryptodev_sym_session_get_private_size,
    .sym_session_configure = psec_cryptodev_sym_session_configure,
    .sym_session_clear = psec_cryptodev_sym_session_clear,

    //raw data-path api
    //.sym_get_raw_dp_ctx_size = ,
    //.sym_configure_raw_dp_ctx = ,
};

struct rte_cryptodev_ops* psec_cryptodev_ops = &psec_ops;
