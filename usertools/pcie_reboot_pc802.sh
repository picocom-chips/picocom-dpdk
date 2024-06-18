#!/bin/bash
#
# PICOCOM PROPRIETARY INFORMATION
#
# This software is supplied under the terms of a license agreement or
# nondisclosure agreement with PICOCOM and may not be copied
# or disclosed except in accordance with the terms of that agreement.
#
# Copyright PICOCOM.
#

ext_reset() {
	GPIO=gpio$1
	if [ ! -f /sys/class/gpio/$GPIO/value ]
	then
		echo "Export GPIO 3-6 ($GPIO) to userspace."
		echo $1 > /sys/class/gpio/export
	fi

	echo "Set GPIO 3-6 ($GPIO) direction to out."
	echo out > /sys/class/gpio/$GPIO/direction

	echo "Set GPIO 3-6 ($GPIO) value to 0."
	echo 0 > /sys/class/gpio/$GPIO/value

	echo "Set GPIO 3-6 ($GPIO) value to 1."
	echo 1 > /sys/class/gpio/$GPIO/value
}

int_reset() {
	dev=$1
	port_id=$2

	bar0=0x`lspci -v -s $dev | grep Memory | head -n 1 | cut -f3 -d' '`
	echo bar0=$bar0

	addr=`echo $(($bar0+0x2e0))`
	RCCNT=`printf "0x%08X\n" $addr`
	echo RCCNT=$RCCNT

	addr=`echo $(($bar0+0x2e4))`
	CMD=`printf "0x%08X\n" $addr`
	echo CMD=$CMD

	addr=`echo $(($bar0+0x2e8))`
	OFFSET=`printf "0x%08X\n" $addr`
	echo OFFSET=$OFFSET

	addr=`echo $(($bar0+0x2ec))`
	WR_DATA=`printf "0x%08X\n" $addr`
	echo WR_DATA=$WR_DATA

	addr=`echo $(($bar0+0x300))`
	EPCNT=`printf "0x%08X\n" $addr`
	echo EPCNT=$EPCNT

	addr=`echo $(($bar0+0x304))`
	ERROR=`printf "0x%08X\n" $addr`
	echo ERROR=$ERROR

	addr=`echo $(($bar0+0x308))`
	RD_DATA=`printf "0x%08X\n" $addr`
	echo RD_DATA=$RD_DATA

	epcnt=`busybox devmem $EPCNT`
	echo epcnt=$epcnt

	rccnt=`echo $(($epcnt+1))`
	echo rccnt=$rccnt

	busybox devmem $WR_DATA 32 $port_id
	busybox devmem $CMD 32 2

	busybox devmem $RCCNT 32 $rccnt
}

set_speed() {
	dev=$1
	speed=$2
	
	if [ -z "$dev" ]; then
		echo "Error: no device specified"
		exit 1
	fi
	
	if [ ! -e "/sys/bus/pci/devices/$dev" ]; then
		dev="0000:$dev"
	fi
	
	if [ ! -e "/sys/bus/pci/devices/$dev" ]; then
		echo "Error: device $dev not found"
		exit 1
	fi
	
	pciec=$(setpci -s $dev CAP_EXP+02.W)
	pt=$((("0x$pciec" & 0xF0) >> 4))
	
	port=$(basename $(dirname $(readlink "/sys/bus/pci/devices/$dev")))
	
	if (($pt == 0)) || (($pt == 1)) || (($pt == 5)); then
		dev=$port
	fi
	
	lc=$(setpci -s $dev CAP_EXP+0c.L)
	ls=$(setpci -s $dev CAP_EXP+12.W)
	
	max_speed=$(("0x$lc" & 0xF))
	
	echo "Link capabilities:" $lc
	echo "Max link speed:" $max_speed
	echo "Link status:" $ls
	echo "Current link speed:" $(("0x$ls" & 0xF))
	
	if [ -z "$speed" ]; then
		speed=$max_speed
	fi
	
	if (($speed > $max_speed)); then
		speed=$max_speed
	fi
	
	echo "Configuring $dev..."
	
	lc2=$(setpci -s $dev CAP_EXP+30.L)
	
	echo "Original link control 2:" $lc2
	echo "Original link target speed:" $(("0x$lc2" & 0xF))
	
	lc2n=$(printf "%08x" $((("0x$lc2" & 0xFFFFFFF0) | $speed)))
	
	echo "New target link speed:" $speed
	echo "New link control 2:" $lc2n
	
	setpci -s $dev CAP_EXP+30.L=$lc2n
	
	echo "Triggering link retraining..."
	
	lc=$(setpci -s $dev CAP_EXP+10.L)
	
	echo "Original link control:" $lc
	
	lcn=$(printf "%08x" $(("0x$lc" | 0x20)))
	
	echo "New link control:" $lcn
	
	setpci -s $dev CAP_EXP+10.L=$lcn
	
	sleep 0.1
	
	ls=$(setpci -s $dev CAP_EXP+12.W)
	
	echo "Link status:" $ls
	echo "Current link speed:" $(("0x$ls" & 0xF))
}

usage() {
	echo "Usage: Script for reset pc802 on NPU"
	echo -e "\t$0 [pc802_index] [-i|-e] [-p port] [-h]"
	echo -e "\tpc802_index, Input pc802 index to be reset: 1-4, default 1"
	echo -e "\t-i, Reset pc802 by pc802 internal gpio, x86 platform default mode"
	echo -e "\t-e, Reset pc802 by NPU gpio, arm platform default mode"
	echo -e "\t-p, Define the gpio port used to reset PC802"
	echo -e "\t-h, Display this help"
}

index=1
mode=""
gpio=""

if [[ `arch` =~ "x86_64" ]];then
	mode="INT"
else
	mode="EXT"
fi

while getopts "hiep:" ARG ; do
	case $ARG in
		i ) mode="INT" ;;
		e ) mode="EXT" ;;
		p ) gpio=$OPTARG ;;
		h ) usage ; exit 0 ;;
	esac
done
shift $((OPTIND -1))

if [ -z $gpio ];then
	if [[ $mode == "INT" ]];then
		gpio=27
	else
		gpio=422
	fi
fi

if [ $1 ];then
    index=$1
    PCI_ADDR=`lspci | awk '/1ec4/{i++;if(i=="'$index'"){print $1;exit;}}'`
else
	index=1
    PCI_ADDR=`lspci | awk '/1ec4/{print $1;exit;}'`
fi

echo "mode:$mode gpio:$gpio index:$index"

if [ -z $PCI_ADDR ];then
	echo "Error: cann't find PC802 $index"
	exit
else
    echo "PC802 is located at ${PCI_ADDR}"
fi

echo "Remove and reset PC802 ${PCI_ADDR} from pice"
dpdk-devbind.py -u ${PCI_ADDR}
if [[ $mode == "INT" ]];then
    int_reset $PCI_ADDR $gpio
	echo "1" > /sys/bus/pci/devices/0000\:${PCI_ADDR/:/\\:}/remove
    sleep 4
elif [[ $mode == "EXT" ]];then
	echo "1" > /sys/bus/pci/devices/0000\:${PCI_ADDR/:/\\:}/remove
    ext_reset $gpio
fi
sleep 1

echo ""
echo "Start pcie rescan ......"
echo "1" > /sys/bus/pci/rescan
lspci

NEW_ADDR=`lspci | awk '/1ec4/{i++;if(i=="'$index'"){print $1;exit;}}'`
if [[ -z "$NEW_ADDR" ]]; then
	echo "Error: cann't find PC802, need to reboot npu."
	exit 1
elif [[ "$NEW_ADDR" != "$PCI_ADDR" ]]; then
	echo "Error: pcie dev:$NEW_ADDR not match source dev:$PCI_ADDR."
    exit 1
fi
echo "Rescan PC802 at ${PCI_ADDR}"
echo ""
set_speed ${PCI_ADDR} 3
lspci -v -s ${PCI_ADDR}

modprobe uio_pci_generic 
dpdk-devbind.py -b uio_pci_generic ${PCI_ADDR}
dpdk-devbind.py -s
