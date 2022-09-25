/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */
#include <rte_memcpy.h>
#include <rte_mbuf.h>
#include <rte_ethdev.h>
#include <rte_lcore.h>
#include <rte_log.h>
#include <rte_errno.h>
#include <rte_string_fns.h>
#include <rte_ether.h>

#include "pc802_ethdev.h"
#include "rte_pmd_pc802.h"

/* Used for the multi-process communication */
#define PDUMP_MP	"mp_pdump"
#define PDUMP_RING	"pdump_ring"
#define BURST_SIZE 32

struct ip_options_timestamp {
	uint8_t  type;
	uint8_t  length ;
	uint8_t  pointer;
	uint8_t  OF_FL;
	uint32_t time_stamp;
};

#define IP_HDR_SIZE (sizeof(struct rte_ipv4_hdr) + sizeof(struct ip_options_timestamp))
#define UDP_HDR_POS (sizeof(struct rte_ether_hdr) + IP_HDR_SIZE)
#define UDP_BUF_POS (UDP_HDR_POS + sizeof(struct rte_udp_hdr))
#define IPV4_ADDR(a, b, c, d)(((a & 0xff) << 24) | ((b & 0xff) << 16) | ((c & 0xff) << 8) | (d & 0xff))

enum pdump_operation {
	DISABLE = 1,
	ENABLE = 2
};

enum pdump_version {
	V1 = 1
};

struct pdump_request {
	uint16_t ver;
	uint16_t op;
	uint32_t flags;
	union pdump_data {
		struct enable_v1 {
			char device[RTE_DEV_NAME_MAX_LEN];
			uint16_t queue;
			struct rte_ring *ring;
			struct rte_mempool *mp;
			void *filter;
		} en_v1;
		struct disable_v1 {
			char device[RTE_DEV_NAME_MAX_LEN];
			uint16_t queue;
			struct rte_ring *ring;
			struct rte_mempool *mp;
			void *filter;
		} dis_v1;
	} data;
};

struct pdump_response {
	uint16_t ver;
	uint16_t res_op;
	int32_t err_value;
};

static struct pdump_cfg {
	bool enable;
	uint16_t pc802_idx;
	uint16_t queue;
	uint32_t flags;
	struct rte_ring *ring;
	struct rte_mempool *mp;

	uint16_t dst_port;
	uint16_t src_port;
	uint32_t sleep_us;
	uint64_t drops;
} pdump_cfg;

struct pdump_pkg {
	uint16_t pc802_index;
	uint16_t queue_id;
	uint32_t rxtx_flag;
	uint64_t tsc;
	PC802_Mem_Block_t *blk;
};

static uint64_t start_tsc;
static rte_atomic32_t pdump_stop = RTE_ATOMIC32_INIT(0);
static pthread_t pdump_tid;
struct rte_ring *pdump_ring;

extern int pc802_ctrl_thread_create(pthread_t *thread, const char *name, pthread_attr_t *attr,
		void *(*start_routine)(void *), void *arg);

static inline uint16_t ipv4_header_init(struct rte_ipv4_hdr *ip_hdr, uint64_t tsc );

static void pdump_copy(struct rte_mbuf **mbufs, uint16_t count)
{
//	static struct rte_ether_addr src_mac = { {0x00, 0x00, 0x00, 0x88, 0x00, 0x22} };
//	static struct rte_ether_addr dst_mac = { {0x11, 0x11, 0x11, 0x88, 0x00, 0x22} };

    uint16_t i;
    uint32_t nb_ring;
    struct rte_mbuf *m;
	struct rte_ether_hdr *eth_hdr;
    struct rte_ipv4_hdr *ip_hdr;
    struct rte_udp_hdr *udp_hdr;
    struct pdump_pkg *pkg;
    uint16_t pkt_len;

    for (i = 0; i < count; i++) {
        m = mbufs[i];
        eth_hdr = rte_pktmbuf_mtod(m, struct rte_ether_hdr *);
        ip_hdr = (struct rte_ipv4_hdr *)&eth_hdr[1];
        udp_hdr = rte_pktmbuf_mtod_offset(m, struct rte_udp_hdr *, UDP_HDR_POS);
        pkg = (struct pdump_pkg *)m->buf_addr;

        // fill ether package
        if (pkg->blk->pkt_length > (rte_pktmbuf_data_room_size(m->pool) - m->data_off - UDP_BUF_POS))
            pkt_len = rte_pktmbuf_data_room_size(m->pool) - m->data_off - UDP_BUF_POS;
        else
            pkt_len = (uint16_t)pkg->blk->pkt_length;
        rte_memcpy(&udp_hdr[1], &pkg->blk[1], pkt_len);

        pkt_len += sizeof(struct rte_udp_hdr);
        udp_hdr->src_port = rte_cpu_to_be_16(pdump_cfg.src_port + pkg->rxtx_flag);
        udp_hdr->dst_port = rte_cpu_to_be_16(pdump_cfg.dst_port + pkg->queue_id);
        udp_hdr->dgram_len = rte_cpu_to_be_16(pkt_len);
        //udp_hdr->dgram_cksum = 0;

        pkt_len += IP_HDR_SIZE;
        //ipv4_header_init(ip_hdr, pkg->tsc);
        ((struct ip_options_timestamp *)&ip_hdr[1])->time_stamp =
            rte_cpu_to_be_32((pkg->tsc - start_tsc) * 100000 / rte_get_tsc_hz());
        ip_hdr->total_length = rte_cpu_to_be_16(pkt_len);
        ip_hdr->hdr_checksum = 0;
		ip_hdr->hdr_checksum = rte_ipv4_cksum(ip_hdr);

        pkt_len += sizeof(struct rte_ether_hdr);
        //eth_hdr->d_addr = dst_mac;
        //eth_hdr->s_addr = src_mac;
        //eth_hdr->ether_type = rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4);

        m->data_len = pkt_len;
        m->pkt_len = pkt_len;
        m->port = pkg->pc802_index;
    }

    nb_ring = rte_ring_enqueue_burst(pdump_cfg.ring, (void *)mbufs, count, NULL);
    if (unlikely(nb_ring < count)) {
        unsigned int drops = count - nb_ring;
        DBLOG("drop %d of packets enqueued to ring\n", drops);
        rte_pktmbuf_free_bulk(&mbufs[nb_ring], drops);
        pdump_cfg.drops += drops;
    }
}

uint16_t pdump_cb(uint16_t pc802_index, uint16_t queue_id, uint16_t rxtx_flag, PC802_Mem_Block_t **blks, uint16_t nb_blks)
{
    if (pdump_cfg.enable && (pc802_index == pdump_cfg.pc802_idx)
		&& ((1<<queue_id) & pdump_cfg.queue) && (rxtx_flag & pdump_cfg.flags)) {
        int i;
//		int nb_mbufs;
		int nb_rings;
		struct rte_mbuf *mbufs[BURST_SIZE];
    	struct pdump_pkg *pkg;
		uint64_t tsc = rte_rdtsc();
#if 0
		nb_mbufs = rte_pktmbuf_alloc_bulk(pdump_cfg.mp, mbufs, nb_blks);
		if (unlikely(nb_mbufs < nb_blks)) {
			unsigned int drops = nb_blks - nb_mbufs;
			DBLOG("drop %d of packets alloc mbuf\n", drops );
			pdump_cfg.drops += drops;
		}
		for (i = 0; i < nb_mbufs; i++) {
#else
		for (i = 0; i < nb_blks; i++) {
			mbufs[i] = rte_pktmbuf_alloc(pdump_cfg.mp);
			if (unlikely(mbufs[i] == NULL)){
				DBLOG("drop %d of packets alloc mbuf %p\n", nb_blks-i, pdump_cfg.mp );
				break;
			}
#endif
			pkg = (struct pdump_pkg *)mbufs[i]->buf_addr;
			pkg->pc802_index = pc802_index;
			pkg->queue_id  = queue_id;
			pkg->rxtx_flag = rxtx_flag;
			pkg->tsc = tsc;
			pkg->blk = blks[i];
		}

		nb_rings = rte_ring_enqueue_burst(pdump_ring, (void *)mbufs, i, NULL);
		if (unlikely(nb_rings < i)) {
			unsigned int drops = i - nb_rings;
			DBLOG("drop %d of packets enqueued to ring\n", drops );
			rte_pktmbuf_free_bulk(&mbufs[i], drops);
			pdump_cfg.drops += drops;
		}
    }
    return nb_blks;
}

static inline uint16_t ipv4_header_init(struct rte_ipv4_hdr *ip_hdr, uint64_t tsc )
{
	static rte_be16_t id=0;
	static uint32_t src_addr = IPV4_ADDR(1, 1, 1, 1);
	static uint32_t dst_addr = IPV4_ADDR(2, 2, 2, 2);

	uint32_t us = (tsc-start_tsc)*100000/rte_get_tsc_hz();
	struct ip_options_timestamp *opt = (struct ip_options_timestamp *)&ip_hdr[1];

	ip_hdr->version_ihl = RTE_IPV4_VHL_DEF+sizeof(struct ip_options_timestamp)/4;
	ip_hdr->type_of_service = 0;
	ip_hdr->fragment_offset = 0;
	ip_hdr->time_to_live = 64;
	ip_hdr->next_proto_id = IPPROTO_UDP;
	ip_hdr->packet_id = id++;
	ip_hdr->total_length = IP_HDR_SIZE;
	ip_hdr->src_addr = rte_cpu_to_be_32(src_addr);
	ip_hdr->dst_addr = rte_cpu_to_be_32(dst_addr);
	ip_hdr->hdr_checksum = 0;

	opt->type = 0x44;
	opt->length = sizeof(struct ip_options_timestamp);
	opt->pointer = 1;
	opt->OF_FL = 0;
	opt->time_stamp = rte_cpu_to_be_32(us);

	return 0;
}
#if 1
static void mbuf_init(__rte_unused struct rte_mempool *mp, __rte_unused void *opaque_arg, void *obj, __rte_unused unsigned i)
{
	static struct rte_ether_addr src_mac = { {0x00, 0x00, 0x00, 0x88, 0x00, 0x22} };
	static struct rte_ether_addr dst_mac = { {0x11, 0x11, 0x11, 0x88, 0x00, 0x22} };

	struct rte_mbuf *m = (struct rte_mbuf *)obj;

	struct rte_ether_hdr *eth_hdr = rte_pktmbuf_mtod(m, struct rte_ether_hdr *);
	struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(m, struct rte_ipv4_hdr *, sizeof(struct rte_ether_hdr));
	struct rte_udp_hdr *udp_hdr = rte_pktmbuf_mtod_offset(m, struct rte_udp_hdr *, UDP_HDR_POS);

	eth_hdr->d_addr = dst_mac;
	eth_hdr->s_addr = src_mac;
	eth_hdr->ether_type = rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4);

	ipv4_header_init(ipv4_hdr,0);

	udp_hdr->src_port  = rte_cpu_to_be_16(pdump_cfg.src_port);
	udp_hdr->dst_port  = rte_cpu_to_be_16(pdump_cfg.dst_port);
	udp_hdr->dgram_len = rte_cpu_to_be_16(sizeof(struct rte_udp_hdr));
	udp_hdr->dgram_cksum = 0; /* No UDP checksum. */
}
#endif
static void *pc802_pdump( __rte_unused void *arg)
{
	int32_t f_stop;
	uint16_t count;
	struct rte_mbuf *mbufs[BURST_SIZE];
    struct timespec req;
    req.tv_sec = 0;
    req.tv_nsec = pdump_cfg.sleep_us;

    while (1) {
        f_stop = rte_atomic32_read(&pdump_stop);
        if (f_stop)
			break;
		count = rte_ring_dequeue_burst(pdump_ring, (void *)mbufs, BURST_SIZE, NULL);
		if(count)
			pdump_copy(mbufs, count);
		else
			nanosleep(&req, NULL);
	}
	req.tv_nsec *= 10;
	nanosleep(&req, NULL);
	return NULL;
}

static int pc802_pdump_start(void)
{
	start_tsc = rte_rdtsc();

	//init mbuf eth ip head
	rte_mempool_obj_iter(pdump_cfg.mp, mbuf_init, NULL);
	if ( NULL == pdump_ring ) {
		pdump_ring = rte_ring_lookup( PDUMP_RING );
		if ( NULL == pdump_ring ) {
			pdump_ring = rte_ring_create( PDUMP_RING, 4096, rte_socket_id(), 0 );
			if ( NULL == pdump_ring){
				DBLOG( "Failed to create ring: %s", strerror(rte_errno));
				return -1;
			}
		}
	}

	rte_atomic32_set( &pdump_stop, 0);
	pc802_ctrl_thread_create( &pdump_tid, "pc802_pdump", NULL, pc802_pdump, NULL);

	pdump_cfg.enable = true;
	return 0;
}

static int pc802_pdump_stop(void)
{
	pdump_cfg.enable = false;
	rte_atomic32_inc(&pdump_stop);
	pthread_join(pdump_tid, NULL);
	if( pdump_ring ){
		rte_ring_free(pdump_ring);
		pdump_ring = NULL;
	}
	return 0;
}

static int set_pdump_rxtx_cbs(const struct pdump_request *p)
{
	int ret = 0;
	uint16_t index;
	uint16_t operation;

	operation = p->op;
	if (operation == ENABLE) {
		DBLOG( "enable pdump req: port=%s, flags=%d, queue=%d, mp=%p.\n",
			p->data.en_v1.device, p->flags, p->data.en_v1.queue, p->data.en_v1.mp );
		index = pc802_get_index_by_name(p->data.en_v1.device);
		if ( MBUF_INVALID_PORT == index ) {
			DBLOG("failed to get port id for device id=%s\n",p->data.en_v1.device);
			return -EINVAL;
		}
		pdump_cfg.flags |= p->flags;
		pdump_cfg.queue |= p->data.en_v1.queue;
		if ( !pdump_cfg.enable ){
			pdump_cfg.pc802_idx = index;
			pdump_cfg.ring  = p->data.en_v1.ring;
			pdump_cfg.mp    = p->data.en_v1.mp;
			ret = pc802_pdump_start();
		}
	} else {
		DBLOG( "disable pdump req.\n" );
		pc802_pdump_stop();
		pdump_cfg.ring = NULL;
		pdump_cfg.mp = NULL;
		pdump_cfg.flags = 0;
		pdump_cfg.queue = 0;
	}

	return ret;
}

static int pdump_server(const struct rte_mp_msg *mp_msg, const void *peer)
{
	struct rte_mp_msg mp_resp;
	const struct pdump_request *cli_req;
	struct pdump_response *resp = (struct pdump_response *)&mp_resp.param;

	/* recv client requests */
	if (mp_msg->len_param != sizeof(*cli_req)) {
		DBLOG("failed to recv from client\n");
		resp->err_value = -EINVAL;
	} else {
		cli_req = (const struct pdump_request *)mp_msg->param;
		resp->ver = cli_req->ver;
		resp->res_op = cli_req->op;
		resp->err_value = set_pdump_rxtx_cbs(cli_req);
	}

	strlcpy(mp_resp.name, PDUMP_MP, RTE_MP_MAX_NAME_LEN);
	mp_resp.len_param = sizeof(*resp);
	mp_resp.num_fds = 0;
	if (rte_mp_reply(&mp_resp, peer) < 0) {
		DBLOG("failed to send to client:%s\n", strerror(rte_errno));
		return -1;
	}

	return 0;
}

int pc802_pdump_init(void)
{
	pdump_cfg.src_port = 8020;
	pdump_cfg.dst_port = 6880;
	pdump_cfg.sleep_us = 100;
	return rte_mp_action_register(PDUMP_MP, pdump_server);;
}

int pc802_pdump_uninit(void)
{
	rte_mp_action_unregister(PDUMP_MP);
	return 0;
}
