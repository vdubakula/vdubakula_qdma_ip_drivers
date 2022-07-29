test_no="ST004"
test_name=$test_no".txt"
q_base=0
run=0
qcnt=8

pf_start_port=0
pf_end_port=3

infile="datafile_16bit_pattern.bin"
test_bit=0
total_tests=40
logfile=test_status
max_completion_size=$(expr 4096 \* 7)
echo " ########################################## Test" $test_no" executing: total subtests :"$total_tests "########################################" >> $logfile

for (( port=$pf_start_port; port <=$pf_end_port ; port++ ))
do
	for dma_size in 28672 57344 65536 131072 262144
	do
		cmp_size=0
		last_pkt=0
		qsize=$(expr $dma_size \/ $qcnt)
		qcnt_loop=$(expr $qcnt \- 1)
		for (( qid=0; qid < $qcnt_loop ; qid++ ))
		do
			out=$test_no"_port"$port"_qcount"$qcnt"_size"$dma_size".bin"
			tmp=$(expr $qid \* $qsize)
			if (($qid == 0))
			then
					skip=0
			else
					skip=$(expr $qsize \+ $tmp)
			fi
			last_size=$(expr $qsize \% $max_completion_size)
			if [ $qsize -lt $max_completion_size ]; then
				cmp_size=$last_size;
				last_pkt=0
			else
				cmp_size=$(expr $qsize \- $last_size)
				last_pkt=1
			fi
			#Check if files are there.
			if [ ! -f $out ]; then
				echo " #### Test" $test_no" ERROR: Queue $out output file does not exists ####" >> $logfile
				let "test_bit++"
				continue
			fi

			cmp -l -i 0:$skip $infile $out -n $cmp_size
			if [ $? -ne 0 ]; then
				echo "#### Test"$test_no" ERROR. Queue $infile  data did not match with $out ####" >> $logfile
				let "test_bit++"
				continue
			fi
			# check for last packet, skip input file to begining
			if (( $last_pkt == 1 ))
			then
				skip_bytes=$(expr $skip \+ $cmp_size)
				cmp -l -i 0:$skip_bytes $infile $out -n $last_size
				if [ $? -ne 0 ]; then
					echo "#### Test"$test_no" ERROR. Queue $infile  data did not match with $out ####" >> $logfile
					let "test_bit++"
				continue
				fi
			fi
		done
	done
done

vf_start_port=4
vf_end_port=7

for (( port=$vf_start_port; port <=$vf_end_port ; port++ ))
do
	for dma_size in 28672 57344 65536 131072 262144
	do
		cmp_size=0
		last_pkt=0
		qsize=$(expr $dma_size \/ $qcnt)
		qcnt_loop=$(expr $qcnt \- 1)
		for (( qid=0; qid < $qcnt_loop ; qid++ ))
		do
			out=$test_no"_port"$port"_qcount"$qcnt"_size"$dma_size".bin"
			tmp="$(expr $qid \* $qsize)"
			if (($qid == 0))
			then
					skip=0
			else
					skip=$(expr $qsize \+ $tmp)
			fi
			last_size=$(expr $qsize \% $max_completion_size)
			if [ $qsize -lt $max_completion_size ]; then
				cmp_size=$last_size;
				last_pkt=0
			else
				cmp_size=$(expr $qsize \- $last_size)
				last_pkt=1
			fi
			#Check if files are there.
			if [ ! -f $out ]; then
				echo " #### Test" $test_no" ERROR: Queue $out output file does not exists ####" >> $logfile
				let "test_bit++"
				continue
			fi

			cmp -l -i 0:$skip $infile $out -n $cmp_size
			if [ $? -ne 0 ]; then
				echo "#### Test"$test_no" ERROR. Queue $infile  data did not match with $out ####" >> $logfile
				let "test_bit++"
				continue
			fi
			# check for last packet, skip input file to begining
			if (( $last_pkt == 1 ))
			then
				skip_bytes=$(expr $skip \+ $cmp_size)
				cmp -l -i 0:$skip_bytes $infile $out -n $last_size
				if [ $? -ne 0 ]; then
					echo "#### Test"$test_no" ERROR. Queue $infile  data did not match with $out ####" >> $logfile
					let "test_bit++"
				continue
				fi
			fi
		done
	done
done

if [ $test_bit -eq 0 ]
then
        echo " ########################################## Test" $test_no" status: PASS  ########################################" >> $logfile
else
        echo " ######################## Test" $test_no" status: FAIL, total sub-tests"$total_tests" failed :"$test_bit "##########################" >> $logfile

fi
