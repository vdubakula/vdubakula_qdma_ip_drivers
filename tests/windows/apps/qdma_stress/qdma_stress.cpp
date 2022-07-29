/*
-- (c) Copyright 2018-2019 Xilinx, Inc. All rights reserved.
--
-- This file contains confidential and proprietary information
-- of Xilinx, Inc. and is protected under U.S. and
-- international copyright and other intellectual property
-- laws.
--
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a Valid license issued to you by
-- Xilinx, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) Xilinx shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of Data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or Xilinx had been advised of the
-- possibility of the same.
--
-- CRITICAL APPLICATIONS
-- Xilinx products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of Xilinx products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
--
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
-------------------------------------------------------------------------------
--
-- Vendor		  : Xilinx
-- Revision		  : $Revision: #5 $
-- Date			  : $DateTime: 2020/10/16 09:44:57 $
-- Last Author	  : $Author: pprerepa $
--
-------------------------------------------------------------------------------
-- Description :
-- This file is part of the Xilinx DMA IP user space application for Windows.
--
-------------------------------------------------------------------------------
*/
#include <time.h>

#include "qdma_stress.hpp"
#include "version.h"

#define MAX_DATA_GEN_LIMIT 65536

enum class q_distribution {
	BOTH_MM_ST = 0,
	MM_ONLY,
	ST_ONLY
};

struct q_list {
	unsigned short pf_no;
	unsigned short q_id;
	unsigned long offset;
	unsigned long max_pack_sz;
};

struct thread_params {
	HANDLE	handle;
	q_list	q_info;
	unsigned long run_time;
	unsigned long xfer_cnt;
	size_t total_xfer_size;
};

#define MAX_BUFF_MM_SIZE	   512

unsigned short no_of_pfs;
unsigned short no_of_qs_per_pf;
unsigned short total_qs = 0;
unsigned int no_q_mm = 0;
unsigned int no_q_st = 0;
q_list *mm_q_list = NULL;
q_list *st_q_list = NULL;
struct thread_params *mm_th_details = NULL;
struct thread_params *st_h2c_th_details = NULL;
struct thread_params *st_c2h_th_details = NULL;
q_distribution q_dist = q_distribution::BOTH_MM_ST;
std::vector<device_details> dev_details;
LARGE_INTEGER g_freq;
HANDLE st_h2c_mutex = INVALID_HANDLE_VALUE;
HANDLE st_c2h_mutex = INVALID_HANDLE_VALUE;
LARGE_INTEGER start_time;

void init_queue_distribution(void)
{
	unsigned long per_q_mm_pack_sz = 0;
	unsigned long total_mm_bram_sz = 512 * 1024;
	unsigned short no_mm_q_pf = 0;
	unsigned short no_st_q_pf = 0;

	if (q_dist == q_distribution::BOTH_MM_ST) {
		no_q_mm = total_qs / 2;
		no_q_st = no_q_mm;
		no_mm_q_pf = no_of_qs_per_pf / 2;
		no_st_q_pf = no_mm_q_pf;
	}
	else if (q_dist == q_distribution::MM_ONLY) {
		no_q_mm = total_qs;
		no_q_st = 0;

		no_mm_q_pf = no_of_qs_per_pf;
		no_st_q_pf = 0;
	}
	else if (q_dist == q_distribution::ST_ONLY) {
		no_q_st = total_qs;
		no_q_mm = 0;

		no_mm_q_pf = 0;
		no_st_q_pf = no_of_qs_per_pf;
	}

	if (no_q_mm) {
		per_q_mm_pack_sz = total_mm_bram_sz / no_q_mm;

		mm_q_list = (q_list *)malloc(no_q_mm * sizeof(q_list));
		mm_th_details = (struct thread_params *)malloc(no_q_mm * sizeof(struct thread_params));

		for (unsigned short pf = 0; pf < no_of_pfs; pf++) {
			for (unsigned short qid = 0; qid < no_mm_q_pf; qid++) {
				auto index = (pf * no_mm_q_pf) + qid;
				if (q_dist == q_distribution::BOTH_MM_ST) {
					mm_q_list[index].pf_no = pf;
					mm_q_list[index].q_id = (qid * 2);
				}
				else {
					mm_q_list[index].pf_no = pf;
					mm_q_list[index].q_id = qid;
				}
				mm_q_list[index].offset = index * per_q_mm_pack_sz;
				mm_q_list[index].max_pack_sz = per_q_mm_pack_sz;

				mm_th_details[index].q_info = mm_q_list[index];
				//printf("MM:\tPF:\t%d\tQID:\t%d\n", mm_q_list[index].pf_no, mm_q_list[index].q_id);
			}
		}
	}
	if (no_q_st) {
		st_q_list = (q_list *)malloc(no_q_st * sizeof(q_list));
		st_h2c_th_details = (struct thread_params *)malloc(no_q_st * sizeof(struct thread_params));
		st_c2h_th_details = (struct thread_params *)malloc(no_q_st * sizeof(struct thread_params));

		for (unsigned short pf = 0; pf < no_of_pfs; pf++) {
			for (unsigned short qid = 0; qid < no_st_q_pf; qid++) {
				auto index = (pf * no_st_q_pf) + qid;
				if (q_dist == q_distribution::BOTH_MM_ST) {
					st_q_list[index].pf_no = pf;
					st_q_list[index].q_id = ((qid * 2) + 1);
				}
				else {
					st_q_list[index].pf_no = pf;
					st_q_list[index].q_id = qid;
				}
				st_q_list[index].offset = 0;
				st_q_list[index].max_pack_sz = 4096;

				st_h2c_th_details[index].q_info = st_q_list[index];
				st_c2h_th_details[index].q_info = st_q_list[index];
				//printf("ST:\tPF:\t%d\tQID:\t%d\n", st_q_list[index].pf_no, st_q_list[index].q_id);
			}

			st_h2c_mutex = CreateMutex(NULL, FALSE, NULL);
			if (st_h2c_mutex == NULL) {
				printf("CreateMutex error: %d\n", GetLastError());
				exit(-1);
			}

			st_c2h_mutex = CreateMutex(NULL, FALSE, NULL);
			if (st_c2h_mutex == NULL) {
				printf("CreateMutex error: %d\n", GetLastError());
				exit(-1);
			}
		}
	}
}

void deinit_queue_distribution(void)
{
	if (mm_q_list) {
		free(mm_q_list);
		mm_q_list = NULL;
	}

	if (mm_th_details) {
		free(mm_th_details);
		mm_th_details = NULL;
	}

	if (st_q_list) {
		free(st_q_list);
		st_q_list = NULL;
	}

	if (st_h2c_th_details) {
		free(st_h2c_th_details);
		st_h2c_th_details = NULL;
	}

	if (st_c2h_th_details) {
		free(st_c2h_th_details);
		st_c2h_th_details = NULL;
	}

	if (st_h2c_mutex != INVALID_HANDLE_VALUE) {
		CloseHandle(st_h2c_mutex);
		st_h2c_mutex = INVALID_HANDLE_VALUE;
	}

	if (st_c2h_mutex != INVALID_HANDLE_VALUE) {
		CloseHandle(st_c2h_mutex);
		st_c2h_mutex = INVALID_HANDLE_VALUE;
	}

}

int add_n_start_queues(void)
{
	unsigned short index;
	ioctl_cmd cmd = {};
	DWORD ioctl_code = IOCTL_QDMA_QUEUE_ADD;
	device_file device;
	unsigned short count = 0;

	/* MM Queues Addition */
	if (no_q_mm != 0) {
		count = 0;
		for (index = 0; index < no_q_mm; index++) {
			memset(&cmd, 0, sizeof(cmd));

			//printf("add MM queue : PF : %d, qid: %4d\n", mm_q_list[index].pf_no, mm_q_list[index].q_id);

			cmd.q_conf.in.qid = mm_q_list[index].q_id;
			cmd.q_conf.in.is_st = false;


			const auto& dev_path = dev_details[mm_q_list[index].pf_no].device_path;
			device.open(dev_path + "\\mgmt", GENERIC_READ | GENERIC_WRITE);

			ioctl_code = IOCTL_QDMA_QUEUE_ADD;
			device.ioctl(ioctl_code, &cmd.q_conf.in, sizeof(cmd.q_conf.in), NULL, 0);
			//cout << "Added Queue " << mm_q_list[index].pf_no << ", " << cmd.q_conf.in.qid << " Successfully\n";

			ioctl_code = IOCTL_QDMA_QUEUE_START;
			device.ioctl(ioctl_code, &cmd.q_conf.in, sizeof(cmd.q_conf.in), NULL, 0);
			//cout << "Start Queue " << mm_q_list[index].pf_no << ", " << cmd.q_conf.in.qid << " Successfully\n";

			device.close();

			count++;
		}
		no_q_mm = count;
		printf("Total %d queues added in MM direction\n", count);
	}
	/* ST Queues Addition */
	if (no_q_st != 0) {
		count = 0;
		for (index = 0; index < no_q_st; index++) {
			memset(&cmd, 0, sizeof(cmd));

			//printf("add ST queue : PF : %d, qid: %4d\n", st_q_list[index].pf_no, st_q_list[index].q_id);

			cmd.q_conf.in.qid = st_q_list[index].q_id;
			cmd.q_conf.in.is_st = true;
			cmd.q_conf.in.c2h_buff_sz_index = 0;
			cmd.q_conf.in.c2h_ring_sz_index = 0;
			cmd.q_conf.in.c2h_th_cnt_index = 0;
			cmd.q_conf.in.c2h_timer_cnt_index = 0;
			cmd.q_conf.in.trig_mode = trig_mode::TRIG_MODE_EVERY;
			cmd.q_conf.in.compl_sz = cmpt_desc_sz::CMPT_DESC_SZ_32B;


			const auto& dev_path = dev_details[st_q_list[index].pf_no].device_path;
			device.open(dev_path + "\\mgmt", GENERIC_READ | GENERIC_WRITE);

			ioctl_code = IOCTL_QDMA_QUEUE_ADD;
			device.ioctl(ioctl_code, &cmd.q_conf.in, sizeof(cmd.q_conf.in), NULL, 0);
			//cout << "Added Queue " << st_q_list[index].pf_no << ", " << cmd.q_conf.in.qid << " Successfully\n";

			ioctl_code = IOCTL_QDMA_QUEUE_START;
			device.ioctl(ioctl_code, &cmd.q_conf.in, sizeof(cmd.q_conf.in), NULL, 0);
			//cout << "Start Queue " << st_q_list[index].pf_no << ", " << cmd.q_conf.in.qid << " Successfully\n";

			device.close();

			count++;
		}
		no_q_st = count;
		printf("Total %d queues added in ST direction\n", count);
	}

	return 0;
}

int stop_n_delete_queues(void)
{
	unsigned short index;
	ioctl_cmd cmd = {};
	DWORD ioctl_code = IOCTL_QDMA_QUEUE_STOP;
	device_file device;

	/* MM Queues Deletion */
	if (no_q_mm != 0) {
		for (index = 0; index < no_q_mm; index++) {
			memset(&cmd, 0, sizeof(cmd));

			cmd.q_conf.in.qid = mm_q_list[index].q_id;
			cmd.q_conf.in.is_st = false;


			const auto& dev_path = dev_details[mm_q_list[index].pf_no].device_path;
			device.open(dev_path + "\\mgmt", GENERIC_READ | GENERIC_WRITE);

			ioctl_code = IOCTL_QDMA_QUEUE_STOP;
			device.ioctl(ioctl_code, &cmd.q_conf.in, sizeof(cmd.q_conf.in), NULL, 0);
			//cout << "Stopped Queue " << mm_q_list[index].pf_no << ", " << cmd.q_conf.in.qid << " Successfully\n";

			ioctl_code = IOCTL_QDMA_QUEUE_DELETE;
			device.ioctl(ioctl_code, &cmd.q_conf.in, sizeof(cmd.q_conf.in), NULL, 0);
			//cout << "Deleted Queue " << mm_q_list[index].pf_no << ", " << cmd.q_conf.in.qid << " Successfully\n";

			device.close();
		}
		printf("Total %d queues removed in MM direction\n", no_q_mm);
	}
	/* ST Queues Deletion */
	if (no_q_st != 0) {
		for (index = 0; index < no_q_st; index++) {
			memset(&cmd, 0, sizeof(cmd));

			cmd.q_conf.in.qid = st_q_list[index].q_id;
			cmd.q_conf.in.is_st = true;


			const auto& dev_path = dev_details[st_q_list[index].pf_no].device_path;
			device.open(dev_path + "\\mgmt", GENERIC_READ | GENERIC_WRITE);

			ioctl_code = IOCTL_QDMA_QUEUE_STOP;
			device.ioctl(ioctl_code, &cmd.q_conf.in, sizeof(cmd.q_conf.in), NULL, 0);
			//cout << "Stopped Queue " << st_q_list[index].pf_no << ", " << cmd.q_conf.in.qid << " Successfully\n";

			ioctl_code = IOCTL_QDMA_QUEUE_DELETE;
			device.ioctl(ioctl_code, &cmd.q_conf.in, sizeof(cmd.q_conf.in), NULL, 0);
			//cout << "Deleted Queue " << st_q_list[index].pf_no << ", " << cmd.q_conf.in.qid << " Successfully\n";

			device.close();
		}
		printf("Total %d queues removed in ST direction\n", no_q_st);
	}

	return 0;
}

static UINT8* allocate_buffer(size_t size, size_t alignment)
{
	if (size == 0) {
		size = 4;
	}

	if (alignment == 0) {
		SYSTEM_INFO sys_info;
		GetSystemInfo(&sys_info);
		alignment = sys_info.dwPageSize;
	}

	return (BYTE*)_aligned_malloc(size, alignment);
}

static UINT32 get_elapsed_time(LARGE_INTEGER &end, LARGE_INTEGER &start)
{
	double time_sec = (unsigned long long)(end.QuadPart - start.QuadPart) / (double)g_freq.QuadPart;

	return (UINT32)(time_sec * 1000);
}

BOOL WINAPI run_mm_h2c_c2h_fn(PVOID arg)
{
	struct thread_params *param = (struct thread_params *)arg;
	bool timer_expired = false;
	LARGE_INTEGER curr_time;
	UINT32 elapsed_time;
	device_file queue;
	UINT8 *wr_buffer = NULL;
	UINT8 *rd_buffer = NULL;
	UINT32 pack_size = 0;
	long device_offset = 0;
	DWORD len = 0;
	int n;
	long xfer_count = 0;

	param->total_xfer_size = 0;
	srand((unsigned int)time(0));

	wr_buffer = allocate_buffer(param->q_info.max_pack_sz, 0);
	if (wr_buffer == NULL) {
		printf("allocate_buffer failed for wr_buffer for queue : %d\n", param->q_info.q_id);
		return false;
	}

	rd_buffer = allocate_buffer(param->q_info.max_pack_sz, 0);
	if (rd_buffer == NULL) {
		printf("allocate_buffer failed for rd_buffer for queue : %d\n", param->q_info.q_id);
		return false;
	}


	device_offset = param->q_info.offset;

	const auto& dev_path = dev_details[param->q_info.pf_no].device_path;
	queue.open(dev_path + "\\queue_"s + to_string(param->q_info.q_id), GENERIC_READ | GENERIC_WRITE);

	//printf("In %s:\tPF:\t%d, qid:\t%d, runtime:\t%d\n", __func__, param->q_info.pf_no, param->q_info.q_id, param->run_time);
	do {
		pack_size = (rand() % param->q_info.max_pack_sz) + 1;

		param->total_xfer_size = param->total_xfer_size + pack_size;

		for (unsigned short i = 0; i < pack_size; i++)
			wr_buffer[i] = rand() % 256;

		queue.seek(device_offset);
		if (!WriteFile(queue.h, wr_buffer, (DWORD)pack_size, &len, NULL)) {
			throw std::runtime_error("Failed to write to device! " + get_last_win_err_msg());
		}

		//Sleep(10);

		//queue.seek(device_offset);
		if (!ReadFile(queue.h, rd_buffer, (DWORD)pack_size, &len, NULL)) {
			throw std::runtime_error("Failed to read from device! " + get_last_win_err_msg());
		}

		//Sleep(10);

		n = memcmp(wr_buffer, rd_buffer, pack_size);
		if (n != 0)
			printf("MM Memory comparison error : PF : %d, qid : %d\n", param->q_info.pf_no, param->q_info.q_id);

		xfer_count++;

		QueryPerformanceCounter(&curr_time);
		elapsed_time = get_elapsed_time(curr_time, start_time);
		if (elapsed_time >= (param->run_time * 1000)) {
			//printf("time : %lld, %lld, %lld\n", start_time.QuadPart, curr_time.QuadPart, g_freq.QuadPart);
			timer_expired = true;
		}

		//Sleep(1);
	} while (timer_expired == false);

	//printf("PF : %d, QID : %3d\tMM Xfer count %d in %d seconds\n", param->q_info.pf_no, param->q_info.q_id, xfer_count, param->run_time);

	queue.close();

	param->xfer_cnt = xfer_count;

	_aligned_free(wr_buffer);
	_aligned_free(rd_buffer);

	return true;
}

static void get_qrange(const string& dev_path, unsigned int& qmax, unsigned int& qbase)
{
	device_file qdma_dev;
	struct qstat_out qstats_info = { 0 };

	qdma_dev.open(dev_path + "\\mgmt"s, GENERIC_READ | GENERIC_WRITE);
	qdma_dev.ioctl(IOCTL_QDMA_GET_QSTATS, NULL, 0, &qstats_info, sizeof(qstats_info));
	qmax = qstats_info.qmax;
	qbase = qstats_info.qbase;
}

BOOL WINAPI run_st_h2c_fn(PVOID arg)
{
	struct thread_params *param = (struct thread_params *)arg;
	bool timer_expired = false;
	LARGE_INTEGER curr_time;
	UINT32 elapsed_time;
	long xfer_count = 0;
	device_file queue;
	UINT32 pack_size = 0;
	DWORD len = 0;
	unsigned int qmax = 0, qbase = 0;

	srand((unsigned int)time(0));

	//printf("In %s:\tPF:\t%d, qid:\t%d, runtime:\t%d\n", __func__, param->q_info.pf_no, param->q_info.q_id, param->run_time);

	const auto& dev_path = dev_details[param->q_info.pf_no].device_path;
	get_qrange(dev_path, qmax, qbase);

	if (param->q_info.q_id >= qmax) {
		cout << "Invalid qid" << endl;
		return FALSE;
	}

	queue.open(dev_path + "\\st_"s + to_string(param->q_info.q_id), GENERIC_READ | GENERIC_WRITE);
	data_generator dgen(dev_path);

	do {
		pack_size = (rand() % param->q_info.max_pack_sz) + 1;
		param->total_xfer_size = param->total_xfer_size + pack_size;

		aligned_vector<uint16_t> wr_buffer(pack_size);
		iota(wr_buffer.begin(), wr_buffer.end(), static_cast<uint16_t>(0)); /* 0, 1, 2, 3, 4 ... */

		WaitForSingleObject(st_h2c_mutex, INFINITE);
		dgen.reset_h2c();

		if (!WriteFile(queue.h, wr_buffer.data(), pack_size, &len, NULL)) {
			throw std::runtime_error("Failed to write to device! " + get_last_win_err_msg());
		}

		if (true != dgen.check_h2c(qbase + param->q_info.q_id))
			printf("Data generator reported error for received data!\n");

		ReleaseMutex(st_h2c_mutex);

		xfer_count++;

		QueryPerformanceCounter(&curr_time);
		elapsed_time = get_elapsed_time(curr_time, start_time);
		if (elapsed_time >= (param->run_time * 1000)) {
			//printf("time : %lld, %lld, %lld\n", start_time.QuadPart, curr_time.QuadPart, g_freq.QuadPart);
			timer_expired = true;
		}
	} while (timer_expired == false);

	queue.close();

	param->xfer_cnt = xfer_count;

	return true;
}

BOOL WINAPI run_st_c2h_fn(PVOID arg)
{
	struct thread_params *param = (struct thread_params *)arg;
	bool timer_expired = false;
	LARGE_INTEGER curr_time;
	UINT32 elapsed_time;
	long xfer_count = 0;
	device_file queue;
	UINT8 *rd_buffer = NULL;
	UINT32 read_cnt = 0;
	UINT32 max_gold_buf_slice_cnt = 0;
	UINT16 *golden_buffer = NULL;
	DWORD len = 0;
	UINT32 pack_size = 0;
	UINT32 generated_packet_cnt = 0;
	int n;
	unsigned int qbase = 0, qmax = 0;

	srand((unsigned int)time(0));

	UNREFERENCED_PARAMETER(param);
	//printf("In %s:\tPF:\t%d, qid:\t%d, runtime:\t%d\n", __func__, param->q_info.pf_no, param->q_info.q_id, param->run_time);

	rd_buffer = allocate_buffer(param->q_info.max_pack_sz, 0);
	if (!rd_buffer) {
		throw std::runtime_error("Error allocating memory" + get_last_win_err_msg());
	}

	const auto& dev_path = dev_details[param->q_info.pf_no].device_path;
	get_qrange(dev_path, qmax, qbase);

	if (param->q_info.q_id >= qmax) {
		cout << "Invalid qid" << endl;
		return FALSE;
	}

	queue.open(dev_path + "\\st_"s + to_string(param->q_info.q_id), GENERIC_READ | GENERIC_WRITE);
	data_generator dgen(dev_path);

	golden_buffer = new UINT16[MAX_DATA_GEN_LIMIT];
	for (unsigned int i = 0; i < MAX_DATA_GEN_LIMIT; i++)
		golden_buffer[i] = (unsigned short)i;

	do {
		pack_size = param->q_info.max_pack_sz;
		max_gold_buf_slice_cnt = (MAX_DATA_GEN_LIMIT / param->q_info.max_pack_sz) * 2; // in bytes

		param->total_xfer_size = param->total_xfer_size + pack_size;

		if (generated_packet_cnt == 0) {
			WaitForSingleObject(st_c2h_mutex, INFINITE);

			//generated_packet_cnt = (rand() % 256) + 1;
			generated_packet_cnt = (rand() % 64) + 1;
			read_cnt = 0;
			dgen.reset_pkt_ctrl();
			dgen.configure_c2h(qbase + param->q_info.q_id, pack_size, generated_packet_cnt);
			dgen.generate_packets();

			Sleep(1);

			ReleaseMutex(st_c2h_mutex);
		}

		if (!ReadFile(queue.h, rd_buffer, pack_size, &len, NULL)) {
			throw std::runtime_error("Failed to read from device! " + get_last_win_err_msg());
		}

		UINT8* cmp_buf = &((UINT8*)golden_buffer)[((read_cnt % max_gold_buf_slice_cnt) * pack_size)];
		n = memcmp(cmp_buf, rd_buffer, pack_size);
		if (n != 0) {
			printf("ST C2H Memory comparison error : PF : %d, qid : %d\n", param->q_info.pf_no, param->q_info.q_id);
		}

		generated_packet_cnt = generated_packet_cnt - 1;

		xfer_count++;
		read_cnt++;

		QueryPerformanceCounter(&curr_time);
		elapsed_time = get_elapsed_time(curr_time, start_time);
		if (generated_packet_cnt == 0) {
			if (elapsed_time >= (param->run_time * 1000)) {
				//printf("time : %lld, %lld, %lld\n", start_time.QuadPart, curr_time.QuadPart, g_freq.QuadPart);
				timer_expired = true;
			}
		}
	} while (timer_expired == false);

	queue.close();

	param->xfer_cnt = xfer_count;

	return true;
}


int run_stress_test(unsigned long run_time)
{
	unsigned short index;
	unsigned long total_mm_xfer_cnt = 0;
	unsigned long total_st_h2c_xfer_cnt = 0;
	unsigned long total_st_c2h_xfer_cnt = 0;

	size_t total_mm_xfer_sz = 0;
	size_t total_st_h2c_xfer_sz = 0;
	size_t total_st_c2h_xfer_sz = 0;

	QueryPerformanceFrequency(&g_freq);
	QueryPerformanceCounter(&start_time);

	for (index = 0; index < no_q_mm; index++) {
		mm_th_details[index].run_time = run_time;
		mm_th_details[index].xfer_cnt = 0;
		mm_th_details[index].total_xfer_size = 0;
		mm_th_details[index].handle =
			CreateThread(NULL,
				1 * 1024 * 1024,
				(LPTHREAD_START_ROUTINE)run_mm_h2c_c2h_fn,
				&mm_th_details[index],
				0,
				NULL);

		if (NULL == mm_th_details[index].handle) {
			printf(" Error MM CreateThread Failed for queue %d:%d, error : %d\n", mm_th_details[index].q_info.pf_no, mm_th_details[index].q_info.q_id, GetLastError());
			ExitProcess(1);
		}

	}
	printf("%d threads created in MM mode\n", no_q_mm);

	for (index = 0; index < no_q_st; index++) {
		st_h2c_th_details[index].run_time = run_time;
		st_h2c_th_details[index].xfer_cnt = 0;
		st_h2c_th_details[index].total_xfer_size = 0;
		st_h2c_th_details[index].handle =
			CreateThread(NULL,
				1 * 1024 * 1024,
				(LPTHREAD_START_ROUTINE)run_st_h2c_fn,
				&st_h2c_th_details[index],
				0,
				NULL);

		if (NULL == st_h2c_th_details[index].handle) {
			printf(" Error ST H2C CreateThread Failed for queue %d:%d, error : %d\n", st_h2c_th_details[index].q_info.pf_no, st_h2c_th_details[index].q_info.q_id, GetLastError());
			ExitProcess(1);
		}

		st_c2h_th_details[index].run_time = run_time;
		st_c2h_th_details[index].xfer_cnt = 0;
		st_c2h_th_details[index].total_xfer_size = 0;
		st_c2h_th_details[index].handle =
			CreateThread(NULL,
				1 * 1024 * 1024,
				(LPTHREAD_START_ROUTINE)run_st_c2h_fn,
				&st_c2h_th_details[index],
				0,
				NULL);

		if (NULL == st_c2h_th_details[index].handle) {
			printf("Error ST C2H CreateThread Failed for queue %d:%d, error : %d\n", st_c2h_th_details[index].q_info.pf_no, st_c2h_th_details[index].q_info.q_id, GetLastError());
			ExitProcess(1);
		}
	}

	printf("%d threads created in ST H2C mode\n", no_q_st);
	printf("%d threads created in ST C2H mode\n", no_q_st);

	for (index = 0; index < no_q_mm; index++) {
		WaitForSingleObject(mm_th_details[index].handle, INFINITE);
		CloseHandle(mm_th_details[index].handle);
	}

	for (index = 0; index < no_q_st; index++) {
		WaitForSingleObject(st_h2c_th_details[index].handle, INFINITE);
		CloseHandle(st_h2c_th_details[index].handle);
	}

	for (index = 0; index < no_q_st; index++) {
		WaitForSingleObject(st_c2h_th_details[index].handle, INFINITE);
		CloseHandle(st_c2h_th_details[index].handle);
	}

	for (index = 0; index < no_q_mm; index++) {
		total_mm_xfer_cnt = total_mm_xfer_cnt + mm_th_details[index].xfer_cnt;
		total_mm_xfer_sz = total_mm_xfer_sz + mm_th_details[index].total_xfer_size;
		//printf("PF : %d, QID : %3d\tMM Xfer count %d in %d seconds\n", mm_th_details[index].q_info.pf_no, mm_th_details[index].q_info.q_id, mm_th_details[index].xfer_cnt, mm_th_details[index].run_time);
	}

	for (index = 0; index < no_q_st; index++) {
		total_st_h2c_xfer_cnt = total_st_h2c_xfer_cnt + st_h2c_th_details[index].xfer_cnt;
		total_st_h2c_xfer_sz = total_st_h2c_xfer_sz + st_h2c_th_details[index].total_xfer_size;
	}

	for (index = 0; index < no_q_st; index++) {
		total_st_c2h_xfer_cnt = total_st_c2h_xfer_cnt + st_c2h_th_details[index].xfer_cnt;
		total_st_c2h_xfer_sz = total_st_c2h_xfer_sz + st_c2h_th_details[index].total_xfer_size;
	}

	printf("Total MM     Xfer count : %ld\n", total_mm_xfer_cnt);
	printf("Total ST H2C Xfer count : %ld\n", total_st_h2c_xfer_cnt);
	printf("Total ST C2H Xfer count : %ld\n", total_st_c2h_xfer_cnt);

	//printf("Total MM	   Xfer count : %ld, Rate : %fMbps\n", total_mm_xfer_cnt, ((float)total_mm_xfer_sz * 8)/(run_time * 1024 * 1024));
	//printf("Total ST H2C Xfer count : %ld, Rate : %fMbps\n", total_st_h2c_xfer_cnt, ((float)total_st_h2c_xfer_sz * 8) / (run_time * 1024 * 1024));
	//printf("Total ST C2H Xfer count : %ld, Rate : %fMbps\n", total_st_c2h_xfer_cnt, ((float)total_st_c2h_xfer_sz * 8) / (run_time * 1024 * 1024));

	return 0;
}

bool sort_fun(device_details d1, device_details d2)
{
	UINT32 bdf_1 = 0x0, bdf_2 = 0x0;

	bdf_1 = (d1.bus_no << 12) | (d1.dev_no << 4) | d1.fun_no;
	bdf_2 = (d2.bus_no << 12) | (d2.dev_no << 4) | d2.fun_no;
	return (bdf_1 < bdf_2);
}

int __cdecl main(const int argc, char* argv[])
{
	int ret = 0;
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	if (argc < 5) {
		printf("Insufficient arguments\n\n");
		printf("Usage : \n\t%s <num_pfs> <num_qs_per_pf> <MM|ST|BOTH> <run_time_secs>\n\n", PROGNAME);
		return -1;
	}

	time_t s_time, e_time;
	char start_time_str[50], end_time_str[50];

	s_time = time(NULL);
	ctime_s(start_time_str, sizeof(start_time_str), &s_time);

	no_of_pfs = (unsigned short)strtoul(argv[1], NULL, 0);
	no_of_qs_per_pf = (unsigned short)strtoul(argv[2], NULL, 0);

	if (strcmp(argv[3], "BOTH") == 0)
		q_dist = q_distribution::BOTH_MM_ST;
	else if (strcmp(argv[3], "MM") == 0)
		q_dist = q_distribution::MM_ONLY;
	else if (strcmp(argv[3], "ST") == 0)
		q_dist = q_distribution::ST_ONLY;

	if ((q_dist == q_distribution::BOTH_MM_ST) && ((no_of_qs_per_pf % 2) != 0))
	{
		printf("When BOTH_MM_ST selected, even no of queues per pf must be specified\n");
		return -1;
	}

	unsigned long run_time = strtoul(argv[4], NULL, 0);

	printf("no_of_pfs : %d, no_of_qs: %d\n", no_of_pfs, no_of_qs_per_pf);

	dev_details = get_device_details(GUID_DEVINTERFACE_QDMA);
	if (no_of_pfs > dev_details.size()) {
		printf("Requested no of PFs %d are not available..only %zd available\n",
			no_of_pfs, dev_details.size());
		return -1;
	}

	std::sort(dev_details.begin(), dev_details.end(), sort_fun);

	total_qs = no_of_pfs * no_of_qs_per_pf;

	for (unsigned int i = 0; i < no_of_pfs; i++) {
		printf("Device Name : %s\n", dev_details[i].device_name.c_str());
	}

	init_queue_distribution();

	ret = add_n_start_queues();
	if (ret < 0) {
		printf("add_n_start_queues failed...Exiting\n");
		goto Exit;
	}

	ret = run_stress_test(run_time);
	if (ret < 0) {
		printf("add_n_start_queues failed...Exiting\n");
		goto Exit1;
	}

Exit1:
	ret = stop_n_delete_queues();
	if (ret < 0) {
		printf("stop_n_delete_queues failed...Exiting\n");
		goto Exit;
	}

Exit:
	deinit_queue_distribution();

	e_time = time(NULL);
	ctime_s(end_time_str, sizeof(end_time_str), &e_time);

	printf("Start time : %s	 End time : %s\n", start_time_str, end_time_str);

	return ret;
}
