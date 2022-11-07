#ifndef QDMA_TEST_TEST_DATA_GENERATOR_H_
#define QDMA_TEST_TEST_DATA_GENERATOR_H_

#include <cstdint>
#include <stddef.h>

#include <xlnx_pci.h>
#include <xlnx_util.h>

#if LINUX
#include <qdma/qdma_nl.h>
#endif

#include <qdma_device.h>
#include <qdma_queue_abs.h>

enum bypass_mode {
	NO_BYPASS_MODE,     /* No Bypass */
	CACHE_BYPASS_MODE,	/* Cache bypass*/
	SIMPLE_BYPASS_MODE,	/* Simple bypass */
	DESC_BYPASS_MODE,	/* desc bypass mode for MM */
	NUM_BYPASS_MODES
};

/// The user logic part of the example design for the QDMA IP implements varies features for testing
/// and demonstration purposes.
///     - A data pattern checker for ST H2C transfers
///     - A data pattern generator for ST C2H transfers
///     - Various control bits
/// Access to the user logic is given via the user BAR. Register map can be found here:
/// xinc/acnd/engineering/ip/pcie/PCIe%20Gen4/AXI4MM/DMA/Everest/QDMA%20Specs/QDMA_Docs/QDMA%20user%20programming.docx
class example_design_ctrl {
public:

    static constexpr size_t bram_size = 512_kB;

    explicit example_design_ctrl(qdma::device& qdev)
        : user_bar(*qdev.user_bar) {
    }

    //---------- data pattern checker specific ----------

    bool check_h2c(const uint32_t qid, bool is_zero_byte_xfer) {
        const auto match_reg = user_bar.read<uint32_t>(0x10);
        const auto match_qid = get_bits(match_reg, 4, 12); // bits 4-15 = qid
        const bool zero_byte_match = is_zero_byte_xfer? is_bit_set(match_reg, 1) : true;
        return (match_qid == qid) && zero_byte_match && check_h2c_match(match_reg); // bit 0 = match
    }

    bool check_h2c_match() {
        const auto match_reg = user_bar.read<uint32_t>(0x10);
        return check_h2c_match(match_reg);
    }

    bool check_h2c_match(uint32_t match_reg) {
        return is_bit_set(match_reg, 0);
    }

    void st_c2h_gen_marker_resp() {
    	user_bar.write<uint32_t>(0x8, 0x22);
    }

    void st_c2h_marker_dis() {
    	user_bar.write<uint32_t>(0x8, 0x0);
    }

    bool check_marker_completion() {
    	const auto stat_reg = user_bar.read<uint32_t>(0x18);
    	return is_bit_set(stat_reg, 0);
    }

    void reset_h2c() {
        user_bar.write<uint32_t>(0xC, 0x1); // clear match for h2c transfer pattern checker
    }

    //---------- data pattern generator specific ----------

    using pattern_t = uint16_t;

    void set_queue(const uint32_t qid) {
        user_bar.write<uint32_t>(0x0, qid);
    }

    void configure_c2h(const uint32_t qid, const uint32_t packet_size,
            const uint32_t num_packets) {
        set_queue(qid);
        user_bar.write<uint32_t>(0x4, packet_size);
        user_bar.write<uint32_t>(0x20, num_packets);
    }

    void generate_packets() {
        uint32_t regval = user_bar.read<uint32_t>(0x8);

        regval = 0x02;
        user_bar.write<uint32_t>(0x8, regval);
    }

    void reset_pkt_ctrl() {
        user_bar.write<uint32_t>(0x8, 0x00);
    }

    void set_wrb_desc_size(xnl_st_c2h_cmpt_desc_size wrb_sz) {
        uint32_t wrbsz_cfg = 0x00;

        switch (wrb_sz) {
            default:

            case XNL_ST_C2H_CMPT_DESC_SIZE_8B:
                wrbsz_cfg = 0x00;
                break;
            case XNL_ST_C2H_CMPT_DESC_SIZE_16B:
                wrbsz_cfg = 0x01;
                break;
            case XNL_ST_C2H_CMPT_DESC_SIZE_32B:
                wrbsz_cfg = 0x02;
                break;
            case XNL_ST_C2H_CMPT_DESC_SIZE_64B:
                wrbsz_cfg = 0x03;
                break;
        }

        user_bar.write<uint32_t>(0x50, wrbsz_cfg);
    }


    //---------- other features ----------

    void set_bypass_mode(qdma::queue::mode mode, qdma::queue::direction dir, bypass_mode bypass) {
        uint32_t reg_val = 0x00;

        if(mode == qdma::queue::mode::memory_mapped) {
        	switch (dir) {
        		case qdma::queue::direction::host_to_card:
        		{
    	        	if( bypass == DESC_BYPASS_MODE)
    	        		reg_val = 0x1;
    	        	else
    	        		reg_val = 0x0;

    	        	break;
        		}
        		case qdma::queue::direction::card_to_host:
        		{
    	        	if( bypass == DESC_BYPASS_MODE)
    	        		reg_val = 0x2;
    	        	else
    	        		reg_val = 0x0;

    	        	break;
        		}
        		case qdma::queue::direction::both:
        		{
    	        	if( bypass == DESC_BYPASS_MODE)
    	        		reg_val = 0x3;
    	        	else
    	        		reg_val = 0x0;

    	        	break;
        		}
        		default:
        			break;
        	}
        }
        else
        {
            switch(dir) {
    			case qdma::queue::direction::host_to_card:
    			{
    				switch (bypass) {
    					default:
    					case NO_BYPASS_MODE:
    						reg_val = 0x00;
    						break;
    					case CACHE_BYPASS_MODE:
    						reg_val = 0x1;
    						break;
    					case SIMPLE_BYPASS_MODE:
    						reg_val = 0x1;
    						break;
    				}
    				break;
    			}
    			case qdma::queue::direction::card_to_host:
    			{
    				switch (bypass) {
    					default:
    					case NO_BYPASS_MODE:
    						reg_val = 0x00;
    						break;
    					case CACHE_BYPASS_MODE:
    						reg_val = 0x2;
    						break;
    					case SIMPLE_BYPASS_MODE:
    						reg_val = 0x4;
    						break;
    				}
    				break;
    			}
    			case qdma::queue::direction::both:
    			{
    				switch (bypass) {
    					default:
    					case NO_BYPASS_MODE:
    						reg_val = 0x00;
    						break;
    					case CACHE_BYPASS_MODE:
    						reg_val = 0x3;
    						break;
    					case SIMPLE_BYPASS_MODE:
    						reg_val = 0x5;
    						break;
    				}
    				break;
    			}
    			default:
    				break;
            }
        }

        user_bar.write<uint32_t>(0x90, reg_val);
    }

    void set_desc_bypass_imm_data_loopback(bool on) {
    	user_bar.write<uint32_t>(0x90, on ? 0x6 : 0x0);
    }

    void set_st_loopback(bool on) {
        uint32_t regval = user_bar.read<uint32_t>(0x8);

        regval &= ~0x01;
        regval |= (on ? 0x1 : 0x0);
        user_bar.write<uint32_t>(0x8, regval);
    }

    void set_imm_data_en(bool imm_on, int device_type, int ip_type) {
         uint32_t regval = 0;

         if ((device_type == QDMA_DEVICE_VERSAL_CPM4)
        		 && (ip_type == QDMA_VERSAL_HARD_IP))
			 regval = (imm_on ? 0x06 : 0x00);
         else
			 regval = (imm_on ? 0x04 : 0x00);

         user_bar.write<uint32_t>(0x8, regval);
     }


    void set_imm_data(int idx, int val) {
       user_bar.write<uint32_t>(0x30 + (4*idx), val);
    }

    /// Initiates a soft reset of the QDMA IP
    /// This means that any csr, fmap or queue programming needs to be redone (i.e. reload the driver)
    void reset_ip() {
        user_bar.write<uint32_t>(0xA0, 0x1);
    }

    void set_prefetch_tag(const uint32_t qid, const uint32_t tag) {
        uint32_t regval = 0;

        regval = (qid & 0x7FF) << 16 | (tag & 0x7F);
        user_bar.write<uint32_t>(0x24, regval);
    }

    int user_bar_reg_read() {
        uint32_t regval = 0;
        regval = user_bar.read<uint32_t>(0x0);
        std::cout << "Reg: 0x0: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x4);
        std::cout << "Reg: 0x4: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x8);
        std::cout << "Reg: 0x8: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x10);
        std::cout << "Reg: 0x10: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x18);
        std::cout << "Reg: 0x18: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x20);
        std::cout << "Reg: 0x20: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x24);
        std::cout << "Reg: 0x24: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x30);
        std::cout << "Reg: 0x30: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x34);
        std::cout << "Reg: 0x34: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x38);
        std::cout << "Reg: 0x38: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x3c);
        std::cout << "Reg: 0x3c: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x40);
        std::cout << "Reg: 0x40: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x44);
        std::cout << "Reg: 0x44: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x48);
        std::cout << "Reg: 0x48: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x4c);
        std::cout << "Reg: 0x4c: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x50);
        std::cout << "Reg: 0x50: " << regval <<"\n";
        regval = 0;

        regval = user_bar.read<uint32_t>(0x90);
        std::cout << "Reg: 0x90: " << regval <<"\n";

	return 0;
    }


private:
    pcie_bar& user_bar;
};



#endif /* QDMA_TEST_TEST_DATA_GENERATOR_H_ */
