/*
 * qdma_instance.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: arayajig
 */


#include <Windows.h>
#include <SetupAPI.h>
#include <INITGUID.H>

#include <stdexcept>
#include "qdma_instance.h"

#include "xlnx_pci.h"
#include "xlnx_util.h"
#include "qdma_driver_api.h"



namespace qdma {

#pragma comment (lib, "Setupapi.lib")

static bool sort_fun(device_details d1, device_details d2)
{
    return ((d1.bus_no < d2.bus_no) && (d1.dev_no < d2.dev_no) && (d1.fun_no < d2.fun_no));
}

int instance_ext::get_dev_index(std::string dev_string) {
    int idx = 0;
    std::stringstream ss;
    std::string qdma_dev;
    std::string qdma_devid;
    size_t pos = 4;

    ss << dev_string;
    ss >> qdma_dev;

    if (qdma_dev[4] == 'v' && qdma_dev[5] == 'f')
        pos = 6;
    qdma_devid = qdma_dev.substr(pos, qdma_dev.length());
    idx = strtoul(qdma_devid.c_str(), NULL, 16);

    return idx;
}

instance_ext::instance_ext(instance_ext::type t)
{
    instance_ext::m_type = t;
    if (t == type::vf)
        return;

    dev_details = get_device_details(GUID_DEVINTERFACE_QDMA);
    n_devices = dev_details.size();
    std::sort(dev_details.begin(), dev_details.end(), sort_fun);

    mgmt.reserve(n_devices);
    mgmt_pf.reserve(n_devices);
    qmax.reserve(n_devices);
    qbase.reserve(n_devices);

    for (auto i = 0u; i < n_devices; i++) {

        uint32_t idx = get_dev_index(dev_details[i].device_name);

        mgmt.emplace_back(dev_details[i].device_path + "\\mgmt", GENERIC_READ | GENERIC_WRITE);
        mgmt_pf.emplace_back(idx);
        struct qstat_out qstats_info = { 0 };
        mgmt[i].ioctl(IOCTL_QDMA_GET_QSTATS, NULL, 0, &qstats_info, sizeof(qstats_info));

        qbase.emplace_back(qstats_info.qbase);
        qmax.emplace_back(qstats_info.qmax);
    }
}
#if 0
void instance_ext::validate_queue(uint32_t dev_id, unsigned &qid)
{
    if ((device_type == QDMA_DEVICE_VERSAL) &&
        (versal_ip_type == QDMA_VERSAL_HARD_IP)) {
        auto idx = get_mgmt_loc_from_dev_id(dev_id);
        if (dev_details[idx].fun_no == 0) {
            qid = qid + 1;
        }
    }
}
#endif
int instance_ext::get_mgmt_loc_from_dev_id(int dev_id)
{
    int idx = -1;
    for (auto i = 0; i < dev_details.size(); i++) {
        if (mgmt_pf.at(i) == dev_id) {
            idx = i;
            break;
        }
    }

    return idx;
}

std::vector<device_details> instance_ext::get_device_details(GUID guid)
{
    auto device_info = SetupDiGetClassDevs((LPGUID)&guid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (device_info == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("GetDevices INVALID_HANDLE_VALUE");
    }

    SP_DEVINFO_DATA dev_info_data;
    dev_info_data.cbSize = sizeof(SP_DEVINFO_DATA);

    SP_DEVICE_INTERFACE_DATA device_interface = { 0 };
    device_interface.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);


    std::vector<device_details> dev_details;
    device_details info;

    /* enumerate through devices */
    for (unsigned index = 0;
        SetupDiEnumDeviceInterfaces(device_info, NULL, &guid, index, &device_interface);
        ++index) {

        char *bus_no = NULL;
        char *dev_addr = NULL;
        DWORD lsize = 0;

        /* get required buffer size */
        unsigned long detailLength = 0;
        if (!SetupDiGetDeviceInterfaceDetail(device_info, &device_interface, NULL, 0, &detailLength, NULL) && GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
            throw std::runtime_error("SetupDiGetDeviceInterfaceDetail - get length failed");
        }

        /* allocate space for device interface detail */
        auto dev_detail = reinterpret_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA>(new char[detailLength]);
        dev_detail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        /* get device interface detail */
        if (!SetupDiGetDeviceInterfaceDetail(device_info, &device_interface, dev_detail, detailLength, NULL, &dev_info_data)) {
            delete[] dev_detail;
            throw std::runtime_error("SetupDiGetDeviceInterfaceDetail - get detail failed");
        }

        /* get the required size for PCIe BUS NUMBER Parameter */
        if (!SetupDiGetDeviceRegistryProperty(device_info, &dev_info_data, SPDRP_BUSNUMBER, NULL, (PBYTE)bus_no, 0, &lsize) && GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
            delete[] dev_detail;
            throw std::runtime_error("SetupDiGetDeviceRegistryProperty - get length failed");
        }

        /* Retrieve the PCIe bus number */
        bus_no = (TCHAR*)malloc(lsize);
        if (!SetupDiGetDeviceRegistryProperty(device_info, &dev_info_data, SPDRP_BUSNUMBER, NULL, (PBYTE)bus_no, lsize, NULL)) {
            delete[] dev_detail;
            free(bus_no);
            throw std::runtime_error("SetupDiGetDeviceRegistryProperty - get Registry failed");
        }

        /* get the required size for PCIe Device Address Parameter */
        if (!SetupDiGetDeviceRegistryProperty(device_info, &dev_info_data, SPDRP_ADDRESS, NULL, (PBYTE)dev_addr, 0, &lsize) && GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
            delete[] dev_detail;
            free(bus_no);
            throw std::runtime_error("SetupDiGetDeviceRegistryProperty - get length failed");
        }

        /* Retrieve the PCIe Device Address */
        dev_addr = (TCHAR*)malloc(lsize);
        if (!SetupDiGetDeviceRegistryProperty(device_info, &dev_info_data, SPDRP_ADDRESS, NULL, (PBYTE)dev_addr, lsize, NULL)) {
            delete[] dev_detail;
            free(bus_no);
            free(dev_addr);
            throw std::runtime_error("SetupDiGetDeviceRegistryProperty - get Registry failed");
        }

        /* Prepare BDF format (0xBBDDF) */
        UINT8 dev_no = (*dev_addr & 0xF8) >> 3;
        UINT8 fun_no = (*dev_addr & 0x7);
        UINT32 bdf = 0x0;
        bdf = bdf | (*bus_no << 12);
        bdf = bdf | (dev_no << 4);
        bdf = bdf | (fun_no);

        /* Prepare the PCIe devices identifier strings */
        std::ostringstream outs;
        outs << "qdma";
        outs.setf(std::ios::hex, std::ios::basefield);
        outs.width(5); outs.fill('0');
        outs << bdf;

        /* Fill the details in info structure */
        info.bus_no = *bus_no;
        info.dev_no = dev_no;
        info.fun_no = fun_no;
        info.device_name = outs.str();
        info.device_path = dev_detail->DevicePath;

        /* Append it to the return vector */
        dev_details.emplace_back(info);

        free(bus_no);
        free(dev_addr);
        delete[] dev_detail;
    }

    SetupDiDestroyDeviceInfoList(device_info);

    return dev_details;
}

std::vector<std::string> instance_ext::get_device_paths(GUID guid)
{

    auto device_info = SetupDiGetClassDevs((LPGUID)&guid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (device_info == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("GetDevices INVALID_HANDLE_VALUE");
    }

    SP_DEVICE_INTERFACE_DATA device_interface = { 0 };
    device_interface.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    // enumerate through devices

    std::vector<std::string> device_paths;

    for (unsigned index = 0;
        SetupDiEnumDeviceInterfaces(device_info, NULL, &guid, index, &device_interface);
        ++index) {

        // get required buffer size
        unsigned long detailLength = 0;
        if (!SetupDiGetDeviceInterfaceDetail(device_info, &device_interface, NULL, 0, &detailLength, NULL) && GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
            throw std::runtime_error("SetupDiGetDeviceInterfaceDetail - get length failed");
        }

        // allocate space for device interface detail
        auto dev_detail = reinterpret_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA>(new char[detailLength]);
        dev_detail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        // get device interface detail
        if (!SetupDiGetDeviceInterfaceDetail(device_info, &device_interface, dev_detail, detailLength, NULL, NULL)) {
            delete[] dev_detail;
            throw std::runtime_error("SetupDiGetDeviceInterfaceDetail - get detail failed");
        }
        device_paths.emplace_back(dev_detail->DevicePath);
        std::cout << dev_detail->DevicePath << "\n";
        delete[] dev_detail;
    }

    SetupDiDestroyDeviceInfoList(device_info);

    return device_paths;

}
std::string instance_ext::get_device_path(UINT32 dev_id)
{
    auto idx = get_mgmt_loc_from_dev_id(dev_id);
    if (idx < 0) {
        throw std::runtime_error("get_mgmt_loc_from_dev_id failed");
    }

    return dev_details[idx].device_path;
}

std::vector<device> instance_ext::get_devices()
{
    std::vector<device> qdma_devices;
    qdma_devices.reserve(n_devices);

    for (auto i = 0u; i < n_devices; i++) {

        uint32_t idx = get_dev_index(dev_details[i].device_name);

        const auto device_details = dev_info(idx);

        qdma_devices.emplace_back(*this, device_details, idx, dev_details[i].device_path);
    }

    return qdma_devices;
}

/** helper function for getting the last_device_id, for INVALID_ID
* testcases
*/
uint32_t instance_ext::get_last_id()
{
    return m_last_id;
}

auto instance_ext::dev_info(uint32_t dev_id) -> device::info
{
    ioctl_cmd cmd = {};
    device::info info = { };

    cmd.dev_info.out = (struct device_info_out *)new struct device_info_out;

    auto idx = get_mgmt_loc_from_dev_id(dev_id);
    if (idx < 0) {
        throw std::runtime_error("get_mgmt_loc_from_dev_id failed");
    }

    try {
        info.max_num_queues = qmax.at(idx);
        info.qbase_start = qbase.at(idx);
        mgmt[idx].ioctl(IOCTL_QDMA_DEVINFO, NULL, 0, cmd.dev_info.out, sizeof(struct device_info_out));

        info.device_cap.flr_present = cmd.dev_info.out->flr_present;
        info.device_cap.mm_channel_max = cmd.dev_info.out->num_mm_channels;
        info.device_cap.mm_cmpl_en = cmd.dev_info.out->mm_cmpl_en;
        info.device_cap.mm_en = cmd.dev_info.out->mm_en;
        info.device_cap.num_pfs = cmd.dev_info.out->num_pfs;
        info.device_cap.num_qs = cmd.dev_info.out->num_qs;
        info.device_cap.st_en = cmd.dev_info.out->st_en;

        if (strstr(cmd.dev_info.out->ver_info.qdma_device_type_str, "Soft IP") != NULL)
            info.device_cap.device_type = QDMA_DEVICE_SOFT;
        else if (strstr(cmd.dev_info.out->ver_info.qdma_device_type_str, "Versal CPM4 Hard IP") != NULL)
            info.device_cap.device_type = QDMA_DEVICE_VERSAL;
        else
            info.device_cap.device_type = QDMA_DEVICE_NONE;

        if (strstr(cmd.dev_info.out->ver_info.qdma_versal_ip_type_str, "Versal Hard IP") != NULL)
            info.device_cap.ip_type = QDMA_VERSAL_HARD_IP;
        else if (strstr(cmd.dev_info.out->ver_info.qdma_versal_ip_type_str, "Versal Soft IP") != NULL)
            info.device_cap.ip_type = QDMA_VERSAL_SOFT_IP;
		else if (strstr(cmd.dev_info.out->ver_info.qdma_versal_ip_type_str, "EQDMA Soft IP") != NULL)
            info.device_cap.ip_type = EQDMA_SOFT_IP;
        else if (strstr(cmd.dev_info.out->ver_info.qdma_versal_ip_type_str, "QDMA Soft IP") != NULL)
            info.device_cap.ip_type = QDMA_SOFT_IP;
        else
            info.device_cap.ip_type = QDMA_VERSAL_NONE;

        device_type = info.device_cap.device_type;
        versal_ip_type = info.device_cap.ip_type;

        if ((info.device_cap.device_type == QDMA_DEVICE_VERSAL) &&
            (info.device_cap.ip_type == QDMA_VERSAL_HARD_IP)) {
            info.device_cap.cmpt_ovf_chk_dis = 0;
            info.device_cap.sw_desc_64b = 0;
            info.device_cap.cmpt_trig_count_timer = 0;
            info.device_cap.cmpt_desc_64b = 0;
            if (dev_details[idx].fun_no == 0u) {
                info.max_num_queues = info.max_num_queues - 1;
                info.qbase_start = 1;
            }
        }
        else if (info.device_cap.device_type == QDMA_DEVICE_SOFT) {
            info.device_cap.cmpt_ovf_chk_dis = 1;
            info.device_cap.sw_desc_64b = 1;
            info.device_cap.cmpt_trig_count_timer = 1;
            info.device_cap.cmpt_desc_64b = 1;
        }

        delete cmd.dev_info.out;
    }
    catch (const std::exception& e) {
        delete cmd.dev_info.out;
        std::cout << "Failed to get devinfo from ioctl : " << e.what() << '\n';
    }

    return info;
}

unsigned instance_ext::add_queue(unsigned dev_id, unsigned q_id, unsigned num_q, queue::mode q_mode,
                   queue::direction q_dir, const queue_ext::config& qcfg, bool throw_err)
{
    ioctl_cmd cmd = {};


    cmd.q_conf.in.is_st = q_mode == queue::mode::streaming ? 1 : 0;
    cmd.q_conf.in.qid                   = q_id;
    cmd.q_conf.in.h2c_ring_sz_index     = (unsigned char)qcfg.idx_rngsz;
    cmd.q_conf.in.c2h_ring_sz_index     = (unsigned char)qcfg.idx_rngsz;
    cmd.q_conf.in.c2h_buff_sz_index     = (unsigned char)qcfg.idx_bufsz;
    cmd.q_conf.in.c2h_timer_cnt_index   = (unsigned char)qcfg.idx_tmr;
    cmd.q_conf.in.c2h_th_cnt_index      = (unsigned char)qcfg.idx_cntr;
    cmd.q_conf.in.compl_sz              = static_cast<enum cmpt_desc_sz>(qcfg.cmptsz);
    cmd.q_conf.in.trig_mode             = static_cast<enum trig_mode>(qcfg.trigmode);
    cmd.q_conf.in.desc_bypass_en        = qcfg.desc_bypass;
    cmd.q_conf.in.pfch_bypass_en        = qcfg.pfetch_bypass;
    cmd.q_conf.in.pfch_en               = qcfg.prefetch;
    cmd.q_conf.in.cmpl_ovf_dis          = qcfg.c2h_ovf_chk_dis;
    cmd.q_conf.in.sw_desc_sz            = (unsigned char)qcfg.sw_desc_sz;
    cmd.q_conf.in.en_mm_cmpl            = qcfg.en_mm_cmpt;

    dev_id = get_mgmt_loc_from_dev_id(dev_id);
    unsigned int ret =
        (unsigned int) mgmt[dev_id].ioctl(IOCTL_QDMA_QUEUE_ADD,
        &cmd.q_conf.in, sizeof(cmd.q_conf.in), NULL, 0, throw_err);

    return ret;
}

unsigned instance_ext::remove_queue(unsigned dev_id, unsigned queue_id, queue_ext::direction q_dir, bool throw_err)
{
    ioctl_cmd cmd = {};

    cmd.q_conf.in.qid = queue_id;
    dev_id = get_mgmt_loc_from_dev_id(dev_id);

    unsigned int ret =
        (unsigned int)mgmt[dev_id].ioctl(IOCTL_QDMA_QUEUE_DELETE,
        &cmd.q_conf.in, sizeof(cmd.q_conf.in), NULL, 0, throw_err);

    return ret;
}

unsigned instance_ext::start_queue(unsigned dev_id, unsigned queue_id, queue_ext::mode q_mode,
                              queue_ext::direction q_dir, const queue_ext::config& qcfg, bool throw_err)
{
    ioctl_cmd cmd = {};

    cmd.q_conf.in.qid = queue_id;
    dev_id = get_mgmt_loc_from_dev_id(dev_id);

    unsigned int ret =
        (unsigned int)mgmt[dev_id].ioctl(IOCTL_QDMA_QUEUE_START,
        &cmd.q_conf.in, sizeof(cmd.q_conf.in), NULL, 0, throw_err);

    return ret;
}

unsigned instance_ext::stop_queue(unsigned dev_id, unsigned queue_id, queue_ext::direction q_dir, bool throw_err)
{
    ioctl_cmd cmd = {};

    cmd.q_conf.in.qid = queue_id;
    dev_id = get_mgmt_loc_from_dev_id(dev_id);

    unsigned int ret =
        (unsigned int)mgmt[dev_id].ioctl(IOCTL_QDMA_QUEUE_STOP,
        &cmd.q_conf.in, sizeof(cmd.q_conf.in), NULL, 0, throw_err);

    return ret;
}


void instance_ext::get_global_csr(unsigned dev_id, struct global_csr_conf &csr)
{
    ioctl_cmd cmd = {};

    cmd.csr.out = (struct csr_conf_out *)new struct csr_conf_out;

    if (mgmt[0].ioctl(IOCTL_QDMA_CSR_DUMP, NULL, 0,
        cmd.csr.out, sizeof(struct csr_conf_out))) {

        for (auto i = 0; i < QDMA_GLOBAL_CSR_ARRAY_SZ; ++i)
            csr.ring_sz[i] = cmd.csr.out->ring_sz[i];
        for (auto i = 0; i < QDMA_GLOBAL_CSR_ARRAY_SZ; ++i)
            csr.c2h_buf_sz[i] = cmd.csr.out->c2h_buff_sz[i];
        for (auto i = 0; i < QDMA_GLOBAL_CSR_ARRAY_SZ; ++i)
            csr.c2h_timer_cnt[i] = cmd.csr.out->c2h_timer_cnt[i];
        for (auto i = 0; i < QDMA_GLOBAL_CSR_ARRAY_SZ; ++i)
            csr.c2h_cnt_th[i] = cmd.csr.out->c2h_th_cnt[i];
        for (auto i = 0; i < QDMA_GLOBAL_CSR_ARRAY_SZ; ++i)
            csr.wb_acc = cmd.csr.out->wb_interval;
    }

    delete cmd.csr.out;
}

std::string instance_ext::read_rx_packet(unsigned dev_id, unsigned queue_id)
{
    //validate_queue(dev_id, queue_id);
    ioctl_cmd cmd = {};
    std::string return_str;
    char udd_data[512];
    int print_len, len = 0;


    cmd.udd_info.in.qid = queue_id;
    cmd.udd_info.out = (struct cmpt_udd_info_out *)new struct cmpt_udd_info_out;

    dev_id = get_mgmt_loc_from_dev_id(dev_id);

    if (mgmt[dev_id].ioctl(IOCTL_QDMA_QUEUE_READ_UDD, &cmd.udd_info.in,
        sizeof(cmd.udd_info.in), cmd.udd_info.out, sizeof(struct cmpt_udd_info_out))) {
        for (auto i = 0UL; ((i < cmd.udd_info.out->length) && (i < 512)); i++) {
            print_len = sprintf_s((udd_data + len), (512 - len), "%02x", cmd.udd_info.out->buffer[i]);
            len += print_len;
        }
        return_str = udd_data;
    }

    delete cmd.udd_info.out;

    return return_str;
}

std::string instance_ext::dump_queue_desc(unsigned dev_id, unsigned queue_id, queue_ext::direction q_dir, bool sw_desc, unsigned desc_start, unsigned desc_end) {
    std::string return_str;
    char *desc_data;
    int print_len, len = 0;

    ioctl_cmd cmd = {};

    cmd.desc_info.in.qid = queue_id;
    cmd.desc_info.in.dir = (q_dir == queue_ext::direction::host_to_card) ? QUEUE_DIR_H2C : QUEUE_DIR_C2H;
    cmd.desc_info.in.desc_type = (sw_desc == true) ? RING_DESC : CMPT_DESC;
    cmd.desc_info.in.desc_start = desc_start;
    cmd.desc_info.in.desc_end = desc_end;

    auto buff_sz = (desc_end - desc_start + 1) * 64;
    unsigned int out_size = sizeof(struct desc_dump_info_out) + buff_sz;

    cmd.desc_info.out = (struct desc_dump_info_out *)new unsigned char[out_size];

    cmd.desc_info.out->data_sz = 0;
    cmd.desc_info.out->desc_sz = 0;

    dev_id = get_mgmt_loc_from_dev_id(dev_id);

    if (mgmt[dev_id].ioctl(IOCTL_QDMA_QUEUE_DUMP_DESC, &cmd.desc_info.in, sizeof(cmd.desc_info.in),
        cmd.desc_info.out, out_size)) {
        auto str_sz = (buff_sz * 2) + 100;
        desc_data = new char[str_sz];
        for (auto i = 0UL; ((i < cmd.desc_info.out->data_sz) && (i < str_sz)); i++) {
            if ((i % cmd.desc_info.out->desc_sz) == 0)
                cmd.desc_info.out->pbuffer[i] = cmd.desc_info.out->pbuffer[i] & 0xF0;
            print_len = sprintf_s((desc_data + len), (str_sz - len), "%02x", cmd.desc_info.out->pbuffer[i]);
            len += print_len;
			if ((i + 1) % cmd.desc_info.out->desc_sz == 0) {
				sprintf_s((desc_data + len), (str_sz - len), "\n");
				len += 1;
			}
        }
        return_str = desc_data;

        delete[] desc_data;
    }

    delete[] cmd.desc_info.out;

    return return_str;
}

uint32_t instance_ext::read_cmpt_data(unsigned dev_id, unsigned queue_id, queue_ext::direction q_dir, char *cmpt_data) {
    ioctl_cmd cmd = {};

    auto buf_sz = 10 * 64;
    unsigned int out_size = sizeof(struct cmpt_data_info_out) + buf_sz;

    cmd.cmpt_info.in.qid = queue_id;
    cmd.cmpt_info.out = (struct cmpt_data_info_out *)new unsigned char[out_size];

    char *temp_cmpt_str = NULL;
    int cmpt_idx = 0;
    size_t num_cmpt_entries = 0;
    dev_id = get_mgmt_loc_from_dev_id(dev_id);
    do {
        int print_len, len = 0;

        cmd.cmpt_info.out->ret_len = 0;
        cmd.cmpt_info.out->cmpt_desc_sz = 0;

        if (mgmt[dev_id].ioctl(IOCTL_QDMA_QUEUE_CMPT_READ, &cmd.cmpt_info.in,
            sizeof(cmd.cmpt_info.in), cmd.cmpt_info.out, out_size, false)) {

            if (cmd.cmpt_info.out->ret_len && cmd.cmpt_info.out->cmpt_desc_sz) {
                auto str_sz = (cmd.cmpt_info.out->ret_len * 2) + 100;
                temp_cmpt_str = new char[str_sz];

                auto j = 0;
                auto idx = 0;
                for (auto i = 0UL; ((i < cmd.cmpt_info.out->ret_len) && (i < str_sz)); i++) {
                    if (i % 4 == 0) {
                        j++;
                    }
                    idx = (4 * j) - ((i % 4) + 1);
                    print_len = sprintf_s((temp_cmpt_str + len), (str_sz - len), "%02x", cmd.cmpt_info.out->pbuffer[idx]);
                    len += print_len;
                }

                strncpy(&cmpt_data[cmpt_idx], temp_cmpt_str, len);
                cmpt_idx = cmpt_idx + len;
                num_cmpt_entries += (cmd.cmpt_info.out->ret_len / cmd.cmpt_info.out->cmpt_desc_sz);

                delete[] temp_cmpt_str;
            }
        }
    } while (cmd.cmpt_info.out->ret_len);

    delete[] cmd.cmpt_info.out;

    return (int)num_cmpt_entries;
}

} // namespace qdma
