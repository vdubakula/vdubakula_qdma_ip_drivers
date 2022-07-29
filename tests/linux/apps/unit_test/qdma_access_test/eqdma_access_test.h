#ifndef __EQDMA_ACCESS_TEST_H__
#define __EQDMA_ACCESS_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#define EQDMA_TOTAL_LEAF_ERROR_AGGREGATORS   9

struct eqdma_errors_mock {
	uint32_t hw_err_position;
	void (*mock_err)(void);
};

extern struct eqdma_errors_mock eqdma_mock_errs_info[EQDMA_TOTAL_LEAF_ERROR_AGGREGATORS];

void mock_desc_err_poison(void);
void mock_eqdma_hw_trq_err(void);
void mock_eqdma_hw_st_c2h_err(void);
void mock_eqdma_hw_st_h2c_err(void);
void mock_eqdma_hw_ram_sbe_err(void);
void mock_eqdma_hw_ram_dbe_err(void);
void mock_dummy_error(void);

#ifdef __cplusplus
}
#endif

#endif /* __EQDMA_ACCESS_TEST_H__ */
