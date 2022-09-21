# Copyright(c) 2020 PICOCOM Corporation

# override default name to drop the hyphen
name = 'test-pc802-oam'
cflags += '-Wno-deprecated-declarations'
cflags += '-DRTE_ENABLE_ASSERT'
sources = files(
        'cmdline.c',
        'test-pc802-oam.c',
)

deps += ['ethdev', 'cmdline', 'bus_pci']

if dpdk_conf.has('RTE_NET_PC802')
    deps += 'net_pc802'
endif
