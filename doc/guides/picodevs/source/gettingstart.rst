.. _getting_start_npu_driver:

User Guide for PCIe Driver in NPU 
=================================

This document provides information for developers on how to develop, and port applications on NPU to integrate with Picocom`s PC802 Chip (SoC).
Picocom provides two modes of NPU driver: 

* user space driver(PC802_UDriver)
* kernel space driver(PC802_KDriver)
  
The software architecture based on PC802_UDriver is shown in the :numref:`figure_user_space_arch`, and the one based on PC802_KDriver is shown in :numref:`figure_kernel_space_arch`.

.. _figure_user_space_arch:
   
.. figure:: img/userspace_arch.*

   More details shown in :ref:`user_space_info`
.. _figure_kernel_space_arch:
   
.. figure:: img/kernelspace_arch.*

   More details shown in :ref:`kernel_space_info`
