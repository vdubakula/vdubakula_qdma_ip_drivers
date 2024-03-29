test_no="MM004"
test_name=$test_no".txt"
q_base=0
run=0
qcnt=2048
infile="mm_datafile_1MB.bin"

vf_start_port=1
vf_end_port=1
logfile=test_status

test_bit=0
total_tests=5


echo " ########################################## Test" $test_no" executing: total subtests :"$total_tests "########################################" >> $logfile

for (( port=$vf_start_port; port <=$vf_end_port ; port++ ))
do
	   for dma_size in 32768 65536 131072 262144 524288
	   do
	 	   out=$test_no"_port"$port"_qcount"$qcnt"_size"$dma_size".bin"

		   #Check if files are there.
		   if [ ! -f $out ]; then
			   echo " #### Test" $test_no" ERROR: Queue $out output file does not exists ####" >> $logfile
			   let "test_bit++"
			   continue
		   fi

		cmp $infile $out -n $dma_size
		if [ $? -eq 1 ]; then
			echo "#### Test"$test_no" ERROR. Queue $infile  data did not match with $out ####" >> $logfile
			   let "test_bit++"
			   continue
		fi
	   done
done

if [ $test_bit -eq 0 ]
then
	echo " ########################################## Test" $test_no" status: PASS  ########################################" >> $logfile
else
	echo " ######################## Test" $test_no" status: FAIL, total sub-tests"$total_tests" failed :"$test_bit "##########################" >> $logfile

fi

test_no="ST004"
test_name=$test_no".txt"
q_base=0
run=0
qcnt=2048

vf_start_port=1
vf_end_port=1

infile="datafile_16bit_pattern.bin"
test_bit=0
total_tests=5
logfile=test_status

echo " ########################################## Test" $test_no" executing: total subtests :"$total_tests "########################################" >> $logfile

for (( port=$vf_start_port; port <=$vf_end_port ; port++ ))
do
	for dma_size in 28672 57344 65536 131072 262144
	do
		qsize="$(expr $dma_size / $qcnt)"
		qcnt_loop="$(expr $qcnt - 1)"
		for (( qid=0; qid < $qcnt_loop ; qid++ ))
		do
			out=$test_no"_port"$port"_qcount"$qcnt"_size"$dma_size".bin"
                        tmp="$(expr $qid \* $qsize)"
                        if (($qid == 0))
                        then
                                skip=0
                        else
                                skip="$(expr $qsize + $tmp)"
                        fi
			#Check if files are there.
			if [ ! -f $out ]; then
				echo " #### Test" $test_no" ERROR: Queue $out output file does not exists ####" >> $logfile
				let "test_bit++"
				continue
			fi

			cmp $infile $out -i 0:$skip -n $qsize
			if [ $? -eq 1 ]; then
				echo "#### Test"$test_no" ERROR. Queue $infile  data did not match with $out ####" >> $logfile
				let "test_bit++"
				continue
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
