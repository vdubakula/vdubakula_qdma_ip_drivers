#!/bin/bash

#set -x 

bdf=01000

if [ $# -lt 3 ]; then
	echo "Invalid arguements."
	echo "$0 <drv_mode> <bdf> <num_qs> <num_vfs> <drv_mode> <test_report>"
	exit;
fi;

bdf=01000
if [ ! -z $1 ]; then
	bdf=$1
fi

num_qs=10
if [ ! -z $2 ]; then
	num_qs=$2
fi

num_vfs=10
if [ ! -z $3 ]; then
	num_vfs=$3
fi

drv_mode=0
drv_mode_string="Auto"
if [ ! -z $4 ]; then
	drv_mode=$4
	if [ $drv_mode -eq "0" ]; then
		drv_mode_string="Auto"
	elif [ $drv_mode -eq "1" ]; then
		drv_mode_string="Poll"
	elif [ $drv_mode -eq "2" ]; then
		drv_mode_string="Direct_Interrupt"
	elif [ $drv_mode -eq "3" ]; then
		drv_mode_string="Interrupt_Aggr"
	fi
fi

opfile=flr_pf_offline_report.xlsx
if [ ! -z $5 ]; then
	opfile=$5
fi

bus_id=${bdf:0:2}
#pf_funcid=qdma${bus_id}000
vf_funcid=qdmavf${bdf}
function fmap_test()
{
	func=$1
	expected_qs=$2
	fmap_num_qs=`dma-ctl dev list | grep ${func} | cut -d " " -f 3 | cut -d "," -f 1`
	if [ $fmap_num_qs -eq $expected_qs ]; then
		return 0
	else
		return 1
	fi
	
}

function q_add_test()
{
	func=$1
	expected_qs=$2
	added_qs=`dma-ctl ${func} q add list 0 ${expected_qs} 2>/dev/null | grep Added | cut -d " " -f 2`
	if [ $added_qs -eq $expected_qs ]; then
		return 0
	else
		return 1
	fi
	
}

function q_start_test()
{
	func=$1
	expected_qs=$2
	added_qs=`dma-ctl ${func} q start list 0 ${expected_qs} 2>/dev/null | grep started | cut -d " " -f 1`
	if [ $added_qs -eq $expected_qs ]; then
		return 0
	else
		return 1
	fi
	
}

function insert_module()
{
	if [ $1 == pf ]; then 
		module_name=qdma-pf
		num_funcs=4
		echo -n "options qdma-pf mode=" > conf_file
	else
		module_name=qdma-vf
		num_funcs=$num_vfs
		echo -n "options qdma-vf mode=" > conf_file
	fi;
	
		for ((j = 0; j < ${num_funcs}; j++))
		do
			echo -n "0x${bus_id}:${j}:${drv_mode}" >> conf_file
			if [ $j != $((${num_funcs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	
		done
		echo -e "" >> conf_file
		rm -rf /etc/modprobe.d/qdma.conf
		cp conf_file /etc/modprobe.d/qdma.conf
		rm -rf conf_file
		modprobe $module_name
}

function execute_t1()
{
        echo "**********TEST CASE START *************"
        #insert_module pf
        insert_module vf
        #echo "Adding ${num_vfs} VFs to PF"
        #echo $num_vfs > /sys/bus/pci/devices/0000\:${bus_id}\:04.0/sriov_numvfs
        echo "Going for FLR of VF"
        echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:04.0/reset
        fmap_test $vf_funcid 0
        if [ $? -eq 0 ]; then
                echo "FMAP clear after FLR"
        fi

        echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:04.0/qdma/qmax


        fmap_test $vf_funcid $num_qs
        if [ $? -eq 0 ]; then
                echo "FMAP programming successful after FLR"
        fi
        q_add_test $vf_funcid $num_qs
        if [ $? -eq 0 ]; then
                echo "Q Add successful after FLR"
        fi
        q_start_test $vf_funcid $num_qs
        if [ $? -eq 0 ]; then
                echo "Q Start successful after FLR"
        fi

        dma-to-device -d /dev/${vf_funcid}-MM-0

        rmmod qdma-vf
        echo "**********TEST CASE END *************"
}
execute_t1
