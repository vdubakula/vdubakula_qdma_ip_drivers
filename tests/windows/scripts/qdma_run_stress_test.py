import os
import sys
import time
import array
import shutil
import random
import filecmp
import datetime
import platform
import threading
import subprocess

from colorama import init
from colorama import Fore, Back, Style


sln_dir = "HEAD\\proj\\sw_host\\windows"
sln_path = sln_dir + "\\QDMA.sln"
bin_path = ""
stress_test_dir = "HEAD\\proj\\sw_test\\windows\\apps\\qdma_stress\\"
stress_sln_path = stress_test_dir + "qdma_stress.sln"
stress_bin_path = ""
stress_test_exit = False
qdma_dev_list = ""
num_q = 2048
mm_q = num_q / 2
st_q = num_q / 2
num_devs = 4
num_q_per_pf = int(num_q / num_devs)
mm_q_lst = []
st_q_lst = []
min_len = 0
max_len = 64 # 4Kb

def print_error(msg):
    print (Fore.WHITE + Back.RED + msg)
    print (Style.RESET_ALL)

def print_warning(msg) :
    print (Fore.WHITE + Back.BLACK + msg)
    print (Style.RESET_ALL)

def print_success(msg):
    print (Fore.GREEN + msg)
    print (Style.RESET_ALL)

def print_msg(msg):
    print (msg)

def generate_data(fname, size, operation) :
    with open(fname, 'wb') as fout:
        if (operation == "random") :
            fout.write(os.urandom(size))
        else :
            #print_msg ("In ST C2H Data Generation : %d" % size)
            h_size = int(size / 2) + int(size % 2);
            while(h_size) :
                if (h_size >= 2048) :
                    pkt_cnt = int(h_size / 2048)
                    pkt_sz = 2048
                else :
                    pkt_cnt = 1
                    pkt_sz = h_size

                part_size = pkt_cnt * pkt_sz
                while (part_size) :
                    chunk = 65536 if (part_size > 65536) else part_size
                    part_size = part_size - chunk
                    #print_msg("part_size : %d, Chunk : %d" % (part_size, chunk))
                    data = array.array("H", range(chunk))
                    data.tofile(fout)
                h_size = h_size - (pkt_cnt * pkt_sz)
            if ((size % 2) != 0) :
                fout.truncate(size)

def build_stress_app(arch, build_mode) :
    cflags = ""
    log_file_name = "build_stress_app.log";
    # build the application
    log = open(log_file_name, 'w')
    cmd = "msbuild.exe %s /t:clean /t:build /p:Configuration=%s /p:Platform=%s /p:ExternalCompilerOptions=\"%s\"" % (stress_sln_path, build_mode, arch, cflags)
    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()
    log.close()

    if (p.returncode != 0) :
        print_error ("Failed to stress test")
        return False

    global stress_bin_path
    #stress_bin_path = ".\\..\\apps\\qdma_stress\\build\\%s\\%s\\bin" % (arch, build_mode)
    stress_bin_path = stress_test_dir + "build\\%s\\%s\\bin" % (arch, build_mode)

    print_success ("Stress application Built for %s mode for %s arch Successfully" % (build_mode, arch))

    return True;


def build_driver(arch, build_mode, run_mode) :
    cflags = "/DSTRESS_TEST"

    #bin_path = sln_dir + "\\build\\%s\\%s" % (arch, build_mode)

    # Make a copy of the original INF File
    inf_file = "%s\\sys\\drv\\qdma.inf" % sln_dir
    inf_bkp_file = "inf_bkp"
    shutil.copyfile(inf_file, inf_bkp_file)

    try:
        if (run_mode.lower() == "poll") :
            cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\inf_mode.ps1 '%s' 1" % (inf_file)
            p = subprocess.Popen(["powershell.exe", "-ExecutionPolicy", "RemoteSigned", cmd], stdout=sys.stdout)
            p.communicate()
            log_file_name = "build_poll.log";

        elif (run_mode.lower() == "intr") :
            cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\inf_mode.ps1 '%s' 2" % (inf_file)
            p = subprocess.Popen(["powershell.exe", "-ExecutionPolicy", "RemoteSigned", cmd], stdout=sys.stdout)
            p.communicate()
            log_file_name = "build_intr.log";

        elif (run_mode.lower() == "aggr") :
            cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\inf_mode.ps1 '%s' 3" % (inf_file)
            p = subprocess.Popen(["powershell.exe", "-ExecutionPolicy", "RemoteSigned", cmd], stdout=sys.stdout)
            p.communicate()
            log_file_name = "build_aggr.log";
        else :
            return False

        # Re-build the driver
        log = open(log_file_name, 'w')
        cmd = "msbuild.exe %s /t:clean /t:build /p:Configuration=%s /p:Platform=%s /p:ExternalCompilerOptions=\"%s\"" % (sln_path, build_mode, arch, cflags)
        p = subprocess.Popen(cmd, stdout=log)
        p.communicate()
        log.flush()
        log.close()

        if (p.returncode != 0) :
            print_error ("Failed to build the driver")
            return False

        print_success ("Driver Built for %s mode Successfully" % run_mode)

    finally:
        # Copy back the original inf file
        shutil.copyfile(inf_bkp_file, inf_file)

    return True

def install_driver(arch, build_mode) :
    bin_path = sln_dir + "\\build\\%s\\%s\\bin" % (arch, build_mode)
    log_file_name = "install_%s_%s.log" % (arch, build_mode)

    log = open(log_file_name, 'w')

    # Remove the already installed drivers
    '''
    cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\uinstall_driver.bat %s" % (arch)
    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()
    if (p.returncode != 0) :
        print_error ("Failed to uninstall previously installed drivers")
        return False
    '''
    uninstall_driver(arch, build_mode)
    # Re-Scan Devices
    cmd = "devcon.exe rescan"
    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()

    time.sleep(3)

    # Install the certificate to root and trsusted publisher places
    cmd = "certmgr.exe -add \"%s\\build\\%s\\%s\\sys\\QDMA.cer\" -s -r localmachine root" % (sln_dir, arch, build_mode)
    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()

    if (p.returncode != 0) :
        print_error ("Failed to Add certificate into root store")
        return False

    cmd = "certmgr.exe -add \"%s\\build\\%s\\%s\\sys\\QDMA.cer\" -s -r localmachine trustedpublisher" % (sln_dir, arch, build_mode)
    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()

    if (p.returncode != 0) :
        print_error ("Failed to Add certificate into trusted publisher store")
        return False

    # Install the driver using pnputil utility
    cmd = "pnputil.exe -i -a \"%s\\build\\%s\\%s\\sys\\QDMA Reference Driver\qdma.inf\"" % (sln_dir, arch, build_mode)
    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()

    log.close()

    if (p.returncode != 0) :
        print_error ("Failed to install the driver")
        return False

    time.sleep(3)

    # Test whether driver installed properly
    cmd = "%s\\dma-ctl.exe" % bin_path
    out = subprocess.check_output([cmd, "dev", "list"])
    out_str = out.decode("utf-8")
    if (out_str.find("No QDMA Devices") != -1) :
        print_error ("Failed to install the driver...No QDMA Devices are getting visible in device manager")
        return False

    print_success("Successfully installed the driver")

    print_msg ("Listing the QDMA devices in the system")
    print_msg (out_str)

    # Save the QDMA devices list
    global qdma_dev_list
    out_str = out_str.rstrip()
    qdma_dev_list = out_str.split("\n")

    return True

def uninstall_driver(arch, build_mode):
    log_file_name = "uninstall_%s_%s.log" % (arch, build_mode)

    log = open(log_file_name, 'w')

    # Remove the already installed drivers
    cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\uinstall_driver.bat %s" % (arch)
    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()
    if (p.returncode != 0) :
        print_error ("Failed to uninstall the drivers")
        return False

    # Re-Scan Devices
    cmd = "devcon.exe rescan"
    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()

    time.sleep(3)
    log.close()

    print_success("Successfully uninstalled the driver")

    return True

def prepare_dev_list(bus_no) :
    dev_list = []
    for i in range(num_devs):
        dev_list.append("qdma%s00%d" % (bus_no, i))

    return dev_list

def add_n_start_queue(dev_name, q_id, q_mode, log) :
    # Add the queue
    if(q_mode == "st") :
        trig_mode = "trigmode every"
        cmd = "%s\\dma-ctl.exe %s queue add mode %s idx_h2c_ringsz 0 idx_c2h_ringsz 0 %s qid %d" % (bin_path, dev_name, q_mode, trig_mode, q_id)
    else :
        cmd = "%s\\dma-ctl.exe %s queue add mode %s idx_h2c_ringsz 0 idx_c2h_ringsz 0 qid %d" % (bin_path, dev_name, q_mode, q_id)

    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()

    if (p.returncode != 0) :
        print_error ("Failed to add the queue : device : %s, q_id : %d", dev_name, q_id)
        return False

    # Start the queue
    cmd = "%s\\dma-ctl.exe %s queue start qid %d" % (bin_path, dev_name, q_id)

    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()

    if (p.returncode != 0) :
        remove_queue(dev_name, q_id, q_mode, log)
        print_error ("Failed to start the queue : device : %s, q_id : %d", dev_name, q_id)
        return False

    global mm_q_lst
    global st_q_lst
    if (q_mode == "mm") :
        mm_q_lst.append([dev_name, q_id])
    else :
        st_q_lst.append([dev_name, q_id])


    return True

def stop_queue(dev_name, q_id, log) :
    # Remove the queue
    cmd = "%s\\dma-ctl.exe %s queue stop qid %d" % (bin_path, dev_name, q_id)
    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()
    if (p.returncode != 0) :
        print_error ("Failed to stop the queue : device : %s, q_id : %d", dev_name, q_id)
        return False

    return True

def remove_queue(dev_name, q_id, log) :
    # Remove the queue
    cmd = "%s\\dma-ctl.exe %s queue delete qid %d" % (bin_path, dev_name, q_id)

    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()
    if (p.returncode != 0) :
        print_error ("Failed to remove the queue : device : %s, q_id : %d", dev_name, q_id)
        return False

    return True


def init_test_setup(dev_list, log) :
    global mm_q_lst
    global st_q_lst
    mm_q_lst = []
    st_q_lst = []
    not_found = 0
    for dev_name in dev_list :
        count = 0
        res = [i for i in qdma_dev_list if dev_name in i]
        if (res != []) :
            q_mode = "mm"
            # FIXME : Test
            # num_q_per_pf = 50
            for q_id in range(num_q_per_pf) :
                status = add_n_start_queue(dev_name, q_id, q_mode, log)

                if (status == True):
                    count = count + 1

                q_mode = "st" if (q_mode == "mm") else "mm"

            print_success ("Total %d queues added in device %s" % (count, dev_name))
        else :
            print_warning ("%s device not found in the list...Continuing stress test without that device" % dev_name)
            not_found = not_found + 1

    if (not_found >= len(dev_list)) :
        print_error ("Not Even single device found")
        return False

    return True

def teardown_test_setup(dev_list, log) :
    for dev_name in dev_list :
        count = 0
        res = [i for i in qdma_dev_list if dev_name in i]
        if (res != []) :
            # FIXME : Test
            # num_q_per_pf = 50
            for q_id in range(num_q_per_pf) :
                status = stop_queue(dev_name, q_id, log)
                if (status == True):
                    count = count + 1

                remove_queue(dev_name, q_id, log)

            print_success ("Total %d queues removed in device %s" % (count, dev_name))

    return True

def run_mm_h2c_c2h(run_mode) :
    #print_msg(mm_q_lst)

    xfer_cnt = 0;
    err_cnt = 0;
    addr = 0x0
    write_file = "data_write_file_mm.bin"
    read_file = "data_read_file_mm.bin"

    log_name = "run_mm_h2c_c2h_%s.txt" % run_mode
    FNULL = open(log_name, 'w')

    while(stress_test_exit == False):
        len = random.randint(min_len, max_len) * 4096
        #print_msg ("Len : %d" % len)
        generate_data(write_file, len, "random")

        for dev_name, q_id in mm_q_lst :
            if (stress_test_exit == True):
                break
            # Write Operation
            cmd = "%s\\dma-rw.exe %s queue_mm_%d write %d -l %u -f %s" % (bin_path, dev_name, q_id, addr, len, write_file)
            p = subprocess.Popen(cmd, stdout=FNULL)
            p.communicate()
            FNULL.flush()
            if ((p.returncode != 0) and (err_cnt < 10)) :
                print_error ("run_mm_h2c_c2h : Write Failed : device : %s, qid : %d, len : %u" % (dev_name, q_id, len))
                err_cnt = err_cnt + 1;
                if (err_cnt >= 10) :
                    print_error("run_mm_h2c_c2h : Max Err Limit Reached...Skipping further error prints")

            # Read Operation
            cmd = "%s\\dma-rw.exe %s queue_mm_%d read %d -l %u -b -f %s" % (bin_path, dev_name, q_id, addr, len, read_file)
            p = subprocess.Popen(cmd, stdout=FNULL)
            p.communicate()
            FNULL.flush()

            status = filecmp.cmp(write_file, read_file)
            if (status != True) :
                if (err_cnt < 10) :
                    print_error ("run_mm_h2c_c2h : Data comparison mismatch : device : %s, qid : %d, len : %u" % (dev_name, q_id, len))
                if (err_cnt == 10) :
                    print_error ("run_mm_h2c_c2h : Max Err Print `Limit Reached...Skipping further error prints")

                err_cnt = err_cnt + 1;
                continue;
            xfer_cnt = xfer_cnt + 1

    FNULL.close()
    print_msg("run_mm_h2c_c2h Thread Exiting : xfer_cnt : %d, err_cnt  %d" % (xfer_cnt, err_cnt))
    return True

def run_st_h2c(run_mode) :
    #print_msg(st_q_lst)

    xfer_cnt = 0;
    err_cnt = 0;
    retry_err_cnt = 0
    write_file = "data_write_file_sth2c.bin"

    log_name = "run_st_h2c_%s.txt" % run_mode
    FNULL = open(log_name, 'w')

    while(stress_test_exit == False):
        len = random.randint(min_len, max_len) * 4096
        #print_msg ("Len : %d" % len)
        generate_data(write_file, len, "incremental")
        for dev_name, q_id in st_q_lst :
            if (stress_test_exit == True):
                break
            '''
            #.\dma-rw.exe pf 0 user write 0xC 0x01 0x00 0x00 0x00
            cmd = "%s\\dma-rw.exe %s user write 0xC 0x01 0x00 0x00 0x00" % (bin_path, dev_name)
            p = subprocess.Popen(cmd, stdout=FNULL)
            p.communicate()
            '''

            # Write Operation
            cmd = "%s\\dma-rw.exe %s queue_st_%d write -l %u -f %s" % (bin_path, dev_name, q_id, len, write_file)
            out = subprocess.check_output(cmd)
            out_str = out.decode("utf-8")
            FNULL.write(out_str)

            if (out_str.find("Data generator returned SUCCESS for received data") == -1) :
                if (err_cnt < 10) :
                    print_error ("\n" + out_str)
                    print_error ("run_st_h2c : write failed, User logic data comparison mismatch, device : %s, qid : %d, len : %u" % (dev_name, q_id, len))

                cmd = "%s\\dma-rw.exe %s queue_st_%d write -l %u -f %s" % (bin_path, dev_name, q_id, len, write_file)
                out = subprocess.check_output(cmd)
                out_str = out.decode("utf-8")
                if ((out_str.find("Data generator returned SUCCESS for received data") == -1)) :
                    retry_err_cnt = retry_err_cnt + 1
                    if (retry_err_cnt < 10) :
                        print_error ("run_st_h2c : Consecutive Retry also write failed")

                if (err_cnt == 10) :
                    print_error("run_st_h2c : Max Err Print Limit Reached...Skipping further error prints")

                err_cnt = err_cnt + 1;
                continue
            xfer_cnt = xfer_cnt + 1

    print_msg("run_st_h2c Thread Exiting : xfer_cnt : %d, err_cnt : %d, retry_err_cnt : %d" % (xfer_cnt, err_cnt, retry_err_cnt))
    return True

def run_st_c2h(run_mode) :
    xfer_cnt = 0;
    err_cnt = 0;
    golden_file = "data_golden_file_stc2h.bin"
    read_file = "data_read_file_stc2h.bin"

    log_name = "run_st_c2h_%s.txt" % run_mode
    FNULL = open(log_name, 'w')

    while(stress_test_exit == False):
        len = random.randint(min_len, max_len) * 4096
        generate_data(golden_file, len, "incremental")
        for dev_name, q_id in st_q_lst :
            if (stress_test_exit == True):
                break
            # Read Operation
            cmd = "%s\\dma-rw.exe %s queue_st_%d read -l %u -b -f %s" % (bin_path, dev_name, q_id, len, read_file)
            p = subprocess.Popen(cmd, stdout=FNULL)
            p.communicate()
            FNULL.flush()
            if ((p.returncode != 0) and (err_cnt < 10)) :
                print_error ("run_st_c2h : Read Failed : device : %s, qid : %d, len : %u" % (dev_name, q_id, len))
                err_cnt = err_cnt + 1;
                if (err_cnt >= 10) :
                    print_error("run_st_c2h : Max Err Limit Reached...Skipping further error prints")

            status = filecmp.cmp(read_file, golden_file)
            if (status != True) :
                if (err_cnt < 10) :
                    print_error ("run_mm_h2c_c2h : Data comparison mismatch : device : %s, qid : %d, len : %u" % (dev_name, q_id, len))

                err_cnt = err_cnt + 1;

                if (err_cnt == 10) :
                    print_error("run_mm_h2c_c2h : Max Err Print Limit Reached...Skipping further error prints")
                continue;


            xfer_cnt = xfer_cnt + 1
    print_msg("run_st_c2h Thread Exiting : xfer_cnt : %d, err_cnt : %d" % (xfer_cnt, err_cnt))
    return True

def update_progress(job_title, progress):
    length = 20 # modify this to change the length
    block = int(round(length*progress))
    msg = "\r{0}: [{1}] {2}%".format(job_title, "#"*block + "-"*(length-block), round(progress*100, 2))
    if progress >= 1: msg += " DONE\r\n"
    sys.stdout.write(msg)
    sys.stdout.flush()

def run_test_app(num_pfs, num_q_per_pf, q_dist, run_time, log) :
    cmd = "%s\\qdma_stress.exe %d %d %s %d" % (stress_bin_path, num_pfs, num_q_per_pf, q_dist, run_time)

    print_warning("cmd : %s" % cmd)

    p = subprocess.Popen(cmd, stdout=log)
    p.communicate()
    log.flush()

    if (p.returncode != 0) :
        print_error ("Failed to run stress test")
        return False

    print_success("Stress Test ran successfully")

    return True

def run_test(dev_list, run_time, run_mode, log) :
    #generate_random_data("data_test_log1.txt", 1024)
    global stress_test_exit

    stress_test_exit = False
    mm_th  = threading.Thread(target=run_mm_h2c_c2h, args=(run_mode,))
    st_th1 = threading.Thread(target=run_st_h2c, args=(run_mode,))
    st_th2 = threading.Thread(target=run_st_c2h, args=(run_mode,))

    mm_th.start()
    st_th1.start()
    st_th2.start()

    total_time = run_time
    acc_time = 0;
    # sleep_time = run_time if (int(run_time / 5) == 0) else 5
    # print_msg("Sleep time : %d" % sleep_time)

    while (run_time > 0) :
        sleep_time = run_time if (int(run_time / 5) == 0) else 5
        #print_msg ("Executing the Queue Transfers : %d" % run_time)
        update_progress("Stress Test Transfers", (acc_time + sleep_time)/total_time)
        run_time = run_time - sleep_time
        acc_time = acc_time + sleep_time
        time.sleep(sleep_time)

    stress_test_exit = True

    mm_th.join()
    st_th1.join()
    st_th2.join()


    return True

def run_stress_test(run_mode, bus_no, no_q, run_time):
    try :
        print_msg ("--------------------------------------")
        print_msg ("Running stress test in %s mode" % run_mode)
        print_msg ("--------------------------------------")
        build_mode = "Release"
        # Deduce machine architecture
        if (platform.machine() == "AMD64") :
            arch = "x64"
        else :
            arch = "x86"

        global num_q
        global mm_q
        global st_q
        global num_q_per_pf
        num_q = no_q
        mm_q = num_q / 2
        st_q = num_q / 2
        num_q_per_pf = int(num_q / num_devs)

        global bin_path
        bin_path = sln_dir + "\\build\\%s\\%s\\bin" % (arch, build_mode)
        #'''
        # Build the driver for given arch and build_mode
        status = build_driver(arch, build_mode, run_mode)
        if (status == False):
            return False
        #'''

        # Install the driver
        status = install_driver(arch, build_mode)
        if (status == False):
            return False

        # Build the stress test application
        status = build_stress_app(arch, build_mode)
        if (status == False):
            return False

        run_start_time = datetime.datetime.now()

        log_fname = "setup_%s_%s.log" % (arch, run_mode)
        log = open(log_fname, 'w')

        # run the test
        status = run_test_app(num_devs, num_q_per_pf, "BOTH", run_time, log);
        if (status == False):
            return False

        run_end_time = datetime.datetime.now()

        log.close()

        with open(log_fname, 'r') as fin:
            print(fin.read())

        print_msg ("Total time taken to run stress test : Planned run time: " + str(run_time) + " seconds, Actual run time : " + str((run_end_time - run_start_time).total_seconds()) + " seconds")


        '''
        dev_list = prepare_dev_list(bus_no)
        log_fname = "setup_%s_%s.log" % (arch, run_mode)
        log = open(log_fname, 'w')

        # Init the test setup
        status = init_test_setup(dev_list, log)
        if (status == False):
            uninstall_driver(arch, build_mode)
            return False

        run_start_time = datetime.datetime.now()

        # run the test
        run_test(dev_list, run_time, run_mode, log)

        run_end_time = datetime.datetime.now()

        print_msg ("Total time taken to run stress test : Planned run time: " + str(run_time) + " seconds, Actual run time : " + str((run_end_time - run_start_time).total_seconds()) + " seconds")

        teardown_test_setup(dev_list, log)

        log.close()
        '''
    finally:
        # Uninstall the driver
        status = uninstall_driver(arch, build_mode)
        if (status == False):
            return False

