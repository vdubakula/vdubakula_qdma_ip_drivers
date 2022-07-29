#!/bin/bash - 
#===============================================================================
#
#          FILE: test_pf_vf_mix_advance2.sh
# 
#         USAGE: ./test_pf_vf_mix_advance3.sh <1/2/3>
# 
#   DESCRIPTION: This script will test all PFs/VFs in different combinations
#				 With google test app
#				 1 Q/PF, 1 VF/PF and 1 Q/VF
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

mode=$1
drv_path=../../../sw_host/mdma/linux/build/

dev_base=0000:06:00
#master_pfs=("0x6000" "0x6001" "0x6002" "0x6003")
master_pfs=("0x6003")
dev_base_hex="${dev_base//:}"
#pfs=(0 1 2 3)
pfs=(0)
q_per_pf=(1)
#num_vfs_per_pf=(0 1 50 60)
num_vfs_per_pf=(60)
total_q=2048

if [ $mode -eq 1 ]; then
	echo "Poll mode is selected"
	function insert_drv() {
		echo "Inserting Driver in Poll mode"
		insmod $drv_path/qdma.ko mode=1 master_pf=$1
		insmod $drv_path/qdma_vf.ko
	}
elif [ $mode -eq 2 ]; then
	echo "Direct Interrupt mode is selected"
	function insert_drv() {
		echo "Inserting Driver in Direct Interrupt Mode"
		insmod $drv_path/qdma.ko mode=2 master_pf=$1
		insmod $drv_path/qdma_vf.ko
	}
elif [ $mode -eq 3 ]; then
	echo "InDirect Interrupt mode is selected"
	function insert_drv() {
		echo "Inserting Driver in InDirect Interrupt Mode"
		insmod $drv_path/qdma.ko mode=3 master_pf=$1
		insmod $drv_path/qdma_vf.ko
	}
else
	echo "Invalid arguement"
	exit 1
fi


#remove all logs file
rm -rf *.log

function remove_drv() {
	/sbin/rmmod qdma
	/sbin/rmmod qdma_vf
}


for m_pf in ${master_pfs[@]}; do

	echo ""
	echo "***** master_pf=$m_pf  All 1 test*****"
	remove_drv
	insert_drv $m_pf
	echo "dma-ctl dev list"
	$drv_path/dma-ctl dev list
	
	# Allocate per PF queues
	echo 1 >  /sys/bus/pci/devices/$dev_base.0/qdma/qmax
	echo 1 >  /sys/bus/pci/devices/$dev_base.1/qdma/qmax
	echo 1 >  /sys/bus/pci/devices/$dev_base.2/qdma/qmax
	echo 1 >  /sys/bus/pci/devices/$dev_base.3/qdma/qmax
							
	# Allocate max queues for all VFs
	if [ "0x6000" == "$m_pf" ]; then
		full_m_pf=0000:06:00.0
	elif [ "0x6001" == "$m_pf" ]; then
		full_m_pf=0000:06:00.1
	elif [ "0x6002" == "$m_pf" ]; then
		full_m_pf=0000:06:00.2
	elif [ "0x6003" == "$m_pf" ]; then
		full_m_pf=0000:06:00.3
	else
		echo "Invalid arguement to convert val"
		exit 1
	fi
	
	echo 100 > /sys/bus/pci/devices/$full_m_pf/qdma/qmax_vfs
	
	#Instanciate VFs
	echo 1 > /sys/bus/pci/devices/$dev_base.0/sriov_numvfs
	echo 1 > /sys/bus/pci/devices/$dev_base.1/sriov_numvfs
	echo 1 > /sys/bus/pci/devices/$dev_base.2/sriov_numvfs
	echo 1 > /sys/bus/pci/devices/$dev_base.3/sriov_numvfs
	
	#Assign Queues to VFs
	echo 1 > /sys/bus/pci/devices/$dev_base.0/virtfn0/qdma/qmax
	echo 1 > /sys/bus/pci/devices/$dev_base.1/virtfn0/qdma/qmax
	echo 1 > /sys/bus/pci/devices/$dev_base.2/virtfn0/qdma/qmax
	echo 1 > /sys/bus/pci/devices/$dev_base.3/virtfn0/qdma/qmax
	
	echo ""
	echo "dma-ctl dev list after"
	$drv_path/dma-ctl dev list
	
	echo "qdma_test"
	qdma_test > MPF$m_pf.Q1PF.VF1pf.Q1VF.log
	if [ $? -ne 0 ]; then
		exit 1
	fi
	
done

remove_drv

echo "All test successfully Pass"
