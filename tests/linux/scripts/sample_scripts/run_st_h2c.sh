#!/bin/bash
#arg 1 = PF
#arg 2 = Queue number
#arg 3 = loop max count
#arg 4 = fix

pf=$1
qid=$2

if [ $3 -eq 0 ]; then
	maxcount=1
else 	maxcount=$3
fi
if [ ! -z $4 ]; then #if arg4 is there fix size
	f_size=1
else
   	f_size=0
fi
usr_bar=2

loop=1
size=1
no_h2c=0
host_adr_high=4094
#mem_div=1024
#mem_div=2048
#mem_div=4096
#mem_div=8192
#mem_div=16384
mem_div=32768
#mem_div=65536
#mem_div=131072
#mem_div=262144
#mem_div=524388
#mem_div=1073741824
#s_high=15000  # max size is 15000 + 1024 (axi_addr) < 16384
s_high=$mem_div
#dev="/dev/mdma$1_qset_$qid"
dev_h2c="/dev/qdma"$1"-ST-"$qid
out="out"$qid
logfile="run_st_h2c"$1"_"$qid".log"
#rm $logfile
echo "timestamp=$(date +%m)"

infile='datafile_16bit_pattern.bin'
function cleanup_queue() {
#	echo "dummy print"
        dma-ctl qdma$pf q stop idx $qid dir h2c
        dma-ctl qdma$pf q del idx $qid dir h2c
}
function start_queue() {
	dma-ctl qdma$pf q add idx $qid mode st dir h2c
	dma-ctl qdma$pf q start idx $qid dir h2c
}

start_queue

while [ "$loop" -le $maxcount ]
do
	if [ $f_size -eq 1 ]; then
		size=$4
		hst_adr1=0
		num_pkt=1
		hst_adr1=0;
		hst_adr2=0;
		axi_adr=$(( $qid*$mem_div ))
        else
		#Random Host address between 0 to 3094
		hst_adr1=$RANDOM
		let "hst_adr1 %= $host_adr_high"
		hst_adr1=0
		# byte size 
		#size=$RANDOM
		f1=$RANDOM
		#f1=1
		let "f1 %= 2"
		if [ $f1 -eq 0 ]; then
			size=$(( ($RANDOM %64) +1 )) ## for random number between 1 and 64
		else
			size=$(( (($RANDOM<<15)|($RANDOM+1))% $mem_div ))
			#size=$(( ($RANDOM<<15)|($RANDOM+1) ))
		fi
		if [ $size -eq 0 ]; then
			let "size = $size + 1"
		fi
		echo "size = $size"
		#let "size %= $s_high"
		
	fi

	echo "** $loop, $dev_h2c, hst_adr1 = $hst_adr1, byte= $size, **"
	#echo "** $loop, $dev, hst_adr1 = $hst_adr1, byte= $size **" >> $logfile
	
 	dma-ctl qdma$pf reg write bar $usr_bar 0x0C 0x1 # clear h2c Match register.

	dma-to-device -d $dev_h2c -f $infile -o $hst_adr1 -s $size

	echo " return value $? "
	pass=`dma-ctl qdma$pf reg read bar $usr_bar 0x10 | grep "0x10" | cut -d '=' -f2 | cut -d 'x' -f2 | cut -d '.' -f1`

	# convert hex to bin
	code=`echo $pass | tr 'a-z' 'A-Z'`
  	val=`echo "obase=2; ibase=16; $code" | bc`
  	echo "$val "

	check=1
	#match=$(($val & $check))
	#echo " $match"
	if [ $(($val & $check)) -eq 1 ];then
		echo "*** Test passed ***"
	else
		echo "#### ERROR Test failed. pattern did not match ####"
		exit 1
	fi
	((loop++))

       	if [ $3 -eq 0 ];then
		((maxcount++))
	fi
done
#cleanup_queue
echo "**** completed ****"
echo "**** completed ****" >> $logfile
exit 0


