# SPDX-License-Identifier: BSD-3-Clause
# Copyright(c) 2020 PICOCOM Corporation

if not is_linux
    build = false
    reason = 'only supported on Linux'
endif


#bha model path env, include pico sec model
runcmd_ret = run_command('sh', '-c', 'echo $BHA_MODEL_PATH', check: true)
psec_model_path = runcmd_ret.stdout().strip()
if psec_model_path == ''
  message('########pico sec runcmd ret null and exit ########')
  assert(false, 'NULL env variable $BHA_MODEL_PATH, please set it first')
else
  message('########pico sec env $BHA_MODEL_PATH: @0@ ########'.format(psec_model_path))
endif

#bha model headers and pico sec model headers include
psec_model_headers = psec_model_path+'/headers/c/'
if run_command('[', '-d', psec_model_headers, ']').returncode() == 0
  message('######## pico sec model headers files directory exists, continue ########')
else
  assert(false, 'pico sec model headers directory not exists, please check it first: @0@'.format(psec_model_headers))
endif
includes += include_directories(psec_model_headers)

#bha model static lib, include pico sec model
psec_model_lib_path = psec_model_path+'/target/release-lto/'
message('########pico sec model find path: @0@ ########'.format(psec_model_lib_path))
psec_model_lib = cc.find_library('bha_model', dirs : [psec_model_lib_path], static: true, required: true)
message('########pico sec model lib: @0@ ########'.format(psec_model_lib))
ext_deps += psec_model_lib


cflags += '-DRTE_CRYPTO_BHA_SEC_MODEL_EN'
deps += ['bus_vdev', 'cryptodev']
includes += include_directories('.')
sources = files(
    'psec_cryptodev.c',
    'psec_cryptodev_ops.c',
    )

headers = files(
    'psec_log.h',
    'psec_cryptodev.h',
    )
