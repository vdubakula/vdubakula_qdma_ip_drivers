#!/usr/bin/python

import subprocess
import sys
import os


#Test case #1 - Single Bit Error Injection
#Method -1
#a. Load the bitstream
#b. Build and insert the kernel module
#c. Write QDMA_RAM_SBE_MSK_A at address 0xf0. Set all bits to 1.
#    dma-ctl qdma01000 reg write bar 2 0xf0 0xff
#d. Write 1 example design register using BAR2 at address 0x68
#    dma-ctl qdma01000 reg write bar 2 0x68 1
#e. Add queue and start traffic.
#   dma-ctl qdma01000 q add idx 0 mode mm dir h2c
#   dma-ctl qdma01000 q start idx 0 dir h2c
#   dma-to-device -d /dev/qdma01000-MM-0 -s 4096
#
#Observe the dmesg logs for error interrupt handler being hit.
#Method -2
#a. Follow Steps (a) to (d) above.
#b. In HEAD\proj\sw_host\mdma\linux\scripts\qdma_run_test_pf.sh, comment out calls to run_st_c2h & run_st_h2c.
#c. Run the script with the parameters as -
#    ./qdma_run_test_pf.sh 01000 0 1 0 1 1 0
#Observe the dmesg logs for the error interrupt handler being hit and the script passing successfully.



#Test case #2 - Double Bit Error Injection
#Build and insert the kernel module
#Write QDMA_RAM_DBE_MSK_A at address 0xf8. Set all bits to 1.
#dma-ctl qdma01000 reg write bar 2 0xf8 0xff
#Write 1 example design register using BAR2 at address 0x6C
# Execute Method-1 and 2 as mentioned in Test case #1
#Observe that the error interrupt handler is being hit and the script failing as the transfer output is having errors.


if len(sys.argv) < 2:
    print ("Invalid arguments")
    print ("Usage: python err_interrupts.py <bdf>")
    print ("Ex: python err_interrupts.py 06000")
    sys.exit(0)


drv_path = "../../../../drivers/linux/"
bdf = sys.argv[1]

def load_drv():
    global dev_list
    os.system("cd " + drv_path + ";rmmod qdma_pf; rmmod qdma_vf; make uninstall-mods;sh make_libqdma.sh; make install-mods;sh ./scripts/qdma_generate_conf_file.sh " + str(bdf[:2]) + " 0 0 0;cd -")
    os.system("modprobe qdma_pf")
    os.system("modprobe qdma_vf")
    qmax_cmd = "echo 10 > /sys/bus/pci/devices/0000:" + bdf[:2] + ":" + bdf[2:4] + "." + bdf[-1] + "/qdma/qmax"
    os.system(qmax_cmd)
    dev_list = list(subprocess.check_output("dma-ctl dev list | awk '{print $1}'",shell=True).strip().split('\n'))


def single_bit_err_intr(RAM_SBE_MSK_A):
    for i in dev_list :
        os.system("dmesg -C > /dev/null")
        subprocess.call("dma-ctl "+ i +" reg write bar 2 "+ RAM_SBE_MSK_A +" 0xff",shell=True)
        subprocess.call("dma-ctl "+ i +" reg write bar 2 0x68 1",shell=True)
        subprocess.call("dma-ctl "+ i +" q add idx 0 mode mm dir h2c",shell=True)
        subprocess.call("dma-ctl "+ i +" q start idx 0 dir h2c",shell=True)
        subprocess.call("dma-to-device -d /dev/qdma06000-MM-0 -s 4096",shell=True)
        dmesg_log = subprocess.check_output("dmesg -c",shell=True)
        if "Error IRQ fired on Funtion#0" in dmesg_log:
            print("Error IRQ fired sucessfully")
        else:
            print("Failed to fire Error IRQ")
        os.system("ln -sf ../../../../drivers/linux/scripts/qdma_run_test_pf.sh")
        os.system("sed -i 's/^run_st_h2c/#run_st_h2c/' qdma_run_test_pf.sh")
        os.system("sed -i 's/^run_st_c2h/#run_st_c2h/' qdma_run_test_pf.sh")
        test_log = subprocess.check_output("./qdma_run_test_pf.sh 06000 0 5 0 1 1 0",shell=True)
        print test_log
        dmesg_log = subprocess.check_output("dmesg -c",shell=True)
        if "Error IRQ fired on Funtion#0" in dmesg_log:
            print("Error IRQ fired sucessfully")
        else:
            print("Failed to fire Error IRQ")



def double_bit_err_intr(RAM_DBE_MSK_A):
    os.system("rmmod qdma-pf")
    os.system("dma-ctl qdma06000 reg write bar 2 0xA0 0x1")
    os.system("modprobe qdma-pf")
    qmax_cmd = "echo 10 > /sys/bus/pci/devices/0000:" + bdf[:2] + ":" + bdf[2:4] + "." + bdf[-1] + "/qdma/qmax"
    os.system(qmax_cmd)
    for i in dev_list :
        os.system("dmesg -C > /dev/null")
        subprocess.call("dma-ctl "+ i +" reg write bar 2 "+ RAM_DBE_MSK_A +" 0xff",shell=True)
        subprocess.call("dma-ctl "+ i +" reg write bar 2 0x6c 1",shell=True)
        subprocess.call("dma-ctl "+ i +" q add idx 0 mode mm dir h2c",shell=True)
        subprocess.call("dma-ctl "+ i +" q start idx 0 dir h2c",shell=True)
        subprocess.call("dma-to-device -d /dev/qdma06000-MM-0 -s 4096",shell=True)
        dmesg_log = subprocess.check_output("dmesg -c",shell=True)
        if "Error IRQ fired on Funtion#0" in dmesg_log:
            print("Error IRQ fired sucessfully")
        else:
            print("Failed to fire Error IRQ")
        test_log = subprocess.check_output("./qdma_run_test_pf.sh 06000 0 5 0 1 1 0",shell=True)
        print test_log
        dmesg_log = subprocess.check_output("dmesg -c",shell=True)
        if "Error IRQ fired on Funtion#0" in dmesg_log:
            print("Error IRQ fired sucessfully")
        else:
            print("Failed to fire Error IRQ")

if __name__ == '__main__':
    print "#############################################################"
    print "######          Testing Error Interrupts               ######"
    print "#############################################################"
    load_drv()
    single_bit_err_intr("0xf0")
    double_bit_err_intr("0xf8")
