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
enable_bi_analysis=1
if [ ! -z $5 ]; then
	enable_bi_analysis=$5
fi

marker_en=1
if [ ! -z $7 ]; then
	marker_en=$7
fi;

vf_perf=0
if [ ! -z $8 ]; then
	vf_perf=$8
fi;

cpm5_flag=0
qtest_args=( "$@" )

for (( i=0; i<${#qtest_args[@]}; i++ ));
do
        if [[ ${qtest_args[$i]} == "CPM5" ]]; then
                cpm5_flag=1
        fi
done

echo $cpm5_flag
exit

#variables
mode=mm
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
keyhole_en=0
aperture_sz=0
offset=0
offset_ch1=0
pci_bbddf="02000"
mm_chnl=0
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
		mode)
			mode=${val}
			;;
		name)
			cfg_name=${val}
			;;
		dir)
			dir=${val}
			;;
		pkt_sz)
			pkt_sz=${val}
			;;
		num_pkt)
			if [ ! -z $6 ]; then
				num_pkt=$6
			else
				num_pkt=${val}
			fi;
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
		mm_chnl)
			mm_chnl=${val}
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
		keyhole_en)
			keyhole_en=${val}
			;;
		aperture_sz)
			aperture_sz=${val}
			;;
		offset)
			offset=${val}
			;;
		offset_ch1)
			offset_ch1=${val}
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

mkdir -p -m 0777 ${outdir}
mkdir -p -m 0777 ${outdir}/configs/${cfg_name}
mkdir -p -m 0777 ${outdir}/dmaperf_results/unidir/${cfg_name}
if [ $enable_bi_analysis -eq 1 ]; then
	mkdir -p -m 0777 ${outdir}/dmaperf_results/bidir/${cfg_name}
fi;
chmod -R 0777 ${outdir}

for ((pf = ${pf_range_start}; pf < ${pf_range_end} + 1; pf++))
do
	echo 512 > /sys/bus/pci/devices/0000:${pci_bus}:${pci_device}.${pf}/qdma/qmax
done
io_sz=${pkt_sz}
i=0

while [ true ]
do
	if [ $mode == st ]; then
		io_sz=$((pkt_sz+(i*64)))
		if (( io_sz > 4096 )); then
			break
		fi
	else
		if (( io_sz > 4096 )); then
			io_sz=$((io_sz+4096))
		else
			io_sz=$(( pkt_sz << i ))
		fi
		if (( io_sz > (1 << max_ram_width) )); then
			break
		fi
	fi;
	i=$(( i+1 ))

	if [[ ( $dir == bi ) || ( $dir == h2c ) ]]; then
		echo "Running ${cfg_name}-h2c for io_size ${io_sz}"
		cfg_file_name=h2c_${cfg_name}_${io_sz}
		log_file=${outdir}/dmaperf_results/unidir/${cfg_name}/log_${io_sz}_${mode}_h2c.txt
		sar_file=${outdir}/dmaperf_results/unidir/${cfg_name}/sar_${io_sz}_${mode}_h2c.txt
		echo "mode=${mode}" > ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "dir=h2c" >>  ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "pf_range=${pf_range_start}:${pf_range_end}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "q_range=${q_range_start}:${q_range_end}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "flags=${flags}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "rngidx=${rngsz_idx}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "cmpl_status_acc=${cmpl_status_acc}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "runtime=${runtime}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "dump_en=${dump_en}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "num_threads=${num_threads}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "num_pkt=${num_pkt}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "mm_chnl=${mm_chnl}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "pkt_sz=${io_sz}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "pci_bus=${pci_bus}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "pci_device=${pci_device}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "marker_en=${marker_en}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		if (( mode == mm )); then
			echo "keyhole_en=${keyhole_en}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
			echo "aperture_sz=${aperture_sz}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		fi;
		echo "offset=${offset}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "offset_ch1=${offset_ch1}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "vf_perf=${vf_perf}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		dma-perf -c ${outdir}/configs/${cfg_name}/${cfg_file_name} > ${log_file} 2>&1 &
		pid=$!
		mpstat -P ALL ${runtime} 1 > ${sar_file} 2>&1
		wait $pid
	fi;
	if [[ ( $dir == bi ) || ( $dir == c2h ) ]]; then
		echo "Running ${cfg_name}-c2h for io_size ${io_sz}"
		cfg_file_name=c2h_${cfg_name}_${io_sz}
		log_file=${outdir}/dmaperf_results/unidir/${cfg_name}/log_${io_sz}_${mode}_c2h.txt
		sar_file=${outdir}/dmaperf_results/unidir/${cfg_name}/sar_${io_sz}_${mode}_c2h.txt
		echo "mode=${mode}" > ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "dir=c2h" >>  ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "pf_range=${pf_range_start}:${pf_range_end}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "q_range=${q_range_start}:${q_range_end}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "flags=${flags}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "cmpl_status_acc=${cmpl_status_acc}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "dump_en=${dump_en}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		if (( mode == st )); then
			echo "tmr_idx=${tmr_idx}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
			echo "cntr_idx=${cntr_idx}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
			echo "trig_mode=${trig_mode}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
			echo "pfetch_en=${pfetch_en}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
			echo "cmptsz=${cmptsz}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		fi;
		echo "rngidx=${rngsz_idx}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "runtime=${runtime}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "num_threads=${num_threads}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "num_pkt=${num_pkt}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "mm_chnl=${mm_chnl}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "pkt_sz=${io_sz}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "pci_bus=${pci_bus}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "pci_device=${pci_device}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "marker_en=${marker_en}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "vf_perf=${vf_perf}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		dma-perf -c ${outdir}/configs/${cfg_name}/${cfg_file_name} > ${log_file} 2>&1 &
		pid=$!
		mpstat -P ALL ${runtime} 1 > ${sar_file} 2>&1
		wait $pid
	fi;
	if [[ ( $dir == bi ) && ( $enable_bi_analysis == 1 ) ]]; then
		echo "Running ${cfg_name}-bi  for io_size ${io_sz}"
		cfg_file_name=bi_${cfg_name}_${io_sz}
		log_file=${outdir}/dmaperf_results/bidir/${cfg_name}/log_${io_sz}_${mode}_bi.txt
		sar_file=${outdir}/dmaperf_results/bidir/${cfg_name}/sar_${io_sz}_${mode}_bi.txt
		echo "mode=${mode}" > ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "dir=${dir}" >>  ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "pf_range=${pf_range_start}:${pf_range_end}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "q_range=${q_range_start}:${q_range_end}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "flags=${flags}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "cmpl_status_acc=${cmpl_status_acc}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "dump_en=${dump_en}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		if (( mode == st )); then
			echo "tmr_idx=${tmr_idx}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
			echo "cntr_idx=${cntr_idx}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
			echo "trig_mode=${trig_mode}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
			echo "pfetch_en=${pfetch_en}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
			echo "cmptsz=${cmptsz}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		fi;
		if (( mode == mm )); then
			echo "keyhole_en=${keyhole_en}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
			echo "aperture_sz=${aperture_sz}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		fi;
		echo "offset=${offset}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "offset_ch1=${offset_ch1}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "rngidx=${rngsz_idx}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "runtime=${runtime}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "num_threads=${num_threads}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "num_pkt=${num_pkt}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "mm_chnl=${mm_chnl}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "pkt_sz=${io_sz}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "pci_bus=${pci_bus}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "pci_device=${pci_device}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "marker_en=${marker_en}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "vf_perf=${vf_perf}" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		echo "" >> ${outdir}/configs/${cfg_name}/${cfg_file_name}
		dma-perf -c ${outdir}/configs/${cfg_name}/${cfg_file_name} > ${log_file} 2>&1 &
		pid=$!
		mpstat -P ALL ${runtime} 1 > ${sar_file} 2>&1
		wait $pid
	fi;
done

if [ $mode == st ]; then
	if [ $cmp5_flag != 1 && $vf_perf -eq 0 ]; then
	    dma-ctl qdma${pci_bbddf} reg write bar 2 0x08 0x80000000
	fi;
	echo ""
else
	if [ $cpm5_flag != 1 &&  $vf_perf -eq 0 ]; then
	    dma-ctl qdma${pci_bbddf} reg write bar 2 0xA0 0x00000001
	fi;
fi;
sleep .001

