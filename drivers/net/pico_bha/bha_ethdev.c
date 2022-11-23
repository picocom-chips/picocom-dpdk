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


static int
eth_bha_configure(struct rte_eth_dev* dev)
{
    dev = dev;

    BHA_LOG(DEBUG, "bha ethdev configure");
    return 0;
}


static int
eth_bha_start(struct rte_eth_dev* dev)
{
    unsigned int i;
    int ret;

    BHA_LOG(DEBUG, "ethdev bha[%d] start", dev->data->port_id);

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
    BHA_LOG(DEBUG, "ethdev bha[%d] modle start rx and tx", dev->data->port_id);
    bha_reg_write(RX_EN, 1);
    bha_reg_write(TX_EN, 1);

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
eth_bha_promiscuous_enable(struct rte_eth_dev* dev)
{
    dev = dev;

    BHA_LOG(DEBUG, "bha ethdev promisc enable");

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

    dev_info->min_rx_bufsize = 128; /* See BSIZE field of RCTL register. */
    dev_info->max_rx_pktlen = 1536; //em_get_max_pktlen(dev); sys calc framesize 1536
    dev_info->max_mac_addrs = 1; //hw->mac.rar_entry_count;

    dev_info->max_rx_queues = 5; //current bha support 5 queue, (0~3) config, (4) default
    dev_info->max_tx_queues = 1;

    dev_info->rx_queue_offload_capa = 0;
    dev_info->rx_offload_capa = 0;
    dev_info->tx_queue_offload_capa = 0;
    dev_info->tx_offload_capa = 0;

    dev_info->rx_desc_lim = (struct rte_eth_desc_lim) {
        .nb_max = BHA_MAX_DESC_NUM,
        .nb_min = BHA_MIN_DESC_NUM,
        .nb_align = BHA_DESC_ALIGN_NUM,
        .nb_seg_max = 1,
        .nb_mtu_seg_max = 1,
    };

    dev_info->tx_desc_lim = (struct rte_eth_desc_lim) {
        .nb_max = BHA_MAX_DESC_NUM,
        .nb_min = BHA_MIN_DESC_NUM,
        .nb_align = BHA_DESC_ALIGN_NUM,
        .nb_seg_max = 1,
        .nb_mtu_seg_max = 1,
    };

    dev_info->speed_capa = RTE_ETH_LINK_SPEED_FIXED;

    /* Preferred queue parameters */
    dev_info->default_rxportconf.nb_queues = 5;
    dev_info->default_txportconf.nb_queues = 1;
    dev_info->default_txportconf.ring_size = BHA_MAX_DESC_NUM;
    dev_info->default_rxportconf.ring_size = BHA_MAX_DESC_NUM;

    return 0;
}

static int
eth_bha_stats_get(struct rte_eth_dev* dev,
    struct rte_eth_stats* stats)
{
    dev = dev;
    stats = stats;

    BHA_LOG(DEBUG, "bha ethdev status get");

    return 0;
}

static int
eth_bha_stats_reset(struct rte_eth_dev* dev)
{
    dev = dev;

    BHA_LOG(DEBUG, "bha ethdev status reset");

    return 0;
}


static int
eth_bha_stop(struct rte_eth_dev* dev)
{
    BHA_LOG(DEBUG, "ethdev bha[%d] stop", dev->data->port_id);

    //stop adapter

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

    if (dev->data->dev_started != 0)
        eth_bha_stop(dev);

    //mac_addrs point to adapter mac_addrs. Free it if independent allocated mem.
    dev->data->mac_addrs = NULL;
    bha_dev_free_queues(dev);

    return 0;
}


static const struct eth_dev_ops bha_ops = {
    .dev_configure = eth_bha_configure,
    .dev_start = eth_bha_start,
    .dev_stop = eth_bha_stop,
    .dev_close = eth_bha_close,
    .link_update = eth_bha_link_update,
    .promiscuous_enable = eth_bha_promiscuous_enable,
    .mac_addr_set = eth_bha_set_mac_address,
    .dev_infos_get = eth_bha_infos_get,
    .stats_get = eth_bha_stats_get,
    .stats_reset = eth_bha_stats_reset,
    .rx_queue_setup = eth_bha_rx_queue_setup,
    .tx_queue_setup = eth_bha_tx_queue_setup,
    .rx_queue_release = eth_bha_rx_queue_release,
    .tx_queue_release = eth_bha_tx_queue_release,
};

static int
rte_pmd_bha_probe(struct rte_vdev_device* vdev)
{
    const char* name;
    struct rte_eth_dev* eth_dev;
    struct bha_adapter* adapter;
    struct rte_eth_dev_data* data;

    name = rte_vdev_device_name(vdev);
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
