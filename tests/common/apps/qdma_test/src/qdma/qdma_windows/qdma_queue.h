/*
 * qdma_queue.h
 *
 *  Created on: Nov 29, 2018
 *      Author: arayajig
 */

#ifndef SRC_QDMA_QDMA_QUEUE_EXT_H_
#define SRC_QDMA_QDMA_QUEUE_EXT_H_

#include "qdma_queue_abs.h"
#include <win_helper.h>
#include <xlnx_device_file.h>

namespace qdma {

class instance_ext;

class queue_ext: public queue {
public:

    struct config {
        uint16_t idx_rngsz = 0; /* selects 2049 ring size */
        uint16_t idx_bufsz = 0;
        uint16_t idx_tmr = 0;
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
    };

    queue_ext(instance_ext& drv, uint32_t dev_id, uint32_t q_id, mode m, direction dir, const config& qcfg);
    queue_ext(instance_ext& drv, uint32_t dev_id, uint32_t q_id, mode m, direction dir, const config& qcfg, bool no_add_start_queue);

    ~queue_ext();

    //queue_ext(const queue_ext& other) = delete;
    queue_ext(const queue_ext& other);
    queue_ext& operator=(const queue_ext& other) = delete;
    queue_ext(queue_ext&& other);
    queue_ext& operator=(queue_ext&& other);

    virtual size_t write(void* buffer, size_t size, long device_offset = 0, bool throw_err = true);
    virtual size_t read(void* buffer, size_t size, long device_offset = 0, bool throw_err = true);

    uint32_t m_hwid = 0;

private:
    instance_ext *m_drv;
    device_file q_dev;
    bool no_add_start_q = false;
    uint32_t m_qmax = 0;
};

} /* namespace qdma */

#endif /* SRC_QDMA_QDMA_QUEUE_EXT_H_ */
