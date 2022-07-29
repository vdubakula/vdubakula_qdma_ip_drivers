import sys
import os
import getopt
import subprocess
import shutil
import datetime
import time
import zipfile
from prettytable import PrettyTable

'''
Usage : python gtest_top.py -c <config_dir> -a <ARCH> -m <Debug|Release> -s [<src dir>] -t [<gtest dir>] -f <cflags> -h
'''

#Global Variables/Parameters
#config_base_dir = "proj\sw_test\qdma\scripts\windows\\..\\common\\gtest_scripts\\gtest_configs"
config_base_dir = os.path.dirname(os.path.realpath(__file__))+"\\..\\..\\common\\gtest_scripts\\gtest_configs"
config_dir = ""
arch = "x64"
build_mode = "Debug"
cflags = ""
src_dir = os.path.dirname(os.path.realpath(__file__))+"\\..\\..\\..\\..\\..\\sw_host\\mdma\\windows"
src_path = src_dir + "\\QDMA.sln"
test_dir = os.path.dirname(os.path.realpath(__file__))+"\\..\\..\\..\\apps\\qdma_test\\vs_solution"
test_path = test_dir + "\\qdma_test.sln"
config_bar="0"
parser_path = os.path.dirname(os.path.realpath(__file__))+"\\..\\..\\common\\scripts\\gtest_scripts\\qdma_gtest_result_parser.py"

d = dict()

d['name'] = "Invalid"
d['mask'] = 0x0
d['repeat'] = 1
d['filter'] = "*MM*"
d['master_pf'] = 1
d['run_gtest'] = 0
d['run_disabled'] = 0
d['valid_drv'] = "windows"

global_exec_sts = 0
global_run_sts = 0
gen_report = True

def print_message(msg):
    t = PrettyTable(['Message'])
    t.add_row([msg])
    print(t)

def usage():
    print ("usage : python %s [OPTIONS]\n" % sys.argv[0])
    print ("Executes the google test regressions for QDMA windows driver\n\n")
    print ("Mandatory arguments")
    print ("\t -c, --config-dir\t gtest configuration files directory")
    print ("\n")
    print ("optional arguments")
    print ("\t -a, --arch\t\t Target system Architecture (default : x64)")
    print ("\t -m, --build-mode\t Project build mode (default : Debug)")
    print ("\t -s, --src-dir\t\t QDMA driver source directory")
    print ("\t -t, --test-dir\t\t QDMA gtest suite directory")
    print ("\t -f, --cflags\t\t CFLAGS for QDMA driver")
    print ("\t -b, --bar-config-index \t\t Config BAR Index for inf configuration")

    print ("\n")
    sys.stdout.flush()




def parse_cfg_file(config_dir, name):
    fname = os.path.join(config_dir, name)
    with open(fname, mode = 'r') as fhandle:
        for line in fhandle:
            if (line[0] == '#') :
                # Ignore comments
                continue

            s = line.split('=')

            if (s[0] == "name") :
                d['name'] = s[1].split('#')[0].replace('\n', '')
            elif (s[0] == "test_mask") :
                d['mask'] = int (s[1].split('#')[0], 16)
            elif (s[0] == "repeat") :
                d['repeat'] = int (s[1].split('#')[0])
            elif (s[0] == "filter") :
                d['filter'] = s[1].split('#')[0].replace('\n', '')
            elif (s[0] == "master_pf") :
                d['master_pf'] = int (s[1].split('#')[0])
            elif (s[0] == "run_gtest") :
                d['run_gtest'] = int (s[1].split('#')[0])
            elif (s[0] == "run_disabled") :
                d['run_disabled'] = int (s[1].split('#')[0])
            elif (s[0] == "pf_qmax_cfg_en") :
                temp = s[1].split('#')[0]
                temp = temp.replace('(', '')
                temp = temp.replace(')', '')
                temp = temp.replace('\n', '')
                temp = temp.split(' ')
                d['pf_qmax_cfg_en'] = []

                for list_item in temp:
                    d['pf_qmax_cfg_en'].append(int (list_item))
            elif (s[0] == "pf_qmax") :
                temp = s[1].split('#')[0]
                temp = temp.replace('(', '')
                temp = temp.replace(')', '')
                temp = temp.replace('\n', '')
                temp  = temp.split(' ')
                d['pf_qmax'] = []

                for list_item in temp:
                    d['pf_qmax'].append(int (list_item))
            elif (s[0] == "pf_nvf") :
                temp = s[1].split('#')[0]
                temp = temp.replace('(', '')
                temp = temp.replace(')', '')
                temp = temp.replace('\n', '')
                temp = temp.split(' ')
                while("" in temp):
                    temp.remove("") 
                d['pf_nvf'] = []
                for list_item in temp:
                    d['pf_nvf'].append(int(list_item))
            elif (s[0] == "vf_pf0_qmax") :
                # ignore the parameter for now
                pass
            elif (s[0] == "vf_pf1_qmax") :
                # ignore the parameter for now
                pass
            elif (s[0] == "vf_pf2_qmax") :
                # ignore the parameter for now
                pass
            elif (s[0] == "vf_pf3_qmax") :
                # ignore the parameter for now
                pass
            elif (s[0] == "valid_drv") :
                temp = s[1].split('#')[0]
                temp = temp.replace('(', '')
                temp = temp.replace(')', '')
                temp = temp.replace('\n', '')
                temp = temp.split(' ')


                d['valid_drv'] = temp;

def run_dma_rw_cmd(cmd):
    dma_rw = src_dir +  "/" + "build" + "/" + arch + "/" + build_mode + "/" + "bin" + "/" + "dma-rw.exe"
    dma_rw_cmd = "%s %s" % (dma_rw, cmd)
    
    dma_rw_logfile = open(d['name'] + "_dma_rw_log.txt", "w")
    print(dma_rw_cmd)
    p = subprocess.Popen(dma_rw_cmd, stdout=dma_rw_logfile)
    p.communicate()
    dma_rw_logfile.close()
    
    dma_rw_logfile = open(d['name'] + "_dma_rw_log.txt", "r")

    output = ""
    for line in dma_rw_logfile :
        if(len(line)) :
            output += line.rstrip()
            output += "\n"

    dma_rw_logfile.close()
    return output

def run_dmactl_cmd(cmd):
    dmactl = src_dir +  "/" + "build" + "/" + arch + "/" + build_mode + "/" + "bin" + "/" + "dma-ctl.exe"
    dmactl_cmd = "%s %s" % (dmactl, cmd)
    
    dmactl_logfile = open(d['name'] + "_dmactl_log.txt", "w")
    print(dmactl_cmd)
    p = subprocess.Popen(dmactl_cmd, stdout=dmactl_logfile)
    p.communicate()
    dmactl_logfile.close()
    
    dmactl_logfile = open(d['name'] + "_dmactl_log.txt", "r")

    output = ""
    for line in dmactl_logfile :
        if(len(line)) :
            output += line.rstrip()
            output += "\n"

    dmactl_logfile.close()
    return output
    
def reset_qdma_device() :
    cmd = "dev list"
    output = run_dmactl_cmd(cmd)

    device_list = []
    lines = output.split("\n")
    for line in lines :
        if(len(line)):
            if (line.find("qdma") != -1):
                dev_name = line.split("\t")
                device_list.append(dev_name[0])
    
    for device in device_list:
        print("Resetting device %s" % device)
        cmd = "%s user write 0xA0 0x01 0x00 0x00 0x00" % (device)
        output = run_dma_rw_cmd(cmd)
        print(output)
        if (output.find("Failed") != -1) :
            sys.exit("Failed to reset qdma device. Terminating the test")

    
def set_qmax() :
    cmd = "dev list"
    output = run_dmactl_cmd(cmd)

    device_list = []
    lines = output.split("\n")
    for line in lines :
        if(len(line)):
            if (line.find("qdma") != -1):
                dev_name = line.split("\t")
                device_list.append(dev_name[0])
    
    for device in device_list:
        cmd = "%s qmax 0" % (device)
        output = run_dmactl_cmd(cmd)
        if (output.find("Failed") != -1) :
            sys.exit("Failed to set qmax. Terminating the test")

    for idx, cfg_en in enumerate(d['pf_qmax_cfg_en']) :
        if (d['pf_qmax_cfg_en'][idx] == 1) :
            qmax = d['pf_qmax'][idx]
            if (int(qmax) and (idx < len(device_list))) :
                cmd = "%s qmax %s" % (device_list[idx], qmax)
                output = run_dmactl_cmd(cmd)
                print(output)
                if (output.find("Failed") != -1) :
                    sys.exit("Failed to set qmax. Terminating the test")


def run_gtest(mode) :
    print_message ("Running gtest in %s mode" % mode)
    sys.stdout.flush()
    #subprocess.call("dir", shell=True)
    inf_file = "%s\\sys\\drv\\qdma.inf" % src_dir

    #print (inf_file)

    inf_bkp_file = test_dir+"\\build\\%s\\%s\\inf_bkp" % (arch, build_mode)
    # Make a copy of the original INF File
    shutil.copyfile(inf_file, inf_bkp_file)

    try:
        # Open subprocess log file
        subprocess_op_log_file = open(d['name'] + mode + "_subprocess_log.txt", "w")
        
        # Modify the Inf file based on the mode
        if (mode.lower() == "poll") :
            cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\inf_mode.ps1 '%s' 1 '%s'" % (inf_file, config_bar)
            p = subprocess.Popen(["powershell.exe", "-ExecutionPolicy", "RemoteSigned", cmd], stdout=subprocess_op_log_file)
            p.communicate()

            # Prepare the log file name based on mode
            log_file = d['name']+"_poll_mode_log"
        elif (mode.lower() == "intr") :
            cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\inf_mode.ps1 '%s' 2 '%s'" % (inf_file, config_bar)
            p = subprocess.Popen(["powershell.exe", "-ExecutionPolicy", "RemoteSigned", cmd], stdout=subprocess_op_log_file)
            p.communicate()

            # Prepare the log file name based on mode
            log_file = d['name']+"_intr_mode_log"
        elif (mode.lower() == "aggr") :
            cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\inf_mode.ps1 '%s' 3 '%s'" % (inf_file, config_bar)
            p = subprocess.Popen(["powershell.exe", "-ExecutionPolicy", "RemoteSigned", cmd], stdout=subprocess_op_log_file)
            p.communicate()

            # Prepare the log file name based on mode
            log_file = d['name']+"_aggr_mode_log"
        elif (mode.lower() == "legacy") :
            cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\inf_mode.ps1 '%s' 4 '%s'" % (inf_file, config_bar)
            p = subprocess.Popen(["powershell.exe", "-ExecutionPolicy", "RemoteSigned", cmd], stdout=subprocess_op_log_file)
            p.communicate()

            # Prepare the log file name based on mode
            log_file = d['name']+"_legacy_mode_log"

        drv_build_path = "%s\\build\\%s\\%s\\sys" % (src_dir, arch, build_mode)
        Trace_log_etl_file = test_dir+"\\build\\%s\\%s\\Tracelog_%s%%d.etl" % (arch, build_mode, log_file)
        # Enable/Start the Trace Logs
        cmd = "traceview -start Tracelog_%s -pdb \"%s\\QDMA.pdb\" -level 7 -flag 0x7FFFFFFF -rt -ft 1 -min 150 -max 200 -b 2048 -newfile 100 -f %s" % (log_file, drv_build_path, Trace_log_etl_file)
        p = subprocess.Popen(cmd, stdin=None, stdout=None, stderr=None)
        #p.communicate()

        time.sleep(3)
        
        # Remove the already installed drivers
        cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\uinstall_driver.bat %s" % (arch)
        p = subprocess.Popen(cmd, stdout=subprocess_op_log_file, shell=True)
        p.communicate()
        if (p.returncode == 0) :
            print_message("Successfully unloaded driver")
        else :
            print_message("Failed to unload driver")

        # Re-Scan Devices
        cmd = "devcon.exe rescan"
        p = subprocess.Popen(cmd, stdout=subprocess_op_log_file)
        p.communicate()
        if (p.returncode == 0) :
            print_message("Device Rescan done")
        else :
            print_message("Failed to rescan devices")

        time.sleep(3)

        # Re-build the driver
        cmd = "msbuild.exe %s /t:clean /t:build /p:Configuration=%s /p:Platform=%s /p:ExternalCompilerOptions=\"%s\"" % (src_path, build_mode, arch, cflags)
        p = subprocess.Popen(cmd, stdout=subprocess_op_log_file)
        p.communicate()

        if (p.returncode == 0) :
            print_message("Successfully build the Driver")
        else :
            print_message("Fauiled to build Driver")
            sys.exit("Terminating the test")

        # Install the certificate to root and trsusted publisher places
        cmd = "certmgr.exe -add \"%s\\build\\%s\\%s\\sys\\QDMA.cer\" -s -r localmachine root" % (src_dir, arch, build_mode)
        p = subprocess.Popen(cmd, stdout=subprocess_op_log_file)
        p.communicate()

        if (p.returncode == 0) :
            print_message("Successfully installed driver certificate 1")
        else :
            print_message("Failed to intall driver certificate 2")
            
        cmd = "certmgr.exe -add \"%s\\build\\%s\\%s\\sys\\QDMA.cer\" -s -r localmachine trustedpublisher" % (src_dir, arch, build_mode)
        p = subprocess.Popen(cmd, stdout=subprocess_op_log_file)
        p.communicate()

        if (p.returncode == 0) :
            print_message("Successfully installed driver certificate 2")
        else :
            print_message("Failed to intall driver certificate 2")

        # Install the driver using pnputil utility
        cmd = "pnputil.exe -i -a \"%s\\build\\%s\\%s\\sys\\QDMA Reference Driver\qdma.inf\"" % (src_dir, arch, build_mode)
        p = subprocess.Popen(cmd, stdout=subprocess_op_log_file, shell=True)
        p.communicate()

        if (p.returncode == 0) :
            print_message("Successfully installed driver")
        else :
            print_message("Failed to intall driver")
            sys.exit("Terminating the test")
        
        # Set the qmax
        set_qmax()

        # Run the gtest application for the requested no of iterations with requested gtest filter
        gtest_params = "--gtest_filter=%s" % d['filter']
        if (d['run_disabled']) :
            gtest_params = gtest_params + " --gtest_also_run_disabled_tests"
        date_n_time = datetime.datetime.now().strftime("%d%m%Y_%I%M")
        consolidated_log_file = test_dir+"\\build\\%s\\%s\\qdma_test_results_%s_consolidated_%s.xml" % (arch, build_mode, log_file, date_n_time)

        cmd_log_file = test_dir+"\\build\\%s\\%s\\%s_%s.txt" % (arch, build_mode, log_file, date_n_time)
        print_message("Log file at : " + cmd_log_file)
        for iter in range(d['repeat']) :
            print_message ("Running gtest in %s mode for %d time" % (mode, (iter+1)))
            sys.stdout.flush()
            iter_log_file = test_dir+"\\build\\%s\\%s\\qdma_test_results_%s_%s_%d.xml" % (arch, build_mode, log_file, date_n_time, iter)
            gtest_log_params = "--gtest_output=xml:%s" % (iter_log_file)
            cmd = "powershell \"%s\\build\\%s\\%s\\qdma_test.exe %s %s | tee -a %s\"" % (test_dir, arch, build_mode, gtest_params, gtest_log_params, cmd_log_file)
            print(cmd)
            p = subprocess.Popen(cmd, stdout=sys.stdout)
            p.communicate()

            global global_run_sts
            global_run_sts = 1;

            if (p.returncode != 0) :
                global global_exec_sts
                global_exec_sts = global_exec_sts + 1

            # Consolidate the report
            if (gen_report == True) :
                cmd = "python %s -c \"%s\" -f \"%s\"" % (parser_path, consolidated_log_file, iter_log_file)
                p = subprocess.Popen(cmd, stdout=sys.stdout)
                p.communicate()


        if (gen_report == True) :
            template_file = "%s\\..\\ts02_2000_0142_QDMA.xlsx" % (test_dir)
            cmd = "python %s -f \"%s\" -t \"%s\"" % (parser_path, consolidated_log_file, template_file)
            p = subprocess.Popen(cmd, stdout=sys.stdout)
            p.communicate()

        # Disable/Stop the Trace Logs
        cmd = "traceview -stop Tracelog_%s" % (log_file)
        p = subprocess.Popen(cmd, stdin=None, stdout=None, stderr=None)
        #p.communicate()

        subprocess_op_log_file.close()

        time.sleep(3)

        # # Convert the etl log files to text files --  For time being this is not done...user can done manually if needed
        # Trace_log_txt_file = test_dir+"\\build\\%s\\%s\\Tracelog_%s.txt" % (arch, build_mode, log_file)
        # cmd = "traceview -process -o %s %s" % (Trace_log_txt_file, Trace_log_etl_file)
        # p = subprocess.Popen(cmd, stdin=None, stdout=None, stderr=None)
        # #p.communicate()
        #
        # time.sleep(10)
        reset_qdma_device();
    finally:
        # Copy back the original inf file
        shutil.copyfile(inf_bkp_file, inf_file)


def zip_all_log_files(dir_name, zip_fname) :
    zhandle = zipfile.ZipFile(dir_name+"\\"+zip_fname, 'w', zipfile.ZIP_DEFLATED)

    for root, dirs, files in os.walk(dir_name):
        for file in files:
            fname, fext = os.path.splitext(file)
            if (fext == '.txt' or fext == '.sum' or fext == '.etl') :
                # print (file)
                zhandle.write(os.path.join(root, file), file)

    zhandle.close()

if __name__=="__main__":
    try:
        opts, args = getopt.getopt(sys.argv[1:], "c:s:t:a:m:b:f:h", ['config-dir=', 'src-dir=', 'test-dir=', 'arch=', 'build-mode=', 'cflags', 'help'])
    except getopt.GetoptError:
        usage()
        sys.exit(1)

    # Retrieve the CLI arguments
    for opt, arg in opts:
        if opt in ('-h', '--help'):
            usage()
            sys.exit(0)
        elif opt in ('-c', '--config-dir'):
            config_dir = arg
        elif opt in ('-s', '--src-dir'):
            src_dir = arg
            src_path = src_dir + "\\QDMA.sln"
        elif opt in ('-t', '--test-dir'):
            test_dir = arg
            test_path = test_dir + "\\qdma_test.sln"
        elif opt in ('-a', '--arch'):
            arch = arg
        elif opt in ('-m', '--build-mode'):
            build_mode = arg
        elif opt in ('-f', '--cflags'):
            cflags = arg
        elif opt in ('-b', '--bar-config-index'):
            config_bar = arg
        else:
            usage()
            sys.exit(1)

    if (config_dir == "") :
        print ("-c/--config-dir argument is must to proceed\n")
        usage()
        sys.exit(1)

    # PATH VALIDATION
    if (not os.path.exists(config_dir)) :
        print ("Config directory doesn't exists, please provide valid path")
        sys.exit(1)
    if (not os.path.exists(src_dir)) :
        print ("Source directory doesn't exists, please provide valid path")
        sys.exit(1)
    if (not os.path.exists(test_dir)) :
        print ("Test directory doesn't exists, please provide valid path")
        sys.exit(1)

    if (arch != "x64" and arch != "x86") :
        print ("Only x64 and x86 are supported architectures. please provide proper option")
        sys.exit(1)

    if (build_mode != "Debug" and build_mode != "Release") :
        print ("Only Debug and Release modes are valid. please provide proper option")
        sys.exit(1)

    cfg_file_cnt = len([name for name in os.listdir(config_dir) if os.path.isfile(os.path.join(config_dir, name))])
    if (cfg_file_cnt == 0) :
        print ("No Configuration files present in the given config-dir")
        sys.exit(1)

    #print ("--------------------------------------------------------")
    print ("\nRunning gtest_top_win.py with the below configuration\n")
    t = PrettyTable(['Configuration', ' Value'])
    t.add_row(['configuration directory', config_dir])
    t.add_row(['build-mode', build_mode])
    t.add_row(['src-dir', src_dir])
    t.add_row(['test-dir', test_dir])
    t.add_row(['cflags', cflags])
    t.add_row(['config bar index', config_bar])
    t.align = 'l'
    print(t)
    
    # Parse the config files and run the script
    for name in os.listdir(config_dir) :
        parse_cfg_file(config_dir, name)
        is_valid_config = False;
        # Check the validity of config
        for i in d['valid_drv'] :
            if (i.lower() == "windows") :
                is_valid_config = True;

        if (not is_valid_config) :
            print ("Config File %s is not valid for windows" % name)
            continue

        if (not d['run_gtest']) :
            print ("run_gtest is disabled in config file")
            continue

        # Run the Regressions
        if ((d['mask'] & 0x02) or (d['mask'] & 0x01)) :
            run_gtest("poll")
        if (d['mask'] & 0x04) :
            run_gtest("intr")
        if (d['mask'] & 0x08) :
            run_gtest("aggr")
        if (d['mask'] & 0x20) :
            run_gtest("legacy")

        # Uninstall the drivers
        t_log_file = open(os.devnull, 'w')
        cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\uinstall_driver.bat %s" % (arch)
        p = subprocess.Popen(cmd, stdout=t_log_file, shell=True)
        p.communicate()
        
        # Re-Scan Devices
        cmd = "devcon.exe rescan"
        p = subprocess.Popen(cmd, stdout=t_log_file)
        p.communicate()

        t_log_file.close()
        time.sleep(3)

        # Zip all the logs
        logs_dir = test_dir+"\\build\\%s\\%s" % (arch, build_mode)
        zip_fname = "trace_logs_gtest_windows.zip"
        zip_all_log_files(logs_dir, zip_fname)
        print_message("Log file zip : " + logs_dir + zip_fname)

        if (global_run_sts != 1) :
            print ("--------------------------------------------------------------------------")
            print ("gtest didn't run with config %s" % d['name'])
            print ("--------------------------------------------------------------------------")
            sys.stdout.flush()
            sys.exit(1)

        if (global_exec_sts != 0) :
            print ("--------------------------------------------------------------------------")
            print ("Test case Failures detected in config %s" % d['name'])
            print ("--------------------------------------------------------------------------")
            sys.stdout.flush()
            sys.exit(1)
        else :
            print ("--------------------------------------------------------------------------")
            print ("completed %s config sucessfully" % d['name'])
            print ("--------------------------------------------------------------------------")
            sys.stdout.flush()
