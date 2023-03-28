#!/bin/bash

n=$1
while [ $n -gt 0 ]
do
	for i  in `grep "Rx-pps" test_lat$n.csv`
	do
		echo -n $i >> test.csv
	done
	echo "" >> test.csv
	let n=$((n/2))
done
	echo "" >> test.csv
n=$1
while [ $n -gt 0 ]
do
        for i  in `grep "Tx-pps" test_lat$n.csv`
        do
                echo -n $i >> test.csv
        done
	echo "" >> test.csv
	let n=$((n/2))
done
	echo "" >> test.csv
n=$1
while [ $n -gt 0 ]
do
        for i  in `grep "Rx-bps" test_lat$n.csv`
        do
                echo -n $i >> test.csv
        done
	echo "" >> test.csv
	let n=$((n/2))
done
	echo "" >> test.csv
n=$1
while [ $n -gt 0 ]
do
        for i  in `grep "Tx-bps" test_lat$n.csv`
        do
                echo -n $i >> test.csv
        done
	echo "" >> test.csv
	let n=$((n/2))
done
	echo "" >> test.csv

echo "Final data in result_testpmd.csv"
