set board_idx [lindex $argv 0]
set device_idx [lindex $argv 1]
set bitstream [lindex $argv 2]

connect
targets 
target $board_idx
source HEAD/proj/util/scripts/spi2vjtag.tcl
device program $bitstream
source HEAD/proj/util/scripts/qdma_versal_mm_st_4pf_252vf.tcl
source HEAD/proj/util/scripts/qdma_versal_msix.tcl
exit
