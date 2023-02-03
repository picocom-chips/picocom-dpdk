#include <time.h>

#include <rte_common.h>
#include <rte_hexdump.h>
#include <rte_mbuf.h>
#include <rte_malloc.h>
#include <rte_memcpy.h>
#include <rte_pause.h>
#include <rte_bus_vdev.h>
#include <rte_ether.h>

#include <rte_crypto.h>
#include <rte_cryptodev.h>
#include <rte_cryptodev_pmd.h>
#include <rte_string_fns.h>
#include <rte_security.h>


static inline void
debug_hexdump(FILE *file, const char *title, const void *buf, size_t len)
{
	if (rte_log_get_global_level() == RTE_LOG_DEBUG)
		rte_hexdump(file, title, buf, len);
}


/* Get number of bytes in X bits (rounding up) */
static uint32_t
ceil_byte_length(uint32_t num_bits)
{
	if (num_bits % 8)
		return ((num_bits >> 3) + 1);
	else
		return (num_bits >> 3);
}

#define TEST_ASSERT_SUCCESS(val, msg, ...) do { \
		typeof(val) _val = (val); \
		if (!(_val == 0)) { \
			printf("TestCase %s() line %d failed (err %d): " \
				msg "\n", __func__, __LINE__, _val, \
				##__VA_ARGS__); \
			return TEST_FAILED; \
		} \
} while (0)

#define TEST_ASSERT_FAIL(val, msg, ...) \
	TEST_ASSERT_SUCCESS(!(val), msg, ##__VA_ARGS__)

#define TEST_ASSERT_NOT_NULL(val, msg, ...) do { \
		if ((val) == NULL) { \
			printf("TestCase %s() line %d failed (null): " \
				msg "\n", __func__, __LINE__, ##__VA_ARGS__); \
			return TEST_FAILED;  \
		} \
} while (0)


#define TEST_ASSERT(cond, msg, ...) do {  \
		if (!(cond)) {  \
			printf("TestCase %s() line %d failed: " \
				msg "\n", __func__, __LINE__, ##__VA_ARGS__); \
			return TEST_FAILED;  \
		} \
} while (0)


#define TEST_SUCCESS EXIT_SUCCESS
#define TEST_FAILED  -1
#define MAXIMUM_IV_LENGTH				(16)
#define MAX_NUM_OPS_INFLIGHT            (4096)


#define MAX_NB_SESSIONS 4


#define DEFAULT_NUM_XFORMS              (2)

#define NUM_MBUFS                       (8191)
#define MBUF_CACHE_SIZE                 (256)

#define MBUF_DATAPAYLOAD_SIZE		(2048 + DIGEST_BYTE_LENGTH_SHA512)

#define MBUF_SIZE			(sizeof(struct rte_mbuf) + \
		RTE_PKTMBUF_HEADROOM + MBUF_DATAPAYLOAD_SIZE)


#define BYTE_LENGTH(x)				(x/8)
/* HASH DIGEST LENGTHS */
#define DIGEST_BYTE_LENGTH_SHA512		(BYTE_LENGTH(512))
#define DIGEST_BYTE_LENGTH_SNOW3G_UIA2		(BYTE_LENGTH(32))


#define IV_OFFSET			(sizeof(struct rte_crypto_op) + \
		sizeof(struct rte_crypto_sym_op) + DEFAULT_NUM_XFORMS * \
		sizeof(struct rte_crypto_sym_xform))



struct crypto_testsuite_params {
	struct rte_mempool *mbuf_pool;
	struct rte_mempool *large_mbuf_pool;
	struct rte_mempool *op_mpool;
	struct rte_mempool *session_mpool;
	struct rte_mempool *session_priv_mpool;
	struct rte_cryptodev_config conf;
	struct rte_cryptodev_qp_conf qp_conf;

	uint8_t valid_devs[RTE_CRYPTO_MAX_DEVS];
	uint8_t valid_dev_count;
};


struct crypto_unittest_params {
	struct rte_crypto_sym_xform cipher_xform;
	struct rte_crypto_sym_xform auth_xform;
	struct rte_crypto_sym_xform aead_xform;
#ifdef RTE_LIB_SECURITY
	struct rte_security_docsis_xform docsis_xform;
#endif

	union {
		struct rte_cryptodev_sym_session *sess;
#ifdef RTE_LIB_SECURITY
		struct rte_security_session *sec_session;
#endif
	};
#ifdef RTE_LIB_SECURITY
	enum rte_security_session_action_type type;
#endif
	struct rte_crypto_op *op;

	struct rte_mbuf *obuf, *ibuf;

	uint8_t *digest;
};


static struct crypto_testsuite_params testsuite_params = { NULL };
static struct crypto_unittest_params unittest_params;


static int sec_setup(void)
{
	struct crypto_testsuite_params *ts_params = &testsuite_params;
	struct rte_cryptodev_info info;
	uint32_t i = 0, nb_devs, dev_id;
	uint16_t qp_id;

	memset(ts_params, 0, sizeof(*ts_params));

	ts_params->mbuf_pool = rte_mempool_lookup("CRYPTO_MBUFPOOL");
	if (ts_params->mbuf_pool == NULL) {
		/* Not already created so create */
		ts_params->mbuf_pool = rte_pktmbuf_pool_create(
				"CRYPTO_MBUFPOOL",
				NUM_MBUFS, MBUF_CACHE_SIZE, 0, MBUF_SIZE,
				rte_socket_id());
		if (ts_params->mbuf_pool == NULL) {
			RTE_LOG(ERR, USER1, "Can't create CRYPTO_MBUFPOOL\n");
			return TEST_FAILED;
		}
	}

	ts_params->large_mbuf_pool = rte_mempool_lookup(
			"CRYPTO_LARGE_MBUFPOOL");
	if (ts_params->large_mbuf_pool == NULL) {
		/* Not already created so create */
		ts_params->large_mbuf_pool = rte_pktmbuf_pool_create(
				"CRYPTO_LARGE_MBUFPOOL",
				1, 0, 0, UINT16_MAX,
				rte_socket_id());
		if (ts_params->large_mbuf_pool == NULL) {
			RTE_LOG(ERR, USER1,
				"Can't create CRYPTO_LARGE_MBUFPOOL\n");
			return TEST_FAILED;
		}
	}

	ts_params->op_mpool = rte_crypto_op_pool_create(
			"MBUF_CRYPTO_SYM_OP_POOL",
			RTE_CRYPTO_OP_TYPE_SYMMETRIC,
			NUM_MBUFS, MBUF_CACHE_SIZE,
			DEFAULT_NUM_XFORMS *
			sizeof(struct rte_crypto_sym_xform) +
			MAXIMUM_IV_LENGTH,
			rte_socket_id());
	if (ts_params->op_mpool == NULL) {
		RTE_LOG(ERR, USER1, "Can't create CRYPTO_OP_POOL\n");
		return TEST_FAILED;
	}

	nb_devs = rte_cryptodev_count();
	if (nb_devs < 1) {
		RTE_LOG(WARNING, USER1, "No crypto devices found?\n");
		return TEST_FAILED;
	}

	/* Create list of valid crypto devs */
	for (i = 0; i < nb_devs; i++) {
		rte_cryptodev_info_get(i, &info);
			ts_params->valid_devs[ts_params->valid_dev_count++] = i;
	}

	if (ts_params->valid_dev_count < 1)
		return TEST_FAILED;

	/* Set up all the qps on the first of the valid devices found */

	dev_id = ts_params->valid_devs[0];

	rte_cryptodev_info_get(dev_id, &info);

	ts_params->conf.nb_queue_pairs = info.max_nb_queue_pairs;
	ts_params->conf.socket_id = SOCKET_ID_ANY;
	ts_params->conf.ff_disable = RTE_CRYPTODEV_FF_SECURITY;

	unsigned int session_size =
		rte_cryptodev_sym_get_private_session_size(dev_id);

	/*
	 * Create mempool with maximum number of sessions.
	 */
	if (info.sym.max_nb_sessions != 0 &&
			info.sym.max_nb_sessions < MAX_NB_SESSIONS) {
		RTE_LOG(ERR, USER1, "Device does not support "
				"at least %u sessions\n",
				MAX_NB_SESSIONS);
		return TEST_FAILED;
	}

	ts_params->session_mpool = rte_cryptodev_sym_session_pool_create(
			"test_sess_mp", MAX_NB_SESSIONS, 0, 0, 0,
			SOCKET_ID_ANY);
	TEST_ASSERT_NOT_NULL(ts_params->session_mpool,
			"session mempool allocation failed");

	ts_params->session_priv_mpool = rte_mempool_create(
			"test_sess_mp_priv",
			MAX_NB_SESSIONS,
			session_size,
			0, 0, NULL, NULL, NULL,
			NULL, SOCKET_ID_ANY,
			0);
	TEST_ASSERT_NOT_NULL(ts_params->session_priv_mpool,
			"session mempool allocation failed");


	TEST_ASSERT_SUCCESS(rte_cryptodev_configure(dev_id,
			&ts_params->conf),
			"Failed to configure cryptodev %u with %u qps",
			dev_id, ts_params->conf.nb_queue_pairs);


	ts_params->qp_conf.nb_descriptors = MAX_NUM_OPS_INFLIGHT;
	ts_params->qp_conf.mp_session = ts_params->session_mpool;
	ts_params->qp_conf.mp_session_private = ts_params->session_priv_mpool;

	for (qp_id = 0; qp_id < info.max_nb_queue_pairs; qp_id++) {
		TEST_ASSERT_SUCCESS(rte_cryptodev_queue_pair_setup(
			dev_id, qp_id, &ts_params->qp_conf,
			rte_cryptodev_socket_id(dev_id)),
			"Failed to setup queue pair %u on cryptodev %u",
			qp_id, dev_id);
	}

	rte_cryptodev_stats_reset(ts_params->valid_devs[0]);

        /* Start the device */
        TEST_ASSERT_SUCCESS(rte_cryptodev_start(ts_params->valid_devs[0]),
                        "Failed to start cryptodev %u",
                        ts_params->valid_devs[0]);


	return TEST_SUCCESS;
}


static int
create_wireless_algo_hash_session(uint8_t dev_id,
	const uint8_t *key, const uint8_t key_len,
	const uint8_t iv_len, const uint8_t auth_len,
	enum rte_crypto_auth_operation op,
	enum rte_crypto_auth_algorithm algo)
{
	uint8_t hash_key[key_len];
	int status;

	struct crypto_testsuite_params *ts_params = &testsuite_params;
	struct crypto_unittest_params *ut_params = &unittest_params;

	memcpy(hash_key, key, key_len);

	debug_hexdump(stdout, "key:", key, key_len);

	/* Setup Authentication Parameters */
	ut_params->auth_xform.type = RTE_CRYPTO_SYM_XFORM_AUTH;
	ut_params->auth_xform.next = NULL;

	ut_params->auth_xform.auth.op = op;
	ut_params->auth_xform.auth.algo = algo;
	ut_params->auth_xform.auth.key.length = key_len;
	ut_params->auth_xform.auth.key.data = hash_key;
	ut_params->auth_xform.auth.digest_length = auth_len;
	ut_params->auth_xform.auth.iv.offset = IV_OFFSET;
	ut_params->auth_xform.auth.iv.length = iv_len;
	ut_params->sess = rte_cryptodev_sym_session_create(
			ts_params->session_mpool);

	status = rte_cryptodev_sym_session_init(dev_id, ut_params->sess,
			&ut_params->auth_xform,
			ts_params->session_priv_mpool);
        if (status < 0) {

		TEST_ASSERT(status < 0,"Session creation succeeded unexpectedly");
                rte_cryptodev_sym_session_free(ut_params->sess);
                return status;
        }

	TEST_ASSERT_NOT_NULL(ut_params->sess, "Session creation failed");
	return 0;
}



static int
create_wireless_algo_hash_operation(const uint8_t *auth_tag,
		unsigned int auth_tag_len,
		const uint8_t *iv, unsigned int iv_len,
		unsigned int data_pad_len,
		enum rte_crypto_auth_operation op,
		unsigned int auth_len, unsigned int auth_offset)
{
	struct crypto_testsuite_params *ts_params = &testsuite_params;

	struct crypto_unittest_params *ut_params = &unittest_params;

	/* Generate Crypto op data structure */
	ut_params->op = rte_crypto_op_alloc(ts_params->op_mpool,
			RTE_CRYPTO_OP_TYPE_SYMMETRIC);
	TEST_ASSERT_NOT_NULL(ut_params->op,
		"Failed to allocate pktmbuf offload");

	/* Set crypto operation data parameters */
	rte_crypto_op_attach_sym_session(ut_params->op, ut_params->sess);

	struct rte_crypto_sym_op *sym_op = ut_params->op->sym;

	/* set crypto operation source mbuf */
	sym_op->m_src = ut_params->ibuf;

	/* iv */
	rte_memcpy(rte_crypto_op_ctod_offset(ut_params->op, uint8_t *, IV_OFFSET),
			iv, iv_len);
	/* digest */
	sym_op->auth.digest.data = (uint8_t *)rte_pktmbuf_append(
					ut_params->ibuf, auth_tag_len);

	TEST_ASSERT_NOT_NULL(sym_op->auth.digest.data,
				"no room to append auth tag");
	ut_params->digest = sym_op->auth.digest.data;
	sym_op->auth.digest.phys_addr = rte_pktmbuf_iova_offset(
			ut_params->ibuf, data_pad_len);
	if (op == RTE_CRYPTO_AUTH_OP_GENERATE)
		memset(sym_op->auth.digest.data, 0, auth_tag_len);
	else
		rte_memcpy(sym_op->auth.digest.data, auth_tag, auth_tag_len);

	debug_hexdump(stdout, "digest:",
		sym_op->auth.digest.data,
		auth_tag_len);

	sym_op->auth.data.length = auth_len;
	sym_op->auth.data.offset = auth_offset;

	return 0;
}

static struct rte_crypto_op *
process_crypto_request(uint8_t dev_id, struct rte_crypto_op *op)
{

	if (rte_cryptodev_enqueue_burst(dev_id, 0, &op, 1) != 1) {
		RTE_LOG(ERR, USER1, "Error sending packet for encryption\n");
		return NULL;
	}

	op = NULL;

	while (rte_cryptodev_dequeue_burst(dev_id, 0, &op, 1) == 0)
		rte_pause();

	if (op->status != RTE_CRYPTO_OP_STATUS_SUCCESS) {
		RTE_LOG(DEBUG, USER1, "Operation status %d\n", op->status);
		return NULL;
	}
        

	return op;
}

static void crypto_free_memory(void)
{

	struct crypto_unittest_params *ut_params = &unittest_params;
	struct crypto_testsuite_params *ts_params = &testsuite_params;

	/*free sess*/
	if (ut_params->sess) {
                        rte_cryptodev_sym_session_clear(
                                        ts_params->valid_devs[0],
                                        ut_params->sess);
                        rte_cryptodev_sym_session_free(ut_params->sess);
                        ut_params->sess = NULL;
        }


	/* free crypto operation structure */
	if (ut_params->op)
		rte_crypto_op_free(ut_params->op);

	/*
	 * free mbuf - both obuf and ibuf are usually the same,
	 * so check if they point at the same address is necessary,
	 * to avoid freeing the mbuf twice.
	 */
	if (ut_params->obuf) {
		rte_pktmbuf_free(ut_params->obuf);
		if (ut_params->ibuf == ut_params->obuf)
			ut_params->ibuf = 0;
		ut_params->obuf = 0;
	}
	if (ut_params->ibuf) {
		rte_pktmbuf_free(ut_params->ibuf);
		ut_params->ibuf = 0;
	}
}


static int snow3gf9_authentication(uint8_t* macI, uint8_t *key, uint8_t key_len, uint8_t *iv, unsigned int iv_len, uint8_t *data, unsigned data_len)
{
	struct crypto_testsuite_params *ts_params = &testsuite_params;
	struct crypto_unittest_params *ut_params = &unittest_params;

	int retval;
	unsigned plaintext_pad_len;
	unsigned plaintext_len;
	uint8_t *plaintext;
	struct rte_cryptodev_info dev_info;
 	unsigned validAuthLenInBits_len = data_len;
        unsigned digest_len  = 4;


	rte_cryptodev_info_get(ts_params->valid_devs[0], &dev_info);
	uint64_t feat_flags = dev_info.feature_flags;

	if (!(feat_flags & RTE_CRYPTODEV_FF_NON_BYTE_ALIGNED_DATA) &&
			((data_len % 8) != 0)) {
		printf("Device doesn't support NON-Byte Aligned Data.\n");
		return -ENOTSUP;
	}

	/* Verify the capabilities */
	struct rte_cryptodev_sym_capability_idx cap_idx;
	cap_idx.type = RTE_CRYPTO_SYM_XFORM_AUTH;
	cap_idx.algo.auth = RTE_CRYPTO_AUTH_SNOW3G_UIA2;
	if (rte_cryptodev_sym_capability_get(ts_params->valid_devs[0],
			&cap_idx) == NULL)
		return -ENOTSUP;

	/* Create SNOW 3G session */
	retval = create_wireless_algo_hash_session(ts_params->valid_devs[0],
			key, key_len,
			iv_len, digest_len,
			RTE_CRYPTO_AUTH_OP_GENERATE,
			RTE_CRYPTO_AUTH_SNOW3G_UIA2);
	if (retval < 0)
		return retval;

	/* alloc mbuf and set payload */
	ut_params->ibuf = rte_pktmbuf_alloc(ts_params->mbuf_pool);

	memset(rte_pktmbuf_mtod(ut_params->ibuf, uint8_t *), 0,
	rte_pktmbuf_tailroom(ut_params->ibuf));

	plaintext_len = ceil_byte_length(data_len);
	/* Append data which is padded to a multiple of */
	/* the algorithms block size */
	plaintext_pad_len = RTE_ALIGN_CEIL(plaintext_len, 16);
	plaintext = (uint8_t *)rte_pktmbuf_append(ut_params->ibuf,
				plaintext_pad_len);
	memcpy(plaintext, data, plaintext_len);

        debug_hexdump(stdout, "plaintext:", plaintext, plaintext_len);


	/* Create SNOW 3G operation */
	retval = create_wireless_algo_hash_operation(NULL, digest_len,
			iv, iv_len,
			plaintext_pad_len, RTE_CRYPTO_AUTH_OP_GENERATE,
			validAuthLenInBits_len,
			0);
	if (retval < 0)
		return retval;

		
	ut_params->op = process_crypto_request(ts_params->valid_devs[0], ut_params->op);
	ut_params->obuf = ut_params->op->sym->m_src;
	TEST_ASSERT_NOT_NULL(ut_params->op, "failed to retrieve obuf");
	ut_params->digest = rte_pktmbuf_mtod(ut_params->obuf, uint8_t *)
			+ plaintext_pad_len;

	debug_hexdump(stdout, "digest:", ut_params->digest, 4);
	
	/*copy to macI*/
	rte_memcpy(macI, ut_params->digest, 4);

	/*crypto free memory*/
	crypto_free_memory();

	return 0;
}

static void cryptodev_device_stop(void)
{
	struct crypto_testsuite_params *ts_params = &testsuite_params;
	struct rte_cryptodev_stats stats;

	rte_cryptodev_stats_get(ts_params->valid_devs[0], &stats);

	/* Stop the device */
	rte_cryptodev_stop(ts_params->valid_devs[0]);
}

static void mpool_check_memory(void)
{
	struct crypto_testsuite_params *ts_params = &testsuite_params;

    	if (ts_params->session_mpool != NULL)
       		printf("SESSION_MPOOL CRYPTO_MBUFPOOL count %u\n", rte_mempool_avail_count(ts_params->session_mpool));

    	if (ts_params->session_priv_mpool != NULL)
       		printf("SESSION_PRIV_MPOOL CRYPTO_MBUFPOOL count %u\n", rte_mempool_avail_count(ts_params->session_priv_mpool));

    	if (ts_params->op_mpool != NULL) {
		printf("OP_MPOOL CRYPTO_OP_POOL count %u\n", rte_mempool_avail_count(ts_params->op_mpool));
    	}

    	if (ts_params->mbuf_pool != NULL)
		printf("MBUF_POOL CRYPTO_MBUFPOOL count %u\n", rte_mempool_avail_count(ts_params->mbuf_pool));

    	if (ts_params->large_mbuf_pool != NULL)
        	RTE_LOG(DEBUG, USER1, "CRYPTO_MBUFPOOL count %u\n", rte_mempool_avail_count(ts_params->large_mbuf_pool));
}

static int snow3gf9(uint8_t* macI, uint8_t* key, uint32_t count, uint32_t fresh, uint32_t dir, uint8_t *data, uint64_t length)
{
   uint32_t IV[4];
	
   /* Prepare the Initialization Vector (IV) for SNOW3G initialization as in    section 4.4. */
   IV[0] = ntohl(count);
   IV[1] = ntohl(fresh);
   IV[2] = ntohl(count ^ (dir << 31));
   IV[3] = ntohl(fresh ^ (dir << 15));

    return snow3gf9_authentication(macI, key, 16, (uint8_t *)IV, 16, data, length);
}

/************snow3g authentication verify************************************************************/

static int 
snow3gf9_authentication_verify(uint8_t* macI, uint8_t mac_len, uint8_t *key, uint8_t key_len, uint8_t *iv, unsigned int iv_len, uint8_t *data, unsigned data_len)
{
	struct crypto_testsuite_params *ts_params = &testsuite_params;
	struct crypto_unittest_params *ut_params = &unittest_params;

	int retval;
	unsigned plaintext_pad_len;
	unsigned plaintext_len;
	uint8_t *plaintext;
 	unsigned validAuthLenInBits_len = data_len;

	/* Verify the capabilities */
	struct rte_cryptodev_sym_capability_idx cap_idx;
	cap_idx.type = RTE_CRYPTO_SYM_XFORM_AUTH;
	cap_idx.algo.auth = RTE_CRYPTO_AUTH_SNOW3G_UIA2;
	if (rte_cryptodev_sym_capability_get(ts_params->valid_devs[0],
			&cap_idx) == NULL)
		return -ENOTSUP;

	/* Create SNOW 3G session */
	retval = create_wireless_algo_hash_session(ts_params->valid_devs[0],
				key, key_len,
				iv_len, mac_len,
				RTE_CRYPTO_AUTH_OP_VERIFY,
				RTE_CRYPTO_AUTH_SNOW3G_UIA2);
	if (retval < 0)
		return retval;
	/* alloc mbuf and set payload */
	ut_params->ibuf = rte_pktmbuf_alloc(ts_params->mbuf_pool);

	memset(rte_pktmbuf_mtod(ut_params->ibuf, uint8_t *), 0,
	rte_pktmbuf_tailroom(ut_params->ibuf));

	plaintext_len = ceil_byte_length(data_len);
	/* Append data which is padded to a multiple of */
	/* the algorithms block size */
	plaintext_pad_len = RTE_ALIGN_CEIL(plaintext_len, 16);
	plaintext = (uint8_t *)rte_pktmbuf_append(ut_params->ibuf,
				plaintext_pad_len);
	memcpy(plaintext, data, plaintext_len);

	/* Create SNOW 3G operation */
	retval = create_wireless_algo_hash_operation(macI,
			mac_len,
			iv, iv_len,
			plaintext_pad_len,
			RTE_CRYPTO_AUTH_OP_VERIFY,
			validAuthLenInBits_len,
			0);
	if (retval < 0)
		return retval;

	ut_params->op = process_crypto_request(ts_params->valid_devs[0],
				ut_params->op);
	TEST_ASSERT_NOT_NULL(ut_params->op, "failed to retrieve obuf");
	ut_params->obuf = ut_params->op->sym->m_src;
	ut_params->digest = rte_pktmbuf_mtod(ut_params->obuf, uint8_t *)
				+ plaintext_pad_len;

	/* Validate obuf */
	if (ut_params->op->status == RTE_CRYPTO_OP_STATUS_SUCCESS)
		return 0;
	else
		return -1;

	return 0;
}

static int snow3gf9_verify(uint8_t* macI, uint8_t mac_len, uint8_t* key, uint32_t count, uint32_t fresh, uint32_t dir, uint8_t *data, uint64_t length)
{
	uint32_t IV[4];
	
   	/* Prepare the Initialization Vector (IV) for SNOW3G initialization as in    section 4.4. */
   	IV[0] = ntohl(count);
   	IV[1] = ntohl(fresh);
   	IV[2] = ntohl(count ^ (dir << 31));
   	IV[3] = ntohl(fresh ^ (dir << 15));

    	return snow3gf9_authentication_verify(macI, mac_len, key, 16, (uint8_t *)IV, 16, data, length);
}

/************snow3g decryption************************************************************/


#ifndef TEST_TRACE_FAILURE
# define TEST_TRACE_FAILURE(_file, _line, _func)
#endif

/* Compare two buffers (length in bytes) */
#define TEST_ASSERT_BUFFERS_ARE_EQUAL(a, b, len,  msg, ...) do {	\
	if (memcmp(a, b, len)) {                                        \
		printf("TestCase %s() line %d failed: "              \
			msg "\n", __func__, __LINE__, ##__VA_ARGS__);    \
		TEST_TRACE_FAILURE(__FILE__, __LINE__, __func__);    \
		return TEST_FAILED;                                  \
	}                                                        \
} while (0)


/* Compare two buffers (length in bits) */
#define TEST_ASSERT_BUFFERS_ARE_EQUAL_BIT(a, b, len, msg, ...) do {	\
	uint8_t _last_byte_a, _last_byte_b;                       \
	uint8_t _last_byte_mask, _last_byte_bits;                  \
	TEST_ASSERT_BUFFERS_ARE_EQUAL(a, b, (len >> 3), msg);     \
	if (len % 8) {                                              \
		_last_byte_bits = len % 8;                   \
		_last_byte_mask = ~((1 << (8 - _last_byte_bits)) - 1); \
		_last_byte_a = ((const uint8_t *)a)[len >> 3];            \
		_last_byte_b = ((const uint8_t *)b)[len >> 3];            \
		_last_byte_a &= _last_byte_mask;                     \
		_last_byte_b &= _last_byte_mask;                    \
		if (_last_byte_a != _last_byte_b) {                  \
			printf("TestCase %s() line %d failed: "              \
				msg "\n", __func__, __LINE__, ##__VA_ARGS__);\
			TEST_TRACE_FAILURE(__FILE__, __LINE__, __func__);    \
			return TEST_FAILED;                                  \
		}                                                        \
	}                                                            \
} while (0)


struct snow3g_test_data {
	struct {
		uint8_t data[64];
		unsigned len;
	} key;

	struct {
		uint8_t data[64] __rte_aligned(16);
		unsigned len;
	} cipher_iv;

	struct {
		uint8_t data[1024];
		unsigned len; /* length must be in Bits */
	} plaintext;

	struct {
		uint8_t data[1024];
		unsigned len; /* length must be in Bits */
	} ciphertext;

	struct {
		unsigned len;
	} validDataLenInBits;

	struct {
		unsigned len;
	} validCipherLenInBits;

	struct {
		unsigned len;
	} validAuthLenInBits;

	struct {
		uint8_t data[64];
		unsigned len;
	} auth_iv;

	struct {
		uint8_t data[64];
		unsigned int len; /* length must be in Bytes */
		unsigned int offset_bytes; /* offset must be in Bytes */
	} digest;

	struct {
		unsigned int len_bits; /* length must be in Bits */
		unsigned int offset_bits;
	} cipher;

	struct {
		unsigned int len_bits; /* length must be in Bits */
		unsigned int offset_bits;
	} auth;
};

struct snow3g_test_data snow3g_test_case_1 = {
	.key = {
		.data = {
			0x2B, 0xD6, 0x45, 0x9F, 0x82, 0xC5, 0xB3, 0x00,
			0x95, 0x2C, 0x49, 0x10, 0x48, 0x81, 0xFF, 0x48
		},
		.len = 16
	},
	.cipher_iv = {
		.data = {
			0x72, 0xA4, 0xF2, 0x0F, 0x64, 0x00, 0x00, 0x00,
			0x72, 0xA4, 0xF2, 0x0F, 0x64, 0x00, 0x00, 0x00
		},
		.len = 16
	},
	.plaintext = {
		.data = {
			0x7E, 0xC6, 0x12, 0x72, 0x74, 0x3B, 0xF1, 0x61,
			0x47, 0x26, 0x44, 0x6A, 0x6C, 0x38, 0xCE, 0xD1,
			0x66, 0xF6, 0xCA, 0x76, 0xEB, 0x54, 0x30, 0x04,
			0x42, 0x86, 0x34, 0x6C, 0xEF, 0x13, 0x0F, 0x92,
			0x92, 0x2B, 0x03, 0x45, 0x0D, 0x3A, 0x99, 0x75,
			0xE5, 0xBD, 0x2E, 0xA0, 0xEB, 0x55, 0xAD, 0x8E,
			0x1B, 0x19, 0x9E, 0x3E, 0xC4, 0x31, 0x60, 0x20,
			0xE9, 0xA1, 0xB2, 0x85, 0xE7, 0x62, 0x79, 0x53,
			0x59, 0xB7, 0xBD, 0xFD, 0x39, 0xBE, 0xF4, 0xB2,
			0x48, 0x45, 0x83, 0xD5, 0xAF, 0xE0, 0x82, 0xAE,
			0xE6, 0x38, 0xBF, 0x5F, 0xD5, 0xA6, 0x06, 0x19,
			0x39, 0x01, 0xA0, 0x8F, 0x4A, 0xB4, 0x1A, 0xAB,
			0x9B, 0x13, 0x48, 0x80
		},
		.len = 800
	},
	.ciphertext = {
		.data = {
			0x8C, 0xEB, 0xA6, 0x29, 0x43, 0xDC, 0xED, 0x3A,
			0x09, 0x90, 0xB0, 0x6E, 0xA1, 0xB0, 0xA2, 0xC4,
			0xFB, 0x3C, 0xED, 0xC7, 0x1B, 0x36, 0x9F, 0x42,
			0xBA, 0x64, 0xC1, 0xEB, 0x66, 0x65, 0xE7, 0x2A,
			0xA1, 0xC9, 0xBB, 0x0D, 0xEA, 0xA2, 0x0F, 0xE8,
			0x60, 0x58, 0xB8, 0xBA, 0xEE, 0x2C, 0x2E, 0x7F,
			0x0B, 0xEC, 0xCE, 0x48, 0xB5, 0x29, 0x32, 0xA5,
			0x3C, 0x9D, 0x5F, 0x93, 0x1A, 0x3A, 0x7C, 0x53,
			0x22, 0x59, 0xAF, 0x43, 0x25, 0xE2, 0xA6, 0x5E,
			0x30, 0x84, 0xAD, 0x5F, 0x6A, 0x51, 0x3B, 0x7B,
			0xDD, 0xC1, 0xB6, 0x5F, 0x0A, 0xA0, 0xD9, 0x7A,
			0x05, 0x3D, 0xB5, 0x5A, 0x88, 0xC4, 0xC4, 0xF9,
			0x60, 0x5E, 0x41, 0x40
		},
		.len = 800
	},
	.cipher = {
		.offset_bits = 0
	},
	.validDataLenInBits = {
		.len = 798
	},
	.validCipherLenInBits = {
		.len = 800
	},
	.auth_iv = {
		.data = {
			 0x72, 0xA4, 0xF2, 0x0F, 0x64, 0x00, 0x00, 0x00,
			 0x72, 0xA4, 0xF2, 0x0F, 0x64, 0x00, 0x00, 0x00
		},
		.len = 16
	}
};

static int
create_wireless_algo_cipher_session(uint8_t dev_id,
			enum rte_crypto_cipher_operation op,
			enum rte_crypto_cipher_algorithm algo,
			const uint8_t *key, const uint8_t key_len,
			uint8_t iv_len)
{
	uint8_t cipher_key[key_len];
	int status;
	struct crypto_testsuite_params *ts_params = &testsuite_params;
	struct crypto_unittest_params *ut_params = &unittest_params;

	memcpy(cipher_key, key, key_len);

	/* Setup Cipher Parameters */
	ut_params->cipher_xform.type = RTE_CRYPTO_SYM_XFORM_CIPHER;
	ut_params->cipher_xform.next = NULL;

	ut_params->cipher_xform.cipher.algo = algo;
	ut_params->cipher_xform.cipher.op = op;
	ut_params->cipher_xform.cipher.key.data = cipher_key;
	ut_params->cipher_xform.cipher.key.length = key_len;
	ut_params->cipher_xform.cipher.iv.offset = IV_OFFSET;
	ut_params->cipher_xform.cipher.iv.length = iv_len;

	debug_hexdump(stdout, "key:", key, key_len);

	/* Create Crypto session */
	ut_params->sess = rte_cryptodev_sym_session_create(
			ts_params->session_mpool);

	status = rte_cryptodev_sym_session_init(dev_id, ut_params->sess,
			&ut_params->cipher_xform,
			ts_params->session_priv_mpool);
	   if (status < 0) {

                TEST_ASSERT(status < 0,"Session creation succeeded unexpectedly");
                rte_cryptodev_sym_session_free(ut_params->sess);
                return status;
        }

        TEST_ASSERT_NOT_NULL(ut_params->sess, "Session creation failed");

	return 0;
}


static int
create_wireless_algo_cipher_operation(const uint8_t *iv, uint8_t iv_len,
			unsigned int cipher_len,
			unsigned int cipher_offset)
{
	struct crypto_testsuite_params *ts_params = &testsuite_params;
	struct crypto_unittest_params *ut_params = &unittest_params;

	/* Generate Crypto op data structure */
	ut_params->op = rte_crypto_op_alloc(ts_params->op_mpool,
				RTE_CRYPTO_OP_TYPE_SYMMETRIC);
	TEST_ASSERT_NOT_NULL(ut_params->op,
				"Failed to allocate pktmbuf offload");

	/* Set crypto operation data parameters */
	rte_crypto_op_attach_sym_session(ut_params->op, ut_params->sess);

	struct rte_crypto_sym_op *sym_op = ut_params->op->sym;

	/* set crypto operation source mbuf */
	sym_op->m_src = ut_params->ibuf;

	/* iv */
	rte_memcpy(rte_crypto_op_ctod_offset(ut_params->op, uint8_t *, IV_OFFSET),
			iv, iv_len);
	sym_op->cipher.data.length = cipher_len;
	sym_op->cipher.data.offset = cipher_offset;
	return 0;
}

static int test_snow3g_decryption(const struct snow3g_test_data *tdata)
{
	struct crypto_testsuite_params *ts_params = &testsuite_params;
	struct crypto_unittest_params *ut_params = &unittest_params;

	int retval;

	uint8_t *plaintext, *ciphertext;
	unsigned ciphertext_pad_len;
	unsigned ciphertext_len;

	/* Verify the capabilities */
	struct rte_cryptodev_sym_capability_idx cap_idx;
	cap_idx.type = RTE_CRYPTO_SYM_XFORM_CIPHER;
	cap_idx.algo.cipher = RTE_CRYPTO_CIPHER_SNOW3G_UEA2;
	if (rte_cryptodev_sym_capability_get(ts_params->valid_devs[0],
			&cap_idx) == NULL)
		return -ENOTSUP;

	/* Create SNOW 3G session */
	retval = create_wireless_algo_cipher_session(ts_params->valid_devs[0],
					RTE_CRYPTO_CIPHER_OP_DECRYPT,
					RTE_CRYPTO_CIPHER_SNOW3G_UEA2,
					tdata->key.data, tdata->key.len,
					tdata->cipher_iv.len);
	if (retval < 0)
		return retval;

	ut_params->ibuf = rte_pktmbuf_alloc(ts_params->mbuf_pool);

	/* Clear mbuf payload */
	memset(rte_pktmbuf_mtod(ut_params->ibuf, uint8_t *), 0,
	       rte_pktmbuf_tailroom(ut_params->ibuf));

	ciphertext_len = ceil_byte_length(tdata->ciphertext.len);
	/* Append data which is padded to a multiple of */
	/* the algorithms block size */
	ciphertext_pad_len = RTE_ALIGN_CEIL(ciphertext_len, 16);
	ciphertext = (uint8_t *)rte_pktmbuf_append(ut_params->ibuf,
				ciphertext_pad_len);
	memcpy(ciphertext, tdata->ciphertext.data, ciphertext_len);

	debug_hexdump(stdout, "ciphertext:", ciphertext, ciphertext_len);

	/* Create SNOW 3G operation */
	retval = create_wireless_algo_cipher_operation(tdata->cipher_iv.data,
					tdata->cipher_iv.len,
					tdata->validCipherLenInBits.len,
					tdata->cipher.offset_bits);
	if (retval < 0)
		return retval;

        ut_params->op = process_crypto_request(ts_params->valid_devs[0], ut_params->op);

	TEST_ASSERT_NOT_NULL(ut_params->op, "failed to retrieve obuf");
	ut_params->obuf = ut_params->op->sym->m_dst;
	if (ut_params->obuf)
		plaintext = rte_pktmbuf_mtod(ut_params->obuf, uint8_t *);
	else
		plaintext = ciphertext;

	debug_hexdump(stdout, "plaintext:", plaintext, ciphertext_len);

	/* Validate obuf */
	TEST_ASSERT_BUFFERS_ARE_EQUAL_BIT(plaintext,
				tdata->plaintext.data,
				tdata->validDataLenInBits.len,
				"SNOW 3G Plaintext data not as expected");
	return 0;
}


static int
test_snow3g_encryption(const struct snow3g_test_data *tdata)
{
	struct crypto_testsuite_params *ts_params = &testsuite_params;
	struct crypto_unittest_params *ut_params = &unittest_params;

	int retval;
	uint8_t *plaintext, *ciphertext;
	unsigned plaintext_pad_len;
	unsigned plaintext_len;
	struct rte_cryptodev_info dev_info;

	rte_cryptodev_info_get(ts_params->valid_devs[0], &dev_info);
	uint64_t feat_flags = dev_info.feature_flags;

	if ((!(feat_flags & RTE_CRYPTODEV_FF_SYM_RAW_DP))) {
		printf("Device doesn't support RAW data-path APIs.\n");
		return -ENOTSUP;
	}

	/* Verify the capabilities */
	struct rte_cryptodev_sym_capability_idx cap_idx;
	cap_idx.type = RTE_CRYPTO_SYM_XFORM_CIPHER;
	cap_idx.algo.cipher = RTE_CRYPTO_CIPHER_SNOW3G_UEA2;
	if (rte_cryptodev_sym_capability_get(ts_params->valid_devs[0],
			&cap_idx) == NULL)
		return -ENOTSUP;

	/* Create SNOW 3G session */
	retval = create_wireless_algo_cipher_session(ts_params->valid_devs[0],
					RTE_CRYPTO_CIPHER_OP_ENCRYPT,
					RTE_CRYPTO_CIPHER_SNOW3G_UEA2,
					tdata->key.data, tdata->key.len,
					tdata->cipher_iv.len);
	if (retval < 0)
		return retval;

	ut_params->ibuf = rte_pktmbuf_alloc(ts_params->mbuf_pool);

	/* Clear mbuf payload */
	memset(rte_pktmbuf_mtod(ut_params->ibuf, uint8_t *), 0,
	       rte_pktmbuf_tailroom(ut_params->ibuf));

	plaintext_len = ceil_byte_length(tdata->plaintext.len);
	/* Append data which is padded to a multiple of */
	/* the algorithms block size */
	plaintext_pad_len = RTE_ALIGN_CEIL(plaintext_len, 16);
	plaintext = (uint8_t *)rte_pktmbuf_append(ut_params->ibuf,
				plaintext_pad_len);
	memcpy(plaintext, tdata->plaintext.data, plaintext_len);

	debug_hexdump(stdout, "plaintext:", plaintext, plaintext_len);

	/* Create SNOW 3G operation */
	retval = create_wireless_algo_cipher_operation(tdata->cipher_iv.data,
					tdata->cipher_iv.len,
					tdata->validCipherLenInBits.len,
					0);
	if (retval < 0)
		return retval;

        ut_params->op = process_crypto_request(ts_params->valid_devs[0], ut_params->op);

	TEST_ASSERT_NOT_NULL(ut_params->op, "failed to retrieve obuf");

	ut_params->obuf = ut_params->op->sym->m_dst;
	if (ut_params->obuf)
		ciphertext = rte_pktmbuf_mtod(ut_params->obuf, uint8_t *);
	else
		ciphertext = plaintext;

	debug_hexdump(stdout, "ciphertext:", ciphertext, plaintext_len);

	/* Validate obuf */
	TEST_ASSERT_BUFFERS_ARE_EQUAL_BIT(
		ciphertext,
		tdata->ciphertext.data,
		tdata->validDataLenInBits.len,
		"SNOW 3G Ciphertext data not as expected");
	return 0;
}

int main(int argc, char **argv)
{
  int ret = 0;
  int i = 0;
  uint8_t macI[4] = {1,2,3,4};
  uint32_t count = 0x38a6f056;
  uint32_t fresh = 0xf8000000;
  uint32_t dir = 0;
  uint64_t length = 88;
  uint8_t data[16] = {0x33, 0x32, 0x34, 0x62, 0x63, 0x39, 0x38, 0x61, 0x37, 0x34, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t key[16] = {0x2b, 0xd6, 0x45, 0x9f, 0x82, 0xc5, 0xb3, 0x00, 0x95, 0x2c, 0x49, 0x10, 0x48, 0x81, 0xff, 0x48};
  uint8_t data1[512] = { 0xD0, 0xA7, 0xD4, 0x63, 0xDF, 0x9F, 0xB2, 0xB2,0x78, 0x83, 0x3F, 0xA0, 0x2E, 0x23, 0x5A, 0xA1,
                        0x72, 0xBD, 0x97, 0x0C, 0x14, 0x73, 0xE1, 0x29,0x07, 0xFB, 0x64, 0x8B, 0x65, 0x99, 0xAA, 0xA0,
                        0xB2, 0x4A, 0x03, 0x86, 0x65, 0x42, 0x2B, 0x20,0xA4, 0x99, 0x27, 0x6A, 0x50, 0x42, 0x70, 0x09};
  uint8_t key1[16] = { 0xC7, 0x36, 0xC6, 0xAA, 0xB2, 0x2B, 0xFF, 0xF9,0x1E, 0x26, 0x98, 0xD2, 0xE2, 0x2A, 0xD5, 0x7E};

  ret = rte_eal_init(argc, argv);
  if (ret < 0) {
          ret = -1;
	  return ret;
  }

  printf("sec setup\n");
  sec_setup();

  printf("\nsnow3g decryption:\n");
  test_snow3g_decryption(&snow3g_test_case_1);
  crypto_free_memory();  
  mpool_check_memory();

  printf("\nsnow3g encryption:\n");
  test_snow3g_encryption(&snow3g_test_case_1);
  crypto_free_memory();  
  mpool_check_memory();

  for(i = 0; i < 10000; i++)
  {
    printf("\nsnow3gf9 authentication:\n");  
    dir = 0, fresh = 0xf8000000, count = 0x38a6f056, length = 88;
    snow3gf9(macI, key, count, fresh, dir, data, length);
    printf("macI: %x %x %x %x\n", macI[0], macI[1], macI[2], macI[3]);

    printf("\nsnow3gf9 authentication verify:\n");  
    ret = snow3gf9_verify(macI, 4, key, count, fresh, dir, data, length);
    if(ret != 0)
    {
	   printf("snow3gf9 authentication verify %d Failure\n", ret);  
	   break;
    }
    printf("snow3gf9 authentication verify %d Success\n", ret);  
    crypto_free_memory();  
 
    printf("\nsnow3gf9 authentication:\n");  
    length = 384, count =  0x14793E41, fresh = 0x0397E8FD, dir = 1;
    snow3gf9(macI, key1, count, fresh, dir, data1, length);
    printf("macI: %x %x %x %x\n", macI[0], macI[1], macI[2], macI[3]);

    printf("\nsnow3gf9 authentication verify:\n");  
    ret = snow3gf9_verify(macI, 4, key1, count, fresh, dir, data1, length);
    if(ret != 0)
    {
	   printf("snow3gf9 authentication verify %d Failure\n", ret);  
	   break;
    }
    printf("snow3gf9 authentication verify %d Success\n", ret);  
    crypto_free_memory();  

    mpool_check_memory();
  }

  cryptodev_device_stop();

  return ret;

}


