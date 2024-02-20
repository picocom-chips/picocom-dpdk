#!/bin/sh

usage () {
cat <<EOF
Usage: reset_pc802_from_gpio.sh  [gpio_port_number]
    if gpio_port_number is omitted, it is set to 27 by default.
EOF
   exit
}

if [ $# -eq "0" ]; then
    gpio_port_number=27
elif [ $# -eq "1" ]; then
    gpio_port_number=$1
else
    usage
fi

pci_addr=`lspci | grep -i 1ec4 | cut -f1 -d' '`
echo PC802 at $pci_addr

bar0=0x`lspci -v -s $pci_addr | grep Memory | head -n 1 | cut -f3 -d' '`
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

busybox devmem $WR_DATA 32 $gpio_port_number
busybox devmem $CMD 32 2

busybox devmem $RCCNT 32 $rccnt

