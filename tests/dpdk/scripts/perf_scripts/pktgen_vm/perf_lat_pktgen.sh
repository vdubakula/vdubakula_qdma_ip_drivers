#!/bin/sh
usrbarctrl=$(($1 + 0x8))
usrbarpktsize=$(($1 + 0x90))
echo $usrbarctrl $usrbarpktsize
./PCIeWriter/rwmem $usrbarpktsize 64
./PCIeWriter/rwmem $usrbarctrl 0x120000
sleep 5
n=64
while [ $n -le 4097 ]
do
	./PCIeWriter/rwmem $usrbarpktsize $n
	echo "perf_lat_pktgen:Data size = $n"
	sleep 25
	let n=$n+64
done
sleep 10
./PCIeWriter/rwmem $usrbarctrl 0x240000
#./PCIeWriter/rwmem $usrbarpktsize 32
# Dummy updation of packet size for H2C syncronization across vms
n=64
while [ $n -le 4097 ]
do
	./PCIeWriter/rwmem $usrbarpktsize $n
	echo "perf_lat_pktgen:Data size = $n"
	sleep 40
	let n=$n+64
done
./PCIeWriter/rwmem $usrbarctrl 0x240000
./PCIeWriter/rwmem $usrbarpktsize 64
echo "Perf_Lat_pktgen:Done!!"
