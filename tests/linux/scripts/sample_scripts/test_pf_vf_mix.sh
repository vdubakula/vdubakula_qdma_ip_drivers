#!/bin/bash - 
#===============================================================================
#
#          FILE: test_pf_vf_mix.sh
# 
#         USAGE: ./test_pf_vf_mix.sh <1/2/3>
# 
#   DESCRIPTION: This script will test all PFs/VFs in different combinations
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
    echo "Usage : $0 <arg>"
    echo "<arg> : "
    echo "        1 - Poll Mode "
    echo "        2 - Direct Interrupt Mode "
    echo "        3 - InDirect Interrupt Mode "
    echo ""
    exit 1
}

if [ $# -ne 1 ]; then
    echo "Invalid arguements."
    print_help
else
    if [ $1 == 1 ] || [ $1 == 2 ] || [ $1 == 3 ]; then
        echo ""
    else
        echo "Invalid arguements."
        print_help
    fi
fi


mode=$1
drv_path=../../../sw_host/mdma/linux/build/

dev_base=0000:06:00
master_pfs=("0x6000" "0x6001" "0x6002" "0x6003")
#master_pfs=("0x6000" "0x6003")
dev_base_hex="${dev_base//:}"
pfs=(0 1 2 3)
#pfs=(0 3)
q_per_pf=(0 1 8 1024 2048)
#q_per_pf=(1800)
num_vfs_per_pf=(0 1 50 60)
#num_vfs_per_pf=(1 7)
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


for pf in ${pfs[@]}; do
	for m_pf in ${master_pfs[@]}; do
		for q_pf in ${q_per_pf[@]}; do
			for num_vf in ${num_vfs_per_pf[@]}; do
				
				max_vf_q=`expr $total_q - $q_pf`
				if [ $num_vf -ne 0 ]; then
					q_vf=`expr $max_vf_q / $num_vf`
				else
					q_vf=0
				fi
				
				echo ""
				echo "***** PF=$pf master_pf=$m_pf PF-Qs=$q_pf VF-Qs=$q_vf MAX_VF-Qs=$max_vf_q  num_vf=$num_vf*****"
				remove_drv
				insert_drv $m_pf
				echo "dma-ctl dev list"
				$drv_path/dma-ctl dev list
										
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
				
				echo "echo $max_vf_q > /sys/bus/pci/devices/$full_m_pf/qdma/qmax_vfs"
				echo $max_vf_q > /sys/bus/pci/devices/$full_m_pf/qdma/qmax_vfs
				if [ $? -ne 0 ]; then
					exit 1
				fi
				
				# Allocate per PF queues
				echo "echo $q_pf >  /sys/bus/pci/devices/$dev_base.$pf/qdma/qmax"
				echo $q_pf >  /sys/bus/pci/devices/$dev_base.$pf/qdma/qmax
				if [ $? -ne 0 ]; then
					exit 1
				fi
				
				#Instanciate VFs
				echo "echo $num_vf > /sys/bus/pci/devices/$dev_base.$pf/sriov_numvfs"
				echo $num_vf > /sys/bus/pci/devices/$dev_base.$pf/sriov_numvfs
				if [ $? -ne 0 ]; then
					exit 1
				fi
				
				if [ $num_vf -ne 0 ]; then
					#Allocate queus per VFs
					
					vf=$((num_vf-1));
					
					while [ $vf -ge 0 ]
					do
						echo "echo $q_vf > /sys/bus/pci/devices/$dev_base.$pf/virtfn$vf/qdma/qmax"
						sleep 1	# Need to fix Borken Pipe error
						echo $q_vf > /sys/bus/pci/devices/$dev_base.$pf/virtfn$vf/qdma/qmax
						if [ $? -ne 0 ]; then
							exit 1
						fi
						vf=$((vf-1))
					done
				fi
				
				echo ""
				echo "dma-ctl dev list after"
				$drv_path/dma-ctl dev list
				
				echo "qdma_test"
				qdma_test > PF$pf.MPF$m_pf.PFQ$q_pf.MAXvfQs$max_vf_q.NUMvfs$num_vf.VFQ$q_vf.log
				if [ $? -ne 0 ]; then
					exit 1
				fi
				echo ""
			done
		done
	done
done

echo "All test successfully Pass"

