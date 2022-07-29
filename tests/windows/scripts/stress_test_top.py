import sys
import os
import getopt
from colorama import init
from colorama import Fore, Back, Style
from qdma_run_stress_test import run_stress_test

# Global Variables / Parameters
bus_no = "65"
test_mode = 0b01110 # poll, intr, aggr
run_time = 60 # in seconds

def print_error(msg, usage_msg = 1):
	print (Fore.WHITE + Back.RED + msg)
	print (Style.RESET_ALL)
	if (usage_msg):
		usage()
	sys.exit(1)

def print_warning(msg) :
	print (Fore.WHITE + Back.YELLOW + msg)
	print (Style.RESET_ALL)
	sys.exit(1)

def print_success(msg):
	print (Fore.GREEN + msg)
	print (Style.RESET_ALL)

def print_msg(msg):
	print (Style.RESET_ALL)
	print (msg)
	print (Style.RESET_ALL)

def usage():
	print ("usage : python %s [OPTIONS]\n" % sys.argv[0])
	print ("Performs stress test on QDMA IP\n\n")
	print ("Mandatory arguments")
	print ("\t -b, --bus-no\t\t PCI bus number")
	print ("\t -m, --test-mode\t Test Mode(b0 -> dummy, b1 -> poll, b2 -> intr, b3 -> Aggr, b4 -> auto)")
	print ("\t -t, --exec-time\t Test Execution time in HH:MM:SS format")
	print ("\t -h, --help\t Shows this help message")
	print ("\n")

	sys.stdout.flush()

def strtoint(str):
	if (str[0] == '0' and str[1] == 'x') :
		int_val = int(str, base=16)
	elif(str[0] == '0' and str[1] == 'o') :
		int_val = int(str, base=8)
	elif(str[0] == '0' and str[1] == 'b') :
		int_val = int(str, base=2)
	else :
		int_val = int(str, base=10)

	return int_val

if __name__=="__main__":
	init()
	print_success ("Welcome to QDMA Stress Test")
	try:
		opts, args = getopt.getopt(sys.argv[1:], "b:m:t:q:h", ['bus-no=', 'test-mode=', 'exec-time=', 'queue-cnt=', 'help'])
	except getopt.GetoptError:
		print_error("ERROR: options are not properly provided..please look into below help\n");

	is_bus_valid = False
	is_testmode_valid = False
	is_exec_time_valid = False
	# Retrieve the CLI arguments
	for opt, arg in opts:
		if opt in ('-h', '--help'):
			usage()
			sys.exit(0)
		elif opt in ('-b', '--bus-no'):
			bus_no = arg
			is_bus_valid = True
		elif opt in ('-m', '--test-mode'):
			test_mode = strtoint(arg)
			is_testmode_valid = True
		elif opt in ('-t', '--exec-time'):
			exec_time = arg.split(":")
			is_exec_time_valid = True
		elif opt in ('-q', '--queue-cnt'):
			no_q = arg
			is_no_q_valid = True
		else:
			usage()
			sys.exit(1)

	# Parameter Validation
	if ((not is_bus_valid) or (not is_testmode_valid) or (not is_no_q_valid) or (not is_exec_time_valid)) :
		print_error("All mandatory arguments are not provided..please look into below help")

	if (strtoint(bus_no) > 255) :
		print_error("Invalid bus number provided..")

	if (bus_no[0] == '0' and (bus_no[1] == 'x' or bus_no[1] == 'X')) :
		bus_no = bus_no[2:]

	if (no_q[0] == '0' and (no_q[1] == 'x' or no_q[1] == 'X')) :
		no_q = no_q[2:]

	no_q = strtoint(no_q)
	if (no_q > 2048) :
		print_error("Queue count more than 2048 is not supported..")

	if (not (test_mode & 0x1E)) :
		print_error("Valid test mode is not provided..please look into below help")

	hrs = strtoint(exec_time[0])
	mins = strtoint(exec_time[1])
	secs = strtoint(exec_time[2])
	if (mins >= 60 or secs >= 60) :
		print_error("-t/--exec-time option is not in standard HH:MM:SS format")
	if (hrs == 0 and mins == 0 and secs == 0) :
		print_error("-t/--exec-time option given as 00:00:00")

	run_time = (hrs * 60 * 60) + (mins * 60) + secs;

	print_msg("Parameters : bus_no : %s, test_mode : 0x%X, no_q : 0x%X, run_time : %d" % (bus_no, test_mode, no_q, run_time))

	if (test_mode & 0x02) :
		run_stress_test("poll", bus_no, no_q, run_time)
	if (test_mode & 0x04) :
		run_stress_test("intr", bus_no, no_q, run_time)
	if (test_mode & 0x08) :
		run_stress_test("aggr", bus_no, no_q, run_time)
	if (test_mode & 0x10) :
		#run_stress_test("auto", bus_no, no_q, run_time)
		print_warning ("Auto Mode is not yet implemented")

