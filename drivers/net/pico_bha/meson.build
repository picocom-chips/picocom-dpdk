# Copyright(c) 2020 PICOCOM Corporation


if not is_linux
    build = false
    reason = 'only supported on Linux'
endif

#bha model path env
runcmd_ret = run_command('sh', '-c', 'echo $BHA_MODEL_PATH', check: true)
bha_model_path = runcmd_ret.stdout().strip()
if bha_model_path == ''
  message('########pico bha runcmd ret null and exit ########')
  assert(false, 'NULL env variable $BHA_MODEL_PATH, please set it first')
else
  message('########pico bha env $BHA_MODEL_PATH: @0@ ########'.format(bha_model_path))
endif

#bha model headers include
bha_model_headers = bha_model_path+'/headers/c/'
if run_command('[', '-d', bha_model_headers, ']').returncode() == 0
  message('######## bha model headers files directory exists, continue ########')
else
  assert(false, 'bha model headers directory not exists, please check it first: @0@'.format(bha_model_headers))
endif
includes += include_directories(bha_model_headers)

#bha model static lib
bha_model_lib_path = bha_model_path+'/target/release-lto/'
message('########pico bha bha model find path: @0@ ########'.format(bha_model_lib_path))
bha_model_lib = cc.find_library('bha_model', dirs : [bha_model_lib_path], static: true, required: true)
message('########pico bha bha model lib: @0@ ########'.format(bha_model_lib))
ext_deps += bha_model_lib


#bha driver
cflags += '-DRTE_NET_BHA_MODEL_EN'
includes += include_directories('.')
sources = files(
  'bha_ethdev.c',
  'bha_rxtx.c',
)

headers = files(
  'rte_pmd_bha.h',
  'bha_ethdev.h',
  'bha_rxtx.h',
  'bha_log.h',
)

