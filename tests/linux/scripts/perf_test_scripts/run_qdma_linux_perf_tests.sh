#!/bin/bash

echo "Usage: $0 <master bbddf> <src_dir> <cfg_dir> <out_dir>"

bbddf=0200
if [ ! -z $1 ]; then
	bbddf=$1
fi;
pci_bus=${bbddf:0:2}

src_dir=${PWD}../../../../drivers/linux/
if [ ! -z $2 ]; then
	src_dir=${PWD}/../../../../$2 #path w.r.t HEAD
fi;

cfg_dir="dmaperf_configs"
if [ ! -z $3 ]; then
	cfg_dir=$3
fi;

testname="default"
if [ ! -z $4 ]; then
	testname=$4
fi;

runtime=10
if [ ! -z $5 ]; then
	runtime=$5
fi;

bidir_en=1
if [ ! -z $6 ]; then
	bidir_en=$6
fi;

count=1
if [ ! -z $7 ]; then
	count=$7
fi;

burst_size=64
if [ ! -z $8 ]; then
	burst_size=$8
fi;

marker_en=1
if [ ! -z $9 ]; then
	marker_en=$9
fi;

vf_perf=0
if [ ! -z ${10} ]; then
	vf_perf=${10}
fi;

cpm5_flag=""
ptest_args=( "$@" )

for (( i=0; i<${#ptest_args[@]}; i++ ));
do
        if [[ ${ptest_args[$i]} == "CPM5" ]]; then
                cpm5_flag=CPM5
        fi
        if [[ ${vf_perf} == "CPM5" ]]; then
		echo ${vf_perf}
                vf_perf=0
        fi
done

start=$SECONDS
CONFIG_FILES=$PWD/${cfg_dir}/*
poll_mode=0
intr_mode=0
intr_aggr=0
auto_mode=1

num_pfs=4

itr=0

cd ${src_dir}
make install-apps
cd -

mkdir -p -m 0777 qdma_perf_results
chmod 0777 qdma_perf_results

run_tests()
{
	if [ ${poll_mode} -eq 1 ]; then
		echo "=========================================================================="
		echo "Poll Mode"
		echo "=========================================================================="
		rm -rf qdma_perf_results/out_poll_${testname}/*
		conf_file="qdma.conf"
		for f in $CONFIG_FILES
		do
			fname=$(basename "$f")
			if [[ $fname == DISABLED_* ]]; then
				continue
			fi

			if [ $vf_perf -eq 1 ]; then
				echo -n "options qdma-vf mode=" > conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:1" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				echo -e "" >> conf_file
				echo -n "options qdma-vf config_bar=" >> conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:0" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				rm -rf /etc/modprobe.d/qdma.conf
				cp conf_file /etc/modprobe.d/qdma.conf
				rm -rf conf_file
				modprobe qdma-vf
				if [ $? -ne 0 ]; then
					exit 1
				fi
				./qdma_linux_perf_auto.sh ${bbddf} $f qdma_perf_results/out_poll_${testname}/${itr} ${runtime} ${bidir_en} ${burst_size} ${marker_en} $vf_perf ${cpm5_flag}
				rmmod qdma-vf
			else
				echo -n "options qdma-pf mode=" > conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:1" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				echo -e "" >> conf_file
				echo -n "options qdma-pf config_bar=" >> conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:0" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				echo -e "" >> conf_file
				echo -n "options qdma-pf master_pf=0x${pci_bus}:0" >> conf_file
				rm -rf /etc/modprobe.d/qdma.conf
				cp conf_file /etc/modprobe.d/qdma.conf
				rm -rf conf_file
				modprobe qdma-pf
				if [ $? -ne 0 ]; then
					exit 1
				fi
				./qdma_linux_perf_auto.sh ${bbddf} $f qdma_perf_results/out_poll_${testname}/${itr} ${runtime} ${bidir_en} ${burst_size} ${marker_en} ${cpm5_flag}
				rmmod qdma-pf
			fi
		done
		chmod -R 0777 qdma_perf_results/out_poll_${testname}
		echo "parsing performance results..."
		python qdma_linux_gen_perf_result.py -d ${PWD}/qdma_perf_results/out_poll_${testname}/${itr}/dmaperf_results/unidir -t ${PWD}/templates -o ${testname}
		python qdma_linux_gen_perf_result.py -d ${PWD}/qdma_perf_results/out_poll_${testname}/${itr}/dmaperf_results/bidir -t ${PWD}/templates -o ${testname}

	fi;

	if [ ${intr_mode} -eq 1 ]; then
		echo "=========================================================================="
		echo "Intr Mode"
		echo "=========================================================================="
		rm -rf qdma_perf_results/out_intr_${testname}/*
		for f in $CONFIG_FILES
		do
			fname=$(basename "$f")
			if [[ $fname == DISABLED_* ]]; then
				continue
			fi

			if [ $vf_perf -eq 1 ]; then
				echo -n "options qdma-vf mode=" > conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:2" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				echo -e "" >> conf_file
				echo -n "options qdma-vf config_bar=" >> conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:0" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				rm -rf /etc/modprobe.d/qdma.conf
				cp conf_file /etc/modprobe.d/qdma.conf
				rm -rf conf_file
				modprobe qdma-vf
				if [ $? -ne 0 ]; then
					exit 1
				fi
				./qdma_linux_perf_auto.sh ${bbddf} $f qdma_perf_results/out_intr_${testname}/${itr} ${runtime} ${bidir_en} ${burst_size} ${marker_en} $vf_perf ${cpm5_flag}
				rmmod qdma-vf
			else
				echo -n "options qdma-pf mode=" > conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:2" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				echo -e "" >> conf_file
				echo -n "options qdma-pf config_bar=" >> conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:0" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				echo -e "" >> conf_file
				echo -n "options qdma-pf master_pf=0x${pci_bus}:0" >> conf_file
				rm -rf /etc/modprobe.d/qdma.conf
				cp conf_file /etc/modprobe.d/qdma.conf
				rm -rf conf_file
				modprobe qdma-pf
				if [ $? -ne 0 ]; then
					exit 1
				fi
				./qdma_linux_perf_auto.sh ${bbddf} $f qdma_perf_results/out_intr_${testname}/${itr} ${runtime} ${bidir_en} ${burst_size} ${marker_en} ${cpm5_flag}
				rmmod qdma-pf
			fi

		done
		chmod -R 0777 qdma_perf_results/out_intr_${testname}
		echo "parsing performance results..."
		python qdma_linux_gen_perf_result.py -d ${PWD}/qdma_perf_results/out_intr_${testname}/${itr}/dmaperf_results/unidir -t ${PWD}/templates -o ${testname}
		python qdma_linux_gen_perf_result.py -d ${PWD}/qdma_perf_results/out_intr_${testname}/${itr}/dmaperf_results/bidir -t ${PWD}/templates -o ${testname}
	fi;

	if [ ${intr_aggr} -eq 1 ]; then
		echo "=========================================================================="
		echo "Aggr Mode"
		echo "=========================================================================="
		rm -rf qdma_perf_results/out_intr_aggr_${testname}/*
		for f in $CONFIG_FILES
		do
			fname=$(basename "$f")
			if [[ $fname == DISABLED_* ]]; then
				continue
			fi

			if [ $vf_perf -eq 1 ]; then
				echo -n "options qdma-vf mode=" > conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:3" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				echo -e "" >> conf_file
				echo -n "options qdma-vf config_bar=" >> conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:0" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				rm -rf /etc/modprobe.d/qdma.conf
				cp conf_file /etc/modprobe.d/qdma.conf
				rm -rf conf_file
				modprobe qdma-vf
				if [ $? -ne 0 ]; then
					exit 1
				fi
				./qdma_linux_perf_auto.sh ${bbddf} $f qdma_perf_results/out_intr_aggr_${testname}/${itr} ${runtime} ${bidir_en} ${burst_size} ${marker_en} $vf_perf ${cpm5_flag}
				rmmod qdma-vf
			else
				echo -n "options qdma-pf mode=" > conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:3" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				echo -e "" >> conf_file
				echo -n "options qdma-pf config_bar=" >> conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:0" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				echo -e "" >> conf_file
				echo -n "options qdma-pf master_pf=0x${pci_bus}:0" >> conf_file
				rm -rf /etc/modprobe.d/qdma.conf
				cp conf_file /etc/modprobe.d/qdma.conf
				rm -rf conf_file
				modprobe qdma-pf
				if [ $? -ne 0 ]; then
					exit 1
				fi
				./qdma_linux_perf_auto.sh ${bbddf} $f qdma_perf_results/out_intr_aggr_${testname}/${itr} ${runtime} ${bidir_en} ${burst_size} ${marker_en} ${cpm5_flag}
				rmmod qdma-pf
			fi
		done
		chmod -R 0777 qdma_perf_results/out_intr_aggr_${testname}
		echo "parsing performance results..."
		python qdma_linux_gen_perf_result.py -d ${PWD}/qdma_perf_results/out_intr_aggr_${testname}/${itr}/dmaperf_results/unidir -t ${PWD}/templates -o ${testname}
		python qdma_linux_gen_perf_result.py -d ${PWD}/qdma_perf_results/out_intr_aggr_${testname}/${itr}/dmaperf_results/bidir -t ${PWD}/templates -o ${testname}
	fi;
	if [ ${auto_mode} -eq 1 ]; then
		echo "=========================================================================="
		echo "Auto Mode"
		echo "=========================================================================="
		rm -rf qdma_perf_results/out_auto_${testname}/*
		for f in $CONFIG_FILES
		do
			fname=$(basename "$f")
			if [[ $fname == DISABLED_* ]]; then
				continue
			fi

			if [ $vf_perf -eq 1 ]; then
				echo -n "options qdma-vf mode=" > conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:0" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				echo -e "" >> conf_file
				echo -n "options qdma-vf config_bar=" >> conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:0" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				rm -rf /etc/modprobe.d/qdma.conf
				cp conf_file /etc/modprobe.d/qdma.conf
				rm -rf conf_file
				modprobe qdma-vf
				if [ $? -ne 0 ]; then
					exit 1
				fi
				./qdma_linux_perf_auto.sh ${bbddf} $f qdma_perf_results/out_auto_${testname}/${itr} ${runtime} ${bidir_en} ${burst_size} ${marker_en} $vf_perf ${cpm5_flag}
				rmmod qdma-vf
			else
				echo -n "options qdma-pf mode=" > conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:0" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				echo -e "" >> conf_file
				echo -n "options qdma-pf config_bar=" >> conf_file
				for ((j = 0; j < ${num_pfs}; j++))
				do
					echo -n "0x${pci_bus}:${j}:0" >> conf_file
					if [ $j != $((${num_pfs} - 1)) ]; then
						echo -n "," >> conf_file
					fi
				done
				echo -e "" >> conf_file
				echo -n "options qdma-pf master_pf=0x${pci_bus}:0" >> conf_file
				rm -rf /etc/modprobe.d/qdma.conf
				cp conf_file /etc/modprobe.d/qdma.conf
				rm -rf conf_file
				modprobe qdma-pf
				if [ $? -ne 0 ]; then
					exit 1
				fi
				./qdma_linux_perf_auto.sh ${bbddf} $f qdma_perf_results/out_auto_${testname}/${itr} ${runtime} ${bidir_en} ${burst_size} ${marker_en} ${cpm5_flag}
				rmmod qdma-pf
			fi
		done
		chmod -R 0777 qdma_perf_results/out_auto_${testname}
		echo "parsing performance results..."
		python qdma_linux_gen_perf_result.py -d ${PWD}/qdma_perf_results/out_auto_${testname}/${itr}/dmaperf_results/unidir -t ${PWD}/templates -o ${testname}
		python qdma_linux_gen_perf_result.py -d ${PWD}/qdma_perf_results/out_auto_${testname}/${itr}/dmaperf_results/bidir -t ${PWD}/templates -o ${testname}
	fi;
	itr=$((itr+1))
}


dmesg -wH > dmesg_log.txt &
dm_pid=$!

kill_dmesg_dump()
{
	kill -9 ${dm_pid}
}

trap kill_dmesg_dump EXIT
while [ ${count} -gt 0 ]
do
	run_tests
	count=$((count-1));
done

echo "Performance analysis and parsing of results finished"

echo "Done"

end=$SECONDS
echo "script execution time: $((end-start)) seconds"
