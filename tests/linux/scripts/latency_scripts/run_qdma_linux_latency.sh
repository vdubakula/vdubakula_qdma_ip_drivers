#!/bin/bash

base_config=
if [ ! -z $2 ]; then
	base_config=$2
else
	echo "Provide configuration file"
	exit 1
fi;
outdir=
if [ ! -z $3 ]; then
	outdir=$3
else
	echo "Provide output folder name"
	exit 1
fi;
runtime=10
if [ ! -z $4 ]; then
	runtime=$4
fi

vf_perf=0
if [ ! -z $5 ]; then
	vf_perf=$5
fi;
#variables
mode=st
dir=bi
max_ram_width=12 #2^12 - 4K
q_range_start=
q_range_end=
pf_range_start=
pf_range_end=
flags=
cmpl_status_acc=1
rngsz_idx=0
num_q=0
num_pf=0
num_threads=1
cfg_name=""
tmr_idx=0
cntr_idx=0
trig_mode=every
num_pkt=64
pkt_sz=64
pfetch_en=0
dump_en=0
cmptsz=0
pci_bbddf="02000"
if [ ! -z $1 ]; then
	pci_bbddf=$1
fi
pci_bus=${pci_bbddf:0:2}
pci_device=${pci_bbddf:2:2}


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
		name)
			cfg_name=${val}
			;;
		pkt_sz)
			pkt_sz=${val}
			;;
		ram_width)
			max_ram_width=${val}
			;;
		num_threads)
			num_threads=${val}
			;;
		flags)
			f_arr=($(awk -F\| '{$1=$1} 1' <<<"${val}"))
			for f in "${f_arr[@]}"
			do
				flags="$flags $f"
			done
			;;
		wb_acc)
			cmpl_status_acc=${val}
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
		pfetch_en)
			pfetch_en=${val}
			;;
		dump_en)
			dump_en=${val}
			;;
		cmptsz)
			cmptsz=${val}
			;;
		q_range)
			q_range=($(awk -F\: '{$1=$1} 1' <<<"${val}"))
			if [ ${q_range[1]} -lt ${q_range[0]} ]; then
				echo "Invalid PF range"
				exit
			fi
			q_range_start=${q_range[0]}
			q_range_end=${q_range[1]}
			;;
		pf_range)
			pf_range=($(awk -F\: '{$1=$1} 1' <<<"${val}"))
			if [ ${pf_range[1]} -lt ${pf_range[0]} ]; then
				echo "Invalid PF range"
				exit
			fi
			pf_range_start=${pf_range[0]}
			pf_range_end=${pf_range[1]}
			;;
		esac
done < $base_config



if [ $vf_perf -eq 0 ]; then
	echo ${cmpl_status_acc} > /sys/bus/pci/devices/0000:${pci_bus}:${pci_device}.${pf_range_start}/qdma/cmpl_status_acc
fi;

for ((pf = ${pf_range_start}; pf < ${pf_range_end} + 1; pf++))
do
	echo 512 > /sys/bus/pci/devices/0000:${pci_bus}:${pci_device}.${pf}/qdma/qmax
done
io_sz=${pkt_sz}
i=0

while [ true ]
do
	io_sz=$((pkt_sz+(i*64)))
	if (( io_sz > 4096 )); then
		break
	fi
	
	i=$(( i+1 ))

	mkdir -p -m 0777 ${outdir}
	mkdir -p -m 0777 ${outdir}/configs/${cfg_name}
	mkdir -p -m 0777 ${outdir}/dmalat_results/bidir/${cfg_name}
	
	chmod -R 0777 ${outdir}
	
	echo "Running ${cfg_name}-bi  for io_size ${io_sz}"
	cfg_file_name=bi_${cfg_name}_${io_sz}
	log_file=${outdir}/dmalat_results/bidir/${cfg_name}/log_${io_sz}_${mode}_bi.txt
	echo "pf_range=${pf_range_start}:${pf_range_end}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "q_range=${q_range_start}:${q_range_end}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "flags=${flags}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "cmpl_status_acc=${cmpl_status_acc}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "dump_en=${dump_en}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "tmr_idx=${tmr_idx}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "cntr_idx=${cntr_idx}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "trig_mode=${trig_mode}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "pfetch_en=${pfetch_en}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "cmptsz=${cmptsz}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "rngidx=${rngsz_idx}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "runtime=${runtime}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "pkt_sz=${io_sz}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "pci_bus=${pci_bus}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "pci_device=${pci_device}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	echo "" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
	dma-latency -c ${outdir}/configs/${cfg_name}/${cfg_file_name} > ${log_file} 2>&1 &
	pid=$!
	wait $pid
	
	
done

if [ $mode == st ]; then
	if [ $vf_perf -eq 1 ]; then
	    dma-ctl qdmavf${pci_bbddf} reg write bar 2 0x08 0x80000000
	else
	    dma-ctl qdma${pci_bbddf} reg write bar 2 0x08 0x80000000
	fi;
	echo ""
else
	if [ $vf_perf -eq 1 ]; then
	    dma-ctl qdmavf${pci_bbddf} reg write bar 2 0xA0 0x00000001
	else
	    dma-ctl qdma${pci_bbddf} reg write bar 2 0x08 0x80000000
	fi;
fi;
sleep .001

