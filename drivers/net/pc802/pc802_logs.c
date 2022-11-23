/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2020 Picocom Corporation
 */

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <rte_version.h>
#if RTE_VERSION >= RTE_VERSION_NUM(21, 5, 0, 0)
#include <eal_log.h>
#else
#include <rte_log.h>
#endif
#include <rte_atomic.h>
#include <rte_eal.h>
#include <rte_errno.h>
#include <rte_mempool.h>
#include <rte_ring.h>

#include "rte_pmd_pc802.h"
#include "pc802_ethdev.h"
#include "pc802_logs.h"

extern char *__progname;

#define LOG_MPOOL "PC802_LOG_MPOOL"
#define LOG_RING  "PC802_LOG_RING"
#define BURST_SIZE 32

#define LOG_HEAD_SIZE (sizeof(struct pc802_log_blk)-96)

/* declared as extern in pc802_logs.h */
int pc802_logtype_init;
int pc802_logtype_driver;
/* only initialize log one time */
static int pc802_log_initialized;

static int log_fd = -1;				/* fd for log */
static bool connected = false;		/* have done connect */

static struct rte_ring    *log_ring = NULL;
static struct rte_mempool *log_pool = NULL;

void pc802_init_log(void)
{
	if (!pc802_log_initialized) {
		pc802_logtype_init = rte_log_register("pmd.net.pc802.init");
		if (pc802_logtype_init >= 0)
			rte_log_set_level(pc802_logtype_init, RTE_LOG_NOTICE);
		pc802_logtype_driver = rte_log_register("pmd.net.pc802.driver");
		if (pc802_logtype_driver >= 0)
			rte_log_set_level(pc802_logtype_driver, RTE_LOG_NOTICE);
		pc802_log_initialized = 1;
	}
}

static int send_log_head(void)
{
    struct pc802_log_blk item;

    item.type = 255;
	item.len  = LOG_HEAD_SIZE;
	item.len += snprintf(item.buf, sizeof(item.buf), "%s[%d]", __progname, getpid() );
	return send(log_fd, &item, item.len, MSG_NOSIGNAL|MSG_DONTWAIT);
}

static void openlog(void)
{
	static const struct sockaddr_un addr = {
		.sun_family = AF_UNIX,
		.sun_path = PC802_LOG_PATH
	};

    log_ring = rte_ring_lookup(LOG_RING);
    if (log_ring == NULL) {
        log_ring = rte_ring_create(LOG_RING, 1024, rte_socket_id(), 0);
        if (log_ring == NULL)
			rte_exit(EXIT_FAILURE, "Ring creation failed: %s\n", rte_strerror(rte_errno) );
    }

    log_pool = rte_mempool_lookup(LOG_MPOOL);
	if (log_pool == NULL) {
        //const char *default_pool_ops = rte_mbuf_best_mempool_ops();
		log_pool = rte_mempool_create(LOG_MPOOL, 1024, sizeof(struct pc802_log_blk),
				RTE_CACHE_LINE_SIZE, 0, NULL, NULL, NULL, NULL, rte_socket_id(), 0);
		if (log_pool == NULL)
			rte_exit(EXIT_FAILURE, "Mempool creation failed: %s\n", rte_strerror(rte_errno) );
	}

	if (log_fd == -1)
		log_fd = socket(AF_UNIX, SOCK_DGRAM|SOCK_CLOEXEC, 0);
	if (log_fd != -1 && !connected) {
		if ( connect(log_fd, &addr, sizeof(addr)) ) {
			close(log_fd);
			log_fd = -1;
		} else{
			send_log_head();
			connected = true;
		}
	}
}

void log_flush(void)
{
    int i, count;
    struct pc802_log_blk *log[BURST_SIZE];

    if (!connected)
		openlog();
	while(connected) {
		count = rte_ring_dequeue_burst(log_ring, (void *)&log, BURST_SIZE, NULL);
		if( !count )
			break;
		for (i=0; i<count; i++) {
			if ( send(log_fd, log[i], log[i]->len, MSG_NOSIGNAL|MSG_DONTWAIT) < 0) {
				close (log_fd);
				log_fd = -1;
				connected = false;
				break;
			}
		}
		rte_mempool_put_bulk(log_pool, (void *)&log, count);
	}
}

void log_event(uint16_t port_id, uint32_t core, uint32_t index, uint32_t event)
{
    struct pc802_log_blk *item;

    if ( 0 != rte_mempool_get(log_pool, (void **)&item) )
        return;

    item->port = port_id;
    item->core = core;
    item->type = PC802_LOG_EVENT;
	item->len  = LOG_HEAD_SIZE+sizeof(item->event);
    item->no   = index;
    item->event = event;

    if (0!=rte_ring_enqueue(log_ring, (void *)item ))
		rte_mempool_put(log_pool, (void *)item);
}

void log_buf(uint16_t port_id, uint32_t core, const char *fmt, ... )
{
	va_list ap;
    struct pc802_log_blk *item;
    if ( 0 != rte_mempool_get(log_pool, (void **)&item) )
        return;

    item->port = port_id;
    item->core = core;
    item->type = PC802_LOG_PRINT;
	item->len  = LOG_HEAD_SIZE;

	va_start(ap, fmt);
	item->len += vsnprintf(item->buf, sizeof(item->buf), fmt, ap);
	va_end(ap);

    if (0!=rte_ring_enqueue(log_ring, (void *)item ))
		rte_mempool_put(log_pool, (void *)item);
}

void log_mb(uint16_t port_id, uint32_t core, uint32_t index,  uint32_t action, uint32_t num, uint32_t *args)
{
    struct pc802_log_blk *item;

    if ( 0 != rte_mempool_get(log_pool, (void **)&item) )
        return;

    item->port = port_id;
    item->core = core;
    item->type = PC802_LOG_MAILBOX;
	item->len  = LOG_HEAD_SIZE+sizeof(magic_mailbox_t)-(MB_NUM_ARGS-num)*sizeof(uint32_t);
    item->no = index;

	item->mb.action = action;
	item->mb.num_args = num;
	while( num-- )
		item->mb.arguments[num] = args[num];

    if (0 != rte_ring_enqueue(log_ring, (void *)item))
        rte_mempool_put(log_pool, (void *)item);
}
