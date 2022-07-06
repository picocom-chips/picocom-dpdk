# Copyright(c) 2020 PICOCOM Corporation

if is_windows
    build = false
    reason = 'not supported on Windows'
    subdir_done()
endif

cflags += '-DRTE_ENABLE_ASSERT'

sources = files(
        'pc802_ethdev.c',
        'pc802_logs.c',
        'pcxx_ipc.c',
        'pc802_oam_lib.c',
        'pc802_mailbox.c'
)

headers = files(
        'rte_pmd_pc802.h',
        'pcxx_ipc.h',
        'pc802_oam_lib.h'
)
