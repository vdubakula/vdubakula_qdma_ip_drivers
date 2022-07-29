#!/bin/sh
usrbarctrl=$(($2 + 0x8))
usrbarpktsize=$(($2 + 0x90))
echo $usrbarctrl $usrbarpktsize
./PCIeWriter/rwmem $usrbarpktsize 64
#./PCIeWriter/rwmem $usrbarctrl 0x120000
sleep 2
n=64
while [ $n -le 4097 ]
do
	./PCIeWriter/rwmem $usrbarpktsize $n
	sleep 15
	echo "****latency for $n" >> latency_report$1
	./latency_measure.sh $2 >> latency_report$1
	let n=$n+64
done
echo -n "MIN Latency," >> test_lat$1.csv
for i  in `grep "Min" latency_report$1 | awk  '{print $5}'`
do
	echo -n $i',' >> test_lat$1.csv
done

echo "" >> test_lat$1.csv

echo -n "Average latency," >> test_lat$1.csv
for i  in `grep "Average" latency_report$1 | awk  '{print $5}'`
do
	echo -n $i',' >> test_lat$1.csv
done

echo "" >> test_lat$1.csv

echo -n "MAX latency," >> test_lat$1.csv
for i  in `grep "MAX" latency_report$1 | awk  '{print $5}'`
do
	echo -n $i',' >> test_lat$1.csv
done
echo "" >> test_lat$1.csv

echo -n "Packet per second," >> test_lat$1.csv
for i  in `grep "total" latency_report$1 | awk  '{print $4}'`
do
	echo -n $i',' >> test_lat$1.csv
done

echo "" >> test_lat$1.csv
echo "all set!!"
#./PCIeWriter/rwmem $usrbarctrl 0x240000