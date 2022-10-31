.. _build_image_scb:

Build and run kernel driver
----------------------------

1. Run pcitest to test PCI-E basic function::

.. code-block:: sh

    $ make KERNEL_DIR=<your kernel source folder> all
    $ sudo insmod pcieptest.ko
    $ export PATH=$PATH:.
    $ ./pcitest.sh

2. Run PC802 traffic test::

.. code-block:: sh

    $ sudo mkdir /lib/firmware/pico
    $ cp <path of pc802.img> to /lib/firmware/pico/pc802.img
    $ make KERNEL_DIR=<your kernel source folder> all
    $ sudo insmod pcsc.ko
    $ sudo ./pcsc_test


3. Build local loopback mode driver (PCI-E independent)::

.. code-block:: sh

    $ sudo mkdir /lib/firmware/pico
    $ cp <path of pc802.img> to /lib/firmware/pico/pc802.img
    $ make KERNEL_DIR=<your kernel source folder> CONFIG_PCSC_LOOPBACK=y all
    $ sudo insmod pcsc_lb.ko
    $ sudo ./pcsc_test

