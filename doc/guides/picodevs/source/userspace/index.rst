.. _user_space_info:

User space
==========

PC802_UDriver is high-performance packet processing driver, leverages `the Data Plane Development Kit (DPDK) <https://www.dpdk.org/>`_ to take advantage of fast I/O. 
DPDK provides fast packet processing libraries and user space drivers. It receives and send packets with a minimum number of CPU cycles by bypassing the kernel and using a user poll mode driver. 
L2/L3 can run as a DPDK application to do the FAPI/OAM data transaction with PC802 in a Linux environment via integrating with ATLL and PC802_UDriver.
Meanwhile, through the KNI (`Kernel NIC Interface <https://www.dpdk.org/>`_)  kernel network interface card interface, PC802_UDriver simulated a virtual network port to provide communication between dpdk applications and linux kernels. The KNI interface allows packets to be received from user mode and forwarded to the linux protocol stack.
The document describes how to compile and run a application basing on PC802_UDriver.

.. toctree::
    :maxdepth: 3
    :numbered:

    system
    compile
    pcie/index
    atll/index
