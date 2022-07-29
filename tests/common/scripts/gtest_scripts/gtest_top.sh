#!/bin/bash

pci_bbddf=02000
cfg_dir=gtest_configs_qdma_soft/default
drv="linux"
src_dir=../../../../sw_host/linux
test_dir=../../apps/qdma_test
config_bar=0
compile_flags=
target="pf_vf"
failures_detected=0
dpdk_bind_drv="igb_uio"
enable_compile=1
multi_apps=0
cpm5_flag=0

if [ $# -lt 2 ]; then
echo "usage: $0 <pci_bbddf> <cfg_dir> [<src dir>] [<gtest dir>] [pf_vf|pf|vf] [linux|dpdk] [Config BAR] [Compile Flags] [dpdk_bind_drv/multi_app] [Compile Flags] [cpm5_flag]"
	exit
fi
if [ ! -z $1 ]; then
	pci_bbddf=$1
fi
if [ ! -d ${PWD}/$2 ]; then
	echo "Invalid Config directory: ${PWD}/$2"
	exit 1
else
	cfg_dir=$2
fi
if [ ! -z $3 ]; then
	src_dir=$3
fi
if [ ! -z $4 ]; then
	test_dir=$4
fi
if [ ! -z $5 ]; then
	if [[ $5 == "pf_vf" || $5 == "pf" || $5 == "vf" ]]; then
		target=$5
	fi
fi
if [ ! -z $6 ]; then
	drv=$6
fi
if [ ! -z $7 ]; then
	config_bar=$7
fi
if [ $drv == "dpdk" ]; then
	if [ ! -z $8 ]; then
		dpdk_bind_drv=$8
	fi
else
	if [ ! -z $8 ]; then
		multi_apps=$8
	fi
fi

if [ ! -z $9 ]; then
	compile_flags=$9
fi

gtest_args=( "$@" )

for (( i=0; i<${#gtest_args[@]}; i++ ));
do
	if [[ ${gtest_args[$i]} == "CPM5" ]]; then
		cpm5_flag=1
		break
	fi
done

if [ $enable_compile == 1 ]; then
	if [ $drv == "linux" ]; then
		./compile_source_linux.sh ${src_dir} ${test_dir} ${target} ${compile_flags}
		com_ret_val=$?
		if [ $com_ret_val -ne 0 ]; then
			echo "Compilation failed"
			exit 1
		fi
	elif [ $drv == "dpdk" ]; then
		dpdk_src=../../../../../incoming/dpdk/dpdk-sources/
		./compile_source_dpdk.sh ${src_dir} ${test_dir} ${dpdk_src} ${target} ${config_bar} ${compile_flags}
	else
		echo "Invalid driver chosen"
		exit 1
	fi
fi

dm_pid=

kill_dmesg_dump()
{
	kill -9 ${dm_pid}
}

if [ $drv == "linux" ]; then
	dmesg -wH > dmesg_log.txt &
	dm_pid=$!
	trap kill_dmesg_dump EXIT
fi
gtest_ret_val=0
CONFIG_FILES=${PWD}/${cfg_dir}/*
for f in $CONFIG_FILES
do
	fname=$(basename "$f")
	if [[ $fname == DISABLED_* ]]; then
		continue
	fi
	echo "Running the gtests on target : " ${target} " : Config File : " $fname
	if [ $drv == "dpdk" ]; then
		./run_gtests.sh ${pci_bbddf} $f ${src_dir} ${test_dir} $drv ${config_bar} ${target} ${dpdk_bind_drv}
		gtest_ret_val=$?
	elif [ $drv == "linux" ]; then
		default_rmem=`sysctl net.core.rmem_max | cut -d = -f2 | cut -d ' ' -f2`
		echo "default rmem=${default_rmem}"
		#Set rmem_max to 512K
		sysctl net.core.rmem_max=524288
		current_setting=`sysctl net.core.rmem_max | cut -d = -f2 | cut -d ' ' -f2`
		echo "rmem_updated to ${current_setting}"
		cd ${src_dir}
		make install-mods
		cd -
		./run_gtests.sh ${pci_bbddf} $f ${src_dir} ${test_dir} $drv ${config_bar} ${target} ${multi_apps} ${cpm5_flag}
		gtest_ret_val=$?
		cd ${src_dir}
		make uninstall-mods
		cd -
		sysctl net.core.rmem_max=${default_rmem}
		default_rmem=`sysctl net.core.rmem_max | cut -d = -f2 | cut -d ' ' -f2`
		echo "Restored rmem_max to ${default_rmem}"
	else
		echo "Invalid Driver"
		exit 1
	fi
	echo "run_gtests.sh for last config returned with $gtest_ret_val"
	if [ $gtest_ret_val -ne 0 ]; then
		failures_detected=1
	fi
done
if [ $failures_detected -ne 0 ]; then
	echo "Completed with failures"
else
	echo "Completed successfully"
fi

if [ $drv == "linux" ]; then
	kill -9 ${dm_pid}
fi
exit $failures_detected
