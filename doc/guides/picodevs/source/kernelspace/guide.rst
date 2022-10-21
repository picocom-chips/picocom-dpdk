.. _build_image_scb:

Quick Start
===========
Ubuntu 20.04 is the official verified build platform for the NXP LSDK2108.

Build SCB image
---------------
 
Download LSDK from `NXP Semiconductor website <https://www.nxp.com/design/software/embedded-software/linux-software-and-development-tools/layerscape-software-development-kit-v21-08:LAYERSCAPE-SDK>`_

Extract and cd to the root folder of the SDK::

   tar zxvf flexbuild_lsdk2108.tgz
   cd flexbuild_lsdk2108

Setup the environment variable and import the build script::

   source setup.env

Get the component source code from remote git repository::

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
   
The development environment is not Ubuntu-20.04 You need to start docker ubuntu-20.04::

   flex-builder docker

Build all the images::

    flex-builder -i mkrfs
    flex-builder -i packrfs
    flex-builder -i mkboot -m ls1046apscb
    flex-builder -i mkfw -m ls1046apscb -b sd
    flex-builder -i mkfw -m ls1046apscb -b qspi

Build PC802_KDriver:
   
    1. If run pcitest to test PCIe basic function::
          
        $ sudo mkdir /lib/firmware/pico
        $ cp <path of pc802.img> to /lib/firmware/pico/pc802.img
        $ make KERNEL_DIR=<your kernel source folder> all
        $ sudo insmod pcieptest.ko
        $ export PATH=$PATH:.
        $ ./pcitest.sh
    
    2. If Run PC802 traffic test::

        $ sudo mkdir /lib/firmware/pico
        $ cp <path of pc802.img> to /lib/firmware/pico/pc802.img
        $ make KERNEL_DIR=<your kernel source folder> all
        $ sudo insmod pcsc.ko
        $ sudo ./pcsc_test
