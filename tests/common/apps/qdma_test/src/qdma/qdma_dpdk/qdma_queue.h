#ifndef SRC_QDMA_QDMA_QUEUE_EXT_H_
#define SRC_QDMA_QDMA_QUEUE_EXT_H_

#include "qdma_queue_abs.h"
#include "xlnx_pci.h"

namespace qdma {

class instance;

class queue_ext: public queue {
public:

    struct config {
        uint16_t idx_rngsz = 1024; /* selects 2048 ring size */
        uint16_t idx_bufsz = 4096;
        uint16_t idx_tmr = 5;
        uint16_t idx_cntr = 64;
        uint8_t sw_desc_sz = 0;
        c2h_wrb_intr_trigmode trigmode = c2h_wrb_intr_trigmode::usr_tmr; 
        xnl_st_c2h_cmpt_desc_size cmptsz = XNL_ST_C2H_CMPT_DESC_SIZE_8B;
        bool desc_bypass = false;
        bool pfetch_bypass = false;
        bool prefetch = false;
        bool fetch_credit = true;
        bool wbk_en = true;
        bool wbk_acc_en = true;
        bool wbk_pend_chk = true;
        bool wrb_stat_desc_en = true;
        bool c2h_cmpl_intr_en = true;
        bool c2h_udd_en = false;
        bool c2h_ovf_chk_dis = false;
        uint16_t burst_size = 32;
    };

    queue_ext(instance& drv, uint32_t dev_id, uint32_t q_id, mode m, direction dir, const config& qcfg);

    ~queue_ext();

    queue_ext(const queue_ext& other) = delete;
    queue_ext& operator=(const queue_ext& other) = delete;
    queue_ext(queue_ext&& other);
    queue_ext& operator=(queue_ext&& other);

    virtual size_t write(void* buffer, size_t size, long device_offset = 0, bool throw_err = true);
    virtual size_t read(void* buffer, size_t size, long device_offset = 0, bool throw_err = true);
private:
    mode m_mode;

};




} // namespace qdma

#endif /* SRC_QDMA_QDMA_QUEUE_EXT_H_ */
