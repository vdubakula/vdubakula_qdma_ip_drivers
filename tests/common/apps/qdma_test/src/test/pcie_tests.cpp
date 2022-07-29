
#include <array>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <vector>

#include <gtest/gtest.h>
#include <xlnx_gtest_ext.h>

#include "qdma_device.h"
#include "test_env.h"

// ===============================Test framework helpers ==========================================

extern test_env env; // in main.cpp

class qdma_pcie_test: public testing::TestWithParam<qdma::instance_ext::type> {};

bool config_bar_access(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

    for(uint32_t func = 0; func < devlist.size(); func++) {
        auto& qdev = devlist[func];
        if (!qdev.max_num_queues)
            continue;

        if (qdev.dma_bar == nullptr)
            return false;

        auto& control_bar = *qdev.dma_bar;

        static const uint32_t addr = 0x244; // scratch register PF0

        // precondition
        if (control_bar.read<uint32_t>(addr) != 0x0)
            return false;

        // set all bits
        control_bar.write(addr, 0xffffffff);
        if (control_bar.read<uint32_t>(addr) != 0xffffffff)
            return false;

        // arbitrary pattern
        control_bar.write(addr, 0xdeadbeef);
        if (control_bar.read<uint32_t>(addr) != 0xdeadbeef)
            return false;

        // restore to old value
        control_bar.write(addr, 0x0);
        if (control_bar.read<uint32_t>(addr) != 0x0)
            return false;
    }
    return true;
}

bool user_bar_access(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

    for(uint32_t func = 0; func < devlist.size(); func++) {
        auto& qdev = devlist[func];
        if (!qdev.max_num_queues)
            continue;

        if (qdev.user_bar == nullptr)
            return false;

        auto& user_bar = *qdev.user_bar;

        std::array<uint8_t, 0x20> buffer = { { 0 } };
        std::iota(begin(buffer), end(buffer), uint8_t(0));

        user_bar.write(0x030, buffer.data(), buffer.size());
        buffer.fill(0xff);
        user_bar.read(0x030, buffer.data(), buffer.size());

        for (unsigned i = 0; i < buffer.size(); ++i) {
            if (buffer[i] != i)
                return false;
        }
    }
    return true;
}

bool bypass_bar_access(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

    for(uint32_t func = 0; func < devlist.size(); func++) {
        auto& qdev = devlist[func];
        if (!qdev.max_num_queues)
            continue;

        if (qdev.bypass_bar == nullptr)
            return false;

        auto& bypass_bar = *qdev.bypass_bar;

        std::array<uint8_t, 0x100> buffer = { { 0 } };
        std::iota(begin(buffer), end(buffer), uint8_t(0));

        bypass_bar.write(0x100, buffer.data(), buffer.size());
        buffer.fill(0xff);
        bypass_bar.read(0x100, buffer.data(), buffer.size());

        for (unsigned i = 0; i < buffer.size(); ++i) {
            if (buffer[i] != i)
                return false;
        }
    }
    return true;
}

TEST_P(qdma_pcie_test, PCIE001_config_bar_access)
{
    ASSERT_TRUE(config_bar_access(GetParam()));
}

TEST_P(qdma_pcie_test, PCIE002_user_bar_access)
{
    ASSERT_TRUE(user_bar_access(GetParam()));
}

TEST_P(qdma_pcie_test, PCIE003_bypass_bar_access)
{
    ASSERT_TRUE(bypass_bar_access(GetParam()));
}

INSTANTIATE_TEST_CASE_P(PCIE_tests, qdma_pcie_test,
            ::testing::Values(qdma::instance_ext::type::pf));
//TO Do
/** Disabling the VF PCI test cases, as the DMA Bar scratch register
     is a global register which is not accessible for VFs
     bypass bar and user bar access checks are also not done for VFs
     This test case will be enabled, when HW team provides the scratch register
     for VFs
*/
INSTANTIATE_TEST_CASE_P(DISABLED_VF_PCIE_tests, qdma_pcie_test,
            ::testing::Values(qdma::instance_ext::type::vf));
