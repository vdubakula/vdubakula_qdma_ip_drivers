/*
-- (c) Copyright 2020 Xilinx, Inc. All rights reserved.
--
-- This file contains confidential and proprietary information
-- of Xilinx, Inc. and is protected under U.S. and
-- international copyright and other intellectual property
-- laws.
--
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- Xilinx, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) Xilinx shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or Xilinx had been advised of the
-- possibility of the same.
--
-- CRITICAL APPLICATIONS
-- Xilinx products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of Xilinx products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
--
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
*/

/**
 * @file qdma_platfom_mock.cpp
 *
 */

#include "qdma_platform_mock.h"
#include "qdma_platform.h"
#include "qdma_access_errors.h"
#include <linux/errno.h>
#include <stdint.h>

testing::StrictMock<qdma_access_mocks> qdma_access_mock;

struct err_code_map error_code_map_list[] = {
	{QDMA_SUCCESS,				0},
	{QDMA_ERR_INV_PARAM,			EINVAL},
	{QDMA_ERR_NO_MEM,			ENOMEM},
	{QDMA_ERR_HWACC_BUSY_TIMEOUT,		EBUSY},
	{QDMA_ERR_HWACC_INV_CONFIG_BAR,		EINVAL},
	{QDMA_ERR_HWACC_NO_PEND_LEGCY_INTR,	EINVAL},
	{QDMA_ERR_HWACC_BAR_NOT_FOUND,		EINVAL},
	{QDMA_ERR_HWACC_FEATURE_NOT_SUPPORTED,	EINVAL},
	{QDMA_ERR_RM_RES_EXISTS,		EPERM},
	{QDMA_ERR_RM_RES_NOT_EXISTS,		EINVAL},
	{QDMA_ERR_RM_DEV_EXISTS,		EPERM},
	{QDMA_ERR_RM_DEV_NOT_EXISTS,		EINVAL},
	{QDMA_ERR_RM_NO_QUEUES_LEFT,		EPERM},
	{QDMA_ERR_RM_QMAX_CONF_REJECTED,	EPERM},
	{QDMA_ERR_MBOX_FMAP_WR_FAILED,		EIO},
	{QDMA_ERR_MBOX_NUM_QUEUES,		EINVAL},
	{QDMA_ERR_MBOX_INV_QID,			EINVAL},
	{QDMA_ERR_MBOX_INV_RINGSZ,		EINVAL},
	{QDMA_ERR_MBOX_INV_BUFSZ,		EINVAL},
	{QDMA_ERR_MBOX_INV_CNTR_TH,		EINVAL},
	{QDMA_ERR_MBOX_INV_TMR_TH,		EINVAL},
	{QDMA_ERR_MBOX_INV_MSG,			EINVAL},
	{QDMA_ERR_MBOX_SEND_BUSY,		EBUSY},
	{QDMA_ERR_MBOX_NO_MSG_IN,		EINVAL},
	{QDMA_ERR_MBOX_REG_READ_FAILED,		EIO},
	{QDMA_ERR_MBOX_ALL_ZERO_MSG,		EINVAL},
};


extern "C"
{

	void qdma_reg_write(void *dev_hndl, uint32_t reg_offst, uint32_t val)
	{
		return;
	}

	uint32_t qdma_reg_read(void *dev_hndl, uint32_t reg_offst)
	{
		return qdma_access_mock.qdma_reg_read(dev_hndl, reg_offst);
	}

	void *qdma_calloc(uint32_t num_blocks, uint32_t size)
	{
		return malloc(num_blocks * size);
	}

	void qdma_memfree(void *memptr)
	{
		free(memptr);
	}

	void qdma_udelay(uint32_t delay_us)
	{
		usleep(delay_us);
	}

	int qdma_reg_access_lock(void *dev_hndl)
	{
		return 0;
	}

	int qdma_reg_access_release(void *dev_hndl)
	{
		return 0;
	}

	void qdma_resource_lock_take(void)
	{
	}

	void qdma_resource_lock_give(void)
	{
	}

	void qdma_hw_error_handler(void *dev_hndl, enum qdma_error_idx err_idx)
	{
		struct mock_devhndl *xdev = (struct mock_devhndl *)dev_hndl;

		xdev->hw_access.qdma_hw_get_error_name(err_idx);
	}

	void qdma_get_device_attr(void *dev_hndl, struct qdma_dev_attributes **dev_cap)
	{
		struct mock_devhndl *xdev = (struct mock_devhndl *)dev_hndl;

		*dev_cap = &xdev->dev_cap;
	}

	void qdma_get_hw_access(void *dev_hndl, struct qdma_hw_access **hw)
	{
		struct mock_devhndl *xdev = (struct mock_devhndl *)dev_hndl;
		*hw = &xdev->hw_access;
	}

	void qdma_strncpy(char *dest, const char *src, size_t n)
	{
		strncpy(dest, src, n);
	}

	int qdma_get_err_code(int acc_err_code)
	{
		return -(error_code_map_list[acc_err_code].err_code);
	}

} // extern C
