#include <algorithm>
#include <sstream>
#include "qdma_queue.h"
#include "qdma_instance.h"

namespace qdma {

int do_recv_mm(int portid, void *buffer, int queueid, int ld_size, int tot_num_desc, size_t buf_size, uint16_t rx_burst_size)
{
	struct rte_mbuf *pkts[NUM_RX_PKTS] = { NULL };
	int nb_rx = 0, i = 0, num_pkts;
	int tdesc;

	if(tot_num_desc == 0) {
			printf("Error: tot_num_desc : invalid value\n");
			return 0;
	}

	//printf("recv start: num-desc: %d, with data-len: %d, last-desc-size:%d\n", tot_num_desc, buf_size, ld_size);
	tdesc = tot_num_desc;
	if (ld_size)
		tdesc--;

	while (tdesc) {
		if (tdesc > rx_burst_size)
			num_pkts = rx_burst_size;
		else
			num_pkts = tdesc;

		/* try to receive RX_BURST_SZ packets */
		nb_rx = rte_eth_rx_burst(portid, queueid, pkts, num_pkts);
		if (nb_rx == 0) {
			printf("Error: dma_from_device failed to receive packets\n");
			return 0;
		}

		for (i = 0; i < nb_rx; i++) {
			struct rte_mbuf *mb = pkts[i];
			memcpy(buffer, rte_pktmbuf_mtod(mb, void*), buf_size);
			buffer = static_cast<char*>(buffer) + buf_size;
			rte_pktmbuf_free(mb);
		}

		tdesc = tdesc - nb_rx;
	}

	if (ld_size) {
		struct rte_mbuf *mb;
		nb_rx = rte_eth_rx_burst(portid, queueid, pkts, 1);
		mb = pkts[0];
		if(nb_rx != 0) {
			memcpy(buffer, rte_pktmbuf_mtod(mb, void*), ld_size);
			buffer = static_cast<char*>(buffer) + ld_size;
			rte_pktmbuf_free(mb);
		}
	}

	//printf("\nDMA received number of packets: %d, on queue-id:%d\n", nb_rx, queueid);
	return 0;
}

int do_recv_st(int portid, void *buffer, int queueid, int input_size)
{
	struct rte_mbuf *pkts[NUM_RX_PKTS] = { NULL };
	int nb_rx = 0, i, ret = 0,tmp = 0, num_pkts, nb_pkts, num_pkts_recv = 0, bytes	= 0;
	int reg_val;
	int user_bar_idx, dma_bar_idx, bypass_bar_idx, en_imm;
	struct rte_mbuf *nxtmb;
	unsigned int max_rx_retry;


#ifdef DUMP_MEMPOOL_USAGE_STATS
	char	mem_pool[RTE_MEMPOOL_NAMESIZE];
	int q_dir = 1;

	snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, portid, queueid, q_dir);
	struct rte_mempool *mp;

	/* get the mempool from which to acquire buffers */
	if ((mp = rte_mempool_lookup(mem_pool)) == NULL)
		throw std::runtime_error("Could not find mempool");
#endif //DUMP_MEMPOOL_USAGE_STATS
	ret = rte_pmd_qdma_get_bar_details(portid, &(dma_bar_idx),
			&(user_bar_idx), &(bypass_bar_idx));
	if (ret < 0)
		throw std::runtime_error("rte_pmd_qdma_get_bar_details failed");
	ret = rte_pmd_qdma_get_immediate_data_state(portid, queueid, &(en_imm));
	if (ret < 0)
		throw std::runtime_error("rte_pmd_qdma_get_immediate_data_state failed");

	/* As per  hardware design a single writeback will point to atmost 7 descriptors.
	 * So If the size of the buffer in descriptor is 4KB, then a single writeback which
	 * corresponds a packet can give you atmost 28KB data.
	 *
	 * As per this when testing sizes beyond 28KB, one needs to split it up in chunks of 28KB,
	 * example : to test 56KB data size, set 28KB as packet length in USER BAR 0x04 register
	 * and no of packets as 2 in user BAR 0x20 register this would give you writebacks or packets,
	 * which needs to be combined as one in application.
	*/

	/* Calculate the number of packets to receive and programming the user bar */
	if(input_size == 0) /* zerobyte support uses one descriptor */
		num_pkts = 1;
	else
		num_pkts = rte_pmd_qdma_compat_pci_read_reg(portid, user_bar_idx, C2H_PACKET_COUNT_REG);
/*	else if(input_size % MAX_WRITEBACK_SIZE != 0)
		num_pkts = input_size/MAX_WRITEBACK_SIZE + 1;
	else
		num_pkts = input_size/MAX_WRITEBACK_SIZE;*/
		reg_val = rte_pmd_qdma_compat_pci_read_reg(portid, user_bar_idx, C2H_CONTROL_REG);
	//reg_val &= C2H_CONTROL_REG_MASK;
	if (reg_val & ST_LOOPBACK_EN){
		do{
			nb_rx = rte_eth_rx_burst(portid, queueid, pkts, NUM_RX_PKTS);
			for (i = 0; i < nb_rx; i++) {
				struct rte_mbuf *mb = pkts[i];
				ret = 0;
				while (mb != NULL){
					memcpy(buffer, rte_pktmbuf_mtod(mb, void*), rte_pktmbuf_data_len(mb));
					ret += rte_pktmbuf_data_len(mb);
					buffer = static_cast<char*>(buffer) + rte_pktmbuf_data_len(mb);
					nxtmb = mb->next;
					mb = nxtmb;
				}
				mb = pkts[i];
				rte_pktmbuf_free(mb);
				//printf("recv count: %d, with data-len: %d\n", i, ret);
				bytes += ret;
			}
		}while(bytes < input_size);
		return bytes;
	}

	while (num_pkts) {
		if (num_pkts > NUM_RX_PKTS)
			nb_pkts = NUM_RX_PKTS;
		else
			nb_pkts = num_pkts;

		num_pkts_recv = nb_pkts;
		max_rx_retry = RX_TX_MAX_RETRY;

		if(en_imm) { /* Immediate data Enabled*/
			/* payload received is zero for the immediate data case. Therefore , no need
			 * to call the rx_burst function again in this case and set the num_pkts to nb_rx
			 * which is always Zero.
			 */
			rte_eth_rx_burst(portid, queueid, pkts, nb_pkts);
			num_pkts = 0;
		}
		else {
			/* try to receive RX_BURST_SZ packets */

			nb_rx = rte_eth_rx_burst(portid, queueid, pkts, nb_pkts);
			tmp = nb_rx;
			if(input_size == 0)
				break;
			while((nb_rx < nb_pkts) && max_rx_retry) {
				/*printf("Couldn't receive all the packets:	 Expected = %d Received = %d. \n"
				"Calling rte_eth_rx_burst again\n", nb_pkts , nb_rx);*/
				usleep(1);
				nb_pkts -= nb_rx;
				nb_rx = rte_eth_rx_burst(portid, queueid, &pkts[tmp], nb_pkts);
				tmp += nb_rx;
				max_rx_retry--;
			}

			num_pkts_recv = tmp;
			if((max_rx_retry == 0) && (tmp == 0)) {
					printf("ERROR: rte_eth_rx_burst failed\n");
					break;
			}

#ifdef DUMP_MEMPOOL_USAGE_STATS
			printf("%s(): %d: queue id = %d, mbuf_avail_count = %d, mbuf_in_use_count = %d\n",
				__func__, __LINE__, queueid, rte_mempool_avail_count(mp), rte_mempool_in_use_count(mp));
#endif //DUMP_MEMPOOL_USAGE_STATS
			for (i = 0; i < num_pkts_recv; i++) {
				struct rte_mbuf *mb = pkts[i];
				while (mb != NULL){
					memcpy(buffer, rte_pktmbuf_mtod(mb, void*), rte_pktmbuf_data_len(mb));
					ret += rte_pktmbuf_data_len(mb);
					buffer = static_cast<char*>(buffer) + rte_pktmbuf_data_len(mb);
					nxtmb = mb->next;
					mb = nxtmb;
				}

				mb = pkts[i];
				rte_pktmbuf_free(mb);
				//printf("recv count: %d, with data-len: %d\n", i, ret);
				ret = 0;
			}
#ifdef DUMP_MEMPOOL_USAGE_STATS
			printf("%s(): %d: queue id = %d, mbuf_avail_count = %d, mbuf_in_use_count = %d, num_pkts_recv = %d\n",
				__func__, __LINE__, queueid, rte_mempool_avail_count(mp), rte_mempool_in_use_count(mp), num_pkts_recv);
#endif //DUMP_MEMPOOL_USAGE_STATS
			num_pkts = num_pkts - num_pkts_recv;
		}
	}

	//printf("\nDMA received number of packets: %d, on queue-id:%d\n", num_pkts, queueid);

	return 0;
}


int do_xmit(int portid, void * buffer, int queueid, int ld_size, int tot_num_desc, int zbyte, size_t buf_size, uint16_t tx_burst_size)
{
	struct rte_mempool *mp;
	struct rte_mbuf *mb[NUM_RX_PKTS] = { NULL };
	int nb_tx = 0, i = 0, tdesc, num_pkts = 0, tmp = 0, nb_pkts = 0;
	uint32_t max_tx_retry;
	char	mem_pool[RTE_MEMPOOL_NAMESIZE];
	int	q_dir = 0;
	int loop_cnt = 5;
	uint16_t burst_size = tx_burst_size;

	snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, portid, queueid, q_dir);

	while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
	{
		usleep(100);
		loop_cnt--;
	}

	if (mp == NULL) {
		printf("do_xmit : Could not find mempool with name: %s\n", mem_pool);
		throw std::runtime_error("do_xmit : Could not find mempool with name:\n");
	}
	tdesc = tot_num_desc;
	if (ld_size)
		tdesc --;

	while (tdesc) {
		if (tdesc > burst_size)
			num_pkts = burst_size;
		else
			num_pkts = tdesc;

		max_tx_retry = RX_TX_MAX_RETRY;
#ifdef DUMP_MEMPOOL_USAGE_STATS
		printf("%s(): %d: queue id %d, mbuf_avail_count = %d, mbuf_in_use_count = %d\n",
			__func__, __LINE__, queueid, rte_mempool_avail_count(mp), rte_mempool_in_use_count(mp));
#endif //DUMP_MEMPOOL_USAGE_STATS
		for (i=0; i<num_pkts; i++) {
			mb[i] = rte_pktmbuf_alloc(mp);
			if (mb[i] == NULL) {
					throw std::runtime_error(" #####Cannot allocate mbuf packet ");
			}
			if (!zbyte){
				memcpy(rte_pktmbuf_mtod(mb[i], void *), buffer , buf_size);
				buffer = static_cast<char*>(buffer) + buf_size;
			}
			mb[i]->nb_segs = 1;
			mb[i]->next = NULL;
			rte_pktmbuf_data_len(mb[i]) = (!zbyte) ? (uint16_t)buf_size : 0;
			rte_pktmbuf_pkt_len(mb[i])	= (!zbyte) ? (uint16_t)buf_size : 0;
		}

#ifdef DUMP_MEMPOOL_USAGE_STATS
		printf("%s(): %d: queue id %d, mbuf_avail_count = %d, mbuf_in_use_count = %d, num_pkts_tx = %d\n",
			__func__, __LINE__, queueid, rte_mempool_avail_count(mp), rte_mempool_in_use_count(mp), num_pkts);
#endif //DUMP_MEMPOOL_USAGE_STATS

		/* try to transmit TX_BURST_SZ packets */
		nb_pkts = num_pkts;
		nb_tx = rte_eth_tx_burst(portid, queueid, mb, num_pkts);
		tmp = nb_tx;
		while((nb_tx < num_pkts) && max_tx_retry) {
			/*printf("Couldn't transmit all the packets: queueid=%d	 Expected = %d Transmitted = %d. \n"
					"Calling rte_eth_tx_burst again\n",queueid, num_pkts , nb_tx);*/
			usleep(1);
			num_pkts -= nb_tx;
			nb_tx = rte_eth_tx_burst(portid, queueid, &mb[tmp], num_pkts);
			tmp += nb_tx;
			max_tx_retry--;
		}
		if((max_tx_retry == 0)) {
			for (i = tmp; i < nb_pkts; i++)
				rte_pktmbuf_free(mb[i]);
			if (tmp == 0) {
				printf("ERROR: rte_eth_tx_burst failed \n");
				break;
			}
		}

		tdesc = tdesc - tmp;
	}

	if (ld_size) {
		mb[0] = rte_pktmbuf_alloc(mp);
		if (mb[0] == NULL) {
				throw std::runtime_error(" #####Cannot allocate mbuf packet");
		}
		memcpy(rte_pktmbuf_mtod(mb[0], void *), buffer, ld_size);
		buffer = static_cast<char*>(buffer) + ld_size;
		mb[0]->nb_segs = 1;
		mb[0]->next = NULL;
		rte_pktmbuf_data_len(mb[0]) = (uint16_t)ld_size;
		rte_pktmbuf_pkt_len(mb[0])	= (uint16_t)ld_size;
		nb_tx = rte_eth_tx_burst(portid, queueid, mb, 1);
		if(nb_tx == 0)
			rte_pktmbuf_free(mb[0]);
	}
	//printf("\nDMA transmitted number of packets: %d, on Queue-id:%d\n", nb_pkts, queueid);
	return 0;
}

queue_ext::queue_ext(instance& drv, uint32_t dev_id, uint32_t q_id, queue::mode mode,
			 queue::direction dir, const queue_ext::config& qcfg){

	m_drv = &drv;
	m_dev_id = dev_id;
	m_qid = q_id;
	m_mode = mode;
	m_dir = dir;
	m_buff_sz = qcfg.idx_bufsz;
	m_burst_size = qcfg.burst_size;
	char	mem_pool[RTE_MEMPOOL_NAMESIZE];
	uint32_t		nb_buff;
	struct rte_mempool	*mbuf_pool;

	/** Mbuf packet pool **/
	nb_buff = ((qcfg.idx_rngsz));

	nb_buff += (6 * NUM_RX_PKTS);

	/* Configure mbuf packet pool with minimum 2K size */
	nb_buff = RTE_MAX(nb_buff, (RTE_MEMPOOL_CACHE_MAX_SIZE * 1.5));
	if (dir == qdma::queue_ext::direction::both){
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, m_dev_id, m_qid, (int)queue_ext::direction::host_to_card);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());
		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for h2c-qid: %d, error: %s\n", m_qid, rte_strerror(rte_errno));
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, m_dev_id, m_qid, (int)queue_ext::direction::card_to_host);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());

		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for c2h-qid: %d, error: %s\n", m_qid, rte_strerror(rte_errno));
		m_drv->add_queue(m_dev_id, m_qid, 1, mode, qdma::queue_ext::direction::host_to_card, qcfg);
		m_drv->add_queue(m_dev_id, m_qid, 1, mode, qdma::queue_ext::direction::card_to_host, qcfg);
		m_drv->start_queue(m_dev_id, m_qid, mode, qdma::queue_ext::direction::host_to_card, qcfg);
		m_drv->start_queue(m_dev_id, m_qid, mode, qdma::queue_ext::direction::card_to_host, qcfg);
	}
	else{
		snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, m_dev_id, m_qid, (int)m_dir);
		mbuf_pool = rte_pktmbuf_pool_create(mem_pool, nb_buff, MP_CACHE_SZ,
				0, qcfg.idx_bufsz + RTE_PKTMBUF_HEADROOM, rte_socket_id());

		if (mbuf_pool == NULL)
			rte_exit(EXIT_FAILURE, " Cannot create mbuf pkt-pool for qid: %d,  direction: %d, error: %s\n", m_qid, (int)m_dir, rte_strerror(rte_errno));
		m_drv->add_queue(m_dev_id, m_qid, 1, mode, dir, qcfg);
		m_drv->start_queue(m_dev_id, m_qid, mode, dir, qcfg);
	}
}

queue_ext::~queue_ext() {
	char mem_pool[RTE_MEMPOOL_NAMESIZE];
	struct rte_mempool *mp;
	int loop_cnt;

	if (m_drv) {
		if (m_dir == qdma::queue_ext::direction::both){
			m_drv->stop_queue(m_dev_id, m_qid, qdma::queue_ext::direction::host_to_card);
			m_drv->stop_queue(m_dev_id, m_qid, qdma::queue_ext::direction::card_to_host);
			snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, m_dev_id, m_qid, (int)queue_ext::direction::host_to_card);
			loop_cnt = 5;
			while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
			{
				usleep(100);
				loop_cnt--;
			}

			if (mp != NULL)
				rte_mempool_free(mp);
			snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, m_dev_id, m_qid, (int)queue_ext::direction::card_to_host);
			loop_cnt = 5;
			while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
			{
				usleep(100);
				loop_cnt--;
			}
			if (mp != NULL)
				rte_mempool_free(mp);
		} else {
			m_drv->stop_queue(m_dev_id, m_qid, m_dir);
			snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, m_dev_id, m_qid, (int)m_dir);
			loop_cnt = 5;
			while (((mp = rte_mempool_lookup(mem_pool)) == NULL) && loop_cnt >= 0)
			{
				usleep(100);
				loop_cnt--;
			}
			if (mp != NULL)
				rte_mempool_free(mp);
		}
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
		m_mode = rhs.m_mode;

		//reset
		m_drv = nullptr;
	}
	return *this;
}

size_t queue_ext::write(void* buffer, const size_t size, const long device_offset, bool throw_err) {

	unsigned tot_num_desc = 1, ld_size = 0;

	(void)throw_err;
	if(size != 0)
		tot_num_desc = (size/ m_buff_sz) + ((size % m_buff_sz) ? 1 : 0);
	ld_size = size % m_buff_sz;

	if (m_mode == queue_ext::mode::memory_mapped)
		rte_pmd_qdma_set_mm_endpoint_addr(m_dev_id, m_qid, RTE_PMD_QDMA_TX, device_offset);

	return do_xmit(m_dev_id, buffer, m_qid, ld_size, tot_num_desc, (size == 0) ? 1 : 0, m_buff_sz, m_burst_size);
}

size_t queue_ext::read(void* buffer, const size_t size, const long device_offset, bool throw_err) {

	unsigned mm_tdesc, mm_ld_size = 0;

	(void)throw_err;
	if (size >= m_buff_sz) {

		if (size % m_buff_sz) {
			mm_tdesc = (size / m_buff_sz) + 1;
			mm_ld_size = size % m_buff_sz;
		}
		else
			mm_tdesc = (size / m_buff_sz);
	}
	else {
		mm_tdesc = 1;
		mm_ld_size = size % m_buff_sz;
	}

	if (m_mode == queue_ext::mode::streaming){
		return do_recv_st(m_dev_id, buffer, m_qid, size);
	}
	else {

		if (m_mode == queue_ext::mode::memory_mapped)
			rte_pmd_qdma_set_mm_endpoint_addr(m_dev_id, m_qid, RTE_PMD_QDMA_RX, device_offset);

		return do_recv_mm(m_dev_id, buffer, m_qid, mm_ld_size, mm_tdesc, m_buff_sz, m_burst_size);
	}

}

} // namespace qdma

