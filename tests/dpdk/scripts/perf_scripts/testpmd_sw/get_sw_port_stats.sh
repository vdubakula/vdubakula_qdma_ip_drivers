#!/bin/bash

echo -n "Rx-pps," >> test_lat$1.csv
for i  in `grep "Rx-pps:" sw_port_stats$1 | awk '{ sub("\r$", ""); print $2}'`
do
	echo -n $i',' >> test_lat$1.csv
done

echo "" >> test_lat$1.csv

echo -n "Tx-pps," >> test_lat$1.csv
for i  in `grep "Tx-pps:" sw_port_stats$1 | awk  '{ sub("\r$", ""); print $2}'`
do
	echo -n $i',' >> test_lat$1.csv
done

echo "" >> test_lat$1.csv

echo -n "Rx-bps," >> test_lat$1.csv
for i  in `grep "Rx-bps:" sw_port_stats$1 | awk '{ sub("\r$", ""); print $4}'`
do
	echo -n $i',' >> test_lat$1.csv
done
echo "" >> test_lat$1.csv

echo -n "Tx-bps," >> test_lat$1.csv
for i  in `grep "Tx-bps:" sw_port_stats$1 | awk  '{ sub("\r$", ""); print $4}'`
do
	echo -n $i',' >> test_lat$1.csv
done

echo "" >> test_lat$1.csv
echo "SW port statistics collected for queues: $1"