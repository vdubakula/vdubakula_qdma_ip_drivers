test_no="MM009"
test_name=$test_no".txt"
q_base=0
run=0
qcnt=8
infile="mm_datafile_1MB.bin"

pf_start_port=0
pf_end_port=1
total_ports=2
logfile=test_status

test_bit=0
total_tests=5


echo " ########################################## Test" $test_no" executing: ########################################" >> $logfile

for (( port=$pf_start_port; port <=$pf_end_port ; port++ ))
do
	   for dma_size in 32768 65536 131072 262144 524288
	   do
	 	   out=$test_no"_port_qcount"$qcnt"_size"$dma_size".bin"$port
		   dma_size_per_port=`expr $dma_size / $total_ports` 

		   #Check if files are there.
		   if [ ! -f $out ]; then
			   echo " #### Test" $test_no" ERROR: Queue $out output file does not exists ####" >> $logfile
			   let "test_bit++"
			   continue
		   fi
		port_off=`expr $port \* $dma_size_per_port`
		cmp $out $infile -i 0:$port_off -n $dma_size_per_port
		if [ $? -eq 1 ]; then
			echo "#### Test"$test_no" ERROR. Queue $infile  data did not match with $out ####" >> $logfile
			   let "test_bit++"
		fi
	   done
done

if [ $test_bit -eq 0 ]
then
	echo " ########################################## Test" $test_no" status: PASS  ########################################" >> $logfile
else
	echo " ######################## Test" $test_no" status: FAIL, check $logfile for failures"##########################" >> $logfile

fi
