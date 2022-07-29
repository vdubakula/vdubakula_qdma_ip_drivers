#ifndef SRC_QDMA_QDMA_INSTANCE_EXT_H_
#define SRC_QDMA_QDMA_INSTANCE_EXT_H_

#include "qdma_instance_abs.h"

#define NUM_DESC_PER_RING 1024
#define MAX_NUM_QUEUES 2048
#define DEFAULT_NUM_QUEUES 64
#define NUM_RX_PKTS 32
#define MP_CACHE_SZ		512

#define MBUF_POOL_NAME_PORT_QUEUE_DIR "mp_%d_%d_%d" /* mempool_port_qid_direction */

#define MAX_WRITEBACK_SIZE (MAX_BUF_SIZE * 7)

/* User bar registers */
#define C2H_ST_QID_REG		0x0
#define C2H_ST_LEN_REG		0x4
#define C2H_CONTROL_REG		0x8
#define ST_LOOPBACK_EN		0x1
#define ST_C2H_START_VAL	0x2
#define ST_C2H_IMMEDIATE_DATA_EN	0x4
#define C2H_CONTROL_REG_MASK		0xF
#define H2C_CONTROL_REG		0xC
#define H2C_STATUS_REG		0x10
#define C2H_PACKET_COUNT_REG	0x20

namespace qdma {

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

		virtual std::vector<device> get_devices();

		virtual unsigned get_num_devices();

		virtual uint32_t get_last_id();

		virtual device::info dev_info(unsigned dev_id);

		virtual unsigned add_queue(unsigned dev_id, unsigned q_id, unsigned num_q, queue_ext::mode q_mode,
						   queue_ext::direction q_dir, const queue_ext::config& qcfg, bool throw_err);

		virtual unsigned start_queue(unsigned dev_id, unsigned queue_id, queue_ext::mode q_mode, queue_ext::direction q_dir,
						 const queue_ext::config& qcfg, bool throw_err);

		virtual unsigned stop_queue(unsigned dev_id, unsigned queue_id, queue_ext::direction q_dir, bool throw_err);


};

} // namespace qdma

#endif /* SRC_QDMA_QDMA_INSTANCE_EXT_H_ */
