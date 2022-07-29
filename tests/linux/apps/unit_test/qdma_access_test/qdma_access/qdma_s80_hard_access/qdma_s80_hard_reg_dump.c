/*
 * Copyright(c) 2019-2020 Xilinx, Inc. All rights reserved.
 */


#include "qdma_s80_hard_reg.h"
#include "qdma_reg_dump.h"

#ifdef ENABLE_WPP_TRACING
#include "qdma_s80_hard_reg_dump.tmh"
#endif


int qdma_s80_hard_cfg_blk_identifier_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,20]      0x%x\n",
	"CFG_BLK_IDENTIFIER", (reg_val &
	CFG_BLK_IDENTIFIER_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19,16]      0x%x\n",
	"CFG_BLK_IDENTIFIER_1", (reg_val &
	CFG_BLK_IDENTIFIER_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,8 ]      0x%x\n",
	"CFG_BLK_IDENTIFIER_RSVD_1", (reg_val &
	CFG_BLK_IDENTIFIER_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"CFG_BLK_IDENTIFIER_VERSION", (reg_val &
	CFG_BLK_IDENTIFIER_VERSION_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_busdev_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"CFG_BLK_BUSDEV_BDF", (reg_val &
	CFG_BLK_BUSDEV_BDF_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_pcie_max_pld_size_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2 ,0 ]      0x%x\n",
	"CFG_BLK_PCIE_MAX_PLD_SIZE", (reg_val &
	CFG_BLK_PCIE_MAX_PLD_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_pcie_max_read_req_size_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2 ,0 ]      0x%x\n",
	"CFG_BLK_PCIE_MAX_READ_REQ_SIZE", (reg_val &
	CFG_BLK_PCIE_MAX_READ_REQ_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_system_id_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"CFG_BLK_SYSTEM_ID", (reg_val &
	CFG_BLK_SYSTEM_ID_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_msi_enable_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17   ]      0x%x\n",
	"CFG_BLK_MSI_ENABLE_3", (reg_val &
	CFG_BLK_MSI_ENABLE_3_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"CFG_BLK_MSI_ENABLE_MSIX3", (reg_val &
	CFG_BLK_MSI_ENABLE_MSIX3_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [13   ]      0x%x\n",
	"CFG_BLK_MSI_ENABLE_2", (reg_val &
	CFG_BLK_MSI_ENABLE_2_MASK) >> 13);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [12   ]      0x%x\n",
	"CFG_BLK_MSI_ENABLE_MSIX2", (reg_val &
	CFG_BLK_MSI_ENABLE_MSIX2_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9    ]      0x%x\n",
	"CFG_BLK_MSI_ENABLE_1", (reg_val &
	CFG_BLK_MSI_ENABLE_1_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8    ]      0x%x\n",
	"CFG_BLK_MSI_ENABLE_MSIX1", (reg_val &
	CFG_BLK_MSI_ENABLE_MSIX1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"CFG_BLK_MSI_ENABLE_0", (reg_val &
	CFG_BLK_MSI_ENABLE_0_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"CFG_BLK_MSI_ENABLE_MSIX0", (reg_val &
	CFG_BLK_MSI_ENABLE_MSIX0_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_pcie_data_width_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2 ,0 ]      0x%x\n",
	"CFG_PCIE_DATA_WIDTH_DATAPATH", (reg_val &
	CFG_PCIE_DATA_WIDTH_DATAPATH_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_pcie_ctl_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"CFG_PCIE_CTL_RRQ_DISABLE", (reg_val &
	CFG_PCIE_CTL_RRQ_DISABLE_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"CFG_PCIE_CTL_RELAXED_ORDERING", (reg_val &
	CFG_PCIE_CTL_RELAXED_ORDERING_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_axi_user_max_pld_size_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6 ,4 ]      0x%x\n",
	"CFG_AXI_USER_MAX_PLD_SIZE_ISSUED", (reg_val &
	CFG_AXI_USER_MAX_PLD_SIZE_ISSUED_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2 ,0 ]      0x%x\n",
	"CFG_AXI_USER_MAX_PLD_SIZE_PROG", (reg_val &
	CFG_AXI_USER_MAX_PLD_SIZE_PROG_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_axi_user_max_read_req_size_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6 ,4 ]      0x%x\n",
	"CFG_AXI_USER_MAX_READ_REQ_SIZE_USISSUED", (reg_val &
	CFG_AXI_USER_MAX_READ_REQ_SIZE_USISSUED_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2 ,0 ]      0x%x\n",
	"CFG_AXI_USER_MAX_READ_REQ_SIZE_USPROG", (reg_val &
	CFG_AXI_USER_MAX_READ_REQ_SIZE_USPROG_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_misc_ctl_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19,8 ]      0x%x\n",
	"CFG_BLK_MISC_CTL_NUM_TAG", (reg_val &
	CFG_BLK_MISC_CTL_NUM_TAG_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4 ,0 ]      0x%x\n",
	"CFG_BLK_MISC_CTL_RQ_METERING_MULTIPLIER", (reg_val &
	CFG_BLK_MISC_CTL_RQ_METERING_MULTIPLIER_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_scratch_0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"CFG_BLK_SCRATCH_0", (reg_val &
	CFG_BLK_SCRATCH_0_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_scratch_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"CFG_BLK_SCRATCH_1", (reg_val &
	CFG_BLK_SCRATCH_1_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_scratch_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"CFG_BLK_SCRATCH_2", (reg_val &
	CFG_BLK_SCRATCH_2_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_scratch_3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"CFG_BLK_SCRATCH_3", (reg_val &
	CFG_BLK_SCRATCH_3_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_scratch_4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"CFG_BLK_SCRATCH_4", (reg_val &
	CFG_BLK_SCRATCH_4_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_scratch_5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"CFG_BLK_SCRATCH_5", (reg_val &
	CFG_BLK_SCRATCH_5_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_scratch_6_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"CFG_BLK_SCRATCH_6", (reg_val &
	CFG_BLK_SCRATCH_6_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_cfg_blk_scratch_7_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"CFG_BLK_SCRATCH_7", (reg_val &
	CFG_BLK_SCRATCH_7_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ram_sbe_msk_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"RAM_SBE", (reg_val &
	RAM_SBE_MSK_A_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ram_sbe_sts_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"RAM_SBE_STS_A_RSVD_1", (reg_val &
	RAM_SBE_STS_A_RSVD_1_MASK) >> 31);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [30   ]      0x%x\n",
	"RAM_SBE_STS_A_PFCH_LL_R", (reg_val &
	RAM_SBE_STS_A_PFCH_LL_RAM_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29   ]      0x%x\n",
	"RAM_SBE_STS_A_WRB_CTXT_R", (reg_val &
	RAM_SBE_STS_A_WRB_CTXT_RAM_MASK) >> 29);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [28   ]      0x%x\n",
	"RAM_SBE_STS_A_PFCH_CTXT_R", (reg_val &
	RAM_SBE_STS_A_PFCH_CTXT_RAM_MASK) >> 28);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [27   ]      0x%x\n",
	"RAM_SBE_STS_A_DESC_REQ_FIFO_R", (reg_val &
	RAM_SBE_STS_A_DESC_REQ_FIFO_RAM_MASK) >> 27);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [26   ]      0x%x\n",
	"RAM_SBE_STS_A_INT_CTXT_R", (reg_val &
	RAM_SBE_STS_A_INT_CTXT_RAM_MASK) >> 26);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [25   ]      0x%x\n",
	"RAM_SBE_STS_A_INT_QID2VEC_R", (reg_val &
	RAM_SBE_STS_A_INT_QID2VEC_RAM_MASK) >> 25);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [24   ]      0x%x\n",
	"RAM_SBE_STS_A_WRB_COAL_DATA_R", (reg_val &
	RAM_SBE_STS_A_WRB_COAL_DATA_RAM_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23   ]      0x%x\n",
	"RAM_SBE_STS_A_TUSER_FIFO_R", (reg_val &
	RAM_SBE_STS_A_TUSER_FIFO_RAM_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22   ]      0x%x\n",
	"RAM_SBE_STS_A_QID_FIFO_R", (reg_val &
	RAM_SBE_STS_A_QID_FIFO_RAM_MASK) >> 22);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [21   ]      0x%x\n",
	"RAM_SBE_STS_A_PLD_FIFO_R", (reg_val &
	RAM_SBE_STS_A_PLD_FIFO_RAM_MASK) >> 21);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [20   ]      0x%x\n",
	"RAM_SBE_STS_A_TIMER_FIFO_R", (reg_val &
	RAM_SBE_STS_A_TIMER_FIFO_RAM_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19   ]      0x%x\n",
	"RAM_SBE_STS_A_PASID_CTXT_R", (reg_val &
	RAM_SBE_STS_A_PASID_CTXT_RAM_MASK) >> 19);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [18   ]      0x%x\n",
	"RAM_SBE_STS_A_DSC_CPLD", (reg_val &
	RAM_SBE_STS_A_DSC_CPLD_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17   ]      0x%x\n",
	"RAM_SBE_STS_A_DSC_CPLI", (reg_val &
	RAM_SBE_STS_A_DSC_CPLI_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"RAM_SBE_STS_A_DSC_SW_CTXT", (reg_val &
	RAM_SBE_STS_A_DSC_SW_CTXT_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15   ]      0x%x\n",
	"RAM_SBE_STS_A_DSC_CRD_RCV", (reg_val &
	RAM_SBE_STS_A_DSC_CRD_RCV_MASK) >> 15);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [14   ]      0x%x\n",
	"RAM_SBE_STS_A_DSC_HW_CTXT", (reg_val &
	RAM_SBE_STS_A_DSC_HW_CTXT_MASK) >> 14);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [13   ]      0x%x\n",
	"RAM_SBE_STS_A_FUNC_MAP", (reg_val &
	RAM_SBE_STS_A_FUNC_MAP_MASK) >> 13);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [12   ]      0x%x\n",
	"RAM_SBE_STS_A_C2H_WR_BRG_DAT", (reg_val &
	RAM_SBE_STS_A_C2H_WR_BRG_DAT_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11   ]      0x%x\n",
	"RAM_SBE_STS_A_C2H_RD_BRG_DAT", (reg_val &
	RAM_SBE_STS_A_C2H_RD_BRG_DAT_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10   ]      0x%x\n",
	"RAM_SBE_STS_A_H2C_WR_BRG_DAT", (reg_val &
	RAM_SBE_STS_A_H2C_WR_BRG_DAT_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9    ]      0x%x\n",
	"RAM_SBE_STS_A_H2C_RD_BRG_DAT", (reg_val &
	RAM_SBE_STS_A_H2C_RD_BRG_DAT_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8 ,5 ]      0x%x\n",
	"RAM_SBE_STS_A_RSVD_2", (reg_val &
	RAM_SBE_STS_A_RSVD_2_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4    ]      0x%x\n",
	"RAM_SBE_STS_A_MI_C2H0_DAT", (reg_val &
	RAM_SBE_STS_A_MI_C2H0_DAT_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3 ,1 ]      0x%x\n",
	"RAM_SBE_STS_A_RSVD_3", (reg_val &
	RAM_SBE_STS_A_RSVD_3_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"RAM_SBE_STS_A_MI_H2C0_DAT", (reg_val &
	RAM_SBE_STS_A_MI_H2C0_DAT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ram_dbe_msk_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"RAM_DBE", (reg_val &
	RAM_DBE_MSK_A_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ram_dbe_sts_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"RAM_DBE_STS_A_RSVD_1", (reg_val &
	RAM_DBE_STS_A_RSVD_1_MASK) >> 31);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [30   ]      0x%x\n",
	"RAM_DBE_STS_A_PFCH_LL_R", (reg_val &
	RAM_DBE_STS_A_PFCH_LL_RAM_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29   ]      0x%x\n",
	"RAM_DBE_STS_A_WRB_CTXT_R", (reg_val &
	RAM_DBE_STS_A_WRB_CTXT_RAM_MASK) >> 29);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [28   ]      0x%x\n",
	"RAM_DBE_STS_A_PFCH_CTXT_R", (reg_val &
	RAM_DBE_STS_A_PFCH_CTXT_RAM_MASK) >> 28);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [27   ]      0x%x\n",
	"RAM_DBE_STS_A_DESC_REQ_FIFO_R", (reg_val &
	RAM_DBE_STS_A_DESC_REQ_FIFO_RAM_MASK) >> 27);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [26   ]      0x%x\n",
	"RAM_DBE_STS_A_INT_CTXT_R", (reg_val &
	RAM_DBE_STS_A_INT_CTXT_RAM_MASK) >> 26);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [25   ]      0x%x\n",
	"RAM_DBE_STS_A_INT_QID2VEC_R", (reg_val &
	RAM_DBE_STS_A_INT_QID2VEC_RAM_MASK) >> 25);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [24   ]      0x%x\n",
	"RAM_DBE_STS_A_WRB_COAL_DATA_R", (reg_val &
	RAM_DBE_STS_A_WRB_COAL_DATA_RAM_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23   ]      0x%x\n",
	"RAM_DBE_STS_A_TUSER_FIFO_R", (reg_val &
	RAM_DBE_STS_A_TUSER_FIFO_RAM_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22   ]      0x%x\n",
	"RAM_DBE_STS_A_QID_FIFO_R", (reg_val &
	RAM_DBE_STS_A_QID_FIFO_RAM_MASK) >> 22);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [21   ]      0x%x\n",
	"RAM_DBE_STS_A_PLD_FIFO_R", (reg_val &
	RAM_DBE_STS_A_PLD_FIFO_RAM_MASK) >> 21);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [20   ]      0x%x\n",
	"RAM_DBE_STS_A_TIMER_FIFO_R", (reg_val &
	RAM_DBE_STS_A_TIMER_FIFO_RAM_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19   ]      0x%x\n",
	"RAM_DBE_STS_A_PASID_CTXT_R", (reg_val &
	RAM_DBE_STS_A_PASID_CTXT_RAM_MASK) >> 19);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [18   ]      0x%x\n",
	"RAM_DBE_STS_A_DSC_CPLD", (reg_val &
	RAM_DBE_STS_A_DSC_CPLD_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17   ]      0x%x\n",
	"RAM_DBE_STS_A_DSC_CPLI", (reg_val &
	RAM_DBE_STS_A_DSC_CPLI_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"RAM_DBE_STS_A_DSC_SW_CTXT", (reg_val &
	RAM_DBE_STS_A_DSC_SW_CTXT_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15   ]      0x%x\n",
	"RAM_DBE_STS_A_DSC_CRD_RCV", (reg_val &
	RAM_DBE_STS_A_DSC_CRD_RCV_MASK) >> 15);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [14   ]      0x%x\n",
	"RAM_DBE_STS_A_DSC_HW_CTXT", (reg_val &
	RAM_DBE_STS_A_DSC_HW_CTXT_MASK) >> 14);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [13   ]      0x%x\n",
	"RAM_DBE_STS_A_FUNC_MAP", (reg_val &
	RAM_DBE_STS_A_FUNC_MAP_MASK) >> 13);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [12   ]      0x%x\n",
	"RAM_DBE_STS_A_C2H_WR_BRG_DAT", (reg_val &
	RAM_DBE_STS_A_C2H_WR_BRG_DAT_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11   ]      0x%x\n",
	"RAM_DBE_STS_A_C2H_RD_BRG_DAT", (reg_val &
	RAM_DBE_STS_A_C2H_RD_BRG_DAT_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10   ]      0x%x\n",
	"RAM_DBE_STS_A_H2C_WR_BRG_DAT", (reg_val &
	RAM_DBE_STS_A_H2C_WR_BRG_DAT_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9    ]      0x%x\n",
	"RAM_DBE_STS_A_H2C_RD_BRG_DAT", (reg_val &
	RAM_DBE_STS_A_H2C_RD_BRG_DAT_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8 ,5 ]      0x%x\n",
	"RAM_DBE_STS_A_RSVD_2", (reg_val &
	RAM_DBE_STS_A_RSVD_2_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4    ]      0x%x\n",
	"RAM_DBE_STS_A_MI_C2H0_DAT", (reg_val &
	RAM_DBE_STS_A_MI_C2H0_DAT_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3 ,1 ]      0x%x\n",
	"RAM_DBE_STS_A_RSVD_3", (reg_val &
	RAM_DBE_STS_A_RSVD_3_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"RAM_DBE_STS_A_MI_H2C0_DAT", (reg_val &
	RAM_DBE_STS_A_MI_H2C0_DAT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_identifier_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"GLBL2_IDENTIFIER", (reg_val &
	GLBL2_IDENTIFIER_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"GLBL2_IDENTIFIER_VERSION", (reg_val &
	GLBL2_IDENTIFIER_VERSION_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_pf_barlite_int_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,18]      0x%x\n",
	"GLBL2_PF_BARLITE_INT_PF3_BAR_MAP", (reg_val &
	GLBL2_PF_BARLITE_INT_PF3_BAR_MAP_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,12]      0x%x\n",
	"GLBL2_PF_BARLITE_INT_PF2_BAR_MAP", (reg_val &
	GLBL2_PF_BARLITE_INT_PF2_BAR_MAP_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,6 ]      0x%x\n",
	"GLBL2_PF_BARLITE_INT_PF1_BAR_MAP", (reg_val &
	GLBL2_PF_BARLITE_INT_PF1_BAR_MAP_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5 ,0 ]      0x%x\n",
	"GLBL2_PF_BARLITE_INT_PF0_BAR_MAP", (reg_val &
	GLBL2_PF_BARLITE_INT_PF0_BAR_MAP_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_pf_vf_barlite_int_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,18]      0x%x\n",
	"GLBL2_PF_VF_BARLITE_INT_PF3_MAP", (reg_val &
	GLBL2_PF_VF_BARLITE_INT_PF3_MAP_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,12]      0x%x\n",
	"GLBL2_PF_VF_BARLITE_INT_PF2_MAP", (reg_val &
	GLBL2_PF_VF_BARLITE_INT_PF2_MAP_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,6 ]      0x%x\n",
	"GLBL2_PF_VF_BARLITE_INT_PF1_MAP", (reg_val &
	GLBL2_PF_VF_BARLITE_INT_PF1_MAP_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5 ,0 ]      0x%x\n",
	"GLBL2_PF_VF_BARLITE_INT_PF0_MAP", (reg_val &
	GLBL2_PF_VF_BARLITE_INT_PF0_MAP_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_pf_barlite_ext_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,18]      0x%x\n",
	"GLBL2_PF_BARLITE_EXT_PF3_BAR_MAP", (reg_val &
	GLBL2_PF_BARLITE_EXT_PF3_BAR_MAP_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,12]      0x%x\n",
	"GLBL2_PF_BARLITE_EXT_PF2_BAR_MAP", (reg_val &
	GLBL2_PF_BARLITE_EXT_PF2_BAR_MAP_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,6 ]      0x%x\n",
	"GLBL2_PF_BARLITE_EXT_PF1_BAR_MAP", (reg_val &
	GLBL2_PF_BARLITE_EXT_PF1_BAR_MAP_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5 ,0 ]      0x%x\n",
	"GLBL2_PF_BARLITE_EXT_PF0_BAR_MAP", (reg_val &
	GLBL2_PF_BARLITE_EXT_PF0_BAR_MAP_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_pf_vf_barlite_ext_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,18]      0x%x\n",
	"GLBL2_PF_VF_BARLITE_EXT_PF3_MAP", (reg_val &
	GLBL2_PF_VF_BARLITE_EXT_PF3_MAP_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,12]      0x%x\n",
	"GLBL2_PF_VF_BARLITE_EXT_PF2_MAP", (reg_val &
	GLBL2_PF_VF_BARLITE_EXT_PF2_MAP_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,6 ]      0x%x\n",
	"GLBL2_PF_VF_BARLITE_EXT_PF1_MAP", (reg_val &
	GLBL2_PF_VF_BARLITE_EXT_PF1_MAP_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5 ,0 ]      0x%x\n",
	"GLBL2_PF_VF_BARLITE_EXT_PF0_MAP", (reg_val &
	GLBL2_PF_VF_BARLITE_EXT_PF0_MAP_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_channel_inst_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"GLBL2_CHANNEL_INST_RSVD_1", (reg_val &
	GLBL2_CHANNEL_INST_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17   ]      0x%x\n",
	"GLBL2_CHANNEL_INST_C2H_ST", (reg_val &
	GLBL2_CHANNEL_INST_C2H_ST_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"GLBL2_CHANNEL_INST_H2C_ST", (reg_val &
	GLBL2_CHANNEL_INST_H2C_ST_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,9 ]      0x%x\n",
	"GLBL2_CHANNEL_INST_RSVD_2", (reg_val &
	GLBL2_CHANNEL_INST_RSVD_2_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8    ]      0x%x\n",
	"GLBL2_CHANNEL_INST_C2H_ENG", (reg_val &
	GLBL2_CHANNEL_INST_C2H_ENG_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,1 ]      0x%x\n",
	"GLBL2_CHANNEL_INST_RSVD_3", (reg_val &
	GLBL2_CHANNEL_INST_RSVD_3_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"GLBL2_CHANNEL_INST_H2C_ENG", (reg_val &
	GLBL2_CHANNEL_INST_H2C_ENG_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_channel_mdma_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"GLBL2_CHANNEL_MDMA_RSVD_1", (reg_val &
	GLBL2_CHANNEL_MDMA_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17   ]      0x%x\n",
	"GLBL2_CHANNEL_MDMA_C2H_ST", (reg_val &
	GLBL2_CHANNEL_MDMA_C2H_ST_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"GLBL2_CHANNEL_MDMA_H2C_ST", (reg_val &
	GLBL2_CHANNEL_MDMA_H2C_ST_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,9 ]      0x%x\n",
	"GLBL2_CHANNEL_MDMA_RSVD_2", (reg_val &
	GLBL2_CHANNEL_MDMA_RSVD_2_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8    ]      0x%x\n",
	"GLBL2_CHANNEL_MDMA_C2H_ENG", (reg_val &
	GLBL2_CHANNEL_MDMA_C2H_ENG_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,1 ]      0x%x\n",
	"GLBL2_CHANNEL_MDMA_RSVD_3", (reg_val &
	GLBL2_CHANNEL_MDMA_RSVD_3_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"GLBL2_CHANNEL_MDMA_H2C_ENG", (reg_val &
	GLBL2_CHANNEL_MDMA_H2C_ENG_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_channel_strm_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"GLBL2_CHANNEL_STRM_RSVD_1", (reg_val &
	GLBL2_CHANNEL_STRM_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17   ]      0x%x\n",
	"GLBL2_CHANNEL_STRM_C2H_ST", (reg_val &
	GLBL2_CHANNEL_STRM_C2H_ST_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"GLBL2_CHANNEL_STRM_H2C_ST", (reg_val &
	GLBL2_CHANNEL_STRM_H2C_ST_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,9 ]      0x%x\n",
	"GLBL2_CHANNEL_STRM_RSVD_2", (reg_val &
	GLBL2_CHANNEL_STRM_RSVD_2_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8    ]      0x%x\n",
	"GLBL2_CHANNEL_STRM_C2H_ENG", (reg_val &
	GLBL2_CHANNEL_STRM_C2H_ENG_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,1 ]      0x%x\n",
	"GLBL2_CHANNEL_STRM_RSVD_3", (reg_val &
	GLBL2_CHANNEL_STRM_RSVD_3_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"GLBL2_CHANNEL_STRM_H2C_ENG", (reg_val &
	GLBL2_CHANNEL_STRM_H2C_ENG_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_channel_cap_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,12]      0x%x\n",
	"GLBL2_CHANNEL_CAP_RSVD_1", (reg_val &
	GLBL2_CHANNEL_CAP_RSVD_1_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,0 ]      0x%x\n",
	"GLBL2_CHANNEL_CAP_MULTIQ_MAX", (reg_val &
	GLBL2_CHANNEL_CAP_MULTIQ_MAX_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_channel_pasid_cap_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL2_CHANNEL_PASID_CAP_RSVD_1", (reg_val &
	GLBL2_CHANNEL_PASID_CAP_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,4 ]      0x%x\n",
	"GLBL2_CHANNEL_PASID_CAP_BRIDGEOFFSET", (reg_val &
	GLBL2_CHANNEL_PASID_CAP_BRIDGEOFFSET_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3 ,2 ]      0x%x\n",
	"GLBL2_CHANNEL_PASID_CAP_RSVD_2", (reg_val &
	GLBL2_CHANNEL_PASID_CAP_RSVD_2_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"GLBL2_CHANNEL_PASID_CAP_BRIDGEEN", (reg_val &
	GLBL2_CHANNEL_PASID_CAP_BRIDGEEN_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"GLBL2_CHANNEL_PASID_CAP_DMAEN", (reg_val &
	GLBL2_CHANNEL_PASID_CAP_DMAEN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_channel_func_ret_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"GLBL2_CHANNEL_FUNC_RET_RSVD_1", (reg_val &
	GLBL2_CHANNEL_FUNC_RET_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"GLBL2_CHANNEL_FUNC_RET_FUNC", (reg_val &
	GLBL2_CHANNEL_FUNC_RET_FUNC_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_system_id_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL2_SYSTEM_ID_RSVD_1", (reg_val &
	GLBL2_SYSTEM_ID_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL2_SYSTEM_ID", (reg_val &
	GLBL2_SYSTEM_ID_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_misc_cap_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"GLBL2_MISC_CAP_RSVD_1", (reg_val &
	GLBL2_MISC_CAP_RSVD_1_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_dbg_pcie_rq0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,20]      0x%x\n",
	"GLBL2_PCIE_RQ0_NPH_AVL", (reg_val &
	GLBL2_PCIE_RQ0_NPH_AVL_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19,10]      0x%x\n",
	"GLBL2_PCIE_RQ0_RCB_AVL", (reg_val &
	GLBL2_PCIE_RQ0_RCB_AVL_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,4 ]      0x%x\n",
	"GLBL2_PCIE_RQ0_SLV_RD_CRED", (reg_val &
	GLBL2_PCIE_RQ0_SLV_RD_CREDS_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3 ,2 ]      0x%x\n",
	"GLBL2_PCIE_RQ0_TAG_EP", (reg_val &
	GLBL2_PCIE_RQ0_TAG_EP_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1 ,0 ]      0x%x\n",
	"GLBL2_PCIE_RQ0_TAG_FL", (reg_val &
	GLBL2_PCIE_RQ0_TAG_FL_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_dbg_pcie_rq1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,17]      0x%x\n",
	"GLBL2_PCIE_RQ1_RSVD_1", (reg_val &
	GLBL2_PCIE_RQ1_RSVD_1_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"GLBL2_PCIE_RQ1_WTLP_REQ", (reg_val &
	GLBL2_PCIE_RQ1_WTLP_REQ_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15   ]      0x%x\n",
	"GLBL2_PCIE_RQ1_WTLP_HEADER_FIFO_FL", (reg_val &
	GLBL2_PCIE_RQ1_WTLP_HEADER_FIFO_FL_MASK) >> 15);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [14   ]      0x%x\n",
	"GLBL2_PCIE_RQ1_WTLP_HEADER_FIFO_EP", (reg_val &
	GLBL2_PCIE_RQ1_WTLP_HEADER_FIFO_EP_MASK) >> 14);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [13   ]      0x%x\n",
	"GLBL2_PCIE_RQ1_RQ_FIFO_EP", (reg_val &
	GLBL2_PCIE_RQ1_RQ_FIFO_EP_MASK) >> 13);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [12   ]      0x%x\n",
	"GLBL2_PCIE_RQ1_RQ_FIFO_FL", (reg_val &
	GLBL2_PCIE_RQ1_RQ_FIFO_FL_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,9 ]      0x%x\n",
	"GLBL2_PCIE_RQ1_TLP", (reg_val &
	GLBL2_PCIE_RQ1_TLPSM_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8 ,6 ]      0x%x\n",
	"GLBL2_PCIE_RQ1_TLPSM512", (reg_val &
	GLBL2_PCIE_RQ1_TLPSM512_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5    ]      0x%x\n",
	"GLBL2_PCIE_RQ1_RREQ0_RCB_O", (reg_val &
	GLBL2_PCIE_RQ1_RREQ0_RCB_OK_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4    ]      0x%x\n",
	"GLBL2_PCIE_RQ1_RREQ0_SLV", (reg_val &
	GLBL2_PCIE_RQ1_RREQ0_SLV_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3    ]      0x%x\n",
	"GLBL2_PCIE_RQ1_RREQ0_VLD", (reg_val &
	GLBL2_PCIE_RQ1_RREQ0_VLD_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"GLBL2_PCIE_RQ1_RREQ1_RCB_O", (reg_val &
	GLBL2_PCIE_RQ1_RREQ1_RCB_OK_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"GLBL2_PCIE_RQ1_RREQ1_SLV", (reg_val &
	GLBL2_PCIE_RQ1_RREQ1_SLV_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"GLBL2_PCIE_RQ1_RREQ1_VLD", (reg_val &
	GLBL2_PCIE_RQ1_RREQ1_VLD_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_dbg_aximm_wr0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,27]      0x%x\n",
	"GLBL2_AXIMM_WR0_RSVD_1", (reg_val &
	GLBL2_AXIMM_WR0_RSVD_1_MASK) >> 27);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [26   ]      0x%x\n",
	"GLBL2_AXIMM_WR0_WR_REQ", (reg_val &
	GLBL2_AXIMM_WR0_WR_REQ_MASK) >> 26);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [25,23]      0x%x\n",
	"GLBL2_AXIMM_WR0_WR_CHN", (reg_val &
	GLBL2_AXIMM_WR0_WR_CHN_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22   ]      0x%x\n",
	"GLBL2_AXIMM_WR0_WTLP_DATA_FIFO_EP", (reg_val &
	GLBL2_AXIMM_WR0_WTLP_DATA_FIFO_EP_MASK) >> 22);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [21   ]      0x%x\n",
	"GLBL2_AXIMM_WR0_WPL_FIFO_EP", (reg_val &
	GLBL2_AXIMM_WR0_WPL_FIFO_EP_MASK) >> 21);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [20,18]      0x%x\n",
	"GLBL2_AXIMM_WR0_BRSP_CLAIM_CHN", (reg_val &
	GLBL2_AXIMM_WR0_BRSP_CLAIM_CHN_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,12]      0x%x\n",
	"GLBL2_AXIMM_WR0_WRREQ_CNT", (reg_val &
	GLBL2_AXIMM_WR0_WRREQ_CNT_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,9 ]      0x%x\n",
	"GLBL2_AXIMM_WR0_BID", (reg_val &
	GLBL2_AXIMM_WR0_BID_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8    ]      0x%x\n",
	"GLBL2_AXIMM_WR0_BVALID", (reg_val &
	GLBL2_AXIMM_WR0_BVALID_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7    ]      0x%x\n",
	"GLBL2_AXIMM_WR0_BREADY", (reg_val &
	GLBL2_AXIMM_WR0_BREADY_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6    ]      0x%x\n",
	"GLBL2_AXIMM_WR0_WVALID", (reg_val &
	GLBL2_AXIMM_WR0_WVALID_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5    ]      0x%x\n",
	"GLBL2_AXIMM_WR0_WREADY", (reg_val &
	GLBL2_AXIMM_WR0_WREADY_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4 ,2 ]      0x%x\n",
	"GLBL2_AXIMM_WR0_AWID", (reg_val &
	GLBL2_AXIMM_WR0_AWID_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"GLBL2_AXIMM_WR0_AWVALID", (reg_val &
	GLBL2_AXIMM_WR0_AWVALID_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"GLBL2_AXIMM_WR0_AWREADY", (reg_val &
	GLBL2_AXIMM_WR0_AWREADY_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_dbg_aximm_wr1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,30]      0x%x\n",
	"GLBL2_AXIMM_WR1_RSVD_1", (reg_val &
	GLBL2_AXIMM_WR1_RSVD_1_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29,24]      0x%x\n",
	"GLBL2_AXIMM_WR1_BRSP_CNT4", (reg_val &
	GLBL2_AXIMM_WR1_BRSP_CNT4_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,18]      0x%x\n",
	"GLBL2_AXIMM_WR1_BRSP_CNT3", (reg_val &
	GLBL2_AXIMM_WR1_BRSP_CNT3_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,12]      0x%x\n",
	"GLBL2_AXIMM_WR1_BRSP_CNT2", (reg_val &
	GLBL2_AXIMM_WR1_BRSP_CNT2_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,6 ]      0x%x\n",
	"GLBL2_AXIMM_WR1_BRSP_CNT1", (reg_val &
	GLBL2_AXIMM_WR1_BRSP_CNT1_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5 ,0 ]      0x%x\n",
	"GLBL2_AXIMM_WR1_BRSP_CNT0", (reg_val &
	GLBL2_AXIMM_WR1_BRSP_CNT0_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_dbg_aximm_rd0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"GLBL2_AXIMM_RD0_RSVD_1", (reg_val &
	GLBL2_AXIMM_RD0_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,17]      0x%x\n",
	"GLBL2_AXIMM_RD0_PND_CNT", (reg_val &
	GLBL2_AXIMM_RD0_PND_CNT_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16,14]      0x%x\n",
	"GLBL2_AXIMM_RD0_RD_CHNL", (reg_val &
	GLBL2_AXIMM_RD0_RD_CHNL_MASK) >> 14);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [13   ]      0x%x\n",
	"GLBL2_AXIMM_RD0_RD_REQ", (reg_val &
	GLBL2_AXIMM_RD0_RD_REQ_MASK) >> 13);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [12,10]      0x%x\n",
	"GLBL2_AXIMM_RD0_RRSP_CLAIM_CHNL", (reg_val &
	GLBL2_AXIMM_RD0_RRSP_CLAIM_CHNL_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,7 ]      0x%x\n",
	"GLBL2_AXIMM_RD0_RID", (reg_val &
	GLBL2_AXIMM_RD0_RID_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6    ]      0x%x\n",
	"GLBL2_AXIMM_RD0_RVALID", (reg_val &
	GLBL2_AXIMM_RD0_RVALID_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5    ]      0x%x\n",
	"GLBL2_AXIMM_RD0_RREADY", (reg_val &
	GLBL2_AXIMM_RD0_RREADY_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4 ,2 ]      0x%x\n",
	"GLBL2_AXIMM_RD0_ARID", (reg_val &
	GLBL2_AXIMM_RD0_ARID_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"GLBL2_AXIMM_RD0_ARVALID", (reg_val &
	GLBL2_AXIMM_RD0_ARVALID_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"GLBL2_AXIMM_RD0_ARREADY", (reg_val &
	GLBL2_AXIMM_RD0_ARREADY_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl2_dbg_aximm_rd1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,30]      0x%x\n",
	"GLBL2_AXIMM_RD1_RSVD_1", (reg_val &
	GLBL2_AXIMM_RD1_RSVD_1_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29,24]      0x%x\n",
	"GLBL2_AXIMM_RD1_RRSP_CNT4", (reg_val &
	GLBL2_AXIMM_RD1_RRSP_CNT4_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,18]      0x%x\n",
	"GLBL2_AXIMM_RD1_RRSP_CNT3", (reg_val &
	GLBL2_AXIMM_RD1_RRSP_CNT3_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,12]      0x%x\n",
	"GLBL2_AXIMM_RD1_RRSP_CNT2", (reg_val &
	GLBL2_AXIMM_RD1_RRSP_CNT2_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,6 ]      0x%x\n",
	"GLBL2_AXIMM_RD1_RRSP_CNT1", (reg_val &
	GLBL2_AXIMM_RD1_RRSP_CNT1_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5 ,0 ]      0x%x\n",
	"GLBL2_AXIMM_RD1_RRSP_CNT0", (reg_val &
	GLBL2_AXIMM_RD1_RRSP_CNT0_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_1_RSVD_1", (reg_val &
	GLBL_RNG_SZ_1_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_1_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_1_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_2_RSVD_1", (reg_val &
	GLBL_RNG_SZ_2_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_2_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_2_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_3_RSVD_1", (reg_val &
	GLBL_RNG_SZ_3_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_3_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_3_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_4_RSVD_1", (reg_val &
	GLBL_RNG_SZ_4_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_4_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_4_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_5_RSVD_1", (reg_val &
	GLBL_RNG_SZ_5_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_5_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_5_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_6_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_6_RSVD_1", (reg_val &
	GLBL_RNG_SZ_6_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_6_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_6_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_7_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_7_RSVD_1", (reg_val &
	GLBL_RNG_SZ_7_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_7_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_7_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_8_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_8_RSVD_1", (reg_val &
	GLBL_RNG_SZ_8_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_8_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_8_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_9_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_9_RSVD_1", (reg_val &
	GLBL_RNG_SZ_9_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_9_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_9_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_A_RSVD_1", (reg_val &
	GLBL_RNG_SZ_A_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_A_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_A_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_B_RSVD_1", (reg_val &
	GLBL_RNG_SZ_B_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_B_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_B_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_c_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_C_RSVD_1", (reg_val &
	GLBL_RNG_SZ_C_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_C_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_C_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_D_RSVD_1", (reg_val &
	GLBL_RNG_SZ_D_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_D_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_D_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_E_RSVD_1", (reg_val &
	GLBL_RNG_SZ_E_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_E_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_E_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_F_RSVD_1", (reg_val &
	GLBL_RNG_SZ_F_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_F_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_F_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_rng_sz_10_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_RNG_SZ_10_RSVD_1", (reg_val &
	GLBL_RNG_SZ_10_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_RNG_SZ_10_RING_SIZE", (reg_val &
	GLBL_RNG_SZ_10_RING_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_err_stat_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,12]      0x%x\n",
	"GLBL_ERR_STAT_RSVD_1", (reg_val &
	GLBL_ERR_STAT_RSVD_1_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11   ]      0x%x\n",
	"GLBL_ERR_STAT_ERR_H2C_ST", (reg_val &
	GLBL_ERR_STAT_ERR_H2C_ST_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10   ]      0x%x\n",
	"GLBL_ERR_STAT_ERR_BDG", (reg_val &
	GLBL_ERR_STAT_ERR_BDG_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9    ]      0x%x\n",
	"GLBL_ERR_STAT_IND_CTXT_CMD_ERR", (reg_val &
	GLBL_ERR_STAT_IND_CTXT_CMD_ERR_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8    ]      0x%x\n",
	"GLBL_ERR_STAT_ERR_C2H_ST", (reg_val &
	GLBL_ERR_STAT_ERR_C2H_ST_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7    ]      0x%x\n",
	"GLBL_ERR_STAT_ERR_C2H_MM_1", (reg_val &
	GLBL_ERR_STAT_ERR_C2H_MM_1_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6    ]      0x%x\n",
	"GLBL_ERR_STAT_ERR_C2H_MM_0", (reg_val &
	GLBL_ERR_STAT_ERR_C2H_MM_0_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5    ]      0x%x\n",
	"GLBL_ERR_STAT_ERR_H2C_MM_1", (reg_val &
	GLBL_ERR_STAT_ERR_H2C_MM_1_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4    ]      0x%x\n",
	"GLBL_ERR_STAT_ERR_H2C_MM_0", (reg_val &
	GLBL_ERR_STAT_ERR_H2C_MM_0_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3    ]      0x%x\n",
	"GLBL_ERR_STAT_ERR_TRQ", (reg_val &
	GLBL_ERR_STAT_ERR_TRQ_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"GLBL_ERR_STAT_ERR_DSC", (reg_val &
	GLBL_ERR_STAT_ERR_DSC_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"GLBL_ERR_STAT_ERR_RAM_DBE", (reg_val &
	GLBL_ERR_STAT_ERR_RAM_DBE_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"GLBL_ERR_STAT_ERR_RAM_SBE", (reg_val &
	GLBL_ERR_STAT_ERR_RAM_SBE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_err_mask_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,9 ]      0x%x\n",
	"GLBL_ERR_RSVD_1", (reg_val &
	GLBL_ERR_RSVD_1_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8 ,0 ]      0x%x\n",
	"GLBL_ERR", (reg_val &
	GLBL_ERR_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_dsc_cfg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,10]      0x%x\n",
	"GLBL_DSC_CFG_RSVD_1", (reg_val &
	GLBL_DSC_CFG_RSVD_1_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9    ]      0x%x\n",
	"GLBL_DSC_CFG_UNC_OVR_COR", (reg_val &
	GLBL_DSC_CFG_UNC_OVR_COR_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8    ]      0x%x\n",
	"GLBL_DSC_CFG_CTXT_FER_DI", (reg_val &
	GLBL_DSC_CFG_CTXT_FER_DIS_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,6 ]      0x%x\n",
	"GLBL_DSC_CFG_RSVD_2", (reg_val &
	GLBL_DSC_CFG_RSVD_2_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5 ,3 ]      0x%x\n",
	"GLBL_DSC_CFG_MAXFETCH", (reg_val &
	GLBL_DSC_CFG_MAXFETCH_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2 ,0 ]      0x%x\n",
	"GLBL_DSC_CFG_WB_ACC_INT", (reg_val &
	GLBL_DSC_CFG_WB_ACC_INT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_dsc_err_sts_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,25]      0x%x\n",
	"GLBL_DSC_ERR_STS_RSVD_1", (reg_val &
	GLBL_DSC_ERR_STS_RSVD_1_MASK) >> 25);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [24   ]      0x%x\n",
	"GLBL_DSC_ERR_STS_SBE", (reg_val &
	GLBL_DSC_ERR_STS_SBE_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23   ]      0x%x\n",
	"GLBL_DSC_ERR_STS_DBE", (reg_val &
	GLBL_DSC_ERR_STS_DBE_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22   ]      0x%x\n",
	"GLBL_DSC_ERR_STS_RQ_CANCEL", (reg_val &
	GLBL_DSC_ERR_STS_RQ_CANCEL_MASK) >> 22);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [21   ]      0x%x\n",
	"GLBL_DSC_ERR_STS_DSC", (reg_val &
	GLBL_DSC_ERR_STS_DSC_MASK) >> 21);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [20   ]      0x%x\n",
	"GLBL_DSC_ERR_STS_D", (reg_val &
	GLBL_DSC_ERR_STS_DMA_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19   ]      0x%x\n",
	"GLBL_DSC_ERR_STS_FLR_CANCEL", (reg_val &
	GLBL_DSC_ERR_STS_FLR_CANCEL_MASK) >> 19);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [18,17]      0x%x\n",
	"GLBL_DSC_ERR_STS_RSVD_2", (reg_val &
	GLBL_DSC_ERR_STS_RSVD_2_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"GLBL_DSC_ERR_STS_DAT_POISON", (reg_val &
	GLBL_DSC_ERR_STS_DAT_POISON_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9    ]      0x%x\n",
	"GLBL_DSC_ERR_STS_TIMEOUT", (reg_val &
	GLBL_DSC_ERR_STS_TIMEOUT_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5    ]      0x%x\n",
	"GLBL_DSC_ERR_STS_FLR", (reg_val &
	GLBL_DSC_ERR_STS_FLR_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4    ]      0x%x\n",
	"GLBL_DSC_ERR_STS_TAG", (reg_val &
	GLBL_DSC_ERR_STS_TAG_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3    ]      0x%x\n",
	"GLBL_DSC_ERR_STS_ADDR", (reg_val &
	GLBL_DSC_ERR_STS_ADDR_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"GLBL_DSC_ERR_STS_PAR", (reg_val &
	GLBL_DSC_ERR_STS_PARAM_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"GLBL_DSC_ERR_STS_UR_C", (reg_val &
	GLBL_DSC_ERR_STS_UR_CA_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"GLBL_DSC_ERR_STS_POISON", (reg_val &
	GLBL_DSC_ERR_STS_POISON_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_dsc_err_msk_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8 ,0 ]      0x%x\n",
	"GLBL_DSC_ERR", (reg_val &
	GLBL_DSC_ERR_MSK_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_dsc_err_log0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"GLBL_DSC_ERR_LOG0_VALID", (reg_val &
	GLBL_DSC_ERR_LOG0_VALID_MASK) >> 31);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [30,29]      0x%x\n",
	"GLBL_DSC_ERR_LOG0_RSVD_1", (reg_val &
	GLBL_DSC_ERR_LOG0_RSVD_1_MASK) >> 29);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [28,17]      0x%x\n",
	"GLBL_DSC_ERR_LOG0_QID", (reg_val &
	GLBL_DSC_ERR_LOG0_QID_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"GLBL_DSC_ERR_LOG0_SEL", (reg_val &
	GLBL_DSC_ERR_LOG0_SEL_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_DSC_ERR_LOG0_CIDX", (reg_val &
	GLBL_DSC_ERR_LOG0_CIDX_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_dsc_err_log1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,9 ]      0x%x\n",
	"GLBL_DSC_ERR_LOG1_RSVD_1", (reg_val &
	GLBL_DSC_ERR_LOG1_RSVD_1_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8 ,5 ]      0x%x\n",
	"GLBL_DSC_ERR_LOG1_SUB_TYPE", (reg_val &
	GLBL_DSC_ERR_LOG1_SUB_TYPE_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4 ,0 ]      0x%x\n",
	"GLBL_DSC_ERR_LOG1_ERR_TYPE", (reg_val &
	GLBL_DSC_ERR_LOG1_ERR_TYPE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_trq_err_sts_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,4 ]      0x%x\n",
	"GLBL_TRQ_ERR_STS_RSVD_1", (reg_val &
	GLBL_TRQ_ERR_STS_RSVD_1_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3    ]      0x%x\n",
	"GLBL_TRQ_ERR_STS_TCP_TIMEOUT", (reg_val &
	GLBL_TRQ_ERR_STS_TCP_TIMEOUT_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"GLBL_TRQ_ERR_STS_VF_ACCESS_ERR", (reg_val &
	GLBL_TRQ_ERR_STS_VF_ACCESS_ERR_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"GLBL_TRQ_ERR_STS_QID_RANGE", (reg_val &
	GLBL_TRQ_ERR_STS_QID_RANGE_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"GLBL_TRQ_ERR_STS_UNMAPPED", (reg_val &
	GLBL_TRQ_ERR_STS_UNMAPPED_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_trq_err_msk_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"GLBL_TRQ_ERR", (reg_val &
	GLBL_TRQ_ERR_MSK_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_trq_err_log_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,28]      0x%x\n",
	"GLBL_TRQ_ERR_LOG_RSVD_1", (reg_val &
	GLBL_TRQ_ERR_LOG_RSVD_1_MASK) >> 28);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [27,24]      0x%x\n",
	"GLBL_TRQ_ERR_LOG_TARGET", (reg_val &
	GLBL_TRQ_ERR_LOG_TARGET_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,16]      0x%x\n",
	"GLBL_TRQ_ERR_LOG_FUNC", (reg_val &
	GLBL_TRQ_ERR_LOG_FUNC_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"GLBL_TRQ_ERR_LOG_ADDRE", (reg_val &
	GLBL_TRQ_ERR_LOG_ADDRESS_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_dsc_dbg_dat0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,30]      0x%x\n",
	"GLBL_DSC_DAT0_RSVD_1", (reg_val &
	GLBL_DSC_DAT0_RSVD_1_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29   ]      0x%x\n",
	"GLBL_DSC_DAT0_CTXT_ARB_DIR", (reg_val &
	GLBL_DSC_DAT0_CTXT_ARB_DIR_MASK) >> 29);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [28,17]      0x%x\n",
	"GLBL_DSC_DAT0_CTXT_ARB_QID", (reg_val &
	GLBL_DSC_DAT0_CTXT_ARB_QID_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16,12]      0x%x\n",
	"GLBL_DSC_DAT0_CTXT_ARB_REQ", (reg_val &
	GLBL_DSC_DAT0_CTXT_ARB_REQ_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11   ]      0x%x\n",
	"GLBL_DSC_DAT0_IRQ_FIFO_FL", (reg_val &
	GLBL_DSC_DAT0_IRQ_FIFO_FL_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10   ]      0x%x\n",
	"GLBL_DSC_DAT0_TMSTALL", (reg_val &
	GLBL_DSC_DAT0_TMSTALL_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,8 ]      0x%x\n",
	"GLBL_DSC_DAT0_RRQ_STALL", (reg_val &
	GLBL_DSC_DAT0_RRQ_STALL_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,6 ]      0x%x\n",
	"GLBL_DSC_DAT0_RCP_FIFO_SPC_STALL", (reg_val &
	GLBL_DSC_DAT0_RCP_FIFO_SPC_STALL_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5 ,4 ]      0x%x\n",
	"GLBL_DSC_DAT0_RRQ_FIFO_SPC_STALL", (reg_val &
	GLBL_DSC_DAT0_RRQ_FIFO_SPC_STALL_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3 ,2 ]      0x%x\n",
	"GLBL_DSC_DAT0_FAB_MRKR_RSP_STALL", (reg_val &
	GLBL_DSC_DAT0_FAB_MRKR_RSP_STALL_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1 ,0 ]      0x%x\n",
	"GLBL_DSC_DAT0_DSC_OUT_STALL", (reg_val &
	GLBL_DSC_DAT0_DSC_OUT_STALL_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_dsc_dbg_dat1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,28]      0x%x\n",
	"GLBL_DSC_DAT1_RSVD_1", (reg_val &
	GLBL_DSC_DAT1_RSVD_1_MASK) >> 28);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [27,22]      0x%x\n",
	"GLBL_DSC_DAT1_EVT_SPC_C2H", (reg_val &
	GLBL_DSC_DAT1_EVT_SPC_C2H_MASK) >> 22);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [21,16]      0x%x\n",
	"GLBL_DSC_DAT1_EVT_SP_H2C", (reg_val &
	GLBL_DSC_DAT1_EVT_SP_H2C_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,8 ]      0x%x\n",
	"GLBL_DSC_DAT1_DSC_SPC_C2H", (reg_val &
	GLBL_DSC_DAT1_DSC_SPC_C2H_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"GLBL_DSC_DAT1_DSC_SPC_H2C", (reg_val &
	GLBL_DSC_DAT1_DSC_SPC_H2C_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_0_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_0_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_0_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_0_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_0_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_0_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_1_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_1_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_1_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_1_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_1_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_1_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_2_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_2_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_2_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_2_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_2_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_2_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_3_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_3_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_3_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_3_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_3_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_3_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_4_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_4_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_4_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_4_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_4_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_4_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_5_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_5_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_5_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_5_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_5_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_5_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_6_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_6_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_6_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_6_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_6_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_6_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_6_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_7_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_7_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_7_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_7_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_7_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_7_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_7_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_8_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_8_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_8_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_8_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_8_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_8_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_8_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_9_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_9_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_9_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_9_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_9_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_9_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_9_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_A_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_A_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_A_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_A_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_A_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_A_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_B_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_B_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_B_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_B_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_B_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_B_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_D_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_D_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_D_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_D_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_D_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_D_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_E_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_E_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_E_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_E_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_E_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_E_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_F_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_F_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_F_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_F_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_F_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_F_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_10_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_10_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_10_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_10_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_10_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_10_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_10_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_11_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_11_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_11_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_11_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_11_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_11_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_11_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_12_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_12_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_12_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_12_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_12_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_12_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_12_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_13_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_13_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_13_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_13_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_13_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_13_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_13_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_14_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_14_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_14_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_14_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_14_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_14_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_14_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_15_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_15_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_15_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_15_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_15_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_15_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_15_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_16_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_16_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_16_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_16_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_16_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_16_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_16_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_17_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_17_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_17_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_17_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_17_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_17_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_17_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_18_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_18_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_18_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_18_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_18_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_18_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_18_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_19_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_19_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_19_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_19_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_19_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_19_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_19_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_1a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_1A_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_1A_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_1A_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_1A_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_1A_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_1A_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_1b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_1B_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_1B_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_1B_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_1B_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_1B_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_1B_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_1c_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_1C_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_1C_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_1C_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_1C_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_1C_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_1C_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_1d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_1D_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_1D_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_1D_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_1D_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_1D_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_1D_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_1e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_1E_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_1E_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_1E_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_1E_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_1E_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_1E_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_1f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_1F_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_1F_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_1F_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_1F_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_1F_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_1F_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_20_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_20_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_20_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_20_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_20_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_20_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_20_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_21_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_21_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_21_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_21_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_21_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_21_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_21_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_22_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_22_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_22_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_22_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_22_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_22_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_22_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_23_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_23_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_23_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_23_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_23_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_23_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_23_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_24_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_24_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_24_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_24_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_24_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_24_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_24_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_25_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_25_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_25_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_25_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_25_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_25_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_25_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_26_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_26_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_26_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_26_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_26_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_26_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_26_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_27_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_27_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_27_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_27_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_27_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_27_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_27_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_28_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_28_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_28_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_28_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_28_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_28_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_28_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_29_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_29_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_29_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_29_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_29_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_29_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_29_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_2a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_2A_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_2A_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_2A_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_2A_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_2A_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_2A_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_2b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_2B_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_2B_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_2B_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_2B_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_2B_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_2B_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_2c_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_2C_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_2C_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_2C_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_2C_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_2C_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_2C_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_2d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_2D_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_2D_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_2D_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_2D_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_2D_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_2D_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_2e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_2E_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_2E_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_2E_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_2E_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_2E_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_2E_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_2f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_2F_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_2F_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_2F_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_2F_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_2F_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_2F_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_30_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_30_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_30_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_30_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_30_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_30_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_30_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_31_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_31_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_31_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_31_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_31_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_31_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_31_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_32_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_32_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_32_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_32_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_32_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_32_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_32_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_33_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_33_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_33_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_33_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_33_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_33_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_33_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_34_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_34_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_34_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_34_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_34_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_34_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_34_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_35_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_35_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_35_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_35_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_35_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_35_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_35_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_36_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_36_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_36_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_36_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_36_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_36_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_36_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_37_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_37_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_37_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_37_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_37_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_37_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_37_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_38_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_38_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_38_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_38_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_38_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_38_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_38_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_39_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_39_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_39_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_39_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_39_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_39_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_39_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_3a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_3A_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_3A_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_3A_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_3A_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_3A_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_3A_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_3b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_3B_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_3B_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_3B_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_3B_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_3B_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_3B_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_3c_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_3C_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_3C_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_3C_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_3C_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_3C_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_3C_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_3d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_3D_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_3D_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_3D_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_3D_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_3D_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_3D_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_3e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_3E_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_3E_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_3E_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_3E_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_3E_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_3E_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_3f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_3F_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_3F_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_3F_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_3F_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_3F_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_3F_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_40_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_40_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_40_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_40_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_40_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_40_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_40_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_41_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_41_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_41_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_41_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_41_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_41_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_41_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_42_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_42_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_42_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_42_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_42_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_42_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_42_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_43_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_43_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_43_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_43_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_43_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_43_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_43_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_44_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_44_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_44_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_44_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_44_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_44_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_44_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_45_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_45_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_45_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_45_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_45_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_45_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_45_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_46_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_46_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_46_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_46_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_46_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_46_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_46_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_47_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_47_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_47_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_47_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_47_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_47_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_47_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_48_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_48_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_48_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_48_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_48_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_48_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_48_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_49_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_49_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_49_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_49_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_49_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_49_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_49_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_4a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_4A_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_4A_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_4A_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_4A_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_4A_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_4A_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_4b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_4B_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_4B_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_4B_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_4B_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_4B_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_4B_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_4c_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_4C_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_4C_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_4C_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_4C_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_4C_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_4C_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_4d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_4D_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_4D_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_4D_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_4D_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_4D_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_4D_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_4e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_4E_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_4E_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_4E_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_4E_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_4E_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_4E_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_4f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_4F_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_4F_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_4F_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_4F_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_4F_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_4F_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_50_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_50_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_50_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_50_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_50_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_50_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_50_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_51_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_51_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_51_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_51_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_51_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_51_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_51_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_52_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_52_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_52_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_52_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_52_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_52_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_52_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_53_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_53_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_53_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_53_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_53_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_53_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_53_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_54_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_54_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_54_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_54_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_54_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_54_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_54_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_55_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_55_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_55_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_55_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_55_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_55_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_55_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_56_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_56_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_56_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_56_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_56_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_56_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_56_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_57_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_57_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_57_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_57_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_57_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_57_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_57_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_58_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_58_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_58_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_58_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_58_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_58_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_58_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_59_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_59_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_59_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_59_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_59_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_59_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_59_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_5a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_5A_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_5A_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_5A_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_5A_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_5A_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_5A_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_5b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_5B_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_5B_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_5B_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_5B_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_5B_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_5B_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_5c_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_5C_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_5C_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_5C_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_5C_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_5C_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_5C_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_5d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_5D_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_5D_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_5D_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_5D_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_5D_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_5D_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_5e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_5E_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_5E_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_5E_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_5E_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_5E_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_5E_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_5f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_5F_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_5F_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_5F_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_5F_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_5F_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_5F_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_60_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_60_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_60_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_60_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_60_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_60_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_60_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_61_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_61_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_61_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_61_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_61_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_61_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_61_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_62_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_62_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_62_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_62_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_62_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_62_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_62_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_63_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_63_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_63_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_63_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_63_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_63_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_63_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_64_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_64_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_64_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_64_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_64_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_64_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_64_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_65_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_65_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_65_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_65_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_65_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_65_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_65_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_66_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_66_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_66_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_66_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_66_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_66_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_66_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_67_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_67_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_67_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_67_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_67_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_67_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_67_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_68_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_68_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_68_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_68_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_68_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_68_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_68_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_69_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_69_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_69_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_69_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_69_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_69_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_69_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_6a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_6A_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_6A_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_6A_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_6A_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_6A_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_6A_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_6b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_6B_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_6B_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_6B_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_6B_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_6B_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_6B_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_6c_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_6C_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_6C_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_6C_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_6C_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_6C_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_6C_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_6d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_6D_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_6D_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_6D_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_6D_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_6D_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_6D_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_6e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_6E_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_6E_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_6E_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_6E_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_6E_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_6E_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_6f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_6F_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_6F_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_6F_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_6F_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_6F_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_6F_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_70_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_70_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_70_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_70_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_70_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_70_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_70_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_71_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_71_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_71_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_71_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_71_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_71_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_71_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_72_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_72_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_72_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_72_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_72_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_72_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_72_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_73_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_73_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_73_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_73_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_73_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_73_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_73_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_74_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_74_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_74_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_74_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_74_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_74_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_74_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_75_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_75_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_75_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_75_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_75_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_75_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_75_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_76_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_76_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_76_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_76_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_76_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_76_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_76_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_77_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_77_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_77_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_77_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_77_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_77_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_77_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_78_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_78_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_78_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_78_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_78_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_78_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_78_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_79_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_79_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_79_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_79_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_79_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_79_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_79_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_7a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_7A_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_7A_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_7A_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_7A_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_7A_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_7A_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_7b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_7B_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_7B_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_7B_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_7B_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_7B_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_7B_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_7c_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_7C_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_7C_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_7C_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_7C_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_7C_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_7C_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_7d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_7D_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_7D_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_7D_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_7D_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_7D_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_7D_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_7e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_7E_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_7E_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_7E_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_7E_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_7E_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_7E_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_7f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_7F_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_7F_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_7F_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_7F_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_7F_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_7F_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_80_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_80_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_80_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_80_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_80_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_80_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_80_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_81_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_81_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_81_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_81_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_81_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_81_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_81_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_82_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_82_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_82_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_82_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_82_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_82_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_82_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_83_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_83_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_83_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_83_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_83_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_83_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_83_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_84_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_84_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_84_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_84_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_84_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_84_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_84_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_85_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_85_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_85_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_85_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_85_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_85_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_85_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_86_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_86_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_86_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_86_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_86_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_86_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_86_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_87_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_87_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_87_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_87_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_87_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_87_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_87_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_88_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_88_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_88_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_88_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_88_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_88_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_88_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_89_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_89_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_89_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_89_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_89_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_89_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_89_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_8a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_8A_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_8A_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_8A_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_8A_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_8A_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_8A_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_8b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_8B_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_8B_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_8B_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_8B_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_8B_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_8B_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_8c_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_8C_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_8C_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_8C_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_8C_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_8C_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_8C_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_8d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_8D_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_8D_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_8D_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_8D_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_8D_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_8D_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_8e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_8E_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_8E_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_8E_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_8E_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_8E_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_8E_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_8f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_8F_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_8F_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_8F_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_8F_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_8F_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_8F_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_90_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_90_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_90_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_90_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_90_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_90_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_90_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_91_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_91_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_91_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_91_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_91_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_91_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_91_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_92_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_92_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_92_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_92_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_92_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_92_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_92_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_93_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_93_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_93_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_93_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_93_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_93_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_93_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_94_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_94_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_94_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_94_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_94_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_94_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_94_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_95_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_95_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_95_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_95_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_95_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_95_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_95_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_96_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_96_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_96_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_96_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_96_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_96_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_96_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_97_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_97_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_97_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_97_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_97_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_97_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_97_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_98_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_98_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_98_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_98_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_98_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_98_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_98_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_99_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_99_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_99_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_99_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_99_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_99_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_99_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_9a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_9A_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_9A_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_9A_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_9A_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_9A_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_9A_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_9b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_9B_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_9B_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_9B_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_9B_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_9B_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_9B_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_9c_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_9C_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_9C_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_9C_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_9C_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_9C_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_9C_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_9d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_9D_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_9D_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_9D_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_9D_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_9D_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_9D_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_9e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_9E_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_9E_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_9E_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_9E_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_9E_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_9E_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_9f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_9F_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_9F_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_9F_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_9F_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_9F_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_9F_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_a0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_A0_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_A0_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_A0_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_A0_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_A0_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_A0_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_a1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_A1_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_A1_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_A1_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_A1_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_A1_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_A1_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_a2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_A2_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_A2_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_A2_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_A2_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_A2_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_A2_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_a3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_A3_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_A3_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_A3_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_A3_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_A3_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_A3_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_a4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_A4_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_A4_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_A4_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_A4_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_A4_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_A4_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_a5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_A5_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_A5_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_A5_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_A5_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_A5_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_A5_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_a6_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_A6_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_A6_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_A6_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_A6_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_A6_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_A6_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_a7_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_A7_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_A7_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_A7_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_A7_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_A7_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_A7_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_a8_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_A8_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_A8_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_A8_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_A8_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_A8_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_A8_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_a9_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_A9_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_A9_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_A9_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_A9_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_A9_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_A9_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_aa_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_AA_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_AA_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_AA_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_AA_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_AA_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_AA_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_ab_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_AB_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_AB_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_AB_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_AB_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_AB_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_AB_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_ac_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_AC_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_AC_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_AC_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_AC_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_AC_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_AC_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_ad_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_AD_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_AD_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_AD_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_AD_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_AD_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_AD_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_ae_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_AE_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_AE_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_AE_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_AE_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_AE_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_AE_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_af_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_AF_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_AF_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_AF_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_AF_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_AF_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_AF_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_b0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_B0_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_B0_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_B0_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_B0_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_B0_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_B0_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_b1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_B1_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_B1_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_B1_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_B1_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_B1_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_B1_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_b2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_B2_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_B2_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_B2_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_B2_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_B2_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_B2_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_b3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_B3_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_B3_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_B3_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_B3_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_B3_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_B3_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_b4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_B4_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_B4_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_B4_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_B4_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_B4_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_B4_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_b5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_B5_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_B5_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_B5_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_B5_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_B5_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_B5_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_b6_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_B6_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_B6_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_B6_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_B6_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_B6_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_B6_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_b7_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_B7_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_B7_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_B7_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_B7_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_B7_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_B7_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_b8_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_B8_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_B8_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_B8_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_B8_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_B8_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_B8_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_b9_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_B9_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_B9_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_B9_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_B9_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_B9_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_B9_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_ba_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_BA_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_BA_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_BA_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_BA_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_BA_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_BA_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_bb_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_BB_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_BB_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_BB_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_BB_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_BB_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_BB_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_bc_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_BC_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_BC_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_BC_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_BC_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_BC_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_BC_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_bd_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_BD_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_BD_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_BD_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_BD_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_BD_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_BD_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_be_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_BE_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_BE_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_BE_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_BE_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_BE_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_BE_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_bf_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_BF_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_BF_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_BF_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_BF_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_BF_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_BF_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_c0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_C0_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_C0_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_C0_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_C0_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_C0_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_C0_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_c1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_C1_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_C1_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_C1_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_C1_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_C1_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_C1_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_c2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_C2_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_C2_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_C2_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_C2_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_C2_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_C2_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_c3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_C3_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_C3_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_C3_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_C3_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_C3_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_C3_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_c4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_C4_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_C4_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_C4_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_C4_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_C4_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_C4_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_c5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_C5_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_C5_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_C5_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_C5_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_C5_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_C5_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_c6_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_C6_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_C6_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_C6_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_C6_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_C6_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_C6_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_c7_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_C7_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_C7_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_C7_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_C7_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_C7_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_C7_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_c8_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_C8_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_C8_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_C8_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_C8_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_C8_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_C8_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_c9_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_C9_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_C9_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_C9_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_C9_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_C9_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_C9_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_ca_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_CA_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_CA_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_CA_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_CA_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_CA_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_CA_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_cb_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_CB_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_CB_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_CB_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_CB_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_CB_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_CB_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_cc_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_CC_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_CC_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_CC_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_CC_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_CC_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_CC_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_cd_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_CD_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_CD_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_CD_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_CD_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_CD_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_CD_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_ce_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_CE_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_CE_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_CE_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_CE_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_CE_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_CE_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_cf_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_CF_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_CF_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_CF_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_CF_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_CF_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_CF_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_d0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_D0_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_D0_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_D0_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_D0_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_D0_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_D0_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_d1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_D1_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_D1_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_D1_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_D1_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_D1_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_D1_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_d2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_D2_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_D2_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_D2_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_D2_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_D2_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_D2_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_d3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_D3_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_D3_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_D3_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_D3_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_D3_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_D3_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_d4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_D4_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_D4_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_D4_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_D4_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_D4_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_D4_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_d5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_D5_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_D5_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_D5_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_D5_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_D5_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_D5_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_d6_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_D6_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_D6_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_D6_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_D6_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_D6_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_D6_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_d7_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_D7_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_D7_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_D7_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_D7_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_D7_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_D7_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_d8_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_D8_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_D8_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_D8_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_D8_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_D8_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_D8_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_d9_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_D9_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_D9_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_D9_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_D9_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_D9_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_D9_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_da_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_DA_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_DA_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_DA_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_DA_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_DA_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_DA_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_db_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_DB_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_DB_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_DB_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_DB_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_DB_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_DB_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_dc_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_DC_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_DC_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_DC_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_DC_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_DC_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_DC_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_dd_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_DD_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_DD_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_DD_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_DD_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_DD_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_DD_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_de_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_DE_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_DE_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_DE_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_DE_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_DE_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_DE_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_df_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_DF_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_DF_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_DF_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_DF_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_DF_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_DF_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_e0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_E0_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_E0_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_E0_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_E0_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_E0_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_E0_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_e1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_E1_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_E1_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_E1_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_E1_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_E1_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_E1_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_e2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_E2_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_E2_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_E2_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_E2_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_E2_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_E2_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_e3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_E3_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_E3_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_E3_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_E3_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_E3_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_E3_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_e4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_E4_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_E4_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_E4_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_E4_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_E4_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_E4_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_e5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_E5_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_E5_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_E5_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_E5_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_E5_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_E5_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_e6_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_E6_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_E6_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_E6_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_E6_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_E6_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_E6_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_e7_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_E7_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_E7_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_E7_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_E7_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_E7_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_E7_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_e8_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_E8_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_E8_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_E8_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_E8_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_E8_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_E8_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_e9_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_E9_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_E9_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_E9_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_E9_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_E9_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_E9_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_ea_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_EA_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_EA_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_EA_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_EA_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_EA_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_EA_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_eb_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_EB_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_EB_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_EB_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_EB_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_EB_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_EB_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_ec_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_EC_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_EC_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_EC_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_EC_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_EC_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_EC_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_ed_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_ED_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_ED_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_ED_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_ED_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_ED_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_ED_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_ee_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_EE_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_EE_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_EE_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_EE_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_EE_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_EE_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_ef_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_EF_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_EF_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_EF_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_EF_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_EF_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_EF_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_trq_sel_fmap_f0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,23]      0x%x\n",
	"TRQ_SEL_FMAP_F0_RSVD_1", (reg_val &
	TRQ_SEL_FMAP_F0_RSVD_1_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,11]      0x%x\n",
	"TRQ_SEL_FMAP_F0_QID_MAX", (reg_val &
	TRQ_SEL_FMAP_F0_QID_MAX_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"TRQ_SEL_FMAP_F0_QID_BASE", (reg_val &
	TRQ_SEL_FMAP_F0_QID_BASE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ind_ctxt_data_3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"IND_CTXT_DATA_3_DAT", (reg_val &
	IND_CTXT_DATA_3_DATA_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ind_ctxt_data_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"IND_CTXT_DATA_2_DAT", (reg_val &
	IND_CTXT_DATA_2_DATA_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ind_ctxt_data_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"IND_CTXT_DATA_1_DAT", (reg_val &
	IND_CTXT_DATA_1_DATA_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ind_ctxt_data_0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"IND_CTXT_DATA_0_DAT", (reg_val &
	IND_CTXT_DATA_0_DATA_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ind_ctxt3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"IND_CTXT3", (reg_val &
	IND_CTXT3_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ind_ctxt2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"IND_CTXT2", (reg_val &
	IND_CTXT2_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ind_ctxt1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"IND_CTXT1", (reg_val &
	IND_CTXT1_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ind_ctxt0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"IND_CTXT0", (reg_val &
	IND_CTXT0_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_ind_ctxt_cmd_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"IND_CTXT_CMD_RSVD_1", (reg_val &
	IND_CTXT_CMD_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,7 ]      0x%x\n",
	"IND_CTXT_CMD_QID", (reg_val &
	IND_CTXT_CMD_QID_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6 ,5 ]      0x%x\n",
	"IND_CTXT_CMD_OP", (reg_val &
	IND_CTXT_CMD_OP_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4 ,1 ]      0x%x\n",
	"IND_CTXT_CMD_SET", (reg_val &
	IND_CTXT_CMD_SET_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"IND_CTXT_CMD_BUSY", (reg_val &
	IND_CTXT_CMD_BUSY_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_1_RSVD_1", (reg_val &
	C2H_TIMER_CNT_1_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_1", (reg_val &
	C2H_TIMER_CNT_1_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_2_RSVD_1", (reg_val &
	C2H_TIMER_CNT_2_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_2", (reg_val &
	C2H_TIMER_CNT_2_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_3_RSVD_1", (reg_val &
	C2H_TIMER_CNT_3_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_3", (reg_val &
	C2H_TIMER_CNT_3_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_4_RSVD_1", (reg_val &
	C2H_TIMER_CNT_4_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_4", (reg_val &
	C2H_TIMER_CNT_4_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_5_RSVD_1", (reg_val &
	C2H_TIMER_CNT_5_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_5", (reg_val &
	C2H_TIMER_CNT_5_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_6_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_6_RSVD_1", (reg_val &
	C2H_TIMER_CNT_6_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_6", (reg_val &
	C2H_TIMER_CNT_6_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_7_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_7_RSVD_1", (reg_val &
	C2H_TIMER_CNT_7_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_7", (reg_val &
	C2H_TIMER_CNT_7_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_8_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_8_RSVD_1", (reg_val &
	C2H_TIMER_CNT_8_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_8", (reg_val &
	C2H_TIMER_CNT_8_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_9_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_9_RSVD_1", (reg_val &
	C2H_TIMER_CNT_9_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_9", (reg_val &
	C2H_TIMER_CNT_9_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_A_RSVD_1", (reg_val &
	C2H_TIMER_CNT_A_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT", (reg_val &
	C2H_TIMER_CNT_A_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_B_RSVD_1", (reg_val &
	C2H_TIMER_CNT_B_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_B", (reg_val &
	C2H_TIMER_CNT_B_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_c_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_C_RSVD_1", (reg_val &
	C2H_TIMER_CNT_C_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_C", (reg_val &
	C2H_TIMER_CNT_C_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_D_RSVD_1", (reg_val &
	C2H_TIMER_CNT_D_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_D", (reg_val &
	C2H_TIMER_CNT_D_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_E_RSVD_1", (reg_val &
	C2H_TIMER_CNT_E_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_E", (reg_val &
	C2H_TIMER_CNT_E_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_F_RSVD_1", (reg_val &
	C2H_TIMER_CNT_F_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_F", (reg_val &
	C2H_TIMER_CNT_F_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_timer_cnt_10_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_TIMER_CNT_10_RSVD_1", (reg_val &
	C2H_TIMER_CNT_10_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_TIMER_CNT_10", (reg_val &
	C2H_TIMER_CNT_10_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_1_RSVD_1", (reg_val &
	C2H_CNT_TH_1_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_1_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_1_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_2_RSVD_1", (reg_val &
	C2H_CNT_TH_2_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_2_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_2_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_3_RSVD_1", (reg_val &
	C2H_CNT_TH_3_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_3_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_3_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_4_RSVD_1", (reg_val &
	C2H_CNT_TH_4_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_4_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_4_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_5_RSVD_1", (reg_val &
	C2H_CNT_TH_5_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_5_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_5_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_6_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_6_RSVD_1", (reg_val &
	C2H_CNT_TH_6_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_6_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_6_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_7_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_7_RSVD_1", (reg_val &
	C2H_CNT_TH_7_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_7_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_7_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_8_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_8_RSVD_1", (reg_val &
	C2H_CNT_TH_8_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_8_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_8_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_9_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_9_RSVD_1", (reg_val &
	C2H_CNT_TH_9_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_9_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_9_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_A_RSVD_1", (reg_val &
	C2H_CNT_TH_A_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_A_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_A_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_b_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_B_RSVD_1", (reg_val &
	C2H_CNT_TH_B_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_B_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_B_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_c_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_C_RSVD_1", (reg_val &
	C2H_CNT_TH_C_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_C_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_C_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_d_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_D_RSVD_1", (reg_val &
	C2H_CNT_TH_D_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_D_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_D_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_e_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_E_RSVD_1", (reg_val &
	C2H_CNT_TH_E_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_E_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_E_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_f_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_F_RSVD_1", (reg_val &
	C2H_CNT_TH_F_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_F_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_F_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_cnt_th_10_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_CNT_TH_10_RSVD_1", (reg_val &
	C2H_CNT_TH_10_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_CNT_TH_10_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_10_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_qid2vec_map_qid_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,11]      0x%x\n",
	"C2H_QID2VEC_MAP_QID_RSVD_1", (reg_val &
	C2H_QID2VEC_MAP_QID_RSVD_1_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"C2H_QID2VEC_MAP_QID_QID", (reg_val &
	C2H_QID2VEC_MAP_QID_QID_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_qid2vec_map_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,19]      0x%x\n",
	"C2H_QID2VEC_MAP_RSVD_1", (reg_val &
	C2H_QID2VEC_MAP_RSVD_1_MASK) >> 19);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [18   ]      0x%x\n",
	"C2H_QID2VEC_MAP_H2C_EN_COAL", (reg_val &
	C2H_QID2VEC_MAP_H2C_EN_COAL_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,9 ]      0x%x\n",
	"C2H_QID2VEC_MAP_H2C_VECTOR", (reg_val &
	C2H_QID2VEC_MAP_H2C_VECTOR_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8    ]      0x%x\n",
	"C2H_QID2VEC_MAP_C2H_EN_COAL", (reg_val &
	C2H_QID2VEC_MAP_C2H_EN_COAL_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_QID2VEC_MAP_C2H_VECTOR", (reg_val &
	C2H_QID2VEC_MAP_C2H_VECTOR_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_s_axis_c2h_accepted_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_S_AXIS_C2H_ACCEPTED", (reg_val &
	C2H_STAT_S_AXIS_C2H_ACCEPTED_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_s_axis_wrb_accepted_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_S_AXIS_WRB_ACCEPTED", (reg_val &
	C2H_STAT_S_AXIS_WRB_ACCEPTED_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_desc_rsp_pkt_accepted_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_DESC_RSP_PKT_ACCEPTED_D", (reg_val &
	C2H_STAT_DESC_RSP_PKT_ACCEPTED_D_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_axis_pkg_cmp_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_AXIS_PKG_CMP", (reg_val &
	C2H_STAT_AXIS_PKG_CMP_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_desc_rsp_accepted_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_DESC_RSP_ACCEPTED_D", (reg_val &
	C2H_STAT_DESC_RSP_ACCEPTED_D_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_desc_rsp_cmp_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_DESC_RSP_CMP_D", (reg_val &
	C2H_STAT_DESC_RSP_CMP_D_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_wrq_out_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_WRQ_OUT", (reg_val &
	C2H_STAT_WRQ_OUT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_wpl_ren_accepted_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_WPL_REN_ACCEPTED", (reg_val &
	C2H_STAT_WPL_REN_ACCEPTED_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_total_wrq_len_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_TOTAL_WRQ_LEN", (reg_val &
	C2H_STAT_TOTAL_WRQ_LEN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_total_wpl_len_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_TOTAL_WPL_LEN", (reg_val &
	C2H_STAT_TOTAL_WPL_LEN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_0_SIZE", (reg_val &
	C2H_BUF_SZ_0_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_1_SIZE", (reg_val &
	C2H_BUF_SZ_1_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_2_SIZE", (reg_val &
	C2H_BUF_SZ_2_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_3_SIZE", (reg_val &
	C2H_BUF_SZ_3_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_4_SIZE", (reg_val &
	C2H_BUF_SZ_4_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_5_SIZE", (reg_val &
	C2H_BUF_SZ_5_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_7_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_7_SIZE", (reg_val &
	C2H_BUF_SZ_7_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_8_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_8_SIZE", (reg_val &
	C2H_BUF_SZ_8_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_9_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_9_SIZE", (reg_val &
	C2H_BUF_SZ_9_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_10_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_10_SIZE", (reg_val &
	C2H_BUF_SZ_10_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_11_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_11_SIZE", (reg_val &
	C2H_BUF_SZ_11_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_12_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_12_SIZE", (reg_val &
	C2H_BUF_SZ_12_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_13_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_13_SIZE", (reg_val &
	C2H_BUF_SZ_13_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_14_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_14_SIZE", (reg_val &
	C2H_BUF_SZ_14_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_buf_sz_15_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_15_SIZE", (reg_val &
	C2H_BUF_SZ_15_SIZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_err_stat_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_ERR_STAT_RSVD_1", (reg_val &
	C2H_ERR_STAT_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15   ]      0x%x\n",
	"C2H_ERR_STAT_WRB_PRTY_ERR", (reg_val &
	C2H_ERR_STAT_WRB_PRTY_ERR_MASK) >> 15);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [14   ]      0x%x\n",
	"C2H_ERR_STAT_WRB_CIDX_ERR", (reg_val &
	C2H_ERR_STAT_WRB_CIDX_ERR_MASK) >> 14);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [13   ]      0x%x\n",
	"C2H_ERR_STAT_WRB_QFULL_ERR", (reg_val &
	C2H_ERR_STAT_WRB_QFULL_ERR_MASK) >> 13);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [12   ]      0x%x\n",
	"C2H_ERR_STAT_WRB_INV_Q_ERR", (reg_val &
	C2H_ERR_STAT_WRB_INV_Q_ERR_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11   ]      0x%x\n",
	"C2H_ERR_STAT_PORT_ID_BYP_IN_MISMATCH", (reg_val &
	C2H_ERR_STAT_PORT_ID_BYP_IN_MISMATCH_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10   ]      0x%x\n",
	"C2H_ERR_STAT_PORT_ID_CTXT_MISMATCH", (reg_val &
	C2H_ERR_STAT_PORT_ID_CTXT_MISMATCH_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9    ]      0x%x\n",
	"C2H_ERR_STAT_ERR_DESC_CNT", (reg_val &
	C2H_ERR_STAT_ERR_DESC_CNT_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8    ]      0x%x\n",
	"C2H_ERR_STAT_RSVD_2", (reg_val &
	C2H_ERR_STAT_RSVD_2_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7    ]      0x%x\n",
	"C2H_ERR_STAT_MSI_INT_FAIL", (reg_val &
	C2H_ERR_STAT_MSI_INT_FAIL_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6    ]      0x%x\n",
	"C2H_ERR_STAT_ENG_WPL_DATA_PAR_ERR", (reg_val &
	C2H_ERR_STAT_ENG_WPL_DATA_PAR_ERR_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5    ]      0x%x\n",
	"C2H_ERR_STAT_RSVD_3", (reg_val &
	C2H_ERR_STAT_RSVD_3_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4    ]      0x%x\n",
	"C2H_ERR_STAT_DESC_RSP_ERR", (reg_val &
	C2H_ERR_STAT_DESC_RSP_ERR_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3    ]      0x%x\n",
	"C2H_ERR_STAT_QID_MISMATCH", (reg_val &
	C2H_ERR_STAT_QID_MISMATCH_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"C2H_ERR_STAT_RSVD_4", (reg_val &
	C2H_ERR_STAT_RSVD_4_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"C2H_ERR_STAT_LEN_MISMATCH", (reg_val &
	C2H_ERR_STAT_LEN_MISMATCH_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"C2H_ERR_STAT_MTY_MISMATCH", (reg_val &
	C2H_ERR_STAT_MTY_MISMATCH_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_err_mask_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_ERR_EN", (reg_val &
	C2H_ERR_EN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_fatal_err_stat_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,19]      0x%x\n",
	"C2H_FATAL_ERR_STAT_RSVD_1", (reg_val &
	C2H_FATAL_ERR_STAT_RSVD_1_MASK) >> 19);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [18   ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_WPL_DATA_PAR_ERR", (reg_val &
	C2H_FATAL_ERR_STAT_WPL_DATA_PAR_ERR_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17   ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_PLD_FIFO_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_PLD_FIFO_RAM_RDBE_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_QID_FIFO_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_QID_FIFO_RAM_RDBE_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15   ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_TUSER_FIFO_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_TUSER_FIFO_RAM_RDBE_MASK) >> 15);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [14   ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_WRB_COAL_DATA_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_WRB_COAL_DATA_RAM_RDBE_MASK) >> 14);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [13   ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_INT_QID2VEC_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_INT_QID2VEC_RAM_RDBE_MASK) >> 13);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [12   ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_INT_CTXT_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_INT_CTXT_RAM_RDBE_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11   ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_DESC_REQ_FIFO_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_DESC_REQ_FIFO_RAM_RDBE_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10   ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_PFCH_CTXT_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_PFCH_CTXT_RAM_RDBE_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9    ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_WRB_CTXT_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_WRB_CTXT_RAM_RDBE_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8    ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_PFCH_LL_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_PFCH_LL_RAM_RDBE_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,4 ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_TIMER_FIFO_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_TIMER_FIFO_RAM_RDBE_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3    ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_QID_MISMATCH", (reg_val &
	C2H_FATAL_ERR_STAT_QID_MISMATCH_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_RSVD_2", (reg_val &
	C2H_FATAL_ERR_STAT_RSVD_2_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_LEN_MISMATCH", (reg_val &
	C2H_FATAL_ERR_STAT_LEN_MISMATCH_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"C2H_FATAL_ERR_STAT_MTY_MISMATCH", (reg_val &
	C2H_FATAL_ERR_STAT_MTY_MISMATCH_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_fatal_err_mask_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_FATAL_ERR_C2HEN", (reg_val &
	C2H_FATAL_ERR_C2HEN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_fatal_err_enable_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,2 ]      0x%x\n",
	"C2H_FATAL_ERR_ENABLE_RSVD_1", (reg_val &
	C2H_FATAL_ERR_ENABLE_RSVD_1_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"C2H_FATAL_ERR_ENABLE_WPL_PAR_INV", (reg_val &
	C2H_FATAL_ERR_ENABLE_WPL_PAR_INV_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"C2H_FATAL_ERR_ENABLE_WRQ_DI", (reg_val &
	C2H_FATAL_ERR_ENABLE_WRQ_DIS_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_glbl_err_int_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"GLBL_ERR_INT_RSVD_1", (reg_val &
	GLBL_ERR_INT_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17   ]      0x%x\n",
	"GLBL_ERR_INT_AR", (reg_val &
	GLBL_ERR_INT_ARM_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"GLBL_ERR_INT_EN_COAL", (reg_val &
	GLBL_ERR_INT_EN_COAL_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,8 ]      0x%x\n",
	"GLBL_ERR_INT_VEC", (reg_val &
	GLBL_ERR_INT_VEC_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"GLBL_ERR_INT_FUNC", (reg_val &
	GLBL_ERR_INT_FUNC_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_pfch_cfg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,25]      0x%x\n",
	"C2H_PFCH_CFG_EVT_QCNT_TH", (reg_val &
	C2H_PFCH_CFG_EVT_QCNT_TH_MASK) >> 25);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [24,16]      0x%x\n",
	"C2H_PFCH_CFG_QCNT", (reg_val &
	C2H_PFCH_CFG_QCNT_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,8 ]      0x%x\n",
	"C2H_PFCH_CFG_NU", (reg_val &
	C2H_PFCH_CFG_NUM_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"C2H_PFCH_CFG_FL_TH", (reg_val &
	C2H_PFCH_CFG_FL_TH_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_int_timer_tick_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_INT_TIMER_TIC", (reg_val &
	C2H_INT_TIMER_TICK_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_desc_rsp_drop_accepted_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_DESC_RSP_DROP_ACCEPTED_D", (reg_val &
	C2H_STAT_DESC_RSP_DROP_ACCEPTED_D_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_desc_rsp_err_accepted_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_DESC_RSP_ERR_ACCEPTED_D", (reg_val &
	C2H_STAT_DESC_RSP_ERR_ACCEPTED_D_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_desc_req_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_DESC_REQ", (reg_val &
	C2H_STAT_DESC_REQ_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_dbg_dma_eng_0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"C2H_STAT_DMA_ENG_0_RSVD_1", (reg_val &
	C2H_STAT_DMA_ENG_0_RSVD_1_MASK) >> 31);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [30,28]      0x%x\n",
	"C2H_STAT_DMA_ENG_0_WRB_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_0_WRB_FIFO_OUT_CNT_MASK) >> 28);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [27,18]      0x%x\n",
	"C2H_STAT_DMA_ENG_0_QID_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_0_QID_FIFO_OUT_CNT_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,8 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_0_PLD_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_0_PLD_FIFO_OUT_CNT_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,5 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_0_WRQ_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_0_WRQ_FIFO_OUT_CNT_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4    ]      0x%x\n",
	"C2H_STAT_DMA_ENG_0_WRB_SM_C", (reg_val &
	C2H_STAT_DMA_ENG_0_WRB_SM_CS_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3 ,0 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_0_MAIN_SM_C", (reg_val &
	C2H_STAT_DMA_ENG_0_MAIN_SM_CS_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_dbg_dma_eng_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"C2H_STAT_DMA_ENG_1_RSVD_1", (reg_val &
	C2H_STAT_DMA_ENG_1_RSVD_1_MASK) >> 31);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [30   ]      0x%x\n",
	"C2H_STAT_DMA_ENG_1_DESC_RSP_LAST", (reg_val &
	C2H_STAT_DMA_ENG_1_DESC_RSP_LAST_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29,20]      0x%x\n",
	"C2H_STAT_DMA_ENG_1_PLD_FIFO_IN_CNT", (reg_val &
	C2H_STAT_DMA_ENG_1_PLD_FIFO_IN_CNT_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19,10]      0x%x\n",
	"C2H_STAT_DMA_ENG_1_PLD_FIFO_OUTPUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_1_PLD_FIFO_OUTPUT_CNT_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,0 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_1_QID_FIFO_IN_CNT", (reg_val &
	C2H_STAT_DMA_ENG_1_QID_FIFO_IN_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_dbg_dma_eng_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,30]      0x%x\n",
	"C2H_STAT_DMA_ENG_2_RSVD_1", (reg_val &
	C2H_STAT_DMA_ENG_2_RSVD_1_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29,20]      0x%x\n",
	"C2H_STAT_DMA_ENG_2_WRB_FIFO_IN_CNT", (reg_val &
	C2H_STAT_DMA_ENG_2_WRB_FIFO_IN_CNT_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19,10]      0x%x\n",
	"C2H_STAT_DMA_ENG_2_WRB_FIFO_OUTPUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_2_WRB_FIFO_OUTPUT_CNT_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,0 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_2_QID_FIFO_OUTPUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_2_QID_FIFO_OUTPUT_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_dbg_dma_eng_3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,30]      0x%x\n",
	"C2H_STAT_DMA_ENG_3_RSVD_1", (reg_val &
	C2H_STAT_DMA_ENG_3_RSVD_1_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29,20]      0x%x\n",
	"C2H_STAT_DMA_ENG_3_ADDR_4K_SPLIT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_3_ADDR_4K_SPLIT_CNT_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19,10]      0x%x\n",
	"C2H_STAT_DMA_ENG_3_WRQ_FIFO_IN_CNT", (reg_val &
	C2H_STAT_DMA_ENG_3_WRQ_FIFO_IN_CNT_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,0 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_3_WRQ_FIFO_OUTPUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_3_WRQ_FIFO_OUTPUT_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_dbg_pfch_err_ctxt_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,14]      0x%x\n",
	"C2H_PFCH_ERR_CTXT_RSVD_1", (reg_val &
	C2H_PFCH_ERR_CTXT_RSVD_1_MASK) >> 14);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [13   ]      0x%x\n",
	"C2H_PFCH_ERR_CTXT_ERR_STAT", (reg_val &
	C2H_PFCH_ERR_CTXT_ERR_STAT_MASK) >> 13);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [12   ]      0x%x\n",
	"C2H_PFCH_ERR_CTXT_CMD_WR", (reg_val &
	C2H_PFCH_ERR_CTXT_CMD_WR_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,1 ]      0x%x\n",
	"C2H_PFCH_ERR_CTXT_QID", (reg_val &
	C2H_PFCH_ERR_CTXT_QID_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"C2H_PFCH_ERR_CTXT_DONE", (reg_val &
	C2H_PFCH_ERR_CTXT_DONE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_first_err_qid_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,21]      0x%x\n",
	"C2H_FIRST_ERR_QID_RSVD_1", (reg_val &
	C2H_FIRST_ERR_QID_RSVD_1_MASK) >> 21);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [20,16]      0x%x\n",
	"C2H_FIRST_ERR_QID_ERR_STAT", (reg_val &
	C2H_FIRST_ERR_QID_ERR_STAT_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,12]      0x%x\n",
	"C2H_FIRST_ERR_QID_CMD_WR", (reg_val &
	C2H_FIRST_ERR_QID_CMD_WR_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,0 ]      0x%x\n",
	"C2H_FIRST_ERR_QID_QID", (reg_val &
	C2H_FIRST_ERR_QID_QID_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_stat_num_wrb_in_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"STAT_NUM_WRB_IN_RSVD_1", (reg_val &
	STAT_NUM_WRB_IN_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"STAT_NUM_WRB_IN_WRB_CNT", (reg_val &
	STAT_NUM_WRB_IN_WRB_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_stat_num_wrb_out_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"STAT_NUM_WRB_OUT_RSVD_1", (reg_val &
	STAT_NUM_WRB_OUT_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"STAT_NUM_WRB_OUT_WRB_CNT", (reg_val &
	STAT_NUM_WRB_OUT_WRB_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_stat_num_wrb_drp_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"STAT_NUM_WRB_DRP_RSVD_1", (reg_val &
	STAT_NUM_WRB_DRP_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"STAT_NUM_WRB_DRP_WRB_CNT", (reg_val &
	STAT_NUM_WRB_DRP_WRB_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_stat_num_stat_desc_out_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"STAT_NUM_STAT_DESC_OUT_RSVD_1", (reg_val &
	STAT_NUM_STAT_DESC_OUT_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"STAT_NUM_STAT_DESC_OUT_CNT", (reg_val &
	STAT_NUM_STAT_DESC_OUT_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_stat_num_dsc_crdt_sent_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"STAT_NUM_DSC_CRDT_SENT_RSVD_1", (reg_val &
	STAT_NUM_DSC_CRDT_SENT_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"STAT_NUM_DSC_CRDT_SENT_CNT", (reg_val &
	STAT_NUM_DSC_CRDT_SENT_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_stat_num_fch_dsc_rcvd_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"STAT_NUM_FCH_DSC_RCVD_RSVD_1", (reg_val &
	STAT_NUM_FCH_DSC_RCVD_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"STAT_NUM_FCH_DSC_RCVD_DSC_CNT", (reg_val &
	STAT_NUM_FCH_DSC_RCVD_DSC_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_stat_num_byp_dsc_rcvd_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,11]      0x%x\n",
	"STAT_NUM_BYP_DSC_RCVD_RSVD_1", (reg_val &
	STAT_NUM_BYP_DSC_RCVD_RSVD_1_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"STAT_NUM_BYP_DSC_RCVD_DSC_CNT", (reg_val &
	STAT_NUM_BYP_DSC_RCVD_DSC_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_wrb_coal_cfg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,26]      0x%x\n",
	"C2H_WRB_COAL_CFG_MAX_BUF_SZ", (reg_val &
	C2H_WRB_COAL_CFG_MAX_BUF_SZ_MASK) >> 26);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [25,14]      0x%x\n",
	"C2H_WRB_COAL_CFG_TICK_VAL", (reg_val &
	C2H_WRB_COAL_CFG_TICK_VAL_MASK) >> 14);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [13,2 ]      0x%x\n",
	"C2H_WRB_COAL_CFG_TICK_CNT", (reg_val &
	C2H_WRB_COAL_CFG_TICK_CNT_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"C2H_WRB_COAL_CFG_SET_GLB_FLUSH", (reg_val &
	C2H_WRB_COAL_CFG_SET_GLB_FLUSH_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"C2H_WRB_COAL_CFG_DONE_GLB_FLUSH", (reg_val &
	C2H_WRB_COAL_CFG_DONE_GLB_FLUSH_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_intr_h2c_req_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_H2C_REQ_RSVD_1", (reg_val &
	C2H_INTR_H2C_REQ_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_INTR_H2C_REQ_CNT", (reg_val &
	C2H_INTR_H2C_REQ_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_intr_c2h_mm_req_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_C2H_MM_REQ_RSVD_1", (reg_val &
	C2H_INTR_C2H_MM_REQ_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_INTR_C2H_MM_REQ_CNT", (reg_val &
	C2H_INTR_C2H_MM_REQ_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_intr_err_int_req_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_ERR_INT_REQ_RSVD_1", (reg_val &
	C2H_INTR_ERR_INT_REQ_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_INTR_ERR_INT_REQ_CNT", (reg_val &
	C2H_INTR_ERR_INT_REQ_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_intr_c2h_st_req_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_C2H_ST_REQ_RSVD_1", (reg_val &
	C2H_INTR_C2H_ST_REQ_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_INTR_C2H_ST_REQ_CNT", (reg_val &
	C2H_INTR_C2H_ST_REQ_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_intr_h2c_err_c2h_mm_msix_ack_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_H2C_ERR_C2H_MM_MSIX_ACK_RSVD_1", (reg_val &
	C2H_INTR_H2C_ERR_C2H_MM_MSIX_ACK_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_INTR_H2C_ERR_C2H_MM_MSIX_ACK_CNT", (reg_val &
	C2H_INTR_H2C_ERR_C2H_MM_MSIX_ACK_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_intr_h2c_err_c2h_mm_msix_fail_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_H2C_ERR_C2H_MM_MSIX_FAIL_RSVD_1", (reg_val &
	C2H_INTR_H2C_ERR_C2H_MM_MSIX_FAIL_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_INTR_H2C_ERR_C2H_MM_MSIX_FAIL_CNT", (reg_val &
	C2H_INTR_H2C_ERR_C2H_MM_MSIX_FAIL_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_intr_h2c_err_c2h_mm_msix_no_msix_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_H2C_ERR_C2H_MM_MSIX_NO_MSIX_RSVD_1", (reg_val &
	C2H_INTR_H2C_ERR_C2H_MM_MSIX_NO_MSIX_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_INTR_H2C_ERR_C2H_MM_MSIX_NO_MSIX_CNT", (reg_val &
	C2H_INTR_H2C_ERR_C2H_MM_MSIX_NO_MSIX_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_intr_h2c_err_c2h_mm_ctxt_inval_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_H2C_ERR_C2H_MM_CTXT_INVAL_RSVD_1", (reg_val &
	C2H_INTR_H2C_ERR_C2H_MM_CTXT_INVAL_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_INTR_H2C_ERR_C2H_MM_CTXT_INVAL_CNT", (reg_val &
	C2H_INTR_H2C_ERR_C2H_MM_CTXT_INVAL_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_intr_c2h_st_msix_ack_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_C2H_ST_MSIX_ACK_RSVD_1", (reg_val &
	C2H_INTR_C2H_ST_MSIX_ACK_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_INTR_C2H_ST_MSIX_ACK_CNT", (reg_val &
	C2H_INTR_C2H_ST_MSIX_ACK_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_intr_c2h_st_msix_fail_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_C2H_ST_MSIX_FAIL_RSVD_1", (reg_val &
	C2H_INTR_C2H_ST_MSIX_FAIL_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_INTR_C2H_ST_MSIX_FAIL_CNT", (reg_val &
	C2H_INTR_C2H_ST_MSIX_FAIL_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_intr_c2h_st_no_msix_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_C2H_ST_NO_MSIX_RSVD_1", (reg_val &
	C2H_INTR_C2H_ST_NO_MSIX_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_INTR_C2H_ST_NO_MSIX_CNT", (reg_val &
	C2H_INTR_C2H_ST_NO_MSIX_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_intr_c2h_st_ctxt_inval_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_C2H_ST_CTXT_INVAL_RSVD_1", (reg_val &
	C2H_INTR_C2H_ST_CTXT_INVAL_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_INTR_C2H_ST_CTXT_INVAL_CNT", (reg_val &
	C2H_INTR_C2H_ST_CTXT_INVAL_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_wr_cmp_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_STAT_WR_CMP_RSVD_1", (reg_val &
	C2H_STAT_WR_CMP_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_STAT_WR_CMP_CNT", (reg_val &
	C2H_STAT_WR_CMP_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_dbg_dma_eng_4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"C2H_STAT_DMA_ENG_4_TUSER_FIFO_OUT_VLD", (reg_val &
	C2H_STAT_DMA_ENG_4_TUSER_FIFO_OUT_VLD_MASK) >> 31);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [30   ]      0x%x\n",
	"C2H_STAT_DMA_ENG_4_WRB_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_4_WRB_FIFO_IN_RDY_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29,20]      0x%x\n",
	"C2H_STAT_DMA_ENG_4_TUSER_FIFO_IN_CNT", (reg_val &
	C2H_STAT_DMA_ENG_4_TUSER_FIFO_IN_CNT_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19,10]      0x%x\n",
	"C2H_STAT_DMA_ENG_4_TUSER_FIFO_OUTPUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_4_TUSER_FIFO_OUTPUT_CNT_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,0 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_4_TUSER_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_4_TUSER_FIFO_OUT_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_dbg_dma_eng_5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,25]      0x%x\n",
	"C2H_STAT_DMA_ENG_5_RSVD_1", (reg_val &
	C2H_STAT_DMA_ENG_5_RSVD_1_MASK) >> 25);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [24   ]      0x%x\n",
	"C2H_STAT_DMA_ENG_5_TUSER_COMB_OUT_VLD", (reg_val &
	C2H_STAT_DMA_ENG_5_TUSER_COMB_OUT_VLD_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23   ]      0x%x\n",
	"C2H_STAT_DMA_ENG_5_TUSER_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_5_TUSER_FIFO_IN_RDY_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,13]      0x%x\n",
	"C2H_STAT_DMA_ENG_5_TUSER_COMB_IN_CNT", (reg_val &
	C2H_STAT_DMA_ENG_5_TUSER_COMB_IN_CNT_MASK) >> 13);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [12,3 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_5_TUSE_COMB_OUTPUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_5_TUSE_COMB_OUTPUT_CNT_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2 ,0 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_5_TUSER_COMB_CNT", (reg_val &
	C2H_STAT_DMA_ENG_5_TUSER_COMB_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_dbg_pfch_qid_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,15]      0x%x\n",
	"C2H_PFCH_QID_RSVD_1", (reg_val &
	C2H_PFCH_QID_RSVD_1_MASK) >> 15);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [14   ]      0x%x\n",
	"C2H_PFCH_QID_ERR_CTXT", (reg_val &
	C2H_PFCH_QID_ERR_CTXT_MASK) >> 14);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [13,11]      0x%x\n",
	"C2H_PFCH_QID_TARGET", (reg_val &
	C2H_PFCH_QID_TARGET_MASK) >> 11);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [10,0 ]      0x%x\n",
	"C2H_PFCH_QID_QID_OR_TAG", (reg_val &
	C2H_PFCH_QID_QID_OR_TAG_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_dbg_pfch_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_PFCH_DAT", (reg_val &
	C2H_PFCH_DATA_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_int_dbg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_INT_RSVD_1", (reg_val &
	C2H_INT_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,4 ]      0x%x\n",
	"C2H_INT_INT_COAL", (reg_val &
	C2H_INT_INT_COAL_SM_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3 ,0 ]      0x%x\n",
	"C2H_INT_INT", (reg_val &
	C2H_INT_INT_SM_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_imm_accepted_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_STAT_IMM_ACCEPTED_RSVD_1", (reg_val &
	C2H_STAT_IMM_ACCEPTED_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_STAT_IMM_ACCEPTED_CNT", (reg_val &
	C2H_STAT_IMM_ACCEPTED_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_marker_accepted_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_STAT_MARKER_ACCEPTED_RSVD_1", (reg_val &
	C2H_STAT_MARKER_ACCEPTED_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_STAT_MARKER_ACCEPTED_CNT", (reg_val &
	C2H_STAT_MARKER_ACCEPTED_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_stat_disable_cmp_accepted_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_STAT_DISABLE_CMP_ACCEPTED_RSVD_1", (reg_val &
	C2H_STAT_DISABLE_CMP_ACCEPTED_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_STAT_DISABLE_CMP_ACCEPTED_CNT", (reg_val &
	C2H_STAT_DISABLE_CMP_ACCEPTED_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_pld_fifo_crdt_cnt_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_PLD_FIFO_CRDT_CNT_RSVD_1", (reg_val &
	C2H_PLD_FIFO_CRDT_CNT_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,0 ]      0x%x\n",
	"C2H_PLD_FIFO_CRDT_CNT_CNT", (reg_val &
	C2H_PLD_FIFO_CRDT_CNT_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_err_stat_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,5 ]      0x%x\n",
	"H2C_ERR_STAT_RSVD_1", (reg_val &
	H2C_ERR_STAT_RSVD_1_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4    ]      0x%x\n",
	"H2C_ERR_STAT_SBE", (reg_val &
	H2C_ERR_STAT_SBE_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3    ]      0x%x\n",
	"H2C_ERR_STAT_DBE", (reg_val &
	H2C_ERR_STAT_DBE_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"H2C_ERR_STAT_NO_DMA_D", (reg_val &
	H2C_ERR_STAT_NO_DMA_DS_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"H2C_ERR_STAT_SDI_MRKR_REQ_MOP_ERR", (reg_val &
	H2C_ERR_STAT_SDI_MRKR_REQ_MOP_ERR_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"H2C_ERR_STAT_ZERO_LEN_D", (reg_val &
	H2C_ERR_STAT_ZERO_LEN_DS_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_err_mask_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"H2C_ERR_EN", (reg_val &
	H2C_ERR_EN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_first_err_qid_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,20]      0x%x\n",
	"H2C_FIRST_ERR_QID_RSVD_1", (reg_val &
	H2C_FIRST_ERR_QID_RSVD_1_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19,16]      0x%x\n",
	"H2C_FIRST_ERR_QID_ERR_TYPE", (reg_val &
	H2C_FIRST_ERR_QID_ERR_TYPE_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,12]      0x%x\n",
	"H2C_FIRST_ERR_QID_RSVD_2", (reg_val &
	H2C_FIRST_ERR_QID_RSVD_2_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,0 ]      0x%x\n",
	"H2C_FIRST_ERR_QID_QID", (reg_val &
	H2C_FIRST_ERR_QID_QID_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_dbg_reg0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"H2C_REG0_NUM_DSC_RCVD", (reg_val &
	H2C_REG0_NUM_DSC_RCVD_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"H2C_REG0_NUM_WRB_SENT", (reg_val &
	H2C_REG0_NUM_WRB_SENT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_dbg_reg1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"H2C_REG1_NUM_REQ_SENT", (reg_val &
	H2C_REG1_NUM_REQ_SENT_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"H2C_REG1_NUM_CMP_SENT", (reg_val &
	H2C_REG1_NUM_CMP_SENT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_dbg_reg2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"H2C_REG2_RSVD_1", (reg_val &
	H2C_REG2_RSVD_1_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"H2C_REG2_NUM_ERR_DSC_RCVD", (reg_val &
	H2C_REG2_NUM_ERR_DSC_RCVD_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_dbg_reg3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"H2C_REG3_DBG", (reg_val &
	H2C_REG3_MASK) >> 31);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [30   ]      0x%x\n",
	"H2C_REG3_DSCO_FIFO_EMPTY", (reg_val &
	H2C_REG3_DSCO_FIFO_EMPTY_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29   ]      0x%x\n",
	"H2C_REG3_DSCO_FIFO_FULL", (reg_val &
	H2C_REG3_DSCO_FIFO_FULL_MASK) >> 29);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [28,26]      0x%x\n",
	"H2C_REG3_CUR_RC_STATE", (reg_val &
	H2C_REG3_CUR_RC_STATE_MASK) >> 26);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [25,16]      0x%x\n",
	"H2C_REG3_RDREQ_LINE", (reg_val &
	H2C_REG3_RDREQ_LINES_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,6 ]      0x%x\n",
	"H2C_REG3_RDATA_LINES_AVAIL", (reg_val &
	H2C_REG3_RDATA_LINES_AVAIL_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5    ]      0x%x\n",
	"H2C_REG3_PEND_FIFO_EMPTY", (reg_val &
	H2C_REG3_PEND_FIFO_EMPTY_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4    ]      0x%x\n",
	"H2C_REG3_PEND_FIFO_FULL", (reg_val &
	H2C_REG3_PEND_FIFO_FULL_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3 ,2 ]      0x%x\n",
	"H2C_REG3_CUR_RQ_STATE", (reg_val &
	H2C_REG3_CUR_RQ_STATE_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"H2C_REG3_DSCI_FIFO_FULL", (reg_val &
	H2C_REG3_DSCI_FIFO_FULL_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"H2C_REG3_DSCI_FIFO_EMPTY", (reg_val &
	H2C_REG3_DSCI_FIFO_EMPTY_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_dbg_reg4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"H2C_REG4_RDREQ_ADDR", (reg_val &
	H2C_REG4_RDREQ_ADDR_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_fatal_err_en_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,1 ]      0x%x\n",
	"H2C_FATAL_ERR_EN_RSVD_1", (reg_val &
	H2C_FATAL_ERR_EN_RSVD_1_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"H2C_FATAL_ERR_EN_H2C", (reg_val &
	H2C_FATAL_ERR_EN_H2C_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_channel_ctl_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,1 ]      0x%x\n",
	"C2H_CHANNEL_CTL_RSVD_1", (reg_val &
	C2H_CHANNEL_CTL_RSVD_1_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"C2H_CHANNEL_CTL_RUN", (reg_val &
	C2H_CHANNEL_CTL_RUN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_channel_ctl_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,1 ]      0x%x\n",
	"C2H_CHANNEL_CTL_1_RUN", (reg_val &
	C2H_CHANNEL_CTL_1_RUN_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"C2H_CHANNEL_CTL_1_RUN_1", (reg_val &
	C2H_CHANNEL_CTL_1_RUN_1_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_mm_status_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,1 ]      0x%x\n",
	"C2H_MM_STATUS_RSVD_1", (reg_val &
	C2H_MM_STATUS_RSVD_1_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"C2H_MM_STATUS_RUN", (reg_val &
	C2H_MM_STATUS_RUN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_channel_cmpl_desc_cnt_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_CHANNEL_CMPL_DESC_CNT_C2H_CO", (reg_val &
	C2H_CHANNEL_CMPL_DESC_CNT_C2H_CO_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_mm_err_code_enable_mask_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"C2H_MM_ERR_CODE_ENABLE_RSVD_1", (reg_val &
	C2H_MM_ERR_CODE_ENABLE_RSVD_1_MASK) >> 31);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [30   ]      0x%x\n",
	"C2H_MM_ERR_CODE_ENABLE_WR_UC_R", (reg_val &
	C2H_MM_ERR_CODE_ENABLE_WR_UC_RAM_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29   ]      0x%x\n",
	"C2H_MM_ERR_CODE_ENABLE_WR_UR", (reg_val &
	C2H_MM_ERR_CODE_ENABLE_WR_UR_MASK) >> 29);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [28   ]      0x%x\n",
	"C2H_MM_ERR_CODE_ENABLE_WR_FLR", (reg_val &
	C2H_MM_ERR_CODE_ENABLE_WR_FLR_MASK) >> 28);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [27,2 ]      0x%x\n",
	"C2H_MM_ERR_CODE_ENABLE_RSVD_2", (reg_val &
	C2H_MM_ERR_CODE_ENABLE_RSVD_2_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"C2H_MM_ERR_CODE_ENABLE_RD_SLV_ERR", (reg_val &
	C2H_MM_ERR_CODE_ENABLE_RD_SLV_ERR_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"C2H_MM_ERR_CODE_ENABLE_WR_SLV_ERR", (reg_val &
	C2H_MM_ERR_CODE_ENABLE_WR_SLV_ERR_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_mm_err_code_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_MM_ERR_CODE_RSVD_1", (reg_val &
	C2H_MM_ERR_CODE_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17   ]      0x%x\n",
	"C2H_MM_ERR_CODE_VALID", (reg_val &
	C2H_MM_ERR_CODE_VALID_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"C2H_MM_ERR_CODE_RDWR", (reg_val &
	C2H_MM_ERR_CODE_RDWR_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4 ,0 ]      0x%x\n",
	"C2H_MM_ERR_CODE", (reg_val &
	C2H_MM_ERR_CODE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_mm_err_info_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,29]      0x%x\n",
	"C2H_MM_ERR_INFO_RSVD_1", (reg_val &
	C2H_MM_ERR_INFO_RSVD_1_MASK) >> 29);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [28,17]      0x%x\n",
	"C2H_MM_ERR_INFO_QID", (reg_val &
	C2H_MM_ERR_INFO_QID_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"C2H_MM_ERR_INFO_DIR", (reg_val &
	C2H_MM_ERR_INFO_DIR_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"C2H_MM_ERR_INFO_CIDX", (reg_val &
	C2H_MM_ERR_INFO_CIDX_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_mm_perf_mon_ctl_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,4 ]      0x%x\n",
	"C2H_MM_PERF_MON_CTL_RSVD_1", (reg_val &
	C2H_MM_PERF_MON_CTL_RSVD_1_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3    ]      0x%x\n",
	"C2H_MM_PERF_MON_CTL_IMM_START", (reg_val &
	C2H_MM_PERF_MON_CTL_IMM_START_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"C2H_MM_PERF_MON_CTL_RUN_START", (reg_val &
	C2H_MM_PERF_MON_CTL_RUN_START_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"C2H_MM_PERF_MON_CTL_IMM_CLEAR", (reg_val &
	C2H_MM_PERF_MON_CTL_IMM_CLEAR_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"C2H_MM_PERF_MON_CTL_RUN_CLEAR", (reg_val &
	C2H_MM_PERF_MON_CTL_RUN_CLEAR_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_mm_perf_mon_cycle_cnt0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_MM_PERF_MON_CYCLE_CNT0_CYC_CNT", (reg_val &
	C2H_MM_PERF_MON_CYCLE_CNT0_CYC_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_mm_perf_mon_cycle_cnt1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,10]      0x%x\n",
	"C2H_MM_PERF_MON_CYCLE_CNT1_RSVD_1", (reg_val &
	C2H_MM_PERF_MON_CYCLE_CNT1_RSVD_1_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,0 ]      0x%x\n",
	"C2H_MM_PERF_MON_CYCLE_CNT1_CYC_CNT", (reg_val &
	C2H_MM_PERF_MON_CYCLE_CNT1_CYC_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_mm_perf_mon_data_cnt0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_MM_PERF_MON_DATA_CNT0_DCNT", (reg_val &
	C2H_MM_PERF_MON_DATA_CNT0_DCNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_mm_perf_mon_data_cnt1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,10]      0x%x\n",
	"C2H_MM_PERF_MON_DATA_CNT1_RSVD_1", (reg_val &
	C2H_MM_PERF_MON_DATA_CNT1_RSVD_1_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,0 ]      0x%x\n",
	"C2H_MM_PERF_MON_DATA_CNT1_DCNT", (reg_val &
	C2H_MM_PERF_MON_DATA_CNT1_DCNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_c2h_mm_dbg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,24]      0x%x\n",
	"C2H_MM_RSVD_1", (reg_val &
	C2H_MM_RSVD_1_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,17]      0x%x\n",
	"C2H_MM_RRQ_ENTRIE", (reg_val &
	C2H_MM_RRQ_ENTRIES_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16,7 ]      0x%x\n",
	"C2H_MM_DAT_FIFO_SPC", (reg_val &
	C2H_MM_DAT_FIFO_SPC_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6    ]      0x%x\n",
	"C2H_MM_RD_STALL", (reg_val &
	C2H_MM_RD_STALL_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5    ]      0x%x\n",
	"C2H_MM_RRQ_FIFO_FI", (reg_val &
	C2H_MM_RRQ_FIFO_FI_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4    ]      0x%x\n",
	"C2H_MM_WR_STALL", (reg_val &
	C2H_MM_WR_STALL_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3    ]      0x%x\n",
	"C2H_MM_WRQ_FIFO_FI", (reg_val &
	C2H_MM_WRQ_FIFO_FI_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"C2H_MM_WBK_STALL", (reg_val &
	C2H_MM_WBK_STALL_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"C2H_MM_DSC_FIFO_EP", (reg_val &
	C2H_MM_DSC_FIFO_EP_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"C2H_MM_DSC_FIFO_FL", (reg_val &
	C2H_MM_DSC_FIFO_FL_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_channel_ctl_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,1 ]      0x%x\n",
	"H2C_CHANNEL_CTL_RSVD_1", (reg_val &
	H2C_CHANNEL_CTL_RSVD_1_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"H2C_CHANNEL_CTL_RUN", (reg_val &
	H2C_CHANNEL_CTL_RUN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_channel_ctl_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"H2C_CHANNEL_CTL_1_RUN", (reg_val &
	H2C_CHANNEL_CTL_1_RUN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_channel_ctl_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"H2C_CHANNEL_CTL_2_RUN", (reg_val &
	H2C_CHANNEL_CTL_2_RUN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_mm_status_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,1 ]      0x%x\n",
	"H2C_MM_STATUS_RSVD_1", (reg_val &
	H2C_MM_STATUS_RSVD_1_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"H2C_MM_STATUS_RUN", (reg_val &
	H2C_MM_STATUS_RUN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_channel_cmpl_desc_cnt_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"H2C_CHANNEL_CMPL_DESC_CNT_H2C_CO", (reg_val &
	H2C_CHANNEL_CMPL_DESC_CNT_H2C_CO_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_mm_err_code_enable_mask_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,30]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RSVD_1", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RSVD_1_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29   ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_WR_SLV_ERR", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_WR_SLV_ERR_MASK) >> 29);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [28   ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_WR_DEC_ERR", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_WR_DEC_ERR_MASK) >> 28);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [27,23]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RSVD_2", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RSVD_2_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22   ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RD_RQ_DIS_ERR", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RD_RQ_DIS_ERR_MASK) >> 22);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [21,17]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RSVD_3", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RSVD_3_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RD_DAT_POISON_ERR", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RD_DAT_POISON_ERR_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,9 ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RSVD_4", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RSVD_4_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8    ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RD_FLR_ERR", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RD_FLR_ERR_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,6 ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RSVD_5", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RSVD_5_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5    ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RD_HDR_ADR_ERR", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RD_HDR_ADR_ERR_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4    ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RD_HDR_PAR", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RD_HDR_PARA_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3    ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RD_HDR_BYTE_ERR", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RD_HDR_BYTE_ERR_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RD_UR_C", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RD_UR_CA_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RD_HRD_POISON_ERR", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RD_HRD_POISON_ERR_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RSVD_6", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RSVD_6_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_mm_err_code_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"H2C_MM_ERR_CODE_RSVD_1", (reg_val &
	H2C_MM_ERR_CODE_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17   ]      0x%x\n",
	"H2C_MM_ERR_CODE_VALID", (reg_val &
	H2C_MM_ERR_CODE_VALID_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"H2C_MM_ERR_CODE_RDWR", (reg_val &
	H2C_MM_ERR_CODE_RDWR_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4 ,0 ]      0x%x\n",
	"H2C_MM_ERR_CODE", (reg_val &
	H2C_MM_ERR_CODE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_mm_err_info_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,29]      0x%x\n",
	"H2C_MM_ERR_INFO_RSVD_1", (reg_val &
	H2C_MM_ERR_INFO_RSVD_1_MASK) >> 29);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [28,17]      0x%x\n",
	"H2C_MM_ERR_INFO_QID", (reg_val &
	H2C_MM_ERR_INFO_QID_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16   ]      0x%x\n",
	"H2C_MM_ERR_INFO_DIR", (reg_val &
	H2C_MM_ERR_INFO_DIR_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"H2C_MM_ERR_INFO_CIDX", (reg_val &
	H2C_MM_ERR_INFO_CIDX_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_mm_perf_mon_ctl_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,4 ]      0x%x\n",
	"H2C_MM_PERF_MON_CTL_RSVD_1", (reg_val &
	H2C_MM_PERF_MON_CTL_RSVD_1_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3    ]      0x%x\n",
	"H2C_MM_PERF_MON_CTL_IMM_START", (reg_val &
	H2C_MM_PERF_MON_CTL_IMM_START_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"H2C_MM_PERF_MON_CTL_RUN_START", (reg_val &
	H2C_MM_PERF_MON_CTL_RUN_START_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"H2C_MM_PERF_MON_CTL_IMM_CLEAR", (reg_val &
	H2C_MM_PERF_MON_CTL_IMM_CLEAR_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"H2C_MM_PERF_MON_CTL_RUN_CLEAR", (reg_val &
	H2C_MM_PERF_MON_CTL_RUN_CLEAR_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_mm_perf_mon_cycle_cnt0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"H2C_MM_PERF_MON_CYCLE_CNT0_CYC_CNT", (reg_val &
	H2C_MM_PERF_MON_CYCLE_CNT0_CYC_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_mm_perf_mon_cycle_cnt1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,10]      0x%x\n",
	"H2C_MM_PERF_MON_CYCLE_CNT1_RSVD_1", (reg_val &
	H2C_MM_PERF_MON_CYCLE_CNT1_RSVD_1_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,0 ]      0x%x\n",
	"H2C_MM_PERF_MON_CYCLE_CNT1_CYC_CNT", (reg_val &
	H2C_MM_PERF_MON_CYCLE_CNT1_CYC_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_mm_perf_mon_data_cnt0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"H2C_MM_PERF_MON_DATA_CNT0_DCNT", (reg_val &
	H2C_MM_PERF_MON_DATA_CNT0_DCNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_mm_perf_mon_data_cnt1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,10]      0x%x\n",
	"H2C_MM_PERF_MON_DATA_CNT1_RSVD_1", (reg_val &
	H2C_MM_PERF_MON_DATA_CNT1_RSVD_1_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,0 ]      0x%x\n",
	"H2C_MM_PERF_MON_DATA_CNT1_DCNT", (reg_val &
	H2C_MM_PERF_MON_DATA_CNT1_DCNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_h2c_mm_dbg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,24]      0x%x\n",
	"H2C_MM_RSVD_1", (reg_val &
	H2C_MM_RSVD_1_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,17]      0x%x\n",
	"H2C_MM_RRQ_ENTRIE", (reg_val &
	H2C_MM_RRQ_ENTRIES_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16,7 ]      0x%x\n",
	"H2C_MM_DAT_FIFO_SPC", (reg_val &
	H2C_MM_DAT_FIFO_SPC_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6    ]      0x%x\n",
	"H2C_MM_RD_STALL", (reg_val &
	H2C_MM_RD_STALL_MASK) >> 6);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [5    ]      0x%x\n",
	"H2C_MM_RRQ_FIFO_FI", (reg_val &
	H2C_MM_RRQ_FIFO_FI_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4    ]      0x%x\n",
	"H2C_MM_WR_STALL", (reg_val &
	H2C_MM_WR_STALL_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [3    ]      0x%x\n",
	"H2C_MM_WRQ_FIFO_FI", (reg_val &
	H2C_MM_WRQ_FIFO_FI_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"H2C_MM_WBK_STALL", (reg_val &
	H2C_MM_WBK_STALL_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"H2C_MM_DSC_FIFO_EP", (reg_val &
	H2C_MM_DSC_FIFO_EP_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"H2C_MM_DSC_FIFO_FL", (reg_val &
	H2C_MM_DSC_FIFO_FL_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_func_status_reg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,12]      0x%x\n",
	"FUNC_STATUS_REG_RSVD_1", (reg_val &
	FUNC_STATUS_REG_RSVD_1_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,4 ]      0x%x\n",
	"FUNC_STATUS_REG_CUR_SRC_FN", (reg_val &
	FUNC_STATUS_REG_CUR_SRC_FN_MASK) >> 4);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"FUNC_STATUS_REG_AC", (reg_val &
	FUNC_STATUS_REG_ACK_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"FUNC_STATUS_REG_O_MSG", (reg_val &
	FUNC_STATUS_REG_O_MSG_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"FUNC_STATUS_REG_I_MSG", (reg_val &
	FUNC_STATUS_REG_I_MSG_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_func_cmd_reg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,3 ]      0x%x\n",
	"FUNC_CMD_REG_RSVD_1", (reg_val &
	FUNC_CMD_REG_RSVD_1_MASK) >> 3);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [2    ]      0x%x\n",
	"FUNC_CMD_REG_RSVD_2", (reg_val &
	FUNC_CMD_REG_RSVD_2_MASK) >> 2);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [1    ]      0x%x\n",
	"FUNC_CMD_REG_MSG_RCV", (reg_val &
	FUNC_CMD_REG_MSG_RCV_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"FUNC_CMD_REG_MSG_SENT", (reg_val &
	FUNC_CMD_REG_MSG_SENT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_func_interrupt_vector_reg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,5 ]      0x%x\n",
	"FUNC_INTERRUPT_VECTOR_REG_RSVD_1", (reg_val &
	FUNC_INTERRUPT_VECTOR_REG_RSVD_1_MASK) >> 5);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [4 ,0 ]      0x%x\n",
	"FUNC_INTERRUPT_VECTOR_REG_IN", (reg_val &
	FUNC_INTERRUPT_VECTOR_REG_IN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_target_func_reg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"TARGET_FUNC_REG_RSVD_1", (reg_val &
	TARGET_FUNC_REG_RSVD_1_MASK) >> 8);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [7 ,0 ]      0x%x\n",
	"TARGET_FUNC_REG_N_ID", (reg_val &
	TARGET_FUNC_REG_N_ID_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int qdma_s80_hard_func_interrupt_ctl_reg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,1 ]      0x%x\n",
	"FUNC_INTERRUPT_CTL_REG_RSVD_1", (reg_val &
	FUNC_INTERRUPT_CTL_REG_RSVD_1_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [0    ]      0x%x\n",
	"FUNC_INTERRUPT_CTL_REG_INT_EN", (reg_val &
	FUNC_INTERRUPT_CTL_REG_INT_EN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}

struct xreg_info qdma_s80_hard_config_regs[] = {
{"CFG_BLK_IDENTIFIER", 0x00,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_identifier_info_dump },
{"CFG_BLK_BUSDEV", 0x04,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_busdev_info_dump },
{"CFG_BLK_PCIE_MAX_PLD_SIZE", 0x08,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_pcie_max_pld_size_info_dump },
{"CFG_BLK_PCIE_MAX_READ_REQ_SIZE", 0x0c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_pcie_max_read_req_size_info_dump },
{"CFG_BLK_SYSTEM_ID", 0x10,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_system_id_info_dump },
{"CFG_BLK_MSI_ENABLE", 0x014,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_msi_enable_info_dump },
{"CFG_PCIE_DATA_WIDTH", 0x18,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_pcie_data_width_info_dump },
{"CFG_PCIE_CTL", 0x1c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_pcie_ctl_info_dump },
{"CFG_AXI_USER_MAX_PLD_SIZE", 0x40,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_axi_user_max_pld_size_info_dump },
{"CFG_AXI_USER_MAX_READ_REQ_SIZE", 0x44,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_axi_user_max_read_req_size_info_dump },
{"CFG_BLK_MISC_CTL", 0x4c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_misc_ctl_info_dump },
{"CFG_BLK_SCRATCH_0", 0x80,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_scratch_0_info_dump },
{"CFG_BLK_SCRATCH_1", 0x84,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_scratch_1_info_dump },
{"CFG_BLK_SCRATCH_2", 0x88,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_scratch_2_info_dump },
{"CFG_BLK_SCRATCH_3", 0x8c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_scratch_3_info_dump },
{"CFG_BLK_SCRATCH_4", 0x90,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_scratch_4_info_dump },
{"CFG_BLK_SCRATCH_5", 0x94,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_scratch_5_info_dump },
{"CFG_BLK_SCRATCH_6", 0x98,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_scratch_6_info_dump },
{"CFG_BLK_SCRATCH_7", 0x9c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_cfg_blk_scratch_7_info_dump },
{"RAM_SBE_MSK_A", 0xf0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ram_sbe_msk_a_info_dump },
{"RAM_SBE_STS_A", 0xf4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ram_sbe_sts_a_info_dump },
{"RAM_DBE_MSK_A", 0xf8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ram_dbe_msk_a_info_dump },
{"RAM_DBE_STS_A", 0xfc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ram_dbe_sts_a_info_dump },
{"GLBL2_IDENTIFIER", 0x100,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_identifier_info_dump },
{"GLBL2_PF_BARLITE_INT", 0x104,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_pf_barlite_int_info_dump },
{"GLBL2_PF_VF_BARLITE_INT", 0x108,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_pf_vf_barlite_int_info_dump },
{"GLBL2_PF_BARLITE_EXT", 0x10c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_pf_barlite_ext_info_dump },
{"GLBL2_PF_VF_BARLITE_EXT", 0x110,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_pf_vf_barlite_ext_info_dump },
{"GLBL2_CHANNEL_INST", 0x114,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_channel_inst_info_dump },
{"GLBL2_CHANNEL_MDMA", 0x118,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_channel_mdma_info_dump },
{"GLBL2_CHANNEL_STRM", 0x11c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_channel_strm_info_dump },
{"GLBL2_CHANNEL_CAP", 0x120,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_channel_cap_info_dump },
{"GLBL2_CHANNEL_PASID_CAP", 0x128,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_channel_pasid_cap_info_dump },
{"GLBL2_CHANNEL_FUNC_RET", 0x12c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_channel_func_ret_info_dump },
{"GLBL2_SYSTEM_ID", 0x130,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_system_id_info_dump },
{"GLBL2_MISC_CAP", 0x134,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_misc_cap_info_dump },
{"GLBL2_DBG_PCIE_RQ0", 0x1b8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_dbg_pcie_rq0_info_dump },
{"GLBL2_DBG_PCIE_RQ1", 0x1bc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_dbg_pcie_rq1_info_dump },
{"GLBL2_DBG_AXIMM_WR0", 0x1c0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_dbg_aximm_wr0_info_dump },
{"GLBL2_DBG_AXIMM_WR1", 0x1c4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_dbg_aximm_wr1_info_dump },
{"GLBL2_DBG_AXIMM_RD0", 0x1c8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_dbg_aximm_rd0_info_dump },
{"GLBL2_DBG_AXIMM_RD1", 0x1cc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_glbl2_dbg_aximm_rd1_info_dump },
{"GLBL_RNG_SZ_1", 0x204,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_1_info_dump },
{"GLBL_RNG_SZ_2", 0x208,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_2_info_dump },
{"GLBL_RNG_SZ_3", 0x20c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_3_info_dump },
{"GLBL_RNG_SZ_4", 0x210,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_4_info_dump },
{"GLBL_RNG_SZ_5", 0x214,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_5_info_dump },
{"GLBL_RNG_SZ_6", 0x218,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_6_info_dump },
{"GLBL_RNG_SZ_7", 0x21c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_7_info_dump },
{"GLBL_RNG_SZ_8", 0x220,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_8_info_dump },
{"GLBL_RNG_SZ_9", 0x224,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_9_info_dump },
{"GLBL_RNG_SZ_A", 0x228,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_a_info_dump },
{"GLBL_RNG_SZ_B", 0x22c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_b_info_dump },
{"GLBL_RNG_SZ_C", 0x230,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_c_info_dump },
{"GLBL_RNG_SZ_D", 0x234,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_d_info_dump },
{"GLBL_RNG_SZ_E", 0x238,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_e_info_dump },
{"GLBL_RNG_SZ_F", 0x23c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_f_info_dump },
{"GLBL_RNG_SZ_10", 0x240,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_rng_sz_10_info_dump },
{"GLBL_ERR_STAT", 0x248,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_err_stat_info_dump },
{"GLBL_ERR_MASK", 0x24c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_err_mask_info_dump },
{"GLBL_DSC_CFG", 0x250,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_dsc_cfg_info_dump },
{"GLBL_DSC_ERR_STS", 0x254,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_dsc_err_sts_info_dump },
{"GLBL_DSC_ERR_MSK", 0x258,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_dsc_err_msk_info_dump },
{"GLBL_DSC_ERR_LOG0", 0x25c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_dsc_err_log0_info_dump },
{"GLBL_DSC_ERR_LOG1", 0x260,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_dsc_err_log1_info_dump },
{"GLBL_TRQ_ERR_STS", 0x264,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_trq_err_sts_info_dump },
{"GLBL_TRQ_ERR_MSK", 0x268,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_trq_err_msk_info_dump },
{"GLBL_TRQ_ERR_LOG", 0x26c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_trq_err_log_info_dump },
{"GLBL_DSC_DBG_DAT0", 0x270,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_dsc_dbg_dat0_info_dump },
{"GLBL_DSC_DBG_DAT1", 0x274,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_dsc_dbg_dat1_info_dump },
{"TRQ_SEL_FMAP_0", 0x400,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_0_info_dump },
{"TRQ_SEL_FMAP_1", 0x404,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_1_info_dump },
{"TRQ_SEL_FMAP_2", 0x408,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_2_info_dump },
{"TRQ_SEL_FMAP_3", 0x40c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_3_info_dump },
{"TRQ_SEL_FMAP_4", 0x410,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_4_info_dump },
{"TRQ_SEL_FMAP_5", 0x414,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_5_info_dump },
{"TRQ_SEL_FMAP_6", 0x418,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_6_info_dump },
{"TRQ_SEL_FMAP_7", 0x41c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_7_info_dump },
{"TRQ_SEL_FMAP_8", 0x420,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_8_info_dump },
{"TRQ_SEL_FMAP_9", 0x424,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_9_info_dump },
{"TRQ_SEL_FMAP_A", 0x428,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_a_info_dump },
{"TRQ_SEL_FMAP_B", 0x42c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_b_info_dump },
{"TRQ_SEL_FMAP_D", 0x430,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_d_info_dump },
{"TRQ_SEL_FMAP_E", 0x434,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_e_info_dump },
{"TRQ_SEL_FMAP_F", 0x438,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_f_info_dump },
{"TRQ_SEL_FMAP_10", 0x43c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_10_info_dump },
{"TRQ_SEL_FMAP_11", 0x440,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_11_info_dump },
{"TRQ_SEL_FMAP_12", 0x444,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_12_info_dump },
{"TRQ_SEL_FMAP_13", 0x448,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_13_info_dump },
{"TRQ_SEL_FMAP_14", 0x44c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_14_info_dump },
{"TRQ_SEL_FMAP_15", 0x450,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_15_info_dump },
{"TRQ_SEL_FMAP_16", 0x454,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_16_info_dump },
{"TRQ_SEL_FMAP_17", 0x458,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_17_info_dump },
{"TRQ_SEL_FMAP_18", 0x45c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_18_info_dump },
{"TRQ_SEL_FMAP_19", 0x460,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_19_info_dump },
{"TRQ_SEL_FMAP_1A", 0x464,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_1a_info_dump },
{"TRQ_SEL_FMAP_1B", 0x468,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_1b_info_dump },
{"TRQ_SEL_FMAP_1C", 0x46c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_1c_info_dump },
{"TRQ_SEL_FMAP_1D", 0x470,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_1d_info_dump },
{"TRQ_SEL_FMAP_1E", 0x474,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_1e_info_dump },
{"TRQ_SEL_FMAP_1F", 0x478,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_1f_info_dump },
{"TRQ_SEL_FMAP_20", 0x47c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_20_info_dump },
{"TRQ_SEL_FMAP_21", 0x480,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_21_info_dump },
{"TRQ_SEL_FMAP_22", 0x484,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_22_info_dump },
{"TRQ_SEL_FMAP_23", 0x488,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_23_info_dump },
{"TRQ_SEL_FMAP_24", 0x48c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_24_info_dump },
{"TRQ_SEL_FMAP_25", 0x490,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_25_info_dump },
{"TRQ_SEL_FMAP_26", 0x494,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_26_info_dump },
{"TRQ_SEL_FMAP_27", 0x498,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_27_info_dump },
{"TRQ_SEL_FMAP_28", 0x49c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_28_info_dump },
{"TRQ_SEL_FMAP_29", 0x4a0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_29_info_dump },
{"TRQ_SEL_FMAP_2A", 0x4a4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_2a_info_dump },
{"TRQ_SEL_FMAP_2B", 0x4a8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_2b_info_dump },
{"TRQ_SEL_FMAP_2C", 0x4ac,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_2c_info_dump },
{"TRQ_SEL_FMAP_2D", 0x4b0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_2d_info_dump },
{"TRQ_SEL_FMAP_2E", 0x4b4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_2e_info_dump },
{"TRQ_SEL_FMAP_2F", 0x4b8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_2f_info_dump },
{"TRQ_SEL_FMAP_30", 0x4bc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_30_info_dump },
{"TRQ_SEL_FMAP_31", 0x4d0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_31_info_dump },
{"TRQ_SEL_FMAP_32", 0x4d4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_32_info_dump },
{"TRQ_SEL_FMAP_33", 0x4d8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_33_info_dump },
{"TRQ_SEL_FMAP_34", 0x4dc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_34_info_dump },
{"TRQ_SEL_FMAP_35", 0x4e0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_35_info_dump },
{"TRQ_SEL_FMAP_36", 0x4e4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_36_info_dump },
{"TRQ_SEL_FMAP_37", 0x4e8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_37_info_dump },
{"TRQ_SEL_FMAP_38", 0x4ec,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_38_info_dump },
{"TRQ_SEL_FMAP_39", 0x4f0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_39_info_dump },
{"TRQ_SEL_FMAP_3A", 0x4f4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_3a_info_dump },
{"TRQ_SEL_FMAP_3B", 0x4f8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_3b_info_dump },
{"TRQ_SEL_FMAP_3C", 0x4fc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_3c_info_dump },
{"TRQ_SEL_FMAP_3D", 0x500,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_3d_info_dump },
{"TRQ_SEL_FMAP_3E", 0x504,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_3e_info_dump },
{"TRQ_SEL_FMAP_3F", 0x508,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_3f_info_dump },
{"TRQ_SEL_FMAP_40", 0x50c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_40_info_dump },
{"TRQ_SEL_FMAP_41", 0x510,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_41_info_dump },
{"TRQ_SEL_FMAP_42", 0x514,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_42_info_dump },
{"TRQ_SEL_FMAP_43", 0x518,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_43_info_dump },
{"TRQ_SEL_FMAP_44", 0x51c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_44_info_dump },
{"TRQ_SEL_FMAP_45", 0x520,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_45_info_dump },
{"TRQ_SEL_FMAP_46", 0x524,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_46_info_dump },
{"TRQ_SEL_FMAP_47", 0x528,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_47_info_dump },
{"TRQ_SEL_FMAP_48", 0x52c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_48_info_dump },
{"TRQ_SEL_FMAP_49", 0x530,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_49_info_dump },
{"TRQ_SEL_FMAP_4A", 0x534,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_4a_info_dump },
{"TRQ_SEL_FMAP_4B", 0x538,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_4b_info_dump },
{"TRQ_SEL_FMAP_4C", 0x53c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_4c_info_dump },
{"TRQ_SEL_FMAP_4D", 0x540,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_4d_info_dump },
{"TRQ_SEL_FMAP_4E", 0x544,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_4e_info_dump },
{"TRQ_SEL_FMAP_4F", 0x548,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_4f_info_dump },
{"TRQ_SEL_FMAP_50", 0x54c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_50_info_dump },
{"TRQ_SEL_FMAP_51", 0x550,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_51_info_dump },
{"TRQ_SEL_FMAP_52", 0x554,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_52_info_dump },
{"TRQ_SEL_FMAP_53", 0x558,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_53_info_dump },
{"TRQ_SEL_FMAP_54", 0x55c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_54_info_dump },
{"TRQ_SEL_FMAP_55", 0x560,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_55_info_dump },
{"TRQ_SEL_FMAP_56", 0x564,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_56_info_dump },
{"TRQ_SEL_FMAP_57", 0x568,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_57_info_dump },
{"TRQ_SEL_FMAP_58", 0x56c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_58_info_dump },
{"TRQ_SEL_FMAP_59", 0x570,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_59_info_dump },
{"TRQ_SEL_FMAP_5A", 0x574,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_5a_info_dump },
{"TRQ_SEL_FMAP_5B", 0x578,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_5b_info_dump },
{"TRQ_SEL_FMAP_5C", 0x57c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_5c_info_dump },
{"TRQ_SEL_FMAP_5D", 0x580,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_5d_info_dump },
{"TRQ_SEL_FMAP_5E", 0x584,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_5e_info_dump },
{"TRQ_SEL_FMAP_5F", 0x588,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_5f_info_dump },
{"TRQ_SEL_FMAP_60", 0x58c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_60_info_dump },
{"TRQ_SEL_FMAP_61", 0x590,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_61_info_dump },
{"TRQ_SEL_FMAP_62", 0x594,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_62_info_dump },
{"TRQ_SEL_FMAP_63", 0x598,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_63_info_dump },
{"TRQ_SEL_FMAP_64", 0x59c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_64_info_dump },
{"TRQ_SEL_FMAP_65", 0x5a0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_65_info_dump },
{"TRQ_SEL_FMAP_66", 0x5a4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_66_info_dump },
{"TRQ_SEL_FMAP_67", 0x5a8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_67_info_dump },
{"TRQ_SEL_FMAP_68", 0x5ac,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_68_info_dump },
{"TRQ_SEL_FMAP_69", 0x5b0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_69_info_dump },
{"TRQ_SEL_FMAP_6A", 0x5b4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_6a_info_dump },
{"TRQ_SEL_FMAP_6B", 0x5b8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_6b_info_dump },
{"TRQ_SEL_FMAP_6C", 0x5bc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_6c_info_dump },
{"TRQ_SEL_FMAP_6D", 0x5c0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_6d_info_dump },
{"TRQ_SEL_FMAP_6E", 0x5c4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_6e_info_dump },
{"TRQ_SEL_FMAP_6F", 0x5c8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_6f_info_dump },
{"TRQ_SEL_FMAP_70", 0x5cc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_70_info_dump },
{"TRQ_SEL_FMAP_71", 0x5d0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_71_info_dump },
{"TRQ_SEL_FMAP_72", 0x5d4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_72_info_dump },
{"TRQ_SEL_FMAP_73", 0x5d8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_73_info_dump },
{"TRQ_SEL_FMAP_74", 0x5dc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_74_info_dump },
{"TRQ_SEL_FMAP_75", 0x5e0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_75_info_dump },
{"TRQ_SEL_FMAP_76", 0x5e4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_76_info_dump },
{"TRQ_SEL_FMAP_77", 0x5e8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_77_info_dump },
{"TRQ_SEL_FMAP_78", 0x5ec,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_78_info_dump },
{"TRQ_SEL_FMAP_79", 0x5f0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_79_info_dump },
{"TRQ_SEL_FMAP_7A", 0x5f4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_7a_info_dump },
{"TRQ_SEL_FMAP_7B", 0x5f8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_7b_info_dump },
{"TRQ_SEL_FMAP_7C", 0x5fc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_7c_info_dump },
{"TRQ_SEL_FMAP_7D", 0x600,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_7d_info_dump },
{"TRQ_SEL_FMAP_7E", 0x604,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_7e_info_dump },
{"TRQ_SEL_FMAP_7F", 0x608,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_7f_info_dump },
{"TRQ_SEL_FMAP_80", 0x60c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_80_info_dump },
{"TRQ_SEL_FMAP_81", 0x610,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_81_info_dump },
{"TRQ_SEL_FMAP_82", 0x614,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_82_info_dump },
{"TRQ_SEL_FMAP_83", 0x618,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_83_info_dump },
{"TRQ_SEL_FMAP_84", 0x61c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_84_info_dump },
{"TRQ_SEL_FMAP_85", 0x620,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_85_info_dump },
{"TRQ_SEL_FMAP_86", 0x624,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_86_info_dump },
{"TRQ_SEL_FMAP_87", 0x628,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_87_info_dump },
{"TRQ_SEL_FMAP_88", 0x62c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_88_info_dump },
{"TRQ_SEL_FMAP_89", 0x630,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_89_info_dump },
{"TRQ_SEL_FMAP_8A", 0x634,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_8a_info_dump },
{"TRQ_SEL_FMAP_8B", 0x638,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_8b_info_dump },
{"TRQ_SEL_FMAP_8C", 0x63c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_8c_info_dump },
{"TRQ_SEL_FMAP_8D", 0x640,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_8d_info_dump },
{"TRQ_SEL_FMAP_8E", 0x644,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_8e_info_dump },
{"TRQ_SEL_FMAP_8F", 0x648,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_8f_info_dump },
{"TRQ_SEL_FMAP_90", 0x64c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_90_info_dump },
{"TRQ_SEL_FMAP_91", 0x650,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_91_info_dump },
{"TRQ_SEL_FMAP_92", 0x654,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_92_info_dump },
{"TRQ_SEL_FMAP_93", 0x658,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_93_info_dump },
{"TRQ_SEL_FMAP_94", 0x65c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_94_info_dump },
{"TRQ_SEL_FMAP_95", 0x660,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_95_info_dump },
{"TRQ_SEL_FMAP_96", 0x664,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_96_info_dump },
{"TRQ_SEL_FMAP_97", 0x668,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_97_info_dump },
{"TRQ_SEL_FMAP_98", 0x66c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_98_info_dump },
{"TRQ_SEL_FMAP_99", 0x670,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_99_info_dump },
{"TRQ_SEL_FMAP_9A", 0x674,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_9a_info_dump },
{"TRQ_SEL_FMAP_9B", 0x678,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_9b_info_dump },
{"TRQ_SEL_FMAP_9C", 0x67c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_9c_info_dump },
{"TRQ_SEL_FMAP_9D", 0x680,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_9d_info_dump },
{"TRQ_SEL_FMAP_9E", 0x684,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_9e_info_dump },
{"TRQ_SEL_FMAP_9F", 0x688,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_9f_info_dump },
{"TRQ_SEL_FMAP_A0", 0x68c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_a0_info_dump },
{"TRQ_SEL_FMAP_A1", 0x690,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_a1_info_dump },
{"TRQ_SEL_FMAP_A2", 0x694,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_a2_info_dump },
{"TRQ_SEL_FMAP_A3", 0x698,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_a3_info_dump },
{"TRQ_SEL_FMAP_A4", 0x69c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_a4_info_dump },
{"TRQ_SEL_FMAP_A5", 0x6a0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_a5_info_dump },
{"TRQ_SEL_FMAP_A6", 0x6a4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_a6_info_dump },
{"TRQ_SEL_FMAP_A7", 0x6a8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_a7_info_dump },
{"TRQ_SEL_FMAP_A8", 0x6ac,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_a8_info_dump },
{"TRQ_SEL_FMAP_A9", 0x6b0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_a9_info_dump },
{"TRQ_SEL_FMAP_AA", 0x6b4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_aa_info_dump },
{"TRQ_SEL_FMAP_AB", 0x6b8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_ab_info_dump },
{"TRQ_SEL_FMAP_AC", 0x6bc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_ac_info_dump },
{"TRQ_SEL_FMAP_AD", 0x6d0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_ad_info_dump },
{"TRQ_SEL_FMAP_AE", 0x6d4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_ae_info_dump },
{"TRQ_SEL_FMAP_AF", 0x6d8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_af_info_dump },
{"TRQ_SEL_FMAP_B0", 0x6dc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_b0_info_dump },
{"TRQ_SEL_FMAP_B1", 0x6e0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_b1_info_dump },
{"TRQ_SEL_FMAP_B2", 0x6e4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_b2_info_dump },
{"TRQ_SEL_FMAP_B3", 0x6e8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_b3_info_dump },
{"TRQ_SEL_FMAP_B4", 0x6ec,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_b4_info_dump },
{"TRQ_SEL_FMAP_B5", 0x6f0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_b5_info_dump },
{"TRQ_SEL_FMAP_B6", 0x6f4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_b6_info_dump },
{"TRQ_SEL_FMAP_B7", 0x6f8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_b7_info_dump },
{"TRQ_SEL_FMAP_B8", 0x6fc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_b8_info_dump },
{"TRQ_SEL_FMAP_B9", 0x700,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_b9_info_dump },
{"TRQ_SEL_FMAP_BA", 0x704,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_ba_info_dump },
{"TRQ_SEL_FMAP_BB", 0x708,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_bb_info_dump },
{"TRQ_SEL_FMAP_BC", 0x70c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_bc_info_dump },
{"TRQ_SEL_FMAP_BD", 0x710,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_bd_info_dump },
{"TRQ_SEL_FMAP_BE", 0x714,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_be_info_dump },
{"TRQ_SEL_FMAP_BF", 0x718,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_bf_info_dump },
{"TRQ_SEL_FMAP_C0", 0x71c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_c0_info_dump },
{"TRQ_SEL_FMAP_C1", 0x720,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_c1_info_dump },
{"TRQ_SEL_FMAP_C2", 0x734,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_c2_info_dump },
{"TRQ_SEL_FMAP_C3", 0x748,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_c3_info_dump },
{"TRQ_SEL_FMAP_C4", 0x74c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_c4_info_dump },
{"TRQ_SEL_FMAP_C5", 0x750,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_c5_info_dump },
{"TRQ_SEL_FMAP_C6", 0x754,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_c6_info_dump },
{"TRQ_SEL_FMAP_C7", 0x758,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_c7_info_dump },
{"TRQ_SEL_FMAP_C8", 0x75c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_c8_info_dump },
{"TRQ_SEL_FMAP_C9", 0x760,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_c9_info_dump },
{"TRQ_SEL_FMAP_CA", 0x764,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_ca_info_dump },
{"TRQ_SEL_FMAP_CB", 0x768,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_cb_info_dump },
{"TRQ_SEL_FMAP_CC", 0x76c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_cc_info_dump },
{"TRQ_SEL_FMAP_CD", 0x770,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_cd_info_dump },
{"TRQ_SEL_FMAP_CE", 0x774,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_ce_info_dump },
{"TRQ_SEL_FMAP_CF", 0x778,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_cf_info_dump },
{"TRQ_SEL_FMAP_D0", 0x77c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_d0_info_dump },
{"TRQ_SEL_FMAP_D1", 0x780,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_d1_info_dump },
{"TRQ_SEL_FMAP_D2", 0x784,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_d2_info_dump },
{"TRQ_SEL_FMAP_D3", 0x788,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_d3_info_dump },
{"TRQ_SEL_FMAP_D4", 0x78c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_d4_info_dump },
{"TRQ_SEL_FMAP_D5", 0x790,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_d5_info_dump },
{"TRQ_SEL_FMAP_D6", 0x794,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_d6_info_dump },
{"TRQ_SEL_FMAP_D7", 0x798,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_d7_info_dump },
{"TRQ_SEL_FMAP_D8", 0x79c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_d8_info_dump },
{"TRQ_SEL_FMAP_D9", 0x7a0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_d9_info_dump },
{"TRQ_SEL_FMAP_DA", 0x7a4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_da_info_dump },
{"TRQ_SEL_FMAP_DB", 0x7a8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_db_info_dump },
{"TRQ_SEL_FMAP_DC", 0x7ac,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_dc_info_dump },
{"TRQ_SEL_FMAP_DD", 0x7b0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_dd_info_dump },
{"TRQ_SEL_FMAP_DE", 0x7b4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_de_info_dump },
{"TRQ_SEL_FMAP_DF", 0x7b8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_df_info_dump },
{"TRQ_SEL_FMAP_E0", 0x7bc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_e0_info_dump },
{"TRQ_SEL_FMAP_E1", 0x7c0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_e1_info_dump },
{"TRQ_SEL_FMAP_E2", 0x7c4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_e2_info_dump },
{"TRQ_SEL_FMAP_E3", 0x7c8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_e3_info_dump },
{"TRQ_SEL_FMAP_E4", 0x7cc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_e4_info_dump },
{"TRQ_SEL_FMAP_E5", 0x7d0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_e5_info_dump },
{"TRQ_SEL_FMAP_E6", 0x7d4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_e6_info_dump },
{"TRQ_SEL_FMAP_E7", 0x7d8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_e7_info_dump },
{"TRQ_SEL_FMAP_E8", 0x7dc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_e8_info_dump },
{"TRQ_SEL_FMAP_E9", 0x7e0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_e9_info_dump },
{"TRQ_SEL_FMAP_EA", 0x7e4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_ea_info_dump },
{"TRQ_SEL_FMAP_EB", 0x7e8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_eb_info_dump },
{"TRQ_SEL_FMAP_EC", 0x7ec,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_ec_info_dump },
{"TRQ_SEL_FMAP_ED", 0x7f0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_ed_info_dump },
{"TRQ_SEL_FMAP_EE", 0x7f4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_ee_info_dump },
{"TRQ_SEL_FMAP_EF", 0x7f8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_ef_info_dump },
{"TRQ_SEL_FMAP_F0", 0x7fc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_trq_sel_fmap_f0_info_dump },
{"IND_CTXT_DATA_3", 0x804,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ind_ctxt_data_3_info_dump },
{"IND_CTXT_DATA_2", 0x808,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ind_ctxt_data_2_info_dump },
{"IND_CTXT_DATA_1", 0x80c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ind_ctxt_data_1_info_dump },
{"IND_CTXT_DATA_0", 0x810,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ind_ctxt_data_0_info_dump },
{"IND_CTXT3", 0x814,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ind_ctxt3_info_dump },
{"IND_CTXT2", 0x818,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ind_ctxt2_info_dump },
{"IND_CTXT1", 0x81c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ind_ctxt1_info_dump },
{"IND_CTXT0", 0x820,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ind_ctxt0_info_dump },
{"IND_CTXT_CMD", 0x824,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_ind_ctxt_cmd_info_dump },
{"C2H_TIMER_CNT_1", 0xa00,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_1_info_dump },
{"C2H_TIMER_CNT_2", 0xa04,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_2_info_dump },
{"C2H_TIMER_CNT_3", 0xa08,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_3_info_dump },
{"C2H_TIMER_CNT_4", 0xa0c,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_4_info_dump },
{"C2H_TIMER_CNT_5", 0xa10,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_5_info_dump },
{"C2H_TIMER_CNT_6", 0xa14,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_6_info_dump },
{"C2H_TIMER_CNT_7", 0xa18,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_7_info_dump },
{"C2H_TIMER_CNT_8", 0xa1c,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_8_info_dump },
{"C2H_TIMER_CNT_9", 0xa20,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_9_info_dump },
{"C2H_TIMER_CNT_A", 0xa24,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_a_info_dump },
{"C2H_TIMER_CNT_B", 0xa28,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_b_info_dump },
{"C2H_TIMER_CNT_C", 0xa2c,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_c_info_dump },
{"C2H_TIMER_CNT_D", 0xa30,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_d_info_dump },
{"C2H_TIMER_CNT_E", 0xa34,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_e_info_dump },
{"C2H_TIMER_CNT_F", 0xa38,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_f_info_dump },
{"C2H_TIMER_CNT_10", 0xa3c,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_timer_cnt_10_info_dump },
{"C2H_CNT_TH_1", 0xa40,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_1_info_dump },
{"C2H_CNT_TH_2", 0xa44,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_2_info_dump },
{"C2H_CNT_TH_3", 0xa48,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_3_info_dump },
{"C2H_CNT_TH_4", 0xa4c,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_4_info_dump },
{"C2H_CNT_TH_5", 0xa50,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_5_info_dump },
{"C2H_CNT_TH_6", 0xa54,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_6_info_dump },
{"C2H_CNT_TH_7", 0xa58,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_7_info_dump },
{"C2H_CNT_TH_8", 0xa5c,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_8_info_dump },
{"C2H_CNT_TH_9", 0xa60,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_9_info_dump },
{"C2H_CNT_TH_A", 0xa64,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_a_info_dump },
{"C2H_CNT_TH_B", 0xa68,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_b_info_dump },
{"C2H_CNT_TH_C", 0xa6c,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_c_info_dump },
{"C2H_CNT_TH_D", 0xa70,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_d_info_dump },
{"C2H_CNT_TH_E", 0xa74,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_e_info_dump },
{"C2H_CNT_TH_F", 0xa78,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_f_info_dump },
{"C2H_CNT_TH_10", 0xa7c,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_cnt_th_10_info_dump },
{"C2H_QID2VEC_MAP_QID", 0xa80,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_qid2vec_map_qid_info_dump },
{"C2H_QID2VEC_MAP", 0xa84,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_qid2vec_map_info_dump },
{"C2H_STAT_S_AXIS_C2H_ACCEPTED", 0xa88,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_stat_s_axis_c2h_accepted_info_dump },
{"C2H_STAT_S_AXIS_WRB_ACCEPTED", 0xa8c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_stat_s_axis_wrb_accepted_info_dump },
{"C2H_STAT_DESC_RSP_PKT_ACCEPTED", 0xa90,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_stat_desc_rsp_pkt_accepted_info_dump },
{"C2H_STAT_AXIS_PKG_CMP", 0xa94,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_stat_axis_pkg_cmp_info_dump },
{"C2H_STAT_DESC_RSP_ACCEPTED", 0xa98,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_desc_rsp_accepted_info_dump },
{"C2H_STAT_DESC_RSP_CMP", 0xa9c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_desc_rsp_cmp_info_dump },
{"C2H_STAT_WRQ_OUT", 0xaa0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_wrq_out_info_dump },
{"C2H_STAT_WPL_REN_ACCEPTED", 0xaa4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_wpl_ren_accepted_info_dump },
{"C2H_STAT_TOTAL_WRQ_LEN", 0xaa8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_total_wrq_len_info_dump },
{"C2H_STAT_TOTAL_WPL_LEN", 0xaac,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_total_wpl_len_info_dump },
{"C2H_BUF_SZ_0", 0xab0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_0_info_dump },
{"C2H_BUF_SZ_1", 0xab4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_1_info_dump },
{"C2H_BUF_SZ_2", 0xab8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_2_info_dump },
{"C2H_BUF_SZ_3", 0xabc,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_3_info_dump },
{"C2H_BUF_SZ_4", 0xac0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_4_info_dump },
{"C2H_BUF_SZ_5", 0xac4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_5_info_dump },
{"C2H_BUF_SZ_7", 0xac8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_7_info_dump },
{"C2H_BUF_SZ_8", 0xacc,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_8_info_dump },
{"C2H_BUF_SZ_9", 0xad0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_9_info_dump },
{"C2H_BUF_SZ_10", 0xad4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_10_info_dump },
{"C2H_BUF_SZ_11", 0xad8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_11_info_dump },
{"C2H_BUF_SZ_12", 0xae0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_12_info_dump },
{"C2H_BUF_SZ_13", 0xae4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_13_info_dump },
{"C2H_BUF_SZ_14", 0xae8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_14_info_dump },
{"C2H_BUF_SZ_15", 0xaec,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_buf_sz_15_info_dump },
{"C2H_ERR_STAT", 0xaf0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_err_stat_info_dump },
{"C2H_ERR_MASK", 0xaf4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_err_mask_info_dump },
{"C2H_FATAL_ERR_STAT", 0xaf8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_fatal_err_stat_info_dump },
{"C2H_FATAL_ERR_MASK", 0xafc,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_fatal_err_mask_info_dump },
{"C2H_FATAL_ERR_ENABLE", 0xb00,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_fatal_err_enable_info_dump },
{"GLBL_ERR_INT", 0xb04,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_glbl_err_int_info_dump },
{"C2H_PFCH_CFG", 0xb08,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_pfch_cfg_info_dump },
{"C2H_INT_TIMER_TICK", 0xb0c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_int_timer_tick_info_dump },
{"C2H_STAT_DESC_RSP_DROP_ACCEPTED", 0xb10,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_stat_desc_rsp_drop_accepted_info_dump },
{"C2H_STAT_DESC_RSP_ERR_ACCEPTED", 0xb14,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_stat_desc_rsp_err_accepted_info_dump },
{"C2H_STAT_DESC_REQ", 0xb18,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_desc_req_info_dump },
{"C2H_STAT_DBG_DMA_ENG_0", 0xb1c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_dbg_dma_eng_0_info_dump },
{"C2H_STAT_DBG_DMA_ENG_1", 0xb20,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_dbg_dma_eng_1_info_dump },
{"C2H_STAT_DBG_DMA_ENG_2", 0xb24,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_dbg_dma_eng_2_info_dump },
{"C2H_STAT_DBG_DMA_ENG_3", 0xb28,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_dbg_dma_eng_3_info_dump },
{"C2H_DBG_PFCH_ERR_CTXT", 0xb2c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_dbg_pfch_err_ctxt_info_dump },
{"C2H_FIRST_ERR_QID", 0xb30,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_first_err_qid_info_dump },
{"STAT_NUM_WRB_IN", 0xb34,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_stat_num_wrb_in_info_dump },
{"STAT_NUM_WRB_OUT", 0xb38,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_stat_num_wrb_out_info_dump },
{"STAT_NUM_WRB_DRP", 0xb3c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_stat_num_wrb_drp_info_dump },
{"STAT_NUM_STAT_DESC_OUT", 0xb40,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_stat_num_stat_desc_out_info_dump },
{"STAT_NUM_DSC_CRDT_SENT", 0xb44,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_stat_num_dsc_crdt_sent_info_dump },
{"STAT_NUM_FCH_DSC_RCVD", 0xb48,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_stat_num_fch_dsc_rcvd_info_dump },
{"STAT_NUM_BYP_DSC_RCVD", 0xb4c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_stat_num_byp_dsc_rcvd_info_dump },
{"C2H_WRB_COAL_CFG", 0xb50,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_wrb_coal_cfg_info_dump },
{"C2H_INTR_H2C_REQ", 0xb54,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_intr_h2c_req_info_dump },
{"C2H_INTR_C2H_MM_REQ", 0xb58,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_intr_c2h_mm_req_info_dump },
{"C2H_INTR_ERR_INT_REQ", 0xb5c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_intr_err_int_req_info_dump },
{"C2H_INTR_C2H_ST_REQ", 0xb60,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_intr_c2h_st_req_info_dump },
{"C2H_INTR_H2C_ERR_C2H_MM_MSIX_ACK", 0xb64,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_intr_h2c_err_c2h_mm_msix_ack_info_dump },
{"C2H_INTR_H2C_ERR_C2H_MM_MSIX_FAIL", 0xb68,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_intr_h2c_err_c2h_mm_msix_fail_info_dump },
{"C2H_INTR_H2C_ERR_C2H_MM_MSIX_NO_MSIX", 0xb6c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_intr_h2c_err_c2h_mm_msix_no_msix_info_dump },
{"C2H_INTR_H2C_ERR_C2H_MM_CTXT_INVAL", 0xb70,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_intr_h2c_err_c2h_mm_ctxt_inval_info_dump },
{"C2H_INTR_C2H_ST_MSIX_ACK", 0xb74,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_intr_c2h_st_msix_ack_info_dump },
{"C2H_INTR_C2H_ST_MSIX_FAIL", 0xb78,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_c2h_intr_c2h_st_msix_fail_info_dump },
{"C2H_INTR_C2H_ST_NO_MSIX", 0xb7c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_intr_c2h_st_no_msix_info_dump },
{"C2H_INTR_C2H_ST_CTXT_INVAL", 0xb80,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_intr_c2h_st_ctxt_inval_info_dump },
{"C2H_STAT_WR_CMP", 0xb84,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_wr_cmp_info_dump },
{"C2H_STAT_DBG_DMA_ENG_4", 0xb88,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_dbg_dma_eng_4_info_dump },
{"C2H_STAT_DBG_DMA_ENG_5", 0xb8c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_dbg_dma_eng_5_info_dump },
{"C2H_DBG_PFCH_QID", 0xb90,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_dbg_pfch_qid_info_dump },
{"C2H_DBG_PFCH", 0xb94,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_dbg_pfch_info_dump },
{"C2H_INT_DBG", 0xb98,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_int_dbg_info_dump },
{"C2H_STAT_IMM_ACCEPTED", 0xb9c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_imm_accepted_info_dump },
{"C2H_STAT_MARKER_ACCEPTED", 0xba0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_marker_accepted_info_dump },
{"C2H_STAT_DISABLE_CMP_ACCEPTED", 0xba4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_stat_disable_cmp_accepted_info_dump },
{"C2H_PLD_FIFO_CRDT_CNT", 0xba8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_pld_fifo_crdt_cnt_info_dump },
{"H2C_ERR_STAT", 0xe00,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_h2c_err_stat_info_dump },
{"H2C_ERR_MASK", 0xe04,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_h2c_err_mask_info_dump },
{"H2C_FIRST_ERR_QID", 0xe08,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_h2c_first_err_qid_info_dump },
{"H2C_DBG_REG0", 0xe0c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_dbg_reg0_info_dump },
{"H2C_DBG_REG1", 0xe10,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_dbg_reg1_info_dump },
{"H2C_DBG_REG2", 0xe14,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_dbg_reg2_info_dump },
{"H2C_DBG_REG3", 0xe18,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_dbg_reg3_info_dump },
{"H2C_DBG_REG4", 0xe1c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_dbg_reg4_info_dump },
{"H2C_FATAL_ERR_EN", 0xe20,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&qdma_s80_hard_h2c_fatal_err_en_info_dump },
{"C2H_CHANNEL_CTL", 0x1004,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_channel_ctl_info_dump },
{"C2H_CHANNEL_CTL_1", 0x1008,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_channel_ctl_1_info_dump },
{"C2H_MM_STATUS", 0x1040,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_mm_status_info_dump },
{"C2H_CHANNEL_CMPL_DESC_CNT", 0x1048,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_channel_cmpl_desc_cnt_info_dump },
{"C2H_MM_ERR_CODE_ENABLE_MASK", 0x1054,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_mm_err_code_enable_mask_info_dump },
{"C2H_MM_ERR_CODE", 0x1058,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_mm_err_code_info_dump },
{"C2H_MM_ERR_INFO", 0x105c,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_mm_err_info_info_dump },
{"C2H_MM_PERF_MON_CTL", 0x10c0,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_mm_perf_mon_ctl_info_dump },
{"C2H_MM_PERF_MON_CYCLE_CNT0", 0x10c4,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_mm_perf_mon_cycle_cnt0_info_dump },
{"C2H_MM_PERF_MON_CYCLE_CNT1", 0x10c8,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_mm_perf_mon_cycle_cnt1_info_dump },
{"C2H_MM_PERF_MON_DATA_CNT0", 0x10cc,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_mm_perf_mon_data_cnt0_info_dump },
{"C2H_MM_PERF_MON_DATA_CNT1", 0x10d0,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_mm_perf_mon_data_cnt1_info_dump },
{"C2H_MM_DBG", 0x10e8,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_c2h_mm_dbg_info_dump },
{"H2C_CHANNEL_CTL", 0x1204,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_channel_ctl_info_dump },
{"H2C_CHANNEL_CTL_1", 0x1208,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_channel_ctl_1_info_dump },
{"H2C_CHANNEL_CTL_2", 0x120c,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_channel_ctl_2_info_dump },
{"H2C_MM_STATUS", 0x1240,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_mm_status_info_dump },
{"H2C_CHANNEL_CMPL_DESC_CNT", 0x1248,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_channel_cmpl_desc_cnt_info_dump },
{"H2C_MM_ERR_CODE_ENABLE_MASK", 0x1254,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_mm_err_code_enable_mask_info_dump },
{"H2C_MM_ERR_CODE", 0x1258,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_mm_err_code_info_dump },
{"H2C_MM_ERR_INFO", 0x125c,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_mm_err_info_info_dump },
{"H2C_MM_PERF_MON_CTL", 0x12c0,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_mm_perf_mon_ctl_info_dump },
{"H2C_MM_PERF_MON_CYCLE_CNT0", 0x12c4,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_mm_perf_mon_cycle_cnt0_info_dump },
{"H2C_MM_PERF_MON_CYCLE_CNT1", 0x12c8,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_mm_perf_mon_cycle_cnt1_info_dump },
{"H2C_MM_PERF_MON_DATA_CNT0", 0x12cc,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_mm_perf_mon_data_cnt0_info_dump },
{"H2C_MM_PERF_MON_DATA_CNT1", 0x12d0,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_mm_perf_mon_data_cnt1_info_dump },
{"H2C_MM_DBG", 0x12e8,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_h2c_mm_dbg_info_dump },
{"FUNC_STATUS_REG", 0x2400,
	1, 0, 0, 0,
	0, QDMA_MAILBOX, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_func_status_reg_info_dump },
{"FUNC_CMD_REG", 0x2404,
	1, 0, 0, 0,
	0, QDMA_MAILBOX, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_func_cmd_reg_info_dump },
{"FUNC_INTERRUPT_VECTOR_REG", 0x2408,
	1, 0, 0, 0,
	0, QDMA_MAILBOX, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_func_interrupt_vector_reg_info_dump },
{"TARGET_FUNC_REG", 0x240c,
	1, 0, 0, 0,
	0, QDMA_MAILBOX, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_target_func_reg_info_dump },
{"FUNC_INTERRUPT_CTL_REG", 0x2410,
	1, 0, 0, 0,
	0, QDMA_MAILBOX, QDMA_REG_READ_PF_ONLY,
	&qdma_s80_hard_func_interrupt_ctl_reg_info_dump },
};

uint32_t qdma_s80_hard_config_num_regs_get(void)
{
	return (sizeof(qdma_s80_hard_config_regs)/
		sizeof(qdma_s80_hard_config_regs[0]));
}

struct xreg_info *qdma_s80_hard_config_regs_get(void)
{
	return qdma_s80_hard_config_regs;
}

