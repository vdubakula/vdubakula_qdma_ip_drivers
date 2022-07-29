#!/bin/bash
# arq 1 : descriptor bypass mode
if [ ! -z $1 ]; then #if arg1 is there byp enable
	byp=1
else
	byp=0
fi


pf=0
qid=0

size=32

axi_adr=0
hst_adr1=0
hst_adr2=0
num_ittr=8

dev_c2h="/dev/qdma$pf-MM-$qid"

dev_h2c="/dev/qdma$pf-MM-$qid"

infile='/root/QDMA/data/data1G.bin'
#infile='/root/QDMA/data/data_seq1G.bin'
out="out"$pf"_"$qid

logfile="test_mm_3_fix"$pf"_"$qid".log"

echo "This test transfer fixed bytes 32, 64, 128, 256, 512, 1024 ... 0.5Meg on H2C Multiple times and read data data on C2H multiple times and compares them on last transfer."

function setup_queue() {
	dma-ctl qdma$pf q add idx $qid mode mm dir bi
	if [ $byp -eq 1 ]; then
		dma-ctl qdma$pf q start idx $qid dir bi bypass_en
	else 
		dma-ctl qdma$pf q start idx $qid dir bi
	fi
}

function cleanup_queue() {
#	echo "dummy print"
	dma-ctl qdma$pf q stop idx $qid dir bi
        dma-ctl qdma$pf q del idx $qid dir bi
}
setup_queue
if [ $byp -eq 1 ]; then
	dma-ctl qdma$pf reg write bar 1 0x090 3
fi
for ((j=0; j< 15; j++)) do
	echo "** $i, $dev_h2c, $dev_c2h, $infile, hst_adr1 = $hst_adr1, hst_adr2 = $hst_adr2, axi_adr= $axi_adr, byte= $size, **" | tee -a $logfile
	
	for ((i=0; i<8; i++ )) do
		dma-to-device -d $dev_h2c -f $infile -o $hst_adr1 -s $size -a $axi_adr
		tmp=$?
		if [ $tmp != 0 ]; then
			echo " ERROR no Write Back completion coming"
			exit 1
		fi
		dma-from-device -d $dev_c2h -f $out -o $hst_adr2 -s $size -a $axi_adr
		tmp=$?
		if [ $tmp != 0 ]; then
			echo " ERROR no Write Back completion coming"
			exit 1
		fi
	done
	cmp $out $infile -n $size
	if [ $? -eq 1 ]; then
		echo "#### ERROR. Queue $qid data did not match ####" | tee -a $logfile
		cleanup_queue
		exit 1
	else
		echo "**** Pass. Queue $size"
	fi
size=$(( $size * 2 ))
done
if [ $byp -eq 1 ]; then
	dma-ctl qdma$pf reg write bar 1 0x090 0
fi
cleanup_queue
echo "**** completed ****"

exit 0


