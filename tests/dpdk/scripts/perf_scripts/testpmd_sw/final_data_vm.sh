#!/bin/sh

final_queue_distribution=$(echo $1 | tr "," "\n")
# echo "final_queue_distribution = "$final_queue_distribution""

for val in $final_queue_distribution
do
	for i  in `grep "Rx-pps" test_lat$val.csv`
	do
		echo -n $i >> testpmd.csv
	done
	echo "" >> testpmd.csv
done

for val in $final_queue_distribution
do
    for i  in `grep "Tx-pps" test_lat$val.csv`
        do
            echo -n $i >> testpmd.csv
        done
	echo "" >> testpmd.csv
done

for val in $final_queue_distribution
do
	for i  in `grep "Rx-bps" test_lat$val.csv`
	do
		echo -n $i >> testpmd.csv
	done
	echo "" >> testpmd.csv
done
for val in $final_queue_distribution
do
	for i  in `grep "Tx-bps" test_lat$val.csv`
	do
		echo -n $i >> testpmd.csv
	done
	echo "" >> testpmd.csv
done
echo "" >> testpmd.csv

echo "Final data in testpmd.csv"

