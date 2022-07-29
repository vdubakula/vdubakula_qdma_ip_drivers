/*
 * qdma_device.h
 *
 *  Created on: Nov 29, 2018
 *      Author: arayajig
 */

#ifndef QDMA_TEST_SRC_QDMA_DEVICE_HPP_
#define QDMA_TEST_SRC_QDMA_DEVICE_HPP_

#include <cstddef>
#include <vector>

#include <xlnx_pci.h>

enum qdma_windows_device_type {
    /** @QDMA_WIN_DEVICE_SOFT - UltraScale+ IP's  */
    QDMA_WIN_DEVICE_SOFT,
    /** @QDMA_LINUX_DEVICE_VERSAL_CPM4 -VERSAL IP  */
    QDMA_WIN_DEVICE_VERSAL,
    /** @EQDMA_DEVICE_SOFT - VERSAL CPM5  */
    EQDMA_WIN_DEVICE_SOFT,
    /** @QDMA_WIN_DEVICE_NONE - Not a valid device  */
    QDMA_WIN_DEVICE_NONE
};

enum qdma_windows_versal_ip_type {
    /** @QDMA_WIN_VERSAL_HARD_IP - Hard IP  */
    QDMA_WIN_VERSAL_HARD_IP,
    /** @QDMA_WIN_VERSAL_SOFT_IP - Soft IP  */
    QDMA_WIN_VERSAL_SOFT_IP,
    /** @QDMA_WIN_SOFT_IP - Soft IP  */
    QDMA_WIN_SOFT_IP,
    /** @EQDMA_WIN_SOFT_IP - Soft IP  */
    EQDMA_WIN_SOFT_IP,
    /** @QDMA_WIN_VERSAL_NONE - Not VERSAL device  */
    QDMA_WIN_VERSAL_NONE
};

#define QDMA_DEVICE_SOFT                    QDMA_WIN_DEVICE_SOFT
#define QDMA_DEVICE_VERSAL                  QDMA_WIN_DEVICE_VERSAL
//#define EQDMA_DEVICE_SOFT   			    EQDMA_WIN_DEVICE_SOFT
#define QDMA_DEVICE_NONE                    QDMA_WIN_DEVICE_NONE

#define QDMA_VERSAL_HARD_IP         QDMA_WIN_VERSAL_HARD_IP
#define QDMA_VERSAL_SOFT_IP         QDMA_WIN_VERSAL_SOFT_IP
#define QDMA_SOFT_IP                QDMA_WIN_SOFT_IP
#define EQDMA_SOFT_IP               EQDMA_WIN_SOFT_IP
#define QDMA_VERSAL_NONE            QDMA_WIN_VERSAL_NONE


struct qdma_dev_attributes {
    unsigned int num_pfs;
    unsigned int num_qs;
    unsigned int flr_present;
    unsigned int st_en;
    unsigned int mm_en;
    unsigned int mm_cmpl_en;
    unsigned int mailbox_en;
    unsigned int mm_channel_max;

    unsigned int sw_desc_64b;
    unsigned int cmpt_ovf_chk_dis;
    unsigned int cmpt_desc_64b;
    unsigned int cmpt_trig_count_timer;

    unsigned int device_type;
    unsigned int ip_type;
};

namespace qdma {


/* ==================== forward declarations ===================================== */
class instance;

/* ==================== declarations ============================================= */
class device {
public:

    struct info {
        //pci_id id;
        int dma_bar_idx = 0;
        int user_bar_idx = 0;
        int max_num_queues = 0;
        int qbase_start = 0;
        qdma_dev_attributes device_cap;
    };

    pcie_bar* user_bar = nullptr;
    pcie_bar* bypass_bar = nullptr;
    pcie_bar* dma_bar = nullptr;

    const unsigned max_num_queues_vf = 64;
    const unsigned max_num_queues = 0;
    const unsigned qbase_start = 0;
    qdma_dev_attributes dev_cap;

    uint32_t dev_id = 0;

    device::device(instance& drv, const info& details, uint32_t devid, std::string path)
        : max_num_queues(details.max_num_queues), qbase_start(details.qbase_start), dev_id(devid), dev_path(path.c_str()), dev_cap(details.device_cap), UserBar(path + "\\user"),
        BypassBar(path + "\\bypass"), ControlBar(path + "\\control")
    {
        user_bar = &UserBar;
        bypass_bar = &BypassBar;
        dma_bar = &ControlBar;
    }

private:
    std::string dev_path;
    pcie_bar UserBar;
    pcie_bar BypassBar;
    pcie_bar ControlBar;
};

} // namespace qdma

#endif /* QDMA_TEST_SRC_QDMA_DEVICE_HPP_ */
