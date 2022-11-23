/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <syslog.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "pico_mb.h"
#include "../../drivers/net/pc802/pc802_logs.h"

#define RUN_PID_FILE    "/var/run/picolog.pid"
typedef enum {
    MB_EMPTY = 0,                //  0 - Idle, no action to perform
    MB_PRINTF,                   //  1 - Semi-hosted printf function
    MB_SIM_STOP,                 //  2 - Stop simulation with exit code (0 - ok, 1+ - error)
    MB_RUN_TESTCASE,             //  3 - Trigger a testcase scenario
    MB_READ_REGISTER,            //  4 - Perform a word read operation
    MB_WRITE_REGISTER,           //  5 - Perform a word write operation
    MB_CONTROL_CPU,              //  6 - Control CPU features (like caching)
    MB_RUN_SYS_CRG,              //  7 - Trigger system CRG configuration
    MB_RUN_GRAPH_DEMO_TESTCASE,  //  8 - Trigger graph demo test sequence
    MB_RUN_LPDDR4_TESTCASE,      //  9 - Trigger LPDDR4 test sequence
    MB_TG_LOAD,                  // 10 - Trigger task graph load (host side)
    MB_TG_CHECK,                 // 11 - Trigger task graph check (host side)
    MB_VEC_READ,                 // 12 - Trigger vector read (host side)
    MB_VEC_DUMP,                 // 13 - Trigger vector dump (host side)
    MB_ATLL_ALLOC,               // 14 - ATLL allocate
    MB_ATLL_RECV_END,            // 15 - ATLL receive
    MB_ATLL_SEND,                // 16 - ATLL transmit
    MB_CACHE_WRITEBACK,          // 17 - Trigger cache writeback
    MB_CACHE_INVALIDATE,         // 18 - Trigger cache invalidation
    MB_CACHE_FLUSH,              // 19 - Trigger cache flush
    MB_PING,                     // 20 - Keepalive test (returns arg 0)
    MB_IRQ_CONTROL,              // 21 - Control IRQ handling
    MB_IRQ_CAUGHT,               // 22 - Notify interrupt was caught
    MB_CRC32,                    // 23 - Calculate crc32
    GPIO_CTRL,                   // 24 - Access and control GPIO
    VIC_TIMER,                   // 25 - Access and control the XC12 VIC's timer
    ANALYTICS,                   // 26
    MB_VEC_BIN_READ,             // 27 - Trigger binary file read (host side)
    MB_VEC_BIN_DUMP,             // 28 - Trigger binary file dump (host side)
    MB_RPC_CALL,                 // 29 - Trigger RPC call
    MB_DDR_RUNNING,              // 30 - Notify host DDR is running
} mailbox_action_t;

static const char *pc802_core_name[] = {
    "PFI 0",    "PFI 1",    "PFI 2",    "PFI 3",    "PFI 4",    "PFI 5",   "PFI 6",   "PFI 7",   "PFI 8",
    "PFI 9",    "PFI 10",   "PFI 11",   "PFI 12",   "PFI 13",   "PFI 14",  "PFI 15",  "ECPRI 0", "ECPRI 1",
    "ECPRI 2",  "ECPRI 3",  "ECPRI 4",  "ECPRI 5",  "ECPRI 6",  "ECPRI 7", "ECPRI 8", "ECPRI 9", "ECPRI 10",
    "ECPRI 11", "ECPRI 12", "ECPRI 13", "ECPRI 14", "ECPRI 15", "XC12 0",  "XC12 1",  "XC12 2"};
static char log_head[64] = "Unknown";

#define PICO_LOG(port, core, type, fmt, args...)                                                \
    do {                                                                                        \
        if (do_fork)                                                                            \
            syslog(type, "%s PC802_%d %s " fmt, log_head, port, pc802_core_name[core], ##args); \
        else                                                                                     \
            printlog(port, core, fmt, ##args);                                                  \
    } while (0);

static volatile uint8_t quit_signal;
static int do_fork = 0; 	/* fork - run in daemon mode - read-only after startup */
static int sock_fd = -1;

static void signal_handler(int sig_num)
{
    if (sig_num == SIGINT) {
        printf("\n\nSignal %d received, preparing to exit...\n", sig_num);
        quit_signal = 1;
        if(sock_fd>=0)
            close(sock_fd);
    }
}

static void printlog(uint16_t port, uint16_t core, const char *format, ...)
{
    va_list ap;
    time_t now;
    char *timestamp;

    time(&now);
    timestamp = ctime(&now) + 4; /* skip day of week */
    timestamp[15] = '\0';
    printf("%s %s: PC802_%d %s ", timestamp, log_head, port, pc802_core_name[core]);

    va_start(ap, format);
    vfprintf(stdout, format, ap);
    va_end(ap);
}

static void handle_mb_printf(uint16_t port, uint16_t core, const magic_mailbox_t *mb)
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
                    formatter[j + 1] = 0;
                    break;
                }
                j++;
            } while (1);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
            if (formatter[j] == 's') {
                sub_str = pico_mb_get(mb->arguments[arg_idx++], core);
                pos += snprintf(&str[pos], sizeof(str) - pos, formatter, sub_str);
            } else {
                pos += snprintf(&str[pos], sizeof(str) - pos, formatter, mb->arguments[arg_idx++]);
            }
#pragma GCC diagnostic pop

        } else {
            str[pos++] = *arg0++;
        }
    }
    str[pos] = 0;

    if (arg_idx != mb->num_args) {
        PICO_LOG(port, core, LOG_INFO, "(arg_idx = %u num_args = %u): format = %s\n", arg_idx, mb->num_args,
                  arg0_bak);
        PICO_LOG(port, core, LOG_INFO, "printf: %s\n", str);
    } else
        PICO_LOG(port, core, LOG_INFO, "%s", str);
    return;
}

static void handle_mb_sim_stop(uint16_t port, uint16_t core, const magic_mailbox_t *mb)
{
    if (1 == mb->num_args) {
        PICO_LOG(port, core, LOG_INFO, "EXIT(%u): code %u \n", mb->num_args, mb->arguments[0]);
    } else if (3 == mb->num_args) {
        const char *func_name = pico_mb_get(mb->arguments[1], core);
        PICO_LOG(port, core, LOG_INFO, "EXIT(%u): code %u function: %s() line %u\n", mb->num_args,
                  mb->arguments[0], func_name, mb->arguments[2]);
    } else {
        PICO_LOG(port, core, LOG_INFO, "EXIT(%u): args:\n", mb->num_args);
        PICO_LOG(port, core, LOG_INFO, "  0x%08X  0x%08X  0x%08X  0x%08X\n", mb->arguments[0], mb->arguments[1],
                  mb->arguments[2], mb->arguments[3]);
        PICO_LOG(port, core, LOG_INFO, "  0x%08X  0x%08X  0x%08X  0x%08X\n", mb->arguments[4], mb->arguments[5],
                  mb->arguments[6], mb->arguments[7]);
    }
    return;
}

static int handle_mailbox(uint16_t port, uint16_t core, uint32_t idx, const magic_mailbox_t *mb)
{
    if (MB_PRINTF == mb->action) {
        handle_mb_printf(port, core, mb);
    } else if (MB_SIM_STOP == mb->action) {
        handle_mb_sim_stop(port, core, mb);
    } else {
        PICO_LOG(port, core, LOG_INFO, "MB[%2u]: action=%u, num_args=%u, args:\n", idx, mb->action, mb->num_args);
        PICO_LOG(port, core, LOG_INFO, "  0x%08X  0x%08X  0x%08X  0x%08X\n", mb->arguments[0], mb->arguments[1],
                  mb->arguments[2], mb->arguments[3]);
        PICO_LOG(port, core, LOG_INFO, "  0x%08X  0x%08X  0x%08X  0x%08X\n", mb->arguments[4], mb->arguments[5],
                  mb->arguments[6], mb->arguments[7]);
    }
    return 0;
}

static void main_loop(int fd)
{
    struct pc802_log_blk log;
    int len;

    while (!quit_signal) {
        len = read(fd, &log, sizeof(log));
        if ( len<0 ) {
            sleep(1);
            continue;
        }
        switch (log.type) {
        case PC802_LOG_EVENT:
            PICO_LOG(log.port, log.core, LOG_NOTICE,
                        "event[%.5u]: 0x%.8X(0x%.5X, %.4d)\n", log.no,
                        log.event, log.event >> 14, log.event & 0x3FFF);
            break;
        case PC802_LOG_MAILBOX:
            handle_mailbox(log.port, log.core, log.no, &log.mb);
            break;
        case PC802_LOG_PRINT:
            PICO_LOG(log.port, log.core, LOG_INFO, "%s", log.buf);
            break;
        case PC802_LOG_HEAD:
            strcpy(log_head, log.buf);
            break;
        default:
            break;
        }
    }

    return;
}

static int create_socket(void)
{
    static struct sockaddr_un addr = {
        .sun_family = AF_UNIX,
        .sun_path = PC802_LOG_PATH,
    };
    int sock_fd;

    unlink(PC802_LOG_PATH);

    sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr));
    chmod(PC802_LOG_PATH, 0666);

    return sock_fd;
}

static int server_is_running(void)
{
	int fd = open(RUN_PID_FILE, O_RDWR | O_TRUNC);
	if (fd == -1) {
		fd = creat(RUN_PID_FILE, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
		if (fd > 0) {
			fchmod(fd, S_IRUSR|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
			//printf("chmod return code is %d\n", retCode);
		} else {
			fd = open(RUN_PID_FILE, O_RDWR | O_TRUNC);
		}
	}
	if (fd < 0) {
		printf("Open file failed, error : %s", strerror(errno));
		return -1;
	}

	struct flock lock;
	lock.l_type = F_WRLCK;
    lock.l_start = 0;
	lock.l_whence = SEEK_SET;
	lock.l_len = 0;
	int ret = fcntl(fd, F_SETLK, &lock);
	if (ret < 0) {
		if (errno == EACCES || errno == EAGAIN) {
			printf("%s already locked, error: %s\n", RUN_PID_FILE, strerror(errno));
			close(fd);
			return -1;
		}
	}

	char buf[16] = {};
	sprintf(buf, "%d", getpid());
	ret = ftruncate(fd, 0);
	ret = write(fd, buf, strlen(buf));
	if (ret < 0) {
		printf("Write file failed, file: %s, error: %s\n", RUN_PID_FILE, strerror(errno));
		close(fd);
		return -1;
	}

	return 0;
}

static void usage(char *progname)
{
	printf("%s [options] \n"
		" -n: run in foreground\n"
		" -h: prints this help\n",
		progname);
}

int main(int argc, char **argv)
{
    int ret,ch;

    while((ch = getopt(argc, argv, "nh")) != EOF) {
        switch(ch) {
		case 'n':
			do_fork = 1;
            break;
		case 'h':
		case '?':
		default:
			usage(argv[0]);
            exit(0);
        }
    }

    if (do_fork) {
        ret = daemon(0,0);
        if(!ret){
            openlog("PC802", LOG_NDELAY, LOG_USER);
            setlogmask(0xff);
            syslog(LOG_INFO,"start log\n");
        }
    }

    if (0 != server_is_running()) {
        printf("pico log process is running! Current process will exit!\n");
        return -1;
    }

    /* catch ctrl-c so we can print on exit */
	signal(SIGINT, signal_handler);

    sock_fd = create_socket();
    pico_mb_init();

    main_loop(sock_fd);

    close(sock_fd);
    unlink(RUN_PID_FILE);
    if (do_fork)
        closelog();

    return 0;
}
