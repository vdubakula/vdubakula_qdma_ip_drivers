test_no="MM001"
test_name=$test_no".txt"
q_base=0
run=0
qcnt=2
infile="mm_datafile_1MB.bin"

pf_start_port=0
pf_end_port=3
logfile=test_status

dma_size=4096
test_bit=0
total_tests=4

echo " ########################################## Test" $test_no" executing: total subtests :"$total_tests "########################################" >> $logfile

for (( port=$pf_start_port; port <=$pf_end_port ; port++ ))
do
	case "$port" in
		0)dma_size=4096 ;;
		1)dma_size=8192 ;;
		2)dma_size=12228 ;;
		3)dma_size=16384 ;;
	esac

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

if [ $test_bit -eq 0 ]
then
	echo " ########################################## Test status: PASS  ########################################" >> $logfile
else
	echo " ######################## Test status: FAIL, total sub-tests"$total_tests" failed :"$test_bit "##########################" >> $logfile

fi