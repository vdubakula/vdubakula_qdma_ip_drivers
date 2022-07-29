
# Arguments check
if { $argc != 3} {
    puts "Incorrect number of arguments! Usage: program_bitstream.tcl <BOARD_INDEX> <DEVICE_INDEX> <BITSTREAM_FILE_PATH>"
    puts "E.g.: vivado -mode batch -source program_bitstream.tcl -tclargs 0 0 xdma_kcu1500_test_bitstream_1.bit".
    return
}

set board_idx [lindex $argv 0]
set device_idx [lindex $argv 1]
set bitstream [lindex $argv 2]

# open the hardware server and connect to it.
open_hw
connect_hw_server

# connect to the board
puts "The target board is [lindex [get_hw_targets] $board_idx]"
open_hw_target [lindex [get_hw_targets] $board_idx]

# select the device
puts "The target device is [lindex [get_hw_devices] $device_idx]"
current_hw_device [lindex [get_hw_devices] $device_idx]
refresh_hw_device [current_hw_device]

# Program the bitstream on the device
puts "The bitstream file is $bitstream"
set_property PROBES.FILE {} [current_hw_device]
set_property FULL_PROBES.FILE {} [current_hw_device]
set_property PROGRAM.FILE $bitstream [current_hw_device]
set_param xicom.use_bitstream_version_check false
program_hw_devices [current_hw_device]

# Refresh the device
refresh_hw_device [current_hw_device]

# cleanup 
disconnect_hw_server
close_hw