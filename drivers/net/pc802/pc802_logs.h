/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _PC802_LOGS_H_
#define _PC802_LOGS_H_

#include <syslog.h>
#include <rte_log.h>

enum PC802_LOG_TYPE {
	PC802_LOG_EVENT,
	PC802_LOG_PRINT,
	PC802_LOG_VEC
};

extern int pc802_logtype_init;
#define PMD_INIT_LOG(level, fmt, args...) \
	rte_log(RTE_LOG_ ## level, pc802_logtype_init, \
		"%s(): " fmt "\n", __func__, ##args)

#define PMD_INIT_FUNC_TRACE() PMD_INIT_LOG(DEBUG, " >>")

#ifdef RTE_LIBRTE_PC802_DEBUG_RX
#define PMD_RX_LOG(level, fmt, args...) \
	RTE_LOG(level, PMD, "%s(): " fmt "\n", __func__, ## args)
#else
#define PMD_RX_LOG(level, fmt, args...) do { } while(0)
#endif

#ifdef RTE_LIBRTE_PC802_DEBUG_TX
#define PMD_TX_LOG(level, fmt, args...) \
	RTE_LOG(level, PMD, "%s(): " fmt "\n", __func__, ## args)
#else
#define PMD_TX_LOG(level, fmt, args...) do { } while(0)
#endif

#ifdef RTE_LIBRTE_PC802_DEBUG_TX_FREE
#define PMD_TX_FREE_LOG(level, fmt, args...) \
	RTE_LOG(level, PMD, "%s(): " fmt "\n", __func__, ## args)
#else
#define PMD_TX_FREE_LOG(level, fmt, args...) do { } while(0)
#endif

extern int pc802_logtype_driver;
#define PMD_DRV_LOG_RAW(level, fmt, args...) \
	rte_log(RTE_LOG_ ## level, pc802_logtype_driver, "%s(): " fmt, \
		__func__, ## args)

#define PMD_DRV_LOG(level, fmt, args...) \
	PMD_DRV_LOG_RAW(level, fmt "\n", ## args)

extern const char* pc802_core_name[];
void pc802_log( uint32_t core, const char *format, ... );
int  pc802_log_get_level( int type );
void pc802_log_set_core( uint32_t core, bool flag);
void pc802_log_change_core( uint32_t core );
void pc802_log_flush(void);
#define PC802_LOG( core, type, fmt, args...) \
	do { \
		syslog( type, "%s " fmt, pc802_core_name[core], ## args); \
		pc802_log( core, "%s " fmt, pc802_core_name[core], ## args); \
	}while (0)

/* log init function shared by e1000 and igb drivers */
void pc802_init_log(void);

struct stStat {
    uint64_t sum; // accumulated sum = s0 + s1 + s2 + ......
    uint64_t sum2; // accumulated square sum = s0*s0 + s1*s1 + s2*s2 + ......
    uint32_t max;
    uint32_t min;
    uint32_t average;
    uint32_t std_dev; //starndard deviation
    uint32_t N; // total number of samples for statistics output
    uint32_t n; // number of samples to be collect before output, its initial value is N, and then decrease to 0
    uint8_t isUsed;
    char name[16];
} __attribute__((__aligned__(64)));

typedef struct stStat Stat_t;

typedef struct {
    uint32_t max;
    uint32_t min;
    uint32_t average;
    uint32_t std_dev; //starndard deviation
} StatResult_t;

int STAT_InitPool(uint32_t num_of_stat);
int STAT_Reset(int stat_no);
int STAT_Alloc(uint32_t max_sample_num, const char *name);
int STAT_Free(int stat_no);
int STAT_Sample(int stat_no, uint32_t sample);
int STAT_CheckResult(int stat_no);
int STAT_GetResult(int stat_no, StatResult_t* pResult);

enum STAT_No_e {
    NO_CTRL_POLL,
    NO_CTRL_RECV,
    NO_CTRL_PROC,
    NO_DATA_PROC,
    NO_FUNC_PROC,
    NO_CTRL_BURST_GOT,
    NO_CTRL_BURST_NULL,
    NO_DATA_BURST_GOT,
    NO_DATA_BURST_NULL,
    NO_CTRL_DATA,
    NUM_STATS
};

void check_proc_time(uint32_t stat_no, uint64_t tdiff_64);

#endif /* _PC802_LOGS_H_ */
