HowTo Guides
============

This section describes how to use some features of PC802_UDriver.

The features is integrated in the PC802_UDriver, and is supported by all NPU applications that are compiled with PC802_UDriver, such as dpdk-testpc802 in ${DPDK_PATH}app/test-PC802/.

PC802 log function
------------------

PC802_UDriver supports PC802 log output for debugging purposes.

This function default enable when PC802 is initialized, and save in syslog.

example:

.. code-block:: console

    #Boot up dpdk-testpc802 enable log:
    dpdk-testpc802

Observe syslog:

.. code-block:: console

    tail -f /var/log/syslog
    Apr 24 04:43:56 localhost dpdk-testpc802[904]: PFI 0 event[00000]: 0x4B3C2D1E(0x12CF0, 11550)
    Apr 24 04:43:56 localhost dpdk-testpc802[904]: PFI 0 event[00001]: 0x881F8C97(0x2207E, 3223)
    Apr 24 04:43:56 localhost dpdk-testpc802[904]: PFI 0 event[00002]: 0x0000018C(0x00000, 0396)
    Apr 24 04:43:56 localhost dpdk-testpc802[904]: PFI 0 event[00003]: 0x00000190(0x00000, 0400)
    Apr 24 04:43:56 localhost dpdk-testpc802[904]: PFI 0 event[00004]: 0x1E2D3C4B(0x078B4, 15435)
    Apr 24 06:14:59 localhost dpdk-testpc802[857]: PFI 0 event[00000]: 0x4B3C2D1E(0x12CF0, 11550)
    Apr 24 06:14:59 localhost dpdk-testpc802[857]: PFI 0 event[00001]: 0x881F8C97(0x2207E, 3223)
    Apr 24 06:14:59 localhost dpdk-testpc802[857]: PFI 0 event[00002]: 0x0000018C(0x00000, 0396)
    Apr 24 06:14:59 localhost dpdk-testpc802[857]: PFI 0 event[00003]: 0x00000190(0x00000, 0400)
    Apr 24 06:14:59 localhost dpdk-testpc802[857]: PFI 0 event[00004]: 0x1E2D3C4B(0x078B4, 15435)
    Apr 24 06:15:00 localhost dpdk-testpc802[857]: PFI 0 PRINTF: run_from_ilm : 58 : cid =  0


You can disable by adding "--log-level=pc802.printf:1" to the EAL argument:

.. code-block:: console

    #Boot up dpdk-testpc802 disable log:
    dpdk-testpc802 --log-level=pc802.printf:1


PC802 Telemetry commands
------------------------

PC802_UDriver supports DPDK Telemetry,Telemetry usage instructions refer to the `DPDK documentation <https://doc.dpdk.org/guides/howto/telemetry.html>`_.

Telemetry commands added by PC802_UDriver:
    /pc802/list
    /pc802/queue
    /pc802/regs
    /pc802/read_mem

example:

.. code-block:: console

    root@bj-nr-19:/home/test# dpdk-telemetry.py
    Connecting to /var/run/dpdk/rte/dpdk_telemetry.v2
    {"version": "DPDK 21.08.0", "pid": 2919, "max_output_len": 16384}
    Connected to application: "nrTestMAC"
    --> /pc802/list
    {"/pc802/list": [0, 1, 2]}
    --> /pc802/regs,0
    {"/pc802/regs": {"DEVEN": 1, "DEVRDY": 8, "DBAL": 1979252736, "DBAH": 2, "ULDMAN": 4, "TDNUM": [128, 128, 32, 0, 128, 32, 64], "TRCCNT": [0, 13865, 23114, 0, 0, 0, 0], "TEPCNT": [0, 13865, 23114, 0, 0, 0, 0], "RDNUM": [128, 128, 32, 0, 128, 32, 64], "RRCCNT": [0, 4620, 23112, 0, 0, 0, 0], "REPCNT": [0, 4620, 23112, 0, 0, 0, 0], "BOOTSRCL": 1977380608, "BOOTSRCH": 2, "BOOTDST": 0, "BOOTSZ": 0, "BOOTRCCNT": 4294967295, "BOOTRSPL": 0, "BOOTRSPH": 0, "BOOTEPCNT": 0, "BOOTERROR": 0, "BOOTDEBUG": 0, "MB_HANDSHAKE": 0, "MACADDRL": 0, "DBGRCAL": 1979318272, "DBGRCAH": 2, "MB_ANDES_DIS": 0, "MB_DSP_DIS": 0, "DBGEPADDR": 0, "DBGBYTESNUM": 0, "DBGCMD": 0, "DBGRCCNT": 0, "DBGEPCNT": 0, "DRVSTATE": 3, "MEMCFGADDR": 51444336, "ULDMA_TIMEOUT_FINISHED": [0, 0, 0, 0], "ULDMA_TIMEOUT_ERROR": [0, 0, 0, 0], "DLDMA_TIMEOUT_FINISHED": [0, 0, 0, 0], "DLDMA_TIMEOUT_ERROR": [0, 0, 0, 0]}}
    --> /pc802/queue,0,1
    {"/pc802/queue": {"dev": 0, "queue": 1, "TX_rc_cnt": 13865, "nb_tx_desc": 128, "tx_free_thresh": 32, "nb_tx_free": 37, "DL_RC": 13865, "DL_EP": 13865, "RX_rc_cnt": 4620, "nb_rx_desc": 128, "nb_rx_hold": 0, "rx_free_thresh": 32, "UL_RC": 4620, "UL_EP": 4620}}
    --> /pc802/read_mem,0,0x10040000,16
    {"/pc802/read_mem": {"10040000:": "00000001, 00000008, 75f90000, 00000002"}}


Eanble KNI function
-------------------

PC802_UDriver supports PC802 ethernet traffic forward to virtual KNI port.

When this feature is enabled, will create a KNI Linux virtual network interface for PC802.

Packets sent to the KNI Linux interface will be received by the PC802_UDriver, and PC802_UDriver may forward packets to PC802 eCPRI interface, and forward between two.

Using this function requires KNI kernel module be inserted.

You can enable by adding "--vdev=net_kni0" to the EAL argument.

example:

.. code-block:: console

    #build with kmods
    meson -Denable_kmods=true build
    ninja -C build install
    #insert rte_kni.ko
    insmod /lib/modules/$(uname -r)/extra/dpdk/rte_kni.ko carrier=on
    #Boot up dpdk-testpc802 forward PC802 ethernet traffic to kni0 virtual port:
    dpdk-testpc802 --vdev=net_kni0


Observe Linux interfaces:

.. code-block:: console

    ifconfig kni0
    kni0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 2034
            inet 192.168.1.1  netmask 255.255.255.0  broadcast 192.168.1.255
            inet6 fe80::14d9:d3ff:fe2b:d796  prefixlen 64  scopeid 0x20<link>
            ether 16:d9:d3:2b:d7:96  txqueuelen 1000  (Ethernet)
            RX packets 119  bytes 9938 (9.9 KB)
            RX errors 0  dropped 0  overruns 0  frame 0
            TX packets 119  bytes 9938 (9.9 KB)
            TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0


Capturing PC802 PCIe queue data
---------------------------------

PC802_UDriver supports capture data on PC802 PCIe queues using the dpdk-pdump tool.

dpdk-pdump usage instructions refer to the `DPDK documentation <https://doc.dpdk.org/guides/tools/pdump.html>`_.

Some parameter descriptions:

* queue: queue mask, 2-7 bits are valid (queue 0 is ethernet, which can be captured directly through the network port), input * means all queues

example:

.. code-block:: console

    #Boot up dpdk-testpc802 enable log:
    dpdk-testpc802

    #in another terminal
    #Capturing PC802 PCIe queue data to file:
    dpdk-pdump -l 0 -- --pdump 'port=0,queue=*,rx-dev=/tmp/pc802.pcap,tx-dev=/tmp/pc802.pcap,mbuf-size=32768'
    #Capturing PC802 PCIe queue data to interface:
    dpdk-pdump -l 0 -- --pdump 'port=0,queue=*,rx-dev=lo,tx-dev=lo,mbuf-size=32768'


capture data description:

* The capture data is saved as a pcap file;
* The captured queue data is stored in the UDP payload;
* Different queues are distinguished by destination ports, and queues 1-6 correspond to ports 6881-6886 respectively;
* The uplink source port is 8021, and the downlink source port is 8022;
* The option of the ip header contains the ip.opt.time_stamp field, which records the original sending and receiving time stamp of the message, and the unit is us.


.. capture_data:

.. figure:: img/capture_data.*

   Captured PC802 PCIe queue data