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

set -e

ARCH="amd64"
IMAGE_PATH=""

while getopts ai: ARGS
do
case $ARGS in
    a)
        ARCH="arm64"
        ;;
    i)
        IMAGE_PATH=$OPTARG
        ;;
    *)
        echo "Unknown option $ARGS"
        ;;
esac
done

#init path and info
FILE_PATH=$(dirname $(readlink -f "$0"))
PRJ_PATH=$FILE_PATH/..
cd $PRJ_PATH
COMMIT_ID=`git rev-parse --short=8 HEAD`
BRANCH=`git symbolic-ref --short -q HEAD`
VERSION=`cat ./drivers/net/pc802/version`
VERSION="${VERSION}-${COMMIT_ID}"

#creat build pkg folder
rm -rf $PRJ_PATH/build-pkg
RELEASE_DIR=$PRJ_PATH/build-pkg/PC802_User_Plane_Driver-release-$ARCH-$VERSION

mkdir -p  $RELEASE_DIR

mkdir -p  $RELEASE_DIR/usr/local
mkdir -p  $RELEASE_DIR/opt/picocom/phyCfgs

mkdir -p  $RELEASE_DIR/DEBIAN
touch  $RELEASE_DIR/DEBIAN/control
touch  $RELEASE_DIR/DEBIAN/postinst
#touch  $RELEASE_DIR/DEBIAN/postrm

#编译软件文件
cd $PRJ_PATH/
if [ "$ARCH" == "arm64" ]; then
    rm -rf aarch64-build-gcc
    meson aarch64-build-gcc --prefix=$RELEASE_DIR/usr/local --cross-file config/arm/arm64_armv8_linux_gcc
    ninja -C aarch64-build-gcc install
else
    rm -rf build
    meson build --prefix=$RELEASE_DIR/usr/local
    ninja -C build install
fi

cp $FILE_PATH/pc802_files/npu_run.sh  $RELEASE_DIR/usr/local/bin/
chmod +x  $RELEASE_DIR/usr/local/bin/npu_run.sh
cp $FILE_PATH/pc802_files/pc802_show.sh  $RELEASE_DIR/usr/local/bin/
chmod +x  $RELEASE_DIR/usr/local/bin/pc802_show.sh

#log config file
cd $PRJ_PATH
cd build-pkg
mkdir -p  $RELEASE_DIR/etc/rsyslog.d
mkdir -p  $RELEASE_DIR/etc/logrotate.d
cp $FILE_PATH/pc802_files/rsyslog.pc802.conf  $RELEASE_DIR/etc/rsyslog.d/40-pc802.conf
cp $FILE_PATH/pc802_files/logrotate.pc802     $RELEASE_DIR/etc/logrotate.d/pc802

if [ -n "$IMAGE_PATH" ]; then
    mkdir -p  $RELEASE_DIR/lib/firmware/pico
    scp $IMAGE_PATH/build-ssbl/pc802.ssbl      $RELEASE_DIR/lib/firmware/pico/
    scp $IMAGE_PATH/build-case_perf/pc802.img  $RELEASE_DIR/lib/firmware/pico/
fi

echo "Package: pc802-user-plane-driver" >> $RELEASE_DIR/DEBIAN/control
echo "Version: $VERSION"    >> $RELEASE_DIR/DEBIAN/control
#echo "Section: free"       >> $RELEASE_DIR/DEBIAN/control
echo "Prioritt: optional"   >> $RELEASE_DIR/DEBIAN/control
echo "Architecture: $ARCH"  >> $RELEASE_DIR/DEBIAN/control
echo "Maintainer: suport@picocom.com"     >> $RELEASE_DIR/DEBIAN/control
echo "Description: picocom PC802 user space driver"   >> $RELEASE_DIR/DEBIAN/control
echo ""                     >> $RELEASE_DIR/DEBIAN/control

echo "# !/bin/sh"                           >> $RELEASE_DIR/DEBIAN/postinst
echo ""                                     >> $RELEASE_DIR/DEBIAN/postinst
echo "systemctl restart rsyslog"            >> $RELEASE_DIR/DEBIAN/postinst
chmod +x  $RELEASE_DIR/DEBIAN/postinst

#echo "# !/bin/sh"                           >> $RELEASE_DIR/DEBIAN/postrm
#chmod +x  $RELEASE_DIR/DEBIAN/postrm

cd $PRJ_PATH/build-pkg
dpkg -b  $RELEASE_DIR PC802_User_Plane_Driver_${ARCH}_${VERSION}.deb