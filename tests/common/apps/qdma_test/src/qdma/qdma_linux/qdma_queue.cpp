#include <algorithm>
#include <sstream>
#include "qdma_queue.h"
#include "qdma_instance.h"

namespace qdma {

queue_ext::queue_ext(instance_ext& drv, uint32_t dev_id, uint32_t q_id, queue::mode mode,
             queue::direction dir, const queue_ext::config& qcfg) {

    m_drv = &drv;
    m_dev_id = dev_id;
    m_qid = q_id;
    m_dir = dir;

    m_drv->add_queue(m_dev_id, m_qid, 1, mode, dir, qcfg);

    if (mode == queue::mode::streaming) {
        if ((dir == queue::direction::both) || (dir == queue::direction::card_to_host))
            m_drv->start_queue(m_dev_id, m_qid, mode, queue::direction::card_to_host, qcfg);

        if ((dir == queue::direction::both) || (dir == queue::direction::host_to_card)) {
            queue_ext::config temp_qcfg = qcfg;
            temp_qcfg.fetch_credit = false;
            m_drv->start_queue(m_dev_id, m_qid, mode, queue::direction::host_to_card, temp_qcfg);
        }
    } else
        m_drv->start_queue(m_dev_id, m_qid, mode, dir, qcfg);

    if (dir != qdma::queue_ext::direction::cmpt) {
		m_cdev.dev_path = m_drv->get_device_path(m_dev_id, m_qid, mode);
	//    std::cout << "Opening " << m_cdev.dev_path << std::endl;
		m_cdev.open(m_cdev.dev_path, device_file::access::rw);
    }
}

queue_ext::queue_ext(instance_ext& drv, uint32_t dev_id, uint32_t q_id, queue::mode mode,
             queue::direction dir, const queue_ext::config& qcfg, bool no_add_start_queue) {

    m_drv = &drv;
    m_dev_id = dev_id;
    m_qid = q_id;
    m_dir = dir;
	if(!no_add_start_queue) {
		m_drv->add_queue(m_dev_id, m_qid, 1, mode, dir, qcfg);

	    if (mode == queue::mode::streaming) {
	        if ((dir == queue::direction::both) || (dir == queue::direction::card_to_host))
	            m_drv->start_queue(m_dev_id, m_qid, mode, queue::direction::card_to_host, qcfg);

	        if ((dir == queue::direction::both) || (dir == queue::direction::host_to_card)) {
	            queue_ext::config temp_qcfg = qcfg;
	            temp_qcfg.fetch_credit = false;
	            m_drv->start_queue(m_dev_id, m_qid, mode, queue::direction::host_to_card, temp_qcfg);
	        }
	    } else
	        m_drv->start_queue(m_dev_id, m_qid, mode, dir, qcfg);
	}
	m_cdev.dev_path = m_drv->get_device_path(m_dev_id, m_qid, mode);
//    std::cout << "Opening " << m_cdev.dev_path << std::endl;
    m_cdev.open(m_cdev.dev_path, device_file::access::rw);
}


queue_ext::~queue_ext() {
    if (m_drv) {
//	std::cout << "closing " << m_cdev.dev_path << std::endl;
    	if (m_dir != qdma::queue_ext::direction::cmpt) {
    		m_cdev.close();
    	}
        m_drv->stop_queue(m_dev_id, m_qid, m_dir);
        m_drv->remove_queue(m_dev_id, m_qid, m_dir);
    }
}

queue_ext::queue_ext(queue_ext && rhs) {
    *this = std::move(rhs);
}

queue_ext& queue_ext::operator=(queue_ext&& rhs) {
    if (this != &rhs) {

        //pilfer
        m_drv = rhs.m_drv;
        m_dev_id = rhs.m_dev_id;
        m_qid = rhs.m_qid;
        m_dir = rhs.m_dir;
        m_cdev = std::move(rhs.m_cdev);

        //reset
        m_drv = nullptr;
    }
    return *this;
}

size_t queue_ext::write(void* buffer, const size_t size, const long device_offset, bool throw_err) {
    m_cdev.seek(device_offset);
//    std::cout << "Writing to " << m_cdev.dev_path << std::endl;
    return m_cdev.write(buffer, size);
}

size_t queue_ext::read(void* buffer, const size_t size, const long device_offset, bool throw_err) {
    m_cdev.seek(device_offset);
//    std::cout << "Reading from " << m_cdev.dev_path << std::endl;
    return m_cdev.read(buffer, size);
}

int queue_ext::aio_rw(io_context_t ctxt, int num_jobs, struct iocb **io_list) {
    return m_cdev.aio_rw(ctxt, num_jobs, io_list);
}

int queue_ext::get_handle(void) {
    return static_cast<int>(m_cdev.get_handle());
}

const char* to_string(queue::mode m) {
    return m == queue_ext::mode::memory_mapped ? "MM" : "ST";
}

const char* to_string(queue::direction d) {
    return d == queue::direction::host_to_card ? "H2C" : "C2H";
}


} // namespace qdma
