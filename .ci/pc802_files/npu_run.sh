#!/usr/bin/env bash
#
# PICOCOM PROPRIETARY INFORMATION
#
# This software is supplied under the terms of a license agreement or
# nondisclosure agreement with PICOCOM and may not be copied
# or disclosed except in accordance with the terms of that agreement.
#
# Copyright PICOCOM.
#

#find PC802 device
BUS=`lspci | awk  '/802/{print $1;exit;}'`
[ -z "$BUS" ] && echo "Not found pc802 device" && exit 0
lspci -v -s $BUS 2> /dev/null

#load driver and bind
modprobe uio_pci_generic
dpdk-devbind.py -b uio_pci_generic $BUS
dpdk-devbind.py -s

#build start env
export PC802_VECTOR_DUMP_DIR="/opt/picocom/phyCfgs"
export PC802_TEST_VECTOR_DIR="/opt/picocom/phyCfgs"
CPUS=`cat /sys/devices/system/cpu/isolated`
[ -z "$CPUS" ] && echo "Not found isolated core" && exit 0

#run applicable
[[ -n "$@" ]] && $@ -l$CPUS --syslog user --log-level lib.eal:debug
