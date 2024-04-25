# Copyright(c) 2020 PICOCOM Corporation

# override default name to drop the hyphen
name = 'review-pc802'
cflags += '-Wno-deprecated-declarations'
cflags += '-DRTE_ENABLE_ASSERT'
sources = files(
        'check-pc802.c'
)

deps += ['ethdev', 'cmdline', 'bus_pci']

if dpdk_conf.has('RTE_NET_PC802')
    deps += 'net_pc802'
endif
