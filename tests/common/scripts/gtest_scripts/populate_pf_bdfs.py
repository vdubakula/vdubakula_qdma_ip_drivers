import getpass
import os
import time
import sys
import subprocess
from array import array

if sys.argv[1] == "EQDMA" :
	pf_devids = ["903f", "913f", "923f", "933f"]
	pf_bdfs = [[], [], [], []]
elif sys.argv[1] == "Ultrascale" :
	pf_devids = ["903f", "913f", "923f", "933f"]
	pf_bdfs = [[], [], [], []]
elif  sys.argv[1] == "Everest" :
	pf_devids = ["b03f", "b13f", "b23f", "b33f"]
	pf_bdfs = [[], [], [], []]
else :
	print "Invalid Device"
	exit(1)

subprocess.Popen("rm -rf pci_dev_list*", shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
cmd = "lspci | grep -i xilinx | awk '{print $1\" \"$7}'"
a = subprocess.Popen(cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
output = a.communicate()[0]
out = output.replace('\n',' ').strip().split(' ')
pci_dic = dict(zip( * [iter(out)] * 2))

for k, v in pci_dic.iteritems():
	for pf in range(0, 4):
		if (v == pf_devids[pf]):
			pf_bdfs[pf].append(k)
			bdf1 = pf_bdfs[pf].pop()
			bdf1 = bdf1.replace(':','')
			bdf1 = bdf1.replace('.','')
			cmd1 = "echo \"Card" + str(pf + 1) +":" + bdf1 + "\" >> pci_dev_list.txt "
			subprocess.Popen(cmd1, shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT)

			
