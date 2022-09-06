#!/bin/bash

if [ $# -lt 4 ]; then
	echo "Invalid arguements."
	echo "$0 <bdf> <num_vfs> <mode_mask> <num_qs> [bitstream file] [device type]"
	exit;
fi

bdf=01000
if [ ! -z $1 ]; then
	bdf=$1
fi

num_vfs=10
if [ ! -z $2 ]; then
	num_vfs=$2
fi

mode_mask=0x0f
if [ ! -z $3 ]; then
	mode_mask=$3
fi

num_qs=10
if [ ! -z $4 ]; then
	num_qs=$4
fi

bitstream="unknown"
if [ ! -z $5 ]; then
	bitstream=$5
fi

device_type="unknown"
if [ ! -z $6 ]; then
	device_type=$6
fi

rmmod *.ko

dm_pid=

kill_dmesg_dump()
{
	kill -9 ${dm_pid}
}

cd ../../../../drivers/linux/
./make_libqdma.sh clean
./make_libqdma.sh
make install-apps
make install-dev
make install-mods
modprobe qdma_pf
dma-ctl qdma${bdf} reg write bar 2 0xA0 0x01
driver_version=`dma-ctl qdma${bdf} cap | grep "qdma driver version" | cut -d ":" -f2`
rmmod qdma_pf
cd -
test_date=$(date +%d-%m-%Y)
timestamp=$(date +%Y-%m-%d-%H-%M)
test_report=flr_pf_offline_test_report_${timestamp}.xlsx
cp flr_pf_offline_test_report_template.xlsx $test_report
python qdma_linux_gen_flr_pf_offline_test.py -o $test_report -u Overview -n $num_vfs -q $num_qs -v $driver_version -d $test_date -b $bitstream -t $device_type

dmesg -w > dmesg_log_${timestamp}.log &
dm_pid=$!
trap kill_dmesg_dump EXIT


function run_flr_test()
{
	drv_mode=0
	if [ $1 == poll ]; then
		drv_mode=1
	elif [ $1 == intr ]; then
		drv_mode=2
	elif [ $1 == aggr ]; then
		drv_mode=3
	else
		drv_mode=0
	fi
	chmod +x qdma_run_flr_pf_offline_test.sh
	./qdma_run_flr_pf_offline_test.sh $bdf $num_qs $num_vfs $drv_mode $test_report
}

if (( mode_mask & 0x02 )); then
	echo "************         FLR Tests for Poll Mode Begin                ************"
	run_flr_test poll
	echo "************         FLR Tests for Poll Mode End                  ************"
fi

if (( mode_mask & 0x04 )); then
	echo "************         FLR Tests for Direct Interrupt Mode Begin    ************"
	run_flr_test intr
	echo "************         FLR Tests for Direct Interrupt Mode End      ************"
fi

if (( mode_mask & 0x08 )); then
	echo "************         FLR Tests Tests for Interrupt Aggr Mode Begin      ************"
	run_flr_test aggr
	echo "************         FLR Tests Tests for Interrupt Aggr Mode End        ************"
fi

if (( mode_mask & 0x01 )); then
	echo "************         FLR Tests Tests for Auto Mode Begin                  ************"
	run_flr_test auto
	echo "************         FLR Tests Tests for Auto Mode End                  ************"
fi

cd ../../../../drivers/linux/
make uninstall-mods
cd -
