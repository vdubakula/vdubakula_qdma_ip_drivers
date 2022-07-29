#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Usage: run_tests.sh <pci bus:device> [<out_dir>]"
	exit;
fi;

pci_bd=$1
testname="default"
if [ ! -z $2 ]; then
	testname=$2
fi;

start=$SECONDS
CONFIG_FILES=$PWD/configs/*
poll_mode=1
intr_mode=1
intr_aggr=1

if [ ${poll_mode} -eq 1 ]; then
	insmod ${PWD}/../../../sw_host/mdma/linux/build/qdma.ko 
	if [ $? -ne 0 ]; then
		exit 1
	fi
	for f in $CONFIG_FILES
	do
		./perf_analysis.sh $f out_poll_${testname} ${pci_bd}
	done
	echo "parsing performance results..."
	./parser.sh ${PWD}/out_poll_${testname}/unidir
	./parser.sh ${PWD}/out_poll_${testname}/bidir

	rmmod qdma
fi

if [ ${intr_mode} -eq 1 ]; then
	insmod ${PWD}/../../../sw_host/mdma/linux/build/qdma.ko poll_mode_en=0
	if [ $? -ne 0 ]; then
		exit 1
	fi
		for f in $CONFIG_FILES
	do
		./perf_analysis.sh $f out_intr_${testname} ${pci_bd}
	done
	echo "parsing performance results..."
	./parser.sh ${PWD}/out_intr_${testname}/unidir
	./parser.sh ${PWD}/out_intr_${testname}/bidir
	rmmod qdma
fi

if [ ${intr_aggr} -eq 1 ]; then
	insmod ${PWD}/../../../sw_host/mdma/linux/build/qdma.ko poll_mode_en=0 ind_intr_mode=1
			if [ $? -ne 0 ]; then
		exit 1
	fi
	for f in $CONFIG_FILES
	do
			./perf_analysis.sh $f out_intr_aggr_${testname} ${pci_bd}
	done
echo "parsing performance results..."
	./parser.sh ${PWD}/out_intr_aggr_${testname}/unidir
	./parser.sh ${PWD}/out_intr_aggr_${testname}/bidir
	rmmod qdma
fi

echo "Performance analysis and parsing of results finished"

echo "Done"

end=$SECONDS
echo "script execution time: $((end-start)) seconds"
