import pexpect
from pexpect import pxssh
import getpass
import re
import os
import time
import sys
import subprocess
from array import array


base_port = 5555
vm_ram = 25534
nb_pf = 1
pf_vfs_cnt = array('i')
vm_num_vfs = array('i')
pf_vfs_devid = ["a03f", "a13f", "a23f", "a33f", "c03f", "c13f", "c23f", "c33f"]
pf_vfs_bdfs = [[], [], [], []]
vm_sid = ["", "", "", "", "", "", "", "", ""]
vf_pf_qs = []
MAX_PFS = 4
MAX_VMS = 4 # existing VM images on a given system.
VM_CFG_START = 8
PF_PORT = 0
VF_PORT = 1
dpdk_bind_drv = "igb_uio"
dpdk_bind_drv_idx = 0
child = ""

total_ports = 1
num_queues = 1
st_queues = 0
ring_depth = 1024
pkt_buff_size = 4096
src_addr = 0
dst_addr = 0
size = 262144
iterations = 0
input_filename = "mm_datafile_1MB.bin"
output_filename = "M001_port0_qcount1_size262144.bin"
output_filename_vf = "M001_port1_qcount1_size262144.bin"
test_mode = "vf_reset"
DPDK_VER = "22.11"

#-----------------------------------------------------
#Path to /HEAD or /REL or /DEV branches
workspace_path = "./../../../../../drivers/dpdk/"

program_name = sys.argv[0]
arg_count = len(sys.argv)

if arg_count < 8 :
    print("Invalid commandline args !!\n")
    print("Usage : python " + program_name + " <bdf> <bind_drv> <num_pfs> <total_queues> <st_queues> <test_mode> <vm_ram> <vm_image_path> <num_vms> <vm1_config> <vm2_config> ... <vm-n_config> \n")
    print("Example : python " + program_name + "  81000 igb_uio 1 1024 512  vf_reset  25534 /scratch 2  \"1 2 3 0\"  \"3 2 2 1\" \n")
    sys.exit(0)

bbddf = sys.argv[1]
dpdk_bind_drv = sys.argv[2]
nb_pf = int(sys.argv[3])
total_queues = int(sys.argv[4])
st_queues = sys.argv[5]
test_mode = sys.argv[6]
vm_ram = int(sys.argv[7])
vm_image_path = sys.argv[8]
nb_vms = int(sys.argv[9])

port_id = PF_PORT
cmd_testapp_launch = "./build/qdma_testapp -c 0xf -n 4"
cmd_port_init = "port_init" + " " + str(port_id) + " " + str(num_queues) + " " + str(st_queues) + " " + str(ring_depth) + " " + str(pkt_buff_size)
cmd_port_reset = "port_reset" + " " + str(port_id) + " " + str(num_queues) + " " + str(st_queues) + " " + str(ring_depth) + " " + str(pkt_buff_size)
cmd_port_shutdown = "port_remove" + " " + str(port_id)
cmd_dma_to_device = "dma_to_device" + " " + str(port_id) + " " + str(num_queues) + " " + input_filename + " " + str(dst_addr) + " " + str(size) + " " + str(iterations)
cmd_dma_from_device = "dma_from_device" + " " + str(port_id) + " " + str(num_queues) + " " + output_filename + " " + str(src_addr) + " " + str(size) + " " + str(iterations)

port_id = VF_PORT
cmd_vf_port_init = "port_init" + " " + str(port_id) + " " + str(num_queues) + " " + str(st_queues) + " " + str(ring_depth) + " " + str(pkt_buff_size)
cmd_vf_dma_to_device = "dma_to_device" + " " + str(port_id) + " " + str(num_queues) + " " + input_filename + " " + str(dst_addr) + " " + str(size) + " " + str(iterations)
cmd_vf_dma_from_device = "dma_from_device" + " " + str(port_id) + " " + str(num_queues) + " " + output_filename_vf + " " + str(src_addr) + " " + str(size) + " " + str(iterations)

#intitialize all Pfs numvfs to '0'.
for pf in range(0, nb_pf):
    pf_vfs_cnt.insert(pf, 0)
for vm in range(0, nb_vms):
    vm_num_vfs.insert(vm, 0)

pci_bus = bbddf[:2]
pci_dev = bbddf[2:4]

print ("nb_pf = " + str(nb_pf))
print ("total_queues = " + str(total_queues))
print ("st_queues = " + str(st_queues))
print ("test_mode = " + str(test_mode))
print ("vm_ram = " + str(vm_ram))
print("DPDK bind driver: " + dpdk_bind_drv + " \n")

p=os.popen("qemu-system-x86_64 --version")
qemu_ver = p.read()
temp = qemu_ver.split(' ')
temp[3]=temp[3].split('(')
qemu_version=temp[3][0]

if nb_vms > MAX_VMS:
    print("Invalid <vm_count>, max allowed is " + str(MAX_VMS) + " !!\n")
    sys.exit(0)

for vm_id in range(1, nb_vms + 1):
    idx = VM_CFG_START + vm_id #vm config starts from index 8
    vm_cfg = str(sys.argv[idx]) # vm_cfg = "3 0 1 1"
    vm_vfs = vm_cfg.split()
    for pf in range(0, nb_pf):
        pf_vfs_cnt[pf] = pf_vfs_cnt[pf] + int(vm_vfs[pf])
        vm_num_vfs[vm_id - 1] = vm_num_vfs[vm_id - 1] + int(vm_vfs[pf])

pwd = os.getcwd()
os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER + "/examples/qdma_testapp/")
os.system("chmod +x *.sh")
os.system("sh setup.sh")

if dpdk_bind_drv == "vfio-pci":
    for pf in range(0, nb_pf):
        os.system("../../usertools/dpdk-devbind.py -b igb_uio " + pci_bus + ":" + pci_dev + "." + str(pf))

        #set num_vfs for each pf
        num_vf_cmd = "echo " + str(pf_vfs_cnt[pf]) + " > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/max_vfs"
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
        num_vf_cmd = "echo " + str(pf_vfs_cnt[pf]) + " > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/max_vfs"
        os.system(num_vf_cmd)

    if (test_mode == "pf_reset" or test_mode == "pf_shutdown"):
        print "Bind VF devices"
        lspci_cmd = "lspci | grep -i xilinx | awk -F \" \" \'(($7 > \"a000\" && $7< \"b000\") || ($7 > \"c000\" && $7< \"d000\")) {print $1}\' | tr -t \"\n\" \" \" "
        lspci_out = subprocess.Popen(lspci_cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT).communicate()[0]
        os.system("../../usertools/dpdk-devbind.py -b igb_uio" + " " + str(lspci_out))

print pwd
print "PF DMA transfers"
port_id = PF_PORT
child = pexpect.spawn("./build/qdma_testapp -c 0xf -n 4")
child.expect('xilinx-app>')
print cmd_port_init
child.sendline(cmd_port_init)
child.expect('xilinx-app>')
print cmd_dma_to_device
child.sendline(cmd_dma_to_device)
child.expect('xilinx-app>')
print cmd_dma_from_device
child.sendline(cmd_dma_from_device)
child.expect('xilinx-app>')
print child.before

if (test_mode == "pf_reset" or test_mode == "pf_shutdown"):
    print "VF DMA transfers"
    port_id = VF_PORT
    print cmd_vf_port_init
    child.sendline(cmd_vf_port_init)
    child.expect('xilinx-app>')
    print cmd_vf_dma_to_device
    child.sendline(cmd_vf_dma_to_device)
    child.expect('xilinx-app>')
    print cmd_vf_dma_from_device
    child.sendline(cmd_vf_dma_from_device)
    child.expect('xilinx-app>')
    print child.before
    os.chdir(pwd)

if dpdk_bind_drv == "vfio-pci":
    lspci_cmd = "lspci | grep -i xilinx | awk -F \" \" \'(($7 > \"a000\" && $7< \"b000\") || ($7 > \"c000\" && $7< \"d000\")) {print $7}\' | tr -t \"\n\" \" \" "
    lspci_out = subprocess.Popen(lspci_cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT).communicate()[0]
    id_list = list(set(lspci_out.replace('\n', ' ').strip().split(' ')))

    for i in range(len(id_list)):
        os.system("echo " + "\"10ee " + str(id_list[i]) + "\"" + " > /sys/bus/pci/drivers/vfio-pci/new_id")

if (test_mode == "vf_reset" or test_mode == "vf_shutdown"):
	cmd = "lspci | grep -i xilinx | awk '{print $1\" \"$7}'"
	a = subprocess.Popen(cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
	output = a.communicate()[0]
	out = output.replace('\n',' ').strip().split(' ')
	pci_dic = dict(zip( * [iter(out)] * 2))

	for k, v in pci_dic.iteritems():
		for pf in range(0, nb_pf):
			if (v == pf_vfs_devid[pf]) or (v == pf_vfs_devid[pf + MAX_PFS]):
				pf_vfs_bdfs[pf].append(k)

	for pf in range(0, nb_pf):
		print pf_vfs_bdfs[pf]

	for vm_id in range(1, nb_vms + 1):
		idx = VM_CFG_START + vm_id #vm config starts from index 8
		vm_cfg = str(sys.argv[idx]) # vm_cfg = "3 0 1 1"
		vm_vfs = vm_cfg.split()
		vm_bdf_assign = ""
		vm_cmd = ""
		vf_bdf = ""
		os.system("modprobe vfio-pci")
		for pf in range(0, nb_pf):
			pf_vfs = int(vm_vfs[pf])
			for x in range(0, pf_vfs):
				if (qemu_version == "2.5.0") :
					if dpdk_bind_drv == "vfio-pci":
						vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + pf_vfs_bdfs[pf].pop()
					else:
						vm_bdf_assign = vm_bdf_assign + " -device pci-assign,host=" + pf_vfs_bdfs[pf].pop()
				else:
					vf_bdf = pf_vfs_bdfs[pf].pop()
					os.system("../../usertools/dpdk-devbind.py -u " + vf_bdf)
					os.system("../../usertools/dpdk-devbind.py -b vfio-pci " + vf_bdf)
					vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + vf_bdf
		port = base_port + vm_id
		vm_cmd = "qemu-system-x86_64 -cpu host -enable-kvm -m " + str(vm_ram) + " -smp sockets=1,cores=4 -hda " + vm_image_path + "/vm" + str(vm_id) + ".qcow2  -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::" + str(port) + "-:22 " + vm_bdf_assign + " -vnc :" + str(port) + "  &"
		print vm_cmd
		os.system(vm_cmd)
	# Let vms up
	time.sleep(180)

try:
    if (test_mode == "vf_reset" or test_mode == "vf_shutdown"):
		for vm_id in range(1, nb_vms + 1):
			print("VM ID =" + str(vm_id))
			vm_sid[vm_id] = pxssh.pxssh(timeout = 5000)
			vm_sid[vm_id].login ("127.0.0.1", "root", "dpdk", port = base_port + vm_id)
			os.chdir(pwd)
			os.system("sshpass -p dpdk rsync -avz  -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "dpdk-stable-" + DPDK_VER + "   root@127.0.0.1:/home/dpdk/")

			vm_sid[vm_id].sendline('cd /home/dpdk/dpdk-stable-' + DPDK_VER)
			vm_sid[vm_id].prompt()
			print vm_sid[vm_id].before
			vm_sid[vm_id].sendline('rm -rf build')
			vm_sid[vm_id].prompt()
			print vm_sid[vm_id].before
			vm_sid[vm_id].sendline ('meson build')
			vm_sid[vm_id].sendline ('cd build')
			vm_sid[vm_id].sendline ('ninja')
			vm_sid[vm_id].sendline ('ninja install')
			vm_sid[vm_id].sendline ('ldconfig')
			vm_sid[vm_id].sendline ('cd ../dpdk-kmods/linux/igb_uio')
			vm_sid[vm_id].sendline ('make')
			vm_sid[vm_id].sendline ('chmod 777 igb_uio.ko')
			vm_sid[vm_id].sendline ('../../..')
			vm_sid[vm_id].prompt()
			print vm_sid[vm_id].before

			if dpdk_bind_drv == "vfio-pci":
				vm_sid[vm_id].sendline('bash ' + "modprobe vfio-pci")
				vm_sid[vm_id].sendline('bash ' + "echo 1 > /sys/module/vfio/parameters/enable_unsafe_noiommu_mode")
				vm_sid[vm_id].sendline('bash ' + "./usertools/dpdk-devbind.py -b vfio-pci 00:04.0")

			vm_sid[vm_id].sendline('cd /home/dpdk/dpdk-stable-' + DPDK_VER + '/examples/qdma_testapp/')
			vm_sid[vm_id].sendline('chmod +x *.sh')
			vm_sid[vm_id].sendline('sh setup.sh')
			vm_sid[vm_id].sendline('sh dpdk_bind_devices.sh')
			vm_sid[vm_id].prompt()
			print vm_sid[vm_id].before

			vm_sid[vm_id].sendline('chmod +x qdma_run_reset_shutdown_tests.sh')
			cmd = "./qdma_run_reset_shutdown_tests.sh " + str(total_ports) +" " + str(num_queues) + " " + str(st_queues) + " " + test_mode + " > dpdk_reset_shutdown_vm_log.txt"
			print cmd
			vm_sid[vm_id].sendline (cmd)
			vm_sid[vm_id].timeout = 100000
			vm_sid[vm_id].sendline('sh dpdk_unbind_devices.sh')
			vm_sid[vm_id].prompt()
			print vm_sid[vm_id].before

			os.chdir(pwd)
			os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER + "/examples/qdma_testapp/")
			os.system("mkdir -p vm" + str(vm_id) + "_logs/")
			os.system("sshpass -p dpdk scp -r -P " + str(base_port + vm_id) + " root@127.0.0.1:/home/dpdk/dpdk-stable-" + DPDK_VER + "/examples/qdma_testapp/dpdk_error_log.txt ./vm" + str(vm_id) + "_logs/")
			os.system("sshpass -p dpdk scp -r -P " + str(base_port + vm_id) + " root@127.0.0.1:/home/dpdk/dpdk-stable-" + DPDK_VER + "/examples/qdma_testapp/dpdk_reset_shutdown_vm_log.txt ./vm" + str(vm_id) + "_logs/")
			os.system("tar -cvzf vm" + str(vm_id) + "_logs.tar.gz vm" + str(vm_id) + "_logs/")
			print ("echo --------------------------------------------vm_" + str(vm_id) + " done---------------------------------------------------------------")

    os.chdir(pwd)
    os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER + "/examples/qdma_testapp/")
    #child.send('\r')
    if (test_mode == "pf_reset"):
        print cmd_port_reset
        child.sendline(cmd_port_reset)
        child.expect('xilinx-app>')
        print child.before

        print("PF DMA transfer after PF reset command\n")
        print cmd_dma_to_device
        child.sendline(cmd_dma_to_device)
        child.expect('xilinx-app>')
        print child.before

        print cmd_dma_from_device
        child.sendline(cmd_dma_from_device)
        child.expect('xilinx-app>')
        print child.before

        print("VF DMA transfer after PF reset command\n")
        print cmd_vf_dma_to_device
        child.sendline(cmd_vf_dma_to_device)
        child.expect('xilinx-app>')
        print cmd_vf_dma_from_device
        child.sendline(cmd_vf_dma_from_device)
        child.expect('xilinx-app>')
        print child.before

    elif (test_mode == "pf_shutdown"):
        print cmd_port_shutdown
        child.sendline(cmd_port_shutdown)
        child.expect('xilinx-app>')
        print child.before

        print("VF DMA transfer after PF shutdown command\n")
        print cmd_vf_dma_to_device
        child.sendline(cmd_vf_dma_to_device)
        child.expect('xilinx-app>')
        print cmd_vf_dma_from_device
        child.sendline(cmd_vf_dma_from_device)
        child.expect('xilinx-app>')
        print child.before

    elif (test_mode == "vf_reset"):
        print("PF DMA transfer after VF reset command\n")
        print cmd_dma_to_device
        child.sendline(cmd_dma_to_device)
        child.expect('xilinx-app>')

        print cmd_dma_from_device
        child.sendline(cmd_dma_from_device)
        child.expect('xilinx-app>')
    elif (test_mode == "vf_shutdown"):
        print("PF DMA transfer after VF shutdown command\n")
        print cmd_dma_to_device
        child.sendline(cmd_dma_to_device)
        child.expect('xilinx-app>')

        print cmd_dma_from_device
        child.sendline(cmd_dma_from_device)
        child.expect('xilinx-app>')
    else:
        print("Invalid test mode\n")

    child.sendcontrol('d')
    time.sleep(10)

    if (test_mode == "vf_reset" or test_mode == "vf_shutdown"):
        for vm_id in range(1, nb_vms + 1):
            vm_sid[vm_id].sendline('poweroff')

    for pf in range(0, nb_pf):
        #Remove num_vfs for each pf
        num_vf_cmd = "echo 0 > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/max_vfs"
        print num_vf_cmd
        os.system(num_vf_cmd)

except pxssh.ExceptionPxssh, e:
    print "pxssh failed on login."
    print str(e)
