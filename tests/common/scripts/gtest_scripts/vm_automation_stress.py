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
pf_vfs_devid = ["a03f", "a13f", "a23f", "a33f"]
pf_vfs_bdfs = [[], [], [], []]
vm_sid = ["", "", "", "", "", "", "", "", ""]
vf_pf_qs = []
MAX_VMS = 4 # existing VM images on a given system.
VM_CFG_START = 8
dpdk_bind_drv = "igb_uio"
dpdk_bind_drv_idx = 0
child = ""

#-----------------------------------------------------
#Path to /HEAD or /REL or /DEV branches
workspace_path = "./../../../../../../../"

program_name = sys.argv[0]
arg_count = len(sys.argv)

if arg_count < 7 :
    print("Invalid commandline args !!\n")
    print("Usage : python " + program_name + " <bdf> <bind_drv> <num_pfs> <total_queues> <time_per_vm> <vm_ram> <vm_image_path> <num_vms> <vm1_config> <vm2_config> ... <vm-n_config> \n")
    print("Example : python " + program_name + "  81000 igb_uio 4 1024 96 25534 /scratch 2  \"1 2 3 0\"  \"3 2 2 1\" \n")
    sys.exit(0)

bbddf = sys.argv[1]
dpdk_bind_drv = sys.argv[2]
nb_pf = int(sys.argv[3])
total_queues = int(sys.argv[4])
time_per_vm = sys.argv[5]
vm_ram = int(sys.argv[6])
vm_image_path = sys.argv[7]
nb_vms = int(sys.argv[8])


#intitialize all Pfs numvfs to '0'.
for pf in range(0, nb_pf):
    pf_vfs_cnt.insert(pf, 0)
for vm in range(0, nb_vms):
    vm_num_vfs.insert(vm, 0)

pci_bus = bbddf[:2]
pci_dev = bbddf[2:4]

print ("nb_pf = " + str(nb_pf))
print ("vm_ram = " + str(vm_ram))
print ("total_queues = " + str(total_queues))
print ("time_per_vm = " + str(time_per_vm))
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
os.chdir(workspace_path + "dpdk-stable-20.11/examples/qdma_testapp/")
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

child = pexpect.spawn("./build/qdma_testapp -c 0xf -n 4")
child.expect('xilinx-app>')
print child.before
os.chdir(pwd)

if dpdk_bind_drv == "vfio-pci":
    lspci_cmd = "lspci | grep -i xilinx | awk -F \" \" \'(($7 > \"a000\" && $7< \"b000\") || ($7 > \"c000\" && $7< \"d000\")) {print $7}\' | tr -t \"\n\" \" \" "
    lspci_out = subprocess.Popen(lspci_cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT).communicate()[0]
    id_list = list(set(lspci_out.replace('\n', ' ').strip().split(' ')))

    for i in range(len(id_list)):
        os.system("echo " + "\"10ee " + str(id_list[i]) + "\"" + " > /sys/bus/pci/drivers/vfio-pci/new_id")

cmd = "lspci | grep -i xilinx | awk '{print $1\" \"$7}'"
a = subprocess.Popen(cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
output = a.communicate()[0]
out = output.replace('\n',' ').strip().split(' ')
pci_dic = dict(zip( * [iter(out)] * 2))

for k, v in pci_dic.iteritems():
    for pf in range(0, nb_pf):
        if (v == pf_vfs_devid[pf]):
            pf_vfs_bdfs[pf].append(k)

for vm_id in range(1, nb_vms + 1):
    idx = VM_CFG_START + vm_id #vm config starts from index 8
    vm_cfg = str(sys.argv[idx]) # vm_cfg = "3 0 1 1"
    vm_vfs = vm_cfg.split()
    vm_bdf_assign = ""
    for pf in range(0, nb_pf):
        pf_vfs = int(vm_vfs[pf])
        for x in range(0, pf_vfs):
            if (qemu_version == "2.5.0") :
                if dpdk_bind_drv == "vfio-pci":
                    vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + pf_vfs_bdfs[pf].pop()
                else:
                    vm_bdf_assign = vm_bdf_assign + " -device pci-assign,host=" + pf_vfs_bdfs[pf].pop()
            else:
                vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + pf_vfs_bdfs[pf].pop()
    port = base_port + vm_id
    vm_cmd = ""
    vm_cmd = "qemu-system-x86_64 -cpu host -enable-kvm -m " + str(vm_ram) + " -smp sockets=1,cores=4 -hda " + vm_image_path + "/vm" + str(vm_id) + ".qcow2  -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::" + str(port) + "-:22 " + vm_bdf_assign + " -vnc :" + str(port) + "  &"
    print vm_cmd
    os.system(vm_cmd)
# Let vms up
time.sleep(180)

try:
    for vm_id in range(1, nb_vms + 1):
        print("VM ID =" + str(vm_id))
        vm_sid[vm_id] = pxssh.pxssh(timeout = 5000)
        vm_sid[vm_id].login ("127.0.0.1", "root", "dpdk", port = base_port + vm_id)
        os.chdir(pwd)
        os.system("sshpass -p dpdk rsync -avz  -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "dpdk-stable-20.11" + "   root@127.0.0.1:/home/dpdk/")

        vm_sid[vm_id].sendline ('cd /home/dpdk/dpdk-stable-20.11')
        vm_sid[vm_id].prompt()
        print vm_sid[vm_id].before
        vm_sid[vm_id].sendline ('rm -rf x86_64-native-linuxapp-gcc')
        vm_sid[vm_id].prompt()
        print vm_sid[vm_id].before
        vm_sid[vm_id].sendline ('make config T=x86_64-native-linuxapp-gcc install -j32 ')
        vm_sid[vm_id].prompt()
        print vm_sid[vm_id].before

        if dpdk_bind_drv == "vfio-pci":
            vm_sid[vm_id].sendline ('bash ' + "modprobe vfio-pci")
            vm_sid[vm_id].sendline ('bash ' + "echo 1 > /sys/module/vfio/parameters/enable_unsafe_noiommu_mode")

        vm_sid[vm_id].sendline ('cd /home/dpdk/dpdk-stable-20.11/examples/qdma_testapp/')
        vm_sid[vm_id].prompt()
        print vm_sid[vm_id].before

        cmd = "./vm_stress_test_top.sh " + str(dpdk_bind_drv) +" " + str(vm_num_vfs[vm_id-1]) + " " + str(total_queues) + " " + str(time_per_vm)
        print cmd
        vm_sid[vm_id].sendline (cmd)
        vm_sid[vm_id].prompt()
        vm_sid[vm_id].sendline ('echo --------------------------------------------vm_' + str(vm_id) + ' done---------------------------------------------------------------')
        os.chdir(pwd)
        os.chdir(workspace_path + "dpdk-stable-20.11")
        os.system("mkdir -p vm" + str(vm_id) + "_logs/")
        os.system("sshpass -p dpdk scp -r -P " + str(base_port + vm_id) + " root@127.0.0.1:/home/dpdk/dpdk-stable-20.11/examples/qdma_testapp/mm_errors_log.txt ./vm" + str(vm_id) + "_logs/")
        os.system("sshpass -p dpdk scp -r -P " + str(base_port + vm_id) + " root@127.0.0.1:/home/dpdk/dpdk-stable-20.11/examples/qdma_testapp/st_errors_log.txt ./vm" + str(vm_id) + "_logs/")
        os.system("tar -cvzf vm" + str(vm_id) + "_logs.tar.gz vm" + str(vm_id) + "_logs/")
        vm_sid[vm_id].prompt()
        print vm_sid[vm_id].before
    os.chdir(pwd)
    os.chdir(workspace_path + "dpdk-stable-20.11/examples/qdma_testapp/")
    child.send('\r')
    child.expect('xilinx-app>')
    child.sendcontrol('d')
    time.sleep(10)
    for vm_id in range(1, nb_vms + 1):
        vm_sid[vm_id].sendline ('poweroff')
    for pf in range(0, nb_pf):
        #Remove num_vfs for each pf
        num_vf_cmd = "echo 0 > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/max_vfs"
        print num_vf_cmd
        os.system(num_vf_cmd)

except pxssh.ExceptionPxssh, e:
    print "pxssh failed on login."
    print str(e)
