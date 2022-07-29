#!/bin/bash
#arg 1 = PF
#arg 2 = Queue number
#arg 3 = Size

pf=$1
qid=$2
size=$3
num_pkt=1
dev_c2h="/dev/qdma"$1"-ST-"$qid
dev_h2c=$dev_c2h
infile='datafile_16bit_pattern.bin'

function cleanup_queue() {
#	echo "dummy print"
        dma-ctl qdma$pf q stop idx $qid dir bi 
        dma-ctl qdma$pf q del idx $qid dir bi
}
function start_queue() {
	dma-ctl qdma$pf q add idx $qid mode st dir h2c
	dma-ctl qdma$pf q start idx $qid dir h2c desc_bypass_en sw_desc_sz 3

	dma-ctl qdma$pf q add idx $qid mode st dir c2h
	dma-ctl qdma$pf q start idx $qid dir c2h c2h_udd_en cmptsz 3
}

# Find user bar
function get_user_bar () {
        tmp=`dma-ctl qdma$pf reg read bar 0 0x10C | grep "0x10c" | cut -d '=' -f2 | cut -d 'x' -f2 | cut -d '.' -f1`
        bar_ext=$(printf '%x\n' "$(( 0x$tmp & 0x00000f ))")

        if [ $bar_ext -eq 2 ]; then
                usr_bar=1
        elif [ $bar_ext -eq 4 ];then
                usr_bar=2
        fi
}

start_queue
loop=1
size=$3
maxcount=$4
hst_adr1=0
get_user_bar
echo "user bar: $usr_bar"

dma-ctl qdma$pf reg write bar $usr_bar 0x90 0x7 # bypass immediate data loopback set.
hw_qbase="$(dma-ctl dev list |grep qdma$pf|cut -d',' -f 2 | cut -d '~' -f 1|xargs)"
hw_qid=$((qid+hw_qbase))
dma-ctl qdma$pf reg write bar $usr_bar 0x0 $hw_qid 
dma-ctl qdma$pf reg write bar $usr_bar 0x4 $size
dma-ctl qdma$pf reg write bar $usr_bar 0x20 $num_pkt #number of packets


while [ "$loop" -le $maxcount ]
do
	dma-to-device -d $dev_h2c -f $infile -o 0x00 -s $size

	dma-ctl qdma$pf q dump idx $qid dir h2c desc 0 $loop > desc_data_dump_file.txt

	sed '1,3d' desc_data_dump_file.txt | head -n -3 | cut -d ' ' -f 3- > desc_data_input_file.txt

	dma-ctl qdma$pf q dump idx $qid dir h2c desc 0 $loop 

	echo "start C2H immediate data"

	dma-ctl qdma$pf reg write bar $usr_bar 0x08 4  # for immediate data

	dma-ctl qdma$pf q dump idx $qid dir c2h cmpt 0 $loop

	dma-ctl qdma$pf q dump idx $qid dir c2h cmpt 0 $loop > writeback_data_dump_file.txt

	sed '1,3d' writeback_data_dump_file.txt | head -n -3 | cut -d ' ' -f 3- > immediate_data_output_file.txt

	#comparing only the first 16 bytes as supported by RTL1.
	cmp desc_data_input_file.txt immediate_data_output_file.txt -i 8 -n 27
	if [ $? -eq 1 ]; then
		echo "#### ERROR. Queue $qid data did not match ####"
		cleanup_queue
		exit 1
	else
		echo "**** Pass. Queue $size"
	fi
	((loop++))
done
cleanup_queue
echo "**** completed ****"
exit 0
