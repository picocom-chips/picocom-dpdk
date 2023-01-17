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

enum bha_pcap_pkt_e {
    BHA_PCAP_PKT_ECPRI = 0,
    BHA_PCAP_PKT_ECPRI_JUMBO,
    BHA_PCAP_PKT_OTHER,
};


static char pcap_input_file[128] = {0};
static char pcap_output_file[128] = {0};

static void
test_bha_model_pcap_mode_enable(enum bha_pcap_pkt_e pkt)
{
    //select testing pcap input file and setting output file
    switch (pkt) {
        case BHA_PCAP_PKT_ECPRI:
            sprintf(pcap_input_file, "%s/%s", BHA_PCAPS_IN_PATH, "ecpri_20_pkts.pcap");
            sprintf(pcap_output_file, "%s/%s", BHA_PCAPS_OUT_PATH, "output_ecpri_pkts.pcap");
            break;

        case BHA_PCAP_PKT_ECPRI_JUMBO:
            sprintf(pcap_input_file, "%s/%s", BHA_PCAPS_IN_PATH, "ecpri_jumbo_20_pkts.pcap");
            sprintf(pcap_output_file, "%s/%s", BHA_PCAPS_OUT_PATH, "output_ecpri_jumbo_pkts.pcap");
            break;

        case BHA_PCAP_PKT_OTHER:
            sprintf(pcap_input_file, "%s/%s", BHA_PCAPS_IN_PATH, "icmp_12_pkts.pcap");
            sprintf(pcap_output_file, "%s/%s", BHA_PCAPS_OUT_PATH, "output_default_pkts.pcap");
            break;

        default:
            TESTBHA_LOG(ERR, "port[%d] ethdev bha pcap packet type illegal %d\n", bha_portid, pkt);
            return;
    }

    //bha model pcaps file mode
    TESTBHA_LOG(DEBUG, "port[%d] ethdev bha pcap input: %s\n", bha_portid, pcap_input_file);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev bha pcap output: %s\n", bha_portid, pcap_output_file);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev bha modle enable pcap mode\n", bha_portid);
    bha_simulate_pcap(pcap_input_file, pcap_output_file);
}

static void
test_bha_model_pcap_file_cmp(void)
{
    //usleep(100000); //wait for tx complete. or query consumer ptr or tx status empty
    if (bha_pcap_cmp(pcap_input_file, pcap_output_file, false))
        TESTBHA_LOG(ERR, "port[%d] ethdev testing pcap file cmp fail!!! \n", bha_portid);
    //bha_abort();
}

static void
test_bha_pcap_mode_init(void)
{
    int ret = 0;
    struct rte_eth_dev_info dev_info;
    int socket_id;
    struct rte_eth_txconf tx_conf;
    struct rte_eth_rxconf rxq_conf0, rxq_conf1;
    //struct filter_conf_s fconf0, fconf1;
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
    //fconf0.et_conf.filter_id = 0; //ether type filter id 0(<BHA_ETH_TYPE_FILTER_ID_MAX) to bonding rxq id
    //fconf0.et_conf.ether_type = 0xaefe; //ecpri pkts
    //fconf0.et_conf.congestion_action = CA_OPS_BLOCKING;
    //rxq_conf0.reserved_ptrs[0] = (void *)&fconf0;
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
    //fconf1.et_conf.filter_id = BHA_ETH_TYPE_FILTER_ID_DFLT; //default filter id to bonding rxq id
    //fconf1.et_conf.ether_type = 0; //any pkts exclude ecpri pkts
    //fconf1.et_conf.congestion_action = CA_OPS_BLOCKING;
    //rxq_conf1.reserved_ptrs[0] = (void *)&fconf1;
    //rx queue 1, nb desc 32
    ret = rte_eth_rx_queue_setup(bha_portid, 1, 32, socket_id, &rxq_conf1, mbuf_pool);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev rx queue 1 setup done. ret %d\n", bha_portid, ret);


    TESTBHA_LOG(DEBUG, "port[%d] ethdev startup...\n", bha_portid);
    ret = rte_eth_dev_start(bha_portid);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev startup done. ret %d\n", bha_portid, ret);
}

void
test_bha_pcap_mode_ecpri_20pkts(void)
{
    uint16_t nb_pkts = 0;
    struct rte_mbuf *pkts_burst[64];
    static uint32_t pkt_cnt = 0;


    test_bha_model_pcap_mode_enable(BHA_PCAP_PKT_ECPRI);
    test_bha_pcap_mode_init();

    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing rxq0 burst\n", bha_portid);
    while (pkt_cnt < 20) {
        nb_pkts = rte_eth_rx_burst(bha_portid, 0, (pkts_burst + pkt_cnt), (20 - pkt_cnt));
        if (nb_pkts != 0) {
            pkt_cnt += nb_pkts;
            TESTBHA_LOG(DEBUG, "port[%d] ethdev testing rxq0 burst nb %d, total %d\n", bha_portid, nb_pkts, pkt_cnt);
        }
        //usleep(100000);
    }

    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing txq0 burst\n", bha_portid);
    nb_pkts = rte_eth_tx_burst(bha_portid, 0, pkts_burst, pkt_cnt);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing txq0 burst nb %d\n", bha_portid, nb_pkts);

    test_bha_model_pcap_file_cmp();
}

void
test_bha_pcap_mode_dfltq_pkts(void)
{
    uint16_t nb_pkts = 0;
    struct rte_mbuf *pkts_burst[64];
    static uint32_t pkt_cnt = 0;


    test_bha_model_pcap_mode_enable(BHA_PCAP_PKT_OTHER);
    test_bha_pcap_mode_init();

    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing rxq1 burst\n", bha_portid);
    while (pkt_cnt < 12) {
        nb_pkts = rte_eth_rx_burst(bha_portid, 1, (pkts_burst + pkt_cnt), (12 - pkt_cnt));
        if (nb_pkts != 0) {
            pkt_cnt += nb_pkts;
            TESTBHA_LOG(DEBUG, "port[%d] ethdev testing rxq1 burst nb %d, total %d\n", bha_portid, nb_pkts, pkt_cnt);
        }
        //usleep(100000);
    }

    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing txq0 burst\n", bha_portid);
    nb_pkts = rte_eth_tx_burst(bha_portid, 0, pkts_burst, pkt_cnt);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing txq0 burst nb %d\n", bha_portid, nb_pkts);

    test_bha_model_pcap_file_cmp();
}

void
test_bha_pcap_mode_ecpri_jumbo_pkts(void)
{
    uint16_t nb_pkts = 0;
    struct rte_mbuf *pkts_burst[64];
    static uint32_t pkt_cnt = 0;
    static uint32_t tx_cnt = 0;


    test_bha_model_pcap_mode_enable(BHA_PCAP_PKT_ECPRI_JUMBO);
    test_bha_pcap_mode_init();

    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing rxq0 burst\n", bha_portid);
    while (pkt_cnt < 20) {
        nb_pkts = rte_eth_rx_burst(bha_portid, 0, (pkts_burst + pkt_cnt), (20 - pkt_cnt));
        if (nb_pkts != 0) {
            pkt_cnt += nb_pkts;
            TESTBHA_LOG(DEBUG, "port[%d] ethdev testing rxq0 burst nb %d, total %d\n", bha_portid, nb_pkts, pkt_cnt);
        }
        //usleep(100000);
    }

    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing txq0 burst\n", bha_portid);
    while (tx_cnt < pkt_cnt) {
        nb_pkts = rte_eth_tx_burst(bha_portid, 0, (pkts_burst + tx_cnt), (pkt_cnt - tx_cnt));
        if (nb_pkts != 0) {
            tx_cnt += nb_pkts;
            TESTBHA_LOG(DEBUG, "port[%d] ethdev testing txq0 burst nb %d, total %d\n", bha_portid, nb_pkts, tx_cnt);
        }
        //usleep(100000);
    }

    test_bha_model_pcap_file_cmp();
}
