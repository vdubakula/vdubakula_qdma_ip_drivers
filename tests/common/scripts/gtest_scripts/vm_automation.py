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
pf_vfs_devid = ["a03f", "a13f", "a23f", "a33f", "c03f", "c13f", "c23f", "c33f"]
pf_vfs_bdfs = [[], [], [], []]
vf_pf_qs = []
config_file_in = "./gtest_configs_qdma_soft/vf_2kq/pf0_vf_2048q.txt"
config_file_out = "./pf0_vf_2048q.txt"
mm_test_file = "mm_pf_test.txt"
st_test_file = "st_pf_test.txt"

def_cfg_pf_nvf = "pf_nvf"
valid_drv = "valid_drv"
dummy_line = "#necessary dummy line"
def_cfg_vf_pf_qs = []

MAX_PFS = 4
MAX_VMS = 4 # existing VM images on a given system.
VM_CFG_START = 12

dpdk_bind_drv = "igb_uio"
dpdk_bind_drv_idx = 0
child = ""
DPDK_VER="22.11"

#-----------------------------------------------------
#Path to /HEAD or /REL or /DEV branches
workspace_path = "../../../../"

program_name = sys.argv[0]
arg_count = len(sys.argv)

if arg_count < 12 :
    print("Invalid commandline args !!\n")
    print("Usage : python " + program_name + " <gtest_script_path>  <gtest_command> <host_drv_path> <driver_used> <bdf> <vm_image_path> <vm_count(say n)> <config_file_in> <config_file_out> <vm_ram> <num_pf> <vm1_config> <vm2_config> ... <vm-n_config> <bind_driver> <config_bar>\n")
    print("Example : python " + program_name + " \"/home/dpdk/REL/2019.1_patch/sw_test/qdma/scripts/common/gtest_scripts/\" \"./gtest_top.sh 04000 ../../../../../../../REL/2019.1_patch/sw_test/qdma/scripts/common/gtest_scripts/gtest_configs/default/ ../../../../../../../REL/2019.1_patch/sw_host/mdma/ ../../../../../../../REL/2019.1_patch/sw_test/qdma/apps/qdma_test vf linux 0 \" \"../../../../../../../REL/2019.1_patch/sw_host/mdma/linux\" linux 04000 /group/cdc_hd/members/vm_images 2 \"gtest_configs_qdma_soft/default_vf/\" \"default_vf.txt\" 20760 4 1024 \"1 2 3 0\"  \"3 2 2 1\" igb_uio 2 \n")
    sys.exit(0)

gtest_script_path = sys.argv[1]
gtest_command = sys.argv[2]
host_drv_path = sys.argv[3]
drv_used = sys.argv[4]
bbddf_array = sys.argv[5].split(' ')
vm_image_path = sys.argv[6]
nb_vms = int(sys.argv[7])
file_in = str(sys.argv[8])
file_out = str(sys.argv[9])
vm_ram = int(sys.argv[10])
nb_pf = int(sys.argv[11])
vf_queues = int(sys.argv[12])

pci_bus =[]
pci_dev =[]
bddf_array_length = len(bbddf_array)
total_pfs = bddf_array_length * nb_pf
eal_options = ""
flter_file = file_in.split("/",2)
filter_out = str(flter_file[1])
print ("filter_out is " + filter_out)
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
    def_cfg_vf_pf_qs.append("vf_pf" + str(pf) + "_qmax")
    print ("def_cfg_vf_pf_qs = " + str(def_cfg_vf_pf_qs[pf]))

config_file_in = "./" + str(file_in) + str(file_out)
config_file_out = "./" + str(file_out)
print ("file_in = " + str(config_file_in))
print ("file_out = " + str(config_file_out))
print ("nb_pf = " + str(nb_pf))
print ("vm_ram = " + str(vm_ram))
print ("vf_queues = " + str(vf_queues))

if drv_used == "dpdk":
    dpdk_bind_drv_idx = VM_CFG_START + nb_vms + 1
    dpdk_bind_drv = sys.argv[dpdk_bind_drv_idx]
    print("DPDK bind driver: " + dpdk_bind_drv + " \n")

#Getting config BAR
config_bar_idx = VM_CFG_START + nb_vms + 2
config_bar = sys.argv[config_bar_idx]

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

    for pf in range(0, total_pfs):
        pf_vfs_cnt[pf] = pf_vfs_cnt[pf] + int(vm_vfs[pf])
        vf_pf_qs[vm_id - 1].append([])
        for vf in range(0, int(vm_vfs[pf])):
            vf_pf_qs[vm_id - 1][pf].append(vf_queues) # set number of queues as 10 for each valid vf

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

else :#dpdk
    pwd = os.getcwd()
    os.chdir(workspace_path + "dpdk-stable-"+DPDK_VER+"/examples/qdma_testapp/")
    dpdk_testapp_path = os.getcwd()
    os.system("chmod +x *.sh")
    os.system("sh setup.sh")

    if dpdk_bind_drv == "vfio-pci":
        for pf in range(0, total_pfs):
            os.system("../../usertools/dpdk-devbind.py -b igb_uio " + pci_bus[pf] + ":" + pci_dev[pf] + "." + str(pf%nb_pf))

            #set num_vfs for each pf
            num_vf_cmd = "echo " + str(pf_vfs_cnt[pf]) + " > /sys/bus/pci/devices/0000:" + pci_bus[pf] + ":" + pci_dev[pf] + "." + str(pf%nb_pf) + "/max_vfs"
            os.system(num_vf_cmd)

            os.system("../../usertools/dpdk-devbind.py -u " + pci_bus[pf] + ":" + pci_dev[pf] + "." + str(pf%nb_pf))

        os.system("modprobe vfio-pci")
        for pf in range(0, total_pfs):
            os.system("../../usertools/dpdk-devbind.py -b vfio-pci " + pci_bus[pf] + ":" + pci_dev[pf] + "." + str(pf%nb_pf))

            if DPDK_VER == "20_11":
		eal_options = eal_options + " -w " + pci_bus[pf] + ":" + pci_dev[pf] + "." + str(pf%nb_pf) + ",config_bar="+ str(config_bar)
	    else:
	        eal_options = eal_options + " -a " + pci_bus[pf] + ":" + pci_dev[pf] + "." + str(pf%nb_pf) + ",config_bar="+ str(config_bar)

    else:
        for pf in range(0, total_pfs):
            os.system("../../usertools/dpdk-devbind.py -b igb_uio " + pci_bus[pf] + ":" + pci_dev[pf] + "." + str(pf%nb_pf))

	    if DPDK_VER == "20_11":
                eal_options = eal_options + " -w " + pci_bus[pf] + ":" + pci_dev[pf] + "." + str(pf%nb_pf) + ",config_bar="+ str(config_bar)
	    else:
	        eal_options = eal_options + " -a " + pci_bus[pf] + ":" + pci_dev[pf] + "." + str(pf%nb_pf) + ",config_bar="+ str(config_bar)

        for pf in range(0, total_pfs):
            #set num_vfs for each pf
            num_vf_cmd = "echo " + str(pf_vfs_cnt[pf]) + " > /sys/bus/pci/devices/0000:" + pci_bus[pf] + ":" + pci_dev[pf] + "." + str(pf%nb_pf) + "/max_vfs"
            os.system(num_vf_cmd)
    print ("EAL options = " + str(eal_options))
    child = pexpect.spawn("./build/qdma_testapp -c 0xf -n 4"+ str(eal_options))
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
        if (v == pf_vfs_devid[pf]) or (v == pf_vfs_devid[pf + MAX_PFS]):
            pf_vfs_bdfs[pf].append(k)

for vm_id in range(1, nb_vms + 1):
    idx = VM_CFG_START + vm_id #vm config starts from index 8
    vm_cfg = str(sys.argv[idx]) # vm_cfg = "3 0 1 1"
    vm_vfs = vm_cfg.split()
    vm_bdf_assign = ""
    vf_bdf = ""
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
                vf_bdf = pf_vfs_bdfs[pf%nb_pf].pop()
                if drv_used == "dpdk":
                    pwd = os.getcwd()
                    os.chdir(dpdk_testapp_path)
                    os.system("../../usertools/dpdk-devbind.py -b vfio-pci " + vf_bdf)
                    os.chdir(pwd)
                vm_bdf_assign = vm_bdf_assign + " -device vfio-pci,host=" + vf_bdf
    port = base_port + vm_id
    vm_cmd = ""
    vm_cmd = "qemu-system-x86_64 -cpu host -enable-kvm -m " + str(vm_ram) + " -smp sockets=1,cores=4 -hda " + vm_image_path + "/vm" + str(vm_id) + ".qcow2  -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::" + str(port) + "-:22 " + vm_bdf_assign + " -vnc :" + str(port) + "  &"
    print vm_cmd
    os.system(vm_cmd)
# Let vms up
print("Entering to sleep for 3 minutes\n")
time.sleep(180)

try:
    for vm_id in range(1, nb_vms + 1):
        print("VM ID = " + str(vm_id))
        def_no = 0
        idx = VM_CFG_START + vm_id #vm config starts from index 9
        vm_cfg = str(sys.argv[idx])
        with open(config_file_in, "rt") as fin:
            with open(config_file_out, "wt") as fout:
                for line in fin:
                    if def_cfg_pf_nvf in line:
                        fout.write(def_cfg_pf_nvf + "=" + "(" + vm_cfg + ")\n")
                    elif valid_drv in line:
                        fout.write(line)
                    elif dummy_line in line:
                        fout.write(line)
                    elif def_cfg_vf_pf_qs[def_no] in line:
                        fout.write(def_cfg_vf_pf_qs[def_no] + "=" + "(" + re.sub('[\[\],]', '', repr(vf_pf_qs[vm_id - 1][def_no])) + ")\n")
                        def_no = def_no + 1
                    else:
                        fout.write(line)
        os.system("ssh-keygen -f \"/root/.ssh/known_hosts\" -R \"[127.0.0.1]:" + str(base_port) + "\"")
        s = pxssh.pxssh(timeout = 5000)
        s.login ("127.0.0.1", "root", "dpdk", port = base_port + vm_id)

        if drv_used == "dpdk":
            os.system("sshpass -p dpdk rsync -avz  -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "dpdk-stable-"+DPDK_VER+"/drivers/net/qdma" + "  root@127.0.0.1:/home/dpdk/dpdk-stable-"+DPDK_VER+"/drivers/net/")
            os.system("sshpass -p dpdk rsync -avz  -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "dpdk-stable-"+DPDK_VER+"/examples/qdma_testapp" + "  root@127.0.0.1:/home/dpdk/dpdk-stable-"+DPDK_VER+"/examples/")
            os.system("sshpass -p dpdk rsync -avz  -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "incoming" + "  root@127.0.0.1:/home/dpdk/")
            os.system("sshpass -p dpdk rsync -avz  -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "drivers" + "  root@127.0.0.1:/home/dpdk/")
            os.system("sshpass -p dpdk rsync -avz  -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "tests" + "  root@127.0.0.1:/home/dpdk/")
            os.system("sshpass -p dpdk rsync -avz  -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "util" + "  root@127.0.0.1:/home/dpdk/")
        else:
            os.system("sshpass -p dpdk rsync -avz  -e 'ssh -p " + str(base_port + vm_id) + " ' "+ workspace_path + "  root@127.0.0.1:/home/dpdk/")

        os.system("sshpass -p dpdk scp -P " + str(base_port + vm_id) + " "+ config_file_out + " root@127.0.0.1:" + gtest_script_path + str(file_in))
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

        print("Entering to sleep while test execution is in progress on vm " + str(vm_id) + " \n")
        if dpdk_bind_drv == "vfio-pci":
            time.sleep(600)
        else:
            time.sleep(60)

        print("Collecting logs from vm " + str(vm_id) + " \n")
        s.sendline ('echo --------------------------------------------vm_' + str(vm_id) + ' done---------------------------------------------------------------')
        os.system("sshpass -p dpdk scp -r -P " + str(base_port + vm_id) + " root@127.0.0.1:" + gtest_script_path + "/../../apps/qdma_test/logs ./vm" + str(vm_id) + "_logs/")

        os.system("tar -cvzf vm" + str(vm_id) + "_logs.tar.gz vm" + str(vm_id) + "_logs/")
        s.prompt()
        print s.before
        s.logout()

    if drv_used == "dpdk":
        os.chdir(workspace_path + "dpdk-stable-"+DPDK_VER+"/examples/qdma_testapp/")
        os.system("rm -f test_status")
        child.timeout = 120
        if filter_out != "vf_2kq" and  filter_out != "vf_mm_completion" and filter_out != "vf_hw_loopback":
            print "Run mm tests on all PFs"
            with open(mm_test_file, "rt") as mm_fin:
                for line in mm_fin:
                    child.send(line)
                    child.expect('xilinx-app>')
            print "Run st tests on all PFs"
            with open(st_test_file, "rt") as st_fin:
                for line in st_fin:
                    child.send(line)
                    child.expect('xilinx-app>')
            os.system("sh mm_pf_dev_verf.sh")
            os.system("sh st_pf_dev_verf.sh")
            os.system("cat test_status")
        child.sendcontrol('d')

except pxssh.ExceptionPxssh, e:
    print "pxssh failed on login."
    print str(e)
