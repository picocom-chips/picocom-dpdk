/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <ethdev_driver.h>
#include <ethdev_vdev.h>
#include <rte_atomic.h>
#include <rte_branch_prediction.h>
#include <rte_bus_vdev.h>
#include <rte_byteorder.h>
#include <rte_common.h>
#include <rte_cycles.h>
#include <rte_debug.h>
#include <rte_errno.h>
#include <rte_ethdev.h>
#include <rte_ip.h>
#include <rte_kvargs.h>
#include <rte_malloc.h>
#include <rte_mbuf.h>
#include <rte_net.h>
#include <rte_string_fns.h>

#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/if_ether.h>
#include <net/if.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>

#include <bha_desc.h>
#include <bha_model.h>
#include <bha_regs.h>

#include <bha_ethdev.h>
#include <bha_rxtx.h>
#include <bha_log.h>


//enable tap mode and input specific tap device
#define BHA_MODE_TAP_ARG    "tap"
//support queue numbers
#define BHA_MAX_RXQN_ARG    "max_rxq_nb"
//queue number to config default rx queue
#define BHA_DEFAULTQ_ARG    "dqn"
//filter - eth type bonding queue id
#define BHA_FILTER_ET0_QID_ARG  "et0_qid"
#define BHA_FILTER_ET1_QID_ARG  "et1_qid"
#define BHA_FILTER_ET2_QID_ARG  "et2_qid"
#define BHA_FILTER_ET3_QID_ARG  "et3_qid"
#define BHA_FILTER_ET_QID_STR   "_qid"
//filter - eth type conf
#define BHA_FILTER_ET0_ARG      "et0"
#define BHA_FILTER_ET1_ARG      "et1"
#define BHA_FILTER_ET2_ARG      "et2"
#define BHA_FILTER_ET3_ARG      "et3"
#define BHA_FILTER_ET_STR       "et"


//BHA TAP mode. ipsec-gw need enable rx checksum offload
#define BHA_RX_OFFLOAD  (RTE_ETH_RX_OFFLOAD_IPV4_CKSUM | \
                         RTE_ETH_RX_OFFLOAD_UDP_CKSUM |  \
                         RTE_ETH_RX_OFFLOAD_TCP_CKSUM)


static int
eth_bha_configure(struct rte_eth_dev* dev)
{
    dev = dev;

    BHA_LOG(DEBUG, "bha ethdev configure");
    return 0;
}

static int
eth_bha_link_update(struct rte_eth_dev* dev,
    int wait_to_complete __rte_unused)
{
    dev = dev;

    BHA_LOG(DEBUG, "bha port (%d) link st update", dev->data->port_id);

    return 0;
}

static int
eth_bha_link_set_up(struct rte_eth_dev *dev)
{
    dev->data->dev_link.link_status = RTE_ETH_LINK_UP;
    return 0;
}

static int
eth_bha_link_set_down(struct rte_eth_dev *dev)
{
    dev->data->dev_link.link_status = RTE_ETH_LINK_DOWN;
    return 0;
}

static int
eth_bha_set_mac_address(struct rte_eth_dev* dev,
    struct rte_ether_addr* addr)
{
    BHA_LOG(DEBUG, "bha ethdev set mac addr");
    rte_ether_addr_copy(addr, &dev->data->mac_addrs[0]);
    return 0;
}

static int
eth_bha_infos_get(__rte_unused struct rte_eth_dev* dev,
    struct rte_eth_dev_info* dev_info)
{
    dev = dev;

    BHA_LOG(DEBUG, "bha ethdev get dev infos");

    dev_info->min_rx_bufsize = BHA_RX_BUF_MIN_SIZE;
    dev_info->max_rx_pktlen = BHA_RX_PKT_MAX_LEN; //min 1536
    dev_info->max_mac_addrs = 1;

    dev_info->max_rx_queues = BHA_RXQ_MAX_NUM; //current bha support 5 queue, (0~3) config, (4) default
    dev_info->max_tx_queues = BHA_TXQ_MAX_NUM;

    dev_info->max_mtu = dev_info->max_rx_pktlen - (RTE_ETHER_HDR_LEN + RTE_ETHER_CRC_LEN);
    dev_info->min_mtu = RTE_ETHER_MIN_MTU;

#ifdef RTE_NET_BHA_MODEL_EN
    dev_info->rx_queue_offload_capa = BHA_RX_OFFLOAD;
    dev_info->rx_offload_capa = dev_info->rx_queue_offload_capa;
#else
    dev_info->rx_queue_offload_capa = 0;
    dev_info->rx_offload_capa = 0;
#endif
    dev_info->tx_queue_offload_capa = 0;
    dev_info->tx_offload_capa = 0;

    dev_info->rx_desc_lim = (struct rte_eth_desc_lim) {
        .nb_max = BHA_MAX_DESC_NUM,
        .nb_min = BHA_MIN_DESC_NUM,
        .nb_align = BHA_DESC_ALIGN_NUM,
    };

    dev_info->tx_desc_lim = (struct rte_eth_desc_lim) {
        .nb_max = BHA_MAX_DESC_NUM,
        .nb_min = BHA_MIN_DESC_NUM,
        .nb_align = BHA_DESC_ALIGN_NUM,
        //.nb_seg_max = 1, //tso, total number of data descs allowed by dev
        .nb_mtu_seg_max = BHA_MAX_SEGMENTS_NUM, //if non-tso, max allowed nb of segments in a single tx pkt
    };

    dev_info->speed_capa = RTE_ETH_LINK_SPEED_FIXED;

    /* Preferred queue parameters */
    dev_info->default_rxportconf.nb_queues = BHA_RXQ_MAX_NUM;
    dev_info->default_txportconf.nb_queues = BHA_TXQ_MAX_NUM;
    dev_info->default_txportconf.ring_size = BHA_MAX_DESC_NUM;
    dev_info->default_rxportconf.ring_size = BHA_MAX_DESC_NUM;

    return 0;
}

static int
eth_bha_stats_get(struct rte_eth_dev* dev,
    struct rte_eth_stats* stats)
{
    int i;
    struct bha_rx_queue* rxq;
    struct bha_tx_queue* txq;
    uint64_t tx_total = 0, tx_bytes_total = 0, tx_err_total = 0;
    uint64_t rx_total = 0, rx_bytes_total = 0;
    uint64_t rx_nombuf = 0, rx_missed = 0, rx_err_total = 0;

    BHA_LOG(DEBUG, "bha ethdev status get, nb_rx_queues %d, nb_tx_queues %d", dev->data->nb_rx_queues, dev->data->nb_tx_queues);

    for (i = 0; i < dev->data->nb_rx_queues; i++) {
        rxq = dev->data->rx_queues[i];
        stats->q_ipackets[i] = rxq->stats.packets;
        stats->q_ibytes[i] = rxq->stats.bytes;
        stats->q_errors[i] = rxq->stats.missed; //dropped rx pkts
        rx_total += stats->q_ipackets[i];
        rx_bytes_total += stats->q_ibytes[i];
        rx_err_total += rxq->stats.errors;
        rx_nombuf += rxq->stats.nombuf; //alloc mbuf fail
        rx_missed += stats->q_errors[i];
    }

    for (i = 0; i < dev->data->nb_tx_queues; i++) {
        txq = dev->data->tx_queues[i];
        stats->q_opackets[i] = txq->stats.packets;
        stats->q_obytes[i] = txq->stats.bytes;
        tx_total += stats->q_opackets[i];
        tx_bytes_total += stats->q_obytes[i];
        tx_err_total += txq->stats.errors;
    }

    stats->ipackets = rx_total;
    stats->ibytes = rx_bytes_total;
    stats->ierrors = rx_err_total;
    stats->rx_nombuf = rx_nombuf;
    stats->imissed = rx_missed;
    stats->opackets = tx_total;
    stats->oerrors = tx_err_total;
    stats->obytes = tx_bytes_total;

    return 0;
}

static int
eth_bha_stats_reset(struct rte_eth_dev* dev)
{
    int i;
    struct bha_rx_queue* rxq;
    struct bha_tx_queue* txq;

    BHA_LOG(DEBUG, "bha ethdev status reset, nb_rx_queues %d, nb_tx_queues %d", dev->data->nb_rx_queues, dev->data->nb_tx_queues);

    for (i = 0; i < dev->data->nb_rx_queues; i++) {
        rxq = dev->data->rx_queues[i];
        rxq->stats.packets = 0;
        rxq->stats.bytes = 0;
        rxq->stats.errors = 0;
        rxq->stats.nombuf = 0;
        rxq->stats.missed = 0;
    }

    for (i = 0; i < dev->data->nb_tx_queues; i++) {
        txq = dev->data->tx_queues[i];
        txq->stats.packets = 0;
        txq->stats.bytes = 0;
        txq->stats.errors = 0;
    }

    return 0;
}


static int
eth_bha_stop(struct rte_eth_dev* dev)
{
    BHA_LOG(DEBUG, "ethdev bha[%d] stop", dev->data->port_id);

    //stop adapter

    eth_bha_link_set_down(dev);

    //clear and reset queues
    bha_dev_clear_and_reset_queues(dev);

    /* Clear stored conf */
	dev->data->scattered_rx = 0;
	dev->data->lro = 0;
    dev->data->dev_started = 0;

    return 0;
}

static int
eth_bha_close(struct rte_eth_dev* dev)
{
    BHA_LOG(DEBUG, "ethdev bha[%d] close", dev->data->port_id);

    if (rte_eal_process_type() != RTE_PROC_PRIMARY)
        return 0;

    eth_bha_link_set_down(dev);

    if (dev->data->dev_started != 0)
        eth_bha_stop(dev);

    //mac_addrs point to adapter mac_addrs. Free it if independent allocated mem.
    dev->data->mac_addrs = NULL;
    bha_dev_free_queues(dev);

#ifdef RTE_NET_BHA_MODEL_EN
    //bha model abort
    bha_abort();
#endif

    return 0;
}

static int
eth_bha_start(struct rte_eth_dev* dev)
{
    unsigned int i;
    int ret;

    BHA_LOG(DEBUG, "ethdev bha[%d] start, lcore id %d", dev->data->port_id, rte_lcore_id());

    for (i = 0; i < dev->data->nb_tx_queues; i++) {
        ret = bha_dev_tx_queue_start(dev, i);
        if (ret < 0)
            return ret;
    }

    for (i = 0; i < dev->data->nb_rx_queues; i++) {
        ret = bha_dev_rx_queue_start(dev, i);
        if (ret < 0)
            return ret;
    }

    //adapter rx and tx enbale
    BHA_LOG(DEBUG, "ethdev bha[%d] model start rx and tx", dev->data->port_id);
    bha_reg_write(RX_EN, 1);
    bha_reg_write(TX_EN, 1);

    eth_bha_link_set_up(dev);

    return 0;
}

static int
eth_bha_mtu_set(struct rte_eth_dev *dev, uint16_t mtu)
{
    struct rte_eth_dev_info dev_info;
    uint32_t frame_size = mtu + (RTE_ETHER_HDR_LEN + RTE_ETHER_CRC_LEN);
    int ret;

    ret = eth_bha_infos_get(dev, &dev_info);
    if (ret != 0)
        return ret;

    /* check that mtu is within the allowed range */
    if (mtu < RTE_ETHER_MIN_MTU || frame_size > dev_info.max_rx_pktlen)
        return -EINVAL;

    /* If device is started, refuse mtu that requires the support of
     * scattered packets when this feature has not been enabled before.
     */
    //!dev->data->scattered_rx &&
    if (dev->data->dev_started &&
        frame_size + 2 * RTE_VLAN_HLEN >
            dev->data->min_rx_buf_size - RTE_PKTMBUF_HEADROOM) {
        BHA_LOG(ERR, "Stop port first.");
        return -EINVAL;
    }

    return 0;
}

static int
eth_bha_promisc_enable(struct rte_eth_dev *dev __rte_unused)
{
    BHA_LOG(DEBUG, "bha ethdev promisc enable");
    return 0;
}

static int
eth_bha_promisc_disable(struct rte_eth_dev *dev __rte_unused)
{
    BHA_LOG(DEBUG, "bha ethdev promisc disable");
    return 0;
}

static const struct eth_dev_ops bha_ops = {
    .dev_configure = eth_bha_configure,
    .dev_start = eth_bha_start,
    .dev_stop = eth_bha_stop,
    .dev_close = eth_bha_close,
    .link_update = eth_bha_link_update,
    .dev_set_link_up = eth_bha_link_set_up,
    .dev_set_link_down = eth_bha_link_set_down,
    .promiscuous_enable = eth_bha_promisc_enable,
    .promiscuous_disable = eth_bha_promisc_disable,
    .mac_addr_set = eth_bha_set_mac_address,
    .dev_infos_get = eth_bha_infos_get,
    .stats_get = eth_bha_stats_get,
    .stats_reset = eth_bha_stats_reset,
    .rx_queue_setup = eth_bha_rx_queue_setup,
    .tx_queue_setup = eth_bha_tx_queue_setup,
    .rx_queue_release = eth_bha_rx_queue_release,
    .tx_queue_release = eth_bha_tx_queue_release,
    .mtu_set = eth_bha_mtu_set,
};

static bool
is_valid_tap_iface(const char *name)
{
    if (*name == '\0')
        return false;

    //format tap?
    if (strlen(name) <= 3)
        return false;

    //format tap?
    if (0 != memcmp(name, "tap", 3))
        return false;

    return true;
}

static int
get_tap_ifname_arg(const char *key __rte_unused,
           const char *value,
           void *extra_args)
{
    char *name = (char *)extra_args;

    //BHA_LOG(DEBUG, "---parse tap ifname func---");
    if (value) {
        if (!is_valid_tap_iface(value)) {
            BHA_LOG(ERR, "invalid param tap interface name (%s)",
                value);
            return -1;
        }
        BHA_LOG(DEBUG, "get input tap interface name (%s)", value);
        strlcpy(name, value, RTE_ETH_NAME_MAX_LEN);
    } else
        return -1;

    return 0;
}

static int
get_int_val_arg(const char *key __rte_unused,
        const char *value, void *extra_args)
{
    const char *a = value;
    int *arg_int = extra_args;

    //BHA_LOG(DEBUG, "---parse int value arg func---");
    if ((value == NULL) || (extra_args == NULL))
        return -EINVAL;

    *arg_int = (int)strtol(a, NULL, 0);

    return 0;
}

static int
get_uint_val_arg(const char *key __rte_unused,
        const char *value, void *extra_args)
{
    const char *a = value;
    unsigned int *arg_uint = extra_args;

    //BHA_LOG(DEBUG, "---parse unsigned int arg func---");
    if ((value == NULL) || (extra_args == NULL))
        return -EINVAL;

    *arg_uint = (unsigned int)strtoul(a, NULL, 0);
    if (*arg_uint == UINT_MAX)
        return -1;

    return 0;
}


static void
eth_bha_parse_input_params(struct rte_eth_dev* eth_dev, const char *params)
{
    struct bha_adapter* adapter = eth_dev->data->dev_private;
    struct rte_kvargs *kvlist = NULL;
    uint32_t max_rxq_nb = 0;
    int default_qid = -1;
    int et_qid[BHA_ETH_TYPE_FILTER_ID_MAX] = {-1,-1,-1,-1};
    uint32_t et_val[BHA_ETH_TYPE_FILTER_ID_MAX] = {0,0,0,0};
    char param_str[16];
    uint32_t i = 0;
    int ret = 0;
#ifdef RTE_NET_BHA_MODEL_EN
    char *ifname;
#endif

    const char *valid_arguments[] = {
#ifdef RTE_NET_BHA_MODEL_EN
        BHA_MODE_TAP_ARG,
#endif
        BHA_MAX_RXQN_ARG,
        BHA_DEFAULTQ_ARG,
        BHA_FILTER_ET0_QID_ARG,
        BHA_FILTER_ET0_ARG,
        BHA_FILTER_ET1_QID_ARG,
        BHA_FILTER_ET1_ARG,
        BHA_FILTER_ET2_QID_ARG,
        BHA_FILTER_ET2_ARG,
        BHA_FILTER_ET3_QID_ARG,
        BHA_FILTER_ET3_ARG,
        NULL
    };

    kvlist = rte_kvargs_parse(params, valid_arguments);
    if (kvlist != NULL) {
#ifdef RTE_NET_BHA_MODEL_EN
        ifname = adapter->tap_ifname;
        adapter->tap_mode_en = false;
        memset(ifname, 0, RTE_ETH_NAME_MAX_LEN);
        ret = rte_kvargs_process(kvlist,
                BHA_MODE_TAP_ARG,
                &get_tap_ifname_arg, ifname);
        if (ret < 0) {
            BHA_LOG(DEBUG, "ethdev bha model parse tap iface name fail. ret %d", ret);
        } else {
            if (is_valid_tap_iface(adapter->tap_ifname)) {
                BHA_LOG(DEBUG, "ethdev bha model get iface[%s] and enable tap mode", adapter->tap_ifname);
                bha_simulate_tap(adapter->tap_ifname);
                adapter->tap_mode_en = true;
            }
        }
#endif

        adapter->max_rxq_nb = 0;
        ret = rte_kvargs_process(kvlist,
                BHA_MAX_RXQN_ARG,
                &get_uint_val_arg, &max_rxq_nb);
        if (ret < 0) {
            BHA_LOG(ERR, "ethdev bha model parse max rx queue number fail. ret %d", ret);
        } else {
            if ((max_rxq_nb > 0) && (max_rxq_nb <= 5)) {
                BHA_LOG(DEBUG, "ethdev bha model parse max rx queue number %d. expect <= 5", max_rxq_nb);
                adapter->max_rxq_nb = max_rxq_nb;
            }
        }

        adapter->default_qid = -1;
        ret = rte_kvargs_process(kvlist,
                BHA_DEFAULTQ_ARG,
                &get_int_val_arg, &default_qid);
        if (ret < 0) {
            BHA_LOG(ERR, "ethdev bha model parse rx filter default queue id fail. ret %d", ret);
        } else {
            if (default_qid >= 0) {
                BHA_LOG(DEBUG, "ethdev bha model conf rx filter default queue id %d. expect (0~4)", default_qid);
                adapter->default_qid = default_qid;
            }
        }

        for (i = 0; i < BHA_ETH_TYPE_FILTER_ID_MAX; i++) {
            adapter->filter_et_qid[i] = -1;
            adapter->filter_et[i] = 0;

            memset(param_str, 0, 16);
            sprintf(param_str, "%s%d%s", BHA_FILTER_ET_STR, i, BHA_FILTER_ET_QID_STR);
            //BHA_LOG(DEBUG, "ethdev bha model parse param - %s", param_str);
            ret = rte_kvargs_process(kvlist,
                    param_str,
                    &get_int_val_arg, &et_qid[i]);
            if (ret < 0) {
                BHA_LOG(ERR, "ethdev bha model parse eth type filter[%d] conf qid fail. ret %d", i, ret);
            } else {
                if ((et_qid[i] >= 0) && (et_qid[i] < 5)) {
                    BHA_LOG(DEBUG, "ethdev bha model parse eth type filter[%d] conf queue id %d. expect (0~4)", i, et_qid[i]);
                    adapter->filter_et_qid[i] = et_qid[i];
                }
            }

            memset(param_str, 0, 16);
            sprintf(param_str, "%s%d", BHA_FILTER_ET_STR, i);
            //BHA_LOG(DEBUG, "ethdev bha model parse param - %s", param_str);
            ret = rte_kvargs_process(kvlist,
                    param_str,
                    &get_uint_val_arg, &et_val[i]);
            if (ret < 0) {
                BHA_LOG(ERR, "ethdev bha model parse eth type filter[%d] conf val fail. ret %d", i, ret);
            } else {
                if ((et_val[i] > 0) && (et_val[i] < 0xFFFF)) {
                    BHA_LOG(DEBUG, "ethdev bha model parse eth type filter[%d] type 0x%x", i, et_val[i]);
                    adapter->filter_et[i] = et_val[i];
                }
            }
        }

        rte_kvargs_free(kvlist);
    }
}

static int
rte_pmd_bha_probe(struct rte_vdev_device* vdev)
{
    const char* name;
    struct rte_eth_dev* eth_dev;
    struct bha_adapter* adapter;
    struct rte_eth_dev_data* data;
    const char *params;

    name = rte_vdev_device_name(vdev);
    params = rte_vdev_device_args(vdev);
    BHA_LOG(DEBUG, "Initializing pmd bha for %s", name);

    //vdev set defaut socket id any, update to the real numa node
    vdev->device.numa_node = rte_socket_id();
    BHA_LOG(DEBUG, "vdev device numa node %d", vdev->device.numa_node);
    eth_dev = rte_eth_vdev_allocate(vdev, sizeof(*adapter));
    if (!eth_dev) {
        BHA_LOG(ERR, "bha fails to alloc device");
        return -ENOMEM;
    }
    BHA_LOG(DEBUG, "ethdev bha name %s", eth_dev->data->name);
    BHA_LOG(DEBUG, "ethdev bha rte_device name %s", vdev->device.name);

    //setup bha info
    data = eth_dev->data;
    adapter = eth_dev->data->dev_private;
    adapter->dev = eth_dev;
    //vdev set defaut socket id any, and same to vdev numa_node
    BHA_LOG(DEBUG, "bha ethdev numa node %d", data->numa_node);
    adapter->port_id = data->port_id;

    //setup default mac addrs
    data->mac_addrs = &adapter->eth_addr;
    adapter->eth_addr.addr_bytes[0] = 0x8C;
    adapter->eth_addr.addr_bytes[1] = 0x1F;
    adapter->eth_addr.addr_bytes[2] = 0x64;
    adapter->eth_addr.addr_bytes[3] = 0xB4;
    adapter->eth_addr.addr_bytes[4] = 0xE0;
    adapter->eth_addr.addr_bytes[5] = 0x00;

    //ethdev operations
    eth_dev->dev_ops = &bha_ops;
    eth_dev->rx_pkt_burst = eth_bha_rx_pkt_burst;
    eth_dev->tx_pkt_burst = eth_bha_tx_pkt_burst;

    //parse input params
    if (params != NULL) {
        eth_bha_parse_input_params(eth_dev, params);
    }

    rte_eth_dev_probing_finish(eth_dev);
    BHA_LOG(DEBUG, "---bha probe complete---");

    return 0;
}

static int
rte_pmd_bha_remove(struct rte_vdev_device* vdev)
{
    struct rte_eth_dev* eth_dev = NULL;
    //struct bha_adapter *adapter;
    int ret;

    BHA_LOG(DEBUG, "bha remove name %s", rte_vdev_device_name(vdev));
    /* find the ethdev entry */
    eth_dev = rte_eth_dev_allocated(rte_vdev_device_name(vdev));
    if (eth_dev == NULL)
        return -ENODEV;

    //adapter = eth_dev->data->dev_private;

    ret = rte_eth_dev_release_port(eth_dev);
    if (ret != 0)
        return -EINVAL;

    BHA_LOG(DEBUG, "---bha remove complete---");

    return 0;
}

static struct rte_vdev_driver pmd_bha_drv = {
    .probe = rte_pmd_bha_probe,
    .remove = rte_pmd_bha_remove,
};

RTE_PMD_REGISTER_VDEV(net_bha, pmd_bha_drv);
RTE_PMD_REGISTER_ALIAS(net_bha, eth_bha);
RTE_LOG_REGISTER_DEFAULT(bha_logtype, NOTICE);
RTE_PMD_REGISTER_PARAM_STRING(net_bha,
#ifdef RTE_NET_BHA_MODEL_EN
                            BHA_MODE_TAP_ARG "=<string>"
#endif
                            BHA_MAX_RXQN_ARG "=<uint32>"
                            BHA_DEFAULTQ_ARG "=<int>"
                            BHA_FILTER_ET0_QID_ARG "=<int>"
                            BHA_FILTER_ET0_ARG "=<uint32>"
                            BHA_FILTER_ET1_QID_ARG "=<int>"
                            BHA_FILTER_ET1_ARG "=<uint32>"
                            BHA_FILTER_ET2_QID_ARG "=<int>"
                            BHA_FILTER_ET2_ARG "=<uint32>"
                            BHA_FILTER_ET3_QID_ARG "=<int>"
                            BHA_FILTER_ET3_ARG "=<uint32>"
                            );
