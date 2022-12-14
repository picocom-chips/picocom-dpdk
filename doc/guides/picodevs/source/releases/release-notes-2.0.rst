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