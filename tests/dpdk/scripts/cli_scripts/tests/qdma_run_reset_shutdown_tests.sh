#!/usr/bin/expect -f

set timeout -1
set arg1 [lindex $argv 0]
set arg2 [lindex $argv 1]
set arg3 [lindex $argv 2]
set arg4 [lindex $argv 3]

set nb_ports $arg1
set nb_queues $arg2
set nb_st_queues $arg3
set test_mode $arg4

set ring_size 1024
set buff_size 4096
set repeat 1
set src_addr 0
set dst_addr 0
set dma_size 262144

set dpdk_error_log "dpdk_error_log.txt"
set err_log_fd [open $dpdk_error_log "w"]

set mm_input_file "mm_datafile_1MB.bin"
set st_input_file "datafile_16bit_pattern.bin"

# Usage: ./build/qdma_testapp -c <processor_mask> -n <Number of memory channels>
spawn ./build/qdma_testapp -c 0xf -n 4
set ids(1) $spawn_id

# puts "Binding dpdk VF devices \n";
# cmd="lspci | grep -i xilinx | awk -F \" \" \'(($7 > \"a000\" && $7< \"b000\") || ($7 > \"c000\" && $7< \"d000\")) {print $1}\' | tr -t \"\n\" \" \" "
# send -i $ids(1) "../../usertools/dpdk-devbind.py -b igb_uio $cmd\r"

for {set port 0} {$port < $nb_ports} {incr port 1} {
	set out "port_$port\_mm_qcount_$nb_queues\_size_$dma_size\.bin"
	puts "qdma mm-rx test file: $out \n";
	send -i $ids(1) \r

	expect  -i $ids(1) "xilinx-app>"
	send -i $ids(1) "port_init $port $nb_queues $nb_st_queues $ring_size $buff_size\r"

	expect -i $ids(1) "xilinx-app>"
	send -i $ids(1) "dma_to_device $port $nb_queues $mm_input_file $dst_addr $dma_size $repeat\r"

	expect -i $ids(1) "DMA transfer to device is completed successfully"
	send -i $ids(1) \r

	expect -i $ids(1) "xilinx-app>"
	send -i $ids(1) "dma_from_device $port $nb_queues $out $src_addr $dma_size $repeat\r"

	expect -i $ids(1) "DMA transfer from device is completed successfully"
	send -i $ids(1) \r
	expect -i $ids(1) "xilinx-app>"
	#Check if files are there.
	if {[file exists $out]} {
		spawn cmp $mm_input_file $out -n $dma_size
		set ids(2) $spawn_id
		expect -i $ids(2) "differ:" {
			puts -nonewline $err_log_fd "ERROR: Data integrity failed for ' $out\n ' "
		}
		wait
	} else {
			puts -nonewline $err_log_fd "ERROR: ' $out ' file does not exists\n"
	}

	if {$test_mode == "vf_reset"} {
		puts "Test mode is VF Reset\n";
		send -i $ids(1) \r

		expect  -i $ids(1) "xilinx-app>"
		send -i $ids(1) "port_reset $port $nb_queues $nb_st_queues $ring_size $buff_size\r"

		expect -i $ids(1) "Port reset done successfully on port-id: $port"
		send -i $ids(1) \r

		expect -i $ids(1) "xilinx-app>"
		send -i $ids(1) "dma_to_device $port $nb_queues $mm_input_file $dst_addr $dma_size $repeat\r"

		expect -i $ids(1) "DMA transfer to device is completed successfully"
		send -i $ids(1) \r

		expect -i $ids(1) "xilinx-app>"
		send -i $ids(1) "dma_from_device $port $nb_queues $out $src_addr $dma_size $repeat\r"

		expect -i $ids(1) "DMA transfer from device is completed successfully"
		send -i $ids(1) \r
		expect -i $ids(1) "xilinx-app>"
		#Check if files are there.
		if {[file exists $out]} {
			spawn cmp $mm_input_file $out -n $dma_size
			set ids(2) $spawn_id
			expect -i $ids(2) "differ:" {
				puts -nonewline $err_log_fd "ERROR: Data integrity failed for ' $out\n ' "
			}
			wait
		} else {
				puts -nonewline $err_log_fd "ERROR: ' $out ' file does not exists\n"
		}
	} else {
		if {$test_mode == "vf_shutdown"} {
			puts "Test mode is VF Shutdown\n";
			send -i $ids(1) \r

			expect  -i $ids(1) "xilinx-app>"
			send -i $ids(1) "port_remove $port\r"

			expect -i $ids(1) "Port remove done successfully on port-id: $port"
			send -i $ids(1) \r

			expect  -i $ids(1) "xilinx-app>"
			send -i $ids(1) "port_init $port $nb_queues $nb_st_queues $ring_size $buff_size\r"

			expect -i $ids(1) "Error: Port initialization on port-id:$port failed"
			send -i $ids(1) \r
			expect -i $ids(1) "xilinx-app>"
			exit
		}
	}

	send -i $ids(1) \r
	expect -i $ids(1) "xilinx-app>"
	send  -i $ids(1) "port_close $port\r"
	expect -i $ids(1) "xilinx-app>"
}

expect -i $ids(1) "xilinx-app>"

# puts "Unbinding dpdk VF devices \n";
# cmd="lspci | grep -i xilinx | awk -F \" \" \'(($7 > \"a000\" && $7< \"b000\") || ($7 > \"c000\" && $7< \"d000\")) {print $1}\' | tr -t \"\n\" \" \" "
# send -i $ids(1) "../../usertools/dpdk-devbind.py -u $cmd\r"

exit
