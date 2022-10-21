.. _introduction:

Introduction
============

Feature Overview
----------------

The PC802 driver has the following feature list,

* Support 5G EMBB data exchange between PHY and MAC.
* Support 4G LTE data exchange between PHY and MAC.
* Support 5G URLLC data exchange between PHY and MAC.
* Support NIC(Network interface card) function.
* Support OAM(operation and maintence) channel.
  
To support the above features, different queue is designed for each feature. In this way, applicaton can use different tasks to operate queue, providing convenience and possibility for parallel processing:

*  There is one pair UL/DL direction circular ring per queue.
*  Different queue has different maximum buffer size :numref:`maxium_buffer_size_definition` for single time data transaction. 

.. _maxium_buffer_size_definition:

.. table:: Maxium buffer size definition

    +--------------+-------------------+----------------+----------------------------------------------+
    | **SOC Type** | **Queue Name**    | **Block Size** |            **Description**                   |
    |              |                   |                |                                              |
    +==============+===================+================+==============================================+
    | PC802        |  Ethernet         | 2k             | None-ecpri Ethernet package                  |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  5G EMBB Data     | 256k           | EMBB FAPI PDSCH/PUSCH data                   |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  5G EMBB Control  | 256k           | EMBB FAPI Control Message                    |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  5G URLLC         | 16k            | URLLC FAPI Control/Data Message              |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  4G LTE Data      | 64k            | LTE FAPI PDSCH/PUSCH data                    |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  4G LTE Control   | 64k            | LTE FAPI Control Message                     |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  OAM              | 16K            | Operation and Manintence Message             |
    +--------------+-------------------+----------------+----------------------------------------------+
    | PC802R       |  Ethernet         | 2k             | None-ecpri Ethernet package                  |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  OAM              | 16K            | Operation and Manintence Message             |
    +--------------+-------------------+----------------+----------------------------------------------+
