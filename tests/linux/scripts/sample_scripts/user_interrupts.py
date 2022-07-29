#!/usr/bin/python

import subprocess
import os
import sys



# Test case #1 
# Setup USER_INTERRUPT (0x094) for generating User Interrupt
# dma-ctl qdma<bdf> reg write bar 2 0x94 0x0<function id>0<User Vector Interrupt Number>1
# Example for bdf 01003 ,
# dma-ctl qdma01003 reg write bar 2 0x94 0x03011
#
# Observe the User interrupt being hit and on which function id it got fired.

# Test Case #2 
# Setup USER_INTERRUPT_MASK ( 0x098) , USER_INTERRUPT_VECTOR ( 0x09C ), USER_INTERRUPT (0x094) for generating User Interrupt
#
# Setup the User Interrupt Register
# dma-ctl qdma<bdf> reg write bar 2 0x94 0x0<function id>0<User Vector Interrupt Number>0
# Setup the USER_INTERRUPT_MASK for bits that need to be set in the USER_INTERRUPT_VECTOR for interrupt to be fired
# dma-ctl qdma<bdf> reg write bar 2 0x98 0x02
# Set the USER_INTERRUPT_VECTOR
# dma-ctl qdma<bdf> reg write bar 2 0x9C 0x02
# Observe the User interrupt being hit and on which function id it got fired.


if len(sys.argv) < 2:
    print ("Invalid arguments")
    print ("Usage: python user_interrupts.py <bdf>")
    print ("Ex: python user_interrupts.py 06000")
    sys.exit(0)

#Interrupt should be fired for these values.
intr_vec_no = ["0x01010", "0x02020", "0x03030"]

#Negative test cases, for which interrupt should not fire for these values.
intr_vec_no_neg = ["0x04040", "0x00202"]

dev_list = []
pci_bus = []
pci_dev = []
drv_path = "../../../../sw_host/linux/"
bdf = sys.argv[1]

def load_drv():
    global dev_list
#    os.system("cd " + drv_path + ";rmmod qdma_pf; rmmod qdma_vf; make uninstall-mods;sh make_libqdma.sh; make install-mods;sh ./scripts/qdma_generate_conf_file.sh " + str(bdf[:2]) + " 0 0 0;cd -")
    for pf in range(0,4):
        pci_bus.append(bdf[:2])
        pci_dev.append(bdf[2:4])

    for pf in range(0,4):
        os.system("modprobe qdma_pf") 
        os.system("modprobe qdma_vf") 
        num_vf_cmd = "echo 1 > /sys/bus/pci/devices/0000:" + pci_bus[pf] + ":" + pci_dev[pf] + "." + str(pf) + "/sriov_numvfs"
        os.system(num_vf_cmd)
        print num_vf_cmd

    dev_list = list(subprocess.check_output("dma-ctl dev list | awk '{print $1}'",shell=True).strip().split('\n'))




def user_intr(usr_intr_reg):
    for i in dev_list :
        os.system("dmesg -C > /dev/null")
        subprocess.call("dma-ctl "+ i +" reg write bar 2 "+ usr_intr_reg +" 0x0" + i[-1] + "011",shell=True)
        get_val = subprocess.check_output("dma-ctl " + i +" reg read bar 2 " + usr_intr_reg,shell=True)
        dmesg_log = subprocess.check_output("dmesg -c",shell=True)
        if "User IRQ fired on Funtion#"+ i[-1] in dmesg_log:
            print("User IRQ fired sucessfully")
        else:
            print("Failed to fire User IRQ")


def usr_intr_mask_vec (usr_mask,usr_vec, mask, neg, *val):
    for i in dev_list :
        os.system("dmesg -C > /dev/null")
        subprocess.call("dma-ctl "+ i +" reg write bar 2 " + usr_mask + " " + mask,shell=True)
        get_val = subprocess.check_output("dma-ctl " + i + " reg read bar 2 " + usr_mask,shell=True)
        for j in val:
            subprocess.check_output("dma-ctl " + i +" reg write bar 2 " + usr_vec + " " + str(j),shell=True)
            dmesg_log = subprocess.check_output("dmesg -c",shell=True)
            if (neg):
                if "User IRQ fired" in dmesg_log:
                    print("Neg test failed as User IRQ is fired:",j)
                else:
                    print("Neg test Passed: User IRQ not fired")
            else:
                if "User IRQ fired" in dmesg_log:
                    print("User IRQ fired sucessfully")
                else:
                    print("Failed to fire User IRQ :",j)

#            break


if __name__ == '__main__':
    print "#############################################################"
    print "######          Testing User Interrupts                ######"
    print "#############################################################"
    load_drv()
    user_intr("0x94")
    usr_intr_mask_vec("0x98","0x9C","0x03030",0,*intr_vec_no)
    usr_intr_mask_vec("0x98","0x9C","0x03030",1,*intr_vec_no_neg)
