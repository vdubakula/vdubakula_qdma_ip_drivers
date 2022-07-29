#include <gtest/gtest.h>

#include "test_env.h"
#include "example_design_ctrl.h"
#include "qdma_queue.h"
#include <qdma/qdma_nl.h>
#include <xlnx_gtest_ext.h>


#define SUCCESS						0
#define MAX_CMD_LEN					1000
#define MAX_RESP_LEN					(2048 * 6)
#define MAX_DUMP_LEN					(MAX_RESP_LEN * 10)
#define MIN_RESP_LEN					128

#define DMACTL_Q_ADD					(1 << 0)
#define DMACTL_Q_START					(1 << 1)
#define DMACTL_Q_DUMP					(1 << 2)
#define DMACTL_Q_STOP					(1 << 3)
#define DMACTL_Q_DEL					(1 << 4)

enum queue_dump_mode {
	none,
	descriptor,
	completion
};

extern test_env env;

/*
 * create a pipe to read from stdout
 */
int exec_cmd(char *cmd, char *cmdresp)
{

	char buffer[MIN_RESP_LEN] = "";

	strcat(cmd, " 2>&1");

	FILE* pipe = popen(cmd, "r");
	if (!pipe)
	{
		std::cout << "exec_cmd : Couldn't start command." << std::endl;
		return -1;
	}

	while (fgets(buffer, MIN_RESP_LEN, pipe) != NULL) {
		strcat(cmdresp, buffer);
	}


	if (pclose(pipe) == -1) {
		std::cout << "exec_cmd : Error returned." << std::endl;
		return -1;
	}

	//printf("%s : cmd executed successfully with cmdresp: %s\n", cmd, cmdresp);
	return SUCCESS;
}


int dmactl_devlist(void)
{
	char cmd[] = "dma-ctl dev list";
	char parseresp[MAX_RESP_LEN] = "";
	unsigned int i = 0;
	std::vector<qdma::device> &devlist = env.get_dev_list(qdma::instance_ext::type::pf);
	char cmdresp[MAX_RESP_LEN] = "";

	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) << std::endl;
		return -1;
	}
	/*qdma17000	0000:17:00.0	max QP: 512, 0~511*/
	for(i = 0; i < env.pfs.size(); i++) {
		snprintf(parseresp, MAX_RESP_LEN,"qdma%05x\t0000:%02x:%02x.%01x\tmax QP: %d, ",
				devlist[i].dev_id, (devlist[i].dev_id >> 8) >> 4, ((devlist[i].dev_id
				>> 3) & 0x1F), (devlist[i].dev_id & 0x7), env.pfs[i].max_num_queues);
		if(strstr(cmdresp, parseresp) == NULL) {
			return -1;
		}
	}

	return SUCCESS;
}

int verify_q_state(qdma::instance_ext::type devtype, uint32_t dev_id, uint32_t q_id, uint32_t numqs,
		qdma_queue_state qstate, qdma::queue_ext::direction dir=qdma::queue_ext::direction::both,
		bool qadd = false, qdma::queue_ext::mode mode = qdma::queue_ext::mode::memory_mapped) {

	uint32_t q_flags = 0;
	uint32_t rv = SUCCESS;
	xnl::socket *qdma_socket;
#ifndef TEST_VF_ALONE
	xnl::socket qdma_socket_pf { XNL_NAME_PF };
	if(devtype == qdma::instance_ext::type::pf) {
		qdma_socket = &qdma_socket_pf;
	}
#endif
	xnl::socket qdma_socket_vf { XNL_NAME_VF };
	if(devtype == qdma::instance_ext::type::vf) {
		qdma_socket = &qdma_socket_vf;
	}
	if(qadd == true) {
		if(mode == qdma::queue_ext::mode::streaming)
			q_flags |= XNL_F_QMODE_ST;
		else if(mode == qdma::queue_ext::mode::memory_mapped)
			q_flags |= XNL_F_QMODE_MM;
	}
	for(uint32_t i = q_id; i < numqs; i++) {
		if (dir != qdma::queue_ext::direction::host_to_card) {
			q_flags |= XNL_F_QDIR_C2H;
			q_flags &= ~(XNL_F_QDIR_H2C);
		}
		else
			q_flags |= XNL_F_QDIR_H2C;
both:
		auto nlcmd = qdma_socket->prepare_msg(XNL_CMD_GET_Q_STATE);
		nlcmd.add_attribute(XNL_ATTR_DEV_IDX, dev_id);
		nlcmd.add_attribute(XNL_ATTR_QIDX, i);
		nlcmd.add_attribute(XNL_ATTR_QFLAG, q_flags);

		qdma_socket->send_msg(nlcmd);
		auto resp = qdma_socket->receive_msg(XNL_ATTR_MAX);

		if(-EINVAL == qdma_socket->get_error()) {
			return -EINVAL;
		}

		uint32_t temp = 0;

		temp = resp.get_attrib<uint32_t>(XNL_ATTR_QIDX);

		if(i != temp) {
			rv = -EINVAL;
			break;
		}

		temp = resp.get_attrib<uint32_t>(XNL_ATTR_Q_STATE);
		if(qstate != temp) {
			rv = -EINVAL;
			break;
		}

		if((dir == qdma::queue_ext::direction::both) && (q_flags & XNL_F_QDIR_C2H)) {
			q_flags &= ~(XNL_F_QDIR_C2H);
			q_flags = (XNL_F_QDIR_H2C);
			goto both;
		}
	}

	return rv;
}




int dmactl_qadd(qdma::instance_ext::type devtype,uint32_t dev_id,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode,
		qdma::queue_ext::direction dir)
{

	char cmd[MAX_CMD_LEN] = "";
	char *cmdresp = NULL;
	char respbuff[MAX_CMD_LEN] = "";
	uint32_t rv = SUCCESS;

	if(numqs > 1) {
		cmdresp = (char *)calloc(MAX_RESP_LEN * numqs, sizeof(char));
	} else {
		cmdresp = (char *)calloc(MAX_RESP_LEN, sizeof(char));
	}
	if(cmdresp == NULL) {
		std::cout << "No response" << std::endl;
		return -1;
	}


	if(devtype == qdma::instance_ext::type::vf) {
		snprintf(cmd, MAX_CMD_LEN,"dma-ctl qdmavf%05x q add ",
				dev_id);
	} else {
		snprintf(cmd, MAX_CMD_LEN,"dma-ctl qdma%05x q add ",
				dev_id);
	}
	if(numqs > 1) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd),"list %d %d ", q_id , numqs);
	} else {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "idx %d ", q_id);
	}

	switch(dir) {
		case qdma::queue_ext::direction::host_to_card:
			snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dir %s ", "h2c");
			break;
		case qdma::queue_ext::direction::card_to_host:
			snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dir %s ",  "c2h");
			break;
		case qdma::queue_ext::direction::both:
			snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dir %s ", "bi");
			break;
		default:
			std::cout << "Invalid Direction" << std::endl;
			free(cmdresp);
			return -1;
	}


	if(mode == qdma::queue_ext::mode::memory_mapped) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "mode %s ", "mm");
	} else if (mode == qdma::queue_ext::mode::streaming) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "mode %s ", "st");
	} else {
		std::cout << "q add:INVALID MODE" << std::endl;
		free(cmdresp);
		return -1;
	}


	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		if(cmdresp != NULL)
			free(cmdresp);
		return -1;
	}


	/**
	 * parse response
	 */
	sprintf(respbuff, "Added %d Queues.", numqs);
	rv = verify_q_state(devtype,dev_id, q_id, numqs, QUEUE_ENABLED, dir, true, mode);

	if(strstr(cmdresp,respbuff) != NULL){
		free(cmdresp);
		return rv;
	} else {
		free(cmdresp);
		return -1;
	}
}




int dmactl_qstart(qdma::instance_ext::type devtype,uint32_t dev_id,
		uint32_t q_id, uint32_t numqs, const qdma::queue_ext::config& qcfg,
		qdma::queue_ext::direction dir=qdma::queue_ext::direction::both,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::memory_mapped)
{
	char cmd[MAX_CMD_LEN] = "";
	char *cmdresp = NULL;
	char respbuff[MAX_CMD_LEN] = "";
	int rv = SUCCESS;

	if(numqs > 1) {
		cmdresp = (char *)calloc(MAX_RESP_LEN * numqs, sizeof(char));
	} else {
		cmdresp = (char *)calloc(MAX_RESP_LEN, sizeof(char));
	}
	if(cmdresp == NULL) {
		return -1;
	}

	if(devtype == qdma::instance_ext::type::vf) {
		snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdmavf%05x q start ",
				dev_id);
	}
	else {
		snprintf(cmd, MAX_CMD_LEN,"dma-ctl qdma%05x q start ",
				dev_id);
	}
	if(numqs > 1) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd),"list %d %d ", q_id,
				numqs);
	} else {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd),"idx %d ", q_id);
	}


	switch(dir) {
		case qdma::queue_ext::direction::host_to_card:
			snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dir %s ",
					"h2c");
			break;
		case qdma::queue_ext::direction::card_to_host:
			snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dir %s ",
					"c2h");
			break;
		case qdma::queue_ext::direction::both:
			snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dir %s ", "bi");
			break;
		default:
			std::cout << "dmactl_qstart : Invalid Direction" << std::endl;
			free(cmdresp);
			return -1;
	}

	if((dir == qdma::queue_ext::direction::card_to_host || dir ==
			qdma::queue_ext::direction::both)) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd),
				"idx_ringsz %d ", qcfg.idx_rngsz);
	}

	if((dir == qdma::queue_ext::direction::card_to_host ||
			dir == qdma::queue_ext::direction::both)) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "idx_bufsz %d ",
				qcfg.idx_bufsz);
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "idx_tmr %d ",
				qcfg.idx_tmr);
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "idx_cntr %d ",
				qcfg.idx_cntr);
	}

	if((dir == qdma::queue_ext::direction::card_to_host ||
			dir == qdma::queue_ext::direction::both)) {
		if(qcfg.trigmode == qdma::queue_ext::c2h_wrb_intr_trigmode::every)
			strcat(cmd, "trigmode every ");
		else if(qcfg.trigmode == qdma::queue_ext::c2h_wrb_intr_trigmode::disable)
			strcat(cmd, "trigmode disable ");
		else if(qcfg.trigmode == qdma::queue_ext::c2h_wrb_intr_trigmode::cntr_tmr)
			strcat(cmd, "trigmode cntr_tmr ");
		else if(qcfg.trigmode == qdma::queue_ext::c2h_wrb_intr_trigmode::usr)
			strcat(cmd, "trigmode usr ");
		else if(qcfg.trigmode == qdma::queue_ext::c2h_wrb_intr_trigmode::usr_cnt)
			strcat(cmd, "trigmode usr_cnt ");
		else if(qcfg.trigmode == qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr)
			strcat(cmd, "trigmode usr_tmr ");
	}
	if (qcfg.sw_desc_sz == 3)
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "sw_desc_sz %d ",
				qcfg.sw_desc_sz);

	if ((dir == qdma::queue_ext::direction::card_to_host ||
			dir == qdma::queue_ext::direction::both) &&
			(qcfg.cmptsz < XNL_ST_C2H_NUM_CMPT_DESC_SIZES))
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "cmptsz %d ",
				qcfg.cmptsz);

	if(qcfg.desc_bypass) {
		strcat(cmd, "desc_bypass_en ");
	}
	if(qcfg.pfetch_bypass) {
		strcat(cmd, "pfetch_bypass_en ");
	}
	if(qcfg.prefetch) {
		strcat(cmd, "pfetch_en ");
	}
	if(!qcfg.fetch_credit) {
		strcat(cmd, "fetch_credit none ");
	}
	if(!qcfg.cmpl_status_en) {
		strcat(cmd, "dis_cmpl_status ");
	}
	if(!qcfg.cmpl_status_acc_en) {
		strcat(cmd, "dis_cmpl_status_acc ");
	}
	if(!qcfg.cmpl_status_pend_chk) {
		strcat(cmd, "dis_cmpl_status_pend_chk ");
	}
	if(!qcfg.cmpl_status_desc_en) {
		strcat(cmd, "dis_cmpl_status ");
	}
	if(qcfg.c2h_cmpl_intr_en &&
			(dir == qdma::queue_ext::direction::card_to_host ||
					dir == qdma::queue_ext::direction::both)) {
		strcat(cmd, "c2h_cmpl_intr_en ");
	}
	if(qcfg.c2h_udd_en &&
			(dir == qdma::queue_ext::direction::card_to_host ||
					dir == qdma::queue_ext::direction::both)) {
		strcat(cmd, "c2h_udd_en ");
	}
	if(qcfg.c2h_ovf_chk_dis &&
			(dir == qdma::queue_ext::direction::card_to_host ||
					dir == qdma::queue_ext::direction::both)) {
		strcat(cmd, "cmpl_ovf_dis ");
	}

	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		if(cmdresp != NULL)
			free(cmdresp);
		return -1;
	}
	sprintf(respbuff, "%d Queues started, idx %d ~ %d", numqs, q_id,
			(q_id - 1 + numqs));

	rv = verify_q_state(devtype,dev_id, q_id, numqs, QUEUE_ONLINE, dir);

	if(NULL != strstr(cmdresp, respbuff)){
		free(cmdresp);
		return rv;
	} else {
		free(cmdresp);
		return -1;
	}
}

int dmactl_devcap(uint32_t dev_id)
{
	char cmd[MAX_CMD_LEN] = "";
	char cmdresp[MAX_RESP_LEN] = "";
	if(cmdresp == NULL) {
		return -1;
	}

	snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdma%05x cap ",
			dev_id);
	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		return -1;
	}
	return SUCCESS;
}


int dmactl_qstop(qdma::instance_ext::type devtype,uint32_t dev_id,
		uint32_t q_id, uint32_t numqs = 1,
		qdma::queue_ext::direction dir=qdma::queue_ext::direction::both)
{

	char cmd[MAX_CMD_LEN] = "";
	char *cmdresp = NULL;
	char respbuff[MAX_CMD_LEN] = "";
	uint32_t rv = SUCCESS;

	if(numqs > 1) {
		cmdresp = (char *)calloc(MAX_RESP_LEN * numqs, sizeof(char));
	} else {
		cmdresp = (char *)calloc(MAX_RESP_LEN, sizeof(char));
	}
	if(cmdresp == NULL) {
		return -1;
	}


	if(devtype == qdma::instance_ext::type::vf)
		snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdmavf%05x q stop ",
				dev_id);
	else
		snprintf(cmd, MAX_CMD_LEN,"dma-ctl qdma%05x q stop ",
				dev_id);

	if(numqs > 1) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "list %d %d ", q_id ,
				numqs);
	} else {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "idx %d ", q_id);
	}

	switch(dir) {
		case qdma::queue_ext::direction::host_to_card:
			snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dir %s ",
					"h2c");
			break;
		case qdma::queue_ext::direction::card_to_host:
			snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dir %s ",
					"c2h");
			break;
		case qdma::queue_ext::direction::both:
			snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dir %s ", "bi");
			break;
		default:
			std::cout <<"dmactl_qstop : Invalid Direction";
			free(cmdresp);
			return -1;
	}


	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		if(cmdresp != NULL)
			free(cmdresp);
		return -1;
	}
	sprintf(respbuff, "Stopped Queues %d -> %d.", q_id, (q_id + numqs - 1));

	rv = verify_q_state(devtype,dev_id, q_id, numqs, QUEUE_ENABLED, dir);

	if(NULL != strstr(cmdresp, respbuff)) {
		free(cmdresp);
		return rv;
	} else {
		free(cmdresp);
		return -1;
	}

}

int dmactl_qdel(qdma::instance_ext::type devtype,uint32_t dev_id,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::direction dir)
{

	char cmd[MAX_CMD_LEN] = "";
	char *cmdresp = NULL;
	char respbuff[MAX_CMD_LEN] = "";
	uint32_t rv = SUCCESS;

	if(numqs > 1) {
		cmdresp = (char *)calloc(MAX_RESP_LEN * numqs, sizeof(char));
	} else {
		cmdresp = (char *)calloc(MAX_RESP_LEN, sizeof(char));
	}
	if(cmdresp == NULL) {
		return -1;
	}


	if(devtype == qdma::instance_ext::type::vf)
		snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdmavf%05x q del ",
				dev_id);
	else
		snprintf(cmd, MAX_CMD_LEN - strlen(cmd),  "dma-ctl qdma%05x q del ",
				dev_id);

	if(numqs > 1) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "list %d %d ", q_id,
				numqs);
	}else {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "idx %d ", q_id);
	}

	switch(dir) {
		case qdma::queue_ext::direction::host_to_card:
			snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dir %s ",
					"h2c");
			break;
		case qdma::queue_ext::direction::card_to_host:
			snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dir %s ",
					"c2h");
			break;
		case qdma::queue_ext::direction::both:
			snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dir %s ", "bi");
			break;
		default:
			std::cout << "dmactl_qdel : Invalid Direction" << std::endl;
			free(cmdresp);
			return -1;
	}


	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		if(cmdresp != NULL)
			free(cmdresp);
		return -1;
	}
	sprintf(respbuff, "Deleted Queues %d -> %d.", q_id, (q_id + numqs - 1));


	if(strstr(cmdresp, respbuff) != NULL){
		free(cmdresp);
		return rv;
	} else {
		free(cmdresp);
		return -1;
	}

}



int dmactl_devstats(uint32_t dev_id, qdma::instance_ext::type devtype)
{
	char cmd[MAX_CMD_LEN] = "";
	char cmdresp[MAX_RESP_LEN] = "";
	char teststr[MAX_CMD_LEN] = "";



	if(devtype == qdma::instance_ext::type::vf)
		snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdmavf%05x stat ",
				dev_id);
	else
		snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdma%05x stat ",
				dev_id);


	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		return -1;
	}

	snprintf(teststr, MAX_CMD_LEN, "qdma%05x:statistics",
					dev_id);
	if(strstr(cmdresp, teststr) != NULL) {
		return SUCCESS;
	} else {
		return -1;
	}
}


int dmactl_devstatsclr(uint32_t dev_id, qdma::instance_ext::type devtype)
{
	char cmd[MAX_CMD_LEN] = "";
	char cmdresp[MAX_RESP_LEN] = "";
	char teststr[MAX_CMD_LEN] = "";



	if(devtype == qdma::instance_ext::type::vf)
		snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdmavf%05x stat clear ",
				dev_id);
	else
		snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdma%05x stat clear ",
				dev_id);

	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		return -1;
	}

	if(devtype == qdma::instance_ext::type::vf)
		snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdmavf%05x stat ",
				dev_id);
	else
		snprintf(cmd, MAX_CMD_LEN,"dma-ctl qdma%05x stat ",
				dev_id);

	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		return -1;
	}

	strcpy(teststr, "Total MM H2C packets processed = 0");
	if(strstr(cmdresp, teststr) != NULL) {
		return SUCCESS;
	} else {
		return -1;
	}
}


int dmactl_regread(uint32_t dev_id, qdma::instance_ext::type devtype, uint32_t bar,
		uint64_t addr, uint32_t *data)
{
	char cmd[MAX_CMD_LEN] = "";
	char cmdresp[MAX_RESP_LEN] = "";
	char parseresp[MAX_CMD_LEN] = "";
	char *strdata= NULL;

	if(devtype == qdma::instance_ext::type::vf)
		snprintf(cmd, MAX_CMD_LEN,"dma-ctl qdmavf%05x reg read bar 0x%x 0x%lx ",
				dev_id, bar, addr);
	else
		snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdma%05x reg read bar 0x%x 0x%lx ",
				dev_id, bar, addr);
	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		return -1;
	}

	sprintf(parseresp, "0x%lx = ", addr);
	if(NULL != (strdata = strstr(cmdresp, parseresp)))
		*data = strtol(strdata + strlen(parseresp), NULL, 16);
	return SUCCESS;

}

int dmactl_regwrite (uint32_t dev_id, qdma::instance_ext::type devtype, uint32_t bar,
		uint64_t addr, uint32_t data)
{
	char cmd[MAX_CMD_LEN] = "";
	char cmdresp[MAX_RESP_LEN] = "";


	if(devtype == qdma::instance_ext::type::vf)
		snprintf(cmd, MAX_CMD_LEN,"dma-ctl qdmavf%05x reg write bar %d 0x%lx %u ",
				dev_id, bar, addr, data);
	else
		snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdma%05x reg write bar %d 0x%lx %u ",
				dev_id, bar, addr, data);

	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		return -1;
	}
	return SUCCESS;

}

int dmactl_regdump(qdma::instance_ext::type devtype, uint32_t dev_id,
		uint32_t q_id, uint32_t numqs)
{

	char cmd[MAX_CMD_LEN] = "";
	char *cmdresp = NULL;
	std::vector<qdma::device> &devlist = env.get_dev_list(devtype);
	auto ip_type = get_ip_type(dev_id, devlist);

	if(numqs > 1) {
		cmdresp = (char *)calloc(MAX_DUMP_LEN * numqs, sizeof(char));
	} else {
		cmdresp = (char *)calloc(MAX_DUMP_LEN, sizeof(char));
	}
	if(cmdresp == NULL) {
		return -1;
	}

	if(devtype == qdma::instance_ext::type::vf)
		snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdmavf%05x reg dump ",
				 	 dev_id);
	else
		snprintf(cmd, MAX_CMD_LEN,"dma-ctl qdma%05x reg dump ",
					dev_id);

	if(numqs > 0) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dmap %d %d ", q_id,
				numqs);
	}

	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		if(cmdresp != NULL)
			free(cmdresp);
		return -1;
	}



	switch(ip_type) {
		case EQDMA_LINUX_SOFT_IP:
			/**
			 * Reg Dump last string
			 * [ 0x240C] TARGET_FUNC_REG
			 *
			 */
			if(strstr(cmdresp, "C2H_WATER_MARK") != NULL) {
				free(cmdresp);
				return SUCCESS;
			} else {
				free(cmdresp);
				return -1;
			}
			break;
		case QDMA_LINUX_VERSAL_HARD_IP:
			/**
			 * Reg Dump last string
			 * [ 0x240C] TARGET_FUNC_REG
			 *
			 */
			if(strstr(cmdresp, "TARGET_FUNC_REG") != NULL) {
				free(cmdresp);
				return SUCCESS;
			} else {
				free(cmdresp);
				return -1;
			}
			break;
		case QDMA_LINUX_SOFT_IP:
			/**
			 * Reg Dump last string
			 * [ 0x2c7c] MSG_OUT_31
			 *
			 */
			if(strstr(cmdresp, "MSG_OUT_31") != NULL) {
				free(cmdresp);
				return SUCCESS;
			} else {
				free(cmdresp);
				return -1;
			}
			break;
		default:
			free(cmdresp);
			return -1;

	}

}

int dmactl_qdump(qdma::instance_ext::type devtype, uint32_t dev_id,
		uint32_t q_id, uint32_t numqs, queue_dump_mode dumpmode,
		uint32_t ringentryX, uint32_t ringentryY)
{
	char cmd[MAX_CMD_LEN] = "";
	char *cmdresp = NULL;
	char respbuff[MAX_RESP_LEN] = "";

	if(numqs > 1) {
		cmdresp = (char *)calloc(MAX_DUMP_LEN * numqs, sizeof(char));
	} else {
		cmdresp = (char *)calloc(MAX_DUMP_LEN, sizeof(char));
	}
	if(cmdresp == NULL) {
		return -1;
	}

	if(devtype == qdma::instance_ext::type::vf)
		snprintf(cmd, MAX_CMD_LEN,"dma-ctl qdmavf%05x q dump ",
					dev_id);
	else
		snprintf(cmd, MAX_CMD_LEN, "dma-ctl qdma%05x q dump ",
					dev_id);

	if(numqs > 1) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "list %d %d ", q_id,
				numqs);
	}else {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "idx %d ", q_id);
	}
	if(dumpmode == completion) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "cmpt %d %d",
				ringentryX, ringentryY);
		sprintf(respbuff, "Dumped descs of queues %d -> %d.", q_id, (numqs  - 1));
	}
	else if(dumpmode == descriptor) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "desc %d %d",
				ringentryX, ringentryY);
		sprintf(respbuff, "Dumped descs of queues %d -> %d.", q_id, (numqs  - 1));
	} else {
		sprintf(respbuff, "Dumped Queues %d -> %d.", q_id, (numqs  - 1));
	}


	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		if(cmdresp != NULL)
			free(cmdresp);
		return -1;
	}

	if(NULL != strstr(cmdresp,respbuff)){
		free(cmdresp);
		return SUCCESS;
	} else {
		free(cmdresp);
		return -1;
	}

}

/*dmactl qdma01000 intring dump vector 3*/

int dmactl_intr_ring_dump(uint32_t dev_id,
		uint32_t vectornum, uint32_t start_idx = 0, uint32_t end_idx = 0)
{
	char cmd[MAX_CMD_LEN] = "";
	char cmdresp[MAX_DUMP_LEN] = "";
	char respbuff[MAX_RESP_LEN] = "";


	if((start_idx == 0) && (end_idx == 0)) {
		snprintf(cmd, MAX_CMD_LEN,"dma-ctl qdma%05x intring dump vector %d ",
				dev_id, vectornum);
	} else {
		snprintf(cmd, MAX_CMD_LEN,"dma-ctl qdma%05x intring dump vector %d %d %d",
			dev_id, vectornum, start_idx, end_idx);
	}

	sprintf(respbuff, "intr_ring_entry = %d", start_idx);

	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		return -1;
	}

	if((strstr(cmdresp, respbuff) != NULL) ||
		(strstr(cmdresp, "Interrupt aggregation not enabled"))) {
		return SUCCESS;
	} else {
		return -1;
	}

}



int dma_transfers(bool tx, qdma::instance_ext::type VF,uint32_t devid,
		qdma::queue_ext::mode mode, uint32_t qidx,
		uint32_t offset = 0, uint32_t size = 0, uint32_t count = 0,
		uint32_t axiaddr = 0, char *inf = NULL,
		char *outf = NULL)
{
	char cmd[MAX_CMD_LEN] = "";
	char cmdresp[MAX_RESP_LEN] = "";
	if(tx) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dma-to-device ");
	} else {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "dma-from-device ");
	}

	if(qdma::instance_ext::type::vf == VF) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), " -d /dev/qdmavf%05x",
				devid);
	} else {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), " -d /dev/qdma%05x",
				devid);
	}

	if(qdma::queue_ext::mode::memory_mapped == mode) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "-MM-%d ", qidx);
	} else {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "-ST-%d ", qidx);
	}

	if(size > 0) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "-s %d ", size);
	}

	if(offset > 0) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "-o 0x%x ", offset);
	}
	if(count > 0) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "-c 0x%x ", count);
	}

	if(inf != NULL) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "-r %s ", inf);
	}

	if(outf != NULL) {
		snprintf((cmd + strlen(cmd)), MAX_CMD_LEN - strlen(cmd), "-w %s ", outf);
	}

	if(SUCCESS != exec_cmd(cmd, cmdresp)) {
		std::cout << "command is : " << std::endl << std::string(cmd) << std::endl;
		std::cout << "command response is" << std::endl << std::string(cmdresp) <<
				std::endl;
		return -1;
	}

	if(NULL != strstr(cmdresp, "Average BW =")) {
		return SUCCESS;
	} else {
		return -1;
	}
}





/*----------------------------------------------------------------------------------------------------
 *
 *  				DMACTL TEST CASES
 *
 * --------------------------------------------------------------------------------------------------*/



struct dmactl_params {
	struct dmactl_qdetails {
		uint32_t pf = 0;
		uint32_t q = 0;
		uint32_t qs = 0;
		uint32_t qops = 0;
		qdma::queue_ext::mode qmode;
		qdma::queue_ext::direction qdir;
		qdma::queue_ext::config qcfg;
		dmactl_qdetails(uint32_t pf_id, uint32_t q_id, uint32_t numqs,
				uint32_t q_operations,
				qdma::queue_ext::mode mode = qdma::queue_ext::mode::memory_mapped,
				qdma::queue_ext::direction dir = qdma::queue_ext::direction::host_to_card,
				qdma::queue_ext::config qconf = qdma::queue_ext::config(),
				uint32_t barid = 0, uint32_t addr = 0, uint32_t regdata = 0,
				queue_dump_mode dumpmod = queue_dump_mode::none,
				uint32_t rngentryX = 0, uint32_t rngentryY = 0)
		: pf(pf_id), q(q_id), qs(numqs), qops(q_operations), qmode(mode), qdir(dir),
		  qcfg(qconf) {}
	};

	std::vector<dmactl_qdetails> dmactl_qd;
	qdma::instance_ext::type devtype = qdma::instance_ext::type::pf;
	uint32_t bar_id = 0;
	uint32_t register_address = 0;
	uint32_t register_data = 0;
	queue_dump_mode dumpmode = queue_dump_mode::none;
	uint32_t ring_entry_x = 0;
	uint32_t ring_entry_y = 0;
	bool negative_test = false;
	dmactl_params() = default;

	dmactl_params(std::vector<dmactl_qdetails>&& txs)
	: dmactl_qd(std::move(txs)) {
	}
	dmactl_params(std::vector<dmactl_qdetails>&& txs, bool negcase)
	: dmactl_qd(std::move(txs)), negative_test(negcase) {
	}
	dmactl_params(std::vector<dmactl_qdetails>&& txs,
			qdma::instance_ext::type dev_type)
	: dmactl_qd(std::move(txs)), devtype(dev_type) {
	}
	dmactl_params(std::vector<dmactl_qdetails>&& txs,
			qdma::instance_ext::type dev_type, bool negcase)
		: dmactl_qd(std::move(txs)), devtype(dev_type), negative_test(negcase) {
	}
	dmactl_params(std::vector<dmactl_qdetails>&& txs,
			qdma::instance_ext::type dev_type, uint32_t bar_num, uint32_t address,
			uint32_t regdata)
	: dmactl_qd(std::move(txs)), devtype(dev_type), bar_id(bar_num),
	  register_address(address), register_data(regdata) {
	}
	dmactl_params(std::vector<dmactl_qdetails>&& txs,
			qdma::instance_ext::type dev_type, queue_dump_mode dumpmod,
			uint32_t rngent_x, uint32_t rngent_y)
	: dmactl_qd(std::move(txs)), devtype(dev_type), dumpmode(dumpmod),
	  ring_entry_x(rngent_x), ring_entry_y(rngent_y) {
	}
};

void PrintTo(const dmactl_params& tp, std::ostream* os) {
	const auto& txs = tp.dmactl_qd;

	//only print the ranges (first and last entry)
	if (!txs.empty()) {
		if (tp.devtype == qdma::instance_ext::type::vf)
			*os << "{ vfs=[";
		else
			*os << "{ pfs=[";
		*os << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.front().pf
				<< ":" << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.back().pf << "], ";
		*os << "queues=[" << txs.front().q << ":" << txs.back().q << "], ";
		*os << "num_of_qs=" << txs.front().qs << " }";
	}
}


class qdma_dmactl_test: public testing::TestWithParam<dmactl_params> {
public:
};


/*
 * Test 1
 *Add and delete queues in PF/VF dir ST/MM and C2H/H2C/BI
 */
static dmactl_params dmactl_q_add_del_test(const uint32_t num_of_functions,
		const uint32_t q_operations, uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::memory_mapped,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::host_to_card,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf,
		bool negtest = false) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t validfunctions = 0;

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}


	qdetails.reserve(validfunctions);


	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(negtest == false) {
			if(dev_type == qdma::instance_ext::type::pf) {
				if(env.pfs[pf_id].max_num_queues == 0)
					continue;
				if(numqs > env.pfs[pf_id].max_num_queues)
					numqs = env.pfs[pf_id].max_num_queues;
			} else {
				if(env.vfs[pf_id].max_num_queues == 0)
					continue;
				if(numqs > env.vfs[pf_id].max_num_queues)
					numqs = env.vfs[pf_id].max_num_queues;
			}
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode,
				dir);
	}
	return dmactl_params { std::move(qdetails) , dev_type, negtest};
}

static dmactl_params dmactl_q_add_start_stop_del_test(const uint32_t num_of_functions,
		const uint32_t q_operations, uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::memory_mapped,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::host_to_card,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf,
		bool negtest = false) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;

	uint32_t validfunctions = 0;

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}


	qdetails.reserve(validfunctions);


	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(negtest == false) {
			if(dev_type == qdma::instance_ext::type::pf) {
				if(env.pfs[pf_id].max_num_queues == 0)
					continue;
				if(numqs > env.pfs[pf_id].max_num_queues)
					numqs = env.pfs[pf_id].max_num_queues;
			} else {
				if(env.vfs[pf_id].max_num_queues == 0)
					continue;
				if(numqs > env.vfs[pf_id].max_num_queues)
					numqs = env.vfs[pf_id].max_num_queues;
			}
		}

		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode,
				dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type, negtest};
}






/*
 * q start  idx_rngsz
 */

static dmactl_params dmactl_ring_idx_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs, uint16_t ring_idx,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.idx_rngsz = ring_idx;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);



	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;

			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;

			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}

		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode,
				dir, qcfg);
	}
	return dmactl_params { std::move(qdetails) , dev_type};
}

/*
 * q start idx_bufsz
 */
static dmactl_params dmactl_buffer_size_idx_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs, uint16_t buffer_size_idx,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;

	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.idx_bufsz = buffer_size_idx;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}


/*
  * q start idx_cntr
  */


static dmactl_params dmactl_counter_idx_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs, uint16_t counter_idx,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;

	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.idx_cntr = counter_idx;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}



/*
 * q start idx_tmr
 */
static dmactl_params dmactl_timer_idx_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs, uint16_t timer_idx,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;

	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.idx_tmr = timer_idx;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode,
				dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}


/*
 * q start trigmode
 */
static dmactl_params dmactl_trigger_mode_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue::c2h_wrb_intr_trigmode triggermode = qdma::queue::c2h_wrb_intr_trigmode::every,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;

	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.trigmode = triggermode;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}


/*
 * q start cmptsz
 */

static dmactl_params dmactl_completion_size_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs, xnl_st_c2h_cmpt_desc_size completion_size,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;

	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.cmptsz = completion_size;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}

/*
 * q start desc_bypass
 */

static dmactl_params dmactl_desc_bypass_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.desc_bypass = true;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}

/*
 * q start pfetch_bypass
 */

static dmactl_params dmactl_prefetch_bypass_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;


	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.desc_bypass = true;
	qcfg.pfetch_bypass = true;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}


/*
 * q start prefetch
 */
static dmactl_params dmactl_prefetch_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.prefetch = true;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}



/*
 * q start fetch_credit
 */
static dmactl_params dmactl_fetch_credit_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.prefetch = true;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}



/*
 * q start c2h_ovf_chk_dis
 */

static dmactl_params dmactl_completion_overflow_desc_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.c2h_ovf_chk_dis = true;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}


/*
 * q start c2h_udd_en
 */
static dmactl_params dmactl_user_defined_desc_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.cmptsz = XNL_ST_C2H_CMPT_DESC_SIZE_8B;
	qcfg.c2h_udd_en = true;


	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}


/*
 * q start c2h_cmpl_intr_en
 */
static dmactl_params dmactl_c2h_completion_interrupt_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.c2h_cmpl_intr_en = true;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}


/*
 * q start cmpl_status_en
 */
static dmactl_params dmactl_disable_cmpl_status_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_params::dmactl_qdetails> qdetails;

	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.cmpl_status_en = false;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}



/*
 * q start cmpl_status_acc_en
 */
static dmactl_params dmactl_disable_cmpl_status_acc_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{

	std::vector<dmactl_params::dmactl_qdetails> qdetails;

	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.cmpl_status_acc_en = false;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}

/*
 * q start cmpl_status_pend_chk
 */

static dmactl_params dmactl_disable_cmpl_status_pend_chk_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.cmpl_status_pend_chk = false;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}


/*
 * q start cmpl_status_desc_en
 */

static dmactl_params dmactl_disable_cmpl_status_desc_en_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.cmpl_status_desc_en = false;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}


/*
 * q start sw_desc_sz
 */
static dmactl_params dmactl_sw_desc_sz_test(const uint32_t num_of_functions,
		uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::mode mode = qdma::queue_ext::mode::streaming,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::card_to_host,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf)
{
	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;
	uint32_t q_operations = DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL;
	qcfg.sw_desc_sz = 3;

	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations, mode, dir, qcfg);
	}

	return dmactl_params { std::move(qdetails) , dev_type};
}




/*
 * 		q dump idx <N> dir [<h2c|c2h|bi>]   dump queue param
 *		q dump list <start_idx> <num_Qs> dir [<h2c|c2h|bi>] - dump queue param
 *		q dump idx <N> dir [<h2c|c2h|bi>] desc <x> <y> - dump desc ring entry x ~ y
 *		q dump list <start_idx> <num_Qs> dir [<h2c|c2h|bi>] desc <x> <y> - dump desc ring entry x ~ y
 *		q dump idx <N> dir [<h2c|c2h|bi>] cmpt <x> <y> - dump cmpt ring entry x ~ y
 *		q dump list <start_idx> <num_Qs> dir [<h2c|c2h|bi>] cmpt <x> <y> - dump cmpt ring entry x ~ y
 *
 */
static dmactl_params dmactl_queue_dump_test(const uint32_t num_of_functions,
		uint32_t q_operations, uint32_t q_id, uint32_t numqs,
		qdma::queue_ext::direction dir = qdma::queue_ext::direction::host_to_card,
		qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf,
		queue_dump_mode dumpmod = queue_dump_mode::none, uint32_t rngent_x = 0,
		uint32_t rngent_y = 0)
{
	std::vector<dmactl_params::dmactl_qdetails> qdetails;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t validfunctions = 0;
	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues > 0)
				validfunctions++;
		} else {
			if(env.vfs[pf_id].max_num_queues > 0)
				validfunctions++;
		}
	}
	qdetails.reserve(validfunctions);

	for (uint32_t pf_id = 0; pf_id < num_of_functions; pf_id++) {
		if(dev_type == qdma::instance_ext::type::pf) {
			if(env.pfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.pfs[pf_id].max_num_queues)
				numqs = env.pfs[pf_id].max_num_queues;
		} else {
			if(env.vfs[pf_id].max_num_queues == 0)
				continue;
			if(numqs > env.vfs[pf_id].max_num_queues)
				numqs = env.vfs[pf_id].max_num_queues;
		}
		qdetails.emplace_back(devlist[pf_id].dev_id, q_id, numqs, q_operations);
	}

	return dmactl_params { std::move(qdetails) , dev_type, dumpmod, rngent_x, rngent_y};

}



TEST_P(qdma_dmactl_test, dmactl_qops_test) {

	const auto& qd = GetParam();

	for (const auto& qmdi : qd.dmactl_qd) {

		SCOPED_TRACE("devtype = " + (qd.devtype == qdma::instance_ext::type::pf) ? "PF" : "VF");
		SCOPED_TRACE("pf = " + int_to_hex(qmdi.pf));
		SCOPED_TRACE("q = " + int_to_hex(qmdi.q));
		SCOPED_TRACE("qs = " + int_to_hex(qmdi.qs));
		auto &devlist = env.get_dev_list(qd.devtype);


        if(validate_test_case(devlist, qmdi.pf, qmdi.qcfg) < 0) {
            //GTEST_SKIP();
            std::cout << "Invalid Test Case" << std::endl;
            continue;
        }
		for(uint32_t i = 0; i < 9; i++) {
			switch(qmdi.qops & (1 << i)) {
				case DMACTL_Q_ADD:
					if(qd.negative_test == false)
						EXPECT_EQ(SUCCESS, dmactl_qadd(qd.devtype, qmdi.pf, qmdi.q, qmdi.qs, qmdi.qmode, qmdi.qdir));
					else
						EXPECT_LT(dmactl_qadd(qd.devtype, qmdi.pf, qmdi.q, qmdi.qs, qmdi.qmode, qmdi.qdir), SUCCESS);
				break;
				case DMACTL_Q_START:
					if(qd.negative_test == false)
						EXPECT_EQ(SUCCESS, dmactl_qstart(qd.devtype, qmdi.pf, qmdi.q, qmdi.qs, qmdi.qcfg, qmdi.qdir));
					else
						EXPECT_LT(dmactl_qstart(qd.devtype, qmdi.pf, qmdi.q, qmdi.qs, qmdi.qcfg, qmdi.qdir), SUCCESS);
				break;
				case DMACTL_Q_STOP:
					if(qd.negative_test == false)
						EXPECT_EQ(SUCCESS, dmactl_qstop(qd.devtype, qmdi.pf, qmdi.q, qmdi.qs, qmdi.qdir));
					else
						EXPECT_LT(dmactl_qstop(qd.devtype, qmdi.pf, qmdi.q, qmdi.qs, qmdi.qdir), SUCCESS);
				break;
				case DMACTL_Q_DEL:
					if(qd.negative_test == false)
						EXPECT_EQ(SUCCESS, dmactl_qdel(qd.devtype, qmdi.pf, qmdi.q, qmdi.qs, qmdi.qdir));
					else
						EXPECT_LT(dmactl_qdel(qd.devtype, qmdi.pf, qmdi.q, qmdi.qs, qmdi.qdir), SUCCESS);
				break;
				case DMACTL_Q_DUMP:
					if(qd.negative_test == false)
						EXPECT_EQ(SUCCESS, dmactl_qdump(qd.devtype, qmdi.pf, qmdi.q, qmdi.qs, qd.dumpmode,
								qd.ring_entry_x, qd.ring_entry_y));
					else
						EXPECT_EQ(dmactl_qdump(qd.devtype, qmdi.pf, qmdi.q, qmdi.qs, qd.dumpmode,
														qd.ring_entry_x, qd.ring_entry_y), SUCCESS);
				break;
			}
		}
	}
}





TEST(qdma_dmactl_fixture_test, DMACTL001_devcap_test) {
	std::vector<qdma::device> &devlist = env.get_dev_list(qdma::instance_ext::type::pf);
	ASSERT_EQ(SUCCESS, dmactl_devcap(devlist[0].dev_id));
}


TEST(qdma_dmactl_fixture_test, DMACTL002_devlist_test) {
	ASSERT_EQ(SUCCESS, dmactl_devlist());
}


/*
 *		reg write [bar <N>] <addr> <val> - write a register
 */

TEST(qdma_dmactl_fixture_test, DMACTL003_read_write_test) {

	qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t num_of_functions = env.pfs.size();

	for(uint32_t i = 0; i < num_of_functions; i++) {
		uint32_t readdata = 0;
		uint32_t writedata = 0xffffffff;
		SCOPED_TRACE("pf = " + int_to_hex(i));
		SCOPED_TRACE("Control bar write");
		SCOPED_TRACE("writedata = " + int_to_hex(writedata));
		dmactl_regwrite(devlist[i].dev_id, dev_type, 0, 0x80, writedata);
		dmactl_regread(devlist[i].dev_id, dev_type, 0, 0x80, &readdata);
		SCOPED_TRACE("read data = " + int_to_hex(readdata));
		ASSERT_EQ(writedata, readdata);
	}

	for(uint32_t i = 0; i < num_of_functions; i++) {
		uint32_t readdata = 0;
		uint32_t writedata = 0xdeadbeef;
		SCOPED_TRACE("pf = " + int_to_hex(i));
		SCOPED_TRACE("Control bar write");
		SCOPED_TRACE("writedata = " + int_to_hex(writedata));
		dmactl_regwrite(devlist[i].dev_id, dev_type, 0, 0x80, writedata);
		dmactl_regread(devlist[i].dev_id, dev_type, 0, 0x80, &readdata);
		SCOPED_TRACE("read data = " + int_to_hex(readdata));
		ASSERT_EQ(writedata, readdata);
	}

}




TEST(qdma_dmactl_fixture_test, DMACTL004_reg_dump_test) {

	qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t num_of_functions = env.pfs.size();
	for(uint32_t i = 0; i < num_of_functions; i++) {
		uint32_t readdata = 0;
		uint32_t writedata = 0xffffffff;
		SCOPED_TRACE("pf = " + int_to_hex(i));
		SCOPED_TRACE("Control bar write");
		SCOPED_TRACE("writedata = " + int_to_hex(writedata));
		dmactl_regwrite(devlist[i].dev_id, dev_type, 0, 0x80, writedata);
		dmactl_regread(devlist[i].dev_id, dev_type, 0, 0x80, &readdata);
		EXPECT_EQ(SUCCESS, dmactl_regdump(dev_type, devlist[i].dev_id, 0, 0));
		SCOPED_TRACE("read data = " + int_to_hex(readdata));
		ASSERT_EQ(writedata, readdata);
	}
}


TEST(qdma_dmactl_fixture_test, DMACTL005_intr_ring_dump) {

	qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t num_of_functions = env.pfs.size();
	auto device_type = get_device_type(env.pfs[env.sys_cfg.master_pf].dev_id, devlist);
	int ip_type = get_ip_type(env.pfs[env.sys_cfg.master_pf].dev_id, devlist);

	for(uint32_t i = 0; i < num_of_functions; i++) {
		SCOPED_TRACE("function : " + i);
		if(devlist[i].dev_id == env.pfs[env.sys_cfg.master_pf].dev_id) {
			SCOPED_TRACE("test : dmactl qdma" + int_to_hex(devlist[i].dev_id) +
					" intring dump vector 3");
			if ((device_type == QDMA_DEVICE_VERSAL_CPM4) &&
					(ip_type == QDMA_VERSAL_HARD_IP))
				EXPECT_EQ(dmactl_intr_ring_dump(devlist[i].dev_id, 2), SUCCESS);
			else
				EXPECT_EQ(dmactl_intr_ring_dump(devlist[i].dev_id, 3), SUCCESS);
		} else {
			SCOPED_TRACE("test : dmactl qdma" + int_to_hex(devlist[i].dev_id) +
					" intring dump vector 2");
			if ((device_type == QDMA_DEVICE_VERSAL_CPM4) &&
					(ip_type == QDMA_VERSAL_HARD_IP))
				EXPECT_EQ(dmactl_intr_ring_dump(devlist[i].dev_id, 1), SUCCESS);
			else
				EXPECT_EQ(dmactl_intr_ring_dump(devlist[i].dev_id, 2), SUCCESS);
		}
		if(devlist[i].dev_id == env.pfs[env.sys_cfg.master_pf].dev_id) {
			SCOPED_TRACE("test : dmactl qdma" + int_to_hex(devlist[i].dev_id) +
					" intring dump vector 3 0 10");
			if ((device_type == QDMA_DEVICE_VERSAL_CPM4) &&
					(ip_type == QDMA_VERSAL_HARD_IP))
				EXPECT_EQ(dmactl_intr_ring_dump(devlist[i].dev_id, 2, 0, 10), SUCCESS);
			else
				EXPECT_EQ(dmactl_intr_ring_dump(devlist[i].dev_id, 3, 0, 10), SUCCESS);
		} else {
			SCOPED_TRACE("test : dmactl qdma" + int_to_hex(devlist[i].dev_id) +
					" intring dump vector 2 0 10");
			if ((device_type == QDMA_DEVICE_VERSAL_CPM4) &&
					(ip_type == QDMA_VERSAL_HARD_IP))
				EXPECT_EQ(dmactl_intr_ring_dump(devlist[i].dev_id, 1, 0, 10), SUCCESS);
			else
				EXPECT_EQ(dmactl_intr_ring_dump(devlist[i].dev_id, 2, 0, 10), SUCCESS);
		}
	}
}

TEST(qdma_dmactl_fixture_test, DMACTL006_stat_test) {

	qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t num_of_functions = env.pfs.size();

	for(uint32_t i = 0; i < num_of_functions; i++) {
		EXPECT_EQ(dmactl_devstats(devlist[i].dev_id, dev_type), SUCCESS);
	}

}

TEST(qdma_dmactl_fixture_test, DMACTL007_stat_clr_test) {

	qdma::instance_ext::type dev_type = qdma::instance_ext::type::pf;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t num_of_functions = env.pfs.size();

	for(uint32_t i = 0; i < num_of_functions; i++) {
		EXPECT_EQ(dmactl_devstatsclr(devlist[i].dev_id, dev_type), SUCCESS);
	}

}


INSTANTIATE_TEST_CASE_P(DMACTL008_mm_q_add_del_test, qdma_dmactl_test, ::testing::Values(
		dmactl_q_add_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card),
		dmactl_q_add_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card),
		dmactl_q_add_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host),
		dmactl_q_add_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host),
		dmactl_q_add_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both),
		dmactl_q_add_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both)
));


INSTANTIATE_TEST_CASE_P(VF_DMACTL008_mm_q_add_del_test, qdma_dmactl_test, ::testing::Values(
		dmactl_q_add_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::vf),
		dmactl_q_add_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::vf),
		dmactl_q_add_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_q_add_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_q_add_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_q_add_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf)
));


INSTANTIATE_TEST_CASE_P(DMACTL009_st_q_add_del_test, qdma_dmactl_test, ::testing::Values(
		dmactl_q_add_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::host_to_card),
		dmactl_q_add_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::host_to_card),
		dmactl_q_add_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_q_add_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_q_add_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both),
		dmactl_q_add_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both)));

INSTANTIATE_TEST_CASE_P(VF_DMACTL009_st_q_add_del_test, qdma_dmactl_test, ::testing::Values(
		dmactl_q_add_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::vf),
		dmactl_q_add_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::vf),
		dmactl_q_add_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_q_add_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_q_add_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_q_add_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf)));

#ifndef TEST_VF_ALONE
INSTANTIATE_TEST_CASE_P(DMACTL010_q_add_del_negative_test, qdma_dmactl_test, ::testing::Values(
		dmactl_q_add_del_test(1, DMACTL_Q_ADD | DMACTL_Q_DEL, (env.pfs[0].max_num_queues + 1), 1,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::pf, true),
		dmactl_q_add_del_test(1, DMACTL_Q_ADD | DMACTL_Q_DEL, 0, (env.pfs[0].max_num_queues + 1),
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::pf, true),
		dmactl_q_add_del_test(1, DMACTL_Q_DEL, 0, (env.pfs[0].max_num_queues),
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::pf, true)
		));
#endif
INSTANTIATE_TEST_CASE_P(DMACTL011_mm_q_add_start_stop_del_test, qdma_dmactl_test, ::testing::Values(
		dmactl_q_add_start_stop_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card),
		dmactl_q_add_start_stop_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card),
		dmactl_q_add_start_stop_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host),
		dmactl_q_add_start_stop_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host),
		dmactl_q_add_start_stop_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both),
		dmactl_q_add_start_stop_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both)));

INSTANTIATE_TEST_CASE_P(VF_DMACTL011_mm_q_add_start_stop_del_test, qdma_dmactl_test, ::testing::Values(
		dmactl_q_add_start_stop_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::vf),
		dmactl_q_add_start_stop_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::vf),
		dmactl_q_add_start_stop_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_q_add_start_stop_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_q_add_start_stop_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_q_add_start_stop_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf)));


INSTANTIATE_TEST_CASE_P(DMACTL012_st_q_add_start_stop_del_test, qdma_dmactl_test, ::testing::Values(
		dmactl_q_add_start_stop_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::host_to_card),
		dmactl_q_add_start_stop_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::host_to_card),
		dmactl_q_add_start_stop_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_q_add_start_stop_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_q_add_start_stop_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both),
		dmactl_q_add_start_stop_del_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both)));

INSTANTIATE_TEST_CASE_P(VF_DMACTL012_st_q_add_start_stop_del_test, qdma_dmactl_test, ::testing::Values(
		dmactl_q_add_start_stop_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::vf),
		dmactl_q_add_start_stop_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::vf),
		dmactl_q_add_start_stop_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_q_add_start_stop_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_q_add_start_stop_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_q_add_start_stop_del_test(env.vfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf)));

#ifndef TEST_VF_ALONE
INSTANTIATE_TEST_CASE_P(DMACTL013_q_add_start_stop_del_negative_test, qdma_dmactl_test, ::testing::Values(
		dmactl_q_add_start_stop_del_test(1, DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL, (env.pfs[0].max_num_queues + 1), 1,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::pf, true),
		dmactl_q_add_start_stop_del_test(1, DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_STOP | DMACTL_Q_DEL, 0, (env.pfs[0].max_num_queues + 1),
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::pf, true),
		dmactl_q_add_start_stop_del_test(1, DMACTL_Q_START, 0, (env.pfs[0].max_num_queues),
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::host_to_card,
				qdma::instance_ext::type::pf, true)
		));
#endif

INSTANTIATE_TEST_CASE_P(DMACTL014_idx_rngsz_test, qdma_dmactl_test, ::testing::Values(
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 2, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 3, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 4, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 5, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 6, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 7, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 8, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 9, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 11, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 12, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 13, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 14, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 15, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both),
		dmactl_ring_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host),
		dmactl_ring_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both),
		dmactl_ring_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both)
		));


INSTANTIATE_TEST_CASE_P(VF_DMACTL014_idx_rngsz_test, qdma_dmactl_test, ::testing::Values(
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 2, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 3, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 4, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 5, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 6, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 7, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 8, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 9, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 11, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 12, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 13, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 14, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 15, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_ring_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf)
		));

INSTANTIATE_TEST_CASE_P(DMACTL015_idx_bufsz_test, qdma_dmactl_test, ::testing::Values(
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 2, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 3, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 4, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 5, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 6, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 7, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 8, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 9, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 11, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 12, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 13, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 14, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 15, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both),
		dmactl_buffer_size_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both)
		));

INSTANTIATE_TEST_CASE_P(VF_DMACTL015_idx_bufsz_test, qdma_dmactl_test, ::testing::Values(
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 2, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 3, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 4, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 5, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 6, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 7, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 8, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 9, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 11, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 12, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 13, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 14, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 15, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_buffer_size_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf)
		));


INSTANTIATE_TEST_CASE_P(DMACTL016_idx_cntr_test, qdma_dmactl_test, ::testing::Values(
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 2, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 3, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 4, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 5, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 6, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 7, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 8, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 9, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 11, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 12, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 13, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 14, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 15, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both),
		dmactl_counter_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host),
		dmactl_counter_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both),
		dmactl_counter_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both)
		));



INSTANTIATE_TEST_CASE_P(VF_DMACTL016_idx_cntr_test, qdma_dmactl_test, ::testing::Values(
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 2, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 3, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 4, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 5, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 6, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 7, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 8, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 9, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 11, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 12, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 13, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 14, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 15, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both,
								qdma::instance_ext::type::vf),
		dmactl_counter_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both,
								qdma::instance_ext::type::vf)
		));

INSTANTIATE_TEST_CASE_P(DMACTL017_idx_tmr_test, qdma_dmactl_test, ::testing::Values(
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 2, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 3, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 4, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 5, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 6, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 7, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 8, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 9, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 11, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 12, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 13, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 14, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 15, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both),
		dmactl_timer_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host),
		dmactl_timer_idx_test(env.pfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both),
		dmactl_timer_idx_test(env.pfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both)
		));


INSTANTIATE_TEST_CASE_P(VF_DMACTL017_idx_tmr_test, qdma_dmactl_test, ::testing::Values(
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 1, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 2, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 3, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 4, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 5, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 6, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 7, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 8, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 9, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 10, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 11, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 12, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 13, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 14, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 15, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 1, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf),
		dmactl_timer_idx_test(env.vfs.size(), 0, 4, 0, qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both,
				qdma::instance_ext::type::vf)
		));


INSTANTIATE_TEST_CASE_P(DMACTL018_intr_trigmode_test, qdma_dmactl_test, ::testing::Values(
		dmactl_trigger_mode_test(env.pfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::every,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_trigger_mode_test(env.pfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::cntr_tmr,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_trigger_mode_test(env.pfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::usr,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_trigger_mode_test(env.pfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::usr_cnt,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_trigger_mode_test(env.pfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::usr_tmr,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host),
		dmactl_trigger_mode_test(env.pfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::every,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both),
		dmactl_trigger_mode_test(env.pfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::every,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both),
		dmactl_trigger_mode_test(env.pfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::every,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host)));

INSTANTIATE_TEST_CASE_P(VF_DMACTL018_intr_trigmode_test, qdma_dmactl_test, ::testing::Values(
		dmactl_trigger_mode_test(env.vfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::every,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_trigger_mode_test(env.vfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::cntr_tmr,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_trigger_mode_test(env.vfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::usr,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_trigger_mode_test(env.vfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::usr_cnt,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_trigger_mode_test(env.vfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::usr_tmr,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_trigger_mode_test(env.vfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::every,
				qdma::queue_ext::mode::streaming, qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_trigger_mode_test(env.vfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::every,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_trigger_mode_test(env.vfs.size(), 0, 1, qdma::queue::c2h_wrb_intr_trigmode::every,
				qdma::queue_ext::mode::memory_mapped, qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));

INSTANTIATE_TEST_CASE_P(DMACTL019_c2h_cmpt_desc_test, qdma_dmactl_test, ::testing::Values(
		dmactl_completion_size_test(env.pfs.size(), 0, 1, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_8B,
				qdma::queue_ext::direction::card_to_host),
		dmactl_completion_size_test(env.pfs.size(), 0, 1, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_16B,
				qdma::queue_ext::direction::card_to_host),
		dmactl_completion_size_test(env.pfs.size(), 0, 1, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_32B,
				qdma::queue_ext::direction::card_to_host),
		dmactl_completion_size_test(env.pfs.size(), 0, 1, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_64B,
				qdma::queue_ext::direction::card_to_host),
		dmactl_completion_size_test(env.pfs.size(), 0, 10, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_8B,
				qdma::queue_ext::direction::card_to_host),
		dmactl_completion_size_test(env.pfs.size(), 0, 10, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_16B,
				qdma::queue_ext::direction::card_to_host),
		dmactl_completion_size_test(env.pfs.size(), 0, 10, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_32B,
				qdma::queue_ext::direction::card_to_host),
		dmactl_completion_size_test(env.pfs.size(), 0, 10, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_64B,
				qdma::queue_ext::direction::card_to_host),
		dmactl_completion_size_test(env.pfs.size(), 0, 1, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_64B,
				qdma::queue_ext::direction::both),
		dmactl_completion_size_test(env.pfs.size(), 0, 10, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_64B,
				qdma::queue_ext::direction::both)
));

INSTANTIATE_TEST_CASE_P(VF_DMACTL019_c2h_cmpt_desc_test, qdma_dmactl_test, ::testing::Values(
		dmactl_completion_size_test(env.vfs.size(), 0, 1, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_8B,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_completion_size_test(env.vfs.size(), 0, 1, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_16B,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_completion_size_test(env.vfs.size(), 0, 1, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_32B,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_completion_size_test(env.vfs.size(), 0, 1, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_64B,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_completion_size_test(env.vfs.size(), 0, 10, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_8B,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_completion_size_test(env.vfs.size(), 0, 10, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_16B,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_completion_size_test(env.vfs.size(), 0, 10, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_32B,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_completion_size_test(env.vfs.size(), 0, 10, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_64B,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_completion_size_test(env.vfs.size(), 0, 1, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_64B,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_completion_size_test(env.vfs.size(), 0, 10, xnl_st_c2h_cmpt_desc_size::XNL_ST_C2H_CMPT_DESC_SIZE_64B,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf)
));


INSTANTIATE_TEST_CASE_P(DMACTL020_desc_bypass_test, qdma_dmactl_test, ::testing::Values(
		dmactl_desc_bypass_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_desc_bypass_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_desc_bypass_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host),
		dmactl_desc_bypass_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host)));

INSTANTIATE_TEST_CASE_P(VF_DMACTL020_desc_bypass_test, qdma_dmactl_test, ::testing::Values(
		dmactl_desc_bypass_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_desc_bypass_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_desc_bypass_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_desc_bypass_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));



INSTANTIATE_TEST_CASE_P(DMACTL021_prefetch_test, qdma_dmactl_test, ::testing::Values(
		dmactl_prefetch_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_prefetch_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_prefetch_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host),
		dmactl_prefetch_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host)));


INSTANTIATE_TEST_CASE_P(VF_DMACTL021_prefetch_test, qdma_dmactl_test, ::testing::Values(
		dmactl_prefetch_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_prefetch_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_prefetch_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_prefetch_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));


INSTANTIATE_TEST_CASE_P(DMACTL022_prefetch_bypass_test, qdma_dmactl_test, ::testing::Values(
		dmactl_prefetch_bypass_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_prefetch_bypass_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_prefetch_bypass_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host),
		dmactl_prefetch_bypass_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host)));

INSTANTIATE_TEST_CASE_P(VF_DMACTL022_prefetch_bypass_test, qdma_dmactl_test, ::testing::Values(
		dmactl_prefetch_bypass_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_prefetch_bypass_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_prefetch_bypass_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_prefetch_bypass_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));



INSTANTIATE_TEST_CASE_P(DMACTL023_fetch_credit_test, qdma_dmactl_test, ::testing::Values(
		dmactl_fetch_credit_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_fetch_credit_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_fetch_credit_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host),
		dmactl_fetch_credit_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host)));

INSTANTIATE_TEST_CASE_P(VF_DMACTL023_fetch_credit_test, qdma_dmactl_test, ::testing::Values(
		dmactl_fetch_credit_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_fetch_credit_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_fetch_credit_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_fetch_credit_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));


INSTANTIATE_TEST_CASE_P(DMACTL024_c2h_ovf_chk_dis_test, qdma_dmactl_test, ::testing::Values(
		dmactl_completion_overflow_desc_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_completion_overflow_desc_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_completion_overflow_desc_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host),
		dmactl_completion_overflow_desc_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host)));

INSTANTIATE_TEST_CASE_P(VF_DMACTL024_c2h_ovf_chk_dis_test, qdma_dmactl_test, ::testing::Values(
		dmactl_completion_overflow_desc_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_completion_overflow_desc_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_completion_overflow_desc_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_completion_overflow_desc_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));



INSTANTIATE_TEST_CASE_P(DMACTL025_c2h_udd_en_test, qdma_dmactl_test, ::testing::Values(
		dmactl_user_defined_desc_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_user_defined_desc_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_user_defined_desc_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host),
		dmactl_user_defined_desc_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host)));

INSTANTIATE_TEST_CASE_P(VF_DMACTL025_c2h_udd_en_test, qdma_dmactl_test, ::testing::Values(
		dmactl_user_defined_desc_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_user_defined_desc_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_user_defined_desc_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_user_defined_desc_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));

INSTANTIATE_TEST_CASE_P(DMACTL026_c2h_cmpl_intr_en_test, qdma_dmactl_test, ::testing::Values(
		dmactl_c2h_completion_interrupt_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_c2h_completion_interrupt_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_c2h_completion_interrupt_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host),
		dmactl_c2h_completion_interrupt_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host)));


INSTANTIATE_TEST_CASE_P(VF_DMACTL026_c2h_cmpl_intr_en_test, qdma_dmactl_test, ::testing::Values(
		dmactl_c2h_completion_interrupt_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_c2h_completion_interrupt_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_c2h_completion_interrupt_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_c2h_completion_interrupt_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));


INSTANTIATE_TEST_CASE_P(DMACTL027_dis_cmpl_status_test, qdma_dmactl_test, ::testing::Values(
		dmactl_disable_cmpl_status_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_disable_cmpl_status_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_disable_cmpl_status_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host),
		dmactl_disable_cmpl_status_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host)));

INSTANTIATE_TEST_CASE_P(VF_DMACTL027_dis_cmpl_status_test, qdma_dmactl_test, ::testing::Values(
		dmactl_disable_cmpl_status_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_disable_cmpl_status_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_disable_cmpl_status_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_disable_cmpl_status_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));




INSTANTIATE_TEST_CASE_P(DMACTL028_dis_cmpl_status_acc_test, qdma_dmactl_test, ::testing::Values(
		dmactl_disable_cmpl_status_acc_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_disable_cmpl_status_acc_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_disable_cmpl_status_acc_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host),
		dmactl_disable_cmpl_status_acc_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host)));

INSTANTIATE_TEST_CASE_P(VF_DMACTL028_dis_cmpl_status_acc_test, qdma_dmactl_test, ::testing::Values(
		dmactl_disable_cmpl_status_acc_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_disable_cmpl_status_acc_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_disable_cmpl_status_acc_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_disable_cmpl_status_acc_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));




INSTANTIATE_TEST_CASE_P(DMACTL029_dis_cmpl_status_pend_chk_test, qdma_dmactl_test, ::testing::Values(
		dmactl_disable_cmpl_status_pend_chk_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_disable_cmpl_status_pend_chk_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_disable_cmpl_status_pend_chk_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host),
		dmactl_disable_cmpl_status_pend_chk_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host)));


INSTANTIATE_TEST_CASE_P(VF_DMACTL029_dis_cmpl_status_pend_chk_test, qdma_dmactl_test, ::testing::Values(
		dmactl_disable_cmpl_status_pend_chk_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_disable_cmpl_status_pend_chk_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_disable_cmpl_status_pend_chk_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_disable_cmpl_status_pend_chk_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));



INSTANTIATE_TEST_CASE_P(DMACTL030_dis_cmpl_status_desc_en_test, qdma_dmactl_test, ::testing::Values(
		dmactl_disable_cmpl_status_desc_en_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_disable_cmpl_status_desc_en_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_disable_cmpl_status_desc_en_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host),
		dmactl_disable_cmpl_status_desc_en_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host)));



INSTANTIATE_TEST_CASE_P(VF_DMACTL030_dis_cmpl_status_desc_en_test, qdma_dmactl_test, ::testing::Values(
		dmactl_disable_cmpl_status_desc_en_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_disable_cmpl_status_desc_en_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_disable_cmpl_status_desc_en_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_disable_cmpl_status_desc_en_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));



INSTANTIATE_TEST_CASE_P(DMACTL031_sw_desc_sz_test, qdma_dmactl_test, ::testing::Values(
		dmactl_sw_desc_sz_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_sw_desc_sz_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both),
		dmactl_sw_desc_sz_test(env.pfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host),
		dmactl_sw_desc_sz_test(env.pfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host)));

INSTANTIATE_TEST_CASE_P(VF_DMACTL031_sw_desc_sz_test, qdma_dmactl_test, ::testing::Values(
		dmactl_sw_desc_sz_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_sw_desc_sz_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::both, qdma::instance_ext::type::vf),
		dmactl_sw_desc_sz_test(env.vfs.size(), 0, 1, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf),
		dmactl_sw_desc_sz_test(env.vfs.size(), 0, 10, qdma::queue_ext::mode::streaming,
				qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::vf)));



INSTANTIATE_TEST_CASE_P(DMACTL032_q_dump_test, qdma_dmactl_test, ::testing::Values(
		dmactl_queue_dump_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DUMP | DMACTL_Q_DEL, 0, 1,
				qdma::queue_ext::direction::host_to_card),
		dmactl_queue_dump_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_DUMP | DMACTL_Q_DEL, 0, 10,
				qdma::queue_ext::direction::host_to_card)));


INSTANTIATE_TEST_CASE_P(DMACTL033_q_dump_desc_test, qdma_dmactl_test, ::testing::Values(
		dmactl_queue_dump_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_DUMP | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::direction::host_to_card,qdma::instance_ext::type::pf,
				queue_dump_mode::descriptor, 0, 100),
		dmactl_queue_dump_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_DUMP | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::direction::host_to_card, qdma::instance_ext::type::pf,
				queue_dump_mode::descriptor, 0, 100)));

INSTANTIATE_TEST_CASE_P(DMACTL034_q_dump_cmpt_test, qdma_dmactl_test, ::testing::Values(
		dmactl_queue_dump_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_DUMP | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 1, qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::pf,
				queue_dump_mode::completion, 0, 1),
		dmactl_queue_dump_test(env.pfs.size(), DMACTL_Q_ADD | DMACTL_Q_START | DMACTL_Q_DUMP | DMACTL_Q_STOP | DMACTL_Q_DEL,
				0, 10, qdma::queue_ext::direction::card_to_host, qdma::instance_ext::type::pf,
				queue_dump_mode::completion, 0, 10)));








/*--------------------------------------------------------------------------------------------------
 *
 *				Memory Mapped TEST CASES
 *
 --------------------------------------------------------------------------------------------------*/
struct dmactl_test_params {

	struct dmactl_transfer {
		uint32_t pf = 0;
		uint32_t q = 0;
		uint32_t it = 0;
		uint32_t offset = 0;
		uint32_t size = 0;
		uint32_t qs = 0;
		qdma::device& qdev;

		dmactl_transfer(uint32_t pf_id, uint32_t q_id, uint32_t iterations, uint32_t offs, uint32_t ts, uint32_t numqs, qdma::device& _qdev=env.pfs.front())
		: pf(pf_id), q(q_id), it(iterations), offset(offs), size(ts), qs(numqs),qdev(_qdev) {}
	};

	std::vector<dmactl_transfer> dmactl_transfers;
	qdma::instance_ext::type devtype = qdma::instance_ext::type::pf;
	qdma::queue_ext::config qcfg;

	dmactl_test_params() = default;

	dmactl_test_params(std::vector<dmactl_transfer>&& txs, qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
		: dmactl_transfers(std::move(txs)), qcfg(_qcfg) {}

	dmactl_test_params(std::vector<dmactl_transfer>&& txs, qdma::instance_ext::type dev_type,
			qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
		: dmactl_transfers(std::move(txs)), devtype(dev_type), qcfg(_qcfg) {}
};

class dmactl_mm_test: public testing::TestWithParam<dmactl_test_params> {
public:
 static const auto mode = qdma::queue_ext::mode::memory_mapped;

};

void PrintTo(const dmactl_test_params& tp, std::ostream* os) {
	const auto& txs = tp.dmactl_transfers;

	//only print the ranges (first and last entry)
	if (!txs.empty()) {
		if (tp.devtype == qdma::instance_ext::type::vf)
			*os << "{ vfs=[";
		else
			*os << "{ pfs=[";
		*os << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.front().pf
				<< ":" << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.back().pf << "], ";
		*os << "queues=[" << txs.front().q << ":" << txs.back().q << "], ";
		*os << "iterations=" << txs.front().it << ", ";
		*os << "tx_offset=" << txs.front().offset << ", ";
		*os << "tx_size=" << txs.front().size << ", ";
		*os << "num_of_queues=" << txs.front().qs << " }";
	}
}


static dmactl_test_params dmactl_mm_basic_dma_test(const std::vector<uint32_t> &num_qs_per_pf, uint32_t numqs,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_test_params::dmactl_transfer> transfers;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t tx_cnt = 0;

	for (uint32_t pf_id = 0; pf_id < num_qs_per_pf.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		tx_cnt++;
	}

	transfers.reserve(tx_cnt);

	for (uint32_t pf_id = 0; pf_id < num_qs_per_pf.size(); pf_id++) {

		if (!devlist[pf_id].max_num_queues) {
			continue;
		}

		if(numqs > num_qs_per_pf[pf_id]) {
			transfers.emplace_back(devlist[pf_id].dev_id, 0, 1, 0, 4096,  num_qs_per_pf[pf_id], devlist[pf_id]);
		} else {
			transfers.emplace_back(devlist[pf_id].dev_id, 0, 1, 0, 4096, numqs,devlist[pf_id]);
		}
	}

	return dmactl_test_params { std::move(transfers) , dev_type};
}


static dmactl_test_params dmactl_mm_txsize_test(const std::vector<uint32_t> &num_qs_per_pf, uint32_t numqs,
		uint32_t txsize, uint32_t count, qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_test_params::dmactl_transfer> transfers;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);


	uint32_t tx_cnt = 0;

	for (uint32_t pf_id = 0; pf_id < num_qs_per_pf.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		tx_cnt++;
	}

		transfers.reserve(tx_cnt);
	for (uint32_t pf_id = 0; pf_id < num_qs_per_pf.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}

		if(numqs > num_qs_per_pf[pf_id]) {
			if(dev_type == qdma::instance_ext::type::pf) {
				transfers.emplace_back(devlist[pf_id].dev_id, 0, count, 0, txsize,
					env.pfs[pf_id].max_num_queues,devlist[pf_id]);
			} else {
				transfers.emplace_back(devlist[pf_id].dev_id, 0, count, 0, txsize,
					env.vfs[pf_id].max_num_queues,devlist[pf_id]);
			}		
		} else {
			transfers.emplace_back(devlist[pf_id].dev_id, 0, count, 0, txsize,
					numqs,devlist[pf_id]);
		}
	}

	return dmactl_test_params { std::move(transfers) , dev_type};
}



static dmactl_test_params dmactl_mm_txoffset_test(
		const std::vector<uint32_t> &num_qs_per_pf, uint32_t numqs,uint32_t txsize,
		 uint32_t txoffset,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_test_params::dmactl_transfer> transfers;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	uint32_t tx_cnt = 0;

	for (uint32_t pf_id = 0; pf_id < num_qs_per_pf.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		tx_cnt++;
	}

	transfers.reserve(tx_cnt);

	for (uint32_t pf_id = 0; pf_id < num_qs_per_pf.size(); pf_id++) {

		if (!devlist[pf_id].max_num_queues) {
			continue;
		}

		if(numqs > num_qs_per_pf[pf_id]) {
			if(dev_type == qdma::instance_ext::type::pf) {
				transfers.emplace_back(devlist[pf_id].dev_id, 0, 1, txoffset, txsize,
					env.pfs[pf_id].max_num_queues,devlist[pf_id]);
			} else {
				transfers.emplace_back(devlist[pf_id].dev_id, 0, 1, txoffset, txsize,
					env.vfs[pf_id].max_num_queues,devlist[pf_id]);
			}
		} else {
			transfers.emplace_back(devlist[pf_id].dev_id, 0, 1, txoffset, txsize,
					numqs,devlist[pf_id]);
		}
	}
	return dmactl_test_params { std::move(transfers) , dev_type};
}



static dmactl_test_params dmactl_mm_ringsz_test(const uint32_t ring_size_idx,
		const uint32_t tx_size, const uint32_t count, const uint32_t numqs,
		qdma::instance_ext::type dev_type=qdma::instance::type::pf) {

	std::vector<dmactl_test_params::dmactl_transfer> transfers;
	qdma::queue_ext::config qcfg;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	uint32_t tx_cnt = 0;

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		tx_cnt++;
	}

	transfers.reserve(tx_cnt);


	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		if(numqs > devlist[pf_id].max_num_queues)
			transfers.emplace_back(devlist[pf_id].dev_id, 0, count, 0, tx_size, devlist[pf_id].max_num_queues,
				devlist[pf_id]);
		else
			transfers.emplace_back(devlist[pf_id].dev_id, 0, count, 0, tx_size, numqs,
							devlist[pf_id]);
	}

	qcfg.idx_rngsz = ring_size_idx;

	return dmactl_test_params { std::move(transfers), dev_type, qcfg };
}




static dmactl_test_params dmactl_mm_descBypass_test(
		const std::vector<uint32_t> &num_qs_per_pf, uint32_t numqs,
		uint32_t txsize, uint32_t count, qdma::instance_ext::type dev_type=
				qdma::instance_ext::type::pf) {

	std::vector<dmactl_test_params::dmactl_transfer> transfers;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;

	uint32_t tx_cnt = 0;

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		tx_cnt++;
	}

	transfers.reserve(tx_cnt);

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;
		if(numqs > devlist[pf_id].max_num_queues)
			transfers.emplace_back(devlist[pf_id].dev_id, 0, count, 0, txsize, devlist[pf_id].max_num_queues,
					devlist[pf_id]);
		else
			transfers.emplace_back(devlist[pf_id].dev_id, 0, count, 0, txsize, numqs,
						devlist[pf_id]);
	}

	qcfg.desc_bypass = true;

	return dmactl_test_params { std::move(transfers), dev_type, qcfg };

}





TEST_P(dmactl_mm_test, dma_h2c_only) {
	const auto& tp = GetParam();
	const auto dir = qdma::queue_ext::direction::host_to_card;
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);


	ASSERT_FALSE(devlist.empty());


	for (const auto& tx : tp.dmactl_transfers) {

		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));

		if(validate_test_case(devlist, tx.pf, tp.qcfg)) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
		continue;
		}


		dmactl_regwrite(tx.pf, tp.devtype,  2, 0x0, 0xffff);
		dmactl_regwrite(tx.pf, tp.devtype,  2, 0x8, 0x0);

		if(tp.qcfg.desc_bypass) {
			dmactl_regwrite(tx.pf, tp.devtype,  2, 0x90, 0x1);
		} else {
			dmactl_regwrite(tx.pf, tp.devtype,  2, 0x90, 0x0);
		}
		ASSERT_EQ(SUCCESS, dmactl_qadd(tp.devtype, tx.pf, tx.q, tx.qs,
				qdma::queue_ext::mode::memory_mapped, dir));
		ASSERT_EQ(SUCCESS, dmactl_qstart(tp.devtype, tx.pf, tx.q, tx.qs, tp.qcfg,
				dir));

		for(uint32_t i = 0; i < tx.qs; i++) {
			ASSERT_EQ(SUCCESS, dma_transfers(1, tp.devtype, tx.pf, qdma::queue_ext::mode::memory_mapped,
					tx.q + i, tx.offset, tx.size, tx.it));
		}

		ASSERT_EQ(SUCCESS, dmactl_qstop(tp.devtype, tx.pf, tx.q, tx.qs, dir));
		ASSERT_EQ(SUCCESS, dmactl_qdel(tp.devtype, tx.pf, tx.q, tx.qs, dir));
	}
}


TEST_P(dmactl_mm_test, dma_c2h_only) {
	const auto& tp = GetParam();
	const auto dir = qdma::queue_ext::direction::card_to_host;
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);


	ASSERT_FALSE(devlist.empty());


	for (const auto& tx : tp.dmactl_transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));
	    if(validate_test_case(devlist, tx.pf, tp.qcfg)) {
	        //GTEST_SKIP();
	        std::cout << "Invalid Test Case" << std::endl;
	        continue;
	    }
		dmactl_regwrite(tx.pf, tp.devtype,  2, 0x0, 0xffff);
		dmactl_regwrite(tx.pf, tp.devtype,  2, 0x8, 0x0);
		if(tp.qcfg.desc_bypass) {
			dmactl_regwrite(tx.pf, tp.devtype,  2, 0x90, 0x2);
		} else {
			dmactl_regwrite(tx.pf, tp.devtype,  2, 0x90, 0x0);
		}

		ASSERT_EQ(SUCCESS, dmactl_qadd(tp.devtype, tx.pf, tx.q, tx.qs,
				qdma::queue_ext::mode::memory_mapped, dir));
		ASSERT_EQ(SUCCESS, dmactl_qstart(tp.devtype, tx.pf, tx.q, tx.qs, tp.qcfg,
				dir));

		for(uint32_t i = 0; i < tx.qs; i++) {
			ASSERT_EQ(SUCCESS, dma_transfers(0, tp.devtype, tx.pf, qdma::queue_ext::mode::memory_mapped,
					tx.q + i, tx.offset, tx.size, tx.it));
		}
		ASSERT_EQ(SUCCESS, dmactl_qstop(tp.devtype, tx.pf, tx.q, tx.qs, dir));
		ASSERT_EQ(SUCCESS, dmactl_qdel(tp.devtype, tx.pf, tx.q, tx.qs, dir));
	}

}

TEST_P(dmactl_mm_test, dma_h2c_c2h) {

	const auto& tp = GetParam();

	const auto dir = qdma::queue_ext::direction::both;
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);


	ASSERT_FALSE(devlist.empty());

	for (const auto& tx : tp.dmactl_transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));

	    if(validate_test_case(devlist, tx.pf, tp.qcfg)) {
	        //GTEST_SKIP();
	        std::cout << "Invalid Test Case" << std::endl;
	        continue;
	    }

		dmactl_regwrite(tx.pf, tp.devtype,  2, 0x0, 0xffff);
		dmactl_regwrite(tx.pf, tp.devtype,  2, 0x8, 0x0);

		if(tp.qcfg.desc_bypass)
			dmactl_regwrite(tx.pf, tp.devtype,  2, 0x90, 0x3);
		else
			dmactl_regwrite(tx.pf, tp.devtype,  2, 0x90, 0x0);


		ASSERT_EQ(SUCCESS, dmactl_qadd(tp.devtype, tx.pf, tx.q, tx.qs,
				qdma::queue_ext::mode::memory_mapped, dir));
		ASSERT_EQ(SUCCESS, dmactl_qstart(tp.devtype, tx.pf, tx.q, tx.qs, tp.qcfg,
				dir));
		for(uint32_t i = 0; i < tx.qs; i++) {
			ASSERT_EQ(SUCCESS, dma_transfers(1, tp.devtype, tx.pf, qdma::queue_ext::mode::memory_mapped,
					tx.q + i, tx.offset, tx.size, tx.it));
			ASSERT_EQ(SUCCESS, dma_transfers(0, tp.devtype, tx.pf, qdma::queue_ext::mode::memory_mapped,
					tx.q + i, tx.offset, tx.size, tx.it));
		}
		ASSERT_EQ(SUCCESS, dmactl_qstop(tp.devtype, tx.pf, tx.q, tx.qs, dir));
		ASSERT_EQ(SUCCESS, dmactl_qdel(tp.devtype, tx.pf, tx.q, tx.qs, dir));
	}
}



INSTANTIATE_TEST_CASE_P(DMACTLMM001_basic_dma_test, dmactl_mm_test, ::testing::Values(
		dmactl_mm_basic_dma_test(get_num_qs_per_pf(env.pfs), 1),
		dmactl_mm_basic_dma_test(get_num_qs_per_pf(env.pfs), 4)
));




INSTANTIATE_TEST_CASE_P(DMACTLMM002_tx_size_test, dmactl_mm_test, ::testing::Values(
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.pfs), 1, 4096, 0),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.pfs), 1, 8192, 0),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.pfs), 1, 4096, 10),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.pfs), 1, 8192, 10),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.pfs), 10, 4096, 0),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.pfs), 10, 8192, 0),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.pfs), 10, 4096, 10),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.pfs), 10, 8192, 10)
));

INSTANTIATE_TEST_CASE_P(VF_DMACTLMM002_tx_size_test, dmactl_mm_test, ::testing::Values(
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.vfs), 1, 4096, 0, qdma::instance_ext::type::vf),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.vfs), 1, 8192, 0, qdma::instance_ext::type::vf),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.vfs), 1, 4096, 10, qdma::instance_ext::type::vf),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.vfs), 1, 8192, 10, qdma::instance_ext::type::vf),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.vfs), 10, 4096, 0, qdma::instance_ext::type::vf),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.vfs), 10, 8192, 0, qdma::instance_ext::type::vf),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.vfs), 10, 4096, 10, qdma::instance_ext::type::vf),
		dmactl_mm_txsize_test(get_num_qs_per_pf(env.vfs), 10, 8192, 10, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(DMACTLMM003_tx_offset_test, dmactl_mm_test, ::testing::Values(
		dmactl_mm_txoffset_test(get_num_qs_per_pf(env.pfs), 1, 4096, 0),
		dmactl_mm_txoffset_test(get_num_qs_per_pf(env.pfs), 1, 4096, 10),
		dmactl_mm_txoffset_test(get_num_qs_per_pf(env.pfs), 10, 4096, 0),
		dmactl_mm_txoffset_test(get_num_qs_per_pf(env.pfs), 10, 4096, 10)
));


INSTANTIATE_TEST_CASE_P(VF_DMACTLMM003_tx_offset_test, dmactl_mm_test, ::testing::Values(
		dmactl_mm_txoffset_test(get_num_qs_per_pf(env.vfs), 1, 4096, 0, qdma::instance_ext::type::vf ),
		dmactl_mm_txoffset_test(get_num_qs_per_pf(env.vfs), 1, 4096, 10, qdma::instance_ext::type::vf),
		dmactl_mm_txoffset_test(get_num_qs_per_pf(env.vfs), 10, 4096, 0, qdma::instance_ext::type::vf),
		dmactl_mm_txoffset_test(get_num_qs_per_pf(env.vfs), 10, 4096, 10, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(DMACTLMM004_ring_size_test, dmactl_mm_test, ::testing::Values(
		dmactl_mm_ringsz_test(0, 4096, 1000, 1),
		dmactl_mm_ringsz_test(0, 4096, 1000, 10),
		dmactl_mm_ringsz_test(1, 4096, 1000, 1),
		dmactl_mm_ringsz_test(2, 4096, 1000, 1)
));


INSTANTIATE_TEST_CASE_P(VF_DMACTLMM004_ring_size_test, dmactl_mm_test, ::testing::Values(
		dmactl_mm_ringsz_test(0, 4096, 1000, 1, qdma::instance_ext::type::vf),
		dmactl_mm_ringsz_test(0, 4096, 1000, 10, qdma::instance_ext::type::vf),
		dmactl_mm_ringsz_test(1, 4096, 1000, 1, qdma::instance_ext::type::vf),
		dmactl_mm_ringsz_test(2, 4096, 1000, 1, qdma::instance_ext::type::vf)
));

INSTANTIATE_TEST_CASE_P(DMACTLMM005_descbypass_test, dmactl_mm_test, ::testing::Values(
		dmactl_mm_descBypass_test(get_num_qs_per_pf(env.pfs), 1, 4096, 0),
		dmactl_mm_descBypass_test(get_num_qs_per_pf(env.pfs), 10, 4096, 0)
));


INSTANTIATE_TEST_CASE_P(VF_DMACTLMM005_descbypass_test, dmactl_mm_test, ::testing::Values(
		dmactl_mm_descBypass_test(get_num_qs_per_pf(env.vfs), 1, 4096, 0, qdma::instance_ext::type::vf),
		dmactl_mm_descBypass_test(get_num_qs_per_pf(env.vfs), 10, 4096, 0, qdma::instance_ext::type::vf)
));





/*---------------------------------------------------------------------------------------------
 *
 *				STREAMING TEST CASES
 *
 ---------------------------------------------------------------------------------------------*/

struct dmactl_st_test_params {

	struct dmactl_st_transfer {
		uint32_t pf = 0;
		uint32_t q = 1;
		uint32_t it = 0;
		uint32_t packet_size = 0;
		uint32_t num_packets = 0;
		uint32_t qs = 0;
		qdma::device& qdev;
		dmactl_st_transfer(uint32_t pf_id, uint32_t q_id, uint32_t iteration,
				uint32_t ps, uint32_t np, uint32_t numqs,
				qdma::device& _qdev=env.pfs.front())
		: pf(pf_id), q(q_id), it(iteration), packet_size(ps), num_packets(np),
		  qs(numqs), qdev(_qdev) {}
	};

	std::vector<dmactl_st_transfer> transfers;
	qdma::instance_ext::type devtype = qdma::instance_ext::type::pf;
	qdma::queue_ext::config qcfg;

	dmactl_st_test_params() = default;
	dmactl_st_test_params(std::vector<dmactl_st_transfer>&& txs,
			qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
	: transfers(std::move(txs)), qcfg(_qcfg) {}

	dmactl_st_test_params(std::vector<dmactl_st_transfer>&& txs,
			qdma::instance_ext::type dev_type,
			qdma::queue_ext::config _qcfg = qdma::queue_ext::config())
		: transfers(std::move(txs)), devtype(dev_type), qcfg(_qcfg) {}
};

void PrintTo(const dmactl_st_test_params& tp, std::ostream* os) {

    //only print the ranges (first and last entry)
    const auto& txs = tp.transfers;
    if (!txs.empty()) {
		if (tp.devtype == qdma::instance_ext::type::vf)
			*os << "{ vfs=[";
		else
			*os << "{ pfs=[";
		*os << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.front().pf
			<< ":" << std::hex << std::uppercase << std::setw(5) << std::setfill('0') << txs.back().pf << "], ";
        *os << "queues=[" << txs.front().q << ":" << txs.back().q << "], ";
        *os << "iterations=" << txs.front().it << ", ";
        *os << "packet_size=" << txs.front().packet_size << ", ";
        *os << "num_packets=" << txs.front().num_packets << ", ";
        *os << "num_of_queues=" << txs.front().qs << " }";
    }
}



class dmactl_st_c2h_test: public testing::TestWithParam<dmactl_st_test_params> {

public:
	void dmactl_test_c2h_only();
	static const auto mode = qdma::queue_ext::mode::streaming;
};


class dmactl_st_test: public dmactl_st_c2h_test {
public:
};




static dmactl_st_test_params dmactl_completion_entry_size(
		const xnl_st_c2h_cmpt_desc_size cmptsz,
		const uint32_t numqs, qdma::instance_ext::type dev_type=
				qdma::instance_ext::type::pf) {


	std::vector<dmactl_st_test_params::dmactl_st_transfer> transfers;
	qdma::queue_ext::config qcfg;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	uint32_t tx_cnt = 0;

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		tx_cnt++;
	}

	transfers.reserve(tx_cnt);

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		if(numqs > devlist[pf_id].max_num_queues)
			transfers.emplace_back(devlist[pf_id].dev_id, 0, 1, 4096, 1, devlist[pf_id].max_num_queues,
							devlist[pf_id]);
		else
			transfers.emplace_back(devlist[pf_id].dev_id, 0, 1, 4096, 1, numqs,
				devlist[pf_id]);
	}

	qcfg.cmptsz = cmptsz;

	return dmactl_st_test_params { std::move(transfers), dev_type, qcfg };

}


static dmactl_st_test_params dmactl_desc_pfetch_test(const uint32_t packet_size,
		const uint32_t numqs,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf,
		const uint32_t num_packets = 1) {

	std::vector<dmactl_st_test_params::dmactl_st_transfer> transfers;
	qdma::queue_ext::config qcfg;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);

	std::default_random_engine rne(time(0));
	uint32_t tx_cnt = 0;

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		tx_cnt++;
	}

	transfers.reserve(tx_cnt);

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;

		std::uniform_int_distribution<uint32_t> rng_q(0,
			devlist[pf_id].max_num_queues < numqs ?
			devlist[pf_id].max_num_queues : devlist[pf_id].max_num_queues - numqs);

		const auto qid = rng_q(rne);

		if(numqs > devlist[pf_id].max_num_queues)
			transfers.emplace_back(devlist[pf_id].dev_id, qid, 1, 4096, 1,
					devlist[pf_id].max_num_queues, devlist[pf_id]);
		else
			transfers.emplace_back(devlist[pf_id].dev_id, qid, 1, 4096, 1,
					numqs, devlist[pf_id]);
	}

	qcfg.prefetch = true;

	return dmactl_st_test_params { std::move(transfers), dev_type, qcfg };

}






static dmactl_st_test_params dmactl_ovf_chk_dis_test(const uint16_t idx_ring_size,
		uint32_t numqs, const uint32_t packet_size, const uint32_t num_transfers,
		const uint32_t num_packets,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_st_test_params::dmactl_st_transfer> transfers;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;

	std::default_random_engine rne(env.random_seed);
	uint32_t tx_cnt = 0;

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		tx_cnt++;
	}

	transfers.reserve(tx_cnt);

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;

		if (numqs > devlist[pf_id].max_num_queues)
			numqs = devlist[pf_id].max_num_queues;

		std::uniform_int_distribution<uint32_t> rng_q(0,
				devlist[pf_id].max_num_queues < numqs ?
				devlist[pf_id].max_num_queues : devlist[pf_id].max_num_queues - numqs);


		const auto qid = rng_q(rne);
		if(numqs > devlist[pf_id].max_num_queues)
		transfers.emplace_back(devlist[pf_id].dev_id, qid, num_transfers, packet_size,
				num_packets, devlist[pf_id].max_num_queues, devlist[pf_id]);
		else
			transfers.emplace_back(devlist[pf_id].dev_id, qid, num_transfers, packet_size,
				num_packets, numqs, devlist[pf_id]);
	}

	qcfg.idx_rngsz = idx_ring_size;
	qcfg.c2h_ovf_chk_dis = true;


	return dmactl_st_test_params { std::move(transfers), dev_type, qcfg };

}




static dmactl_st_test_params dmactl_buf_size_test(const uint32_t idx_buf_size,
		const uint32_t packet_size, const uint32_t num_transfers, const uint32_t numqs,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_st_test_params::dmactl_st_transfer> transfers;
	qdma::queue_ext::config qcfg;

	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	std::default_random_engine rne(time(0));
	uint32_t tx_cnt = 0;

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		tx_cnt++;
	}

	transfers.reserve(tx_cnt);

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;

		std::uniform_int_distribution<uint32_t> rng_q(0,
				devlist[pf_id].max_num_queues < numqs ?
				devlist[pf_id].max_num_queues : devlist[pf_id].max_num_queues - numqs);

		const auto qid = rng_q(rne);
		/*dmactl_st_transfer(uint32_t pf_id, uint32_t q_id, uint32_t iteration,
		 * uint32_t ps, uint32_t np, uint32_t numqs,
		 * qdma::device& _qdev=env.pfs.front())*/
		if(dev_type == qdma::instance_ext::type::pf) {
		if(devlist[pf_id].max_num_queues < numqs) {
			transfers.emplace_back(env.pfs[pf_id].dev_id, qid, num_transfers, packet_size,
					1, devlist[pf_id].max_num_queues, devlist[pf_id]);
		}
		else
			transfers.emplace_back(env.pfs[pf_id].dev_id, qid, num_transfers, packet_size,
					1, numqs, devlist[pf_id]);
		} else {
			if(devlist[pf_id].max_num_queues < numqs) {
				transfers.emplace_back(env.vfs[pf_id].dev_id, qid, num_transfers, packet_size,
					1, devlist[pf_id].max_num_queues, devlist[pf_id]);
			}
			else
				transfers.emplace_back(env.vfs[pf_id].dev_id, qid, num_transfers, packet_size,
					1, numqs, devlist[pf_id]);

		}


	}

	qcfg.idx_bufsz = idx_buf_size;


	return dmactl_st_test_params { std::move(transfers), dev_type, qcfg };

}




static dmactl_st_test_params dmactl_tmr_cnt_test(const uint32_t idx_timer_cnt,
		const uint32_t packet_size, const uint32_t num_transfers, const uint32_t numqs,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {

	std::vector<dmactl_st_test_params::dmactl_st_transfer> transfers;
	qdma::queue_ext::config qcfg;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	std::default_random_engine rne(time(0));
	uint32_t tx_cnt = 0;

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		tx_cnt++;
	}

	transfers.reserve(tx_cnt);


	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;
		std::uniform_int_distribution<uint32_t> rng_q(0,
					devlist[pf_id].max_num_queues < numqs ?
					devlist[pf_id].max_num_queues : devlist[pf_id].max_num_queues - numqs);	
		const auto qid = rng_q(rne);

		if(devlist[pf_id].max_num_queues < numqs)
			transfers.emplace_back(devlist[pf_id].dev_id, qid, num_transfers, packet_size, 1,
					devlist[pf_id].max_num_queues, devlist[pf_id]);
		else
			transfers.emplace_back(devlist[pf_id].dev_id, qid, num_transfers, packet_size, 1, numqs, devlist[pf_id]);
	}

	qcfg.idx_tmr = idx_timer_cnt;
	qcfg.trigmode  = qdma::queue_ext::c2h_wrb_intr_trigmode::usr_tmr;

	return dmactl_st_test_params { std::move(transfers), dev_type, qcfg };
}


static dmactl_st_test_params ring_size_test(const uint32_t ring_size,
		const uint32_t packet_size, const uint32_t num_transfers, const uint32_t numqs,
		qdma::instance_ext::type dev_type=qdma::instance_ext::type::pf) {
	std::vector<dmactl_st_test_params::dmactl_st_transfer> transfers;
	std::vector<qdma::device> &devlist = env.get_dev_list(dev_type);
	qdma::queue_ext::config qcfg;

	uint32_t tx_cnt = 0;

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues) {
			continue;
		}
		tx_cnt++;
	}

	transfers.reserve(tx_cnt);

	for (uint32_t pf_id = 0; pf_id < devlist.size(); pf_id++) {
		if (!devlist[pf_id].max_num_queues)
			continue;
		if(devlist[pf_id].max_num_queues < numqs)
			transfers.emplace_back(devlist[pf_id].dev_id, 0, num_transfers, packet_size,
							1, devlist[pf_id].max_num_queues,devlist[pf_id]);
		else
			transfers.emplace_back(devlist[pf_id].dev_id, 0, num_transfers, packet_size,
				1, numqs,devlist[pf_id]);
	}

	qcfg.idx_rngsz = ring_size;

	return dmactl_st_test_params { std::move(transfers), dev_type, qcfg };
}




void dmactl_st_c2h_test::dmactl_test_c2h_only() {

	const auto& tp = GetParam();
	const auto dir = qdma::queue_ext::direction::card_to_host;
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());

	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));
		if(validate_test_case(devlist, tx.pf, tp.qcfg)) {
			//GTEST_SKIP();
			std::cout << "Invalid Test Case" << std::endl;
			continue;
		}

	    /*dmactl qdma01000 q add idx 0 mode st dir c2h
		  dmactl qdma01000 q start idx 0 dir c2h
		  dmactl qdma01000 reg write bar 2 0x0 16384
		  dmactl qdma01000 reg write bar 2 0x4 4096
		  dmactl qdma01000 reg write bar 2 0x20 2
		  dmactl qdma01000 reg write bar 2 0x08 2
		  dma-from-device -d /dev/qdma01000-ST-0 -s 4096
		  dmactl qdma01000 q stop idx 0 dir c2h
		  dmactl qdma01000 q del idx 0 dir c2h*/

		ASSERT_EQ(SUCCESS, dmactl_qadd(tp.devtype, tx.pf, tx.q, tx.qs, qdma::queue_ext::mode::streaming, dir));
		ASSERT_EQ(SUCCESS, dmactl_qstart(tp.devtype, tx.pf, tx.q, tx.qs, tp.qcfg, dir));

		for(uint32_t i = 0; i < tx.it; i++) {
			for(uint32_t i = 0; i < tx.qs; i++) {
				auto hw_qid = get_hw_qid(tx.pf, tx.q + i, devlist);
				dmactl_regwrite(tx.pf, tp.devtype,  2, 0x0, hw_qid);
				dmactl_regwrite(tx.pf, tp.devtype,  2, 0x4, tx.packet_size);
				dmactl_regwrite(tx.pf, tp.devtype,  2, 0x20, tx.num_packets);
				dmactl_regwrite(tx.pf, tp.devtype,  2, 0x8, 2);
				ASSERT_LE(SUCCESS,dma_transfers(0, tp.devtype, tx.pf, qdma::queue_ext::mode::streaming, tx.q + i, 0, tx.packet_size, tx.num_packets));
			}
		}
		ASSERT_EQ(SUCCESS, dmactl_qstop(tp.devtype, tx.pf, tx.q, tx.qs, dir));
		ASSERT_EQ(SUCCESS, dmactl_qdel(tp.devtype, tx.pf, tx.q, tx.qs, dir));
	}

}



TEST_P(dmactl_st_c2h_test, c2h_only) {
	ASSERT_NO_FATAL_FAILURE(dmactl_test_c2h_only());
}


TEST_P(dmactl_st_test, c2h_only) {
	ASSERT_NO_FATAL_FAILURE(dmactl_test_c2h_only());
}

TEST_P(dmactl_st_test, h2c_only) {

	const auto& tp = GetParam();
	const auto dir = qdma::queue_ext::direction::host_to_card;
	std::vector<qdma::device> &devlist = env.get_dev_list(tp.devtype);
	ASSERT_FALSE(devlist.empty());
	for (const auto& tx : tp.transfers) {
		SCOPED_TRACE("pf=" + int_to_hex(tx.pf));
		SCOPED_TRACE("queue=" + std::to_string(tx.q));

	    if(validate_test_case(devlist, tx.pf, tp.qcfg)){
	        //GTEST_SKIP();
	        std::cout << "Invalid Test Case" << std::endl;
	        continue;
	    }
		ASSERT_EQ(SUCCESS, dmactl_qadd(tp.devtype, tx.pf, tx.q, tx.qs, qdma::queue_ext::mode::streaming, dir));
		ASSERT_EQ(SUCCESS, dmactl_qstart(tp.devtype, tx.pf, tx.q, tx.qs, tp.qcfg, dir));
		for(uint32_t i = 0; i < tx.qs; i++) {
			/* 	dmactl qdma0 reg write bar $usr_bar 0x0C 0x1 # clear h2c Match register.
				dma-to-device -d $dev_h2c -f $infile -o $hst_adr1 -s $size*/
			dmactl_regwrite(tx.pf, tp.devtype,  2, 0xc, 1);
			ASSERT_LE(SUCCESS,dma_transfers(1, tp.devtype, tx.pf, qdma::queue_ext::mode::streaming, tx.q + i, 0, tx.packet_size, tx.it));
		}
		ASSERT_EQ(SUCCESS, dmactl_qstop(tp.devtype, tx.pf, tx.q, tx.qs, dir));
		ASSERT_EQ(SUCCESS, dmactl_qdel(tp.devtype, tx.pf, tx.q, tx.qs, dir));
	}
}




INSTANTIATE_TEST_CASE_P(DMACTLST001_c2h_tmr_cnt, dmactl_st_c2h_test, ::testing::Values(
	dmactl_tmr_cnt_test(0, 4_kB - 1 ,1, 1),
	dmactl_tmr_cnt_test(0, 4_kB - 1 ,1, 10)));

INSTANTIATE_TEST_CASE_P(VF_DMACTLST001_c2h_tmr_cnt, dmactl_st_c2h_test, ::testing::Values(
	dmactl_tmr_cnt_test(0, 4_kB - 1 ,1, 1, qdma::instance_ext::type::vf),
	dmactl_tmr_cnt_test(0, 4_kB - 1 ,1, 10, qdma::instance_ext::type::vf)));

INSTANTIATE_TEST_CASE_P(DMACTLST002_ring_sizes, dmactl_st_c2h_test, ::testing::Values(
		ring_size_test(0, 4_kB ,1000, 1)));

INSTANTIATE_TEST_CASE_P(VF_DMACTLST002_ring_sizes, dmactl_st_c2h_test, ::testing::Values(
		ring_size_test(0, 4_kB ,1000, 1, qdma::instance_ext::type::vf)));

INSTANTIATE_TEST_CASE_P(DMACTLST003_c2h_buf_sz, dmactl_st_c2h_test, ::testing::Values(
	dmactl_buf_size_test(1, 1_kB ,1, 1)));

INSTANTIATE_TEST_CASE_P(VF_DMACTLST003_c2h_buf_sz, dmactl_st_c2h_test, ::testing::Values(
	dmactl_buf_size_test(1, 1_kB ,1, 1, qdma::instance_ext::type::vf)));

INSTANTIATE_TEST_CASE_P(DMACTLST004_ovf_chk_dis, dmactl_st_c2h_test, ::testing::Values(
	dmactl_ovf_chk_dis_test(2, 5, 4_kB ,50, 60)));

INSTANTIATE_TEST_CASE_P(VF_DMACTLST004_ovf_chk_dis, dmactl_st_c2h_test, ::testing::Values(
	dmactl_ovf_chk_dis_test(2, 5, 4_kB ,50, 60, qdma::instance_ext::type::vf)));

INSTANTIATE_TEST_CASE_P(DMACTLST005_completion_entry_size, dmactl_st_c2h_test, ::testing::Values(
		dmactl_completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_8B, 1)));

INSTANTIATE_TEST_CASE_P(VF_DMACTLST005_completion_entry_size, dmactl_st_c2h_test, ::testing::Values(
		dmactl_completion_entry_size(XNL_ST_C2H_CMPT_DESC_SIZE_8B, 1, qdma::instance_ext::type::vf)));

INSTANTIATE_TEST_CASE_P(DMACTLST006_desc_pfetch, dmactl_st_c2h_test, ::testing::Values(
	dmactl_desc_pfetch_test(4_kB, 1)));
