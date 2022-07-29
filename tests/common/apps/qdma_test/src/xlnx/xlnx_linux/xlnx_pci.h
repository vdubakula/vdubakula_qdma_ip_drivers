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

#include <qdma/qdma_nl.h>
#include <xlnx_netlink.h>

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

class pcie_bar {
public:

    pcie_bar(pci_id id, size_t bar, bool is_vf)
	: qdma_socket(is_vf ? XNL_NAME_VF : XNL_NAME_PF) {

        const auto dev_path = get_device_resource_path(id);
        const auto bar_path = get_bar_resource_path(id, bar);
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

    pcie_bar(const pcie_bar& rhs) = delete;
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
    	if (!mmap_fallback) {
			auto b = get_aligned_addr<T>(address);
			*b = t;
    	} else {
			unsigned dev_id = (m_id.bus << 12) | (m_id.dev << 4) | (m_id.fn);
			auto cmd = qdma_socket.prepare_msg(XNL_CMD_REG_WRT);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
			cmd.add_attribute(XNL_ATTR_REG_BAR_NUM, bar_num);
			cmd.add_attribute(XNL_ATTR_REG_ADDR, address);
			cmd.add_attribute(XNL_ATTR_REG_VAL, t);
			qdma_socket.send_msg(cmd);
			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);
			if (not resp_str) {
				throw std::runtime_error("XNL_ATTR_GENMSG did not return a string");
			}
    	}
    }

    template<typename T = uint32_t>
    T read(size_t address) {
    	if (!mmap_fallback) {
    		return *get_aligned_addr<T>(address);
    	} else {
			unsigned dev_id = (m_id.bus << 12) | (m_id.dev << 4) | (m_id.fn);
			auto cmd = qdma_socket.prepare_msg(XNL_CMD_REG_RD);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
			cmd.add_attribute(XNL_ATTR_REG_BAR_NUM, bar_num);
			cmd.add_attribute(XNL_ATTR_REG_ADDR, address);
			qdma_socket.send_msg(cmd);
			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			T reg_val = resp.get_attrib<T>(XNL_ATTR_REG_VAL);
			return reg_val;
    	}
    }

    template<typename T = uint32_t>
    void write(size_t address, T* t, size_t array_size) {
    	if(!mmap_fallback) {
    		std::memcpy(get_aligned_addr<T>(address), t, array_size * sizeof(T));
    	} else {
    		size_t i;
    		unsigned dev_id = (m_id.bus << 12) | (m_id.dev << 4) | (m_id.fn);
    		for(i = 0; i < (array_size * sizeof(T)); i++) {
    			auto cmd = qdma_socket.prepare_msg(XNL_CMD_REG_WRT);
    			cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
    			cmd.add_attribute(XNL_ATTR_REG_BAR_NUM, bar_num);
    			cmd.add_attribute(XNL_ATTR_REG_ADDR, address);
    			address += sizeof(uint32_t);
    			cmd.add_attribute(XNL_ATTR_REG_VAL, *t);
    			t++;
    			qdma_socket.send_msg(cmd);
    			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);
    			if (not resp_str) {
    				throw std::runtime_error("XNL_ATTR_GENMSG did not return a string");
        	    }
    		}
    	}
    }

    template<typename T = uint32_t>
    void read(size_t address, T* t, size_t array_size) {
    	if(!mmap_fallback) {
    		std::memcpy(t, get_aligned_addr<T>(address), array_size * sizeof(T));
    	} else {
    		size_t i;
    		unsigned dev_id = (m_id.bus << 12) | (m_id.dev << 4) | (m_id.fn);
    		for(i = 0; i < (array_size * sizeof(T)); i++) {
    			auto cmd = qdma_socket.prepare_msg(XNL_CMD_REG_RD);
    			cmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
    			cmd.add_attribute(XNL_ATTR_REG_BAR_NUM, bar_num);
    			cmd.add_attribute(XNL_ATTR_REG_ADDR, address);
    			address += sizeof(uint32_t);
    			qdma_socket.send_msg(cmd);
    			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    			uint32_t reg_val = resp.get_attrib<uint32_t>(XNL_ATTR_REG_VAL);
    			*t = reg_val;
    			t++;
    		}
    	}
    }

    static bool exists(pci_id id, uint32_t bar) {
        const auto path = get_bar_resource_path(id, bar);
        return ( access( path.c_str(), F_OK ) != -1 );
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

private:
    void* base = nullptr;
    size_t mapped_size = 0;
    bool mmap_fallback = 0;
    unsigned int bar_num = 0;
    pci_id m_id;
#ifdef TEST_VF_ALONE
    xnl::socket qdma_socket { XNL_NAME_VF };
#else
    xnl::socket qdma_socket { XNL_NAME_PF };
#endif

    template<typename T = uint32_t>
    T* get_aligned_addr(size_t address) {
        return &static_cast<T*>(base)[address / sizeof(T)];
    }
};

#endif /* QDMA_TEST_XLNX_XLNX_PCI_H_ */
