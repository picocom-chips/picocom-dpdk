#!/bin/sh

pid_app=`pidof dpdk-testpc802`
pci_addr=`lspci | grep -i 1ec4 | cut -f1 -d' '`

./reset_evb_pc802.sh $pid_app $pci_addr
