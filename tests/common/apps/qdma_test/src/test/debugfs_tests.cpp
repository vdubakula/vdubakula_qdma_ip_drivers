#include <gtest/gtest.h>
#include "test_env.h"
#include "qdma_queue.h"
#include <qdma/qdma_nl.h>
#include <xlnx_gtest_ext.h>
#include <dirent.h>
#include <errno.h>

#include "test_env.h"
#include "example_design_ctrl.h"
#include "qdma_queue.h"
#include <qdma/qdma_nl.h>
#include <xlnx_gtest_ext.h>


extern test_env env;

#define MAX_DEBUGFS_BUF_LEN		(2048 * 10)
#define PF_PATH 		"/sys/kernel/debug/qdma-pf/"
#define VF_PATH 		"/sys/kernel/debug/qdma-vf/"



static int check_dir(char *dirname)
{
	DIR *opendirval = opendir(dirname);
	if(opendirval == nullptr)
		return -1;

	closedir(opendirval);
	return 1;
}

static int check_file(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if(fd < 0)
		return -1;

	close(fd);
	return 1;
}


static int parse_debugfs_info(char * filepath)
{

	char cmd[MAX_DEBUGFS_BUF_LEN] = "";
	char cmdresp[MAX_DEBUGFS_BUF_LEN] = "";

	snprintf(cmd, MAX_DEBUGFS_BUF_LEN, "cat %s ", filepath);
	if(exec_cmd(cmd, cmdresp) != 0)
		return -1;

	if(strstr(cmdresp, "Master PF") == NULL) {
		std::cout << "Error Master PF" << std::endl;
		return -1;
	}
	if(strstr(cmdresp, "QBase") == NULL) {
		std::cout << "Error QBase" << std::endl;
		return -1;
	}
	if(strstr(cmdresp, "Max Qsets") == NULL) {
		std::cout << "Error Qsets" << std::endl;
		return -1;
	}
	if(strstr(cmdresp, "Number of VFs") == NULL) {
		std::cout << "Error Vfs" << std::endl;
		return -1;
	}
	if(strstr(cmdresp, "Max number of VFs") == NULL){
		std::cout <<"Max Vfs" << std::endl;
		return -1;
	}
	if(strstr(cmdresp, "Driver Mode") == NULL) {
		std::cout <<"Error Driver Mode" << std::endl;
		return -1;
	}
	return 1;
}


static int parse_debugfs_reg(char *filepath)
{

	char cmd[MAX_DEBUGFS_BUF_LEN] = "";
	char cmdresp[MAX_DEBUGFS_BUF_LEN] = "";
	char cmpstr[MAX_DEBUGFS_BUF_LEN] = "";
	int i = 0;
	snprintf(cmd, MAX_DEBUGFS_BUF_LEN, "cat %s ", filepath);
	if(exec_cmd(cmd, cmdresp) != 0)
		return -1;
	if(strstr(cmdresp, "reg dump") == NULL) {
		std::cout << "ERROR reg dump" << std::endl;
		return -1;
	}
	return 1;
}

static int parse_debugfs_cmpt(char *filepath, qdma::instance_ext::type devtype, uint32_t dev_id,
		uint32_t q_id, qdma::queue_ext::mode mode, qdma::queue_ext::direction dir)
{

	char cmd[MAX_DEBUGFS_BUF_LEN] = "";
	char cmdresp[MAX_DEBUGFS_BUF_LEN] = "";
	char cmpstr[MAX_DEBUGFS_BUF_LEN] = "";

	/**
	 *  Parse info file
	 */
	snprintf(cmd, MAX_DEBUGFS_BUF_LEN, "cat %s%s ", filepath, "info");
	if(exec_cmd(cmd, cmdresp) != 0)
		return -1;

	sprintf(cmpstr, "%s%s%05x-%s-%d %s cfg'ed", "qdma", (devtype == qdma::instance_ext::type::pf ? "" : "vf"),
			dev_id, (mode == qdma::queue_ext::mode::streaming ? "ST" : "MM"), q_id,
			(dir == qdma::queue_ext::direction::card_to_host ? "C2H" : "H2C"));
	if(strstr(cmdresp, cmpstr) == NULL) {
		std::cout << "info" << std::endl;
		return -1;
	}

	memset(cmd, 0, MAX_DEBUGFS_BUF_LEN);
	snprintf(cmd, MAX_DEBUGFS_BUF_LEN, "cat %s%s ", filepath, "desc");
	if(exec_cmd(cmd, cmdresp) != 0)
		return -1;
	if(strstr(cmdresp, cmpstr) == NULL) {
		std::cout << "desc" << std::endl;
		return -1;
	}
	snprintf(cmd, MAX_DEBUGFS_BUF_LEN, "cat %s%s ", filepath, "cntxt");
	if(exec_cmd(cmd, cmdresp) != 0)
		return -1;
	if(strstr(cmdresp, "Completion Context") != NULL) {
		if(strstr(cmdresp, "Descriptor Size") == NULL) {
			std::cout << "Descriptor Size" << std::endl;
			return -1;
		}
		if(strstr(cmdresp, "PIDX") == NULL) {
			std::cout << "PIDX" << std::endl;
			return -1;
		}
		if(strstr(cmdresp, "Enable Status Desc Update") == NULL) {
			std::cout << "Enable Status Desc Update" << std::endl;
			return -1;
		}
		if(strstr(cmdresp, "CIDX") == NULL) {
			std::cout << "CIDX" << std::endl;
			return -1;
		}
	} else {
		std::cout << "SW Context" << std::endl;
		return -1;
	}
	return 1;
}

static int parse_debugfs_direction(char *filepath, qdma::instance_ext::type devtype, uint32_t dev_id,
		uint32_t q_id, qdma::queue_ext::mode mode, qdma::queue_ext::direction dir)
{

	char cmd[MAX_DEBUGFS_BUF_LEN] = "";
	char cmdresp[MAX_DEBUGFS_BUF_LEN] = "";
	char cmpstr[MAX_DEBUGFS_BUF_LEN] = "";

	/**
	 *  Parse info file
	 */
	snprintf(cmd, MAX_DEBUGFS_BUF_LEN, "cat %s%s ", filepath, "info");
	if(exec_cmd(cmd, cmdresp) != 0)
		return -1;

	sprintf(cmpstr, "%s%s%05x-%s-%d %s cfg'ed", "qdma", (devtype == qdma::instance_ext::type::pf ? "" : "vf"),
			dev_id, (mode == qdma::queue_ext::mode::streaming ? "ST" : "MM"), q_id,
			(dir == qdma::queue_ext::direction::card_to_host ? "C2H" : "H2C"));
	if(strstr(cmdresp, cmpstr) == NULL) {
		return -1;
	}

	memset(cmd, 0, MAX_DEBUGFS_BUF_LEN);
	snprintf(cmd, MAX_DEBUGFS_BUF_LEN, "cat %s%s ", filepath, "desc");
	if(exec_cmd(cmd, cmdresp) != 0)
		return -1;
	if(strstr(cmdresp, cmpstr) == NULL)
		return -1;

	snprintf(cmd, MAX_DEBUGFS_BUF_LEN, "cat %s%s ", filepath, "cntxt");
	if(exec_cmd(cmd, cmdresp) != 0)
		return -1;
	if(strstr(cmdresp, "SW Context") != NULL) {
		if(strstr(cmdresp, "Bypass Enable") == NULL) {
			std::cout << "Bypass Enable" << std::endl;
			return -1;
		}
		if(strstr(cmdresp, "PIDX") == NULL) {
			std::cout << "PIDX" << std::endl;
			return -1;
		}
		if(strstr(cmdresp, "HW Context") == NULL) {
			std::cout << "HW Context" << std::endl;
			return -1;
		}
		if(strstr(cmdresp, "CIDX") == NULL) {
			std::cout << "CIDX" << std::endl;
			return -1;
		}
	} else {
		std::cout << "SW Context" << std::endl;
		return -1;
	}
	return 1;
}

void test_function_entry(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
	unsigned int i = 0;
	char buf[MAX_DEBUGFS_BUF_LEN] = "";
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	for(i = 0; i < devlist.size(); i++) {
		snprintf(buf, strlen(VF_PATH), "%s",
				dev_type == qdma::instance_ext::type::pf ? PF_PATH : VF_PATH);
		snprintf(buf + strlen(buf), MAX_DEBUGFS_BUF_LEN, "/0000:%02x:%02x:%01x",
				(devlist[i].dev_id >> 8) >> 4, (devlist[i].dev_id >> 4) & 0x1F,
				(devlist[i].dev_id & 0x7));
		ASSERT_EQ(check_dir(buf), 1);
	}

}

void test_info_files(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
	unsigned int i = 0;
	char buf[MAX_DEBUGFS_BUF_LEN] = "";
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	for(i = 0; i < devlist.size(); i++) {
		/*Check if info file is present*/
		snprintf(buf, strlen(VF_PATH), "%s",
				(dev_type == qdma::instance_ext::type::pf ? PF_PATH : VF_PATH));
		snprintf(buf + strlen(buf), MAX_DEBUGFS_BUF_LEN, "/0000:%02x:%02x:%01x/qdma_info",
				(devlist[i].dev_id >> 8) >> 4, (devlist[i].dev_id >> 4) & 0x1F,
				(devlist[i].dev_id & 0x7));
		ASSERT_EQ(check_file(buf), 1);
		ASSERT_EQ(parse_debugfs_info(buf), 1);
	}

}


void test_reg_files(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
	unsigned int i = 0;
	char buf[MAX_DEBUGFS_BUF_LEN] = "";
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	for(i = 0; i < devlist.size(); i++) {
		/*Check if info file is present*/
		snprintf(buf, strlen(VF_PATH), "%s",
				dev_type == qdma::instance_ext::type::pf ? PF_PATH : VF_PATH);
		snprintf(buf + strlen(buf), MAX_DEBUGFS_BUF_LEN, "/0000:%02x:%02x:%01x/qdma_regs",
				(devlist[i].dev_id >> 8) >> 4, (devlist[i].dev_id >> 4) & 0x1F,
				(devlist[i].dev_id & 0x7));
		ASSERT_EQ(check_file(buf), 1);
		if (dev_type == qdma::instance_ext::type::pf) {
			ASSERT_EQ(parse_debugfs_reg(buf), 1);
		}
	}
}


struct debugfs_param {

	struct func_info {
		uint32_t pf = 0;
		uint32_t q_id = 0;
		uint32_t numqs = 1;
		qdma::instance_ext::type devtype = qdma::instance_ext::type::pf;
		func_info(uint32_t pf_id = 0, uint32_t queue_id = 0, uint32_t num_queues = 1,
				qdma::instance_ext::type pf_vf = qdma::instance_ext::type::pf)
		: pf(pf_id), q_id(queue_id), numqs(num_queues), devtype(pf_vf){}
	};

	std::vector<func_info> debugfs_func;
	qdma::queue_ext::mode mode;
	qdma::queue_ext::direction direction;

	debugfs_param(std::vector<func_info>&& devs,
			qdma::queue_ext::mode qmode, qdma::queue_ext::direction qdir)
		: debugfs_func(std::move(devs)), mode(qmode), direction(qdir) {}

};

void PrintTo(const debugfs_param& tp, std::ostream* os) {
	const auto& txs = tp.debugfs_func;

	//only print the ranges (first and last entry)
	if (!txs.empty()) {
		if (txs.front().devtype == qdma::instance_ext::type::vf)
			*os << "{ vfs=[";
		else
			*os << "{ pfs=[";
		*os << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.front().pf
				<< ":" << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.back().pf << "], ";
		*os << "queues=[" << txs.front().q_id << ":" << txs.back().q_id << "], ";
		*os << "num_of_qs=" << txs.front().numqs << " }";
	}
}

class qdma_debugfs_function_test: public testing::TestWithParam<qdma::instance_ext::type> {};
class qdma_debugfs_queues_test: public testing::TestWithParam<debugfs_param> {};

static debugfs_param debugfs_queues_test(qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::host_to_card,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::memory_mapped) {

	std::vector<debugfs_param::func_info> testParams;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t num_of_functions = 0;
	uint32_t q_id = 0;
	uint32_t numqs = 2048;
	uint32_t validfunctions = 0;

	if(dev_type == qdma::instance_ext::type::pf)
		num_of_functions = env.pfs.size();
	else
		num_of_functions = env.vfs.size();

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	testParams.reserve(validfunctions);
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
			if(dev_type == qdma::instance_ext::type::pf) {
				if(env.pfs[pf_id].max_num_queues == 0)
					continue;
				if(numqs > env.pfs[pf_id].max_num_queues)
					numqs = env.pfs[pf_id].max_num_queues;
			} else {
				if(env.vfs[pf_id].max_num_queues == 0)
					continue;
				if(numqs > env.vfs[pf_id].max_num_queues)
					numqs = env.vfs[pf_id].max_num_queues;
			}
			testParams.emplace_back(devlist[pf_id].dev_id, q_id,
					numqs, dev_type);
	}
	return  debugfs_param{ std::move(testParams), mode, dir};
}


TEST_P(qdma_debugfs_function_test, DEBUGFS001_check_function_dir) {
	test_function_entry(GetParam());
}


TEST_P(qdma_debugfs_function_test, DEBUGFS002_parse_info) {
	test_info_files(GetParam());
}

TEST_P(qdma_debugfs_function_test, DEBUGFS003_parse_reg) {
	test_reg_files(GetParam());
}


TEST_P(qdma_debugfs_queues_test, debugfs_queues_check) {
	
	const auto& debugfs_info = GetParam();

	for (const auto& test : debugfs_info.debugfs_func) {

		SCOPED_TRACE("devtype = " + (test.devtype == qdma::instance_ext::type::pf) ? "PF" : "VF");
		SCOPED_TRACE("pf = " + int_to_hex(test.pf));
		SCOPED_TRACE("q = " + int_to_hex(test.q_id));
		SCOPED_TRACE("qs = " + int_to_hex(test.numqs));
		SCOPED_TRACE("Adding queues");

		ASSERT_EQ(dmactl_qadd(test.devtype, test.pf, test.q_id,
				test.numqs, debugfs_info.mode, debugfs_info.direction), 0);

		for(unsigned int j = 0; j < test.numqs; j++) {
			char buf[MAX_DEBUGFS_BUF_LEN] = "";
			if(test.devtype == qdma::instance_ext::type::pf)
				snprintf(buf, MAX_DEBUGFS_BUF_LEN, PF_PATH "0000:%02x:%02x:%01x/queues/%d/",
						(test.pf >> 8) >> 4, (test.pf >> 4) & 0x1F,
						(test.pf & 0x7), test.q_id + j);
			else
				snprintf(buf, MAX_DEBUGFS_BUF_LEN, VF_PATH "0000:%02x:%02x:%01x/queues/%d/",
						(test.pf >> 8) >> 4, (test.pf >> 4) & 0x1F,
						(test.pf & 0x7), test.q_id + j);

			ASSERT_EQ(check_dir(buf), 1);

			if((debugfs_info.mode == qdma::queue_ext::mode::streaming) &&
				((debugfs_info.direction == qdma::queue_ext::direction::card_to_host)
				|| (debugfs_info.direction ==qdma::queue_ext::direction::both))) {

				char cmptbuf[MAX_DEBUGFS_BUF_LEN] = "";
				strcpy(cmptbuf, buf);
				strcat(cmptbuf, "cmpt/");
				ASSERT_EQ(check_dir(cmptbuf), 1);
				//parse completion
				ASSERT_EQ(parse_debugfs_cmpt(cmptbuf, test.devtype, test.pf, (test.q_id + j),
				debugfs_info.mode, qdma::queue_ext::direction::card_to_host), 1);
			}

			if((debugfs_info.direction == qdma::queue_ext::direction::card_to_host)
				|| (debugfs_info.direction ==qdma::queue_ext::direction::both)) {

				char c2hbuf[MAX_DEBUGFS_BUF_LEN] = "";
				strcpy(c2hbuf, buf);
				strcat(c2hbuf, "c2h/");
				ASSERT_EQ(check_dir(c2hbuf), 1);
				//parse c2h
				ASSERT_EQ(parse_debugfs_direction(c2hbuf, test.devtype, test.pf, (test.q_id + j),
					debugfs_info.mode, qdma::queue_ext::direction::card_to_host), 1);
			}

			if((debugfs_info.direction == qdma::queue_ext::direction::host_to_card)
				|| (debugfs_info.direction ==qdma::queue_ext::direction::both)) {

				char h2cbuf[MAX_DEBUGFS_BUF_LEN] = "";
				strcpy(h2cbuf, buf);
				strcat(h2cbuf, "h2c/");
				ASSERT_EQ(check_dir(h2cbuf), 1);
				//parse c2h
				ASSERT_EQ(parse_debugfs_direction(h2cbuf, test.devtype, test.pf, (test.q_id + j), debugfs_info.mode,
					qdma::queue_ext::direction::host_to_card), 1);
			}
		}
		ASSERT_EQ(dmactl_qdel(test.devtype, test.pf, test.q_id,
				test.numqs, debugfs_info.direction), 0);
	}
}


INSTANTIATE_TEST_CASE_P(DEBUGFS_function_test, qdma_debugfs_function_test,
						::testing::Values(qdma::instance_ext::type::pf));

INSTANTIATE_TEST_CASE_P(VF_DEBUGFS_function_test, qdma_debugfs_function_test,
						::testing::Values(qdma::instance_ext::type::vf));


INSTANTIATE_TEST_CASE_P(DEBUGFS004_queues_test, qdma_debugfs_queues_test, ::testing::Values(
				debugfs_queues_test(qdma::instance_ext::type::pf),
				debugfs_queues_test(qdma::instance_ext::type::pf,
					qdma::queue_ext::direction::card_to_host),
				debugfs_queues_test(qdma::instance_ext::type::pf,
					qdma::queue_ext::direction::card_to_host, qdma::queue_ext::mode::streaming),
				debugfs_queues_test(qdma::instance_ext::type::pf,
					qdma::queue_ext::direction::host_to_card, qdma::queue_ext::mode::streaming)));

INSTANTIATE_TEST_CASE_P(VF_DEBUGFS004_queues_test, qdma_debugfs_queues_test, ::testing::Values(
				debugfs_queues_test(qdma::instance_ext::type::vf),
				debugfs_queues_test(qdma::instance_ext::type::vf,
					qdma::queue_ext::direction::card_to_host),
				debugfs_queues_test(qdma::instance_ext::type::vf,
					qdma::queue_ext::direction::card_to_host, qdma::queue_ext::mode::streaming),
				debugfs_queues_test(qdma::instance_ext::type::vf,
					qdma::queue_ext::direction::host_to_card, qdma::queue_ext::mode::streaming)));
