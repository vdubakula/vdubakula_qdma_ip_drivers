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
pf_vfs_devid = ["c03f", "c13f", "c23f", "c33f", "a03f", "a13f", "a23f", "a33f", "a038", "a138", "a238", "a338", "a034", "a134", "a234", "a334"]
pf_vfs_bdfs = [[], [], [], []]


def_cfg_pf_nvf = "pf_nvf"
valid_drv = "valid_drv"
dummy_line = "#necessary dummy line"


MAX_VMS = 4 # existing VM images on a given system.
VM_CFG_START = 11

dpdk_bind_drv = "igb_uio"
dpdk_bind_drv_idx = 0
child = ""

#-----------------------------------------------------
#Path to /HEAD or /REL or /DEV branches
workspace_path = "../../../../"

program_name = sys.argv[0]
arg_count = len(sys.argv)

if arg_count < 12 :
    print("Invalid commandline args !!\n")
    print("Usage : python " + program_name + " <script_path>  <command> <host_drv_path> <driver_used> <bdf> <vm_image_path> <vm_count(say n)> <vm_ram> <cores> <testname> <num_pf> <vm1_config> <vm2_config> ... <vm-n_config> <bind_driver> <config_bar>\n")
    sys.exit(0)

script_path = sys.argv[1]
command = sys.argv[2]
host_drv_path = sys.argv[3]
drv_used = sys.argv[4]
bbddf_array = sys.argv[5].split(' ')
vm_image_path = sys.argv[6]
nb_vms = int(sys.argv[7])
vm_ram = int(sys.argv[8])
cores = int(sys.argv[9])
testname = sys.argv[10]
nb_pf = int(sys.argv[11])

pci_bus =[]
pci_dev =[]
bddf_array_length = len(bbddf_array)
total_pfs = bddf_array_length * nb_pf
eal_options = ""
#intitialize all Pfs numvfs to '0'.
print ("BDF array length is " + str(bddf_array_length))
print ("total_pfs is " + str(total_pfs))
for pf in range(0, bddf_array_length):
    bbddf = (str)(bbddf_array[pf])
    for l in range(0, nb_pf):
        pci_bus.append(bbddf[:2])
        pci_dev.append(bbddf[2:4])

for pf in range(0, total_pfs):
    pf_vfs_cnt.insert(pf, 0)



print ("total_ps = " + str(total_pfs))
print ("nb_pf = " + str(nb_pf))
print ("vm_ram = " + str(vm_ram))
print ("cores = " + str(cores))




#Getting config BAR
config_bar_idx = VM_CFG_START + nb_vms + 2
config_bar = sys.argv[config_bar_idx]
print ("config bar = " + config_bar)
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

    for pf in range(0, total_pfs):
        pf_vfs_cnt[pf] = pf_vfs_cnt[pf] + int(vm_vfs[pf])
#--------------------------- linux specific started here ----------------------------

if drv_used == "linux":
    os.system("cd " + host_drv_path + ";rmmod qdma_pf; rmmod qdma_vf; make uninstall-mods;sh make_libqdma.sh; make install-mods;./scripts/qdma_generate_conf_file.sh " + str(bbddf[:2]) + " " + str(nb_pf) + " 0 " + str(config_bar)+ ";cd -")
    for pf in range(0, bddf_array_length):
        bbddf = (str)(bbddf_array[pf])
    os.system("modprobe qdma_pf")
    for pf in range(0, total_pfs):
        #set num_vfs for each pf
        num_vf_cmd = "echo " + str(pf_vfs_cnt[pf]) + " > /sys/bus/pci/devices/0000:" + pci_bus[pf] + ":" + pci_dev[pf] + "." + str(pf%nb_pf) + "/sriov_numvfs"
        os.system(num_vf_cmd)
        print num_vf_cmd
    os.system("rmmod qdma_vf")
#--------------------------- linux specific end here ----------------------------



cmd = "lspci | grep -i xilinx | awk '{print $1\" \"$7}'"
a = subprocess.Popen(cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
output = a.communicate()[0]
out = output.replace('\n',' ').strip().split(' ')
pci_dic = dict(zip( * [iter(out)] * 2))

for k, v in pci_dic.iteritems():
    for pf in range(0, nb_pf):
        if (v == pf_vfs_devid[pf]):
            print ("Gen 3x16, idx=" + str(pf))
            pf_vfs_bdfs[pf].append(k)
        elif (v == pf_vfs_devid[pf+4]):
            print ("Gen 3x8, idx=" + str(pf))
            pf_vfs_bdfs[pf].append(k)
        elif (v == pf_vfs_devid[pf+8]):
            print ("Gen 3x4 idx=" + str(pf))
            pf_vfs_bdfs[pf].append(k)

for vm_id in range(1, nb_vms + 1):
    idx = VM_CFG_START + vm_id #vm config starts from index 8
    vm_cfg = str(sys.argv[idx]) # vm_cfg = "3 0 1 1"
    vm_vfs = vm_cfg.split()
    vm_bdf_assign = ""
    for pf in range(0, total_pfs):
        pf_vfs = int(vm_vfs[pf])
        for x in range(0, pf_vfs):
            if (qemu_version == "2.5.0") :
                if dpdk_bind_drv == "vfio-pci":
                    os.system("modprobe vfio-pci")
                    vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + pf_vfs_bdfs[pf%nb_pf].pop()
                else:
                    vm_bdf_assign = vm_bdf_assign + " -device pci-assign,host=" + pf_vfs_bdfs[pf%nb_pf].pop()
            else:
                os.system("modprobe vfio-pci")
                vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + pf_vfs_bdfs[pf%nb_pf].pop()
    port = base_port + vm_id
    vm_cmd = ""
    vm_cmd = "qemu-system-x86_64 -cpu host -enable-kvm -m " + str(vm_ram) + " -smp sockets=1,cores="+ str(cores) +" -hda " + vm_image_path + "/vm" + str(vm_id) + ".qcow2  -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::" + str(port) + "-:22 " + vm_bdf_assign + " -vnc :" + str(port) + "  &"
    print vm_cmd
    os.system(vm_cmd)
# Let vms up
time.sleep(180)

try:
    for vm_id in range(1, nb_vms + 1):
        print("VM ID = " + str(vm_id))
        def_no = 0
        idx = VM_CFG_START + vm_id #vm config starts from index 9
        vm_cfg = str(sys.argv[idx])

        s = pxssh.pxssh(timeout = 200000)
        s.login ("127.0.0.1", "root", "dpdk", port = base_port + vm_id)
        os.system("sshpass -p dpdk rsync -avz  --exclude 'incoming' -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "  root@127.0.0.1:/home/dpdk/")
        s.sendline ('echo --------------------------------------------vm_'+ str(vm_id) +'logs---------------------------------------------------------------')
        s.prompt()
        print s.before
        s.sendline ('cd ' + script_path)
        s.prompt()
        print s.before
        s.sendline ('cd ' + host_drv_path)
        s.prompt()
        print s.before
        s.sendline ('./make_libqdma.sh')
        s.prompt()
        print s.before
        s.sendline ('rmmod qdma_vf')
        s.prompt()
        print s.before
        s.sendline ('make uninstall-mods')
        s.prompt()
        print s.before
        s.sendline ('make install-mods')
        s.prompt()
        print s.before
        s.sendline ('modprobe qdma_vf')
        s.prompt()
        print s.before
        s.sendline ('cd -')
        s.prompt()
        print s.before

        print("command: " + command + " \n")
        s.sendline ('bash ' + command )
        s.prompt()
        print s.before


        s.sendline ('echo --------------------------------------------vm_' + str(vm_id) + ' done---------------------------------------------------------------')
        s.prompt()
        print s.before
        os.system("sshpass -p dpdk scp -r -P " + str(base_port + vm_id) + " root@127.0.0.1:" + script_path + "/qdma_perf_results/out_auto_" + testname + "/0/dmaperf_results/*.xlsx .")
        os.system("sshpass -p dpdk scp -r -P " + str(base_port + vm_id) + " root@127.0.0.1:" + script_path + "dmesg_log.txt ./dmesg_vm.log")

        os.system("dmesg > dmesg_host.log")
        s.sendline('shutdown 1')
        s.prompt()
        print s.before
        s.logout()

        time.sleep(1)



except pxssh.ExceptionPxssh, e:
    print "pxssh failed on login."
    print str(e)
