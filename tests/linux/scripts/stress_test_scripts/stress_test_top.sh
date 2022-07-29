#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Invalid arguements."
	echo "$0 <bbddf> [<test mask>] [<total execution time>] [<pf_vf|pf|vf>]"
	exit;
fi;

dm_pid=

kill_dmesg_dump()
{
	kill -9 ${dm_pid}
}



bdf=01000
num_qs=2048
num_pfs=4
override_pf_nvf=0
target="pf_vf"
if [ ! -z $1 ]; then
	bdf=$1
fi
test_mask=0x0f
if [ ! -z $2 ]; then
	test_mask=$2
fi
run_time="04:00:00"
if [ ! -z $3 ]; then
	run_time=$3
fi
if [ ! -z $4 ]; then
	num_qs=$4
fi
if [ ! -z $5 ]; then
	override_pf_nvf=$5
fi
if [ ! -z $6 ]; then
	if [[ $6 == "pf_vf" || $6 == "pf" || $6 == "vf" ]]; then
		target=$6
	fi
fi
timestamp=$(date +%Y-%m-%d-%H-%M)
test_report=stress_test_report_$timestamp.xlsx
cp stress_test_report_template.xlsx $test_report
dmesg -w > dmesg_log_${timestamp}.log &
dm_pid=$!
trap kill_dmesg_dump EXIT
cd ../../../../sw_host/linux/
./make_libqdma.sh clean
./make_libqdma.sh
make install-apps
make install-mods
make install-dev

case $target in
  "vf")
    dmactl dev list
    ;;

  pf | pf_vf)
	modprobe qdma-pf
	echo ${bdf}
	dma-ctl qdma${bdf} reg write bar 2 0xA0 0x01
	rmmod qdma-pf
    ;;
esac
cd -

function cleanup_env()
{
	if [[ ( "$target" == "vf" ) || ( "$target" == "pf_vf" ) ]]; then
		rmmod qdma-vf
	fi
	if [[ ( "$target" == "pf" ) || ( "$target" == "pf_vf" ) ]]; then
		rmmod qdma-pf
	fi
}

function run_stress_test()
{
	drv_mode=0
	conf_file="qdma.conf"
	pci_bus=${bdf:0:2}
	if [ $1 == poll ]; then
		echo -n "options qdma-pf mode=" > conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:1" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	
		done
		echo -e "" >> conf_file
		echo -n "options qdma-pf config_bar=" >> conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:0" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	 
		done
		echo -e "" >> conf_file
		echo -n "options qdma-pf master_pf=0x${pci_bus}:0" >> conf_file
		echo -e "" >> conf_file
		echo -n "options qdma-vf mode=" >> conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:1" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	
		done
		echo -e "" >> conf_file
		echo -n "options qdma-vf config_bar=" >> conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:0" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	 
		done
	elif [ $1 == intr ]; then
		echo -n "options qdma-pf mode=" > conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:2" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	
		done
		echo -e "" >> conf_file
		echo -n "options qdma-pf config_bar=" >> conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:0" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	 
		done
		echo -e "" >> conf_file
		echo -n "options qdma-pf master_pf=0x${pci_bus}:0" >> conf_file
		echo -e "" >> conf_file
		echo -n "options qdma-vf mode=" >> conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:2" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	
		done
		echo -e "" >> conf_file
		echo -n "options qdma-vf config_bar=" >> conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:0" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	 
		done
	elif [ $1 == aggr ]; then
		echo -n "options qdma-pf mode=" > conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:3" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	
		done
		echo -e "" >> conf_file
		echo -n "options qdma-pf config_bar=" >> conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:0" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	 
		done
		echo -e "" >> conf_file
		echo -n "options qdma-pf master_pf=0x${pci_bus}:0" >> conf_file
		echo -e "" >> conf_file
		echo -n "options qdma-vf mode=" >> conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:3" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	
		done
		echo -e "" >> conf_file
		echo -n "options qdma-vf config_bar=" >> conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:0" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	 
		done
	else
		echo -n "options qdma-pf mode=" > conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:0" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	
		done
		echo -e "" >> conf_file
		echo -n "options qdma-pf config_bar=" >> conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:0" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	 
		done
		echo -e "" >> conf_file
		echo -n "options qdma-pf master_pf=0x${pci_bus}:0" >> conf_file
		echo -e "" >> conf_file
		echo -n "options qdma-vf mode=" >> conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:0" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	
		done
		echo -e "" >> conf_file
		echo -n "options qdma-vf config_bar=" >> conf_file
		for ((j = 0; j < ${num_pfs}; j++))
		do
			echo -n "0x${pci_bus}:${j}:0" >> conf_file
			if [ $j != $((${num_pfs} - 1)) ]; then
				echo -n "," >> conf_file
			fi	 
		done
	fi
	rm -rf /etc/modprobe.d/qdma.conf
	cp conf_file /etc/modprobe.d/qdma.conf
	rm -rf conf_file
	cd ../../../../sw_host/linux/
	make install-mods
	if [[ ( "$target" == "pf" ) || ( "$target" == "pf_vf" ) ]]; then
		modprobe qdma-pf
	fi
	if [[ ( "$target" == "vf" ) || ( "$target" == "pf_vf" ) ]]; then
		modprobe qdma-vf
	fi
	cd -
	chmod +x qdma_run_stress_test.sh
	./qdma_run_stress_test.sh $bdf $num_qs $run_time $override_pf_nvf $1 0 0 0 $test_report $target
	if [[ ( "$target" == "vf" ) || ( "$target" == "pf_vf" ) ]]; then
		rmmod qdma-vf
	fi
	if [[ ( "$target" == "pf" ) || ( "$target" == "pf_vf" ) ]]; then
		dma-ctl qdma$bdf reg write bar 2 0xA0 0x01
	fi
	if [[ ( "$target" == "pf" ) || ( "$target" == "pf_vf" ) ]]; then
		rmmod qdma-pf
	fi
	cd ../../../../sw_host/linux/
	make uninstall-mods
	cd -
}

trap cleanup_env EXIT

if (( test_mask & 0x02 )); then
	run_stress_test poll
fi
if (( test_mask & 0x04 )); then
	run_stress_test intr
fi
if (( test_mask & 0x08 )); then
	run_stress_test aggr
fi
if (( test_mask & 0x01 )); then
	run_stress_test auto
fi

