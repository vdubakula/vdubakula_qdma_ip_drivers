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
pf_vfs_devid = ["903f", "913f", "923f", "933f", "b03f", "b13f", "b23f", "b33f"]
pf_vfs_bdfs = [[], [], [], []]
MAX_VMS = 4 # existing VM images on a given system.
MAX_PFS = 4

dpdk_bind_drv = "igb_uio"
child = ""

#-----------------------------------------------------
#Path to /HEAD or /REL or /DEV branches
workspace_path = "../../../../"

program_name = sys.argv[0]
arg_count = len(sys.argv)

if arg_count < 7 :
    print("Invalid commandline args !!\n")
    print("Usage : python " + program_name + " <gtest_script_path>  <gtest_command> <host_drv_path> <driver_used> <bdf> <vm_image_path> <vm_count(say n)> <vm_ram> <nb_pf> <bind_drv>\n")
    print("Example : python " + program_name + " \"/home/dpdk/REL/2019.1_patch/sw_test/qdma/scripts/common/gtest_scripts/\" \"./gtest_top.sh 04000 ../../../../../../../REL/2019.1_patch/sw_test/qdma/scripts/common/gtest_scripts/gtest_configs/default/ ../../../../../../../REL/2019.1_patch/sw_host/mdma/ ../../../../../../../REL/2019.1_patch/sw_test/qdma/apps/qdma_test pf_vf linux 0 \" \"../../../../../../../REL/2019.1_patch/sw_host/mdma/linux\" linux 04000 2  15260 2 igb_uio \n")
    sys.exit(0)

gtest_script_path = sys.argv[1]
gtest_command = sys.argv[2]
host_drv_path = sys.argv[3]
drv_used = sys.argv[4]
bbddf = sys.argv[5]
vm_image_path = sys.argv[6]
nb_vms = int(sys.argv[7])
vm_ram = int(sys.argv[8])
nb_pf = int(sys.argv[9])
pci_bus = bbddf[:2]
pci_dev = bbddf[2:4]

num_pfs_vm = nb_pf/nb_vms

print ("nb_pf = " + str(nb_pf))
print ("vm_ram = " + str(vm_ram))

if drv_used == "dpdk":
    dpdk_bind_drv = sys.argv[10]
print("DPDK bind driver: " + dpdk_bind_drv + " \n")

p=os.popen("qemu-system-x86_64 --version")
qemu_ver = p.read()
temp = qemu_ver.split(' ')
temp[3]=temp[3].split('(')
qemu_version=temp[3][0]

if nb_vms > MAX_VMS:
    print("Invalid <vm_count>, max allowed is " + str(MAX_VMS) + " !!\n")
    sys.exit(0)

#--------------------------- linux specific started here ----------------------------

if drv_used == "linux":
    os.system("cd " + host_drv_path + "; sh make_libqdma.sh")
    os.system("insmod " + host_drv_path + "/bin/qdma.ko")

    for pf in range(0, nb_pf):
        #set num_vfs for each pf
        num_vf_cmd = "echo " + str(pf_vfs_cnt[pf]) + " > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/sriov_numvfs"
        os.system(num_vf_cmd)

#--------------------------- linux specific end here ----------------------------

else :#dpdk
    pwd = os.getcwd()
    os.chdir(pwd)

if dpdk_bind_drv == "vfio-pci":
    lspci_cmd = "lspci | grep -i xilinx | awk -F \" \" \'(($7 > \"9000\" && $7< \"a000\")) {print $7}\' | tr -t \"\n\" \" \" "
    lspci_out = subprocess.Popen(lspci_cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT).communicate()[0]
    id_list = list(set(lspci_out.replace('\n', ' ').strip().split(' ')))
    os.system("modprobe vfio-pci")

    for i in range(len(id_list)):
        os.system("echo " + "\"10ee " + str(id_list[i]) + "\"" + " > /sys/bus/pci/drivers/vfio-pci/new_id")

cmd = "lspci | grep -i xilinx | awk '{print $1\" \"$7}'"
a = subprocess.Popen(cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
output = a.communicate()[0]
out = output.replace('\n',' ').strip().split(' ')
pci_dic = dict(zip( * [iter(out)] * 2))

for k, v in pci_dic.iteritems():
    for pf in range(0, nb_pf):
        if (v == pf_vfs_devid[pf]) or (v == pf_vfs_devid[pf + MAX_PFS]):
            pf_vfs_bdfs[pf].append(k)
assign_id = 0
os.system("modprobe vfio-pci")
for vm_id in range(1, nb_vms + 1):
    vm_bdf_assign = ""
    for x in range(0, num_pfs_vm):
        if (qemu_version == "2.5.0") :
            if dpdk_bind_drv == "vfio-pci":
                vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + pf_vfs_bdfs[assign_id].pop()
            else:
                vm_bdf_assign = vm_bdf_assign + " -device pci-assign,host=" + pf_vfs_bdfs[assign_id].pop()
        else:
            vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + pf_vfs_bdfs[assign_id].pop()
        assign_id = assign_id + 1
    port = base_port + vm_id
    vm_cmd = ""
    vm_cmd = "qemu-system-x86_64 -cpu host -enable-kvm -m " + str(vm_ram) + " -smp sockets=1,cores=4 -hda " + vm_image_path + "/vm" + str(vm_id) + ".qcow2  -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::" + str(port) + "-:22 " + vm_bdf_assign + " -vnc :" + str(port) + "  &"
    print vm_cmd
    os.system(vm_cmd)
# Let vms up
time.sleep(180)

try:
    for vm_id in range(1, nb_vms + 1):
        print(vm_id)
        s = pxssh.pxssh(timeout = 5000)
        s.login ("127.0.0.1", "root", "dpdk", port = base_port + vm_id)
        os.system("sshpass -p dpdk rsync -avz  --exclude 'incoming' -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "  root@127.0.0.1:/home/dpdk/")
        s.sendline ('echo --------------------------------------------vm_'+ str(vm_id) +'logs---------------------------------------------------------------')
        s.prompt()
        print s.before
        s.sendline ('cd ' + gtest_script_path)
        s.prompt()
        print s.before

        if dpdk_bind_drv == "vfio-pci":
            s.sendline ('bash ' + "modprobe vfio-pci")
            s.sendline ('bash ' + "echo 1 > /sys/module/vfio/parameters/enable_unsafe_noiommu_mode")

        print("gtest command: " + gtest_command + " \n")
        s.sendline ('bash ' + gtest_command )
        s.prompt()
        print s.before

        if dpdk_bind_drv == "vfio-pci":
            time.sleep(600)
        else:
            time.sleep(60)

        s.sendline ('echo --------------------------------------------vm_' + str(vm_id) + ' done---------------------------------------------------------------')
        os.system("sshpass -p dpdk scp -r -P " + str(base_port + vm_id) + " root@127.0.0.1:" + gtest_script_path + "/../../apps/qdma_test/logs ./vm" + str(vm_id) + "_logs/")

        os.system("tar -cvzf vm" + str(vm_id) + "_logs.tar.gz vm" + str(vm_id) + "_logs/")
        s.prompt()
        print s.before
        s.logout()

except pxssh.ExceptionPxssh, e:
    print "pxssh failed on login."
    print str(e)
