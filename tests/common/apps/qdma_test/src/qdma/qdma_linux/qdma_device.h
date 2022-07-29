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

#include <xlnx_pci.h>

enum qdma_linux_device_type {
	/** @QDMA_DEVICE_SOFT - UltraScale+ IP's  */
	QDMA_LINUX_DEVICE_SOFT,
	/** @QDMA_LINUX_DEVICE_VERSAL_CPM4 -VERSAL CPM4 IP  */
	QDMA_LINUX_DEVICE_VERSAL_CPM4,
	/** @QDMA_LINUX_DEVICE_VERSAL_CPM5 -VERSAL CPM5 IP  */
	QDMA_LINUX_DEVICE_VERSAL_CPM5,
	/** @QDMA_DEVICE_NONE - Not a valid device  */
	QDMA_LINUX_DEVICE_NONE
};

enum qdma_linux_ip_type {
	/** @QDMA_LINUX_VERSAL_HARD_IP - Hard IP  */
	QDMA_LINUX_VERSAL_HARD_IP,
	/** @QDMA_LINUX_VERSAL_SOFT_IP - Soft IP  */
	QDMA_LINUX_VERSAL_SOFT_IP,
	/** @QDMA_LINUX_SOFT_IP - Hard IP  */
	QDMA_LINUX_SOFT_IP,
	/** @EQDMA_LINUX_SOFT_IP - Soft IP  */
	EQDMA_LINUX_SOFT_IP,
	/** @QDMA_VERSAL_NONE - Not versal device  */
	QDMA_LINUX_NONE_IP
};

#define  QDMA_DEVICE_SOFT           	QDMA_LINUX_DEVICE_SOFT
#define  QDMA_DEVICE_VERSAL_CPM4    	QDMA_LINUX_DEVICE_VERSAL_CPM4
#define  QDMA_DEVICE_VERSAL_CPM5    	QDMA_LINUX_DEVICE_VERSAL_CPM5

#define  QDMA_VERSAL_HARD_IP            QDMA_LINUX_VERSAL_HARD_IP
#define  QDMA_VERSAL_SOFT_IP            QDMA_LINUX_VERSAL_SOFT_IP
#define  QDMA_SOFT_IP                   QDMA_LINUX_SOFT_IP
#define  EQDMA_SOFT_IP                  EQDMA_LINUX_SOFT_IP


struct qdma_dev_attributes {
	/** @num_pfs - Num of PFs*/
	uint8_t num_pfs;
	/** @num_qs - Num of Queues */
	uint16_t num_qs;
	/** @flr_present - FLR resent or not? */
	uint8_t flr_present:1;
	/** @st_en - ST mode supported or not? */
	uint8_t st_en:1;
	/** @mm_en - MM mode supported or not? */
	uint8_t mm_en:1;
	/** @mm_cmpt_en - MM with Completions supported or not? */
	uint8_t mm_cmpt_en:1;
	/** @mailbox_en - Mailbox supported or not? */
	uint8_t mailbox_en:1;
	/** @mm_channel_max - Num of MM channels */
	uint8_t mm_channel_max;

	/** Below are the list of HW features which are populated by qdma_access based on RTL version */
	/** @qid2vec_ctx - To indicate support of qid2vec context */
	uint8_t qid2vec_ctx:1;
	/** @cmpt_ovf_chk_dis - To indicate support of overflow check disable in CMPT ring */
	uint8_t cmpt_ovf_chk_dis:1;
	/** @mailbox_intr - To indicate support of mailbox interrupt */
	uint8_t mailbox_intr:1;
	/** @sw_desc_64b - To indicate support of 64 bytes C2H/H2C descriptor format */
	uint8_t sw_desc_64b:1;
	/** @cmpt_desc_64b - To indicate support of 64 bytes CMPT descriptor format */
	uint8_t cmpt_desc_64b:1;
	/** @dynamic_bar - To indicate support of dynamic bar detection */
	uint8_t dynamic_bar:1;
	/** @legacy_intr - To indicate support of legacy interrupt */
	uint8_t legacy_intr:1;
	/** @cmpt_trig_count_timer - To indicate support of counter + timer
	 * trigger mode
	 */
	uint8_t cmpt_trig_count_timer:1;
	/** @qdma_linux_device_type - Device Type */
	enum qdma_linux_device_type device_type;
	/** @qdma_linux_ip_type - IP Type */
	enum qdma_linux_ip_type ip_type;
};

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
        pci_id id;
        int dma_bar_idx = 0;
        int user_bar_idx = 0;
        int max_num_queues = 0;
        int qbase_start = 0;
        qdma_dev_attributes dev_cap;
    };

    device(instance& drv, const info& details);

    pcie_bar* dma_bar = nullptr;
    pcie_bar* user_bar = nullptr;
    pcie_bar* bypass_bar = nullptr;

    pci_id m_id;
    const unsigned max_num_queues = 0;
    const unsigned qbase_start = 0;
    const unsigned max_num_queues_vf = 64; // TODO
    qdma_dev_attributes dev_cap;
	uint32_t dev_id = 0;

private:
    instance& m_drv;
    std::vector<pcie_bar> m_pcie_bars;
    bool is_vf = false;
};

} // namespace qdma

#endif /* QDMA_TEST_SRC_QDMA_DEVICE_HPP_ */
