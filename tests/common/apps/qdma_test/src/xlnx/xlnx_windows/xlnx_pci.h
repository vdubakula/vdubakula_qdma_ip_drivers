/*
 * xlnx_pci.h
 *
 *  Created on: Nov 29, 2018
 *      Author: arayajig
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

#include <win_helper.h>
#include "xlnx_device_file.h"

class pcie_bar {

public:
    std::string DevString;
    device_file bar;

    pcie_bar() {
        bar.h = INVALID_HANDLE_VALUE;
    }

    pcie_bar(std::string dev_path) {
        DevString = dev_path;
        bar.open(dev_path, GENERIC_WRITE | GENERIC_READ);
    }
    ~pcie_bar() {
        bar.close();
    }

    pcie_bar(const pcie_bar& rhs) = delete;
    pcie_bar& operator=(const pcie_bar& rhs) = delete;

    pcie_bar(pcie_bar && rhs) {
        this->bar.h = INVALID_HANDLE_VALUE;
    }

    template<typename T = uint32_t>
    void write(size_t address, T t) {
        bar.write<T>(address, t);
    }

    template<typename T = uint32_t>
    T read(size_t address) {
        return bar.read<T>(address);
    }

    void write(size_t address, void* t, size_t array_size) {
        bar.seek((long)address);
        bar.write(t, array_size);
    }

    void read(size_t address, void* t, size_t array_size) {
        bar.seek((long)address);
        bar.read(t, array_size);
    }
};

#endif /* QDMA_TEST_XLNX_XLNX_PCI_H_ */
