#include <gtest/gtest.h>
#include <xlnx_gtest_ext.h>

#include "test_env.h"

// ===============================Test framework helpers ==========================================


class qdma_nl_test: public testing::TestWithParam<qdma::instance_ext::type> {};

extern test_env env; // in main.cpp

void dev_list(xnl::socket& qdma_socket)
{
    auto cmd = qdma_socket.prepare_msg(XNL_CMD_DEV_LIST);
    qdma_socket.send_msg(cmd);
    auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
    char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

    EXPECT_FALSE(qdma_socket.has_error());
    EXPECT_NE(resp_str, nullptr);
}

void dev_info(xnl::socket& qdma_socket, qdma::instance_ext::type dev_type)
{
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

    for(uint32_t func = 0; func < devlist.size(); func++) {
        if (!devlist[func].max_num_queues)
            continue;

        auto cmd = qdma_socket.prepare_msg(XNL_CMD_DEV_INFO);
		cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[func].dev_id);
        qdma_socket.send_msg(cmd);
        auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);

        EXPECT_FALSE(qdma_socket.has_error());
        EXPECT_EQ(devlist[func].m_id.bus, resp.get_attrib<uint32_t>(XNL_ATTR_PCI_BUS));
        EXPECT_EQ(devlist[func].m_id.dev, resp.get_attrib<uint32_t>(XNL_ATTR_PCI_DEV));
        EXPECT_EQ(devlist[func].m_id.fn, resp.get_attrib<uint32_t>(XNL_ATTR_PCI_FUNC));
        EXPECT_GE(resp.get_attrib<uint32_t>(XNL_ATTR_DEV_CFG_BAR), 0);
        EXPECT_LE(resp.get_attrib<uint32_t>(XNL_ATTR_DEV_CFG_BAR), 6);
        EXPECT_GE(resp.get_attrib<uint32_t>(XNL_ATTR_DEV_USR_BAR), 0);
        EXPECT_LE(resp.get_attrib<uint32_t>(XNL_ATTR_DEV_USR_BAR), 6);
    }

    // Failure case 1: missing XNL_ATTR_DEV_IDX attribute
    {
        auto cmd = qdma_socket.prepare_msg(XNL_CMD_DEV_INFO);
        qdma_socket.send_msg(cmd);
        auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
        char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

        EXPECT_TRUE(qdma_socket.has_error());
        EXPECT_EQ(-EINVAL, qdma_socket.get_error());
        EXPECT_NE(resp_str, nullptr); // TODO check error message
    }

    // Failure case 2: XNL_ATTR_DEV_IDX incorrect value
    {
        auto cmd = qdma_socket.prepare_msg(XNL_CMD_DEV_INFO);
        if (dev_type == qdma::instance_ext::type::pf)
        	cmd.add_attribute(XNL_ATTR_DEV_IDX, env.last_pf + 1);
        else
        	cmd.add_attribute(XNL_ATTR_DEV_IDX, env.last_vf + 1);
        qdma_socket.send_msg(cmd);
        auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
        char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

        EXPECT_TRUE(qdma_socket.has_error());
        EXPECT_EQ(-EINVAL, qdma_socket.get_error());
        EXPECT_NE(resp_str, nullptr); // TODO check error message
    }
}


void q_add_del(xnl::socket& qdma_socket, qdma::instance_ext::type dev_type)
{
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
    uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C;
	uint32_t first_idx = 0;
	bool found_first_valid = false;

    for(uint32_t func = 0; func < devlist.size(); func++) {
        if (!devlist[func].max_num_queues)
            continue;
		found_first_valid = true;
		first_idx = func;
		break;
	}

	//combination of all PF,VF qs 0 without any VF
	if (found_first_valid) {
		// successful case - add 1 queue
		{
			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);
		}

		// successful case - delete 1 queue
		{
			uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C;

			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DEL);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);
		}

		// successful case - add available queue pairs
		{
			uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;

			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[first_idx].max_num_queues);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);
		}

		// successful case - delete avialable queue pairs
		{
			uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;

			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DEL);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[first_idx].max_num_queues);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);
		}

		// Failure case 1: missing XNL_ATTR_DEV_IDX attribute
		{
			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);
			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_TRUE(qdma_socket.has_error());
			EXPECT_EQ(-EINVAL, qdma_socket.get_error());
			EXPECT_NE(resp_str, nullptr); // TODO check error message
		}

		// Failure case 2: XNL_ATTR_DEV_IDX incorrect value
		{
			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
	        if (dev_type == qdma::instance_ext::type::pf) {
	        	cmd.add_attribute(XNL_ATTR_DEV_IDX, env.last_pf + 1);
	        }
	        else {
	        	cmd.add_attribute(XNL_ATTR_DEV_IDX, env.last_vf + 1);
	        }
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);
			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_TRUE(qdma_socket.has_error());
			EXPECT_EQ(-EINVAL, qdma_socket.get_error());
			EXPECT_NE(resp_str, nullptr); // TODO check error message
		}

		// Failure case 3: missing XNL_ATTR_QIDX attribute
		{
			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);

			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);
			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_TRUE(qdma_socket.has_error());
			EXPECT_EQ(-EINVAL, qdma_socket.get_error());
			EXPECT_NE(resp_str, nullptr); // TODO check error message
		}

		// Failure case 4: XNL_ATTR_QIDX incorrect value
		{
			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, devlist[first_idx].max_num_queues);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);
			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_TRUE(qdma_socket.has_error());
			EXPECT_EQ(-EINVAL, qdma_socket.get_error());
			EXPECT_NE(resp_str, nullptr); // TODO check error message
		}
	}
}

void q_list(xnl::socket& qdma_socket, qdma::instance_ext::type dev_type)
{
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
    // successful case - empty
    for(uint32_t func = 0; func < devlist.size(); func++) {
        uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;
        if (!devlist[func].max_num_queues)
            continue;

        auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_LIST);
        cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[func].dev_id);
        cmd.add_attribute(XNL_ATTR_QIDX, 0u);
        cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[func].max_num_queues);
        cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
        qdma_socket.send_msg(cmd);
        auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
        char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

        EXPECT_FALSE(qdma_socket.has_error());
        EXPECT_NE(resp_str, nullptr);
    }
    // successful case - add all queue pairs
    for(uint32_t func = 0; func < devlist.size(); func++) {
        uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;

        if (!devlist[func].max_num_queues)
            continue;

        auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
        cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[func].dev_id);
        cmd.add_attribute(XNL_ATTR_QIDX, 0u);
        cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[func].max_num_queues);
        cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
        qdma_socket.send_msg(cmd);

        auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
        char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

        EXPECT_FALSE(qdma_socket.has_error());
        EXPECT_NE(resp_str, nullptr);
    }

    // successful case - full
    for(uint32_t func = 0; func < devlist.size(); func++) {
        uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;
        if (!devlist[func].max_num_queues)
            continue;
        auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_LIST);
        cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[func].dev_id);
        cmd.add_attribute(XNL_ATTR_QIDX, 0u);
        cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[func].max_num_queues);
        cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
        qdma_socket.send_msg(cmd);
        auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
        char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

        EXPECT_FALSE(qdma_socket.has_error());
        EXPECT_NE(resp_str, nullptr);
    }
    for(uint32_t func = 0; func < devlist.size(); func++) {
        uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;
        if (!devlist[func].max_num_queues)
            continue;
        auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_LIST);
        cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[func].dev_id);
        cmd.add_attribute(XNL_ATTR_QIDX, 0u);
        cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[func].max_num_queues);
        cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
        qdma_socket.send_msg(cmd);
        auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
        char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

        EXPECT_FALSE(qdma_socket.has_error());
        EXPECT_NE(resp_str, nullptr);
    }
    // successful case - delete all queue pairs
    for(uint32_t func = 0; func < devlist.size(); func++) {
        uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;
        if (!devlist[func].max_num_queues)
            continue;

        auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DEL);
        cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[func].dev_id);
        cmd.add_attribute(XNL_ATTR_QIDX, 0u);
        cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[func].max_num_queues);
        cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
        qdma_socket.send_msg(cmd);

        auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
        char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

        EXPECT_FALSE(qdma_socket.has_error());
        EXPECT_NE(resp_str, nullptr);
    }

    // Failure case 1: missing XNL_ATTR_DEV_IDX attribute
    {
        auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_LIST);
        cmd.add_attribute(XNL_ATTR_QIDX, 0u);
        cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
        qdma_socket.send_msg(cmd);
        auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
        char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

        EXPECT_TRUE(qdma_socket.has_error());
        EXPECT_EQ(-EINVAL, qdma_socket.get_error());
        EXPECT_NE(resp_str, nullptr); // TODO check error message
    }

    // Failure case 2: XNL_ATTR_DEV_IDX incorrect value
    {
        auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_LIST);
        if (dev_type == qdma::instance_ext::type::pf) {
            cmd.add_attribute(XNL_ATTR_DEV_IDX, env.last_pf + 1);
        }
        else {
            cmd.add_attribute(XNL_ATTR_DEV_IDX, env.last_vf + 1);
        }
        cmd.add_attribute(XNL_ATTR_QIDX, 0u);
        cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
        qdma_socket.send_msg(cmd);
        auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
        char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

        EXPECT_TRUE(qdma_socket.has_error());
        EXPECT_EQ(-EINVAL, qdma_socket.get_error());
        EXPECT_NE(resp_str, nullptr); // TODO check error message
    }
}

void q_start_stop(xnl::socket& qdma_socket, qdma::instance_ext::type dev_type)
{
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t first_idx = 0;
	bool found_first_valid = false;

    for(uint32_t func = 0; func < devlist.size(); func++) {
        if (!devlist[func].max_num_queues)
            continue;
		found_first_valid = true;
		first_idx = func;
		break;
	}

	//combination of all PF,VF qs 0 without any VF
	if (found_first_valid) {
		// successful case - start 1 queue
		{
		    uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C;
		    uint32_t q_flags_start = XNL_F_QDIR_H2C;

			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_START);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags_start);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);
		}

		// successful case - stop 1 queue
		{
			uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C;
			uint32_t q_flags_stop = XNL_F_QDIR_H2C;

			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_STOP);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags_stop);
			qdma_socket.send_msg(cmd);

			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DEL);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);
		}

		// successful case - start available queue pairs
		{
			uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;
			uint32_t q_flags_start = XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;

			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[first_idx].max_num_queues);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_START);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[first_idx].max_num_queues);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags_start);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);
		}

		// successful case - stop avialable queue pairs
		{
			uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;
			uint32_t q_flags_stop = XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;

			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_STOP);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[first_idx].max_num_queues);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags_stop);
			qdma_socket.send_msg(cmd);

			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DEL);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[first_idx].max_num_queues);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);
		}
	}
}

void q_dump(xnl::socket& qdma_socket, qdma::instance_ext::type dev_type)
{
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t first_idx = 0;
	bool found_first_valid = false;

    for(uint32_t func = 0; func < devlist.size(); func++) {
        if (!devlist[func].max_num_queues)
            continue;
		found_first_valid = true;
		first_idx = func;
		break;
	}

	//combination of all PF,VF qs 0 without any VF
	if (found_first_valid) {
		// successful case - dump 1 queue
		{
		    uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C;
		    uint32_t q_flags_dump = XNL_F_QDIR_H2C;

			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DUMP);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags_dump);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DEL);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);
		}

		// successful case - dump available queue pairs
		{
			uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;
			uint32_t q_flags_dump = XNL_F_QDIR_H2C | XNL_F_QDIR_C2H;

			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[first_idx].max_num_queues);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DUMP);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[first_idx].max_num_queues);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags_dump);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DEL);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, devlist[first_idx].max_num_queues);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);
		}
	}
}

void q_dump_desc(xnl::socket& qdma_socket, qdma::instance_ext::type dev_type)
{
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t first_idx = 0;
	unsigned desc_start = 0, desc_end = 1;
	bool found_first_valid = false;

    for(uint32_t func = 0; func < devlist.size(); func++) {
        if (!devlist[func].max_num_queues)
            continue;
		found_first_valid = true;
		first_idx = func;
		break;
	}

	//combination of all PF,VF qs 0 without any VF
	if (found_first_valid) {
		// successful case - dump 1 queue
		{
		    uint32_t q_flags = XNL_F_QMODE_MM | XNL_F_QDIR_H2C;
		    uint32_t q_flags_dump = XNL_F_QDIR_H2C;

			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_START);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags_dump);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DESC);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags_dump);
			cmd.add_attribute(XNL_ATTR_RANGE_START, desc_start);
			cmd.add_attribute(XNL_ATTR_RANGE_END, desc_end);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_STOP);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags_dump);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DEL);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);
		}
	}
}

void q_dump_cmpt(xnl::socket& qdma_socket, qdma::instance_ext::type dev_type)
{
    std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t first_idx = 0;
	unsigned desc_start = 0, desc_end = 1;
	bool found_first_valid = false;

    for(uint32_t func = 0; func < devlist.size(); func++) {
        if (!devlist[func].max_num_queues)
            continue;
		found_first_valid = true;
		first_idx = func;
		break;
	}

	//combination of all PF,VF qs 0 without any VF
	if (found_first_valid) {
		// successful case - dump 1 queue
		{
		    uint32_t q_flags = XNL_F_QMODE_ST | XNL_F_QDIR_C2H;
		    uint32_t q_flags_dump = XNL_F_QDIR_C2H;
		    uint32_t default_rng_idx = 0x09;
		    uint32_t q_start_flags = XNL_F_CMPL_STATUS_EN | XNL_F_CMPL_STATUS_PEND_CHK |
		    		 XNL_F_CMPL_STATUS_DESC_EN | XNL_F_CMPL_STATUS_ACC_EN |
					 XNL_F_FETCH_CREDIT | XNL_F_QDIR_C2H;

			auto cmd = qdma_socket.prepare_msg(XNL_CMD_Q_ADD);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			auto resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			char* resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_START);
			cmd.add_attribute(XNL_ATTR_QRNGSZ_IDX, default_rng_idx);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_start_flags);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_CMPT);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags_dump);
			cmd.add_attribute(XNL_ATTR_RANGE_START, desc_start);
			cmd.add_attribute(XNL_ATTR_RANGE_END, desc_end);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_STOP);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags_dump);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);

			cmd = qdma_socket.prepare_msg(XNL_CMD_Q_DEL);
			cmd.add_attribute(XNL_ATTR_DEV_IDX, devlist[first_idx].dev_id);
			cmd.add_attribute(XNL_ATTR_QIDX, 0u);
			cmd.add_attribute(XNL_ATTR_NUM_Q, 1);
			cmd.add_attribute(XNL_ATTR_QFLAG, q_flags);
			qdma_socket.send_msg(cmd);

			resp = qdma_socket.receive_msg(XNL_ATTR_MAX);
			resp_str = resp.get_attrib<char*>(XNL_ATTR_GENMSG);

			EXPECT_FALSE(qdma_socket.has_error());
			EXPECT_NE(resp_str, nullptr);
		}
	}
}

void nl_connect(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
    if (dev_type == qdma::instance_ext::type::pf)
    	EXPECT_NO_THROW(xnl::socket qdma_socket { XNL_NAME_PF };)
		<< "Failed to open a netlink socket to qdma driver";
    else
    	EXPECT_NO_THROW(xnl::socket qdma_socket { XNL_NAME_VF };)
		<< "Failed to open a netlink socket to qdma driver";
}

void nl_dev_list(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
    if (dev_type == qdma::instance_ext::type::pf)
    {
        xnl::socket qdma_socket { XNL_NAME_PF };
        dev_list(qdma_socket);

    }
    else
    {
        xnl::socket qdma_socket { XNL_NAME_VF };
        dev_list(qdma_socket);
    }
}

void nl_dev_info(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
    if (dev_type == qdma::instance_ext::type::pf)
    {
        xnl::socket qdma_socket { XNL_NAME_PF };
        dev_info(qdma_socket, dev_type);

    }
    else
    {
        xnl::socket qdma_socket { XNL_NAME_VF };
        dev_info(qdma_socket, dev_type);
    }
}

void nl_q_add_del(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
    if (dev_type == qdma::instance_ext::type::pf)
    {
        xnl::socket qdma_socket { XNL_NAME_PF };
        q_add_del(qdma_socket, dev_type);

    }
    else
    {
        xnl::socket qdma_socket { XNL_NAME_VF };
        q_add_del(qdma_socket, dev_type);
    }
}

void nl_q_list(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
    if (dev_type == qdma::instance_ext::type::pf)
    {
        xnl::socket qdma_socket { XNL_NAME_PF };
        q_list(qdma_socket, dev_type);

    }
    else
    {
        xnl::socket qdma_socket { XNL_NAME_VF };
        q_list(qdma_socket, dev_type);
    }
}

void nl_q_start_stop(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
    if (dev_type == qdma::instance_ext::type::pf)
    {
        xnl::socket qdma_socket { XNL_NAME_PF };
        q_start_stop(qdma_socket, dev_type);

    }
    else
    {
        xnl::socket qdma_socket { XNL_NAME_VF };
        q_start_stop(qdma_socket, dev_type);
    }
}

void nl_q_dump(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
    if (dev_type == qdma::instance_ext::type::pf)
    {
        xnl::socket qdma_socket { XNL_NAME_PF };
        q_dump(qdma_socket, dev_type);

    }
    else
    {
        xnl::socket qdma_socket { XNL_NAME_VF };
        q_dump(qdma_socket, dev_type);
    }
}

void nl_q_dump_desc(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
    if (dev_type == qdma::instance_ext::type::pf)
    {
        xnl::socket qdma_socket { XNL_NAME_PF };
        q_dump_desc(qdma_socket, dev_type);

    }
    else
    {
        xnl::socket qdma_socket { XNL_NAME_VF };
        q_dump_desc(qdma_socket, dev_type);
    }
}

void nl_q_dump_cmpt(qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
    if (dev_type == qdma::instance_ext::type::pf)
    {
        xnl::socket qdma_socket { XNL_NAME_PF };
        q_dump_cmpt(qdma_socket, dev_type);

    }
    else
    {
        xnl::socket qdma_socket { XNL_NAME_VF };
        q_dump_cmpt(qdma_socket, dev_type);
    }
}

TEST_P(qdma_nl_test, NL001_connect)
{
    nl_connect(GetParam());
}

TEST_P(qdma_nl_test, NL002_dev_list)
{
	nl_dev_list(GetParam());
}

TEST_P(qdma_nl_test, NL003_dev_info)
{
	nl_dev_info(GetParam());
}

TEST_P(qdma_nl_test, NL004_q_add_del)
{
	nl_q_add_del(GetParam());
}

TEST_P(qdma_nl_test, NL005_q_list)
{
	nl_q_list(GetParam());
}

TEST_P(qdma_nl_test, NL006_q_start_stop)
{
	nl_q_start_stop(GetParam());
}

TEST_P(qdma_nl_test, NL007_q_dump)
{
	nl_q_dump(GetParam());
}

TEST_P(qdma_nl_test, NL008_q_dump_desc)
{
	nl_q_dump_desc(GetParam());
}

TEST_P(qdma_nl_test, NL009_q_dump_wrb)
{
	nl_q_dump_cmpt(GetParam());
}

INSTANTIATE_TEST_CASE_P(NL_TESTS,
            qdma_nl_test,
            ::testing::Values(qdma::instance_ext::type::pf));

INSTANTIATE_TEST_CASE_P(VF_NL_TESTS,
		    qdma_nl_test,
		    ::testing::Values(qdma::instance_ext::type::vf));
