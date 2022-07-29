#ifndef SRC_QDMA_QDMA_QUEUE_EXT_H_
#define SRC_QDMA_QDMA_QUEUE_EXT_H_

#include "qdma_queue_abs.h"
#include <xlnx_device_file.h>
#include <qdma/qdma_nl.h>

namespace qdma {

class instance_ext;

class queue_ext: public queue {
public:

    struct config {
    	uint16_t idx_rngsz = XNL_QDMA_RNGSZ_256_IDX;
        uint16_t idx_bufsz = 0;
        uint16_t idx_tmr = 9;
        uint16_t idx_cntr = 7;
        uint16_t sw_desc_sz = 0;
        c2h_wrb_intr_trigmode trigmode = c2h_wrb_intr_trigmode::every;
        xnl_st_c2h_cmpt_desc_size cmptsz = XNL_ST_C2H_CMPT_DESC_SIZE_8B;
        bool desc_bypass = false;
        bool pfetch_bypass = false;
        bool prefetch = false;
        bool fetch_credit = true;
        bool cmpl_status_en = true;
        bool cmpl_status_acc_en = true;
        bool cmpl_status_pend_chk = true;
        bool cmpl_status_desc_en = true;
        bool c2h_cmpl_intr_en = true;
        bool c2h_udd_en = false;
        bool c2h_ovf_chk_dis = false;
        bool en_mm_cmpt = false;
        uint16_t burst_size = 32;
    };

    queue_ext(instance_ext& drv, uint32_t dev_id, uint32_t q_id, mode m, direction dir, const config& qcfg);
    queue_ext(instance_ext& drv, uint32_t dev_id, uint32_t q_id, mode m, direction dir, const config& qcfg, bool no_add_start_queue);

    ~queue_ext();

    queue_ext(const queue_ext& other) = delete;
    queue_ext& operator=(const queue_ext& other) = delete;
    queue_ext(queue_ext&& other);
    queue_ext& operator=(queue_ext&& other);

    virtual size_t write(void* buffer, size_t size, long device_offset = 0, bool throw_err = true);
    virtual size_t read(void* buffer, size_t size, long device_offset = 0, bool throw_err = true);

    int aio_rw(io_context_t ctxt, int num_jobs, struct iocb **io_list);
    int get_handle();

    std::string get_dev_path();

    bool is_st_c2h() const;

private:
    instance_ext *m_drv;
    device_file m_cdev;
};

const char* to_string(queue_ext::mode m);

const char* to_string(queue_ext::direction d);

} // namespace qdma

#endif /* SRC_QDMA_QDMA_QUEUE_EXT_H_ */
