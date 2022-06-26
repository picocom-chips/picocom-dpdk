#!/bin/bash
#
# PICOCOM PROPRIETARY INFORMATION
#
# This software is supplied under the terms of a license agreement or
# nondisclosure agreement with PICOCOM and may not be copied
# or disclosed except in accordance with the terms of that agreement.
#
# Copyright PICOCOM.
#

set -x
set -e

#init path and info
FILE_PATH=$(dirname $(readlink -f "$0"))
PRJ_PATH=$FILE_PATH/..
cd $PRJ_PATH
COMMIT_ID=`git rev-parse --short=8 HEAD`
BRANCH=`git symbolic-ref --short -q HEAD`

#creat build pkg folder
rm -rf $PRJ_PATH/build-pkg
RELEASE_DIR=$PRJ_PATH/build-pkg/PC802_NR_PHY_User_Plane_Driver-release-$COMMIT_ID
mkdir -p  $RELEASE_DIR                         # 在该目录下存放生成deb包的文件以及目录
mkdir -p  $RELEASE_DIR/DEBIAN                  #目录名必须大写
mkdir -p  $RELEASE_DIR/usr/local               # 将文件安装到/boot目录下
mkdir -p  $RELEASE_DIR/opt/picocom/phyCfgs     # 将文件安装到/boot目录下
touch  $RELEASE_DIR/DEBIAN/control             # 必须要有该文件
touch  $RELEASE_DIR/DEBIAN/postinst            # 软件安装完后，执行该Shell脚本
#touch  $RELEASE_DIR/DEBIAN/postrm             # 软件卸载后，执行该Shell脚本

#编译软件文件
cd $PRJ_PATH/pcie/user_space/DPDK
rm -rf build
meson --prefix=$RELEASE_DIR/usr/local build
cd build
ninja install
cp $PRJ_PATH/script/npu_run.sh  $RELEASE_DIR/usr/local/bin/
chmod +x  $RELEASE_DIR/usr/local/bin/npu_run.sh
cp $PRJ_PATH/script/pc802_show.sh  $RELEASE_DIR/usr/local/bin/
chmod +x  $RELEASE_DIR/usr/local/bin/pc802_show.sh

#igb_uio
cd $PRJ_PATH/build-pkg
git clone https://glhk.picocomtech.com/tools/dpdk-kmods.git
cd dpdk-kmods/linux/igb_uio
make
cp igb_uio.ko $RELEASE_DIR/usr/local/bin/

#log config file
cd $PRJ_PATH
cd build-pkg
mkdir -p  $RELEASE_DIR/etc/rsyslog.d
mkdir -p  $RELEASE_DIR/etc/logrotate.d
cp ../pcie/user_space/config/rsyslog.pc802.conf  $RELEASE_DIR/etc/rsyslog.d/40-pc802.conf
cp ../pcie/user_space/config/logrotate.pc802  $RELEASE_DIR/etc/logrotate.d/pc802

#gen package info
#Package: mysoftware
#Version: 2016-02-26
#Section: free
#Priority: optional
#Depends: libssl.0.0.so, libstdc++2.10-glibc2.2
#Suggests: Openssl
#Architecture: i386
#Installed-Size: 66666
#Maintainer: Simon @ newdivide7037#gmail.com
#Provides: mysoftware
#Description: just for test

echo "Package: PC802_NR_PHY_User_Plane_Driver" >> $RELEASE_DIR/DEBIAN/control       #软件名称，中间不能有空格
echo "Version: 1.1"           >> $RELEASE_DIR/DEBIAN/control       #软件版本
echo "Section: free"        >> $RELEASE_DIR/DEBIAN/control         #软件类别
echo "Prioritt: optional"   >> $RELEASE_DIR/DEBIAN/control         #软件对于系统的重要性
echo "Architecture: amd64"  >> $RELEASE_DIR/DEBIAN/control         #软件所支持的平台架构
echo "Maintainer: suport@picocom.com"     >> $RELEASE_DIR/DEBIAN/control         #打包人和联系方式
echo "Description: picocom PC802 user space driver"   >> $RELEASE_DIR/DEBIAN/control      #对软件的描述
echo ""                     >> $RELEASE_DIR/DEBIAN/control         #此处必须空一行再结束

echo "# !/bin/sh"                           >> $RELEASE_DIR/DEBIAN/postinst
echo ""                                     >> $RELEASE_DIR/DEBIAN/postinst
echo "systemctl restart rsyslog"            >> $RELEASE_DIR/DEBIAN/postinst
chmod +x  $RELEASE_DIR/DEBIAN/postinst

#echo "# !/bin/sh"                           >> $RELEASE_DIR/DEBIAN/postrm
#chmod +x  $RELEASE_DIR/DEBIAN/postrm

cd $PRJ_PATH/build-pkg
dpkg -b  $RELEASE_DIR PC802_NR_PHY_User_Plane_Driver_amd64_$COMMIT_ID.deb #第一个参数为将要打包的目录名， #第二个参数为生成包的名称