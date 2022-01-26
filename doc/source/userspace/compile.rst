.. _compile_pcie_drver_userspace:

Compiling the PC802 PCIe driver from Source
===========================================

You need insmod igb_uio.ko to bind PC802 to linux kernel:

Download kmod code from `DPDK Kmode repo <https://dpdk.org/git/dpdk-kmods>`_. 

build igb_uio
    .. code-block:: console

       cd path/to/git/repo/dpdk-kmods/linux/igb_uio
       make
       insmod igb_uio.ko

.. _build_PC802_PCIe_driver:

Build PC802 PCIe driver on NPU side from source code
----------------------------------------------------

Download PC802_UDriver and enter directory::

   cd path/npu_driver/pcie/user_space/DPDK

Please see `DPDK Documentation <https://www.dpdk.org/>`_ for compiling DPDK.

.. _check_PC802_active:

Check if PC802 is active
------------------------

.. code-block:: console
    
    ./usertools/dpdk-devbind.py -s

.. code-block:: console

    Network devices using kernel driver
    ===================================
    ... 
    Other Network devices
    =====================
    0000:af:00.0 'DWC_usb31 abcf' unused=windrvr1440
    No 'Crypto' devices detected
    ============================
    No 'Eventdev' devices detected
    ============================
    No 'Mempool' devices detected
    ============================
    No 'Compress' devices detected
    ============================

Optional driver ``af: 00.0`` has appeared::

    usertools/dpdk-devbind.py -b igb_uio af:00.0

.. code-block:: console
    
    Network devices using DPDK-compatible driver
    ============================================
    0000:af:00.0 'DWC_usb31 abcf' drv=vfio-pci unused=windrvr1440
    Network devices using kernel driver
    ===================================
    ... 
    No 'Crypto' devices detected
    ============================
    No 'Eventdev' devices detected
    ==============================
    No 'Mempool' devices detected
    =============================
    No 'Compress' devices detected
    ==============================

As shown in the above figure, it means that the binding has been successful


