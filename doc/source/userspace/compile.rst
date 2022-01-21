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

Build PC802 pcie driver on NPU side
-----------------------------------

Download `DPDK 21.08<http://fast.dpdk.org/rel/dpdk-21.08.tar.xz>`_.
.. code-block:: console
   wget http://fast.dpdk.org/rel/dpdk-21.08.tar.xz

Apply PC802_UDriver patch.
.. code-block:: console
   cd dpdk-21.08
   patch  -p1 < ../Picocom-PC802-PCIe-UDriver-based-on-DPDK-21.08.patch

Please see `DPDK Documentation <https://www.dpdk.org/>`_ for compiling DPDK.

Check if PC802 is active
------------------------

.. code-block:: console
    
    ./usertools/dpdk-devbind.py -s

.. code-block:: console
    
    Network devices using kernel driver
    ===================================
    ...
    No 'Crypto' devices detected
    ============================
    No 'Eventdev' devices detected
    ==============================
    No 'Mempool' devices detected
    ==============================
    No 'Compress' devices detected
    ==============================


Without ``af: 00.0``, you need to restart the server, and vice versa.
 
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


