#!/bin/bash - 
#===============================================================================
#
#          FILE: test_pf_all.sh
# 
#         USAGE: ./test_pf_all.sh <1/2/3>
# 
#   DESCRIPTION: This script will test all PFs in different combinations
#				 With google test app
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: keyurp, 
#  ORGANIZATION: 
#       CREATED: 08/28/2018 03:25:37 AM
#      REVISION:  ---
#===============================================================================

set -o nounset                              # Treat unset variables as an error

function print_help() {
    echo ""
    echo "Usage : $0 <mode> <bus> <device> <drv_path>"
    echo "<mode> : Mode selection"
	echo "        0 - All Mode "
    echo "        1 - Poll Mode "
    echo "        2 - Direct Interrupt Mode "
    echo "        3 - InDirect Interrupt Mode "
	echo ""
	echo "<bus> : PCIe base BUS no e.g. 06"
	echo ""
	echo "<device> : PCIe base device no e.g. 00"	
	echo "           Default - 00 "
	echo ""
	echo "<drv_path> : Path to driver build directory"
	echo "            Default - ../../../sw_host/mdma/linux/build/ "
    echo ""
    exit 1
}

if [ $# -lt 3 ]; then
    echo "Invalid arguements."
    print_help
else
    if [ $1 -ge 0 ] && [ $1 -le 3 ]; then
		echo ""
    else
        echo "Invalid arguements."
        print_help
    fi
fi


mode_arg=$1
bus=$2
device=${3:-"00"}
drv_path=${4:-"../../../sw_host/mdma/linux/build/"}
log_dir="$0.logs"

#check driver directory is valid or not
if [ ! -f "$drv_path/qdma.ko" ]; then
	echo "$drv_path Invalid directory"
	echo ""
	exit 1
fi

poll_mode_arg="mode=1"
dintr_mode_arg="mode=2"
indintr_mode_arg="mode=3"

dev_base="0000:$bus:$device"
master_pfs=("0x$bus"0"$device" "0x$bus"00"$((device+1))" "0x$bus"00"$((device+2))" "0x$bus"00"$((device+3))")
dev_base_hex="${dev_base//:}"
pfs=(0 1 2 3)
q_per_pf=(0 1 8 1024 2048)

function remove_drv() {
	/sbin/rmmod qdma
	/sbin/rmmod qdma_vf
}

function do_flr() {
	echo "echo 1 > /sys/bus/pci/devices/$dev_base.0/reset"
	echo 1 > /sys/bus/pci/devices/$dev_base.0/reset
	if [ $? -ne 0 ]; then
		exit 1
	fi
	echo "echo 1 > /sys/bus/pci/devices/$dev_base.1/reset"
	echo 1 > /sys/bus/pci/devices/$dev_base.1/reset
	if [ $? -ne 0 ]; then
		exit 1
	fi
	echo "echo 1 > /sys/bus/pci/devices/$dev_base.2/reset"
	echo 1 > /sys/bus/pci/devices/$dev_base.2/reset
	if [ $? -ne 0 ]; then
		exit 1
	fi
	echo "echo 1 > /sys/bus/pci/devices/$dev_base.3/reset"
	echo 1 > /sys/bus/pci/devices/$dev_base.3/reset
	if [ $? -ne 0 ]; then
		exit 1
	fi
}

#remove all logs file
rm -rf $log_dir
mkdir $log_dir
if [ $? -ne 0 ]; then
	exit 1
fi


if [ $mode_arg -eq 1 ]; then
	echo "Poll mode is selected"
	mode_arg=("$poll_mode_arg")
	IFS=""
elif [ $mode_arg -eq 2 ]; then
	echo "Direct Interrupt mode is selected"
	mode_arg=("$dintr_mode_arg")
	IFS=""
elif [ $mode_arg -eq 3 ]; then
	echo "InDirect Interrupt mode is selected"
	mode_arg=("$indintr_mode_arg")
	IFS=""
elif [ $mode_arg -eq 0 ]; then
	echo "All mode is selected"
	mode_arg=("$poll_mode_arg"
				"$dintr_mode_arg"
				"$indintr_mode_arg")
	IFS=""
else
	echo "Invalid arguement"
	print_help
fi

remove_drv

for mode in ${mode_arg[*]}; do
	echo ""
	echo "Testing ${mode}"
	if [ "${mode}" = "$poll_mode_arg" ]; then
		str_mode="poll"
	elif [ "${mode}" = "$dintr_mode_arg" ]; then
		str_mode="directInterrupt"
	elif [ "${mode}" = "$indintr_mode_arg" ]; then
		str_mode="IndirectInterrupt"
	else
		echo "Invalid mode"
		exit 1
	fi

	for pf in ${pfs[@]}; do
		for m_pf in ${master_pfs[@]}; do
			for q in ${q_per_pf[@]}; do		
				echo ""
				echo "***** PF=$pf master_pf=$m_pf Q=$q *****"
				
				log_file=$str_mode.PF$pf.MPF$m_pf.Q$q.log
				touch $log_dir/$log_file				
				
				echo "insmod $drv_path/qdma.ko $mode master_pf=$m_pf"
				insmod $drv_path/qdma.ko $mode master_pf=$m_pf
				if [ $? -ne 0 ]; then
					exit 1
				fi
				
				echo "insmod $drv_path/qdma_vf.ko"
				insmod $drv_path/qdma_vf.ko
				if [ $? -ne 0 ]; then
					exit 1
				fi
				
				echo "dma-ctl dev list initial" >> $log_dir/$log_file
				$drv_path/dma-ctl dev list >> $log_dir/$log_file
				
				echo "echo $q >  /sys/bus/pci/devices/$dev_base.$pf/qdma/qmax" >> $log_dir/$log_file
				echo $q >  /sys/bus/pci/devices/$dev_base.$pf/qdma/qmax
				if [ $? -ne 0 ]; then
					exit 1
				fi
				echo "dma-ctl dev list after" >> $log_dir/$log_file
				$drv_path/dma-ctl dev list >> $log_dir/$log_file
				
				echo "qdma_test"
				qdma_test >> $log_dir/$log_file
				if [ $? -ne 0 ]; then
					exit 1
				fi				
				echo ""
				remove_drv
			done
		done
	done
	echo "$str_mode mode Passed"
	do_flr
	sleep 2
done


echo "All test successfully Pass"
