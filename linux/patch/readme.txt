How to patch for LS1046A

#Download develop environment Ubuntu-20.04.3
tar -xvf flexbuild_lsdk2108.tgz
cd flexbuild_lsdk2108/
source setup.env
flex-builder -i repo-fetch

cd flexbuild_lsdk2108/
vim configs/sdk.yml, and change OPTEE：y to OPTEE：n


#Apply kernel patch
cd components/linux/linux/
git checkout -b LSDK-21.08-LS1046A-PSCB-PR1
cp ../../../patch/linux.patch .
patch -p1 < linux.patch
rm -f linux.patch

#Apply lsdk patch
cd flexbuild_lsdk2108/
patch -p1 < flexbuild_lsdk2108.patch
rm -rf flexbuild_lsdk2108.patch

#Apply atf patch
cp ../../../patch/atf.patch .
cd flexbuild_lsdk2108/components/firmware/atf
patch -p1 < atf.patch
rm -rf atf.patch

#Apply rcw patch
cd flexbuild_lsdk2108/components/firmware/rcw
patch -p1 < rcw.patch
rm -rf rcw.patch

#Apply uboot  patch
cd flexbuild_lsdk2108/components/firmware/uboot
patch -p1 < uboot.patch
rm -rf uboot.patch


#Complile steps:
flex-builder  -i mkfw -a arm64 -m ls1046apscb -b sd
flex-builder -i mkboot -a arm64 -m ls1046apscb -b sd
flex-builder -c linux -a arm64
flex-builder -c dpdk -a arm64
flex-builder -c pktgen_dpdk -a arm64
flex-builder -i merge-component -a arm64
flex-builder -i mkitb -r ubuntu:main -a arm64


