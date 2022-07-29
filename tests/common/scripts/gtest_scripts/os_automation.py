from pexpect import pxssh
import getpass
import os
import time
import sys
import subprocess
from array import array

test = "default_pf"
base_port = 5556
vm_ram = int(sys.argv[2]) 
bbddff = sys.argv[4]
pci_bus = bbddff[:2]
pci_dev = bbddff[2:4]
nb_pf = 4
driver_path = sys.argv[3]
pf_vfs_cnt = [1, 1, 1, 1] 
Ultrascale=0
EQDMA=0
if sys.argv[1] == "Ultrascale":
	Ultrascale=1
	pf_devids = ["903f", "913f", "923f", "933f"] 
	pf_bdfs = [[], [], [], []]
	pf_vfs_devid = ["a03f", "a13f", "a23f", "a33f"]
	pf_vfs_bdfs = [[], [], [], []]
elif sys.argv[1] == "Versal":
	Ultrascale=0
	pf_devids = ["b03f", "b13f", "b23f", "b33f"] 
	pf_bdfs = [[], [], [], []]
	pf_vfs_devid = ["c03f", "c13f", "c23f", "c33f"]
	pf_vfs_bdfs = [[], [], [], []]
elif sys.argv[1] == "EQDMA":
	EQDMA=1
	pf_devids = ["903f", "913f", "923f", "933f"] 
	pf_bdfs = [[], [], [], []]
	pf_vfs_devid = ["a03f", "a13f", "a23f", "a33f"]
	pf_vfs_bdfs = [[], [], [], []]
else:
	print "Invalid device"
	exit(1)

config_file_in = "./gtest_configs_qdma_soft/default_vf/default_vf.txt"
config_file_out = "./default_vf.txt"
MAX_VMS = 4
VM_CFG_START = 6

vm_imgs_path = []

program_name = sys.argv[0]
arg_count = len(sys.argv)
compile_once = 1
result_file = open("Result.txt", "w+")

def test_os(pf_vf, src_dict, logs_dir, vm_img, printos=True):
	global base_port
	global pf_vfs_cnt
	global compile_once
	drv_used = "linux"
	nb_vms = nb_pf + 4
	gtest_script_path = "/home/dpdk/Test/sw_test/common/scripts/gtest_scripts/"
	gtest_cmd = ""
	if pf_vf == "default_pf" :
		os.system("rmmod vfio-pci")
		os.system("rm /etc/modprobe.d/vfio.conf")
		if EQDMA == 1:
			os.system("echo \"options vfio-pci ids=10EE:903F,10EE:913F,10EE:923F,10EE:933F\" >> /etc/modprobe.d/vfio.conf")
			gtest_cmd = "./gtest_top.sh pci_dev_list.txt gtest_configs_eqdma/os_automation/default_pf ../../../../sw_host/linux ../../../../sw_test/common/apps/qdma_test pf_vf linux 0"
		elif Ultrascale == 1:
			os.system("echo \"options vfio-pci ids=10EE:903F,10EE:913F,10EE:923F,10EE:933F\" >> /etc/modprobe.d/vfio.conf")
			gtest_cmd = "./gtest_top.sh pci_dev_list.txt gtest_configs_qdma_soft/os_automation/default_pf ../../../../sw_host/linux ../../../../sw_test/common/apps/qdma_test pf_vf linux 0"
		else :
			os.system("echo \"options vfio-pci ids=10EE:B03F,10EE:B13F,10EE:B23F,10EE:B33F\" >> /etc/modprobe.d/vfio.conf")
			gtest_cmd = "./gtest_top.sh pci_dev_list.txt gtest_configs_qdma_hard_s80/os_automation/default_pf ../../../../sw_host/linux ../../../../sw_test/common/apps/qdma_test pf_vf linux 0"
		os.system("modprobe vfio-pci")
	elif pf_vf == "default_vf" :
		os.system("rmmod vfio-pci")
		os.system("rm /etc/modprobe.d/vfio.conf")
		if EQDMA == 1:
			os.system("echo \"options vfio-pci ids=10EE:A03F,10EE:A13F,10EE:A23F,10EE:A33F\" >> /etc/modprobe.d/vfio.conf")
			gtest_cmd = "./gtest_top.sh 00400 gtest_configs_eqdma/os_automation/default_vf ../../../../sw_host/linux ../../../../sw_test/common/apps/qdma_test vf linux 0"
		elif Ultrascale == 1:
			os.system("echo \"options vfio-pci ids=10EE:A03F,10EE:A13F,10EE:A23F,10EE:A33F\" >> /etc/modprobe.d/vfio.conf")
			gtest_cmd = "./gtest_top.sh 00400 gtest_configs_qdma_soft/os_automation/default_vf ../../../../sw_host/linux ../../../../sw_test/common/apps/qdma_test vf linux 0"
		else:
			os.system("echo \"options vfio-pci ids=10EE:C03F,10EE:C13F,10EE:C23F,10EE:C33F\" >> /etc/modprobe.d/vfio.conf")
			gtest_cmd = "./gtest_top.sh 00400 gtest_configs_qdma_hard_s80/os_automation/default_vf ../../../../sw_host/linux ../../../../sw_test/common/apps/qdma_test vf linux 0"
		os.system("modprobe vfio-pci")


		for pf in range(0, 3):
			pf_vfs_cnt[pf] = 1

		if drv_used == "linux":
			if compile_once == 1:
				os.system("cd "  + driver_path + "/sw_host/linux ; sh make_libqdma.sh; make install-mods; cd -")
				compile_once = 0
			os.system("modprobe qdma_pf")

		for pf in range(0, nb_pf):
			#set num_vfs for each pf
			if EQDMA == 1:
				num_vf_cmd = "echo " + str(pf_vfs_cnt[pf]) + " > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/sriov_numvfs"
			elif Ultrascale == 1:
				num_vf_cmd = "echo " + str(pf_vfs_cnt[pf]) + " > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/sriov_numvfs"
			else:
				num_vf_cmd = "echo " + str(pf_vfs_cnt[pf]) + " > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/sriov_numvfs"
			os.system(num_vf_cmd)

	cmd = "lspci | grep -i xilinx | awk '{print $1\" \"$7}'"
	a = subprocess.Popen(cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
	output = a.communicate()[0]
	out = output.replace('\n',' ').strip().split(' ')
	pci_dic = dict(zip( * [iter(out)] * 2))

	for k, v in pci_dic.iteritems():
		for pf in range(0, nb_pf):
			if (v == pf_devids[pf]):
				pf_bdfs[pf].append(k)

	for k, v in pci_dic.iteritems():
		for pf in range(0, nb_pf):
			if (v == pf_vfs_devid[pf]):
				pf_vfs_bdfs[pf].append(k)

	vm_bdf_assign = ""

	if pf_vf == "default_vf" :
		for x in range(0, len(pf_vfs_bdfs)):
			vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + pf_vfs_bdfs[x].pop()
	else :
		for pf in range(0, len(pf_bdfs)):
			vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + pf_bdfs[pf].pop()
		
	vm_cmd = "qemu-system-x86_64 -cpu host -enable-kvm -m " + str(vm_ram) + " -smp sockets=1,cores=4 -hda " + vm_img + "  -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::" + str(base_port) + "-:22 " + vm_bdf_assign + " -vnc :" + str(base_port) + "  &"
	print "-------------------"
	print "  Starting OS      "
	print "\t\t" + vm_cmd
	print "-------------------"
	os.system(vm_cmd)
	
	# Let vms up
	time.sleep(120)
	#-----------------------------------------------------
	
	try:
		os.system("ssh-keygen -f \"/root/.ssh/known_hosts\" -R \"[127.0.0.1]:" + str(base_port) + "\"")
		s = pxssh.pxssh(timeout = 5000)
		s.login ("127.0.0.1", "root", "dpdk", port = base_port)
		s.sendline ('rm -rf /home/dpdk/*')
		s.prompt()
		print s.before
		s.sendline ('mkdir -p /home/dpdk/Test/{sw_host/{linux,qdma_access},sw_test/common/scripts/gtest_scripts,sw_test/common/apps/qdma_test}')
		s.prompt()
		print s.before
		s.sendline ('cd /home/dpdk/Test')
		s.prompt()
		print s.before
		s.sendline ('chmod -R 0777 ./*')
		s.prompt()
		print s.before
		#checking if sw_host and sw_test dirs are present
		if (os.path.isdir(src_dict + 'sw_host') and os.path.isdir(src_dict + 'sw_test')) :
			os.system("sshpass -p dpdk scp -o StrictHostKeyChecking=no -P " + str(base_port) + " -r " + src_dict + "sw_host/linux/*  dpdk@127.0.0.1:/home/dpdk/Test/sw_host/linux/")
			os.system("sshpass -p dpdk scp -o StrictHostKeyChecking=no -P " + str(base_port) + " -r " + src_dict + "sw_host/qdma_access/*  dpdk@127.0.0.1:/home/dpdk/Test/sw_host/qdma_access/")
			os.system("sshpass -p dpdk scp -o StrictHostKeyChecking=no -P " + str(base_port) + " -r " + src_dict + "sw_test/common/scripts/gtest_scripts/*  dpdk@127.0.0.1:/home/dpdk/Test/sw_test/common/scripts/gtest_scripts/")							
			os.system("sshpass -p dpdk scp -o StrictHostKeyChecking=no -P " + str(base_port) + " -r " + src_dict + "sw_test/common/apps/qdma_test/*  dpdk@127.0.0.1:/home/dpdk/Test/sw_test/common/apps/qdma_test/")
		else :
			print "Invalid Directory hence exiting"
			s.sendline ("shutdown -h 1")
			s.prompt()
			print s.before
			exit()

		s.sendline ('ls /home/dpdk/Test/sw_test/common/apps/qdma_test/')
		s.prompt()
		print s.before
		s.sendline ('echo "OS Under Test"')
		s.prompt()
		print s.before
		s.sendline ('if [ -f /etc/os-release ];then cat /etc/os-release; else cat /etc/lsb-release ; fi')
		s.prompt()
		print s.before
		if printos:
			result_file.write("Testing OS:\n")
			result_file.write("----------\n")
			result_file.write(s.before.strip("cat /etc/os-release"))
			s.sendline ('uname -r')
			s.prompt()
			result_file.write(s.before)

		s.sendline ('echo -----------OS logs------------')
		s.prompt()
		print s.before.strip("echo -----------OS logs------------")
		s.sendline ('cd ' + gtest_script_path)
		s.prompt()
		print s.before
		if pf_vf == "default_pf" :
			s.sendline ('python populate_pf_bdfs.py ' + sys.argv[1])
			s.prompt()
			print s.before
			s.sendline ('cat pci_dev_list.txt')
			s.prompt()
			print s.before
		s.sendline ('bash ' + gtest_cmd)
		s.prompt(timeout=500000)
		print s.before
		s.sendline ('echo $? ')
		s.prompt()
		outputstr = s.before
		print outputstr
		if (outputstr.find("1") == -1) :
			if pf_vf == "default_pf" :
				result_file.write("PF Testing: Passed\n")
			else:
				result_file.write("VF Testing: Passed\n")
		else :
			if pf_vf == "default_pf" :
				result_file.write("PF Testing: Failed\n")
			else:
				result_file.write("VF Testing: Failed\n")

		time.sleep(30)
		s.sendline ('echo ---------OS done-------------')
		os.system("mkdir  -p " + logs_dir + "/{pf,vf}")
		if pf_vf == "default_pf" : 
			os.system("sshpass -p dpdk scp -r -P " + str(base_port) + " root@127.0.0.1:" + gtest_script_path + "/../../apps/qdma_test/logs  " + logs_dir + "/pf")
			os.system("sshpass -p dpdk scp -r -P " + str(base_port) + " root@127.0.0.1:" + gtest_script_path + "dmesg_log.txt  " + logs_dir + "/pf")
			os.system("sshpass -p dpdk scp -r -P " + str(base_port) + " root@127.0.0.1:" + gtest_script_path + "/../../apps/qdma_test/" + "build_linux_pf_vf" + "/*.xlsx " + logs_dir + "/pf")
		else :
			os.system("sshpass -p dpdk scp -r -P " + str(base_port) + " root@127.0.0.1:" + gtest_script_path + "/../../apps/qdma_test/logs  " + logs_dir + "/vf")
			os.system("sshpass -p dpdk scp -r -P " + str(base_port) + " root@127.0.0.1:" + gtest_script_path + "dmesg_log.txt " + logs_dir + "/vf")
			os.system("sshpass -p dpdk scp -r -P " + str(base_port) + " root@127.0.0.1:" + gtest_script_path + "/../../apps/qdma_test/" + "build_linux_vf" + "/*.xlsx " + logs_dir + "/vf")
		s.sendline ("shutdown -h 1")
		s.prompt()
		print s.before
		s.logout()
		time.sleep(120)
		if pf_vf == "default_vf" :
			os.system('rmmod qdma_pf')		
	
	except pxssh.ExceptionPxssh, e:
		print "pxssh failed on login."
		print str(e)
	
	base_port = base_port + 1

if arg_count < 5 :
    print("Invalid commandline args !!\n")
    print("Usage : python " + program_name + " <Ultrascale/Versal> <RAM> <source directory> <BBDDFF><VM 1 Image Path> ....... <VM n Image Path>\n")
    print("Example : python " + program_name + " Ultrascale 20480 ../../../../../../HEAD/proj 65000 /group/cdc_hd/members/vm_images/Centos/Centos.qcow2 /group/cdc_hd/members/vm_images/Fedora/fedora28.qcow2\n")
    sys.exit(0)

for vm_img in range(5, arg_count):
	vm_imgs_path.append(sys.argv[vm_img])
	
######for loop over all the VM images
for vm_img in range(0, len(vm_imgs_path)):
	log_path = vm_imgs_path[vm_img].split('/')

	print "-------------------------------------------------"
	print "     Testing " + log_path[len(log_path) - 1] + " OS"
	print "-------------------------------------------------"

	print "     Testing PF" 
	##Test OS with PF attached
	test_os("default_pf", driver_path, log_path[len(log_path) - 1], vm_imgs_path[vm_img])
	print "     Tested PF" 

	print "     Testing VF" 
	##Test OS with VFs attached
	test_os("default_vf", driver_path, log_path[len(log_path) - 1], vm_imgs_path[vm_img], False)
	print "     Tested VF" 

	os.system("tar -cvzf " + log_path[len(log_path) - 1] + "_logs.tar.gz " + log_path[len(log_path) - 1])

os.system("cd " + driver_path +"/sw_host/linux ; make uninstall-mods")
result_file.close()
result_file = open("Result.txt", "r")	
result = result_file.read()
print "\n\n\n"
print "--------------------------------------------------------------------------------------------------------"
print "\t\t\tTest Results"
print "--------------------------------------------------------------------------------------------------------"
print result
result_file.close()
if (result.find("PF Testing: Failed") != -1) | (result.find("VF Testing: Failed") != -1):
	exit(1)
else :
	exit(0)
