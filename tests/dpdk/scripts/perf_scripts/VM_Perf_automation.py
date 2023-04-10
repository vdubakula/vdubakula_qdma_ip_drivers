import pexpect
from pexpect import pxssh
from pexpect import *
import getpass
import re
import os
import time
import sys
import subprocess
from array import array

base_port = 5555
vm_ram = 24576
cores_vm = 24
nb_pf = 1
vm_sid = ["", "", "", "", "", "", "", "", ""]
pf_vfs_devid = ["a03f", "a13f", "a23f", "a33f", "a038", "a138", "a238", "a338", "a034", "a134", "a234", "a334"]
pf_vfs_devid_h10 = ["c03f", "c13f", "c23f", "c33f", "c038", "c138", "c238", "c338", "c034", "c134", "c234", "c334"]
pf_vfs_bdfs = [[], [], [], []]
host_num_queues = 1
MAX_VMS = 16 # existing VM images on a given system.
dpdk_bind_drv = "igb_uio"
child = ""
child1 = ""
vm_cfg = []
DPDK_VER="22.11"

#------------------Notes(Pre-conditions)------------------
#1. Atleast 30 Huge pages should be alocated in the host
#2. Atleast 10 Huge pages should be alocated in all of the VM's
#3. Maximum of 16 VM's are supported
#4. User should ensure that limited memory be mounted for host huge pages so that remaining memory will be used by VM in a separate mount point
#    Example: mount -t hugetlbfs -o size=4G none /mnt/huge
#5. In case of latest qemu version, it is expected that vfio-pci driver is inserted by updating the device id's in relavant files prior to running this script
#    Example: modprobe vfio-pci
#---------------------------------------------------------

#Path to /HEAD or /REL or /DEV branches
workspace_path = "./../../../../"

program_name = sys.argv[0]
arg_count = len(sys.argv)

if arg_count < 13 :
    print("Invalid commandline args !!\n")
    print("Usage : python " + program_name + " <bdf> <num_vms> <vm_image_path> <testpmd_enable> <pktgen_enable> <test_pmd_host_num_queues> <testpmd_vm_queue_cfg> <pktgen_host_num_queue> <pktgen_vm_num_queue> <bind_drv> <num_cores> <vm_ram> <nb_pf>\n")
    print("Example : python VM_Perf_automation.py 81:00.0 1 /group/cdc_hd/members/vm_images/vm_automation 1 1 1 \"8 4 2 1\" 1 2 igb_uio 18 24576 1\n")
    sys.exit(0)

bbddf = sys.argv[1]
nb_vms = int(sys.argv[2])
vm_image_path = sys.argv[3]
testpmd_enable = int(sys.argv[4])
pktgen_enable = int(sys.argv[5])
testpmd_host_num_queues = int(sys.argv[6])
testpmd_queue_cfg = str(sys.argv[7]) # testpmd queues for each VM config
pktgen_host_num_queues = int(sys.argv[8])
vm_pktgen_queue = int(sys.argv[9])
dpdk_bind_drv = sys.argv[10]
cores_vm = int(sys.argv[11])
vm_ram = int(sys.argv[12])
nb_pf = int(sys.argv[13])

vm_queue_cfg = testpmd_queue_cfg.split()
len_queues = len(vm_queue_cfg)

print ("testpmd_enable = " + str(testpmd_enable))
print ("pktgen_enable = " + str(pktgen_enable))
print ("testpmd_host_num_queues = " + str(testpmd_host_num_queues))
print ("pktgen_host_num_queues = " + str(pktgen_host_num_queues))
print ("vm_pktgen_queue = " + str(vm_pktgen_queue))
print ("number of vm queues entries for testpmd = " + str(len_queues))
print ("cores_vm = " + str(cores_vm))
print ("vm_ram = " + str(vm_ram))
print ("nb_pf = " + str(nb_pf))

pci_bus = bbddf[:2]
pci_dev = bbddf[3:5]

addr_lspci_cmd = "lspci -vv -s " + bbddf + " | grep Region\" \"2 | grep size | awk '{print $5}'"
addr = subprocess.Popen(addr_lspci_cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT).communicate()[0]
addr = "0x" + str(addr)
print ("User bar offset = " + str(addr))
#Disabling packet generation
usrbar = int(addr, 16) + 0x8
usrbarctrl = hex(usrbar)
print ("User bar packet enable address= " + str(usrbarctrl))
os.system("devmem2 " + str(usrbarctrl) +" w 0x120000")
#Updating packet size to 64
usrbar = int(addr, 16) + 0x90
usrbarctrl = hex(usrbar)
print ("User bar packet size address = " + str(usrbarctrl))
os.system("devmem2 " + str(usrbarctrl) +" w 96")
#Updating descriptor
usrbar = int(addr, 16) + 0x50
usrbarctrl = hex(usrbar)
os.system("devmem2 " + str(usrbarctrl) +" w 1")

p=os.popen("qemu-system-x86_64 --version")
qemu_ver = p.read()
temp = qemu_ver.split(' ')
temp[3]=temp[3].split('(')
qemu_version=temp[3][0]
nb_vfs = nb_vms/nb_pf
print ("Number of VFs for each PF = " + str(nb_vfs))
if nb_vms > MAX_VMS:
    print("Invalid <vm_count>, max allowed is " + str(MAX_VMS) + " !!\n")
    sys.exit(0)

pwd = os.getcwd()
os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER + "/examples/qdma_testapp/")
dpdk_testapp_path = os.getcwd()
os.system("chmod +x *.sh")
os.system("sh setup_host.sh")

if dpdk_bind_drv == "vfio-pci":
    for pf in range(0, nb_pf):
        os.system("../../usertools/dpdk-devbind.py -b igb_uio " + pci_bus + ":" + pci_dev + "." + str(pf))

        #set num_vfs for each pf
        num_vf_cmd = "echo " + str(nb_vfs) + " > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/max_vfs"
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
        num_vf_cmd = "echo " + str(nb_vfs) + " > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/max_vfs"
        print num_vf_cmd
        os.system(num_vf_cmd)

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
        if (v == pf_vfs_devid[pf]) or (v == pf_vfs_devid_h10[pf]):
            print ("Gen 3x16, idx=" + str(pf)) 
            pf_vfs_bdfs[pf].append(k)
        elif (v == pf_vfs_devid[pf+4]) or (v == pf_vfs_devid_h10[pf+4]):     
            print ("Gen 3x8, idx=" + str(pf)) 
            pf_vfs_bdfs[pf].append(k)
        elif (v == pf_vfs_devid[pf+8]) or (v == pf_vfs_devid_h10[pf+8]):     
            print ("Gen 3x4 idx=" + str(pf)) 
            pf_vfs_bdfs[pf].append(k)

if (qemu_version != "2.5.0") :
    os.system("modprobe vfio-pci")

vm_ram = vm_ram/nb_vms
mount_ram = vm_ram/1024
cores_vm = cores_vm/nb_vms
pf_id = 0
for vm_id in range(1, nb_vms + 1):
    vm_bdf_assign = ""
    vf_bdf = ""
    # for pf in range(0, nb_pf):
    if (qemu_version == "2.5.0") :
        if dpdk_bind_drv == "vfio-pci":
            vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + pf_vfs_bdfs[pf_id].pop()
        else:
            vm_bdf_assign = vm_bdf_assign + " -device pci-assign,host=" + pf_vfs_bdfs[pf_id].pop()
    else:
        vf_bdf = pf_vfs_bdfs[pf_id].pop()
        curr_pwd = os.getcwd()
        os.chdir(dpdk_testapp_path)
        os.system("../../usertools/dpdk-devbind.py -b vfio-pci " + vf_bdf)
        os.chdir(curr_pwd)
        vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + vf_bdf
    pf_id = pf_id + 1
    if (pf_id == nb_pf) :
        pf_id = 0
    port = base_port + vm_id
    cmd = "mkdir /mnt/huge_vm" + str(vm_id)
    print cmd
    os.system(cmd)
    cmd = "mount -t hugetlbfs -o size=" + str(mount_ram) + "G none /mnt/huge_vm" + str(vm_id)
    print cmd
    os.system(cmd)
    vm_cmd = ""
    vm_cmd = "qemu-system-x86_64 -cpu host -enable-kvm -m " + str(vm_ram) + " -mem-prealloc -mem-path /mnt/huge_vm" + str(vm_id) +" -smp sockets=1,cores=" + str(cores_vm) + " -hda " + vm_image_path + "/vm" + str(vm_id) + ".qcow2  -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::" + str(port) + "-:22 " + vm_bdf_assign + " -vnc :" + str(port) + "  &"
    print vm_cmd
    os.system(vm_cmd)
pf_id = 0
# Let vms up
time.sleep(150)
item = 0
try:
    os.chdir(pwd)
    for vm_id in range(1, nb_vms + 1):
        print("VM ID =" + str(vm_id))
        vm_sid[vm_id] = pxssh.pxssh(timeout = 5000)
        vm_sid[vm_id].login ("127.0.0.1", "root", "dpdk", port = base_port + vm_id)
        # vm_sid[vm_id].sendline ('rm -rf /home/dpdk/dpdk-stable-20.11/')
        os.system("sshpass -p dpdk rsync -avz  -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "dpdk-stable-" + DPDK_VER + "   root@127.0.0.1:/home/dpdk/")

        vm_sid[vm_id].sendline ('cd /home/dpdk/dpdk-stable-' + DPDK_VER)
        vm_sid[vm_id].prompt()
        print vm_sid[vm_id].before
        vm_sid[vm_id].sendline ('rm -rf build')
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
        vm_sid[vm_id].sendline ('cd ../../..')
        vm_sid[vm_id].prompt()
        print vm_sid[vm_id].before

        if dpdk_bind_drv == "vfio-pci":
            vm_sid[vm_id].sendline ('bash ' + "modprobe vfio-pci")
            vm_sid[vm_id].sendline ('bash ' + "echo 1 > /sys/module/vfio/parameters/enable_unsafe_noiommu_mode")

        vm_sid[vm_id].sendline ('modprobe uio')
        vm_sid[vm_id].prompt()
        print vm_sid[vm_id].before
        vm_sid[vm_id].sendline ('insmod dpdk-kmods/linux/igb_uio/igb_uio.ko')
        vm_sid[vm_id].prompt()
        print vm_sid[vm_id].before
        if dpdk_bind_drv == "vfio-pci":
            vm_sid[vm_id].sendline ('usertools/dpdk-devbind.py -b vfio-pci 00:04.0')
        else:
            vm_sid[vm_id].sendline ('usertools/dpdk-devbind.py -b igb_uio 00:04.0')
        vm_sid[vm_id].prompt()
        print vm_sid[vm_id].before
        vm_sid[vm_id].sendline ('cd /home/dpdk/dpdk-stable-' + DPDK_VER + '/perf_scripts')
        vm_sid[vm_id].sendline ('chmod -R 777 *')
        #vm_sid[vm_id].sendline ('./dpdk_tune.sh')
        vm_sid[vm_id].prompt()
        print vm_sid[vm_id].before
    os.chdir(pwd)
    os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER + "/perf_scripts/")
    #os.system("./dpdk_tune.sh")
    # Measurement for testpmd
    if (testpmd_enable == 1):
        print "Executing testpmd\n"
        os.chdir(pwd)
        if (testpmd_host_num_queues == 0):
            os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER + "/examples/qdma_testapp/")
            child = pexpect.spawn("./build/qdma_testapp -c 0xf -n 4")
            child.expect('xilinx-app>')
            print child.before
        else:
            cores = testpmd_host_num_queues + 1
            core_mask = hex((0xFFFFFFFF >> (31-cores)))
            os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER)
            child = pexpect.spawn("./build/app/dpdk-testpmd -c" + str(core_mask) +" -n4 -a "+ str(bbddf) + ",desc_prefetch=1,cmpt_desc_len=16 --iova-mode=pa -- -i --nb-cores=" + str(cores) + " --rxq=" + str(testpmd_host_num_queues) + " --txq=" + str(testpmd_host_num_queues) + " --rxd=2048 --txd=2048 --burst=64 --mbuf-size=4224 --total-num-mbufs=32768")
            child.expect('testpmd>')
            print child.before
            child.sendline ('start')
            child.expect ('testpmd>')
            print child.before
        os.chdir(pwd)
        idx = 0
        while(idx < len_queues):
            queues = int(vm_queue_cfg[idx])
            for vm_id in range(1, nb_vms + 1):
                print ("queues = " + str(queues))
                cores = queues + 1
                core_mask = hex((0xFFFFFFFF >> (31-cores)))
                print ("core_mask = " + str(core_mask))
                vm_sid[vm_id].sendline ('cd /home/dpdk/dpdk-stable-' + DPDK_VER + '/')
                vm_sid[vm_id].prompt()
                print vm_sid[vm_id].before
                testpmd_cmd = "./build/app/dpdk-testpmd -c" + str(core_mask) +" -n4 -a 00:04.0,desc_prefetch=1,cmpt_desc_len=16 --iova-mode=pa -- -i --nb-cores=" + str(cores) + " --rxq=" + str(queues) + " --txq=" + str(queues) + " --rxd=2048 --txd=2048 --burst=64 --mbuf-size=4224 --total-num-mbufs=131072"
                print testpmd_cmd
                vm_sid[vm_id].sendline (testpmd_cmd)
                vm_sid[vm_id].expect ('testpmd>')
                vm_sid[vm_id].before
                vm_sid[vm_id].sendline ('start')
                vm_sid[vm_id].expect ('testpmd>')
                print vm_sid[vm_id].before

            os.chdir(pwd)
            perf_queues=(nb_vms * queues)
            vm_cfg.append(perf_queues)
            os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER + "/perf_scripts/testpmd_sw/")
            child1 = pexpect.spawn("./perf_lat.sh " + str(perf_queues) + " " + str(addr))
            child1.timeout = 2000
            child1.expect(pexpect.EOF)
            print child1.before

            for vm_id in range(1, nb_vms + 1):
                vm_sid[vm_id].sendline ('quit')
                vm_sid[vm_id].prompt()
                print vm_sid[vm_id].before
            idx = idx + 1
        vm_cfg_final = ",".join(str(item) for item in vm_cfg)
        os.chdir(pwd)
        os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER + "/perf_scripts/testpmd_sw/")
        print ("VM queue config = "+ str(vm_cfg_final))
        os.system("sh ./final_data_vm.sh " + str(vm_cfg_final))
        if (testpmd_host_num_queues == 0):
            os.chdir(pwd)
            os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER + "/examples/qdma_testapp/")
            child.send('\r')
            child.expect('xilinx-app>')
            child.sendcontrol('d')
            time.sleep(10)
        else:
            os.chdir(pwd)
            os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER + "/")
            child.send('\r')
            child.expect ('testpmd>')
            print child.before
            child.send('quit')
            print child.before
    # Measurement for pktgen
    elif (pktgen_enable == 1):
        print "Executing pktgen\n"
        os.chdir(pwd)
        if (pktgen_host_num_queues == 0):
            os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER + "/examples/qdma_testapp/")
            child = pexpect.spawn("./build/qdma_testapp -c 0xf -n 4")
            child.expect('xilinx-app>')
            print child.before
        else:
            os.chdir(workspace_path + "pktgen-22.04.1")
            child = pexpect.spawn("./pktgen_perf_vm.sh "+ bbddf + " " + str(pktgen_host_num_queues) + " 16_1 ")

        os.chdir(pwd)
        for vm_id in range(1, nb_vms + 1):
            print("VM ID =" + str(vm_id))
            print vm_sid[vm_id].before
            os.system("sshpass -p dpdk rsync -avz  -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "pktgen-22.04.1" + "   root@127.0.0.1:/home/dpdk/")
            vm_sid[vm_id].sendline ('cd /home/dpdk/pktgen-22.04.1')
            vm_sid[vm_id].prompt()
            print vm_sid[vm_id].before
            vm_sid[vm_id].sendline ('export RTE_SDK=/home/dpdk/dpdk-stable-' + DPDK_VER )
            vm_sid[vm_id].prompt()
            print vm_sid[vm_id].before
            vm_sid[vm_id].sendline ('export RTE_TARGET=build')
            vm_sid[vm_id].prompt()
            print vm_sid[vm_id].before
            vm_sid[vm_id].sendline ('make clean')
            vm_sid[vm_id].prompt()
            print vm_sid[vm_id].before
            vm_sid[vm_id].sendline ('make')
            vm_sid[vm_id].prompt()
            print vm_sid[vm_id].before
            pktgen_cmd = "./pktgen_perf_vm.sh 00:04.0 " + str(vm_pktgen_queue) + " 16_1"
            print pktgen_cmd
            vm_sid[vm_id].sendline (pktgen_cmd)
        time.sleep(30)
        os.chdir(pwd)
        os.chdir(workspace_path + "pktgen-22.04.1")
        os.system("chmod -R 777 *")
        child1 = pexpect.spawn("./perf_lat_pktgen.sh  " + str(addr))
        child1.timeout = 10000
        child1.expect(pexpect.EOF)
        print child1.before

        # Wait till the execution completes
        time.sleep(50)
        for vm_id in range(1, nb_vms + 1):
            os.chdir(pwd)
            os.chdir(workspace_path + "pktgen-22.04.1")
            os.system("mkdir -p vm" + str(vm_id) + "_logs/")
            os.system("sshpass -p dpdk scp -r -P " + str(base_port + vm_id) + " root@127.0.0.1:/home/dpdk/pktgen-22.04.1/test*.csv ./vm" + str(vm_id) + "_logs/")
            os.system("tar -cvzf vm" + str(vm_id) + "_logs.tar.gz vm" + str(vm_id) + "_logs/")
            vm_sid[vm_id].prompt()
            print vm_sid[vm_id].before
        os.chdir(pwd)
        os.chdir(workspace_path + "pktgen-22.04.1")
        if (pktgen_host_num_queues != 0):
            os.system("mv -f test_"+ str(pktgen_host_num_queues) + ".csv test_" + str(pktgen_host_num_queues) + "_" + str(vm_pktgen_queue) + ".csv")
        if (pktgen_host_num_queues == 0):
            os.chdir(pwd)
            os.chdir(workspace_path + "dpdk-stable-" + DPDK_VER + "/examples/qdma_testapp/")
            child.send('\r')
            child.expect('xilinx-app>')
            child.sendcontrol('d')
            time.sleep(10)
    for vm_id in range(1, nb_vms + 1):
        vm_sid[vm_id].sendline ('poweroff')
    time.sleep(10)
    for pf in range(0, nb_pf):
        #Remove num_vfs for each pf
        num_vf_cmd = "echo 0 > /sys/bus/pci/devices/0000:" + pci_bus + ":" + pci_dev + "." + str(pf) + "/max_vfs"
        print num_vf_cmd
        os.system(num_vf_cmd)
except pxssh.ExceptionPxssh, e:
    print "pxssh failed on login."
    print str(e)
