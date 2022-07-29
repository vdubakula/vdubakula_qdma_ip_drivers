#!/bin/bash

if [ $# -lt 2 ]; then
echo "usage: $0 <target_id> <bitstream_file>"
        exit
fi

rm program_bitfile.tcl
echo "connect" > program_bitfile.tcl
echo "targets" >> program_bitfile.tcl
echo "targets $1" >> program_bitfile.tcl
echo "fpga -f $2" >> program_bitfile.tcl
echo "exit" >> program_bitfile.tcl

/proj/xbuilds/2019.2_INT_daily_latest/installs/lin64/Vivado/2019.2/bin/xsdb program_bitfile.tcl
rm program_bitfile.tcl
