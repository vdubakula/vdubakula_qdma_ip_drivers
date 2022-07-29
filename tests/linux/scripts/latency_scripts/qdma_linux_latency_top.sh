#!/bin/bash

echo "Usage: $0 <master bbddf> <src_dir> <cfg_dir> <out_dir> <runtime> <no. of iterations>"

bbddf=0200
if [ ! -z $1 ]; then
	bbddf=$1
fi;
pci_bus=${bbddf:0:2}

src_dir=${PWD}/../../../../sw_host/linux/
if [ ! -z $2 ]; then
	src_dir=${PWD}/../../../../../../$2 #path w.r.t HEAD
fi;

cfg_dir="dmaperf_configs"
if [ ! -z $3 ]; then
	cfg_dir=$3
fi;

testname="default"
if [ ! -z $4 ]; then
	testname=$4
fi;

runtime=10
if [ ! -z $5 ]; then
	runtime=$5
fi;

count=1
if [ ! -z $6 ]; then
	count=$6
fi;


result_dir=""
CPUSpeed=`lscpu | grep "Model name" | cut -d @ -f 2 | cut -d " " -f 2 | cut -d G -f 1`
mkdir -p -m 0777 qdma_lat_results
chmod 0777 qdma_lat_results
result_dir="qdma_lat_results"


start=$SECONDS
CONFIG_FILES=$PWD/${cfg_dir}/*
poll_mode=0
intr_mode=0
intr_aggr=0
auto_mode=1

itr=0

cd ${src_dir}
make install-apps
make install-dev
cd -



run_tests()
{
	if [ ${poll_mode} -eq 1 ]; then
		echo "=========================================================================="
		echo "Poll Mode"
		echo "=========================================================================="
		rm -rf ${result_dir}/out_poll_${testname}/*
		for f in $CONFIG_FILES
		do
			fname=$(basename "$f")
			if [[ $fname == DISABLED_* ]]; then
				continue
			fi
			insmod ${src_dir}/bin/qdma.ko mode=0x${pci_bus}1111
			if [ $? -ne 0 ]; then
				exit 1
			fi

			
			./run_qdma_linux_latency.sh ${bbddf} $f ${result_dir}/out_poll_${testname}/${itr} ${runtime}
			
			rmmod qdma
		done
		chmod -R 0777 ${result_dir}/out_poll_${testname}
		python qdma_linux_gen_latency_result.py -d ${PWD}/${result_dir}/out_poll_${testname}/${itr}/dmalat_results/bidir -s $CPUSpeed -t ${PWD}/templates -o ${testname}
		
	
	fi;
	
	if [ ${intr_mode} -eq 1 ]; then
		echo "=========================================================================="
		echo "Intr Mode"
		echo "=========================================================================="
		rm -rf ${result_dir}/out_intr_${testname}/*
		for f in $CONFIG_FILES
		do
			fname=$(basename "$f")
			if [[ $fname == DISABLED_* ]]; then
				continue
			fi
			insmod ${src_dir}/bin/qdma.ko mode=0x${pci_bus}2222
			if [ $? -ne 0 ]; then
				exit 1
			fi
			./run_qdma_linux_latency.sh ${bbddf} $f ${result_dir}/out_intr_${testname}/${itr} ${runtime}
			rmmod qdma
		done
		chmod -R 0777 ${result_dir}/out_intr_${testname}
		python qdma_linux_gen_latency_result.py -d ${PWD}/${result_dir}/out_intr_${testname}/${itr}/dmalat_results/bidir -s $CPUSpeed -t ${PWD}/templates -o ${testname}
		
	fi;
	
	if [ ${intr_aggr} -eq 1 ]; then
		echo "=========================================================================="
		echo "Aggr Mode"
		echo "=========================================================================="
		rm -rf ${result_dir}/out_intr_aggr_${testname}/*
		for f in $CONFIG_FILES
		do
			fname=$(basename "$f")
			if [[ $fname == DISABLED_* ]]; then
				continue
			fi
			insmod ${src_dir}/bin/qdma.ko mode=0x${pci_bus}3333
			if [ $? -ne 0 ]; then
				exit 1
			fi
			./run_qdma_linux_latency.sh ${bbddf} $f ${result_dir}/out_aggr_${testname}/${itr} ${runtime}
			rmmod qdma
		done
		chmod -R 0777 ${result_dir}/out_intr_aggr_${testname}
		
		echo "Parsing latency results"
		python qdma_linux_gen_latency_result.py -d ${PWD}/${result_dir}/out_aggr_${testname}/${itr}/dmalat_results/bidir -t -s $CPUSpeed ${PWD}/templates -o ${testname}
		
	fi;
	if [ ${auto_mode} -eq 1 ]; then
		echo "=========================================================================="
		echo "Auto Mode"
		echo "=========================================================================="
		rm -rf ${result_dir}/out_auto_${testname}/*
		for f in $CONFIG_FILES
		do
			fname=$(basename "$f")
			if [[ $fname == DISABLED_* ]]; then
				continue
			fi
			insmod ${src_dir}/bin/qdma.ko mode=0x${pci_bus}0000
			if [ $? -ne 0 ]; then
				exit 1
			fi
			./run_qdma_linux_latency.sh ${bbddf} $f ${result_dir}/out_auto_${testname}/${itr} ${runtime}
			rmmod qdma
		done
		chmod -R 0777 ${result_dir}/out_auto_${testname}
		
		echo "parsing latency results"
		python qdma_linux_gen_latency_result.py -d ${PWD}/${result_dir}/out_auto_${testname}/${itr}/dmalat_results/bidir -t ${PWD}/templates -s $CPUSpeed -o ${testname}
		
	fi;
	itr=$((itr+1))
}


dmesg -wH > dmesg_log.txt &
dm_pid=$!

kill_dmesg_dump()
{
	kill -9 ${dm_pid}
}

trap kill_dmesg_dump EXIT
while [ ${count} -gt 0 ]
do
	run_tests
	count=$((count-1));
done

echo "Performance analysis and parsing of results finished"

echo "Done"

end=$SECONDS
echo "script execution time: $((end-start)) seconds"
