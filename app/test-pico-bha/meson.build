# Copyright(c) 2020 PICOCOM Corporation


if not is_linux
    build = false
    reason = 'only supported on Linux'
endif

#app test bha path
runcmd_ret = run_command('pwd', check: true)
app_test_bha_path = runcmd_ret.stdout().strip()
if app_test_bha_path == ''
  message('########app test bha runcmd ret null and exit ########')
  assert(false, 'NULL app test bha path!!!')
else
  message('########app test bha PATH: @0@ ########'.format(app_test_bha_path))
endif

#app test bha pcaps path
test_bha_pcaps_in_path = app_test_bha_path+'/files_pcap/'
test_bha_pcaps_out_path = app_test_bha_path+'/../../build/'
if run_command('[', '-d', test_bha_pcaps_in_path, ']').returncode() == 0
  message('######## test bha pcaps files folder exists, continue ########')
else
  assert(false, 'test bha pcaps files folder not exists, please check it first: @0@'.format(test_bha_pcaps_in_path))
endif
message('########test bha pcaps in path: @0@ ########'.format(test_bha_pcaps_in_path))
message('########test bha pcaps out path: @0@ ########'.format(test_bha_pcaps_out_path))
dpdk_conf.set('BHA_PCAPS_IN_PATH', '"'+test_bha_pcaps_in_path+'"')
dpdk_conf.set('BHA_PCAPS_OUT_PATH', '"'+test_bha_pcaps_out_path+'"')


cflags += '-DRTE_TEST_BHA_MODEL_EN'
sources = files(
  'test_bha.c',
  'pcap_mode.c',
  'crypto_dev.c',
  'cmdline.c',
)

headers = files(
  'test_bha.h',
)

deps += ['eal', 'mempool', 'net', 'mbuf', 'bus_vdev', 'cmdline', 'ethdev', 'cryptodev', 'security', 'ipsec']
if dpdk_conf.has('RTE_NET_PICO_BHA')
    deps += 'net_pico_bha'
endif
if dpdk_conf.has('RTE_CRYPTO_PICO_SEC')
    deps += 'crypto_pico_sec'
endif
if dpdk_conf.has('RTE_CRYPTO_SCHEDULER')
    deps += 'crypto_scheduler'
endif

includes = include_directories('.')
