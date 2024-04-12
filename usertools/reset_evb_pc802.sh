#!/bin/sh

usage () {
cat <<EOF
Usage: reset_evb_pc802.sh pid pci_addr [gpio_port_number]
    if gpio_port_number is omitted, it is set to 27 by default.
EOF
   exit
}

if [ $# -eq "2" ]; then
    gpio_port_number=27
elif [ $# -eq "3" ]; then
    gpio_port_number=$3
else
    usage
fi
echo pid=$1
echo pci_addr=$2
echo gpio_port_number=$gpio_port_number

#exit 0

kill -9 $1
dpdk-devbind.py -u $2

./reset_pc802_from_gpio.sh $2 $gpio_port_number

echo 1 > /sys/bus/pci/devices/"0000:$2"/remove

