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
You can enter the index of the PC802 through the pc802_get_port_id interface to get the port ID.

.. code-block:: c

    int main(int argc, char** argv)
    {
        int diag;
        int pc802_index = 0;

        ...

        diag = rte_eal_init(argc, argv);
        if (diag < 0)
            rte_panic("Cannot init EAL\n");

        pcxx_oam_init();
        for ( pc802_index=0; pc802_index<pcxxGetDevCount(); pc802_index++ )
        {
            port_init(pc802_index);
        }

        ...

        return 0;
    }

    static int port_init(uint16_t pc802_index){
        struct rte_mempool* mbuf_pool;
        struct rte_eth_dev_info dev_info;
        struct rte_eth_txconf tx_conf;
        int socket_id;
        uint16_t cell;
        int port = pc802_get_port_id(pc802_index);

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

        for (cell = 0; cell < CELL_NUM_PRE_DEV; cell++)
        {
            pcxxDataOpen(&data_cb_info, pc802_index, cell);
            pcxxCtrlOpen(&ctrl_cb_info, pc802_index, cell);
        }

        rte_eth_dev_start(port);
    }

Create an infinite loop of task to poll the ctrl channels. Because data is an accompanying channel to a ctrl channel, there is no need to create a separate receiving task.

.. code-block:: c

    while (1) {
        pcxxCtrlRecv(pc802_index, cell_index);
    }

To enable the OAM function, you need to call pcxx_oam_init for initialization. Then call OAM lib interfaces, Register the callback function to receive OAM messages and send OAM messages.

.. note:: OAM messages are defined in document PC-003615-DC-1-NR_PHY_OAM_API_Specification, please contact `Picocom <info@picocom.com>`_.

Data exchange process
---------------------

.. _figure_mac_phy_data_exchange:

.. figure:: img/mac_phy_data_exchange.*

   Data exchange process between PHY and MAC
