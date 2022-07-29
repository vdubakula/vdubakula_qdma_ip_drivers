#!/bin/sh
num_queue=$2
echo "using device $1"
addr=`lspci -vv -s $1 | grep "Region 2" | grep "size" | awk '{print $5}'`
echo "pkt gen addr is $addr"
export PKT_GEN_ADDR=$addr
for var in "$@"
do
	if [ "$var" = "$1" ]
	then
		continue
	elif [ "$var" = "$2" ]
	then
		continue
	elif [ "$var" = "$3" ]
	then
		echo "desc_pfch = $var, H2C will be executed"
		export RUN_H2C=1
	else
		echo "desc_pfch = $var, H2C will not be executed"
		export RUN_H2C=0
	fi

	desc=`echo $var | awk -F '_' '{print $1}'`
	pfch=`echo $var | awk -F '_' '{print $2}'`
	echo "Descriptor len = $desc Prefetch enable = $pfch"
	addr1="0x$addr"
	desc_addr=$(( addr1+0x50 ))
	./devmem $desc_addr w $(( desc/16 ))

	c2=$(( $num_queue + 1 ))
	c3=$(( c2 + 1 ))
	c4=$(( c2 + $num_queue ))

	echo "Starting Measurement for $num_queue Queues"
	echo "Running on cores [2-$c2:$c3-$c4].0"
	./launch_pktgen_vm.expect $1 $desc $pfch $c2 $c3 $c4 > output_$var$num_queue
	dos2unix -f output_$var$num_queue
	sleep 1

	echo "" > test_$var_$num_queue.csv

	echo -n "mstb_tx_$num_queue," >> test_$var_$num_queue.csv
	for i  in `grep "mbits_tx" output_$var$num_queue | awk  '{print $3}'`
	do
		echo -n $i >> test_$var_$num_queue.csv
	done
	echo "" >> test_$var_$num_queue.csv


	echo -n "mstb_rx_$num_queue," >> test_$var_$num_queue.csv
	for i  in `grep "mbits_rx" output_$var$num_queue | awk  '{print $3}'`
	do
		echo -n $i >> test_$var_$num_queue.csv
	done
	echo "" >> test_$var_$num_queue.csv
done
