:orphan:

.. _bsp_2.0:


PC802 driver 2.0
##################

New features
************
* SI-1013: Added support for capturing traffic from PC802 PCIe
* SI-1011: Optimized the cpu and memory consumption of the PC802 log function
* SI-939: Added support for multi-process mode with PC802
* SI-909: Added OAM lib to support DU OM features
* SI-855: Added support for PCIe register to transfer slot indication
* SI-998: Added support for multi-threads mode with PC802
* SI-801: Added support for ORANIC board
* SI-808: Added support for rerun app without rebooting NPU
* SI-806: Added support for enable KNI interface for PC802


Bug fixes
*********


Known issues
************


API Changes
************
* The ``dev_inde`` and ``cell_index`` input parameters are added to the ATLL interface below to support multiple PC802s, which can be turned on by the MULTI_PC802 macro, and turned off by default:

  * ``pcxxCtrlOpen``
  * ``pcxxCtrlClose``
  * ``pcxxDataOpen``
  * ``pcxxDataClose``
  * ``pcxxSendStart``
  * ``pcxxSendEnd``
  * ``pcxxCtrlAlloc``
  * ``pcxxCtrlSend``
  * ``pcxxCtrlRecv``
  * ``pcxxDataAlloc``
  * ``pcxxDataSend``

PC802 driver 2.0.1
##################

New features
************
* SI-1017: Added support for Different firmware&vector file for different chip in ORANIC
* SI-1337: Optimized PCIe msg jitter

Bug fixes
*********
* SI-1369: Fix PC802 driver(v2.0) PCIe channel failure on FSBL V0


PC802 driver 2.1
##################

New features
************
* SI-1331 Added PC802 PCIe message timing statistics and checks
* SI-1326 Added PC802 dpdk-telemetry debug command
* SI-1309 Reduced debugging memory
* SI-1300 Support max 4096 descriptors per PCIe queue


Bug fixes
*********

PC802 driver 2.2
##################

New features
************
* SI-1335 Support VEC access from CEVA DSPs

Bug fixes
*********

PC802 driver 2.3
##################

New features
************
* NDF-90: mailbox v3 on NPU DPDK driver
=======================================

mailbox v3 supports NPU output printf from PC802 booted by FSBL v0
and also reduces much CPU load of mailbox thread on NPU side.

* SI-1584: support SSBL printf
* SI-1357: support PC802 core dump

Bug fixes
*********
* NDF-99: fix build warnings of PC802 driver and test cases

PC802 driver 2.4
##################

New features
************
* SI-1599: support PC802 dump data on the fly
* SI-1602: PC802 can stop PCIe mini trace
* SI-1630: stop trace for inactive cores
* NDF-54:  Oam message header add seq_id field
* NDF-121: ATLL interface adds support for legacy cell queues

Enhancement
***********
* NDF-112: NPU doesn't get unnecessary mailbox memory

Bug fixes
*********
* NDF-111: fix duplicated and invalid mailbox message
* NDF-125: Fix kni not starting when there are multiple dpdk devices

PC802 driver 2.5
##################

New features
************
* SI-1703: support PC806
* NDF-100: support secondary process start PC802

Bug fixes
*********
* NDF-130: fix freeing ssbl_img twice
* NDF-131: fix mailbox log not support different FW