#!/bin/bash

if [ $# -lt 3 ]; then
echo "usage: $0 <target_id> <versal_es2_jtag_boot file> <pdi>"
        exit
fi

rm test1.tcl
echo "connect" > test1.tcl
echo "targets" >> test1.tcl
echo "targets $1" >> test1.tcl
echo "source $2" >> test1.tcl
echo "device program $3" >> test1.tcl
echo "exit" >> test1.tcl

#cat test1.tcl
/proj/xbuilds/2019.2_INT_daily_latest/installs/lin64/Vivado/2019.2/bin/xsdb test1.tcl
rm test1.tcl
#reboot
