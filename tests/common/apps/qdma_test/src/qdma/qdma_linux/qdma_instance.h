#ifndef SRC_QDMA_QDMA_INSTANCE_EXT_H_
#define SRC_QDMA_QDMA_INSTANCE_EXT_H_


#include "qdma_instance_abs.h"

namespace qdma {

/** QDMA Global CSR array size */
#define QDMA_GLOBAL_CSR_ARRAY_SZ        16

struct global_csr_conf {
    /** Descriptor ring size ie. queue depth */
    unsigned int ring_sz[QDMA_GLOBAL_CSR_ARRAY_SZ];
    /** C2H timer count  list */
    unsigned int c2h_timer_cnt[QDMA_GLOBAL_CSR_ARRAY_SZ];
    /** C2H counter threshold list*/
    unsigned int c2h_cnt_th[QDMA_GLOBAL_CSR_ARRAY_SZ];
    /** C2H buffer size list */
    unsigned int c2h_buf_sz[QDMA_GLOBAL_CSR_ARRAY_SZ];
    /** wireback acculation enable/disable */
    unsigned int wb_acc = 0;
};

// qdma driver instance
// implementes user-space control api
class instance_ext: public instance {
public:

    instance_ext() = default;
    instance_ext(const instance_ext& other) = delete;
    instance_ext& operator=(const instance_ext& other) = delete;
    instance_ext(instance_ext&& other) = default;
    instance_ext& operator=(instance_ext&& other) = default;

    instance_ext(type t);



    std::string get_device_path(unsigned dev_id, unsigned q_id, queue_ext::mode mode);

    std::vector<std::string> get_num_devices();
    virtual std::vector<device> get_devices();
    virtual device::info dev_info(unsigned dev_id);
	virtual int get_dev_index(std::string dev_string);
	virtual uint32_t get_last_id();


    virtual unsigned add_queue(unsigned dev_id, unsigned q_id, unsigned num_q, queue::mode q_mode,
                       queue::direction q_dir, const queue_ext::config& qcfg, bool throw_err = true);
    virtual unsigned remove_queue(unsigned dev_id, unsigned queue_id, queue::direction q_dir, bool throw_err = true);

    virtual unsigned start_queue(unsigned dev_id, unsigned queue_id, queue::mode q_mode, queue::direction q_dir,
                     const queue_ext::config& qcfg, bool throw_err = true);

    virtual unsigned stop_queue(unsigned dev_id, unsigned queue_id, queue::direction q_dir, bool throw_err = true);

    virtual std::string dump_queue(unsigned dev_id, unsigned queue_id, queue::direction q_dir);
    virtual std::string dump_queue_desc(unsigned dev_id, unsigned queue_id, queue::direction q_dir, bool sw_desc, unsigned desc_start, unsigned desc_end);
    //virtual std::string dump_reg(unsigned dev_id);
    virtual std::string read_rx_packet(unsigned dev_id, unsigned queue_id);
    virtual uint32_t read_cmpt_data(unsigned dev_id, unsigned queue_id, queue::direction q_dir, char *cmpt_data);
    virtual void get_global_csr(unsigned dev_id, unsigned index, unsigned count, struct global_csr_conf &csr);

private:
#ifdef TEST_VF_ALONE
    xnl::socket qdma_socket { XNL_NAME_VF };
#else
    xnl::socket qdma_socket { XNL_NAME_PF };
#endif
};

} // namespace qdma

#endif /* SRC_QDMA_QDMA_INSTANCE_EXT_H_ */
