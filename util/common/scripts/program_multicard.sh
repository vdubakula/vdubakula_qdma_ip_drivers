#!/bin/bash

IFS=' ' # space ( ) is set as delimiter
read -ra TARGET_ID_LIST <<< "$1" # Input string is read into an array as tokens separated by IFS
read -ra BITFILE_LIST <<< "$2" # Input string is read into an array as tokens separated by IFS

num=0
for i in "${TARGET_ID_LIST[@]}"
do
	#/proj/xbuilds/2019.1_daily_latest/installs/lin64/Vivado/2019.1/bin/vivado -nolog -nojournal -mode batch -source HEAD/proj/util/common/scripts/program_bitstream.tcl -tclargs ${BOARD_IDX_LIST[$num]} 0 ${BITFILE_LIST[$num]}
	sh util/common/scripts/program_qdma_bitstream.sh ${TARGET_ID_LIST[$num]} ${BITFILE_LIST[$num]}
	num=$((num+1))
done
