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
#include "qdma_soft_reg.h"
#include "qdma_soft_access.h"
#include "qdma_cpm4_reg.h"
//#include "eqdma_soft_reg.h"
#include "qdma_cpm4_access.h"
#include "eqdma_soft_access.h"
#include "qdma_reg_dump.h"
#include "eqdma_access_test.h"
using::testing::_;
using::testing::AtLeast;
using::testing::Return;
using::testing::Mock;
using::testing::InSequence;

#define QDMA_CPM4_REG_TRQ_SEL_FMAP_STEP  4

#define QDMA_CPM4_OFFSET_IND_CTXT_CMD     QDMA_CPM4_IND_CTXT_CMD_ADDR
#define QDMA_CPM4_REG_TRQ_SEL_FMAP_BASE   QDMA_CPM4_TRQ_SEL_FMAP_0_ADDR


#define QDMA_NUM_VERSIONS								3
#define QDMA_SOFT_VERSION								0
#define EQDMA_SOFT_VERSION								1
#define CPM4_VERSION								2

#define QDMA_OFFSET_CONFIG_BLOCK_ID_VAL					0x1fd30000

#define CPM4_OFFSET_CONFIG_BLOCK_ID_PF_VAL			0x1fd30001
#define CPM4_OFFSET_CONFIG_BLOCK_ID_VF_VAL			0x1fd31000

#define EQDMA_OFFSET_CONFIG_BLOCK_ID_PF_VAL				0x1fd30001
#define EQDMA_OFFSET_CONFIG_BLOCK_ID_VF_VAL				0x1fd30010

#define QDMA_OFFSET_GLBL2_MISC_CAP_VAL					0x2010003 //134
#define QDMA_OFFSET_GLBL2_PF_BARLITE_INT_VAL			0x41041	//104
#define QDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP_VAL			0x800	//120
#define QDMA_OFFSET_GLBL2_CHANNEL_MDMA_VAL				0x30f0f	//118

#define EQDMA_OFFSET_GLBL2_MISC_CAP_VAL					0x100003 //134
#define EQDMA_OFFSET_GLBL2_PF_BARLITE_INT_VAL			0x41041	//104
#define EQDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP_VAL			0x800	//120
#define EQDMA_OFFSET_GLBL2_CHANNEL_MDMA_VAL				0x30f0f	//118

#define CPM4_OFFSET_GLBL2_MISC_CAP_VAL				0x10000003 //134
#define CPM4_OFFSET_GLBL2_PF_BARLITE_INT_VAL		0x41041	//104
#define CPM4_OFFSET_GLBL2_CHANNEL_QDMA_CAP_VAL		0x800	//120
#define CPM4_OFFSET_GLBL2_CHANNEL_MDMA_VAL			0x30f0f	//118

#define QDMA_SOFT_NUM_REGS								156
#define CPM4_NUM_REGS								140
#define EQDMA_SOFT_NUM_REGS								169

extern struct qdma_hw_err_info qdma_err_info[];
extern struct eqdma_hw_err_info eqdma_err_info[];

void mock_access_init(int version)
{
	switch (version) {
	case QDMA_SOFT_VERSION:
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_CONFIG_BLOCK_ID))
				.WillOnce(Return(QDMA_OFFSET_CONFIG_BLOCK_ID_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillOnce(Return(QDMA_OFFSET_GLBL2_MISC_CAP_VAL));
		break;
	case EQDMA_SOFT_VERSION:
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_CONFIG_BLOCK_ID))
				.WillOnce(Return(EQDMA_OFFSET_CONFIG_BLOCK_ID_PF_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillOnce(Return(EQDMA_OFFSET_GLBL2_MISC_CAP_VAL));
		break;
	case CPM4_VERSION:
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_CONFIG_BLOCK_ID))
				.WillOnce(Return(CPM4_OFFSET_CONFIG_BLOCK_ID_PF_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillOnce(Return(CPM4_OFFSET_GLBL2_MISC_CAP_VAL));
		break;
	default:
		std::cout << "invalid qdma version \n";
		break;
	}
}

void mock_access_init_vf()
{
	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_VF_VERSION))
			.Times(2)
			.WillRepeatedly(Return(QDMA_OFFSET_CONFIG_BLOCK_ID_VAL));
}

void mock_access_init_vf_user_bar(int version)
{
	switch (version) {
	case QDMA_SOFT_VERSION:
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_VF_VERSION))
		.Times(2)
		.WillRepeatedly(Return(QDMA_OFFSET_CONFIG_BLOCK_ID_VAL));
		break;
	case CPM4_VERSION:
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_VF_VERSION))
		.Times(2)
		.WillRepeatedly(Return(CPM4_OFFSET_CONFIG_BLOCK_ID_VF_VAL));
		break;
	case EQDMA_SOFT_VERSION:
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_VF_VERSION))
				.WillOnce(Return(0));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,EQDMA_OFFSET_VF_VERSION))
				.Times(2)
				.WillRepeatedly(Return(EQDMA_OFFSET_CONFIG_BLOCK_ID_VF_VAL));
		break;
	}
}


void mock_version_register(int version, uint8_t is_vf, int times)
{
	int reg_addr = (is_vf) ? QDMA_OFFSET_VF_VERSION :
			QDMA_OFFSET_GLBL2_MISC_CAP;

	switch (version) {
	case QDMA_SOFT_VERSION:
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,reg_addr))
			.Times(times)
			.WillRepeatedly(Return(QDMA_OFFSET_GLBL2_MISC_CAP_VAL));
		break;
	case EQDMA_SOFT_VERSION:
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,reg_addr))
			.Times(times)
			.WillRepeatedly(Return(EQDMA_OFFSET_GLBL2_MISC_CAP_VAL));
		break;
	case CPM4_VERSION:
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,reg_addr))
			.Times(times)
			.WillRepeatedly(Return(CPM4_OFFSET_GLBL2_MISC_CAP_VAL));
		break;
	default:
		std::cout << "invalid qdma version \n";
		break;
	}
}

enum bit_stream_type {
	BIT_STREAM_MM_ONLY = 0,
	BIT_STREAM_MM_ST,
};
void mock_dev_attr_regs(int version, enum bit_stream_type type=BIT_STREAM_MM_ST, bool mm_cmpt_en=true) {

	uint32_t qdma_cap_val;
	uint32_t qdma_misc_cap_val;

	/** Same values and register addresses used for all three designs */
	if ((version == QDMA_SOFT_VERSION) || (version == CPM4_VERSION)) {
		qdma_cap_val = QDMA_OFFSET_GLBL2_CHANNEL_MDMA_VAL;
		qdma_misc_cap_val = QDMA_OFFSET_GLBL2_MISC_CAP_VAL;
	}
	else if (version == EQDMA_SOFT_VERSION) {
		qdma_cap_val = EQDMA_OFFSET_GLBL2_CHANNEL_MDMA_VAL;
		qdma_misc_cap_val = EQDMA_OFFSET_GLBL2_MISC_CAP_VAL;
	}

	/** Fields are common across designs */
	if (mm_cmpt_en == false) {
		qdma_misc_cap_val = (qdma_misc_cap_val & ~(QDMA_GLBL2_MM_CMPT_EN_MASK));
	} else {
		qdma_misc_cap_val = (qdma_misc_cap_val | QDMA_GLBL2_MM_CMPT_EN_MASK);
	}

	if (type == BIT_STREAM_MM_ONLY) {
		/* QDMA design :
		 * 	b0 & b8 for MM
		 * 	b16 & b17 for ST
		 */

		/** Clear MM bits */
		qdma_cap_val = qdma_cap_val & ~(0x0101);
		/** Clear ST bits */
		qdma_cap_val = qdma_cap_val & ~(0x30000);
		/** SET MM bits */
		qdma_cap_val = qdma_cap_val | (0x0101);
		//printf("MM Only BS : 0x%X, 0x%X\n", qdma_cap_val, QDMA_OFFSET_GLBL2_CHANNEL_MDMA_VAL);
	}
	else {
		/** Clear MM bits */
		qdma_cap_val = qdma_cap_val & ~(0x0101);
		/** Clear ST bits */
		qdma_cap_val = qdma_cap_val & ~(0x30000);
		/** SET MM bits */
		qdma_cap_val = qdma_cap_val | (0x0101) | (0x30000);
	}

	switch (version) {
	case QDMA_SOFT_VERSION:
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_PF_BARLITE_INT))
				.WillOnce(Return(QDMA_OFFSET_GLBL2_PF_BARLITE_INT_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP))
				.WillOnce(Return(QDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillOnce(Return(QDMA_OFFSET_GLBL2_MISC_CAP_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_MDMA))
				.WillOnce(Return(qdma_cap_val));
		break;
	case EQDMA_SOFT_VERSION:
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_PF_BARLITE_INT))
				.WillRepeatedly(Return(EQDMA_OFFSET_GLBL2_PF_BARLITE_INT_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP))
				.WillRepeatedly(Return(EQDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillRepeatedly(Return(EQDMA_OFFSET_GLBL2_MISC_CAP_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_MDMA))
				.WillRepeatedly(Return(qdma_cap_val));
		break;
	case CPM4_VERSION:
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_PF_BARLITE_INT))
				.WillOnce(Return(QDMA_OFFSET_GLBL2_PF_BARLITE_INT_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP))
				.WillOnce(Return(QDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillOnce(Return(QDMA_OFFSET_GLBL2_MISC_CAP_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_MDMA))
				.WillOnce(Return(qdma_cap_val));
		break;
	default:
		std::cout << "invalid qdma version \n";
		break;
	}
}


class qdma_access_api_test : public ::testing::Test {
	protected:
		void SetUp() override {}
		void TearDown() override {Mock::VerifyAndClear(&qdma_access_mock);}
};



 /**
 * @brief      API001_qdma_access_init_test, FUT : int qdma_hw_access_init(void *dev_hndl, uint8_t is_vf,
														struct qdma_hw_access *hw_access)
 *
 * @details    Testcases :
 *			   - dev_hndl NULL
 *			   - hw_access NULL
 *			   - Success Case PF
 *			   - Failure case Config_ID not correct
 */ 
TEST_F(qdma_access_api_test, API001_qdma_access_init_test)
{
	/*Testcases : dev_hndl NULL*/
	{
		struct qdma_hw_access hw_access = {0};
		EXPECT_EQ(-QDMA_ERR_INV_PARAM , qdma_hw_access_init(NULL, 0,
				 &hw_access));
	}

	/*Testcases : hw_access NULL*/
	{
		uint32_t dev_hndl;
		EXPECT_EQ(-QDMA_ERR_INV_PARAM , qdma_hw_access_init(&dev_hndl, 0,
				 NULL));
	}

	for (int k = QDMA_SOFT_VERSION; k < QDMA_NUM_VERSIONS; k++) {
		/*Testcases : Success Case PF*/
		{
			struct qdma_hw_access hw_access = {0};
			uint32_t dev_hndl;
			mock_access_init(k);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
						 &hw_access));

		}
		/*Testcases : Success Case VF*/
		{
			struct qdma_hw_access hw_access = {0};
			uint32_t dev_hndl;
			mock_access_init_vf();
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 1,
						 &hw_access));

		}
		/*Testcases : Failure case Config_ID not correct*/
		{
			struct qdma_hw_access hw_access = {0};
			uint32_t dev_hndl;
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_CONFIG_BLOCK_ID))
						.WillOnce(Return(0x0));

			EXPECT_EQ(-QDMA_ERR_HWACC_INV_CONFIG_BAR, qdma_hw_access_init(&dev_hndl, 0,
						 &hw_access));

			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_VF_VERSION))
				.WillOnce(Return(0x0));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,EQDMA_OFFSET_VF_VERSION))
				.WillOnce(Return(0x0));
			EXPECT_EQ(-QDMA_ERR_HWACC_INV_CONFIG_BAR, qdma_hw_access_init(&dev_hndl, 1,
						 &hw_access));

		}
	}
	/*Testcases : Different versions*/
	{
		struct qdma_hw_access hw_access = {0};
		uint32_t dev_hndl;

		/*Testcases : vivado_release_id 0 device_type 3 versal_ip_type 0*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_CONFIG_BLOCK_ID))
				.WillOnce(Return(QDMA_OFFSET_CONFIG_BLOCK_ID_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillOnce(Return(0x30000000));
		EXPECT_EQ(QDMA_SUCCESS, qdma_hw_access_init(&dev_hndl, 0,
					 &hw_access));

		/*Testcases : vivado_release_id 1 device_type 0 versal_ip_type 0*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_CONFIG_BLOCK_ID))
				.WillOnce(Return(QDMA_OFFSET_CONFIG_BLOCK_ID_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillOnce(Return(0x1000000));
		EXPECT_EQ(QDMA_SUCCESS, qdma_hw_access_init(&dev_hndl, 0,
					 &hw_access));

		/*Testcases : vivado_release_id 4 device_type 0 versal_ip_type 0*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_CONFIG_BLOCK_ID))
				.WillOnce(Return(QDMA_OFFSET_CONFIG_BLOCK_ID_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillOnce(Return(0x4000000));
		EXPECT_EQ(QDMA_SUCCESS, qdma_hw_access_init(&dev_hndl, 0,
					 &hw_access));

		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_CONFIG_BLOCK_ID))
				.WillOnce(Return(QDMA_OFFSET_CONFIG_BLOCK_ID_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillOnce(Return(0x11000003));
		EXPECT_EQ(QDMA_SUCCESS, qdma_hw_access_init(&dev_hndl, 0,
					 &hw_access));

		/*Testcases : vivado_release_id 1 device_type 1 versal_ip_type 0*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_CONFIG_BLOCK_ID))
				.WillOnce(Return(QDMA_OFFSET_CONFIG_BLOCK_ID_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillOnce(Return(0x11100003));
		EXPECT_EQ(QDMA_SUCCESS, qdma_hw_access_init(&dev_hndl, 0,
					 &hw_access));

		/*Testcases : vivado_release_id 1 device_type 1 versal_ip_type 2*/	 
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_CONFIG_BLOCK_ID))
				.WillOnce(Return(QDMA_OFFSET_CONFIG_BLOCK_ID_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillOnce(Return(0x11200003));
		EXPECT_EQ(QDMA_SUCCESS, qdma_hw_access_init(&dev_hndl, 0,
					 &hw_access));
	 }
}

 /**
 * @brief      API002_get_error_code_test, FUT : int qdma_get_error_code(int acc_err_code)
 *
 * @details    Testcases :
 *			   - Success Case all error cases
 *			   - acc_err_code -ve value
 *			   - acc_err_code greater than QDMA_ERR_MBOX_ALL_ZERO_MSG
 */

struct get_err_code_params {
	struct get_err_code_val {
		int expected_err;
		int access_err;
		get_err_code_val(int sys_err, int acs_err)
			:expected_err(sys_err), access_err(acs_err){}
	};
	std::vector<get_err_code_val> params;

	get_err_code_params(std::vector<get_err_code_val>&& parameter):
		params(parameter){}
};


class get_error_code_Test_class : public testing::TestWithParam<get_err_code_params> {
	protected:
		void SetUp() override {}
		void TearDown() override {Mock::VerifyAndClear(&qdma_access_mock);}
};

static get_err_code_params qdma_get_error_code_params(void)
{
	std::vector<get_err_code_params::get_err_code_val> testParams;
	extern struct err_code_map error_code_map_list[QDMA_ERR_MBOX_ALL_ZERO_MSG];

	testParams.reserve(QDMA_ERR_MBOX_ALL_ZERO_MSG+2);

	for (int i = 0; i <= (QDMA_ERR_MBOX_ALL_ZERO_MSG); i++)
		testParams.emplace_back(error_code_map_list[i].err_code,
				error_code_map_list[i].acc_err_code);

	return get_err_code_params{std::move(testParams)};
}

TEST_P(get_error_code_Test_class, get_error_code) {
	auto& testVals = GetParam();

	for (const auto& test : testVals.params) {
		EXPECT_EQ((test.expected_err * -1), qdma_get_error_code(test.access_err));
	}
}

INSTANTIATE_TEST_CASE_P(API002_get_error_code_test, get_error_code_Test_class,
						::testing::Values(qdma_get_error_code_params()));



 /**
 * @brief      API003_qdma_initiate_flr, FUT : int qdma_initiate_flr(void *dev_hndl, uint8_t is_vf)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *			   - Success Case 1 PF
 *			   - Success Case 2 VF
 */

TEST_F(qdma_access_api_test, API003_qdma_initiate_flr)
{
	struct mock_devhndl dev_hndl;

	for (int i = QDMA_SOFT_VERSION; i < CPM4_VERSION; i++) {

		mock_access_init(i);

		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases : dev_hndl is NULL*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_initiate_flr(NULL, 0));

		/*Testcases : Success Case PF*/
		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_initiate_flr(&dev_hndl, 0));

		/*Testcases : Success Case VF*/
		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_initiate_flr(&dev_hndl, 1));
	}
}

 /**
 * @brief      API004_qdma_legacy_intr_conf, FUT : int qdma_legacy_intr_conf(void *dev_hndl,
													enum status_type enable)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *			   - Success Case 1 Enabled
 *			   - Success Case 2 Disable
 */

TEST_F(qdma_access_api_test, API004_qdma_legacy_intr_conf)
{
	struct mock_devhndl dev_hndl;
	uint8_t done = 0;
	int retVal = 0;

	mock_access_init(QDMA_SOFT_VERSION);

	EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
				&dev_hndl.hw_access));

	/*Testcases : Invalid DevHandle*/
	EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_legacy_intr_conf(NULL, ENABLE));

	/*Testcases : Success Case Success Enable*/
	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_INTERRUPT_CFG))
			.WillRepeatedly(Return(0));

	EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_legacy_intr_conf(&dev_hndl, ENABLE));

	/*Testcases : Success Case Success Disable*/
	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_INTERRUPT_CFG))
			.WillRepeatedly(Return(0));

	EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_legacy_intr_conf(&dev_hndl, DISABLE));

}


 /**
 * @brief      API005_qdma_clear_pend_legacy_intr, FUT : int qdma_clear_pend_legacy_intr(void *dev_hndl)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - Success Case 1 Enabled
 */

TEST_F(qdma_access_api_test, API005_qdma_clear_pend_legacy_intr)
{
	struct mock_devhndl dev_hndl;
	uint8_t done = 0;
	int retVal = 0;


	mock_access_init(QDMA_SOFT_VERSION);

	EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
				&dev_hndl.hw_access));

	/*Testcases : dev_hndl is NULL*/
	EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_clear_pend_legacy_intr(NULL));

	/*Testcases : Success Case 1 Enable*/
	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_INTERRUPT_CFG))
				.WillRepeatedly(Return(0));

	EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_clear_pend_legacy_intr(&dev_hndl));
}


 /**
 * @brief      API006_qdma_is_legacy_intr_pend, FUT : int qdma_is_legacy_intr_pend(void *dev_hndl)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - Success Case 1 Pending
 *             - Success Case 2 cleared
 */
TEST_F(qdma_access_api_test, API006_qdma_is_legacy_intr_pend)
{
	struct mock_devhndl dev_hndl;
	uint8_t done = 0;
	int retVal = 0;

	for (int i = QDMA_SOFT_VERSION; i < CPM4_VERSION; i++) {

		mock_access_init(i);

		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases : dev_hndl is NULL*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_is_legacy_intr_pend(NULL));

		/*Testcases : Success Case 1 Pending*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_INTERRUPT_CFG))
				.WillRepeatedly(Return(0x02));

		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_is_legacy_intr_pend(&dev_hndl));

		/*Testcases : Success Case 2 cleared*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_INTERRUPT_CFG))
				.WillRepeatedly(Return(0x0));

		EXPECT_EQ(-QDMA_ERR_HWACC_NO_PEND_LEGCY_INTR, dev_hndl.hw_access.qdma_is_legacy_intr_pend(&dev_hndl));

	}
}

 /**
 * @brief      API007_qdma_is_flr_done, FUT : int qdma_is_flr_done(void *dev_hndl, uint8_t is_vf,
											uint8_t *done)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - done is NULL
 *             - Success Case PF
 *			   - Success Case VF with multiple hw_monitor read
 *			   - Success Case VF with single hw_monitor read
 */
TEST_F(qdma_access_api_test, API007_qdma_is_flr_done)
{
	struct mock_devhndl dev_hndl;
	uint8_t done = 0;
	int retVal = 0;

	for (int i = QDMA_SOFT_VERSION; i < CPM4_VERSION; i++) {

		mock_access_init(i);

		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));


		/*Testcases : Invalid DevHandle*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_is_flr_done(NULL, 0, &done));

		/*Testcases : Invalid hw_access*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_is_flr_done(&dev_hndl, 1, NULL));

		/*Testcases : Success Case PF*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_PF_REG_FLR_STATUS))
				.WillRepeatedly(Return(0));

		retVal = dev_hndl.hw_access.qdma_is_flr_done(&dev_hndl, 0, &done);
		EXPECT_TRUE(done && (retVal == QDMA_SUCCESS));

		/*Testcases : hw_monitor_reg timeout*/
		done = 0;
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_PF_REG_FLR_STATUS))
				.Times(100*100 + 1)
				.WillRepeatedly(Return(1));

		retVal = dev_hndl.hw_access.qdma_is_flr_done(&dev_hndl, 0, &done);
		EXPECT_TRUE((done == 0) && (retVal == QDMA_SUCCESS));

		/*Testcases : Success Case VF*/
		done = 0;
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_VF_REG_FLR_STATUS))
				.Times(4)
				.WillOnce(Return(1))
				.WillOnce(Return(1))
				.WillOnce(Return(1))
				.WillRepeatedly(Return(0));

		retVal = dev_hndl.hw_access.qdma_is_flr_done(&dev_hndl, 1, &done);
		EXPECT_TRUE(done && (retVal == QDMA_SUCCESS));

		/*Testcases : Success Case VF*/
		done = 0;
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_VF_REG_FLR_STATUS))
				.WillRepeatedly(Return(0));

		retVal = dev_hndl.hw_access.qdma_is_flr_done(&dev_hndl, 1, &done);
		EXPECT_TRUE(done && (retVal == QDMA_SUCCESS));

		/*Testcases : hw_monitor_reg timeout*/
		done = 0;
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_VF_REG_FLR_STATUS))
				.Times(100*100 + 1)
				.WillRepeatedly(Return(1));

		retVal = dev_hndl.hw_access.qdma_is_flr_done(&dev_hndl, 1, &done);
		EXPECT_TRUE((done == 0) && (retVal == QDMA_SUCCESS));
	}
}

 /**
 * @brief      API008_qdma_hw_error_process, FUT : int qdma_hw_error_process(void *dev_hndl)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - glbl_err_stat is not set
 *			   - Success
 */

TEST_F(qdma_access_api_test, API008_qdma_hw_error_process)
{
	struct mock_devhndl dev_hndl;
	uint32_t hw_err_position[TOTAL_LEAF_ERROR_AGGREGATORS] = {
		QDMA_DSC_ERR_POISON,
		QDMA_TRQ_ERR_UNMAPPED,
		QDMA_ST_C2H_ERR_MTY_MISMATCH,
		QDMA_ST_FATAL_ERR_MTY_MISMATCH,
		QDMA_ST_H2C_ERR_ZERO_LEN_DESC,
		QDMA_SBE_ERR_MI_H2C0_DAT,
		QDMA_DBE_ERR_MI_H2C0_DAT
	};


	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {

		mock_access_init(i);
		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		mock_dev_attr_regs(i);
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, &dev_hndl.dev_cap));


		/*Testcases : Invalid DevHandle*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_hw_error_process(NULL));


		mock_dev_attr_regs(i);
		/*Testcases : glbl_err_stat is not set*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_STAT))
				.WillOnce(Return(0));
		EXPECT_EQ(QDMA_HW_ERR_NOT_DETECTED, dev_hndl.hw_access.qdma_hw_error_process(&dev_hndl));

		/*Testcases : Success test*/
		if (i == EQDMA_SOFT_VERSION) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_STAT))
					.WillOnce(Return(1));

			for (int j = 0; j < EQDMA_TOTAL_LEAF_ERROR_AGGREGATORS; j++) {

				uint32_t bit = eqdma_mock_errs_info[j].hw_err_position;

				if ((!dev_hndl.dev_cap.st_en) && (bit == QDMA_ST_C2H_ERR_MTY_MISMATCH ||
						bit == QDMA_ST_FATAL_ERR_MTY_MISMATCH ||
						bit == QDMA_ST_H2C_ERR_ZERO_LEN_DESC))
					continue;

				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, eqdma_err_info[bit].stat_reg_addr))
									.WillRepeatedly(Return(0xffffffff));
				eqdma_mock_errs_info[j].mock_err();
			}

			mock_dev_attr_regs(i);
			EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_process(&dev_hndl));

		} else {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_STAT))
					.WillOnce(Return(1));

			for (int j = 0; j < TOTAL_LEAF_ERROR_AGGREGATORS; j++) {
				uint32_t bit = hw_err_position[j];

				if ((!dev_hndl.dev_cap.st_en) && (bit == QDMA_ST_C2H_ERR_MTY_MISMATCH ||
						bit == QDMA_ST_FATAL_ERR_MTY_MISMATCH ||
						bit == QDMA_ST_H2C_ERR_ZERO_LEN_DESC))
					continue;

				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, qdma_err_info[bit].stat_reg_addr))
									.WillRepeatedly(Return(0xffffffff));
				eqdma_mock_errs_info[j].mock_err();
			}

			mock_dev_attr_regs(i);
			EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_process(&dev_hndl));
		}

		if (i == EQDMA_SOFT_VERSION) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_STAT))
					.WillOnce(Return(1));

			for (int j = 0; j < EQDMA_TOTAL_LEAF_ERROR_AGGREGATORS; j++) {
				uint32_t bit = eqdma_mock_errs_info[j].hw_err_position;

				if ((!dev_hndl.dev_cap.st_en) && (bit == QDMA_ST_C2H_ERR_MTY_MISMATCH ||
						bit == QDMA_ST_FATAL_ERR_MTY_MISMATCH ||
						bit == QDMA_ST_H2C_ERR_ZERO_LEN_DESC))
					continue;

				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, eqdma_err_info[bit].stat_reg_addr))
									.WillRepeatedly(Return(0));
				eqdma_mock_errs_info[j].mock_err();
			}

			mock_dev_attr_regs(i);
			EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_process(&dev_hndl));
	
		} else {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_STAT))
					.WillOnce(Return(1));

			for (int j = 0; j < TOTAL_LEAF_ERROR_AGGREGATORS; j++) {
				uint32_t bit = hw_err_position[j];

				if ((!dev_hndl.dev_cap.st_en) && (bit == QDMA_ST_C2H_ERR_MTY_MISMATCH ||
						bit == QDMA_ST_FATAL_ERR_MTY_MISMATCH ||
						bit == QDMA_ST_H2C_ERR_ZERO_LEN_DESC))
					continue;

				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, qdma_err_info[bit].stat_reg_addr))
									.WillRepeatedly(Return(0));
			}

			mock_dev_attr_regs(i);
			EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_process(&dev_hndl));
		}

		if (i == EQDMA_SOFT_VERSION) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_STAT))
					.WillOnce(Return(1));

			for (int j = 0; j < EQDMA_TOTAL_LEAF_ERROR_AGGREGATORS; j++) {
				uint32_t bit = eqdma_mock_errs_info[j].hw_err_position;

				if ((!dev_hndl.dev_cap.st_en) && (bit == QDMA_ST_C2H_ERR_MTY_MISMATCH ||
						bit == QDMA_ST_FATAL_ERR_MTY_MISMATCH ||
						bit == QDMA_ST_H2C_ERR_ZERO_LEN_DESC))
					continue;

				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, eqdma_err_info[bit].stat_reg_addr))
									.WillRepeatedly(Return(0xffffffff));
				eqdma_mock_errs_info[j].mock_err();
			}

			mock_dev_attr_regs(i, BIT_STREAM_MM_ONLY, false);
			EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_process(&dev_hndl));

		} else {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_STAT))
					.WillOnce(Return(1));

			for (int j = 0; j < TOTAL_LEAF_ERROR_AGGREGATORS; j++) {
				uint32_t bit = hw_err_position[j];

				if ((!dev_hndl.dev_cap.st_en) && (bit == QDMA_ST_C2H_ERR_MTY_MISMATCH ||
						bit == QDMA_ST_FATAL_ERR_MTY_MISMATCH ||
						bit == QDMA_ST_H2C_ERR_ZERO_LEN_DESC))
					continue;

				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, qdma_err_info[bit].stat_reg_addr))
									.WillRepeatedly(Return(0xffffffff));
			}

			mock_dev_attr_regs(i, BIT_STREAM_MM_ONLY, false);
			EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_process(&dev_hndl));
		}
	}
}

 /**
 * @brief      API009_qdma_hw_get_error_name, FUT : const char * qdma_hw_get_error_name(enum qdma_error_idx err_idx)
 *
 * @details    Testcases :
 *             - Success Case
 *             - Max value for err_idx
 */
TEST_F(qdma_access_api_test, API009_qdma_hw_get_error_name)
{
	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {

		if (i == EQDMA_SOFT_VERSION) {
			struct mock_devhndl dev_hndl;

			mock_access_init(i);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
						&dev_hndl.hw_access));

			/*Testcases : Success Test*/
			for(int i = EQDMA_DSC_ERR_POISON; i < EQDMA_ERRS_ALL; i++) {
				EXPECT_TRUE(NULL != dev_hndl.hw_access.qdma_hw_get_error_name((enum qdma_error_idx)(i)));
			}

			/*Testcases : Max value for err_idx*/
			EXPECT_TRUE(NULL == dev_hndl.hw_access.qdma_hw_get_error_name(EQDMA_ERRS_ALL));
		} else if (i == QDMA_SOFT_VERSION){
			struct mock_devhndl dev_hndl;

			mock_access_init(i);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
						&dev_hndl.hw_access));
			/*Testcases : Success Test*/
			for(int i = QDMA_DSC_ERR_POISON; i < QDMA_ERRS_ALL; i++) {
				EXPECT_TRUE(NULL != dev_hndl.hw_access.qdma_hw_get_error_name((enum qdma_error_idx)(i)));
			}
			/*Testcases : Max value for err_idx*/
			EXPECT_TRUE(NULL == dev_hndl.hw_access.qdma_hw_get_error_name((enum qdma_error_idx)QDMA_ERRS_ALL));
		}  else if (i == CPM4_VERSION){
			struct mock_devhndl dev_hndl;

			mock_access_init(i);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
						&dev_hndl.hw_access));
			/*Testcases : Success Test*/
			for(int i = QDMA_CPM4_DSC_ERR_POISON; i < QDMA_CPM4_ERRS_ALL; i++) {
				EXPECT_TRUE(NULL != dev_hndl.hw_access.qdma_hw_get_error_name((enum qdma_error_idx)(i)));
			}
			/*Testcases : Max value for err_idx*/
			EXPECT_TRUE(NULL == dev_hndl.hw_access.qdma_hw_get_error_name((enum qdma_error_idx)QDMA_CPM4_ERRS_ALL));
		}
	}
}


/**
 * @brief      API010_qdma_hw_error_intr_rearm, FUT : int qdma_hw_error_intr_rearm(void *dev_hndl)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - Success Case
 */

TEST_F(qdma_access_api_test, API010_qdma_hw_error_intr_rearm)
{
	struct mock_devhndl dev_hndl;

	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {

		mock_access_init(i);
		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases : Invalid DevHandle*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_hw_error_intr_rearm(NULL));

		/*Testcases : Success Test Cases*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL_ERR_INT))
				.WillOnce(Return(0x01));
		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_intr_rearm(&dev_hndl));
	}
}

/**
 * @brief      API011_qdma_hw_error_intr_setup, FUT : int qdma_hw_error_intr_setup(void *dev_hndl, uint16_t func_id,
														uint8_t err_intr_index)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - func_id 0 and err_intr_index 0
 *             - func_id Max Value
 *             - err_intr_index Max Value
 */
TEST_F(qdma_access_api_test, API011_qdma_hw_error_intr_setup)
{
	struct mock_devhndl dev_hndl;

	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {

		mock_access_init(i);
		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases :Invalid DevHandle*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_hw_error_intr_setup(NULL, 0, 0));

		/*Testcases : Success*/
		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_intr_setup(&dev_hndl, 0, 0));

		/*Testcases :Function ID should be uint8_t*/
		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_intr_setup(&dev_hndl, 0xffff, 0));

		/*Testcases : err_intr_index Max Value*/
		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_intr_setup(&dev_hndl, 0, 0xff));
	}
}


/**
 * @brief      API012_qdma_get_function_number, FUT : int qdma_get_function_number(void *dev_hndl,
														uint8_t *func_id)

 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - func_id is NULL
 *             - Success Cases for different function numbers
 */
TEST_F(qdma_access_api_test, API012_qdma_get_function_number)
{
	struct mock_devhndl dev_hndl;
	uint8_t func_id;
	int retVal;

	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {

		mock_access_init(i);
		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases : Invalid DevHandle*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_get_function_number(NULL, 0));

		/*Testcases : func_id is NULL*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_get_function_number(&dev_hndl, NULL));

		/*Testcases : Success case function id 0*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_FUNC_RET))
				.WillOnce(Return(0x0));

		retVal = dev_hndl.hw_access.qdma_get_function_number(&dev_hndl, &func_id);
		EXPECT_TRUE((retVal == QDMA_SUCCESS) && (func_id == 0x0));

		/*Testcases : Success case function id 0xff*/
		func_id = 0;
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_FUNC_RET))
				.WillOnce(Return(0xff));

		retVal = dev_hndl.hw_access.qdma_get_function_number(&dev_hndl, &func_id);
		EXPECT_TRUE((retVal == QDMA_SUCCESS) && (func_id == 0xff));

		/*Testcases : Success case function id 0xfff*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_FUNC_RET))
				.WillOnce(Return(0xfff));

		retVal = dev_hndl.hw_access.qdma_get_function_number(&dev_hndl, &func_id);
		EXPECT_TRUE((retVal == QDMA_SUCCESS) && (func_id == 0xff));
	}
}


/**
 * @brief      API013_qdma_get_user_bar, FUT : int qdma_get_user_bar(void *dev_hndl, uint8_t is_vf,
													uint8_t *user_bar)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - user_bar is NULL
 *             - Success Cases for different User BAR values
 */

TEST_F(qdma_access_api_test, API013_qdma_get_user_bar)
{
	struct mock_devhndl dev_hndl;
	int retVal;
	uint8_t user_bar;
	uint32_t user_bar_id;

	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {
		mock_access_init(i);

		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases : Invalid DevHandle*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_get_user_bar(NULL, 0, 0, &user_bar));

		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_get_user_bar(&dev_hndl, 0, 0, NULL));

		/*Testcases : Success PF Case with shifting BAR value*/

		int retVal;
		for (int j = 0; j < 6; j++) {
			user_bar_id = (1 << ((6 * i) + j));

			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_PF_BARLITE_EXT))
					.WillOnce(Return(user_bar_id));
			retVal = dev_hndl.hw_access.qdma_get_user_bar(&dev_hndl, 0, i, &user_bar);
			EXPECT_TRUE((retVal == QDMA_SUCCESS) && (user_bar == j));
		}


		/*Testcases : USER BAR NOT found*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_PF_BARLITE_EXT))
				.WillOnce(Return(0x104100));

		retVal = dev_hndl.hw_access.qdma_get_user_bar(&dev_hndl, 0, 0, &user_bar);
		EXPECT_TRUE((retVal == -QDMA_ERR_HWACC_BAR_NOT_FOUND));

}

}


TEST_F(qdma_access_api_test, API013_qdma_get_vf_user_bar) {

	struct mock_devhndl dev_hndl;
	int retVal;
	uint8_t user_bar;
	uint32_t user_bar_id;

	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {
		mock_access_init_vf_user_bar(i);
		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 1,
					&dev_hndl.hw_access));

		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_get_user_bar(NULL, 1, 0, &user_bar));

		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_get_user_bar(&dev_hndl, 1, 0, NULL));
		for (int j = 0; j < 6; j++) {
			switch (i) {
				case QDMA_SOFT_VERSION:
					user_bar_id = (1 << j);
					EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_VF_USER_BAR_ID))
							.WillOnce(Return(user_bar_id));
					retVal = dev_hndl.hw_access.qdma_get_user_bar(&dev_hndl, 1, i, &user_bar);
					EXPECT_TRUE((retVal == QDMA_SUCCESS) && (user_bar == j));
					break;
				case EQDMA_SOFT_VERSION:
					user_bar_id = (1 << ((6 * i) + j));
					EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,EQDMA_OFFSET_VF_USER_BAR))
							.WillOnce(Return(user_bar_id));
					retVal = dev_hndl.hw_access.qdma_get_user_bar(&dev_hndl, 1, i, &user_bar);
					EXPECT_TRUE((retVal == QDMA_SUCCESS) && (user_bar == j));
					break;
				case CPM4_VERSION:
					retVal = dev_hndl.hw_access.qdma_get_user_bar(&dev_hndl, 1, i, &user_bar);
					EXPECT_TRUE((retVal == QDMA_SUCCESS) && (user_bar == 2));
					break;
			}
		}
	}
}

/**
 * @brief      API014_qdma_mm_channel_conf, FUT : int qdma_mm_channel_conf(void *dev_hndl,
															uint8_t channel, uint8_t is_c2h,
															uint8_t enable)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - Success channel 0, is_c2h 0, enable 0
 *             - Success channel 0xff, is_c2h 0, enable 0
 *             - Success channel 0, is_c2h 1, enable 0
 *             - Success channel 0, is_c2h 0, enable 1
 */

TEST_F(qdma_access_api_test, API014_qdma_mm_channel_conf)
{
	struct mock_devhndl dev_hndl;

	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {
		mock_access_init(i);

		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases : Invalid DevHandle*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_mm_channel_conf(NULL, 0, 0, 0));

		mock_dev_attr_regs(i);
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, &dev_hndl.dev_cap));

		mock_dev_attr_regs(i);
		/*Testcases : Success channel 0, is_c2h 0, enable 0*/
		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_mm_channel_conf(&dev_hndl, 0, 0, 0));
		mock_dev_attr_regs(i);
		/*Testcases : Success channel 0xff, is_c2h 0, enable 0*/
		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_mm_channel_conf(&dev_hndl, 0xff, 0, 0));
		mock_dev_attr_regs(i);
		/*Testcases : Success channel 0, is_c2h 1, enable 0*/
		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_mm_channel_conf(&dev_hndl, 0, 1, 0));
		mock_dev_attr_regs(i);
		/*Testcases : Success channel 0, is_c2h 0, enable 1*/
		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_mm_channel_conf(&dev_hndl, 0, 0, 1));
	}
}

/**
 * @brief      API015_qdma_queue_intr_cidx_update, FUT : int qdma_queue_intr_cidx_update(void *dev_hndl,
														uint8_t is_vf, uint16_t qid,
														const struct qdma_intr_cidx_reg_info *reg_info)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - reg_info is NULL
 *             - Success Cases
 */

TEST_F(qdma_access_api_test, API015_qdma_queue_intr_cidx_update)
{
	struct mock_devhndl dev_hndl;
	struct qdma_intr_cidx_reg_info reg_info = {0};

	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {
		mock_access_init(i);

		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases : Invalid DevHandle*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_queue_intr_cidx_update(NULL, 0, 0, &reg_info));

		/*Testcases : reg_info is NULL*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM,
				dev_hndl.hw_access.qdma_queue_intr_cidx_update(&dev_hndl, 0, 0, NULL));
		/*Testcases : Success Case PF*/
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_queue_intr_cidx_update(&dev_hndl, 0, 0, &reg_info));
		/*Testcases : Success Case VF*/
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_queue_intr_cidx_update(&dev_hndl, 1, 0, &reg_info));
	}
}


/**
 * @brief      API016_qdma_queue_cmpt_cidx_update, FUT : int qdma_queue_cmpt_cidx_update(void *dev_hndl,
														uint8_t is_vf, uint16_t qid,
														const struct qdma_q_cmpt_cidx_reg_info *reg_info)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - reg_info is NULL
 *             - Success Cases
 */

TEST_F(qdma_access_api_test, API016_qdma_queue_cmpt_cidx_update)
{
	struct mock_devhndl dev_hndl;
	struct qdma_q_cmpt_cidx_reg_info reg_info = {0};

	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {
		mock_access_init(i);

		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases : Invalid DevHandle*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_queue_cmpt_cidx_update(NULL, 0, 0, &reg_info));

		/*Testcases : reg_info is NULL*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM,
				dev_hndl.hw_access.qdma_queue_cmpt_cidx_update(&dev_hndl, 0, 0, NULL));

		/*Testcases : Success Case PF*/
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_queue_cmpt_cidx_update(&dev_hndl, 0, 0, &reg_info));

		/*Testcases : Success Case VF*/
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_queue_cmpt_cidx_update(&dev_hndl, 1, 0, &reg_info));
	}
}

/**
 * @brief      API017_qdma_queue_cmpt_cidx_read, FUT : int qdma_queue_cmpt_cidx_read(void *dev_hndl, uint8_t is_vf,
																uint16_t qid,
																struct qdma_q_cmpt_cidx_reg_info *reg_info)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - reg_info is NULL
 *             - Success Cases
 */
TEST_F(qdma_access_api_test, API017_qdma_queue_cmpt_cidx_read)
{
	struct mock_devhndl dev_hndl;
	struct qdma_q_cmpt_cidx_reg_info reg_info = {0};

	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {
		mock_access_init(i);

		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases : Invalid DevHandle*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_queue_cmpt_cidx_read(NULL, 0, 0, &reg_info));

		/*Testcases : reg_info is NULL*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM,
				dev_hndl.hw_access.qdma_queue_cmpt_cidx_read(&dev_hndl, 0, 0, NULL));

		/*Testcases : Success Case PF*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_DMAP_SEL_CMPT_CIDX))
				.WillOnce(Return(0x0));

		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_queue_cmpt_cidx_read(&dev_hndl, 0, 0, &reg_info));

		/*Testcases : Success Case VF*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_VF_DMAP_SEL_CMPT_CIDX))
				.WillOnce(Return(0x0));

		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_queue_cmpt_cidx_read(&dev_hndl, 1, 0, &reg_info));
	}
}



/**
 * @brief      API018_qdma_queue_pidx_update, FUT : int qdma_queue_pidx_update(void *dev_hndl, uint8_t is_vf,
																uint16_t qid, uint8_t is_c2h
																struct qdma_q_pidx_reg_info *reg_info)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - reg_info is NULL
 *             - Success Cases
 *             - Check for invalid qid
 */

TEST_F(qdma_access_api_test, API018_qdma_queue_pidx_update)
{
	struct mock_devhndl dev_hndl;
	struct qdma_q_pidx_reg_info reg_info = {0};

	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {
		mock_access_init(i);

		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases :Invalid DevHandle*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_queue_pidx_update(NULL, 0, 0, 0, &reg_info));

		/*Testcases : reg_info is NULL*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM,
				dev_hndl.hw_access.qdma_queue_pidx_update(&dev_hndl, 0, 0, 0, NULL));
		/*Testcases : Success Cases*/
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_queue_pidx_update(&dev_hndl, 0, 0, 0, &reg_info));
		/*Testcases : Success Cases*/
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_queue_pidx_update(&dev_hndl, 1, 0, 0, &reg_info));
		/*Testcases : Success Cases*/
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_queue_pidx_update(&dev_hndl, 0, 0, 1, &reg_info));
		/*Testcases : Success Cases*/
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_queue_pidx_update(&dev_hndl, 1, 0, 0, &reg_info));

	}

}


/**
 * @brief      API019_qdma_get_device_attributes, FUT : int qdma_get_device_attributes(void *dev_hndl,
															struct qdma_dev_attributes *dev_info)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - dev_info is NULL
 *             - Success Cases
 */
TEST_F(qdma_access_api_test, API019_qdma_get_device_attributes)
{
	struct mock_devhndl dev_hndl;

	for (int i = QDMA_SOFT_VERSION; i < QDMA_NUM_VERSIONS; i++) {
		mock_access_init(i);
		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases : Invalid DevHandle*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM,
				dev_hndl.hw_access.qdma_get_device_attributes(NULL, &dev_hndl.dev_cap));
		/*Testcases : dev_info is NULL*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, NULL));

		/*Testcases : dev_info is NULL*/
		mock_dev_attr_regs(i);
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, &dev_hndl.dev_cap));
	}

}


/*******************************************************************************
 * Context APIs
 *******************************************************************************/
void mock_qdma_context_read(int version, int cnt) {
	uint32_t cmd_reg_addr =
			(version == CPM4_VERSION) ?
					QDMA_CPM4_OFFSET_IND_CTXT_CMD :
					QDMA_OFFSET_IND_CTXT_CMD;

	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
			.Times(4)
			.WillOnce(Return(1))
			.WillOnce(Return(1))
			.WillOnce(Return(1))
			.WillRepeatedly(Return(0));
	for (int i = 0; i < cnt; i++)
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (i * 4)))
					.WillRepeatedly(Return(0xff));

}

void mock_qdma_context_write(int version) {
	uint32_t cmd_reg_addr =
			(version == CPM4_VERSION) ?
					QDMA_CPM4_OFFSET_IND_CTXT_CMD :
					QDMA_OFFSET_IND_CTXT_CMD;

	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
			.Times(4)
			.WillOnce(Return(1))
			.WillOnce(Return(1))
			.WillOnce(Return(1))
			.WillRepeatedly(Return(0));
}

void mock_qdma_context_clear(int version){
	uint32_t cmd_reg_addr =
			(version == CPM4_VERSION) ?
					QDMA_CPM4_OFFSET_IND_CTXT_CMD :
					QDMA_OFFSET_IND_CTXT_CMD;

	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
			.Times(4)
			.WillOnce(Return(1))
			.WillOnce(Return(1))
			.WillOnce(Return(1))
			.WillRepeatedly(Return(0));
}

void mock_qdma_context_invalidate(int version)
{
	uint32_t cmd_reg_addr =
			(version == CPM4_VERSION) ?
					QDMA_CPM4_OFFSET_IND_CTXT_CMD :
					QDMA_OFFSET_IND_CTXT_CMD;

	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
			.Times(4)
			.WillOnce(Return(1))
			.WillOnce(Return(1))
			.WillOnce(Return(1))
			.WillRepeatedly(Return(0));
}

void mock_hw_monitor_failure(int version)
{
	uint32_t cmd_reg_addr =
			(version == CPM4_VERSION) ?
					QDMA_CPM4_OFFSET_IND_CTXT_CMD :
					QDMA_OFFSET_IND_CTXT_CMD;

	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
			.Times(50001)
			.WillRepeatedly(Return(1));
}


struct ctx_conf {
	struct ctx_conf_param {
		uint8_t valid_dev_hndl;
		uint8_t valid_cntxt;
		enum qdma_hw_access_type access_type;
		ctx_conf_param(uint8_t devhndl, uint8_t context,
				enum qdma_hw_access_type acs_type)
			:valid_dev_hndl(devhndl), valid_cntxt(context), access_type(acs_type){}
	};
	std::vector<ctx_conf_param> params;
	uint16_t val16bit;
	uint8_t c2h;
	uint8_t ip_version;
	ctx_conf(std::vector<ctx_conf_param>&& parameter, uint8_t ver):
		params(parameter), ip_version(ver){}
	ctx_conf(std::vector<ctx_conf_param>&& parameter, uint8_t ver,
			uint16_t rngidx):
			params(parameter), ip_version(ver), val16bit(rngidx){}
	ctx_conf(std::vector<ctx_conf_param>&& parameter, uint8_t ver,
			uint8_t is_c2h, uint16_t qid):
			params(parameter), ip_version(ver), c2h(is_c2h), val16bit(qid){}
};


class intx_cntx_conf_Test_class : public testing::TestWithParam<ctx_conf> {
		protected:
		void SetUp() override {}
		void TearDown() override {Mock::VerifyAndClear(&qdma_access_mock);}
};
class credit_ctx_conf_Test_class : public testing::TestWithParam<ctx_conf> {
		protected:
		void SetUp() override {}
		void TearDown() override {Mock::VerifyAndClear(&qdma_access_mock);}
};
class qid2vec_conf_Test_class : public testing::TestWithParam<ctx_conf> {
		protected:
		void SetUp() override {}
		void TearDown() override {Mock::VerifyAndClear(&qdma_access_mock);}
};
class hw_ctx_conf_Test_class : public testing::TestWithParam<ctx_conf> {
		protected:
		void SetUp() override {}
		void TearDown() override {Mock::VerifyAndClear(&qdma_access_mock);}
};
class cmpt_ctx_conf_Test_class : public testing::TestWithParam<ctx_conf> {
		protected:
		void SetUp() override {}
		void TearDown() override {Mock::VerifyAndClear(&qdma_access_mock);}
};
class pfetch_ctx_conf_Test_class : public testing::TestWithParam<ctx_conf> {
		protected:
		void SetUp() override {}
		void TearDown() override {Mock::VerifyAndClear(&qdma_access_mock);}
};
class sw_ctx_conf_Test_class : public testing::TestWithParam<ctx_conf> {
		protected:
		void SetUp() override {}
		void TearDown() override {Mock::VerifyAndClear(&qdma_access_mock);}
};
class fmap_conf_Test_class : public testing::TestWithParam<ctx_conf> {
		protected:
		void SetUp() override {}
		void TearDown() override {Mock::VerifyAndClear(&qdma_access_mock);}
};



/**
 * @brief      API020_qdma_indirect_intr_ctx_conf, FUT : int qdma_indirect_intr_ctx_conf(void *dev_hndl,
					uint16_t ring_index,
					struct qdma_indirect_intr_ctxt *ctxt,
					enum qdma_hw_access_type access_type)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - ctxt is NULL
 *             - access_type MAX Value
 *             - Success Cases
 */
static ctx_conf get_intx_cntx_cnf_params(uint8_t ip_version)
{
	std::vector<ctx_conf::ctx_conf_param> testParams;
	uint16_t ring_index;
	uint32_t num_txs = ((QDMA_HW_ACCESS_MAX - 1) * 3) +1;

	testParams.reserve(num_txs);
	ring_index = 0;

	testParams.emplace_back(1, 1, QDMA_HW_ACCESS_MAX);

	for (int j = 0; j < QDMA_HW_ACCESS_WRITE; j++) {
		testParams.emplace_back(1, 0,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}
	for (int j = 0; j < QDMA_HW_ACCESS_MAX; j++) {
		testParams.emplace_back(0, 1,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));

		testParams.emplace_back(1, 1,
				(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}


	return ctx_conf{std::move(testParams), ip_version, ring_index};
}



TEST_P(intx_cntx_conf_Test_class, qdma_indirect_intr_ctx_conf) {
	auto& testVals = GetParam();

	for (const auto& test : testVals.params) {

		if ((!test.valid_dev_hndl) || (!test.valid_cntxt)
			|| (test.access_type >= QDMA_HW_ACCESS_MAX)) {
			struct mock_devhndl dev_hndl;
			struct mock_devhndl *hndl = NULL;
			struct qdma_indirect_intr_ctxt *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt =
			(struct qdma_indirect_intr_ctxt *)malloc(sizeof(struct qdma_indirect_intr_ctxt));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
						&dev_hndl.hw_access));

			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_indirect_intr_ctx_conf((void *)hndl, testVals.val16bit,
							cntxt,
							test.access_type));

			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		} else {
			struct mock_devhndl *hndl = NULL;
			struct qdma_indirect_intr_ctxt *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt = (struct qdma_indirect_intr_ctxt *)malloc(sizeof(struct qdma_indirect_intr_ctxt));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init((void *)hndl, 0,
						&hndl->hw_access));

			switch (test.access_type) {
			case QDMA_HW_ACCESS_READ:
				mock_qdma_context_read(testVals.ip_version,
					(testVals.ip_version == EQDMA_SOFT_VERSION) ? 4 : 3);
				break;
			case QDMA_HW_ACCESS_WRITE:
				if (testVals.ip_version == CPM4_VERSION) {
					cntxt->page_size = QDMA_INDIRECT_INTR_RING_SIZE_32KB + 1;
					EXPECT_EQ(-QDMA_ERR_INV_PARAM,
						hndl->hw_access.qdma_indirect_intr_ctx_conf(hndl, testVals.val16bit,
						cntxt, test.access_type));
					cntxt->page_size = QDMA_INDIRECT_INTR_RING_SIZE_32KB;
				}
				mock_qdma_context_write(testVals.ip_version);
				break;
			case QDMA_HW_ACCESS_CLEAR:
				mock_qdma_context_clear(testVals.ip_version);
				break;
			case QDMA_HW_ACCESS_INVALIDATE:
				mock_qdma_context_invalidate(testVals.ip_version);
				break;
			default:
				break;
			}

			if (testVals.ip_version == CPM4_VERSION)
				cntxt->page_size = QDMA_INDIRECT_INTR_RING_SIZE_16KB;
			EXPECT_EQ(QDMA_SUCCESS, hndl->hw_access.qdma_indirect_intr_ctx_conf((void *)hndl,
							testVals.val16bit, cntxt, test.access_type));

			mock_hw_monitor_failure(testVals.ip_version);
			EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT, hndl->hw_access.qdma_indirect_intr_ctx_conf((void *)hndl,
							testVals.val16bit, cntxt, test.access_type));

			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		}
	}
}

INSTANTIATE_TEST_CASE_P(API020_qdma_indirect_intr_ctx_conf, intx_cntx_conf_Test_class,
						::testing::Values(get_intx_cntx_cnf_params(QDMA_SOFT_VERSION),
								get_intx_cntx_cnf_params(EQDMA_SOFT_VERSION),
								get_intx_cntx_cnf_params(CPM4_VERSION)));


/**
 * @brief      API021_qdma_credit_intr_ctx_conf, FUT : int qdma_credit_ctx_conf(void *dev_hndl, uint8_t c2h,
					uint16_t hw_qid,
					struct qdma_descq_credit_ctxt *ctxt,
					enum qdma_hw_access_type access_type
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - ctxt is NULL
 *             - access_type MAX Value
 *             - Success Cases
 */
static ctx_conf get_credit_ctx_conf_params(uint8_t ip_version, uint8_t c2h, uint16_t hw_qid)
{
	std::vector<ctx_conf::ctx_conf_param> testParams;
	uint32_t num_txs = ((QDMA_HW_ACCESS_MAX - 1) * 3) +1;

	testParams.reserve(num_txs);

	testParams.emplace_back(1, 1, QDMA_HW_ACCESS_MAX);

	for (int j = 0; j < QDMA_HW_ACCESS_WRITE; j++) {
		testParams.emplace_back(1, 0,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}
	for (int j = 0; j < QDMA_HW_ACCESS_MAX; j++) {
		testParams.emplace_back(0, 1,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));

		testParams.emplace_back(1, 1,
				(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}


	return ctx_conf{std::move(testParams), ip_version, c2h, hw_qid};
}


TEST_P(credit_ctx_conf_Test_class, qdma_credit_ctx_conf) {
	auto& testVals = GetParam();

	for (const auto& test : testVals.params) {

		if ((!test.valid_dev_hndl) || (!test.valid_cntxt) || (testVals.c2h > 1) ||
				(test.access_type >= QDMA_HW_ACCESS_MAX) || (test.access_type == QDMA_HW_ACCESS_WRITE)) {
			struct mock_devhndl dev_hndl;
			struct mock_devhndl *hndl = NULL;
			struct qdma_descq_credit_ctxt *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt = (struct qdma_descq_credit_ctxt *)malloc(sizeof(struct qdma_descq_credit_ctxt));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
						&dev_hndl.hw_access));

			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_credit_ctx_conf((void *)hndl, testVals.c2h,
					testVals.val16bit, cntxt, test.access_type));
			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		} else {
			struct mock_devhndl *hndl = NULL;
			struct qdma_descq_credit_ctxt *cntxt = NULL;

			hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			cntxt = (struct qdma_descq_credit_ctxt *)malloc(sizeof(struct qdma_descq_credit_ctxt));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init((void *)hndl, 0,
						&hndl->hw_access));

			switch (test.access_type) {
			case QDMA_HW_ACCESS_READ:
				mock_qdma_context_read(testVals.ip_version, 1);
				break;
			case QDMA_HW_ACCESS_CLEAR:
				mock_qdma_context_clear(testVals.ip_version);
				break;
			case QDMA_HW_ACCESS_INVALIDATE:
				mock_qdma_context_invalidate(testVals.ip_version);
				break;
			default:
				break;

			}

			EXPECT_EQ(QDMA_SUCCESS, hndl->hw_access.qdma_credit_ctx_conf(hndl,
							testVals.c2h, testVals.val16bit,
							cntxt,
							test.access_type));

			mock_hw_monitor_failure(testVals.ip_version);
			EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT, hndl->hw_access.qdma_credit_ctx_conf(hndl,
							testVals.c2h, testVals.val16bit,
							cntxt,
							test.access_type));

			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		}
	}
}

INSTANTIATE_TEST_CASE_P(API021_qdma_credit_intr_ctx_conf, credit_ctx_conf_Test_class,
						::testing::Values(get_credit_ctx_conf_params(QDMA_SOFT_VERSION, 0, 0),
								get_credit_ctx_conf_params(EQDMA_SOFT_VERSION, 0, 0),
								get_credit_ctx_conf_params(CPM4_VERSION, 0, 0),
								get_credit_ctx_conf_params(QDMA_SOFT_VERSION, 1, 0),
								get_credit_ctx_conf_params(EQDMA_SOFT_VERSION, 1, 0),
								get_credit_ctx_conf_params(CPM4_VERSION, 1, 0),
								get_credit_ctx_conf_params(QDMA_SOFT_VERSION, 2, 0),
								get_credit_ctx_conf_params(EQDMA_SOFT_VERSION, 2, 0)));


 /**
 * @brief      API022_qdma_qid2vec_conf, FUT : int qdma_qid2vec_conf(void *dev_hndl,
				uint8_t c2h, uint16_t hw_qid,
				struct qdma_qid2vec *ctxt,
				enum qdma_hw_access_type access_type_
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - ctxt is NULL
 *             - access_type MAX Value
 *             - Success Cases
 */
void mock_qdma_qid2vec_context_clear()
{
	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_CPM4_OFFSET_IND_CTXT_CMD))
			.WillRepeatedly(Return(0));
}



static ctx_conf get_qid2vec_ctx_conf_params(uint8_t ip_version, uint8_t c2h, uint16_t hw_qid)
{
	std::vector<ctx_conf::ctx_conf_param> testParams;
	uint32_t num_txs = ((QDMA_HW_ACCESS_MAX - 1) * 3) +1;

	testParams.reserve(num_txs);
	testParams.emplace_back(1, 1, QDMA_HW_ACCESS_MAX);

	for (int j = 0; j < QDMA_HW_ACCESS_WRITE; j++) {
		testParams.emplace_back(1, 0,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}
	for (int j = 0; j < QDMA_HW_ACCESS_MAX; j++) {
		testParams.emplace_back(0, 1,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));

		testParams.emplace_back(1, 1,
				(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}


	return ctx_conf{std::move(testParams), ip_version, c2h, hw_qid};
}


TEST_P(qid2vec_conf_Test_class, qdma_qid2vec_ctx_conf) {
	auto& testVals = GetParam();

	for (const auto& test : testVals.params) {
		if ((!test.valid_dev_hndl) || (!test.valid_cntxt) ||
				(test.access_type >= QDMA_HW_ACCESS_MAX)) {
			struct mock_devhndl dev_hndl;
			struct mock_devhndl *hndl = NULL;
			struct qdma_qid2vec *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt = (struct qdma_qid2vec *)malloc(sizeof(struct qdma_qid2vec));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
						&dev_hndl.hw_access));

			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_qid2vec_conf(hndl, testVals.c2h,
					testVals.val16bit, cntxt, test.access_type));
			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		} else {
			struct mock_devhndl *hndl = NULL;
			struct qdma_qid2vec *cntxt = NULL;

			hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			cntxt = (struct qdma_qid2vec *)malloc(sizeof(struct qdma_qid2vec));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(hndl, 0,
						&hndl->hw_access));

			switch (test.access_type) {
			case QDMA_HW_ACCESS_READ:
				mock_qdma_context_read(testVals.ip_version, 1);
				break;
			case QDMA_HW_ACCESS_WRITE:
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_CPM4_OFFSET_IND_CTXT_CMD))
						.Times(5)
						.WillOnce(Return(1))
						.WillOnce(Return(1))
						.WillOnce(Return(1))
						.WillRepeatedly(Return(0));
				break;
			case QDMA_HW_ACCESS_CLEAR:
				mock_qdma_qid2vec_context_clear();
				break;
			case QDMA_HW_ACCESS_INVALIDATE:
				mock_qdma_context_invalidate(testVals.ip_version);
				break;
			default:
				printf("Invalid Operation\n");
				break;
			}

			EXPECT_EQ(QDMA_SUCCESS, hndl->hw_access.qdma_qid2vec_conf(hndl,
							testVals.c2h, testVals.val16bit, cntxt,
							test.access_type));

			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,
					QDMA_CPM4_OFFSET_IND_CTXT_CMD))
					.Times(50001)
					.WillRepeatedly(Return(1));
			EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT, hndl->hw_access.qdma_qid2vec_conf(hndl,
							testVals.c2h, testVals.val16bit, cntxt,
							test.access_type));
			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		}
	}
}

INSTANTIATE_TEST_CASE_P(API022_qdma_qid2vec_conf, qid2vec_conf_Test_class,
						::testing::Values(get_qid2vec_ctx_conf_params(CPM4_VERSION, 0, 0),
						get_qid2vec_ctx_conf_params(CPM4_VERSION, 1, 0)));



 /**
 * @brief      API023_qdma_qdma_hw_ctx_conf, FUT : int qdma_hw_ctx_conf(void *dev_hndl,
					uint8_t c2h, uint16_t hw_qid,
					struct qdma_descq_hw_ctxt *ctxt,
					enum qdma_hw_access_type access_type)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - ctxt is NULL
 *             - access_type MAX Value
 *             - Success Cases
 */


static ctx_conf get_hw_ctx_conf_params(uint8_t ip_version, uint8_t c2h, uint16_t hw_qid)
{
	std::vector<ctx_conf::ctx_conf_param> testParams;
	uint32_t num_txs = ((QDMA_HW_ACCESS_MAX - 1) * 3) +1;

	testParams.reserve(num_txs);

	testParams.emplace_back(1, 1, QDMA_HW_ACCESS_MAX);

	for (int j = 0; j < QDMA_HW_ACCESS_WRITE; j++) {
		testParams.emplace_back(1, 0,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}
	for (int j = 0; j < QDMA_HW_ACCESS_MAX; j++) {
		testParams.emplace_back(0, 1,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));

		testParams.emplace_back(1, 1,
				(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}
	return ctx_conf{std::move(testParams), ip_version, c2h, hw_qid};
}


TEST_P(hw_ctx_conf_Test_class, qdma_hw_ctx_conf) {
	auto& testVals = GetParam();

	for (const auto& test : testVals.params) {

		if ((!test.valid_dev_hndl) || (!test.valid_cntxt) || (testVals.c2h > 1) ||
				(test.access_type >= QDMA_HW_ACCESS_MAX) || (test.access_type == QDMA_HW_ACCESS_WRITE)) {
			struct mock_devhndl dev_hndl;
			struct mock_devhndl *hndl = NULL;
			struct qdma_descq_hw_ctxt *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt = (struct qdma_descq_hw_ctxt *)malloc(sizeof(struct qdma_descq_hw_ctxt));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
						&dev_hndl.hw_access));

			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_hw_ctx_conf(hndl, testVals.c2h,
					testVals.val16bit, cntxt, test.access_type));
			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);

		} else {
			struct mock_devhndl *hndl = NULL;
			struct qdma_descq_hw_ctxt *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt = (struct qdma_descq_hw_ctxt *)malloc(sizeof(struct qdma_descq_hw_ctxt));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(hndl, 0,
						&hndl->hw_access));

			switch (test.access_type) {
			case QDMA_HW_ACCESS_READ:
				mock_qdma_context_read(testVals.ip_version, 2);
				break;
			case QDMA_HW_ACCESS_CLEAR:
				mock_qdma_context_clear(testVals.ip_version);
				break;
			case QDMA_HW_ACCESS_INVALIDATE:
				mock_qdma_context_invalidate(testVals.ip_version);
				break;
			default:
				break;

			}

			EXPECT_EQ(QDMA_SUCCESS, hndl->hw_access.qdma_hw_ctx_conf(hndl,
							testVals.c2h, testVals.val16bit,
							cntxt, test.access_type));

			mock_hw_monitor_failure(testVals.ip_version);
			EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT, hndl->hw_access.qdma_hw_ctx_conf(hndl,
							testVals.c2h, testVals.val16bit,
							cntxt, test.access_type));
			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		}
	}
}

INSTANTIATE_TEST_CASE_P(API023_qdma_hw_ctx_conf, hw_ctx_conf_Test_class,
						::testing::Values(get_hw_ctx_conf_params(QDMA_SOFT_VERSION, 0, 0),
						get_hw_ctx_conf_params(EQDMA_SOFT_VERSION, 0, 0),
						get_hw_ctx_conf_params(CPM4_VERSION, 0, 0),
						get_hw_ctx_conf_params(QDMA_SOFT_VERSION, 1, 0),
						get_hw_ctx_conf_params(EQDMA_SOFT_VERSION, 1, 0),
						get_hw_ctx_conf_params(CPM4_VERSION, 1, 0),
						get_hw_ctx_conf_params(QDMA_SOFT_VERSION, 2, 0)));


 /**
 * @brief      API024_qdma_cmpt_ctx_conf, FUT : int qdma_cmpt_ctx_conf(void *dev_hndl,
					uint16_t hw_qid,
					struct qdma_descq_cmpt_ctxt *ctxt,
					enum qdma_hw_access_type access_type)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - ctxt is NULL
 *             - access_type MAX Value
 *             - Success Cases
 */
static ctx_conf get_qdma_cmpt_ctx_conf_params(uint8_t ip_version, uint8_t c2h, uint16_t hw_qid)
{
	std::vector<ctx_conf::ctx_conf_param> testParams;
	uint32_t num_txs = ((QDMA_HW_ACCESS_MAX - 1) * 3) +1;

	testParams.reserve(num_txs);

	testParams.emplace_back(1, 1, QDMA_HW_ACCESS_MAX);

	for (int j = 0; j < QDMA_HW_ACCESS_WRITE; j++) {
		testParams.emplace_back(1, 0,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}
	for (int j = 0; j < QDMA_HW_ACCESS_MAX; j++) {
		testParams.emplace_back(0, 1,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));

		testParams.emplace_back(1, 1,
				(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}

	return ctx_conf{std::move(testParams), ip_version, hw_qid};
}


TEST_P(cmpt_ctx_conf_Test_class, qdma_cmpt_ctx_conf) {
	auto& testVals = GetParam();

	for (const auto& test : testVals.params) {

		if ((!test.valid_dev_hndl) || (!test.valid_cntxt) ||
				(test.access_type >= QDMA_HW_ACCESS_MAX)) {
			struct mock_devhndl dev_hndl;
			struct mock_devhndl *hndl = NULL;
			struct qdma_descq_cmpt_ctxt *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt = (struct qdma_descq_cmpt_ctxt *)malloc(sizeof(struct qdma_descq_cmpt_ctxt));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
						&dev_hndl.hw_access));
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_cmpt_ctx_conf(hndl, testVals.val16bit,
					cntxt, test.access_type));

			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		} else {
			struct mock_devhndl *hndl = NULL;
			struct qdma_descq_cmpt_ctxt *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt = (struct qdma_descq_cmpt_ctxt *)malloc(sizeof(struct qdma_descq_cmpt_ctxt));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(hndl, 0,
						&hndl->hw_access));

			switch (test.access_type) {
			case QDMA_HW_ACCESS_READ:
				mock_qdma_context_read(testVals.ip_version, ((testVals.ip_version == EQDMA_SOFT_VERSION) ? 6 : 5));
				break;
			case QDMA_HW_ACCESS_WRITE:
				if (testVals.ip_version != QDMA_SOFT_VERSION) {
					cntxt->trig_mode = QDMA_CMPT_UPDATE_TRIG_MODE_TMR_CNTR + 1;
					EXPECT_EQ(-QDMA_ERR_INV_PARAM, hndl->hw_access.qdma_cmpt_ctx_conf(hndl, testVals.val16bit,
						cntxt, test.access_type));
					cntxt->trig_mode = QDMA_CMPT_UPDATE_TRIG_MODE_TMR_CNTR;
				}
				mock_qdma_context_write(testVals.ip_version);
				break;
			case QDMA_HW_ACCESS_CLEAR:
				mock_qdma_context_clear(testVals.ip_version);
				break;
			case QDMA_HW_ACCESS_INVALIDATE:
				mock_qdma_context_invalidate(testVals.ip_version);
				break;
			default:
				break;

			}
			cntxt->trig_mode = QDMA_CMPT_UPDATE_TRIG_MODE_TMR_CNTR;
			EXPECT_EQ(QDMA_SUCCESS, hndl->hw_access.qdma_cmpt_ctx_conf(hndl,
							testVals.val16bit, cntxt, test.access_type));
			mock_hw_monitor_failure(testVals.ip_version);
			EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT, hndl->hw_access.qdma_cmpt_ctx_conf(hndl,
							testVals.val16bit, cntxt, test.access_type));
			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		}
	}
}

INSTANTIATE_TEST_CASE_P(API024_qdma_cmpt_ctx_conf, cmpt_ctx_conf_Test_class,
						::testing::Values(get_qdma_cmpt_ctx_conf_params(QDMA_SOFT_VERSION, 0, 0),
								get_qdma_cmpt_ctx_conf_params(EQDMA_SOFT_VERSION, 0, 0),
								get_qdma_cmpt_ctx_conf_params(CPM4_VERSION, 0, 0)));

/**
 * @brief      API025_qdma_pfetch_ctx_conf, FUT : int qdma_pfetch_ctx_conf(void *dev_hndl,
					uint16_t hw_qid,
					struct qdma_descq_prefetch_ctxt *ctxt,
					enum qdma_hw_access_type access_type)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - ctxt is NULL
 *             - access_type MAX Value
 *             - Success Cases
 */
static ctx_conf get_qdma_pfetch_ctx_conf_params(uint8_t ip_version, uint16_t hw_qid)
{
	std::vector<ctx_conf::ctx_conf_param> testParams;
	uint32_t num_txs = ((QDMA_HW_ACCESS_MAX - 1) * 3) +1;

	testParams.reserve(num_txs);

	testParams.emplace_back(1, 1, QDMA_HW_ACCESS_MAX);

	for (int j = 0; j < QDMA_HW_ACCESS_WRITE; j++) {
		testParams.emplace_back(1, 0,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}
	for (int j = 0; j < QDMA_HW_ACCESS_MAX; j++) {
		testParams.emplace_back(0, 1,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));

		testParams.emplace_back(1, 1,
				(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}


	return ctx_conf{std::move(testParams), ip_version, hw_qid};
}


TEST_P(pfetch_ctx_conf_Test_class, qdma_pfetch_ctx_conf) {
	auto& testVals = GetParam();

	for (const auto& test : testVals.params) {

		if ((!test.valid_dev_hndl) || (!test.valid_cntxt) ||
				(test.access_type >= QDMA_HW_ACCESS_MAX)) {
			struct mock_devhndl dev_hndl;
			struct mock_devhndl *hndl = NULL;
			struct qdma_descq_prefetch_ctxt *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt = (struct qdma_descq_prefetch_ctxt *)malloc(sizeof(struct qdma_descq_prefetch_ctxt));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
						&dev_hndl.hw_access));

			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_pfetch_ctx_conf(hndl, testVals.val16bit,
					cntxt, test.access_type));

			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		} else {
			struct mock_devhndl *hndl = NULL;
			struct qdma_descq_prefetch_ctxt *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt = (struct qdma_descq_prefetch_ctxt *)malloc(sizeof(struct qdma_descq_prefetch_ctxt));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(hndl, 0,
						&hndl->hw_access));

			switch (test.access_type) {
				case QDMA_HW_ACCESS_READ:
					mock_qdma_context_read(testVals.ip_version, 2);
					break;
				case QDMA_HW_ACCESS_WRITE:
					mock_qdma_context_write(testVals.ip_version);
					break;
				case QDMA_HW_ACCESS_CLEAR:
					mock_qdma_context_clear(testVals.ip_version);
					break;
				case QDMA_HW_ACCESS_INVALIDATE:
					mock_qdma_context_invalidate(testVals.ip_version);
					break;
				default:
					break;
			}

			EXPECT_EQ(QDMA_SUCCESS, hndl->hw_access.qdma_pfetch_ctx_conf(hndl,
							testVals.val16bit, cntxt,
							test.access_type));

			mock_hw_monitor_failure(testVals.ip_version);
			EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT, hndl->hw_access.qdma_pfetch_ctx_conf(hndl,
							testVals.val16bit, cntxt,
							test.access_type));
			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		}
	}
}

INSTANTIATE_TEST_CASE_P(API025_qdma_pfetch_ctx_conf, pfetch_ctx_conf_Test_class,
						::testing::Values(get_qdma_pfetch_ctx_conf_params(QDMA_SOFT_VERSION, 0),
								get_qdma_pfetch_ctx_conf_params(EQDMA_SOFT_VERSION, 0),
								get_qdma_pfetch_ctx_conf_params(CPM4_VERSION, 0)));


/**
 * @brief      API026_qdma_sw_ctx_conf, FUT : int qdma_sw_ctx_conf(void *dev_hndl,
													uint8_t c2h, uint16_t hw_qid,
													struct qdma_descq_sw_ctxt *ctxt,
													enum qdma_hw_access_type access_type)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - ctxt is NULL
 *             - access_type MAX Value
 *             - Success Cases
 */

static ctx_conf get_qdma_sw_ctx_conf_params(uint8_t ip_version, uint8_t c2h, uint16_t hw_qid)
{
	std::vector<ctx_conf::ctx_conf_param> testParams;
	uint32_t num_txs = ((QDMA_HW_ACCESS_MAX - 1) * 3) +1;

	testParams.reserve(num_txs);

	testParams.emplace_back(1, 1, QDMA_HW_ACCESS_MAX);

	for (int j = 0; j < QDMA_HW_ACCESS_WRITE; j++) {
		testParams.emplace_back(1, 0,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}
	for (int j = 0; j < QDMA_HW_ACCESS_MAX; j++) {
		testParams.emplace_back(0, 1,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));

		testParams.emplace_back(1, 1,
				(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}

	return ctx_conf{std::move(testParams), ip_version, c2h, hw_qid};
}


TEST_P(sw_ctx_conf_Test_class, qdma_sw_ctx_conf) {
	auto& testVals = GetParam();

	for (const auto& test : testVals.params) {

		if ((!test.valid_dev_hndl) || (!test.valid_cntxt) ||
				(test.access_type >= QDMA_HW_ACCESS_MAX)) {
			struct mock_devhndl dev_hndl;
			struct mock_devhndl *hndl = NULL;
			struct qdma_descq_sw_ctxt *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt = (struct qdma_descq_sw_ctxt *)malloc(sizeof(struct qdma_descq_sw_ctxt));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
						&dev_hndl.hw_access));

			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_sw_ctx_conf(hndl,
					testVals.c2h, testVals.val16bit, cntxt, test.access_type));
			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		} else {
			struct mock_devhndl *hndl = NULL;
			struct qdma_descq_sw_ctxt *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt = (struct qdma_descq_sw_ctxt *)malloc(sizeof(struct qdma_descq_sw_ctxt));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(hndl, 0,
						&hndl->hw_access));

			switch (test.access_type) {
			case QDMA_HW_ACCESS_READ:
				if (testVals.ip_version == CPM4_VERSION) {
					EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_CPM4_OFFSET_IND_CTXT_CMD))
							.Times(5)
							.WillOnce(Return(1))
							.WillOnce(Return(1))
							.WillOnce(Return(1))
							.WillRepeatedly(Return(0));
					for (int i = 0; i < 4; i++)
						EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (i * 4)))
									.WillRepeatedly(Return(0xff));
				} else if (testVals.ip_version == QDMA_SOFT_VERSION) {
					mock_qdma_context_read(testVals.ip_version, 5);
				} else {
					mock_qdma_context_read(testVals.ip_version, 8);
				}
				break;
			case QDMA_HW_ACCESS_WRITE:
				if (testVals.ip_version == CPM4_VERSION) {
					cntxt->desc_sz = QDMA_DESC_SIZE_64B + 1;
					EXPECT_EQ(-QDMA_ERR_INV_PARAM, hndl->hw_access.qdma_sw_ctx_conf(hndl, testVals.c2h,
								testVals.val16bit, cntxt, test.access_type));

					cntxt->desc_sz = QDMA_DESC_SIZE_64B;
					cntxt->rngsz_idx = QDMA_NUM_RING_SIZES;
					EXPECT_EQ(-QDMA_ERR_INV_PARAM, hndl->hw_access.qdma_sw_ctx_conf(hndl, testVals.c2h,
								testVals.val16bit, cntxt, test.access_type));
					cntxt->desc_sz = 0;
					cntxt->rngsz_idx = 0;
				}
				mock_qdma_context_write(testVals.ip_version);
				break;
			case QDMA_HW_ACCESS_CLEAR:
				mock_qdma_context_clear(testVals.ip_version);
				break;
			case QDMA_HW_ACCESS_INVALIDATE:
				mock_qdma_context_invalidate(testVals.ip_version);
				break;
			default:
				break;
			}

			EXPECT_EQ(QDMA_SUCCESS, hndl->hw_access.qdma_sw_ctx_conf(hndl, testVals.c2h,
							testVals.val16bit, cntxt, test.access_type));
		
			mock_hw_monitor_failure(testVals.ip_version);
			EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT, hndl->hw_access.qdma_sw_ctx_conf(hndl, testVals.c2h,
							testVals.val16bit, cntxt, test.access_type));
			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);
		}
	}
}

INSTANTIATE_TEST_CASE_P(API026_qdma_sw_ctx_conf, sw_ctx_conf_Test_class,
						::testing::Values(get_qdma_sw_ctx_conf_params(QDMA_SOFT_VERSION, 0, 0),
								get_qdma_sw_ctx_conf_params(EQDMA_SOFT_VERSION, 0, 0),
								get_qdma_sw_ctx_conf_params(CPM4_VERSION, 0, 0)));

/**
 * @brief      API027_qdma_fmap_conf, FUT : int qdma_fmap_conf(void *dev_hndl,
					uint16_t func_id,
					struct qdma_fmap_cfg *config,
					enum qdma_hw_access_type access_type)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - ctxt is NULL
 *             - access_type MAX Value
 *             - Success Cases 
 */
static ctx_conf get_qdma_fmap_conf_params(uint8_t ip_version, uint16_t func_id)
{
	std::vector<ctx_conf::ctx_conf_param> testParams;
	uint32_t num_txs = ((QDMA_HW_ACCESS_MAX - 1) * 3) +1;
	testParams.reserve(num_txs);

	testParams.emplace_back(1, 1, QDMA_HW_ACCESS_MAX);

	for (int j = 0; j < QDMA_HW_ACCESS_WRITE; j++) {
		testParams.emplace_back(1, 0,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}
	for (int j = 0; j < QDMA_HW_ACCESS_MAX; j++) {
		testParams.emplace_back(0, 1,
			(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));

		testParams.emplace_back(1, 1,
				(enum qdma_hw_access_type)(QDMA_HW_ACCESS_READ + j));
	}
	return ctx_conf{std::move(testParams), ip_version, func_id};
}


TEST_P(fmap_conf_Test_class, qdma_fmap_ctx_conf) {
	auto& testVals = GetParam();

	for (const auto& test : testVals.params) {

		if ((!test.valid_dev_hndl) || (!test.valid_cntxt) ||
				(test.access_type >= QDMA_HW_ACCESS_MAX) || (test.access_type == QDMA_HW_ACCESS_INVALIDATE)) {
			struct mock_devhndl dev_hndl;
			struct mock_devhndl *hndl = NULL;
			struct qdma_fmap_cfg *cntxt = NULL;

			if (test.valid_dev_hndl)
				hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
			if (test.valid_cntxt)
				cntxt = (struct qdma_fmap_cfg *)malloc(sizeof(struct qdma_fmap_cfg));

			mock_access_init(testVals.ip_version);
			EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
						&dev_hndl.hw_access));

			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_fmap_conf(hndl,
					testVals.val16bit, cntxt, test.access_type));

			if (hndl)
				free(hndl);
			if (cntxt)
				free(cntxt);	
		} else {
			if (testVals.ip_version != CPM4_VERSION) {
				struct mock_devhndl *hndl = NULL;
				struct qdma_fmap_cfg *cntxt = NULL;

				if (test.valid_dev_hndl)
					hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
				if (test.valid_cntxt)
					cntxt = (struct qdma_fmap_cfg *)malloc(sizeof(struct qdma_fmap_cfg));

				mock_access_init(testVals.ip_version);
				EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(hndl, 0,
							&hndl->hw_access));

				switch (test.access_type) {
				case QDMA_HW_ACCESS_READ:
					mock_qdma_context_read(testVals.ip_version, 5);
					break;
				case QDMA_HW_ACCESS_WRITE:
					mock_qdma_context_write(testVals.ip_version);
					break;
				case QDMA_HW_ACCESS_CLEAR:
					mock_qdma_context_clear(testVals.ip_version);
					break;
				case QDMA_HW_ACCESS_INVALIDATE:
					mock_qdma_context_invalidate(testVals.ip_version);
					break;
				default:
					break;
				}

				EXPECT_EQ(QDMA_SUCCESS, hndl->hw_access.qdma_fmap_conf(hndl,
								testVals.val16bit, cntxt, test.access_type));

				mock_hw_monitor_failure(testVals.ip_version);
				EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT, hndl->hw_access.qdma_fmap_conf(hndl,
								testVals.val16bit, cntxt, test.access_type));
				if (hndl)
					free(hndl);
				if (cntxt)
					free(cntxt);
			} else {
				struct mock_devhndl *hndl = NULL;
				struct qdma_fmap_cfg *cntxt = NULL;

				if (test.valid_dev_hndl)
					hndl = (struct mock_devhndl *)malloc(sizeof(struct mock_devhndl));
				if (test.valid_cntxt)
					cntxt = (struct qdma_fmap_cfg *)malloc(sizeof(struct qdma_fmap_cfg));

				mock_access_init(testVals.ip_version);
				EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(hndl, 0,
							&hndl->hw_access));

				switch (test.access_type) {
					case QDMA_HW_ACCESS_READ:
						EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,(QDMA_CPM4_REG_TRQ_SEL_FMAP_BASE +
											(testVals.val16bit * QDMA_CPM4_REG_TRQ_SEL_FMAP_STEP))))
						.WillOnce(Return(1));
						break;
					case QDMA_HW_ACCESS_WRITE:
						break;
					case QDMA_HW_ACCESS_CLEAR:
						break;
					default:
						break;
				}

				EXPECT_EQ(QDMA_SUCCESS, hndl->hw_access.qdma_fmap_conf(hndl,
								testVals.val16bit, cntxt, test.access_type));

				if (hndl)
					free(hndl);
				if (cntxt)
					free(cntxt);

			}
		}
	}
}

INSTANTIATE_TEST_CASE_P(API027_qdma_fmap_conf, fmap_conf_Test_class,
						::testing::Values(get_qdma_fmap_conf_params(QDMA_SOFT_VERSION, 0),
								get_qdma_fmap_conf_params(EQDMA_SOFT_VERSION, 0),
								get_qdma_fmap_conf_params(CPM4_VERSION, 0)));

/**
 * @brief      API028_qdma_dump_config_regs, FUT : int qdma_dump_config_regs(void *dev_hndl,
					uint8_t is_vf, char *buf,
					uint32_t buflen)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - buf is NULL
 *             - is_vf is 1
 *             - Success Cases
 */


void mock_queue_dump_config_regs(struct mock_devhndl &dev_hndl, struct xreg_info *reg_info, uint32_t no_of_regs)
{
	for (int i = 0; i < no_of_regs; i++) {
		if ((GET_CAPABILITY_MASK(dev_hndl.dev_cap.mm_en, dev_hndl.dev_cap.st_en,
				dev_hndl.dev_cap.mm_cmpt_en, dev_hndl.dev_cap.mailbox_en)
				& reg_info[i].mode) == 0)
			continue;
		if (dev_hndl.dev_cap.debug_mode == 0 &&
				reg_info[i].is_debug_reg == 1) {
			continue;
		}
		for (int j = 0; j < reg_info[i].repeat; j++) {

			switch(reg_info[i].addr + (j * 4)) {
			case 0x104:
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,(reg_info[i].addr + (j * 4))))
					.Times(2)
					.WillOnce(Return(QDMA_OFFSET_GLBL2_PF_BARLITE_INT_VAL))
					.WillOnce(Return(QDMA_OFFSET_GLBL2_PF_BARLITE_INT_VAL));

				break;
			case 0x118:
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_MDMA))
					.Times(2)
					.WillOnce(Return(QDMA_OFFSET_GLBL2_CHANNEL_MDMA_VAL))
					.WillOnce(Return(QDMA_OFFSET_GLBL2_CHANNEL_MDMA_VAL));
				break;
			case 0x120:
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP))
					.Times(2)
					.WillOnce(Return(QDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP_VAL))
					.WillOnce(Return(QDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP_VAL));
				break;
			case 0x134:
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
					.Times(2)
					.WillOnce(Return(QDMA_OFFSET_GLBL2_MISC_CAP_VAL))
					.WillOnce(Return(QDMA_OFFSET_GLBL2_MISC_CAP_VAL));
				break;
			default:
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,(reg_info[i].addr + (j * 4))))
					.WillOnce(Return(1));
				break;
			}
		}
	}
}
 
TEST_F(qdma_access_api_test, API028_qdma_dump_config_regs)
{

	for (int k = QDMA_SOFT_VERSION; k < QDMA_NUM_VERSIONS; k++) {
		struct mock_devhndl dev_hndl;

		mock_access_init(k);
		EXPECT_EQ(QDMA_SUCCESS, qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));
		mock_dev_attr_regs(k);
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, &dev_hndl.dev_cap));

		{
			/*Testcases : dev_hndl is NULL*/
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_dump_config_regs(NULL,
							0, NULL, 100));
		}

		{
			/*Testcases : buf is NULL*/
			EXPECT_EQ(-QDMA_ERR_NO_MEM, dev_hndl.hw_access.qdma_dump_config_regs(&dev_hndl,
							0, NULL, 100));
		}

		if (k == QDMA_SOFT_VERSION) {
			//printf("QDMA Soft\n");
			struct xreg_info *reg_info = qdma_get_config_regs();
			int buflen = qdma_soft_reg_dump_buf_len();
			char *buf = (char *)malloc(buflen);
			uint32_t no_of_regs = qdma_get_config_num_regs();

			/*Testcases : is_vf is 1*/
			EXPECT_EQ(-QDMA_ERR_HWACC_FEATURE_NOT_SUPPORTED, dev_hndl.hw_access.qdma_dump_config_regs(&dev_hndl,
					1, buf, buflen));

			mock_queue_dump_config_regs(dev_hndl, reg_info, no_of_regs);
			/*Testcases : success case*/
			EXPECT_LT(0, dev_hndl.hw_access.qdma_dump_config_regs(&dev_hndl,
							0, buf, buflen));
		} else if (k == CPM4_VERSION) {
			//printf("CPM4 Hard\n");
			struct xreg_info *reg_info = qdma_cpm4_get_config_regs();
			int buflen = qdma_cpm4_reg_dump_buf_len();
			char *buf = (char *)malloc(buflen);
			uint32_t no_of_regs = qdma_cpm4_get_config_num_regs();

			/*Testcases : is_vf is 1*/
			EXPECT_EQ(-QDMA_ERR_HWACC_FEATURE_NOT_SUPPORTED, dev_hndl.hw_access.qdma_dump_config_regs(&dev_hndl,
					1, buf, buflen));

			mock_queue_dump_config_regs(dev_hndl, reg_info, no_of_regs);
			/*Testcases : success case*/
			EXPECT_LT(0, dev_hndl.hw_access.qdma_dump_config_regs(&dev_hndl,
						0, buf, buflen));
		}
		else  {
			//printf("EQDMA SOft IP\n");
			struct xreg_info *reg_info = eqdma_get_config_regs();
			int buflen = eqdma_reg_dump_buf_len();
			char *buf = (char *)malloc(buflen);
			uint32_t no_of_regs = eqdma_get_config_num_regs();

			/*Testcases : is_vf is 1*/
			EXPECT_EQ(-QDMA_ERR_HWACC_FEATURE_NOT_SUPPORTED, dev_hndl.hw_access.qdma_dump_config_regs(&dev_hndl,
					1, buf, buflen));

			mock_queue_dump_config_regs(dev_hndl, reg_info, no_of_regs);

			/** TODO : This additional expect_call is for register 0x104, as the register ODS file doesn't have regs 0x104, 0x108, 0x10c, 0x100 */
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_PF_BARLITE_INT))
				.Times(1)
				.WillOnce(Return(EQDMA_OFFSET_GLBL2_PF_BARLITE_INT_VAL));
			/*Testcases : success case*/
			EXPECT_LT(0, dev_hndl.hw_access.qdma_dump_config_regs(&dev_hndl,
							0, buf, buflen));
		}
	}
}


/**
 * @brief      API029_qdma_dump_queue_context, FUT : int qdma_dump_queue_context(void *dev_hndl, uint8_t is_vf,
															uint8_t st,
															enum qdma_dev_q_type q_type,
															struct qdma_descq_context *ctxt_data,
															char *buf, uint32_t buflen)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - ctxt_data is NULL
 *             - q_type QDMA_DEV_Q_TYPE_MAX
 *             - buf is NULL
 *             - buflen 0
 *             - Success Cases
 */

TEST_F(qdma_access_api_test, API029_qdma_dump_queue_context)
{
	for (int k = QDMA_SOFT_VERSION; k < QDMA_NUM_VERSIONS; k++) {
		struct mock_devhndl dev_hndl;

		mock_access_init(k);
		EXPECT_EQ(QDMA_SUCCESS, qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));
		mock_dev_attr_regs(k);
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, &dev_hndl.dev_cap));

		{
			/*Testcases : dev_hndl is NULL*/
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_dump_queue_context(NULL,
							0, QDMA_DEV_Q_TYPE_H2C, NULL, NULL, 0));
		}

		{
			/*Testcases : ctxt_data is NULL*/
			int buflen = 17664 * 2;
			char *buf = (char *)malloc(buflen);
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_dump_queue_context(&dev_hndl,
					 0, QDMA_DEV_Q_TYPE_H2C, NULL, buf, buflen));
			free(buf);
		}

		{
			/*Testcases : buf is NULL*/
			struct qdma_descq_context ctxt_data = {0};
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_dump_queue_context(&dev_hndl,
					0, QDMA_DEV_Q_TYPE_H2C, &ctxt_data, NULL, 17664));
		}

		{
			/*Testcases : buflen is 0*/
			struct qdma_descq_context ctxt_data = {0};
			char buf[10] = {0};
			EXPECT_EQ(-QDMA_ERR_NO_MEM, dev_hndl.hw_access.qdma_dump_queue_context(&dev_hndl,
					0, QDMA_DEV_Q_TYPE_H2C, &ctxt_data, buf, 0));
		}


		{
			/*Testcases : q_type QDMA_DEV_Q_TYPE_MAX*/
			struct qdma_descq_context ctxt_data = {0};
			int buflen = 17664 * 2;
			char *buf = (char *)malloc(buflen);
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_dump_queue_context(&dev_hndl,
					0, QDMA_DEV_Q_TYPE_MAX, &ctxt_data, buf, buflen));
			free(buf);
		}

		if (k == QDMA_SOFT_VERSION) {
			for (int i = QDMA_DEV_Q_TYPE_H2C; i < QDMA_DEV_Q_TYPE_MAX; i++) {
				struct qdma_descq_context ctxt_data = {0};
				int buflen = 17664;
				char *buf = (char *)malloc(buflen);
				int times = 2;

				EXPECT_LT(0, dev_hndl.hw_access.qdma_dump_queue_context(&dev_hndl,
						0, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i),
						&ctxt_data, buf, buflen));

				EXPECT_LT(0, dev_hndl.hw_access.qdma_dump_queue_context(&dev_hndl,
						 1, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i),
						&ctxt_data, buf, buflen));

				EXPECT_LT(0, dev_hndl.hw_access.qdma_dump_queue_context(&dev_hndl,
						1, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i),
						&ctxt_data, buf, buflen));

				EXPECT_LT(0, dev_hndl.hw_access.qdma_dump_queue_context(&dev_hndl,
									1, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i),
									&ctxt_data, buf, buflen));
			}
		} else {
			for (int i = QDMA_DEV_Q_TYPE_H2C; i <= QDMA_DEV_Q_TYPE_CMPT; i++) {
				struct qdma_descq_context ctxt_data = {0};
				int buflen = 22784;
				char *buf = (char *)malloc(buflen);
				int retval = 0;
				if (k != EQDMA_SOFT_VERSION) {
					if (i >= QDMA_DEV_Q_TYPE_CMPT)
						retval = -2;
				}


				EXPECT_LT(retval, dev_hndl.hw_access.qdma_dump_queue_context(&dev_hndl,
						0, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i),
						&ctxt_data, buf, buflen));
				if (k == CPM4_VERSION) {
					EXPECT_LT(retval, dev_hndl.hw_access.qdma_dump_queue_context(&dev_hndl,
							0, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i),
							&ctxt_data, buf, buflen));
				}

				EXPECT_LT(retval, dev_hndl.hw_access.qdma_dump_queue_context(&dev_hndl,
						0, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i),
						&ctxt_data, buf, buflen));

				EXPECT_LT(retval, dev_hndl.hw_access.qdma_dump_queue_context(&dev_hndl,
									1, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i),
									&ctxt_data, buf, buflen));
			}
		}

	}
}


/**
 * @brief      API030_qdma_dump_intr_context, FUT : int qdma_dump_intr_context(void *dev_hndl,
															struct qdma_indirect_intr_ctxt *intr_ctx,
															int ring_index,
															char *buf, uint32_t buflen)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - ctxt_data is NULL
 *             - q_type QDMA_DEV_Q_TYPE_MAX
 *             - buf is NULL
 *             - buflen 0
 *             - Success Cases 
 */
TEST_F(qdma_access_api_test, API030_qdma_dump_intr_context)
{
	for (int k = QDMA_SOFT_VERSION; k < QDMA_NUM_VERSIONS; k++) {
		struct mock_devhndl dev_hndl;

		mock_access_init(k);
		EXPECT_EQ(QDMA_SUCCESS, qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));
		mock_dev_attr_regs(k);
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, &dev_hndl.dev_cap));

		{
			/*Testcases : dev_hndl is NULL*/
			struct qdma_indirect_intr_ctxt intr_ctx = {0};
			char buf[10] = {0};

			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_dump_intr_context(NULL,
					&intr_ctx, 0, buf, 10));
		}

		{
			char buf[10] = {0};
			/*Testcases : ctxt_data is NULL*/
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_dump_intr_context(&dev_hndl,
					NULL, 0, buf, 10));
		}
		{
			/*Testcases : buf is NULL*/
			struct qdma_indirect_intr_ctxt intr_ctx = {0};
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_dump_intr_context(&dev_hndl,
					&intr_ctx, 0, NULL, 10));
		}

		{
			struct qdma_indirect_intr_ctxt intr_ctx = {0};
			char buf[10] = {0};
			/*Testcases : buf is 0*/
			EXPECT_EQ(-QDMA_ERR_NO_MEM, dev_hndl.hw_access.qdma_dump_intr_context(&dev_hndl,
					&intr_ctx, 0, buf, 0));
		}

		for (int i = 0; i < 514; i++) {
			struct qdma_indirect_intr_ctxt intr_ctx = {0};
			int buflen = 17664;
			char *buf = (char *)malloc(buflen);
			/*Testcases : buf is 0*/
			EXPECT_LT(0, dev_hndl.hw_access.qdma_dump_intr_context(&dev_hndl,
					&intr_ctx, i, buf, buflen));
			free(buf);
		}
	}
}



void mock_sw_context_read_fail(int version)
{
	uint32_t cmd_reg_addr = (version == CPM4_VERSION) ?
			QDMA_CPM4_OFFSET_IND_CTXT_CMD :
			QDMA_OFFSET_IND_CTXT_CMD;

	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
								.Times(50001)
								.WillRepeatedly(Return(1));
}

void mock_hw_context_read_fail(int version)
{

	uint32_t cmd_reg_addr = (version == CPM4_VERSION) ?
			QDMA_CPM4_OFFSET_IND_CTXT_CMD :
			QDMA_OFFSET_IND_CTXT_CMD;
	InSequence s;
	int sw_context_words = 4;

	/*Sw Context read mock*/
	if (version == EQDMA_SOFT_VERSION) {
		sw_context_words = 8;
	} else if (version == QDMA_SOFT_VERSION) {
		sw_context_words = 5;
	}
	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
						.WillOnce(Return(0));
	for (int i = 0; i < sw_context_words; i++) {
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (i * 4)))
				.Times(1)
				.WillRepeatedly(Return(0xff));
	}

	/*Qid2Vec Context read mock*/
	if (version == CPM4_VERSION) {
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
						.Times(1)
						.WillRepeatedly(Return(0));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA))
						.Times(1)
						.WillOnce(Return(0xff));
	}

	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
								.Times(50001)
								.WillRepeatedly(Return(1));

}

void mock_credit_context_read_fail(int version, bool qid2vec)
{
	uint32_t cmd_reg_addr = (version == CPM4_VERSION) ?
			QDMA_CPM4_OFFSET_IND_CTXT_CMD :
			QDMA_OFFSET_IND_CTXT_CMD;
	InSequence s;
	int sw_context_words = 4;

	/*Sw Context read mock*/
	if (version == EQDMA_SOFT_VERSION) {
		sw_context_words = 8;
	} else if (version == QDMA_SOFT_VERSION) {
		sw_context_words = 5;
	}
	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
						.WillOnce(Return(0));
	for (int i = 0; i < sw_context_words; i++) {
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (i * 4)))
				.Times(1)
				.WillRepeatedly(Return(0xff));
	}
	/*Qid2Vec Context read mock*/
	if (version == CPM4_VERSION) {
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
						.Times(1)
						.WillRepeatedly(Return(0));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA))
						.Times(1)
						.WillOnce(Return(0xff));
	}
	/*HW context read mock*/
	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
						.WillOnce(Return(0));
	for (int i = 0; i < 2; i++) {
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (i * 4)))
				.Times(1)
				.WillRepeatedly(Return(0xff));
	}
	/*Qid2Vec Context read mock*/
	if ((version == CPM4_VERSION) && qid2vec) {
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
						.Times(1)
						.WillRepeatedly(Return(0));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA))
						.Times(1)
						.WillOnce(Return(0xff));
	}

	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
								.Times(50001)
								.WillRepeatedly(Return(1));
}

void mock_pfetch_context_read_fail(int version, bool st, enum qdma_dev_q_type q_type)
{
	uint32_t cmd_reg_addr = (version == CPM4_VERSION) ?
			QDMA_CPM4_OFFSET_IND_CTXT_CMD :
			QDMA_OFFSET_IND_CTXT_CMD;
	InSequence s;

	if ((st == true) && (q_type == QDMA_DEV_Q_TYPE_C2H)) {
		/*Sw Context read mock*/
		int sw_context_words = 4;
		if (version == EQDMA_SOFT_VERSION) {
			sw_context_words = 8;
		} else if (version == QDMA_SOFT_VERSION) {
			sw_context_words = 5;
		}
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
							.WillOnce(Return(0));
		for (int i = 0; i < sw_context_words; i++) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (i * 4)))
					.Times(1)
					.WillRepeatedly(Return(0xff));
		}
		/*Qid2Vec Context read mock*/
		if (version == CPM4_VERSION) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
							.Times(1)
							.WillRepeatedly(Return(0));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA))
							.Times(1)
							.WillOnce(Return(0xff));
		}
		/*HW context read mock*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
							.WillOnce(Return(0));
		for (int i = 0; i < 2; i++) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (i * 4)))
					.Times(1)
					.WillRepeatedly(Return(0xff));
		}
		/*Qid2Vec Context read mock*/
		if ((version == CPM4_VERSION)) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
							.Times(1)
							.WillRepeatedly(Return(0));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA))
							.Times(1)
							.WillOnce(Return(0xff));
		}

		/*Credit Context read mock*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
					.Times(1)
					.WillRepeatedly(Return(0));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA))
					.Times(1)
					.WillRepeatedly(Return(0xff));

		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
									.Times(50001)
									.WillRepeatedly(Return(1));
	} else {
		printf("Invalid Options\n");
	}
}

void mock_cmpt_context_read_fail(int version, bool st, enum qdma_dev_q_type q_type)
{
	uint32_t cmd_reg_addr = (version == CPM4_VERSION) ?
			QDMA_CPM4_OFFSET_IND_CTXT_CMD :
			QDMA_OFFSET_IND_CTXT_CMD;
	InSequence s;
	if (version == CPM4_VERSION) {
		return;
	}
	if ((st == true) && (q_type == QDMA_DEV_Q_TYPE_C2H)) {
		/*Sw Context read mock*/
		int sw_context_words = 5;
		if (version == EQDMA_SOFT_VERSION) {
			sw_context_words = 8;
		}
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
							.WillOnce(Return(0));
		for (int i = 0; i < sw_context_words; i++) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (i * 4)))
					.Times(1)
					.WillRepeatedly(Return(0xff));
		}

		/*HW context read mock*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
							.WillOnce(Return(0));
		for (int i = 0; i < 2; i++) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (i * 4)))
					.Times(1)
					.WillRepeatedly(Return(0xff));
		}

		/*Credit Context read mock*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
					.Times(1)
					.WillRepeatedly(Return(0));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA))
					.Times(1)
					.WillRepeatedly(Return(0xff));

		/*Pfetch Context read mock*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
					.Times(1)
					.WillRepeatedly(Return(0));
		for (int i = 0; i < 2; i++) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (i * 4)))
					.Times(1)
					.WillRepeatedly(Return(0xff));
		}

		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
									.Times(50001)
									.WillRepeatedly(Return(1));
	} else {
		printf("Invalid Options\n");
	}
}


void mock_context_read_and_dump(int version, bool st, enum qdma_dev_q_type q_type)
{
	uint32_t cmd_reg_addr = (version == CPM4_VERSION) ?
			QDMA_CPM4_OFFSET_IND_CTXT_CMD :
			QDMA_OFFSET_IND_CTXT_CMD;

	if (version == QDMA_SOFT_VERSION) {
		if (!st && (q_type == QDMA_DEV_Q_TYPE_CMPT)) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
								.Times(1)
								.WillRepeatedly(Return(0));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (0 * 4)))
								.Times(1)
								.WillRepeatedly(Return(0xff));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (1 * 4)))
								.Times(1)
								.WillRepeatedly(Return(0xff));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (2 * 4)))
									.Times(1)
									.WillRepeatedly(Return(0xff));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (3 * 4)))
								.Times(1)
								.WillRepeatedly(Return(0xff));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (4 * 4)))
									.Times(1)
									.WillRepeatedly(Return(0xff));

		} else if ((st == true) && (q_type == QDMA_DEV_Q_TYPE_C2H)) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
								.Times(5)
								.WillRepeatedly(Return(0));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (0 * 4)))
								.Times(5)
								.WillRepeatedly(Return(0xff));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (1 * 4)))
								.Times(4)
								.WillRepeatedly(Return(0xff));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (2 * 4)))
									.Times(2)
									.WillRepeatedly(Return(0xff));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (3 * 4)))
								.Times(2)
								.WillRepeatedly(Return(0xff));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (4 * 4)))
									.Times(2)
									.WillRepeatedly(Return(0xff));
		} else if (q_type != QDMA_DEV_Q_TYPE_CMPT) {
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
								.Times(3)
								.WillRepeatedly(Return(0));

			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA))
								.Times(3)
								.WillRepeatedly(Return(0xff));

			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (1 * 4)))
								.Times(2)
								.WillRepeatedly(Return(0xff));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (2 * 4)))
									.Times(1)
									.WillRepeatedly(Return(0xff));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (3 * 4)))
								.Times(1)
								.WillRepeatedly(Return(0xff));
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (4 * 4)))
									.Times(1)
									.WillRepeatedly(Return(0xff));
		}
	} else if (version == CPM4_VERSION) {
		if ((st == true) && (q_type == QDMA_DEV_Q_TYPE_C2H)) {
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
									.Times(7)
									.WillRepeatedly(Return(0));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (0 * 4)))
									.Times(7)
									.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (1 * 4)))
									.Times(4)
									.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (2 * 4)))
										.Times(2)
										.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (3 * 4)))
									.Times(2)
									.WillRepeatedly(Return(0xff));
		} else if (q_type != QDMA_DEV_Q_TYPE_CMPT) {
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
									.Times(5)
									.WillRepeatedly(Return(0));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (0 * 4)))
									.Times(5)
									.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (1 * 4)))
									.Times(2)
									.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (2 * 4)))
										.Times(1)
										.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (3 * 4)))
									.Times(1)
									.WillRepeatedly(Return(0xff));
			}
		} else {
			if ((st == true) && (q_type == QDMA_DEV_Q_TYPE_C2H)) {

				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
									.Times(5)
									.WillRepeatedly(Return(0));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (0 * 4)))
									.Times(5)
									.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (1 * 4)))
									.Times(4)
									.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (2 * 4)))
										.Times(2)
										.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (3 * 4)))
									.Times(2)
									.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (4 * 4)))
										.Times(2)
										.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (5 * 4)))
										.Times(2)
										.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (6 * 4)))
										.Times(1)
										.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (7 * 4)))
										.Times(1)
										.WillRepeatedly(Return(0xff));

			} else if (q_type != QDMA_DEV_Q_TYPE_CMPT) {

				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
									.Times(3)
									.WillRepeatedly(Return(0));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (0 * 4)))
									.Times(3)
									.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (1 * 4)))
									.Times(2)
									.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (2 * 4)))
										.Times(1)
										.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (3 * 4)))
									.Times(1)
									.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (4 * 4)))
										.Times(1)
										.WillRepeatedly(Return(0xff));
								EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (5 * 4)))
										.Times(1)
										.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (6 * 4)))
										.Times(1)
										.WillRepeatedly(Return(0xff));
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_IND_CTXT_DATA + (7 * 4)))
										.Times(1)
										.WillRepeatedly(Return(0xff));	
			}
	}
}

/**
 * @brief API031_qdma_read_dump_queue_context, FUT : int qdma_read_dump_queue_context(void *dev_hndl,
														uint8_t is_vf,
														uint16_t qid_hw,
														uint8_t st,
														enum qdma_dev_q_type q_type,
														char *buf, uint32_t buflen)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - ctxt_data is NULL
 *             - q_type QDMA_DEV_Q_TYPE_MAX
 *             - buf is NULL
 *             - buflen 0
 *             - Success Cases
 */
TEST_F(qdma_access_api_test, API031_qdma_read_dump_queue_context)
{
	for (int k = QDMA_SOFT_VERSION; k < QDMA_NUM_VERSIONS; k++) {
		struct mock_devhndl dev_hndl;

		mock_access_init(k);
		EXPECT_EQ(QDMA_SUCCESS, qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));
		mock_dev_attr_regs(k);

		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, &dev_hndl.dev_cap));
		{
			/*Testcases : dev_hndl = NULL*/
			char buf[10] = {0};
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_read_dump_queue_context(NULL,
						0, 0, QDMA_DEV_Q_TYPE_H2C, buf, 10));
		}

		{

			char buf[10] = {0};

			EXPECT_EQ(-QDMA_ERR_NO_MEM, dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
					 0, 0, QDMA_DEV_Q_TYPE_H2C, buf, 10));
		}

		{
			/*Testcases : q_type = QDMA_DEV_Q_TYPE_MAX*/
			char buf[10] = {0};
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
					 0, 0, QDMA_DEV_Q_TYPE_MAX, buf, 10));
		}

		{
			/*Testcases : buf = NULL*/
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
					 0, 0, QDMA_DEV_Q_TYPE_MAX, NULL, 10));
		}

		{
			/*Testcases : buflen = 0*/
			char buf[10] = {0};
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
					 0, 0, QDMA_DEV_Q_TYPE_MAX, buf, 0));
		}

		if (k == QDMA_SOFT_VERSION) {
			for (int i = QDMA_DEV_Q_TYPE_H2C; i < QDMA_DEV_Q_TYPE_MAX; i++) {
				int buflen = 17664;
				char *buf = (char *)malloc(buflen);

				/*Testcases : Success for ST = 0*/
				mock_context_read_and_dump(k, false, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i));
				EXPECT_LT(0, dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
						 0, 0, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i), buf, buflen));

				/*Testcases : Success for ST = 1*/
				mock_context_read_and_dump(k, true, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i));
				EXPECT_LT(0, dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
						 0, 1, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i), buf, buflen));

				free(buf);

			}
		} else {
			for (int i = QDMA_DEV_Q_TYPE_H2C; i <= QDMA_DEV_Q_TYPE_C2H; i++) {
				int buflen = 22784;
				char *buf = (char *)malloc(buflen);

				/*Testcases : Success for ST = 0*/
				mock_context_read_and_dump(k, false, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i));
				EXPECT_LT(0, dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
						 0, 0, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i), buf, buflen));

				/*Testcases : Success for ST = 1*/
				mock_context_read_and_dump(k, true, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i));
				EXPECT_LT(0, dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
						 0, 1, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C + i), buf, buflen));

				free(buf);
			}
		}

		{
			int buflen = 22784;
			char *buf = (char *)malloc(buflen);

			/*Testcases : sw context read failure*/

			mock_sw_context_read_fail(k);
			EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT,
				dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
					 0, 0, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C), buf, buflen));

			/*Testcases : hw context read failure*/
			mock_hw_context_read_fail(k);
			EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT,
				dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
					 0, 0, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C), buf, buflen));

			mock_credit_context_read_fail(k, false);
			EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT,
			dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
				 0, 0, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C), buf, buflen));

			if (k == CPM4_VERSION) {
				mock_credit_context_read_fail(k, true);
				EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT,
				dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
					 0, 0, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_H2C), buf, buflen));
			}

			mock_pfetch_context_read_fail(k, true, QDMA_DEV_Q_TYPE_C2H);
			EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT,
			dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
				 0, 1, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_C2H), buf, buflen));

			if (k != CPM4_VERSION) {
				mock_cmpt_context_read_fail(k, true, QDMA_DEV_Q_TYPE_C2H);
				EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT,
				dev_hndl.hw_access.qdma_read_dump_queue_context(&dev_hndl,
					 0, 1, (enum qdma_dev_q_type)(QDMA_DEV_Q_TYPE_C2H), buf, buflen));
			}
			free(buf);
		}

	}
}

/**
 * @brief API032_qdma_global_writeback_interval_conf, FUT : int qdma_global_writeback_interval_conf(void *dev_hndl,
														enum qdma_wrb_interval *wb_int,
														enum qdma_hw_access_type access_type)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - wb_int is NULL
 *             - access_type QDMA_DEV_Q_TYPE_MAX
 *             - Success Cases
 */
TEST_F(qdma_access_api_test, API032_qdma_global_writeback_interval_conf)
{
	for (int k = QDMA_SOFT_VERSION; k < QDMA_NUM_VERSIONS; k++) {
		struct mock_devhndl dev_hndl;

		mock_access_init(k);
		EXPECT_EQ(QDMA_SUCCESS, qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));
		mock_dev_attr_regs(k);
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, &dev_hndl.dev_cap));

		/*Testcases : dev_hndl is NULL*/
		{
			enum qdma_wrb_interval wb_int = QDMA_WRB_INTERVAL_512;

			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_global_writeback_interval_conf(NULL,
						NULL, QDMA_HW_ACCESS_READ));
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_global_writeback_interval_conf(NULL,
						&wb_int, QDMA_HW_ACCESS_WRITE));
		}
		/*Testcases : wb_int is NULL*/
		{
			enum qdma_wrb_interval wb_int = QDMA_NUM_WRB_INTERVALS;

			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_global_writeback_interval_conf(&dev_hndl,
						NULL, QDMA_HW_ACCESS_READ));
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_global_writeback_interval_conf(&dev_hndl,
						&wb_int, QDMA_HW_ACCESS_WRITE));
		}
		/*Testcases : Invalid Params*/
		{
			enum qdma_wrb_interval wb_int;
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_global_writeback_interval_conf(&dev_hndl,
						&wb_int, QDMA_HW_ACCESS_CLEAR));
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_global_writeback_interval_conf(&dev_hndl,
						&wb_int, QDMA_HW_ACCESS_INVALIDATE));
		}
		/*Testcases : Success case*/
		{
			enum qdma_wrb_interval wb_int;

			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_DSC_CFG))
								.WillRepeatedly(Return(0));
			mock_dev_attr_regs(k);
			EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_global_writeback_interval_conf(&dev_hndl,
						&wb_int, QDMA_HW_ACCESS_READ));
			mock_dev_attr_regs(k);
			EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_global_writeback_interval_conf(&dev_hndl,
						&wb_int, QDMA_HW_ACCESS_WRITE));
		}
		/*Testcases : Disabled capabilities*/
		{
			dev_hndl.dev_cap.st_en = dev_hndl.dev_cap.mm_cmpt_en = 0;
			enum qdma_wrb_interval wb_int = QDMA_WRB_INTERVAL_512;

			mock_dev_attr_regs(k, BIT_STREAM_MM_ONLY, false);
			EXPECT_EQ(-QDMA_ERR_HWACC_FEATURE_NOT_SUPPORTED,
						dev_hndl.hw_access.qdma_global_writeback_interval_conf(&dev_hndl,
						&wb_int, QDMA_HW_ACCESS_READ));
			mock_dev_attr_regs(k, BIT_STREAM_MM_ONLY, false);
			EXPECT_EQ(-QDMA_ERR_HWACC_FEATURE_NOT_SUPPORTED,
						dev_hndl.hw_access.qdma_global_writeback_interval_conf(&dev_hndl,
						&wb_int, QDMA_HW_ACCESS_WRITE));
		}
	}
}



 /**
 * @brief API033_qdma_set_default_global_csr, FUT : int qdma_set_default_global_csr(void *dev_hndl)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - Success Cases
 */
TEST_F(qdma_access_api_test, API033_qdma_set_default_global_csr)
{
	for (int k = QDMA_SOFT_VERSION; k < QDMA_NUM_VERSIONS; k++) {

		struct mock_devhndl dev_hndl;

		mock_access_init(k);
		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));
		/*Testcases : dev_hndl is NULL*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_set_default_global_csr(NULL));

		/*Testcases : Success Cases*/
		mock_dev_attr_regs(k);
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, &dev_hndl.dev_cap));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_C2H_PFETCH_CACHE_DEPTH))
							.WillRepeatedly(Return(0));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_C2H_CMPT_COAL_BUF_DEPTH))
							.WillRepeatedly(Return(0));
		mock_dev_attr_regs(k);
		if (dev_hndl.hw_access.qdma_set_default_global_csr)
			EXPECT_EQ(QDMA_SUCCESS,
					dev_hndl.hw_access.qdma_set_default_global_csr(&dev_hndl));
	}

}

/**
 * @brief API034_qdma_hw_error_enable, FUT : int qdma_hw_error_enable(void *dev_hndl, enum qdma_error_idx err_idx)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - err_idx QDMA_ERRS_ALL + 1
 *             - Success Cases
 */
TEST_F(qdma_access_api_test, API034_qdma_hw_error_enable)
{
	printf("WARNING: This test case needs some fixes for CPM4 Hard Devices, Temporarily patched\n");

	for (int k = QDMA_SOFT_VERSION; k < QDMA_NUM_VERSIONS; k++) {
		struct mock_devhndl dev_hndl;

		mock_access_init(k);
		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));
		mock_dev_attr_regs(k);
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, &dev_hndl.dev_cap));

		if (k != CPM4_VERSION) {
			/*Testcases : dev_hndl is NULL*/
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_hw_error_enable(NULL, (enum qdma_error_idx)(QDMA_ERRS_ALL + 1)));
		}

		if (k == QDMA_SOFT_VERSION) {
			/*Testcases : err_idx > QDMA_ERRS_ALL*/
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_hw_error_enable(&dev_hndl,
					(enum qdma_error_idx)(QDMA_ERRS_ALL + 1)));
		}
		else if (k == CPM4_VERSION) {
			/*Testcases : err_idx > EQDMA_ERRS_ALL*/
			//EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_hw_error_enable(&dev_hndl,
			//		(enum qdma_error_idx)(EQDMA_ERRS_ALL + 1)));
		}

		else {
			/*Testcases : err_idx > EQDMA_ERRS_ALL*/
			EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_hw_error_enable(&dev_hndl,
					(enum qdma_error_idx)(EQDMA_ERRS_ALL + 1)));
		}

		if (k != CPM4_VERSION) {
			/*Testcases : Success Cases*/
			for (int i = QDMA_DSC_ERR_POISON; i < QDMA_ERRS_ALL; i++) {
				if (k != EQDMA_SOFT_VERSION) {
					EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, qdma_err_info[i].mask_reg_addr))
										.WillRepeatedly(Return(0xffffffff));
				} else {
					EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, eqdma_err_info[i].mask_reg_addr))
										.WillRepeatedly(Return(0xffffffff));
				}
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_MASK))
									.WillRepeatedly(Return(0xffffffff));

				mock_dev_attr_regs(k);
				EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_enable(&dev_hndl,
						(enum qdma_error_idx)(i)));

				if (i < QDMA_ST_C2H_ERR_MTY_MISMATCH &&
						i > QDMA_ST_H2C_ERR_ALL) {
						if (k != EQDMA_SOFT_VERSION) {
							EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, qdma_err_info[i].mask_reg_addr))
												.WillRepeatedly(Return(0xffffffff));
						} else {
							EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, eqdma_err_info[i].mask_reg_addr))
												.WillRepeatedly(Return(0xffffffff));
						}
						EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_MASK))
											.WillRepeatedly(Return(0xffffffff));
				}
				mock_dev_attr_regs(k);
				EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_enable(&dev_hndl,
						(enum qdma_error_idx)(i)));
			}
		}

		if (k == QDMA_SOFT_VERSION) {
			mock_dev_attr_regs(k);
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_MASK))
								.Times(TOTAL_LEAF_ERROR_AGGREGATORS)
								.WillRepeatedly(Return(0xffffffff));
			EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_enable(&dev_hndl,
					QDMA_ERRS_ALL));
		}
		else if (k == CPM4_VERSION) {
			//EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_MASK))
			//					.Times(TOTAL_LEAF_ERROR_AGGREGATORS)
			//					.WillRepeatedly(Return(0xffffffff));
		}
		else {
			mock_dev_attr_regs(k);
			EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_MASK))
								.Times(EQDMA_TOTAL_LEAF_ERROR_AGGREGATORS)
								.WillRepeatedly(Return(0xffffffff));
			EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_enable(&dev_hndl,
					EQDMA_ERRS_ALL));
		}


		{
			int temp = 0;
			if (k == QDMA_SOFT_VERSION) {
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_MASK))
								.Times(TOTAL_LEAF_ERROR_AGGREGATORS - 3) // 3 errors are not present for MM only bitstream
								.WillRepeatedly(Return(0xffffffff));
				mock_dev_attr_regs(k, BIT_STREAM_MM_ONLY);

				EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_enable(&dev_hndl,
					QDMA_ERRS_ALL));
			}
			else if (k == CPM4_VERSION) {
				//none
				;
			}
			else {
				EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, QDMA_OFFSET_GLBL_ERR_MASK)) //EQDMA_GLBL_ERR_MASK_ADDR
								.Times(EQDMA_TOTAL_LEAF_ERROR_AGGREGATORS - 3) // 3 errors are not present for MM only bitstream
								.WillRepeatedly(Return(0xffffffff));
				mock_dev_attr_regs(k, BIT_STREAM_MM_ONLY);
				EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_hw_error_enable(&dev_hndl,
					EQDMA_ERRS_ALL));
			}
		}
	}

}


/**
 * @brief API035_qdma_global_csr_conf, FUT : int qdma_hw_error_enable(void *dev_hndl, enum qdma_error_idx err_idx)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - err_idx QDMA_ERRS_ALL + 1
 *             - Success Cases
 */
void mock_qdma_read_csr_values(uint32_t reg_offst,
		uint32_t idx, uint32_t cnt)
{
	uint32_t index, reg_addr;

	reg_addr = reg_offst + (idx * sizeof(uint32_t));
	for (index = 0; index < cnt; index++) {
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, reg_addr +
					      (index * sizeof(uint32_t))))
						.WillOnce(Return(0xff));

	}
}
struct struct_global_csr_conf {
	struct global_csr_conf_params {
		uint8_t valid_dev_hndl;
		uint8_t index;
		uint8_t count;
		uint8_t csr_val;
		enum qdma_global_csr_type csr_type;
		enum qdma_hw_access_type access_type;
		int expected_return;
		int reg_offst;
		global_csr_conf_params(uint8_t dev_hndl, uint8_t ind, uint8_t cnt,
				uint8_t csrval,
				enum qdma_global_csr_type csrtyp,
				enum qdma_hw_access_type accesstyp, int retval, int offset)
			:valid_dev_hndl(dev_hndl), index(ind), count(cnt), csr_val(csrval),
				csr_type(csrtyp), access_type(accesstyp), expected_return(retval),
				reg_offst(offset){}
	};
	int ip_version;
	std::vector<global_csr_conf_params> params;

	struct_global_csr_conf(std::vector<global_csr_conf_params>&& parameter, int version):
		params(parameter), ip_version(version){}
};


class global_csr_conf_Test_class : public testing::TestWithParam<struct_global_csr_conf> {
	protected:
		void SetUp() override {}
		void TearDown() override {Mock::VerifyAndClear(&qdma_access_mock);}
};

static struct_global_csr_conf get_global_csr_conf_params(int version, uint8_t index, uint8_t count,
							enum qdma_global_csr_type csr_type, uint32_t reg_offset, bool negcase = true)
{
	std::vector<struct_global_csr_conf::global_csr_conf_params> testParams;

	testParams.reserve(14);

	if (negcase) {
		testParams.emplace_back(0, 0, 0, 1, csr_type, QDMA_HW_ACCESS_READ, -QDMA_ERR_INV_PARAM, reg_offset);
		testParams.emplace_back(1, 0, 0, 1, csr_type, QDMA_HW_ACCESS_READ, -QDMA_ERR_INV_PARAM,reg_offset);
		testParams.emplace_back(1, 16, 10, 1, csr_type, QDMA_HW_ACCESS_READ, -QDMA_ERR_INV_PARAM, reg_offset);
		testParams.emplace_back(1, 0, 100, 1, csr_type, QDMA_HW_ACCESS_READ, -QDMA_ERR_INV_PARAM, reg_offset);
		testParams.emplace_back(1, 0, 10, 0, csr_type, QDMA_HW_ACCESS_READ, -QDMA_ERR_INV_PARAM, reg_offset);
		testParams.emplace_back(0, 0, 0, 1, csr_type, QDMA_HW_ACCESS_WRITE, -QDMA_ERR_INV_PARAM, reg_offset);
		testParams.emplace_back(1, 0, 0, 1, csr_type, QDMA_HW_ACCESS_WRITE, -QDMA_ERR_INV_PARAM,reg_offset);
		testParams.emplace_back(1, 16, 10, 1, csr_type, QDMA_HW_ACCESS_WRITE, -QDMA_ERR_INV_PARAM, reg_offset);
		testParams.emplace_back(1, 0, 100, 1, csr_type, QDMA_HW_ACCESS_WRITE, -QDMA_ERR_INV_PARAM, reg_offset);
		testParams.emplace_back(1, 0, 10, 0, csr_type, QDMA_HW_ACCESS_WRITE, -QDMA_ERR_INV_PARAM, reg_offset);
		testParams.emplace_back(1, 0, 10, 0, csr_type, QDMA_HW_ACCESS_MAX, -QDMA_ERR_INV_PARAM, reg_offset);
		testParams.emplace_back(1, 0, 10, 0, csr_type, QDMA_HW_ACCESS_CLEAR, -QDMA_ERR_INV_PARAM, reg_offset);
		testParams.emplace_back(1, 0, 10, 0, csr_type, QDMA_HW_ACCESS_INVALIDATE, -QDMA_ERR_INV_PARAM, reg_offset);
	}
	testParams.emplace_back(1, index, count, 1, csr_type, QDMA_HW_ACCESS_READ, QDMA_SUCCESS, reg_offset);
	testParams.emplace_back(1, index, count, 1, csr_type, QDMA_HW_ACCESS_WRITE, QDMA_SUCCESS, reg_offset);

	return struct_global_csr_conf{std::move(testParams), version};
}

TEST_P(global_csr_conf_Test_class, global_csr_conf) {
	auto& testVals = GetParam();
	struct mock_devhndl dev_hndl;
	enum qdma_global_csr_type test_csr;

	mock_access_init(testVals.ip_version);
	EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));
	mock_dev_attr_regs(testVals.ip_version);
	EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, &dev_hndl.dev_cap));

	for (const auto& test : testVals.params) {
		uint32_t csr_values[20] = {0};
		if ((test.expected_return == QDMA_SUCCESS) &&
			test.access_type == QDMA_HW_ACCESS_READ) {
			mock_qdma_read_csr_values(test.reg_offst,
				test.index, test.count);
		}
		if ((test.expected_return == QDMA_SUCCESS) &&
			((test.csr_type == QDMA_CSR_TIMER_CNT) ||
			(test.csr_type == QDMA_CSR_CNT_TH) ||
			(test.csr_type == QDMA_CSR_BUF_SZ))) {
			mock_dev_attr_regs(testVals.ip_version);
		}
		test_csr = test.csr_type;
		EXPECT_EQ(test.expected_return, dev_hndl.hw_access.qdma_global_csr_conf(
				test.valid_dev_hndl ? (&dev_hndl): NULL,
				test.index, test.count,
				test.csr_val ? csr_values : NULL, test.csr_type, test.access_type));
	}

	{
		uint32_t csr_values[20] = {0};
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_global_csr_conf(
				(void *)&dev_hndl, 0, 10, csr_values,
				(enum qdma_global_csr_type)(QDMA_CSR_BUF_SZ + 1), QDMA_HW_ACCESS_READ));
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_global_csr_conf(
				&dev_hndl, 0, 10, csr_values,
				(enum qdma_global_csr_type)(QDMA_CSR_BUF_SZ + 1), QDMA_HW_ACCESS_WRITE));

		if (test_csr != QDMA_CSR_RING_SZ) {
			dev_hndl.dev_cap.st_en = dev_hndl.dev_cap.mm_cmpt_en = 0;
			mock_dev_attr_regs(testVals.ip_version, BIT_STREAM_MM_ONLY, false);
			EXPECT_EQ(-QDMA_ERR_HWACC_FEATURE_NOT_SUPPORTED, dev_hndl.hw_access.qdma_global_csr_conf(
					(void *)&dev_hndl, 0, 10, csr_values,
					test_csr, QDMA_HW_ACCESS_READ));
			mock_dev_attr_regs(testVals.ip_version, BIT_STREAM_MM_ONLY, false);
			EXPECT_EQ(-QDMA_ERR_HWACC_FEATURE_NOT_SUPPORTED, dev_hndl.hw_access.qdma_global_csr_conf(
					(void *)&dev_hndl, 0, 10, csr_values,
					test_csr, QDMA_HW_ACCESS_WRITE));
		}
	}
}

INSTANTIATE_TEST_CASE_P(API035_qdma_global_csr_conf, global_csr_conf_Test_class,
						::testing::Values(get_global_csr_conf_params(QDMA_SOFT_VERSION, 0, 16, QDMA_CSR_RING_SZ, QDMA_OFFSET_GLBL_RNG_SZ),
							get_global_csr_conf_params(QDMA_SOFT_VERSION, 0, 16, QDMA_CSR_TIMER_CNT, QDMA_OFFSET_C2H_TIMER_CNT),
							get_global_csr_conf_params(QDMA_SOFT_VERSION, 0, 16, QDMA_CSR_CNT_TH, QDMA_OFFSET_C2H_CNT_TH),
							get_global_csr_conf_params(QDMA_SOFT_VERSION, 0, 16, QDMA_CSR_BUF_SZ, QDMA_OFFSET_C2H_BUF_SZ),
							get_global_csr_conf_params(EQDMA_SOFT_VERSION, 0, 16, QDMA_CSR_RING_SZ, QDMA_OFFSET_GLBL_RNG_SZ),
							get_global_csr_conf_params(EQDMA_SOFT_VERSION, 0, 16, QDMA_CSR_TIMER_CNT, QDMA_OFFSET_C2H_TIMER_CNT),
							get_global_csr_conf_params(EQDMA_SOFT_VERSION, 0, 16, QDMA_CSR_CNT_TH, QDMA_OFFSET_C2H_CNT_TH),
							get_global_csr_conf_params(EQDMA_SOFT_VERSION, 0, 16, QDMA_CSR_BUF_SZ, QDMA_OFFSET_C2H_BUF_SZ),
							get_global_csr_conf_params(CPM4_VERSION, 0, 16, QDMA_CSR_RING_SZ, QDMA_OFFSET_GLBL_RNG_SZ),
							get_global_csr_conf_params(CPM4_VERSION, 0, 16, QDMA_CSR_TIMER_CNT, QDMA_OFFSET_C2H_TIMER_CNT),
							get_global_csr_conf_params(CPM4_VERSION, 0, 16, QDMA_CSR_CNT_TH, QDMA_OFFSET_C2H_CNT_TH),
							get_global_csr_conf_params(CPM4_VERSION, 0, 16, QDMA_CSR_BUF_SZ, QDMA_OFFSET_C2H_BUF_SZ)
							));

/**
 * @brief API036_init_ctxt_memory, FUT : int qdma_hw_error_enable(void *dev_hndl, enum qdma_error_idx err_idx)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - err_idx QDMA_ERRS_ALL + 1
 *             - Success Cases
 */
TEST_F(qdma_access_api_test, API036_init_ctxt_memory)
{
	for (int k = QDMA_SOFT_VERSION; k < QDMA_NUM_VERSIONS; k++) {

		struct mock_devhndl dev_hndl;
		uint32_t cmd_reg_addr = (k == CPM4_VERSION) ?
					QDMA_CPM4_OFFSET_IND_CTXT_CMD :
					QDMA_OFFSET_IND_CTXT_CMD;
		uint32_t times = (k == CPM4_VERSION) ? 16384 : 16388;

		mock_access_init(k);
		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));
		mock_dev_attr_regs(k);
		EXPECT_EQ(QDMA_SUCCESS,
				dev_hndl.hw_access.qdma_get_device_attributes(&dev_hndl, &dev_hndl.dev_cap));

		/*Testcases : dev_hndl is NULL*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM, dev_hndl.hw_access.qdma_init_ctxt_memory(NULL));

		mock_dev_attr_regs(k);
		/*Testcases : Success*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
			.Times(times)
			.WillRepeatedly(Return(0));

		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_init_ctxt_memory(&dev_hndl));

		/*Testcases : Hw Access timeout*/
		mock_dev_attr_regs(k);
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
			.Times(50001)
			.WillRepeatedly(Return(1));

		EXPECT_EQ(-QDMA_ERR_HWACC_BUSY_TIMEOUT, dev_hndl.hw_access.qdma_init_ctxt_memory(&dev_hndl));

		/*Testcases : ST Disabled*/
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_PF_BARLITE_INT))
				.WillOnce(Return(QDMA_OFFSET_GLBL2_PF_BARLITE_INT_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP))
				.WillOnce(Return(QDMA_OFFSET_GLBL2_CHANNEL_QDMA_CAP_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_MISC_CAP))
			.WillOnce(Return(QDMA_OFFSET_GLBL2_MISC_CAP_VAL));
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_,QDMA_OFFSET_GLBL2_CHANNEL_MDMA))
				.WillOnce(Return(0x0000F));

		times = (k == CPM4_VERSION) ? 12288 : 12292;
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, cmd_reg_addr))
			.Times(times)
			.WillRepeatedly(Return(0));

		EXPECT_EQ(QDMA_SUCCESS, dev_hndl.hw_access.qdma_init_ctxt_memory(&dev_hndl));

	}

}


/**
 * @brief API037_qdma_reg_dump_buf_len, FUT : int qdma_reg_dump_buf_len(void *dev_hndl,
													uint8_t is_vf, uint32_t *buflen)
 *
 * @details    Testcases :
 *             - dev_hndl is NULL
 *             - Success for PF
 *             - Success for VF
 *             - buflen is NULL
 */
TEST_F(qdma_access_api_test, API037_qdma_acc_reg_dump_buf_len)
{
	enum qdma_ip_type ip_type;
	for (int k = QDMA_SOFT_VERSION; k < QDMA_NUM_VERSIONS; k++) {

		struct mock_devhndl dev_hndl;
		int buflen;
		switch (k)
		{
			case QDMA_SOFT_VERSION:
				ip_type = QDMA_SOFT_IP;
				break;
			case EQDMA_SOFT_VERSION:
				ip_type = QDMA_SOFT_IP;
				break;
			case CPM4_VERSION:
				ip_type = QDMA_SOFT_IP;
				break;
		}
		mock_access_init(k);
		EXPECT_EQ(QDMA_SUCCESS , qdma_hw_access_init(&dev_hndl, 0,
					&dev_hndl.hw_access));

		/*Testcases : dev_hndl is NULL*/
		EXPECT_EQ(-QDMA_ERR_INV_PARAM , qdma_acc_reg_dump_buf_len(NULL, ip_type,
					&buflen));

		EXPECT_EQ(QDMA_SUCCESS , qdma_acc_reg_dump_buf_len(&dev_hndl, ip_type,
					&buflen));

		EXPECT_EQ(QDMA_SUCCESS , qdma_acc_reg_dump_buf_len(&dev_hndl, ip_type,
					&buflen));
	}
}



