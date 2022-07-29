/*
 * qdma_test_env.hpp
 *
 *  Created on: Mar 1, 2018
 *      Author: alexande
 */

#ifndef TEST_QDMA_TEST_ENV_HPP_
#define TEST_QDMA_TEST_ENV_HPP_

#include <cstdint>
#include <vector>
#include <random>
#include <numeric>

#include "qdma_device.h"
#include "qdma_instance.h"
#include "qdma_queue_abs.h"

struct sys_setup_config {
	unsigned int multiple_apps;
	unsigned int master_pf;
	unsigned int num_pf;
	unsigned int *pf_qmax_cfg_en;
	unsigned int *pf_qmax_lst;
	unsigned int *pf_nvf_lst;
	unsigned int **vf_pf_qmax_lst;
	unsigned int qmaxvfs;
	unsigned int num_cards;
	unsigned int *pci_bus;
	unsigned int *pci_dev;
};

enum test_type {
	TEST_PF_VF = 0,
	TEST_VF = 1,
};

enum driver_idx {
	VF_IDX = 0,
	PF_IDX=1
};


extern int exec_cmd(char *cmd, char *cmdresp);
extern int dmactl_qadd(qdma::instance_ext::type devtype,uint32_t dev_id,
		uint32_t q_id, uint32_t numqs = 1,
		qdma::queue_ext::mode mode=qdma::queue_ext::mode::memory_mapped,
		qdma::queue_ext::direction dir=qdma::queue_ext::direction::both);
extern int dmactl_qdel(qdma::instance_ext::type devtype,uint32_t dev_id,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::direction dir=qdma::queue_ext::direction::both);





class test_env {
public:

	test_env() {
#ifdef TEST_VF_ALONE
	drivers.emplace_back(qdma::instance_ext::type::vf);
#else
	drivers.emplace_back(qdma::instance_ext::type::vf);
	drivers.emplace_back(qdma::instance_ext::type::pf);
#endif
    }

#ifdef LINUX
	void validate_ring_size(void) {
		char write_val[100] = {'\0'};
		char buf_cmd[200] = {'\0'};
		char rcv_buf[100] = {'\0'};
		char expected_val[100] = {'\0'};
		char orig[100] = {'\0'};
		int fp, ret = 0;
		unsigned short rng_sz_arr[16] = { /* making sure idx 2 corresponds to 256 ring size */
			0x100, 0x200, 0x400, 0x2000, 0x1000, 0x800, 0x400,
			0x200, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
		};

		snprintf(write_val, 100, "%u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u",
				rng_sz_arr[0], rng_sz_arr[1], rng_sz_arr[2], rng_sz_arr[3],
				rng_sz_arr[4], rng_sz_arr[5], rng_sz_arr[6], rng_sz_arr[7],
				rng_sz_arr[8], rng_sz_arr[9], rng_sz_arr[10], rng_sz_arr[11],
				rng_sz_arr[12], rng_sz_arr[13], rng_sz_arr[14], rng_sz_arr[15]);

		snprintf(expected_val, 100, "%u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u",
				rng_sz_arr[0], rng_sz_arr[1], rng_sz_arr[2], rng_sz_arr[3],
				rng_sz_arr[4], rng_sz_arr[5], rng_sz_arr[6], rng_sz_arr[7],
				rng_sz_arr[8], rng_sz_arr[9], rng_sz_arr[10], rng_sz_arr[11],
				rng_sz_arr[12], rng_sz_arr[13], rng_sz_arr[14], rng_sz_arr[15]);

		snprintf(orig, 100, "/sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/glbl_rng_sz",
				sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);

		fp = open(orig, O_RDONLY);
		if (fp < 0) {
			printf("Could not open %s\n", orig);
			exit(1);
		}

		memset(orig, '\0', 100);

		ret = read(fp, orig, 100);
		if (ret < 0) {
			printf("Error: Could not read the file\n");
			exit(1);
		}

		orig[ret - 1]='\0';

		snprintf(buf_cmd, 200, "echo \"%s\" > "
				"/sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/glbl_rng_sz",
				write_val, sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);

		system(buf_cmd);

		snprintf(rcv_buf, 100,
				"/sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/glbl_rng_sz",
				sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);

		fp = open(rcv_buf, O_RDONLY);
		if (fp < 0) {
			printf("Could not open %s\n", rcv_buf);
			exit(1);
		}

		memset(rcv_buf, '\0', 100);

		ret = read(fp, rcv_buf, 100);
		if (ret < 0) {
			printf("Error: Could not read the file\n");
			exit(1);
		}
		rcv_buf[ret - 1]='\0';

		if (memcmp(rcv_buf, expected_val, strlen(rcv_buf))) {
			printf("ring size values do not match\n actual - %s\n expected - %s\n",
			       rcv_buf, expected_val);
			exit(1);
		}
		close(fp);
		/* restore global ring size */
        memset(buf_cmd, '\0', 200);
		snprintf(buf_cmd, 200,
				"echo \"%s\" > /sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/glbl_rng_sz",
				orig, sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
		system(buf_cmd);
	}
	void validate_buf_size(void) {
		char buf_val[100] = {'\0'};
		char buf_cmd[200] = {'\0'};
		char rcv_buf[100] = {'\0'};
		char orig[100] = {'\0'};
		int fp, ret = 0;
		unsigned short buf_sz_arr[16] = {
			0x1000, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x1000,
			0x4000, 0x1000, 0x2000, 0x1000, 0x4000, 0x1000, 0x2000, 0x1000
		};
		snprintf(buf_val, 100, "%u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u",
				buf_sz_arr[0], buf_sz_arr[1], buf_sz_arr[2], buf_sz_arr[3],
				buf_sz_arr[4], buf_sz_arr[5], buf_sz_arr[6], buf_sz_arr[7],
				buf_sz_arr[8], buf_sz_arr[9], buf_sz_arr[10], buf_sz_arr[11],
				buf_sz_arr[12], buf_sz_arr[13], buf_sz_arr[14], buf_sz_arr[15]);
		snprintf(buf_cmd, 200, "echo \"%s\" > /sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/buf_sz",
				buf_val, sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
        snprintf(rcv_buf, 100, "/sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/buf_sz",
                sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
        snprintf(orig, 100, "/sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/buf_sz",
                sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
        fp = open(orig, O_RDONLY);
        if (fp < 0) {
            printf("Could not open %s\n", orig);
            exit(1);
        }
        memset(orig, '\0', 100);
        ret = read(fp, orig, 100);
        if (ret < 0) {
            printf("Error: Could not read the file\n");
            exit(1);
        }
		system(buf_cmd);
		fp = open(rcv_buf, O_RDONLY);
		if (fp < 0) {
			printf("Could not open %s\n", rcv_buf);
			exit(1);
		}
		memset(rcv_buf, '\0', 100);
		ret = read(fp, rcv_buf, 100);
		if (ret < 0) {
			printf("Error: Could not read the file\n");
			exit(1);
		}
		rcv_buf[ret - 1]='\0';
		if (memcmp(buf_val, rcv_buf, strlen(rcv_buf))) {
			printf("buf_sz size values do not match\n actual - %s\n expected - %s\n",
			       rcv_buf, buf_val);
			exit(1);
		}
		close(fp);
		/* restore default values */
		memset(buf_cmd, '\0', 200);
        snprintf(buf_cmd, 200, "echo \"%s\" > /sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/buf_sz",
                orig, sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
        system(buf_cmd);
	}
	void validate_timer_threshold(void) {
		char buf_val[100] = {'\0'};
		char buf_cmd[200] = {'\0'};
        char rcv_buf[100] = {'\0'};
        char orig[100] = {'\0'};
		int fp, ret = 0;
		unsigned char tmr_th_arr[16] = {
			16, 32, 64, 127, 32, 8, 3, 1,
			2, 3, 8, 16, 32, 64, 128, 192
		};

		snprintf(buf_val, 100, "%u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u",
			 tmr_th_arr[0], tmr_th_arr[1], tmr_th_arr[2], tmr_th_arr[3],
			 tmr_th_arr[4], tmr_th_arr[5], tmr_th_arr[6], tmr_th_arr[7],
			 tmr_th_arr[8], tmr_th_arr[9], tmr_th_arr[10], tmr_th_arr[11],
			 tmr_th_arr[12], tmr_th_arr[13], tmr_th_arr[14], tmr_th_arr[15]);
		snprintf(buf_cmd, 200, "echo \"%s\" > /sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/c2h_timer_cnt",
			 buf_val, sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
        snprintf(rcv_buf, 100, "/sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/c2h_timer_cnt",
             sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
        snprintf(orig, 100, "/sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/c2h_timer_cnt",
             sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
        fp = open(orig, O_RDONLY);
        if (fp < 0) {
            printf("Could not open %s\n", orig);
            exit(1);
        }
        memset(orig, '\0', 100);
        ret = read(fp, orig, 100);
        if (ret < 0) {
            printf("Error: Could not read the file\n");
            exit(1);
        }
		system(buf_cmd);
		fp = open(rcv_buf, O_RDONLY);
		if (fp < 0) {
			printf("Could not open %s\n", rcv_buf);
			exit(1);
		}
		memset(rcv_buf, '\0', 100);
		ret = read(fp, rcv_buf, 100);
		if (ret < 0) {
			printf("Error: Could not read the file\n");
			exit(1);
		}
		rcv_buf[ret - 1]='\0';
		if (memcmp(buf_val, rcv_buf, strlen(rcv_buf) - 3)) {
			printf("Timer threshold size values do not match\n actual - %s\n expected - %s\n",
					rcv_buf, buf_val);
			exit(1);
		}
		close(fp);
		/* restore default values */
        memset(buf_cmd, '\0', 200);
		snprintf(buf_cmd, 200, "echo \"%s\" > /sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/c2h_timer_cnt",
			 orig, sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
		system(buf_cmd);
	}
	void validate_counter_threshold(void) {
		char buf_val[100] = {'\0'};
		char buf_cmd[200] = {'\0'};
        char rcv_buf[100] = {'\0'};
        char orig[100] = {'\0'};
		int fp, ret = 0;
		unsigned char cntr_th_arr[16] = {
			1, 2, 4, 32, 16, 8, 64, 2,
			1, 1, 2, 8, 16, 32, 64, 128
		};

		snprintf(buf_val, 100, "%u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u",
			 cntr_th_arr[0], cntr_th_arr[1], cntr_th_arr[2], cntr_th_arr[3],
			 cntr_th_arr[4], cntr_th_arr[5], cntr_th_arr[6], cntr_th_arr[7],
			 cntr_th_arr[8], cntr_th_arr[9], cntr_th_arr[10], cntr_th_arr[11],
			 cntr_th_arr[12], cntr_th_arr[13], cntr_th_arr[14], cntr_th_arr[15]);
		snprintf(buf_cmd, 200, "echo \"%s\" > /sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/c2h_cnt_th",
			 buf_val, sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
        snprintf(rcv_buf, 100, "/sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/c2h_cnt_th",
             sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
        snprintf(orig, 100, "/sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/c2h_cnt_th",
             sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
        fp = open(orig, O_RDONLY);
        if (fp < 0) {
            printf("Could not open %s\n", orig);
            exit(1);
        }
        memset(orig, '\0', 100);
        ret = read(fp, orig, 100);
        if (ret < 0) {
            printf("Error: Could not read the file\n");
            exit(1);
        }
		system(buf_cmd);
		fp = open(rcv_buf, O_RDONLY);
		if (fp < 0) {
			printf("Could not open %s\n", rcv_buf);
			exit(1);
		}
		memset(rcv_buf, '\0', 100);
		ret = read(fp, rcv_buf, 100);
		if (ret < 0) {
			printf("Error: Could not read the file\n");
			exit(1);
		}
		rcv_buf[ret - 1]='\0';
		if (memcmp(buf_val, rcv_buf, strlen(rcv_buf) - 3)) {
			printf("Timer threshold size values do not match\n actual - %s\n expected - %s\n",
			       rcv_buf, buf_val);
			exit(1);
		}
		close(fp);
		memset(buf_cmd, '\0', 200);
		snprintf(buf_cmd, 200, "echo \"%s\" > /sys/bus/pci/devices/0000:%02x:%02x.%01x/qdma/c2h_cnt_th",
			 orig, sys_cfg.pci_bus[0], sys_cfg.pci_dev[0], sys_cfg.master_pf);
		system(buf_cmd);
	}
	void set_global_csr(void) {
		validate_ring_size();
		validate_buf_size();
		validate_timer_threshold();
		validate_counter_threshold();
	}
#endif

	void update() {
#ifdef _WIN32
        pfs = drivers[PF_IDX].get_devices();
#else
#ifdef TEST_VF_ALONE
	vfs = drivers[VF_IDX].get_devices();
	last_vf = drivers[VF_IDX].get_last_id();
#else
	pfs = drivers[PF_IDX].get_devices();
	last_pf = drivers[PF_IDX].get_last_id();
	vfs = drivers[VF_IDX].get_devices();
	last_vf = drivers[VF_IDX].get_last_id();
#endif
	random_seed = std::random_device()();
#ifdef DPDK
#else
#ifndef TEST_VF_ALONE
/* CSR Register update is not allowed, hence commented out */
#if 0
	if (sys_cfg.pci_bus[0] != 0)
		set_global_csr();
#endif
	drivers[PF_IDX].get_global_csr(pfs[sys_cfg.master_pf].dev_id, 0, 16, csr);
#endif

#endif
#endif
	}

#ifndef DPDK
		struct qdma::global_csr_conf csr;
#endif

	std::vector<qdma::instance_ext> drivers;
	std::vector<qdma::device> pfs;
	std::vector<qdma::device> vfs;

	uint32_t last_pf  = 0;
	uint32_t last_vf = 0;
	uint32_t random_seed = 0;

	struct sys_setup_config sys_cfg = {0,0,0,0,0,0,0,0,0,0,0};

	std::vector<qdma::device>& get_dev_list(qdma::instance_ext::type devtype){
		if (qdma::instance_ext::type::vf == devtype)
			return vfs;
		else
			return pfs;
	};

	qdma::instance_ext& get_drv_instance(qdma::instance_ext::type devtype){
		if (qdma::instance_ext::type::vf == devtype)
			return drivers[VF_IDX];
		else
			return drivers[PF_IDX];
	};

#ifdef DPDK
	struct rte_mempool *mpool = 0;
	int nb_buff = 0;
#endif
};

// Each PF maintains its qid's relative to itself.
// Thus if there are 2 PFs and each has 32 queues assigned, then:
// - PF0 sw_qid 0 = hw_qid 0
// - PF0 sw_qid 31 = hw_qid 31
// - PF1 sw_qid 0 = hw_qid 32
// - PF1 sw_qid 31 = hw_qid 63
#ifdef DPDK
inline unsigned get_hw_qid(unsigned vf_id, unsigned sw_qid) {
#else
inline unsigned get_hw_qid(unsigned vf_id, unsigned sw_qid,
								std::vector<qdma::device>& vfs) {
#endif
	// get base hw_qid for this pf
	uint32_t vf_hw_qid_base = 0;

#ifdef DPDK
	rte_pmd_qdma_get_queue_base(vf_id, &vf_hw_qid_base);
	return vf_hw_qid_base + sw_qid;
#else

	for(const auto& vf : vfs) {
		if (vf_id == vf.dev_id) {
			vf_hw_qid_base = vf.qbase_start;
			break;
		}
	}

    return vf_hw_qid_base + sw_qid;
#endif
}

#ifdef DPDK
inline const struct rte_pmd_qdma_dev_attributes * get_dev_capability(unsigned vf_id,
		std::vector<qdma::device>& vfs) {
	for (const auto& vf : vfs) {
		if (vf_id == vf.dev_id) {
			return &vf.dev_cap;
		}
	}
	return NULL;
}
#elif _WIN32
inline const struct qdma_dev_attributes *get_dev_capability(unsigned dev_id,
    std::vector<qdma::device>& pfs)
{
    for (const auto& pf : pfs) {
        if (dev_id == pf.dev_id) {
            return &pf.dev_cap;
        }
    }
    return NULL;
}
#else
inline const struct qdma_dev_attributes * get_dev_capability(unsigned vf_id,
			std::vector<qdma::device>& vfs) {
	for (const auto& vf : vfs) {
		if (vf_id == vf.dev_id) {
			return &vf.dev_cap;
		}
	}
	return NULL;
}
#endif

inline int get_device_type(unsigned vf_id,
			std::vector<qdma::device>& vfs) {
	for (const auto& vf : vfs) {
		if (vf_id == vf.dev_id) {
			return vf.dev_cap.device_type;
		}
	}

	return -1;
}

inline int get_ip_type(unsigned vf_id,
			std::vector<qdma::device>& vfs) {
	for (const auto& vf : vfs) {
		if (vf_id == vf.dev_id) {
			return vf.dev_cap.ip_type;
		}
	}

	return -1;
}


inline int validate_test_case(std::vector<qdma::device> &devlist,
		unsigned int dev_id, qdma::queue_ext::config qcfg) {

#ifdef DPDK
	const struct rte_pmd_qdma_dev_attributes *dev_attr =
			get_dev_capability(dev_id, devlist);
#else
	const struct qdma_dev_attributes *dev_attr =
			get_dev_capability(dev_id, devlist);
#endif

	if(qcfg.sw_desc_sz == ST_C2H_SW_DESC_SIZE_64B) {
		if(!dev_attr->sw_desc_64b) {
			printf("Invalid: sw_desc_64b\n");
			return -1;
		}
	}
	if(qcfg.c2h_ovf_chk_dis) {
		if(!dev_attr->cmpt_ovf_chk_dis) {
			printf("Invalid: cmpt_ovf_chk_dis\n");
			return -1;
		}
	}
	if(qcfg.cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B) {
		if(!dev_attr->cmpt_desc_64b) {
			printf("Invalid: cmpt_desc_64b\n");
			return -1;
		}
	}

	if(qcfg.trigmode == qdma::queue_ext::c2h_wrb_intr_trigmode::cntr_tmr) {
		if (!dev_attr->cmpt_trig_count_timer) {
			printf("Invalid: cmpt_trig_count_timer\n");
			return -1;
		}
	}

	return 0;
}

inline unsigned get_hw_qid(std::vector<qdma::device>::const_iterator vf_it,
		unsigned sw_qid, std::vector<qdma::device>& pfs,
		std::vector<qdma::device>& vfs) {

	auto sum_max_num_queues = [](unsigned sum, const qdma::device& dev) {
		return sum + dev.max_num_queues;
	};

	// sum of VF queues only (excluding this VF)
	unsigned vf_q_sum = std::accumulate(vfs.cbegin(), vf_it, 0u, sum_max_num_queues);
	std::cout << "\t vf_q_sum=" << vf_q_sum << "\n";

	// find the PF corresponding to this VF - FIXME assumes that all VFs are loaded for a given PF
	unsigned tmp = 0;
	const auto pf_it = std::find_if(pfs.begin(), pfs.end(), [&](const qdma::device& pf) -> bool {
		if (vf_q_sum >= tmp && (vf_q_sum <  tmp + pf.max_num_queues_vf)) {
			return true;
		} else {
			tmp += pf.max_num_queues_vf;
			return false;
		}
	});
	if(pf_it == pfs.end()) {
		throw std::runtime_error("could not find PF for this VF");
	}
	std::cout << "\t pf_idx=" << std::distance(pfs.begin(), pf_it) << "\n";

	// sum of all PF queues (including this PF)
	unsigned pf_q_sum = std::accumulate(pfs.begin(), pf_it, pf_it->max_num_queues, sum_max_num_queues);
	std::cout << "\t pf_q_sum=" << pf_q_sum << "\n";

	return pf_q_sum + vf_q_sum + sw_qid;
}

#endif /* TEST_QDMA_TEST_ENV_HPP_ */
