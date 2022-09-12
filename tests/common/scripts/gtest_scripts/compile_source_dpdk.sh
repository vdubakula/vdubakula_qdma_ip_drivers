#!/bin/bash

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root"
   exit 1
fi

src_dir=${PWD}/../../../../drivers/dpdk
test_dir=${PWD}/../../apps/qdma_test
target="pf_vf"
compile_flags=
config_bar=0

if [ ! -z $1 ]; then
	src_dir=${PWD}/$1
fi

if [ ! -z $2 ]; then
	test_dir=${PWD}/$2
fi

if [ ! -z $3 ]; then
	dpdk_src=${PWD}/$3
fi

if [ ! -z $4 ]; then
	if [[ $4 == "pf_vf" || $4 == "pf" || $4 == "vf" ]]; then
		target=$4
	fi
fi

if [ ! -z $5 ]; then
	config_bar=$5
fi

if [ ! -z $6 ]; then
	compile_flags=$6
fi



if [ ! -d $src_dir ]; then
	echo "no such $src_dir directory exists"
	exit
fi

if [ ! -d $test_dir ]; then
	echo "no such $test_dir directory exists"
	exit
fi

if [ ! -d $dpdk_src ]; then
	echo "no such $dpdk_src directory exists"
	exit
fi

build_dir=build_dpdk_$target

mkdir -p ${test_dir}/${build_dir}
chmod 777 ${test_dir}/${build_dir} -R
mkdir -p ${test_dir}/logs
chmod 777 ${test_dir}/logs -R
rm -f ${test_dir}/logs/*
rm -r ${test_dir}/${build_dir}/
mkdir -p ${test_dir}/${build_dir}/DPDK

cd ${test_dir}/${build_dir}/DPDK
tar xzf ${dpdk_src}/dpdk-stable-20.11.tar.gz
cd dpdk-stable-20.11
tar xzf ${dpdk_src}/dpdk-kmods.tar.gz
cd dpdk-kmods/linux/igb_uio
make
chmod 777 igb_uio.ko
cd ../../..
patch -p1 < ${src_dir}/patches/dpdk/0001-net-qdma-Integrate-qdma-pmd-to-dpdk-20.11.patch
patch -p1 < ${src_dir}/patches/testpmd/0001-TESTPMD-20.11-Patch-to-add-additional-rxtx-ops.patch
patch -p1 < ${src_dir}/patches/proc-info/0001-Add-QDMA-xdebug-to-proc-info-of-dpdk-20.11.patch

rsync -av ${src_dir}/drivers/net/qdma drivers/net/
rsync -av ${src_dir}/../qdma_access drivers/net/qdma/.
sed -i '/dev_info->max_mac_addrs = 1;/a\\tdev_info->dev_capa |= RTE_ETH_DEV_CAPA_RUNTIME_RX_QUEUE_SETUP | RTE_ETH_DEV_CAPA_RUNTIME_TX_QUEUE_SETUP;' drivers/net/qdma/qdma_devops.c
sed -i '/dev_info->max_mac_addrs = 1;/a\\tdev_info->dev_capa |= RTE_ETH_DEV_CAPA_RUNTIME_RX_QUEUE_SETUP | RTE_ETH_DEV_CAPA_RUNTIME_TX_QUEUE_SETUP;' drivers/net/qdma/qdma_vf_ethdev.c
sed -i "s/#define DEFAULT_PF_CONFIG_BAR .*/#define DEFAULT_PF_CONFIG_BAR   (${config_bar})/"  drivers/net/qdma/qdma.h
sed -i "s/#define DEFAULT_VF_CONFIG_BAR .*/#define DEFAULT_VF_CONFIG_BAR   (${config_bar})/"  drivers/net/qdma/qdma.h
make config T=x86_64-native-linuxapp-gcc
sed -i "s/struct rte_pci_device.*pci_dev = bus_device;/struct rte_pci_device *pci_dev = (struct rte_pci_device *)bus_device;/" lib/librte_ethdev/rte_ethdev_pci.h
meson build
meson configure build -Dc_args=${compile_flags}
cd build
ninja
ninja install
ldconfig
export RTE_SDK=${PWD}
export RTE_TARGET=build
cd ${test_dir}/${build_dir}/
echo "Building the test application for target : " $target
if [[ $target == "pf_vf" || $target == "pf" ]]; then
	cmake -DDPDK:BOOL=ON ..
elif [ $target == "vf" ]; then
	cmake -DDPDK:BOOL=ON -DTEST_VF_ALONE:BOOL=ON ..
fi
make
