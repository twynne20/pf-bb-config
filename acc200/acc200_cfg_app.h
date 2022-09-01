/******************************************************************************
*
*   Copyright (c) 2022 Intel.
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*       http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*
*******************************************************************************/

#ifndef _ACC200_CFG_APP_H_
#define _ACC200_CFG_APP_H_

#include "acc100_cfg_app.h"

#define ACC200_BYTES_IN_WORD 4

#define ACC200_NUM_VFS                  16
#define ACC200_NUM_QGRPS                16
#define ACC200_NUM_QGRPS_PER_WORD       8
#define ACC200_NUM_AQS                  16
#define ACC200_MAX_QDEPTH               12
#define MAX_ENQ_BATCH_SIZE              255
#define ACC200_NUM_TMPL  32
#define VF_OFFSET_QOS 16 /* offset in Memory Space specific to QoS Mon */
#define ACC200_TMPL_PRI_0 0x03020100
#define ACC200_TMPL_PRI_1 0x07060504
#define ACC200_TMPL_PRI_2 0x0b0a0908
#define ACC200_TMPL_PRI_3 0x0f0e0d0c
#define ACC200_WORDS_IN_ARAM_SIZE (256 * 1024 / 4)

#define ACC200_SIG_UL_5G       0
#define ACC200_SIG_UL_5G_LAST  4
#define ACC200_SIG_DL_5G      10
#define ACC200_SIG_DL_5G_LAST 11
#define ACC200_SIG_UL_4G      12
#define ACC200_SIG_UL_4G_LAST 16
#define ACC200_SIG_DL_4G      21
#define ACC200_SIG_DL_4G_LAST 23
#define ACC200_SIG_FFT        24
#define ACC200_SIG_FFT_LAST   24

#define ACC200_NUM_ACCS       5 /* FIXMEFFT */
#define ACC200_ACCMAP_0       0
#define ACC200_ACCMAP_1       2
#define ACC200_ACCMAP_2       1
#define ACC200_ACCMAP_3       3
#define ACC200_ACCMAP_4       4
#define ACC200_PF_VAL         2

/* ACC200 Configuration */
#define ACC200_FABRIC_MODE      0x8000103
#define ACC200_CFG_DMA_ERROR    0x3DF
#define ACC200_CFG_AXI_CACHE    0x11
#define ACC200_CFG_QMGR_HI_P    0x0F0F
#define ACC200_CLOCK_GATING_EN  0x30000
#define ACC200_ENGINE_OFFSET    0x1000
#define ACC200_MS_IN_US         (1000)
#define ACC200_FFT_CFG_0        0x2001
#define ACC200_FFT_RAM_EN       0x80000000
#define ACC200_FFT_RAM_DIS      0x0
#define ACC200_FFT_RAM_SIZE     512
#define ACC200_FFT_PAGE_SIZE    512
#define ACC200_FFT_FIST_OFFSET  256
#define ACC200_CLK_EN           0x00000881
#define ACC200_CLK_DIS          0x01F00881
#define ACC200_PG_MASK_0        0x1F
#define ACC200_PG_MASK_1        0xF
#define ACC200_PG_MASK_2        0x1
#define ACC200_PG_MASK_3        0x0
#define ACC200_PG_MASK_FFT      1
#define ACC200_PG_MASK_4GUL     4
#define ACC200_PG_MASK_5GUL     8
#define ACC200_PROC_TIMEOUT     0x2000 /* 1ms */

#define ACC200_LUT_SIZE (16*(16+32+64+128+256+512+1024))

#define ACC200_INFO_RING_NUM_ENTRIES 1024

#define ACC200_PERMON_CTRL_REG_VF_OFFSET 256

#define ACC200_FFT_FIRST_OFFSET  256

/* Mask used to calculate an index in an Info Ring array (not a byte offset) */
#define ACC200_INFO_RING_MASK          (ACC200_INFO_RING_NUM_ENTRIES-1)
#define ACC200_INFO_RING_PTR_MASK      ((ACC200_INFO_RING_NUM_ENTRIES*4)-1)

#define INFO_RING_DET_INFO		GENMASK(15, 0)
#define INFO_RING_DET_INFO_AQ_ID	GENMASK(3, 0)
#define INFO_RING_DET_INFO_QG_ID	GENMASK(7, 4)
#define INFO_RING_DET_INFO_VF_ID	GENMASK(13, 8)
#define INFO_RING_DET_INFO_FEC_SLICE	GENMASK(7, 0)
#define INFO_RING_DET_INFO_VF		GENMASK(13, 8)
#define INFO_RING_INT_NB		GENMASK(22, 16)
#define INFO_RING_MSI_0			BIT(23)
#define INFO_RING_VF2PF			GENMASK(29, 24)
#define INFO_RING_LOOP			BIT(30)
#define INFO_RING_VALID			BIT(31)

#define ACC200_5GUL_ENGS 5
#define ACC200_5GDL_ENGS 2
#define ACC200_FFT_ENGS 1
#define ACC200_PMON_OFF_1 256
#define ACC200_PMON_OFF_2 16

/**
 * Structure to pass ACC200 configuration.
 * Note: all VF Bundles will have the same configuration.
 */
struct acc200_conf {
	bool pf_mode_en;  /**< 1 if PF is used for dataplane, 0 for VFs */
	/** 1 if input '1' bit is represented by a positive LLR value, 0 if '1'
	 * bit is represented by a negative value.
	 */
	bool input_pos_llr_1_bit;
	/** 1 if output '1' bit is represented by a positive value, 0 if '1'
	 * bit is represented by a negative value.
	 */
	bool output_pos_llr_1_bit;
	uint16_t num_vf_bundles;  /**< Number of VF bundles to setup */
	struct q_topology_t q_ul_4g;  /**< Uplink queues */
	struct q_topology_t q_dl_4g;  /**< Downlink queues */
	struct q_topology_t q_ul_5g;  /**< Uplink queues */
	struct q_topology_t q_dl_5g;  /**< Downlink queues */
	struct q_topology_t q_fft;  /**< FFT queues */
	/** Uplink arbitration configuration */
	struct arbitration_t arb_ul_4g[ACC200_NUM_VFS];
	/** Downlink arbitration configuration */
	struct arbitration_t arb_dl_4g[ACC200_NUM_VFS];
	/** Uplink arbitration configuration */
	struct arbitration_t arb_ul_5g[ACC200_NUM_VFS];
	/** Downlink arbitration configuration */
	struct arbitration_t arb_dl_5g[ACC200_NUM_VFS];
	/** FFT arbitration configuration */
	struct arbitration_t arb_fft[ACC200_NUM_VFS];
};

typedef struct {
	char *name;
	bool use_det_info;
	bool fatal;
} acc200_ir_int_type_info;

#define ACC200_INFO_RING_SIZE (ACC200_INFO_RING_NUM_ENTRIES * \
		sizeof(uint32_t))

/*
 * Configure ACC200
 */

extern int
acc200_parse_conf_file(const char *file_name, struct acc200_conf *acc200_conf);

#endif /* _ACC200_CFG_APP_H_ */
