/*
 * Copyright(c) 2019-2020 Xilinx, Inc. All rights reserved.
 */


#include "eqdma_soft_reg.h"
#include "qdma_reg_dump.h"

#ifdef ENABLE_WPP_TRACING
#include "eqdma_soft_reg_dump.tmh"
#endif


int eqdma_cfg_blk_identifier_info_dump(
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


int eqdma_cfg_blk_pcie_max_pld_size_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,7 ]      0x%x\n",
	"CFG_BLK_PCIE_MAX_PLD_SIZE_RSVD_1", (reg_val &
	CFG_BLK_PCIE_MAX_PLD_SIZE_RSVD_1_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6 ,4 ]      0x%x\n",
	"CFG_BLK_PCIE_MAX_PLD_SIZE_PROG", (reg_val &
	CFG_BLK_PCIE_MAX_PLD_SIZE_PROG_MASK) >> 4);

	if (rv < 0) {
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
	"CFG_BLK_PCIE_MAX_PLD_SIZE_RSVD_2", (reg_val &
	CFG_BLK_PCIE_MAX_PLD_SIZE_RSVD_2_MASK) >> 3);

	if (rv < 0) {
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
	"CFG_BLK_PCIE_MAX_PLD_SIZE_ISSUED", (reg_val &
	CFG_BLK_PCIE_MAX_PLD_SIZE_ISSUED_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_cfg_blk_pcie_max_read_req_size_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,7 ]      0x%x\n",
	"CFG_BLK_PCIE_MAX_READ_REQ_SIZE_RSVD_1", (reg_val &
	CFG_BLK_PCIE_MAX_READ_REQ_SIZE_RSVD_1_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6 ,4 ]      0x%x\n",
	"CFG_BLK_PCIE_MAX_READ_REQ_SIZE_PROG", (reg_val &
	CFG_BLK_PCIE_MAX_READ_REQ_SIZE_PROG_MASK) >> 4);

	if (rv < 0) {
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
	"CFG_BLK_PCIE_MAX_READ_REQ_SIZE_RSVD_2", (reg_val &
	CFG_BLK_PCIE_MAX_READ_REQ_SIZE_RSVD_2_MASK) >> 3);

	if (rv < 0) {
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
	"CFG_BLK_PCIE_MAX_READ_REQ_SIZE_ISSUED", (reg_val &
	CFG_BLK_PCIE_MAX_READ_REQ_SIZE_ISSUED_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_cfg_blk_system_id_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,17]      0x%x\n",
	"CFG_BLK_SYSTEM_ID_RSVD_1", (reg_val &
	CFG_BLK_SYSTEM_ID_RSVD_1_MASK) >> 17);

	if (rv < 0) {
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
	"CFG_BLK_SYSTEM_ID_INST_TYPE", (reg_val &
	CFG_BLK_SYSTEM_ID_INST_TYPE_MASK) >> 16);

	if (rv < 0) {
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


int eqdma_cfg_blk_msix_enable_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"CFG_BLK_MSIX_ENABLE", (reg_val &
	CFG_BLK_MSIX_ENABLE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_cfg_pcie_data_width_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,3 ]      0x%x\n",
	"CFG_PCIE_DATA_WIDTH_RSVD_1", (reg_val &
	CFG_PCIE_DATA_WIDTH_RSVD_1_MASK) >> 3);

	if (rv < 0) {
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


int eqdma_cfg_pcie_ctl_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"CFG_PCIE_CTL_RSVD_1", (reg_val &
	CFG_PCIE_CTL_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,16]      0x%x\n",
	"CFG_PCIE_CTL_MGMT_AXIL_CTRL", (reg_val &
	CFG_PCIE_CTL_MGMT_AXIL_CTRL_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,2 ]      0x%x\n",
	"CFG_PCIE_CTL_RSVD_2", (reg_val &
	CFG_PCIE_CTL_RSVD_2_MASK) >> 2);

	if (rv < 0) {
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


int eqdma_cfg_blk_msi_enable_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"CFG_BLK_MSI_ENABLE", (reg_val &
	CFG_BLK_MSI_ENABLE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_cfg_axi_user_max_pld_size_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,7 ]      0x%x\n",
	"CFG_AXI_USER_MAX_PLD_SIZE_RSVD_1", (reg_val &
	CFG_AXI_USER_MAX_PLD_SIZE_RSVD_1_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


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
	"%-40s [3    ]      0x%x\n",
	"CFG_AXI_USER_MAX_PLD_SIZE_RSVD_2", (reg_val &
	CFG_AXI_USER_MAX_PLD_SIZE_RSVD_2_MASK) >> 3);

	if (rv < 0) {
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


int eqdma_cfg_axi_user_max_read_req_size_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,7 ]      0x%x\n",
	"CFG_AXI_USER_MAX_READ_REQ_SIZE_RSVD_1", (reg_val &
	CFG_AXI_USER_MAX_READ_REQ_SIZE_RSVD_1_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


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
	"%-40s [3    ]      0x%x\n",
	"CFG_AXI_USER_MAX_READ_REQ_SIZE_RSVD_2", (reg_val &
	CFG_AXI_USER_MAX_READ_REQ_SIZE_RSVD_2_MASK) >> 3);

	if (rv < 0) {
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


int eqdma_cfg_blk_misc_ctl_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,24]      0x%x\n",
	"CFG_BLK_MISC_CTL_RSVD_1", (reg_val &
	CFG_BLK_MISC_CTL_RSVD_1_MASK) >> 24);

	if (rv < 0) {
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
	"CFG_BLK_MISC_CTL_10B_TAG_EN", (reg_val &
	CFG_BLK_MISC_CTL_10B_TAG_EN_MASK) >> 23);

	if (rv < 0) {
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
	"CFG_BLK_MISC_CTL_RSVD_2", (reg_val &
	CFG_BLK_MISC_CTL_RSVD_2_MASK) >> 22);

	if (rv < 0) {
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
	"CFG_BLK_MISC_CTL_AXI_WB", (reg_val &
	CFG_BLK_MISC_CTL_AXI_WBK_MASK) >> 21);

	if (rv < 0) {
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
	"CFG_BLK_MISC_CTL_AXI_DSC", (reg_val &
	CFG_BLK_MISC_CTL_AXI_DSC_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


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
	"%-40s [7 ,5 ]      0x%x\n",
	"CFG_BLK_MISC_CTL_RSVD_3", (reg_val &
	CFG_BLK_MISC_CTL_RSVD_3_MASK) >> 5);

	if (rv < 0) {
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


int eqdma_cfg_pl_cred_ctl_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,5 ]      0x%x\n",
	"CFG_PL_CRED_CTL_RSVD_1", (reg_val &
	CFG_PL_CRED_CTL_RSVD_1_MASK) >> 5);

	if (rv < 0) {
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
	"CFG_PL_CRED_CTL_SLAVE_CRD_RL", (reg_val &
	CFG_PL_CRED_CTL_SLAVE_CRD_RLS_MASK) >> 4);

	if (rv < 0) {
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
	"CFG_PL_CRED_CTL_RSVD_2", (reg_val &
	CFG_PL_CRED_CTL_RSVD_2_MASK) >> 1);

	if (rv < 0) {
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
	"CFG_PL_CRED_CTL_MASTER_CRD_RST", (reg_val &
	CFG_PL_CRED_CTL_MASTER_CRD_RST_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_cfg_blk_scratch_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"CFG_BLK_SCRATCH", (reg_val &
	CFG_BLK_SCRATCH_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_cfg_gic_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,1 ]      0x%x\n",
	"CFG_GIC_RSVD_1", (reg_val &
	CFG_GIC_RSVD_1_MASK) >> 1);

	if (rv < 0) {
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
	"CFG_GIC_GIC_IRQ", (reg_val &
	CFG_GIC_GIC_IRQ_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_ram_sbe_msk_1_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"RAM_SBE_MSK_1", (reg_val &
	RAM_SBE_MSK_1_A_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_ram_sbe_sts_1_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,5 ]      0x%x\n",
	"RAM_SBE_STS_1_A_RSVD", (reg_val &
	RAM_SBE_STS_1_A_RSVD_MASK) >> 5);

	if (rv < 0) {
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
	"RAM_SBE_STS_1_A_PFCH_CTXT_CAM_RAM_1", (reg_val &
	RAM_SBE_STS_1_A_PFCH_CTXT_CAM_RAM_1_MASK) >> 4);

	if (rv < 0) {
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
	"RAM_SBE_STS_1_A_PFCH_CTXT_CAM_RAM_0", (reg_val &
	RAM_SBE_STS_1_A_PFCH_CTXT_CAM_RAM_0_MASK) >> 3);

	if (rv < 0) {
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
	"RAM_SBE_STS_1_A_TAG_EVEN_R", (reg_val &
	RAM_SBE_STS_1_A_TAG_EVEN_RAM_MASK) >> 2);

	if (rv < 0) {
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
	"RAM_SBE_STS_1_A_TAG_ODD_R", (reg_val &
	RAM_SBE_STS_1_A_TAG_ODD_RAM_MASK) >> 1);

	if (rv < 0) {
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
	"RAM_SBE_STS_1_A_RC_RRQ_EVEN_R", (reg_val &
	RAM_SBE_STS_1_A_RC_RRQ_EVEN_RAM_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_ram_dbe_msk_1_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"RAM_DBE_MSK_1", (reg_val &
	RAM_DBE_MSK_1_A_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_ram_dbe_sts_1_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,5 ]      0x%x\n",
	"RAM_DBE_STS_1_A_RSVD", (reg_val &
	RAM_DBE_STS_1_A_RSVD_MASK) >> 5);

	if (rv < 0) {
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
	"RAM_DBE_STS_1_A_PFCH_CTXT_CAM_RAM_1", (reg_val &
	RAM_DBE_STS_1_A_PFCH_CTXT_CAM_RAM_1_MASK) >> 4);

	if (rv < 0) {
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
	"RAM_DBE_STS_1_A_PFCH_CTXT_CAM_RAM_0", (reg_val &
	RAM_DBE_STS_1_A_PFCH_CTXT_CAM_RAM_0_MASK) >> 3);

	if (rv < 0) {
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
	"RAM_DBE_STS_1_A_TAG_EVEN_R", (reg_val &
	RAM_DBE_STS_1_A_TAG_EVEN_RAM_MASK) >> 2);

	if (rv < 0) {
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
	"RAM_DBE_STS_1_A_TAG_ODD_R", (reg_val &
	RAM_DBE_STS_1_A_TAG_ODD_RAM_MASK) >> 1);

	if (rv < 0) {
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
	"RAM_DBE_STS_1_A_RC_RRQ_EVEN_R", (reg_val &
	RAM_DBE_STS_1_A_RC_RRQ_EVEN_RAM_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_ram_sbe_msk_a_info_dump(
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


int eqdma_ram_sbe_sts_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"RAM_SBE_STS_A_RC_RRQ_ODD_R", (reg_val &
	RAM_SBE_STS_A_RC_RRQ_ODD_RAM_MASK) >> 31);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_PEND_FIFO_R", (reg_val &
	RAM_SBE_STS_A_PEND_FIFO_RAM_MASK) >> 30);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_PFCH_LL_R", (reg_val &
	RAM_SBE_STS_A_PFCH_LL_RAM_MASK) >> 29);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_WRB_CTXT_R", (reg_val &
	RAM_SBE_STS_A_WRB_CTXT_RAM_MASK) >> 28);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_PFCH_CTXT_R", (reg_val &
	RAM_SBE_STS_A_PFCH_CTXT_RAM_MASK) >> 27);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_DESC_REQ_FIFO_R", (reg_val &
	RAM_SBE_STS_A_DESC_REQ_FIFO_RAM_MASK) >> 26);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_INT_CTXT_R", (reg_val &
	RAM_SBE_STS_A_INT_CTXT_RAM_MASK) >> 25);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_QID_FIFO_R", (reg_val &
	RAM_SBE_STS_A_QID_FIFO_RAM_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,19]      0x%x\n",
	"RAM_SBE_STS_A_TIMER_FIFO_R", (reg_val &
	RAM_SBE_STS_A_TIMER_FIFO_RAM_MASK) >> 19);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_MI_TL_SLV_FIFO_R", (reg_val &
	RAM_SBE_STS_A_MI_TL_SLV_FIFO_RAM_MASK) >> 18);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_DSC_CPLD", (reg_val &
	RAM_SBE_STS_A_DSC_CPLD_MASK) >> 17);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_DSC_CPLI", (reg_val &
	RAM_SBE_STS_A_DSC_CPLI_MASK) >> 16);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_DSC_SW_CTXT", (reg_val &
	RAM_SBE_STS_A_DSC_SW_CTXT_MASK) >> 15);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_DSC_CRD_RCV", (reg_val &
	RAM_SBE_STS_A_DSC_CRD_RCV_MASK) >> 14);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_DSC_HW_CTXT", (reg_val &
	RAM_SBE_STS_A_DSC_HW_CTXT_MASK) >> 13);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_FUNC_MAP", (reg_val &
	RAM_SBE_STS_A_FUNC_MAP_MASK) >> 12);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_C2H_WR_BRG_DAT", (reg_val &
	RAM_SBE_STS_A_C2H_WR_BRG_DAT_MASK) >> 11);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_C2H_RD_BRG_DAT", (reg_val &
	RAM_SBE_STS_A_C2H_RD_BRG_DAT_MASK) >> 10);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_H2C_WR_BRG_DAT", (reg_val &
	RAM_SBE_STS_A_H2C_WR_BRG_DAT_MASK) >> 9);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_H2C_RD_BRG_DAT", (reg_val &
	RAM_SBE_STS_A_H2C_RD_BRG_DAT_MASK) >> 8);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_MI_C2H3_DAT", (reg_val &
	RAM_SBE_STS_A_MI_C2H3_DAT_MASK) >> 7);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_MI_C2H2_DAT", (reg_val &
	RAM_SBE_STS_A_MI_C2H2_DAT_MASK) >> 6);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_MI_C2H1_DAT", (reg_val &
	RAM_SBE_STS_A_MI_C2H1_DAT_MASK) >> 5);

	if (rv < 0) {
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
	"%-40s [3    ]      0x%x\n",
	"RAM_SBE_STS_A_MI_H2C3_DAT", (reg_val &
	RAM_SBE_STS_A_MI_H2C3_DAT_MASK) >> 3);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_MI_H2C2_DAT", (reg_val &
	RAM_SBE_STS_A_MI_H2C2_DAT_MASK) >> 2);

	if (rv < 0) {
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
	"RAM_SBE_STS_A_MI_H2C1_DAT", (reg_val &
	RAM_SBE_STS_A_MI_H2C1_DAT_MASK) >> 1);

	if (rv < 0) {
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


int eqdma_ram_dbe_msk_a_info_dump(
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


int eqdma_ram_dbe_sts_a_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"RAM_DBE_STS_A_RC_RRQ_ODD_R", (reg_val &
	RAM_DBE_STS_A_RC_RRQ_ODD_RAM_MASK) >> 31);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_PEND_FIFO_R", (reg_val &
	RAM_DBE_STS_A_PEND_FIFO_RAM_MASK) >> 30);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_PFCH_LL_R", (reg_val &
	RAM_DBE_STS_A_PFCH_LL_RAM_MASK) >> 29);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_WRB_CTXT_R", (reg_val &
	RAM_DBE_STS_A_WRB_CTXT_RAM_MASK) >> 28);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_PFCH_CTXT_R", (reg_val &
	RAM_DBE_STS_A_PFCH_CTXT_RAM_MASK) >> 27);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_DESC_REQ_FIFO_R", (reg_val &
	RAM_DBE_STS_A_DESC_REQ_FIFO_RAM_MASK) >> 26);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_INT_CTXT_R", (reg_val &
	RAM_DBE_STS_A_INT_CTXT_RAM_MASK) >> 25);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_QID_FIFO_R", (reg_val &
	RAM_DBE_STS_A_QID_FIFO_RAM_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,19]      0x%x\n",
	"RAM_DBE_STS_A_TIMER_FIFO_R", (reg_val &
	RAM_DBE_STS_A_TIMER_FIFO_RAM_MASK) >> 19);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_MI_TL_SLV_FIFO_R", (reg_val &
	RAM_DBE_STS_A_MI_TL_SLV_FIFO_RAM_MASK) >> 18);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_DSC_CPLD", (reg_val &
	RAM_DBE_STS_A_DSC_CPLD_MASK) >> 17);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_DSC_CPLI", (reg_val &
	RAM_DBE_STS_A_DSC_CPLI_MASK) >> 16);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_DSC_SW_CTXT", (reg_val &
	RAM_DBE_STS_A_DSC_SW_CTXT_MASK) >> 15);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_DSC_CRD_RCV", (reg_val &
	RAM_DBE_STS_A_DSC_CRD_RCV_MASK) >> 14);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_DSC_HW_CTXT", (reg_val &
	RAM_DBE_STS_A_DSC_HW_CTXT_MASK) >> 13);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_FUNC_MAP", (reg_val &
	RAM_DBE_STS_A_FUNC_MAP_MASK) >> 12);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_C2H_WR_BRG_DAT", (reg_val &
	RAM_DBE_STS_A_C2H_WR_BRG_DAT_MASK) >> 11);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_C2H_RD_BRG_DAT", (reg_val &
	RAM_DBE_STS_A_C2H_RD_BRG_DAT_MASK) >> 10);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_H2C_WR_BRG_DAT", (reg_val &
	RAM_DBE_STS_A_H2C_WR_BRG_DAT_MASK) >> 9);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_H2C_RD_BRG_DAT", (reg_val &
	RAM_DBE_STS_A_H2C_RD_BRG_DAT_MASK) >> 8);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_MI_C2H3_DAT", (reg_val &
	RAM_DBE_STS_A_MI_C2H3_DAT_MASK) >> 7);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_MI_C2H2_DAT", (reg_val &
	RAM_DBE_STS_A_MI_C2H2_DAT_MASK) >> 6);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_MI_C2H1_DAT", (reg_val &
	RAM_DBE_STS_A_MI_C2H1_DAT_MASK) >> 5);

	if (rv < 0) {
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
	"%-40s [3    ]      0x%x\n",
	"RAM_DBE_STS_A_MI_H2C3_DAT", (reg_val &
	RAM_DBE_STS_A_MI_H2C3_DAT_MASK) >> 3);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_MI_H2C2_DAT", (reg_val &
	RAM_DBE_STS_A_MI_H2C2_DAT_MASK) >> 2);

	if (rv < 0) {
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
	"RAM_DBE_STS_A_MI_H2C1_DAT", (reg_val &
	RAM_DBE_STS_A_MI_H2C1_DAT_MASK) >> 1);

	if (rv < 0) {
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


int eqdma_glbl2_identifier_info_dump(
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


int eqdma_glbl2_channel_inst_info_dump(
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
	"%-40s [15,12]      0x%x\n",
	"GLBL2_CHANNEL_INST_RSVD_2", (reg_val &
	GLBL2_CHANNEL_INST_RSVD_2_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,8 ]      0x%x\n",
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
	"%-40s [7 ,4 ]      0x%x\n",
	"GLBL2_CHANNEL_INST_RSVD_3", (reg_val &
	GLBL2_CHANNEL_INST_RSVD_3_MASK) >> 4);

	if (rv < 0) {
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


int eqdma_glbl2_channel_mdma_info_dump(
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
	"%-40s [15,12]      0x%x\n",
	"GLBL2_CHANNEL_MDMA_RSVD_2", (reg_val &
	GLBL2_CHANNEL_MDMA_RSVD_2_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,8 ]      0x%x\n",
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
	"%-40s [7 ,4 ]      0x%x\n",
	"GLBL2_CHANNEL_MDMA_RSVD_3", (reg_val &
	GLBL2_CHANNEL_MDMA_RSVD_3_MASK) >> 4);

	if (rv < 0) {
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


int eqdma_glbl2_channel_strm_info_dump(
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
	"%-40s [15,12]      0x%x\n",
	"GLBL2_CHANNEL_STRM_RSVD_2", (reg_val &
	GLBL2_CHANNEL_STRM_RSVD_2_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,8 ]      0x%x\n",
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
	"%-40s [7 ,4 ]      0x%x\n",
	"GLBL2_CHANNEL_STRM_RSVD_3", (reg_val &
	GLBL2_CHANNEL_STRM_RSVD_3_MASK) >> 4);

	if (rv < 0) {
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


int eqdma_glbl2_channel_cap_info_dump(
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


int eqdma_glbl2_channel_pasid_cap_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,2 ]      0x%x\n",
	"GLBL2_CHANNEL_PASID_CAP_RSVD_1", (reg_val &
	GLBL2_CHANNEL_PASID_CAP_RSVD_1_MASK) >> 2);

	if (rv < 0) {
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


int eqdma_glbl2_system_id_info_dump(
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


int eqdma_glbl2_misc_cap_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"GLBL2_MISC_CAP", (reg_val &
	GLBL2_MISC_CAP_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl2_dbg_pcie_rq0_info_dump(
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
	"%-40s [19,9 ]      0x%x\n",
	"GLBL2_PCIE_RQ0_RCB_AVL", (reg_val &
	GLBL2_PCIE_RQ0_RCB_AVL_MASK) >> 9);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [8 ,2 ]      0x%x\n",
	"GLBL2_PCIE_RQ0_SLV_RD_CRED", (reg_val &
	GLBL2_PCIE_RQ0_SLV_RD_CREDS_MASK) >> 2);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ0_TAG_EP", (reg_val &
	GLBL2_PCIE_RQ0_TAG_EP_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl2_dbg_pcie_rq1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,21]      0x%x\n",
	"GLBL2_PCIE_RQ1_RSVD_1", (reg_val &
	GLBL2_PCIE_RQ1_RSVD_1_MASK) >> 21);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [20,19]      0x%x\n",
	"GLBL2_PCIE_RQ1_TAG_FL", (reg_val &
	GLBL2_PCIE_RQ1_TAG_FL_MASK) >> 19);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_WTLP_HEADER_FIFO_FL", (reg_val &
	GLBL2_PCIE_RQ1_WTLP_HEADER_FIFO_FL_MASK) >> 18);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_WTLP_HEADER_FIFO_EP", (reg_val &
	GLBL2_PCIE_RQ1_WTLP_HEADER_FIFO_EP_MASK) >> 17);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_RQ_FIFO_EP", (reg_val &
	GLBL2_PCIE_RQ1_RQ_FIFO_EP_MASK) >> 16);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_RQ_FIFO_FL", (reg_val &
	GLBL2_PCIE_RQ1_RQ_FIFO_FL_MASK) >> 15);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [14,12]      0x%x\n",
	"GLBL2_PCIE_RQ1_TLP", (reg_val &
	GLBL2_PCIE_RQ1_TLPSM_MASK) >> 12);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_TLPSM512", (reg_val &
	GLBL2_PCIE_RQ1_TLPSM512_MASK) >> 9);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_RREQ_RCB_O", (reg_val &
	GLBL2_PCIE_RQ1_RREQ_RCB_OK_MASK) >> 8);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_RREQ0_SLV", (reg_val &
	GLBL2_PCIE_RQ1_RREQ0_SLV_MASK) >> 7);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_RREQ0_VLD", (reg_val &
	GLBL2_PCIE_RQ1_RREQ0_VLD_MASK) >> 6);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_RREQ0_RDY", (reg_val &
	GLBL2_PCIE_RQ1_RREQ0_RDY_MASK) >> 5);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_RREQ1_SLV", (reg_val &
	GLBL2_PCIE_RQ1_RREQ1_SLV_MASK) >> 4);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_RREQ1_VLD", (reg_val &
	GLBL2_PCIE_RQ1_RREQ1_VLD_MASK) >> 3);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_RREQ1_RDY", (reg_val &
	GLBL2_PCIE_RQ1_RREQ1_RDY_MASK) >> 2);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_WTLP_REQ", (reg_val &
	GLBL2_PCIE_RQ1_WTLP_REQ_MASK) >> 1);

	if (rv < 0) {
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
	"GLBL2_PCIE_RQ1_WTLP_STRADDLE", (reg_val &
	GLBL2_PCIE_RQ1_WTLP_STRADDLE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl2_dbg_aximm_wr0_info_dump(
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


int eqdma_glbl2_dbg_aximm_wr1_info_dump(
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


int eqdma_glbl2_dbg_aximm_rd0_info_dump(
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
	"%-40s [16   ]      0x%x\n",
	"GLBL2_AXIMM_RD0_RD_REQ", (reg_val &
	GLBL2_AXIMM_RD0_RD_REQ_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,13]      0x%x\n",
	"GLBL2_AXIMM_RD0_RD_CHNL", (reg_val &
	GLBL2_AXIMM_RD0_RD_CHNL_MASK) >> 13);

	if (rv < 0) {
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


int eqdma_glbl2_dbg_aximm_rd1_info_dump(
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


int eqdma_glbl2_dbg_fab0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"GLBL2_FAB0_H2C_INB_CONV_IN_VLD", (reg_val &
	GLBL2_FAB0_H2C_INB_CONV_IN_VLD_MASK) >> 31);

	if (rv < 0) {
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
	"GLBL2_FAB0_H2C_INB_CONV_IN_RDY", (reg_val &
	GLBL2_FAB0_H2C_INB_CONV_IN_RDY_MASK) >> 30);

	if (rv < 0) {
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
	"GLBL2_FAB0_H2C_SEG_IN_VLD", (reg_val &
	GLBL2_FAB0_H2C_SEG_IN_VLD_MASK) >> 29);

	if (rv < 0) {
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
	"GLBL2_FAB0_H2C_SEG_IN_RDY", (reg_val &
	GLBL2_FAB0_H2C_SEG_IN_RDY_MASK) >> 28);

	if (rv < 0) {
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
	"GLBL2_FAB0_H2C_SEG_OUT_VLD", (reg_val &
	GLBL2_FAB0_H2C_SEG_OUT_VLD_MASK) >> 24);

	if (rv < 0) {
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
	"GLBL2_FAB0_H2C_SEG_OUT_RDY", (reg_val &
	GLBL2_FAB0_H2C_SEG_OUT_RDY_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,16]      0x%x\n",
	"GLBL2_FAB0_H2C_MST_CRDT_STAT", (reg_val &
	GLBL2_FAB0_H2C_MST_CRDT_STAT_MASK) >> 16);

	if (rv < 0) {
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
	"GLBL2_FAB0_C2H_SLV_AFIFO_FULL", (reg_val &
	GLBL2_FAB0_C2H_SLV_AFIFO_FULL_MASK) >> 15);

	if (rv < 0) {
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
	"GLBL2_FAB0_C2H_SLV_AFIFO_EMPTY", (reg_val &
	GLBL2_FAB0_C2H_SLV_AFIFO_EMPTY_MASK) >> 14);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [13,10]      0x%x\n",
	"GLBL2_FAB0_C2H_DESEG_SEG_VLD", (reg_val &
	GLBL2_FAB0_C2H_DESEG_SEG_VLD_MASK) >> 10);

	if (rv < 0) {
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
	"GLBL2_FAB0_C2H_DESEG_SEG_RDY", (reg_val &
	GLBL2_FAB0_C2H_DESEG_SEG_RDY_MASK) >> 9);

	if (rv < 0) {
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
	"GLBL2_FAB0_C2H_DESEG_OUT_VLD", (reg_val &
	GLBL2_FAB0_C2H_DESEG_OUT_VLD_MASK) >> 8);

	if (rv < 0) {
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
	"GLBL2_FAB0_C2H_DESEG_OUT_RDY", (reg_val &
	GLBL2_FAB0_C2H_DESEG_OUT_RDY_MASK) >> 7);

	if (rv < 0) {
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
	"GLBL2_FAB0_C2H_INB_DECONV_OUT_VLD", (reg_val &
	GLBL2_FAB0_C2H_INB_DECONV_OUT_VLD_MASK) >> 6);

	if (rv < 0) {
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
	"GLBL2_FAB0_C2H_INB_DECONV_OUT_RDY", (reg_val &
	GLBL2_FAB0_C2H_INB_DECONV_OUT_RDY_MASK) >> 5);

	if (rv < 0) {
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
	"GLBL2_FAB0_C2H_DSC_CRDT_AFIFO_FULL", (reg_val &
	GLBL2_FAB0_C2H_DSC_CRDT_AFIFO_FULL_MASK) >> 4);

	if (rv < 0) {
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
	"GLBL2_FAB0_C2H_DSC_CRDT_AFIFO_EMPTY", (reg_val &
	GLBL2_FAB0_C2H_DSC_CRDT_AFIFO_EMPTY_MASK) >> 3);

	if (rv < 0) {
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
	"GLBL2_FAB0_IRQ_IN_AFIFO_FULL", (reg_val &
	GLBL2_FAB0_IRQ_IN_AFIFO_FULL_MASK) >> 2);

	if (rv < 0) {
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
	"GLBL2_FAB0_IRQ_IN_AFIFO_EMPTY", (reg_val &
	GLBL2_FAB0_IRQ_IN_AFIFO_EMPTY_MASK) >> 1);

	if (rv < 0) {
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
	"GLBL2_FAB0_IMM_CRD_AFIFO_EMPTY", (reg_val &
	GLBL2_FAB0_IMM_CRD_AFIFO_EMPTY_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl2_dbg_fab1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,25]      0x%x\n",
	"GLBL2_FAB1_BYP_OUT_CRDT_STAT", (reg_val &
	GLBL2_FAB1_BYP_OUT_CRDT_STAT_MASK) >> 25);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [24,18]      0x%x\n",
	"GLBL2_FAB1_TM_DSC_STS_CRDT_STAT", (reg_val &
	GLBL2_FAB1_TM_DSC_STS_CRDT_STAT_MASK) >> 18);

	if (rv < 0) {
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
	"GLBL2_FAB1_C2H_CMN_AFIFO_FULL", (reg_val &
	GLBL2_FAB1_C2H_CMN_AFIFO_FULL_MASK) >> 17);

	if (rv < 0) {
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
	"GLBL2_FAB1_C2H_CMN_AFIFO_EMPTY", (reg_val &
	GLBL2_FAB1_C2H_CMN_AFIFO_EMPTY_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,13]      0x%x\n",
	"GLBL2_FAB1_RSVD_1", (reg_val &
	GLBL2_FAB1_RSVD_1_MASK) >> 13);

	if (rv < 0) {
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
	"GLBL2_FAB1_C2H_BYP_IN_AFIFO_FULL", (reg_val &
	GLBL2_FAB1_C2H_BYP_IN_AFIFO_FULL_MASK) >> 12);

	if (rv < 0) {
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
	"GLBL2_FAB1_RSVD_2", (reg_val &
	GLBL2_FAB1_RSVD_2_MASK) >> 9);

	if (rv < 0) {
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
	"GLBL2_FAB1_C2H_BYP_IN_AFIFO_EMPTY", (reg_val &
	GLBL2_FAB1_C2H_BYP_IN_AFIFO_EMPTY_MASK) >> 8);

	if (rv < 0) {
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
	"GLBL2_FAB1_RSVD_3", (reg_val &
	GLBL2_FAB1_RSVD_3_MASK) >> 5);

	if (rv < 0) {
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
	"GLBL2_FAB1_H2C_BYP_IN_AFIFO_FULL", (reg_val &
	GLBL2_FAB1_H2C_BYP_IN_AFIFO_FULL_MASK) >> 4);

	if (rv < 0) {
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
	"GLBL2_FAB1_RSVD_4", (reg_val &
	GLBL2_FAB1_RSVD_4_MASK) >> 1);

	if (rv < 0) {
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
	"GLBL2_FAB1_H2C_BYP_IN_AFIFO_EMPTY", (reg_val &
	GLBL2_FAB1_H2C_BYP_IN_AFIFO_EMPTY_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl2_dbg_match_sel_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"GLBL2_MATCH_SEL_RSV", (reg_val &
	GLBL2_MATCH_SEL_RSV_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,13]      0x%x\n",
	"GLBL2_MATCH_SEL_CSR_SEL", (reg_val &
	GLBL2_MATCH_SEL_CSR_SEL_MASK) >> 13);

	if (rv < 0) {
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
	"GLBL2_MATCH_SEL_CSR_EN", (reg_val &
	GLBL2_MATCH_SEL_CSR_EN_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,10]      0x%x\n",
	"GLBL2_MATCH_SEL_ROTATE1", (reg_val &
	GLBL2_MATCH_SEL_ROTATE1_MASK) >> 10);

	if (rv < 0) {
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
	"GLBL2_MATCH_SEL_ROTATE0", (reg_val &
	GLBL2_MATCH_SEL_ROTATE0_MASK) >> 8);

	if (rv < 0) {
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
	"GLBL2_MATCH_SEL_SEL", (reg_val &
	GLBL2_MATCH_SEL_SEL_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl2_dbg_match_msk_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"GLBL2_MATCH", (reg_val &
	GLBL2_MATCH_MSK_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl2_dbg_match_pat_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"GLBL2_MATCH_PAT_PATTERN", (reg_val &
	GLBL2_MATCH_PAT_PATTERN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl_rng_sz_1_info_dump(
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


int eqdma_glbl_rng_sz_2_info_dump(
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


int eqdma_glbl_rng_sz_3_info_dump(
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


int eqdma_glbl_rng_sz_4_info_dump(
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


int eqdma_glbl_rng_sz_5_info_dump(
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


int eqdma_glbl_rng_sz_6_info_dump(
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


int eqdma_glbl_rng_sz_7_info_dump(
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


int eqdma_glbl_rng_sz_8_info_dump(
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


int eqdma_glbl_rng_sz_9_info_dump(
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


int eqdma_glbl_rng_sz_a_info_dump(
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


int eqdma_glbl_rng_sz_b_info_dump(
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


int eqdma_glbl_rng_sz_c_info_dump(
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


int eqdma_glbl_rng_sz_d_info_dump(
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


int eqdma_glbl_rng_sz_e_info_dump(
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


int eqdma_glbl_rng_sz_f_info_dump(
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


int eqdma_glbl_rng_sz_10_info_dump(
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


int eqdma_glbl_err_stat_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"GLBL_ERR_STAT_RSVD_1", (reg_val &
	GLBL_ERR_STAT_RSVD_1_MASK) >> 18);

	if (rv < 0) {
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
	"GLBL_ERR_STAT_ERR_FAB", (reg_val &
	GLBL_ERR_STAT_ERR_FAB_MASK) >> 17);

	if (rv < 0) {
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
	"GLBL_ERR_STAT_ERR_H2C_ST", (reg_val &
	GLBL_ERR_STAT_ERR_H2C_ST_MASK) >> 16);

	if (rv < 0) {
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
	"GLBL_ERR_STAT_ERR_BDG", (reg_val &
	GLBL_ERR_STAT_ERR_BDG_MASK) >> 15);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [14,9 ]      0x%x\n",
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


int eqdma_glbl_err_mask_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
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


int eqdma_glbl_dsc_cfg_info_dump(
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


int eqdma_glbl_dsc_err_sts_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,26]      0x%x\n",
	"GLBL_DSC_ERR_STS_RSVD_1", (reg_val &
	GLBL_DSC_ERR_STS_RSVD_1_MASK) >> 26);

	if (rv < 0) {
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
	"GLBL_DSC_ERR_STS_PORT_ID", (reg_val &
	GLBL_DSC_ERR_STS_PORT_ID_MASK) >> 25);

	if (rv < 0) {
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
	"%-40s [8    ]      0x%x\n",
	"GLBL_DSC_ERR_STS_FLR", (reg_val &
	GLBL_DSC_ERR_STS_FLR_MASK) >> 8);

	if (rv < 0) {
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
	"GLBL_DSC_ERR_STS_TAG", (reg_val &
	GLBL_DSC_ERR_STS_TAG_MASK) >> 6);

	if (rv < 0) {
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
	"GLBL_DSC_ERR_STS_ADDR", (reg_val &
	GLBL_DSC_ERR_STS_ADDR_MASK) >> 5);

	if (rv < 0) {
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
	"GLBL_DSC_ERR_STS_PAR", (reg_val &
	GLBL_DSC_ERR_STS_PARAM_MASK) >> 4);

	if (rv < 0) {
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
	"GLBL_DSC_ERR_STS_BCNT", (reg_val &
	GLBL_DSC_ERR_STS_BCNT_MASK) >> 3);

	if (rv < 0) {
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
	"GLBL_DSC_ERR_STS_UR_C", (reg_val &
	GLBL_DSC_ERR_STS_UR_CA_MASK) >> 2);

	if (rv < 0) {
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
	"GLBL_DSC_ERR_STS_POISON", (reg_val &
	GLBL_DSC_ERR_STS_POISON_MASK) >> 1);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl_dsc_err_msk_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
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


int eqdma_glbl_dsc_err_log0_info_dump(
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
	"%-40s [30   ]      0x%x\n",
	"GLBL_DSC_ERR_LOG0_SEL", (reg_val &
	GLBL_DSC_ERR_LOG0_SEL_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29,13]      0x%x\n",
	"GLBL_DSC_ERR_LOG0_RSVD_1", (reg_val &
	GLBL_DSC_ERR_LOG0_RSVD_1_MASK) >> 13);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [12,0 ]      0x%x\n",
	"GLBL_DSC_ERR_LOG0_QID", (reg_val &
	GLBL_DSC_ERR_LOG0_QID_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl_dsc_err_log1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,28]      0x%x\n",
	"GLBL_DSC_ERR_LOG1_RSVD_1", (reg_val &
	GLBL_DSC_ERR_LOG1_RSVD_1_MASK) >> 28);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [27,12]      0x%x\n",
	"GLBL_DSC_ERR_LOG1_CIDX", (reg_val &
	GLBL_DSC_ERR_LOG1_CIDX_MASK) >> 12);

	if (rv < 0) {
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
	"GLBL_DSC_ERR_LOG1_RSVD_2", (reg_val &
	GLBL_DSC_ERR_LOG1_RSVD_2_MASK) >> 9);

	if (rv < 0) {
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


int eqdma_glbl_trq_err_sts_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"GLBL_TRQ_ERR_STS_RSVD_1", (reg_val &
	GLBL_TRQ_ERR_STS_RSVD_1_MASK) >> 8);

	if (rv < 0) {
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
	"GLBL_TRQ_ERR_STS_TCP_QSPC_TIMEOUT", (reg_val &
	GLBL_TRQ_ERR_STS_TCP_QSPC_TIMEOUT_MASK) >> 7);

	if (rv < 0) {
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
	"GLBL_TRQ_ERR_STS_RSVD_2", (reg_val &
	GLBL_TRQ_ERR_STS_RSVD_2_MASK) >> 6);

	if (rv < 0) {
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
	"GLBL_TRQ_ERR_STS_QID_RANGE", (reg_val &
	GLBL_TRQ_ERR_STS_QID_RANGE_MASK) >> 5);

	if (rv < 0) {
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
	"GLBL_TRQ_ERR_STS_QSPC_UNMAPPED", (reg_val &
	GLBL_TRQ_ERR_STS_QSPC_UNMAPPED_MASK) >> 4);

	if (rv < 0) {
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
	"GLBL_TRQ_ERR_STS_TCP_CSR_TIMEOUT", (reg_val &
	GLBL_TRQ_ERR_STS_TCP_CSR_TIMEOUT_MASK) >> 3);

	if (rv < 0) {
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
	"GLBL_TRQ_ERR_STS_RSVD_3", (reg_val &
	GLBL_TRQ_ERR_STS_RSVD_3_MASK) >> 2);

	if (rv < 0) {
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
	"GLBL_TRQ_ERR_STS_VF_ACCESS_ERR", (reg_val &
	GLBL_TRQ_ERR_STS_VF_ACCESS_ERR_MASK) >> 1);

	if (rv < 0) {
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
	"GLBL_TRQ_ERR_STS_CSR_UNMAPPED", (reg_val &
	GLBL_TRQ_ERR_STS_CSR_UNMAPPED_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl_trq_err_msk_info_dump(
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


int eqdma_glbl_trq_err_log_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"GLBL_TRQ_ERR_LOG_SRC", (reg_val &
	GLBL_TRQ_ERR_LOG_SRC_MASK) >> 31);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [30,27]      0x%x\n",
	"GLBL_TRQ_ERR_LOG_TARGET", (reg_val &
	GLBL_TRQ_ERR_LOG_TARGET_MASK) >> 27);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [26,17]      0x%x\n",
	"GLBL_TRQ_ERR_LOG_FUNC", (reg_val &
	GLBL_TRQ_ERR_LOG_FUNC_MASK) >> 17);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [16,0 ]      0x%x\n",
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


int eqdma_glbl_dsc_dbg_dat0_info_dump(
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


int eqdma_glbl_dsc_dbg_dat1_info_dump(
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


int eqdma_glbl_dsc_dbg_ctl_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,3 ]      0x%x\n",
	"GLBL_DSC_CTL_RSVD_1", (reg_val &
	GLBL_DSC_CTL_RSVD_1_MASK) >> 3);

	if (rv < 0) {
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
	"GLBL_DSC_CTL_SELECT", (reg_val &
	GLBL_DSC_CTL_SELECT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl_dsc_err_log2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"GLBL_DSC_ERR_LOG2_OLD_PIDX", (reg_val &
	GLBL_DSC_ERR_LOG2_OLD_PIDX_MASK) >> 16);

	if (rv < 0) {
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
	"GLBL_DSC_ERR_LOG2_NEW_PIDX", (reg_val &
	GLBL_DSC_ERR_LOG2_NEW_PIDX_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl_glbl_interrupt_cfg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,2 ]      0x%x\n",
	"GLBL_GLBL_INTERRUPT_CFG_RSVD_1", (reg_val &
	GLBL_GLBL_INTERRUPT_CFG_RSVD_1_MASK) >> 2);

	if (rv < 0) {
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
	"GLBL_GLBL_INTERRUPT_CFG_LGCY_INTR_PENDING", (reg_val &
	GLBL_GLBL_INTERRUPT_CFG_LGCY_INTR_PENDING_MASK) >> 1);

	if (rv < 0) {
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
	"GLBL_GLBL_INTERRUPT_CFG_EN_LGCY_INTR", (reg_val &
	GLBL_GLBL_INTERRUPT_CFG_EN_LGCY_INTR_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl_vch_host_profile_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,28]      0x%x\n",
	"GLBL_VCH_HOST_PROFILE_RSVD_1", (reg_val &
	GLBL_VCH_HOST_PROFILE_RSVD_1_MASK) >> 28);

	if (rv < 0) {
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
	"GLBL_VCH_HOST_PROFILE_2C", (reg_val &
	GLBL_VCH_HOST_PROFILE_2C_MM_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,20]      0x%x\n",
	"GLBL_VCH_HOST_PROFILE_2C_ST", (reg_val &
	GLBL_VCH_HOST_PROFILE_2C_ST_MASK) >> 20);

	if (rv < 0) {
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
	"GLBL_VCH_HOST_PROFILE_VCH_DSC", (reg_val &
	GLBL_VCH_HOST_PROFILE_VCH_DSC_MASK) >> 16);

	if (rv < 0) {
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
	"GLBL_VCH_HOST_PROFILE_VCH_INT_MSG", (reg_val &
	GLBL_VCH_HOST_PROFILE_VCH_INT_MSG_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,8 ]      0x%x\n",
	"GLBL_VCH_HOST_PROFILE_VCH_INT_AGGR", (reg_val &
	GLBL_VCH_HOST_PROFILE_VCH_INT_AGGR_MASK) >> 8);

	if (rv < 0) {
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
	"GLBL_VCH_HOST_PROFILE_VCH_CMPT", (reg_val &
	GLBL_VCH_HOST_PROFILE_VCH_CMPT_MASK) >> 4);

	if (rv < 0) {
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
	"GLBL_VCH_HOST_PROFILE_VCH_C2H_PLD", (reg_val &
	GLBL_VCH_HOST_PROFILE_VCH_C2H_PLD_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl_bridge_host_profile_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,4 ]      0x%x\n",
	"GLBL_BRIDGE_HOST_PROFILE_RSVD_1", (reg_val &
	GLBL_BRIDGE_HOST_PROFILE_RSVD_1_MASK) >> 4);

	if (rv < 0) {
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
	"GLBL_BRIDGE_HOST_PROFILE_BDGID", (reg_val &
	GLBL_BRIDGE_HOST_PROFILE_BDGID_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_aximm_irq_dest_addr_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"AXIMM_IRQ_DEST_ADDR_ADDR", (reg_val &
	AXIMM_IRQ_DEST_ADDR_ADDR_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_fab_err_log_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,7 ]      0x%x\n",
	"FAB_ERR_LOG_RSVD_1", (reg_val &
	FAB_ERR_LOG_RSVD_1_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6 ,0 ]      0x%x\n",
	"FAB_ERR_LOG_SRC", (reg_val &
	FAB_ERR_LOG_SRC_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl_req_err_sts_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,11]      0x%x\n",
	"GLBL_REQ_ERR_STS_RSVD_1", (reg_val &
	GLBL_REQ_ERR_STS_RSVD_1_MASK) >> 11);

	if (rv < 0) {
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
	"GLBL_REQ_ERR_STS_RC_DISCONTINUE", (reg_val &
	GLBL_REQ_ERR_STS_RC_DISCONTINUE_MASK) >> 10);

	if (rv < 0) {
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
	"GLBL_REQ_ERR_STS_RC_PRTY", (reg_val &
	GLBL_REQ_ERR_STS_RC_PRTY_MASK) >> 9);

	if (rv < 0) {
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
	"GLBL_REQ_ERR_STS_RC_FLR", (reg_val &
	GLBL_REQ_ERR_STS_RC_FLR_MASK) >> 8);

	if (rv < 0) {
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
	"GLBL_REQ_ERR_STS_RC_TIMEOUT", (reg_val &
	GLBL_REQ_ERR_STS_RC_TIMEOUT_MASK) >> 7);

	if (rv < 0) {
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
	"GLBL_REQ_ERR_STS_RC_INV_BCNT", (reg_val &
	GLBL_REQ_ERR_STS_RC_INV_BCNT_MASK) >> 6);

	if (rv < 0) {
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
	"GLBL_REQ_ERR_STS_RC_INV_TAG", (reg_val &
	GLBL_REQ_ERR_STS_RC_INV_TAG_MASK) >> 5);

	if (rv < 0) {
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
	"GLBL_REQ_ERR_STS_RC_START_ADDR_MISMCH", (reg_val &
	GLBL_REQ_ERR_STS_RC_START_ADDR_MISMCH_MASK) >> 4);

	if (rv < 0) {
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
	"GLBL_REQ_ERR_STS_RC_RID_TC_ATTR_MISMCH", (reg_val &
	GLBL_REQ_ERR_STS_RC_RID_TC_ATTR_MISMCH_MASK) >> 3);

	if (rv < 0) {
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
	"GLBL_REQ_ERR_STS_RC_NO_DAT", (reg_val &
	GLBL_REQ_ERR_STS_RC_NO_DATA_MASK) >> 2);

	if (rv < 0) {
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
	"GLBL_REQ_ERR_STS_RC_UR_CA_CR", (reg_val &
	GLBL_REQ_ERR_STS_RC_UR_CA_CRS_MASK) >> 1);

	if (rv < 0) {
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
	"GLBL_REQ_ERR_STS_RC_POISONED", (reg_val &
	GLBL_REQ_ERR_STS_RC_POISONED_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_glbl_req_err_msk_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"GLBL_REQ_ERR", (reg_val &
	GLBL_REQ_ERR_MSK_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_ind_ctxt_data_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"IND_CTXT_DATA_DAT", (reg_val &
	IND_CTXT_DATA_DATA_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_ind_ctxt_mask_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"IND_CTXT", (reg_val &
	IND_CTXT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_ind_ctxt_cmd_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,20]      0x%x\n",
	"IND_CTXT_CMD_RSVD_1", (reg_val &
	IND_CTXT_CMD_RSVD_1_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19,7 ]      0x%x\n",
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
	"IND_CTXT_CMD_SEL", (reg_val &
	IND_CTXT_CMD_SEL_MASK) >> 1);

	if (rv < 0) {
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


int eqdma_c2h_timer_cnt_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_TIMER_CNT_RSVD_1", (reg_val &
	C2H_TIMER_CNT_RSVD_1_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_TIMER_CNT", (reg_val &
	C2H_TIMER_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_cnt_th_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_CNT_TH_RSVD_1", (reg_val &
	C2H_CNT_TH_RSVD_1_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_CNT_TH_THESHOLD_CNT", (reg_val &
	C2H_CNT_TH_THESHOLD_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_stat_s_axis_c2h_accepted_info_dump(
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


int eqdma_c2h_stat_s_axis_wrb_accepted_info_dump(
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


int eqdma_c2h_stat_desc_rsp_pkt_accepted_info_dump(
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


int eqdma_c2h_stat_axis_pkg_cmp_info_dump(
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


int eqdma_c2h_stat_desc_rsp_accepted_info_dump(
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


int eqdma_c2h_stat_desc_rsp_cmp_info_dump(
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


int eqdma_c2h_stat_wrq_out_info_dump(
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


int eqdma_c2h_stat_wpl_ren_accepted_info_dump(
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


int eqdma_c2h_stat_total_wrq_len_info_dump(
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


int eqdma_c2h_stat_total_wpl_len_info_dump(
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


int eqdma_c2h_buf_sz_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_BUF_SZ_IZE", (reg_val &
	C2H_BUF_SZ_IZE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_err_stat_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,21]      0x%x\n",
	"C2H_ERR_STAT_RSVD_1", (reg_val &
	C2H_ERR_STAT_RSVD_1_MASK) >> 21);

	if (rv < 0) {
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
	"C2H_ERR_STAT_WRB_PORT_ID_ERR", (reg_val &
	C2H_ERR_STAT_WRB_PORT_ID_ERR_MASK) >> 20);

	if (rv < 0) {
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
	"C2H_ERR_STAT_HDR_PAR_ERR", (reg_val &
	C2H_ERR_STAT_HDR_PAR_ERR_MASK) >> 19);

	if (rv < 0) {
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
	"C2H_ERR_STAT_HDR_ECC_COR_ERR", (reg_val &
	C2H_ERR_STAT_HDR_ECC_COR_ERR_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_ERR_STAT_HDR_ECC_UNC_ERR", (reg_val &
	C2H_ERR_STAT_HDR_ECC_UNC_ERR_MASK) >> 17);

	if (rv < 0) {
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
	"C2H_ERR_STAT_AVL_RING_DSC_ERR", (reg_val &
	C2H_ERR_STAT_AVL_RING_DSC_ERR_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_ERR_STAT_RSVD_2", (reg_val &
	C2H_ERR_STAT_RSVD_2_MASK) >> 11);

	if (rv < 0) {
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
	"C2H_ERR_STAT_RSVD_3", (reg_val &
	C2H_ERR_STAT_RSVD_3_MASK) >> 8);

	if (rv < 0) {
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
	"C2H_ERR_STAT_RSVD_4", (reg_val &
	C2H_ERR_STAT_RSVD_4_MASK) >> 5);

	if (rv < 0) {
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
	"C2H_ERR_STAT_SH_CMPT_DSC_ERR", (reg_val &
	C2H_ERR_STAT_SH_CMPT_DSC_ERR_MASK) >> 2);

	if (rv < 0) {
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


int eqdma_c2h_err_mask_info_dump(
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


int eqdma_c2h_fatal_err_stat_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,21]      0x%x\n",
	"C2H_FATAL_ERR_STAT_RSVD_1", (reg_val &
	C2H_FATAL_ERR_STAT_RSVD_1_MASK) >> 21);

	if (rv < 0) {
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
	"C2H_FATAL_ERR_STAT_HDR_ECC_UNC_ERR", (reg_val &
	C2H_FATAL_ERR_STAT_HDR_ECC_UNC_ERR_MASK) >> 20);

	if (rv < 0) {
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
	"C2H_FATAL_ERR_STAT_AVL_RING_FIFO_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_AVL_RING_FIFO_RAM_RDBE_MASK) >> 19);

	if (rv < 0) {
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
	"C2H_FATAL_ERR_STAT_CMPT_FIFO_RAM_RDBE", (reg_val &
	C2H_FATAL_ERR_STAT_CMPT_FIFO_RAM_RDBE_MASK) >> 15);

	if (rv < 0) {
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
	"C2H_FATAL_ERR_STAT_RESERVED2", (reg_val &
	C2H_FATAL_ERR_STAT_RESERVED2_MASK) >> 13);

	if (rv < 0) {
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
	"C2H_FATAL_ERR_STAT_RESERVED1", (reg_val &
	C2H_FATAL_ERR_STAT_RESERVED1_MASK) >> 2);

	if (rv < 0) {
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


int eqdma_c2h_fatal_err_mask_info_dump(
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


int eqdma_c2h_fatal_err_enable_info_dump(
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


int eqdma_glbl_err_int_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,30]      0x%x\n",
	"GLBL_ERR_INT_RSVD_1", (reg_val &
	GLBL_ERR_INT_RSVD_1_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29,26]      0x%x\n",
	"GLBL_ERR_INT_HOST_ID", (reg_val &
	GLBL_ERR_INT_HOST_ID_MASK) >> 26);

	if (rv < 0) {
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
	"GLBL_ERR_INT_DIS_INTR_ON_VF", (reg_val &
	GLBL_ERR_INT_DIS_INTR_ON_VF_MASK) >> 25);

	if (rv < 0) {
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
	"GLBL_ERR_INT_AR", (reg_val &
	GLBL_ERR_INT_ARM_MASK) >> 24);

	if (rv < 0) {
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
	"GLBL_ERR_INT_EN_COAL", (reg_val &
	GLBL_ERR_INT_EN_COAL_MASK) >> 23);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [22,12]      0x%x\n",
	"GLBL_ERR_INT_VEC", (reg_val &
	GLBL_ERR_INT_VEC_MASK) >> 12);

	if (rv < 0) {
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


int eqdma_c2h_pfch_cfg_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_PFCH_CFG_EVTFL_TH", (reg_val &
	C2H_PFCH_CFG_EVTFL_TH_MASK) >> 16);

	if (rv < 0) {
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


int eqdma_c2h_pfch_cfg_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_PFCH_CFG_1_EVT_QCNT_TH", (reg_val &
	C2H_PFCH_CFG_1_EVT_QCNT_TH_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_PFCH_CFG_1_QCNT", (reg_val &
	C2H_PFCH_CFG_1_QCNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_pfch_cfg_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"C2H_PFCH_CFG_2_FENCE", (reg_val &
	C2H_PFCH_CFG_2_FENCE_MASK) >> 31);

	if (rv < 0) {
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
	"C2H_PFCH_CFG_2_RSVD", (reg_val &
	C2H_PFCH_CFG_2_RSVD_MASK) >> 29);

	if (rv < 0) {
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
	"C2H_PFCH_CFG_2_VAR_DESC_NO_DROP", (reg_val &
	C2H_PFCH_CFG_2_VAR_DESC_NO_DROP_MASK) >> 28);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [27,12]      0x%x\n",
	"C2H_PFCH_CFG_2_LL_SZ_TH", (reg_val &
	C2H_PFCH_CFG_2_LL_SZ_TH_MASK) >> 12);

	if (rv < 0) {
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
	"C2H_PFCH_CFG_2_VAR_DESC_NU", (reg_val &
	C2H_PFCH_CFG_2_VAR_DESC_NUM_MASK) >> 6);

	if (rv < 0) {
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
	"C2H_PFCH_CFG_2_NU", (reg_val &
	C2H_PFCH_CFG_2_NUM_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_int_timer_tick_info_dump(
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


int eqdma_c2h_stat_desc_rsp_drop_accepted_info_dump(
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


int eqdma_c2h_stat_desc_rsp_err_accepted_info_dump(
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


int eqdma_c2h_stat_desc_req_info_dump(
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


int eqdma_c2h_stat_dbg_dma_eng_0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"C2H_STAT_DMA_ENG_0_S_AXIS_C2H_TVALID", (reg_val &
	C2H_STAT_DMA_ENG_0_S_AXIS_C2H_TVALID_MASK) >> 31);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_0_S_AXIS_C2H_TREADY", (reg_val &
	C2H_STAT_DMA_ENG_0_S_AXIS_C2H_TREADY_MASK) >> 30);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [29,27]      0x%x\n",
	"C2H_STAT_DMA_ENG_0_S_AXIS_WRB_TVALID", (reg_val &
	C2H_STAT_DMA_ENG_0_S_AXIS_WRB_TVALID_MASK) >> 27);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [26,24]      0x%x\n",
	"C2H_STAT_DMA_ENG_0_S_AXIS_WRB_TREADY", (reg_val &
	C2H_STAT_DMA_ENG_0_S_AXIS_WRB_TREADY_MASK) >> 24);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_0_PLD_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_0_PLD_FIFO_IN_RDY_MASK) >> 23);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_0_QID_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_0_QID_FIFO_IN_RDY_MASK) >> 22);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_0_ARB_FIFO_OUT_VLD", (reg_val &
	C2H_STAT_DMA_ENG_0_ARB_FIFO_OUT_VLD_MASK) >> 21);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [20,9 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_0_ARB_FIFO_OUT_QID", (reg_val &
	C2H_STAT_DMA_ENG_0_ARB_FIFO_OUT_QID_MASK) >> 9);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_0_WRB_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_0_WRB_FIFO_IN_RDY_MASK) >> 8);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_0_WRB_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_0_WRB_FIFO_OUT_CNT_MASK) >> 5);

	if (rv < 0) {
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


int eqdma_c2h_stat_dbg_dma_eng_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,29]      0x%x\n",
	"C2H_STAT_DMA_ENG_1_RSVD_1", (reg_val &
	C2H_STAT_DMA_ENG_1_RSVD_1_MASK) >> 29);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [28,18]      0x%x\n",
	"C2H_STAT_DMA_ENG_1_QID_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_1_QID_FIFO_OUT_CNT_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_1_PLD_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_1_PLD_FIFO_OUT_CNT_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6 ,0 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_1_PLD_ST_FIFO_CNT", (reg_val &
	C2H_STAT_DMA_ENG_1_PLD_ST_FIFO_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_stat_dbg_dma_eng_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,29]      0x%x\n",
	"C2H_STAT_DMA_ENG_2_RSVD_1", (reg_val &
	C2H_STAT_DMA_ENG_2_RSVD_1_MASK) >> 29);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [28,18]      0x%x\n",
	"C2H_STAT_DMA_ENG_2_QID_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_2_QID_FIFO_OUT_CNT_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_2_PLD_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_2_PLD_FIFO_OUT_CNT_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6 ,0 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_2_PLD_ST_FIFO_CNT", (reg_val &
	C2H_STAT_DMA_ENG_2_PLD_ST_FIFO_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_stat_dbg_dma_eng_3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,24]      0x%x\n",
	"C2H_STAT_DMA_ENG_3_RSVD_1", (reg_val &
	C2H_STAT_DMA_ENG_3_RSVD_1_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,19]      0x%x\n",
	"C2H_STAT_DMA_ENG_3_WRQ_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_3_WRQ_FIFO_OUT_CNT_MASK) >> 19);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_QID_FIFO_OUT_VLD", (reg_val &
	C2H_STAT_DMA_ENG_3_QID_FIFO_OUT_VLD_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_PLD_FIFO_OUT_VLD", (reg_val &
	C2H_STAT_DMA_ENG_3_PLD_FIFO_OUT_VLD_MASK) >> 17);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_PLD_ST_FIFO_OUT_VLD", (reg_val &
	C2H_STAT_DMA_ENG_3_PLD_ST_FIFO_OUT_VLD_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_PLD_ST_FIFO_OUT_DATA_EOP", (reg_val &
	C2H_STAT_DMA_ENG_3_PLD_ST_FIFO_OUT_DATA_EOP_MASK) >> 15);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_PLD_ST_FIFO_OUT_DATA_AVL_IDX_ENABLE", (reg_val &
	C2H_STAT_DMA_ENG_3_PLD_ST_FIFO_OUT_DATA_AVL_IDX_ENABLE_MASK) >> 14);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_PLD_ST_FIFO_OUT_DATA_DROP", (reg_val &
	C2H_STAT_DMA_ENG_3_PLD_ST_FIFO_OUT_DATA_DROP_MASK) >> 13);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_PLD_ST_FIFO_OUT_DATA_ERR", (reg_val &
	C2H_STAT_DMA_ENG_3_PLD_ST_FIFO_OUT_DATA_ERR_MASK) >> 12);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_DESC_CNT_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_3_DESC_CNT_FIFO_IN_RDY_MASK) >> 11);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_DESC_RSP_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_3_DESC_RSP_FIFO_IN_RDY_MASK) >> 10);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_PLD_PKT_ID_LARGER_0", (reg_val &
	C2H_STAT_DMA_ENG_3_PLD_PKT_ID_LARGER_0_MASK) >> 9);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_WRQ_VLD", (reg_val &
	C2H_STAT_DMA_ENG_3_WRQ_VLD_MASK) >> 8);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_WRQ_RDY", (reg_val &
	C2H_STAT_DMA_ENG_3_WRQ_RDY_MASK) >> 7);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_WRQ_FIFO_OUT_RDY", (reg_val &
	C2H_STAT_DMA_ENG_3_WRQ_FIFO_OUT_RDY_MASK) >> 6);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_WRQ_PACKET_OUT_DATA_DROP", (reg_val &
	C2H_STAT_DMA_ENG_3_WRQ_PACKET_OUT_DATA_DROP_MASK) >> 5);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_WRQ_PACKET_OUT_DATA_ERR", (reg_val &
	C2H_STAT_DMA_ENG_3_WRQ_PACKET_OUT_DATA_ERR_MASK) >> 4);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_WRQ_PACKET_OUT_DATA_MARKER", (reg_val &
	C2H_STAT_DMA_ENG_3_WRQ_PACKET_OUT_DATA_MARKER_MASK) >> 3);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_WRQ_PACKET_PRE_EOR", (reg_val &
	C2H_STAT_DMA_ENG_3_WRQ_PACKET_PRE_EOR_MASK) >> 2);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_WCP_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_3_WCP_FIFO_IN_RDY_MASK) >> 1);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_3_PLD_ST_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_3_PLD_ST_FIFO_IN_RDY_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_dbg_pfch_err_ctxt_info_dump(
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


int eqdma_c2h_first_err_qid_info_dump(
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
	"C2H_FIRST_ERR_QID_ERR_TYPE", (reg_val &
	C2H_FIRST_ERR_QID_ERR_TYPE_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,13]      0x%x\n",
	"C2H_FIRST_ERR_QID_RSVD", (reg_val &
	C2H_FIRST_ERR_QID_RSVD_MASK) >> 13);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [12,0 ]      0x%x\n",
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


int eqdma_stat_num_wrb_in_info_dump(
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


int eqdma_stat_num_wrb_out_info_dump(
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


int eqdma_stat_num_wrb_drp_info_dump(
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


int eqdma_stat_num_stat_desc_out_info_dump(
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


int eqdma_stat_num_dsc_crdt_sent_info_dump(
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


int eqdma_stat_num_fch_dsc_rcvd_info_dump(
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


int eqdma_stat_num_byp_dsc_rcvd_info_dump(
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


int eqdma_c2h_wrb_coal_cfg_info_dump(
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


int eqdma_c2h_intr_h2c_req_info_dump(
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


int eqdma_c2h_intr_c2h_mm_req_info_dump(
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


int eqdma_c2h_intr_err_int_req_info_dump(
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


int eqdma_c2h_intr_c2h_st_req_info_dump(
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


int eqdma_c2h_intr_h2c_err_c2h_mm_msix_ack_info_dump(
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


int eqdma_c2h_intr_h2c_err_c2h_mm_msix_fail_info_dump(
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


int eqdma_c2h_intr_h2c_err_c2h_mm_msix_no_msix_info_dump(
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


int eqdma_c2h_intr_h2c_err_c2h_mm_ctxt_inval_info_dump(
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


int eqdma_c2h_intr_c2h_st_msix_ack_info_dump(
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


int eqdma_c2h_intr_c2h_st_msix_fail_info_dump(
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


int eqdma_c2h_intr_c2h_st_no_msix_info_dump(
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


int eqdma_c2h_intr_c2h_st_ctxt_inval_info_dump(
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


int eqdma_c2h_stat_wr_cmp_info_dump(
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


int eqdma_c2h_stat_dbg_dma_eng_4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,24]      0x%x\n",
	"C2H_STAT_DMA_ENG_4_RSVD_1", (reg_val &
	C2H_STAT_DMA_ENG_4_RSVD_1_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,19]      0x%x\n",
	"C2H_STAT_DMA_ENG_4_WRQ_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_4_WRQ_FIFO_OUT_CNT_MASK) >> 19);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_QID_FIFO_OUT_VLD", (reg_val &
	C2H_STAT_DMA_ENG_4_QID_FIFO_OUT_VLD_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_PLD_FIFO_OUT_VLD", (reg_val &
	C2H_STAT_DMA_ENG_4_PLD_FIFO_OUT_VLD_MASK) >> 17);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_PLD_ST_FIFO_OUT_VLD", (reg_val &
	C2H_STAT_DMA_ENG_4_PLD_ST_FIFO_OUT_VLD_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_PLD_ST_FIFO_OUT_DATA_EOP", (reg_val &
	C2H_STAT_DMA_ENG_4_PLD_ST_FIFO_OUT_DATA_EOP_MASK) >> 15);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_PLD_ST_FIFO_OUT_DATA_AVL_IDX_ENABLE", (reg_val &
	C2H_STAT_DMA_ENG_4_PLD_ST_FIFO_OUT_DATA_AVL_IDX_ENABLE_MASK) >> 14);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_PLD_ST_FIFO_OUT_DATA_DROP", (reg_val &
	C2H_STAT_DMA_ENG_4_PLD_ST_FIFO_OUT_DATA_DROP_MASK) >> 13);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_PLD_ST_FIFO_OUT_DATA_ERR", (reg_val &
	C2H_STAT_DMA_ENG_4_PLD_ST_FIFO_OUT_DATA_ERR_MASK) >> 12);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_DESC_CNT_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_4_DESC_CNT_FIFO_IN_RDY_MASK) >> 11);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_DESC_RSP_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_4_DESC_RSP_FIFO_IN_RDY_MASK) >> 10);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_PLD_PKT_ID_LARGER_0", (reg_val &
	C2H_STAT_DMA_ENG_4_PLD_PKT_ID_LARGER_0_MASK) >> 9);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_WRQ_VLD", (reg_val &
	C2H_STAT_DMA_ENG_4_WRQ_VLD_MASK) >> 8);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_WRQ_RDY", (reg_val &
	C2H_STAT_DMA_ENG_4_WRQ_RDY_MASK) >> 7);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_WRQ_FIFO_OUT_RDY", (reg_val &
	C2H_STAT_DMA_ENG_4_WRQ_FIFO_OUT_RDY_MASK) >> 6);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_WRQ_PACKET_OUT_DATA_DROP", (reg_val &
	C2H_STAT_DMA_ENG_4_WRQ_PACKET_OUT_DATA_DROP_MASK) >> 5);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_WRQ_PACKET_OUT_DATA_ERR", (reg_val &
	C2H_STAT_DMA_ENG_4_WRQ_PACKET_OUT_DATA_ERR_MASK) >> 4);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_WRQ_PACKET_OUT_DATA_MARKER", (reg_val &
	C2H_STAT_DMA_ENG_4_WRQ_PACKET_OUT_DATA_MARKER_MASK) >> 3);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_WRQ_PACKET_PRE_EOR", (reg_val &
	C2H_STAT_DMA_ENG_4_WRQ_PACKET_PRE_EOR_MASK) >> 2);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_WCP_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_4_WCP_FIFO_IN_RDY_MASK) >> 1);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_4_PLD_ST_FIFO_IN_RDY", (reg_val &
	C2H_STAT_DMA_ENG_4_PLD_ST_FIFO_IN_RDY_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_stat_dbg_dma_eng_5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,30]      0x%x\n",
	"C2H_STAT_DMA_ENG_5_RSVD_1", (reg_val &
	C2H_STAT_DMA_ENG_5_RSVD_1_MASK) >> 30);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_5_WRB_SM_VIRT_CH", (reg_val &
	C2H_STAT_DMA_ENG_5_WRB_SM_VIRT_CH_MASK) >> 29);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [28,24]      0x%x\n",
	"C2H_STAT_DMA_ENG_5_WRB_FIFO_IN_REQ", (reg_val &
	C2H_STAT_DMA_ENG_5_WRB_FIFO_IN_REQ_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,22]      0x%x\n",
	"C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_CNT", (reg_val &
	C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_CNT_MASK) >> 22);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [21,6 ]      0x%x\n",
	"C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_LEN", (reg_val &
	C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_LEN_MASK) >> 6);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_VIRT_CH", (reg_val &
	C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_VIRT_CH_MASK) >> 5);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_VAR_DESC", (reg_val &
	C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_VAR_DESC_MASK) >> 4);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_DROP_REQ", (reg_val &
	C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_DROP_REQ_MASK) >> 3);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_NUM_BUF_OV", (reg_val &
	C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_NUM_BUF_OV_MASK) >> 2);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_MARKER", (reg_val &
	C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_MARKER_MASK) >> 1);

	if (rv < 0) {
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
	"C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_HAS_CMPT", (reg_val &
	C2H_STAT_DMA_ENG_5_ARB_FIFO_OUT_DATA_HAS_CMPT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_dbg_pfch_qid_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_PFCH_QID_RSVD_1", (reg_val &
	C2H_PFCH_QID_RSVD_1_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_PFCH_QID_ERR_CTXT", (reg_val &
	C2H_PFCH_QID_ERR_CTXT_MASK) >> 15);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [14,12]      0x%x\n",
	"C2H_PFCH_QID_TARGET", (reg_val &
	C2H_PFCH_QID_TARGET_MASK) >> 12);

	if (rv < 0) {
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


int eqdma_c2h_dbg_pfch_info_dump(
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


int eqdma_c2h_int_dbg_info_dump(
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


int eqdma_c2h_stat_imm_accepted_info_dump(
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


int eqdma_c2h_stat_marker_accepted_info_dump(
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


int eqdma_c2h_stat_disable_cmp_accepted_info_dump(
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


int eqdma_c2h_pld_fifo_crdt_cnt_info_dump(
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


int eqdma_c2h_intr_dyn_req_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_DYN_REQ_RSVD_1", (reg_val &
	C2H_INTR_DYN_REQ_RSVD_1_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_INTR_DYN_REQ_CNT", (reg_val &
	C2H_INTR_DYN_REQ_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_intr_dyn_misc_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_INTR_DYN_MISC_RSVD_1", (reg_val &
	C2H_INTR_DYN_MISC_RSVD_1_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_INTR_DYN_MISC_CNT", (reg_val &
	C2H_INTR_DYN_MISC_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_drop_len_mismatch_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_DROP_LEN_MISMATCH_RSVD_1", (reg_val &
	C2H_DROP_LEN_MISMATCH_RSVD_1_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_DROP_LEN_MISMATCH_CNT", (reg_val &
	C2H_DROP_LEN_MISMATCH_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_drop_desc_rsp_len_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_DROP_DESC_RSP_LEN_RSVD_1", (reg_val &
	C2H_DROP_DESC_RSP_LEN_RSVD_1_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_DROP_DESC_RSP_LEN_CNT", (reg_val &
	C2H_DROP_DESC_RSP_LEN_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_drop_qid_fifo_len_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_DROP_QID_FIFO_LEN_RSVD_1", (reg_val &
	C2H_DROP_QID_FIFO_LEN_RSVD_1_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_DROP_QID_FIFO_LEN_CNT", (reg_val &
	C2H_DROP_QID_FIFO_LEN_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_drop_pld_cnt_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_DROP_PLD_CNT_RSVD_1", (reg_val &
	C2H_DROP_PLD_CNT_RSVD_1_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_DROP_PLD_CNT_CNT", (reg_val &
	C2H_DROP_PLD_CNT_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_cmpt_format_0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_CMPT_FORMAT_0_DESC_ERR_LOC", (reg_val &
	C2H_CMPT_FORMAT_0_DESC_ERR_LOC_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_CMPT_FORMAT_0_COLOR_LOC", (reg_val &
	C2H_CMPT_FORMAT_0_COLOR_LOC_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_cmpt_format_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_CMPT_FORMAT_1_DESC_ERR_LOC", (reg_val &
	C2H_CMPT_FORMAT_1_DESC_ERR_LOC_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_CMPT_FORMAT_1_COLOR_LOC", (reg_val &
	C2H_CMPT_FORMAT_1_COLOR_LOC_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_cmpt_format_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_CMPT_FORMAT_2_DESC_ERR_LOC", (reg_val &
	C2H_CMPT_FORMAT_2_DESC_ERR_LOC_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_CMPT_FORMAT_2_COLOR_LOC", (reg_val &
	C2H_CMPT_FORMAT_2_COLOR_LOC_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_cmpt_format_3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_CMPT_FORMAT_3_DESC_ERR_LOC", (reg_val &
	C2H_CMPT_FORMAT_3_DESC_ERR_LOC_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_CMPT_FORMAT_3_COLOR_LOC", (reg_val &
	C2H_CMPT_FORMAT_3_COLOR_LOC_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_cmpt_format_4_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_CMPT_FORMAT_4_DESC_ERR_LOC", (reg_val &
	C2H_CMPT_FORMAT_4_DESC_ERR_LOC_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_CMPT_FORMAT_4_COLOR_LOC", (reg_val &
	C2H_CMPT_FORMAT_4_COLOR_LOC_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_cmpt_format_5_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_CMPT_FORMAT_5_DESC_ERR_LOC", (reg_val &
	C2H_CMPT_FORMAT_5_DESC_ERR_LOC_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_CMPT_FORMAT_5_COLOR_LOC", (reg_val &
	C2H_CMPT_FORMAT_5_COLOR_LOC_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_cmpt_format_6_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_CMPT_FORMAT_6_DESC_ERR_LOC", (reg_val &
	C2H_CMPT_FORMAT_6_DESC_ERR_LOC_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_CMPT_FORMAT_6_COLOR_LOC", (reg_val &
	C2H_CMPT_FORMAT_6_COLOR_LOC_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_pfch_cache_depth_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,16]      0x%x\n",
	"C2H_PFCH_CACHE_DEPTH_MAX_STBUF", (reg_val &
	C2H_PFCH_CACHE_DEPTH_MAX_STBUF_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_PFCH_CACHE_DEPTH", (reg_val &
	C2H_PFCH_CACHE_DEPTH_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_wrb_coal_buf_depth_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,8 ]      0x%x\n",
	"C2H_WRB_COAL_BUF_DEPTH_RSVD_1", (reg_val &
	C2H_WRB_COAL_BUF_DEPTH_RSVD_1_MASK) >> 8);

	if (rv < 0) {
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
	"C2H_WRB_COAL_BUF_DEPTH_BUFFER", (reg_val &
	C2H_WRB_COAL_BUF_DEPTH_BUFFER_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_pfch_crdt_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,1 ]      0x%x\n",
	"C2H_PFCH_CRDT_RSVD_1", (reg_val &
	C2H_PFCH_CRDT_RSVD_1_MASK) >> 1);

	if (rv < 0) {
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
	"C2H_PFCH_CRDT_RSVD_2", (reg_val &
	C2H_PFCH_CRDT_RSVD_2_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_stat_has_cmpt_accepted_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_STAT_HAS_CMPT_ACCEPTED_RSVD_1", (reg_val &
	C2H_STAT_HAS_CMPT_ACCEPTED_RSVD_1_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_STAT_HAS_CMPT_ACCEPTED_CNT", (reg_val &
	C2H_STAT_HAS_CMPT_ACCEPTED_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_stat_has_pld_accepted_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_STAT_HAS_PLD_ACCEPTED_RSVD_1", (reg_val &
	C2H_STAT_HAS_PLD_ACCEPTED_RSVD_1_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_STAT_HAS_PLD_ACCEPTED_CNT", (reg_val &
	C2H_STAT_HAS_PLD_ACCEPTED_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_pld_pkt_id_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_PLD_PKT_ID_CMPT_WAIT", (reg_val &
	C2H_PLD_PKT_ID_CMPT_WAIT_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_PLD_PKT_ID_DAT", (reg_val &
	C2H_PLD_PKT_ID_DATA_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_pld_pkt_id_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_PLD_PKT_ID_1_CMPT_WAIT", (reg_val &
	C2H_PLD_PKT_ID_1_CMPT_WAIT_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_PLD_PKT_ID_1_DAT", (reg_val &
	C2H_PLD_PKT_ID_1_DATA_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_drop_pld_cnt_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_DROP_PLD_CNT_1_RSVD_1", (reg_val &
	C2H_DROP_PLD_CNT_1_RSVD_1_MASK) >> 18);

	if (rv < 0) {
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
	"C2H_DROP_PLD_CNT_1_CNT", (reg_val &
	C2H_DROP_PLD_CNT_1_CNT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_h2c_err_stat_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,6 ]      0x%x\n",
	"H2C_ERR_STAT_RSVD_1", (reg_val &
	H2C_ERR_STAT_RSVD_1_MASK) >> 6);

	if (rv < 0) {
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
	"H2C_ERR_STAT_PAR_ERR", (reg_val &
	H2C_ERR_STAT_PAR_ERR_MASK) >> 5);

	if (rv < 0) {
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


int eqdma_h2c_err_mask_info_dump(
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


int eqdma_h2c_first_err_qid_info_dump(
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
	"%-40s [15,13]      0x%x\n",
	"H2C_FIRST_ERR_QID_RSVD_2", (reg_val &
	H2C_FIRST_ERR_QID_RSVD_2_MASK) >> 13);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [12,0 ]      0x%x\n",
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


int eqdma_h2c_dbg_reg0_info_dump(
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


int eqdma_h2c_dbg_reg1_info_dump(
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


int eqdma_h2c_dbg_reg2_info_dump(
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


int eqdma_h2c_dbg_reg3_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"H2C_REG3_RSVD_1", (reg_val &
	H2C_REG3_RSVD_1_MASK) >> 31);

	if (rv < 0) {
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


int eqdma_h2c_dbg_reg4_info_dump(
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


int eqdma_h2c_fatal_err_en_info_dump(
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


int eqdma_h2c_req_throt_pcie_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"H2C_REQ_THROT_PCIE_EN_REQ", (reg_val &
	H2C_REQ_THROT_PCIE_EN_REQ_MASK) >> 31);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [30,19]      0x%x\n",
	"H2C_REQ_THROT_PCIE", (reg_val &
	H2C_REQ_THROT_PCIE_MASK) >> 19);

	if (rv < 0) {
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
	"H2C_REQ_THROT_PCIE_EN_DAT", (reg_val &
	H2C_REQ_THROT_PCIE_EN_DATA_MASK) >> 18);

	if (rv < 0) {
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
	"H2C_REQ_THROT_PCIE_DATA_THRESH", (reg_val &
	H2C_REQ_THROT_PCIE_DATA_THRESH_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_h2c_aln_dbg_reg0_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,0 ]      0x%x\n",
	"H2C_ALN_REG0_NUM_PKT_SENT", (reg_val &
	H2C_ALN_REG0_NUM_PKT_SENT_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_h2c_req_throt_aximm_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"H2C_REQ_THROT_AXIMM_EN_REQ", (reg_val &
	H2C_REQ_THROT_AXIMM_EN_REQ_MASK) >> 31);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [30,19]      0x%x\n",
	"H2C_REQ_THROT_AXI", (reg_val &
	H2C_REQ_THROT_AXIMM_MASK) >> 19);

	if (rv < 0) {
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
	"H2C_REQ_THROT_AXIMM_EN_DAT", (reg_val &
	H2C_REQ_THROT_AXIMM_EN_DATA_MASK) >> 18);

	if (rv < 0) {
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
	"H2C_REQ_THROT_AXIMM_DATA_THRESH", (reg_val &
	H2C_REQ_THROT_AXIMM_DATA_THRESH_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_mm_ctl_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,9 ]      0x%x\n",
	"C2H_MM_CTL_RESERVED1", (reg_val &
	C2H_MM_CTL_RESERVED1_MASK) >> 9);

	if (rv < 0) {
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
	"C2H_MM_CTL_ERRC_EN", (reg_val &
	C2H_MM_CTL_ERRC_EN_MASK) >> 8);

	if (rv < 0) {
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
	"C2H_MM_CTL_RESERVED0", (reg_val &
	C2H_MM_CTL_RESERVED0_MASK) >> 1);

	if (rv < 0) {
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
	"C2H_MM_CTL_RUN", (reg_val &
	C2H_MM_CTL_RUN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_mm_status_info_dump(
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


int eqdma_c2h_mm_cmpl_desc_cnt_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_MM_CMPL_DESC_CNT_C2H_CO", (reg_val &
	C2H_MM_CMPL_DESC_CNT_C2H_CO_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_mm_err_code_enable_mask_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"C2H_MM_ERR_CODE_ENABLE_RESERVED1", (reg_val &
	C2H_MM_ERR_CODE_ENABLE_RESERVED1_MASK) >> 31);

	if (rv < 0) {
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
	"C2H_MM_ERR_CODE_ENABLE_RESERVED0", (reg_val &
	C2H_MM_ERR_CODE_ENABLE_RESERVED0_MASK) >> 2);

	if (rv < 0) {
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


int eqdma_c2h_mm_err_code_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,28]      0x%x\n",
	"C2H_MM_ERR_CODE_RESERVED1", (reg_val &
	C2H_MM_ERR_CODE_RESERVED1_MASK) >> 28);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [27,12]      0x%x\n",
	"C2H_MM_ERR_CODE_CIDX", (reg_val &
	C2H_MM_ERR_CODE_CIDX_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,10]      0x%x\n",
	"C2H_MM_ERR_CODE_RESERVED0", (reg_val &
	C2H_MM_ERR_CODE_RESERVED0_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,5 ]      0x%x\n",
	"C2H_MM_ERR_CODE_SUB_TYPE", (reg_val &
	C2H_MM_ERR_CODE_SUB_TYPE_MASK) >> 5);

	if (rv < 0) {
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


int eqdma_c2h_mm_err_info_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"C2H_MM_ERR_INFO_VALID", (reg_val &
	C2H_MM_ERR_INFO_VALID_MASK) >> 31);

	if (rv < 0) {
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
	"C2H_MM_ERR_INFO_SEL", (reg_val &
	C2H_MM_ERR_INFO_SEL_MASK) >> 30);

	if (rv < 0) {
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
	"C2H_MM_ERR_INFO_RSVD_1", (reg_val &
	C2H_MM_ERR_INFO_RSVD_1_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,0 ]      0x%x\n",
	"C2H_MM_ERR_INFO_QID", (reg_val &
	C2H_MM_ERR_INFO_QID_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_mm_perf_mon_ctl_info_dump(
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


int eqdma_c2h_mm_perf_mon_cycle_cnt0_info_dump(
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


int eqdma_c2h_mm_perf_mon_cycle_cnt1_info_dump(
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


int eqdma_c2h_mm_perf_mon_data_cnt0_info_dump(
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


int eqdma_c2h_mm_perf_mon_data_cnt1_info_dump(
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


int eqdma_c2h_mm_dbg_info_dump(
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


int eqdma_h2c_mm_ctl_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,9 ]      0x%x\n",
	"H2C_MM_CTL_RESERVED1", (reg_val &
	H2C_MM_CTL_RESERVED1_MASK) >> 9);

	if (rv < 0) {
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
	"H2C_MM_CTL_ERRC_EN", (reg_val &
	H2C_MM_CTL_ERRC_EN_MASK) >> 8);

	if (rv < 0) {
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
	"H2C_MM_CTL_RESERVED0", (reg_val &
	H2C_MM_CTL_RESERVED0_MASK) >> 1);

	if (rv < 0) {
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
	"H2C_MM_CTL_RUN", (reg_val &
	H2C_MM_CTL_RUN_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_h2c_mm_status_info_dump(
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


int eqdma_h2c_mm_cmpl_desc_cnt_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"H2C_MM_CMPL_DESC_CNT_H2C_CO", (reg_val &
	H2C_MM_CMPL_DESC_CNT_H2C_CO_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_h2c_mm_err_code_enable_mask_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,30]      0x%x\n",
	"H2C_MM_ERR_CODE_ENABLE_RESERVED5", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RESERVED5_MASK) >> 30);

	if (rv < 0) {
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
	"H2C_MM_ERR_CODE_ENABLE_RESERVED4", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RESERVED4_MASK) >> 23);

	if (rv < 0) {
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
	"H2C_MM_ERR_CODE_ENABLE_RESERVED3", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RESERVED3_MASK) >> 17);

	if (rv < 0) {
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
	"H2C_MM_ERR_CODE_ENABLE_RESERVED2", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RESERVED2_MASK) >> 9);

	if (rv < 0) {
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
	"H2C_MM_ERR_CODE_ENABLE_RESERVED1", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RESERVED1_MASK) >> 6);

	if (rv < 0) {
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
	"H2C_MM_ERR_CODE_ENABLE_RESERVED0", (reg_val &
	H2C_MM_ERR_CODE_ENABLE_RESERVED0_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_h2c_mm_err_code_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,28]      0x%x\n",
	"H2C_MM_ERR_CODE_RSVD_1", (reg_val &
	H2C_MM_ERR_CODE_RSVD_1_MASK) >> 28);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [27,12]      0x%x\n",
	"H2C_MM_ERR_CODE_CIDX", (reg_val &
	H2C_MM_ERR_CODE_CIDX_MASK) >> 12);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [11,10]      0x%x\n",
	"H2C_MM_ERR_CODE_RESERVED0", (reg_val &
	H2C_MM_ERR_CODE_RESERVED0_MASK) >> 10);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [9 ,5 ]      0x%x\n",
	"H2C_MM_ERR_CODE_SUB_TYPE", (reg_val &
	H2C_MM_ERR_CODE_SUB_TYPE_MASK) >> 5);

	if (rv < 0) {
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


int eqdma_h2c_mm_err_info_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31   ]      0x%x\n",
	"H2C_MM_ERR_INFO_VALID", (reg_val &
	H2C_MM_ERR_INFO_VALID_MASK) >> 31);

	if (rv < 0) {
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
	"H2C_MM_ERR_INFO_SEL", (reg_val &
	H2C_MM_ERR_INFO_SEL_MASK) >> 30);

	if (rv < 0) {
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
	"H2C_MM_ERR_INFO_RSVD_1", (reg_val &
	H2C_MM_ERR_INFO_RSVD_1_MASK) >> 24);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [23,0 ]      0x%x\n",
	"H2C_MM_ERR_INFO_QID", (reg_val &
	H2C_MM_ERR_INFO_QID_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_h2c_mm_perf_mon_ctl_info_dump(
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


int eqdma_h2c_mm_perf_mon_cycle_cnt0_info_dump(
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


int eqdma_h2c_mm_perf_mon_cycle_cnt1_info_dump(
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


int eqdma_h2c_mm_perf_mon_data_cnt0_info_dump(
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


int eqdma_h2c_mm_perf_mon_data_cnt1_info_dump(
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


int eqdma_h2c_mm_dbg_info_dump(
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


int eqdma_c2h_crdt_coal_cfg_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,18]      0x%x\n",
	"C2H_CRDT_COAL_CFG_1_RSVD_1", (reg_val &
	C2H_CRDT_COAL_CFG_1_RSVD_1_MASK) >> 18);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [17,10]      0x%x\n",
	"C2H_CRDT_COAL_CFG_1_PLD_FIFO_TH", (reg_val &
	C2H_CRDT_COAL_CFG_1_PLD_FIFO_TH_MASK) >> 10);

	if (rv < 0) {
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
	"C2H_CRDT_COAL_CFG_1_TIMER_TH", (reg_val &
	C2H_CRDT_COAL_CFG_1_TIMER_TH_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_crdt_coal_cfg_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,24]      0x%x\n",
	"C2H_CRDT_COAL_CFG_2_RSVD_1", (reg_val &
	C2H_CRDT_COAL_CFG_2_RSVD_1_MASK) >> 24);

	if (rv < 0) {
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
	"C2H_CRDT_COAL_CFG_2_FIFO_TH", (reg_val &
	C2H_CRDT_COAL_CFG_2_FIFO_TH_MASK) >> 16);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [15,11]      0x%x\n",
	"C2H_CRDT_COAL_CFG_2_RESERVED1", (reg_val &
	C2H_CRDT_COAL_CFG_2_RESERVED1_MASK) >> 11);

	if (rv < 0) {
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
	"C2H_CRDT_COAL_CFG_2_NT_TH", (reg_val &
	C2H_CRDT_COAL_CFG_2_NT_TH_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_pfch_byp_qid_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,12]      0x%x\n",
	"C2H_PFCH_BYP_QID_RSVD_1", (reg_val &
	C2H_PFCH_BYP_QID_RSVD_1_MASK) >> 12);

	if (rv < 0) {
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
	"C2H_PFCH_BYP_QID", (reg_val &
	C2H_PFCH_BYP_QID_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_pfch_byp_tag_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,20]      0x%x\n",
	"C2H_PFCH_BYP_TAG_RSVD_1", (reg_val &
	C2H_PFCH_BYP_TAG_RSVD_1_MASK) >> 20);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [19,8 ]      0x%x\n",
	"C2H_PFCH_BYP_TAG_BYP_QID", (reg_val &
	C2H_PFCH_BYP_TAG_BYP_QID_MASK) >> 8);

	if (rv < 0) {
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
	"C2H_PFCH_BYP_TAG_RSVD_2", (reg_val &
	C2H_PFCH_BYP_TAG_RSVD_2_MASK) >> 7);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;


	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [6 ,0 ]      0x%x\n",
	"C2H_PFCH_BYP_TAG", (reg_val &
	C2H_PFCH_BYP_TAG_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_water_mark_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_WATER_MARK_HIGH_W", (reg_val &
	C2H_WATER_MARK_HIGH_WM_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_WATER_MARK_LOW_W", (reg_val &
	C2H_WATER_MARK_LOW_WM_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_notify_empty_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,16]      0x%x\n",
	"C2H_NOTIFY_EMPTY_RSVD_1", (reg_val &
	C2H_NOTIFY_EMPTY_RSVD_1_MASK) >> 16);

	if (rv < 0) {
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
	"C2H_NOTIFY_EMPTY_NOE", (reg_val &
	C2H_NOTIFY_EMPTY_NOE_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_stat_s_axis_c2h_accepted_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_S_AXIS_C2H_ACCEPTED_1", (reg_val &
	C2H_STAT_S_AXIS_C2H_ACCEPTED_1_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_stat_s_axis_wrb_accepted_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_S_AXIS_WRB_ACCEPTED_1", (reg_val &
	C2H_STAT_S_AXIS_WRB_ACCEPTED_1_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_stat_desc_rsp_pkt_accepted_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_DESC_RSP_PKT_ACCEPTED_1_D", (reg_val &
	C2H_STAT_DESC_RSP_PKT_ACCEPTED_1_D_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_stat_axis_pkg_cmp_1_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_AXIS_PKG_CMP_1", (reg_val &
	C2H_STAT_AXIS_PKG_CMP_1_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_stat_s_axis_wrb_accepted_2_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_STAT_S_AXIS_WRB_ACCEPTED_2", (reg_val &
	C2H_STAT_S_AXIS_WRB_ACCEPTED_2_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_c2h_st_pld_fifo_depth_info_dump(
		uint32_t reg_val, char *buf, uint32_t buf_len)
{
	int len = 0, rv = 0;

	rv = QDMA_SNPRINTF_S(buf + len, buf_len - len,
	DEBGFS_LINE_SZ,
	"%-40s [31,0 ]      0x%x\n",
	"C2H_ST_PLD_FIFO_DEPTH", (reg_val &
	C2H_ST_PLD_FIFO_DEPTH_MASK) >> 0);

	if (rv < 0) {
		qdma_log_error(
		"%s Buff too small, err:%d\n",
		__func__,
		-QDMA_ERR_NO_MEM);
		return -QDMA_ERR_NO_MEM;
	}
	len += rv;

	return len;
}


int eqdma_func_status_reg_info_dump(
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


int eqdma_func_cmd_reg_info_dump(
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


int eqdma_func_interrupt_vector_reg_info_dump(
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


int eqdma_target_func_reg_info_dump(
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


int eqdma_func_interrupt_ctl_reg_info_dump(
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

struct xreg_info eqdma_config_regs[] = {
{"CFG_BLK_IDENTIFIER", 0x00,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_blk_identifier_info_dump },
{"CFG_BLK_PCIE_MAX_PLD_SIZE", 0x08,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_blk_pcie_max_pld_size_info_dump },
{"CFG_BLK_PCIE_MAX_READ_REQ_SIZE", 0x0c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_blk_pcie_max_read_req_size_info_dump },
{"CFG_BLK_SYSTEM_ID", 0x10,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_blk_system_id_info_dump },
{"CFG_BLK_MSIX_ENABLE", 0x014,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_blk_msix_enable_info_dump },
{"CFG_PCIE_DATA_WIDTH", 0x18,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_pcie_data_width_info_dump },
{"CFG_PCIE_CTL", 0x1c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_pcie_ctl_info_dump },
{"CFG_BLK_MSI_ENABLE", 0x20,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_blk_msi_enable_info_dump },
{"CFG_AXI_USER_MAX_PLD_SIZE", 0x40,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_axi_user_max_pld_size_info_dump },
{"CFG_AXI_USER_MAX_READ_REQ_SIZE", 0x44,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_axi_user_max_read_req_size_info_dump },
{"CFG_BLK_MISC_CTL", 0x4c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_blk_misc_ctl_info_dump },
{"CFG_PL_CRED_CTL", 0x68,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_pl_cred_ctl_info_dump },
{"CFG_BLK_SCRATCH", 0x80,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_blk_scratch_info_dump },
{"CFG_GIC", 0xa0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_cfg_gic_info_dump },
{"RAM_SBE_MSK_1_A", 0xe0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_ram_sbe_msk_1_a_info_dump },
{"RAM_SBE_STS_1_A", 0xe4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_ram_sbe_sts_1_a_info_dump },
{"RAM_DBE_MSK_1_A", 0xe8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_ram_dbe_msk_1_a_info_dump },
{"RAM_DBE_STS_1_A", 0xec,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_ram_dbe_sts_1_a_info_dump },
{"RAM_SBE_MSK_A", 0xf0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_ram_sbe_msk_a_info_dump },
{"RAM_SBE_STS_A", 0xf4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_ram_sbe_sts_a_info_dump },
{"RAM_DBE_MSK_A", 0xf8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_ram_dbe_msk_a_info_dump },
{"RAM_DBE_STS_A", 0xfc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_ram_dbe_sts_a_info_dump },
{"GLBL2_IDENTIFIER", 0x100,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_identifier_info_dump },
{"GLBL2_CHANNEL_INST", 0x114,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_channel_inst_info_dump },
{"GLBL2_CHANNEL_MDMA", 0x118,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_channel_mdma_info_dump },
{"GLBL2_CHANNEL_STRM", 0x11c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_channel_strm_info_dump },
{"GLBL2_CHANNEL_CAP", 0x120,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_channel_cap_info_dump },
{"GLBL2_CHANNEL_PASID_CAP", 0x128,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_channel_pasid_cap_info_dump },
{"GLBL2_SYSTEM_ID", 0x130,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_system_id_info_dump },
{"GLBL2_MISC_CAP", 0x134,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_misc_cap_info_dump },
{"GLBL2_DBG_PCIE_RQ0", 0x1b8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_dbg_pcie_rq0_info_dump },
{"GLBL2_DBG_PCIE_RQ1", 0x1bc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_dbg_pcie_rq1_info_dump },
{"GLBL2_DBG_AXIMM_WR0", 0x1c0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_dbg_aximm_wr0_info_dump },
{"GLBL2_DBG_AXIMM_WR1", 0x1c4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_dbg_aximm_wr1_info_dump },
{"GLBL2_DBG_AXIMM_RD0", 0x1c8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_dbg_aximm_rd0_info_dump },
{"GLBL2_DBG_AXIMM_RD1", 0x1cc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_dbg_aximm_rd1_info_dump },
{"GLBL2_DBG_FAB0", 0x1d0,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_dbg_fab0_info_dump },
{"GLBL2_DBG_FAB1", 0x1d4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_dbg_fab1_info_dump },
{"GLBL2_DBG_MATCH_SEL", 0x1f4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_dbg_match_sel_info_dump },
{"GLBL2_DBG_MATCH_MSK", 0x1f8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_dbg_match_msk_info_dump },
{"GLBL2_DBG_MATCH_PAT", 0x1fc,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl2_dbg_match_pat_info_dump },
{"GLBL_RNG_SZ_1", 0x204,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_1_info_dump },
{"GLBL_RNG_SZ_2", 0x208,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_2_info_dump },
{"GLBL_RNG_SZ_3", 0x20c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_3_info_dump },
{"GLBL_RNG_SZ_4", 0x210,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_4_info_dump },
{"GLBL_RNG_SZ_5", 0x214,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_5_info_dump },
{"GLBL_RNG_SZ_6", 0x218,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_6_info_dump },
{"GLBL_RNG_SZ_7", 0x21c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_7_info_dump },
{"GLBL_RNG_SZ_8", 0x220,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_8_info_dump },
{"GLBL_RNG_SZ_9", 0x224,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_9_info_dump },
{"GLBL_RNG_SZ_A", 0x228,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_a_info_dump },
{"GLBL_RNG_SZ_B", 0x22c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_b_info_dump },
{"GLBL_RNG_SZ_C", 0x230,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_c_info_dump },
{"GLBL_RNG_SZ_D", 0x234,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_d_info_dump },
{"GLBL_RNG_SZ_E", 0x238,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_e_info_dump },
{"GLBL_RNG_SZ_F", 0x23c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_f_info_dump },
{"GLBL_RNG_SZ_10", 0x240,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_rng_sz_10_info_dump },
{"GLBL_ERR_STAT", 0x248,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_err_stat_info_dump },
{"GLBL_ERR_MASK", 0x24c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_err_mask_info_dump },
{"GLBL_DSC_CFG", 0x250,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_dsc_cfg_info_dump },
{"GLBL_DSC_ERR_STS", 0x254,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_dsc_err_sts_info_dump },
{"GLBL_DSC_ERR_MSK", 0x258,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_dsc_err_msk_info_dump },
{"GLBL_DSC_ERR_LOG0", 0x25c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_dsc_err_log0_info_dump },
{"GLBL_DSC_ERR_LOG1", 0x260,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_dsc_err_log1_info_dump },
{"GLBL_TRQ_ERR_STS", 0x264,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_trq_err_sts_info_dump },
{"GLBL_TRQ_ERR_MSK", 0x268,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_trq_err_msk_info_dump },
{"GLBL_TRQ_ERR_LOG", 0x26c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_trq_err_log_info_dump },
{"GLBL_DSC_DBG_DAT0", 0x270,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_dsc_dbg_dat0_info_dump },
{"GLBL_DSC_DBG_DAT1", 0x274,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_dsc_dbg_dat1_info_dump },
{"GLBL_DSC_DBG_CTL", 0x278,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_dsc_dbg_ctl_info_dump },
{"GLBL_DSC_ERR_LOG2", 0x27c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_dsc_err_log2_info_dump },
{"GLBL_GLBL_INTERRUPT_CFG", 0x2c4,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_glbl_interrupt_cfg_info_dump },
{"GLBL_VCH_HOST_PROFILE", 0x2c8,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_vch_host_profile_info_dump },
{"GLBL_BRIDGE_HOST_PROFILE", 0x308,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_bridge_host_profile_info_dump },
{"AXIMM_IRQ_DEST_ADDR", 0x30c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_aximm_irq_dest_addr_info_dump },
{"FAB_ERR_LOG", 0x314,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_fab_err_log_info_dump },
{"GLBL_REQ_ERR_STS", 0x318,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl_req_err_sts_info_dump },
{"GLBL_REQ_ERR_MSK", 0x31c,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_glbl_req_err_msk_info_dump },
{"IND_CTXT_DATA", 0x804,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_ind_ctxt_data_info_dump },
{"IND_CTXT_MASK", 0x824,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_ind_ctxt_mask_info_dump },
{"IND_CTXT_CMD", 0x844,
	1, 0, 0, 0,
	0, QDMA_MM_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_ind_ctxt_cmd_info_dump },
{"C2H_TIMER_CNT", 0xa00,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_timer_cnt_info_dump },
{"C2H_CNT_TH", 0xa40,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_cnt_th_info_dump },
{"C2H_STAT_S_AXIS_C2H_ACCEPTED", 0xa88,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_stat_s_axis_c2h_accepted_info_dump },
{"C2H_STAT_S_AXIS_WRB_ACCEPTED", 0xa8c,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_stat_s_axis_wrb_accepted_info_dump },
{"C2H_STAT_DESC_RSP_PKT_ACCEPTED", 0xa90,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_stat_desc_rsp_pkt_accepted_info_dump },
{"C2H_STAT_AXIS_PKG_CMP", 0xa94,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_stat_axis_pkg_cmp_info_dump },
{"C2H_STAT_DESC_RSP_ACCEPTED", 0xa98,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_desc_rsp_accepted_info_dump },
{"C2H_STAT_DESC_RSP_CMP", 0xa9c,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_desc_rsp_cmp_info_dump },
{"C2H_STAT_WRQ_OUT", 0xaa0,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_wrq_out_info_dump },
{"C2H_STAT_WPL_REN_ACCEPTED", 0xaa4,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_wpl_ren_accepted_info_dump },
{"C2H_STAT_TOTAL_WRQ_LEN", 0xaa8,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_total_wrq_len_info_dump },
{"C2H_STAT_TOTAL_WPL_LEN", 0xaac,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_total_wpl_len_info_dump },
{"C2H_BUF_SZ", 0xab0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_buf_sz_info_dump },
{"C2H_ERR_STAT", 0xaf0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_err_stat_info_dump },
{"C2H_ERR_MASK", 0xaf4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_err_mask_info_dump },
{"C2H_FATAL_ERR_STAT", 0xaf8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_fatal_err_stat_info_dump },
{"C2H_FATAL_ERR_MASK", 0xafc,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_fatal_err_mask_info_dump },
{"C2H_FATAL_ERR_ENABLE", 0xb00,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_fatal_err_enable_info_dump },
{"GLBL_ERR_INT", 0xb04,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_glbl_err_int_info_dump },
{"C2H_PFCH_CFG", 0xb08,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_pfch_cfg_info_dump },
{"C2H_PFCH_CFG_1", 0xa80,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_pfch_cfg_1_info_dump },
{"C2H_PFCH_CFG_2", 0xa84,
	1, 0, 0, 0,
	0, QDMA_COMPLETION_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_pfch_cfg_2_info_dump },
{"C2H_INT_TIMER_TICK", 0xb0c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_int_timer_tick_info_dump },
{"C2H_STAT_DESC_RSP_DROP_ACCEPTED", 0xb10,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_stat_desc_rsp_drop_accepted_info_dump },
{"C2H_STAT_DESC_RSP_ERR_ACCEPTED", 0xb14,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_stat_desc_rsp_err_accepted_info_dump },
{"C2H_STAT_DESC_REQ", 0xb18,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_desc_req_info_dump },
{"C2H_STAT_DBG_DMA_ENG_0", 0xb1c,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_dbg_dma_eng_0_info_dump },
{"C2H_STAT_DBG_DMA_ENG_1", 0xb20,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_dbg_dma_eng_1_info_dump },
{"C2H_STAT_DBG_DMA_ENG_2", 0xb24,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_dbg_dma_eng_2_info_dump },
{"C2H_STAT_DBG_DMA_ENG_3", 0xb28,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_dbg_dma_eng_3_info_dump },
{"C2H_DBG_PFCH_ERR_CTXT", 0xb2c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_dbg_pfch_err_ctxt_info_dump },
{"C2H_FIRST_ERR_QID", 0xb30,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_first_err_qid_info_dump },
{"STAT_NUM_WRB_IN", 0xb34,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_stat_num_wrb_in_info_dump },
{"STAT_NUM_WRB_OUT", 0xb38,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_stat_num_wrb_out_info_dump },
{"STAT_NUM_WRB_DRP", 0xb3c,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_stat_num_wrb_drp_info_dump },
{"STAT_NUM_STAT_DESC_OUT", 0xb40,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_stat_num_stat_desc_out_info_dump },
{"STAT_NUM_DSC_CRDT_SENT", 0xb44,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_stat_num_dsc_crdt_sent_info_dump },
{"STAT_NUM_FCH_DSC_RCVD", 0xb48,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_stat_num_fch_dsc_rcvd_info_dump },
{"STAT_NUM_BYP_DSC_RCVD", 0xb4c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_stat_num_byp_dsc_rcvd_info_dump },
{"C2H_WRB_COAL_CFG", 0xb50,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_wrb_coal_cfg_info_dump },
{"C2H_INTR_H2C_REQ", 0xb54,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_intr_h2c_req_info_dump },
{"C2H_INTR_C2H_MM_REQ", 0xb58,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_intr_c2h_mm_req_info_dump },
{"C2H_INTR_ERR_INT_REQ", 0xb5c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_intr_err_int_req_info_dump },
{"C2H_INTR_C2H_ST_REQ", 0xb60,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_intr_c2h_st_req_info_dump },
{"C2H_INTR_H2C_ERR_C2H_MM_MSIX_ACK", 0xb64,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_intr_h2c_err_c2h_mm_msix_ack_info_dump },
{"C2H_INTR_H2C_ERR_C2H_MM_MSIX_FAIL", 0xb68,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_intr_h2c_err_c2h_mm_msix_fail_info_dump },
{"C2H_INTR_H2C_ERR_C2H_MM_MSIX_NO_MSIX", 0xb6c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_intr_h2c_err_c2h_mm_msix_no_msix_info_dump },
{"C2H_INTR_H2C_ERR_C2H_MM_CTXT_INVAL", 0xb70,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_intr_h2c_err_c2h_mm_ctxt_inval_info_dump },
{"C2H_INTR_C2H_ST_MSIX_ACK", 0xb74,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_intr_c2h_st_msix_ack_info_dump },
{"C2H_INTR_C2H_ST_MSIX_FAIL", 0xb78,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_c2h_intr_c2h_st_msix_fail_info_dump },
{"C2H_INTR_C2H_ST_NO_MSIX", 0xb7c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_intr_c2h_st_no_msix_info_dump },
{"C2H_INTR_C2H_ST_CTXT_INVAL", 0xb80,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_intr_c2h_st_ctxt_inval_info_dump },
{"C2H_STAT_WR_CMP", 0xb84,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_wr_cmp_info_dump },
{"C2H_STAT_DBG_DMA_ENG_4", 0xb88,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_dbg_dma_eng_4_info_dump },
{"C2H_STAT_DBG_DMA_ENG_5", 0xb8c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_dbg_dma_eng_5_info_dump },
{"C2H_DBG_PFCH_QID", 0xb90,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_dbg_pfch_qid_info_dump },
{"C2H_DBG_PFCH", 0xb94,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_dbg_pfch_info_dump },
{"C2H_INT_DBG", 0xb98,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_int_dbg_info_dump },
{"C2H_STAT_IMM_ACCEPTED", 0xb9c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_imm_accepted_info_dump },
{"C2H_STAT_MARKER_ACCEPTED", 0xba0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_marker_accepted_info_dump },
{"C2H_STAT_DISABLE_CMP_ACCEPTED", 0xba4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_disable_cmp_accepted_info_dump },
{"C2H_PLD_FIFO_CRDT_CNT", 0xba8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_pld_fifo_crdt_cnt_info_dump },
{"C2H_INTR_DYN_REQ", 0xbac,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_intr_dyn_req_info_dump },
{"C2H_INTR_DYN_MISC", 0xbb0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_intr_dyn_misc_info_dump },
{"C2H_DROP_LEN_MISMATCH", 0xbb4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_drop_len_mismatch_info_dump },
{"C2H_DROP_DESC_RSP_LEN", 0xbb8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_drop_desc_rsp_len_info_dump },
{"C2H_DROP_QID_FIFO_LEN", 0xbbc,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_drop_qid_fifo_len_info_dump },
{"C2H_DROP_PLD_CNT", 0xbc0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_drop_pld_cnt_info_dump },
{"C2H_CMPT_FORMAT_0", 0xbc4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_cmpt_format_0_info_dump },
{"C2H_CMPT_FORMAT_1", 0xbc8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_cmpt_format_1_info_dump },
{"C2H_CMPT_FORMAT_2", 0xbcc,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_cmpt_format_2_info_dump },
{"C2H_CMPT_FORMAT_3", 0xbd0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_cmpt_format_3_info_dump },
{"C2H_CMPT_FORMAT_4", 0xbd4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_cmpt_format_4_info_dump },
{"C2H_CMPT_FORMAT_5", 0xbd8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_cmpt_format_5_info_dump },
{"C2H_CMPT_FORMAT_6", 0xbdc,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_cmpt_format_6_info_dump },
{"C2H_PFCH_CACHE_DEPTH", 0xbe0,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_pfch_cache_depth_info_dump },
{"C2H_WRB_COAL_BUF_DEPTH", 0xbe4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_wrb_coal_buf_depth_info_dump },
{"C2H_PFCH_CRDT", 0xbe8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_pfch_crdt_info_dump },
{"C2H_STAT_HAS_CMPT_ACCEPTED", 0xbec,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_has_cmpt_accepted_info_dump },
{"C2H_STAT_HAS_PLD_ACCEPTED", 0xbf0,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_has_pld_accepted_info_dump },
{"C2H_PLD_PKT_ID", 0xbf4,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_pld_pkt_id_info_dump },
{"C2H_PLD_PKT_ID_1", 0xbf8,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_pld_pkt_id_1_info_dump },
{"C2H_DROP_PLD_CNT_1", 0xbfc,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_drop_pld_cnt_1_info_dump },
{"H2C_ERR_STAT", 0xe00,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_h2c_err_stat_info_dump },
{"H2C_ERR_MASK", 0xe04,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_h2c_err_mask_info_dump },
{"H2C_FIRST_ERR_QID", 0xe08,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_h2c_first_err_qid_info_dump },
{"H2C_DBG_REG0", 0xe0c,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_dbg_reg0_info_dump },
{"H2C_DBG_REG1", 0xe10,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_dbg_reg1_info_dump },
{"H2C_DBG_REG2", 0xe14,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_dbg_reg2_info_dump },
{"H2C_DBG_REG3", 0xe18,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_dbg_reg3_info_dump },
{"H2C_DBG_REG4", 0xe1c,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_dbg_reg4_info_dump },
{"H2C_FATAL_ERR_EN", 0xe20,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_VF,
	&eqdma_h2c_fatal_err_en_info_dump },
{"H2C_REQ_THROT_PCIE", 0xe24,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_req_throt_pcie_info_dump },
{"H2C_ALN_DBG_REG0", 0xe28,
	1, 0, 0, 0,
	1, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_aln_dbg_reg0_info_dump },
{"H2C_REQ_THROT_AXIMM", 0xe2c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_req_throt_aximm_info_dump },
{"C2H_MM_CTL", 0x1004,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_mm_ctl_info_dump },
{"C2H_MM_STATUS", 0x1040,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_mm_status_info_dump },
{"C2H_MM_CMPL_DESC_CNT", 0x1048,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_mm_cmpl_desc_cnt_info_dump },
{"C2H_MM_ERR_CODE_ENABLE_MASK", 0x1054,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_mm_err_code_enable_mask_info_dump },
{"C2H_MM_ERR_CODE", 0x1058,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_mm_err_code_info_dump },
{"C2H_MM_ERR_INFO", 0x105c,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_mm_err_info_info_dump },
{"C2H_MM_PERF_MON_CTL", 0x10c0,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_mm_perf_mon_ctl_info_dump },
{"C2H_MM_PERF_MON_CYCLE_CNT0", 0x10c4,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_mm_perf_mon_cycle_cnt0_info_dump },
{"C2H_MM_PERF_MON_CYCLE_CNT1", 0x10c8,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_mm_perf_mon_cycle_cnt1_info_dump },
{"C2H_MM_PERF_MON_DATA_CNT0", 0x10cc,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_mm_perf_mon_data_cnt0_info_dump },
{"C2H_MM_PERF_MON_DATA_CNT1", 0x10d0,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_mm_perf_mon_data_cnt1_info_dump },
{"C2H_MM_DBG", 0x10e8,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_mm_dbg_info_dump },
{"H2C_MM_CTL", 0x1204,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_mm_ctl_info_dump },
{"H2C_MM_STATUS", 0x1240,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_mm_status_info_dump },
{"H2C_MM_CMPL_DESC_CNT", 0x1248,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_mm_cmpl_desc_cnt_info_dump },
{"H2C_MM_ERR_CODE_ENABLE_MASK", 0x1254,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_mm_err_code_enable_mask_info_dump },
{"H2C_MM_ERR_CODE", 0x1258,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_mm_err_code_info_dump },
{"H2C_MM_ERR_INFO", 0x125c,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_mm_err_info_info_dump },
{"H2C_MM_PERF_MON_CTL", 0x12c0,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_mm_perf_mon_ctl_info_dump },
{"H2C_MM_PERF_MON_CYCLE_CNT0", 0x12c4,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_mm_perf_mon_cycle_cnt0_info_dump },
{"H2C_MM_PERF_MON_CYCLE_CNT1", 0x12c8,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_mm_perf_mon_cycle_cnt1_info_dump },
{"H2C_MM_PERF_MON_DATA_CNT0", 0x12cc,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_mm_perf_mon_data_cnt0_info_dump },
{"H2C_MM_PERF_MON_DATA_CNT1", 0x12d0,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_mm_perf_mon_data_cnt1_info_dump },
{"H2C_MM_DBG", 0x12e8,
	1, 0, 0, 0,
	0, QDMA_MM_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_h2c_mm_dbg_info_dump },
{"C2H_CRDT_COAL_CFG_1", 0x1400,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_crdt_coal_cfg_1_info_dump },
{"C2H_CRDT_COAL_CFG_2", 0x1404,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_crdt_coal_cfg_2_info_dump },
{"C2H_PFCH_BYP_QID", 0x1408,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_pfch_byp_qid_info_dump },
{"C2H_PFCH_BYP_TAG", 0x140c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_pfch_byp_tag_info_dump },
{"C2H_WATER_MARK", 0x1500,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_water_mark_info_dump },
{"C2H_NOTIFY_EMPTY", 0x1800,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_notify_empty_info_dump },
{"C2H_STAT_S_AXIS_C2H_ACCEPTED_1", 0x1804,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_s_axis_c2h_accepted_1_info_dump },
{"C2H_STAT_S_AXIS_WRB_ACCEPTED_1", 0x1808,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_s_axis_wrb_accepted_1_info_dump },
{"C2H_STAT_DESC_RSP_PKT_ACCEPTED_1", 0x180c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_desc_rsp_pkt_accepted_1_info_dump },
{"C2H_STAT_AXIS_PKG_CMP_1", 0x1900,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_axis_pkg_cmp_1_info_dump },
{"C2H_STAT_S_AXIS_WRB_ACCEPTED_2", 0x1908,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_stat_s_axis_wrb_accepted_2_info_dump },
{"C2H_ST_PLD_FIFO_DEPTH", 0x190c,
	1, 0, 0, 0,
	0, QDMA_ST_MODE, QDMA_REG_READ_PF_ONLY,
	&eqdma_c2h_st_pld_fifo_depth_info_dump },
{"FUNC_STATUS_REG", 0x2400,
	1, 0, 0, 0,
	0, QDMA_MAILBOX, QDMA_REG_READ_PF_ONLY,
	&eqdma_func_status_reg_info_dump },
{"FUNC_CMD_REG", 0x2404,
	1, 0, 0, 0,
	0, QDMA_MAILBOX, QDMA_REG_READ_PF_ONLY,
	&eqdma_func_cmd_reg_info_dump },
{"FUNC_INTERRUPT_VECTOR_REG", 0x2408,
	1, 0, 0, 0,
	0, QDMA_MAILBOX, QDMA_REG_READ_PF_ONLY,
	&eqdma_func_interrupt_vector_reg_info_dump },
{"TARGET_FUNC_REG", 0x240c,
	1, 0, 0, 0,
	0, QDMA_MAILBOX, QDMA_REG_READ_PF_ONLY,
	&eqdma_target_func_reg_info_dump },
{"FUNC_INTERRUPT_CTL_REG", 0x2410,
	1, 0, 0, 0,
	0, QDMA_MAILBOX, QDMA_REG_READ_PF_ONLY,
	&eqdma_func_interrupt_ctl_reg_info_dump },
};

uint32_t eqdma_config_num_regs_get(void)
{
	return (sizeof(eqdma_config_regs)/
		sizeof(eqdma_config_regs[0]));
}

struct xreg_info *eqdma_config_regs_get(void)
{
	return eqdma_config_regs;
}

