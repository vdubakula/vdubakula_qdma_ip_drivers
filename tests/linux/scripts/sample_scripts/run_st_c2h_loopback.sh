#!/bin/bash
pf=$1
qid=$2
#arg 4 = f_size
#arg 5 = num_pkt

if [ $3 -eq 0 ]; then
	maxcount=1
else 	maxcount=$3
fi
if [ ! -z $4 ]; then #if arg4 is there fix size
	f_size=1
	size=$4
	num_pkt=$5
else
   	f_size=0
fi

echo "$pf $qid $maxcount $size $num_pkt"

#TODO: need to handle the number of qs for pf
hw_qid=$(($qid + $(($pf*32)) ))
usr_bar=2
loop=1
no_h2c=0
no_c2h=0
axi_adr=0
axi_adr_high=1024   #random AXI address between 0 to 1024
host_adr_high=4094
#mem_div=1024
#mem_div=2048
#mem_div=4096
#mem_div=8192
mem_div=16384
#mem_div=32768
#mem_div=65536
#mem_div=131072
#mem_div=262144
#mem_div=524388
#mem_div=1073741824
#s_high=15000  # max size is 15000 + 1024 (axi_addr) < 16384
s_high=$mem_div

dev_c2h="/dev/qdma$1-ST-$2"
dev_h2c="/dev/qdma$1-ST-$2"
out="out$2"
logfile="loopback$1_$2.log"
infile='datafile_16bit_pattern.bin'

function cleanup_queue() {
#	echo "dummy print"
        dma-ctl qdma$pf q stop idx $qid dir bi
        dma-ctl qdma$pf q del idx $qid dir bi
}

function randomize_tx_params() {
                #Random Host address between 0 to 3094
                hst_adr1=$RANDOM
                let "hst_adr1 %= $host_adr_high"
                hst_adr1=0;
                # byte size
                f1=$RANDOM
                let "f1 %= 2"
                if [ $f1 -eq 0 ]; then
                        size=$(( ($RANDOM %64) +1 )) ## for random number between 1 and 64
                else
                        #size=$(( (($RANDOM<<15)|($RANDOM+1))% $max_size ))
                        size=$(( ($RANDOM<<15)|($RANDOM+1) ))
                fi
                let "size %= $s_high"
                echo "size = $size"
                even=$size
                let "even %= 2"
                if [ $even -eq 1 ];then
                        let "size = $size+1"
                fi

                num_pkt=$(( ($RANDOM % 9) +1))
	echo " num_pkt = $num_pkt"

}

echo "*** Queue = $2, c2h module name = $dev_c2h  h2c module name = $dev_h2c****"

dma-ctl qdma$pf q add idx $qid mode st dir bi
dma-ctl qdma$pf q start idx $qid dir bi
dma-ctl qdma$pf reg write bar $usr_bar 0x0 $hw_qid  # for Queue 0
# enable loop back in the design
dma-ctl qdma$pf reg write bar $usr_bar 0x08 1

while [ "$loop" -le $maxcount ]
do
	if [ $f_size -eq 1 ]; then
		hst_adr1=0
	else
		randomize_tx_params
	fi
	echo "size = $size num_pkt= $num_pkt"

	let "tsize= $size*$num_pkt" # if more packets are requested.

	echo "** $loop, $dev_c2h, hst_adr1 = $hst_adr1, byte= $size, **"

	#dma-ctl qdma$pf reg write bar $usr_bar 0x4 $size
	#dma-ctl qdma$pf reg write bar $usr_bar 0x20 $num_pkt #number of packets
	dma-from-device -d $dev_c2h -f $out -o $hst_adr1 -s $tsize &

        echo "** $loop, $dev_h2c, infile = $infile hst_adr1 = $hst_adr1, byte= $size, **"
        dma-to-device -d $dev_h2c -f $infile -o $hst_adr1 -s $tsize &

	wait
	#Check if files is there.
	if [ ! -f $out ]; then
		echo " #### ERROR: Queue $2 output file does not exists ####"
		echo " #### ERROR: Queue $2 output file does not exists ####" >> $logfile
		cleanup_queue
		exit 1
	fi
	# check files size
	filesize=$(stat -c%s "$out")
	if [ $filesize -gt $tsize ]; then
		echo "#### ERROR: Queue $2 output file size does not match, filesize= $filesize ####"
		echo "#### ERROR: Queue $2 output file size does not match, filesize= $filesize ####" >> $logfile
		cleanup_queue
		exit 1
	fi
	#compare file
	cmp $out $infile -n $tsize
	if [ $? -eq 1 ]; then
		echo "#### Test ERROR. Queue $2 data did not match ####"
		echo "#### Test ERROR. Queue $2 data did not match ####" >> $logfile
		dma-ctl qdma$pf q dump idx $qid dir c2h
		dma-ctl qdma$pf reg dump
		cleanup_queue
		exit 1
	else
		echo "**** Test pass. Queue $2"
	fi
	#rm $out
	((loop++))
       	if [ $3 -eq 0 ];then
		((maxcount++))
	fi
done
cleanup_queue
echo "**** completed ****"
echo "**** completed ****" >> $logfile
exit 0


