#ifdef _WIN32
#define NOMINMAX
#endif

#include <algorithm>
#include <cstdint>
#include <exception>
#include <functional>
#include <numeric>
#include <string>
#include <thread>
#include <vector>
#include <stddef.h>

#include <gtest/gtest.h>

#include "example_design_ctrl.h"
#include "qdma_instance.h"
#include "qdma_queue.h"
#include "test_env.h"
#include "xlnx_gtest_ext.h"
#include "xlnx_util.h"

// =============================== Test framework helpers ==========================================

extern test_env env; // in main.cpp

struct threaded_test_params {

    struct transfer {
        uint32_t pf = 0;
        uint32_t q = 0;
        uint32_t it = 0;
        uint32_t size = 0;
        mutable uint32_t flag = 0;
        qdma::device& qdev;

        transfer(uint32_t pf_id, uint32_t q_id, uint32_t iterations, uint32_t ts, qdma::device& _qdev=env.pfs.front())
            : pf(pf_id), q(q_id), it(iterations), size(ts), qdev(_qdev) {}
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

    threaded_test_params() = default;
#ifdef DPDK
    threaded_test_params(std::vector<fmap>&& fmaps, std::vector<transfer>&& txs, qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
            : pfs(std::move(fmaps)), transfers(std::move(txs)), qcfg(_qcfg) {
        }
    threaded_test_params(std::vector<fmap>&& fmaps, std::vector<transfer>&& txs, qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf , qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
    	    : pfs(std::move(fmaps)), transfers(std::move(txs)), devtype(dev_type), qcfg(_qcfg) {
    	}
#else
    threaded_test_params(std::vector<transfer>&& txs, qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
        : transfers(std::move(txs)), qcfg(_qcfg) {
    }

    threaded_test_params(std::vector<transfer>&& txs, qdma::instance_ext::type dev_type,  qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
        : transfers(std::move(txs)), devtype(dev_type), qcfg(_qcfg) {
    }
#endif
};

void PrintTo(const threaded_test_params& tp, std::ostream* os) {

    const auto& txs = tp.transfers;
    //only print the ranges (first and last entry)
    if (!txs.empty()) {
        *os << "{ pfs=[" << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.front().pf
                << ":" << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.back().pf << "], ";
        *os << "queues=[" << txs.front().q << ":" << txs.back().q << "], ";
        *os << "iterations=" << txs.front().it << ", ";
        *os << "tx_size=" << txs.front().size << " }";
    }
}

// Separate test group class for concurrent tests of MM queues
class qdma_threaded_test: public testing::TestWithParam<threaded_test_params> {
    void SetUp() override {
        // TODO clear BRAM via bypass BAR
    }

public:
    std::vector<std::thread> workers;

    template<typename Callable>
    void execute_in_parallel(Callable& work, const threaded_test_params& tp) {
        workers.reserve(tp.transfers.size());
        for (const auto& tx : tp.transfers) {
            workers.emplace_back(work, std::ref(tx));
        }
        for (auto& w : workers) {
            w.join();
        }
    }
};

class qdma_threaded_mm_test: public qdma_threaded_test {};
class qdma_threaded_st_test: public qdma_threaded_test {};

// ====================== Test Case Parameter Generators ===========================================

/// create test scenario where for each queue in num_q, it cycles through num_pf and executes num_it
/// transfers of tx_size bytes.
/// e.g.  interleaved_tx_test(2, 4, 1, 4K) produces:
///     [0] = { pf=0, q=0, it=1, tx_size=4k }
///     [1] = { pf=1, q=1, it=1, tx_size=4k }
///     [2] = { pf=0, q=2, it=1, tx_size=4k }
///     [3] = { pf=1, q=3, it=1, tx_size=4k }
static threaded_test_params interleaved_tx_test(unsigned num_func, unsigned num_q, unsigned num_it,
                                                size_t tx_size, qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

    std::vector<threaded_test_params::transfer> transfers;
    transfers.reserve(num_q);

    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

    if (num_func > devlist.size())
		num_func = (unsigned int)devlist.size();

#ifdef DPDK
    std::vector<threaded_test_params::fmap> fmaps;
    uint32_t base = 0;
    fmaps.reserve(num_func);
#endif

    for (unsigned func_index = 0; func_index < num_func; func_index++) {
    	if (!devlist[func_index].max_num_queues)
			continue;

        if (num_q > devlist[func_index].max_num_queues) {
        	num_q = devlist[func_index].max_num_queues;
        }
#ifdef DPDK
	    	fmaps.emplace_back(devlist[func_index].dev_id, base, num_q);
	    	base += num_q;
#endif
		for (unsigned q = 0; q < num_q; q++) {
				transfers.emplace_back(devlist[func_index].dev_id, q, num_it, (uint32_t)tx_size, devlist[func_index]);
        }
    }
#ifdef DPDK
    return threaded_test_params { std::move(fmaps), std::move(transfers), dev_type};
#else
    return threaded_test_params { std::move(transfers), dev_type};
#endif
}

// ====================== Test Cases (Fixtures) ====================================================

TEST_F(qdma_threaded_mm_test, MM008_q_open_close_threaded) {

    if (!env.pfs.empty())
    {
	    qdma::queue_ext::config config;
#ifdef DPDK
	    struct rte_eth_conf	    port_conf;
	    for(uint32_t pf = 0; pf < env.pfs.size(); pf++) {
			memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
			auto& qdev = env.pfs[pf];
			if (!env.pfs[pf].max_num_queues)
				continue;
			try{
				rte_eth_dev_configure(env.pfs[pf].dev_id, qdev.max_num_queues, qdev.max_num_queues, &port_conf);
			} catch (const std::exception& e){
				FAIL() << "Cannot configure port %d"<< env.pfs[pf].dev_id << e.what();
			}
	    }
#endif

	    auto work = [](uint32_t pf, uint32_t qid, qdma::queue_ext::direction dir, const qdma::queue_ext::config& config) {
			const auto mode = qdma::queue_ext::mode::memory_mapped;
			SCOPED_TRACE("pf=" + int_to_hex(pf));
			SCOPED_TRACE("queue=" + std::to_string(qid));
			EXPECT_NO_THROW(
				qdma::instance_ext pf_driver { qdma::instance_ext::type::pf };
				qdma::queue_ext q(pf_driver, pf, qid, mode, dir, config)
			) << "failed to open h2c queue";
	    };

		// keep number of open threads/qdma_instances limited
		const int block_size = 10;
#ifdef _WIN32
		workers.reserve(block_size); // For windows, one add will enable both h2c and c2h dir
#else
        workers.reserve(block_size * 2); // h2c and c2h and per pf
#endif
		for (size_t pf = 0; pf < env.pfs.size(); pf++) {
			if (!env.pfs[pf].max_num_queues) {
				continue;
			}
			const int max_qid = env.pfs[pf].max_num_queues;
			for (int qid_block = 0; qid_block < max_qid; qid_block+= block_size) {
				const int qid_end = std::min(max_qid, qid_block + block_size);
				for (int qid = qid_block; qid < qid_end; qid++) {
					workers.emplace_back(work, env.pfs[pf].dev_id, qid, qdma::queue_ext::direction::host_to_card, config);
#ifndef _WIN32
					workers.emplace_back(work, env.pfs[pf].dev_id, qid, qdma::queue_ext::direction::card_to_host, config);
#endif
				}
				for (auto& w : workers) {
					w.join();
				}
				workers.clear();
			}

		}
#ifdef DPDK
	    for(uint32_t pf = 0; pf < env.pfs.size(); pf++){
			if (!env.pfs[pf].max_num_queues)
				continue;
			rte_pmd_qdma_dev_close(env.pfs[pf].dev_id);
	    }
#endif
    }
    else
    {
	    std::cout << "PF List Empty...Bypassing the Test" << std::endl;
    }
}

TEST_F(qdma_threaded_st_test, ST017_q_open_close_threaded) {
    ASSERT_FALSE(env.pfs.empty());
    qdma::queue_ext::config config;

#ifdef DPDK
	struct rte_eth_conf	    port_conf;
	for(uint32_t pf = 0; pf < env.pfs.size(); pf++){
		memset(&port_conf, 0x0, sizeof(struct rte_eth_conf));
		auto& qdev = env.pfs[pf];
		if (!env.pfs[pf].max_num_queues)
			continue;
		try{
			rte_eth_dev_configure(env.pfs[pf].dev_id, qdev.max_num_queues, qdev.max_num_queues, &port_conf);
		} catch (const std::exception& e){
			FAIL() << "Cannot configure port %d"<< env.pfs[pf].dev_id << e.what();
		}
	}
#endif

    auto work = [](uint32_t pf, uint32_t qid, qdma::queue_ext::direction dir, const qdma::queue_ext::config& config) {
        const auto mode = qdma::queue_ext::mode::streaming;
        SCOPED_TRACE("pf=" + int_to_hex(pf));
        SCOPED_TRACE("queue=" + std::to_string(qid));
        EXPECT_NO_THROW(
                qdma::instance_ext pf_driver { qdma::instance_ext::type::pf };
                qdma::queue_ext q(pf_driver, pf, qid, mode, dir, config)
        ) << "failed to open h2c queue";
    };

	// keep number of open threads/qdma_instances limited
	const int block_size = 10;
#ifdef _WIN32
    workers.reserve(block_size); // For windows, one add will enable both h2c and c2h dir
#else
	workers.reserve(block_size * 2); // h2c and c2h and per pf
#endif
	for (size_t pf = 0; pf < env.pfs.size(); pf++) {
		if (!env.pfs[pf].max_num_queues) {
			continue;
		}
		const int max_qid = env.pfs[pf].max_num_queues;
		for (int qid_block = 0; qid_block < max_qid; qid_block+= block_size) {
			const int qid_end = std::min(max_qid, qid_block + block_size);
			for (int qid = qid_block; qid < qid_end; qid++) {
				workers.emplace_back(work, env.pfs[pf].dev_id, qid, qdma::queue_ext::direction::host_to_card, config);
#ifndef _WIN32
				workers.emplace_back(work, env.pfs[pf].dev_id, qid, qdma::queue_ext::direction::card_to_host, config);
#endif
			}
			for (auto& w : workers) {
				w.join();
			}
			workers.clear();
		}

	}
#ifdef DPDK
	for(uint32_t pf = 0; pf < env.pfs.size(); pf++){
		if (!env.pfs[pf].max_num_queues)
			continue;
		rte_pmd_qdma_dev_close(env.pfs[pf].dev_id);
	}
#endif
}

// ====================== Test Cases (Parameterized) ===============================================
#ifndef _WIN32
TEST_P(qdma_threaded_mm_test, mm_h2c_c2h) {
    // test case constants
    using pattern_t = uint8_t;
    const auto  dir = qdma::queue_ext::direction::both;
    const auto& tp = GetParam();
    const auto mode = qdma::queue_ext::mode::memory_mapped;
    const auto array_size = example_design_ctrl::bram_size / sizeof(pattern_t);

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

    // define work function to create queues and execute transfers
    auto work = [&](const threaded_test_params::transfer& tx) {
        try {
            aligned_vector<pattern_t> wr_buffer(array_size);
            aligned_vector<pattern_t> rd_buffer(array_size);
            // setup test buffers
            SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
            SCOPED_TRACE("queue=" + std::to_string(tx.q));

            // setup user logic
            example_design_ctrl user_logic(tx.qdev);
            // setup user logic
            if(tp.qcfg.desc_bypass)
            	user_logic.set_bypass_mode(mode, dir, DESC_BYPASS_MODE);
            else
            	user_logic.set_bypass_mode(mode, dir, NO_BYPASS_MODE);

            qdma::queue_ext q(drv, tx.pf, tx.q, mode, dir, tp.qcfg);

            for (unsigned i = 0; i < tx.it; i++) {
                std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0));    // 0, 1, 2, 3, 4 ...
                std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
                ASSERT_NE(rd_buffer, wr_buffer);
                SCOPED_TRACE("iteration=" + std::to_string(i));

                EXPECT_NO_THROW(q.write(wr_buffer.data(), tx.size, 0))
                    << "h2c transfer returned with an error!";
                usleep(1000);
                EXPECT_NO_THROW(q.read(rd_buffer.data(), tx.size, 0))
                    << "c2h transfer returned with an error!";

                // Compare read data with expected
                auto cmp_result = std::memcmp(wr_buffer.data(),
                                              rd_buffer.data(), tx.size);
                EXPECT_EQ(cmp_result, 0) << "data returned from c2h tx does not match h2c data!\n"
                        << print_diffs(wr_buffer.cbegin(), wr_buffer.cend(), rd_buffer.cbegin());
            }
        } catch (const std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    };

    execute_in_parallel(work, tp);

#ifdef DPDK
    for(const auto& pf : tp.pfs){
    	if (pf.qmax){
    		rte_pmd_qdma_dev_close(pf.dev_id);
    	}
    }
#endif
}
#endif

TEST_P(qdma_threaded_st_test, st_c2h) {

    using pattern_t = example_design_ctrl::pattern_t;
    const auto& tp = GetParam();
    const auto mode = qdma::queue_ext::mode::streaming;
    const auto dir = qdma::queue_ext::direction::card_to_host;
    const auto array_size = example_design_ctrl::bram_size / sizeof(pattern_t);

    qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);

    // get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

    if (!tp.transfers.size())
    	return;

    // setup buffers - each transfer scenario has its own read buffer
    std::vector<aligned_vector<pattern_t>> rd_buffers;
    rd_buffers.reserve(tp.transfers.size());
    for (const auto& tx : tp.transfers) {
        rd_buffers.emplace_back(tx.size * tx.it);
    }

    // we only need a single buffer for expected data pattern
    aligned_vector<pattern_t> expected(array_size);
    auto ex_it = expected.begin();
    for (size_t i = 0; i < tp.transfers.front().it; i++) {
        auto chunk_size = tp.transfers.front().size / sizeof(pattern_t);
        std::iota(ex_it, ex_it + chunk_size, static_cast<pattern_t>(0));    // 0, 1, 2, 3, 4 ...
        ex_it += chunk_size;
    }

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
    // open queues
    std::vector<qdma::queue_ext> c2h_qs;
    c2h_qs.reserve(tp.transfers.size());
    for (const auto& tx : tp.transfers) {
        SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
        SCOPED_TRACE("queue=" + std::to_string(tx.q));

        c2h_qs.emplace_back(drv, tx.pf, tx.q, mode, dir, tp.qcfg);
    }

    // start threads to read data
    auto work = [&](uint32_t idx) {
        auto& tx = tp.transfers[idx];
        auto& c2h_q = c2h_qs[idx];
        auto& rd_buffer = rd_buffers[idx];
        SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
        SCOPED_TRACE("queue=" + std::to_string(tx.q));
#ifdef DPDK
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
#endif
        for (unsigned i = 0; i < tx.it; i++) {
            SCOPED_TRACE("iteration=" + std::to_string(i));
#ifdef DPDK
	    	while(!tx.flag)
        	std::this_thread::sleep_for(std::chrono::milliseconds(1));
#endif
            int offset = i * tx.size / sizeof(pattern_t);
            ASSERT_NO_THROW(c2h_q.read(rd_buffer.data() + offset, tx.size))
                << "c2h transfer returned with an error!";
#ifdef DPDK
            tx.flag=0;
#endif
        }
    };
    workers.reserve(tp.transfers.size());
    for (size_t i = 0; i < tp.transfers.size(); i++) {
        workers.emplace_back(work, (uint32_t)i);
    }

    // trigger data packets - interleaved
    for (uint32_t i = 0; i < tp.transfers[0].it; i++) {
        for (auto& tx : tp.transfers) {
		// setup user logic
        	example_design_ctrl user_logic(tx.qdev);

            if(tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass)
            	user_logic.set_bypass_mode(mode, dir, SIMPLE_BYPASS_MODE);
            else if (tp.qcfg.desc_bypass)
            	user_logic.set_bypass_mode(mode, dir, CACHE_BYPASS_MODE);
            else
            	user_logic.set_bypass_mode(mode, dir, NO_BYPASS_MODE);

            user_logic.set_wrb_desc_size(tp.qcfg.cmptsz);
            user_logic.set_st_loopback(false);
#ifdef DPDK
        	const auto hw_qid = get_hw_qid(tx.pf, tx.q);
        	while(tx.flag)
        		std::this_thread::sleep_for(std::chrono::milliseconds(1));
        	user_logic.configure_c2h(hw_qid, tx.size, 1);
        	user_logic.generate_packets();
        	tx.flag = 1;
        	std::this_thread::sleep_for(std::chrono::milliseconds(1)); // fixme
#else
        	const auto hw_qid = get_hw_qid(tx.pf, tx.q, devlist);
        	user_logic.configure_c2h(hw_qid, tx.size, 1);
        	user_logic.generate_packets();

#ifndef _WIN32
        	std::this_thread::sleep_for(std::chrono::milliseconds(1)); // fixme
#endif

#endif
        }
    }

    // wait until threads complete
    for (auto& w : workers) {
        w.join();
    }

    // compare results
    for (size_t i = 0; i < rd_buffers.size(); i++) {
        auto cmp_result = std::memcmp(expected.data(), rd_buffers[i].data(),
                tp.transfers[i].size * tp.transfers[i].it);
        EXPECT_EQ(0, cmp_result) << "packet data of tx" << i << " does not match expected pattern!\n"
                << print_diffs(expected.cbegin(), expected.cend(), rd_buffers[i].cbegin());
    }
#ifdef DPDK
    c2h_qs.erase(c2h_qs.begin(), c2h_qs.end());
    for(const auto& pf : tp.pfs){
    	if (pf.qmax){
    		//env.pfs[pf.dev_id].max_num_queues = 512;
    		rte_pmd_qdma_dev_close(pf.dev_id);
    	}
    }
#endif
}

// ====================== Test Parameter Definitions ===============================================

INSTANTIATE_TEST_CASE_P(MM009_threaded_tx, qdma_threaded_mm_test, ::testing::Values(
        // num_pf, num_q, num_tx, tx_size
        interleaved_tx_test(1, 4, 10, 4_kB),
        interleaved_tx_test(1, 64, 10, 4_kB),
        interleaved_tx_test(1, 16, 10, 16_kB),
        //interleaved_tx_test(4, 4, 10, 4_kB),
        //interleaved_tx_test(4, 64, 10, 4_kB),
        //interleaved_tx_test(4, 16, 10, 16_kB)
        interleaved_tx_test((unsigned)env.pfs.size(), 4, 10, 4_kB),
        interleaved_tx_test((unsigned)env.pfs.size(), 64, 10, 4_kB),
        interleaved_tx_test((unsigned)env.pfs.size(), 16, 10, 16_kB)
));


INSTANTIATE_TEST_CASE_P(VF_MM009_threaded_tx, qdma_threaded_mm_test, ::testing::Values(
        // num_vf, num_q, num_tx, tx_size
        interleaved_tx_test(1, 4, 10, 4_kB, qdma::instance_ext::type::vf),
        interleaved_tx_test(1, 64, 10, 4_kB, qdma::instance_ext::type::vf),
        interleaved_tx_test(1, 16, 10, 16_kB, qdma::instance_ext::type::vf),
        //interleaved_tx_test(4, 4, 10, 4_kB),
        //interleaved_tx_test(4, 64, 10, 4_kB),
        //interleaved_tx_test(4, 16, 10, 16_kB)
        interleaved_tx_test((unsigned)env.vfs.size(), 4, 10, 4_kB, qdma::instance_ext::type::vf),
        interleaved_tx_test((unsigned)env.vfs.size(), 64, 10, 4_kB, qdma::instance_ext::type::vf),
        interleaved_tx_test((unsigned)env.vfs.size(), 16, 10, 16_kB, qdma::instance_ext::type::vf)
));


INSTANTIATE_TEST_CASE_P(ST018_threaded_tx, qdma_threaded_st_test, ::testing::Values(
        // num_pf, num_q, num_tx, tx_size
        interleaved_tx_test(1, 4, 10, 4_kB),
        interleaved_tx_test(1, 64, 10, 4_kB),
        interleaved_tx_test(1, 16, 10, 16_kB),
        //interleaved_tx_test(4, 4, 10, 4_kB),
        //interleaved_tx_test(4, 64, 10, 4_kB),
        //interleaved_tx_test(4, 16, 10, 16_kB)
        interleaved_tx_test((unsigned)env.pfs.size(), 4, 10, 4_kB),
        interleaved_tx_test((unsigned)env.pfs.size(), 64, 10, 4_kB),
        interleaved_tx_test((unsigned)env.pfs.size(), 16, 10, 16_kB)
));

INSTANTIATE_TEST_CASE_P(VF_ST018_threaded_tx, qdma_threaded_st_test, ::testing::Values(
        // num_pf, num_q, num_tx, tx_size
        interleaved_tx_test(1, 4, 10, 4_kB, qdma::instance_ext::type::vf),
        interleaved_tx_test(1, 64, 10, 4_kB, qdma::instance_ext::type::vf),
        interleaved_tx_test(1, 16, 10, 16_kB, qdma::instance_ext::type::vf),
        //interleaved_tx_test(4, 4, 10, 4_kB),
        //interleaved_tx_test(4, 64, 10, 4_kB),
        //interleaved_tx_test(4, 16, 10, 16_kB)
        interleaved_tx_test((unsigned)env.vfs.size(), 4, 10, 4_kB, qdma::instance_ext::type::vf),
        interleaved_tx_test((unsigned)env.vfs.size(), 64, 10, 4_kB, qdma::instance_ext::type::vf),
        interleaved_tx_test((unsigned)env.vfs.size(), 16, 10, 16_kB, qdma::instance_ext::type::vf)
));

