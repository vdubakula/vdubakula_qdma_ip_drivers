#!/bin/bash

function print_help() {
	echo ""
	echo "Usage : $0 [<bind-driver>] [<num-vfs>] [<total-queues>] [<total-time>]"
	echo "Ex : $0 81000 igb_uio 8 2048 00:01:00 0"
	echo "<bbddf> : PF Bus device function in bbddf format ex:06000"
	echo ""
	echo "<bind-driver> : igb_uio or vfio-pci"
	echo "           Default - igb_uio"
	echo ""
	echo ""
	echo "<num-vfs> : number of vfs per pf"
	echo "           Default - 08 "
	echo ""
	echo "<total-queues> : Number of queues to be used for stress testing"
	echo "		       this total queues will be distributed uniformly across functions."
	echo "           Default - 96 (ie 8 queues per fucniton)"
	echo ""
	echo "<total-time> : execution time in hh:mm:ss format"
	echo "           Default - 00:01:00 "
	echo ""
}

function print_functionality() {
	echo ""
	echo "This script does the stress testing of QDMA IP DPDK Driver."
	echo "This script requires following parameters for execution:"
	echo "    --> Total number of vfs per pf on which this testing needs to be done (optional)."
	echo "    --> Total number of queues on which this testing needs to be done (optional)."
	echo "        This paramater defaults to 96. These queues are distributed for all available functions equally"
	echo "    --> Total durations for which the transfers needs to be stressed (optional) in hh:mm:sec format."
	echo "        This defaults to 1 min."
	echo " For all ports, each queue will be tested in MM-mode and ST-mode, in case of timeout (test execution reached the input stress testing time)"
	echo " any pending operation for given queue on given port will be carried out before quit the application."
	echo "***Note: An exit function is registered so that when the script completes execution or is forcefully terminated, the environemnt that"
	echo "was setup will be cleaned up."
}

if [ $# -lt 1 ]; then
	echo "Invalid arguements."
	print_help
	exit 1
fi;
if [ $1 == "-h" ]; then
	print_help
	print_functionality
	exit 0
fi

bind_drv=igb_uio

if [ ! -z $1 ]; then
	bind_drv=$1
fi

num_vfs=8
if [ ! -z $2 ]; then
	num_vfs=$2
fi

total_queues=96 #by default 8-queues per port.
if [ ! -z $3 ]; then
	total_queues=$3
fi

total_time="00:10:00"
if [ ! -z $4 ]; then
	total_time=$4
fi

#Total time is converted to seconds
t_hrs=$((${total_time:0:2}))
t_mins=$((${total_time:3:2}))
t_secs=$((${total_time:6:2}))
total_time_in_seconds=$(( (60*60*t_hrs) + (60*t_mins) + t_secs ))

function print_errs() {
	while read -r line; do
		echo $line
	done <<< "$1"
}

function cleanup_env()
{
	echo  "clean up: Unbind all funcitons, report if any errors"

	# Unbind the vfs
	cmd=`lspci | grep -i xilinx | awk -F " " '(($7 > "a000" && $7< "b000") || ($7 > "c000" && $7 < "d000")){print $1}' | tr -t "\n" " "`
	echo "vfs unbinding            : "$cmd
	../../usertools/dpdk-devbind.py -u $cmd
	if [ $? -lt 0 ]; then
		echo "failed to unbind vfs"
		exit 1
	fi


echo "****************************** ERRORS *************************"
mm_errs=$(cat mm_errors_log.txt | grep "Error\|ERROR\|FAIL\|Fail")
st_errs=$(cat st_errors_log.txt | grep "Error\|ERROR\|FAIL\|Fail")
if [ "${mm_errs}" != "" ]; then
	echo "MM Errors:"
	print_errs "${mm_errs}"
fi
if [ "${st__errs}" != "" ]; then
	echo "ST Errors:"
	print_errs "${st_errs}"
fi

echo ""
}

function test_setup()
{
	# load drivers
	. ./setup.sh

	echo "dpdk bind driver used for vfs: "$bind_drv

	cmd=`lspci | grep -i xilinx | awk -F " " '(($7 > "a000" && $7< "b000") || ($7 > "c000" && $7 < "d000")){print $1}' | tr -t "\n" " "`
	../../usertools/dpdk-devbind.py -b $bind_drv $cmd
	if [ $? -lt 0 ]; then
		echo "failed to bind vfs"
		exit 1
	fi

}

function run_stress_test()
{

	# total_ports=$((($num_vfs * $num_pfs) + $num_pfs))
	total_ports=$num_vfs
	q_per_port=$(($total_queues / $total_ports))
	test_setup

	chmod +x qdma_run_dpdk_stress_test.sh
	./qdma_run_dpdk_stress_test.sh $total_ports $q_per_port $total_time_in_seconds
}

run_stress_test
trap cleanup_env EXIT


