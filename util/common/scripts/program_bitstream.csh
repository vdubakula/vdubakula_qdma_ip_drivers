#!/bin/csh

if ($# != 3) then
    echo "Usage:    $0 BOARD_INDEX DEVICE_INDEX BITFILE"
    echo "  BOARD_INDEX   Index of hw_target as seen in Vivado in brackets after Board ID. E.g.:"
    echo "                  Xilinx/12809621t165A (0)  <--  index 0"
    echo "                  Xilinx/12809621t198A (1)  <--  index 1"
    echo "  DEVICE_INDEX  Index of hw_device as seen in Vivado for that hw_target"
    echo "                  xcvu9p_0  <-- index 0 "
    echo "                  xcvu9p_1  <-- index 1 "
    echo "  BITFILE       file path for .bit file"
    echo "Example:"
    echo "  $0 0 0 ./my_bitfile.bin"
    exit 1
endif

icons_pcieapps add -t xilinx -v 2018.2_daily_latest
vivado -nolog -nojournal -mode batch -source program_bitstream.tcl -tclargs $1 $2 $3
