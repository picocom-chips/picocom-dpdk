# SPDX-License-Identifier: BSD-3-Clause
# Copyright(c) 2018 Intel Corporation

sources = files('sec_cryptodev.c')
deps += ['cryptodev', 'net', 'security']
if dpdk_conf.has('RTE_CRYPTO_SCHEDULER')
	deps += 'crypto_scheduler'
endif
