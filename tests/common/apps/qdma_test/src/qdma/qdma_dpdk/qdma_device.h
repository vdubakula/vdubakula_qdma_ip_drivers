/*
 * qdma_device.hpp
 *
 *  Created on: Jan 22, 2018
 *      Author: alexande
 */

#ifndef QDMA_TEST_SRC_QDMA_DEVICE_HPP_
#define QDMA_TEST_SRC_QDMA_DEVICE_HPP_

#include <cstddef>
#include <vector>

#include "xlnx_pci.h"

extern int config_max_queues;
namespace qdma {


// ==================== forward declarations ======================================================

class instance;

// ==================== constants =================================================================

static constexpr size_t qdma_id_mask = 0xfff00000;
static constexpr size_t qdma_id = 0x1fd00000;

// ==================== declarations ===============================================================

class device {
public:

    struct info {
        uint32_t id;
        int dma_bar_idx = 0;
        int user_bar_idx = 0;
        int bypass_bar_idx = 0;
        int max_num_queues = 0;
        struct rte_pmd_qdma_dev_attributes dev_cap;
    };

    device(instance& drv, const info& details);

    pcie_bar* dma_bar = nullptr;
    pcie_bar* user_bar = nullptr;
    pcie_bar* bypass_bar = nullptr;

    uint32_t m_id;
    unsigned max_num_queues = 0;
    const unsigned max_num_queues_vf = 64; // TODO
    struct rte_pmd_qdma_dev_attributes dev_cap;
    uint32_t dev_id = 0;

private:
    instance& m_drv;
    std::vector<pcie_bar> m_pcie_bars;
};

} // namespace qdma

#endif /* QDMA_TEST_SRC_QDMA_DEVICE_HPP_ */
