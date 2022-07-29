/*
 * qdma_device.cpp
 *
 *  Created on: Feb 5, 2018
 *      Author: alexande
 */

#include "qdma_device.h"

#include <iostream>
#include <sstream>
#include "xlnx_util.h"

namespace qdma {

device::device(instance& drv, const info& details)
    : m_id(details.id), max_num_queues(details.max_num_queues), dev_cap(details.dev_cap), m_drv(drv) {


    // save pointer to dma control bar
    m_pcie_bars.reserve(3);

    m_pcie_bars.emplace_back(m_id, details.dma_bar_idx);
    dma_bar = m_pcie_bars.data();

    // save pointer to user_bar
    if (details.user_bar_idx != -1) {

        m_pcie_bars.emplace_back(m_id, details.user_bar_idx);
        user_bar = m_pcie_bars.data() + 1;
    }
	 // save pointer to bypass_bar
	if (details.bypass_bar_idx != -1) {

		m_pcie_bars.emplace_back(m_id, details.bypass_bar_idx);
		bypass_bar = m_pcie_bars.data() + 2;
    }
}

} // namespace qdma
