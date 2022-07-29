#!/bin/bash

if [ $# -lt 2 ]; then
echo "usage: $0 <target_id> <pdi>"
        exit
fi

rm test1.tcl
echo "connect" > test1.tcl
echo "targets" >> test1.tcl
echo "targets $1" >> test1.tcl
echo "after 1000" >> test1.tcl
echo "device program $2" >> test1.tcl
echo "after 100" >> test1.tcl
echo "exit" >> test1.tcl

#cat test1.tcl
/proj/xbuilds/2021.2_INT_daily_latest/installs/lin64/Vivado/2021.2/bin/xsdb test1.tcl
rm test1.tcl
#reboot
