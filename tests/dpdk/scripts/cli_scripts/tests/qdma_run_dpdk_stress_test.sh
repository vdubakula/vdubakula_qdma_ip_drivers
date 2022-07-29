#!/usr/bin/expect -f

set timeout -1
set arg1 [lindex $argv 0]
set arg2 [lindex $argv 1]
set arg3 [lindex $argv 2]

set nb_ports $arg1
set nb_queues $arg2
set total_exec_time $arg3

set ring_size 1024
set buff_size 4096
set mm_dma_size_max 524288
set st_dma_size_max 262144


set mm_err_log "mm_errors_log.txt"
set st_err_log "st_errors_log.txt"
set mm_err_fd [open $mm_err_log "w"]
set st_err_fd [open $st_err_log "w"]

set mm_input_file "mm_datafile_1MB.bin"
set st_input_file "datafile_16bit_pattern.bin"

set TEST_STARTTIME [exec date +%s]

spawn ./build/qdma_testapp -c 0xf -n 4
set ids(1) $spawn_id

set TEST_CURTIME [exec date +%s]
set mmelapsed_time [expr $TEST_CURTIME - $TEST_STARTTIME]

puts "Total Execution time in seconds =: $total_exec_time \n";
puts "Initial elapsed time =: $mmelapsed_time \n";
while { $mmelapsed_time < $total_exec_time} {

	for {set port 0} {$port < $nb_ports} {incr port 1} {
		set mm_dma_size [expr { int($mm_dma_size_max * rand()) }]
		set st_dma_size [expr { int($st_dma_size_max * rand()) }]
		set repeat 1
		set out "port_$port\_mm_qcount_$nb_queues\_size_$mm_dma_size\.bin"
		puts "qdma mm-rx test file: $out \n";
		send -i $ids(1) \r

		expect  -i $ids(1) "xilinx-app>"
		send -i $ids(1) "port_init $port $nb_queues 0 $ring_size $buff_size\r"

		expect -i $ids(1) "xilinx-app>"
		send -i $ids(1) "dma_to_device $port $nb_queues $mm_input_file 0 $mm_dma_size $repeat\r"

		expect -i $ids(1) "DMA transfer to device is completed successfully"
		send -i $ids(1) \r

		expect -i $ids(1) "xilinx-app>"
		send -i $ids(1) "dma_from_device $port $nb_queues $out 0 $mm_dma_size $repeat\r"

		expect -i $ids(1) "DMA transfer from device is completed successfully"
		send -i $ids(1) \r
		expect -i $ids(1) "xilinx-app>"
		#Check if files are there.
		if {[file exists $out]} {
			spawn cmp $mm_input_file $out -n $mm_dma_size
			set ids(2) $spawn_id
			expect -i $ids(2) "differ:" {
				puts -nonewline $mm_err_fd "ERROR: Data integrity failed for ' $out\n ' "
			}
			wait
		} else {
				puts -nonewline $mm_err_fd "ERROR: ' $out ' file does not exists\n"
		}

		send -i $ids(1) \r
		expect -i $ids(1) "xilinx-app>"
		send  -i $ids(1) "port_close $port\r"
		expect -i $ids(1) "xilinx-app>"

		set TEST_CURTIME [exec date +%s]
		set mmelapsed_time [expr $TEST_CURTIME - $TEST_STARTTIME]
		puts "\n MM: Elapsed time is: $mmelapsed_time \n";
		if {$mmelapsed_time > $total_exec_time} {
			exit 0
		}

		#ST queues
		set out "port_$port\_st_qcount_$nb_queues\_size_$st_dma_size\.bin"
		puts "qdma st-rx test file: $out \n";
		send -i $ids(1) \r

		expect  -i $ids(1) "xilinx-app>"
		send -i $ids(1) "port_init $port $nb_queues $nb_queues $ring_size $buff_size\r"

		expect -i $ids(1) "xilinx-app>"
		send -i $ids(1) "dma_from_device $port $nb_queues $out 0 $st_dma_size $repeat\r"

		expect -i $ids(1) "xilinx-app>"
		send -i $ids(1) "dma_to_device $port $nb_queues $st_input_file 0 $st_dma_size $repeat\r"

		expect -i $ids(1) "xilinx-app>"
		#Check if files are there.
		if {[file exists $out]} {
			set qsize [expr $st_dma_size / $nb_queues]
			for {set qid 0} {$qid < $nb_queues -1} {incr qid 1} {
				set tmp [expr $qid * $qsize]
				if {$qid == 0 } {
					set skip 0
				} else {
					set skip [expr $qsize + $tmp]
				}

				spawn cmp $st_input_file $out -i 0:$skip -n $qsize
				set ids(2) $spawn_id
				expect -i $ids(2) "differ:" {
					puts -nonewline $st_err_fd "ERROR: Data integrity failed for ' $out\n ' "
				}
			wait
			}
		} else {
			puts -nonewline $st_err_fd "ERROR:' $out ' file does not exists\n"
		}

		send -i $ids(1) \r
		expect -i $ids(1) "xilinx-app>"
		send  -i $ids(1) "port_close $port\r"
		expect -i $ids(1) "xilinx-app>"

		set TEST_CURTIME [exec date +%s]
		set mmelapsed_time [expr $TEST_CURTIME - $TEST_STARTTIME]
		puts "\n ST: Elapsed time is: $mmelapsed_time \n";
		if {$mmelapsed_time > $total_exec_time} {
			exit 0
		}
	}
}

expect -i $ids(1) "xilinx-app>"
wait eof
exit

