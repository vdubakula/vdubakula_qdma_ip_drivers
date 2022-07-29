#!/bin/bash
pf=$1
qid_c2h=$2
qid_h2c=$3
#arg 4 = f_size
#arg 5 = num_pkt

if [ $4 -eq 0 ]; then
	maxcount=1
else 	maxcount=$4
fi
if [ ! -z $5 ]; then #if arg5 is there fix size
	f_size=1
	size=$5
	num_pkt=$6
else
   	f_size=0
fi

echo "$pf $qid_c2h $qid_h2c $maxcount $size $num_pkt"

hw_qid=$(($qid_c2h + $(($pf*32)) ))
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
dev_h2c="/dev/qdma$1-ST-$3"
datafile="file_$2_$3"
logfile="st_loopback$1_$2_$3.log"
infile='./datafile_16bit_pattern.bin'

function cleanup_queue_c2h() {

        dma-ctl qdma$pf q stop idx $qid_c2h dir c2h
        dma-ctl qdma$pf q del idx $qid_c2h dir c2h
}

function cleanup_queue_h2c() {

        dma-ctl qdma$pf q stop idx $qid_h2c dir h2c
        dma-ctl qdma$pf q del idx $qid_h2c dir h2c
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

echo "*** C2H: Queue = $2, module name = $dev_c2h ****"
echo "*** H2C: Queue = $3, module name = $dev_h2c ****"

function start_queue_c2h() {

	dma-ctl qdma$pf q add idx $qid_c2h mode st dir c2h
	dma-ctl qdma$pf q start idx $qid_c2h dir c2h
	dma-ctl qdma$pf reg write bar $usr_bar 0x0 $hw_qid  # Enter the hardware qid
}

function start_queue_h2c() {

	dma-ctl qdma$pf q add idx $qid_h2c mode st dir h2c
	dma-ctl qdma$pf q start idx $qid_h2c dir h2c
}

start_queue_c2h
start_queue_h2c
while [ "$loop" -le $maxcount ]
do
	#C2H TRANSFER
	if [ $f_size -eq 1 ]; then
		hst_adr1=0
	else
		randomize_tx_params
	fi
	echo "size = $size num_pkt= $num_pkt"

	let "tsize= $size*$num_pkt" # if more packets are requested.

	echo "** $loop, $dev_c2h, hst_adr1 = $hst_adr1, byte= $size, **"

	echo "*** size0 = $tsize *******"
	dma-ctl qdma$pf reg write bar $usr_bar 0x4 $size
	dma-ctl qdma$pf reg write bar $usr_bar 0x20 $num_pkt #number of packets
	dma-from-device -d $dev_c2h -f $datafile -o $hst_adr1 -s $tsize &

	dma-ctl qdma$pf reg write bar $usr_bar 0x08 2

	wait
	#Check if files is there.
	if [ ! -f $datafile ]; then
		echo " #### ERROR: Queue $2 output file does not exists ####"
		echo " #### ERROR: Queue $2 output file does not exists ####" >> $logfile
		cleanup_queue_c2h
		cleanup_queue_h2c
		exit 1
	fi
	# check files size
	filesize=$(stat -c%s "$datafile")
	if [ $filesize -gt $tsize ]; then
		echo "#### ERROR: Queue $2 output file size does not match, filesize= $filesize ####"
		echo "#### ERROR: Queue $2 output file size does not match, filesize= $filesize ####" >> $logfile
		cleanup_queue_c2h
		cleanup_queue_h2c
		exit 1
	fi

	#H2C TRANSFER
        echo "** $loop, $dev_h2c, hst_adr1 = $hst_adr1, byte= $size, **"
        #echo "** $loop, $dev, hst_adr1 = $hst_adr1, byte= $size **" >> $logfile
        
        echo "*** size1 = $tsize *******"

        dma-ctl qdma$pf reg write bar $usr_bar 0x0C 0x1 # clear h2c Match register.

        dma-to-device -d $dev_h2c -f $datafile -o $hst_adr1 -s $tsize

	#compare file

	#rm $out_co " return value $? "
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
                cleanup_queue_c2h
                cleanup_queue_h2c
                exit 1
        fi

	((loop++))

       	if [ $3 -eq 0 ];then
		((maxcount++))
	fi
done
cleanup_queue_c2h
cleanup_queue_h2c
echo "**** completed ****"
echo "**** completed ****" >> $logfile
exit 0


