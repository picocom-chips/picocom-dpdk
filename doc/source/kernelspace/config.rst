.. _config_board:

Configure Board
===============

Configure MAC address for ethernet in uboot
-------------------------------------------

Press any key in u-boot stage to enter u-boot shell, then run the following command line::

    setenv ethaddr 00:04:9F:03:05:E4
    saveenv

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

