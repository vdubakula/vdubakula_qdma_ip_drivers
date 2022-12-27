#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <random>

#include <gtest/gtest.h>

#include "example_design_ctrl.h"
#include "qdma_instance.h"
#include "qdma_queue.h"
#include "test_env.h"
#include "xlnx_gtest_ext.h"
#include "xlnx_util.h"

#define NUM_DEV_TYPES 2
#define CMPT_DESC_ENTRY_MASK 0xF0
// ===============================Test framework helpers ==========================================

extern test_env env; // in main.cpp

struct test_params {

	struct transfer {
		uint32_t pf = 0;
		uint32_t q = 0;
		uint32_t it = 0;
		uint32_t offset = 0;
		uint32_t size = 0;
		qdma::device& qdev;

		transfer(uint32_t pf_id, uint32_t q_id, uint32_t iterations, uint32_t offs, uint32_t ts, qdma::device& _qdev=env.pfs.front())
		: pf(pf_id), q(q_id), it(iterations), offset(offs), size(ts), qdev(_qdev) {}
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

test_params() = default;
#ifdef DPDK
test_params(std::vector<fmap>&& fmaps, std::vector<transfer>&& txs, qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
: pfs(std::move(fmaps)), transfers(std::move(txs)), qcfg(_qcfg) {
}
test_params(std::vector<fmap>&& fmaps, std::vector<transfer>&& txs, qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf, qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
: pfs(std::move(fmaps)), transfers(std::move(txs)), devtype(dev_type), qcfg(_qcfg) {
}
#else
test_params(std::vector<transfer>&& txs, qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
: transfers(std::move(txs)), qcfg(_qcfg) {
}
test_params(std::vector<transfer>&& txs, qdma::instance_ext::type dev_type, qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
: transfers(std::move(txs)), devtype(dev_type), qcfg(_qcfg) {
}
#endif
};


void PrintTo(const test_params& tp, std::ostream* os) {
	const auto& txs = tp.transfers;

	//only print the ranges (first and last entry)
	if (!txs.empty()) {
		if (tp.devtype == qdma::instance_ext::type::vf)
			*os << "{ vfs=[";
		else
			*os << "{ pfs=[";
		*os << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.front().pf
				<< ":" << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.back().pf << "], ";
		*os << "queues=[" << txs.front().q << ":" << txs.back().q << "], ";
		*os << "iterations=" << txs.front().it << ", ";
		*os << "tx_offset=" << txs.front().offset << ", ";
		*os << "tx_size=" << txs.front().size << " }";
	}

	//    print full test param structure
	//    *os << "[ ";
	//    for (const auto& tx : txs) {
	//        *os << "{ pf=" << tx.pf << ", ";
	//        *os << "q=" << tx.q << ", ";
	//        *os << "it=" << tx.it << ", ";
	//        *os << "offs=" << tx.offset << ", ";
	//        *os << "size=" << tx.size << " }, ";
	//    }
	//    *os << "]\n";
}

class qdma_mm_test: public testing::TestWithParam<test_params> {
public:
	void SetUp() override {

		wr_buffer.resize(array_size);
		rd_buffer.resize(array_size);
		expected.resize(array_size);

		std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
		std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
		std::iota(expected.begin(), expected.end(), static_cast<pattern_t>(0));   // 0, 1, 2, 3, 4 ...

	}

	using pattern_t = uint8_t;
	static const auto mode = qdma::queue_ext::mode::memory_mapped;
	static const auto array_size = example_design_ctrl::bram_size / sizeof(pattern_t);
	aligned_vector<pattern_t> wr_buffer;
	aligned_vector<pattern_t> rd_buffer;
	aligned_vector<pattern_t> expected;
};

class qdma_neg_mm_overflow_test: public testing::TestWithParam<test_params> {
public:
	void SetUp() override {

		wr_buffer.resize(array_size);
		rd_buffer.resize(array_size);
		expected.resize(array_size);

		std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
		std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
		std::iota(expected.begin(), expected.end(), static_cast<pattern_t>(0));   // 0, 1, 2, 3, 4 ...

	}

	using pattern_t = uint8_t;
	static const auto mode = qdma::queue_ext::mode::memory_mapped;
	static const auto array_size = example_design_ctrl::bram_size / sizeof(pattern_t);
	aligned_vector<pattern_t> wr_buffer;
	aligned_vector<pattern_t> rd_buffer;
	aligned_vector<pattern_t> expected;
};

class qdma_mm_cmpt_test: public testing::TestWithParam<test_params> {
public:
	virtual void SetUp() override {

		wr_buffer.resize(array_size);
		rd_buffer.resize(array_size);
		expected.resize(array_size);

		std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
		std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
		std::iota(expected.begin(), expected.end(), static_cast<pattern_t>(0));   // 0, 1, 2, 3, 4 ...

	}

	virtual void TearDown() override {

	}

	std::vector<qdma::queue_ext> queues;
	using pattern_t = uint8_t;
	static const auto mode = qdma::queue_ext::mode::memory_mapped;
	static const auto array_size = example_design_ctrl::bram_size / sizeof(pattern_t);
	aligned_vector<pattern_t> wr_buffer;
	aligned_vector<pattern_t> rd_buffer;
	aligned_vector<pattern_t> expected;
};

class qdma_mm_temp_test: public testing::TestWithParam<test_params> {
public:
	virtual void SetUp() override {

		wr_buffer.resize(array_size);
		rd_buffer.resize(array_size);
		expected.resize(array_size);

		std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
		std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
		std::iota(expected.begin(), expected.end(), static_cast<pattern_t>(0));   // 0, 1, 2, 3, 4 ...

	}

	virtual void TearDown() override {

	}

	std::vector<qdma::queue_ext> queues;
	using pattern_t = uint8_t;
	static const auto mode = qdma::queue_ext::mode::memory_mapped;
	static const auto array_size = example_design_ctrl::bram_size / sizeof(pattern_t);
	aligned_vector<pattern_t> wr_buffer;
	aligned_vector<pattern_t> rd_buffer;
	aligned_vector<pattern_t> expected;
};

class qdma_neg_mm_inv_ring_size_test: public testing::TestWithParam<test_params> {
public:
	virtual void SetUp() override {

		wr_buffer.resize(array_size);
		rd_buffer.resize(array_size);
		expected.resize(array_size);

		std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
		std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
		std::iota(expected.begin(), expected.end(), static_cast<pattern_t>(0));   // 0, 1, 2, 3, 4 ...

	}

	virtual void TearDown() override {

	}

	std::vector<qdma::queue_ext> queues;
	using pattern_t = uint8_t;
	static const auto mode = qdma::queue_ext::mode::memory_mapped;
	static const auto array_size = example_design_ctrl::bram_size / sizeof(pattern_t);
	aligned_vector<pattern_t> wr_buffer;
	aligned_vector<pattern_t> rd_buffer;
	aligned_vector<pattern_t> expected;
};

class qdma_neg_mm_proc_without_start_test: public testing::TestWithParam<test_params> {
public:
	virtual void SetUp() override {

		wr_buffer.resize(array_size);
		rd_buffer.resize(array_size);
		expected.resize(array_size);

		std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
		std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
		std::iota(expected.begin(), expected.end(), static_cast<pattern_t>(0));   // 0, 1, 2, 3, 4 ...

	}

	virtual void TearDown() override {

	}

	std::vector<qdma::queue_ext> queues;
	using pattern_t = uint8_t;
	static const auto mode = qdma::queue_ext::mode::memory_mapped;
	static const auto array_size = example_design_ctrl::bram_size / sizeof(pattern_t);
	aligned_vector<pattern_t> wr_buffer;
	aligned_vector<pattern_t> rd_buffer;
	aligned_vector<pattern_t> expected;
};

class qdma_neg_inv_qid_ops : public testing::TestWithParam<test_params> {
public:
    virtual void SetUp() override {

    }

    virtual void TearDown() override {

    }

    std::vector<qdma::queue_ext> queues;
    using pattern_t = uint8_t;
    static const auto mode = qdma::queue_ext::mode::memory_mapped;
};

TEST_P(qdma_neg_mm_inv_ring_size_test, h2c_c2h) {

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
		enum rte_pmd_qdma_queue_mode_t queue_mode = RTE_PMD_QDMA_MEMORY_MAPPED_MODE;
		uint32_t		nb_buff;
		int test_status = 0;

		/** Mbuf packet pool **/
		nb_buff = ((tp.qcfg.idx_rngsz));

		nb_buff += (6 * NUM_RX_PKTS);

		/* Configure mbuf packet pool with minimum 2K size */
		nb_buff = RTE_MAX(nb_buff, (RTE_MEMPOOL_CACHE_MAX_SIZE * 1.5));

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

static test_params basic_dma_test(const std::vector<uint32_t> &num_qs_per_pf, qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {
	std::vector<test_params::transfer> transfers;
	auto num_transfer = 0;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

#ifdef DPDK
	std::vector<test_params::fmap> fmaps;
	uint32_t base = 0;
#endif
	for (uint32_t pf_id = 0; pf_id < num_qs_per_pf.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
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
	if (!devlist[pf_id].max_num_queues) {
		continue;
	}
	if (devlist[pf_id].max_num_queues < num_qs_per_pf[pf_id])
		continue;
	for (uint32_t qid = 0; qid < num_qs_per_pf[pf_id]; qid++) {
		transfers.emplace_back(devlist[pf_id].dev_id, qid, 1, 0, 4_kB, devlist[pf_id]);
	}
}

#ifdef DPDK
return test_params { std::move(fmaps), std::move(transfers), dev_type };
#else
return test_params { std::move(transfers) , dev_type};
#endif
}

static test_params tx_param_test(const uint32_t tx_offset, const uint32_t tx_size,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {
	std::vector<test_params::transfer> transfers;
#ifdef DPDK
	std::vector<test_params::fmap> fmaps;
	uint32_t base = 0;

	fmaps.reserve(env.pfs.size());
#endif
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	transfers.reserve(devlist.size());

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
#ifdef DPDK
		fmaps.emplace_back(devlist[pf_id].dev_id, base, 1);
		base += 1;
#endif
		transfers.emplace_back(devlist[pf_id].dev_id, 0, 1, tx_offset, tx_size, devlist[pf_id]);
	}

#ifdef DPDK
	return test_params { std::move(fmaps), std::move(transfers), dev_type };
#else
	return test_params { std::move(transfers), dev_type };
#endif

}


static test_params mm_cmpt_ovf_chk_dis_test(const uint32_t ring_size, const uint32_t tx_size,
		const uint32_t num_transfers, qdma::instance_ext::type dev_type=qdma::instance::type::pf) {
	std::vector<test_params::transfer> transfers;
	qdma::queue_ext::config qcfg;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

#ifdef DPDK
	std::vector<test_params::fmap> fmaps;
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
		transfers.emplace_back(devlist[pf_id].dev_id, 0, num_transfers, 0, tx_size, devlist[pf_id]);

	}

	qcfg.idx_rngsz = ring_size;
	qcfg.c2h_ovf_chk_dis = true;

#ifdef DPDK
	return test_params { std::move(fmaps), std::move(transfers), dev_type, qcfg };
#else
	return test_params { std::move(transfers), dev_type, qcfg };
#endif

}


static test_params timer_cnt_test(const uint32_t idx_timer_cnt, const uint32_t tx_size,
		const uint32_t num_transfers,
	qdma::instance_ext::type dev_type=qdma::instance::type::pf) {
	std::vector<test_params::transfer> transfers;
	qdma::queue_ext::config qcfg;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

#ifdef DPDK
	std::vector<test_params::fmap> fmaps;
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
		transfers.emplace_back(devlist[pf_id].dev_id, 0, num_transfers, 0, tx_size, devlist[pf_id]);
	}

	qcfg.idx_tmr = idx_timer_cnt;
	qcfg.trigmode  = qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr;


#ifdef DPDK
	return test_params { std::move(fmaps), std::move(transfers), dev_type, qcfg };
#else
	return test_params { std::move(transfers), dev_type, qcfg };
#endif

}

#if defined (DPDK)
static test_params negative_overflow_test(const uint32_t ring_size, const uint32_t tx_size,
		const uint32_t num_transfers, qdma::instance_ext::type dev_type=qdma::instance::type::pf) {
	std::vector<test_params::transfer> transfers;
	qdma::queue_ext::config qcfg;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

#ifdef DPDK
	std::vector<test_params::fmap> fmaps;
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
		transfers.emplace_back(devlist[pf_id].dev_id, 0, num_transfers, 0, tx_size, devlist[pf_id]);

	}

	qcfg.idx_rngsz = ring_size;
#ifndef _WIN32
	qcfg.burst_size = 512;
#endif
	qcfg.idx_bufsz = 1024;
#ifdef DPDK
	return test_params { std::move(fmaps), std::move(transfers), dev_type, qcfg };
#else
	return test_params { std::move(transfers), dev_type, qcfg };
#endif

}
#endif

static test_params ring_size_test(const uint32_t ring_size, const uint32_t tx_size,
		const uint32_t num_transfers, qdma::instance_ext::type dev_type=qdma::instance::type::pf) {
	std::vector<test_params::transfer> transfers;
	qdma::queue_ext::config qcfg;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

#ifdef DPDK
	std::vector<test_params::fmap> fmaps;
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
		transfers.emplace_back(devlist[pf_id].dev_id, 0, num_transfers, 0, tx_size, devlist[pf_id]);

	}

	qcfg.idx_rngsz = ring_size;

#ifdef DPDK
	return test_params { std::move(fmaps), std::move(transfers), dev_type, qcfg };
#else
	return test_params { std::move(transfers), dev_type, qcfg };
#endif

}

static test_params desc_bypass_test(const uint32_t q_id, const uint32_t num_tx,
		const uint32_t tx_size, qdma::instance_ext::type dev_type=qdma::instance::type::pf) {

	std::vector<test_params::transfer> transfers;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
#ifdef DPDK
	std::vector<test_params::fmap> fmaps;
	uint32_t base = 0;

	fmaps.reserve(env.pfs.size());
#endif
	qdma::queue_ext::config qcfg;

	transfers.reserve(devlist.size());
	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;
#ifdef DPDK
		fmaps.emplace_back(devlist[pf_id].dev_id, base, 1);
		base += 1;
#endif
		transfers.emplace_back(devlist[pf_id].dev_id, q_id, num_tx, 0, tx_size, devlist[pf_id]);
	}

	qcfg.desc_bypass = true;

#ifdef DPDK
	return test_params { std::move(fmaps), std::move(transfers), dev_type, qcfg};
#else
	return test_params { std::move(transfers), dev_type, qcfg };
#endif

}


static std::vector<test_params> randomized_tests(const uint32_t seed, const uint32_t num_tests, qdma::instance::type dev_type=qdma::instance::type::pf) {

	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
    // setup random number generators
    std::default_random_engine rne(seed);
    std::uniform_int_distribution<uint32_t> rng_pf(0, (uint32_t)devlist.size() - 1);    // pf
    std::uniform_int_distribution<uint32_t> rng_it(1, 1000);    // iterations
    std::uniform_int_distribution<uint32_t> rng_ts(1, example_design_ctrl::bram_size);    // transfer size

	std::vector<test_params> tp;
	for (uint32_t i = 0; i < num_tests; i++) {

		if (!devlist.size())
			continue;

		const auto pf = rng_pf(rne);

		if (!devlist[pf].max_num_queues)
			continue;

#ifdef DPDK
		std::vector<test_params::fmap> fmaps;
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
		const auto transfer_size = rng_ts(rne);

		std::vector<test_params::transfer> transfers;
		transfers.emplace_back(devlist[pf].dev_id, qid, num_transfers, 0, transfer_size, devlist[pf]);

#ifdef DPDK
		tp.emplace_back(std::move(fmaps), std::move(transfers), dev_type);
#else
		tp.emplace_back(std::move(transfers), dev_type);
#endif
	}
	return tp;
}


// ====================== Test Cases ==============================================================

TEST_P(qdma_neg_mm_proc_without_start_test, h2c_c2h) {

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
        /* MM read/write without queue add and start */
        {
            qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
            const auto dir = qdma::queue_ext::direction::both;
            static const auto mode = qdma::queue_ext::mode::memory_mapped;
            bool no_add_start_queue = true;

            /* Queue constructor called, but queue not added */
            qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg, no_add_start_queue);

            auto len = q.write(wr_buffer.data(), tx.size, 0, false);
            EXPECT_EQ(0, len) << "qdma_neg_mm_proc_without_start_test part-1 test case failed!\n";

            len = q.read(rd_buffer.data(), tx.size, 0, false);
            EXPECT_EQ(0, len) << "qdma_neg_mm_proc_without_start_test part-1 test case failed!\n";
        }
        /* MM read/write with queue add and without queue start */
        {
            qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
            const auto dir = qdma::queue_ext::direction::both;
            static const auto mode = qdma::queue_ext::mode::memory_mapped;
            bool no_add_start_queue = true;

            /* Queue constructor called, but queue not added */
            qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg, no_add_start_queue);

            auto res = drv.add_queue(tx.pf, tx.q, 1, mode, dir, tp.qcfg);
            EXPECT_EQ(1, res) << "drv.add_queue part-2 test case failed!\n";


            auto len = q.write(wr_buffer.data(), tx.size, 0, false);
            EXPECT_EQ(0, len) << "qdma_neg_mm_proc_without_start_test part-2 test case failed!\n";

            len = q.read(rd_buffer.data(), tx.size, 0, false);
            EXPECT_EQ(0, len) << "qdma_neg_mm_proc_without_start_test part-2 test case failed!\n";

            drv.remove_queue(tx.pf, tx.q, dir);
        }
#elif DPDK
		struct rte_mempool			*mbuf_pool;
		struct rte_eth_txconf		tx_conf;
		struct rte_eth_rxconf		rx_conf;
		int							ret;
		char	mem_pool[RTE_MEMPOOL_NAMESIZE];
		enum rte_pmd_qdma_queue_mode_t queue_mode = RTE_PMD_QDMA_MEMORY_MAPPED_MODE;
		uint32_t		nb_buff;
		int test_status = 0;

		/** Mbuf packet pool **/
		nb_buff = ((tp.qcfg.idx_rngsz));

		nb_buff += (6 * NUM_RX_PKTS);

		/* Configure mbuf packet pool with minimum 2K size */
		nb_buff = RTE_MAX(nb_buff, (RTE_MEMPOOL_CACHE_MAX_SIZE * 1.5));

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

		struct rte_mbuf *pkts[NUM_RX_PKTS] = { NULL };
		int nb_rx = 0;

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
		// freeing up rx memory
		for (i = 0; i < nb_rx; i++) {
				struct rte_mbuf *mb = pkts[i];
				while (mb != NULL){
					rte_pktmbuf_free(mb);
				}
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

TEST_P(qdma_neg_inv_qid_ops, q_add) {
    const auto& tp = GetParam();
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
#ifdef _WIN32
        /* Opening a queue file with invalid qid */
        {
            qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
            const auto dir = qdma::queue_ext::direction::both;
            static const auto mode = qdma::queue_ext::mode::memory_mapped;
            bool no_add_start_queue = true;

            /* Queue constructor called, but queue not added */
            qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg, no_add_start_queue);

            /* Force an Invalid Queue ID */
            auto forced_invalid_qid = 513; /* 0 to 511 are valid queue ids for any PF */

            auto ret = drv.add_queue(tx.pf, forced_invalid_qid, 1, mode, dir, tp.qcfg, false);
            EXPECT_EQ(0, ret) << "Invalid qid add test failed!\n";
        }
#endif
    }
}

TEST_P(qdma_neg_inv_qid_ops, q_start) {
    const auto& tp = GetParam();
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
#ifdef _WIN32
        /* Opening a queue file with invalid qid */
        {
            qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
            const auto dir = qdma::queue_ext::direction::both;
            static const auto mode = qdma::queue_ext::mode::memory_mapped;
            bool no_add_start_queue = true;

            /* Queue constructor called, but queue not added */
            qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg, no_add_start_queue);

            /* Force an Invalid Queue ID */
            auto forced_invalid_qid = 513; /* 0 to 511 are valid queue ids for any PF */

            auto ret = drv.start_queue(tx.pf, forced_invalid_qid, mode, dir, tp.qcfg, false);
            EXPECT_EQ(0, ret) << "Invalid qid start test failed!\n";
        }
#endif
    }
}

TEST_P(qdma_neg_inv_qid_ops, q_stop) {
    const auto& tp = GetParam();
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
#ifdef _WIN32
        /* Opening a queue file with invalid qid */
        {
            qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
            const auto dir = qdma::queue_ext::direction::both;
            static const auto mode = qdma::queue_ext::mode::memory_mapped;
            bool no_add_start_queue = true;

            /* Queue constructor called, but queue not added */
            qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg, no_add_start_queue);

            /* Force an Invalid Queue ID */
            auto forced_invalid_qid = 513; /* 0 to 511 are valid queue ids for any PF */

            auto ret = drv.stop_queue(tx.pf, forced_invalid_qid, dir, false);
            EXPECT_EQ(0, ret) << "Invalid qid stop test failed!\n";
        }
#endif
    }
}

TEST_P(qdma_neg_inv_qid_ops, q_remove) {
    const auto& tp = GetParam();
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
#ifdef _WIN32
        /* Opening a queue file with invalid qid */
        {
            qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
            const auto dir = qdma::queue_ext::direction::both;
            static const auto mode = qdma::queue_ext::mode::memory_mapped;
            bool no_add_start_queue = true;

            /* Queue constructor called, but queue not added */
            qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg, no_add_start_queue);

            /* Force an Invalid Queue ID */
            auto forced_invalid_qid = 513; /* 0 to 511 are valid queue ids for any PF */

            auto ret = drv.remove_queue(tx.pf, forced_invalid_qid, dir, false);
            EXPECT_EQ(0, ret) << "Invalid qid delete test failed!\n";
        }
#endif
    }
}


TEST_P(qdma_neg_mm_overflow_test, dma_h2c_c2h) {

	// test case constants
	const auto dir = qdma::queue_ext::direction::both;
	const auto& tp = GetParam();
	qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

	// pre-condition confirm test buffers are not equal
	ASSERT_NE(rd_buffer, wr_buffer);

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
	// execute code under test
	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));

		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}


		example_design_ctrl user_logic{ tx.qdev };
		// setup user logic
		if(tp.qcfg.desc_bypass)
			user_logic.set_bypass_mode(qdma::queue_ext::mode::memory_mapped, dir, DESC_BYPASS_MODE);
		// tp.qcfg.burst_size = 512;
		// tp.qcfg.idx_bufsz = 1024;
		qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg);

		for (unsigned i = 0; i < tx.it; i++) {
			SCOPED_TRACE("iteration=" + std::to_string(i));

			ASSERT_NO_THROW(q.write(wr_buffer.data(), tx.size, tx.offset))
			<< "h2c transfer returned with an error!";
			ASSERT_NO_THROW(q.read(rd_buffer.data(), tx.size, tx.offset))
			<< "c2h transfer returned with an error!";
#ifdef LINUX
			char *cmd = new char[500];
			snprintf(cmd, 500, "echo **********H2C INFO************; "
						"cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/queues/%d/h2c/cntxt;"
						"cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/qdma_regs;"
						"echo ***********C2H INFO*************; "
						"cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/queues/%d/c2h/cntxt;"
						"cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/qdma_regs;",
						(tp.devtype == qdma::instance_ext::type::vf) ? "vf" : "pf",
						(tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7), tx.q,
						(tp.devtype == qdma::instance_ext::type::vf) ? "vf" : "pf",
						(tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7),
						(tp.devtype == qdma::instance_ext::type::vf) ? "vf" : "pf",
						(tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7), tx.q,
						(tp.devtype == qdma::instance_ext::type::vf) ? "vf" : "pf",
						(tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7));

			// Compare read data with expected
			auto cmp_result = std::memcmp(wr_buffer.data(), rd_buffer.data(), tx.size);
			EXPECT_EQ(cmp_result, 0) << "data returned from c2h tx does not match h2c data!\n"
					<< print_diffs(wr_buffer.cbegin(), wr_buffer.cend(), rd_buffer.cbegin())
					<< system(cmd);
			delete[] cmd;
#elif _WIN32
			auto cmp_result = std::memcmp(wr_buffer.data(), rd_buffer.data(), tx.size);
			EXPECT_EQ(cmp_result, 0) << "data returned from c2h tx does not match h2c data!\n"
					<< print_diffs(wr_buffer.cbegin(), wr_buffer.cend(), rd_buffer.cbegin());
#else
			// Compare read data with expected
			auto cmp_result = std::memcmp(wr_buffer.data(), rd_buffer.data(), tx.size);
			EXPECT_EQ(cmp_result, 0) << "data returned from c2h tx does not match h2c data!\n"
					<< print_diffs(wr_buffer.cbegin(), wr_buffer.cend(), rd_buffer.cbegin())
					<<  rte_pmd_qdma_dbg_qinfo(tx.pf, tx.q);
#endif
			// reset read buffer
			std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
		}
	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax)
			rte_pmd_qdma_dev_close(pf.dev_id);
	}
#endif
}

TEST_P(qdma_mm_test, dma_h2c_only) {

	const auto& tp = GetParam();
	const auto dir = qdma::queue_ext::direction::host_to_card;
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

	// execute code under test
	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));

		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}

		example_design_ctrl user_logic{ tx.qdev };
		// setup user logic
		if(tp.qcfg.desc_bypass)
			user_logic.set_bypass_mode(qdma::queue_ext::mode::memory_mapped, dir, DESC_BYPASS_MODE);
		qdma::queue_ext h2c_q(drv, tx.pf, tx.q, mode, dir, tp.qcfg);

		for (unsigned i = 0; i < tx.it; i++) {
			SCOPED_TRACE("iteration=" + std::to_string(i));
#ifdef LINUX
			char *cmd = new char[200];
			char *regcmd = new char[200];

			snprintf(cmd, 200, "cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/queues/%d/h2c/cntxt",
					(tp.devtype == qdma::instance::type::pf) ? "pf" : "vf",
							(tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7), tx.q);
			snprintf(regcmd, 200, "cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/qdma_regs",
					(tp.devtype == qdma::instance::type::pf) ? "pf" : "vf",
							(tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7));

			try {
				h2c_q.write(wr_buffer.data(), tx.size, tx.offset);
			} catch (const std::exception& e) {
				FAIL() << "h2c transfer returned with an error! " << e.what() << system(cmd) << system(regcmd);
			}
			delete[] cmd;
			delete[] regcmd;
#elif _WIN32
			try {
				h2c_q.write(wr_buffer.data(), tx.size, tx.offset);
			}
			catch (const std::exception& e) {
				FAIL() << "h2c transfer returned with an error! " << e.what();
			}
#else
			try {
				h2c_q.write(wr_buffer.data(), tx.size, tx.offset);
			} catch (const std::exception& e) {
				FAIL() << "h2c transfer returned with an error! " << e.what() <<  rte_pmd_qdma_dbg_qinfo(tx.pf, tx.q);
			}
#endif
			// Check data was correctly written to BRAM
			// TODO Needs bypass bar to confirm
		}
	}

#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax)
			rte_pmd_qdma_dev_close(pf.dev_id);
	}
#endif
}

TEST_P(qdma_mm_test, dma_c2h_only) {

	const auto& tp = GetParam();
	const auto dir = qdma::queue_ext::direction::card_to_host;
	qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

	// Write test pattern to BRAM
	// TODO Needs bypass bar
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

	// execute code under test
	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));

		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}
		example_design_ctrl user_logic{ tx.qdev };
		// setup user logic
		if(tp.qcfg.desc_bypass)
			user_logic.set_bypass_mode(qdma::queue_ext::mode::memory_mapped, dir, DESC_BYPASS_MODE);

		qdma::queue_ext c2h_q(drv, tx.pf, tx.q, mode, dir, tp.qcfg);

		for (unsigned i = 0; i < tx.it; i++) {
			SCOPED_TRACE("iteration=" + std::to_string(i));
#ifdef LINUX
			char *cmd = new char[200];
			char *regcmd = new char[200];

			snprintf(cmd, 200, "cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/queues/%d/c2h/cntxt",
						(tp.devtype == qdma::instance_ext::type::vf) ? "vf" : "pf",
						(tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7), tx.q);
			snprintf(regcmd, 200, "cat /sys/kernel/debug/qdma-%s/%02x:%02x:%01x/qdma_regs",
					(tp.devtype == qdma::instance::type::pf) ? "pf" : "vf",
							(tx.pf >> 8) >> 4, ((tx.pf >> 3) & 0x1F), (tx.pf & 0x7));

			try {
				c2h_q.read(rd_buffer.data(), tx.size, tx.offset);
			} catch (const std::exception& e) {
				FAIL() << "c2h transfer returned with an error!" << system(cmd) << system(regcmd);
			}
			delete[] cmd;
			delete[] regcmd;
#elif _WIN32
			try {
				c2h_q.read(rd_buffer.data(), tx.size, tx.offset);
			}
			catch (const std::exception& e) {
				FAIL() << "c2h transfer returned with an error!" << e.what();
			}
#else
			try {
				c2h_q.read(rd_buffer.data(), tx.size, tx.offset);
			} catch (const std::exception& e) {
				rte_pmd_qdma_dbg_qinfo(tx.pf, tx.q);
				FAIL() << "c2h transfer returned with an error!";
			}
#endif
			// Compare read data with expected
			// TODO Needs bypass bar to confirm
		}
	}

#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax)
			rte_pmd_qdma_dev_close(pf.dev_id);
	}
#endif
}

TEST_P(qdma_mm_test, dma_h2c_c2h) {

	// test case constants
	const auto dir = qdma::queue_ext::direction::both;
	const auto& tp = GetParam();
	qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

	// pre-condition confirm test buffers are not equal
	ASSERT_NE(rd_buffer, wr_buffer);

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
	// execute code under test
	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));

		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}


		example_design_ctrl user_logic{ tx.qdev };
		// setup user logic
		if(tp.qcfg.desc_bypass)
			user_logic.set_bypass_mode(qdma::queue_ext::mode::memory_mapped, dir, DESC_BYPASS_MODE);

		qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg);

		for (unsigned i = 0; i < tx.it; i++) {
			SCOPED_TRACE("iteration=" + std::to_string(i));

			ASSERT_NO_THROW(q.write(wr_buffer.data(), tx.size, tx.offset))
			<< "h2c transfer returned with an error!";
			ASSERT_NO_THROW(q.read(rd_buffer.data(), tx.size, tx.offset))
			<< "c2h transfer returned with an error!";
#ifdef LINUX
			char *cmd = new char[500];
			snprintf(cmd, 500, "echo **********H2C INFO************; "
						"cat /sys/kernel/debug/qdma-%s/0000\\:%02x\\:%02x\\:%01x/queues/%d/h2c/cntxt;"
						"cat /sys/kernel/debug/qdma-%s/0000\\:%02x\\:%02x\\:%01x/qdma_regs;"
						"echo ***********C2H INFO*************; "
						"cat /sys/kernel/debug/qdma-%s/0000\\:%02x\\:%02x\\:%01x/queues/%d/c2h/cntxt;"
						"cat /sys/kernel/debug/qdma-%s/0000\\:%02x\\:%02x\\:%01x/qdma_regs;",
						(tp.devtype == qdma::instance_ext::type::vf) ? "vf" : "pf",
						(tx.pf >> 12), ((tx.pf >> 4) & 0xFF), (tx.pf & 0xF), tx.q,
						(tp.devtype == qdma::instance_ext::type::vf) ? "vf" : "pf",
						(tx.pf >> 12), ((tx.pf >> 4) & 0xFF), (tx.pf & 0xF),
						(tp.devtype == qdma::instance_ext::type::vf) ? "vf" : "pf",
						(tx.pf >> 12), ((tx.pf >> 4) & 0xFF), (tx.pf & 0xF), tx.q,
						(tp.devtype == qdma::instance_ext::type::vf) ? "vf" : "pf",
						(tx.pf >> 12), ((tx.pf >> 4) & 0xFF), (tx.pf & 0xF));
			
			// Compare read data with expected
			auto cmp_result = std::memcmp(wr_buffer.data(), rd_buffer.data(), tx.size);
			EXPECT_EQ(cmp_result, 0) << "data returned from c2h tx does not match h2c data!\n"
					<< print_diffs(wr_buffer.cbegin(), wr_buffer.cend(), rd_buffer.cbegin())
					<< system(cmd);
			delete[] cmd;
#elif _WIN32
			auto cmp_result = std::memcmp(wr_buffer.data(), rd_buffer.data(), tx.size);
			EXPECT_EQ(cmp_result, 0) << "data returned from c2h tx does not match h2c data!\n"
					<< print_diffs(wr_buffer.cbegin(), wr_buffer.cend(), rd_buffer.cbegin());
#else
			// Compare read data with expected
			auto cmp_result = std::memcmp(wr_buffer.data(), rd_buffer.data(), tx.size);
			EXPECT_EQ(cmp_result, 0) << "data returned from c2h tx does not match h2c data!\n"
					<< print_diffs(wr_buffer.cbegin(), wr_buffer.cend(), rd_buffer.cbegin())
					<<  rte_pmd_qdma_dbg_qinfo(tx.pf, tx.q);
#endif
			// reset read buffer
			std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
		}
	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax)
			rte_pmd_qdma_dev_close(pf.dev_id);
	}
#endif
}

TEST_P(qdma_mm_temp_test, dma_h2c_c2h) {

	const auto& tp = GetParam();
	qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

	static const auto mode = qdma::queue_ext::mode::memory_mapped;
	// test case constants
	const auto dir = qdma::queue_ext::direction::both;

	// pre-condition confirm test buffers are not equal
	ASSERT_NE(rd_buffer, wr_buffer);

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
	// execute code under test
	queues.reserve(tp.transfers.size());

	for(const auto& tx : tp.transfers) {
		if(validate_test_case(devlist, tx.pf, tp.qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}

		queues.emplace_back(drv, tx.pf, tx.q, mode, dir, tp.qcfg);
	}

	struct find_id{
		uint32_t pf;
		uint32_t q;
		find_id(uint32_t pf, uint32_t q): pf(pf),q(q) { }
		bool operator()(test_params::transfer const& m) const {
			return (m.pf == pf) && (m.q == q);
		}
	};

	for(auto& q : queues){
		auto tx = std::find_if (tp.transfers.begin(), tp.transfers.end()-1, find_id(q.m_dev_id, q.m_qid));

		example_design_ctrl user_logic{ tx->qdev };
		user_logic.set_queue(0xffff);
		user_logic.reset_pkt_ctrl();
		// setup user logic
		if(tp.qcfg.desc_bypass)
			user_logic.set_bypass_mode(qdma::queue_ext::mode::memory_mapped, dir, DESC_BYPASS_MODE);
		else
			user_logic.set_bypass_mode(qdma::queue_ext::mode::memory_mapped, dir, NO_BYPASS_MODE);

		SCOPED_TRACE("pf=" + int_to_hex(tx->pf));
		SCOPED_TRACE("queue=" + std::to_string(tx->q));
		for (unsigned i = 0; i < tx->it; i++) {
			SCOPED_TRACE("iteration=" + std::to_string(i));

			ASSERT_NO_THROW(q.write(wr_buffer.data(), tx->size, tx->offset))
			<< "h2c transfer returned with an error!";
			ASSERT_NO_THROW(q.read(rd_buffer.data(), tx->size, tx->offset))
			<< "c2h transfer returned with an error!";

			// Compare read data with expected
			auto cmp_result = std::memcmp(wr_buffer.data(), rd_buffer.data(), tx->size);
			EXPECT_EQ(cmp_result, 0) << "data returned from c2h tx does not match h2c data!\n"
					<< print_diffs(wr_buffer.cbegin(), wr_buffer.cend(), rd_buffer.cbegin());

			// reset read buffer
			std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
		}
	}
	queues.erase(queues.begin(), queues.end());
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax)
			rte_pmd_qdma_dev_close(pf.dev_id);
	}
#endif
}

//Perform queue operations ( open and close) on all the functions
//for all the queues
TEST_F(qdma_mm_test, MM001_queues_open_close) {

	const auto dir = qdma::queue_ext::direction::both;
	qdma::queue_ext::config qcfg;
	qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf;

	qdma::instance_ext &drv = env.get_drv_instance(dev_type);
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for (uint32_t func = 0; func < devlist.size(); func++) {
		auto& qdev = devlist[func];
		if (!devlist[func].max_num_queues)
			continue;
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
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
TEST_F(qdma_mm_test, VF_MM001_queues_open_close) {

	const auto dir = qdma::queue_ext::direction::both;
	qdma::queue_ext::config qcfg;
	qdma::instance_ext::type dev_type = qdma::instance_ext::type::vf;
	qdma::instance_ext &drv = env.get_drv_instance(dev_type);
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for (uint32_t func = 0; func < devlist.size(); func++) {
		auto& qdev = devlist[func];
		if (!devlist[func].max_num_queues)
			continue;
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
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

TEST_F(qdma_mm_test, DISABLED_NT017_queue_open_internal_mode) {
	const auto dir = qdma::queue_ext::direction::both;
	qdma::queue_ext::config qcfg;
	qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf;

	qdma::instance_ext& drv = env.get_drv_instance(dev_type);
	std::vector<qdma::device>& devlist = env.get_dev_list(dev_type);
	int test_status = 0;

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for (uint32_t func = 0; func < devlist.size(); func++) {
		auto& qdev = devlist[func];
		if (!devlist[func].max_num_queues)
			continue;
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try {
			rte_eth_dev_configure(devlist[func].dev_id, qdev.max_num_queues, qdev.max_num_queues, &port_conf);
		}
		catch (const std::exception& e) {
			FAIL() << "Cannot configure port %d" << devlist[func].dev_id << e.what();
		}
	}
#endif

	/** QDMA Internal mode */
	qcfg.desc_bypass = false;
	qcfg.pfetch_bypass = false;
	for (uint32_t func = 0; func < devlist.size(); func++) {
		if (!devlist[func].max_num_queues) {
			continue;
		}

		for (uint32_t i = 0; i < devlist[func].max_num_queues; i++) {
#ifdef _WIN32
			/* Queue constructor called, but queue not added */
			qdma::queue_ext q(drv, devlist[func].dev_id, i, mode, dir, qcfg, true /* no add start q */);

			auto res = drv.add_queue(devlist[func].dev_id, i, 1, mode, dir, qcfg);
			if (res != 0) {
				drv.remove_queue(devlist[func].dev_id, i, dir);
			}
			EXPECT_EQ(0, res) << "drv.add_queue success (which is not expected)!\n";
#else
			try {
				qdma::queue_ext q(drv, devlist[func].dev_id, i, mode, dir, qcfg);
			} catch (const std::exception& e){
				test_status = 1;
				std::cout << "Cannot open queue" << devlist[func].dev_id << "_q" << i << " " << e.what() << '\n';
			}
			EXPECT_EQ(1, test_status) << "Negative testing of bypass only mode failed!\n";
#endif
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

TEST_F(qdma_mm_test, DISABLED_NT018_queue_open_simple_bypass_mode) {
	const auto dir = qdma::queue_ext::direction::both;
	qdma::queue_ext::config qcfg;
	qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf;

	qdma::instance_ext& drv = env.get_drv_instance(dev_type);
	std::vector<qdma::device>& devlist = env.get_dev_list(dev_type);
	int test_status = 0;

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for (uint32_t func = 0; func < devlist.size(); func++) {
		auto& qdev = devlist[func];
		if (!devlist[func].max_num_queues)
			continue;
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		try {
			rte_eth_dev_configure(devlist[func].dev_id, qdev.max_num_queues, qdev.max_num_queues, &port_conf);
		}
		catch (const std::exception& e) {
			FAIL() << "Cannot configure port %d" << devlist[func].dev_id << e.what();
		}
	}
#endif

	/** QDMA Simple bypass mode */
	qcfg.desc_bypass = true;
	qcfg.pfetch_bypass = true;
	for (uint32_t func = 0; func < devlist.size(); func++) {
		if (!devlist[func].max_num_queues) {
			continue;
		}
		for (uint32_t i = 0; i < devlist[func].max_num_queues; i++) {
#ifdef _WIN32
			/* Queue constructor called, but queue not added */
			qdma::queue_ext q(drv, devlist[func].dev_id, i, mode, dir, qcfg, true /* no add start q */);

			auto res = drv.add_queue(devlist[func].dev_id, i, 1, mode, dir, qcfg);
			if (res != 0) {
				drv.remove_queue(devlist[func].dev_id, i, dir);
			}
			EXPECT_EQ(0, res) << "drv.add_queue success (which is not expected)!\n";
#else
			try {
				qdma::queue_ext q(drv, devlist[func].dev_id, i, mode, dir, qcfg);
			} catch (const std::exception& e){
				test_status = 1;
				std::cout << "Cannot open queue" << devlist[func].dev_id << "_q" << i << " " << e.what() << '\n';
			}
			EXPECT_EQ(1, test_status) << "Negative testing of internal only mode failed!\n";
#endif
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

TEST_P(qdma_mm_cmpt_test, DISABLED_mm_completion) {
#ifdef _WIN32
	const auto mode = qdma::queue_ext::mode::memory_mapped;
	qdma::queue_ext::config qcfg;
	int cmptsz_map[] = {8, 16, 32, 64};
	uint32_t imm_data;
	int k = 0;
	unsigned char *bytes;
	const auto& tp = GetParam();
	int consume_cnt;


	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

	std::default_random_engine rne((unsigned int)time(0));
	std::uniform_int_distribution<uint32_t> rng_data(0, 0xFFFFFFFF);
	std::uniform_int_distribution<uint32_t> rng_wbsz(0, 3);    // write back entry size
	std::uniform_int_distribution<uint32_t> rng_nb_entries(1, 256);

	// setup buffers - using BRAM size as max transfer length, even though they are unrelated
	aligned_vector<pattern_t> buffer(array_size);

    auto tmode = 0;
    for (tmode = 0; tmode < 4; tmode++) {
        switch (tmode) {
            case 0:
                qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::every;
                break;
            case 1:
                qcfg.idx_cntr = 0;
                qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::usr_cnt;
                break;
            case 2:
                qcfg.idx_tmr = 0;
                qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr;
                break;
            case 3:
                qcfg.idx_tmr = 0;
                qcfg.idx_cntr = 0;
                qcfg.trigmode = qdma::queue_ext::c2h_wrb_intr_trigmode::cntr_tmr;
                break;
            default:
                break;
        }
	    for (const auto& xfer : tp.transfers) {
            auto nb_entries = rng_nb_entries(rne);
            const auto cmptsz = rng_wbsz(rne);
            auto usr_imm_data_regs = cmptsz_map[cmptsz] / 4;
            uint64_t buf_sz = cmptsz_map[cmptsz];
            int device_type = get_device_type(xfer.pf, devlist);
            int ip_type = get_ip_type(xfer.pf, devlist);

            if (cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B)
                usr_imm_data_regs = 8;

            SCOPED_TRACE("pf=" + int_to_hex(xfer.pf));
            SCOPED_TRACE("queue=" + std::to_string(xfer.q));
            SCOPED_TRACE("rng_wbsz=" + std::to_string(cmptsz));

			qcfg.c2h_udd_en = 1;
			qcfg.cmptsz = static_cast<xnl_st_c2h_cmpt_desc_size>(cmptsz);
			if(validate_test_case(devlist, xfer.pf, qcfg) < 0) {
				//GTEST_SKIP();
				std::cout << "Invalid Test Case" << std::endl;
				continue;
			}
			example_design_ctrl user_logic{ xfer.qdev };
			user_logic.reset_pkt_ctrl();
			user_logic.set_st_loopback(false);

            qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
            const auto dir = qdma::queue_ext::direction::card_to_host;
            const auto hw_qid = get_hw_qid(xfer.pf, xfer.q, devlist);
            qcfg.en_mm_cmpt = 1;
            /** Queue started with cmptsz and c2h_udd_en */
            qdma::queue_ext h2c_q(drv, xfer.pf, xfer.q, mode, dir, qcfg);

            /** setting the cmpt size and HW QID */
            user_logic.set_wrb_desc_size(qcfg.cmptsz);
            uint64_t entry;
            for (entry = 0; entry < nb_entries; entry++) {
                /* Setting UDD in userbar registers */
                char buf[1000];
                char buf_64b[1000];
                char cmpt_buff[2000];
                char newArray[2000];
                uint64_t buff_ptr = 0;
                uint64_t buff_64b_ptr = 0;
                memset(buf, 0, buf_sz);
                memset(buf_64b, 0, buf_sz);
                memset(cmpt_buff, 0, buf_sz);

                for (auto j = 0; j < usr_imm_data_regs; j++) {
                    imm_data = rng_data(rne);
                    user_logic.set_imm_data(j, imm_data);
                    bytes = reinterpret_cast<unsigned char*>(&imm_data);

                    for (k = 0; k < 4; k++) {
                        /* Creating a buffer to store the higher 32bytes of data */
                        if (cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B) {
                            buff_64b_ptr += sprintf(buf_64b + buff_64b_ptr, "%02x", bytes[3 - k]);
                        }
                        /* Ignoring the first 4 bits while creating a buffer for the lower 32 bytes */
                        if ((j == 0) && (k == 3)) {
                            buff_ptr += sprintf(buf + buff_ptr, "%02x", (bytes[3 - k] & CMPT_DESC_ENTRY_MASK));
                        } else {
                            buff_ptr += sprintf(buf + buff_ptr, "%02x", bytes[3 - k]);
                        }
                    }
                }
                user_logic.set_queue(hw_qid);
                /* Generate two packets for usr_cnt mode as it is configured with 2.
                   Generate two more packets as HW is generating interrupt for every (usr_cnt + 2) packets */
                user_logic.set_imm_data_en(qcfg.c2h_udd_en, device_type, ip_type);
                if (qcfg.trigmode == qdma::queue_ext::c2h_wrb_intr_trigmode::usr_cnt) {
                    user_logic.set_imm_data_en(qcfg.c2h_udd_en, device_type, ip_type);
                    user_logic.set_imm_data_en(qcfg.c2h_udd_en, device_type, ip_type);
                    user_logic.set_imm_data_en(qcfg.c2h_udd_en, device_type, ip_type);
                }

                /* adding delay to make sure HW has generated the writeback entry */
                for (int delay = 0; delay < (200 * 1024); delay++);

                consume_cnt = drv.read_cmpt_data(xfer.pf, xfer.q, dir, cmpt_buff);
                if (consume_cnt != 0) {
                    if (cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B) {
                        memcpy(newArray, buf, usr_imm_data_regs * 4);
                        memcpy(newArray + (usr_imm_data_regs * 4 * 1), buf_64b, usr_imm_data_regs * 4);
                        if (qcfg.trigmode == qdma::queue_ext::c2h_wrb_intr_trigmode::usr_cnt) {
                            memcpy(newArray + (usr_imm_data_regs * 4 * 2), buf, usr_imm_data_regs * 4);
                            memcpy(newArray + (usr_imm_data_regs * 4 * 3), buf_64b, usr_imm_data_regs * 4);
                            memcpy(newArray + (usr_imm_data_regs * 4 * 4), buf, usr_imm_data_regs * 4);
                            memcpy(newArray + (usr_imm_data_regs * 4 * 5), buf_64b, usr_imm_data_regs * 4);
                            memcpy(newArray + (usr_imm_data_regs * 4 * 6), buf, usr_imm_data_regs * 4);
                            memcpy(newArray + (usr_imm_data_regs * 4 * 7), buf_64b, usr_imm_data_regs * 4);

                        }
                        auto cmp_res = memcmp(newArray, cmpt_buff, cmptsz);
                        EXPECT_EQ(0, cmp_res) << "cmpt_buff : packet data does not match expected pattern!\n" << cmptsz;

                    } else {
                        memcpy(newArray, buf, usr_imm_data_regs * 4);
                        if (qcfg.trigmode == qdma::queue_ext::c2h_wrb_intr_trigmode::usr_cnt) {
                            memcpy(newArray + (usr_imm_data_regs * 4 * 1), buf, usr_imm_data_regs * 4);
                            memcpy(newArray + (usr_imm_data_regs * 4 * 2), buf, usr_imm_data_regs * 4);
                            memcpy(newArray + (usr_imm_data_regs * 4 * 3), buf, usr_imm_data_regs * 4);

                        }
                        auto cmp_res = memcmp(buf, cmpt_buff, cmptsz_map[cmptsz]);
                        ASSERT_EQ(0, cmp_res) << "cmpt_buff : packet data does not match expected pattern!" << cmptsz << std::endl;
                    }
                } else {
                    int cmp_res = 1;
                    EXPECT_EQ(0, cmp_res) << "cmpt_buff : Hardware failed to process entry :" << entry << "with cmpt size :\n" << cmptsz;
                }
            }
        }
	}

#else
	const auto mode = qdma::queue_ext::mode::memory_mapped;
	qdma::queue_ext::config qcfg;
	int cmptsz_map[] = {8, 16, 32, 64};
	uint32_t imm_data;
	int k = 0;
	unsigned char *bytes;
	const auto& tp = GetParam();
	int consume_cnt;

	qcfg = tp.qcfg;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

	std::default_random_engine rne(time(0));
	std::uniform_int_distribution<uint32_t> rng_data(0, 0xFFFFFFFF);
	std::uniform_int_distribution<uint32_t> rng_wbsz(0, 3);    // write back entry size
#ifdef DPDK
	std::uniform_int_distribution<uint32_t> rng_nb_entries(1, 2048);
#else
	std::uniform_int_distribution<uint32_t> rng_nb_entries(1, 32);
#endif

	// setup buffers - using BRAM size as max transfer length, even though they are unrelated
	aligned_vector<pattern_t> buffer(array_size);

#ifdef DPDK
	int ret = 0;
	struct rte_eth_conf    port_conf;
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
		auto nb_entries = rng_nb_entries(rne);
#ifdef DPDK
		const auto cmptsz = cmptsz_map[rng_wbsz(rne)];
		auto usr_imm_data_regs = cmptsz/4;
		uint64_t buf_sz = cmptsz;
#else
		const auto cmptsz = rng_wbsz(rne);
		auto usr_imm_data_regs = cmptsz_map[cmptsz]/4;
		uint64_t buf_sz = cmptsz_map[cmptsz];
#endif
		int device_type = get_device_type(xfer.pf, devlist);
		int ip_type = get_ip_type(xfer.pf, devlist);

		if (cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B)
			usr_imm_data_regs = 8;

		SCOPED_TRACE("pf=" + int_to_hex(xfer.pf));
		SCOPED_TRACE("queue=" + std::to_string(xfer.q));
		SCOPED_TRACE("rng_wbsz=" + std::to_string(cmptsz));

		qcfg.c2h_udd_en = 1;
		qcfg.cmptsz = static_cast<xnl_st_c2h_cmpt_desc_size>(cmptsz);
		if(validate_test_case(devlist, xfer.pf, qcfg) < 0) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}
		example_design_ctrl user_logic{ xfer.qdev };
		user_logic.reset_pkt_ctrl();
		user_logic.set_st_loopback(false);

#ifdef DPDK
		const auto hw_qid = get_hw_qid(xfer.pf, xfer.q);
		ret = rte_pmd_qdma_set_queue_mode(xfer.pf, xfer.q, (rte_pmd_qdma_queue_mode_t)mode);
		if(ret < 0)
			throw std::runtime_error("rte_pmd_qdma_set_queue_mode  failed");
		ret = rte_pmd_qdma_set_cmpt_descriptor_size(xfer.pf, xfer.q, (rte_pmd_qdma_cmpt_desc_len)qcfg.cmptsz);
		 if(ret < 0)
			 throw std::runtime_error("rte_pmd_qdma_set_cmpt_descriptor_size failed");
		ret = rte_pmd_qdma_dev_cmptq_setup(xfer.pf, xfer.q, tp.qcfg.idx_rngsz, 0);
		if(ret < 0)
			throw std::runtime_error("rte_pmd_qdma_dev_cmptq_setup failed");
		ret = rte_pmd_qdma_set_cmpt_overflow_check(xfer.pf, xfer.q, tp.qcfg.c2h_ovf_chk_dis);
		if(ret < 0)
			throw std::runtime_error("rte_pmd_qdma_set_cmpt_overflow_check failed");
		ret = rte_pmd_qdma_set_cmpt_trigger_mode(xfer.pf, xfer.q, (rte_pmd_qdma_tigger_mode_t)tp.qcfg.trigmode);
		if(ret < 0)
			throw std::runtime_error("rte_pmd_qdma_set_cmpt_trigger_mode failed");
		ret = rte_pmd_qdma_set_cmpt_timer(xfer.pf, xfer.q, tp.qcfg.idx_tmr);
		if(ret < 0)
			throw std::runtime_error("rte_pmd_qdma_set_cmpt_timer failed");
		ret = rte_pmd_qdma_dev_cmptq_start(xfer.pf, xfer.q);
		if(ret < 0)
			throw std::runtime_error("rte_pmd_qdma_dev_cmptq_start failed");

#else
		qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
		const auto dir = qdma::queue_ext::direction::cmpt;
		const auto hw_qid = get_hw_qid(xfer.pf, xfer.q, devlist);
		/** Queue started with cmptsz and c2h_udd_en */
		qdma::queue_ext q(drv, xfer.pf, xfer.q, mode, dir, qcfg);
#endif

		/** setting the cmpt size and HW QID */
		user_logic.set_wrb_desc_size(qcfg.cmptsz);
		uint64_t entry;
		for (entry =0; entry < nb_entries; entry++) {
			/* Setting UDD in userbar registers */
#ifdef DPDK
			char * buf = new char[buf_sz];
			char * buf_64b = new char[buf_sz];
			char * cmpt_buff = new char[buf_sz];
			char * newArray = new char[buf_sz];
#else
			char buf[1000];
			char buf_64b[1000];
			char cmpt_buff[1000];
			char newArray[1000];
#endif
			uint64_t buff_ptr = 0;
			uint64_t buff_64b_ptr = 0;
			memset(buf, 0, buf_sz);
			memset(buf_64b, 0, buf_sz);
			memset(cmpt_buff, 0, buf_sz);

			for(auto j = 0; j < usr_imm_data_regs; j++) {
				imm_data = rng_data(rne);
				user_logic.set_imm_data(j , imm_data);
				bytes = reinterpret_cast<unsigned char*>(&imm_data);
#ifdef DPDK
				for(k = 0 ; k < 4 ; k++) {
					/* Creating a buffer to store the higher 32bytes of data */
					if(cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B) {
						*(buf_64b + buff_64b_ptr) = bytes[k];
						buff_64b_ptr++;
					}
					/* Ignoring the first 4 bits while creating a buffer for the lower 32 bytes */
					if ((j == 0) && (k == 0)) {
						*(buf + buff_ptr) = (bytes[k] & CMPT_DESC_ENTRY_MASK);
						buff_ptr++;
					} else {
						*(buf + buff_ptr) = (bytes[k]);
						buff_ptr++;
					}
				}
#else
				for(k = 0 ; k < 4 ; k++) {
					/* Creating a buffer to store the higher 32bytes of data */
					if(cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B) {
						buff_64b_ptr += sprintf(buf_64b + buff_64b_ptr, "%02x", bytes[3 - k]);
					}
					/* Ignoring the first 4 bits while creating a buffer for the lower 32 bytes */
					if ((j == 0) && (k == 3)) {
						buff_ptr += sprintf(buf + buff_ptr, "%02x", (bytes[3 - k] & CMPT_DESC_ENTRY_MASK));
					} else {
						buff_ptr += sprintf(buf + buff_ptr, "%02x", bytes[3 -k]);
					}
				}
#endif
			}
			user_logic.set_queue(hw_qid);
			user_logic.set_imm_data_en(qcfg.c2h_udd_en, device_type, ip_type);

            /* adding delay to make sure HW has generated the writeback entry */
            usleep(200);

#ifdef DPDK
			/* adding delay to make sure HW has generated the writeback entry */
			int sleep_cnt;

			usleep(200);
			consume_cnt = rte_pmd_qdma_mm_cmpt_process(xfer.pf, xfer.q, cmpt_buff, 1);
			for (sleep_cnt = 1; sleep_cnt <= 10; sleep_cnt++) {
				if (consume_cnt == 1 )
					break;
				else	{
					usleep(200);
					consume_cnt = rte_pmd_qdma_mm_cmpt_process(xfer.pf, xfer.q, cmpt_buff, 1);
				}
			}

			if (consume_cnt == 1 ) {
				if(cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B) {
					memcpy(newArray, buf, usr_imm_data_regs * 4);
					memcpy(newArray + (usr_imm_data_regs * 4) , buf_64b, usr_imm_data_regs * 4);
				}

				if (cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B) {
					auto cmp_res = memcmp(newArray, cmpt_buff, cmptsz);
					EXPECT_EQ(0, cmp_res) << "udd : packet data does not match expected pattern!\n" << cmptsz;
				}else {
					auto cmp_res = memcmp(buf, cmpt_buff , cmptsz);
					EXPECT_EQ(0, cmp_res) << "udd : packet data does not match expected pattern!\n" << cmptsz;
				}
			} else {
				int cmp_res = 1;
				EXPECT_EQ(0, cmp_res) << "udd : Hardware failed to process entry :" <<entry <<"with cmpt size :\n" << cmptsz;
			}

			delete[] newArray;
			delete[] buf;
			delete[] buf_64b;
			delete[] cmpt_buff;
#else
			consume_cnt = drv.read_cmpt_data(xfer.pf, xfer.q, dir, cmpt_buff);
			if (consume_cnt == 1 ) {
				if(cmptsz == XNL_ST_C2H_CMPT_DESC_SIZE_64B) {
					memcpy(newArray, buf, usr_imm_data_regs * 4);
					memcpy(newArray + (usr_imm_data_regs * 4) , buf_64b, usr_imm_data_regs * 4);
					auto cmp_res = memcmp(newArray, cmpt_buff, cmptsz);
					EXPECT_EQ(0, cmp_res) << "cmpt_buff : packet data does not match expected pattern!\n" << cmptsz;

				} else {
					auto cmp_res = memcmp(buf, cmpt_buff, cmptsz_map[cmptsz]);
					ASSERT_EQ(0, cmp_res) << "cmpt_buff : packet data does not match expected pattern!" << cmptsz << std::endl;				}
			} else {
				int cmp_res = 1;
				EXPECT_EQ(0, cmp_res) << "cmpt_buff : Hardware failed to process entry :" <<entry <<"with cmpt size :\n" << cmptsz;
			}
#endif
		}
#ifdef DPDK
		ret = rte_pmd_qdma_dev_cmptq_stop(xfer.pf, xfer.q);
		if(ret < 0)
			throw std::runtime_error("rte_pmd_qdma_dev_cmptq_stop failed");
#endif
	}
#ifdef DPDK
	for(const auto& pf : tp.pfs){
		if (pf.qmax){
			rte_pmd_qdma_dev_close(pf.dev_id);
		}
	}
#endif
#endif
}
//open a queue , perform a transfer and close the queue. Do this for all the queues assigned to the PF
INSTANTIATE_TEST_CASE_P(MM002A_basic_dma_test, qdma_mm_test, ::testing::Values(
		basic_dma_test(get_num_qs_per_pf(env.pfs))                    // all PF   all Q,
));

//open all the queues at once and perform a transfer
#ifdef DPDK
INSTANTIATE_TEST_CASE_P(MM002B_basic_dma_test, qdma_mm_temp_test, ::testing::Values(
		basic_dma_test(get_num_qs_per_pf(env.pfs))                    // all PF   all Q,
));
INSTANTIATE_TEST_CASE_P(VF_MM002B_basic_dma_test, qdma_mm_temp_test, ::testing::Values(
		basic_dma_test(get_num_qs_per_pf(env.vfs),qdma::instance_ext::type::vf)                    // all PF   all Q,
));
INSTANTIATE_TEST_CASE_P(MM010_basic_cmpt_test, qdma_mm_cmpt_test, ::testing::Values(
		basic_dma_test(get_num_qs_per_pf(env.pfs))                    // all PF   all Q,
));
INSTANTIATE_TEST_CASE_P(VF_MM010_basic_cmpt_test, qdma_mm_cmpt_test, ::testing::Values(
		basic_dma_test(get_num_qs_per_pf(env.vfs),qdma::instance_ext::type::vf)                    // all PF   all Q,
));
INSTANTIATE_TEST_CASE_P(MM011_cmpt_ringsz_test, qdma_mm_cmpt_test, ::testing::Values(
		ring_size_test(256, 4_kB ,1000),
		ring_size_test(512, 8_kB, 1000),
		ring_size_test(1024, 10_kB, 1000)
));
INSTANTIATE_TEST_CASE_P(VF_MM011_cmpt_ringsz_test, qdma_mm_cmpt_test, ::testing::Values(
		ring_size_test(256, 4_kB ,1000, qdma::instance_ext::type::vf),
		ring_size_test(512, 8_kB, 1000, qdma::instance_ext::type::vf),
		ring_size_test(1024, 10_kB, 1000, qdma::instance_ext::type::vf)
));
INSTANTIATE_TEST_CASE_P(MM012_cmpt_timer_test, qdma_mm_cmpt_test, ::testing::Values(
		timer_cnt_test(5, 4_kB ,1000),
		timer_cnt_test(10, 4_kB ,1000),
		timer_cnt_test(30, 4_kB ,1000),
		timer_cnt_test(125, 4_kB ,1000),
		timer_cnt_test(50, 4_kB ,1000),
		timer_cnt_test(4, 4_kB ,1000),
		timer_cnt_test(1, 4_kB ,1000),
		timer_cnt_test(20, 4_kB ,1000)
));
INSTANTIATE_TEST_CASE_P(VF_MM012_cmpt_timer_test, qdma_mm_cmpt_test, ::testing::Values(
		timer_cnt_test(5, 4_kB ,1000, qdma::instance_ext::type::vf),
		timer_cnt_test(10, 4_kB ,1000, qdma::instance_ext::type::vf),
		timer_cnt_test(30, 4_kB ,1000, qdma::instance_ext::type::vf),
		timer_cnt_test(125, 4_kB ,1000,qdma::instance_ext::type::vf),
		timer_cnt_test(50, 4_kB ,1000, qdma::instance_ext::type::vf),
		timer_cnt_test(4, 4_kB ,1000, qdma::instance_ext::type::vf),
		timer_cnt_test(1, 4_kB ,1000, qdma::instance_ext::type::vf),
		timer_cnt_test(20, 4_kB ,1000, qdma::instance_ext::type::vf)
));
INSTANTIATE_TEST_CASE_P(MM013_cmpt_ovf_chk_dis_test, qdma_mm_cmpt_test, ::testing::Values(
		mm_cmpt_ovf_chk_dis_test(256, 4_kB ,1000),
		mm_cmpt_ovf_chk_dis_test(512, 8_kB, 1000),
		mm_cmpt_ovf_chk_dis_test(1024, 10_kB, 1000)
));
INSTANTIATE_TEST_CASE_P(VF_MM013_cmpt_ovf_chk_dis_test, qdma_mm_cmpt_test, ::testing::Values(
		mm_cmpt_ovf_chk_dis_test(256, 4_kB ,1000, qdma::instance_ext::type::vf),
		mm_cmpt_ovf_chk_dis_test(512, 8_kB, 1000, qdma::instance_ext::type::vf),
		mm_cmpt_ovf_chk_dis_test(1024, 10_kB, 1000, qdma::instance_ext::type::vf)
));
#else
INSTANTIATE_TEST_CASE_P(MM002B_basic_dma_test, qdma_mm_temp_test, ::testing::Values(
		basic_dma_test(get_num_qs_per_pf(env.pfs))                    // all PF   all Q,
));

INSTANTIATE_TEST_CASE_P(VF_MM002B_basic_dma_test, qdma_mm_temp_test, ::testing::Values(
		basic_dma_test(get_num_qs_per_pf(env.vfs),qdma::instance_ext::type::vf)                    // all PF   all Q,
));

INSTANTIATE_TEST_CASE_P(MM010_basic_cmpt_test, qdma_mm_cmpt_test, ::testing::Values(
		basic_dma_test(get_num_qs_per_pf(env.pfs))                    // all PF   all Q,
));

INSTANTIATE_TEST_CASE_P(VF_MM010_basic_cmpt_test, qdma_mm_cmpt_test, ::testing::Values(
		basic_dma_test(get_num_qs_per_pf(env.vfs),qdma::instance_ext::type::vf)                    // all PF   all Q,
));

INSTANTIATE_TEST_CASE_P(MM011_cmpt_ringsz_test, qdma_mm_cmpt_test, ::testing::Values(
		ring_size_test(0, 4_kB ,1000),
		ring_size_test(1, 4_kB, 1000),
		ring_size_test(2, 8_kB, 1000)
));

INSTANTIATE_TEST_CASE_P(VF_MM011_cmpt_ringsz_test, qdma_mm_cmpt_test, ::testing::Values(
		ring_size_test(0, 4_kB ,1000, qdma::instance_ext::type::vf),
		ring_size_test(1, 4_kB, 1000, qdma::instance_ext::type::vf),
		ring_size_test(2, 8_kB, 1000, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(MM012_cmpt_timer_test, qdma_mm_cmpt_test, ::testing::Values(
		timer_cnt_test(0, 4_kB ,1000),
		timer_cnt_test(1, 4_kB ,1000),
		timer_cnt_test(2, 4_kB ,1000),
		timer_cnt_test(4, 4_kB ,1000),
		timer_cnt_test(5, 4_kB ,1000),
		timer_cnt_test(6, 4_kB ,1000),
		timer_cnt_test(8, 4_kB ,1000),
		timer_cnt_test(11, 4_kB ,1000)

));

INSTANTIATE_TEST_CASE_P(VF_MM012_cmpt_timer_test, qdma_mm_cmpt_test, ::testing::Values(
		timer_cnt_test(0, 4_kB ,1000, qdma::instance_ext::type::vf),
		timer_cnt_test(1, 4_kB ,1000, qdma::instance_ext::type::vf),
		timer_cnt_test(2, 4_kB ,1000, qdma::instance_ext::type::vf),
		timer_cnt_test(4, 4_kB ,1000,qdma::instance_ext::type::vf),
		timer_cnt_test(5, 4_kB ,1000, qdma::instance_ext::type::vf),
		timer_cnt_test(6, 4_kB ,1000, qdma::instance_ext::type::vf),
		timer_cnt_test(8, 4_kB ,1000, qdma::instance_ext::type::vf),
		timer_cnt_test(11, 4_kB ,1000, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(MM013_cmpt_ovf_chk_dis_test, qdma_mm_cmpt_test, ::testing::Values(
		mm_cmpt_ovf_chk_dis_test(0, 4_kB ,1000),
		mm_cmpt_ovf_chk_dis_test(1, 4_kB, 1000),
		mm_cmpt_ovf_chk_dis_test(2, 8_kB, 1000)
));

INSTANTIATE_TEST_CASE_P(VF_MM013_cmpt_ovf_chk_dis_test, qdma_mm_cmpt_test, ::testing::Values(
		mm_cmpt_ovf_chk_dis_test(0, 4_kB ,1000, qdma::instance_ext::type::vf),
		mm_cmpt_ovf_chk_dis_test(1, 4_kB, 1000, qdma::instance_ext::type::vf),
		mm_cmpt_ovf_chk_dis_test(2, 8_kB, 1000, qdma::instance_ext::type::vf)
));
#endif

//Test all the functions with a single queue( queue id 0) for the
//following tx sizes: 1 , 4K , 4K + 1, 4k-1, 8k , 16k , 32k, 64k , 128k , 256k , 512k
INSTANTIATE_TEST_CASE_P(MM003_tx_sizes, qdma_mm_test, ::testing::Values(
		// tx_offset, tx_size
		tx_param_test(0, 1),
		tx_param_test(0, 4_kB - 1),
		tx_param_test(0, 4_kB),
		tx_param_test(0, 4_kB + 1),
		tx_param_test(0, 8_kB ),
		tx_param_test(0, 16_kB ),
		tx_param_test(0, 32_kB ),
		tx_param_test(0, 64_kB ),
		tx_param_test(0, 128_kB ),
		tx_param_test(0, 256_kB),
		tx_param_test(0, 512_kB)
));

//Test all the functions with a single queue( queue id 0) for the
//following tx offsets: 1 , 4KB , 252KB, 256kB
INSTANTIATE_TEST_CASE_P(MM004_tx_offsets, qdma_mm_test, ::testing::Values(
		// tx_offset, tx_size
		tx_param_test(1, 1),
		tx_param_test(4_kB, 4_kB),
		tx_param_test(252_kB, 4_kB),
		tx_param_test(256_kB - 1, 1)
));



#ifdef DPDK
	INSTANTIATE_TEST_CASE_P(MM005_ring_sizes, qdma_mm_test, ::testing::Values(
			// ring_size, tx_size, num_tx
			ring_size_test(256, 4_kB ,1000),
			ring_size_test(512, 8_kB, 1000),
			ring_size_test(1024, 10_kB, 1000)
	));
#else
INSTANTIATE_TEST_CASE_P(MM005_ring_sizes, qdma_mm_test, ::testing::Values(
	// ring_size_idx, tx_size, num_tx
	ring_size_test(0, 4_kB ,1000),
	ring_size_test(1, 4_kB ,1000),
	ring_size_test(2, 8_kB ,1000)/*,
    ring_size_test(3, 4_kB ,1),
    ring_size_test(4, 4_kB ,1),
    ring_size_test(5, 4_kB ,1),
    ring_size_test(6, 4_kB ,1),
    ring_size_test(7, 4_kB ,1),
    ring_size_test(8, 4_kB ,1),
    ring_size_test(9, 4_kB ,1)*/
));
#endif


#ifdef DPDK
	INSTANTIATE_TEST_CASE_P(VF_MM005_ring_sizes, qdma_mm_test, ::testing::Values(
			// ring_size, tx_size, num_tx
			ring_size_test(256, 4_kB ,1000, qdma::instance_ext::type::vf),
			ring_size_test(512, 8_kB, 1000, qdma::instance_ext::type::vf),
			ring_size_test(1024, 10_kB, 1000, qdma::instance_ext::type::vf)
	));
#endif

#ifdef	LINUX
INSTANTIATE_TEST_CASE_P(VF_MM005_ring_sizes, qdma_mm_test, ::testing::Values(
	// ring_size_idx, tx_size, num_tx
	ring_size_test(0, 4_kB ,1000, qdma::instance_ext::type::vf),
	ring_size_test(1, 4_kB ,1000, qdma::instance_ext::type::vf),
	ring_size_test(2, 8_kB ,1000, qdma::instance_ext::type::vf)
));
#endif

INSTANTIATE_TEST_CASE_P(MM007_desc_bypass, qdma_mm_test, ::testing::Values(
	// qid, num_tx, tx_size
	desc_bypass_test(0, 10, 1),
	desc_bypass_test(0, 10, 4_kB),
	desc_bypass_test(0, 10, 256_kB),
	desc_bypass_test(0, 10, 8_kB)
));

//TODO: This test works with only  vu9p_g3x16_1525_c2h_simbyp_18.3_1030.bit. For other bitstream , it
//fails and becaus eof this , other tests also starts failing. So currently disabling it.
#ifdef _WIN32
INSTANTIATE_TEST_CASE_P(VF_MM007_desc_bypass, qdma_mm_test, ::testing::Values(
    // qid, num_tx, tx_size
    desc_bypass_test(0, 10, 1, qdma::instance_ext::type::vf),
    desc_bypass_test(0, 10, 4_kB, qdma::instance_ext::type::vf),
    desc_bypass_test(0, 10, 8_kB, qdma::instance_ext::type::vf),
    desc_bypass_test(0, 10, 256_kB, qdma::instance_ext::type::vf)
));
#else
INSTANTIATE_TEST_CASE_P(VF_MM007_desc_bypass, qdma_mm_test, ::testing::Values(
	// qid, num_tx, tx_size
	desc_bypass_test(0, 10, 1, qdma::instance_ext::type::vf),
	desc_bypass_test(0, 10, 4_kB, qdma::instance_ext::type::vf),
	desc_bypass_test(0, 10, 256_kB, qdma::instance_ext::type::vf),
	desc_bypass_test(0, 10, 8_kB, qdma::instance_ext::type::vf)
));
#endif

INSTANTIATE_TEST_CASE_P(MM006_randomized_transfers, qdma_mm_test, ::testing::ValuesIn(
	// seed for random engine, num_tests to generate
	randomized_tests(env.random_seed, 10)
));

INSTANTIATE_TEST_CASE_P(VF_MM006_randomized_transfers, qdma_mm_test, ::testing::ValuesIn(
	// seed for random engine, num_tests to generate
	randomized_tests(env.random_seed, 10, qdma::instance_ext::type::vf)
));

//VF Test case starts

//open a queue , perform a transfer and close the queue. Do this for all the queues assigned to the PF
INSTANTIATE_TEST_CASE_P(VF_MM002A_basic_dma_test, qdma_mm_test, ::testing::Values(
	basic_dma_test(get_num_qs_per_pf(env.vfs), qdma::instance_ext::type::vf)                    // all PF   all Q,
));

INSTANTIATE_TEST_CASE_P(VF_MM003_tx_sizes, qdma_mm_test, ::testing::Values(
	// tx_offset, tx_size
	tx_param_test(0, 1, qdma::instance_ext::type::vf),
	tx_param_test(0, 4_kB - 1, qdma::instance_ext::type::vf),
	tx_param_test(0, 4_kB, qdma::instance_ext::type::vf),
	tx_param_test(0, 4_kB + 1, qdma::instance_ext::type::vf),
	tx_param_test(0, 8_kB, qdma::instance_ext::type::vf),
	tx_param_test(0, 16_kB, qdma::instance_ext::type::vf),
	tx_param_test(0, 32_kB, qdma::instance_ext::type::vf),
	tx_param_test(0, 64_kB, qdma::instance_ext::type::vf),
	tx_param_test(0, 128_kB, qdma::instance_ext::type::vf),
	tx_param_test(0, 256_kB, qdma::instance_ext::type::vf),
	tx_param_test(0, 512_kB, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(VF_MM004_tx_offsets, qdma_mm_test, ::testing::Values(
	// tx_offset, tx_size
	tx_param_test(1, 1, qdma::instance_ext::type::vf),
	tx_param_test(4_kB, 4_kB, qdma::instance_ext::type::vf),
	tx_param_test(252_kB, 4_kB, qdma::instance_ext::type::vf),
	tx_param_test(256_kB - 1, 1, qdma::instance_ext::type::vf)
));

#ifdef DPDK
INSTANTIATE_TEST_CASE_P(NT006_MM_ring_sizes, qdma_neg_mm_inv_ring_size_test, ::testing::Values(
	// ring_size, tx_size, num_tx
	ring_size_test(7, 4_kB ,1000)
));

INSTANTIATE_TEST_CASE_P(VF_NT006_MM_ring_sizes, qdma_neg_mm_inv_ring_size_test, ::testing::Values(
			// ring_size, tx_size, num_tx
			ring_size_test(7, 4_kB ,1000, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(DISABLED_NT016_MM_overflow_test, qdma_neg_mm_overflow_test, ::testing::Values(
	// ring_size, tx_size, num_tx
	negative_overflow_test(256, 512_kB ,1000)
));

INSTANTIATE_TEST_CASE_P(DISABLED_VF_NT016_MM_overflow_test, qdma_neg_mm_overflow_test, ::testing::Values(
			// ring_size, tx_size, num_tx
			negative_overflow_test(256, 512_kB ,1000, qdma::instance_ext::type::vf)
	));

INSTANTIATE_TEST_CASE_P(NT008_MM_read_write_without_start, qdma_neg_mm_proc_without_start_test, ::testing::Values(
	// ring_size, tx_size, num_tx
	ring_size_test(256, 4_kB ,1000)
));

INSTANTIATE_TEST_CASE_P(VF_NT008_MM_read_write_without_start, qdma_neg_mm_proc_without_start_test, ::testing::Values(
			// ring_size, tx_size, num_tx
			ring_size_test(256, 4_kB ,1000, qdma::instance_ext::type::vf)
	));
#elif defined(_WIN32)
INSTANTIATE_TEST_CASE_P(NT008_MM_read_write_without_start, qdma_neg_mm_proc_without_start_test, ::testing::Values(
    // ring_size, tx_size, num_tx
    ring_size_test(4, 4_kB, 1000)
));

INSTANTIATE_TEST_CASE_P(NT010_to_NT014_MM_invalid_qid_ops, qdma_neg_inv_qid_ops, ::testing::Values(
    // ring_size, tx_size, num_tx
    ring_size_test(4, 4_kB, 1)
));

#endif
