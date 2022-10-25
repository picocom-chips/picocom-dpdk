.. _config_board:

Configuring the Board
=====================

Configuring MAC address for Ethernet in uboot
-------------------------------------------

Press any key in u-boot stage to enter the u-boot shell, and then run the following command line::

    setenv ethaddr 00:04:9F:03:05:E4
    saveenv

Configuring static IP address for the board
---------------------------------------------

In the ubuntu shell after the board is booted to Ubuntu, run the following command::

    ifconfig fm1-mac5 192.168.1.90/24
    
In the u-boot shell, run the following commands::

    setenv ipaddr 192.168.1.90
    setenv netmask 255.255.255.0
    saveenv


Configuring the board to get IP address from DHCP server
----------------------------------------------------------

In the ubuntu shell after the board is booted to Ubuntu, run the following command::
  
    dhclient -v fm1-mac5

In the u-boot shell, run the following command::

    dhcp

