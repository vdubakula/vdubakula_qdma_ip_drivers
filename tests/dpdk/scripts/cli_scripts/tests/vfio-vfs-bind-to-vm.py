import subprocess
import os

cmd = "lspci | grep -i xilinx | awk '{print $1\" \"$7}'"
a = subprocess.Popen(cmd,shell=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
output = a.communicate()[0]
out = output.replace('\n',' ').strip().split(' ')
pci_dic = dict(zip(*[iter(out)]*2))

for k, v in pci_dic.iteritems():
    # 40960 == 0xa000
    if (int(v,16) > 40960):
        os.system ("echo \"10ee "+v+"\" > /sys/bus/pci/drivers/vfio-pci/new_id")
        os.system ("echo 0000:"+k+" > /sys/bus/pci/devices/0000:"+k+"/driver/unbind")
        os.system ("echo 0000:"+k+" > /sys/bus/pci/drivers/vfio-pci/bind")
        print ("VF's bdf: "+k+" device-id "+v+" binded to vfio")
