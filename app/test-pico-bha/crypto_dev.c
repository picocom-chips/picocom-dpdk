/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <time.h>

#include <sys/queue.h>
#include <sys/stat.h>

#include <inttypes.h>
#include <stdint.h>
#include <unistd.h>

#include <cmdline.h>
#include <cmdline_parse.h>
#include <cmdline_rdline.h>
#include <cmdline_socket.h>
#include <rte_alarm.h>
#include <rte_atomic.h>
#include <rte_branch_prediction.h>
#include <rte_byteorder.h>
#include <rte_common.h>
#include <rte_cryptodev.h>
#include <rte_cycles.h>
#include <rte_debug.h>
#include <rte_dev.h>
#include <rte_eal.h>
#include <rte_errno.h>
#include <rte_ethdev.h>
#include <rte_ether.h>
#include <rte_interrupts.h>
#include <rte_launch.h>
#include <rte_lcore.h>
#include <rte_log.h>
#include <rte_malloc.h>
#include <rte_mbuf.h>
#include <rte_mbuf_pool_ops.h>
#include <rte_memcpy.h>
#include <rte_memory.h>
#include <rte_mempool.h>
#include <rte_pci.h>
#include <rte_per_lcore.h>
#include <rte_string_fns.h>

#include <bha_model.h>
#include <rte_pmd_bha.h>
#include <test_bha.h>

#define MAXIMUM_IV_LENGTH (16)
#define MAX_NB_SESSIONS (4) //ref nb_cdev, nb_ports, and*crypto scheduler workers. bha sec model support max 64
#define MAX_NUM_OPS_INFLIGHT (32)
#define IV_OFFSET (sizeof(struct rte_crypto_op) + sizeof(struct rte_crypto_sym_op)) //according to op pool create

struct crypto_sym_test_data {
    struct {
        uint8_t data[64];
        unsigned len; //key len exclude salt len
    } key; //support key + salt(4B at last)

    struct {
        uint8_t data[64];
        unsigned len;
    } iv;

    struct {
        uint8_t data[512];
        unsigned len;
    } aad;

    struct {
        uint8_t data[2048];
        unsigned len;
    } plaintext;

    struct {
        uint8_t data[2048];
        unsigned len;
    } ciphertext;

    struct {
        uint8_t data[16];
        unsigned len;
    } digest;
};

//aes gcm test data
static struct crypto_sym_test_data aes_gcm_data = {
    .key = {
        .data = {
            0xdd, 0x73, 0x67, 0x0f,
            0xb2, 0x21, 0xf7, 0xee,
            0x18, 0x5f, 0x58, 0x18,
            0x06, 0x5e, 0x22, 0xdd,
            0xa3, 0x78, 0x0f, 0xc9,
            0x00, 0xfc, 0x02, 0xef,
            0x00, 0x23, 0x2c, 0x66,
            0x1d, 0x7b, 0xff, 0xce,
            0xc3, 0x3d, 0xe6, 0x53 }, //append 4B salt at last
        .len = 32 },

    //nonce
    .iv = {
        .data = {
            0xc3, 0x3d, 0xe6, 0x53, //first 4B salt
            0x44, 0xcf, 0xbf, 0x22,
            0x8e, 0x16, 0x52, 0xbd },
        .len = 12 },

    .aad = {
        .data = {
            0xe1, 0xa5, 0xe5, 0x24,
            0x27, 0xf1, 0xc5, 0xb8,
            0x87, 0x57, 0x5a, 0x6f,
            0x2c, 0x44, 0x54, 0x29 },
        .len = 16 },

    .plaintext = {
        .data = {
            0xad, 0xa4, 0xd9, 0x81,
            0x47, 0xb3, 0x0e, 0x5a,
            0x90, 0x12, 0x29, 0x95,
            0x2a },
        .len = 13 },

    .ciphertext = {
        .data = {
            0x6e, 0xd4, 0xe4, 0xbd,
            0x1f, 0x95, 0x3d, 0x47,
            0xc5, 0x28, 0x8c, 0x48,
            0xf4 },
        .len = 13 },

    .digest = {
        .data = {
            0x40, 0x4e, 0x3a, 0x9b,
            0x9f, 0x5d, 0xda, 0xb9,
            0xee, 0x16, 0x9a, 0x7c,
            0x7c, 0x2c, 0xf7, 0xaf },
        .len = 16 },
};

//test bha port id
extern uint16_t bha_portid;
extern uint8_t psec_cdevid;

//memory pool
static struct rte_mempool* sym_sess_pool;
static struct rte_mempool* priv_sess_pool;
static struct rte_mempool* crypto_mbuf_pool;
static struct rte_mempool* crypto_op_pool;

//test sym session and crypto op
static struct rte_cryptodev_sym_session* test_sym_sess;
static struct rte_crypto_op* test_crypto_op;

static void
test_bha_crypto_init(void)
{
    uint8_t dev_id = psec_cdevid;
    struct rte_cryptodev_info info;
    unsigned int priv_sess_size;
    struct rte_cryptodev_config conf;
    struct rte_cryptodev_qp_conf qp_conf;
    uint16_t qp_id;
    int ret = 0;

    rte_cryptodev_info_get(dev_id, &info);
    priv_sess_size = rte_cryptodev_sym_get_private_session_size(dev_id);
    TESTBHA_LOG(DEBUG, "Get crypto dev max qp nb %d, sym max sess nb %d, priv sess size %d", info.max_nb_queue_pairs, info.sym.max_nb_sessions, priv_sess_size);

    if (info.sym.max_nb_sessions != 0 && info.sym.max_nb_sessions < MAX_NB_SESSIONS) {
        TESTBHA_LOG(ERR, "crypto pico sec device do not support enough sym sessions %d\n", info.sym.max_nb_sessions);
        return;
    }

    sym_sess_pool = rte_cryptodev_sym_session_pool_create(
        "sym_sess_mp", MAX_NB_SESSIONS, 0, 0, 0,
        rte_socket_id());
    if (sym_sess_pool == NULL) {
        TESTBHA_LOG(ERR, "crypto psec create sym sessions mem pool failed!\n");
        return;
    }

    priv_sess_pool = rte_mempool_create(
        "priv_sess_mp",
        MAX_NB_SESSIONS,
        priv_sess_size,
        0, 0, NULL, NULL, NULL,
        NULL, rte_socket_id(),
        0);
    if (priv_sess_pool == NULL) {
        TESTBHA_LOG(ERR, "crypto psec create private sym sessions mem pool failed!\n");
        return;
    }

    conf.nb_queue_pairs = info.max_nb_queue_pairs;
    conf.socket_id = rte_socket_id();
    conf.ff_disable = RTE_CRYPTODEV_FF_SECURITY; //security/sym/asym
    rte_cryptodev_configure(dev_id, &conf);

    qp_conf.nb_descriptors = MAX_NUM_OPS_INFLIGHT;
    qp_conf.mp_session = sym_sess_pool;
    qp_conf.mp_session_private = priv_sess_pool;

    for (qp_id = 0; qp_id < info.max_nb_queue_pairs; qp_id++) {
        rte_cryptodev_queue_pair_setup(dev_id, qp_id, &qp_conf, rte_socket_id());
    }

    rte_cryptodev_stats_reset(dev_id);

    ret = rte_cryptodev_start(dev_id);
    if (ret < 0)
        TESTBHA_LOG(ERR, "crypto pico sec device[%d] start fail! %d\n", dev_id, ret);
}

static int
aead_session_create_and_init(uint8_t dev_id, enum rte_crypto_aead_algorithm algo,
    enum rte_crypto_aead_operation op,
    struct crypto_sym_test_data* testdata)
{
    int status;
    struct rte_crypto_sym_xform aead_xform;
    struct rte_cryptodev_sym_session* sess;

    aead_xform.type = RTE_CRYPTO_SYM_XFORM_AEAD;
    aead_xform.next = NULL;
    aead_xform.aead.algo = algo;
    aead_xform.aead.op = op;
    aead_xform.aead.key.data = testdata->key.data; //4B salt at last
    aead_xform.aead.key.length = testdata->key.len; //only key len exclude salt
    aead_xform.aead.iv.offset = IV_OFFSET;
    aead_xform.aead.iv.length = testdata->iv.len; //full IV len include salt
    aead_xform.aead.digest_length = testdata->digest.len;
    aead_xform.aead.aad_length = testdata->aad.len; //match ipsec lib defined aad struct and len

    //create crypto sym session
    sess = rte_cryptodev_sym_session_create(sym_sess_pool);
    if (sess == NULL) {
        TESTBHA_LOG(ERR, "crypto pico sec device[%d] create sym session fail!!!\n", dev_id);
        return -1;
    }
    status = rte_cryptodev_sym_session_init(dev_id, sess, &aead_xform, priv_sess_pool);
    test_sym_sess = sess;

    return status;
}

static int
aead_operation_create(enum rte_crypto_aead_algorithm algo __rte_unused,
    enum rte_crypto_aead_operation op,
    struct crypto_sym_test_data* testdata,
    struct rte_mbuf* in_mbuf,
    struct rte_mbuf* out_mbuf)
{
    struct rte_crypto_op* crypto_op;
    struct rte_crypto_sym_op* sym_op;
    uint8_t *plaintext, *ciphertext;
    unsigned int aad_pad_len, plaintext_pad_len;
    unsigned int iv_pad_len;
    uint8_t *iv_pkt_addr = NULL;
    out_mbuf = out_mbuf;

    //generate crypto op
    crypto_op = rte_crypto_op_alloc(crypto_op_pool, RTE_CRYPTO_OP_TYPE_SYMMETRIC);
    if (crypto_op == NULL) {
        rte_exit(EXIT_FAILURE, "Cannot alloc crypto op from pool\n");
        return -1;
    }
    sym_op = crypto_op->sym;

    //append aad data
    //aad_pad_len = RTE_ALIGN_CEIL(testdata->aad.len, 16);
    aad_pad_len = testdata->aad.len;
    sym_op->aead.aad.data = (uint8_t*)rte_pktmbuf_append(in_mbuf, aad_pad_len);
    sym_op->aead.aad.phys_addr = rte_pktmbuf_iova(in_mbuf);
    memcpy(sym_op->aead.aad.data, testdata->aad.data, testdata->aad.len);

    //append iv according to op pool create
    uint8_t* iv_ptr = rte_crypto_op_ctod_offset(crypto_op, uint8_t*, IV_OFFSET);
    rte_memcpy(iv_ptr, testdata->iv.data, testdata->iv.len);

    //append iv into packet buf too
    iv_pad_len = testdata->iv.len - 4; //remove salt
    iv_pkt_addr = (uint8_t*)rte_pktmbuf_append(in_mbuf, iv_pad_len);
    memcpy(iv_pkt_addr, testdata->iv.data + 4, testdata->iv.len - 4);

    //append plaintext/ciphertext
    if (op == RTE_CRYPTO_AEAD_OP_ENCRYPT) {
        //plaintext_pad_len = RTE_ALIGN_CEIL(testdata->plaintext.len, 16);
        plaintext_pad_len = testdata->plaintext.len;
        plaintext = (uint8_t*)rte_pktmbuf_append(in_mbuf, plaintext_pad_len);
        memcpy(plaintext, testdata->plaintext.data, testdata->plaintext.len);
    } else {
        //plaintext_pad_len = RTE_ALIGN_CEIL(testdata->ciphertext.len, 16);
        plaintext_pad_len = testdata->ciphertext.len;
        ciphertext = (uint8_t*)rte_pktmbuf_append(in_mbuf, plaintext_pad_len);
        memcpy(ciphertext, testdata->ciphertext.data, testdata->ciphertext.len);
    }

    //append digest data
    if (op == RTE_CRYPTO_AEAD_OP_ENCRYPT) {
        sym_op->aead.digest.data = (uint8_t*)rte_pktmbuf_append(in_mbuf, testdata->digest.len);
        memset(sym_op->aead.digest.data, 0, testdata->digest.len);
        sym_op->aead.digest.phys_addr = rte_pktmbuf_iova_offset(in_mbuf, plaintext_pad_len + aad_pad_len);
    } else {
        sym_op->aead.digest.data = (uint8_t*)rte_pktmbuf_append(in_mbuf, testdata->digest.len);
        sym_op->aead.digest.phys_addr = rte_pktmbuf_iova_offset(in_mbuf, plaintext_pad_len + aad_pad_len);
        rte_memcpy(sym_op->aead.digest.data, testdata->digest.data, testdata->digest.len);
    }

    sym_op->aead.data.length = testdata->plaintext.len;
    sym_op->aead.data.offset = aad_pad_len + iv_pad_len;
    test_crypto_op = crypto_op;

    return 0;
}

static int
crypto_op_req_proc(uint8_t dev_id, struct rte_crypto_op* op)
{
    if (rte_cryptodev_enqueue_burst(dev_id, 0, &op, 1) != 1) {
        TESTBHA_LOG(ERR, "crypto enqueue proc error\n");
        return -1;
    }

    while (rte_cryptodev_dequeue_burst(dev_id, 0, &op, 1) == 0)
        usleep(100000);

    if (op->status != RTE_CRYPTO_OP_STATUS_SUCCESS) {
        TESTBHA_LOG(ERR, "crypto dequeue proc error, status %d\n", op->status);
        return -1;
    }

    return 0;
}

#if 0
static void
dump_mem_info(void *addr, uint32_t len)
{
    uint8_t *buf = (uint8_t*)addr;
    uint32_t i = 0;

    TESTBHA_LOG(DEBUG, "--- Dump mem content addr 0x%lx, len %d ---", (uint64_t)addr, len);
    for(i = 0; i < len; i++)
        TESTBHA_LOG(DEBUG, "0x%x ", buf[i]);
    TESTBHA_LOG(DEBUG, "--- Dump mem content addr 0x%lx, len %d. Done ---", (uint64_t)addr, len);
}
#endif

void test_bha_crypto_aes256_gcm(void)
{
    struct rte_cryptodev_info dev_info;
    const struct rte_cryptodev_symmetric_capability* capability = NULL;
    struct rte_cryptodev_sym_capability_idx cap_idx;
    struct rte_mbuf* input_mbuf;
    struct crypto_sym_test_data* testdata = &aes_gcm_data;
    uint8_t *ciphertext, *digest_tag, *aad_data, *iv_data, *plaintext;
    int ret = 0;

    bha_logger_en();
    bha_ipsec_simulate();

    test_bha_crypto_init();

    //check feature
    rte_cryptodev_info_get(psec_cdevid, &dev_info);
    if (!(dev_info.feature_flags & RTE_CRYPTODEV_FF_SYMMETRIC_CRYPTO)) {
        TESTBHA_LOG(ERR, "crypto pico sec device[%d] req feature not met 0x%lx !!!\n", psec_cdevid, dev_info.feature_flags);
        return;
    }

    //get crypto capability
    cap_idx.type = RTE_CRYPTO_SYM_XFORM_AEAD;
    cap_idx.algo.aead = RTE_CRYPTO_AEAD_AES_GCM;
    capability = rte_cryptodev_sym_capability_get(psec_cdevid, &cap_idx);
    if (capability == NULL) {
        TESTBHA_LOG(ERR, "crypto pico sec device[%d] get capability aes gcm not met !!!\n", psec_cdevid);
        return;
    }

    if (rte_cryptodev_sym_capability_check_aead(
            capability, testdata->key.len, testdata->digest.len,
            testdata->aad.len, testdata->iv.len)
        < 0) {
        TESTBHA_LOG(ERR, "crypto pico sec device[%d] gcm alg check fail! key_len %d, digest_len %d, iv_len %d, aad_len %d\n", psec_cdevid, testdata->key.len, testdata->digest.len, testdata->iv.len, testdata->aad.len);
        return;
    }

    //create crypto op pool, mbuf nb 256, private=iv and max 16B
    crypto_op_pool = rte_crypto_op_pool_create("crypto_op_pool",
        RTE_CRYPTO_OP_TYPE_SYMMETRIC, 256, 128, MAXIMUM_IV_LENGTH,
        rte_socket_id());

    if (crypto_op_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create crypto op pool\n");

    //create pkt mbuf pool
    crypto_mbuf_pool = rte_mempool_lookup("crypto_mbuf_pool");
    if (crypto_mbuf_pool == NULL) {
        crypto_mbuf_pool = rte_pktmbuf_pool_create(
            "crypto_mbuf_pool",
            256, RTE_CACHE_LINE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE,
            rte_socket_id());
        if (crypto_mbuf_pool == NULL) {
            rte_exit(EXIT_FAILURE, "Cannot create crypto mbuf pool\n");
            return;
        }
    }

    TESTBHA_LOG(INFO, "AES GCM encrypt test start...");
    //create session
    ret = aead_session_create_and_init(psec_cdevid,
        RTE_CRYPTO_AEAD_AES_GCM,
        RTE_CRYPTO_AEAD_OP_ENCRYPT,
        testdata);
    if (ret < 0) {
        TESTBHA_LOG(ERR, "crypto pico sec device[%d] sym session create and init fail! ret %d\n", psec_cdevid, ret);
        return;
    }

    input_mbuf = rte_pktmbuf_alloc(crypto_mbuf_pool);
    memset(rte_pktmbuf_mtod(input_mbuf, uint8_t*), 0, rte_pktmbuf_tailroom(input_mbuf));

    ret = aead_operation_create(
        RTE_CRYPTO_AEAD_AES_GCM,
        RTE_CRYPTO_AEAD_OP_ENCRYPT,
        testdata,
        input_mbuf, NULL);
    if (ret < 0)
        return;

    rte_crypto_op_attach_sym_session(test_crypto_op, test_sym_sess);

    test_crypto_op->sym->m_src = input_mbuf;
    test_crypto_op->sym->m_dst = NULL;

    if (crypto_op_req_proc(psec_cdevid, test_crypto_op) < 0) {
        TESTBHA_LOG(ERR, "ERROR: crypto op req proc return error!!!");
        goto aes_gcm_exit;
    }

    aad_data = rte_pktmbuf_mtod_offset(test_crypto_op->sym->m_src, uint8_t*, 0);
    iv_data = rte_pktmbuf_mtod_offset(test_crypto_op->sym->m_src, uint8_t*, testdata->aad.len);
    ciphertext = rte_pktmbuf_mtod_offset(test_crypto_op->sym->m_src, uint8_t*,
        test_crypto_op->sym->aead.data.offset);
    digest_tag = ciphertext + testdata->ciphertext.len;

    //dump_mem_info((void*)aad_data, testdata->aad.len);
    //dump_mem_info((void*)iv_data, (testdata->iv.len - 4));
    //dump_mem_info((void*)ciphertext, testdata->ciphertext.len);
    //dump_mem_info((void*)digest_tag, testdata->digest.len);

    //check encryption data content
    if (0 != memcmp((void*)aad_data, testdata->aad.data, testdata->aad.len)) {
        TESTBHA_LOG(ERR, "ERROR: aad data check fail!!!");
        goto aes_gcm_exit;
    }
    if (0 != memcmp((void*)iv_data, testdata->iv.data + 4, (testdata->iv.len - 4))) { //remove 4B salt
        TESTBHA_LOG(ERR, "ERROR: iv data check fail!!!");
        goto aes_gcm_exit;
    }
    if (0 != memcmp((void*)ciphertext, testdata->ciphertext.data, testdata->ciphertext.len)) {
        TESTBHA_LOG(ERR, "ERROR: ciphertext check fail!!!");
        goto aes_gcm_exit;
    }
    if (0 != memcmp((void*)digest_tag, testdata->digest.data, testdata->digest.len)) {
        TESTBHA_LOG(ERR, "ERROR: digest check fail!!!");
        goto aes_gcm_exit;
    }
    TESTBHA_LOG(INFO, "AES GCM encrypt test free sym_sess(priv_sess), op, mbuf");
    rte_cryptodev_sym_session_clear(psec_cdevid, test_sym_sess);
    rte_cryptodev_sym_session_free(test_sym_sess);
    test_sym_sess = NULL;
    rte_crypto_op_free(test_crypto_op);
    test_crypto_op = NULL;
    rte_pktmbuf_free(input_mbuf);
    input_mbuf = NULL;
    TESTBHA_LOG(INFO, "AES GCM encrypt test complete and pass");

    TESTBHA_LOG(INFO, "AES GCM decrypt test start...");
    //create session
    ret = aead_session_create_and_init(psec_cdevid,
        RTE_CRYPTO_AEAD_AES_GCM,
        RTE_CRYPTO_AEAD_OP_DECRYPT,
        testdata);
    if (ret < 0) {
        TESTBHA_LOG(ERR, "crypto pico sec device[%d] sym session create and init fail! ret %d\n", psec_cdevid, ret);
        return;
    }

    input_mbuf = rte_pktmbuf_alloc(crypto_mbuf_pool);
    memset(rte_pktmbuf_mtod(input_mbuf, uint8_t*), 0, rte_pktmbuf_tailroom(input_mbuf));

    ret = aead_operation_create(
        RTE_CRYPTO_AEAD_AES_GCM,
        RTE_CRYPTO_AEAD_OP_DECRYPT,
        testdata,
        input_mbuf, NULL);
    if (ret < 0)
        return;

    rte_crypto_op_attach_sym_session(test_crypto_op, test_sym_sess);

    test_crypto_op->sym->m_src = input_mbuf;
    test_crypto_op->sym->m_dst = NULL;

    if (crypto_op_req_proc(psec_cdevid, test_crypto_op) < 0) {
        TESTBHA_LOG(ERR, "ERROR: crypto op req proc return error!!!");
        goto aes_gcm_exit;
    }

    aad_data = rte_pktmbuf_mtod_offset(test_crypto_op->sym->m_src, uint8_t*, 0);
    iv_data = rte_pktmbuf_mtod_offset(test_crypto_op->sym->m_src, uint8_t*, testdata->aad.len);
    plaintext = rte_pktmbuf_mtod_offset(test_crypto_op->sym->m_src, uint8_t*,
        test_crypto_op->sym->aead.data.offset);
    digest_tag = plaintext + testdata->plaintext.len;

    //dump_mem_info((void*)aad_data, testdata->aad.len);
    //dump_mem_info((void*)iv_data, (testdata->iv.len - 4));
    //dump_mem_info((void*)plaintext, testdata->plaintext.len);
    //dump_mem_info((void*)digest_tag, testdata->digest.len);

    //check encryption data content
    if (0 != memcmp((void*)aad_data, testdata->aad.data, testdata->aad.len)) {
        TESTBHA_LOG(ERR, "ERROR: aad data check fail!!!");
        goto aes_gcm_exit;
    }
    if (0 != memcmp((void*)iv_data, testdata->iv.data + 4, (testdata->iv.len - 4))) { //remove 4B salt
        TESTBHA_LOG(ERR, "ERROR: iv data check fail!!!");
        goto aes_gcm_exit;
    }
    if (0 != memcmp((void*)plaintext, testdata->plaintext.data, testdata->plaintext.len)) {
        TESTBHA_LOG(ERR, "ERROR: plaintext check fail!!!");
        goto aes_gcm_exit;
    }
    if (0 != memcmp((void*)digest_tag, testdata->digest.data, testdata->digest.len)) {
        TESTBHA_LOG(ERR, "ERROR: digest check fail!!!");
        goto aes_gcm_exit;
    }
    TESTBHA_LOG(INFO, "AES GCM decrypt test free sym_sess(priv_sess), op, mbuf");
    rte_cryptodev_sym_session_clear(psec_cdevid, test_sym_sess);
    rte_cryptodev_sym_session_free(test_sym_sess);
    test_sym_sess = NULL;
    rte_crypto_op_free(test_crypto_op);
    test_crypto_op = NULL;
    rte_pktmbuf_free(input_mbuf);
    input_mbuf = NULL;
    TESTBHA_LOG(INFO, "AES GCM decrypt test complete and pass");

aes_gcm_exit:
    bha_ipsec_abort();
    //TESTBHA_LOG(INFO, "AES GCM test mbuf mem pool count %d", rte_mempool_avail_count(crypto_mbuf_pool));
    //TESTBHA_LOG(INFO, "AES GCM test op mem pool count %d", rte_mempool_avail_count(crypto_op_pool));
    //TESTBHA_LOG(INFO, "AES GCM test priv sess mem pool count %d", rte_mempool_avail_count(priv_sess_pool));
    //TESTBHA_LOG(INFO, "AES GCM test sym sess mem pool count %d", rte_mempool_avail_count(sym_sess_pool));
    TESTBHA_LOG(INFO, "AES GCM test free all mem pool");
    rte_mempool_free(crypto_mbuf_pool);
    crypto_mbuf_pool = NULL;
    rte_mempool_free(crypto_op_pool);
    crypto_op_pool = NULL;
    rte_mempool_free(priv_sess_pool);
    priv_sess_pool = NULL;
    rte_mempool_free(sym_sess_pool);
    sym_sess_pool = NULL;
    //crypto device stop and close in quit cmd
}
