#include <algorithm>
#include <array>
#include <chrono>
#include <cstring>
#include <fstream>
#include <numeric>
#include <random>
#include <thread>
#include <string>
#include <sstream>

#include <xlnx_gtest_ext.h>
#include <xlnx_util.h>

#include "example_design_ctrl.h"
#include "qdma_device.h"
#include "test_env.h"

#define NUM_DEV_TYPES 2
// =============================== Test framework helpers ==========================================

extern test_env env; // in main.cpp

struct st_test_params {

    struct transfer {
        uint32_t pf = 0;
        uint32_t q = 1;
        uint32_t it = 0;
        uint32_t packet_size = 0;
        uint32_t num_packets = 0;
        qdma::device& qdev;

        transfer(uint32_t pf_id, uint32_t q_id, uint32_t iteration, uint32_t ps, uint32_t np, qdma::device& _qdev=env.pfs.front())
            : pf(pf_id), q(q_id), it(iteration), packet_size(ps), num_packets(np), qdev(_qdev) {}
    };

#ifdef DPDK
    struct fmap{
    	uint32_t dev_id =  0;
    	uint32_t qbase = 0;
    	uint32_t qmax = 0;

    	fmap(uint32_t pf_id, uint32_t q_base_id, uint32_t q_max_id)
    	: dev_id(pf_id), qbase(q_base_id), qmax(q_max_id){}
    };

    std::vector<fmap> pfs;
#endif

    std::vector<transfer> transfers;
    qdma::instance_ext::type devtype = qdma::instance_ext::type::pf;
    qdma::queue_ext::config qcfg;

    st_test_params() = default;
#ifdef DPDK
    st_test_params(std::vector<fmap>&& fmaps, std::vector<transfer>&& txs, qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
            : pfs(std::move(fmaps)), transfers(std::move(txs)), qcfg(_qcfg) {
        }
    st_test_params(std::vector<fmap>&& fmaps, std::vector<transfer>&& txs, qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf , qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
    	    : pfs(std::move(fmaps)), transfers(std::move(txs)), devtype(dev_type), qcfg(_qcfg) {
    	}
#else
    st_test_params(std::vector<transfer>&& txs, qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
        : transfers(std::move(txs)), qcfg(_qcfg) {

    }

    st_test_params(std::vector<transfer>&& txs, qdma::instance_ext::type dev_type, qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
	    : transfers(std::move(txs)), devtype(dev_type), qcfg(_qcfg) {
	}
#endif
};

void PrintTo(const st_test_params& tp, std::ostream* os) {

    //only print the ranges (first and last entry)
    const auto& txs = tp.transfers;
    if (!txs.empty()) {
		if (tp.devtype == qdma::instance_ext::type::vf)
			*os << "{ vfs=[";
		else
			*os << "{ pfs=[";
		*os << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.front().pf
			<< ":" << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.back().pf << "], ";
        *os << "queues=[" << txs.front().q << ":" << txs.back().q << "], ";
        *os << "iterations=" << txs.front().it << ", ";
        *os << "packet_size=" << txs.front().packet_size << ", ";
        *os << "num_packets=" << txs.front().num_packets << " }";
    }
}

// test group class for test cases which only apply to ST C2H
class qdma_st_c2h_test: public testing::TestWithParam<st_test_params> {
public:

    virtual void SetUp() override {
        rd_buffer.resize(array_size);
        expected.resize(array_size);
        std::iota(expected.begin(), expected.end(), static_cast<pattern_t>(0));    // 0, 1, 2, 3, 4 ...
    }

    virtual void TearDown() override {
    }

    void testbody_c2h_only();
    using pattern_t = example_design_ctrl::pattern_t;
    static const auto mode = qdma::queue_ext::mode::streaming;
    static const auto array_size = example_design_ctrl::bram_size / sizeof(pattern_t);
    aligned_vector<pattern_t> rd_buffer;
    aligned_vector<pattern_t> expected;
};

// test group class for tests cases which apply to all ST scenarios (H2C, C2H and loopback)
class qdma_st_test: public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }

    aligned_vector<pattern_t> wr_buffer;
};

class qdma_st_temp_test: public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }
    virtual void TearDown() override {

    }

    std::vector<qdma::queue_ext> queues;

    aligned_vector<pattern_t> wr_buffer;
};

class qdma_st_generic_test: public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }

    aligned_vector<pattern_t> wr_buffer;
};

class qdma_st_64b_test: public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }

    aligned_vector<pattern_t> wr_buffer;
};

class qdma_neg_st_ring_size_test: public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }

    aligned_vector<pattern_t> wr_buffer;
};

class qdma_neg_inv_buf_size_test: public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }

    aligned_vector<pattern_t> wr_buffer;
};

class qdma_neg_inv_tmr_cnt_test: public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }

    aligned_vector<pattern_t> wr_buffer;
};

class qdma_neg_add_inv_qid_test: public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }

    aligned_vector<pattern_t> wr_buffer;
};

class qdma_neg_start_inv_qid_test: public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }

    aligned_vector<pattern_t> wr_buffer;
};

class qdma_neg_stop_inv_qid_test: public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }

    aligned_vector<pattern_t> wr_buffer;
};

class qdma_neg_dump_inv_qid_test: public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }

    aligned_vector<pattern_t> wr_buffer;
};

class qdma_neg_proc_without_start_test: public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }

    aligned_vector<pattern_t> wr_buffer;
};

class qdma_neg_read_write_overflow : public qdma_st_c2h_test {
public:

    virtual void SetUp() override {
        qdma_st_c2h_test::SetUp();
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
    }

    aligned_vector<pattern_t> wr_buffer;
};

// ====================== Test Case Parameter Generators ===========================================
#if defined(DPDK) | defined(_WIN32)
static st_test_params st_negative_overflow_test(const uint32_t ring_size, const uint32_t tx_size,
		const uint32_t num_transfers, qdma::instance_ext::type dev_type=qdma::instance::type::pf) {
	std::vector<st_test_params::transfer> transfers;
	qdma::queue_ext::config qcfg;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

#ifdef DPDK
	std::vector<st_test_params::fmap> fmaps;
	uint32_t base = 0;


	fmaps.reserve(env.pfs.size());
#endif
	transfers.reserve(devlist.size());
	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
#ifdef DPDK
		fmaps.emplace_back(devlist[pf_id].dev_id, base, 1);
		base += 1;
#endif
		transfers.emplace_back(devlist[pf_id].dev_id, 0, 1, tx_size, num_transfers, devlist[pf_id]);

	}

	qcfg.idx_rngsz = ring_size;
#ifndef _WIN32
	qcfg.burst_size = 512;
#endif
	qcfg.idx_bufsz = 1024;
#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers), dev_type, qcfg };
#else
	return st_test_params { std::move(transfers), dev_type, qcfg };
#endif

}

static st_test_params multi_param_test(const uint32_t ring_size, const uint32_t idx_buf_size, const uint32_t packet_size,
                                  const uint32_t idx_timer_cnt, const uint32_t idx_cntr_th, qdma::queue_ext::c2h_wrb_intr_trigmode trig_mode=qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr,
								  qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {
    std::vector<st_test_params::transfer> transfers;
    // get the pf/vf device list based on dev_type
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
    qdma::queue_ext::config qcfg;

#ifdef DPDK
    std::vector<st_test_params::fmap> fmaps;
    uint32_t base = 0;


    fmaps.reserve(env.pfs.size());
#endif

    transfers.reserve(devlist.size());
    for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;

#ifdef DPDK
	    fmaps.emplace_back(devlist[pf_id].dev_id, base, 1);
	    base += 1;
#endif

		 transfers.emplace_back(devlist[pf_id].dev_id, 0, 1, packet_size, 512, devlist[pf_id]);
    }

    qcfg.idx_rngsz = ring_size;
	qcfg.idx_bufsz = idx_buf_size;
	qcfg.idx_cntr = idx_cntr_th;
	qcfg.idx_tmr = idx_timer_cnt;

	qcfg.trigmode  = trig_mode;
	// qcfg.trigmode  = qdma::queue_ext::c2h_wrb_intr_trigmode::usr_cnt;

    if(devlist.size()) {
        if (!((get_device_type(devlist[0].dev_id, devlist) == QDMA_DEVICE_VERSAL_CPM4) &&
			(get_ip_type(devlist[0].dev_id, devlist) == QDMA_VERSAL_HARD_IP))) {
			qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
        }
    }

#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers), dev_type , qcfg };
#else
	return st_test_params { std::move(transfers), dev_type, qcfg };
#endif
}
#endif

static st_test_params basic_dma_test(const std::vector<uint32_t> &num_qs_per_pf, qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf,
		const uint32_t tx_size = 4_kB) {
    std::vector<st_test_params::transfer> transfers;
    unsigned int num_transfer = 0;
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
    qdma::queue_ext::config qcfg;

#ifdef DPDK
    std::vector<st_test_params::fmap> fmaps;
    uint32_t base = 0;
#endif

    for (uint32_t pf_id = 0; pf_id < num_qs_per_pf.size(); pf_id++) {
        if (!devlist[pf_id].max_num_queues)
            continue;
        if (devlist[pf_id].max_num_queues < num_qs_per_pf[pf_id])
            continue;
        for (uint32_t qid = 0; qid < num_qs_per_pf[pf_id]; qid++) {
            num_transfer++;
        }
    }

#ifdef DPDK
    fmaps.reserve(num_qs_per_pf.size());
    for(uint32_t pf_id =0; pf_id < num_qs_per_pf.size(); pf_id++){
        if (!devlist[pf_id].max_num_queues)
            continue;
    	fmaps.emplace_back(devlist[pf_id].dev_id, base, num_qs_per_pf[pf_id]);
    	base += num_qs_per_pf[pf_id];
    }
#endif

    transfers.reserve(num_transfer);
    for (uint32_t pf_id = 0; pf_id < num_qs_per_pf.size(); pf_id++) {
        if (!devlist[pf_id].max_num_queues)
            continue;
        if (devlist[pf_id].max_num_queues < num_qs_per_pf[pf_id])
            continue;
        for (uint32_t qid = 0; qid < num_qs_per_pf[pf_id]; qid++) {
            transfers.emplace_back(devlist[pf_id].dev_id, qid, 1, tx_size, 1, devlist[pf_id]);
        }
    }
    if(devlist.size()) {
        if (!((get_device_type(devlist[0].dev_id, devlist) == QDMA_DEVICE_VERSAL_CPM4) &&
			(get_ip_type(devlist[0].dev_id, devlist) == QDMA_VERSAL_HARD_IP))) {
            qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
        }
    }

#ifdef DPDK
    return st_test_params { std::move(fmaps), std::move(transfers), dev_type, qcfg};
#else
    return st_test_params { std::move(transfers), dev_type, qcfg};
#endif
}


static st_test_params tx_param_test(const uint32_t packet_size,
				    qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf,
				    const uint32_t num_packets = 1,
				    const uint32_t nqueues = 1) {

    std::vector<st_test_params::transfer> transfers;
    qdma::queue_ext::config qcfg;

#ifdef DPDK
    std::vector<st_test_params::fmap> fmaps;
    uint32_t base = 0;

    fmaps.reserve(env.pfs.size());
#endif

	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	transfers.reserve(devlist.size());

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;
#ifdef DPDK
	    	fmaps.emplace_back(devlist[pf_id].dev_id, base, nqueues);
	    	base += nqueues;
#endif
			for (uint32_t q = 0; q < nqueues; q++ )
				transfers.emplace_back(devlist[pf_id].dev_id, q, 1, packet_size, num_packets, devlist[pf_id]);
    }

    if(devlist.size()) {
        if (!((get_device_type(devlist[0].dev_id, devlist) == QDMA_DEVICE_VERSAL_CPM4) &&
			(get_ip_type(devlist[0].dev_id, devlist) == QDMA_VERSAL_HARD_IP))) {
			qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
        }
    }

#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers), dev_type, qcfg};
#else
	return st_test_params { std::move(transfers), dev_type, qcfg};
#endif
}

static st_test_params ring_size_test(const uint32_t ring_size, const uint32_t packet_size,
                                  const uint32_t num_transfers, qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {
    std::vector<st_test_params::transfer> transfers;
    // get the pf/vf device list based on dev_type
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
    qdma::queue_ext::config qcfg;

#ifdef DPDK
    std::vector<st_test_params::fmap> fmaps;
    uint32_t base = 0;


    fmaps.reserve(env.pfs.size());
#endif

    transfers.reserve(devlist.size());
    for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;

#ifdef DPDK
	    fmaps.emplace_back(devlist[pf_id].dev_id, base, 1);
	    base += 1;
#endif

		 transfers.emplace_back(devlist[pf_id].dev_id, 0, num_transfers, packet_size, 1, devlist[pf_id]);
    }

    qcfg.idx_rngsz = ring_size;

    if(devlist.size()) {
        if (!((get_device_type(devlist[0].dev_id, devlist) == QDMA_DEVICE_VERSAL_CPM4) &&
			(get_ip_type(devlist[0].dev_id, devlist) == QDMA_VERSAL_HARD_IP))) {
			qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
        }
    }

#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers), dev_type , qcfg };
#else
	return st_test_params { std::move(transfers), dev_type, qcfg };
#endif
}

static st_test_params tmr_cnt_test(const uint32_t idx_timer_cnt,
		const uint32_t packet_size, const uint32_t num_transfers,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {
	std::vector<st_test_params::transfer> transfers;
	qdma::queue_ext::config qcfg;

#ifdef DPDK
	std::vector<st_test_params::fmap> fmaps;
	uint32_t base = 0;

	fmaps.reserve(env.pfs.size());
#endif
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	std::default_random_engine rne((unsigned int)time(0));
	transfers.reserve(devlist.size());
	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;

		std::uniform_int_distribution<uint32_t> rng_q(0, devlist[pf_id].max_num_queues - 1);    // queue
		const auto qid = rng_q(rne);
#ifdef DPDK
		fmaps.emplace_back(devlist[pf_id].dev_id, base, devlist[pf_id].max_num_queues );
		base += devlist[pf_id].max_num_queues;
#endif
		transfers.emplace_back(devlist[pf_id].dev_id, qid, num_transfers, packet_size, 1, devlist[pf_id]);
	}

	qcfg.idx_tmr = idx_timer_cnt;
	qcfg.trigmode  = qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr;

#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers),dev_type, qcfg};
#else
	return st_test_params { std::move(transfers), dev_type, qcfg };
#endif
}

static st_test_params cntr_th_test(const uint32_t idx_cntr_th,
		const uint32_t packet_size, const uint32_t num_pkts,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {
	std::vector<st_test_params::transfer> transfers;
	qdma::queue_ext::config qcfg;
#ifdef DPDK
	std::vector<st_test_params::fmap> fmaps;
	uint32_t base = 0;

	fmaps.reserve(env.pfs.size());
#endif

	//get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	std::default_random_engine rne((unsigned int)time(0));
	transfers.reserve(devlist.size());
	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;

		std::uniform_int_distribution<uint32_t> rng_q(0, devlist[pf_id].max_num_queues - 1);    // queue
		const auto qid = rng_q(rne);
#ifdef DPDK
		fmaps.emplace_back(devlist[pf_id].dev_id, base, devlist[pf_id].max_num_queues );
		base += devlist[pf_id].max_num_queues;
#endif
		transfers.emplace_back(devlist[pf_id].dev_id, qid, 1, packet_size, num_pkts, devlist[pf_id]);

	}

	qcfg.idx_cntr = idx_cntr_th;
	qcfg.trigmode  = qdma::queue_ext::c2h_wrb_intr_trigmode::usr_cnt;

#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers),dev_type, qcfg};
#else
	return st_test_params { std::move(transfers), dev_type, qcfg };
#endif
}

static st_test_params buf_size_test(const uint32_t idx_buf_size,
		const uint32_t packet_size, const uint32_t num_transfers,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {


	std::vector<st_test_params::transfer> transfers;
	qdma::queue_ext::config qcfg;

#ifdef DPDK
	std::vector<st_test_params::fmap> fmaps;
	uint32_t base = 0;

	fmaps.reserve(env.pfs.size());
#endif

	//get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	std::default_random_engine rne((unsigned int)time(0));
	transfers.reserve(devlist.size());
	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;

		std::uniform_int_distribution<uint32_t> rng_q(0, devlist[pf_id].max_num_queues - 1);    // queue
		const auto qid = rng_q(rne);
#ifdef DPDK
		fmaps.emplace_back(devlist[pf_id].dev_id, base, devlist[pf_id].max_num_queues );
		base += devlist[pf_id].max_num_queues;
#endif
		transfers.emplace_back(devlist[pf_id].dev_id, qid, num_transfers, packet_size, 1, devlist[pf_id]);
	}

	if(devlist.size()) {
        if (!((get_device_type(devlist[0].dev_id, devlist) == QDMA_DEVICE_VERSAL_CPM4) &&
			(get_ip_type(devlist[0].dev_id, devlist) == QDMA_VERSAL_HARD_IP))) {
			qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
        }
	}


	qcfg.idx_bufsz = idx_buf_size;

#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers),dev_type, qcfg};
#else
	return st_test_params { std::move(transfers), dev_type, qcfg };
#endif
}

static st_test_params cache_bypass_test(const uint32_t packet_size, bool prefetch_en = false,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf, const uint32_t num_packets = 1) {

	std::vector<st_test_params::transfer> transfers;
#ifdef DPDK
	std::vector<st_test_params::fmap> fmaps;
	uint32_t base = 0;

	fmaps.reserve(env.pfs.size());
#endif
	qdma::queue_ext::config qcfg;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	std::default_random_engine rne((unsigned int)time(0));
    transfers.reserve(devlist.size());
    for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;
    	std::uniform_int_distribution<uint32_t> rng_q(0, devlist[pf_id].max_num_queues - 1);    // queue
		const auto qid = rng_q(rne);
#ifdef DPDK
		fmaps.emplace_back(devlist[pf_id].dev_id, base, devlist[pf_id].max_num_queues );
		base += devlist[pf_id].max_num_queues;
#endif
		transfers.emplace_back(devlist[pf_id].dev_id, qid, 10, packet_size, num_packets, devlist[pf_id]);
	}

    if(devlist.size()) {
        if (!((get_device_type(devlist[0].dev_id, devlist) == QDMA_DEVICE_VERSAL_CPM4) &&
			(get_ip_type(devlist[0].dev_id, devlist) == QDMA_VERSAL_HARD_IP))) {
            qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
        }
    }
	qcfg.desc_bypass = true;
	qcfg.prefetch = prefetch_en;

#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers),dev_type, qcfg};
#else
	return st_test_params { std::move(transfers), dev_type, qcfg };
#endif

}

static st_test_params desc_pfetch_test(const uint32_t packet_size, qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf, const uint32_t num_packets = 1) {

	std::vector<st_test_params::transfer> transfers;

#ifdef DPDK
	std::vector<st_test_params::fmap> fmaps;
	uint32_t base = 0;

	fmaps.reserve(env.pfs.size());
#endif
	qdma::queue_ext::config qcfg;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	std::default_random_engine rne((unsigned int)time(0));

    transfers.reserve(devlist.size());
    for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;

#ifdef DPDK
		fmaps.emplace_back(devlist[pf_id].dev_id, base, devlist[pf_id].max_num_queues);
		base += devlist[pf_id].max_num_queues;
#endif

		std::uniform_int_distribution<uint32_t> rng_q(0, devlist[pf_id].max_num_queues - 1);    // queue
		const auto qid = rng_q(rne);

		transfers.emplace_back(devlist[pf_id].dev_id, qid, 10, packet_size, num_packets, devlist[pf_id]);
	}

    if(devlist.size()) {
        if (!((get_device_type(devlist[0].dev_id, devlist) == QDMA_DEVICE_VERSAL_CPM4) &&
			(get_ip_type(devlist[0].dev_id, devlist) == QDMA_VERSAL_HARD_IP))) {
            qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
        }
    }
	qcfg.prefetch = true;

#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers), dev_type,  qcfg};
#else
	return st_test_params { std::move(transfers), dev_type, qcfg };
#endif

}

static st_test_params ovf_chk_dis_test(const uint16_t idx_ring_size, uint32_t numqs,
									const uint32_t packet_size,
                                  const uint32_t num_transfers, const uint32_t num_packets, qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {
    std::vector<st_test_params::transfer> transfers;
#ifdef DPDK
	std::vector<st_test_params::fmap> fmaps;
	uint32_t base = 0;

	fmaps.reserve(env.pfs.size());
#endif
    // get the pf/vf device list based on dev_type
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
    qdma::queue_ext::config qcfg;

    std::default_random_engine rne(env.random_seed);
    transfers.reserve(devlist.size() * numqs);
    for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;
		if (numqs > devlist[pf_id].max_num_queues)
			numqs = devlist[pf_id].max_num_queues;
#ifdef DPDK
		fmaps.emplace_back(devlist[pf_id].dev_id, base, devlist[pf_id].max_num_queues);
		base += devlist[pf_id].max_num_queues;
#endif
		for (uint32_t i = 0; i < numqs; i++) {
			std::uniform_int_distribution<uint32_t> rng_q(0, devlist[pf_id].max_num_queues - 1);    // queue
			const auto qid = rng_q(rne);
			transfers.emplace_back(devlist[pf_id].dev_id, qid, num_transfers, packet_size, num_packets, devlist[pf_id]);
		}
    }

	if(devlist.size()) {
        if (!((get_device_type(devlist[0].dev_id, devlist) == QDMA_DEVICE_VERSAL_CPM4) &&
			(get_ip_type(devlist[0].dev_id, devlist) == QDMA_VERSAL_HARD_IP))) {
			qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
        }
	}

	qcfg.idx_rngsz = idx_ring_size;
	qcfg.c2h_ovf_chk_dis = true;

#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers), dev_type,  qcfg};
#else
	return st_test_params { std::move(transfers), dev_type, qcfg };
#endif
}

static st_test_params completion_entry_size(const xnl_st_c2h_cmpt_desc_size cmptsz,
					    const uint32_t packet_size,
					    qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {
    std::vector<st_test_params::transfer> transfers;
    qdma::queue_ext::config qcfg;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

#ifdef DPDK
	std::vector<st_test_params::fmap> fmaps;
	uint32_t base = 0;

	fmaps.reserve(env.pfs.size());
#endif

    transfers.reserve(devlist.size());
    for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
#ifdef DPDK
		fmaps.emplace_back(devlist[pf_id].dev_id, base, 1);
		base += 1;
#endif
        transfers.emplace_back(devlist[pf_id].dev_id, 0, 1, packet_size, 1, devlist[pf_id]);
    }

    if(devlist.size()) {
        if (!((get_device_type(devlist[0].dev_id, devlist) == QDMA_DEVICE_VERSAL_CPM4) &&
			(get_ip_type(devlist[0].dev_id, devlist) == QDMA_VERSAL_HARD_IP))) {
			qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
        }
    }
	qcfg.cmptsz = cmptsz;

#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers), dev_type, qcfg};
#else
	return st_test_params { std::move(transfers), dev_type, qcfg };
#endif
}

static st_test_params simple_bypass_test(const uint32_t packet_size, bool prefetch_en = false,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf, const uint32_t num_packets = 1) {

    std::vector<st_test_params::transfer> transfers;
    qdma::queue_ext::config qcfg;

	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

    std::default_random_engine rne((unsigned int)time(0));
#ifdef DPDK
	std::vector<st_test_params::fmap> fmaps;
	uint32_t base = 0;

	fmaps.reserve(env.pfs.size());
#endif

    transfers.reserve(devlist.size());
    for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}

		std::uniform_int_distribution<uint32_t> rng_q(0, devlist[pf_id].max_num_queues - 1);    // queue
		const auto qid = rng_q(rne);
#ifdef DPDK
		fmaps.emplace_back(devlist[pf_id].dev_id, base, devlist[pf_id].max_num_queues);
		base += devlist[pf_id].max_num_queues;
#endif
		transfers.emplace_back(devlist[pf_id].dev_id, qid, 10, packet_size, num_packets, devlist[pf_id]);
	}

	if(devlist.size()) {
        if (!((get_device_type(devlist[0].dev_id, devlist) == QDMA_DEVICE_VERSAL_CPM4) &&
			(get_ip_type(devlist[0].dev_id, devlist) == QDMA_VERSAL_HARD_IP))) {
			qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
        }
	}

    qcfg.desc_bypass = true;
    qcfg.pfetch_bypass = true;
    qcfg.prefetch = prefetch_en;
#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers), dev_type, qcfg};
#else
	return st_test_params { std::move(transfers), dev_type, qcfg };
#endif
}

static std::vector<st_test_params> randomized_tests(const uint32_t seed,
        const uint32_t num_tests, qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<st_test_params> tp;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
    // setup random number generators
    std::default_random_engine rne(seed);
    std::uniform_int_distribution<uint32_t> rng_pf(0, (uint32_t)devlist.size() - 1);    // pf
    std::uniform_int_distribution<uint32_t> rng_it(1, 1000);    // iterations
    std::uniform_int_distribution<uint32_t> rng_ps(2, 4_kB);    // packet size
    std::uniform_int_distribution<uint32_t> rng_np(1, 32);    // num packets

    for (uint32_t i = 0; i < num_tests; i++) {

		if (!devlist.size())
			continue;

        const auto pf = rng_pf(rne);
	if (!devlist[pf].max_num_queues)
		continue;

#ifdef DPDK
		std::vector<st_test_params::fmap> fmaps;
		uint32_t base = 0;
		fmaps.reserve(devlist.size());

		for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
				if (!devlist[pf_id].max_num_queues) {
					continue;
				}
				fmaps.emplace_back(devlist[pf_id].dev_id, base,devlist[pf_id].max_num_queues);
				base += devlist[pf_id].max_num_queues;
		}
#endif

	std::uniform_int_distribution<uint32_t> rng_q(0, devlist[pf].max_num_queues - 1);    // queue
        const auto qid = rng_q(rne);
        const auto num_transfers = rng_it(rne);
        const auto packet_size = rng_ps(rne) & ~1u; // mask LSB to ensure packet_size is always even
        const auto num_packets = rng_np(rne);
        qdma::queue_ext::config qcfg;

        std::vector<st_test_params::transfer> transfers;
        transfers.emplace_back(devlist[pf].dev_id, qid, num_transfers, packet_size, num_packets, devlist[pf]);

        if(devlist.size()) {
            if (!((get_device_type(devlist[0].dev_id, devlist) == QDMA_DEVICE_VERSAL_CPM4) &&
			(get_ip_type(devlist[0].dev_id, devlist) == QDMA_VERSAL_HARD_IP))) {
                qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
            }
        }

#ifdef DPDK
       tp.emplace_back(std::move(fmaps), std::move(transfers), dev_type, qcfg);
#else
       tp.emplace_back(std::move(transfers), dev_type, qcfg);
#endif
    }

    return tp;
}
// ====================== Test Cases (Fixtures) ====================================================

//Perform queue operations ( open and close) on all the functions
//for all the queues
TEST_F(qdma_st_test, ST001_queues_open_close) {
    const auto mode = qdma::queue_ext::mode::streaming;
    const auto dir = qdma::queue_ext::direction::both;
    qdma::queue_ext::config qcfg;
    qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf;
    qdma::instance_ext &drv = env.get_drv_instance(dev_type);
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

#ifdef DPDK
    struct rte_eth_conf	    port_conf;
    memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
    for (uint32_t func = 0; func < devlist.size(); func++) {
        auto& qdev = devlist[func];
        if (!devlist[func].max_num_queues)
            continue;
        try{
            rte_eth_dev_configure(devlist[func].dev_id, qdev.max_num_queues, qdev.max_num_queues, &port_conf);
        } catch (const std::exception& e){
            FAIL() << "Cannot configure port %d"<< devlist[func].dev_id << e.what();
        }
    }
#endif

    for (uint32_t func = 0; func < devlist.size(); func++) {
        if (!devlist[func].max_num_queues) {
			continue;
        }
        for (uint32_t i = 0; i < devlist[func].max_num_queues; i++) {
			EXPECT_NO_THROW(
				qdma::queue_ext h2c_q(drv, devlist[func].dev_id, i, mode, dir, qcfg)
			)<< "failed to open queue" << devlist[func].dev_id << "_q" << i;
        }
    }
#ifdef DPDK
    for (uint32_t func = 0; func < devlist.size(); func++) {
		if (!devlist[func].max_num_queues)
		    continue;
		rte_pmd_qdma_dev_close(devlist[func].dev_id);
    }
#endif
}

//Perform queue operations ( open and close) on all the functions
//for all the queues
TEST_F(qdma_st_test, VF_ST001_queues_open_close) {
    const auto mode = qdma::queue_ext::mode::streaming;
    const auto dir = qdma::queue_ext::direction::both;
    qdma::queue_ext::config qcfg;
    qdma::instance_ext::type dev_type = qdma::instance_ext::type::vf;
    qdma::instance_ext &drv = env.get_drv_instance(dev_type);
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

#ifdef DPDK
    struct rte_eth_conf	    port_conf;
    memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
    for (uint32_t func = 0; func < devlist.size(); func++) {
        auto& qdev = devlist[func];
        if (!devlist[func].max_num_queues)
            continue;
        try{
            rte_eth_dev_configure(devlist[func].dev_id, qdev.max_num_queues, qdev.max_num_queues, &port_conf);
        } catch (const std::exception& e){
            FAIL() << "Cannot configure port %d"<< devlist[func].dev_id << e.what();
        }
    }
#endif

    for (uint32_t func = 0; func < devlist.size(); func++) {
        if (!devlist[func].max_num_queues) {
			continue;
        }
        for (uint32_t i = 0; i < devlist[func].max_num_queues; i++) {
			EXPECT_NO_THROW(
				qdma::queue_ext h2c_q(drv, devlist[func].dev_id, i, mode, dir, qcfg)
			)<< "failed to open queue" << devlist[func].dev_id << "_q" << i;
        }
    }
#ifdef DPDK
    for (uint32_t func = 0; func < devlist.size(); func++) {
		if (!devlist[func].max_num_queues)
		    continue;
		rte_pmd_qdma_dev_close(devlist[func].dev_id);
    }
#endif
}

// ====================== Test Cases (Parameterized) ===============================================
#ifdef DPDK
TEST_P(qdma_neg_st_ring_size_test, h2c_c2h) {

	const auto& tp = GetParam();
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for(const auto& pf : tp.pfs) {
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try{
			rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
		} catch (const std::exception& e){
			FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
		}
	}
#endif

	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));
		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}

#ifdef DPDK
		struct rte_mempool			*mbuf_pool;
		struct rte_eth_txconf		tx_conf;
		struct rte_eth_rxconf		rx_conf;
		int							ret;
		char	mem_pool[RTE_MEMPOOL_NAMESIZE];
		enum rte_pmd_qdma_queue_mode_t queue_mode = RTE_PMD_QDMA_STREAMING_MODE;
		uint32_t		nb_buff;
		int test_status = 0;

		/** Mbuf packet pool **/
		nb_buff = ((tp.qcfg.idx_rngsz));

		nb_buff += NUM_RX_PKTS;

		/* Configure mbuf packet pool with minimum 2K size */
		nb_buff = RTE_MAX(nb_buff, (RTE_MEMPOOL_CACHE_MAX_SIZE * 2.5));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());
		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for h2c-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());

		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for c2h-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		if ((mbuf_pool = rte_mempool_lookup(mem_pool)) == NULL)
			throw std::runtime_error("add_queue: Could not find mempool with name:");
		memset(&tx_conf, 0x0, sizeof(struct rte_eth_txconf));
		memset(&rx_conf, 0x0, sizeof(struct rte_eth_rxconf));

		ret = rte_pmd_qdma_set_queue_mode(tx.pf, tx.q, queue_mode);
		if(ret < 0)
		throw std::runtime_error("rte_pmd_qdma_set_queue_mode  failed");

		tx_conf.tx_deferred_start = 1;

		ret = rte_eth_tx_queue_setup(tx.pf, tx.q, tp.qcfg.idx_rngsz, 0,
					&tx_conf);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_eth_tx_queue_setup failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
		}
		/* Update the threshold in rxconf */
		rx_conf.rx_thresh.wthresh = tp.qcfg.idx_cntr;

		ret = rte_eth_rx_queue_setup(tx.pf, tx.q, tp.qcfg.idx_rngsz, 0,
						&rx_conf, mbuf_pool);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_eth_rx_queue_setup failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
			// FAIL();
		}
		EXPECT_EQ(0, test_status) << "Negative test case is failed!\n";

		//freeing up memory
		struct rte_mempool *mp;
		int loop_cnt;
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}

		if (mp != NULL)
			rte_mempool_free(mp);
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}
		if (mp != NULL)
			rte_mempool_free(mp);
#endif

	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}

TEST_P(qdma_neg_inv_buf_size_test, h2c_c2h) {

	const auto& tp = GetParam();
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for(const auto& pf : tp.pfs) {
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try{
			rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
		} catch (const std::exception& e){
			FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
		}
	}
#endif

	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));
		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}

#ifdef DPDK
		struct rte_mempool			*mbuf_pool;
		struct rte_eth_rxconf		rx_conf;
		int							ret;
		char	mem_pool[RTE_MEMPOOL_NAMESIZE];
		enum rte_pmd_qdma_queue_mode_t queue_mode = RTE_PMD_QDMA_STREAMING_MODE;
		uint32_t		nb_buff;
		int test_status = 0;

		/** Mbuf packet pool **/
		nb_buff = ((tp.qcfg.idx_rngsz));

		nb_buff += NUM_RX_PKTS;

		/* Configure mbuf packet pool with minimum 2K size */
		nb_buff = RTE_MAX(nb_buff, (RTE_MEMPOOL_CACHE_MAX_SIZE * 2.5));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());

		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for c2h-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		if ((mbuf_pool = rte_mempool_lookup(mem_pool)) == NULL)
			throw std::runtime_error("add_queue: Could not find mempool with name:");
		memset(&rx_conf, 0x0, sizeof(struct rte_eth_rxconf));

		ret = rte_pmd_qdma_set_queue_mode(tx.pf, tx.q, queue_mode);
		if(ret < 0)
		throw std::runtime_error("rte_pmd_qdma_set_queue_mode  failed");

		/* Update the threshold in rxconf */
		rx_conf.rx_thresh.wthresh = tp.qcfg.idx_cntr;

		ret = rte_eth_rx_queue_setup(tx.pf, tx.q, tp.qcfg.idx_rngsz, 0,
						&rx_conf, mbuf_pool);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_eth_rx_queue_setup failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
			// FAIL();
		}
		EXPECT_EQ(0, test_status) << "Negative test case is failed!\n";

		//freeing up memory
		struct rte_mempool *mp;
		int loop_cnt;
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}

		if (mp != NULL)
			rte_mempool_free(mp);
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}
		if (mp != NULL)
			rte_mempool_free(mp);
#endif

	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}

TEST_P(qdma_neg_inv_tmr_cnt_test, h2c_c2h) {

	const auto& tp = GetParam();
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for(const auto& pf : tp.pfs) {
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try{
			rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
		} catch (const std::exception& e){
			FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
		}
	}
#endif

	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));
		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}

#ifdef DPDK
		struct rte_mempool			*mbuf_pool;
		struct rte_eth_txconf		tx_conf;
		struct rte_eth_rxconf		rx_conf;
		int							ret;
		char	mem_pool[RTE_MEMPOOL_NAMESIZE];
		enum rte_pmd_qdma_queue_mode_t queue_mode = RTE_PMD_QDMA_STREAMING_MODE;
		uint32_t		nb_buff;
		int test_status = 0;

		/** Mbuf packet pool **/
		nb_buff = ((tp.qcfg.idx_rngsz));

		nb_buff += NUM_RX_PKTS;

		/* Configure mbuf packet pool with minimum 2K size */
		nb_buff = RTE_MAX(nb_buff, (RTE_MEMPOOL_CACHE_MAX_SIZE * 2.5));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());
		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for h2c-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());

		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for c2h-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		if ((mbuf_pool = rte_mempool_lookup(mem_pool)) == NULL)
			throw std::runtime_error("add_queue: Could not find mempool with name:");
		memset(&tx_conf, 0x0, sizeof(struct rte_eth_txconf));
		memset(&rx_conf, 0x0, sizeof(struct rte_eth_rxconf));

		ret = rte_pmd_qdma_set_queue_mode(tx.pf, tx.q, queue_mode);
		if(ret < 0)
		throw std::runtime_error("rte_pmd_qdma_set_queue_mode  failed");

		ret = rte_pmd_qdma_set_cmpt_trigger_mode(tx.pf, tx.q, (rte_pmd_qdma_tigger_mode_t)tp.qcfg.trigmode);
		if(ret < 0)
			throw std::runtime_error("rte_pmd_qdma_set_cmpt_trigger_mode failed");
		ret = rte_pmd_qdma_set_cmpt_timer(tx.pf, tx.q, tp.qcfg.idx_tmr);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_pmd_qdma_set_cmpt_timer failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
		}

		EXPECT_EQ(0, test_status) << "Negative test case is failed!\n";

		//freeing up memory
		struct rte_mempool *mp;
		int loop_cnt;
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}

		if (mp != NULL)
			rte_mempool_free(mp);
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}
		if (mp != NULL)
			rte_mempool_free(mp);
#endif

	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}

TEST_P(qdma_neg_add_inv_qid_test, h2c_c2h) {

	const auto& tp = GetParam();
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for(const auto& pf : tp.pfs) {
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try{
			rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
		} catch (const std::exception& e){
			FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
		}
	}
#endif

	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));
		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}

#ifdef DPDK
		struct rte_mempool			*mbuf_pool;
		struct rte_eth_txconf		tx_conf;
		struct rte_eth_rxconf		rx_conf;
		int							ret;
		char	mem_pool[RTE_MEMPOOL_NAMESIZE];
		enum rte_pmd_qdma_queue_mode_t queue_mode = RTE_PMD_QDMA_STREAMING_MODE;
		uint32_t		nb_buff;
		int test_status = 0;

		/** Mbuf packet pool **/
		nb_buff = ((tp.qcfg.idx_rngsz));

		nb_buff += NUM_RX_PKTS;

		/* Configure mbuf packet pool with minimum 2K size */
		nb_buff = RTE_MAX(nb_buff, (RTE_MEMPOOL_CACHE_MAX_SIZE * 2.5));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());
		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for h2c-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());

		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for c2h-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		if ((mbuf_pool = rte_mempool_lookup(mem_pool)) == NULL)
			throw std::runtime_error("add_queue: Could not find mempool with name:");
		memset(&tx_conf, 0x0, sizeof(struct rte_eth_txconf));
		memset(&rx_conf, 0x0, sizeof(struct rte_eth_rxconf));

		ret = rte_pmd_qdma_set_queue_mode(tx.pf, tx.q, queue_mode);
		if(ret < 0)
		throw std::runtime_error("rte_pmd_qdma_set_queue_mode  failed");

		tx_conf.tx_deferred_start = 1;

		ret = rte_eth_tx_queue_setup(tx.pf, 65535, tp.qcfg.idx_rngsz, 0,
					&tx_conf);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_eth_tx_queue_setup failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
		}
		/* Update the threshold in rxconf */
		rx_conf.rx_thresh.wthresh = tp.qcfg.idx_cntr;

		ret = rte_eth_rx_queue_setup(tx.pf, 65535, tp.qcfg.idx_rngsz, 0,
						&rx_conf, mbuf_pool);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_eth_rx_queue_setup failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
			// FAIL();
		}
		EXPECT_EQ(0, test_status) << "Negative test case is failed!\n";

		//freeing up memory
		struct rte_mempool *mp;
		int loop_cnt;
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}

		if (mp != NULL)
			rte_mempool_free(mp);
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}
		if (mp != NULL)
			rte_mempool_free(mp);
#endif

	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}

TEST_P(qdma_neg_start_inv_qid_test, h2c_c2h) {

	const auto& tp = GetParam();
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for(const auto& pf : tp.pfs) {
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try{
			rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
		} catch (const std::exception& e){
			FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
		}
	}
#endif

	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));
		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}

#ifdef DPDK
		struct rte_mempool			*mbuf_pool;
		struct rte_eth_txconf		tx_conf;
		struct rte_eth_rxconf		rx_conf;
		int							ret;
		char	mem_pool[RTE_MEMPOOL_NAMESIZE];
		enum rte_pmd_qdma_queue_mode_t queue_mode = RTE_PMD_QDMA_STREAMING_MODE;
		uint32_t		nb_buff;
		int test_status = 0;

		/** Mbuf packet pool **/
		nb_buff = ((tp.qcfg.idx_rngsz));

		nb_buff += NUM_RX_PKTS;

		/* Configure mbuf packet pool with minimum 2K size */
		nb_buff = RTE_MAX(nb_buff, (RTE_MEMPOOL_CACHE_MAX_SIZE * 2.5));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());
		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for h2c-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());

		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for c2h-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		if ((mbuf_pool = rte_mempool_lookup(mem_pool)) == NULL)
			throw std::runtime_error("add_queue: Could not find mempool with name:");
		memset(&tx_conf, 0x0, sizeof(struct rte_eth_txconf));
		memset(&rx_conf, 0x0, sizeof(struct rte_eth_rxconf));

		ret = rte_pmd_qdma_set_queue_mode(tx.pf, tx.q, queue_mode);
		if(ret < 0)
		throw std::runtime_error("rte_pmd_qdma_set_queue_mode  failed");

		tx_conf.tx_deferred_start = 1;

		ret = rte_eth_tx_queue_setup(tx.pf, tx.q, tp.qcfg.idx_rngsz, 0,
					&tx_conf);
		if (ret < 0) {
			FAIL() << "rte_eth_tx_queue_setup failed for port %d"<< tx.pf ;
		}
		/* Update the threshold in rxconf */
		rx_conf.rx_thresh.wthresh = tp.qcfg.idx_cntr;

		ret = rte_eth_rx_queue_setup(tx.pf, tx.q, tp.qcfg.idx_rngsz, 0,
						&rx_conf, mbuf_pool);
		if (ret < 0) {
			FAIL() << "rte_eth_rx_queue_setup failed for port %d"<< tx.pf ;
		}
		struct rte_eth_dev *dev;
		dev = &rte_eth_devices[tx.pf];
		dev->data->dev_started = 1;
		ret = rte_eth_dev_tx_queue_start(tx.pf, 65535);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_eth_tx_queue_setup failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
		}

		ret = rte_eth_dev_rx_queue_start(tx.pf, 65535);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_eth_tx_queue_setup failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
		}

		EXPECT_EQ(0, test_status) << "Negative test case is failed!\n";

		//freeing up memory
		struct rte_mempool *mp;
		int loop_cnt;
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}

		if (mp != NULL)
			rte_mempool_free(mp);
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}
		if (mp != NULL)
			rte_mempool_free(mp);
#endif

	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}

TEST_P(qdma_neg_stop_inv_qid_test, h2c_c2h) {

	const auto& tp = GetParam();
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for(const auto& pf : tp.pfs) {
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try{
			rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
		} catch (const std::exception& e){
			FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
		}
	}
#endif

	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));
		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}

#ifdef DPDK
		struct rte_mempool			*mbuf_pool;
		struct rte_eth_txconf		tx_conf;
		struct rte_eth_rxconf		rx_conf;
		int							ret;
		char	mem_pool[RTE_MEMPOOL_NAMESIZE];
		enum rte_pmd_qdma_queue_mode_t queue_mode = RTE_PMD_QDMA_STREAMING_MODE;
		uint32_t		nb_buff;
		int test_status = 0;

		/** Mbuf packet pool **/
		nb_buff = ((tp.qcfg.idx_rngsz));

		nb_buff += NUM_RX_PKTS;

		/* Configure mbuf packet pool with minimum 2K size */
		nb_buff = RTE_MAX(nb_buff, (RTE_MEMPOOL_CACHE_MAX_SIZE * 2.5));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());
		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for h2c-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());

		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for c2h-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		if ((mbuf_pool = rte_mempool_lookup(mem_pool)) == NULL)
			throw std::runtime_error("add_queue: Could not find mempool with name:");
		memset(&tx_conf, 0x0, sizeof(struct rte_eth_txconf));
		memset(&rx_conf, 0x0, sizeof(struct rte_eth_rxconf));

		ret = rte_pmd_qdma_set_queue_mode(tx.pf, tx.q, queue_mode);
		if(ret < 0)
		throw std::runtime_error("rte_pmd_qdma_set_queue_mode  failed");

		// tx_conf.tx_deferred_start = 1;

		ret = rte_eth_tx_queue_setup(tx.pf, tx.q, tp.qcfg.idx_rngsz, 0,
					&tx_conf);
		if (ret < 0) {
			FAIL() << "rte_eth_tx_queue_setup failed for port %d"<< tx.pf ;
		}
		/* Update the threshold in rxconf */
		rx_conf.rx_thresh.wthresh = tp.qcfg.idx_cntr;

		ret = rte_eth_rx_queue_setup(tx.pf, tx.q, tp.qcfg.idx_rngsz, 0,
						&rx_conf, mbuf_pool);
		if (ret < 0) {
			FAIL() << "rte_eth_rx_queue_setup failed for port %d"<< tx.pf ;
		}
		struct rte_eth_dev *dev;
		dev = &rte_eth_devices[tx.pf];
		dev->data->dev_started = 1;
		ret = rte_eth_dev_tx_queue_start(tx.pf, tx.q);
		if (ret < 0) {
			FAIL() << "rte_eth_dev_tx_queue_start failed for port %d"<< tx.pf ;
		}

		ret = rte_eth_dev_rx_queue_start(tx.pf, tx.q);
		if (ret < 0) {
			FAIL() << "rte_eth_dev_rx_queue_start failed for port %d"<< tx.pf ;
		}

		ret = rte_eth_dev_tx_queue_stop(tx.pf, 65535);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_eth_dev_tx_queue_stop failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
			// FAIL();
		}
		ret = rte_eth_dev_rx_queue_stop(tx.pf, 65535);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_eth_dev_rx_queue_stop failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
			// FAIL();
		}
		EXPECT_EQ(0, test_status) << "Negative test case is failed!\n";
		ret = rte_eth_dev_tx_queue_stop(tx.pf, tx.q);
		if (ret < 0 )
			throw std::runtime_error("Failed to stop H2C queue");
		ret = rte_eth_dev_rx_queue_stop(tx.pf, tx.q);
		if (ret < 0 )
			throw std::runtime_error("Failed to stop C2H queue");
		dev->data->dev_started = 0;
		//freeing up memory
		struct rte_mempool *mp;
		int loop_cnt;
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}

		if (mp != NULL)
			rte_mempool_free(mp);
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}
		if (mp != NULL)
			rte_mempool_free(mp);
#endif

	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}

TEST_P(qdma_neg_dump_inv_qid_test, h2c_c2h) {

	const auto& tp = GetParam();
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

#ifdef DPDK
    struct rte_eth_conf	    port_conf;
    for(const auto& pf : tp.pfs) {
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try{
			rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
		} catch (const std::exception& e){
			FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
		}
	}
#endif

	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));
		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}

#ifdef DPDK
		struct rte_mempool			*mbuf_pool;
		struct rte_eth_txconf		tx_conf;
		struct rte_eth_rxconf		rx_conf;
		int							ret;
		char	mem_pool[RTE_MEMPOOL_NAMESIZE];
		enum rte_pmd_qdma_queue_mode_t queue_mode = RTE_PMD_QDMA_STREAMING_MODE;
		uint32_t		nb_buff;
		int test_status = 0;

		/** Mbuf packet pool **/
		nb_buff = ((tp.qcfg.idx_rngsz));

		nb_buff += NUM_RX_PKTS;

		/* Configure mbuf packet pool with minimum 2K size */
		nb_buff = RTE_MAX(nb_buff, (RTE_MEMPOOL_CACHE_MAX_SIZE * 2.5));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());
		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for h2c-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());

		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for c2h-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		if ((mbuf_pool = rte_mempool_lookup(mem_pool)) == NULL)
			throw std::runtime_error("add_queue: Could not find mempool with name:");
		memset(&tx_conf, 0x0, sizeof(struct rte_eth_txconf));
		memset(&rx_conf, 0x0, sizeof(struct rte_eth_rxconf));

		ret = rte_pmd_qdma_set_queue_mode(tx.pf, tx.q, queue_mode);
		if(ret < 0)
		throw std::runtime_error("rte_pmd_qdma_set_queue_mode  failed");

		// tx_conf.tx_deferred_start = 1;

		ret = rte_eth_tx_queue_setup(tx.pf, tx.q, tp.qcfg.idx_rngsz, 0,
					&tx_conf);
		if (ret < 0) {
			FAIL() << "rte_eth_tx_queue_setup failed for port %d"<< tx.pf ;
		}
		/* Update the threshold in rxconf */
		rx_conf.rx_thresh.wthresh = tp.qcfg.idx_cntr;

		ret = rte_eth_rx_queue_setup(tx.pf, tx.q, tp.qcfg.idx_rngsz, 0,
						&rx_conf, mbuf_pool);
		if (ret < 0) {
			FAIL() << "rte_eth_rx_queue_setup failed for port %d"<< tx.pf ;
		}
		struct rte_eth_dev *dev;
		dev = &rte_eth_devices[tx.pf];
		dev->data->dev_started = 1;
		ret = rte_eth_dev_tx_queue_start(tx.pf, tx.q);
		if (ret < 0) {
			FAIL() << "rte_eth_dev_tx_queue_start failed for port %d"<< tx.pf ;
		}

		ret = rte_eth_dev_rx_queue_start(tx.pf, tx.q);
		if (ret < 0) {
			FAIL() << "rte_eth_dev_rx_queue_start failed for port %d"<< tx.pf ;
		}

		ret = rte_pmd_qdma_dbg_qinfo(tx.pf, 65535);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_pmd_qdma_dbg_qinfo failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
		}
		ret = rte_pmd_qdma_dbg_qinfo(255, tx.q);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_pmd_qdma_dbg_qinfo failed for port_id = %d queue id = %d\n", 255, tx.q);
			test_status = 1;
		}
		ret = rte_pmd_qdma_dbg_qdesc(tx.pf, 65535, 0, 0x10, RTE_PMD_QDMA_XDEBUG_DESC_C2H);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_pmd_qdma_dbg_qdesc failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
		}
		ret = rte_pmd_qdma_dbg_qdesc(255, tx.q, 0, 0x10, RTE_PMD_QDMA_XDEBUG_DESC_C2H);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_pmd_qdma_dbg_qdesc failed for port_id = %d queue id = %d\n", 255, tx.q);
			test_status = 1;
		}
		ret = rte_pmd_qdma_dbg_regdump(255);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_pmd_qdma_dbg_regdump failed for port_id = %d\n", 255);
			test_status = 1;
		}
		ret = rte_pmd_qdma_dbg_qdevice(255);
		if (ret < 0) {
		}
		else
		{
			printf("Negative testing of rte_pmd_qdma_dbg_qdevice failed for port_id = %d\n", 255);
			test_status = 1;
		}
		EXPECT_EQ(0, test_status) << "Negative test case is failed!\n";
		ret = rte_eth_dev_tx_queue_stop(tx.pf, tx.q);
		if (ret < 0 )
			throw std::runtime_error("Failed to stop H2C queue");
		ret = rte_eth_dev_rx_queue_stop(tx.pf, tx.q);
		if (ret < 0 )
			throw std::runtime_error("Failed to stop C2H queue");
		dev->data->dev_started = 0;
		//freeing up memory
		struct rte_mempool *mp;
		int loop_cnt;
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}

		if (mp != NULL)
			rte_mempool_free(mp);
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}
		if (mp != NULL)
			rte_mempool_free(mp);
#endif

	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}
#endif

#if defined(DPDK) | defined(_WIN32)
TEST_P(qdma_neg_proc_without_start_test, h2c_c2h) {

	const auto& tp = GetParam();
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for(const auto& pf : tp.pfs) {
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try{
			rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
		} catch (const std::exception& e){
			FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
		}
	}
#endif

	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));
		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}

#ifdef _WIN32
        /* ST read/write without queue add and start */
        {
            qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
            const auto dir = qdma::queue_ext::direction::both;
            static const auto mode = qdma::queue_ext::mode::streaming;
            bool no_add_start_queue = true;

            /* Queue constructor called, but queue not added */
            qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg, no_add_start_queue);

            auto len = q.write(wr_buffer.data(), tx.packet_size, 0, false);
            EXPECT_EQ(0, len) << "qdma_neg_proc_without_start_test part-1 test case failed!\n";

            len = q.read(rd_buffer.data(), tx.packet_size, 0, false);
            EXPECT_EQ(0, len) << "qdma_neg_proc_without_start_test part-1 test case failed!\n";
        }

        /* ST read/write with queue add and without queue start */
        {
            qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
            const auto dir = qdma::queue_ext::direction::both;
            static const auto mode = qdma::queue_ext::mode::streaming;
            bool no_add_start_queue = true;

            /* Queue constructor called, but queue not added */
            qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg, no_add_start_queue);

            auto res = drv.add_queue(tx.pf, tx.q, 1, mode, dir, tp.qcfg);
			EXPECT_EQ(1, res) << "drv.add_queue part-2 test case failed!\n";

            auto len = q.write(wr_buffer.data(), tx.packet_size, 0, false);
            EXPECT_EQ(0, len) << "qdma_neg_proc_without_start_test part-2 test case failed!\n";

            // setup user logic
            example_design_ctrl user_logic{ tx.qdev };

            const auto hw_qid = q.m_hwid;
            const auto tx_size = (tx.packet_size * tx.num_packets);

            user_logic.reset_pkt_ctrl();
            user_logic.set_st_loopback(false);
            user_logic.configure_c2h(hw_qid, tx.packet_size, tx.num_packets);
            user_logic.generate_packets();


            len = q.read(rd_buffer.data(), tx.packet_size, 0, false);
            EXPECT_EQ(0, len) << "qdma_neg_proc_without_start_test part-2 test case failed!\n";
            drv.remove_queue(tx.pf, tx.q, dir);
        }
        /* Breaking with single PF in windows, at later PFs, Prefetch context programming issue is coming
        *  and hardware userlogic is not sophisticated enough for negative test cases
        */
        break;
#elif DPDK
		struct rte_mempool			*mbuf_pool;
		struct rte_eth_txconf		tx_conf;
		struct rte_eth_rxconf		rx_conf;
		int							ret;
		char	mem_pool[RTE_MEMPOOL_NAMESIZE];
		enum rte_pmd_qdma_queue_mode_t queue_mode = RTE_PMD_QDMA_STREAMING_MODE;
		uint32_t		nb_buff;
		int test_status = 0;

		/** Mbuf packet pool **/
		nb_buff = ((tp.qcfg.idx_rngsz));

		nb_buff += NUM_RX_PKTS;

		/* Configure mbuf packet pool with minimum 2K size */
		nb_buff = RTE_MAX(nb_buff, (RTE_MEMPOOL_CACHE_MAX_SIZE * 2.5));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());
		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for h2c-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, tp.qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());

		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for c2h-qid: %d, error: %s\n", tx.q, rte_strerror(rte_errno));

		memset(&tx_conf, 0x0, sizeof(struct rte_eth_txconf));
		memset(&rx_conf, 0x0, sizeof(struct rte_eth_rxconf));

		ret = rte_pmd_qdma_set_queue_mode(tx.pf, tx.q, queue_mode);
		if(ret < 0)
		throw std::runtime_error("rte_pmd_qdma_set_queue_mode  failed");

		// tx_conf.tx_deferred_start = 1;

		ret = rte_eth_tx_queue_setup(tx.pf, tx.q, tp.qcfg.idx_rngsz, 0,
					&tx_conf);
		if (ret < 0) {
			FAIL() << "rte_eth_tx_queue_setup failed for port %d"<< tx.pf ;
		}
		/* Update the threshold in rxconf */
		// rx_conf.rx_thresh.wthresh = tp.qcfg.idx_cntr;

		ret = rte_eth_rx_queue_setup(tx.pf, tx.q, tp.qcfg.idx_rngsz, 0,
						&rx_conf, mbuf_pool);
		if (ret < 0) {
			FAIL() << "rte_eth_rx_queue_setup failed for port %d"<< tx.pf ;
		}

		// tx burst
		struct rte_mempool *mp;
		struct rte_mbuf *mb[NUM_RX_PKTS] = { NULL };
		int nb_tx = 0, i = 0, num_pkts = 10;
		int loop_cnt = 5;
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}

		if (mp == NULL) {
			printf("do_xmit : Could not find mempool with name: %s\n", mem_pool);
			throw std::runtime_error("do_xmit : Could not find mempool with name:\n");
		}

		for (i=0; i<num_pkts; i++) {
			mb[i] = rte_pktmbuf_alloc(mp);
			if (mb[i] == NULL) {
					throw std::runtime_error(" #####Cannot allocate mbuf packet ");
			}
			mb[i]->nb_segs = 1;
			mb[i]->next = NULL;
			rte_pktmbuf_data_len(mb[i]) = (uint16_t)tp.qcfg.idx_bufsz ;
			rte_pktmbuf_pkt_len(mb[i])	= (uint16_t)tp.qcfg.idx_bufsz ;
		}
		nb_tx = rte_eth_tx_burst(tx.pf, tx.q, mb, num_pkts);
		if (nb_tx == 0) {
		}
		else
		{
			printf("Negative testing of rte_eth_tx_burst failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
		}

		//rx burst

		struct rte_mbuf *pkts[NUM_RX_PKTS] = { NULL };
		int nb_rx = 0;
		struct rte_mbuf *nxtmb;
		// setup user logic
		example_design_ctrl user_logic{ tx.qdev };
		user_logic.reset_pkt_ctrl();

		user_logic.set_st_loopback(false);

		const auto hw_qid = get_hw_qid(tx.pf, tx.q);
		const auto tx_size = (tx.packet_size * tx.num_packets);

		user_logic.reset_pkt_ctrl();
		user_logic.configure_c2h(hw_qid, tx.packet_size, tx.num_packets);
		user_logic.generate_packets();

		SCOPED_TRACE("hw_qid=" + std::to_string(hw_qid));
		SCOPED_TRACE("cmptsz=" + std::to_string(tp.qcfg.cmptsz));
		SCOPED_TRACE("tx_size=" + std::to_string(tx_size));
		SCOPED_TRACE("iteration=" + std::to_string(i));
		nb_rx = rte_eth_rx_burst(tx.pf, tx.q, pkts, NUM_RX_PKTS);
		if (nb_rx == 0) {
		}
		else
		{
			printf("Negative testing of rte_eth_rx_burst failed for port_id = %d queue id = %d\n", tx.pf, tx.q);
			test_status = 1;
		}
		EXPECT_EQ(0, test_status) << "Negative test case is failed!\n";
		//freeing up tx memory
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::host_to_card);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}

		if (mp != NULL)
			rte_mempool_free(mp);
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, tx.pf, tx.q, (int)qdma::queue_ext::direction::card_to_host);
		loop_cnt = 5;
		while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
		{
			usleep(100);
			loop_cnt--;
		}
		if (mp != NULL)
			rte_mempool_free(mp);
		//freeing up rx memory
		for (i = 0; i < nb_rx; i++) {
				struct rte_mbuf *mb = pkts[i];
				while (mb != NULL){
					ret += rte_pktmbuf_data_len(mb);
					nxtmb = mb->next;
					mb = nxtmb;
				}

				mb = pkts[i];
				rte_pktmbuf_free(mb);
			}
#endif

	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}
#endif

#ifdef _WIN32
TEST_P(qdma_neg_read_write_overflow, h2c_c2h) {
    const auto& tp = GetParam();
    const auto dir = qdma::queue_ext::direction::both;
    const auto mode = qdma::queue_ext::mode::streaming;
    qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
    // get the pf/vf device list based on dev_type
    std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
    ASSERT_FALSE(devlist.empty());

    for (const auto& tx : tp.transfers) {
        SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
        SCOPED_TRACE("queue=" + std::to_string(tx.q));
        if (validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
            //GTEST_SKIP();
            std::cout << "Invalid Test Case" << std::endl;
            continue;
        }

        example_design_ctrl user_logic{ tx.qdev };
        user_logic.reset_pkt_ctrl();

        // setup user logic
        if (tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass)
            user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir, SIMPLE_BYPASS_MODE);
        else if (tp.qcfg.desc_bypass)
            user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir, CACHE_BYPASS_MODE);
        else
            user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir, NO_BYPASS_MODE);

        user_logic.set_st_loopback(false);

        qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg);

        for (unsigned i = 0; i < tx.it; i++) {
            SCOPED_TRACE("iteration=" + std::to_string(i));

            /* Write Overflow Test */
            {
                user_logic.reset_h2c();
                auto tx_size = tx.packet_size * tx.num_packets;
                const auto buf_sz = (tx_size / sizeof(pattern_t));

                wr_buffer.resize(buf_sz);
                std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0));    // 0, 1, 2, 3, 4 ...

#ifdef _WIN32
                auto len = q.write(wr_buffer.data(), tx_size, 0, false);
                EXPECT_EQ(0, len) << "qdma_neg_read_write_overflow : Write test failed";
#endif
            }
            /* Read Overflow Test */
            {
#ifdef _WIN32
                const auto hw_qid = q.m_hwid;
#endif
                const auto tx_size = (tx.packet_size * tx.num_packets);
                const auto buf_sz = (tx_size / sizeof(pattern_t));
                rd_buffer.resize(buf_sz);
                expected.resize(buf_sz);


                for (unsigned i = 0; i < tx.it; i++) {
                    std::iota(expected.begin(), expected.end(), static_cast<pattern_t>(0));    // 0, 1, 2, 3, 4 ...
                    std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));

                    user_logic.reset_pkt_ctrl();
                    user_logic.configure_c2h(hw_qid, tx.packet_size, tx.num_packets);
                    user_logic.set_wrb_desc_size(tp.qcfg.cmptsz);
                    user_logic.generate_packets();

                    SCOPED_TRACE("hw_qid=" + std::to_string(hw_qid));
                    SCOPED_TRACE("cmptsz=" + std::to_string(tp.qcfg.cmptsz));
                    SCOPED_TRACE("tx_size=" + std::to_string(tx_size));
                    SCOPED_TRACE("iteration=" + std::to_string(i));

#ifdef _WIN32
                    auto len = q.read(rd_buffer.data(), tx_size, 0, false);
                    EXPECT_EQ(0, len);
#endif
                }
            }
        }
    }
}
#endif

TEST_P(qdma_st_test, h2c_only) {

    const auto& tp = GetParam();
	const auto dir = qdma::queue_ext::direction::host_to_card;
	const auto mode = qdma::queue_ext::mode::streaming;
	qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());


#ifdef DPDK
    struct rte_eth_conf	    port_conf;
    for(const auto& pf : tp.pfs){
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
    	try{
    		rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
    	} catch (const std::exception& e){
    		FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
    	}
    }
#endif

    for (const auto& tx : tp.transfers) {
        SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
        SCOPED_TRACE("queue=" + std::to_string(tx.q));
        if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
            //GTEST_SKIP();
            std::cout << "Invalid Test Case" << std::endl;
            continue;
        }

        example_design_ctrl user_logic{ tx.qdev };
        user_logic.reset_pkt_ctrl();

        // setup user logic
        if(tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass)
        	user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir, SIMPLE_BYPASS_MODE);
        else if (tp.qcfg.desc_bypass)
        	user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir, CACHE_BYPASS_MODE);
        else
        	user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir, NO_BYPASS_MODE);

        user_logic.set_st_loopback(false);

        qdma::queue_ext h2c_q(drv, tx.pf, tx.q, mode, dir, tp.qcfg);

        for (unsigned i = 0; i < tx.it; i++) {
            SCOPED_TRACE("iteration=" + std::to_string(i));

            user_logic.reset_h2c();
            auto tx_size = tx.packet_size * tx.num_packets;
            const auto buf_sz = (tx_size / sizeof(pattern_t));

            wr_buffer.resize(buf_sz);
            std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0));    // 0, 1, 2, 3, 4 ...

#ifdef DPDK
            ASSERT_NO_THROW(
                    h2c_q.write(wr_buffer.data(), tx_size);
            )<< "h2c transfer returned with an error!";

            //usleep(1500);

            const auto hw_qid = get_hw_qid(tx.pf, tx.q);
			bool ret = 0;
			unsigned retry = 50;
			while(retry)
			{
				usleep(500);
				ret = user_logic.check_h2c(hw_qid, (tx.packet_size == 0));
				if(ret == true)
					break;
				else
					printf("h2c data checker did not receive expected data pattern!, retry count = %u\n", (50 - (retry-1)));

				retry--;
			}

            EXPECT_TRUE(ret)
                << "h2c data checker did not receive expected data pattern!"
                << rte_pmd_qdma_dbg_qinfo(tx.pf, tx.q)
                << rte_pmd_qdma_dbg_regdump(tx.pf)
		<< user_logic.user_bar_reg_read();
#elif _WIN32
            ASSERT_NO_THROW(
                h2c_q.write(wr_buffer.data(), tx_size);
            ) << "h2c transfer returned with an error!";

            const auto hw_qid =  h2c_q.m_hwid;// get_hw_qid(tx.pf, tx.q, devlist);

            EXPECT_TRUE(user_logic.check_h2c(hw_qid, (tx.packet_size == 0)))
                << "h2c data checker did not receive expected data pattern!";
#else
            char *cmd = new char[200];
            char *regcmd = new char[200];
            snprintf(cmd, 200, "cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/queues/%d/h2c/cntxt",
                             (tp.devtype == qdma::instance::type::pf) ? "pf" : "vf",
							 (tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7), tx.q);

            snprintf(regcmd, 200, "cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/qdma_regs",
            			(tp.devtype == qdma::instance::type::pf) ? "pf" : "vf",
						(tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7));

            ASSERT_NO_THROW(
                    h2c_q.write(wr_buffer.data(), tx_size);
            )<< "h2c transfer returned with an error!"<< system(cmd) << system(regcmd);

			const auto hw_qid = get_hw_qid(tx.pf, tx.q, devlist);
			bool ret = false;
			unsigned retry = 50;
			while (retry)
			{
				usleep(2000);
				ret = user_logic.check_h2c(hw_qid, (tx.packet_size == 0));
				if(ret == true)
					break;
				retry--;
			}

			if (ret != true && retry == 0) {
				std::cout << "h2c data checker did not receive expected data "
						"pattern!, retry count = " << (50 - retry) << "\n"
						<< system(cmd) << system(regcmd);
			}
			delete[] cmd;
			delete[] regcmd;
#endif
        }
    }
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}



void qdma_st_c2h_test::testbody_c2h_only() {

    const auto& tp = GetParam();
	const auto dir = qdma::queue_ext::direction::card_to_host;
	const auto mode = qdma::queue_ext::mode::streaming;
	qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

#ifdef DPDK
    struct rte_eth_conf	    port_conf;
    for(const auto& pf : tp.pfs) {
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
    	try{
    		rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
    	} catch (const std::exception& e){
    		FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
    	}
    }
#endif

    for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));
        if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
            //GTEST_SKIP();
            std::cout << "Invalid Test Case" << std::endl;
            continue;
        }

        example_design_ctrl user_logic{ tx.qdev };
		user_logic.reset_pkt_ctrl();

		// setup user logic
		if(tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass) {
			if (!(((get_device_type(tx.pf, devlist) == QDMA_DEVICE_SOFT) &&
					(get_ip_type(tx.pf, devlist) == EQDMA_SOFT_IP)) ||
					((get_device_type(tx.pf, devlist) == QDMA_DEVICE_VERSAL_CPM5) &&
					(get_ip_type(tx.pf, devlist) == QDMA_VERSAL_HARD_IP)))) {
					user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming,
					dir, SIMPLE_BYPASS_MODE);
			}
		} else if (tp.qcfg.desc_bypass)
			user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming,
				dir, CACHE_BYPASS_MODE);
		else
			user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming,
				dir, NO_BYPASS_MODE);

		user_logic.set_st_loopback(false);
		qdma::queue_ext c2h_q(drv, tx.pf, tx.q, mode, dir, tp.qcfg);
#ifdef DPDK
		const auto hw_qid = get_hw_qid(tx.pf, tx.q);
#elif _WIN32
        const auto hw_qid = c2h_q.m_hwid;
#else
		const auto hw_qid = get_hw_qid(tx.pf, tx.q, devlist);
#endif
		const auto tx_size = (tx.packet_size * tx.num_packets);
		const auto buf_sz = (tx_size / sizeof(pattern_t));
		rd_buffer.resize(buf_sz);
		expected.resize(buf_sz);

		//user_logic.user_bar_reg_read();
		if ((((get_device_type(tx.pf, devlist) == QDMA_DEVICE_SOFT)
			&& (get_ip_type(tx.pf, devlist) == EQDMA_SOFT_IP))||
			((get_device_type(tx.pf, devlist) == QDMA_DEVICE_VERSAL_CPM5)
			&& (get_ip_type(tx.pf, devlist) == QDMA_VERSAL_HARD_IP)))
				&& (tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass)) {
			auto& control_bar = *tx.qdev.dma_bar;
			control_bar.write(EQDMA_C2H_PFCH_BYP_QID, hw_qid);
			const auto prefetch_tag = control_bar.read<uint32_t>(EQDMA_C2H_PFCH_BYP_TAG);
			// Write the tag value and the qid that is used to fetch the tag in user bar register 0x24
			user_logic.set_prefetch_tag(hw_qid, prefetch_tag);

			// setup user logic
			user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming,
					dir, SIMPLE_BYPASS_MODE);
			user_logic.set_st_loopback(false);
		}

		 for (unsigned i = 0; i < tx.it; i++) {
			std::iota(expected.begin(), expected.end(), static_cast<pattern_t>(0));    // 0, 1, 2, 3, 4 ...
			std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));

			user_logic.reset_pkt_ctrl();
			user_logic.configure_c2h(hw_qid, tx.packet_size, tx.num_packets);
			user_logic.set_wrb_desc_size(tp.qcfg.cmptsz);
			user_logic.generate_packets();

			SCOPED_TRACE("hw_qid=" + std::to_string(hw_qid));
			SCOPED_TRACE("cmptsz=" + std::to_string(tp.qcfg.cmptsz));
			SCOPED_TRACE("tx_size=" + std::to_string(tx_size));
			SCOPED_TRACE("iteration=" + std::to_string(i));

#ifdef DPDK
			ASSERT_NO_THROW(
					c2h_q.read(rd_buffer.data(), tx_size);
			)<< "c2h transfer returned with an error!";

			// compare packet data with expected
			auto cmp_result = std::memcmp(expected.data(), rd_buffer.data(), tx_size);
			EXPECT_EQ(0, cmp_result) << "packet data does not match expected pattern!\n"
					<< print_diffs(expected.cbegin(), expected.cend(), rd_buffer.cbegin())
					<< rte_pmd_qdma_dbg_qinfo(tx.pf, tx.q)
					<< rte_pmd_qdma_dbg_regdump(tx.pf)
		                        << user_logic.user_bar_reg_read();
#elif _WIN32
			ASSERT_NO_THROW(
				c2h_q.read(rd_buffer.data(), tx_size);
				) << "c2h transfer returned with an error!";


			// compare packet data with expected
			auto cmp_result = std::memcmp(expected.data(), rd_buffer.data(), tx_size);
			ASSERT_EQ(0, cmp_result) << "packet data does not match expected pattern!\n"
				<< print_diffs(expected.cbegin(), expected.cend(), rd_buffer.cbegin());
#else
			char cmd[400];
			char *regcmd = new char[200];
			snprintf(cmd, 200, "cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/queues/%d/c2h/cntxt; "
			    "cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/queues/%d/cmpt/cntxt",
			     (tp.devtype == qdma::instance::type::pf) ? "pf" : "vf",
			     (tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7), tx.q,
			     (tp.devtype == qdma::instance::type::pf) ? "pf" : "vf",
			     (tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7), tx.q);

			snprintf(regcmd, 200, "cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/qdma_regs",
			     (tp.devtype == qdma::instance::type::pf) ? "pf" : "vf",
			     (tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7));


			ASSERT_NO_THROW(
					c2h_q.read(rd_buffer.data(), tx_size);
			)<< "c2h transfer returned with an error!"
			        << system(cmd) << system(regcmd);


			// compare packet data with expected
			auto cmp_result = std::memcmp(expected.data(), rd_buffer.data(), tx_size);
			ASSERT_EQ(0, cmp_result) << "packet data does not match expected pattern!\n"
					<< print_diffs(expected.cbegin(), expected.cend(), rd_buffer.cbegin())
					<< system(cmd) << system(regcmd)
		                        << user_logic.user_bar_reg_read();
			delete[] regcmd;
#endif
		}
#if defined(LINUX) || defined (DPDK) || defined (_WIN32)
		//Send the Marker completion request before closing of the queues for EQDMA.
		if (((get_device_type(tx.pf, devlist) == QDMA_DEVICE_SOFT) &&
			(get_ip_type(tx.pf, devlist) == EQDMA_SOFT_IP)) &&
			(!(tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass)))
		{
			user_logic.st_c2h_gen_marker_resp();
			unsigned retry = 50;
			while(retry) {
				usleep(500);
				if (user_logic.check_marker_completion() == true)
					break;
				else
					printf("Didnt received the c2h marker completion, retry count = %u\n", (50 - (retry-1)));
				retry--;
			}
			user_logic.st_c2h_marker_dis();
		}
#endif
	}

#ifdef DPDK
	for(const auto& pf : tp.pfs) {
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}

TEST_P(qdma_st_test, c2h_only) {
    ASSERT_NO_FATAL_FAILURE(testbody_c2h_only());
}

TEST_P(qdma_st_c2h_test, c2h_only) {
    ASSERT_NO_FATAL_FAILURE(testbody_c2h_only());
}


static st_test_params generic_tests(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<st_test_params::transfer> transfers;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	transfers.reserve(10);
#ifdef DPDK
	std::vector<st_test_params::fmap> fmaps;
	uint32_t base = 0;
	fmaps.reserve(devlist.size());
#endif
	if (!devlist.size()) {
#ifdef DPDK
		return st_test_params { std::move(fmaps), std::move(transfers), dev_type };
#else
		return st_test_params { std::move(transfers), dev_type};
#endif
	}
#ifdef DPDK
	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		fmaps.emplace_back(devlist[pf_id].dev_id, base,devlist[pf_id].max_num_queues);
		base += devlist[pf_id].max_num_queues;
	}
#endif

	// setup random number generators
	std::default_random_engine rne((unsigned int)time(0));
	std::uniform_int_distribution<uint32_t> rng_pf(0, (uint32_t)devlist.size() - 1);    // pf
	std::uniform_int_distribution<uint32_t> rng_it(1, 1000);    // iterations
	std::uniform_int_distribution<uint32_t> rng_ps(4_kB, 4_kB);    // packet size
	std::uniform_int_distribution<uint32_t> rng_np(1, 32);    // num packets
	qdma::queue_ext::config qcfg;

	for (uint32_t i = 0; i < 10; i++) {

		const auto pf = rng_pf(rne);
		if (!devlist[pf].max_num_queues)
			continue;

		std::uniform_int_distribution<uint32_t> rng_q(0, devlist[pf].max_num_queues - 1); // queue
		const auto qid = rng_q(rne);
		const auto num_transfers = rng_it(rne);
		const auto packet_size = rng_ps(rne) & ~1u; // mask LSB to ensure packet_size is always even
		const auto num_packets = rng_np(rne);

		transfers.emplace_back(devlist[pf].dev_id, qid, num_transfers, packet_size, num_packets, devlist[pf]);
	}

    if(devlist.size()) {
        if (!((get_device_type(devlist[0].dev_id, devlist) == QDMA_DEVICE_VERSAL_CPM4) &&
			(get_ip_type(devlist[0].dev_id, devlist) == QDMA_VERSAL_HARD_IP))) {
                qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
        }
    }


#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers), dev_type,  qcfg};
#else
	return st_test_params { std::move(transfers), dev_type, qcfg};
#endif

}

TEST_P(qdma_st_generic_test, c2h_h2c) {

	const auto c2h_dir = qdma::queue_ext::direction::card_to_host;
	const auto h2c_dir = qdma::queue_ext::direction::host_to_card;
	const auto& tp = GetParam();

	qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

	// setup buffers - using BRAM size as max transfer length, even though they are unrelated
	aligned_vector<pattern_t> buffer(array_size);

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for(const auto& pf : tp.pfs) {
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try{
			rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
		} catch (const std::exception& e){
			FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
		}
	}
#endif

	for (const auto& xfer : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(xfer.pf));
		SCOPED_TRACE("queue=" + std::to_string(xfer.q));
		if(validate_test_case(devlist, xfer.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}
		auto device_type = get_device_type(xfer.pf, devlist);
		int ip_type = get_ip_type(xfer.pf, devlist);
		example_design_ctrl user_logic{ xfer.qdev };
		user_logic.reset_pkt_ctrl();
#ifdef DPDK
		const auto hw_qid = get_hw_qid(xfer.pf, xfer.q);
#elif LINUX
		const auto hw_qid = get_hw_qid(xfer.pf, xfer.q, devlist);
#endif

		// setup user logic
		if(tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass)
			user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both, SIMPLE_BYPASS_MODE);
		else if (tp.qcfg.desc_bypass)
			user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both, CACHE_BYPASS_MODE);
		else
			user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both, NO_BYPASS_MODE);

		user_logic.set_st_loopback(false);
#ifdef _WIN32
        qdma::queue_ext q(drv, xfer.pf, xfer.q, mode, c2h_dir, tp.qcfg);
        const auto hw_qid = q.m_hwid;
#else
		qdma::queue_ext c2h_q(drv, xfer.pf, xfer.q, mode, c2h_dir, tp.qcfg);
		qdma::queue_ext h2c_q(drv, xfer.pf, xfer.q, mode, h2c_dir, tp.qcfg);
#endif
		for (unsigned i = 0; i < xfer.it; i++) {
			user_logic.configure_c2h(hw_qid, xfer.packet_size, xfer.num_packets);
			user_logic.set_wrb_desc_size(tp.qcfg.cmptsz);
			user_logic.set_imm_data_en(tp.qcfg.c2h_udd_en, device_type, ip_type);
			user_logic.generate_packets();
#ifdef DPDK
			/*
			DPDK read/write APIs are asynchronous calls,
			hence, give some time for packet generator to generate packet
			so that read API can get the packet by that time.
			*/
			usleep(2000);
#endif
			SCOPED_TRACE("iteration=" + std::to_string(i));

			/* C2H Transfer */
			const auto xfer_size = xfer.packet_size * xfer.num_packets;
#ifdef _WIN32
            ASSERT_NO_THROW(
                q.read(buffer.data(), xfer_size)
            ) << "c2h transfer returned with an error!";

            /* Initiate H2C */
            user_logic.reset_h2c();

            ASSERT_NO_THROW(
                q.write(buffer.data(), xfer_size);
            ) << "h2c transfer returned with an error!";
#else
			ASSERT_NO_THROW(
				c2h_q.read(buffer.data(), xfer_size)
			)<< "c2h transfer returned with an error!";

			/* Initiate H2C */
			user_logic.reset_h2c();

			ASSERT_NO_THROW(
				h2c_q.write(buffer.data(), xfer_size);
			)<< "h2c transfer returned with an error!";
#endif
			// usleep(1500);
#ifdef DPDK
			bool ret = 0;
			unsigned retry = 50;
			while(retry)
			{
				usleep(500);
				ret = user_logic.check_h2c(hw_qid, (xfer.packet_size == 0));
				if(ret == true)
					break;
				else
					printf("h2c data checker did not receive expected data pattern!, retry count = %u\n", (50 - (retry-1)));

				retry--;
			}

			EXPECT_TRUE(ret)
				<< "h2c data checker did not receive expected data pattern!"
				<< rte_pmd_qdma_dbg_qinfo(xfer.pf, xfer.q)
				<< rte_pmd_qdma_dbg_regdump(xfer.pf)
		                << user_logic.user_bar_reg_read();
#else
			EXPECT_TRUE(user_logic.check_h2c(hw_qid, (xfer.packet_size == 0)))
				<< "h2c data checker did not receive expected data pattern!";
#endif
		}
	}

#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}

TEST_P(qdma_st_generic_test, completion_payload_mix) {

	const auto mode = qdma::queue_ext::mode::streaming;
	const auto dir = qdma::queue_ext::direction::card_to_host;
	qdma::queue_ext::config qcfg;
	int cmptsz_map[] = {8, 16, 32, 64};
	char buf[1000];
	char buf_64b[1000];
	int len = 0;
	int len_64b = 0;
	uint32_t imm_data;
	int k = 0;
	unsigned char *bytes;
	const auto& tp = GetParam();

	qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

	std::default_random_engine rne((unsigned int)time(0));
	std::uniform_int_distribution<uint32_t> rng_data(0, 0xFFFFFFFF);
	std::uniform_int_distribution<uint32_t> rng_wbsz(0, 2);    // write back entry size
	std::uniform_int_distribution<uint32_t> rng_imm(0, 1);    // enabling immedaite data capture

	// setup buffers - using BRAM size as max transfer length, even though they are unrelated
	aligned_vector<pattern_t> buffer(array_size);

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for(const auto& pf : tp.pfs) {
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try{
			rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
		} catch (const std::exception& e){
			FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
		}
	}
#endif

	for (const auto& xfer : tp.transfers) {
		const auto device_type = get_device_type(xfer.pf, devlist);
		const auto ip_type = get_ip_type(xfer.pf, devlist);

		memset(buf, 0, 1000);
		len = 0;
#ifdef DPDK
		auto cmptsz = cmptsz_map[rng_wbsz(rne)];

		if ((cmptsz == 64) &&
				(device_type == QDMA_DEVICE_VERSAL_CPM4) &&
				(ip_type == QDMA_VERSAL_HARD_IP)) {
			cmptsz = 32;
		}
#else
		auto cmptsz = rng_wbsz(rne);
		if ((cmptsz == 3) &&
				((device_type == QDMA_DEVICE_VERSAL_CPM4) &&
				(ip_type == QDMA_VERSAL_HARD_IP))) {
			cmptsz = 2;
		}
#endif
		const auto imm_en = rng_imm(rne);
#ifdef DPDK
		auto usr_imm_data_regs = cmptsz/4;
#else
		auto usr_imm_data_regs = cmptsz_map[cmptsz]/4;
#endif

		if (cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B)
			usr_imm_data_regs = 8;

		SCOPED_TRACE("pf=" + int_to_hex(xfer.pf));
		SCOPED_TRACE("queue=" + std::to_string(xfer.q));
		SCOPED_TRACE("imm_en=" + std::to_string(imm_en));
		SCOPED_TRACE("rng_wbsz=" + std::to_string(cmptsz));

		qcfg.c2h_udd_en = imm_en;
		qcfg.cmptsz = static_cast<xnl_st_c2h_cmpt_desc_size>(cmptsz);

		if(validate_test_case(devlist, xfer.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}

		example_design_ctrl user_logic{ xfer.qdev };
		user_logic.reset_pkt_ctrl();

		// setup user logic
		if(tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass) {
			user_logic.set_bypass_mode(mode, dir, SIMPLE_BYPASS_MODE);
		} else if (tp.qcfg.desc_bypass) {
			user_logic.set_bypass_mode(mode, dir, CACHE_BYPASS_MODE);
		} else {
			user_logic.set_bypass_mode(mode, dir, NO_BYPASS_MODE);
		}

		user_logic.set_st_loopback(false);
		/** Queue started with cmptsz and c2h_udd_en */
		qdma::queue_ext c2h_q(drv, xfer.pf, xfer.q, mode, dir, qcfg);

#ifdef DPDK
		const auto hw_qid = get_hw_qid(xfer.pf, xfer.q);
#elif _WIN32
		const auto hw_qid = c2h_q.m_hwid;
#else
		const auto hw_qid = get_hw_qid(xfer.pf, xfer.q, devlist);
#endif

		/** setting the cmpt size and HW QID */
		user_logic.set_wrb_desc_size(qcfg.cmptsz);

		if(imm_en) {

			len_64b = 0;
			memset(buf_64b, 0, 1000);
			/* Setting UDD in userbar registers */
			for(auto j = 0; j < usr_imm_data_regs; j++) {
				imm_data = rng_data(rne);
				user_logic.set_imm_data(j , imm_data);

				bytes = reinterpret_cast<unsigned char*>(&imm_data);
				for(k = 0 ; k < 4 ; k++) {

					if((device_type == QDMA_DEVICE_VERSAL_CPM4)
							&& (ip_type == QDMA_VERSAL_HARD_IP)) {
						/* Ignoring the first 4 bits while creating a buffer for the lower 32 bytes */
						if ((j == 0) && (k < 2)) {
							/*ignoring the first 16 bits*/
						}
						else if ((j == 0) && (k == 2)) {
							len += sprintf(buf + len, "%02x", (bytes[k] & 0xF0));
						}else {
							len += sprintf(buf + len, "%02x", bytes[k]);
						}
					} else {

						/* Creating a buffer to store the higher 32bytes of data */
						if(cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B)
							len_64b += sprintf(buf_64b + len_64b, "%02x", bytes[k]);
							/* Ignoring the first 4 bits while creating a buffer for the lower 32 bytes */
						if ((j == 0) && (k == 0)) {
							len += sprintf(buf + len, "%02x", (bytes[k] & 0xF0));
						} else {
							len += sprintf(buf + len, "%02x", bytes[k]);
						}
					}
				}
			}

			if((device_type == QDMA_DEVICE_VERSAL_CPM4)
					&& (ip_type == QDMA_VERSAL_HARD_IP)) {
				user_logic.configure_c2h(hw_qid, 64, 1);
				user_logic.set_imm_data_en(qcfg.c2h_udd_en, QDMA_DEVICE_VERSAL_CPM4, ip_type);
			}
			else {
				user_logic.set_queue(hw_qid);
				user_logic.set_imm_data_en(qcfg.c2h_udd_en, QDMA_DEVICE_SOFT, ip_type);
			}

		} else {
			user_logic.configure_c2h(hw_qid, xfer.packet_size, xfer.num_packets);
			user_logic.generate_packets();
		}

		buf[len] = '\0';
		len++;
		if(cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B) {
			buf_64b[len] = '\0';
			len_64b++;
		}

#ifdef _WIN32
        /** 5000 msec sleep (x10 times when compared to linux and dpdk).
         *  This is to bypass the issue specified in JIRA XDMA-991
         *  FIXME : Once the JIRA issue is resolved, make this usleep to 500
         */
        usleep(5000);
#else
		/* adding delay to make sure HW has generated the writeback entry */
		usleep(500);
#endif

		const auto tx_size = xfer.packet_size * xfer.num_packets;
		const auto buf_sz = (tx_size / sizeof(pattern_t));
		if (imm_en) {
#ifdef DPDK
			rd_buffer.resize(buf_sz);
			ASSERT_NO_THROW(c2h_q.read(rd_buffer.data(), tx_size))<< "c2h transfer returned with an error!";
			char filename[30];
			snprintf(filename, 30,"q_%d_immmediate_data.txt",xfer.q);
			std::ifstream immfile(filename);
			if (cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B) {
				//unsigned char temp[len*2];
				std::string temp;
				temp.resize(len * 2);
				char * newArray = new char[std::strlen(buf)+std::strlen(buf)+1];
				std::strcpy(newArray,buf);
				std::strcat(newArray,buf_64b);
				immfile.read((char *)temp.c_str(),len * 2);
				auto cmp_res = strncmp(newArray, temp.c_str(), len * 2);
				EXPECT_EQ(0, cmp_res) << "udd : packet data does not match expected pattern!\n" << cmptsz;
			}else {
				//unsigned char temp[len];
				std::string temp;
				temp.resize(cmptsz);
				//immfile.read((char *)&temp[0], len);
				immfile.read((char *)temp.c_str(),cmptsz);
				auto cmp_res = strncmp(buf, temp.c_str() , cmptsz);
				EXPECT_EQ(0, cmp_res) << "udd : packet data does not match expected pattern!\n" << cmptsz;
			}
			immfile.close();
			system("rm -rf q_*");
#else
			auto udd = drv.read_rx_packet(xfer.pf, xfer.q);
			if (cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B) {
				char * newArray = new char[std::strlen(buf)+std::strlen(buf)+1];
				std::strcpy(newArray,buf);
				std::strcat(newArray,buf_64b);
				auto cmp_res = strncmp(newArray, udd.c_str(), len * 2);
				delete[] newArray;
				ASSERT_EQ(0, cmp_res) << "udd : packet data does not match expected pattern!" << cmptsz << std::endl;
			} else {
				auto cmp_res = strncmp(buf, udd.c_str(), cmptsz_map[cmptsz]);
				ASSERT_EQ(0, cmp_res) << "udd : packet data does not match expected pattern!" << cmptsz << std::endl;
			}
#endif
		} else {
			rd_buffer.resize(buf_sz);
			expected.resize(buf_sz);
			std::iota(expected.begin(), expected.end(), static_cast<pattern_t>(0));    // 0, 1, 2, 3, 4 ...
			ASSERT_NO_THROW(
					c2h_q.read(rd_buffer.data(), tx_size)
			)<< "c2h transfer returned with an error!";
			// compare packet data with expected
			auto cmp_result = std::memcmp(expected.data(), rd_buffer.data(), tx_size);
			EXPECT_EQ(0, cmp_result) << "payload : packet data does not match expected pattern!\n"
					<< print_diffs(expected.cbegin(), expected.cend(), rd_buffer.cbegin());
		}
		rd_buffer.resize(array_size);
		expected.resize(array_size);
	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}


TEST_P(qdma_st_generic_test, DISABLED_h2c_c2h_loopback) {

	const auto dir = qdma::queue_ext::direction::both;
	const auto& tp = GetParam();

	qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

	// setup buffers - using BRAM size as max transfer length, even though they are unrelated
	aligned_vector<pattern_t> buffer(array_size);

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for(const auto& pf : tp.pfs) {
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try{
			rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
		} catch (const std::exception& e){
			FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
		}
	}
#endif

	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));

        if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
            //GTEST_SKIP();
            std::cout << "Invalid Test Case" << std::endl;
            continue;
        }

#ifdef DPDK
		const auto hw_qid = get_hw_qid(tx.pf, tx.q);
#else
		const auto hw_qid = get_hw_qid(tx.pf, tx.q, devlist);
#endif
		example_design_ctrl user_logic{ tx.qdev};
		user_logic.reset_pkt_ctrl();

		// setup user logic
		if(tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass)
			user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir, SIMPLE_BYPASS_MODE);
		else if (tp.qcfg.desc_bypass)
			user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir, CACHE_BYPASS_MODE);
		else
			user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir, NO_BYPASS_MODE);

		qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg);
		user_logic.set_queue(hw_qid);
		user_logic.set_st_loopback(true);
		user_logic.set_wrb_desc_size(tp.qcfg.cmptsz);

		for (unsigned i = 0; i < tx.it; i++) {
			SCOPED_TRACE("iteration=" + std::to_string(i));

			user_logic.reset_h2c();
			const auto tx_size = tx.packet_size * tx.num_packets;

			rd_buffer.resize(tx_size / sizeof(pattern_t));
			wr_buffer.resize(tx_size / sizeof(pattern_t));
			std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...

			ASSERT_NO_THROW(
				q.write(wr_buffer.data(), tx_size);
				)<< "h2c transfer returned with an error!";
			usleep(1500);

			ASSERT_NO_THROW(
				q.read(rd_buffer.data(), tx_size)
			)<< "c2h transfer returned with an error!";

			// compare packet data with expected
			auto cmp_result = std::memcmp(wr_buffer.data(), rd_buffer.data(), tx_size);
			EXPECT_EQ(0, cmp_result) << "packet data does not match expected pattern!\n"
				<< print_diffs(wr_buffer.cbegin(), wr_buffer.cend(), rd_buffer.cbegin());
		}
	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
}


TEST_P(qdma_st_temp_test, h2c_c2h) {

	const auto& tp = GetParam();
	qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
    ASSERT_FALSE(devlist.empty());

#ifdef _WIN32
    if (devlist.size() > 4) {
	    std::cout << "More than 4 PFs detected and hence bypassing the test case\n";
	    return;
    }
#endif

    const auto dir = qdma::queue_ext::direction::both;
    static const auto mode = qdma::queue_ext::mode::streaming;

#ifdef DPDK
    struct rte_eth_conf	    port_conf;
    for(const auto& pf : tp.pfs){
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
    	try{
    		rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
    	} catch (const std::exception& e){
    		FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
    	}
    }
#endif

    queues.reserve(tp.transfers.size());
    for(const auto& tx : tp.transfers){
        if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
            //GTEST_SKIP();
            std::cout << "Invalid Test Case" << std::endl;
            continue;
        }

		queues.emplace_back(drv, tx.pf, tx.q, mode, dir, tp.qcfg);
    }

    struct find_id {
		uint32_t pf;
		uint32_t q;
		find_id(uint32_t pf, uint32_t q): pf(pf),q(q) { }
		bool operator()(st_test_params::transfer const& m) const {
			return (m.pf == pf) && (m.q == q);
		}
    };

    for(auto& q : queues){
        auto tx = std::find_if (tp.transfers.begin(), tp.transfers.end()-1, find_id(q.m_dev_id, q.m_qid));
        SCOPED_TRACE("pf=" + int_to_hex(tx->pf));
        SCOPED_TRACE("queue=" + std::to_string(tx->q));
        const auto device_type = get_device_type(tx->pf, devlist);
		const auto ip_type = get_ip_type(tx->pf, devlist);
#ifdef DPDK
        const auto hw_qid = get_hw_qid(tx->pf, tx->q);
#elif _WIN32
        const auto hw_qid = q.m_hwid;
#else
        const auto hw_qid = get_hw_qid(tx->pf, tx->q, devlist);
#endif

        example_design_ctrl user_logic{ tx->qdev };
        user_logic.reset_pkt_ctrl();

        // setup user logic
        if(tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass)
        	user_logic.set_bypass_mode(mode, dir, SIMPLE_BYPASS_MODE);
        else if (tp.qcfg.desc_bypass)
        	user_logic.set_bypass_mode(mode, dir, CACHE_BYPASS_MODE);
        else
        	user_logic.set_bypass_mode(mode, dir, NO_BYPASS_MODE);

        user_logic.set_st_loopback(false);
        for (unsigned i = 0; i < tx->it; i++) {
			SCOPED_TRACE("iteration=" + std::to_string(i));

			user_logic.reset_h2c();
			EXPECT_NO_THROW(
					q.write(wr_buffer.data(), tx->packet_size * tx->num_packets);
			)<< "h2c transfer returned with an error!";
#ifdef DPDK
			// usleep(1500);
#endif
			user_logic.set_queue(hw_qid);
#ifdef DPDK
			bool ret = 0;
			unsigned retry = 50;
			while(retry)
			{
				usleep(500);
				ret = user_logic.check_h2c(hw_qid, (tx->packet_size == 0));
				if(ret == true)
					break;
				else
					printf("h2c data checker did not receive expected data pattern!, retry count = %u\n", (50 - (retry-1)));

				retry--;
			}

			EXPECT_TRUE(ret)
				<< "h2c data checker did not receive expected data pattern!"
				<< rte_pmd_qdma_dbg_qinfo(tx->pf, tx->q)
				<< rte_pmd_qdma_dbg_regdump(tx->pf)
		                << user_logic.user_bar_reg_read();
#else
			EXPECT_TRUE(user_logic.check_h2c(hw_qid, (tx->packet_size == 0)))
				<< "h2c data checker did not receive expected data pattern!";
#endif
			user_logic.set_wrb_desc_size(tp.qcfg.cmptsz);
			user_logic.configure_c2h(hw_qid, tx->packet_size, tx->num_packets);
			user_logic.set_wrb_desc_size(tp.qcfg.cmptsz);
			user_logic.set_imm_data_en(tp.qcfg.c2h_udd_en, device_type, ip_type);
			user_logic.generate_packets();

			const auto tx_size = tx->packet_size * tx->num_packets;

			EXPECT_NO_THROW(
					q.read(rd_buffer.data(), tx_size)
			)<< "c2h transfer returned with an error!";

			// compare packet data with expected
			auto cmp_result = std::memcmp(expected.data(), rd_buffer.data(), tx_size);
			EXPECT_EQ(0, cmp_result) << "packet data does not match expected pattern!\n"
					<< print_diffs(expected.cbegin(), expected.cend(), rd_buffer.cbegin())
                                        << user_logic.user_bar_reg_read();
		}
    }
    queues.erase(queues.begin(), queues.end());
#ifdef DPDK
    for(const auto& pf : tp.pfs){
    	if (pf.qmax){
    		//env.pfs[pf.dev_id].max_num_queues = 512;
    		rte_pmd_qdma_dev_close(pf.dev_id);
    	}
    }
#endif
}

static st_test_params desc_64b_test(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<st_test_params::transfer> transfers;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	transfers.reserve(1);
#ifdef DPDK
	std::vector<st_test_params::fmap> fmaps;
	uint32_t base = 0;
	fmaps.reserve(devlist.size());
#endif
	if (!devlist.size()) {
#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers), dev_type };
#else
	return st_test_params { std::move(transfers), dev_type};
#endif
	}
#ifdef DPDK
	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
			if (!devlist[pf_id].max_num_queues) {
				continue;
			}
			fmaps.emplace_back(devlist[pf_id].dev_id, base,devlist[pf_id].max_num_queues);
			base += devlist[pf_id].max_num_queues;
	}
#endif

	// setup random number generators
	std::default_random_engine rne((unsigned int)time(0));
	std::uniform_int_distribution<uint32_t> rng_func(0, (uint32_t)devlist.size() - 1);    // pf
	std::uniform_int_distribution<uint32_t> rng_nt(1, 8);    // no of transfers or iterations
	std::uniform_int_distribution<uint32_t> rng_ps(4_kB, 4_kB);
	std::uniform_int_distribution<uint32_t> rng_np(1, 8);    // no of packets

	for (uint32_t i = 0; i < 10; i++) {

		const auto func = rng_func(rne);
		if (!devlist[func].max_num_queues)
			continue;

		std::uniform_int_distribution<uint32_t> rng_q(0, devlist[func].max_num_queues - 1); // queue
		const auto qid = rng_q(rne);
	    const auto num_transfers = rng_nt(rne);
	    const auto packet_size = rng_ps(rne);
	    const auto num_packets = rng_np(rne);

		transfers.emplace_back(devlist[func].dev_id, qid, num_transfers, packet_size, num_packets, devlist[func]);
	}

#ifdef DPDK
	return st_test_params { std::move(fmaps), std::move(transfers), dev_type };
#else
	return st_test_params { std::move(transfers), dev_type};
#endif
}

TEST_P(qdma_st_64b_test, desc_bypass_imm_data_loopback) {

    const auto& tp = GetParam();
    const auto mode = qdma::queue_ext::mode::streaming;
    const auto h2c_dir = qdma::queue_ext::direction::host_to_card;
    const auto c2h_dir = qdma::queue_ext::direction::card_to_host;
    qdma::queue_ext::config h2c_qcfg;
    qdma::queue_ext::config c2h_qcfg;
    int cmptsz_map[] = {8, 16, 32, 64};
    std::string desc_string;
    std::string wrb_string;

    std::default_random_engine rne((unsigned int)time(0));
    std::uniform_int_distribution<uint32_t> rng_wbsz(0, 3);    // write back entry size

    qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
    // get the pf/vf device list based on dev_type
    std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
    ASSERT_FALSE(devlist.empty());

#ifdef DPDK
    struct rte_eth_conf	    port_conf;
    for(const auto& pf : tp.pfs){
        memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
        try{
            rte_eth_dev_configure(pf.dev_id, pf.qmax, pf.qmax, &port_conf);
        } catch (const std::exception& e){
            FAIL() << "Cannot configure port %d"<< pf.dev_id << e.what();
        }
    }
#endif

    for (const auto& tx : tp.transfers) {
        if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
            //GTEST_SKIP();
            std::cout << "Invalid Test Case" << std::endl;
            continue;
        }
        const auto device_type = get_device_type(tx.pf, devlist);
		const auto ip_type = get_ip_type(tx.pf, devlist);
#ifdef DPDK
        auto tx_size = tx.packet_size * tx.num_packets;
        const auto buf_sz = (tx_size / sizeof(pattern_t));
#else

#if defined(LINUX) || defined (_WIN32)
        auto& control_bar = *tx.qdev.dma_bar;
		uint32_t pidx_addr = 0;
        if (tp.devtype == qdma::instance_ext::type::pf)
            pidx_addr = 98308;
        else
            pidx_addr = 12292;
#endif
        int pidx_val = 0;
        unsigned int dump_descs_cnt = 0;



#endif
        example_design_ctrl user_logic{ tx.qdev };
        user_logic.reset_pkt_ctrl();
#ifdef DPDK
        const auto cmptsz = cmptsz_map[rng_wbsz(rne)];
        {
#else
        const auto cmptsz = rng_wbsz(rne);
#endif
        // setup buffers - using BRAM size as max transfer length, even though they are unrelated
        aligned_vector<pattern_t> wr_buffer(array_size);

        //tp.transfers.emplace_back(env.pfs[pf].dev_id, qid, num_transfers, packet_size, num_packets, env.pfs[pf]);

        h2c_qcfg.sw_desc_sz = XNL_ST_C2H_CMPT_DESC_SIZE_64B;
        h2c_qcfg.desc_bypass = true;
#ifdef _WIN32
		/* Same queue config parameters for both H2C and C2H */
		h2c_qcfg.cmptsz = static_cast<xnl_st_c2h_cmpt_desc_size>(cmptsz);
#endif
        qdma::queue_ext h2c_q(drv, tx.pf, tx.q, mode, h2c_dir, h2c_qcfg);

#ifndef _WIN32
		c2h_qcfg.c2h_udd_en = 1;
		c2h_qcfg.cmptsz = static_cast<xnl_st_c2h_cmpt_desc_size>(cmptsz);
		qdma::queue_ext c2h_q(drv, tx.pf, tx.q, mode, c2h_dir, c2h_qcfg);
#endif

        // setup user logic
#ifdef DPDK
        const auto hw_qid = get_hw_qid(tx.pf, tx.q);
#elif _WIN32
		const auto hw_qid = h2c_q.m_hwid;
#else
        const auto hw_qid = get_hw_qid(tx.pf, tx.q, devlist);
#endif
        user_logic.set_desc_bypass_imm_data_loopback(true);
        user_logic.set_st_loopback(false);

        for (unsigned i = 0; i < tx.it; i++) {

            for(unsigned j = 0; j < tx.num_packets; j++) {
#if defined(LINUX) || defined (_WIN32)
                //update PIDX
                pidx_val++;
                control_bar.write(pidx_addr + (tx.q*16), pidx_val);
#else
                //H2C transfer
                wr_buffer.resize(buf_sz);
                std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0));    // 0, 1, 2, 3, 4 ...
                    ASSERT_NO_THROW(
                        h2c_q.write(wr_buffer.data(), tx.packet_size);
                        )<< "h2c transfer returned with an error!";
#endif
                // Enable immediate data
                user_logic.set_wrb_desc_size(static_cast<xnl_st_c2h_cmpt_desc_size>(cmptsz));
                user_logic.configure_c2h(hw_qid, tx.packet_size, 1);
                usleep(500);
                user_logic.set_imm_data_en(true, device_type, ip_type);

                /* adding delay to make sure HW has generated the writeback entry */
                usleep(10000);
#ifdef DPDK
                //dpdk should initiate the rx burst
                ASSERT_NO_THROW(
                        c2h_q.read(rd_buffer.data(), tx.packet_size)
                       )<< "c2h transfer returned with an error!";
#endif
            }
        }

#ifdef DPDK
        }
        char source1, source2;
        char fln_in[50], fln_out[50];
        int i, mis_match = 0;
        int dz_len = XNL_ST_C2H_CMPT_DESC_SIZE_64B;
        uint32_t p = 0;

        sprintf(fln_in, "q_%d_%s", tx.q, "h2c_desc_data.txt");
        sprintf(fln_out, "q_%d_%s", tx.q, "immmediate_data.txt");

        FILE *fp1 = fopen(fln_in, "rb+");
        FILE *fp2 = fopen(fln_out, "rb+");

        if (fp1 != NULL && fp2 != NULL) {
            for (p = 0; p < (tx.num_packets * tx.it); p++) {
                fseek(fp1, p * dz_len, SEEK_SET);
                fseek(fp2, p * cmptsz, SEEK_SET);
                for (i = 0; i < cmptsz; i++) {
                    fread(&source1, 1, 1, fp1);
                    fread(&source2, 1, 1, fp2);

                    if (i == 0) {
                        source1 = source1 | 0x0f;
                        source2 = source2 | 0x0f;
                    }
                    if(source1 != source2) {
                        //printf("mismatch at %d\n", i);
                        mis_match = 1;
                        break;
                    }
                }
            }
            fclose(fp2);
            fclose(fp1);
        } else {
            mis_match = 1; // Fopen error
            if (fp1 != NULL)
                fclose(fp1);
            if (fp2 != NULL)
                fclose(fp2);
        }

        EXPECT_EQ(0, mis_match) << "desc data doesn't match the immediate data!\n";

        system("rm -rf q_*");
#elif defined(_WIN32)
		auto sw_desc_data = drv.dump_queue_desc(tx.qdev.dev_id, tx.q, h2c_dir, 1, 0, (pidx_val - 1));
		auto wrb_desc_data = drv.dump_queue_desc(tx.qdev.dev_id, tx.q, c2h_dir, 0, 0, (pidx_val - 1));

		/* Implementing a logic to fetch only the data portion of the q dump */
		std::ofstream desc_output_file("desc_output.txt");
		desc_output_file << sw_desc_data.c_str();
		std::ofstream wrb_output_file("wrb_output.txt");
		wrb_output_file << wrb_desc_data.c_str();
		desc_output_file.close();
		wrb_output_file.close();

		std::ifstream desc_input_file("desc_output.txt");
		std::ifstream wrb_input_file("wrb_output.txt");
		if (desc_input_file.good() && wrb_input_file.good()) {
			std::string desc_line, wrb_line;

			while (std::getline(desc_input_file, desc_line) && std::getline(wrb_input_file, wrb_line)) {
				dump_descs_cnt++;

				std::string dline = desc_line.substr(0, (cmptsz_map[cmptsz] * 2));

				desc_string += dline;
				wrb_string += wrb_line;

				if (dump_descs_cnt == (tx.it * tx.num_packets))
					break;
			}
		}
		desc_input_file.close();
		wrb_input_file.close();
		DeleteFile("desc_output.txt");
		DeleteFile("wrb_output.txt");

		EXPECT_NE(desc_string.empty(), true);
		EXPECT_NE(wrb_string.empty(), true);

		/* Comparing the data of both the strings */
		auto cmp_result = desc_string.compare(wrb_string);
		EXPECT_EQ(0, cmp_result) << "desc data doesn't match the immediate data!\n"
			<< print_diffs(desc_string.cbegin(), desc_string.cend(), wrb_string.cbegin());


#else
        auto sw_desc_data = drv.dump_queue_desc(tx.qdev.dev_id, tx.q, h2c_dir, 1, 0, pidx_val);
        auto wrb_desc_data = drv.dump_queue_desc(tx.qdev.dev_id, tx.q, c2h_dir, 0, 0, pidx_val);

        /* Implementing a logic to fetch only the data portion of the q dump */
        std::ofstream desc_output_file("desc_output.txt");
        desc_output_file << sw_desc_data.c_str();
        std::ofstream wrb_output_file("wrb_output.txt");
        wrb_output_file << wrb_desc_data.c_str();

        desc_output_file.close();
        wrb_output_file.close();

        std::ifstream desc_input_file ("desc_output.txt");
        std::ifstream wrb_input_file ("wrb_output.txt");
        if(desc_input_file.good() && wrb_input_file.good()) {
            std::string desc_line, wrb_line;

            std::getline(desc_input_file, desc_line);
            std::getline(wrb_input_file, wrb_line);
            while(std::getline(desc_input_file,desc_line) && std::getline(wrb_input_file,wrb_line)) {
                dump_descs_cnt++;
                std::istringstream desc_stream(desc_line);
                std::istringstream wrb_stream(wrb_line);
                std::string desc_str;
                std::string wrb_str;

                desc_stream>>desc_str;
                wrb_stream>>wrb_str;
                desc_stream>>desc_str;
                wrb_stream>>wrb_str;
                for(int i=0; i < cmptsz_map[cmptsz]/4; i++) {
                    desc_stream>>desc_str;
                    if(i == 0)
                        desc_str.back() = '0';
                    desc_string.append(desc_str);
                    wrb_stream>>wrb_str;
                    if(i == 0)
                        wrb_str.back() = '0';
                    wrb_string.append(wrb_str);
                }
                if(dump_descs_cnt == tx.it)
                    break;
            }
        }

        desc_input_file.close();
        wrb_input_file.close();

#ifdef _WIN32
		DeleteFile("desc_output.txt");
		DeleteFile("wrb_output.txt");
#else
		system("rm -rf desc_output.txt wrb_output.txt");
#endif

        /* Comparing the data of both the strings */
        auto cmp_result = desc_string.compare(wrb_string);
        EXPECT_EQ(0, cmp_result) << "desc data doesn't match the immediate data!\n"
                << print_diffs(desc_string.cbegin(), desc_string.cend(), wrb_string.cbegin());

#endif

        /* Reverting back the user logic register to default state */
        user_logic.set_desc_bypass_imm_data_loopback(false);
        user_logic.set_imm_data_en(false, device_type, ip_type);
    }
#ifdef DPDK
    for(const auto& pf : tp.pfs){
        if (pf.qmax){
            rte_pmd_qdma_dev_close(pf.dev_id);
        }
    }
#endif
}

// ====================== Test Parameter Definitions ===============================================


////open a queue , perform a transfer and close the queue. Do this for all the queues assigned to the PF
INSTANTIATE_TEST_CASE_P(ST002A_basic_dma_test, qdma_st_test, ::testing::Values(
        basic_dma_test(get_num_qs_per_pf(env.pfs))                    // all PF   all Q,
));

//open a queue , perform a transfer and close the queue. Do this for all the queues assigned to the PF
INSTANTIATE_TEST_CASE_P(VF_ST002A_basic_dma_test, qdma_st_test, ::testing::Values(
        basic_dma_test(get_num_qs_per_pf(env.vfs), qdma::instance_ext::type::vf)                    // all PF   all Q,
));

//open all the queues at once and perform a transfer
#ifdef DPDK
INSTANTIATE_TEST_CASE_P(ST002B_basic_dma_test, qdma_st_temp_test, ::testing::Values(
        basic_dma_test(get_num_qs_per_pf(env.pfs))                    // all PF   all Q,
));
INSTANTIATE_TEST_CASE_P(VF_ST002B_basic_dma_test, qdma_st_temp_test, ::testing::Values(
        basic_dma_test(get_num_qs_per_pf(env.vfs), qdma::instance_ext::type::vf)                    // all PF   all Q,
));
#else
INSTANTIATE_TEST_CASE_P(ST002B_basic_dma_test, qdma_st_temp_test, ::testing::Values(
        basic_dma_test(get_num_qs_per_pf(env.pfs))                    // all PF   all Q,
));

INSTANTIATE_TEST_CASE_P(VF_ST002B_basic_dma_test, qdma_st_temp_test, ::testing::Values(
        basic_dma_test(get_num_qs_per_pf(env.vfs), qdma::instance_ext::type::vf)                    // all PF   all Q,
));
#endif
//Test all the functions with a single queue( queue id 0) for the
//following tx sizes: 2 , 4K , 8K, 10K, 16K , 24K , 28K
INSTANTIATE_TEST_CASE_P(ST003_packet_sizes, qdma_st_test, ::testing::Values(
        // tx_offset, tx_size
        tx_param_test(2),
        tx_param_test(4_kB),
        tx_param_test(8_kB),
        tx_param_test(10_kB),
        tx_param_test(16_kB),
        tx_param_test(24_kB),
        tx_param_test(28_kB)
));

//Test all the functions with a single queue( queue id 0) for the
//following tx sizes: 2 , 4K , 8K, 10K, 16K , 24K , 28K
INSTANTIATE_TEST_CASE_P(VF_ST003_packet_sizes, qdma_st_test, ::testing::Values(
        // tx_offset, tx_size
        tx_param_test(2, qdma::instance_ext::type::vf),
        tx_param_test(4_kB, qdma::instance_ext::type::vf),
        tx_param_test(8_kB, qdma::instance_ext::type::vf),
        tx_param_test(10_kB, qdma::instance_ext::type::vf),
        tx_param_test(16_kB, qdma::instance_ext::type::vf),
        tx_param_test(24_kB, qdma::instance_ext::type::vf),
        tx_param_test(28_kB, qdma::instance_ext::type::vf)
));

//Test all the functions with a single queue( queue id 0) for different num packets
INSTANTIATE_TEST_CASE_P(ST004_num_packets, qdma_st_test, ::testing::Values(
        // tx_offset, tx_size
        tx_param_test(2, qdma::instance_ext::type::pf, 16),
        tx_param_test(4_kB, qdma::instance_ext::type::pf, 16),
        tx_param_test(8_kB, qdma::instance_ext::type::pf, 16),
        tx_param_test(10_kB, qdma::instance_ext::type::pf, 16),
        tx_param_test(16_kB, qdma::instance_ext::type::pf, 16),
        tx_param_test(24_kB, qdma::instance_ext::type::pf, 9),
        tx_param_test(28_kB, qdma::instance_ext::type::pf, 8)
));

//Test all the functions with a single queue( queue id 0) for different num packets
INSTANTIATE_TEST_CASE_P(VF_ST004_num_packets, qdma_st_test, ::testing::Values(
        // tx_offset, tx_size
        tx_param_test(2, qdma::instance_ext::type::vf, 16),
        tx_param_test(4_kB, qdma::instance_ext::type::vf, 16),
        tx_param_test(8_kB, qdma::instance_ext::type::vf, 16),
        tx_param_test(10_kB, qdma::instance_ext::type::vf, 16),
        tx_param_test(16_kB, qdma::instance_ext::type::vf, 16),
        tx_param_test(24_kB, qdma::instance_ext::type::vf, 9),
        tx_param_test(28_kB, qdma::instance_ext::type::vf, 8)
));

#ifdef DPDK
INSTANTIATE_TEST_CASE_P(CFG001_ST_ring_sizes, qdma_st_test, ::testing::Values(
        // ring_size, tx_size, num_tx
        ring_size_test(256, 4_kB, 1000),
        ring_size_test(256, 8_kB, 1),
        ring_size_test(512, 4_kB, 1000),
        ring_size_test(512, 8_kB, 1),
        ring_size_test(1024, 8_kB, 1000),
        ring_size_test(1024, 10_kB, 1000),
        ring_size_test(1024, 28_kB, 1000),
        ring_size_test(2048, 4_kB, 1),
        ring_size_test(4096, 4_kB, 1),
        ring_size_test(4096, 8_kB, 1)

//      TODO
//      ring_size_test(512, 4_kB ,2000),
//      ring_size_test(1024, 8_kB, 2000),
//      ring_size_test(2048, 10_kB, 2000)
));

INSTANTIATE_TEST_CASE_P(VF_CFG001_ST_ring_sizes, qdma_st_test, ::testing::Values(
        // ring_size, tx_size, num_tx
        ring_size_test(256, 4_kB, 1000,qdma::instance_ext::type::vf),
        ring_size_test(256, 4_kB, 1,qdma::instance_ext::type::vf),
        ring_size_test(512, 4_kB, 1000,qdma::instance_ext::type::vf),
        ring_size_test(512, 4_kB, 1,qdma::instance_ext::type::vf),
        ring_size_test(1024, 8_kB, 1000,qdma::instance_ext::type::vf),
        ring_size_test(1024, 10_kB, 1000,qdma::instance_ext::type::vf),
        ring_size_test(1024, 28_kB, 1000,qdma::instance_ext::type::vf),
        ring_size_test(2048, 4_kB, 1,qdma::instance_ext::type::vf),
        ring_size_test(4096, 4_kB, 1,qdma::instance_ext::type::vf),
        ring_size_test(4096, 8_kB, 1,qdma::instance_ext::type::vf)

//      TODO
//      ring_size_test(512, 4_kB ,2000),
//      ring_size_test(1024, 8_kB, 2000),
//      ring_size_test(2048, 10_kB, 2000)
));
#else
INSTANTIATE_TEST_CASE_P(CFG001_ST_ring_sizes, qdma_st_test, ::testing::Values(
        // ring_size, tx_size, num_tx
        ring_size_test(0, 4_kB ,1),
        ring_size_test(1, 4_kB ,1000),
        ring_size_test(2, 4_kB ,1000),
        ring_size_test(3, 4_kB ,1000),
        ring_size_test(4, 4_kB ,1),
        ring_size_test(5, 4_kB ,1),
        ring_size_test(6, 4_kB ,1),
        ring_size_test(7, 4_kB ,1),
        ring_size_test(8, 4_kB ,1),
        ring_size_test(9, 4_kB ,1)
));

INSTANTIATE_TEST_CASE_P(VF_CFG001_ST_ring_sizes, qdma_st_test, ::testing::Values(
        // ring_size, tx_size, num_tx
        ring_size_test(0, 4_kB ,1, qdma::instance_ext::type::vf),
        ring_size_test(1, 4_kB ,1, qdma::instance_ext::type::vf),
        ring_size_test(2, 4_kB ,1, qdma::instance_ext::type::vf),
        ring_size_test(3, 4_kB ,1, qdma::instance_ext::type::vf),
        ring_size_test(4, 4_kB ,1, qdma::instance_ext::type::vf),
        ring_size_test(5, 4_kB ,1, qdma::instance_ext::type::vf),
        ring_size_test(6, 4_kB ,1, qdma::instance_ext::type::vf),
        ring_size_test(7, 4_kB ,1, qdma::instance_ext::type::vf),
        ring_size_test(8, 4_kB ,1, qdma::instance_ext::type::vf),
        ring_size_test(9, 4_kB ,1, qdma::instance_ext::type::vf)
));
#endif


INSTANTIATE_TEST_CASE_P(ST006_completion_entry_size, qdma_st_c2h_test, ::testing::Values(
        // wrb desc size, packet_size
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_8B, 4_kB),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_8B, 64),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_8B, 8_kB),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_16B, 16_kB),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_16B, 64),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_16B, 28_kB),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_32B, 16_kB),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_32B, 64),
	completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_64B, 64),
	completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_64B, 4_kB),
	completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_64B, 16_kB),
	completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_64B, 28_kB)

));



INSTANTIATE_TEST_CASE_P(VF_ST006_completion_entry_size, qdma_st_c2h_test, ::testing::Values(
        // wrb desc size, packet_size
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_8B, 4_kB, qdma::instance_ext::type::vf),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_8B, 64, qdma::instance_ext::type::vf),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_8B, 8_kB, qdma::instance_ext::type::vf),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_16B, 16_kB, qdma::instance_ext::type::vf),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_16B, 64, qdma::instance_ext::type::vf),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_16B, 28_kB, qdma::instance_ext::type::vf),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_32B, 16_kB, qdma::instance_ext::type::vf),
        completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_32B, 64, qdma::instance_ext::type::vf),
	completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_64B, 64, qdma::instance_ext::type::vf),
	completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_64B, 4_kB, qdma::instance_ext::type::vf),
	completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_64B, 16_kB, qdma::instance_ext::type::vf),
	completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_64B, 28_kB, qdma::instance_ext::type::vf)

));

INSTANTIATE_TEST_CASE_P(ST007_st_randomized_transfers, qdma_st_test, ::testing::ValuesIn(
        randomized_tests(env.random_seed, 10)
));

INSTANTIATE_TEST_CASE_P(VF_ST007_st_randomized_transfers, qdma_st_test, ::testing::ValuesIn(
        randomized_tests(env.random_seed, 10, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(ST008_cache_bypass, qdma_st_test, ::testing::Values(
        // packet_size
		cache_bypass_test(2),
		cache_bypass_test(4_kB),
		cache_bypass_test(8_kB),
		cache_bypass_test(28_kB),
		cache_bypass_test(2, true, qdma::instance_ext::type::pf, 1),
		cache_bypass_test(4_kB, true, qdma::instance_ext::type::pf, 1),
		cache_bypass_test(8_kB, true, qdma::instance_ext::type::pf, 1),
		cache_bypass_test(28_kB, true, qdma::instance_ext::type::pf, 1)
));

INSTANTIATE_TEST_CASE_P(VF_ST008_cache_bypass, qdma_st_test, ::testing::Values(
        // packet_size
		cache_bypass_test(2, false, qdma::instance_ext::type::vf),
		cache_bypass_test(4_kB, false, qdma::instance_ext::type::vf),
		cache_bypass_test(8_kB, false, qdma::instance_ext::type::vf),
		cache_bypass_test(28_kB, false, qdma::instance_ext::type::vf),
		cache_bypass_test(2, true, qdma::instance_ext::type::vf, 1),
		cache_bypass_test(4_kB, true, qdma::instance_ext::type::vf, 1),
		cache_bypass_test(8_kB, true, qdma::instance_ext::type::vf, 1),
		cache_bypass_test(28_kB, true, qdma::instance_ext::type::vf, 1)
));

INSTANTIATE_TEST_CASE_P(ST009_desc_pfetch, qdma_st_c2h_test, ::testing::Values(
        // packet_size
        desc_pfetch_test(2),
        desc_pfetch_test(4_kB),
        desc_pfetch_test(8_kB),
        desc_pfetch_test(28_kB)
));

INSTANTIATE_TEST_CASE_P(VF_ST009_desc_pfetch, qdma_st_c2h_test, ::testing::Values(
        // packet_size
        desc_pfetch_test(2, qdma::instance_ext::type::vf),
        desc_pfetch_test(4_kB, qdma::instance_ext::type::vf),
        desc_pfetch_test(8_kB, qdma::instance_ext::type::vf),
        desc_pfetch_test(28_kB, qdma::instance_ext::type::vf)
));

//TODO: This test works with only  vu9p_g3x16_1525_c2h_simbyp_18.3_1030.bit. For other bitstream , it
//fails and becaus eof this , other tests also starts failing. So currently disabling it.
INSTANTIATE_TEST_CASE_P(ST014_simple_bypass, qdma_st_c2h_test, ::testing::Values(
        // packet_size
		simple_bypass_test(2),
		simple_bypass_test(4_kB),
		simple_bypass_test(8_kB),
		simple_bypass_test(28_kB),
		simple_bypass_test(2, true),
		simple_bypass_test(4_kB, true),
		simple_bypass_test(8_kB, true),
		simple_bypass_test(28_kB, true)
));

//TODO: This test works with only  vu9p_g3x16_1525_c2h_simbyp_18.3_1030.bit. For other bitstream , it
//fails and becaus eof this , other tests also starts failing. So currently disabling it.
INSTANTIATE_TEST_CASE_P(VF_ST014_simple_bypass, qdma_st_c2h_test, ::testing::Values(
        // packet_size
		/*
		simple_bypass_test(2),
		simple_bypass_test(4_kB),
		simple_bypass_test(8_kB),
		simple_bypass_test(28_kB),
		*/
		simple_bypass_test(2, false, qdma::instance_ext::type::vf),
		simple_bypass_test(4_kB, false, qdma::instance_ext::type::vf),
		simple_bypass_test(8_kB, false, qdma::instance_ext::type::vf),
		simple_bypass_test(28_kB, false, qdma::instance_ext::type::vf),

		simple_bypass_test(2, true, qdma::instance_ext::type::vf),
		simple_bypass_test(4_kB, true, qdma::instance_ext::type::vf),
		simple_bypass_test(8_kB, true, qdma::instance_ext::type::vf),
		simple_bypass_test(28_kB, true, qdma::instance_ext::type::vf)
));

#ifdef DPDK
INSTANTIATE_TEST_CASE_P(ST015_ovf_chk_dis, qdma_st_c2h_test, ::testing::Values(
		ovf_chk_dis_test(1024, 5, 4_kB ,4096, 1),
		ovf_chk_dis_test(1024, 5, 8_kB ,2048, 1)
));
INSTANTIATE_TEST_CASE_P(VF_ST015_ovf_chk_dis, qdma_st_c2h_test, ::testing::Values(
		ovf_chk_dis_test(1024, 5, 4_kB ,4096, 1, qdma::instance_ext::type::vf),
		ovf_chk_dis_test(1024, 5, 8_kB ,2048, 1, qdma::instance_ext::type::vf)
));
#else
INSTANTIATE_TEST_CASE_P(ST015_ovf_chk_dis, qdma_st_c2h_test, ::testing::Values(
        ovf_chk_dis_test(3, 5, 4_kB ,50, 60),
        ovf_chk_dis_test(3, 5, 8_kB ,50, 40)
));
INSTANTIATE_TEST_CASE_P(VF_ST015_ovf_chk_dis, qdma_st_c2h_test, ::testing::Values(
        ovf_chk_dis_test(3, 5, 4_kB ,50, 60, qdma::instance_ext::type::vf),
        ovf_chk_dis_test(3, 5, 8_kB ,50, 40, qdma::instance_ext::type::vf)
));
#endif

INSTANTIATE_TEST_CASE_P(ST005_zero_length_tx, qdma_st_test, ::testing::Values(
        // wrb desc size, packet_size
        tx_param_test(24_kB),
        tx_param_test(0)
));

INSTANTIATE_TEST_CASE_P(VF_ST005_zero_length_tx, qdma_st_test, ::testing::Values(
        // wrb desc size, packet_size
        tx_param_test(24_kB, qdma::instance_ext::type::vf),
        tx_param_test(0, qdma::instance_ext::type::vf)
));

#ifdef DPDK
INSTANTIATE_TEST_CASE_P(CFG004_c2h_tmr_cnt, qdma_st_c2h_test, ::testing::Values(
	// timer_cnt index, tx_size, num_tx
	// timer 5
	tmr_cnt_test(5, 4_kB - 1 ,1),
	tmr_cnt_test(5, 4_kB, 1),
	tmr_cnt_test(5, 4_kB + 1, 1),

    // timer 10
	tmr_cnt_test(10, 4_kB - 1 ,1),
	tmr_cnt_test(10, 4_kB, 1),
	tmr_cnt_test(10, 4_kB + 1, 1),

    // timer 30
	tmr_cnt_test(30, 4_kB - 1 ,1),
	tmr_cnt_test(30, 4_kB, 1),
	tmr_cnt_test(30, 4_kB + 1, 1),

    // timer 125
	tmr_cnt_test(125, 4_kB - 1 ,1),
	tmr_cnt_test(125, 4_kB, 1),
	tmr_cnt_test(125, 4_kB + 1, 1),

    // timer 50
	tmr_cnt_test(50, 4_kB - 1 ,1),
	tmr_cnt_test(50, 4_kB, 1),
	tmr_cnt_test(50, 4_kB + 1, 1),

    // timer 4
	tmr_cnt_test(4, 4_kB - 1 ,1),
	tmr_cnt_test(4, 4_kB, 1),
	tmr_cnt_test(4, 4_kB + 1, 1),

    // timer 1
	tmr_cnt_test(1, 4_kB - 1 ,1),
	tmr_cnt_test(1, 4_kB, 1),
	tmr_cnt_test(1, 4_kB + 1, 1),

    // timer 20
	tmr_cnt_test(20, 4_kB - 1 ,1),
	tmr_cnt_test(20, 4_kB, 1),
	tmr_cnt_test(20, 4_kB + 1, 1)
));
#else
INSTANTIATE_TEST_CASE_P(CFG004_c2h_tmr_cnt, qdma_st_c2h_test, ::testing::Values(
	// index 0
	tmr_cnt_test(0, 4_kB - 1 ,1),
	tmr_cnt_test(0, 4_kB, 1),
	tmr_cnt_test(0, 4_kB + 1, 1),

        // index 1
	tmr_cnt_test(1, 4_kB - 1 ,1),
	tmr_cnt_test(1, 4_kB, 1),
	tmr_cnt_test(1, 4_kB + 1, 1),

        // index 2
	tmr_cnt_test(2, 4_kB - 1 ,1),
	tmr_cnt_test(2, 4_kB, 1),
	tmr_cnt_test(2, 4_kB + 1, 1),

		// index 3
	tmr_cnt_test(3, 4_kB - 1 ,1),
	tmr_cnt_test(3, 4_kB, 1),
	tmr_cnt_test(3, 4_kB + 1, 1),

		// index 4
	tmr_cnt_test(4, 4_kB - 1 ,1),
	tmr_cnt_test(4, 4_kB, 1),
	tmr_cnt_test(4, 4_kB + 1, 1),

		// index 5
	tmr_cnt_test(5, 4_kB - 1 ,1),
	tmr_cnt_test(5, 4_kB, 1),
	tmr_cnt_test(5, 4_kB + 1, 1),

		// index 6
	tmr_cnt_test(6, 4_kB - 1 ,1),
	tmr_cnt_test(6, 4_kB, 1),
	tmr_cnt_test(6, 4_kB + 1, 1),

		// index 6
	tmr_cnt_test(7, 4_kB - 1 ,1),
	tmr_cnt_test(7, 4_kB, 1),
	tmr_cnt_test(7, 4_kB + 1, 1),

	// index 6
	tmr_cnt_test(8, 4_kB - 1 ,1),
	tmr_cnt_test(8, 4_kB, 1),
	tmr_cnt_test(8, 4_kB + 1, 1)
));
#endif

#ifdef DPDK
INSTANTIATE_TEST_CASE_P(VF_CFG004_c2h_tmr_cnt, qdma_st_c2h_test, ::testing::Values(
	// timer_cnt index, tx_size, num_tx
	// timer 5
	tmr_cnt_test(5, 4_kB - 1,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(5, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(5, 4_kB + 1, 1, qdma::instance_ext::type::vf),

	// timer 10
	tmr_cnt_test(10, 4_kB - 1,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(10, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(10, 4_kB + 1, 1, qdma::instance_ext::type::vf),

	// timer 30
	tmr_cnt_test(30, 4_kB - 1, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(30, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(30, 4_kB + 1, 1, qdma::instance_ext::type::vf),

	// timer 125
	tmr_cnt_test(125, 4_kB - 1 ,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(125, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(125, 4_kB + 1, 1, qdma::instance_ext::type::vf),

	// timer 50
	tmr_cnt_test(50, 4_kB - 1 ,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(50, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(50, 4_kB + 1, 1, qdma::instance_ext::type::vf),

	// timer 4
	tmr_cnt_test(4, 4_kB - 1 ,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(4, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(4, 4_kB + 1, 1, qdma::instance_ext::type::vf),

	// timer 1
	tmr_cnt_test(1, 4_kB - 1 ,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(1, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(1, 4_kB + 1, 1, qdma::instance_ext::type::vf),

	// timer 20
	tmr_cnt_test(20, 4_kB - 1 ,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(20, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(20, 4_kB + 1, 1, qdma::instance_ext::type::vf)
));
#else
INSTANTIATE_TEST_CASE_P(VF_CFG004_c2h_tmr_cnt, qdma_st_c2h_test, ::testing::Values(
	// index 0
	tmr_cnt_test(0, 4_kB - 1, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(0, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(0, 4_kB + 1, 1, qdma::instance_ext::type::vf),

        // index 1
	tmr_cnt_test(1, 4_kB - 1, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(1, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(1, 4_kB + 1, 1, qdma::instance_ext::type::vf),

        // index 2
	tmr_cnt_test(2, 4_kB - 1 ,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(2, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(2, 4_kB + 1, 1, qdma::instance_ext::type::vf),

		// index 3
	tmr_cnt_test(3, 4_kB - 1 ,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(3, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(3, 4_kB + 1, 1, qdma::instance_ext::type::vf),

		// index 4
	tmr_cnt_test(4, 4_kB - 1 ,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(4, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(4, 4_kB + 1, 1, qdma::instance_ext::type::vf),

		// index 5
	tmr_cnt_test(5, 4_kB - 1 ,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(5, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(5, 4_kB + 1, 1, qdma::instance_ext::type::vf),

		// index 6
	tmr_cnt_test(6, 4_kB - 1 ,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(6, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(6, 4_kB + 1, 1, qdma::instance_ext::type::vf),

	// index 7
	tmr_cnt_test(7, 4_kB - 1 ,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(7, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(7, 4_kB + 1, 1, qdma::instance_ext::type::vf),

	// index 8
	tmr_cnt_test(8, 4_kB - 1 ,1, qdma::instance_ext::type::vf),
	tmr_cnt_test(8, 4_kB, 1, qdma::instance_ext::type::vf),
	tmr_cnt_test(8, 4_kB + 1, 1, qdma::instance_ext::type::vf)
));
#endif

// counter threshold index, tx_size, num_tx
#ifdef DPDK
INSTANTIATE_TEST_CASE_P(CFG002_c2h_cntr_th, qdma_st_c2h_test, ::testing::Values(
	// counter 16
	cntr_th_test(16, 4_kB, 18),
	cntr_th_test(16, 4_kB + 2, 18),

	// counter 32
	cntr_th_test(32, 8_kB, 34),

	// counter 64
	cntr_th_test(64, 16_kB, 66),

	// counter 128
	cntr_th_test(128, 4_kB, 130),

	// counter 4
	cntr_th_test(4, 4_kB, 6)

));
#else
INSTANTIATE_TEST_CASE_P(CFG002_c2h_cntr_th, qdma_st_c2h_test, ::testing::Values(
	/*
	 * 	uint32_t cnt_th[QDMA_NUM_C2H_COUNTERS] = {2, 4, 8, 16, 24, 32, 48, 64,
	 *    			80, 96, 112, 128, 144, 160, 176, 192};
	 */

	cntr_th_test(2, 4_kB, 10),

	cntr_th_test(3, 4_kB, 18),

	cntr_th_test(7, 4_kB, 66),

	cntr_th_test(4, 4_kB, 26)
));
#endif


#ifdef DPDK
// counter threshold index, tx_size, num_tx
INSTANTIATE_TEST_CASE_P(VF_CFG002_c2h_cntr_th, qdma_st_c2h_test, ::testing::Values(
	// counter 16
	cntr_th_test(16, 4_kB, 18, qdma::instance_ext::type::vf),
	cntr_th_test(16, 4_kB + 2, 18, qdma::instance_ext::type::vf),

	// counter 32
	cntr_th_test(32, 8_kB, 34, qdma::instance_ext::type::vf),

	// counter 64
	cntr_th_test(64, 16_kB, 66, qdma::instance_ext::type::vf),

	// counter 128
	cntr_th_test(128, 4_kB, 130, qdma::instance_ext::type::vf),

	// counter 4
	cntr_th_test(4, 4_kB, 6, qdma::instance_ext::type::vf)

));
#else
INSTANTIATE_TEST_CASE_P(VF_CFG002_c2h_cntr_th, qdma_st_c2h_test, ::testing::Values(
		/*
		 * 	uint32_t cnt_th[QDMA_NUM_C2H_COUNTERS] = {2, 4, 8, 16, 24, 32, 48, 64,
		 *    			80, 96, 112, 128, 144, 160, 176, 192};
		 */
		cntr_th_test(2, 4_kB, 10, qdma::instance_ext::type::vf),

		cntr_th_test(3, 4_kB, 18, qdma::instance_ext::type::vf),

		cntr_th_test(7, 4_kB, 66, qdma::instance_ext::type::vf),

		cntr_th_test(4, 4_kB, 26, qdma::instance_ext::type::vf)
));
#endif

#ifdef LINUX
INSTANTIATE_TEST_CASE_P(CFG003_c2h_buf_sz, qdma_st_c2h_test, ::testing::Values(
	// buf sz index, tx_size, num_tx
	// Only buffers of PAGE_SIZE and abvoe are supported !
	// As this is 16bit register, only 4k to 32k are supported
	//
	buf_size_test(2, 1_kB ,1), /* 512 */
	buf_size_test(3, 2_kB, 1), /* 1024 */
	buf_size_test(4, 4_kB, 1), /* 2048 */
	//buf_size_test(5, 4_kB, 1), /* 3968 */
	buf_size_test(6, 4_kB, 1) /* 4096 */
));
#elif _WIN32
INSTANTIATE_TEST_CASE_P(CFG003_c2h_buf_sz, qdma_st_c2h_test, ::testing::Values(
    // buf sz index, tx_size, num_tx
    // Only buffers of PAGE_SIZE and abvoe are supported !
    // As this is 16bit register, only 4k to 32k are supported
    //
    buf_size_test(1, 256, 1), /* 256 */
    buf_size_test(2, 512, 1), /* 512 */
    buf_size_test(3, 1_kB, 1), /* 1024 */
    buf_size_test(4, 2_kB, 1), /* 2048 */
    buf_size_test(5, 3_kB, 1), /* 3968 */
    buf_size_test(6, 4_kB, 1)  /* 4096 */
));
#else
INSTANTIATE_TEST_CASE_P(CFG003_c2h_buf_sz, qdma_st_c2h_test, ::testing::Values(
	// buf sz index, tx_size, num_tx
//	buf_size_test(256, 4_kB ,1),
//	buf_size_test(512, 4_kB ,1)
	buf_size_test(1024, 4_kB ,1),
	buf_size_test(2048, 4_kB, 1),
	buf_size_test(4096, 4_kB, 1),
	buf_size_test(8192, 4_kB, 1)
));
#endif

#ifdef LINUX
INSTANTIATE_TEST_CASE_P(VF_CFG003_c2h_buf_sz, qdma_st_c2h_test, ::testing::Values(
	// buf sz index, tx_size, num_tx
	// Only buffers of PAGE_SIZE and abvoe are supported !
	// As this is 16bit register, only 4k to 32k are supported
	//
	buf_size_test(2, 1_kB ,1, qdma::instance_ext::type::vf), /* 512 */
	buf_size_test(3, 2_kB, 1, qdma::instance_ext::type::vf), /* 1024 */
	buf_size_test(4, 4_kB, 1, qdma::instance_ext::type::vf), /* 2048 */
	//buf_size_test(5, 4_kB, 1, qdma::instance_ext::type::vf), /* 3968 */
	buf_size_test(6, 4_kB, 1, qdma::instance_ext::type::vf) /* 4096 */
));
#else
INSTANTIATE_TEST_CASE_P(VF_CFG003_c2h_buf_sz, qdma_st_c2h_test, ::testing::Values(
	// buf sz index, tx_size, num_tx
//	buf_size_test(256, 4_kB ,1),
//	buf_size_test(512, 4_kB ,1)
	buf_size_test(1024, 4_kB ,1, qdma::instance_ext::type::vf),
	buf_size_test(2048, 4_kB, 1, qdma::instance_ext::type::vf),
	buf_size_test(4096, 4_kB, 1, qdma::instance_ext::type::vf),
	buf_size_test(8192, 4_kB, 1, qdma::instance_ext::type::vf)
));
#endif


INSTANTIATE_TEST_CASE_P(ST010_test_generic, qdma_st_generic_test, ::testing::Values(
	generic_tests()
));

INSTANTIATE_TEST_CASE_P(VF_ST010_test_generic, qdma_st_generic_test, ::testing::Values(
	generic_tests(qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(ST016_64B_desc, qdma_st_64b_test, ::testing::Values(
	desc_64b_test()
));

INSTANTIATE_TEST_CASE_P(VF_ST016_64B_desc, qdma_st_64b_test, ::testing::Values(
	desc_64b_test(qdma::instance_ext::type::vf)
));

#ifdef DPDK
INSTANTIATE_TEST_CASE_P(NT007A_ST_ring_sizes, qdma_neg_st_ring_size_test, ::testing::Values(

        multi_param_test(7, 1024, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr)
));
INSTANTIATE_TEST_CASE_P(VF_NT007A_ST_ring_sizes, qdma_neg_st_ring_size_test, ::testing::Values(

        multi_param_test(7, 1024, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr, qdma::instance_ext::type::vf)
));
INSTANTIATE_TEST_CASE_P(NT007B_ST_buf_sizes, qdma_neg_inv_buf_size_test, ::testing::Values(
        multi_param_test(256, 100, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr)
));
INSTANTIATE_TEST_CASE_P(VF_NT007B_ST_buf_sizes, qdma_neg_inv_buf_size_test, ::testing::Values(
        multi_param_test(256, 100, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr, qdma::instance_ext::type::vf)
));
INSTANTIATE_TEST_CASE_P(NT007C_ST_tmr_cnt, qdma_neg_inv_tmr_cnt_test, ::testing::Values(
        multi_param_test(256, 1024, 4_kB, 40, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr)
));
INSTANTIATE_TEST_CASE_P(VF_NT007C_ST_tmr_cnt, qdma_neg_inv_tmr_cnt_test, ::testing::Values(
        multi_param_test(256, 1024, 4_kB, 40, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(NT010_ST_invalid_qid_queue_add, qdma_neg_add_inv_qid_test, ::testing::Values(
        multi_param_test(256, 1024, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr)
));
INSTANTIATE_TEST_CASE_P(VF_NT010_ST_invalid_qid_queue_add, qdma_neg_add_inv_qid_test, ::testing::Values(
        multi_param_test(256, 1024, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(NT011_ST_invalid_qid_queue_start, qdma_neg_start_inv_qid_test, ::testing::Values(
        multi_param_test(256, 1024, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr)
));
INSTANTIATE_TEST_CASE_P(VF_NT011_ST_invalid_qid_queue_start, qdma_neg_start_inv_qid_test, ::testing::Values(
        multi_param_test(256, 1024, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(NT012_ST_invalid_qid_queue_stop, qdma_neg_stop_inv_qid_test, ::testing::Values(
        multi_param_test(256, 1024, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr)
));
INSTANTIATE_TEST_CASE_P(VF_NT012_ST_invalid_qid_queue_stop, qdma_neg_stop_inv_qid_test, ::testing::Values(
        multi_param_test(256, 1024, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(NT014_ST_invalid_qid_queue_dump, qdma_neg_dump_inv_qid_test, ::testing::Values(
        multi_param_test(256, 1024, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr)
));
INSTANTIATE_TEST_CASE_P(VF_NT014_ST_invalid_qid_queue_dump, qdma_neg_dump_inv_qid_test, ::testing::Values(
        multi_param_test(256, 1024, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr, qdma::instance_ext::type::vf)
));
INSTANTIATE_TEST_CASE_P(DISABLED_NT009B_ST_read_write_without_start, qdma_neg_proc_without_start_test, ::testing::Values(
        multi_param_test(256, 1024, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr)
));
INSTANTIATE_TEST_CASE_P(DISABLED_VF_NT009B_ST_read_write_without_start, qdma_neg_proc_without_start_test, ::testing::Values(
        multi_param_test(256, 1024, 4_kB, 30, 64, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(DISABLED_NT016_ST_overflow_test, qdma_st_test, ::testing::Values(
        st_negative_overflow_test(256, 512_kB ,1000)
));

INSTANTIATE_TEST_CASE_P(DISABLED_VF_NT016_ST_overflow_test, qdma_st_test, ::testing::Values(
        st_negative_overflow_test(256, 512_kB ,1000, qdma::instance_ext::type::vf)
));
#elif _WIN32
INSTANTIATE_TEST_CASE_P(DISABLED_NT009B_ST_read_write_without_start, qdma_neg_proc_without_start_test, ::testing::Values(
        multi_param_test(4, 0, 4_kB, 9, 0, qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr)
));

INSTANTIATE_TEST_CASE_P(DISABLED_NT016_ST_overflow_test, qdma_neg_read_write_overflow, ::testing::Values(
    st_negative_overflow_test(1, 4_kB, 100)
));
#endif
