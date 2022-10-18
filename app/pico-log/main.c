/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <getopt.h>
#include <signal.h>
#include <stdbool.h>
#include <net/if.h>

#include <rte_eal.h>
#include <rte_alarm.h>
#include <rte_common.h>
#include <rte_debug.h>
#include <rte_ethdev.h>
#include <rte_memory.h>
#include <rte_lcore.h>
#include <rte_branch_prediction.h>
#include <rte_errno.h>
#include <rte_dev.h>
#include <rte_kvargs.h>
#include <rte_mempool.h>
#include <rte_ring.h>
#include <rte_string_fns.h>
#include <rte_log.h>

#include "pico_log.h"
#include "pico_mb.h"

#define MB_NUM_ARGS              8
#define MB_NUM_HANDLERS          8
#define MB_HANDSHAKE_HOST_LEGACY 0xBEEFBEEF
#define MB_HANDSHAKE_HOST_RINGS  0xCAFECAFE
#define MB_HANDSHAKE_CPU         0xF00DF00D
#define MB_HANDSHAKE_READY       0xDEADDEAD

typedef enum {
    MB_EMPTY=0,                 //  0 - Idle, no action to perform
    MB_PRINTF,                  //  1 - Semi-hosted printf function
    MB_SIM_STOP,                //  2 - Stop simulation with exit code (0 - ok, 1+ - error)
    MB_RUN_TESTCASE,            //  3 - Trigger a testcase scenario
    MB_READ_REGISTER,           //  4 - Perform a word read operation
    MB_WRITE_REGISTER,          //  5 - Perform a word write operation
    MB_CONTROL_CPU,             //  6 - Control CPU features (like caching)
    MB_RUN_SYS_CRG,             //  7 - Trigger system CRG configuration
    MB_RUN_GRAPH_DEMO_TESTCASE, //  8 - Trigger graph demo test sequence
    MB_RUN_LPDDR4_TESTCASE,     //  9 - Trigger LPDDR4 test sequence
    MB_TG_LOAD,                 // 10 - Trigger task graph load (host side)
    MB_TG_CHECK,                // 11 - Trigger task graph check (host side)
    MB_VEC_READ,                // 12 - Trigger vector read (host side)
    MB_VEC_DUMP,                // 13 - Trigger vector dump (host side)
    MB_ATLL_ALLOC,              // 14 - ATLL allocate
    MB_ATLL_RECV_END,           // 15 - ATLL receive
    MB_ATLL_SEND,               // 16 - ATLL transmit
    MB_CACHE_WRITEBACK,         // 17 - Trigger cache writeback
    MB_CACHE_INVALIDATE,        // 18 - Trigger cache invalidation
    MB_CACHE_FLUSH,             // 19 - Trigger cache flush
    MB_PING,                    // 20 - Keepalive test (returns arg 0)
    MB_IRQ_CONTROL,             // 21 - Control IRQ handling
    MB_IRQ_CAUGHT,              // 22 - Notify interrupt was caught
    MB_CRC32,                   // 23 - Calculate crc32
    GPIO_CTRL,                  // 24 - Access and control GPIO
    VIC_TIMER,                  // 25 - Access and control the XC12 VIC's timer
    ANALYTICS,                  // 26
    MB_VEC_BIN_READ,            // 27 - Trigger binary file read (host side)
    MB_VEC_BIN_DUMP,            // 28 - Trigger binary file dump (host side)
    MB_RPC_CALL,                // 29 - Trigger RPC call
    MB_DDR_RUNNING,             // 30 - Notify host DDR is running
} mailbox_action_t;

typedef struct {
    uint32_t         action;                 // 0x00
    uint32_t         num_args;               // 0x04
    uint32_t         retval;                 // 0x08
    uint32_t         error;                  // 0x0C
    uint32_t         arguments[MB_NUM_ARGS]; // 0x10+
} magic_mailbox_t;

#define LOG_MP    "PC802_LOG"
#define LOG_MPOOL "PC802_LOG_MPOOL"
#define LOG_RING  "PC802_LOG_RING"

#define BURST_SIZE 32

/* Maximum delay for exiting after primary process. */
#define MONITOR_INTERVAL (500 * 1000)

/* true if x is a power of 2 */
#define POWEROF2(x) ((((x)-1) & (x)) == 0)

enum log_en_dis {
	DISABLE = 0,
	ENABLE = 1
};

struct pc802_log_request {
	uint16_t ver;
	uint16_t op;
	struct rte_ring *ring;
	struct rte_mempool *mp;
};

struct pc802_log_response {
	uint16_t ver;
	uint16_t res_op;
	int32_t err_value;
};

struct pc802_log_blk {
	uint16_t port;
	uint16_t core;
	uint32_t type;
	uint32_t no;
	union {
		magic_mailbox_t mb;
		uint32_t event;
		char buf[96];
	};
} __rte_cache_aligned;


static struct rte_ring    *log_ring = NULL;
static struct rte_mempool *log_pool = NULL;

static volatile uint8_t quit_signal;

static void monitor_primary(void *arg __rte_unused)
{
	if (quit_signal)
		return;

	if (rte_eal_primary_proc_alive(NULL)) {
		rte_eal_alarm_set(MONITOR_INTERVAL, monitor_primary, NULL);
		return;
	}
	printf("Primary process is no longer active, exiting...\n");
	quit_signal = 1;
}

static void signal_handler(int sig_num)
{
	if (sig_num == SIGINT) {
		printf("\n\nSignal %d received, preparing to exit...\n", sig_num);
		quit_signal = 1;
	}
}

static int get_first_ctrl_cpu(void)
{
	int core=0;
    rte_cpuset_t ctrl_cpuset;

	CPU_ZERO(&ctrl_cpuset);
    if ( 0 == CPU_COUNT(&ctrl_cpuset) ) {
        FILE *fp = NULL;
        char buffer[128] = {0};
        int min,max;
        char *ret = NULL;

        fp = popen("cat /sys/devices/system/cpu/present", "r");
        ret = fgets(buffer, sizeof(buffer), fp);
        pclose(fp);
        if ( (ret!=NULL) && (2== sscanf( buffer, "%d-%d", &min, &max )) ) {
            for( core=min; core<=max; core++ )
                CPU_SET( core, &ctrl_cpuset );
        }

        fp = popen("cat /sys/devices/system/cpu/isolated", "r");
        ret = fgets(buffer, sizeof(buffer), fp);
        pclose(fp);
        if ( (ret!=NULL) && (2== sscanf( buffer, "%d-%d", &min, &max )) ) {
            for( core=min; core<=max; core++ )
                CPU_CLR( core, &ctrl_cpuset );
        }
    }

	core=0;
	do {
		if (CPU_ISSET(core, &ctrl_cpuset))
			return core;
	} while (++core < CPU_SETSIZE);

    return 0;
}

static void handle_mb_printf(uint16_t port, uint16_t core, const magic_mailbox_t *mb )
{
    char str[2048];
    char formatter[16];
    const char *arg0 = pico_mb_get(mb->arguments[0], core);
    const char *arg0_bak = arg0;
    int pos = 0;
    uint32_t arg_idx = 1;
    const char *sub_str;
    uint32_t j;

    pos += sprintf(&str[pos], "PRINTF: ");
    while (*arg0) {
        if (*arg0 == '%') {
            formatter[0] = '%';
            arg0++;
            j = 1;
            do {
                assert(j < 15);
                formatter[j] = *arg0++;
                if (isalpha(formatter[j])) {
                    formatter[j+1] = 0;
                    break;
                }
                j++;
            } while (1);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
            if (formatter[j] == 's') {
                sub_str = pico_mb_get(mb->arguments[arg_idx++], core);
                pos += snprintf(&str[pos], sizeof(str)-pos, formatter, sub_str);
            } else {
                pos += snprintf(&str[pos], sizeof(str)-pos, formatter, mb->arguments[arg_idx++]);
            }
#pragma GCC diagnostic pop

        } else {
            str[pos++] = *arg0++;
        }
    }
    str[pos] = 0;

    if (arg_idx != mb->num_args) {
        PC802_LOG(port, core, RTE_LOG_INFO, "(arg_idx = %u num_args = %u): format = %s\n",
            arg_idx, mb->num_args, arg0_bak);
        PC802_LOG(port, core, RTE_LOG_INFO, "printf: %s\n", str);
    }
	else
    	PC802_LOG(port, core, RTE_LOG_INFO, "%s", str );
    return;
}

static void handle_mb_sim_stop( uint16_t port, uint16_t core, const magic_mailbox_t *mb )
{
    if (1 == mb->num_args) {
        PC802_LOG(port, core, RTE_LOG_INFO, "EXIT(%u): code %u \n", mb->num_args, mb->arguments[0]);
    } else if (3 == mb->num_args) {
        const char *func_name = pico_mb_get(mb->arguments[1], core);
        PC802_LOG(port, core, RTE_LOG_INFO, "EXIT(%u): code %u function: %s() line %u\n",
            mb->num_args, mb->arguments[0], func_name, mb->arguments[2]);
    } else {
        PC802_LOG( port, core, RTE_LOG_INFO, "EXIT(%u): args:\n", mb->num_args);
        PC802_LOG( port, core, RTE_LOG_INFO, "  0x%08X  0x%08X  0x%08X  0x%08X\n", mb->arguments[0], mb->arguments[1],
            mb->arguments[2], mb->arguments[3]);
        PC802_LOG( port, core, RTE_LOG_INFO, "  0x%08X  0x%08X  0x%08X  0x%08X\n", mb->arguments[4], mb->arguments[5],
            mb->arguments[6], mb->arguments[7]);
    }
    return;
}

static int handle_mailbox(uint16_t port, uint16_t core, uint32_t idx, const magic_mailbox_t *mb )
{
	if (MB_PRINTF == mb->action) {
		handle_mb_printf(port, core, mb);
	} else if (MB_SIM_STOP == mb->action) {
		handle_mb_sim_stop(port, core, mb );
	} else {
		PC802_LOG(port, core, RTE_LOG_INFO, "MB[%2u]: action=%u, num_args=%u, args:\n", idx, mb->action, mb->num_args );
		PC802_LOG(port, core, RTE_LOG_INFO, "  0x%08X  0x%08X  0x%08X  0x%08X\n",
			mb->arguments[0], mb->arguments[1], mb->arguments[2], mb->arguments[3]);
		PC802_LOG(port, core, RTE_LOG_INFO, "  0x%08X  0x%08X  0x%08X  0x%08X\n",
			mb->arguments[4], mb->arguments[5], mb->arguments[6], mb->arguments[7]);
	}
    return 0;
}

static void recv_log(void)
{
    int i;
    struct pc802_log_blk *log[BURST_SIZE];
    uint16_t count;
    struct timespec ts = {.tv_sec = 0, .tv_nsec = 1000 * 1000};

    while (!quit_signal) {
        count = rte_ring_dequeue_burst(log_ring, (void *)&log, BURST_SIZE, NULL);
        for (i = 0; i < count; i++) {
            switch (log[i]->type) {
            case PC802_LOG_EVENT:
				PC802_LOG( log[i]->port, log[i]->core, RTE_LOG_NOTICE, "event[%.5u]: 0x%.8X(0x%.5X, %.4d)\n",
						log[i]->no, log[i]->event, log[i]->event>>14, log[i]->event&0x3FFF );
                break;
            case PC802_LOG_MAILBOX:
                handle_mailbox(log[i]->port, log[i]->core, log[i]->no, &log[i]->mb);
                break;
            case PC802_LOG_PRINT:
                PC802_LOG(log[i]->port, log[i]->core, RTE_LOG_INFO, "%s", log[i]->buf);
                break;
            default:
                break;
            }
        }
        if (count)
            rte_mempool_put_bulk(log_pool, (void *)&log, count);
        else
			nanosleep(&ts, NULL);
    }

    return;
}

static int log_req( int flag )
{
	int ret = -1;
	struct rte_mp_msg mp_req, *mp_rep;
	struct rte_mp_reply mp_reply;
	struct timespec ts = {.tv_sec = 5, .tv_nsec = 0};
	struct pc802_log_request *req = (struct pc802_log_request *)mp_req.param;
	struct pc802_log_response *resp;

	req->ver = 1;
	req->op = flag;
	if( flag ) {
		req->ring = log_ring;
		req->mp   = log_pool;
	}
	else{
		req->ring = NULL;
		req->mp   = NULL;
	}

	strcpy( mp_req.name, LOG_MP );
	mp_req.len_param = sizeof(*req);
	mp_req.num_fds = 0;
	if (rte_mp_request_sync(&mp_req, &mp_reply, &ts) == 0) {
		mp_rep = &mp_reply.msgs[0];
		resp = (struct pc802_log_response *)mp_rep->param;
		rte_errno = resp->err_value;
		if (!resp->err_value)
			ret = 0;
		free(mp_reply.msgs);
	}

	if (ret < 0)
		printf("Request for log enable/disable failed\n");
	return ret;
}

int main(int argc, char **argv)
{
    int ret;
    int i;
    char n_flag[8] = "-l0";
    char mp_flag[] = "--proc-type=secondary";
    char *argp[argc + 2];

    signal(SIGINT, signal_handler);
    sprintf(n_flag, "-l%d", get_first_ctrl_cpu());

    argp[0] = argv[0];
    argp[1] = n_flag;
    argp[2] = mp_flag;

    for (i = 1; i < argc; i++)
		argp[i + 2] = argv[i];
    argc += 2;

    ret = rte_eal_init(argc, argp);
    if (ret < 0)
		rte_panic("Cannot init EAL\n");

    log_ring = rte_ring_lookup(LOG_RING);
    if (log_ring == NULL) {
        log_ring = rte_ring_create(LOG_RING, 1024, rte_socket_id(), 0);
        if (log_ring == NULL)
			rte_exit(EXIT_FAILURE, "%s:%s:%d\n", rte_strerror(rte_errno), __func__, __LINE__);
    }

    log_pool = rte_mempool_lookup(LOG_MPOOL);
	if (log_pool == NULL) {
        //const char *default_pool_ops = rte_mbuf_best_mempool_ops();
		log_pool = rte_mempool_create(LOG_MPOOL, 1024, sizeof(struct pc802_log_blk),
				RTE_CACHE_LINE_SIZE, 0, NULL, NULL, NULL, NULL, rte_socket_id(), 0);
		if (log_pool == NULL)
			rte_exit(EXIT_FAILURE, "Mempool creation failed: %s\n", rte_strerror(rte_errno) );
        //rte_mempool_set_ops_byname(log_pool, default_pool_ops, NULL);
        //rte_mempool_populate_default(log_pool);
	}

	pico_mb_init( );

    log_req( ENABLE );
    rte_eal_alarm_set(MONITOR_INTERVAL, monitor_primary, NULL);

    recv_log();

    rte_eal_alarm_cancel(monitor_primary, NULL);
	log_req( DISABLE );

    ret = rte_eal_cleanup();
    if (ret)
		printf("Error from rte_eal_cleanup(), %d\n", ret);

    return 0;
}
