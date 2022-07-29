#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Usage: perf_analysis.sh <config_file> <relative_out_dir> <pci bus number>"
	exit;
fi;

CONFIG_FILE=$1
pci_bd=$3
pci_bus=$(echo ${pci_bd} | awk '{split($0, pci_bd_arr, ":")} END{print pci_bd_arr[1]}')
pci_dev=$(echo ${pci_bd} | awk '{split($0, pci_bd_arr, ":")} END{print pci_bd_arr[2]}')
qdma_dev=${pci_bus}${pci_dev}
OUT=$2

if [ -z "$CONFIG_FILE" ]; then
	echo "Configuration file does not exist"
	exit;
fi;

#variables
mode=mm
dir=bi
max_ram_width=18 #2^18 - 256K 
declare -a pf_lst=()
declare -a q_lst=()
flags=
wb_acc=1
rngsz_idx=0
ioengine=sync
runtime=
num_q=0
num_pf=0
num_threads=1
enable_bi_analysis=1
cfg_name=""
node_mode_str=MM
st_num_pkts=64
tmr_idx=0
cntr_idx=0
trig_mode=every
declare -a st_io_size_lst=(64 128 256 512 1024 2048 4096 8192 16384 24576 28672)

#parse config file
while IFS= read -r line; do
	line="$(echo -e "${line}" | sed -e 's/^[[:space:]]*//')" #remove leading white spaces
	line="$(echo -e "${line}" | sed -e 's/[[:space:]]*$//')" #remove trailing white spaces
	if [[ $line == \#* ]]; then
		#skip comment lines
		continue
	fi
	
	cmd_arr=($(awk -F# '{$1=$1} 1' <<<"${line}"))
	line=${cmd_arr[0]} #strip comments in line

	cmd_arr=($(awk -F= '{$1=$1} 1' <<<"${line}"))
	cmd=${cmd_arr[0]} #extract variable
	val=${cmd_arr[1]} #extract value
	
	case $cmd in
		runtime)
			runtime=${val}
			;;
		ioengine)
			ioengine=${val}
			;;
		mode)
			mode=${val}
			;;
		name)
			cfg_name=${val}
			;;
		dir)
			dir=${val}
			;;
		bidir_en)
			enable_bi_analysis=${val}
			;;
		size)
			size=${val}
			;;
		ram_width)
			max_ram_width=${val}
			;;
		num_threads)
			num_threads=${val}
			;;
				runtime)
			runtime=${val}
			;;
				flags)
			f_arr=($(awk -F\| '{$1=$1} 1' <<<"${val}"))
			for f in "${f_arr[@]}"
			do
				flags="$flags $f"
			done
			;;
		wb_acc)
			wb_acc=${val}
			;;
		tmr_idx)
			tmr_idx=${val}
			;;
		cntr_idx)
			cntr_idx=${val}
			;;
		trig_mode)
			trig_mode=${val}
			;;
		rngidx)
			rngsz_idx=${val}
			;;
		q_range)
			q_range=($(awk -F\: '{$1=$1} 1' <<<"${val}"))
			if [ ${q_range[1]} -lt ${q_range[0]} ]; then
				echo "Invalid PF range"
				exit
			fi
			num_q=$((q_range[1]-q_range[0]+1))
			for ((qid=${q_range[0]};qid<=${q_range[1]};qid++))
			do
				q_lst+=($qid)
			done
			;;
		pf_range)
			pf_range=($(awk -F\: '{$1=$1} 1' <<<"${val}"))
			if [ ${pf_range[1]} -lt ${pf_range[0]} ]; then
				echo "Invalid PF range"
				exit
			fi
			num_pf=$((pf_range[1]-pf_range[0]+1))
			for ((pf=${pf_range[0]};pf<=${pf_range[1]};pf++))
			do
				pf_lst+=($pf)
			done
			;;
		esac
done < $CONFIG_FILE

#set wb acc
echo $wb_acc > /sys/bus/pci/devices/0000\:${pci_bd}.0/qdma/wrb_acc

outdir="$PWD/$OUT"
mkdir -p ${outdir}/unidir/${ioengine}-${cfg_name}
mkdir -p ${outdir}/bidir/${ioengine}-${cfg_name}
num_cmds=0

iosize=64 #starting to profile from 64 bytes all the way till max_bram size
declare -a q_add_lst=()
declare -a q_start_lst=()
declare -a q_stop_lst=()
declare -a q_del_lst=()
declare -a fio_h2c_cmd_lst=()
declare -a fio_c2h_cmd_lst=()
declare -a fio_bi_cmd_lst=()
declare -a out_fio_h2c_log_lst=()
declare -a out_sar_h2c_log_lst=()
declare -a out_fio_c2h_log_lst=()
declare -a out_sar_c2h_log_lst=()
declare -a out_fio_bi_log_lst=()
declare -a out_sar_bi_log_lst=()

q_start_param=
if [ $mode == st ]; then
	node_mode_str=ST
	q_start_param="idx_tmr ${tmr_idx} idx_cntr ${cntr_idx} trigmode ${trig_mode}"
fi

#prepare environment setup/cleanup commands
for pf in ${pf_lst}
do
	for qid in ${q_lst[@]}
	do
		#q control commands	    	    
		q_add_lst+=("dmactl qdma${qdma_dev}${pf} q add idx ${qid} mode ${mode} dir ${dir}")
		q_start_lst+=("dmactl qdma${qdma_dev}${pf} q start idx ${qid} dir ${dir} ${flags} idx_ringsz ${rngsz_idx} ${q_start_param}")
		q_stop_lst+=("dmactl qdma${qdma_dev}${pf} q stop idx ${qid} dir ${dir}")
		q_del_lst+=("dmactl qdma${qdma_dev}${pf} q del idx ${qid} dir ${dir}")
	done
done

total_q=$((num_pf*num_q))
#prepare fio commands
fio_cmd="fio --allow_file_create=0 --numjobs=$num_threads --group_reporting=1 --ioengine=$ioengine --mem=mmap --zero_buffers"
for (( i=$iosize; i<=$((1<<max_ram_width)); i=$((i<<1)) ))
do
	cur_io_size=$i
	h2c_io_size=$cur_io_size
	c2h_io_size=$cur_io_size
	h2c_io_blK_sz=$i
	c2h_io_blk_sz=$i
	h2c_io_name=$i
	c2h_io_name=$i
	if [ $mode == st ]; then
		h2c_io_blK_sz=${st_io_size_lst[${num_cmds}]}
		c2h_io_blk_sz=${st_io_size_lst[${num_cmds}]}
		cur_io_size=${st_io_size_lst[${num_cmds}]}
		c2h_io_size=$((st_num_pkts * c2h_io_blk_sz)) # fixed IO Size
		c2h_io_name=$c2h_io_blk_sz
		c2h_io_blk_sz=${c2h_io_size}
		h2c_io_size=$((st_num_pkts * h2c_io_blK_sz))
		h2c_io_name=$h2c_io_blK_sz
	fi
	fio_h2c_cmd=$fio_cmd
	fio_h2c_cmd+=" --runtime=$runtime --time_based"
	fio_c2h_cmd=$fio_cmd
	fio_c2h_cmd+=" --runtime=$runtime --time_based"
	fio_bi_cmd=$fio_cmd
	fio_bi_cmd+=" --runtime=$runtime --time_based"
	for pf in ${pf_lst[@]}
	do
		for qid in ${q_lst[@]}
		do
			# h2c
			h2c_attr=" --name=write${h2c_io_name}-${cfg_name} --bs=${h2c_io_blK_sz} --size=${h2c_io_size} --offset=0 --rw=write --filename=/dev/qdma${qdma_dev}${pf}-${node_mode_str}-${qid}"
			fio_h2c_cmd+=$h2c_attr
			
			# c2h
			c2h_attr=" --name=read${c2h_io_name}-${cfg_name} --bs=${c2h_io_blk_sz} --size=${c2h_io_size} --offset=0 --rw=read --filename=/dev/qdma${qdma_dev}${pf}-${node_mode_str}-${qid}"
			fio_c2h_cmd+=$c2h_attr

			# bi
			fio_bi_cmd+=$h2c_attr
			fio_bi_cmd+=$c2h_attr
		done
	done
	fio_h2c_cmd_lst+=("$fio_h2c_cmd")
	fio_c2h_cmd_lst+=("$fio_c2h_cmd")
	fio_bi_cmd_lst+=("$fio_bi_cmd")
	
	if [ $mode == st ]; then
		c2h_io_size=${st_io_size_lst[${num_cmds}]}
		h2c_io_size=${st_io_size_lst[${num_cmds}]}
	fi

	#log file details
	out_fio_h2c_log_lst+=("${outdir}/unidir/${ioengine}-${cfg_name}/fio_${cur_io_size}_h2c.log")
	out_sar_h2c_log_lst+=("${outdir}/unidir/${ioengine}-${cfg_name}/sar_${cur_io_size}_h2c.log")
	out_fio_c2h_log_lst+=("${outdir}/unidir/${ioengine}-${cfg_name}/fio_${cur_io_size}_c2h.log")
	out_sar_c2h_log_lst+=("${outdir}/unidir/${ioengine}-${cfg_name}/sar_${cur_io_size}_c2h.log")
	out_fio_bi_log_lst+=("${outdir}/bidir/${ioengine}-${cfg_name}/fio_${cur_io_size}_bi.log")
	out_sar_bi_log_lst+=("${outdir}/bidir/${ioengine}-${cfg_name}/sar_${cur_io_size}_bi.log")
	num_cmds=$((num_cmds+1))
done
#setup environment
echo "Setting up environment"
for ((i=0;i<total_q;i++))
do
	q_add_cmd=${q_add_lst[$i]}
	echo ${q_add_cmd}
	${q_add_cmd} #add queue
done

sar_run_time=$((runtime/2))
sar_sleep_time=$((sar_run_time/2))

#Disable Wrb FIFO in HW user logic
if [ $mode == st ]; then
	dmactl qdma${qdma_dev}0 reg write bar 2 0x08 0x120000
fi
#start executing commands
for ((i=0;i<num_cmds;i++))
do
	fio_exec_cmd=
	fio_h2c_log=${out_fio_h2c_log_lst[$i]}
	fio_c2h_log=${out_fio_c2h_log_lst[$i]}
	fio_bi_log=${out_fio_bi_log_lst[$i]}
	sar_h2c_log=${out_sar_h2c_log_lst[$i]}
	sar_c2h_log=${out_sar_c2h_log_lst[$i]}
	sar_bi_log=${out_sar_bi_log_lst[$i]}
	cur_io_size=$((64<<$i))
	
	#configure packet size
	if [ $mode == st ]; then
		cur_io_size=${st_io_size_lst[$i]}
		dmactl qdma${qdma_dev}0 reg write bar 2 0x90 $cur_io_size
	fi
	#start queue
	for ((q=0;q<total_q;q++))
	do
		q_start_cmd=${q_start_lst[$q]}
		echo ${q_start_cmd}
		${q_start_cmd} #start queue
	done
		
	#h2c
	fio_exec_cmd=${fio_h2c_cmd_lst[$i]}
	echo "Starting h2c performance analysis for iosize=$cur_io_size"
	echo $fio_exec_cmd
	${fio_exec_cmd}  > ${fio_h2c_log} 2>&1 &
	if [ $? -ne 0 ]; then
		echo "fio command for h2c analysis failed"
		exit 1
	fi
	pid=$!
	sleep ${sar_sleep_time}
	sar -u $sar_run_time 1 > ${sar_h2c_log} 2>&1
	wait $pid

	#c2h
	fio_exec_cmd=${fio_c2h_cmd_lst[$i]}
	echo "Starting c2h performance analysis for iosize=$cur_io_size"
	echo $fio_exec_cmd
	${fio_exec_cmd}  > ${fio_c2h_log} 2>&1 &
	if [ $? -ne 0 ]; then
		echo "fio command for c2h analysis failed"
		exit 1
	fi
	pid=$!
	sleep ${sar_sleep_time}
	sar -u $sar_run_time 1 > ${sar_c2h_log} 2>&1
	wait $pid

	if [ $enable_bi_analysis -eq 1 ]; then
	#bi
		fio_exec_cmd=${fio_bi_cmd_lst[$i]}
		echo "Starting h2c&c2h performance analysis for iosize=$cur_io_size"
		echo $fio_exec_cmd
		${fio_exec_cmd}  > ${fio_bi_log} 2>&1 &
		if [ $? -ne 0 ]; then
			echo "fio command for h2c&c2h analysis failed"
			exit 1
		fi
		pid=$!
		sleep ${sar_sleep_time}
		sar -u ${sar_run_time} 1 > ${sar_bi_log} 2>&1
		wait $pid
	fi

	#clean up residuals
	for ((q=0;q<total_q;q++))
	do
		q_stop_cmd=${q_stop_lst[$q]}
		echo ${q_stop_cmd}
		${q_stop_cmd} #stop queue
	done
done

echo "Cleaning up environment"
#cleanup environment
for ((i=0;i<total_q;i++))
do
	q_del_cmd=${q_del_lst[$i]}
	echo ${q_del_cmd}
	${q_del_cmd} #delete queue
done
