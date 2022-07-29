#ifndef SRC_QDMA_QDMA_QUEUE_H_
#define SRC_QDMA_QDMA_QUEUE_H_

#include <cstddef>
#include <cstdint>
#include <string>

#define EQDMA_C2H_PFCH_BYP_QID 0x1408
#define EQDMA_C2H_PFCH_BYP_TAG 0x140C

enum mode {
	ST_C2H_SW_DESC_SIZE_8B,
	ST_C2H_SW_DESC_SIZE_16B,
	ST_C2H_SW_DESC_SIZE_32B,
	ST_C2H_SW_DESC_SIZE_64B
};


namespace qdma {

class instance;

class queue {
public:

    enum class mode {
        memory_mapped,
        streaming,
    };

    enum class direction {
        host_to_card,
        card_to_host,
        both,
        cmpt
    };

    enum class c2h_wrb_intr_trigmode {
        disable,
        every,
        usr_cnt,
        usr,
        usr_tmr,
		cntr_tmr
    };

    virtual size_t write(void* buffer, size_t size, long device_offset = 0, bool throw_err = true) =0;
    virtual size_t read(void* buffer, size_t size, long device_offset = 0, bool throw_err = true) =0;


public:
    instance* m_drv;
    uint32_t m_dev_id = 0;
    uint32_t m_qid = 0;
    size_t m_buff_sz = 4096;
    size_t m_burst_size = 32;
    direction m_dir;
};


} // namespace qdma

#endif /* SRC_QDMA_QDMA_QUEUE_H_ */
