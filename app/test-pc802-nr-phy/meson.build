# Copyright(c) 2020 PICOCOM Corporation

# override default name to drop the hyphen
name = 'testpc802nrphy'
cflags += '-Wno-deprecated-declarations'
cflags += '-DRTE_ENABLE_ASSERT'
dpdk_conf.set('MULTI_PC802', get_option('enable_multi_pc802'))
sources = files(
        'testpc802.c',
        'cmdline.c'
)

deps += ['ethdev', 'cmdline', 'bus_pci']

if dpdk_conf.has('RTE_NET_PC802')
    deps += 'net_pc802'
endif
