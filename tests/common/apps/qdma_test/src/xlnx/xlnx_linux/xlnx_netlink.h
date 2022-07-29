/*
 * xnl.h
 *
 *  Created on: Jan 29, 2018
 *      Author: alexande
 */

#ifndef QDMA_TEST_XLNX_XNL_H_
#define QDMA_TEST_XLNX_XNL_H_

#include <iostream>
#include <mutex>
#include <semaphore.h>

#include <netlink/netlink.h>
#include <netlink/socket.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/ctrl.h>
#include <netlink/genl/family.h>

#define NETLINK_SOCKET_BUFFER_LENGTH (512 * 1024)

/// xilinx netlink c++
namespace xnl {

class message {
public:

    message() {
        m_handle = nlmsg_alloc();
        if (not m_handle) {
            throw std::runtime_error("nlmsg_alloc failed!");
        }
    }

    message(nl_msg* msg) :
            m_handle(msg) {
        nlmsg_get(msg); // take ownership of nl message handle
    }

    ~message() {
        if (m_handle) {
            nlmsg_free(m_handle);
        }
    }

    message(const message& other) = delete;
    message& operator=(const message& other) = delete;

    message(message&& other) {
        if (this != &other) {
            *this = std::move(other);
        }
    }

    message& operator=(message&& other) {
        if (this != &other) {
            //pilfer
            m_handle = other.m_handle;

            //reset
            other.m_handle = nullptr;
        }
        return *this;
    }

    nl_msg* get() const noexcept {
        return m_handle;
    }

    void parse(int max_attribs) {
        m_attribs.resize(max_attribs + 1);
        if (genlmsg_parse(nlmsg_hdr(m_handle), 0, m_attribs.data(),
                max_attribs, nullptr) != NL_OK) {
            throw std::runtime_error("nlmsg_parse failed!");
        }
    }

    void add_attribute(size_t id, uint32_t value) {
        nla_put_u32(m_handle, id, value);
    }

    void add_attribute(size_t id, const char* value) {
        nla_put_string(m_handle, id, value);
    }

    template<typename T>
    T get_attrib(size_t id) {
        return {};
    }

private:
    nl_msg* m_handle = nullptr;
    std::vector<nlattr*> m_attribs;
};

template<> inline
uint32_t message::get_attrib<uint32_t>(size_t id) {
    if (m_attribs.empty() || id >= m_attribs.size()) {
        throw std::runtime_error("no uint32_t attribute to get");
    }
    return nla_get_u32(m_attribs[id]);
}

template<> inline
int32_t message::get_attrib<int32_t>(size_t id) {
    if (m_attribs.empty() || id >= m_attribs.size()) {
        throw std::runtime_error("no uint32_t attribute to get");
    }
    return nla_get_u32(m_attribs[id]);
}

template<> inline
char* message::get_attrib<char*>(size_t id) {
    if (m_attribs.empty() || id >= m_attribs.size()) {
        throw std::runtime_error("no char* attribute to get");
    }
    return nla_get_string(m_attribs[id]);
}

template<> inline
void* message::get_attrib<void*>(size_t id) {
    if (m_attribs.empty() || id >= m_attribs.size()) {
        throw std::runtime_error("no void* attribute to get");
    }
    return nla_data(m_attribs[id]);
}

class socket {
public:

    explicit socket(const char* family_name) {
    	sem_init(&sem_m_msgs, 0, 0);
        m_msgs.reserve(2048);

        m_sock = nl_socket_alloc();
        genl_connect(m_sock);
		if (nl_socket_set_buffer_size(m_sock, NETLINK_SOCKET_BUFFER_LENGTH,
									  NETLINK_SOCKET_BUFFER_LENGTH) < 0)
			throw std::runtime_error("Error in configuring netlink socket size");
        m_family_id = genl_ctrl_resolve(m_sock, family_name);
        if (m_family_id < 0) {
            throw std::runtime_error("Could not find netlink family: " + std::string(family_name));
        }

        nl_socket_disable_seq_check(m_sock);

        nl_socket_modify_cb(m_sock, NL_CB_VALID, NL_CB_CUSTOM, receive_msg_cb, this);
        nl_socket_modify_err_cb(m_sock, NL_CB_CUSTOM, receive_msg_err_cb, this);
    }

    ~socket() {
        if (m_sock) {
            nl_socket_free(m_sock);
        }
    }

    socket(const socket& other) = delete;
    socket& operator=(const socket& other) = delete;

    socket(socket&& other) {
        if (this != &other) {
            *this = std::move(other);
        }
    }

    socket& operator=(socket&& other) {
        if (this != &other) {
            //pilfer
            m_sock = other.m_sock;
            m_family_id = other.m_family_id;

            nl_socket_modify_cb(m_sock, NL_CB_VALID, NL_CB_CUSTOM, receive_msg_cb, this);
            nl_socket_modify_err_cb(m_sock, NL_CB_CUSTOM, receive_msg_err_cb, this);
        	sem_init(&sem_m_msgs, 0, 0);

            //reset
            other.m_sock = nullptr;
        }
        return *this;
    }

    message prepare_msg(int cmd) {

        message msg; // alloc msg

        // set msg header
        genlmsg_put(msg.get(), NL_AUTO_PORT, NL_AUTO_SEQ, m_family_id, 0, 0, cmd, 0);
        return msg;
    }

    void send_msg(message& msg) {
        //std::cout << "sending nl message:\n";
        //nl_msg_dump(msg.get(), stdout);
        std::lock_guard<std::mutex> lock(send_mutex);

        int ret = nl_send_auto(m_sock, msg.get());
        if (ret < 0) {
            throw std::runtime_error("nl_send_auto failed!");
        }
        if (nl_wait_for_ack(m_sock) < 0) {
            throw std::runtime_error("nl_wait_for_ack failed!");
        }
    }

    message receive_msg(int max_attribs = 32) {
        if (nl_recvmsgs_default(m_sock) < 0) {
            throw std::runtime_error("nl_recvmsgs_default failed!");
        }
        sem_wait(&sem_m_msgs);
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_msgs.empty()) {
            throw std::runtime_error("no return message received after sending command!");
        }
        auto msg = std::move(m_msgs.back());
        m_msgs.pop_back();
        msg.parse(max_attribs);
        return msg;
    }

    void set_error(int err) {
        last_err = err;
    }

    bool has_error() {
        return last_err != 0;
    }

    int get_error(bool clear = true) {
        const int err = last_err;
        if (clear)
            last_err = 0;
        return err;
    }

    static int receive_msg_cb(struct nl_msg *msg, void *user_ptr) {
        socket* this_ = reinterpret_cast<socket*>(user_ptr);
        if (not this_) {
            std::cout << "user_ptr=null! expected valid xnl::socket object!\n";
            return NL_STOP;
        }

        std::lock_guard<std::mutex> lock(this_->m_mutex);
        this_->m_msgs.emplace_back(msg);
        //std::cout << "received nl message:\n";
        //nl_msg_dump(msg, stdout);
        sem_post(&this_->sem_m_msgs);

        return NL_OK;
    }

    static int receive_msg_err_cb(struct sockaddr_nl *nla,
        struct nlmsgerr *nlerr, void *user_ptr) {
        socket* this_ = reinterpret_cast<socket*>(user_ptr);
        if (not this_) {
            std::cout << "user_ptr=null! expected valid xnl::socket object!\n";
            return NL_STOP;
        }

        this_->set_error(nlerr->error);
        sem_post(&this_->sem_m_msgs);
        return 0;
    }

private:
    nl_sock* m_sock = nullptr;
    int m_family_id = 0;
    std::vector<message> m_msgs;
    std::mutex m_mutex;
    std::mutex send_mutex;

    int last_err = 0;
    sem_t sem_m_msgs;
};

} // namespace xnl

#endif /* QDMA_TEST_XLNX_XNL_H_ */
