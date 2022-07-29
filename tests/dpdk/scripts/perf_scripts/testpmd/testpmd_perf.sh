#!/bin/sh
echo "using device $1"
addr=`lspci -vv -s $1 | grep "Region 2" | grep "size" | awk '{print $5}'`
addr_cfg=`lspci -vv -s $1 | grep "Region 0" | grep "size" | awk '{print $5}'`
addr="0x$addr"
addr_cfg="0x$addr_cfg"
echo "cfg BAR addr is $addr_cfg"
echo "pkt gen addr is $addr"
export PKT_GEN_ADDR=$addr
version_addr=$(( addr_cfg+0x134 ))
version=`./PCIeWriter/rwmem $version_addr`
version=`echo $version | sed 's/.*= 0x*\([a-z0-9]*\).*/\1/'`
version="0x$version"
echo "version is $version"
bit1=$(( version>>20 ))
bit1=$(( bit1&0x1 ))
bit2=$(( version>>24 ))
bit2=$(( bit2&0x1 ))
bit2=$(( ! $bit2 ))
is_eqdma=$(( bit1&bit2 ))
echo "is_eqdma is $is_eqdma"
for var in "$@"
do
	if [ "$var" = "$1" ] || [ "$var" = "$3" ];
	then
		continue
	fi

	desc=`echo $var | awk -F '_' '{print $1}'`
	pfch=`echo $var | awk -F '_' '{print $2}'`

	desc_addr=$(( addr+0x50 ))
	reset_addr=$(( addr+0x08 ))
	./PCIeWriter/rwmem $desc_addr $(( desc/16 ))
#	./PCIeWriter/rwmem $reset_addr 0x80000000
	./PCIeWriter/rwmem $reset_addr 0x120000
	echo "Writing $(( desc/16 )) at addr 16#$desc_addr"

	echo "Descriptor len = $desc Prefetch enable = $pfch"
	echo "Descriptor len = $desc Prefetch enable = $pfch"

	online_cpus=`nproc`
	./perf_testpmd.expect $1 $desc $pfch $addr $3 $online_cpus $is_eqdma
	sleep 1
	mv test.csv testpmd_$desc$pfch.csv
done
