/*
 * qdma_instance.h
 *
 *  Created on: Nov 29, 2018
 *      Author: arayajig
 */

#ifndef SRC_QDMA_QDMA_INSTANCE_EXT_H_
#define SRC_QDMA_QDMA_INSTANCE_EXT_H_


#include "qdma_instance_abs.h"

namespace qdma {

/* QDMA Global CSR array size */
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
    unsigned int wb_acc;
};

struct device_details {
    UINT8 bus_no;
    UINT8 dev_no;
    UINT8 fun_no;
    std::string device_name;
    std::string device_path;
};

/* qdma driver instance */
class instance_ext: public instance {
private:
    size_t n_devices = 0;
    std::vector<device_file> mgmt;
    std::vector<int> mgmt_pf;
    unsigned int device_type;
    unsigned int versal_ip_type;
    std::vector<unsigned int> qbase;
    std::vector<unsigned int> qmax;

public:
    std::vector<device_details> dev_details;

    instance_ext() = default;
    instance_ext(const instance_ext& other) = delete;
    instance_ext& operator=(const instance_ext& other) = delete;
    instance_ext(instance_ext&& other) = default;
    instance_ext& operator=(instance_ext&& other) = default;

    instance_ext(type t);

    //void validate_queue(uint32_t dev_id, unsigned &qid);
    unsigned int get_device_qbase(uint32_t idx) {
        return qbase.at(idx);
    };
    int get_mgmt_loc_from_dev_id(int dev_id);
    std::vector<std::string> get_device_paths(GUID guid);
    std::vector<device_details> get_device_details(GUID guid);

    std::string get_device_path(UINT32 dev_id);
    virtual int instance_ext::get_dev_index(std::string dev_string);
    virtual std::vector<device> get_devices();
    virtual device::info dev_info(uint32_t dev_id);
    virtual uint32_t get_last_id();
    virtual unsigned add_queue(unsigned dev_id, unsigned q_id, unsigned num_q, queue::mode q_mode,
                       queue::direction q_dir, const queue_ext::config& qcfg, bool throw_err = true);
    virtual unsigned remove_queue(unsigned dev_id, unsigned queue_id, queue::direction q_dir, bool throw_err = true);
    virtual unsigned start_queue(unsigned dev_id, unsigned queue_id, queue::mode q_mode, queue::direction q_dir,
                     const queue_ext::config& qcfg, bool throw_err = true);
    virtual unsigned stop_queue(unsigned dev_id, unsigned queue_id, queue::direction q_dir, bool throw_err = true);
    virtual void get_global_csr(unsigned dev_id, struct global_csr_conf &csr);
    virtual std::string read_rx_packet(unsigned dev_id, unsigned queue_id);
    virtual std::string dump_queue_desc(unsigned dev_id, unsigned queue_id, queue::direction q_dir, bool sw_desc, unsigned desc_start, unsigned desc_end);
    virtual uint32_t read_cmpt_data(unsigned dev_id, unsigned queue_id, queue::direction q_dir, char *cmpt_data);
};

} /* namespace qdma */

#endif /* SRC_QDMA_QDMA_INSTANCE_EXT_H_ */
