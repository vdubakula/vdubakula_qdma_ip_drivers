import sys
import os
import getopt
import subprocess
import shutil
import datetime
import time

'''
Usage : python gtest_top.py -c <config_dir> -a <ARCH> -m <Debug|Release> -s [<src dir>] -t [<template file>] -c <config file> -l linkMode -h
'''

#Global Variables/Parameters
arch = "x64"
build_mode = "Release"
src_dir = os.path.realpath(__file__)+"\\..\\..\\..\\..\\..\\sw_host\\mdma\\windows"
src_path = src_dir + "\\QDMA.sln"
config_bar = "0"
config_file_name = "HEAD\\proj\\sw_test\\windows\\scripts\\perf_scripts\\config\\st.txt"
perf_app_vs = "HEAD\\proj\\sw_host\\windows\\apps\\diskspd\\diskspd_vs\\diskspd.sln"
perf_app = "HEAD\\proj\\sw_host\\windows\\apps\\diskspd\\diskspd_vs\\x64\\Release\\diskspd.exe"
perf_script = "HEAD\\proj\\sw_test\\windows\\scripts\\perf_scripts\\perf_run.py"
template_file_index = 0
template_file_name = [
'HEAD\\proj\\sw_test\\windows\\scripts\\perf_scripts\\templates\\perf_result_template_mm_unidir.xlsx',
'HEAD\\proj\\sw_test\\windows\\scripts\\perf_scripts\\templates\\perf_result_template_mm_bidir.xlsx',
'HEAD\\proj\\sw_test\\windows\\scripts\\perf_scripts\\templates\\perf_result_template_st_unidir.xlsx',
'HEAD\\proj\\sw_test\\windows\\scripts\\perf_scripts\\templates\\perf_result_template_st_bidir.xlsx'
]
link_mode = "3x16"


def usage():
    print ("usage : python %s [OPTIONS]\n" % sys.argv[0])
    print ("Windows performance top script\n\n")
    print ("arguments")
    print ("\t -a, --arch\t\t Target system Architecture (default : x64)")
    print ("\t -m, --build-mode\t Project build mode (default : Debug)")
    print ("\t -s, --src-dir\t\t QDMA driver source directory")
    print ("\t -b, --bar-config-index \t\t Config BAR Index for inf configuration")
    print ("\t -t, --template-file \t\t Excel file template")
    print ("\t -c, --config-file \t\t QDMA configuration for perf application")
    print ("\t -l, --link-mode \t\t QDMA PCIe Link Mode configuration")
    print ("\n")
    sys.stdout.flush()



def build_and_load(mode, link_mode) :
    print ("Running gtest in %s mode" % mode)
    sys.stdout.flush()
    #subprocess.call("dir", shell=True)
    inf_file = "%s\\sys\\drv\\qdma.inf" % src_dir

    #print (inf_file)

    inf_bkp_file = src_dir+"\\inf_bkp"
    # Make a copy of the original INF File
    shutil.copyfile(inf_file, inf_bkp_file)

    try:
        # Modify the Inf file based on the mode
        if (mode.lower() == "poll") :
            cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\inf_mode.ps1 '%s' 1 '%s'" % (inf_file, config_bar)
            p = subprocess.Popen(["powershell.exe", "-ExecutionPolicy", "RemoteSigned", cmd], stdout=sys.stdout)
            p.communicate()
        elif (mode.lower() == "intr") :
            cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\inf_mode.ps1 '%s' 2 '%s'" % (inf_file, config_bar)
            p = subprocess.Popen(["powershell.exe", "-ExecutionPolicy", "RemoteSigned", cmd], stdout=sys.stdout)
            p.communicate()
        elif (mode.lower() == "aggr") :
            cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\inf_mode.ps1 '%s' 3 '%s'" % (inf_file, config_bar)
            p = subprocess.Popen(["powershell.exe", "-ExecutionPolicy", "RemoteSigned", cmd], stdout=sys.stdout)
            p.communicate()
        elif (mode.lower() == "legacy") :
            cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\inf_mode.ps1 '%s' 4 '%s'" % (inf_file, config_bar)
            p = subprocess.Popen(["powershell.exe", "-ExecutionPolicy", "RemoteSigned", cmd], stdout=sys.stdout)
            p.communicate()

        drv_build_path = "%s\\build\\%s\\%s\\sys" % (src_dir, arch, build_mode)
        time.sleep(3)

        # Remove the already installed drivers
        cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\uinstall_driver.bat %s" % (arch)
        p = subprocess.Popen(cmd, stdout=sys.stdout)
        p.communicate()

        # Re-Scan Devices
        cmd = "devcon.exe rescan"
        p = subprocess.Popen(cmd, stdout=sys.stdout)
        p.communicate()

        time.sleep(3)

        # Re-build the driver
        cmd = "msbuild.exe %s /t:clean /t:build /p:Configuration=%s /p:Platform=%s" % (src_path, build_mode, arch)
        p = subprocess.Popen(cmd, stdout=sys.stdout)
        p.communicate()

        # build perf application
        cmd = "MSBuild.exe %s /t:clean /t:build /p:Configuration=Release /p:Platform=x64" % (perf_app_vs)
        p = subprocess.Popen(cmd, stdout=sys.stdout)
        p.communicate()

        # Install the certificate to root and trsusted publisher places
        cmd = "certmgr.exe -add \"%s\\build\\%s\\%s\\sys\\QDMA.cer\" -s -r localmachine root" % (src_dir, arch, build_mode)
        p = subprocess.Popen(cmd, stdout=sys.stdout)
        p.communicate()

        cmd = "certmgr.exe -add \"%s\\build\\%s\\%s\\sys\\QDMA.cer\" -s -r localmachine trustedpublisher" % (src_dir, arch, build_mode)
        p = subprocess.Popen(cmd, stdout=sys.stdout)
        p.communicate()

        # Install the driver using pnputil utility
        cmd = "pnputil.exe -i -a \"%s\\build\\%s\\%s\\sys\\QDMA Reference Driver\qdma.inf\"" % (src_dir, arch, build_mode)
        p = subprocess.Popen(cmd, stdout=sys.stdout)
        p.communicate()

        # Run perf exe
        cmd = "python %s -t %s -c %s -e %s -l %s" % (perf_script, template_file_name[template_file_index], config_file_name, perf_app, link_mode)
        p = subprocess.Popen(cmd, stdout=sys.stdout)
        p.communicate()
    finally:
        # Copy back the original inf file
        shutil.copyfile(inf_bkp_file, inf_file)

if __name__=="__main__":
    try:
        opts, args = getopt.getopt(sys.argv[1:], "s:a:m:b:t:c:l:h", ['src-dir=', 'arch=', 'build-mode=', 'bar-config-index', 'template-file-index', 'link-mode=', 'help'])
    except getopt.GetoptError:
        usage()
        sys.exit(1)

    # Retrieve the CLI arguments
    for opt, arg in opts:
        if opt in ('-h', '--help'):
            usage()
            sys.exit(0)
        elif opt in ('-s', '--src-dir'):
            src_dir = arg
            src_path = src_dir + "\\QDMA.sln"
        elif opt in ('-a', '--arch'):
            arch = arg
        elif opt in ('-m', '--build-mode'):
            build_mode = arg
        elif opt in ('-b', '--bar-config-index'):
            config_bar = arg
        elif opt in ('-t', '--template-file-index'):
            template_file_index = int(arg)
        elif opt in ('-c', '--config-file'):
            config_file_name = arg
        elif opt in ('-l', '--link-mode'):
            link_mode = arg
        else:
            usage()
            sys.exit(1)

    # PATH VALIDATION
    if (not os.path.exists(src_dir)) :
        print ("Source directory doesn't exists, please provide valid path")
        sys.exit(1)

    if (arch != "x64" and arch != "x86") :
        print ("Only x64 and x86 are supported architectures. please provide proper option")
        sys.exit(1)

    if (build_mode != "Debug" and build_mode != "Release") :
        print ("Only Debug and Release modes are valid. please provide proper option")
        sys.exit(1)

    print ("--------------------------------------------------------")
    print ("Running qdma_top_perf.py with the below configuration : ")
    print ("arch\t\t: ", arch)
    print ("build-mode\t: ", build_mode)
    print ("src-dir\t\t: ", src_dir)
    print ("Template File \t: ", template_file_name[template_file_index])
    print ("Config File \t: ", config_file_name)
    print ("--------------------------------------------------------")

    build_and_load("aggr", link_mode)

    # Uninstall the drivers
    cmd = "HEAD\\proj\\util\\windows\\jenkins\\scripts\\uinstall_driver.bat %s" % (arch)
    p = subprocess.Popen(cmd, stdout=sys.stdout)
    p.communicate()

    # Re-Scan Devices
    cmd = "devcon.exe rescan"
    p = subprocess.Popen(cmd, stdout=sys.stdout)
    p.communicate()

    time.sleep(3)
    print ("Driver build and load done")
    print ("--------------------------------------------------------")
