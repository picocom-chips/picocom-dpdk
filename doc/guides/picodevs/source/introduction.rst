.. _introduction:

Introduction
============

Feature overview
----------------

The PC802 driver has the following features:

* 2 * C/U split traffic channels
* 1 * legacy(none C/U split) traffic channel
* Ethernet channel
* OAM channel
* PC802 debugging function


To support the above features, a different queue is designed for each feature. In this way, the application can use different tasks to operate queues, which makes parallel processing possible and convenient:

*  There is one pair of UL/DL direction circular ring per queue.
*  Different queues have different maximum buffer sizes. :numref:`maxium_buffer_size_definition` lists the maximum buffer size for single-time data transaction.

.. _maxium_buffer_size_definition:

.. table:: Maximum buffer size definition

    +--------------+-------------------+----------------+----------------------------------------------+
    | **SOC Type** | **Queue Name**    | **Block Size** |            **Description**                   |
    |              |                   |                |                                              |
    +==============+===================+================+==============================================+
    | PC802        |  Ethernet         | 2k             | None-ecpri Ethernet package                  |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  TRAFFIC DATA 1   | 256k           | CELL 0 FAPI PDSCH/PUSCH data                 |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  TRAFFIC CTRL 1   | 256k           | CELL 0 FAPI Control Message                  |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  LEGACY           | 16k            | Legacy(none C/U split) cell Message          |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  TRAFFIC DATA 2   | 256k           | CELL 1 FAPI PDSCH/PUSCH data                 |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  TRAFFIC CTRL 2   | 256k           | CELL 1 FAPI Control Message                  |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  OAM              | 8K             | Operation and maintenance Message            |
    +--------------+-------------------+----------------+----------------------------------------------+
    | PC802R       |  Ethernet         | 2k             | None-ecpri Ethernet package                  |
    |              +-------------------+----------------+----------------------------------------------+
    |              |  OAM              | 8K             | Operation and maintenance Message            |
    +--------------+-------------------+----------------+----------------------------------------------+
