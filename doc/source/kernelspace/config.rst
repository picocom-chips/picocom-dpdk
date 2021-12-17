.. _config_board:

Configure Board
===============

Configure static IP for the board
---------------------------------

In ubuntu shell after the board booted to Ubuntu::

    ifconfig fm1-mac5 192.168.1.90/24
    
In u-boot shell::

    setenv ipaddr 192.168.1.90
    setenv netmask 255.255.255.0
    saveenv


Configure the board to get IP from DHCP server
----------------------------------------------

In ubuntu shell after the board booted to Ubuntu::
  
    dhclient -v fm1-mac5

In u-boot shell::
    dhcp

Configure MAC address for ethernet in uboot
-------------------------------------------

Press any key in u-boot stage to enter u-boot shell, then run the following command line::

    setenv ethaddr 00:04:9F:03:05:E4
    saveenv

Flash firmware image to SD card
-------------------------------

Assume your SD card has device node at /dev/sdb, using the following command line. 
    
The device nodes are not exactly same on different machines, it could be sdc, sdd, sde ..., or /dev/mmcblk0::

    sudo dd if=firmware_ls1046apscb_sdboot.img of=/dev/sdb bs=1k seek=4 conv=sync
