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
vm_ram = 6144
nb_pf = 4
pf_vfs_cnt = array('i')
pf_vfs_devid = ["a03f", "a13f", "a23f", "a33f"]
versal_vfs_devid = ["a03f", "a13f", "a23f", "a33f"]
pf_vfs_bdfs = [[], [], [], []]
vf_pf_qs = []
MAX_VMS = 4 # existing VM images on a given system.
VM_CFG_START = 8


#-----------------------------------------------------
#Path to /HEAD or /REL or /DEV branches
workspace_path = "../../../../"

program_name = sys.argv[0]
arg_count = len(sys.argv)

if arg_count < 7 :
    print("Invalid commandline args !!\n")
    print("Python script will launch VM, run the stress test and store the result in tar file with the VM name\n")
    print("Usage : python " + program_name + " <stress_script_path>  <stress_command_command> <host_drv_path> <driver_used> <bdf> <vm_count(say n)> <vm1_config> <vm2_config> ... <vm-n_config>\n")
    print("Example : python " + program_name + " \"/home/dpdk/tests/linux/scripts/stress_test_scripts\" \"./stress_test_top.sh 04000 15 00:00:10 28 1 vf\" \"../../../../drivers/linux/\" linux 06000 /scratch/ 1 \"1 1 1 1\"")
    sys.exit(0)

#intitialize all Pfs numvfs to '0'.
for pf in range(0, nb_pf):
    pf_vfs_cnt.insert(pf, 0)

gtest_script_path = sys.argv[1]
gtest_command = sys.argv[2]
host_drv_path = sys.argv[3]
drv_used = sys.argv[4]
vm_ram = sys.argv[5]
bbddf = sys.argv[6]
vm_image_path = sys.argv[7]
nb_vms = int(sys.argv[8])
pci_bus = bbddf[:2]
pci_dev = bbddf[2:4]

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
    vf_pf_qs.append([])

    for pf in range(0, nb_pf):
        pf_vfs_cnt[pf] = pf_vfs_cnt[pf] + int(vm_vfs[pf])
        vf_pf_qs[vm_id - 1].append([])
        for vf in range(0, int(vm_vfs[pf])):
            vf_pf_qs[vm_id - 1][pf].append(10) # set number of queues as 10 for each valid vf

#--------------------------- linux specific started here ----------------------------

if drv_used == "linux":
    os.system("cd " + host_drv_path + "; sh make_libqdma.sh")
    os.system("cd " + host_drv_path + "; make install-mods")
    os.system("rmmod qdma-pf")
    os.system("rmmod qdma-vf")
    os.system("modprobe qdma-pf")
    os.system("modprobe vfio-pci")

    for pf in range(0, nb_pf):
        #set num_vfs for each pf
        num_vf_cmd = "echo " + str(pf_vfs_cnt[pf]) + " > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/sriov_numvfs"
        os.system(num_vf_cmd)


cmd = "lspci | grep -i xilinx | awk '{print $1\" \"$7}'"
a = subprocess.Popen(cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
output = a.communicate()[0]
out = output.replace('\n',' ').strip().split(' ')
pci_dic = dict(zip( * [iter(out)] * 2))

for k, v in pci_dic.iteritems():
    for pf in range(0, nb_pf):
        if (v == pf_vfs_devid[pf]):
            pf_vfs_bdfs[pf].append(k)
        elif (v == versal_vfs_devid[pf]):
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
                vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + pf_vfs_bdfs[pf].pop()
            else:
                vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + pf_vfs_bdfs[pf].pop()
    port = base_port + vm_id
    vm_cmd = ""
    vm_cmd = "qemu-system-x86_64 -cpu host -enable-kvm -m " + str(vm_ram) + " -smp sockets=1,cores=4 -hda " + vm_image_path + "/vm" + str(vm_id) + ".qcow2  -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::" + str(port) + "-:22 " + vm_bdf_assign + " -vnc :" + str(port) + "  &"
    print vm_cmd
    os.system(vm_cmd)
# Let vms up
time.sleep(120)

try:
    for vm_id in range(1, nb_vms + 1):
        s = pxssh.pxssh(timeout = 2000000)
        s.login ("127.0.0.1", "root", "dpdk", port = base_port + vm_id)

        s.sendline ('rm -rf /home/dpdk/*')
        s.prompt()
        print s.before
        s.sendline ('mkdir -p /home/dpdk/{drivers/{linux,qdma_access},tests/linux/scripts/}')
        s.prompt()
        print s.before
        s.sendline ('cd /home/dpdk/')
        s.prompt()
        print s.before
        s.sendline ('chmod -R 0777 ./*')
        s.prompt()
        print s.before
        src_dict="../../../../"
        #checking if sw_host and sw_test dirs are present
        if (os.path.isdir(src_dict + 'drivers') and os.path.isdir(src_dict + 'tests')) :
            os.system("sshpass -p dpdk scp -o StrictHostKeyChecking=no -P " + str(port) + " -r " + src_dict + "drivers/linux/*  root@127.0.0.1:/home/dpdk/drivers/linux/")
            os.system("sshpass -p dpdk scp -o StrictHostKeyChecking=no -P " + str(port) + " -r " + src_dict + "drivers/qdma_access/*  root@127.0.0.1:/home/dpdk/drivers/qdma_access/")
            os.system("sshpass -p dpdk scp -o StrictHostKeyChecking=no -P " + str(port) + " -r " + src_dict + "tests/linux/scripts/*  root@127.0.0.1:/home/dpdk/tests/linux/scripts/")
        else :
            print "Invalid Directory hence exiting"
            s.sendline ("shutdown -h 1")
            s.prompt()
            print s.before
            exit()
        s.sendline ('echo --------------------------------------------vm_'+ str(vm_id) +'logs---------------------------------------------------------------')
        s.prompt()
        print s.before
        s.sendline ('cd /home/dpdk/drivers/linux')
        s.prompt()
        print s.before
        s.sendline ('ls -ll')
        s.prompt()
        print s.before
        s.sendline ('sed -i s/coverity_mandate=1/coverity_mandate=0/g make_libqdma.sh')
        s.prompt()
        print s.before
        s.sendline ('sed -i s/cppchecker_mandate=1/cppchecker_mandate=0/g make_libqdma.sh')
        s.prompt()
        print s.before
        s.sendline ('sed -i s/sparse_mandate=1/sparse_mandate=0/g make_libqdma.sh')
        s.prompt()
        print s.before
        s.sendline ('./make_libqdma.sh clean; ./make_libqdma.sh')
        s.prompt()
        print s.before
        s.sendline ('make install-mods; modprobe qdma-pf')
        s.prompt()
        print s.before
        s.sendline ('cd ' + gtest_script_path)
        s.prompt()
        print s.before
        print("gtest command: " + gtest_command + " \n")
        s.sendline ('bash ' + gtest_command )
        s.prompt()
        print s.before
        time.sleep(60)
        print "logs"
        s.sendline ('echo --------------------------------------------vm_' + str(vm_id) + ' done---------------------------------------------------------------')
        s.prompt()
        print s.before
        os.system("sshpass -p dpdk scp -r -P " + str(base_port + vm_id) + " root@127.0.0.1:" + gtest_script_path + "/stress_test_report_2* .")
        os.system("sshpass -p dpdk scp -r -P " + str(base_port + vm_id) + " root@127.0.0.1:" + gtest_script_path + "/dmesg* .")
        s.sendline('rm -f stress_test_report_2* dmesg*')
        s.prompt()
        print s.before
        s.sendline ('shutdown 1')
        s.prompt()
        print s.before
        s.logout()
        time.sleep(1)
        for pf in range(0, nb_pf):
            #set num_vfs for each pf
            num_vf_cmd = "echo 0 > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/sriov_numvfs"
            os.system(num_vf_cmd)

except pxssh.ExceptionPxssh, e:
    print "pxssh failed on login."
    print str(e)
