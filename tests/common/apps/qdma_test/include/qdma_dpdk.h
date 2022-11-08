/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2017-2018 Xilinx, Inc. All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Xilinx, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "rte_pmd_qdma.h"

#define DEFAULT_QDMA_CMPT_DESC_LEN (RTE_PMD_QDMA_CMPT_DESC_LEN_8B)
#define RX_TX_MAX_RETRY			(1000)

#define  QDMA_DEVICE_SOFT               RTE_PMD_QDMA_DEVICE_SOFT
#define  QDMA_DEVICE_VERSAL_CPM4         RTE_PMD_QDMA_DEVICE_VERSAL_CPM4
#define  QDMA_DEVICE_VERSAL_CPM5         RTE_PMD_QDMA_DEVICE_VERSAL_CPM5

#define  QDMA_VERSAL_HARD_IP        RTE_PMD_QDMA_VERSAL_HARD_IP
#define  QDMA_VERSAL_SOFT_IP        RTE_PMD_QDMA_VERSAL_SOFT_IP
#define  QDMA_SOFT_IP               RTE_PMD_QDMA_SOFT_IP
#define  EQDMA_SOFT_IP              RTE_PMD_EQDMA_SOFT_IP


enum xnl_st_c2h_cmpt_desc_size {
	XNL_ST_C2H_CMPT_DESC_SIZE_8B = 8,
	XNL_ST_C2H_CMPT_DESC_SIZE_16B = 16,
	XNL_ST_C2H_CMPT_DESC_SIZE_32B = 32,
	XNL_ST_C2H_CMPT_DESC_SIZE_64B = 64
};

enum dma_data_direction {
	DMA_BIDIRECTIONAL = 0,
	DMA_TO_DEVICE = 1,
	DMA_FROM_DEVICE = 2,
	DMA_NONE = 3,
};

extern "C" uint32_t qdma_pci_read_reg(struct rte_eth_dev *dev, uint32_t bar, uint32_t reg);
extern "C" void qdma_pci_write_reg(struct rte_eth_dev *dev, uint32_t bar,
                    uint32_t reg, uint32_t val);
