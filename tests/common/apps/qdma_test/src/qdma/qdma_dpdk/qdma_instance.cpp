

#include "qdma_instance.h"

#include <stdexcept>

#include "xlnx_pci.h"
#include "xlnx_util.h"


namespace qdma {

instance_ext::instance_ext(instance_ext::type t){

	m_type = t;

}

uint32_t instance_ext::get_last_id(){

	return 0;
}
std::vector<device> instance_ext::get_devices() {
	auto num_devs = get_num_devices();

	std::vector<device> qdma_devices;
	qdma_devices.reserve(num_devs);
	for (auto i = 0u; i < num_devs; i++) {
		const auto dev_details = dev_info(i);
		qdma_devices.emplace_back(*this, dev_details);
		qdma_devices[i].dev_id = dev_details.id;
	}
	return std::move(qdma_devices);
}


//size_t instance::get_num_devices(std::vector<std::string> *dev_strings) {
unsigned instance_ext::get_num_devices() {

	int num_ports, pf_ports = 0, vf_ports = 0;
	enum rte_pmd_qdma_pci_func_type func_type;
	num_ports = rte_eth_dev_count_avail();
	if (num_ports < 1)
		throw std::runtime_error("No Ethernet devices found Try updating the FPGA image");
	for(int i=0; i < num_ports; i++ ){
		rte_pmd_qdma_get_pci_func_type(i, &func_type);
		if (func_type == RTE_PMD_QDMA_PCI_FUNC_VF)
			vf_ports++;
		else
			pf_ports++;
	}
	if (m_type == instance_ext::type::pf )
		return pf_ports;
	else
		return vf_ports;
}

auto instance_ext::dev_info(unsigned dev_id) -> device::info {

	device::info info;
	int pf_ports = 0, vf_ports = 0, num_ports;
	int ret = 0;
	int *pf, *vf;
	struct rte_pmd_qdma_dev_attributes dev_attr;

	num_ports = rte_eth_dev_count_avail();
	if (num_ports < 1)
		throw std::runtime_error("No Ethernet devices found Try updating the FPGA image");

	/*Create port to pf,vf mapping.*/
	pf= new int[num_ports];
	vf= new int[num_ports];

	if (pf == nullptr || vf == nullptr)
		throw std::runtime_error("PF/VF memory allocation failed");

	for (int i =0; i < num_ports; i++) {
		/* Mark invalid*/
		pf[i] = -1;
		vf[i] = -1;

		enum rte_pmd_qdma_pci_func_type func_type;
		rte_pmd_qdma_get_pci_func_type(i, &func_type);

		if (func_type == RTE_PMD_QDMA_PCI_FUNC_VF) {
			vf[vf_ports] = i;
			vf_ports++;
		}
		if (func_type == RTE_PMD_QDMA_PCI_FUNC_PF) {
			pf[pf_ports] = i;
			pf_ports++;
		}
	}

	/* Get portid for a given pf/vf */
	if (m_type == instance_ext::type::vf )
		info.id = vf[dev_id];
	if (m_type == instance_ext::type::pf )
		info.id = pf[dev_id];
	delete[] pf;
	delete[] vf;

	ret = rte_pmd_qdma_get_bar_details(info.id, &(info.dma_bar_idx),
			&(info.user_bar_idx), &(info.bypass_bar_idx));
	if (ret < 0)
		throw std::runtime_error("rte_pmd_qdma_get_bar_details failed");

	ret = rte_pmd_qdma_get_device_capabilities(info.id, &dev_attr);
	if (ret < 0)
		throw std::runtime_error("rte_pmd_qdma_get_device_capabilities failed");

	info.dev_cap.num_pfs = dev_attr.num_pfs;
	info.dev_cap.num_qs = dev_attr.num_qs;
	info.dev_cap.flr_present = dev_attr.flr_present;
	info.dev_cap.st_en = dev_attr.st_en;
	info.dev_cap.mm_en = dev_attr.mm_en;
	info.dev_cap.mm_cmpt_en = dev_attr.mm_cmpt_en;
	info.dev_cap.mailbox_en = dev_attr.mailbox_en;
	info.dev_cap.mm_channel_max = dev_attr.mm_channel_max;
	info.dev_cap.cmpt_ovf_chk_dis = dev_attr.cmpt_ovf_chk_dis;
	info.dev_cap.sw_desc_64b = dev_attr.sw_desc_64b;
	info.dev_cap.cmpt_desc_64b = dev_attr.cmpt_desc_64b;
	info.dev_cap.cmpt_trig_count_timer = dev_attr.cmpt_trig_count_timer;
	info.dev_cap.device_type = dev_attr.device_type;
	info.dev_cap.ip_type = dev_attr.ip_type;

	return info;
}


unsigned instance_ext::add_queue(unsigned dev_id, unsigned q_id, __rte_unused unsigned num_q, queue_ext::mode q_mode,
							 queue_ext::direction q_dir, const queue_ext::config& qcfg, bool throw_err) {

	struct rte_mempool			*mbuf_pool;
	struct rte_eth_txconf		tx_conf;
	struct rte_eth_rxconf		rx_conf;
	int							ret;
	enum rte_pmd_qdma_rx_bypass_mode	rx_bypass_mode = RTE_PMD_QDMA_RX_BYPASS_NONE;
	char	mem_pool[RTE_MEMPOOL_NAMESIZE];
	enum rte_pmd_qdma_queue_mode_t queue_mode;
	struct rte_pmd_qdma_dev_attributes dev_attr;

	if(q_mode == queue_ext::mode::streaming) {
		queue_mode = RTE_PMD_QDMA_STREAMING_MODE;
	}
	else if(q_mode == queue_ext::mode::memory_mapped) {
		queue_mode = RTE_PMD_QDMA_MEMORY_MAPPED_MODE;
	}
	else {
		printf("%s, %d, invalid queue mode is specified, queue mode = %d\n", __func__, __LINE__, (int)q_mode);
	}

	(void)throw_err;
	snprintf(mem_pool, RTE_MEMPOOL_NAMESIZE, MBUF_POOL_NAME_PORT_QUEUE_DIR, dev_id, q_id, (int)q_dir);
	if ((mbuf_pool = rte_mempool_lookup(mem_pool)) == NULL)
		throw std::runtime_error("add_queue: Could not find mempool with name:");
	memset(&tx_conf, 0x0, sizeof(struct rte_eth_txconf));
	memset(&rx_conf, 0x0, sizeof(struct rte_eth_rxconf));

	ret = rte_pmd_qdma_get_device_capabilities(dev_id, &dev_attr);
	if (ret < 0)
		throw std::runtime_error("rte_pmd_qdma_get_device_capabilities failed");

	ret = rte_pmd_qdma_set_queue_mode(dev_id, q_id, queue_mode);
	if(ret < 0)
		throw std::runtime_error("rte_pmd_qdma_set_queue_mode  failed");

	if (q_dir == queue_ext::direction::host_to_card){
		tx_conf.tx_deferred_start = 1;
		if (qcfg.desc_bypass) {
			ret = rte_pmd_qdma_configure_tx_bypass(dev_id, q_id,
					RTE_PMD_QDMA_TX_BYPASS_ENABLE,
					(rte_pmd_qdma_bypass_desc_len)qcfg.sw_desc_sz);

			if(ret < 0) {
				throw std::runtime_error("rte_pmd_qdma_configure_tx_bypass failed");
			}
		}
		ret = rte_eth_tx_queue_setup(dev_id, q_id, qcfg.idx_rngsz, 0,
					&tx_conf);
		if (ret < 0) {
			printf("rte_eth_tx_queue_setup failed with error %d for port_id = %d queue id = %d\n", ret, dev_id, q_id);
			throw std::runtime_error("Cannot setup TX Queue");
		}
	}
	else if (q_dir == queue_ext::direction::card_to_host){
		rx_conf.rx_deferred_start = 1;

		if((qcfg.desc_bypass == 1) && (qcfg.pfetch_bypass == 1)) {
			rx_bypass_mode = RTE_PMD_QDMA_RX_BYPASS_SIMPLE;
		}
		else if(qcfg.desc_bypass == 1) {
			rx_bypass_mode = RTE_PMD_QDMA_RX_BYPASS_CACHE;
		}
		ret = rte_pmd_qdma_configure_rx_bypass(dev_id, q_id, rx_bypass_mode, (rte_pmd_qdma_bypass_desc_len)qcfg.sw_desc_sz);
		if(ret < 0)
			throw std::runtime_error("rte_pmd_qdma_configure_rx_bypass failed");

		if(q_mode == queue_ext::mode::streaming) {
			ret = rte_pmd_qdma_set_cmpt_descriptor_size(dev_id, q_id, (rte_pmd_qdma_cmpt_desc_len )qcfg.cmptsz);
			if(ret < 0)
				throw std::runtime_error("rte_pmd_qdma_set_cmpt_descriptor_size failed");
		}

		/* Update the threshold in rxconf */
		rx_conf.rx_thresh.wthresh = qcfg.idx_cntr;
		ret = rte_eth_rx_queue_setup(dev_id, q_id, qcfg.idx_rngsz, 0,
						&rx_conf, mbuf_pool);
		if (ret < 0) {
			printf("rte_eth_rx_queue_setup failed with error %d for port_id = %d, queue id = %d\n", ret, dev_id, q_id);
			throw std::runtime_error("Cannot setup RX Queue");
		}

		if(q_mode == queue_ext::mode::streaming) {
			ret = rte_pmd_qdma_set_c2h_descriptor_prefetch(dev_id, q_id, qcfg.prefetch);
			if(ret < 0)
				throw std::runtime_error("rte_pmd_qdma_set_c2h_descriptor_prefetch failed");
			if(!((dev_attr.device_type == QDMA_DEVICE_VERSAL_CPM4) &&
					(dev_attr.ip_type == QDMA_VERSAL_HARD_IP))) {
				ret = rte_pmd_qdma_set_cmpt_overflow_check(dev_id, q_id, qcfg.c2h_ovf_chk_dis);
				if(ret < 0)
					throw std::runtime_error("rte_pmd_qdma_set_cmpt_overflow_check failed");
			}
			ret = rte_pmd_qdma_set_cmpt_trigger_mode(dev_id, q_id, (rte_pmd_qdma_tigger_mode_t)qcfg.trigmode);
			if(ret < 0)
				throw std::runtime_error("rte_pmd_qdma_set_cmpt_trigger_mode failed");
			ret = rte_pmd_qdma_set_cmpt_timer(dev_id, q_id, qcfg.idx_tmr);
			if(ret < 0)
				throw std::runtime_error("rte_pmd_qdma_set_cmpt_timer failed");
			ret = rte_pmd_qdma_set_immediate_data_state(dev_id, q_id, qcfg.c2h_udd_en);
			if(ret < 0)
				throw std::runtime_error("rte_pmd_qdma_set_immediate_data_state failed\n");
		}
	}
	else
		throw std::runtime_error("Undefined Direction");

	//std::cout << resp_str << "\n";
	return 0; //FIXME resp.get_attrib<uint32_t>(XNL_ATTR_QIDX);
}



unsigned instance_ext::start_queue(unsigned dev_id, unsigned queue_id, __rte_unused queue_ext::mode q_mode,
							  queue_ext::direction q_dir, __rte_unused const queue_ext::config& qcfg, bool throw_err) {

	int ret;
	struct rte_eth_dev *dev;

	/* DPDK v18.11.0 expects rte_eth_dev_start() to be done before starting any queue,
	 * gtest tests are acting on per qeueue base, so we explicitly mark device as started.
	 */
	(void)throw_err;
	dev = &rte_eth_devices[dev_id];
	dev->data->dev_started = 1;

	if (q_dir == queue_ext::direction::host_to_card){
		ret = rte_eth_dev_tx_queue_start(dev_id, queue_id);
		if (ret < 0 )
			throw std::runtime_error("Failed to start H2C queue");
	}
	else if (q_dir == queue_ext::direction::card_to_host){
		ret = rte_eth_dev_rx_queue_start(dev_id, queue_id);
		if (ret < 0 )
			throw std::runtime_error("Failed to start C2H queue");
	}
	return 0;
}

unsigned instance_ext::stop_queue(unsigned dev_id, unsigned queue_id, queue_ext::direction q_dir, bool throw_err) {

	int ret;
	struct rte_eth_dev *dev;

	(void)throw_err;
	dev = &rte_eth_devices[dev_id];

	if (q_dir == queue_ext::direction::host_to_card){
			ret = rte_eth_dev_tx_queue_stop(dev_id, queue_id);
			if (ret < 0 )
				throw std::runtime_error("Failed to stop H2C queue");
		}
		else if (q_dir == queue_ext::direction::card_to_host){
			ret = rte_eth_dev_rx_queue_stop(dev_id, queue_id);
			if (ret < 0 )
				throw std::runtime_error("Failed to stop C2H queue");
		}
	dev->data->dev_started = 0;
	return 0;
}


} // namespace qdma
