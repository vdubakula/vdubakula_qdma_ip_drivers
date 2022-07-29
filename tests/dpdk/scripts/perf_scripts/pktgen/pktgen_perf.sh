#!/bin/sh
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
	reset_addr=$(( addr1+0x08 ))
	./devmem $desc_addr w $(( desc/16 ))
	./devmem $reset_addr w 0x80000000

	for n in 8 4 2 1
	do
		c2=$(( n + 1 ))
		c3=$(( c2 + 1 ))
		c4=$(( c2 + n ))

		echo "Starting Measurement for $n Queues"
		echo "Running on cores [2-$c2:$c3-$c4].0"
		./launch_pktgen.expect $1 $desc $pfch $c2 $c3 $c4 > output_$var$n
		dos2unix -f output_$var$n
		sleep 1
	done

	echo "" > test_$var.csv
	for n in 8 4 2 1
	do
		echo -n "mstb_tx_$n," >> test_$var.csv
		for i  in `grep "mbits_tx" output_$var$n | awk  '{print $3}'`
		do
			echo -n $i >> test_$var.csv
		done
		echo "" >> test_$var.csv
	done
	for n in 8 4 2 1
	do

		echo -n "mstb_rx_$n," >> test_$var.csv
		for i  in `grep "mbits_rx" output_$var$n | awk  '{print $3}'`
		do
			echo -n $i >> test_$var.csv
		done
		echo "" >> test_$var.csv
	done
done
