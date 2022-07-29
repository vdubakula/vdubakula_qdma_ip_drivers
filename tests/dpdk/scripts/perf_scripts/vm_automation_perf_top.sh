#!/bin/sh

init=0
declare -a host_queue_dist
declare -a vm_queue_dist

testpmd_queue_distribution=$(echo $7)
echo "testpmd queue distribution: "${testpmd_queue_distribution}""

pktgen_queue_distribution=$(echo $8 | tr " " "\n")
pktgen_vm_queue_distribution=$(echo $9 | tr " " "\n")
i=0
for val in $pktgen_queue_distribution
do
	host_queue_dist[i]=$val
	i=$(( i + 1 ))
done
i=0
for val in $pktgen_vm_queue_distribution
do
	vm_queue_dist[i]=$val
	i=$(( i + 1 ))
done
#Get length of arrays
len_host="${#host_queue_dist[*]}"
len_vm="${#vm_queue_dist[*]}"

if (("$len_host" != "$len_vm"))
then
	echo "Invalid queue distribution";
	exit
fi
echo "${11}"
echo "${12}"
if (( $4 == 1 ))
then
	python VM_Perf_automation.py $1 $2 $3 $4 $init $6 "$testpmd_queue_distribution" ${host_queue_dist[0]} ${vm_queue_dist[0]} ${10} ${11} ${12} ${13}
fi

if (( $5 == 1 ))
then
	for (( i=0; i < len_host; i++ ))
	do
		# python VM_Perf_automation.py $1 $2 $3 $init $5 $6 "${testpmd_queue_distribution}" ${host_queue_dist[i]} ${vm_queue_dist[i]} ${10} ${11} ${12}
		python VM_Perf_automation.py $1 $2 $3 $init $5 $6 "${testpmd_queue_distribution}" ${host_queue_dist[i]} ${vm_queue_dist[i]} ${10} ${11} ${12} ${13}
	done
fi
