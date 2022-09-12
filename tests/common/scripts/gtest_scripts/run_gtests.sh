#!/bin/bash

base_config=
pci_bbddf_config=01000
if [ ! -z $1 ]; then
	pci_bbddf_config=$1
fi
if [ ! -z $2 ]; then
	base_config=$2
else
	echo "usage: $0 <config file> <src_dir> <test_dir> <driver linux|dpdk>"
	exit 1
fi;

test_mask=0x01
repeat=20
bdf=$1
m_pf=0
pf_qmax_cfg_en=(0 0 0 0)
pf_qmax=(449 449 449 449)
pf_nvf=(0 0 0 0)
qmaxvfs=0
declare -a nq_vf_pf0=()
declare -a nq_vf_pf1=()
declare -a nq_vf_pf2=()
declare -a nq_vf_pf3=()
declare -a total_vfs_lst=()
declare -a pci_card_list=()
declare -a pci_bdf_list=()
declare -a pci_bus=()
declare -a pci_device=()
declare -a cfg_filename=()
declare -a test_app_pids=()
pf_nvf=(0 0 0 0)
src_dir=${PWD}/../../../../drivers/linux
test_dir=${PWD}/../../apps/qdma_test
filter="*"
drv="linux"
num_cards=1
num_pfs=4
dev_max_q=2048
run_gtest=1
config_name=""
script_dir=${PWD}
is_valid_config=0
config_bar=0
run_disabled=0
target="pf_vf"
fail_log=
dpdk_bind_drv="igb_uio"
multi_apps=0
cpm5_flag=0

if [ ! -z $3 ]; then
	src_dir=${PWD}/$3
fi

if [ ! -z $4 ]; then
	test_dir=${PWD}/$4
fi

if [ ! -z $5 ]; then
	drv=$5
fi

if [ ! -z $6 ]; then
	config_bar=$6
fi

if [ ! -z $7 ]; then
	if [[ $7 == "pf_vf" || $7 == "pf" || $7 == "vf" ]]; then
		target=$7
	fi
fi
if [ $drv == "dpdk" ]; then
	if [ ! -z $8 ]; then
		dpdk_bind_drv=$8
	fi
else
	if [ ! -z $8 ]; then
		multi_apps=$8
	fi
fi

if [ ! -z $9 ]; then
      cpm5_flag=$9
fi

build_dir=build_${drv}_$target
RTE_SDK=${test_dir}/${build_dir}/DPDK/dpdk-stable-20.11
RTE_TARGET=build

filename='.tmp.txt'
rm -f ${filename}
while IFS= read -r line; do
	line="$(echo -e "${line}" | sed -e 's/^[[:space:]]*//')" #remove leading white spaces
	line="$(echo -e "${line}" | sed -e 's/[[:space:]]*$//')" #remove trailing white spaces
	if [[ $line == \#* ]]; then
		#skip comment lines
		continue
	fi

	cmd_arr=$(awk -F'#' '{print $1}' <<< ${line})
	line=${cmd_arr[0]} #stripped comments in line

	cmd=$(awk -F'=' '{print $1}' <<< ${line}) #extract variable
	val_str=$(awk -F'=' '{print $2}' <<< ${line}) #extract value
	val=$(echo ${val_str} | sed 's/ *$//g') #strip trailing spaces

	case $cmd in
		name)
			config_name=${val}
			;;
		test_mask)
			test_mask=${val}
			;;
		repeat)
			repeat=${val}
			;;
		filter)
			filter="${val}"
			;;
		master_pf)
			m_pf=${val}
			;;
		pf_qmax_cfg_en)
			arr_str=$(echo ${val} | sed 's/[()]//g')
			pf_qmax_cfg_en=($(awk -F' ' '{$1=$1} 1' <<<"${arr_str}"))
			;;
		pf_qmax)
			arr_str=$(echo ${val} | sed 's/[()]//g')
			pf_qmax=($(awk -F' ' '{$1=$1} 1' <<<"${arr_str}"))
			;;
		pf_nvf)
			arr_str=$(echo ${val} | sed 's/[()]//g')
			pf_nvf=($(awk -F' ' '{$1=$1} 1' <<<"${arr_str}"))
			;;
		qmaxvfs)
			qmaxvfs=${val}
			;;
		vf_pf0_qmax)
			arr_str=$(echo ${val} | sed 's/[()]//g')
			nq_vf_pf0=($(awk -F' ' '{$1=$1} 1' <<<"${arr_str}"))
			;;
		vf_pf1_qmax)
			arr_str=$(echo ${val} | sed 's/[()]//g')
			nq_vf_pf1=($(awk -F' ' '{$1=$1} 1' <<<"${arr_str}"))
			;;
		vf_pf2_qmax)
			arr_str=$(echo ${val} | sed 's/[()]//g')
			nq_vf_pf2=($(awk -F' ' '{$1=$1} 1' <<<"${arr_str}"))
			;;
		vf_pf3_qmax)
			arr_str=$(echo ${val} | sed 's/[()]//g')
			nq_vf_pf3=($(awk -F' ' '{$1=$1} 1' <<<"${arr_str}"))
			;;
		num_pfs)
			num_pfs=${val}
			;;
		dev_max_q)
			dev_max_q=${val}
			;;
		run_gtest)
			run_gtest=${val}
			;;
		run_disabled)
			run_disabled=${val}
			;;
		valid_drv)
			arr_str=$(echo ${val} | sed 's/[()]//g')
			valid_drv=($(awk -F' ' '{$1=$1} 1' <<<"${arr_str}"))
			num_valid_drv=${#valid_drv[@]}
			for ((i = 0; i < num_valid_drv; i++))
			do
				if [ "${valid_drv[i]}" == "${drv}" ]; then
					is_valid_config=1
				fi
			done
			if  [ $is_valid_config -eq 0 ]; then
				echo "skipping $base_config"
				exit
			fi
			;;
		esac
	case $cmd in
		name)
			continue
			;;
		test_mask)
			continue
			;;
		repeat)
			continue
			;;
		filter)
			continue
			;;
		run_gtest)
			continue
			;;
		valid_drv)
			continue
			;;
	esac
	echo $line >> ${filename}
done < $base_config

if  [ $is_valid_config -eq 0 ]; then
	echo "skipping $base_config"
	exit
fi

if [ ! -d $src_dir ]; then
	echo "no such $src_dir directory exists"
	exit
fi

if [ ! -d $test_dir ]; then
	echo "no such $test_dir directory exists"
	exit
fi

validate_config()
{
	if [[ $target == "pf_vf" || $target == "pf" ]]; then
		for ((i = 0; i < num_cards; i++))
		do
			#validate vfs
			num_pfs=${#pf_qmax[@]}
			for ((j = 0; j < num_pfs; j++))
			do
				if [ ${pf_nvf[$j]} -gt ${total_vfs_lst[$j]} ]; then
					echo "Invalid num vf for ${pci_bus[i]}:${pci_device[i]}.${j} - cfg/actual: ${pf_nvf[$j]}/${total_vfs_lst[$j]}"
					exit
				fi
				case $j in
					0)
						num_entries_vf_q=${#nq_vf_pf0[@]}
						;;
					1)
						num_entries_vf_q=${#nq_vf_pf1[@]}
						;;
					2)
						num_entries_vf_q=${#nq_vf_pf2[@]}
						;;
					3)
						num_entries_vf_q=${#nq_vf_pf3[@]}
						;;
					esac
				num_vfs=${pf_nvf[$j]}
				if [ ${num_entries_vf_q} -gt ${num_vfs} ]; then
					echo "more entries in nq_vf_pf${j}"
					exit
				fi
				#validate qmax
				if [ ${pf_qmax[$j]} -gt $dev_max_q ]; then
					echo "Invalid qmax for pf_qmax[$j]"
				fi
				for ((k = 0; k < num_entries_vf_q; k++))
				do
					case $j in
						0)
							if [ ${nq_vf_pf0[$k]} -gt $qmaxvfs ]; then
								echo "Invalid qmax for nq_vf_pf01[$k]"
							fi
							;;
						1)
							if [ ${nq_vf_pf1[$k]} -gt $qmaxvfs ]; then
								echo "Invalid qmax for nq_vf_pf1[$k]"
							fi
							;;
						2)
							if [ ${nq_vf_pf2[$k]} -gt $qmaxvfs ]; then
								echo "Invalid qmax for nq_vf_pf2[$k]"
							fi
							;;
						3)
							if [ ${nq_vf_pf3[$k]} -gt $qmaxvfs ]; then
								echo "Invalid qmax for nq_vf_pf3[$k]"
							fi
							;;
					esac
				done
			done
		done
	fi
}

set_qmax_for_vfs_from_host()
{
	for ((i = 0; i < num_cards; i++))
	do
		for ((j = 0; j < num_pfs; j++))
		do
			#set max q per VF
			case $j in
				0)
					for ((k = 0; k < ${pf_nvf[${j}]}; k++))
					do
						echo ${nq_vf_pf0[$k]} > /sys/bus/pci/devices/0000\:${pci_bus[i]}\:${pci_device[i]}.${j}/virtfn${k}/qdma/qmax
						if [ $? -lt 0 ]; then
							echo "failed to set qmax for pf_nvf[${j}, ${k}]]"
							exit 1
						fi
					done
					;;
				1)
					for ((k = 0; k < ${pf_nvf[${j}]}; k++))
					do
						echo ${nq_vf_pf1[$k]} > /sys/bus/pci/devices/0000\:${pci_bus[i]}\:${pci_device[i]}.${j}/virtfn${k}/qdma/qmax
						if [ $? -lt 0 ]; then
							echo "failed to set qmax for pf_nvf[${j}, ${k}]]"
							exit 1
						fi
					done
					;;
				2)
					for ((k = 0; k < ${pf_nvf[${j}]}; k++))
					do
						echo ${nq_vf_pf2[$k]} > /sys/bus/pci/devices/0000\:${pci_bus[i]}\:${pci_device[i]}.${j}/virtfn${k}/qdma/qmax
						if [ $? -lt 0 ]; then
							echo "failed to set qmax for pf_nvf[${j}, ${k}]]"
							exit 1
						fi
					done
					;;
				3)
					for ((k = 0; k < ${pf_nvf[${j}]}; k++))
					do
						echo ${nq_vf_pf3[$k]} > /sys/bus/pci/devices/0000\:${pci_bus[i]}\:${pci_device[i]}.${j}/virtfn${k}/qdma/qmax
						if [ $? -lt 0 ]; then
							echo "failed to set qmax for pf_nvf[${j}, ${k}]]"
							exit 1
						fi
					done
					;;
			esac
		done
	done
}

set_qmax_for_vf()
{
	vf_bdfs=$(lspci | grep -i xilinx | awk -F " " '$7 > "a000" {print $1}' | tr -t "\n" " ")
	vfn=0
	total_vfns=0
	for ((i = 0; i < num_pfs; i++))
	do
		total_vfns=$((total_vfns + pf_nvf[${i}]))
	done

	for ((i = 0; i < num_pfs; i++))
	do
		case $i in
			0)
				for ((j = 0; j < ${pf_nvf[${i}]}; j++))
				do
					bdf=$(echo $vf_bdfs | cut -d' ' -f$((vfn + 1)))

					echo ${nq_vf_pf0[$j]} > /sys/bus/pci/devices/0000\:${bdf}/qdma/qmax
					if [ $? -lt 0 ]; then
						echo "failed to set qmax for pf_nvf[${i}, ${j}]]"
						exit 1
					fi

					vfn=$((vfn+1))
					if [ $vfn -gt $total_vfns ]; then
						i=$num_pfs
						break
					fi
				done
				;;
			1)
				for ((j = 0; j < ${pf_nvf[${i}]}; j++))
				do
					bdf=$(echo $vf_bdfs | cut -d' ' -f$((vfn + 1)))

					echo ${nq_vf_pf1[$j]} > /sys/bus/pci/devices/0000\:${bdf}/qdma/qmax
					if [ $? -lt 0 ]; then
						echo "failed to set qmax for pf_nvf[${i}, ${j}]]"
						exit 1
					fi

					vfn=$((vfn+1))
					if [ $vfn -gt $total_vfns ]; then
						i=$num_pfs
						break
					fi
				done
				;;
			2)
				for ((j = 0; j < ${pf_nvf[${i}]}; j++))
				do
					bdf=$(echo $vf_bdfs | cut -d' ' -f$((vfn + 1)))

					echo ${nq_vf_pf2[$j]} > /sys/bus/pci/devices/0000\:${bdf}/qdma/qmax
					if [ $? -lt 0 ]; then
						echo "failed to set qmax for pf_nvf[${i}, ${j}]]"
						exit 1
					fi

					vfn=$((vfn+1))
					if [ $vfn -gt $total_vfns ]; then
						i=$num_pfs
						break
					fi
				done
				;;
			3)
				for ((j = 0; j < ${pf_nvf[${i}]}; j++))
				do
					bdf=$(echo $vf_bdfs | cut -d' ' -f$((vfn + 1)))

					echo ${nq_vf_pf3[$j]} > /sys/bus/pci/devices/0000\:${bdf}/qdma/qmax
					if [ $? -lt 0 ]; then
						echo "failed to set qmax for pf_nvf[${i}, ${j}]]"
						exit 1
					fi

					vfn=$((vfn+1))
					if [ $vfn -gt $total_vfns ]; then
						i=$num_pfs
						break
					fi
				done
				;;
		esac
	done
}

get_env()
{
	if [[ $target == "pf_vf" || $target == "pf" ]]; then
		for ((i = 0; i < num_cards; i++))
		do
			for ((j = 0; j < num_pfs; j++))
			do
				num_vf=$((`cat /sys/bus/pci/devices/0000\:${pci_bus[i]}\:${pci_device[i]}.${j}/sriov_totalvfs`))
				total_vfs_lst+=($num_vf)
				echo "Total avaialable vf in pf${j} is ${num_vf}"
			done
		done
	fi
}

setup_env()
{
	echo "Setting Host QDMA settings"
	if [[ $target == "pf_vf" || $target == "pf" ]]; then
		for ((i = 0; i < num_cards; i++))
		do
			for ((j = 0; j < num_pfs; j++))
			do
				#enable number of VFs for PF
				echo  ${pf_nvf[${j}]} > /sys/bus/pci/devices/0000\:${pci_bus[i]}\:${pci_device[i]}.${j}/sriov_numvfs
				if [ $? -lt 0 ]; then
					echo "failed to set sriov_numvfs for pf[${j}]"
					exit 1
				fi
			done

			for ((j = 0; j < num_pfs; j++))
			do
				if [ ${pf_qmax_cfg_en[${j}]} -gt 0 ]; then
					echo  ${pf_qmax[${j}]} > /sys/bus/pci/devices/0000\:${pci_bus[i]}\:${pci_device[i]}.${j}/qdma/qmax
					if [ $? -lt 0 ]; then
						echo "failed to set qmax for pf[${j}]"
						exit 1
					fi
				fi
				sleep .1
			done
		done
	fi
	echo "waiting for all vfs probe to be completed..."
	sleep 5 #wait for vf_probe of all vfs be completed
	echo "setting qmax..."

	if [ $target == "pf_vf" ]; then
		set_qmax_for_vfs_from_host
	elif [ $target == "vf" ]; then
		set_qmax_for_vf
	fi
}

setup_env_dpdk()
{
	num_pfs=${#pf_qmax[@]}
	modprobe uio
	insmod ${RTE_SDK}/dpdk-kmods/linux/igb_uio/igb_uio.ko
	modprobe vfio-pci

	export RTE_SDK=${RTE_SDK}
	export RTE_TARGET=build
}

get_bdf_for_all_pci_cards()
{
	i=0
	while IFS= read -r line; do
		line="$(echo -e "${line}" | sed -e 's/^[[:space:]]*//')" #remove leading white spaces
		line="$(echo -e "${line}" | sed -e 's/[[:space:]]*$//')" #remove trailing white spaces
		if [[ $line == \#* ]]; then
			#skip comment lines
			continue
		fi

		cmd_arr=$(awk -F'#' '{print $1}' <<< ${line})
		line=${cmd_arr[0]} #stripped comments in line

		cmd=$(awk -F':' '{print $1}' <<< ${line}) #extract variable
		val_str=$(awk -F':' '{print $2}' <<< ${line}) #extract value
		val=$(echo ${val_str} | sed 's/ *$//g') #strip trailing spaces

		pci_card_list[$i]=$cmd
		pci_bdf_list[$i]=$val

		i=$(($i+1))
		num_cards=$i
	done < $pci_bbddf_config
}

run_test()
{
	if [[ $target == "pf" && $run_gtest -ne 0 ]]; then
		echo "Error : Invalid Combination found in configuration : target : $target, run_gtest : $run_gtest"
	fi

	insmod_param=""
	vf_insmod_param=""
	g_master_pf=""
	g_config_bar=""
	g_mode=""
	nb_csv=$(($num_cards - 1))

	conf_file="qdma.conf"
	
	log_file="${config_name}_auto_mode_log"
	if [ $1 == "intr" ]; then
		log_file="${config_name}_intr_mode_log"
	elif [ $1 == "aggr" ]; then
		log_file="${config_name}_aggr_mode_log"
	elif [ $1 == "poll" ]; then
		log_file="${config_name}_poll_mode_log"
	elif [ $1 == "mixed" ]; then
		log_file="${config_name}_mixed_mode_log"
	elif [ $1 == "legacy" ]; then
		log_file="${config_name}_leacy_mode_log"
	fi;

	echo -n "options qdma-pf mode=" > conf_file
	
	for ((j = 0; j < num_pfs; j++))
	do
		for ((i = 0; i < num_cards; i++))
		do
			if [ $1 == "intr" ]; then
				echo -n "0x${pci_bus[i]}:${j}:2," >> conf_file
			elif [ $1 == "aggr" ]; then
				echo -n "0x${pci_bus[i]}:${j}:3," >> conf_file
			elif [ $1 == "poll" ]; then
				echo -n "0x${pci_bus[i]}:${j}:1," >> conf_file
			elif [ $1 == "mixed" ]; then
				if [ j == 0 ]; then
					echo -n "0x${pci_bus[i]}:${j}:0," >> conf_file
				elif [ j == 1 ]; then
					echo -n "0x${pci_bus[i]}:${j}:1," >> conf_file
				elif [ j == 2 ]; then
					echo -n "0x${pci_bus[i]}:${j}:2," >> conf_file
				else
					echo -n "0x${pci_bus[i]}:${j}:3," >> conf_file
				fi
			elif [ $1 == "legacy" ]; then
				echo -n "0x${pci_bus[i]}:${j}:4," >> conf_file
			else
				echo -n "0x${pci_bus[i]}:${j}:0," >> conf_file
			fi
		done
	done
	echo -e "" >> conf_file
	echo -n "options qdma-pf config_bar=" >> conf_file
	for ((j = 0; j < num_pfs; j++))
	do
		for ((i = 0; i < num_cards; i++))
		do
			echo -n "0x${pci_bus[i]}:${j}:${config_bar}," >> conf_file
		done
	done
	echo -e "" >> conf_file
	echo -n "options qdma-pf master_pf=" >> conf_file
	for ((i = 0; i < num_cards; i++))
	do
		echo -n "0x${pci_bus[i]}:${m_pf}," >> conf_file
	done	

	echo -e "" >> conf_file
	echo -n "options qdma-vf mode=" >> conf_file
	for ((j = 0; j < num_pfs; j++))
	do
		for ((i = 0; i < num_cards; i++))
		do
			if [ ${pf_nvf[${j}]} -ne 0 ]; then
				if [ $1 == "intr" ]; then
					echo -n "0x${pci_bus[i]}:${j}:2," >> conf_file
				elif [ $1 == "aggr" ]; then
					echo -n "0x${pci_bus[i]}:${j}:3," >> conf_file
				elif [ $1 == "poll" ]; then
					echo -n "0x${pci_bus[i]}:${j}:1," >> conf_file
				elif [ $1 == "mixed" ]; then
					if [ j == 0 ]; then
						echo -n "0x${pci_bus[i]}:${j}:0," >> conf_file
					elif [ j == 1 ]; then
						echo -n "0x${pci_bus[i]}:${j}:1," >> conf_file
					elif [ j == 2 ]; then
						echo -n "0x${pci_bus[i]}:${j}:2," >> conf_file
					else
						echo -n "0x${pci_bus[i]}:${j}:3," >> conf_file
					fi
				elif [ $1 == "legacy" ]; then
					echo -n "0x${pci_bus[i]}:${j}:4," >> conf_file
				else
					echo -n "0x${pci_bus[i]}:${j}:0," >> conf_file
				fi
			fi	
		done
	done
	echo -e "" >> conf_file
	echo -n "options qdma-vf config_bar=" >> conf_file
	for ((j = 0; j < num_pfs; j++))
	do
		for ((i = 0; i < num_cards; i++))
		do
			if [ ${pf_nvf[${j}]} -ne 0 ]; then
				echo -n "0x${pci_bus[i]}:${j}:${config_bar}," >> conf_file
			fi
		done
	done
	rm -rf /etc/modprobe/qdma.conf
	cp conf_file /etc/modprobe.d/qdma.conf
	date_time=`date +%Y%m%d_%H%M%S`
	cfgfname=$(basename "${base_config}")
	cfgname=$(awk -F'.' '{print $1}' <<< ${cfgfname})
	xml_log_file_name_ext=${log_file}
	log_file="${log_file}_${date_time}_${cfgname}.txt"
	if [ $drv == "linux" ]; then
		cd ${src_dir}
		if [ $target == "pf_vf" ]; then
			modprobe qdma-pf
			modprobe qdma-vf
		elif [ $target == "pf" ]; then
			modprobe qdma-pf
		elif [ $target == "vf" ]; then
			modprobe qdma-vf
		fi
	fi

	# Let the Driver do its initialization Routine
	sleep 2

	if [[ ($run_gtest -eq 0) && ($drv == "linux") ]]; then
		setup_env
	elif [[ ($drv == "dpdk") ]]; then
		setup_env_dpdk
	fi
	#dev list
	echo "result being logged to ${test_dir}/logs/${log_file}"
	if [[ ($run_gtest -eq 0) && ($drv == "linux") ]]; then
		dma-ctl dev list > ${test_dir}/logs/${log_file}
	fi

	if [ ${run_gtest} -eq 1 ]; then
		if [ $drv == "linux" ]; then
			ulimit -n 1048576
		fi

		echo ""
		echo "============================================="
		echo "Running regression in ${config_name}-$1 mode"
		echo "============================================="
		cd ${test_dir}/${build_dir}
		gtest_param=" --gtest_filter=${filter}"
		if [ $run_disabled -ne 0 ]; then
			gtest_param=" --gtest_also_run_disabled_tests --gtest_filter=${filter}"
		fi
		gen_report=1
		if [ $drv == "linux" ];then
			if [ $multi_apps -ne 0 ]; then
				cfg_param="-f ${script_dir}/"
			else
				cfg_param="-f ${script_dir}/${filename}"
			fi
		elif [ $drv == "dpdk" ];then
			cfg_param="--cfg_name=${script_dir}/${filename}"
		fi
		for ((i = 1; i <= repeat; i++))
		do
			echo "Repeating all tests (iteration ${i}) . . ." | tee -a ${test_dir}/logs/${log_file}
			echo "" | tee -a ${test_dir}/logs/${log_file}
			if [ $drv == "linux" ]; then
				if [ $multi_apps -ne 0 ]; then
					for ((idx = 1; idx < num_cards; idx++))
					do
						src/qdma_test ${gtest_param} --gtest_output=xml:qdma_test_results_Card_${idx}_${xml_log_file_name_ext}_${date_time}_${i}.xml ${cfg_param}${cfg_filename[idx]} | tee -a ${test_dir}/logs/card${idx}_${log_file} &
						test_app_pids[${idx} - 1]=$!
					done
					src/qdma_test ${gtest_param} --gtest_output=xml:qdma_test_results_Card_0_${xml_log_file_name_ext}_${date_time}_${i}.xml ${cfg_param}${cfg_filename[0]} | tee -a ${test_dir}/logs/card0_${log_file} 
					for((app_id = 0; app_id < num_cards - 1; app_id++))
					do
						wait ${test_app_pids[${app_id}]}
					done
				else
					src/qdma_test ${gtest_param} --gtest_output=xml:qdma_test_results_${xml_log_file_name_ext}_${date_time}_${i}.xml ${cfg_param} | tee -a ${test_dir}/logs/${log_file} 
				fi
				if [ "${PIPESTATUS[0]}" -ne "0" ]; then
					gen_report=0
					break
				fi
				if [ $multi_apps -ne 1 ]; then
					cfg_param=""
				fi
			fi
			if [ $drv == "dpdk" ]; then
				src/qdma_test -c f -n 4 ${cfg_param} -- --bind_driver=${dpdk_bind_drv} --config="(2048)" ${gtest_param} --gtest_output=xml:qdma_test_results_${xml_log_file_name_ext}_${date_time}_${i}.xml | tee -a ${test_dir}/logs/${log_file}
				if [ "${PIPESTATUS[0]}" -ne "0" ]; then
					gen_report=0
					break
				fi
			fi
			if [ $gen_report -eq 1 ]; then
				if [ $drv == "dpdk" ]; then
					python ${script_dir}/qdma_gtest_result_parser.py -c ${test_dir}/${build_dir}/qdma_test_results_${xml_log_file_name_ext}_consolidated_${date_time}.xml -f qdma_test_results_${xml_log_file_name_ext}_${date_time}_${i}.xml
					#rm -f qdma_test_results_${xml_log_file_name_ext}_${date_time}_${i}.xml
				fi
				if [ $drv == "linux" ]; then
					if [ $multi_apps -ne 0 ]; then
						for ((idx = 0; idx < num_cards; idx++))
						do 
							python ${script_dir}/qdma_gtest_result_parser.py -c ${test_dir}/${build_dir}/qdma_test_results_Card_${idx}_${xml_log_file_name_ext}_consolidated_${date_time}.xml -f qdma_test_results_Card_${idx}_${xml_log_file_name_ext}_${date_time}_${i}.xml
						done
					else
						python ${script_dir}/qdma_gtest_result_parser.py -c ${test_dir}/${build_dir}/qdma_test_results_${xml_log_file_name_ext}_consolidated_${date_time}.xml -f qdma_test_results_${xml_log_file_name_ext}_${date_time}_${i}.xml
					fi 
				else 
					echo "Invalid driver"
				fi
			fi
		done

		if [ $gen_report -eq 1 ]; then
			if [ $drv == "dpdk" ]; then
				echo "generating report for ${config_name}-$1 mode at ${test_dir}/${build_dir}/qdma_test_results_${xml_log_file_name_ext}_consolidated_${date_time}.xlsx"
				python ${script_dir}/qdma_gtest_result_parser.py -f ${test_dir}/${build_dir}/qdma_test_results_${xml_log_file_name_ext}_consolidated_${date_time}.xml -t ${test_dir}/ts02_2000_0142_QDMA.xlsx
				result_file=${test_dir}/${build_dir}/qdma_test_results_${xml_log_file_name_ext}_consolidated_${date_time}.xml
				fail_log=$(cat ${result_file} | grep -E 'failures="[1-9]+[0-9]*"')
			else
				if [ $multi_apps -ne 0 ]; then
					for ((idx = 0; idx < num_cards; idx++))
					do 
						echo "generating report for ${config_name}-$1 mode at ${test_dir}/${build_dir}/qdma_test_results_Card_${idx}_${xml_log_file_name_ext}_consolidated_${date_time}.xlsx"
						python ${script_dir}/qdma_gtest_result_parser.py -f ${test_dir}/${build_dir}/qdma_test_results_Card_${idx}_${xml_log_file_name_ext}_consolidated_${date_time}.xml -t ${test_dir}/ts02_2000_0142_QDMA.xlsx
						result_file=${test_dir}/${build_dir}/qdma_test_results_Card_${idx}_${xml_log_file_name_ext}_consolidated_${date_time}.xml
						fail_log=$(cat ${result_file} | grep -E 'failures="[1-9]+[0-9]*"')					
						fail_log=$(cat ${result_file} | grep -E 'failures="[1-9]+[0-9]*"')					
						if [ "${fail_log}" != "" ]; then
							echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
							echo "Failures detected at CARD $idx"
							echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
						fi
					done
				else
					echo "generating report for ${config_name}-$1 mode at ${test_dir}/${build_dir}/qdma_test_results_${xml_log_file_name_ext}_consolidated_${date_time}.xlsx"
					python ${script_dir}/qdma_gtest_result_parser.py -f ${test_dir}/${build_dir}/qdma_test_results_${xml_log_file_name_ext}_consolidated_${date_time}.xml -t ${test_dir}/ts02_2000_0142_QDMA.xlsx
					result_file=${test_dir}/${build_dir}/qdma_test_results_${xml_log_file_name_ext}_consolidated_${date_time}.xml
					fail_log=$(cat ${result_file} | grep -E 'failures="[1-9]+[0-9]*"')
				fi
			fi
		else
			echo "report for ${config_name}-$1 mode at ${test_dir}/${build_dir}/qdma_test_results_${xml_log_file_name_ext}_consolidated_${date_time}.xlsx is not generated"
			fail_log="fail"
		fi
		echo "============================================="

	fi

	if [ $target == "pf" ]; then
		echo "Press Any Key after completing VM execution(if any)"
		read -n 1 -s
	fi

	if [ $drv == "linux" ]; then
		if [ $target == "pf_vf" ]; then
			rmmod qdma-vf
			for ((i = 0; i < num_cards; i++))
			do
				m_bdf=${pci_bus[i]}${pci_device[i]}${m_pf}
				echo "card $i m_bdf $m_bdf"
				if [[ $cpm5_flag != 1 ]];then
					dma-ctl qdma${m_bdf} reg write bar 2 0xA0 0x01
				fi
			done
			rmmod qdma-pf
		elif [ $target == "pf" ]; then
			for ((i = 0; i < num_cards; i++))
			do
				m_bdf=${pci_bus[i]}${pci_device[i]}${m_pf}
				echo "card $i m_bdf $m_bdf"
				if [[ $cpm5_flag != 1 ]];then
					dma-ctl qdma${m_bdf} reg write bar 2 0xA0 0x01
				fi
			done
			rmmod qdma-pf
		elif [ $target == "vf" ]; then
			rmmod qdma-vf
		fi
	elif [ $drv == "dpdk" ];then
		rmmod igb_uio
		rmmod uio
	fi
}

echo "starting ${config_name} configuration tests"
if [ -f $pci_bbddf_config ]; then
	get_bdf_for_all_pci_cards

	num=0
	for i in ${pci_card_list[@]}
	do
		pci_bus[num]=0x${pci_bdf_list[num]:0:2}
		pci_device[num]=0x${pci_bdf_list[num]:2:2}
		if [ $drv == "linux" ]; then
			pci_bus[num]=${pci_bdf_list[num]:0:2}
			pci_device[num]=${pci_bdf_list[num]:2:2}
		fi
		num=$(($num + 1))
	done
else
	multi_apps=0
	pci_card_list[0]="Card1"
	pci_bdf_list[0]=$pci_bbddf_config
	pci_bus[0]=0x${pci_bbddf_config:0:2}
	pci_device[0]=0x${pci_bbddf_config:2:2}
	if [ $drv == "linux" ]; then
		pci_bus[0]=${pci_bbddf_config:0:2}
		pci_device[0]=${pci_bbddf_config:2:2}
	fi
fi

if [ $multi_apps -ne 0 ]; then
	for ((i = 0; i < num_cards; i++))
	do
		cfg_filename[i]=card_${i}${filename}
		rm -rf ${cfg_filename[i]}
		cp ${filename} ${cfg_filename[i]}
		echo "pci_bus=(${pci_bus[i]})" >> ${cfg_filename[i]}
		echo "pci_dev=(${pci_device[i]})" >> ${cfg_filename[i]}
		echo "multiple_apps=1" >> ${cfg_filename[i]}
	done
else
	echo "pci_bus=(${pci_bus[*]})" >> ${filename}
	echo "pci_dev=(${pci_device[*]})">> ${filename}
fi

if [[ ($run_gtest -eq 0) && ($drv == "linux") ]]; then
	get_env
	validate_config
fi

if [ $drv == "dpdk" ]; then
	test_mask=0x02
fi

#poll mode
if ((test_mask & 0x02)); then
	run_test "poll"
fi

#direct interrupt
if ((test_mask & 0x04)); then
	run_test "intr"
fi

#indirect interrupt mode
if ((test_mask & 0x08)); then
	run_test "aggr"
fi

#auto mode
if ((test_mask & 0x01)); then
	run_test "auto"
fi

#mixed mode
if ((test_mask & 0x10)); then
	run_test "mixed"
fi

#Leagcy mode
if ((test_mask & 0x20)); then
	run_test "legacy"
fi

rm -f ${script_dir}/${filename}
if [ "${fail_log}" != "" ]; then
	echo "Test case failures detected"
	exit 1
else
	echo "completed ${config_name} sucessfully"
	exit 0
fi
