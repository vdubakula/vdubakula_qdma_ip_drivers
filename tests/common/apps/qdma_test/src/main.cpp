/*
 * main.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: alexande
 */

#include <gtest/gtest.h>

#include "example_design_ctrl.h"
#include "qdma_device.h"
#include "test_env.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>

#ifdef _WIN32
#include <win_helper.h>
#else
#include <err.h>
#endif



#ifdef DPDK
#define CMD_LINE_OPT_CONFIG	"config"
#define CMD_LINE_OPT_BIND_DRV	"bind_driver"
#define BIND_DRV_VFIO_PCI	"vfio-pci"
#define BIND_DRV_IGB_UIO	"igb_uio"
char bind_drv[30];
#endif

// global object for storing test environment which are common across all tests:
//  - handle to qdma driver ctrl
//  - number of qdma devices
//  - seed for random number generator
//  - bram size of bitstream
// To use this just reference as:
//      extern qdma_test_env env;
// in the test cpp file of your choice.
test_env env;

static struct option const long_opts[] = {
    {"cfg_name", optional_argument, NULL, 'f'},
    {"gtest_repeat", optional_argument, NULL, 0},
    {"gtest_filter", optional_argument, NULL, 0},
    {"gtest_output", optional_argument, NULL, 0},
	{"gtest_list_tests", optional_argument, NULL, 0},
#ifdef DPDK
    {"core mask", required_argument, NULL, 'c'},
    {"number of memory channels", required_argument, NULL, 'n'},
    {"filename", 1, 0, 0},
    {CMD_LINE_OPT_CONFIG, 1, 0, 0},
    {CMD_LINE_OPT_BIND_DRV, 1, 0, 0},
#endif
    {0, 0, 0, 0}
};

static void usage(const char *name)
{
#ifdef DPDK
    printf("%s [EAL options] --"
        " --config (totalqueues)",
        name);
#else
    int i = 0;
    fprintf(stdout, "%s\n\n", name);
    fprintf(stdout, "usage: %s [OPTIONS]\n\n", name);

    fprintf(stdout, "  -%c (--%s) config file that has configration for system setup\n",
        long_opts[i].val, long_opts[i].name);
    i++;
#endif
}

#ifdef DPDK
int config_max_queues;

static int
parse_dpdk_config(const char *q_arg)
{
	char s[256];
	const char *p, *p0 = q_arg;
	char *end;
	enum fieldnames {
		FLD_NUM_QUEUES = 0,
		_NUM_FLD
	};
	unsigned long int_fld[_NUM_FLD];
	char *str_fld[_NUM_FLD];
	int i;
	unsigned size;

	while ((p = strchr(p0,'(')) != NULL) {
		++p;
		if((p0 = strchr(p,')')) == NULL)
			return -1;

		size = p0 - p;
		if(size >= sizeof(s))
			return -1;

		snprintf(s, sizeof(s), "%.*s", size, p);
		if (rte_strsplit(s, sizeof(s), str_fld, _NUM_FLD, ',') != _NUM_FLD)
			return -1;
		for (i = 0; i < _NUM_FLD; i++){
			errno = 0;
			int_fld[i] = strtoul(str_fld[i], &end, 0);
			if (errno != 0 || end == str_fld[i])
				return -1;
		}

		config_max_queues = (unsigned int)int_fld[FLD_NUM_QUEUES];
		if(config_max_queues > MAX_NUM_QUEUES)
		{
			printf("Invalid number of Queues\n");
			return -1;
		}
	}
	return 0;
}

int parse_cmdline(int argc, char **argv)
{
	int cmd_opt, ret;
	int option_index;
	const char *str5 = "Invalid config";
	char *prgname = argv[0];
	char **argvopt;

	/* Default driver is igb_uio */
	strncpy(bind_drv, BIND_DRV_IGB_UIO, strlen(BIND_DRV_IGB_UIO));
	argvopt = argv;
	while ((cmd_opt = getopt_long(argc, argvopt, "c:n:", long_opts, &option_index)) != EOF) {
		switch (cmd_opt)
		{
			case 'c':
				/* eal option */
				break;
			case 'n':
				/* eal option */
				break;
			case 'b':
				/* eal option */
				break;
			case 0:
				if (!strncmp(long_opts[option_index].name,
							CMD_LINE_OPT_CONFIG,
							sizeof(CMD_LINE_OPT_CONFIG))) {

					ret = parse_dpdk_config(optarg);
					if (ret) {
						printf("%s\n", str5);
						usage(prgname);
						return -1;
					}
				}

				if (!strncmp(long_opts[option_index].name,
							CMD_LINE_OPT_BIND_DRV,
							sizeof(CMD_LINE_OPT_BIND_DRV))) {

					strncpy(bind_drv, optarg, strlen(optarg));
				}

				break;
			/*default:
				printf("please pass valid parameters as follows:\n");
				return -1;*/
		}
	}

	return 0;
}
#endif

static unsigned int num_trailing_blanks(char *word)
{
    unsigned int i = 0;
    size_t slen = strlen(word);

    if (!slen) return 0;
    while (isspace(word[slen - i - 1])) {
        i++;
    }

    return i;
}

static char * strip_blanks(char *word, size_t *blanks)
{
    char *p = word;
    unsigned int i = 0;

    while (isblank(p[0])) {
        p++;
        i++;
    }
    if (blanks)
        *blanks = i;

    return p;
}

static char * strip_comments(char *word)
{
    size_t numblanks;
    char *p = strip_blanks(word, &numblanks);

    if (p[0] == '#')
        return NULL;
    else
        p = strtok(word, "#");

    return p;
}

static int arg_read_int(char *s, unsigned int *v)
{
    char *p = NULL;


    *v = strtoul(s, &p, 0);
    if (*p && (*p != '\n') && !isblank(*p)) {
    printf("Error: something not right%s %s %s",s, p, isblank(*p)? "true": "false");
        return -EINVAL;
    }
    return 0;
}

static int arg_read_int_array(char *s, unsigned int *v, unsigned int max_arr_size)
{
    size_t slen = strlen(s);
    unsigned int trail_blanks = num_trailing_blanks(s);
    char *str = (char *)malloc(slen - trail_blanks + 1);
    char *elem;
    int cnt = 0;
    int ret;

    memset(str, '\0', slen + 1);
    strncpy(str, s + 1, slen - trail_blanks - 2);
    str[slen] = '\0';

    elem = strtok(str, " ,");/* space or comma separated */
    while (elem != NULL) {
        ret = arg_read_int(elem, &v[cnt]);
        if (ret < 0) {
            printf("ERROR: Invalid array element %sin %s\n", elem, s);
            exit(0);
        }
        cnt++;
        elem = strtok(NULL, " ,");
        if (cnt > (int)max_arr_size) { /* to avoid out of bounds */
            printf("ERROR: More than expected number of elements in %s - expected = %u\n",
                   str, max_arr_size);
            exit(0);
        }
    }
    free(str);

    return cnt;
}

static int arg_read_hex(char *s, unsigned int *v)
{
    char *p = NULL;


    *v = strtoul(s, &p, 16);
    if (*p && (*p != '\n') && !isblank(*p)) {
    printf("Error: something not right%s %s %s",s, p, isblank(*p)? "true": "false");
        return -EINVAL;
    }
    return 0;
}

static int arg_read_hex_array(char *s, unsigned int *v, unsigned int max_arr_size)
{
    size_t slen = strlen(s);
    unsigned int trail_blanks = num_trailing_blanks(s);
    char *str = (char *)malloc(slen - trail_blanks + 1);
    char *elem;
    int cnt = 0;
    int ret;

    memset(str, '\0', slen + 1);
    strncpy(str, s + 1, slen - trail_blanks - 2);
    str[slen] = '\0';

    elem = strtok(str, " ,");/* space or comma separated */
    while (elem != NULL) {
        ret = arg_read_hex(elem, &v[cnt]);
        if (ret < 0) {
            printf("ERROR: Invalid array element %sin %s\n", elem, s);
            exit(0);
        }
        cnt++;
        elem = strtok(NULL, " ,");
        if (cnt > (int)max_arr_size) { /* to avoid out of bounds */
            printf("ERROR: More than expected number of elements in %s - expected = %u\n",
                   str, max_arr_size);
            exit(0);
        }
    }
    free(str);

    return cnt;
}

static int get_array_len(char *s)
{
    int i, len = 0;

    if (strlen(s) < 2)
        return -EINVAL;
    if ((s[0] != '(') && (s[strlen(s) - 1] != ')'))
        return -EINVAL;
    if ((s[0] == '(') && (s[1] == ')'))
        return 0;
    for (i = 0; i < (int)strlen(s); i++) {
        if ((s[i] == ' ') || (s[i] == ',')) /* space or comma separated */
                len++;
        if (s[i] == ')')
            break;
    }

    return (len + 1);
}

static void parse_config_file(const char *cfg_fname)
{
    char *realbuf;
    size_t linelen = 0;
    size_t numblanks;
    char *config, *value;

    std::ifstream infile;
    auto filestate = infile.exceptions();
    infile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        infile.open(cfg_fname, std::ios_base::in);
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "Exception happened: " << e.what() << std::endl;
        std::cout << "libc error #" << ": " << ::strerror(errno) << std::endl;
        std::cout << "handled" << std::endl;
        exit(EXIT_FAILURE);
    }

    infile.exceptions(filestate);

    for (std::string line; std::getline(infile, line); ) {
        char *linebuf = new char[line.length() + 1];
        std::unique_ptr<char> smart_ptr(linebuf);

        strcpy(linebuf, line.c_str());
        linelen = line.length();

        linebuf = strip_comments(linebuf);
        if (!linebuf)
            continue;

        realbuf = strip_blanks(linebuf, &numblanks);
        linelen -= numblanks;
        if (0 == linelen) {
            continue;
        }
        if (strlen(realbuf) == 0) {
            continue;
        }

        config = strtok(realbuf, "=");
        value = strtok(NULL, "=");
        if (!strncmp(config, "master_pf", 8)) {
            if (arg_read_int(value, &env.sys_cfg.master_pf)) {
                printf("Error: Invalid master_pf:%s\n", value);
                exit(1);
            }
        } else if (!strncmp(config, "qmaxvfs", 7)) {
                if (arg_read_int(value, &env.sys_cfg.qmaxvfs)) {
                    printf("Error: Invalid qmaxvfs:%s\n", value);
                    exit(1);
                }
        } else if (!strncmp(config, "pf_qmax_cfg_en", 14)) {
            int arr_len = get_array_len(value);
            int ret;

            if (arr_len < 0) {
                printf("ERROR: Invalid pf_qmax_cfg_en - %s\n", value);
                exit(1);
            }
            env.sys_cfg.num_pf = arr_len;
            if (arr_len) {
                env.sys_cfg.pf_qmax_cfg_en = (unsigned int *)calloc(arr_len, sizeof(unsigned int));
                ret = arg_read_int_array(value, env.sys_cfg.pf_qmax_cfg_en, arr_len);
                if (ret <= 0) {
                    printf("Error: Invalid pf_qmax_cfg_en:%s\n", value);
                    exit(1);
                }
            }
        } else if (!strncmp(config, "pf_qmax", 7)) {
            int arr_len = get_array_len(value);
            int ret;

            if ((arr_len < 0) || (arr_len != (int)env.sys_cfg.num_pf)) {
                printf("ERROR: Invalid number of entries in pf_qmax - %s\n", value);
                exit(1);
            }
            if (arr_len) {
                env.sys_cfg.pf_qmax_lst = (unsigned int *)calloc(arr_len, sizeof(unsigned int));
                ret = arg_read_int_array(value, env.sys_cfg.pf_qmax_lst, arr_len);
                if (ret <= 0) {
                    printf("Error: Invalid pf_qmax_lst:%s\n", value);
                    exit(1);
                }
            }
        } else if (!strncmp(config, "pf_nvf", 6)) {
            int arr_len = get_array_len(value);
            int ret, i;

            if ((arr_len < 0) || (arr_len != (int)env.sys_cfg.num_pf)) {
                printf("ERROR: Invalid number of entries in pf_nvf_lst - %s\n", value);
                exit(1);
            }
            if (arr_len) {
                env.sys_cfg.pf_nvf_lst = (unsigned int *)calloc(arr_len, sizeof(unsigned int));
                ret = arg_read_int_array(value, env.sys_cfg.pf_nvf_lst, arr_len);
                if (ret <= 0) {
                    printf("Error: Invalid pf_nvf_lst:%s\n", value);
                    exit(1);
                }
            }
            env.sys_cfg.vf_pf_qmax_lst = (unsigned int **)calloc(arr_len, sizeof(unsigned int *));
            for (i = 0; i < arr_len; i++)
                env.sys_cfg.vf_pf_qmax_lst[i] = (unsigned int *)calloc(env.sys_cfg.pf_nvf_lst[i], sizeof(unsigned int));
        } else if (!strncmp(config, "vf_pf", 5)) {
            size_t slen = strlen(config);
            char *str;
            int arr_len;
            int ret;
            int pf = 0;

            if (strncmp(config+slen-5, "_qmax", 5)) {
                printf("ERROR: unknown config param %s\n", config);
                exit(1);
            }
            if (!env.sys_cfg.pf_nvf_lst) {
                printf("ERROR: set pf_nvf_lst before vf_pf*_qmax\n");
                exit(1);
            }
            str = strtok(config+5, "_");
            if (str != NULL) {
                int r = arg_read_int(str, (unsigned int *)&pf);

                if (r < 0) {
                    printf("ERROR: Invalid PF number %s in %s\n", str, config);
                    exit(1);
                }
                if (pf > (int)env.sys_cfg.num_pf) {
                    printf("%d PF number does not exist. Invalid %s config\n", pf, config);
                    exit(1);
                }

            }
            arr_len = get_array_len(value);
            if ((arr_len < 0) || (arr_len > (int)env.sys_cfg.pf_nvf_lst[pf])) {
                printf("ERROR: Invalid number of entries in vf_pf%d_qmax - %s\n", pf, value);
                exit(1);
            }
            if (arr_len) {
                ret = arg_read_int_array(value, env.sys_cfg.vf_pf_qmax_lst[pf], arr_len);
                if (ret <= 0) {
                    printf("Error: Invalid vf_pf%d_qmax:%s\n", pf, value);
                    exit(1);
                }
            }
        } else if (!strncmp(config, "pci_bus", 7)) {
            int arr_len = get_array_len(value);
            int ret;

            if (arr_len < 0) {
                printf("ERROR: Invalid pci_bus - %s\n", value);
                exit(1);
            }
            env.sys_cfg.num_cards = arr_len;
            if (arr_len) {
                env.sys_cfg.pci_bus = (unsigned int *)calloc(arr_len, sizeof(unsigned int));
                ret = arg_read_hex_array(value, env.sys_cfg.pci_bus, arr_len);
                if (ret <= 0) {
                    printf("Error: Invalid pci_bus:%s\n", value);
                    exit(1);
                }
            }
        } else if (!strncmp(config, "pci_dev", 7)) {
            int arr_len = get_array_len(value);
            int ret;

            if (arr_len < 0) {
                printf("ERROR: Invalid pci_dev - %s\n", value);
                exit(1);
            }
            if (arr_len) {
                env.sys_cfg.pci_dev = (unsigned int *)calloc(arr_len, sizeof(unsigned int));
                ret = arg_read_int_array(value, env.sys_cfg.pci_dev, arr_len);
                if (ret <= 0) {
                    printf("Error: Invalid pci_dev:%s\n", value);
                    exit(1);
                }
            }
        } else if(!strncmp(config, "multiple_apps", 7)) {
			if (arg_read_int(value, &env.sys_cfg.multiple_apps)) {
                printf("Error: Invalid master_pf:%s\n", value);
                exit(1);
            }
		}
        else {
            printf("WARNING: Unknown parameter '%s'\n", config);
        }
    }

    infile.close();
}

#define DISPLAY_CONFIG_INFO 0
#if DISPLAY_CONFIG_INFO
static void dump_setp_config(void)
{
    int i, j;

    printf("master_pf = %u\n", env.sys_cfg.master_pf);
    printf("num_pf = %u\n", env.sys_cfg.num_pf);
    printf("pf_qmax_cfg_en = (");
    for (i = 0; i < (int)env.sys_cfg.num_pf; i++)
        printf(" %u", env.sys_cfg.pf_qmax_cfg_en[i]);
    printf(")\n");
    printf("pf_qmax = (");
    for (i = 0; i < (int)env.sys_cfg.num_pf; i++)
        printf(" %u", env.sys_cfg.pf_qmax_lst[i]);
    printf(")\n");
    printf("pf_nvf = (");
    for (i = 0; i < (int)env.sys_cfg.num_pf; i++)
        printf(" %u", env.sys_cfg.pf_nvf_lst[i]);
    printf(")\n");
    printf("pf_nvf = (");
    for (i = 0; i < (int)env.sys_cfg.num_pf; i++)
        printf(" %u", env.sys_cfg.pf_nvf_lst[i]);
    printf(")\n");
    printf("qdmaxvfs = %u\n", env.sys_cfg.qmaxvfs);
    for (i = 0; i < (int)env.sys_cfg.num_pf; i++) {
        printf("vf_pf%d_qmax = (", i);
        for (j = 0; j < (int)env.sys_cfg.pf_nvf_lst[i]; j++) {
            printf(" %u", env.sys_cfg.vf_pf_qmax_lst[i][j]);
        }
        printf(")\n");
    }
}
#endif

#ifndef _WIN32
static void validate_config(void)
{
#ifndef TEST_VF_ALONE
    unsigned int num_vf;
    int i, j;
    char filename[100] = {'\0'};
    char totalvf_str[10] = {'\0'};

	for (i = 0; i < (int)env.sys_cfg.num_cards; i++) {
		for (j = 0; j < (int)env.sys_cfg.num_pf; j++) {
			if (env.sys_cfg.pf_nvf_lst[j] > 0) {
				FILE *fp;

				snprintf(filename, 100, "/sys/bus/pci/devices/0000:%02x:%02x.%01x/sriov_totalvfs", env.sys_cfg.pci_bus[i],
						 env.sys_cfg.pci_dev[i], j);
				fp = fopen(filename, "r");
				if (fp == NULL) {
					printf("Error: %s - No such file\n", filename);
					exit(1);
				}
				memset(filename, '\0', 100);
				if ( fgets (totalvf_str , 10 , fp) != NULL )
					sscanf(totalvf_str, "%u", &num_vf);
				else {
					printf("Error: %s - could not read file\n", filename);
					fclose(fp);
					exit(1);
				}
				memset(totalvf_str, '\0', 10);
				if (num_vf < env.sys_cfg.pf_nvf_lst[j]) {
					printf("Error: Invalid configuration - pf_nvf[%d]\n", j);
					fclose(fp);
					exit(1);
				}
				fclose(fp);
			}
		}
	}
#endif

}
#endif

#ifdef _WIN32
static void platform_init(int argc, char** argv)
{
    /* Nothing to init */
}

static void setup_env(void)
{
    /* Nothing to setup */
}

#elif DPDK
static void platform_init(int argc, char** argv)
{
	int ret = 0;

	ret = rte_eal_init(argc, argv);
	if (ret < 0)
		rte_exit(EXIT_FAILURE, "Error with EAL initialization\n");
	// rte_log_set_global_level(RTE_LOG_ERR); // uncomment this if the global log level needed to be set to ERROR
	rte_log_set_level(RTE_LOGTYPE_PMD, RTE_LOG_ERR); // Set the PMD log level to error
}

static void setup_env(void)
{
	char *cmd = 0;
	int ret = 0;
	std::string cmd_out;
	char *path;
	int i, j;

	path = getenv("RTE_SDK");
	if (!path){
		printf("RTE_SDK not defined\n");
		exit(1);
	}

	cmd = new char[10000];
#ifndef TEST_VF_ALONE
	for (i = 0; i < (int)env.sys_cfg.num_cards; i++) {
		for (j = 0; j < (int)env.sys_cfg.num_pf; j++) {
			if (env.sys_cfg.pf_qmax_cfg_en[j]) {
				if(!strncmp(bind_drv, BIND_DRV_VFIO_PCI, strlen(BIND_DRV_VFIO_PCI))){
					system("modprobe vfio-pci");
					snprintf(cmd, 10000, "%s/usertools/dpdk-devbind.py -b %s %02x:%02x.%01x",path, BIND_DRV_IGB_UIO, env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j);
					printf("%s\n", cmd);
					ret = system(cmd);
					if (ret != 0) {
						printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
						exit(1);
					}
					if (env.sys_cfg.pf_nvf_lst[j]) {
						snprintf(cmd, 1000, "echo %u > /sys/bus/pci/devices/0000\\:%02x\\:%02x.%01x/max_vfs",
								env.sys_cfg.pf_nvf_lst[j], env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j);

						printf("%s\n", cmd);
						ret = system(cmd);
						if (ret != 0) {
							printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
							exit(1);
						}
					}
					snprintf(cmd, 10000, "%s/usertools/dpdk-devbind.py -u %02x:%02x.%01x",path,env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j);
					printf("%s\n", cmd);
					ret = system(cmd);
					if (ret != 0) {
						printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
						exit(1);
					}

					snprintf(cmd, 10000, "%s/usertools/dpdk-devbind.py -b %s %02x:%02x.%01x",path, BIND_DRV_VFIO_PCI, env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j);
					printf("%s\n", cmd);
					ret = system(cmd);
					if (ret != 0) {
						printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
						exit(1);
					}
				} else {
					snprintf(cmd, 10000, "%s/usertools/dpdk-devbind.py -b %s  %02x:%02x.%01x",path, BIND_DRV_IGB_UIO, env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j);
					printf("%s\n", cmd);
					ret = system(cmd);
					if (env.sys_cfg.pf_nvf_lst[j]) {
						snprintf(cmd, 1000, "echo %u > /sys/bus/pci/devices/0000\\:%02x\\:%02x.%01x/max_vfs",
								env.sys_cfg.pf_nvf_lst[j], env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j);

						printf("%s\n", cmd);
						ret = system(cmd);
						if (ret != 0) {
							printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
							exit(1);
						}
					}

				}
				memset(cmd, '\0', 10000);
			}
		}
	}

#endif

	/*
		1. lspci | grep -i xilinx  -- Gives the list of Xilinx PCI devices
			Ex : xhdipdslab42:~% lspci | grep -i xilinx
				81:00.0 Memory controller: Xilinx Corporation Device 903f
				81:00.1 Memory controller: Xilinx Corporation Device 913f
				81:00.2 Memory controller: Xilinx Corporation Device 923f
				81:00.3 Memory controller: Xilinx Corporation Device 933f
				81:00.4 Memory controller: Xilinx Corporation Device a03f
				81:00.5 Memory controller: Xilinx Corporation Device a13f
				81:00.6 Memory controller: Xilinx Corporation Device a23f
				81:00.7 Memory controller: Xilinx Corporation Device a33f

		2. awk -F " " 'NR>%d{print $1}'
			  i. This command reads the pipe output from above command line by line (like a loop)
			 ii. Separates the strings by a space " " (-F " " option)
			iii. Prints first string (81:00.4) to the console (print $1) only if the NR(No of Records) > #num_pf

			Ex : xhdipdslab42:~% lspci | grep -i xilinx | awk -F " " 'NR>4{print $1}'
				81:00.4
				81:00.5
				81:00.6
				81:00.7
		3. tr -t "\n" " "
			i. Translate(tr) command replaces new line("\n") with a space(" ")

			Ex : xhdipdslab42:~% lspci | grep -i xilinx | awk -F " " 'NR>4{print $1}' | tr -t "\n" " "
				81:00.4 81:00.5 81:00.6 81:00.7

		4. Finally, the command extracts all the VF BDF info into a single string that can be used to bind VFs
	*/
	//snprintf(cmd, 100000, "lspci | grep -i xilinx|awk -F \" \" \'NR>%d{print $1}\'| tr -t \"\n\" \" \" ", (int)env.sys_cfg.num_pf);
	snprintf(cmd, 10000, "lspci | grep -i xilinx | awk -F \" \" \'(($7 > \"a000\" && $7< \"b000\") || ($7 > \"c000\" && $7< \"d000\")) {print $1}\' | tr -t \"\n\" \" \" ");
	//cmd_out = xlnx::os::execute_command("lspci | grep -i xilinx|awk -F \" \" \'NR>4{print $1}\'| tr -t \"\n\" \" \" ");
	cmd_out = xlnx::os::execute_command(cmd);

	delete[] cmd;

	if (cmd_out != ""){

		cmd = new char[cmd_out.size() + 1000];

#ifdef TEST_VF_ALONE
		if(!strncmp(bind_drv, BIND_DRV_VFIO_PCI, strlen(BIND_DRV_VFIO_PCI)))
			system("echo 1 > /sys/module/vfio/parameters/enable_unsafe_noiommu_mode");
#endif

		snprintf(cmd, cmd_out.size()+1000, "%s/usertools/dpdk-devbind.py -b %s  %s",path, bind_drv, cmd_out.c_str());
		printf("cmd_out : %s\n", cmd_out.c_str());
		ret = system(cmd);

		if (ret != 0) {
			printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
			exit(1);
		}
		delete[] cmd;
	}
}

static void cleanup_env(void)
{
	char *cmd = 0;
	int ret = 0;
	unsigned int i, j;
	std::string cmd_out;
	char *path;
	cmd = new char[10000];

	path = getenv("RTE_SDK");
	if (!path){
		printf("RTE_SDK not defined\n");
		exit(1);
	}
	// detaching all the PF and VF devices
	if (env.pfs.empty() && env.vfs.empty()) {
		std::cerr << "Error: Failed to find any QDMA devices!\n";
		std::exit(-1);
	}

	for (i = 0; i < env.vfs.size(); i++) {
		struct rte_device *dev;
		auto& vf = env.vfs[i];
		dev = rte_eth_devices[vf.dev_id].device;
		printf("Removing VF device with dev id %d\n", vf.dev_id);
		/*Detach the device, it will invoke device remove/uninit */
		if (rte_dev_remove(dev))
			printf("Failed to detach port '%d'\n", vf.dev_id);
	}

	qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	auto device_type = get_device_type(env.pfs[env.sys_cfg.master_pf].dev_id, devlist);
	if (device_type != QDMA_DEVICE_VERSAL_CPM5) {
		qdma::device& qdev=env.pfs.front();
		example_design_ctrl user_logic{ qdev };
		user_logic.reset_ip();
	}

	for (i = 0; i < env.pfs.size(); i++) {
		struct rte_device *dev;
		auto& pf = env.pfs[i];
		printf("Removing PF device with dev id %d\n", pf.dev_id);
		dev = rte_eth_devices[pf.dev_id].device;
		/*Detach the device, it will invoke device remove/uninit */
		if (rte_dev_remove(dev))
			printf("Failed to detach port '%d'\n", pf.dev_id);
	}

	for (i = 0; i < env.sys_cfg.num_cards; i++) {
	snprintf(cmd, 10000, "lspci | grep -i xilinx | grep -i  %x: | awk -F \" \" \'(($7 > \"a000\" && $7< \"b000\") || ($7 > \"c000\" && $7< \"d000\")) {print $1}\' | tr -t \"\n\" \" \" ", env.sys_cfg.pci_bus[i]);
	cmd_out = xlnx::os::execute_command(cmd);

	delete[] cmd;

	if (cmd_out != ""){
		cmd = new char[cmd_out.size() + 1000];

		snprintf(cmd, cmd_out.size()+1000, "%s/usertools/dpdk-devbind.py -u %s",path, cmd_out.c_str());

		printf("cmd_out : %s\n", cmd_out.c_str());

		ret = system(cmd);

		if (ret != 0) {
			printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
			exit(1);
		}


		delete[] cmd;
	}
	}

#ifndef TEST_VF_ALONE
	cmd = new char[10000];

	for (i = 0; i < env.sys_cfg.num_cards; i++) {
		for (j = 0; j < env.sys_cfg.num_pf; j++) {
			if (env.sys_cfg.pf_qmax_cfg_en[j]) {
				if (!strncmp(bind_drv, BIND_DRV_VFIO_PCI, strlen(BIND_DRV_VFIO_PCI))){
					snprintf(cmd, 10000, "%s/usertools/dpdk-devbind.py -u %02x:%02x.%01x",path,env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j);
					printf("%s\n", cmd);
					ret = system(cmd);
					if (ret != 0) {
						printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
						exit(1);
					}

					snprintf(cmd, 10000, "%s/usertools/dpdk-devbind.py -b %s  %02x:%02x.%01x",path, BIND_DRV_IGB_UIO, env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j);
					printf("%s\n", cmd);
					ret = system(cmd);
					if (ret != 0) {
						printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
						exit(1);
					}
				}
				if (env.sys_cfg.pf_nvf_lst[j]) {
					snprintf(cmd, 1000, "echo 0 > /sys/bus/pci/devices/0000\\:%02x\\:%02x.%01x/max_vfs",
							env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j);

					printf("%s\n", cmd);
					ret = system(cmd);
					if (ret != 0) {
						printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
						exit(1);
					}
				}
				snprintf(cmd, 10000, "%s/usertools/dpdk-devbind.py -u %02x:%02x.%01x",path,env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j);
				printf("%s\n", cmd);
				ret = system(cmd);
				if (ret != 0) {
					printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
					exit(1);
				}
				memset(cmd, '\0', 10000);
			}
		}
	}

	delete[] cmd;
#endif

}
#else
static void platform_init(int argc, char** argv)
{
    char cmd[100] = {'\0'};
    int ret = 0;

    snprintf(cmd, 100, "dma-ctl dev list");

    printf("%s\n", cmd);
    ret = system(cmd);
    if (WIFSIGNALED(ret) &&
        (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)) {
        printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
        exit(1);
    }
    system("ulimit -n 1048576"); /* This is to allow more file descriptors to be open at a time */
}

static void setup_env(void)
{
    char cmd[100] = {'\0'};
    int ret = 0;
    int i, j, k;

#ifdef TEST_VF_ALONE
    char command[200];
    std::string cmd_out;

#endif

#ifndef TEST_VF_ALONE
	for (i = 0; i < (int)env.sys_cfg.num_cards; i++) {
		for (j = 0; j < (int)env.sys_cfg.num_pf; j++) {
			if (env.sys_cfg.pf_nvf_lst[j] > 0) {
				snprintf(cmd, 100, "echo %u > /sys/bus/pci/devices/0000:%02x:%02x.%01x/sriov_numvfs",
						 env.sys_cfg.pf_nvf_lst[j], env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j);

				printf("%s\n", cmd);
				ret = system(cmd);
				if (ret != 0) {
					printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
					exit(1);
				}
				memset(cmd, '\0', 100);
			}
		}
		sleep(1);
		for (j = 0; j < (int)env.sys_cfg.num_pf; j++) {
			if (env.sys_cfg.pf_qmax_cfg_en[j]) {
				snprintf(cmd, 100, "echo %u > /sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/qmax",
					 env.sys_cfg.pf_qmax_lst[j], env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j);

				printf("%s\n", cmd);
				ret = system(cmd);
				if (ret != 0) {
					printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
					exit(1);
				}
				memset(cmd, '\0', 100);
			}
		}
	}
#endif

    printf("In setup_env before virtfn echo : %d\n", env.vfs.empty());
#ifdef TEST_VF_ALONE
	int pf_vfs_bdf_field = 0;
	for (i = 0; i < (int)env.sys_cfg.num_pf; i++) {
		for (j = 0; j < (int)env.sys_cfg.pf_nvf_lst[i]; j++) {
			/*
			1. 'lspci | grep -i xilinx' Lists all Xilinx PCI devices
				Ex : xhdipdslab42:~% lspci | grep -i xilinx
					81:00.0 Memory controller: Xilinx Corporation Device 903f
					81:00.1 Memory controller: Xilinx Corporation Device 913f
					81:00.2 Memory controller: Xilinx Corporation Device 923f
					81:00.3 Memory controller: Xilinx Corporation Device 933f
					81:00.4 Memory controller: Xilinx Corporation Device a03f
					81:00.5 Memory controller: Xilinx Corporation Device a13f
					81:00.6 Memory controller: Xilinx Corporation Device a23f
					81:00.7 Memory controller: Xilinx Corporation Device a33f

			2. 'lspci | grep -i xilinx | awk -F \" \" \'$7 > \"a000\" {print $1}' filters
			    the PCI xilinx devices which has device ID greater than 0xA000 and prints their BDFs
				Ex : xhdipdslab42:~% lspci | grep -i xilinx | awk -F " " 'NR>4{print $1}'
					81:00.4
					81:00.5
					81:00.6
					81:00.7
			3. 'lspci | grep -i xilinx | awk -F \" \" \'$7 > \"a000\" {print $1} | tr -t \"\\n\" \" \"'
			    replaces '\n' with a space
				Ex : xhdipdslab42:~% lspci | grep -i xilinx | awk -F " " 'NR>4{print $1}' | tr -t "\n" " "
					81:00.4 81:00.5 81:00.6 81:00.7

			4. 'lspci | grep -i xilinx | awk -F \" \" \'$7 > \"a000\" {print $1} | tr -t \"\\n\" \" \" | cut -d\' \' -f%d'
			   cuts the bigger string into smaller strings delimited by a space
				Ex : xhdipdslab42:~% lspci | grep -i xilinx | awk -F " " 'NR>4{print $1}' | tr -t "\n" " | cut -d\' \' -f1 "
					81:00.4
				Ex : xhdipdslab42:~% lspci | grep -i xilinx | awk -F " " 'NR>4{print $1}' | tr -t "\n" " | cut -d\' \' -f2 "
					81:00.5
			*/
			snprintf(command, 200, \
				"lspci | grep -i xilinx | awk -F \" \" \'$7 > \"a000\" "
				"{print $1}\' | tr -t \"\\n\" \" \" | cut -d\' \' -f%d", ++pf_vfs_bdf_field);

			printf("Commmand : %s\n", command);

			cmd_out = xlnx::os::execute_command(command);

			if (cmd_out != "") {
				cmd_out.erase(std::remove(cmd_out.begin(), cmd_out.end(), '\n'), cmd_out.end());

				printf("cmd_out : %s\n", cmd_out.c_str());

				snprintf(cmd, 100, "echo %u > /sys/bus/pci/devices/0000:%s/qdma/qmax",
					 env.sys_cfg.vf_pf_qmax_lst[i][j], cmd_out.c_str());
				printf("%s\n", cmd);

				ret = system(cmd);
				if (ret != 0) {
					printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
					exit(1);
				}
				memset(cmd, '\0', 100);
			}
		}
	}
#else
	for (i = 0; i < (int)env.sys_cfg.num_cards; i++) {
		for (j = 0; j < (int)env.sys_cfg.num_pf; j++) {
			for (k = 0; k < (int)env.sys_cfg.pf_nvf_lst[j]; k++) {
				snprintf(cmd, 100, "echo %u > /sys/bus/pci/devices/0000:%02x:%02x.%01x/virtfn%d/qdma/qmax",
						 env.sys_cfg.vf_pf_qmax_lst[j][k], env.sys_cfg.pci_bus[i], env.sys_cfg.pci_dev[i], j, k);

				printf("%s\n", cmd);

				ret = system(cmd);
				if (ret != 0) {
					printf("Error: %s - Failed with errcode = %d\n", cmd, ret);
					exit(1);
				}
				memset(cmd, '\0', 100);
			}
		}
	}
#endif
}
#endif

static void cleanup(void)
{
    int i;

#ifdef DPDK
	cleanup_env();
#endif

    for (i = 0; i < (int)env.sys_cfg.num_pf; i++){
		if(env.sys_cfg.vf_pf_qmax_lst[i] != NULL)
			free(env.sys_cfg.vf_pf_qmax_lst[i]);
	}
	free(env.sys_cfg.vf_pf_qmax_lst);
	free(env.sys_cfg.pf_nvf_lst);
	free(env.sys_cfg.pf_qmax_lst);
	free(env.sys_cfg.pf_qmax_cfg_en);

}

int main (int argc, char* argv[])
{
    int cmd_opt;
    char *cfg_fname = NULL;
    int option_index;

    int dpdk_argc=1;
#ifdef DPDK
    struct rte_pci_device *vf_pci_dev;
    size_t i, j, pf_idx;
#endif

    while ((cmd_opt = getopt_long(argc, argv, "f:c:n:gtest_repeat:gtest_output:gtest_filter:gtest_list_tests:config:bind_driver", long_opts, &option_index)) != -1) {
        switch (cmd_opt)
        {
        case 'f':
            /* config file name */
            cfg_fname = strdup(optarg);
            break;
#ifdef DPDK
        case 'c':
    		dpdk_argc+= 2;
           break;
        case 'n':
    		dpdk_argc += 2;
            break;
        case 0:
            break;
#else
        case 0:
            /* long option */

            break;
#endif
        default:
            usage(argv[0]);
            break;
        }
    }
#ifdef DPDK
    parse_cmdline(argc, argv);
#endif
    if (cfg_fname) {
        printf("Parsing config file %s\n", cfg_fname);
        parse_config_file(cfg_fname);
        atexit(cleanup);
#if DISPLAY_CONFIG_INFO
        dump_setp_config();
        exit(1);
#endif
#ifndef _WIN32
        printf("Validating config\n");
        validate_config();
#endif
        printf("setting up environment\n");
        setup_env();

        sleep(1);
    }

    platform_init(dpdk_argc, argv);

    env.update();

    if (env.pfs.empty() && env.vfs.empty()) {
        std::cerr << "Error: Failed to find any QDMA devices!\n";
        std::exit(-1);
    }

#ifdef DPDK
    if (cfg_fname != NULL){

		pf_idx = 0;
		for (i = 0; i < env.sys_cfg.num_cards; i++) {
			for (j = 0; j < env.sys_cfg.num_pf; j++) {
#ifndef TEST_VF_ALONE
				if (env.sys_cfg.pf_qmax_cfg_en[j]) {
					auto& pf = env.pfs[pf_idx];
					pf.max_num_queues = env.sys_cfg.pf_qmax_lst[j];
				}
#endif
				pf_idx++;
			}
		}

		for (i = 0, j=0; i < env.vfs.size(); i++) {
			auto& vf = env.vfs[i];
			vf_pci_dev = RTE_ETH_DEV_TO_PCI(&rte_eth_devices[vf.dev_id]);

			auto pf = ((vf_pci_dev->id.device_id) >> 8) & 0x0F;

			uint8_t num_vf_pf = env.sys_cfg.pf_nvf_lst[pf];
			vf.max_num_queues = env.sys_cfg.vf_pf_qmax_lst[pf][j];
			j++;
			if( j >= num_vf_pf)
				j=0;
		}
	}
#endif

    if (!env.pfs.empty())
    	std::cout << "num_pfs=" << env.pfs.size() << "\n";
    if (!env.vfs.empty())
    	std::cout << "num_vfs=" << env.vfs.size() << "\n";

    std::cout << "bram_size=" << example_design_ctrl::bram_size << "\n";
    std::cout << "random_seed=" << env.random_seed << "\n";
    if (!env.pfs.empty()) {
        for (size_t i = 0; i < env.pfs.size(); i++) {
            const auto& pf = env.pfs[i];
            std::cout << "PF" << i << ": " <<  pf.max_num_queues << " queues\n";
            if(get_device_type(env.pfs[i].dev_id, env.pfs) == -1) {
                std::cout << "Invalid device type" << std::endl;
                       exit(-1);
            }
        }

    }
    if (!env.vfs.empty()) {
        for (size_t i = 0; i < env.vfs.size(); i++) {
            const auto& vf = env.vfs[i];
#ifdef DPDK
            std::cout << "VF" << i << ": " << vf.max_num_queues << " queues" <<"\n";
#else
            std::cout << "VF" << i << ": " << vf.max_num_queues << " queues" <<", q_base = " << vf.qbase_start <<"\n";
#endif
            if(get_device_type(env.vfs[i].dev_id, env.vfs) == -1) {
                std::cout << "Invalid device type" << std::endl;
                exit(-1);
            }
        }
    }

    ::testing::InitGoogleTest(&argc, argv);

    // don't test VF if no VF devices are enabled
    if (env.vfs.empty()) {
        std::cout << "Filtered out VF test cases since no VF devices have been detected.\n";
        auto& filter_str = testing::GTEST_FLAG(filter);
        if (filter_str.find_last_of('-') != filter_str.npos ){
            filter_str += ":*VF*";
        } else {
            filter_str += "-*VF*";
        }
    }

    return RUN_ALL_TESTS();

}


