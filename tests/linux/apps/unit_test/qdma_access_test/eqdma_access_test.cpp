#include "qdma_platform_mock.h"
//#include "qdma_soft_reg.h"
//#include "qdma_soft_access.h"
//#include "qdma_cpm4_reg.h"
#include "eqdma_soft_reg.h"
//#include "qdma_cpm4_access.h"
#include "eqdma_soft_access.h"
#include "qdma_reg_dump.h"
#include "eqdma_access_test.h"

using::testing::_;
using::testing::AtLeast;
using::testing::Return;
using::testing::Mock;
using::testing::InSequence;

struct eqdma_errors_mock eqdma_mock_errs_info[EQDMA_TOTAL_LEAF_ERROR_AGGREGATORS] =
{
	        {EQDMA_DSC_ERR_POISON, mock_desc_err_poison},
	        {EQDMA_TRQ_ERR_CSR_UNMAPPED, mock_eqdma_hw_trq_err},
	        {EQDMA_ST_C2H_ERR_MTY_MISMATCH, mock_eqdma_hw_st_c2h_err},
	        {EQDMA_ST_FATAL_ERR_MTY_MISMATCH, mock_eqdma_hw_st_c2h_err},
	        {EQDMA_ST_H2C_ERR_ZERO_LEN_DESC, mock_eqdma_hw_st_h2c_err},
			  {EQDMA_SBE_1_ERR_RC_RRQ_EVEN_RAM, mock_eqdma_hw_ram_sbe_err},
	        {EQDMA_SBE_ERR_MI_H2C0_DAT, mock_eqdma_hw_ram_sbe_err},
			  {EQDMA_DBE_1_ERR_RC_RRQ_EVEN_RAM, mock_eqdma_hw_ram_dbe_err},
	        {EQDMA_DBE_ERR_MI_H2C0_DAT, mock_eqdma_hw_ram_dbe_err}

};

void mock_dummy_error(void) {
	//none
	;
}


void mock_desc_err_poison(void)
{
	int i = 0, len = 0;
	uint32_t desc_err_reg_list[] = {
		EQDMA_GLBL_DSC_ERR_STS_ADDR,
		EQDMA_GLBL_DSC_ERR_LOG0_ADDR,
		EQDMA_GLBL_DSC_ERR_LOG1_ADDR,
		EQDMA_GLBL_DSC_DBG_DAT0_ADDR,
		EQDMA_GLBL_DSC_DBG_DAT1_ADDR,
		EQDMA_GLBL_DSC_ERR_LOG2_ADDR
	};
	int desc_err_num_regs = sizeof(desc_err_reg_list)/sizeof(uint32_t);

	for (i = 0; i < desc_err_num_regs; i++) {
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, desc_err_reg_list[i]))
							.WillRepeatedly(Return(0xffffffff));
	}
}

void mock_eqdma_hw_trq_err(void)
{
	int i = 0, len = 0;
	uint32_t trq_err_reg_list[] = {
		EQDMA_GLBL_TRQ_ERR_STS_ADDR,
		EQDMA_GLBL_TRQ_ERR_LOG_ADDR
	};
	int trq_err_reg_num_regs = sizeof(trq_err_reg_list)/sizeof(uint32_t);

	for (i = 0; i < trq_err_reg_num_regs; i++) {
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, trq_err_reg_list[i]))
							.WillRepeatedly(Return(0xffffffff));
	}
}

void mock_eqdma_hw_st_c2h_err(void)
{
	int i = 0, len = 0;
	uint32_t st_c2h_err_reg_list[] = {
		EQDMA_C2H_ERR_STAT_ADDR,
		EQDMA_C2H_FATAL_ERR_STAT_ADDR,
		EQDMA_C2H_FIRST_ERR_QID_ADDR,
		EQDMA_C2H_STAT_S_AXIS_C2H_ACCEPTED_ADDR,
		EQDMA_C2H_STAT_S_AXIS_WRB_ACCEPTED_ADDR,
		EQDMA_C2H_STAT_DESC_RSP_PKT_ACCEPTED_ADDR,
		EQDMA_C2H_STAT_AXIS_PKG_CMP_ADDR,
		EQDMA_C2H_STAT_DBG_DMA_ENG_0_ADDR,
		EQDMA_C2H_STAT_DBG_DMA_ENG_1_ADDR,
		EQDMA_C2H_STAT_DBG_DMA_ENG_2_ADDR,
		EQDMA_C2H_STAT_DBG_DMA_ENG_3_ADDR,
		EQDMA_C2H_STAT_DESC_RSP_DROP_ACCEPTED_ADDR,
		EQDMA_C2H_STAT_DESC_RSP_ERR_ACCEPTED_ADDR
	};
	int st_c2h_err_num_regs = sizeof(st_c2h_err_reg_list)/sizeof(uint32_t);

	for (i = 0; i < st_c2h_err_num_regs; i++) {
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, st_c2h_err_reg_list[i]))
							.WillRepeatedly(Return(0xffffffff));
	}
}

void mock_eqdma_hw_st_h2c_err(void)
{
	int i = 0, len = 0;
	uint32_t st_h2c_err_reg_list[] = {
		EQDMA_H2C_ERR_STAT_ADDR,
		EQDMA_H2C_FIRST_ERR_QID_ADDR,
		EQDMA_H2C_DBG_REG0_ADDR,
		EQDMA_H2C_DBG_REG1_ADDR,
		EQDMA_H2C_DBG_REG2_ADDR,
		EQDMA_H2C_DBG_REG3_ADDR,
		EQDMA_H2C_DBG_REG4_ADDR
	};
	int st_h2c_err_num_regs = sizeof(st_h2c_err_reg_list)/sizeof(uint32_t);

	for (i = 0; i < st_h2c_err_num_regs; i++) {
		EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, st_h2c_err_reg_list[i]))
							.WillRepeatedly(Return(0xffffffff));
	}
}

void mock_eqdma_hw_ram_sbe_err(void)
{
	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, EQDMA_RAM_SBE_STS_A_ADDR))
						.WillRepeatedly(Return(0xffffffff));
	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, EQDMA_RAM_SBE_STS_1_A_ADDR))
						.WillRepeatedly(Return(0xffffffff));

}

void mock_eqdma_hw_ram_dbe_err(void)
{
	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, EQDMA_RAM_DBE_STS_A_ADDR))
						.WillRepeatedly(Return(0xffffffff));
	EXPECT_CALL(qdma_access_mock, qdma_reg_read(_, EQDMA_RAM_DBE_STS_1_A_ADDR))
						.WillRepeatedly(Return(0xffffffff));
}






