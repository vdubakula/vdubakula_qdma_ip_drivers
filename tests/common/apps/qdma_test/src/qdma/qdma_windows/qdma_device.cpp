/*
 * qdma_device.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: arayajig
 */

#include "qdma_device.h"

#include <iostream>
#include <sstream>
#include <xlnx_device_file.h>
#include <xlnx_util.h>

namespace qdma {

device::device(instance& drv, const info& details)
    : m_id(details.id), max_num_queues(details.max_num_queues), qbase_start(details.qbase_start), m_drv(drv) {

    m_pcie_bars.reserve(3);
    if (not pcie_bar::exists(m_id, details.dma_bar_idx)) {
        throw std::runtime_error("dma_bar not present at index " + std::to_string(details.dma_bar_idx));
    }
    m_pcie_bars.emplace_back(m_id, details.dma_bar_idx);
    dma_bar = m_pcie_bars.data();

    if (details.user_bar_idx != -1) {
        if (not pcie_bar::exists(m_id, details.user_bar_idx)) {
            throw std::runtime_error("user_bar not present at index "
                                     + std::to_string(details.user_bar_idx)
                                     + " for device at "
                                     + pcie_bar::get_device_resource_path(details.id));
        }
        m_pcie_bars.emplace_back(m_id, details.user_bar_idx);
        user_bar = m_pcie_bars.data() + 1;
    }

    for (int i = 0; i < 9; i++) {
        if (i == details.dma_bar_idx || i == details.user_bar_idx) {
            continue;
        }
        if (pcie_bar::exists(m_id, i)) {
            m_pcie_bars.emplace_back(m_id, i);
            bypass_bar = m_pcie_bars.data() + 2;
            break;
        }
    }
}

} /* namespace qdma */
