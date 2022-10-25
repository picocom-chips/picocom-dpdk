.. _prepare_sd_card:

SD card image
=============

Formatting SD card
------------------

To partition and format the target SD/eMMC/USB disk and install your custom distro image::

    $ flex-installer -i pf -d /dev/sdx                   (default 4 partitions as 4P=128M:2G:5G:-1)
    or
    $ flex-installer -i pf -d /dev/sdx -p 4P=128M:3G:6G:-1   (specify your custom partitions as 4P=128M:3G:6G:-1)

Flashing firmware to SD card
-----------------------------

Assume your SD card has a device node at /dev/sdb, then you can flash firmware image to SD card by using the following command line::
    
    The device nodes are not exactly same on different machines, it could be sdc, sdd, sde ..., or /dev/mmcblk0::

        - Install composite firmware image:
        $ sudo dd if=firmware_ls1046apscb_sdboot.img of=/dev/sdX bs=512 seek=8 conv=sync


Extracting the boot and rootfs images to SD card
------------------------------------------------

Assume your SD card partitions are already mounted to the system. For example, on Ubuntu 18.04, the boot partition /dev/sdb2 and rootfs partition /dev/sdb4 will be mounted into the filesystem folder at /mnt/sdb2, /mnt/sdb4. Then you can extract boot and rootfs images to your SD card by using the following command line::

    - Install boot partition image:
    $ sudo tar -xvf boot_LS_arm64_lts_5.10.tgz -C /media/user/boot/

    - Install root partition image:
    $ sudo tar -xvf rootfs_lsdk2108_ubuntu_main_arm64.tgz -C /media/user/data4/


Downloading and deploying LSDK composite firmware in Windows environment
------------------------------------------------------------------------

* Download the `DD for Windows tool <http://download.si-linux.co.jp/dd_for_windows/DDWin_Ver0998.zip>`_ and install it.
* Run the DD tool for Windows as an administrator.
* Click Choose disk, Choose file, and Restore to program the newly generated composite firmware (with _4k suffix in file name) into the target SD card.
* Unplug your SD card from the Windows host machine and plug it on the target board.
* Set the DIP switch for SD boot or run sd_bootcmd at U-Boot prompt.
  
Programming QSPI flash
----------------------

Copy the qspi flash boot image to the mmc card boot partition, and then run the following command in the uboot shell::

    load mmc 0:2 $load_addr firmware_ls1046apscb_qspiboot.img
    sf probe 0:0
    sf erase 0 +$filesize && sf write $load_addr 0 $filesize
