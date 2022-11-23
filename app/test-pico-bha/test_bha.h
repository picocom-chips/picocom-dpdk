/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#ifndef _TEST_BHA_H_
#define _TEST_BHA_H_

//test bha log
extern int testbha_logtype;

#define TESTBHA_LOG(level, fmt, args...) \
    rte_log(RTE_LOG_##level, testbha_logtype, "testbha: " fmt "\n", ##args)



//cmdline
void test_bha_cmdline(void);
void test_bha_ethdev_stop(void);
void test_bha_ethdev_close(void);
void test_bha_exit(void);


//pcap mode testing
void test_bha_pcap_mode_ecpri_20pkts(void);
void test_bha_pcap_mode_dfltq_pkts(void);
void test_bha_pcap_mode_ecpri_jumbo_pkts(void);





#endif /* _TEST_BHA_H_ */
