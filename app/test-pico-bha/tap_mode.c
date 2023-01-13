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


//test bha port id
extern uint16_t bha_portid;


static void
test_bha_tap_mode_init(void)
{
    int ret = 0;
    struct rte_eth_dev_info dev_info;
    int socket_id;
    struct rte_eth_txconf tx_conf;
    struct rte_eth_rxconf rxq_conf0, rxq_conf1;
    struct rte_mempool* mbuf_pool;
    //struct rte_mempool* tx_mbuf_pool;
    char mbufp_name[32] = { 0 };
    struct rte_eth_conf dev_conf = {
        .rxmode = {
            .mtu = RTE_ETHER_MAX_LEN, //1518
        },
    };


    rte_eth_dev_info_get(bha_portid, &dev_info);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev bha dev_info numa_node %d\n", bha_portid, dev_info.device->numa_node);
    socket_id = dev_info.device->numa_node;
    //socket_id = rte_eth_dev_socket_id(bha_portid);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev info numa node id %d, device name %s, driver name %s\n", bha_portid, socket_id, dev_info.device->name, dev_info.driver_name);
    tx_conf = dev_info.default_txconf;

    //nb_tx_q 1. nb_rx_q 2, the sample use one queue to recv specific eth type pkts, the other one queue recv others pkts
    ret = rte_eth_dev_configure(bha_portid, 2, 1, &dev_conf);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev configure done. ret %d\n", bha_portid, ret);

    ////tx mbuf pool setup
    //sprintf(mbufp_name, "MBP_BHA%d_TXQ_%d", bha_portid, 0);
    ////mbuf nb 256, mbuf cache 128B, mbuf data size (2048+128)B
    //tx_mbuf_pool = rte_pktmbuf_pool_create(mbufp_name, 256,
    //    128, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    //if (tx_mbuf_pool == NULL)
    //    rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on %s Line %d\n", __func__, __LINE__);
    //tx queue id 0, nb desc 32
    ret = rte_eth_tx_queue_setup(bha_portid, 0, 32, socket_id, &tx_conf);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev tx queue setup done. ret %d\n", bha_portid, ret);

    //rx queue 0 mbuf pool create. For specific ether type pkts
    sprintf(mbufp_name, "MBP_BHA%d_RXQ_%d", bha_portid, 0);
    //mbuf nb 256, mbuf cache 128B, mbuf data size (2048+128)B
    mbuf_pool = rte_pktmbuf_pool_create(mbufp_name, 256,
        128, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on %s Line %d\n", __func__, __LINE__);
    //conf rx queue, tmp use the reserved zone in struct for bha specific rx queue conf
    //uint64_t reserved_64s[2];
    //void *reserved_ptrs[2]; //tmp in use
    rxq_conf0 = dev_info.default_rxconf;
    //rx queue 0, nb desc 32
    ret = rte_eth_rx_queue_setup(bha_portid, 0, 32, socket_id, &rxq_conf0, mbuf_pool);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev rx queue 0 setup done. ret %d\n", bha_portid, ret);

    //rx queue 1 mbuf pool create. For other pkts recv which are not specific ether type pkts
    sprintf(mbufp_name, "MBP_BHA%d_RXQ_%d", bha_portid, 1);
    //mbuf nb 256, mbuf cache 128B, mbuf data size (2048+128)B
    mbuf_pool = rte_pktmbuf_pool_create(mbufp_name, 256,
        128, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on %s Line %d\n", __func__, __LINE__);
    rxq_conf1 = dev_info.default_rxconf;
    //rx queue 1, nb desc 32
    ret = rte_eth_rx_queue_setup(bha_portid, 1, 32, socket_id, &rxq_conf1, mbuf_pool);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev rx queue 1 setup done. ret %d\n", bha_portid, ret);


    TESTBHA_LOG(DEBUG, "port[%d] ethdev startup...\n", bha_portid);
    ret = rte_eth_dev_start(bha_portid);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev startup done. ret %d\n", bha_portid, ret);
}


void
test_bha_tap_mode_dfltq_pkts(void)
{
    uint16_t nb_pkts = 0;
    struct rte_mbuf *pkts_burst[64];
    static uint32_t pkt_cnt = 0;
    uint32_t i = 0;
    uint32_t j = 0;
    struct rte_mbuf *mb;
    uint8_t *data_buf = NULL;
    uint32_t test_pkt_nb = 5;
    uint16_t test_qid = 0;


    test_bha_tap_mode_init();

    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing rxq1 burst\n", bha_portid);
    while (pkt_cnt < test_pkt_nb) {
        nb_pkts = rte_eth_rx_burst(bha_portid, test_qid, (pkts_burst + pkt_cnt), (test_pkt_nb - pkt_cnt));
        if (nb_pkts != 0) {
            for(i = pkt_cnt; i < (pkt_cnt + nb_pkts); i++) { 
                mb = pkts_burst[i];
                data_buf = (uint8_t*)((uint64_t)(mb->buf_addr) + mb->data_off);
                TESTBHA_LOG(DEBUG, "------ Dump packet header - 16B ------\n");
                //if ((0x88 == data_buf[12]) && (0xf7 == data_buf[13]))
                //    TESTBHA_LOG(DEBUG, "------ Recv ptpv2 pkt 0x88f7! len %d ------\n", mb->data_len);
                for (j = 0; j < 16; j++)
                    TESTBHA_LOG(DEBUG, "0x%x ", data_buf[j]);
                TESTBHA_LOG(DEBUG, "------ Dump packet header - 16B done! ------\n");
            }
            pkt_cnt += nb_pkts;
            TESTBHA_LOG(DEBUG, "port[%d] ethdev testing rxq1 burst nb %d, total %d\n", bha_portid, nb_pkts, pkt_cnt);
        }
        usleep(100000);
    }

    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing txq0 burst\n", bha_portid);
    nb_pkts = rte_eth_tx_burst(bha_portid, 0, pkts_burst, pkt_cnt);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing txq0 burst nb %d\n", bha_portid, nb_pkts);
}
