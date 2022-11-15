.. _user_space_info:

User space Driver
=================

PC802_UDriver includes two parts, Abstract Transport Layer Lib(:ref:`atll_api`). and :ref:`PCIe_driver_info`.

* PC802 PCIe driver: A high-performance packet processing driver, leverages `the Data Plane Development Kit (DPDK) <https://www.dpdk.org/>`_ to take advantage of fast I/O.
* ATLL: Designed as fast communication interface between PHY and MAC layers. Abstract from platform-specific transport mechanisms (SHM, PCIe) and to offer a homogeneous interface to the application layer.

L2/L3 can run as a DPDK application to do the FAPI/OAM data transaction with PC802 in a Linux environment via integrating with PC802_UDriver. Meanwhile, through the KNI (`Kernel NIC Interface <https://www.dpdk.org/>`_)  kernel network interface card interface, PC802 PCIe driver simulates a virtual network port to provide communication between dpdk applications and linux kernels. The KNI interface allows packets to be received from user mode and forwarded to the linux protocol stack.
The chapter describes how to compile and run a application based on PC802_UDriver.

.. toctree::
    :maxdepth: 3
    :numbered:

    system
    compile
    program_guide
    howto
