.. _atll_sample:

Compile ATLL in userspace
-------------------------

Please refer to :ref:`build_PC802_PCIe_driver` for build PC802 pcie driver on NPU side.

Running ATLL sample in userspace
--------------------------------

**case 101**

Unlike case1, which uses interfaces, case101 uses interfaces packaged as pcxx for unpackaged interfaces.

.. code-block:: console
    
    PC802>> test case 101
    PC802>> Begin Test Case 101
    DL_MSG[1][188]: N=151 S=0x093D2069 D=0x23618B3F
    pc802_tx_mblk_burst : 467 : DL DESC[2][ 22]: virtAddr=0x227384C3C0 phyAddr=0x227384C3C0 Length=612 Type=2 EOP=1
    pc802_rx_mblk_burst : 409 : UL DESC[2][ 22]: virtAddr=0x226F904540 phyAddr=0x226F904540 Length=612 Type=2 EOP=1
    UL_MSG[188]: N=153 S=0x093D2069 D=0x23618B3F
    Case 101 --- PASSED

**case 102**

The same function as case2, the calling interface is different, the interface is the same as case101

.. code-block:: console
    
    PC802>> test case 102
    PC802>> Begin Test Case 102
    DL_MSG[1][189]: N= 10 S=0x2EA22C60 D=0x050A3F70
    DL_MSG[1][190]: N=296 S=0x0D9DEB29 D=0x6602005A
    pc802_tx_mblk_burst : 467 : DL DESC[1][ 38]: virtAddr=0x227B45BBC0 phyAddr=0x227B45BBC0 Length=48 Type=0 EOP=1
    pc802_tx_mblk_burst : 467 : DL DESC[2][ 23]: virtAddr=0x227388C440 phyAddr=0x227388C440 Length=1192 Type=1 EOP=1
    pc802_rx_mblk_burst : 409 : UL DESC[2][ 23]: virtAddr=0x226F9445C0 phyAddr=0x226F9445C0 Length=1192 Type=1 EOP=1
    pc802_rx_mblk_burst : 409 : UL DESC[1][ 21]: virtAddr=0x22778D44C0 phyAddr=0x22778D44C0 Length=48 Type=0 EOP=1
    UL_MSG[189]: N=12 S=0x2EA22C60 D=0x050A3F70
    UL_MSG[190]: N=298 S=0x0D9DEB29 D=0x6602005A
    Case 102 --- PASSED

**case 103**

The same function as case3, the calling interface is different, the interface is the same as case101

.. code-block:: console
    
    PC802>> test case 103
    PC802>> Begin Test Case 103
    >>DL_MSG[1][191]: N=320 S=0x3CC7B55E D=0x7F03367B
    >>DL_MSG[1][192]: N=213 S=0x0DC68E27 D=0x4A83986C
     pc802_tx_mblk_burst : 467 : DL DESC[1][ 39]: virtAddr=0x227B41BB40 phyAddr=0x227B41BB40 Length=1288 Type=0 EOP=0
    DL_MSG[1][193]: N= 10 S=0x5B4900E4 D=0x65CF782F
    pc802_tx_mblk_burst : 467 : DL DESC[1][ 40]: virtAddr=0x227B75C1C0 phyAddr=0x227B75C1C0 Length=860 Type=0 EOP=1
    pc802_tx_mblk_burst : 467 : DL DESC[2][ 24]: virtAddr=0x22738CC4C0 phyAddr=0x22738CC4C0 Length=48 Type=1 EOP=1
    pc802_rx_mblk_burst : 409 : UL DESC[2][ 24]: virtAddr=0x226F984640 phyAddr=0x226F984640 Length=48 Type=1 EOP=1
    pc802_rx_mblk_burst : 409 : UL DESC[1][ 22]: virtAddr=0x2277914540 phyAddr=0x2277914540 Length=2148 Type=0 EOP=1
    UL_MSG[191]: N=322 S=0x3CC7B55E D=0x7F03367B
    UL_MSG[192]: N=215 S=0x0DC68E27 D=0x4A83986C
    UL_MSG[193]: N=12 S=0x5B4900E4 D=0x65CF782F
    Case 103 --- PASSED

**case 104**

The same function as case4, the calling interface is different, the interface is the same as case101

.. code-block:: console
    
    PC802>> test case 104
    PC802>> Begin Test Case 104
    ...
    UL_MSG[208]: N=70 S=0x591D8A40 D=0x70AA06D3
    UL_MSG[209]: N=82 S=0x68E7C3C3 D=0x4587B13B
    UL_MSG[210]: N=462 S=0x13FD8746 D=0x280346CB
    Case 104 --- PASSED

**case 105**

The same function as case5, the calling interface is different, the interface is the same as case101

.. code-block:: console
    
    PC802>> test case 105
    PC802>> Begin Test Case 105
    ...
    UL_MSG[363]: N=350 S=0x077C8097 D=0x7C5399C8
    UL_MSG[364]: N=457 S=0x75FE5B7F D=0x22E8CA9E
    UL_MSG[365]: N=512 S=0x58C447E2 D=0x2CA616F4
    UL_MSG[366]: N=95 S=0x02980471 D=0x6A94FDBE
    Case 105 --- PASSED

**case 201**

Test whether the network function is normal

.. code-block:: console
    
    PC802>> test case 201
    PC802>> Begin Test Case 201
    ...
    Case 201 --- PASSED

**case 301**

Testing OAM channel connectivity and messaging

.. code-block:: console
    
    PC802>> test case 301
    PC802>> Begin Test Case 301
    DL_MSG[1][367]: N=154 S=0x6E271020 D=0x69BAE888
    pc802_tx_mblk_burst : 467 : DL DESC[6][  0]: virtAddr=0x226B37BA40 phyAddr=0x226B37BA40 Length=624 Type=2 EOP=1
    pc802_rx_mblk_burst : 409 : UL DESC[6][  0]: virtAddr=0x2267373A40 phyAddr=0x2267373A40 Length=624 Type=0 EOP=1
    Case 301 --- PASSED

**Quit**

Secure exit procedure

.. code-block:: console
    
    PC802>> quit
