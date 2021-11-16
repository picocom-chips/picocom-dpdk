# Copyright(c) 2020 PICOCOM Corporation

# override default name to drop the hyphen
name = 'testpc802'
cflags += '-Wno-deprecated-declarations'
sources = files(
        'cmdline.c',
        'testpc802.c',
)

deps += ['ethdev', 'cmdline', 'bus_pci']
