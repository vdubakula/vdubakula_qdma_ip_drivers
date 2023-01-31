import pexpect
from pexpect import pxssh
import getpass
import re
import os
import time
import sys
import subprocess
from array import array

nb_pf = 1
PF_PORT = 0
VF_PORT = 1
dpdk_bind_drv = "igb_uio"
child = ""
total_ports = 1
num_queues = 2
st_queues = 1
ring_depth = 1024
pkt_buff_size = 4096
src_addr = 0
dst_addr = 0
size = 262144
iterations = 0
input_filename = "mm_datafile_1MB.bin"
output_filename = "M001_port0_qcount1_size262144.bin"
output_filename_vf = "M001_port1_qcount1_size262144.bin"
DPDK_VER="22.11"
#-----------------------------------------------------
#Path to /HEAD or /REL or /DEV branches
workspace_path = "./../../../../../drivers/dpdk/"

program_name = sys.argv[0]
arg_count = len(sys.argv)

if arg_count < 8 :
    print("Invalid commandline args !!\n")
    print("Usage : python " + program_name + " <bdf> <bind_drv> <num_pfs> <total_queues> <st_queues> <reg_addr> <num_regs>\n")
    print("Example : python " + program_name + "  81000 igb_uio 1 2 1 0x40\n")
    sys.exit(0)

bbddf = sys.argv[1]
dpdk_bind_drv = sys.argv[2]
nb_pf = int(sys.argv[3])
total_queues = int(sys.argv[4])
st_queues = sys.argv[5]
reg_addr = sys.argv[6]
num_regs = sys.argv[7]
nb_pf = 1
nb_vf = 1

pwd = os.getcwd()
print ("pwd = " + pwd)

pci_bus = bbddf[:2]
pci_dev = bbddf[2:4]

print ("nb_pf = " + str(nb_pf))
print ("total_queues = " + str(total_queues))
print ("st_queues = " + str(st_queues))
print("DPDK bind driver: " + dpdk_bind_drv + " \n")

os.chdir(workspace_path + "dpdk-stable-"+DPDK_VER+"/examples/qdma_testapp/")
os.system("chmod +x *.sh")
os.system("sh setup.sh")
pwd = os.getcwd()
print ("pwd = " + pwd)

if dpdk_bind_drv == "vfio-pci":
    for pf in range(0, nb_pf):
        os.system("../../usertools/dpdk-devbind.py -b igb_uio " + pci_bus + ":" + pci_dev + "." + str(pf))

        #set num_vfs for each pf
        num_vf_cmd = "echo " + str(nb_vf) + " > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/max_vfs"
        os.system(num_vf_cmd)

        os.system("../../usertools/dpdk-devbind.py -u " + pci_bus + ":" + pci_dev + "." + str(pf))

    os.system("modprobe vfio-pci")
    for pf in range(0, nb_pf):
        os.system("../../usertools/dpdk-devbind.py -b vfio-pci " + pci_bus + ":" + pci_dev + "." + str(pf))

else:
    for pf in range(0, nb_pf):
        os.system("../../usertools/dpdk-devbind.py -b igb_uio " + pci_bus + ":" + pci_dev + "." + str(pf))

    for pf in range(0, nb_pf):
        #set num_vfs for each pf
        num_vf_cmd = "echo " + str(nb_vf) + " > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/max_vfs"
        os.system(num_vf_cmd)

    print "Bind VF devices"
    lspci_cmd = "lspci | grep -i xilinx | awk -F \" \" \'(($7 > \"a000\" && $7< \"b000\") || ($7 > \"c000\" && $7< \"d000\")) {print $1}\' | tr -t \"\n\" \" \" "
    lspci_out = subprocess.Popen(lspci_cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT).communicate()[0]
    os.system("../../usertools/dpdk-devbind.py -b igb_uio" + " " + str(lspci_out))
    print lspci_out
    print ("lspci_out = " + str(lspci_out))

pf_bdf = pci_bus + ":" + pci_dev + "." + "0"
vf_bdf = lspci_out

port_id = PF_PORT
cmd_testapp_launch = "./build/qdma_testapp -c 0xf -n 4 " + "-a " + pci_bus + ":" + pci_dev + "." + "0" + ", -a "+ lspci_out
cmd_port_init = "port_init" + " " + str(port_id) + " " + str(num_queues) + " " + str(st_queues) + " " + str(ring_depth) + " " + str(pkt_buff_size)
cmd_port_reset = "port_reset" + " " + str(port_id) + " " + str(num_queues) + " " + str(st_queues) + " " + str(ring_depth) + " " + str(pkt_buff_size)
cmd_port_shutdown = "port_remove" + " " + str(port_id)
cmd_pf_reg_dump= "reg_dump" + " " + str(port_id)
cmd_pf_reg_info_read = "reg_info_read" + " " + str(port_id) + " " + str(reg_addr) + " " + str(num_regs)
cmd_dma_to_device = "dma_to_device" + " " + str(port_id) + " " + str(num_queues) + " " + input_filename + " " + str(dst_addr) + " " + str(size) + " " + str(iterations)
cmd_dma_from_device = "dma_from_device" + " " + str(port_id) + " " + str(num_queues) + " " + output_filename + " " + str(src_addr) + " " + str(size) + " " + str(iterations)

port_id = VF_PORT
cmd_vf_port_init = "port_init" + " " + str(port_id) + " " + str(num_queues) + " " + str(st_queues) + " " + str(ring_depth) + " " + str(pkt_buff_size)
cmd_vf_reg_dump= "reg_dump" + " " + str(port_id)
cmd_vf_reg_info_read = "reg_info_read" + " " + str(port_id) + " " + str(reg_addr) + " " + str(num_regs)
cmd_vf_dma_to_device = "dma_to_device" + " " + str(port_id) + " " + str(num_queues) + " " + input_filename + " " + str(dst_addr) + " " + str(size) + " " + str(iterations)
cmd_vf_dma_from_device = "dma_from_device" + " " + str(port_id) + " " + str(num_queues) + " " + output_filename_vf + " " + str(src_addr) + " " + str(size) + " " + str(iterations)

proc_info_reg_dump_cmd = "./build/app/dpdk-proc-info -a " + pf_bdf + ", -a " + vf_bdf + " -- -p 3 -q 0  -g"
proc_info_reg_field_cmd = "./build/app/dpdk-proc-info -a " + pf_bdf + ", -a "+ vf_bdf + " -- -p 3 -q 0 --reg-info" + " " + str(reg_addr)
proc_info_qdevice_cmd = "./build/app/dpdk-proc-info -a "+ pf_bdf + ", -a "+ vf_bdf + " -- -p 3 -q 0  --qdevice"
proc_info_qinfo_cmd = "./build/app/dpdk-proc-info -a " + pf_bdf + ", -a "+ vf_bdf + " -- -p 3 -q 0  --qinfo"
proc_info_desc_dump_tx_cmd = "./build/app/dpdk-proc-info -a " + pf_bdf + ", -a "+ vf_bdf + " -- -p 3 -q 0 --desc-dump tx"
proc_info_desc_dump_rx_cmd = "./build/app/dpdk-proc-info -a " + pf_bdf + ", -a "+ vf_bdf + " -- -p 3 -q 0 --desc-dump rx"
proc_info_desc_dump_cmpt_cmd = "./build/app/dpdk-proc-info -a " + pf_bdf + ", -a "+ vf_bdf + " -- -p 3 -q 0 --desc-dump cmpt"
proc_info_stats_cmd = "./build/app/dpdk-proc-info -a " + pf_bdf + ", -a "+ vf_bdf + " -- -p 3 -q 0 --stats"

try:
	print "PF DMA transfers"
	port_id = PF_PORT
	print ("cmd_testapp_launch = " + str(cmd_testapp_launch))
	child = pexpect.spawn(cmd_testapp_launch)
	child.expect('xilinx-app>')
	print ("cmd_port_init = " + str(cmd_port_init))
	child.sendline(cmd_port_init)
	child.expect('xilinx-app>')
	print ("cmd_dma_to_device = " + str(cmd_dma_to_device))
	child.sendline(cmd_dma_to_device)
	child.expect('xilinx-app>')
	print ("cmd_dma_from_device = " + str(cmd_dma_from_device))
	child.sendline(cmd_dma_from_device)
	child.expect('xilinx-app>')
	print child.before

	print "VF DMA transfers"
	print ("cmd_vf_port_init = " + str(cmd_vf_port_init))
	child.sendline(cmd_vf_port_init)
	child.expect('xilinx-app>')
	print ("cmd_vf_dma_to_device = " + str(cmd_vf_dma_to_device))
	child.sendline(cmd_vf_dma_to_device)
	child.expect('xilinx-app>')
	print ("cmd_vf_dma_from_device = " + str(cmd_vf_dma_from_device))
	child.sendline(cmd_vf_dma_from_device)
	child.expect('xilinx-app>')
	print child.before

	os.chdir(workspace_path + "dpdk-stable-"+DPDK_VER+"/")
	pwd = os.getcwd()
	print ("pwd = " + pwd)
	sys.stdout.flush()
	print ("proc_info_reg_dump_cmd = " + str(proc_info_reg_dump_cmd))
	os.system(proc_info_reg_dump_cmd)
	print ("proc_info_reg_field_cmd = " + str(proc_info_reg_field_cmd))
	os.system(proc_info_reg_field_cmd)
	print ("proc_info_qdevice_cmd = " + str(proc_info_qdevice_cmd))
	os.system(proc_info_qdevice_cmd)
	print ("proc_info_qinfo_cmd = " + str(proc_info_qinfo_cmd))
	os.system(proc_info_qinfo_cmd)
	print ("proc_info_desc_dump_tx_cmd = " + str(proc_info_desc_dump_tx_cmd))
	os.system(proc_info_desc_dump_tx_cmd)
	print ("proc_info_desc_dump_rx_cmd = " + str(proc_info_desc_dump_rx_cmd))
	os.system(proc_info_desc_dump_rx_cmd)
	print ("proc_info_desc_dump_cmpt_cmd = " + str(proc_info_desc_dump_cmpt_cmd))
	os.system(proc_info_desc_dump_cmpt_cmd)
	print ("proc_info_stats_cmd = " + str(proc_info_stats_cmd))
	os.system(proc_info_stats_cmd)
	sys.stdout.flush()

	print "PF register dump"
	print ("cmd_pf_reg_dump = " + str(cmd_pf_reg_dump))
	child.sendline(cmd_pf_reg_dump)
	child.expect('xilinx-app>')
	print child.before
	print ("cmd_pf_reg_info_read = " + str(cmd_pf_reg_info_read))
	child.sendline(cmd_pf_reg_info_read)
	child.expect('xilinx-app>')
	print child.before

	print "VF register dump"
	print ("cmd_vf_reg_dump = " + str(cmd_vf_reg_dump))
	child.sendline(cmd_vf_reg_dump)
	child.expect('xilinx-app>')
	print child.before
	print ("cmd_vf_reg_info_read = " + str(cmd_vf_reg_info_read))
	child.sendline(cmd_vf_reg_info_read)
	child.expect('xilinx-app>')
	print child.before

	child.sendcontrol('d')
	time.sleep(2)

	os.system("./usertools/dpdk-devbind.py -u " + lspci_out)
	os.system("echo 0" + " > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/max_vfs")
	os.system("./usertools/dpdk-devbind.py -u " + pci_bus + ":" + pci_dev + "." + str(pf))

except pxssh.ExceptionPxssh, e:
    print "pxssh failed on login."
    print str(e)
