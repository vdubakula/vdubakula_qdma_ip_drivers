#!/usr/bin/python
copyright_header_dec ="""
This script attempts to add a header to each file in the given directory/subdirectories
The header will be put the line after a Shebang (#!) if present.
Only files matching "*.c" and "*.h" are currently processed.

usage: python copyright_header.py -d <target forder/file> -c <text file containing copyright header> [-a/p] [-f] [-x] [--xd <list of exclude directories w.r.t base folder>] [--xf <list of exclude files>]
   copyright_header.txt is supposed to be along with copyright_header.py

"""
import os
import re
import sys
from argparse import ArgumentParser

usage = "copyright_header.py [-a/p] [-x] [-f] -d input_directory/input_file -c copyright_header.txt [--xd \"apps\" \"debug\" \"libs\" \"freertos\"] [--xf \"\"]"
parser = ArgumentParser(prog='copyright_header.py', usage=usage, description=copyright_header_dec, add_help=True)
parser.add_argument("-c", "--copyright_file",
                    action="store", type=str, dest="cprt_file",
                    help = "file containing copyright header. Should be in same path as copyright_header.py")
parser.add_argument("-d", "--in_dir",
                    action="store", type=str, dest="target_dir",
                    help = "Directory or file on which the script needs to be executed")
parser.add_argument("--xd", action="store", nargs='*',
                            type=str,
                            default=[],dest="exclude_dir_list",
                            help = "list of folders that need to be excluded. These will be space separated strings and paths are to be w.r.t base folder")
parser.add_argument("--xf", action="store", nargs='*',
                            type=str,
                            default=[],dest="exclude_file_list",
                            help = "list of files that need to be excluded. These will be space separated strings and paths are to be w.r.t base folder")
parser.add_argument("-a", action="store_true", dest="copyright_append", default=False, help = "Append the copyright header instead of replacing")
parser.add_argument("-p", action="store_true", dest="copyright_prepend", default=False, help = "prepend the copyright header instead of replacing")
parser.add_argument("-f", "--format", action="store_true", dest="copyright_format", default=False, help = "Format the copyright header")
parser.add_argument("-x", action="store_true", dest="skip_type", default=False, help = "skip file type checking for copyright header processing")
parser.print_usage()
args = parser.parse_args()


def writeheader(filename, header):
    """
    write a header to filename,
    skip files where first line after optional shebang matches the skip regex
    filename should be the name of the file to write to
    header should be a list of strings
    """
    try:
        f = open(filename,"r")
        inpt =f.readlines()
        f.close()
    except IOError as err:
        print("something went wrong trying to read input file %s: %s\n" % (filename,err))
        return
    output = []
    infile_data = ""
    in_file_lines = len(inpt)
    for i in range(in_file_lines):
        infile_data+= inpt[i]

    copyright_str = r"/\*[\s\S]*Copyright[\s\S]+?\*/\s*"
    copyrightregex = re.compile(copyright_str, re.MULTILINE)
    crh_matches = re.findall(copyrightregex, infile_data)
    if (len(crh_matches) != 0):
        rest_of_file = re.split(copyrightregex, infile_data)
        append_copyright = args.copyright_append
        prepend_copyright = args.copyright_prepend
        if (prepend_copyright == True):
            output.extend(header)
            output.extend(infile_data)
        elif (append_copyright == True):
            for crh_match in crh_matches:
                output.extend(crh_match)
            output.extend(header)
            for rest_entry in rest_of_file:
                output.extend(rest_entry)
        else:
            modified_data = re.sub(copyrightregex, "", infile_data)
            output.extend(header)
            output.extend(modified_data)
    else:
        output.extend(header)
        output.extend(infile_data)

    modified_data = ""
    if (args.copyright_format):
        infile_data = ""
        for i in range(len(output)):
            infile_data += output[i]
        format_str = r"(?P<cpr_hdr>/\*[\s\S]*Copyright[\s\S]+?\*)/\s+/\*"
        regex_format = re.compile(format_str, re.MULTILINE)
        cpr_hdr_match = regex_format.match(infile_data)
        if not (cpr_hdr_match == None):
            modified_data = re.sub(regex_format, cpr_hdr_match.group('cpr_hdr'), infile_data)
        else:
            for i in range(len(output)):
                modified_data += output[i]
    else:
        for i in range(len(output)):
            modified_data += output[i]
    try:
        f = open(filename,'w')
        f.write(modified_data)
        f.close()
        print("added header to %s\n" %filename)
    except IOError as err:
        print("something went wrong trying to add header to %s: %s\n" % (filename,err))

def main(arguments=sys.argv):
    """
    main function: parses arguments and calls addheader
    """
    ##argument parsing
    args = parser.parse_args()
    process_dir = os.path.abspath(args.target_dir)
    exec_dir = os.getcwd()

    fileregex = r"[\w\d]+\.[ch]$"
    #compile regex
    fileregex = re.compile(fileregex)
    #read in the headerfile just once
    headerfilename = os.path.join(exec_dir, args.cprt_file)
    headerfile = open(headerfilename)
    header = headerfile.readlines()
    headerfile.close()
    ex_dir_list = args.exclude_dir_list
    ex_file_list = args.exclude_file_list
    skip_type_check = args.skip_type

    if os.path.isdir(process_dir):
        for subdir, dirs, files in os.walk(process_dir):
            for file in files:
                proc_file = True
                for dirname in ex_dir_list:
                    dirbasename = os.path.join(process_dir, dirname)
                    if str(subdir).startswith(dirbasename):
                        proc_file = False
                        break
                if proc_file == False:
                    continue
                fullfn = os.path.join(subdir, file)
                if file in ex_file_list:
                    continue
                if (fileregex.match(file) or (skip_type_check == True)): #if file matches file regex, write the header
                    writeheader(fullfn, header)
    else:
        writeheader(process_dir, header)

#call the main method
main()