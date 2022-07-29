/*
 * qdma_queue.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: arayajig
 */
#include <algorithm>
#include <sstream>
#include "qdma_queue.h"
#include "qdma_instance.h"

namespace qdma {

queue_ext::queue_ext(instance_ext& drv, uint32_t dev_id, uint32_t q_id, queue::mode mode,
                     queue::direction dir, const queue_ext::config& qcfg)
    //: q_dev(drv.get_device_path(dev_id) + (mode == queue::mode::memory_mapped ? "\\queue_" : "\\st_") + std::to_string(q_id), GENERIC_WRITE | GENERIC_READ)
{
    //drv.validate_queue(dev_id, q_id);

    m_drv = &drv;
    m_dev_id = dev_id;
    m_qid = q_id;
    m_dir = dir;
    q_dev.open(drv.get_device_path(dev_id) + (mode == queue::mode::memory_mapped ? "\\queue_" : "\\st_") + std::to_string(q_id), GENERIC_WRITE | GENERIC_READ);

    auto idx = drv.get_mgmt_loc_from_dev_id(dev_id);
    if (idx < 0) {
        throw std::runtime_error("get_mgmt_loc_from_dev_id failed");
    }

    m_hwid = drv.get_device_qbase(idx) + q_id;

    no_add_start_q = false;
    auto res = drv.add_queue(dev_id, q_id, 1, mode, dir, qcfg);
    if (res == false) {
        throw std::runtime_error("drv.add_queue failed");
    }

    res = drv.start_queue(dev_id, q_id, mode, dir, qcfg);
    if (res == false) {
        drv.remove_queue(dev_id, q_id, dir);
        throw std::runtime_error("drv.start_queue failed");
    }
}

queue_ext::queue_ext(instance_ext& drv, uint32_t dev_id, uint32_t q_id, queue::mode mode,
    queue::direction dir, const queue_ext::config& qcfg, bool no_add_start_queue)
{
    //drv.validate_queue(dev_id, q_id);

    m_drv = &drv;
    m_dev_id = dev_id;
    m_qid = q_id;
    m_dir = dir;
    q_dev.open(drv.get_device_path(dev_id) + (mode == queue::mode::memory_mapped ? "\\queue_" : "\\st_") + std::to_string(q_id), GENERIC_WRITE | GENERIC_READ);

    auto idx = drv.get_mgmt_loc_from_dev_id(dev_id);
    if (idx < 0) {
        throw std::runtime_error("get_mgmt_loc_from_dev_id failed");
    }

    m_hwid = drv.get_device_qbase(idx) + q_id;

    no_add_start_q = no_add_start_queue;
    if (!no_add_start_queue) {
        auto res = drv.add_queue(dev_id, q_id, 1, mode, dir, qcfg);
        if (res == false) {
            throw std::runtime_error("drv.add_queue failed");
        }

        res = drv.start_queue(dev_id, q_id, mode, dir, qcfg);
        if (res == false) {
            drv.remove_queue(dev_id, q_id, dir);
            throw std::runtime_error("drv.start_queue failed");
        }
    }
}

queue_ext::~queue_ext() {
    q_dev.close();
    if (!no_add_start_q) {
        m_drv->stop_queue(m_dev_id, m_qid, m_dir);
        m_drv->remove_queue(m_dev_id, m_qid, m_dir);
    }
}

queue_ext::queue_ext(const queue_ext& other) {
    m_dev_id = other.m_dev_id;
    q_dev = other.q_dev;
    m_qid = other.m_qid;
    m_dir = other.m_dir;
    m_drv = other.m_drv;
}

queue_ext::queue_ext(queue_ext && rhs) {
    *this = std::move(rhs);
}

queue_ext& queue_ext::operator=(queue_ext&& rhs) {
    if (this != &rhs) {
        m_drv = rhs.m_drv;
        m_dev_id = rhs.m_dev_id;
        m_qid = rhs.m_qid;
        m_dir = rhs.m_dir;
        m_drv = nullptr;
    }

    return *this;
}

size_t queue_ext::write(void* buffer, const size_t size, const long device_offset, bool throw_err)
{
    q_dev.seek(device_offset);
    return q_dev.write(buffer, size, throw_err);
}

size_t queue_ext::read(void* buffer, const size_t size, const long device_offset, bool throw_err)
{
    q_dev.seek(device_offset);
    return q_dev.read(buffer, size, throw_err);
}

} /* namespace qdma */
