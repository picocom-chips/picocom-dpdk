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

//log conf
int testbha_logtype;

#define TESTBHA_LOG(level, fmt, args...) \
    rte_log(RTE_LOG_##level, testbha_logtype, "testbha: " fmt, ##args)

static void
signal_handler(int signum)
{
    if (signum == SIGINT || signum == SIGTERM) {
        printf("\n\nSignal %d received, preparing to exit...\n",
            signum);

        signal(signum, SIG_DFL);
        kill(getpid(), signum);
    }
}

int main(int argc, char** argv)
{
    int diag;
    int ret = 0;
    uint16_t count;
    uint16_t nb_ports;
    uint16_t port_id;
    uint16_t ports_ids[RTE_MAX_ETHPORTS];
    uint16_t bha_portid = 0;
    struct rte_eth_dev_info dev_info;
    int socket_id;
    struct rte_eth_txconf tx_conf;
    struct rte_eth_rxconf rxq_conf0, rxq_conf1;
    struct filter_conf_s fconf0, fconf1;
    struct rte_mempool* mbuf_pool;
    struct rte_mempool* tx_mbuf_pool;
    char mbufp_name[32] = { 0 };
    struct rte_eth_conf dev_conf = {
        .rxmode = {
            .mtu = RTE_ETHER_MAX_LEN, //1518
        },
    };
    uint16_t nb_rx_pkts = 0;
    struct rte_mbuf *pkts_burst[64];
    static uint32_t pkt_cnt = 0;


    testbha_logtype = rte_log_register("testbha");
    if (testbha_logtype < 0)
        rte_exit(EXIT_FAILURE, "Cannot register log type");
    rte_log_set_level(testbha_logtype, RTE_LOG_DEBUG);

    TESTBHA_LOG(DEBUG, "testbha logging");

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    diag = rte_eal_init(argc, argv);
    if (diag < 0)
        rte_exit(EXIT_FAILURE, "Cannot init EAL: %s\n",
            rte_strerror(rte_errno));

    //currently not support secondary startup
    if (rte_eal_process_type() == RTE_PROC_SECONDARY)
        rte_exit(EXIT_FAILURE,
            "Secondary process type not supported.\n");

    //iova don't care 0; iova_pa 1; iova_va 2
    TESTBHA_LOG(DEBUG, "Get iova mode %d\n", rte_eal_iova_mode());

    count = 0;
    RTE_ETH_FOREACH_DEV(port_id)
    {
        ports_ids[count] = port_id;
        count++;
    }
    nb_ports = count;
    if (nb_ports == 0) {
        TESTBHA_LOG(WARNING, "No probed ethernet devices\n");
    } else if (nb_ports == 1) {
        TESTBHA_LOG(DEBUG, "Probed ethernet devices nb_ports %d, the 1st portid %d\n", nb_ports, ports_ids[0]);
        bha_portid = ports_ids[0];
    } else {
        TESTBHA_LOG(ERR, "Probed ethernet devices nb_ports %d > 1, check!\n", nb_ports);
        return EXIT_FAILURE;
    }


    //bha model pcaps file mode
    TESTBHA_LOG(DEBUG, "port[%d] ethdev bha modle enable pcap file input mode\n", bha_portid);
    bha_simulate_pcap(BHA_DRV_PCAPS_IN, BHA_DRV_PCAPS_OUT);


    rte_eth_dev_info_get(bha_portid, &dev_info);
    //vdev default eth_dev->device->numa_node = SOCKET_ID_ANY (-1), get current numa node id
    socket_id = rte_eth_dev_socket_id(bha_portid);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev info numa node id %d, device name %s, driver name %s\n", bha_portid, socket_id, dev_info.device->name, dev_info.driver_name);
    tx_conf = dev_info.default_txconf;

    //nb_tx_q 1. nb_rx_q 2, the sample use one queue to recv specific eth type pkts, the other one queue recv others pkts
    ret = rte_eth_dev_configure(bha_portid, 2, 1, &dev_conf);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev configure done. ret %d\n", bha_portid, ret);

    //tx mbuf pool setup
    sprintf(mbufp_name, "MBP_BHA%d_TXQ_%d", bha_portid, 0);
    //mbuf nb 256, mbuf cache 128B, mbuf data size (2048+128)B
    tx_mbuf_pool = rte_pktmbuf_pool_create(mbufp_name, 256,
        128, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    if (tx_mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on %s Line %d\n", __func__, __LINE__);
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
    fconf0.et_conf.filter_id = 0; //ether type filter id 0 to bonding rxq id
    fconf0.et_conf.ether_type = 0xaefe; //ecpri pkts
    fconf0.et_conf.congestion_action = CA_OPS_BLOCKING;
    rxq_conf0.reserved_ptrs[0] = (void *)&fconf0;
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
    fconf1.et_conf.filter_id = 4; //ether type filter id 4(default filter id) to bonding rxq id
    fconf1.et_conf.ether_type = 0; //any pkts exclude ecpri pkts
    fconf1.et_conf.congestion_action = CA_OPS_BLOCKING;
    rxq_conf1.reserved_ptrs[0] = (void *)&fconf1;
    //rx queue 1, nb desc 32
    ret = rte_eth_rx_queue_setup(bha_portid, 1, 32, socket_id, &rxq_conf1, mbuf_pool);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev rx queue 1 setup done. ret %d\n", bha_portid, ret);


    TESTBHA_LOG(DEBUG, "port[%d] ethdev startup...\n", bha_portid);
    ret = rte_eth_dev_start(bha_portid);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev startup done. ret %d\n", bha_portid, ret);


    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing rxq0 burst\n", bha_portid);
    while (pkt_cnt < 20) {
        nb_rx_pkts = rte_eth_rx_burst(bha_portid, 0, (pkts_burst + pkt_cnt), (20 - pkt_cnt));
        if (nb_rx_pkts != 0) {
            pkt_cnt += nb_rx_pkts;
            TESTBHA_LOG(DEBUG, "port[%d] ethdev testing rxq0 burst nb %d, total %d\n", bha_portid, nb_rx_pkts, pkt_cnt);
        }
    }

    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing txq0 burst\n", bha_portid);
    nb_rx_pkts = rte_eth_tx_burst(bha_portid, 0, pkts_burst, pkt_cnt);
    TESTBHA_LOG(DEBUG, "port[%d] ethdev testing txq0 burst nb %d\n", bha_portid, nb_rx_pkts);


    while (1) {
        usleep(1000);
    }

    return EXIT_SUCCESS;
}
