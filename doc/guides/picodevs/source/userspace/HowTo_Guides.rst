How to use the API
==================

This section describes how to use the API provided by the PC802_UDriver.

Initialization process
----------------------

Before running DPDK app, all the required PCIe devices (including PC802) should be bound to DPDK low layer driver (for example, igb_uio) by using a tool like dpdk-devbind.py.  
Then the ret_eal_init( ) will probe these devices and allocate their port IDs.

The port IDs are allocated by DPDK EAL. All PCIe devices are bound to DPDK driver and a port ID is allocated for each DPDK virtual device.  
For all DPDK bound PCIe Ethernet devices (including PC802), their port IDs are in the increasing order of their specific value computed by their PCIe address. 
The value = (domain << 24) | (bus << 16) | (device << 8 ) | function.  The larger this value is, the larger the port ID is.

.. code-block:: c

    static int port_init(uint16_t port){
        struct rte_mempool* mbuf_pool;
        struct rte_eth_dev_info dev_info;
        struct rte_eth_txconf tx_conf;
        int socket_id;

        rte_eth_dev_info_get(port, &dev_info);
        socket_id = dev_info.device->numa_node;

        mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL_ETH_TX", 2048,
            128, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
        if (mbuf_pool == NULL)
            rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on Line %d\n", __LINE__);
        mpool_pc802_tx = mbuf_pool;

        mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL_ETH_RX", 2048,
            128, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
        if (mbuf_pool == NULL)
            rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on Line %d\n", __LINE__);

        rte_eth_dev_configure(port, 1, 1, &dev_conf);
        tx_conf = dev_info.default_txconf;
        rte_eth_tx_queue_setup(port, 0, 128, socket_id, &tx_conf);
        rte_eth_rx_queue_setup(port, 0, 128, socket_id, NULL, mbuf_pool);

        pcxxDataOpen(&data_cb_info);

        pcxxCtrlOpen(&ctrl_cb_info);

        pcxxOamOpen(&log_cb_info);

        rte_eth_dev_start(port);

    }

Create an infinite loop of task to poll the ctrl channels. Because data is an accompanying channel to a ctrl channel, there is no need to create a separate receiving task.

.. code-block:: c

    while (1) {
        pcxxCtrlRecv();
    }

Create an infinite loop of task to poll the oam channels

.. code-block:: c
    
    while (1) {
        pcxxOamRecv();
    }


Data exchange process
---------------------

.. _figure_mac_phy_data_exchange:

.. figure:: img/mac_phy_data_exchange.*
   
   Data exchange process between PHY and MAC
