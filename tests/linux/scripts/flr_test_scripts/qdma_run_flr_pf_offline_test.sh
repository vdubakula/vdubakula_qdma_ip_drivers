#!/bin/bash

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
pf_funcid=qdma${bus_id}000
vf_funcid=qdmavf${bus_id}004
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

# Test-Case 1
# Perform FLR of PF without any queues.
# After FLR perform qmax programming.
# Verify that fmap programming, adding/ starting Q and running traffic on the Q added is working fine
function execute_t1()
{
	echo "**********TEST CASE 1 START *************"
	insert_module pf
	echo "Programming ${num_qs} in FMAP"	
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
	echo "Going for reset of PF"
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/reset
	fmap_test $pf_funcid 0
	if [ $? -eq 0 ]; then
		echo "FMAP clear after FLR"
	fi
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
	fmap_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "FMAP programming successful after FLR"
	fi
	q_add_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Add successful after FLR"
	fi
	q_start_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Start successful after FLR"
	fi
	dma-to-device -d /dev/qdma${bdf}-MM-0
	if [ $? -eq 0 ]; then
		echo "Test case 1 PASS"
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 1 -r "PASS"
	else
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 1 -r "FAIL"
	fi
	rmmod qdma-pf
	echo "**********TEST CASE 1 END *************"
}
# Test Case 2
# Add 10 Qs to PF and start it.
# Perform FLR on the PF.
# Verify that the Q added has been deleted and the FMAP programming for the PF has been reset.
# Verify that fmap programming, adding/ starting Q and running traffic on the Q added is working fine
function execute_t2()
{
	echo "**********TEST CASE 2 START *************"
	insert_module pf
	echo "Programming ${num_qs} in FMAP"	
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
	echo "Add and start ${num_qs} in PF"	
	q_add_test $pf_funcid $num_qs
	q_start_test $pf_funcid $num_qs
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/reset
	fmap_test $pf_funcid 0
	if [ $? -eq 0 ]; then
		echo "FMAP clear after FLR"
	fi
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
	fmap_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "FMAP programming successful after FLR"
	fi
	q_add_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Add successful after FLR"
	fi
	q_start_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Start successful after FLR"
	fi
	dma-to-device -d /dev/$pf_funcid-MM-0
	if [ $? -eq 0 ]; then
		echo "Test case 2 PASS"
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 2 -r "PASS"
	else
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 2 -r "FAIL"
	fi
	rmmod qdma-pf
	echo "**********TEST CASE 2 END *************"
}

# Test Case 3
# Add VFs to PF
# Perform FLR on VF
# verify that fmap programming is OK
# adding/starting Q and running traffic on the Q is working fine
function execute_t3()
{
	echo "**********TEST CASE 3 START *************"
	insert_module pf
	insert_module vf
	echo "Adding ${num_vfs} VFs to PF"
	echo $num_vfs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo "Going for FLR of VF"
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/reset
	fmap_test $vf_funcid 0
	if [ $? -eq 0 ]; then
		echo "FMAP clear after FLR"
	fi
	
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/qdma/qmax
	
	
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
	
	if [ $? -eq 0 ]; then
		echo "Test case 3 PASS"
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 3 -r "PASS"
	else
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 3 -r "FAIL"
	fi
	rmmod qdma-vf
	rmmod qdma-pf
	echo "**********TEST CASE 3 END *************"
}

# Add VFs to PF
# Add 10 Qs to the VF and start them
# Perform FLR on VF
# After FLR, verify that fmap programming is erased.
# Reprogram the FMAP for the VF
# Adding/starting Q and running traffic on the Q is working fine after the FLR
function execute_t4()
{
	echo "**********TEST CASE 4 START *************"
	insert_module pf
	insert_module vf
	
	echo "Adding ${num_vfs} VFs to PF"
	echo $num_vfs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo "Add and start ${num_qs} in VF"
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/qdma/qmax
	q_add_test $vf_funcid $num_qs
	q_start_test $vf_funcid $num_qs
	echo "Going for FLR of VF"
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/reset
	fmap_test $vf_funcid 0
	if [ $? -eq 0 ]; then
		echo "FMAP programming is cleared FLR"
	fi
	
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/qdma/qmax
	
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
	
	if [ $? -eq 0 ]; then
		echo "Test case 4 PASS"
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 4 -r "PASS"
	else
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 4 -r "FAIL"
	fi
	rmmod qdma-vf
	rmmod qdma-pf
	echo "**********TEST CASE 4 END *************"
}

# Test case 5
# Add 1 VF to PF
# Perform FLR on the PF
# FLR flow for both PF and VF should get triggered
function execute_t5()
{
	echo "**********TEST CASE 5 START *************"
	insert_module pf
	insert_module vf
	echo "Adding ${num_vfs} VFs to PF"
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/qdma/qmax
	echo "Going for FLR of PF"
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/reset
	fmap_test $pf_funcid 0
	if [ $? -eq 0 ]; then
		echo "FMAP programming is cleared FLR for PF"
	fi
	fmap_test $vf_funcid 0
	if [ $? -eq 0 ]; then
		echo "FMAP programming is cleared FLR for VF"
	fi
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
		
	fmap_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "FMAP programming successful after FLR for PF"
	fi
	q_add_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Add successful after FLR"
	fi
	q_start_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Start successful after FLR"
	fi
	dma-to-device -d /dev/${pf_funcid}-MM-0
	if [ $? -eq 0 ]; then
		echo "Test case 5 PASS"
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 5 -r "PASS"
	else
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 5 -r "FAIL"
	fi
	rmmod qdma-vf
	rmmod qdma-pf
	echo "**********TEST CASE 5 END *************"
}

# Test case 6
# Add 10 VFs to PF 
# Perform FLR on the PF
# FLR flow for both PF and all VFs should get triggered
function execute_t6()
{
	echo "**********TEST CASE 6 START *************"
	insert_module pf
	insert_module vf
	echo $num_vfs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo "Program ${num_qs} in FMAP for PF and VF"
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/qdma/qmax
	echo "Going for reset"
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/reset
	fmap_test $pf_funcid 0
	if [ $? -eq 0 ]; then
		echo "FMAP programming is cleared FLR for PF"
	fi
	fmap_test $vf_funcid 0
	if [ $? -eq 0 ]; then
		echo "FMAP programming is cleared FLR for VF"
	fi
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
		
	fmap_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "FMAP programming successful after FLR for PF"
	fi
	q_add_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Add successful after FLR"
	fi
	q_start_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Start successful after FLR"
	fi
	dma-to-device -d /dev/${pf_funcid}-MM-0
	if [ $? -eq 0 ]; then
		echo "Test case 6 PASS"
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 6 -r "PASS"
	else
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 6 -r "FAIL"
	fi
	rmmod qdma-vf
	rmmod qdma-pf
	echo "**********TEST CASE 6 END *************"
}

# Test case 7
# Add 1 VF to PF
# Add and start 10 Qs to the PF
# Perform FLR on the PF
# Verify that FLR of both PF and VF gets triggered
# Verify that FMAP programming of the PF and VF gets erased
# Verify that Adding, Starting and running traffic on Q works fine for PF
function execute_t7()
{
	echo "**********TEST CASE 7 START *************"
	insert_module pf
	insert_module vf
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo "Program ${num_qs} in FMAP for PF and VF"
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/qdma/qmax
	echo "Add and start Qs in PF"
	fmap_test $pf_funcid $num_qs
	q_add_test $pf_funcid $num_qs
	q_start_test $pf_funcid $num_qs
	
	echo "Going for reset"
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/reset
	fmap_test $pf_funcid 0
	if [ $? -eq 0 ]; then
		echo "FMAP programming is cleared FLR for PF"
	fi
	fmap_test $vf_funcid 0
	if [ $? -eq 0 ]; then
		echo "FMAP programming is cleared after FLR for VF"
	fi
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
		
	fmap_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "FMAP programming successful after FLR for PF"
	fi
	q_add_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Add successful after FLR for PF"
	fi
	q_start_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Start successful after FLR for PF"
	fi
	dma-to-device -d /dev/${pf_funcid}-MM-0
	if [ $? -eq 0 ]; then
		echo "Test case 7 PASS"
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 7 -r "PASS"
	else
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 7 -r "FAIL"
	fi
	rmmod qdma-vf
	rmmod qdma-pf
	echo "**********TEST CASE 7 END *************"
}

# Test case 8
# Add 1 VF to PF
# Add and start 10 Qs to the PF and VF
# Perform FLR on the PF
# Verify that FLR of both PF and VF gets triggered
# Verify that FMAP programming of the PF gets erased
# Verify that Adding, Starting and running traffic on Q works fine for PF
function execute_t8()
{
	echo "**********TEST CASE 8 START *************"
	insert_module pf
	insert_module vf
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo "Program ${num_qs} in FMAP for PF and VF"
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/qdma/qmax
	echo "Add and start Qs in PF"
	fmap_test $pf_funcid $num_qs
	q_add_test $pf_funcid $num_qs
	q_start_test $pf_funcid $num_qs
	
	echo "Add and start Qs in VF"
	fmap_test $vf_funcid $num_qs
	q_add_test $vf_funcid $num_qs
	q_start_test $vf_funcid $num_qs
	#dma-to-device -d /dev/${vf_funcid}-MM-0 -c 5000000 &
	echo "Going for reset of PF"
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/reset
	fmap_test $pf_funcid 0
	if [ $? -eq 0 ]; then
		echo "FMAP programming is cleared FLR for PF"
	fi
	fmap_test $vf_funcid 0
	if [ $? -eq 0 ]; then
		echo "FMAP programming is cleared FLR for VF"
	fi
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
		
	fmap_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "FMAP programming successful after FLR for PF"
	fi
	q_add_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Add successful after FLR for PF"
	fi
	q_start_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Start successful after FLR for PF"
	fi
	dma-to-device -d /dev/${pf_funcid}-MM-0
	if [ $? -eq 0 ]; then
		echo "Test case 8 PASS"
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 8 -r "PASS"
	else
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 8 -r "FAIL"
	fi
	rmmod qdma-vf
	rmmod qdma-pf
	echo "**********TEST CASE 8 END *************"
}

# Test Case 9
# Add 10 VF to each PF
# Add and start 10 Qs to each VF and PF
# Perform FLR on the PF
# Verify that FLR of both PF and VF gets triggered
# Verify that FMAP programming of the PF and VF gets erased
# Verify that Adding, Starting and running traffic on Q works fine for PF after FLR
# rmmod of qdma_vf.ko and qdma.ko should work fine. 

function execute_t9()
{
	echo "**********TEST CASE 9 START *************"
	insert_module pf
	insert_module vf
	echo "Adding VFs on each PF"
	echo $num_vfs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo $num_vfs > /sys/bus/pci/devices/0000\:${bus_id}\:00.1/sriov_numvfs
	echo $num_vfs > /sys/bus/pci/devices/0000\:${bus_id}\:00.2/sriov_numvfs
	echo $num_vfs > /sys/bus/pci/devices/0000\:${bus_id}\:00.3/sriov_numvfs
	i=0
	echo "Adding VFs complete, progrmming queues for VFs on PF0"
	while [ $i -lt $num_vfs ]
	do
		
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/virtfn${i}/qdma/qmax
		i=`expr $i + 1`
	done
	i=0
	
	while [ $i -lt $num_vfs ]
	do		
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.1/virtfn${i}/qdma/qmax
		i=`expr $i + 1`
	done
	i=0
	
	while [ $i -lt $num_vfs ]
	do		
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.2/virtfn${i}/qdma/qmax
		i=`expr $i + 1`
	done
	i=0
	
	while [ $i -lt $num_vfs ]
	do
		
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.3/virtfn${i}/qdma/qmax
		i=`expr $i + 1`
	done
	i=0
	echo "Adding VFs complete, progrmming queues for all VFs"
	while [ $i -lt $num_vfs ]
	do
		i=`expr $i + 1`
		dd=`dma-ctl dev list | grep qdmavf | sed ''"${i}"','"${i}"'!d' | cut -d ":" -f 3 | cut -d "." -f 1`
		ff=`dma-ctl dev list | grep qdmavf | sed ''"${i}"','"${i}"'!d' | cut -d ":" -f 3 | cut -d "." -f 2 | cut -f 1` 
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:${dd}.${ff}/qdma/qmax
		vf_funcid=qdmavf${bus_id}${dd}${ff}
		fmap_test $vf_funcid $num_qs
		q_add_test $vf_funcid $num_qs
		q_start_test $vf_funcid $num_qs		
	done
	
	
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/reset
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
		
	fmap_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "FMAP programming successful after FLR for PF0"
	fi
	q_add_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Add successful after FLR for PF0"
	fi
	q_start_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Start successful after FLR for PF0"
	fi
	dma-to-device -d /dev/${pf_funcid}-MM-0
	
	if [ $? -eq 0 ]; then
		echo "FLR of other PFs"
		echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.1/reset
		echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.2/reset
		echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.3/reset
		
		echo "dma-ctl dev list o/p after FLR of all PFs"
		dma-ctl dev list
		dma-to-device -d /dev/${pf_funcid}-MM-0
		if [ $? -eq 0 ]; then
			echo "Test case 9 PASS"
			python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 9 -r "PASS"
		else
			python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 9 -r "FAIL"
		fi
		
	else
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 9 -r "FAIL"
	fi
	rmmod qdma-vf
	rmmod qdma-pf
	echo "**********TEST CASE 9 END *************"
}


# Test case 10
# Add 1 VF on PF
# Perform an rmmod of the PF
# Perform rmmod of the VF
# QMAX programming , Add/start Q for both the VF and the PF should work fine  

function execute_t10()
{
	echo "**********TEST CASE 10 START *************"
	insert_module pf
	insert_module vf
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo "Removing the PF driver"
	rmmod qdma-pf
	rmmod qdma-vf
	insert_module pf
	insert_module vf
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
	pf_funcid=qdma${bus_id}000
	fmap_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "FMAP programming successful after PF Offline for PF"
	fi
	q_add_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Add successful after PF Offline for PF"
	fi
	q_start_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Start successful after PF Offline for PF"
	fi
	
	dma-to-device -d /dev/${pf_funcid}-MM-0
	if [ $? -eq 0 ]; then
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/qdma/qmax
		vf_funcid=qdmavf${bus_id}004
		fmap_test $vf_funcid $num_qs
		if [ $? -eq 0 ]; then
			echo "FMAP programming successful after PF Offline for VF"
		fi
		q_add_test $vf_funcid $num_qs
		if [ $? -eq 0 ]; then
			echo "Q Add successful after PF Offline for VF"
		fi
		q_start_test $vf_funcid $num_qs
		if [ $? -eq 0 ]; then
			echo "Q Start successful after PF Offline for VF"
		fi
		dma-to-device -d /dev/${vf_funcid}-MM-0
		if [ $? -eq 0 ]; then
			echo "Test case 10 PASS"
			python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 10 -r "PASS"
		else
			python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 10 -r "FAIL"
		fi
	else
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 10 -r "FAIL"
	fi
	
	rmmod qdma-vf
	rmmod qdma-pf
	echo "**********TEST CASE 10 END   *************"
}

# Test Case 11
# Add 1 VF on PF0
# Add 10 Qs to the PF and VF.
# Remove the PF driver
# Observe that the PF driver is removed without any errors
# Observe that the VF is not listed anymore and the VF driver is loaded.
# Re-insert the PF driver and mount VF on it 
# VF driver should be able to attach to the VF added.
# Addition of Qs, starting of Qs and running of traffic on both the PF and the VF should run as expected
function execute_t11()
{
	echo "**********TEST CASE 11 START *************"
	insert_module pf
	insert_module vf
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/qdma/qmax
	pf_funcid=qdma${bus_id}000
	vf_funcid=qdmavf${bus_id}004
	fmap_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "FMAP programming successful PF"
	fi
	q_add_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Add successful for PF"
	fi
	q_start_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Start successful for PF"
	fi
	fmap_test $vf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "FMAP programming successful for VF"
	fi
	q_add_test $vf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Add successful for VF"
	fi
	q_start_test $vf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Start successful for VF"
	fi
	
	echo "Removing the PF driver"
	rmmod qdma-pf
	rmmod qdma-vf
	insert_module pf
	insert_module vf
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
	fmap_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "FMAP programming successful after PF Offline for PF"
	fi
	q_add_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Add successful after PF Offline for PF"
	fi
	q_start_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Start successful after PF Offline for PF"
	fi
	
	dma-to-device -d /dev/${pf_funcid}-MM-0
	if [ $? -eq 0 ]; then
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/qdma/qmax
		vf_funcid=qdmavf${bus_id}004
		fmap_test $vf_funcid $num_qs
		if [ $? -eq 0 ]; then
			echo "FMAP programming successful after PF Offline for VF"
		fi
		q_add_test $vf_funcid $num_qs
		if [ $? -eq 0 ]; then
			echo "Q Add successful after PF Offline for VF"
		fi
		q_start_test $vf_funcid $num_qs
		if [ $? -eq 0 ]; then
			echo "Q Start successful after PF Offline for VF"
		fi
		dma-to-device -d /dev/${vf_funcid}-MM-0
		if [ $? -eq 0 ]; then
			echo "Test case 11 PASS"
			python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 11 -r "PASS"
		else
			python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 11 -r "FAIL"
		fi
	else
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 11 -r "FAIL"
	fi
	
	rmmod qdma-vf
	rmmod qdma-pf
	echo "**********TEST CASE 11 END   *************"
}

# Test case 12
# Add 10 VFs to each PF
# rmmod the PF 
# Observe that all the VFs added are removed
# Insert the PF driver again and mount 1 VF on each PF again
# Addition/starting of Qs and running traffic on both the PF and VF should work as expected.

function execute_t12() 
{
	echo "**********TEST CASE 12 START *************"
	insert_module pf
	insert_module vf
	echo "Adding VFs on each PF"
	echo $num_vfs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo $num_vfs > /sys/bus/pci/devices/0000\:${bus_id}\:00.1/sriov_numvfs
	echo $num_vfs > /sys/bus/pci/devices/0000\:${bus_id}\:00.2/sriov_numvfs
	echo $num_vfs > /sys/bus/pci/devices/0000\:${bus_id}\:00.3/sriov_numvfs
	i=0
	echo "Adding VFs complete, progrmming queues for VFs on PF0"
	while [ $i -lt $num_vfs ]
	do
		
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/virtfn${i}/qdma/qmax
		i=`expr $i + 1`
	done
	i=0
	echo "Adding VFs complete, progrmming queues for VF on PF1"
	while [ $i -lt $num_vfs ]
	do
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.1/virtfn${i}/qdma/qmax
		i=`expr $i + 1`
	done
	i=0
	echo "Adding VFs complete, progrmming queues for VF on PF2"
	while [ $i -lt $num_vfs ]
	do		
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.2/virtfn${i}/qdma/qmax
		i=`expr $i + 1`
	done
	i=0
	echo "Adding VFs complete, progrmming queues for VF on PF3"
	while [ $i -lt $num_vfs ]
	do		
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.3/virtfn${i}/qdma/qmax
		i=`expr $i + 1`
	done
	i=0
	total_vfs=`expr $num_vfs \\* 4`
	while [ $i -lt $total_vfs ]
	do
		i=`expr $i + 1`
		dd=`dma-ctl dev list | grep qdmavf | sed ''"${i}"','"${i}"'!d' | cut -d ":" -f 3 | cut -d "." -f 1`
		ff=`dma-ctl dev list | grep qdmavf | sed ''"${i}"','"${i}"'!d' | cut -d ":" -f 3 | cut -d "." -f 2 | cut -f 1` 
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:${dd}.${ff}/qdma/qmax
		vf_funcid=qdmavf${bus_id}${dd}${ff}
		fmap_test $vf_funcid $num_qs
		q_add_test $vf_funcid $num_qs
		q_start_test $vf_funcid $num_qs		
	done
	
	dma-ctl dev list

	echo "Removing the PF driver"
	rmmod qdma-pf
	rmmod qdma-vf
	insert_module pf
	insert_module vf
	echo 1 > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/sriov_numvfs
	echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.0/qdma/qmax
	fmap_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "FMAP programming successful after PF Offline for PF"
	fi
	q_add_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Add successful after PF Offline for PF"
	fi
	q_start_test $pf_funcid $num_qs
	if [ $? -eq 0 ]; then
		echo "Q Start successful after PF Offline for PF"
	fi
	
	dma-to-device -d /dev/${pf_funcid}-MM-0
	if [ $? -eq 0 ]; then
		echo $num_qs > /sys/bus/pci/devices/0000\:${bus_id}\:00.4/qdma/qmax
		vf_funcid=qdmavf${bus_id}004
		fmap_test $vf_funcid $num_qs
		if [ $? -eq 0 ]; then
			echo "FMAP programming successful after PF Offline for VF"
		fi
		q_add_test $vf_funcid $num_qs
		if [ $? -eq 0 ]; then
			echo "Q Add successful after PF Offline for VF"
		fi
		q_start_test $vf_funcid $num_qs
		if [ $? -eq 0 ]; then
			echo "Q Start successful after PF Offline for VF"
		fi
		dma-to-device -d /dev/${vf_funcid}-MM-0
		if [ $? -eq 0 ]; then
			echo "Test case 12 PASS"
			python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 12 -r "PASS"
		else
			python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 12 -r "FAIL"
		fi
	else
		python qdma_linux_gen_flr_pf_offline_test.py -o $opfile -u Result -m $drv_mode_string -i 12 -r "FAIL"
	fi
	
	rmmod qdma-vf
	rmmod qdma-pf
}
execute_t1
execute_t2
execute_t3
execute_t4
execute_t5
execute_t6
execute_t7
execute_t8
execute_t9
execute_t10
execute_t11
execute_t12
