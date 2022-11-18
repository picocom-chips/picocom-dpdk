# Copyright(c) 2020 PICOCOM Corporation


if not is_linux
    build = false
    reason = 'only supported on Linux'
endif

sources = files(
  'test_bha.c',
)

headers = files(
)

deps += ['ethdev', 'cmdline', 'bus_vdev']
if dpdk_conf.has('RTE_NET_PICO_BHA')
    deps += 'net_pico_bha'
endif

