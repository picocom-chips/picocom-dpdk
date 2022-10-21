System Requirements
===================

This section describes the packages required to compile the PC802_UDriver.

BIOS setting prerequisite on x86
--------------------------------

For the majority of platforms, no special BIOS settings are needed to use PC802 PCIe driver.
However, for power management functionality and high performance of small packets, BIOS setting changes may be needed.

.. note::
    If UEFI secure boot is enabled, the Linux kernel may disallow the use of UIO on the system.
    Therefore, devices for use by DPDK should be bound to the ``igb_uio`` or ``uio_pci_generic``.

Linux OS
--------
**Required:**

*   Kernel version >= 4.4

    The kernel version required is based on the oldest long-term stable kernel available
    at kernel.org.
    Compatibility for recent distribution kernels will be kept, notably RHEL/CentOS 7.

    The kernel version in use can be checked by using the command::

       uname -r

*   glibc >= 2.7 (for features related to cpuset)

    The version can be checked using the ``ldd --version`` command.

DPDK
----
**Required:**

X86 platform:

    DPDK Version `DPDK 21.08.0 <http://fast.dpdk.org/rel/dpdk-21.08.tar.xz>`_

LXP LS1046A platform:

    DPDK Version in `LSDK 21.08 <https://www.nxp.com/design/software/embedded-software/linux-software-and-development-tools/layerscape-software-development-kit-v21-08:LAYERSCAPE-SDK>`_
