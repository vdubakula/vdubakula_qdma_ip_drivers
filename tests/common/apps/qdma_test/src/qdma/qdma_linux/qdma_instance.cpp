/*******************************************************************************
 *
 * Xilinx XDMA IP Core Linux Driver
 * Copyright(c) 2015 - 2017 Xilinx, Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * The full GNU General Public License is included in this distribution in
 * the file called "LICENSE".
 *
 * Karen Xie <karen.xie@xilinx.com>
 *
 ******************************************************************************/

#include <stdexcept>
#include "qdma_instance.h"
#include "test_env.h"

#include "xlnx_pci.h"
#include "xlnx_util.h"
#include <stdio.h>
#include <stdlib.h>

extern test_env env;
#include <iostream>
using namespace std;

int find_devices(const std::string& str, const std::string& sub, std::string& result)
{
    if (sub.length() == 0) return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos;
	offset = str.find(sub, offset + sub.length()))
    {
    	auto i = 0u;
    	char temp[200] = {0};
    	while (str.length() > i) {
    		temp[i] = str[offset + i];
    		if (str[offset + i] == '\n')
    			break;
    		i++;
    	}
    	result.append(temp);
        ++count;
    }
    return count;
}

string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}


namespace qdma {

namespace {
uint32_t queue_dir_to_nl_q_flag(queue_ext::direction q_dir) {
    switch (q_dir) {
    case queue_ext::direction::host_to_card:
        return XNL_F_QDIR_H2C;
    case queue_ext::direction::card_to_host:
        return XNL_F_QDIR_C2H;
    case queue_ext::direction::both:
        return XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;
    case queue_ext::direction::cmpt:
    	return XNL_F_Q_CMPL;
    };
    return 0;
}
} // end anonymous namespace

instance_ext::instance_ext(instance_ext::type t)
    : qdma_socket(t == type::pf ? XNL_NAME_PF : XNL_NAME_VF) {
	instance_ext::m_type = t;
}

int instance_ext::get_dev_index(std::string dev_string) {
	int idx = 0;
	std::stringstream ss;
	std::string qdma_dev;
	std::string qdma_devid;
	size_t pos=4;

	ss << dev_string;
	ss >> qdma_dev;

	if (qdma_dev[4] == 'v' && qdma_dev[5] == 'f')
	    pos = 6;
	qdma_devid = qdma_dev.substr(pos, qdma_dev.length());
	idx = strtoul(qdma_devid.c_str(), NULL, 16);

	return idx;
}

std::vector<device> instance_ext::get_devices() {
    auto dev_strings = get_num_devices();
    auto num_devs = dev_strings.size();
    std::vector<device> qdma_devices;
    qdma_devices.reserve(num_devs);

    for (auto i = 0u; i < num_devs; i++) {
	uint32_t idx = get_dev_index(dev_strings[i]);
	//save the last id for last_id+1 INVALID_ID tests
	if (idx > m_last_id)
		m_last_id = idx;
	const auto dev_details = dev_info(idx);
	qdma_devices.emplace_back(*this, dev_details);
	qdma_devices[i].dev_id = idx;
    }
    return std::move(qdma_devices);
}

/** helper function for getting the last_device_id, for INVALID_ID
* testcases
*/
uint32_t instance_ext::get_last_id() {
	return m_last_id;
}

//size_t instance::get_num_devices(std::vector<std::string> *dev_strings) {
std::vector<std::string> instance_ext::get_num_devices() {

    auto cmd = qdma_socket.prepare_msg(XNL_CMD_DEV_LIST);
    qdma_socket.send_msg(cmd);
    auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    char* dev_list_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);
    if(dev_list_str == NULL)
    	exit(-1);
    std::string result;
	if (env.sys_cfg.multiple_apps == 1) {
		for (auto idx = 1u; idx <= env.sys_cfg.num_cards; idx++) {
			string qdmabus = "qdma";
			std::stringstream ss;
			if (m_type == type::vf)
				qdmabus.append("vf");
			if(env.sys_cfg.pci_bus[(idx-1)] < 0xF)
				qdmabus.append("0");
			ss << std::hex << env.sys_cfg.pci_bus[(idx-1)];
			qdmabus.append(ss.str());
			find_devices(convertToString(dev_list_str, strlen(dev_list_str)), qdmabus, result);
		}
		auto dev_strings = split(result.c_str(), '\n');
		return dev_strings;
	} else {
		auto dev_strings = split(dev_list_str, '\n');
		return dev_strings;
	}
}

std::string instance_ext::get_device_path(unsigned dev_id, unsigned q_id, queue_ext::mode q_mode) {
    std::stringstream ss;
    ss << "/dev/qdma";
    if (m_type == type::vf) {
        ss << "vf";
    }
    ss << std::hex << std::setw(5) << std::setfill('0') << dev_id;
    ss << "-" << std::dec << to_string(q_mode) << '-' << q_id;
    return ss.str();
}

auto instance_ext::dev_info(unsigned dev_id) -> device::info {

    auto cmd = qdma_socket.prepare_msg(XNL_CMD_DEV_INFO);
    cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
    qdma_socket.send_msg(cmd);
    auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);

    device::info info;
    info.id.bus = resp.get_attrib<uint32_t>(XNL_ATTR_PCI_BUS);
    info.id.dev = resp.get_attrib<uint32_t>(XNL_ATTR_PCI_DEV);
    info.id.fn = resp.get_attrib<uint32_t>(XNL_ATTR_PCI_FUNC);
    info.dma_bar_idx = resp.get_attrib<uint32_t>(XNL_ATTR_DEV_CFG_BAR);
    info.user_bar_idx = resp.get_attrib<int32_t>(XNL_ATTR_DEV_USR_BAR);
    info.max_num_queues = resp.get_attrib<uint32_t>(XNL_ATTR_DEV_QSET_MAX);
    info.qbase_start = resp.get_attrib<uint32_t>(XNL_ATTR_DEV_QSET_QBASE);

    auto cmd1 = qdma_socket.prepare_msg(XNL_CMD_DEV_CAP);
    cmd1.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
    qdma_socket.send_msg(cmd1);

    auto resp1 = qdma_socket.receive_msg(XNL_ATTR_MAX);
    char *device_type = resp1.get_attrib<char*>(XNL_ATTR_DEVICE_TYPE);
    char *ip_type = resp1.get_attrib<char*>(XNL_ATTR_IP_TYPE);
	void *device_cap = resp1.get_attrib<void*>(XNL_ATTR_DEV);

    /** copy the device capability values except the device type and versal ip type */
	memcpy(&info.dev_cap, device_cap, (sizeof(info.dev_cap) -
							sizeof(info.dev_cap.device_type) +
							sizeof(info.dev_cap.ip_type)));

    if (strstr(device_type, "Soft IP") != NULL) {
    	info.dev_cap.device_type = QDMA_LINUX_DEVICE_SOFT;
    } else if (strstr(device_type, "Versal CPM4 Hard IP") != NULL) {
    	info.dev_cap.device_type = QDMA_LINUX_DEVICE_VERSAL_CPM4;
    } else if (strstr(device_type, "Versal Hard CPM5") != NULL) {
    	info.dev_cap.device_type = QDMA_LINUX_DEVICE_VERSAL_CPM5;
    } else {
    	info.dev_cap.device_type = QDMA_LINUX_DEVICE_NONE;
    }


    if (strstr(ip_type, "Versal Soft IP") != NULL) {
	info.dev_cap.ip_type = QDMA_LINUX_VERSAL_SOFT_IP;
    } else if (strstr(ip_type, "Versal Hard IP") != NULL) {
	info.dev_cap.ip_type = QDMA_LINUX_VERSAL_HARD_IP;
    } else if (strstr(ip_type, "EQDMA Soft IP") != NULL) {
	info.dev_cap.ip_type = EQDMA_LINUX_SOFT_IP;
    } else if (strstr(ip_type, "QDMA Soft IP") != NULL) {
	info.dev_cap.ip_type = QDMA_LINUX_SOFT_IP;
    } else {
	info.dev_cap.ip_type = QDMA_LINUX_NONE_IP;
    }

//	std::cout << ip_ver_buf;

	//TODO:Remove Debug prints
//	printf("num_pfs           = %d\n", info.dev_cap.num_pfs);
//	printf("num_qs            = %d\n",info.dev_cap.num_qs);
//	printf("flr_present       = %d\n",info.dev_cap.flr_present);
//	printf("st_en             = %d\n",info.dev_cap.st_en);
//	printf("mm_en             = %d\n",info.dev_cap.mm_en);
//	printf("mm_cmpt_en        = %d\n",info.dev_cap.mm_cmpt_en);
//	printf("mailbox_en        = %d\n",info.dev_cap.mailbox_en);
//	printf("mm_channel_max    = %d\n",info.dev_cap.mm_channel_max);
//	printf("qid2vec_ctx       = %d\n",info.dev_cap.qid2vec_ctx);
//	printf("cmpt_ovf_chk_dis  = %d\n",info.dev_cap.cmpt_ovf_chk_dis);
//	printf("mailbox_intr      = %d\n",info.dev_cap.mailbox_intr);
//	printf("sw_desc_64b       = %d\n",info.dev_cap.sw_desc_64b);
//	printf("cmpt_desc_64b     = %d\n",info.dev_cap.cmpt_desc_64b);
//	printf("dynamic_bar       = %d\n",info.dev_cap.dynamic_bar);
//	printf("legacy_intr       = %d\n",info.dev_cap.legacy_intr);
//	printf("cmpt_trig_c       = %d\n",info.dev_cap.cmpt_trig_count_timer);

	//std::cout <<"qbase_start = "<< info.qbase_start <<std::endl;
    return info;
}

unsigned instance_ext::add_queue(unsigned dev_id, unsigned q_id, unsigned num_q, queue::mode q_mode,
                   queue::direction q_dir, const queue_ext::config& qcfg, bool throw_err) {

    uint32_t q_flags = q_mode == queue_ext::mode::memory_mapped ? XNL_F_QMODE_MM : XNL_F_QMODE_ST;
    q_flags |= queue_dir_to_nl_q_flag(q_dir);

    auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
    cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
    cmd.add_attribute(XNL_ATTR_QIDX, q_id);
    cmd.add_attribute(XNL_ATTR_NUM_Q, num_q);
    cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
    qdma_socket.send_msg(cmd);

    auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    if (qdma_socket.has_error()) {
        throw std::runtime_error("Received error in QDMA socket!");
    }
    char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);
    if (not resp_str) {
        throw std::runtime_error("XNL_ATTR_GENMSG did not return a string");
    }

    //std::cout << resp_str << "\n";
    return 0;
}

unsigned instance_ext::remove_queue(unsigned dev_id, unsigned queue_id, queue_ext::direction q_dir, bool throw_err) {

    uint32_t q_flags = queue_dir_to_nl_q_flag(q_dir);

    auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DEL);
    cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
    cmd.add_attribute(XNL_ATTR_QIDX, queue_id);
    cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
    cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
    qdma_socket.send_msg(cmd);

    auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    if (qdma_socket.has_error()) {
        throw std::runtime_error("Received error in QDMA socket!");
    }
    char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);
    if (not resp_str) {
        throw std::runtime_error("XNL_ATTR_GENMSG did not return a string");
    }
    //std::cout << resp_str << "\n";    // TODO
    return 0;
}

unsigned instance_ext::start_queue(unsigned dev_id, unsigned queue_id, queue_ext::mode q_mode,
                              queue_ext::direction q_dir, const queue_ext::config& qcfg, bool throw_err) {

    uint32_t q_flags = queue_dir_to_nl_q_flag(q_dir);

    q_flags |= qcfg.desc_bypass ? XNL_F_DESC_BYPASS_EN : 0;
    q_flags |= qcfg.pfetch_bypass ? XNL_F_PFETCH_BYPASS_EN : 0;
    q_flags |= qcfg.prefetch ? XNL_F_PFETCH_EN : 0;
    q_flags |= qcfg.fetch_credit ? XNL_F_FETCH_CREDIT : 0;
    q_flags |= qcfg.cmpl_status_en ? XNL_F_CMPL_STATUS_EN : 0;
    q_flags |= qcfg.cmpl_status_acc_en ? XNL_F_CMPL_STATUS_ACC_EN : 0;
    q_flags |= qcfg.cmpl_status_pend_chk ? XNL_F_CMPL_STATUS_PEND_CHK : 0;
    q_flags |= qcfg.cmpl_status_desc_en ? XNL_F_CMPL_STATUS_DESC_EN : 0;
    q_flags |= qcfg.c2h_cmpl_intr_en ? XNL_F_C2H_CMPL_INTR_EN : 0;
    q_flags |= qcfg.c2h_udd_en ? XNL_F_CMPL_UDD_EN : 0;
    q_flags |= qcfg.c2h_ovf_chk_dis ? XNL_F_CMPT_OVF_CHK_DIS : 0;

    auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_START);
    cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
    cmd.add_attribute(XNL_ATTR_QIDX, queue_id);
    cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
    cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
    cmd.add_attribute(XNL_ATTR_QRNGSZ_IDX, qcfg.idx_rngsz);
    cmd.add_attribute(XNL_ATTR_C2H_BUFSZ_IDX, qcfg.idx_bufsz);
    cmd.add_attribute(XNL_ATTR_CMPT_TIMER_IDX, qcfg.idx_tmr);
    cmd.add_attribute(XNL_ATTR_CMPT_CNTR_IDX, qcfg.idx_cntr);
    cmd.add_attribute(XNL_ATTR_CMPT_TRIG_MODE, static_cast<uint32_t>(qcfg.trigmode));
    if (qcfg.sw_desc_sz == 3)
    	cmd.add_attribute(XNL_ATTR_SW_DESC_SIZE, static_cast<uint32_t>(qcfg.sw_desc_sz));

    if (((q_mode == queue_ext::mode::streaming) && (q_dir == queue_ext::direction::card_to_host)) ||
    	((q_mode == queue_ext::mode::memory_mapped) && (q_dir == queue_ext::direction::cmpt)))
        cmd.add_attribute(XNL_ATTR_CMPT_DESC_SIZE, static_cast<uint32_t>(qcfg.cmptsz));
   qdma_socket.send_msg(cmd);

    auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    if (qdma_socket.has_error()) {
        throw std::runtime_error("Received error in QDMA socket!");
    }
    char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);
    if (not resp_str) {
        throw std::runtime_error("XNL_ATTR_GENMSG did not return a string");
    }
    return 0;
}

unsigned instance_ext::stop_queue(unsigned dev_id, unsigned queue_id, queue_ext::direction q_dir, bool throw_err) {

    uint32_t q_flags = queue_dir_to_nl_q_flag(q_dir);

    auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_STOP);
    cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
    cmd.add_attribute(XNL_ATTR_QIDX, queue_id);
    cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
    cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
    qdma_socket.send_msg(cmd);

    auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    if (qdma_socket.has_error()) {
        throw std::runtime_error("Received error in QDMA socket!");
    }
    char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);
    if (not resp_str) {
        throw std::runtime_error("XNL_ATTR_GENMSG did not return a string");
    }
    return 0;
}

std::string instance_ext::dump_queue(unsigned dev_id, unsigned queue_id, queue_ext::direction q_dir) {

    uint32_t q_flags = queue_dir_to_nl_q_flag(q_dir);

    auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DUMP);
    cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
    cmd.add_attribute(XNL_ATTR_QIDX, queue_id);
    cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
    cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
    qdma_socket.send_msg(cmd);

    auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);
    if (not resp_str) {
        throw std::runtime_error("XNL_ATTR_GENMSG did not return a string");
    }
    return resp_str;
}

std::string instance_ext::dump_queue_desc(unsigned dev_id, unsigned queue_id, queue_ext::direction q_dir, bool sw_desc, unsigned desc_start, unsigned desc_end) {

    uint32_t q_flags = queue_dir_to_nl_q_flag(q_dir);

    if (sw_desc) {
    	auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DESC);
		cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
		cmd.add_attribute(XNL_ATTR_QIDX, queue_id);
		cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
		cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
		cmd.add_attribute(XNL_ATTR_RANGE_START, desc_start);
		cmd.add_attribute(XNL_ATTR_RANGE_END, desc_end);
		qdma_socket.send_msg(cmd);
    }
    else {
    	auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_CMPT);
		cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
		cmd.add_attribute(XNL_ATTR_QIDX, queue_id);
		cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
		cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
		cmd.add_attribute(XNL_ATTR_RANGE_START, desc_start);
		cmd.add_attribute(XNL_ATTR_RANGE_END, desc_end);
		qdma_socket.send_msg(cmd);
    }

    auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);
    if (not resp_str) {
        throw std::runtime_error("XNL_ATTR_GENMSG did not return a string");
    }
    return resp_str;
}

std::string instance_ext::read_rx_packet(unsigned dev_id, unsigned queue_id) {
    uint32_t q_flags = XNL_F_QDIR_C2H;

    auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_UDD);
    cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
    cmd.add_attribute(XNL_ATTR_QIDX, queue_id);
    cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
    cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
    qdma_socket.send_msg(cmd);

    auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);
    if (not resp_str) {
        throw std::runtime_error("XNL_ATTR_GENMSG did not return a string");
    }
    return resp_str;
}

uint32_t instance_ext::read_cmpt_data(unsigned dev_id, unsigned queue_id, queue_ext::direction q_dir, char *cmpt_data) {
    uint32_t q_flags = queue_dir_to_nl_q_flag(q_dir);

    auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_CMPT_READ);
    cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
    cmd.add_attribute(XNL_ATTR_QIDX, queue_id);
    cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
    qdma_socket.send_msg(cmd);

    auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);
    auto cmpt_strings = split(resp_str, '\n');
    auto num_entries = cmpt_strings.size();


    std::string temp_str = resp_str;
    temp_str.erase(std::remove(temp_str.begin(), temp_str.end(), ' '), temp_str.end());
    temp_str.erase(std::remove(temp_str.begin(), temp_str.end(), '\n'), temp_str.end());
    strncpy(cmpt_data, temp_str.c_str(), temp_str.size());


    if (not cmpt_data) {
        throw std::runtime_error("XNL_ATTR_GENMSG did not return a string");
    }

    return num_entries;
}

void instance_ext::get_global_csr(unsigned dev_id,  unsigned index, unsigned count, struct global_csr_conf &csr) {

    auto cmd = qdma_socket.prepare_msg(XNL_CMD_GLOBAL_CSR);
    cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
    cmd.add_attribute(XNL_ATTR_CSR_INDEX, index);
    cmd.add_attribute(XNL_ATTR_CSR_COUNT, count);

    qdma_socket.send_msg(cmd);
    auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    void *buff = resp.get_attrib<void *>(XNL_ATTR_GLOBAL_CSR);
    if (NULL == buff) {
        throw std::runtime_error("XNL_ATTR_GLOBAL_CSR did not return data");
    }

    memcpy((void *)&csr, buff, sizeof(struct global_csr_conf));

}

} // namespace qdma
