#ifndef SRC_QDMA_QDMA_INSTANCE_ABS_H_
#define SRC_QDMA_QDMA_INSTANCE_ABS_H_

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>
#include <stddef.h>

#include "qdma_device.h"
#include "qdma_queue.h"

namespace qdma {

// qdma driver instance
// implementes user-space control api
class instance {
public:

    enum class type {
        pf,
        vf
    };

    virtual std::vector<device> get_devices() = 0;

	virtual uint32_t get_last_id() = 0;

    virtual device::info dev_info(unsigned dev_id) = 0;


    virtual unsigned start_queue(unsigned dev_id, unsigned queue_id, queue::mode q_mode, queue_ext::direction q_dir,
                     const queue_ext::config& qcfg, bool throw_err = true) = 0;

    virtual unsigned stop_queue(unsigned dev_id, unsigned queue_id, queue::direction q_dir, bool throw_err = true) = 0;

    virtual unsigned add_queue(unsigned dev_id, unsigned q_id, unsigned num_q, queue::mode q_mode,
                       queue::direction q_dir, const queue_ext::config& qcfg, bool throw_err = true) = 0;


	type m_type = type::pf;
protected:
	uint32_t m_last_id;
};

inline std::vector<uint32_t> get_num_qs_per_pf(std::vector<device>& qdevs) {

    std::vector<uint32_t> num_qs_per_pf;
    num_qs_per_pf.reserve(qdevs.size());
    std::transform(qdevs.cbegin(), qdevs.cend(), std::back_inserter(num_qs_per_pf),
            [](const device& qdev) -> uint32_t {
                    return qdev.max_num_queues;
    });
    return num_qs_per_pf;
}

} // namespace qdma

#endif /* SRC_QDMA_QDMA_INSTANCE_ABS_H_ */
