#!/usr/bin/env bash
#/* SPDX-License-Identifier: BSD-3-Clause
# * Copyright(c) 2018-2022 Picocom Corporation
# */

SCRIPT_DIR=$(dirname $(readlink -f "$0"))
cd $SCRIPT_DIR
PRJ_PATH=`git rev-parse --show-toplevel`
echo $PRJ_PATH
cd $PRJ_PATH
rm -fr build-docs
mkdir -p build-docs && cd $_
cmake $PRJ_PATH/doc/guides/picodevs
make -j sphinxhtml 2>&1 | tee sphinxhtml.log
make -j sphinxlatex 2>&1 | tee sphinxlatex.log
pushd sphinxlatex
make 2>&1 | tee sphinxpdf.log
popd
