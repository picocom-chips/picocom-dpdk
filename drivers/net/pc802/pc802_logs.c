/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2020 Picocom Corporation
 */

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <syslog.h>
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

/* declared as extern in pc802_logs.h */
int pc802_logtype_init;
int pc802_logtype_driver;
static int pc802_event_type;
static int pc802_print_type;
static int pc802_vec_type;
static rte_atomic32_t pc802_event_cnt;
static uint64_t pc802_logflag_core = 0;//0x7FFFFFFFF;
const char* pc802_core_name[] = {
	"PFI 0",
	"PFI 1",
	"PFI 2",
	"PFI 3",
	"PFI 4",
	"PFI 5",
	"PFI 6",
	"PFI 7",
	"PFI 8",
	"PFI 9",
	"PFI 10",
	"PFI 11",
	"PFI 12",
	"PFI 13",
	"PFI 14",
	"PFI 15",
	"ECPRI 0",
	"ECPRI 1",
	"ECPRI 2",
	"ECPRI 3",
	"ECPRI 4",
	"ECPRI 5",
	"ECPRI 6",
	"ECPRI 7",
	"ECPRI 8",
	"ECPRI 9",
	"ECPRI 10",
	"ECPRI 11",
	"ECPRI 12",
	"ECPRI 13",
	"ECPRI 14",
	"ECPRI 15",
	"XC12 0",
	"XC12 1",
	"XC12 2"
};

static FILE *log_stream = NULL;
/* only initialize log one time */
static int pc802_log_initialized;

static ssize_t log_write(__rte_unused void *c, const char *buf, size_t size) {
	return fwrite(buf, 1, size, stdout);
}

static cookie_io_functions_t log_func = {
	.write = log_write,
};

static void pc802_log_flag_show(void) {
	int i=0;

	printf( "\n   CORE   CTRL KEY 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15\n" );

	printf( "PFI[0-15]   [0-F]:");
	for( i=0; i<16; i++ )
		printf( "%2c ", pc802_logflag_core&(1<<i)?'*':' ' );

	printf( "\nECPRI[0-15] [G-V]:");
	for( i=16; i<32; i++ )
		printf( "%2c ", pc802_logflag_core&(1<<i)?'*':' ' );

	printf( "\nXC12[0-2]   [W-Y]:");
	for( i=32; i<35; i++ )
		printf( "%2c ", pc802_logflag_core&((uint64_t)1<<i)?'*':' ' );
	printf( "\nCTRL ALL    [ Z ]\n");
}

void pc802_log_set_core( uint32_t core, bool flag) {
	if(flag)
		pc802_logflag_core |= ((uint64_t)1<<core);
	else
		pc802_logflag_core &= (~((uint64_t)1<<core));
	pc802_log_flag_show();
}

void pc802_log_change_core( uint32_t core ) {
	if ( pc802_logflag_core & ((uint64_t)1<<core) )
		pc802_logflag_core &= (~((uint64_t)1<<core));
	else
		pc802_logflag_core |= ((uint64_t)1<<core);
	pc802_log_flag_show();
}

static void getkey(void) {
    char buf[32];
    fd_set          rfds;
    struct timeval  tv = {0,0};

	FD_ZERO( &rfds );
	FD_SET( STDIN_FILENO, &rfds );
	if ( select( STDIN_FILENO+1, &rfds, NULL, NULL, &tv ) > 0 ) {
		if ( read( STDIN_FILENO, buf, sizeof(buf) ) > 0 ){
			if ( (buf[0]>='0') && (buf[0]<='9') )
				pc802_log_change_core( buf[0]-'0');
			else if ( (buf[0]>='A') && (buf[0]<='Y') )
				pc802_log_change_core( buf[0]-'A'+10 );
			else if ( (buf[0]>='a') && (buf[0]<='y') )
				pc802_log_change_core( buf[0]-'a'+10 );
			else if ( (buf[0]=='Z') || (buf[0]=='z') ) {
				pc802_logflag_core = (pc802_logflag_core>0?0:0x7FFFFFFFF);
				pc802_log_flag_show();
			}
			else
				pc802_log_flag_show();
		}
	}
}

void pc802_log_flush(void) {
	if ( (rte_log_get_level(pc802_event_type) > (int)RTE_LOG_INFO)
		 || (rte_log_get_level(pc802_print_type) > (int)RTE_LOG_INFO) )
		getkey( );

	if ( rte_atomic32_read(&pc802_event_cnt)>0 && NULL!=log_stream ) {
		fflush(log_stream);
		fflush(stdout);
		rte_atomic32_clear(&pc802_event_cnt);
	}
}

void pc802_log( uint32_t core, const char *format, ... ) {
	va_list ap;

	if ( ( NULL==log_stream ) || (!(pc802_logflag_core&((uint64_t)1<<core))) )
		return;

	if ( log_stream != NULL ) {
		va_start(ap, format);
		vfprintf(log_stream, format, ap);
		va_end(ap);
	}
	rte_atomic32_inc(&pc802_event_cnt);
}

int pc802_log_get_level( int type ) {
	if ( type == PC802_LOG_EVENT )
		return rte_log_get_level(pc802_event_type);
	else if ( type == PC802_LOG_PRINT )
		return rte_log_get_level(pc802_print_type);
	else if ( type == PC802_LOG_VEC )
		return rte_log_get_level(pc802_vec_type);
	return -1;
}

void pc802_init_log(void) {
	if (!pc802_log_initialized) {
		log_stream = fopencookie(NULL, "w+", log_func);
		if ( NULL==log_stream )
			return;
		//eal_log_set_default(log_stream);
		pc802_logtype_init = rte_log_register("pmd.net.pc802.init");
		if (pc802_logtype_init >= 0)
			rte_log_set_level(pc802_logtype_init, RTE_LOG_NOTICE);
		pc802_logtype_driver = rte_log_register("pmd.net.pc802.driver");
		if (pc802_logtype_driver >= 0)
			rte_log_set_level(pc802_logtype_driver, RTE_LOG_NOTICE);
		pc802_event_type = rte_log_register("pc802.event");
		//if (pc802_event_type >= 0)
		//	rte_log_set_level(pc802_event_type, RTE_LOG_DEBUG);
		pc802_print_type = rte_log_register("pc802.printf");
		pc802_vec_type = rte_log_register("pc802.vec");
		pc802_log_initialized = 1;
	}
}

static struct rte_ring    *log_ring = NULL;
static struct rte_mempool *log_pool = NULL;
static enum log_en_dis log_flag = DISABLE;

static int log_request(const struct rte_mp_msg *mp_msg, const void *peer)
{
	struct rte_mp_msg mp_rsp;
	const struct pc802_log_request *req;
	struct pc802_log_response *rsp = (struct pc802_log_response *)&mp_rsp.param;

	/* recv client requests */
	if (mp_msg->len_param != sizeof(*req)) {
		printf("failed to recv from client\n");
		rsp->err_value = -EINVAL;
	} else {
        req = (const struct pc802_log_request *)mp_msg->param;
        rsp->ver = req->ver;
        rsp->res_op = req->op;
        if (req->op) {
			if( (NULL != req->pool) && (NULL != req->ring) ) {
				log_pool = req->pool;
				log_ring = req->ring;
				log_flag = ENABLE;
				rsp->err_value = 0;
				printf("recv log enable req\n");
			}
			else
				rsp->err_value = -EINVAL;
        }
		else{
            log_pool = NULL;
            log_ring = NULL;
			log_flag = DISABLE;
			rsp->err_value = 0;
			printf("recv log disable req\n");
		}
    }

	strncpy(mp_rsp.name, LOG_MP, RTE_MP_MAX_NAME_LEN);
	mp_rsp.len_param = sizeof(*rsp);
	mp_rsp.num_fds = 0;
	if (rte_mp_reply(&mp_rsp, peer) < 0) {
		printf("failed to send to client:%s\n", strerror(rte_errno));
		return -1;
	}

	return 0;
}

int log_server_init(void)
{
	return rte_mp_action_register(LOG_MP, log_request);
}

void log_event(uint16_t port_id, uint32_t core, uint32_t index, uint32_t event)
{
	if (!log_flag){
		pc802_log( core, "event[%.5u]: 0x%.8X(0x%.5X, %.4d)\n", index, event, event>>14, event&0x3FFF );
		return;
	}
    struct pc802_log_blk *item;
    if ( 0!= rte_mempool_get(log_pool, (void **)&item) )
        return;

    item->port = port_id;
    item->core = core;
    item->type = PC802_LOG_EVENT;
    item->no = index;
    item->event = event;

    if (0!=rte_ring_enqueue(log_ring, (void *)item ))
		rte_mempool_put(log_pool, (void *)item);
}

void log_buf(uint16_t port_id, uint32_t core, const char *fmt, ... )
{
	static uint32_t index=0;
	if (!log_flag){

		return;
	}
	va_list ap;
    struct pc802_log_blk *item;
    if ( 0 != rte_mempool_get(log_pool, (void **)&item) )
        return;

    item->port = port_id;
    item->core = core;
    item->type = PC802_LOG_PRINT;
    item->no = index++;
	va_start(ap, fmt);
	vsnprintf(item->buf, sizeof(item->buf), fmt, ap);
	va_end(ap);

    if (0!=rte_ring_enqueue(log_ring, (void *)item ))
		rte_mempool_put(log_pool, (void *)item);
}

void log_mb(uint16_t port_id, uint32_t core, uint32_t index, const magic_mailbox_t *mb)
{
	if (!log_flag){
		pc802_log(core, "MB[%2u][%2u]: action=%u, num_args=%u, args:\n", core, index, mb->action, mb->num_args);
		pc802_log(core, "  0x%08X  0x%08X  0x%08X  0x%08X\n", mb->arguments[0], mb->arguments[1],
			mb->arguments[2], mb->arguments[3]);
		pc802_log(core, "  0x%08X  0x%08X  0x%08X  0x%08X\n", mb->arguments[4], mb->arguments[5],
			mb->arguments[6], mb->arguments[7]);
		return;
	}
    struct pc802_log_blk *item;
    if ( 0 != rte_mempool_get(log_pool, (void **)&item) ){
		printf("failed to get mem:%s\n", strerror(rte_errno));
        return;
	}

    item->port = port_id;
    item->core = core;
    item->type = PC802_LOG_MAILBOX;
    item->no = index;

	rte_memcpy(&item->mb, mb, sizeof(magic_mailbox_t)-sizeof(uint32_t)*(MB_NUM_ARGS-mb->num_args));

    if (0!=rte_ring_enqueue(log_ring, (void *)item )){
		printf("failed to rte_ring_enqueue:%s\n", strerror(rte_errno));
		rte_mempool_put(log_pool, (void *)item);
	}
}
