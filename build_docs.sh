#!/usr/bin/env bash

#. $(dirname "$0")/setup.sh

export NPU_DRIVER_BASE=~/picocom/npu_driver

#module load /opt/picocom/tools/modulefiles/gcc/andes/latest
#module load project/pc802/soc_verify
#module load ceva/xc12/17.5.2

rm -fr build-docs
mkdir -p build-docs && cd $_
cmake ${NPU_DRIVER_BASE}/doc/
make -j  sphinxhtml 2>&1 | tee sphinxhtml.log
make -j  sphinxlatex 2>&1 | tee sphinxlatex.log
pushd sphinxlatex
make 2>&1 | tee sphinxpdf.log
popd

#cd ..
#tar -zcvf build-docs.tar.bz2 build-docs/
