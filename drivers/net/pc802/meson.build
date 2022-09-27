# Copyright(c) 2020 PICOCOM Corporation

if is_windows
    build = false
    reason = 'not supported on Windows'
    subdir_done()
endif

commit = run_command('git','rev-parse', '--short=8', 'HEAD').stdout().strip()
if run_command('git', 'status', '-s').stdout().strip()!=''
        commit += '*'
endif
version = run_command(find_program('cat', 'more'), files(meson.current_source_dir()+'/version')).stdout().strip()
version += '('+commit+')'
message('version: @0@'.format(version))
dpdk_conf.set('PC802_UDRIVER_VERSION', '"'+version+'"')
cflags += '-DRTE_ENABLE_ASSERT'
dpdk_conf.set('MULTI_PC802', get_option('enable_multi_pc802'))

sources = files(
        'pc802_ethdev.c',
        'pc802_kni.c',
        'pc802_pdump.c',
        'pc802_logs.c',
        'pcxx_ipc.c',
        'pcxx_oam.c',
        'pc802_mailbox.c'
)

headers = files(
        'rte_pmd_pc802.h',
        'pcxx_ipc.h',
        'pcxx_oam.h'
)
