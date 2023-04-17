/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <unistd.h>
#include <rte_common.h>
#include <rte_ether.h>
#include <rte_version.h>
#if RTE_VERSION >= RTE_VERSION_NUM(21, 5, 0, 0)
#include <ethdev_driver.h>
#else
#include <rte_ethdev_driver.h>
#endif
#include "rte_pmd_pc802.h"
#include "pc802_ethdev.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#define PKT_BURST_SZ 32

static uint16_t kni_port = 0xFFFF;

/* Mempool for mbufs */
static struct rte_mempool *kni_pool = NULL;
static pthread_t kni_tid;

static uint16_t pc802_num = 0;
static uint16_t pc802_port[PC802_INDEX_MAX] = {0};

/* Structure type for recording kni interface specific stats */
struct kni_interface_stats {
    uint64_t rx_packets[PC802_INDEX_MAX];
    uint64_t rx_dropped;
    uint64_t tx_packets;
    uint64_t tx_dropped[PC802_INDEX_MAX];
};

/* kni device statistics array */
static struct kni_interface_stats kni_stats;

static rte_atomic32_t kni_stop = RTE_ATOMIC32_INIT(0);

int pc802_kni_init(void);
int pc802_kni_release(void);
void pc802_kni_print_stats(void);

void pc802_kni_print_stats(void)
{
    uint16_t i;

    printf("\n**PC802 KNI statistics**\n");
    printf("KNI:      rx_dropped:%lu     tx_packets:%lu\n", kni_stats.rx_dropped, kni_stats.tx_packets );

    for (i = 0; i < pc802_num; i++) {
        printf("Port%d %d:  rx_packets:%lu     tx_dropped:%lu\n",
               i, pc802_port[i], kni_stats.rx_packets[i], kni_stats.tx_dropped[i] );
    }
    printf("=======================================\n");

    fflush(stdout);
}

/**
 * Interface to burst rx and enqueue mbufs into rx_q
 */
static int kni_ingress(uint16_t index)
{
    unsigned nb_rx, num;
    struct rte_mbuf *pkts_burst[PKT_BURST_SZ];

    /* Burst rx from eth */
    nb_rx = rte_eth_rx_burst(pc802_port[index], PC802_TRAFFIC_ETHERNET, pkts_burst, PKT_BURST_SZ);
    if (0 == nb_rx) return 0;
    kni_stats.rx_packets[index] += nb_rx;

    /* Burst tx to kni */
    num = rte_eth_tx_burst(kni_port, 0, pkts_burst, nb_rx);
    if (unlikely(num < nb_rx)) {
        /* Free mbufs not tx to kni interface */
		DBLOG("kni burst fail, dropped %lu.\n", kni_stats.rx_dropped);
        rte_pktmbuf_free_bulk(&pkts_burst[num], nb_rx - num);
        kni_stats.rx_dropped += nb_rx - num;
    }

    return nb_rx;
}

/**
 * Interface to dequeue mbufs from tx_q and burst tx
 */
static int kni_egress(void)
{
    uint16_t i;
    uint16_t nb_tx, num;
    struct rte_mbuf *pkts_burst[PKT_BURST_SZ];

    /* Burst rx from kni */
    num = rte_eth_rx_burst(kni_port, 0, pkts_burst, PKT_BURST_SZ);
    if (0 == num) return 0;
    kni_stats.tx_packets += num;

    if (0 == pc802_num) {
		DBLOG("no pc802 tx dropped %lu.\n", kni_stats.tx_dropped[0]);
        rte_pktmbuf_free_bulk(pkts_burst, num);
        kni_stats.tx_dropped[0] += num;
        return num;
    }
    else if (pc802_num > 1) {
        for (i = 0; i < num; i++) {
            rte_pktmbuf_refcnt_update(pkts_burst[i], pc802_num);
        }
    }

    for (i = 0; i < pc802_num; i++) {
        /* Burst tx to eth */
        nb_tx = rte_eth_tx_burst(pc802_port[i], PC802_TRAFFIC_ETHERNET, pkts_burst, num);
        if (unlikely(nb_tx < num)) {
            /* Free mbufs not tx to NIC */
			DBLOG("pc802 %d burst fail, tx dropped %lu.\n", pc802_port[i], kni_stats.tx_dropped[i]);
            rte_pktmbuf_free_bulk(&pkts_burst[nb_tx], num - nb_tx);
            kni_stats.tx_dropped[i] += num - nb_tx;
        }
    }
    return num;
}

static void * kni_loop(void *arg __rte_unused)
{
    int i;
    int32_t f_stop;
    unsigned count;

	DBLOG("Start kni thread.\n");
    while (1) {
        f_stop = rte_atomic32_read(&kni_stop);
        if (f_stop) break;
        count = 0;
        for (i = 0; i < pc802_num; i++) {
            count += kni_ingress(i);
        }
        count += kni_egress();

        if (0 == count) {
            usleep(100);
        }
    }

    return NULL;
}

int pc802_kni_add_port(uint16_t port)
{
    // rte_eth_dev_callback_register();
    if (pc802_num >= ARRAY_SIZE(pc802_port)) return -EINVAL;

    if (0 == pc802_num) pc802_kni_init();

    pc802_port[pc802_num++] = port;
    return 0;
}

/* Initialise pc802 kni function */
int pc802_kni_init(void)
{
    struct rte_eth_conf dev_conf = {
        .rxmode =
            {
                .max_rx_pkt_len = RTE_ETHER_MAX_LEN,
            },
    };
    int ret;
    uint16_t port;
    struct rte_eth_dev_info dev_info;
    struct rte_eth_txconf tx_conf;
    int socket_id;

    RTE_ETH_FOREACH_DEV(port)
    {
        DBLOG("ETH DEV %d: %s\n", port, rte_eth_devices[port].device->name);
        if (NULL == strstr(rte_eth_devices[port].device->name, "kni")) continue;

        rte_eth_dev_info_get(port, &dev_info);
        socket_id = dev_info.device->numa_node;

        kni_pool = rte_pktmbuf_pool_create("pc802_kni", 2048, 128, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
        if (kni_pool == NULL) {
            DBLOG("Cannot create mbuf pool.\n");
            return -EINVAL;
        }

        rte_eth_dev_configure(port, 1, 1, &dev_conf);
        tx_conf = dev_info.default_txconf;
        rte_eth_tx_queue_setup(port, 0, 128, socket_id, &tx_conf);
        rte_eth_rx_queue_setup(port, 0, 128, socket_id, NULL, kni_pool);

        ret = rte_eth_dev_start(port);
        if (ret < 0) {
            DBLOG("Error starting kni dev %d.\n", port);
            return -EINVAL;
        }
        kni_port = port;
        DBLOG("Create kni port %d.\n", kni_port);

        ret = rte_ctrl_thread_create(&kni_tid, "kni", NULL, kni_loop, NULL);
        if (ret < 0) {
            DBLOG("Could not create kni thread!\n");
            return -EINVAL;
        }
        break;
    }

    return 0;
}

int pc802_kni_release(void)
{
    void *retval;

    pc802_num = 0;
    rte_atomic32_inc(&kni_stop);
    pthread_join(kni_tid, &retval);

    if (0xFFFF != kni_port) rte_eth_dev_stop(kni_port);

    if (kni_pool) kni_pool = NULL;  // rte_pktmbuf_pool_free(kni_pool);

    return 0;
}
