/*
 * xlnx_pci.h
 *
 *  Created on: Feb 5, 2018
 *      Author: alexande
 */

#ifndef QDMA_TEST_XLNX_XLNX_PCI_H_
#define QDMA_TEST_XLNX_XLNX_PCI_H_

#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <system_error>


#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <rte_eal.h> /**> rte_eal_init */
#include <rte_debug.h> /**> for rte_panic */
#include <rte_ethdev.h> /**> rte_eth_rx_burst */
#include <rte_errno.h> /**> rte_errno global var */
#include <rte_memzone.h> /**> rte_memzone_dump */
#include <rte_memcpy.h>
#include <rte_malloc.h>
#include <rte_cycles.h>
#include <rte_log.h>
#include <rte_string_fns.h>
#include <rte_mbuf.h>
#include <getopt.h>
#include "qdma_dpdk.h"

struct pci_id {
    unsigned bus = 0;
    unsigned dev = 0;
    unsigned fn = 0;
};

inline std::string to_string(pci_id id) {
    // 01:02:3
    // where bus_id=0x01, dev_id=0x02, fn_id=3
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    ss << std::setw(2) << id.bus << ":";
    ss << std::setw(2) << id.dev << ".";
    ss << id.fn;
    return ss.str();
}

class pcie_bar{
public:

	pcie_bar (uint32_t id, size_t bar) {
		bar_num = bar;
		m_id = id;
		pci_id bdf;
		rte_pmd_qdma_get_bdf(m_id, &bdf.bus, &bdf.dev, &bdf.fn);

		const auto dev_path = get_device_resource_path(bdf);
		const auto bar_path = get_bar_resource_path(bdf, bar);
		std::ifstream resource_map(dev_path);

		for (size_t i = 0; i <= bar; i++) {
			size_t start, end, flags;
			resource_map >> std::hex >> start >> end >> flags;
			if (i == bar) {
				mapped_size = end - start + 1;
			}
		}

		int fd = open(bar_path.c_str(), O_RDWR);
		if (fd < 0) {
			throw std::system_error(errno, std::system_category(),
					"Failed to open bar resource! " + bar_path);
		}

		base = mmap(nullptr, mapped_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
		close(fd);

		if (base == MAP_FAILED) {
			mmap_fallback = 1;
			bar_num = bar;
			m_id = id;
		}
	}

    ~pcie_bar() {
        if (base && !mmap_fallback) {
            munmap(base, mapped_size);
        }
    }

    pcie_bar (const pcie_bar& rhs) = delete;
    pcie_bar& operator=(const pcie_bar& rhs) = delete;

    // Define move constructor and move assignment
    pcie_bar(pcie_bar && rhs)  {
        *this = std::move(rhs);
    }
    pcie_bar& operator=(pcie_bar&& rhs) {
        if (this != &rhs) {
            base = rhs.base; //pilfer
            rhs.base = nullptr; //reset
        }
        return *this;
    };

	template<typename T = uint32_t>
    void write(size_t address, T t) {
	rte_pmd_qdma_compat_pci_write_reg(m_id, bar_num, address, t);
    }

	template<typename T = uint32_t>
    T read(size_t address) {
	T reg_val = (T) rte_pmd_qdma_compat_pci_read_reg(m_id, bar_num, address);
    return reg_val;
    }

    template<typename T = uint32_t>
    void write(size_t address, T* t, size_t array_size) {
    		std::memcpy(get_aligned_addr<T>(address), t, array_size * sizeof(T));
    }

    template<typename T = uint32_t>
    void read(size_t address, T* t, size_t array_size) {
        	std::memcpy(t, get_aligned_addr<T>(address), array_size * sizeof(T));
     }

    static std::string get_device_resource_path(pci_id id) {
        // /sys/bus/pci/devices/0000:01:02:3/resource
        // where bus_id=0x01, dev_id=0x02, fn_id=3
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        ss << "/sys/bus/pci/devices/0000:" << to_string(id) << "/resource";
        return ss.str();
    }

    static std::string get_bar_resource_path(pci_id id, uint32_t bar) {
    std::stringstream ss;
    ss << get_device_resource_path(id) << bar;
        return ss.str();
    }

protected:
    void* base = nullptr;
    size_t mapped_size = 0;
    bool mmap_fallback = 0;
    unsigned int bar_num = 0;
    uint32_t m_id;

    template<typename T = uint32_t>
    T* get_aligned_addr(size_t address) {
        return &static_cast<T*>(base)[address / sizeof(T)];
    }


};

#endif /* QDMA_TEST_XLNX_XLNX_PCI_H_ */
