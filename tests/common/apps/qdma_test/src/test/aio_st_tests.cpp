#include <cstddef>
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include <gtest/gtest.h>
#include <xlnx_gtest_ext.h>
#include <xlnx_util.h>
#include <xlnx_device_file.h>

#include "test_env.h"
#include "example_design_ctrl.h"
#include "qdma_device.h"

// ===============================Test framework helpers ==========================================

extern test_env env; // in main.cpp

struct st_aio_test_params {

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

    std::vector<transfer> transfers;
    qdma::instance::type devtype = qdma::instance_ext::type::pf;
    qdma::queue_ext::config qcfg;

    st_aio_test_params() = default;
	st_aio_test_params(std::vector<transfer>&& txs, qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
		: transfers(std::move(txs)), qcfg(_qcfg) {
	}
	st_aio_test_params(std::vector<transfer>&& txs, qdma::instance_ext::type dev_type, qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
		: transfers(std::move(txs)), devtype(dev_type), qcfg(_qcfg) {
	}

};

void PrintTo(const st_aio_test_params& tp, std::ostream* os) {

    const auto& txs = tp.transfers;
    //only print the ranges (first and last entry)
    if (not txs.empty()) {
		if (tp.devtype == qdma::instance_ext::type::vf)
			*os << "{ vfs=[" << txs.front().pf << ":" << txs.back().pf << "], ";
		else
			*os << "{ pfs=[" << txs.front().pf << ":" << txs.back().pf << "], ";

        *os << "queues=[" << txs.front().q << ":" << txs.back().q << "], ";
        *os << "iterations=" << txs.front().it << ", ";
        *os << "tx_offset=" << txs.front().offset << ", ";
        *os << "tx_size=" << txs.front().size << " }";
    }
}

class qdma_st_aio_test: public testing::TestWithParam<st_aio_test_params> {
public:
    virtual void SetUp() override {
        rd_buffer.resize(array_size);
        wr_buffer.resize(array_size);
        std::iota(wr_buffer.begin(), wr_buffer.end(), static_cast<pattern_t>(0)); // 0, 1, 2, 3, 4 ...
        std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
    }

    virtual void TearDown() override {
    	if(io_list) {
		io_destroy(ctxt);
    		free(io_list);
    		io_list = NULL;
    	}
    }

    using pattern_t = example_design_ctrl::pattern_t;
    static const auto mode = qdma::queue_ext::mode::streaming;
    static const auto array_size = example_design_ctrl::bram_size / sizeof(pattern_t);
    aligned_vector<pattern_t> rd_buffer;
    aligned_vector<pattern_t> wr_buffer;
    struct iocb **io_list = NULL;
    io_context_t ctxt;
};

static st_aio_test_params tx_param_test(const uint32_t tx_offset, const uint32_t tx_size,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {
    std::vector<st_aio_test_params::transfer> transfers;
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
    transfers.reserve(devlist.size());
    for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
			if (!devlist[pf_id].max_num_queues) {
				continue;
			}
            transfers.emplace_back(devlist[pf_id].dev_id, 0, 1, tx_offset, tx_size, devlist[pf_id]);
    }

    return st_aio_test_params { std::move(transfers), dev_type};
}

static std::vector<st_aio_test_params> randomized_tests(const uint32_t seed, const uint32_t num_tests, qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

    std::default_random_engine rne(seed);
    //std::uniform_int_distribution<uint32_t> rng_pf(0, env.pfs.size() - 1);    // pf
    std::uniform_int_distribution<uint32_t> rng_pf(0, devlist.size() - 1);    // pf
    std::uniform_int_distribution<uint32_t> rng_it(1, 9);    // iterations
    std::uniform_int_distribution<uint32_t> rng_ts(1, 28_kB);    // transfer size

    std::vector<st_aio_test_params> tp;
    for (uint32_t i = 0; i < num_tests; i++) {

    	if (!devlist.size())
    		continue;

        const auto pf = rng_pf(rne);
		//if (!env.pfs[pf].max_num_queues) {
		if (!devlist[pf].max_num_queues) {
			continue;
		}
        //std::uniform_int_distribution<uint32_t> rng_q(0, env.pfs[pf].max_num_queues - 1);    // queue
        std::uniform_int_distribution<uint32_t> rng_q(0, devlist[pf].max_num_queues - 1);    // queue
        const auto qid = rng_q(rne);
        const auto num_transfers = rng_it(rne);
        const auto transfer_size = rng_ts(rne);

        std::vector<st_aio_test_params::transfer> transfers;
        transfers.emplace_back(devlist[pf].dev_id, qid, num_transfers, 0, transfer_size, devlist[pf]);
        tp.emplace_back(std::move(transfers), dev_type);
    }
    return tp;
}

// ====================== Test Cases ==============================================================

TEST_P(qdma_st_aio_test, h2c_only) {

    // test case constants
    using dir = qdma::queue_ext::direction;
	const auto& tp = GetParam();
	qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());
	std::vector<struct iocb> aio_reqs;
    auto max_size = example_design_ctrl::bram_size + 1;

    aio_reqs.reserve(1);

    // execute code under test
    for (const auto& tx : tp.transfers) {

        if(validate_test_case(devlist, tx.pf, tp.qcfg)) {
            //GTEST_SKIP();
            std::cout << "Invalid Test Case" << std::endl;
            continue;
        }
        example_design_ctrl user_logic{ tx.qdev };
        user_logic.reset_pkt_ctrl();
        // setup user logic
        if(tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass)
            user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir::host_to_card, SIMPLE_BYPASS_MODE);
        else if (tp.qcfg.desc_bypass)
            user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir::host_to_card, CACHE_BYPASS_MODE);
        else
            user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir::host_to_card, NO_BYPASS_MODE);
        qdma::queue_ext h2c_q(drv, tx.pf, tx.q, mode, dir::host_to_card, tp.qcfg);
        const auto hw_qid = get_hw_qid(tx.pf, tx.q, devlist);

    	user_logic.set_queue(hw_qid);
    	user_logic.set_st_loopback(false);
    	unsigned char *wr_begin = (unsigned char *)wr_buffer.data();
    	io_list = (struct iocb **)calloc(1, sizeof(struct iocb *));

    	ASSERT_GT(max_size, tx.size);
    	SCOPED_TRACE("itr=" + std::to_string(tx.it));

    	for (unsigned i = 0; i < tx.it; i++) {
    		std::memset(aio_reqs.data(), 0, aio_reqs.capacity());
    		io_prep_pwrite(aio_reqs.data(),
    				static_cast<int>(h2c_q.get_handle()),
					wr_begin,
					static_cast<size_t>(tx.size),
					tx.offset);

    		io_list[0] = aio_reqs.data();
    		memset(&ctxt, 0, sizeof(ctxt));
    		EXPECT_EQ(io_queue_init(1, &ctxt), 0) << "Error: io_setup error";

    		user_logic.reset_h2c();
    		EXPECT_NO_THROW(h2c_q.aio_rw(ctxt, 1, io_list)) /* This will add all reads and writes */
    		<< "aio requests returned with an error!";
    		EXPECT_TRUE(user_logic.check_h2c(hw_qid, (tx.size == 0)))
    		<< "h2c data checker did not receive expected data pattern!";
    		io_destroy(ctxt);
    	}
    	free(io_list);
    	io_list=NULL;
    }
}

TEST_P(qdma_st_aio_test, c2h_only) {

    // test case constants
    using dir = qdma::queue_ext::direction;
    const auto& tp = GetParam();
    qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
    // get the pf/vf device list based on dev_type
    std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
    ASSERT_FALSE(devlist.empty());
    std::vector<struct iocb> aio_reqs;
    auto max_size = example_design_ctrl::bram_size + 1;

    aio_reqs.reserve(1);

    // execute code under test
    for (const auto& tx : tp.transfers) {
	example_design_ctrl user_logic{ tx.qdev };
	user_logic.reset_pkt_ctrl();
	// setup user logic
	if(tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass)
		user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir::card_to_host, SIMPLE_BYPASS_MODE);
	else if (tp.qcfg.desc_bypass)
		user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir::card_to_host, CACHE_BYPASS_MODE);
	else
		user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir::card_to_host, NO_BYPASS_MODE);
        qdma::queue_ext c2h_q(drv, tx.pf, tx.q, mode, dir::card_to_host, tp.qcfg);
        auto incr_size = tx.size;
        const auto hw_qid = get_hw_qid(tx.pf, tx.q, devlist);

        std::memset(aio_reqs.data(), 0, aio_reqs.capacity());
        user_logic.set_st_loopback(false);
        unsigned char *rd_begin = (unsigned char *)rd_buffer.data();

        ASSERT_GT(max_size, tx.size*tx.it);
        SCOPED_TRACE("incr_sz=" + std::to_string(incr_size));
        SCOPED_TRACE("itr=" + std::to_string(tx.it));

        io_list = (struct iocb **)calloc(1, sizeof(struct iocb *));

        for (unsigned i = 0; i < tx.it; i++) {
            io_prep_pread(aio_reqs.data(),
                          static_cast<int>(c2h_q.get_handle()),
                          rd_begin,
                          static_cast<size_t>(tx.size),
                          tx.offset);

            io_list[0] = aio_reqs.data();

            user_logic.configure_c2h(hw_qid, tx.size, 1);
            user_logic.generate_packets();
            memset(&ctxt, 0, sizeof(ctxt));
            EXPECT_EQ(io_queue_init(1, &ctxt), 0) << "Error: io_setup error";

            EXPECT_NO_THROW(c2h_q.aio_rw(ctxt, 1, io_list)) /* This will add all reads and writes */
                << "aio requests returned with an error!";
            unsigned char *wr_begin = (unsigned char *)rd_buffer.data();
            {
                 // Compare read data with expected
                auto cmp_result = std::memcmp(wr_begin, rd_begin, tx.size);
                EXPECT_EQ(cmp_result, 0) << "c2h data does not match expected pattern!\n"
                            << print_diffs(wr_buffer.cbegin(), wr_buffer.cend(), rd_buffer.cbegin());
            }
            std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
            io_destroy(ctxt);
        }
        // reset read buffer
        free(io_list);
        io_list=NULL;
    }
}

TEST_P(qdma_st_aio_test, DISABLED_h2c_c2h_loopback) {

    // test case constants
    using dir = qdma::queue_ext::direction;
    const auto& tp = GetParam();
	qdma::instance_ext &drv = env.get_drv_instance(tp.devtype);
	// get the pf/vf device list based on dev_type
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
    ASSERT_FALSE(devlist.empty());

    std::vector<struct iocb> aio_reqs;
    auto max_size = example_design_ctrl::bram_size + 1;

    aio_reqs.reserve(2);

    // execute code under test
    for (const auto& tx : tp.transfers) {
	example_design_ctrl user_logic(tx.qdev);
	user_logic.reset_pkt_ctrl();

	// setup user logic
	if(tp.qcfg.desc_bypass && tp.qcfg.pfetch_bypass)
		user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir::both, SIMPLE_BYPASS_MODE);
	else if (tp.qcfg.desc_bypass)
		user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir::both, CACHE_BYPASS_MODE);
	else
		user_logic.set_bypass_mode(qdma::queue_ext::mode::streaming, dir::both, NO_BYPASS_MODE);

        qdma::queue_ext h2c_q(drv, tx.pf, tx.q, mode, dir::host_to_card, tp.qcfg);
        qdma::queue_ext c2h_q(drv, tx.pf, tx.q, mode, dir::card_to_host, tp.qcfg);
        auto incr_size = tx.size;
        const auto hw_qid = get_hw_qid(tx.pf, tx.q, devlist);

        std::memset(aio_reqs.data(), 0, aio_reqs.capacity());
        user_logic.set_queue(hw_qid);
        user_logic.set_st_loopback(true);
        unsigned char * wr_begin = (unsigned char *)wr_buffer.data();
        unsigned char * rd_begin = (unsigned char *)rd_buffer.data();

        ASSERT_GT(max_size, tx.size*tx.it);
        ASSERT_GT(28_kB + 1, tx.size);
        SCOPED_TRACE("incr_sz=" + std::to_string(incr_size));
        SCOPED_TRACE("itr=" + std::to_string(tx.it));
        io_list = (struct iocb **)calloc(2, sizeof(struct iocb *));

        for (unsigned i = 0; i < tx.it; i++) {
            io_prep_pwrite(aio_reqs.data(),
                           static_cast<int>(h2c_q.get_handle()),
                           wr_begin,
                           static_cast<size_t>(tx.size),
                           tx.offset);
            io_prep_pread(aio_reqs.data() + 1,
                          static_cast<int>(c2h_q.get_handle()),
                          rd_begin,
                          static_cast<size_t>(tx.size),
                          tx.offset);

            io_list[0] = aio_reqs.data();
            io_list[1] = aio_reqs.data() + 1;

            memset(&ctxt, 0, sizeof(ctxt));
            EXPECT_EQ(io_queue_init(2, &ctxt), 0) << "Error: io_setup error";

            EXPECT_NO_THROW(h2c_q.aio_rw(ctxt, 2, io_list)) /* This will add all reads and writes */
                << "aio requests returned with an error!";
            {
                // Compare read data with expected
                auto cmp_result = std::memcmp(wr_buffer.data(), rd_buffer.data(), tx.size);
                EXPECT_EQ(cmp_result, 0) << "data returned from c2h tx does not match h2c data!\n"
                            << print_diffs(wr_buffer.cbegin(), wr_buffer.cend(), rd_buffer.cbegin());

                // reset read buffer
                std::fill(rd_buffer.begin(), rd_buffer.end(), static_cast<pattern_t>(0xAC));
            }
            io_destroy(ctxt);
        }
        free(io_list);
        io_list=NULL;
    }
}

//PF Test cases
INSTANTIATE_TEST_CASE_P(AIOST001_tx_sizes, qdma_st_aio_test, ::testing::Values(
        // tx_offset, tx_size
        tx_param_test(0, 1),
        tx_param_test(0, 4_kB - 1),
        tx_param_test(0, 4_kB),
        tx_param_test(0, 4_kB + 1),
        tx_param_test(0, 8_kB),
        tx_param_test(0, 16_kB),
        tx_param_test(0, 24_kB),
        tx_param_test(0, 28_kB)
));


INSTANTIATE_TEST_CASE_P(AIOST002_randomized_transfers, qdma_st_aio_test, ::testing::ValuesIn(
        // seed for random engine, num_tests to generate
        randomized_tests(env.random_seed, 10)
));
//PF Test case end

//VF Test cases
INSTANTIATE_TEST_CASE_P(VF_AIOST001_tx_sizes, qdma_st_aio_test, ::testing::Values(
        // tx_offset, tx_size
        tx_param_test(0, 1, qdma::instance_ext::type::vf),
        tx_param_test(0, 4_kB - 1, qdma::instance_ext::type::vf),
        tx_param_test(0, 4_kB, qdma::instance_ext::type::vf),
        tx_param_test(0, 4_kB + 1, qdma::instance_ext::type::vf),
        tx_param_test(0, 8_kB, qdma::instance_ext::type::vf),
        tx_param_test(0, 16_kB, qdma::instance_ext::type::vf),
        tx_param_test(0, 24_kB, qdma::instance_ext::type::vf),
        tx_param_test(0, 28_kB, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(VF_AIOST002_randomized_transfers, qdma_st_aio_test, ::testing::ValuesIn(
        // seed for random engine, num_tests to generate
        randomized_tests(env.random_seed, 10, qdma::instance_ext::type::vf)
));
//VF Test cases end
