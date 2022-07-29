#!/bin/bash

src_dir=${PWD}/../../../../sw_host/linux
test_dir=${PWD}/../../apps/qdma_test
compile_flags=
target="pf_vf"

if [ ! -z $1 ]; then
	src_dir=${PWD}/$1
fi

if [ ! -z $2 ]; then
	test_dir=${PWD}/$2
fi

if [ ! -z $3 ]; then
	if [[ $3 == "pf_vf" || $3 == "pf" || $3 == "vf" ]]; then
		target=$3
	fi
fi

if [ ! -z $4 ]; then
	compile_flags=$4
fi

if [ ! -d $src_dir ]; then
	echo "no such $src_dir directory exists"
	exit
fi

if [ ! -d $test_dir ]; then
	echo "no such $test_dir directory exists"
	exit
fi

build_dir=build_linux_$target
mkdir -p ${test_dir}/${build_dir}
chmod 0777 ${test_dir}/${build_dir}
mkdir -p ${test_dir}/logs
chmod 0777 ${test_dir}/logs
rm -f ${test_dir}/logs/*
cd ${src_dir}
chmod 0777 *.sh
./make_libqdma.sh clean
./make_libqdma.sh ${compile_flags}
make install-dev
make install-apps
depmod -a
cd ${test_dir}/${build_dir}
rm -rf *
echo "Building the test application for target : " $target
if [[ $target == "pf_vf" || $target == "pf" ]]; then
	cmake -DLINUX:BOOL=ON ..
elif [ $target == "vf" ]; then
	cmake -DLINUX:BOOL=ON -DTEST_VF_ALONE:BOOL=ON ..
fi
make
