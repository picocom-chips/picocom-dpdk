export ORIGINAL_DPDK=./dpdk-21.08 
diff  -ruN -x "*.data" $ORIGINAL_DPDK  npu_driver/pcie/user_space/DPDK/ > Picocom-PC802-PCIe-UDriver-based-on-DPDK-21.08.patch