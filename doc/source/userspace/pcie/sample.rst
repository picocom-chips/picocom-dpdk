Running Driver Testcases
------------------------
The chapter describes how to compile and run applications integrating with this driver.

Run instructions::
    
    ./build/app/dpdk-testpc802

After successful operation, print as shown in the following figure appears::
    
    PC802>>


Please refer to :ref:`build_PC802_PCIe_driver` for build PC802 pcie driver on NPU side and running.

**test case 1**

Bi-directional testing for "5G EMBB Control" queue.

.. code-block:: console
    
    PC802>> test case 1
    PC802>> Begin Test Case 1
    02DL_MSG[1][  0]: N= 25 S=0x772E00AD D=0x40FEF01C
    >pc802_tx_mblk_burst : 467 : DL DESC[2][  0]: virtAddr=0x227338BA40 phyAddr=0x227338BA40 Length=108 Type=2 EOP=1
    > pc802_rx_mblk_burst : 409 : UL DESC[2][  0]: virtAddr=0x226F383A40 phyAddr=0x226F383A40 Length=108 Type=2 EOP=1
    CASE1: UL msg length = 108
    UL_MSG[1][  0]: N= 25 S=0x772E00AD D=0x40FEF01C
    UL_MSG[0]: N=27 S=0x772E00AD D=0x40FEF01C
    Case 1 --- PASSED

**test case 2**

Bi-directional testing to verfiy the sending and receiving of single messages via "5G EMBB Data" and "5G EMBB Control" queues

.. code-block:: console
    
    PC802>> test case 2
    PC802>> Begin Test Case 2
    DL_MSG[1][  1]: N=214 S=0x5A49BDAD D=0x5DB6E6FC
    pc802_tx_mblk_burst : 467 : DL DESC[1][  0]: virtAddr=0x227B39BA40 phyAddr=0x227B39BA40 Length=864 Type=0 EOP=1
    DL_MSG[1][  2]: N=103 S=0x09DD4930 D=0x4071A05B
    pc802_tx_mblk_burst : 467 : DL DESC[2][  1]: virtAddr=0x227338BA40 phyAddr=0x227338BA40 Length=420 Type=1 EOP=1
    pc802_rx_mblk_burst : 409 : UL DESC[1][  0]: virtAddr=0x2277393A40 phyAddr=0x2277393A40 Length=864 Type=0 EOP=1
    pc802_rx_mblk_burst : 409 : UL DESC[2][  1]: virtAddr=0x226F3C3AC0 phyAddr=0x226F3C3AC0 Length=420 Type=1 EOP=1
    UL_MSG[1]: N=216 S=0x5A49BDAD D=0x5DB6E6FC
    UL_MSG[2]: N=105 S=0x09DD4930 D=0x4071A05B
    Case 2 --- PASSED

**test case 3**

Bi-directional testing to verfiy the sending and receiving of  messages via "5G EMBB Data" and "5G EMBB Control" queues, 2 * "5G EMBB Data" messages and 1 * "5G EMBB Control" message

.. code-block:: console
    
    PC802>> test case 3
    PC802>> Begin Test Case 3
    DL_MSG[1][  3]: N=444 S=0x3467EF00 D=0x11A179D4
    pc802_tx_mblk_burst : 467 : DL DESC[1][  1]: virtAddr=0x227B39BA40 phyAddr=0x227B39BA40 Length=1784 Type=0 EOP=0
    DL_MSG[1][  4]: N=317 S=0x18153AB6 D=0x4337011C
    pc802_tx_mblk_burst : 467 : DL DESC[1][  2]: virtAddr=0x227B3DBAC0 phyAddr=0x227B3DBAC0 Length=1276 Type=0 EOP=1
    DL_MSG[1][  5]: N= 34 S=0x53C1FC3E D=0x00775D37
    pc802_tx_mblk_burst : 467 : DL DESC[2][  2]: virtAddr=0x227338BA40 phyAddr=0x227338BA40 Length=144 Type=1 EOP=1
    pc802_rx_mblk_burst : 409 : UL DESC[1][  1]: virtAddr=0x22773D3AC0 phyAddr=0x22773D3AC0 Length=3060 Type=0 EOP=1
    pc802_rx_mblk_burst : 409 : UL DESC[2][  2]: virtAddr=0x226F403B40 phyAddr=0x226F403B40 Length=144 Type=1 EOP=1
    UL_MSG[3]: N=446 S=0x3467EF00 D=0x11A179D4
    UL_MSG[4]: N=319 S=0x18153AB6 D=0x4337011C
    UL_MSG[5]: N=36 S=0x53C1FC3E D=0x00775D37
    Case 3 --- PASSED

**test case 4**

Bi-directional testing to verfiy the sending and receiving of  messages via "5G EMBB Data" and "5G EMBB Control" queues, 16 * "5G EMBB Data" messages and 16 * "5G EMBB Control" message

.. code-block:: console
    
    PC802>> test case 4
    PC802>> Begin Test Case 4
    ...
    UL_MSG[16]: N=41 S=0x0B9BFDA2 D=0x34B7EEEB
    UL_MSG[17]: N=432 S=0x4C7FAE85 D=0x718006A1
    UL_MSG[18]: N=463 S=0x588F8354 D=0x43C4BC3B
    UL_MSG[19]: N=161 S=0x4FBEAB02 D=0x50D7EAAF
    UL_MSG[20]: N=168 S=0x129A7BDA D=0x551919D0
    UL_MSG[21]: N=203 S=0x38BDD8CC D=0x33A4069E
    UL_MSG[22]: N=490 S=0x1176F893 D=0x1C0C3C9C
    Case 4 --- PASSED

**test case 5**

Test testcase4 repeatly, random payload in messages

.. code-block:: console
    
    PC802>> test case 5
    PC802>> Begin Test Case 5
    ...
    UL_MSG[182]: N=498 S=0x678D0B94 D=0x4D8272BD
    UL_MSG[183]: N=453 S=0x7C36E12F D=0x4BA533B2
    UL_MSG[184]: N=348 S=0x55E720A6 D=0x43724668
    UL_MSG[185]: N=147 S=0x69172615 D=0x6C6469BC
    UL_MSG[186]: N=172 S=0x5376783F D=0x1EC74071
    UL_MSG[187]: N=42 S=0x08D6809E D=0x2222C3A0
    Case 5 --- PASSED