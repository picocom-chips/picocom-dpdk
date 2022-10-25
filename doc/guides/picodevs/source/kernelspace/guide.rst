.. _build_image_scb:

Quick Start
===========
The PC802 Small Cell Development Board (PC802SCB) is a flexible 5G NR/LTE development platform for evaluating the PC802 for different small cell use cases. The PC802SCB includes an on-board NXP 
Network Processing Unit (NPU). For more hardware information on PC802SCB, contact `Picocom <info@picocom.com>`_ to get "PC802 Small Cell Development Board Product Brief".

Building PC802SCB image
------------------------
 
Download LSDK from `NXP Semiconductor website <https://www.nxp.com/design/software/embedded-software/linux-software-and-development-tools/layerscape-software-development-kit-v21-08:LAYERSCAPE-SDK>`_

Extract and cd it to the root folder of the SDK::

   tar zxvf flexbuild_lsdk2108.tgz
   cd flexbuild_lsdk2108

Setup the environment variables and import the build script::

   source setup.env

Get the component source code from the remote git repository::

   flex-builder -i repo-update
   flex-builder -i repo-fetch

Patch the component source to support Pico SCB::

    # patch the linux kernel
    cd components/linux/linux
    git checkout -b LSDK-21.08-LS1046A-PSCB-PR1 
    patch -p1 < {path_to_patch}/linux.patch
    cd -

    # patch the atf
    cd components/firmware/atf
    patch -p1 < {path_to_patch}/atf.patch
    cd -

    # patch the rcw
    cd components/firmware/rcw
    patch -p1 < {path_to_patch}/rcw.patch
    cd -

    # patch the uboot
    cd components/firmware/uboot
    patch -p1 < {path_to_patch}/uboot.patch
    cd -

    # patch the lsdk
    patch -p1 < {path_to_patch}/flexbuild_lsdk2108.patch
   
If the development environment is not Ubuntu-20.04, you need to start docker ubuntu-20.04::

   flex-builder docker

Build all the images::

    flex-builder -i mkrfs
    flex-builder -i packrfs
    flex-builder -i mkboot -m ls1046apscb
    flex-builder -i mkfw -m ls1046apscb -b sd
    flex-builder -i mkfw -m ls1046apscb -b qspi

Build and run PC802_KDriver:
   
    1. Run pcitest to test the PCIe basic function::
          
        $ sudo mkdir /lib/firmware/pico
        $ cp <path of pc802.img> to /lib/firmware/pico/pc802.img
        $ make KERNEL_DIR=<your kernel source folder> all
        $ sudo insmod pcieptest.ko
        $ export PATH=$PATH:.
        $ ./pcitest.sh
    
    2. Run the PC802 traffic test::

        $ sudo mkdir /lib/firmware/pico
        $ cp <path of pc802.img> to /lib/firmware/pico/pc802.img
        $ make KERNEL_DIR=<your kernel source folder> all
        $ sudo insmod pcsc.ko
        $ sudo ./pcsc_test
