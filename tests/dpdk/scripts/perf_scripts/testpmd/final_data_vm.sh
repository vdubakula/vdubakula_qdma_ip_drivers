#!/bin/sh

final_queue_distribution=$(echo $1 | tr "," "\n")
# echo "final_queue_distribution = "$final_queue_distribution""

for val in $final_queue_distribution
do
	for i  in `grep "MIN" test_lat$val.csv`
	do
		echo -n $i >> testpmd.csv
	done
	echo "" >> testpmd.csv
done

for val in $final_queue_distribution
do
    for i  in `grep "Average" test_lat$val.csv`
        do
            echo -n $i >> testpmd.csv
        done
	echo "" >> testpmd.csv
done

for val in $final_queue_distribution
do
	for i  in `grep "MAX" test_lat$val.csv`
	do
		echo -n $i >> testpmd.csv
	done
	echo "" >> testpmd.csv
done
for val in $final_queue_distribution
do
	for i  in `grep "Packet" test_lat$val.csv`
	do
		echo -n $i >> testpmd.csv
	done
	echo "" >> testpmd.csv
done
echo "" >> testpmd.csv

echo "Final data in testpmd.csv"

