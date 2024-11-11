/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (c) 2024 Realtek Semiconductor Corp. All rights reserved.
 *
 * This software is a confidential and proprietary property of Realtek
 * Semiconductor Corp. Disclosure, reproduction, redistribution, in
 * whole or in part, of this work and its derivatives without express
 * permission is prohibited.
 *
 * Realtek Semiconductor Corp. reserves the right to update, modify, or
 * discontinue this software at any time without notice. This software is
 * provided "as is" and any express or implied warranties, including, but
 * not limited to, the implied warranties of merchantability and fitness for
 * a particular purpose are disclaimed. In no event shall Realtek
 * Semiconductor Corp. be liable for any direct, indirect, incidental,
 * special, exemplary, or consequential damages (including, but not limited
 * to, procurement of substitute goods or services; loss of use, data, or
 * profits; or business interruption) however caused and on any theory of
 * liability, whether in contract, strict liability, or tort (including
 * negligence or otherwise) arising in any way out of the use of this software,
 * even if advised of the possibility of such damage.
 */

#ifndef _CLK_RTS3917_H_
#define _CLK_RTS3917_H_

#include <clk-uclass.h>

#define USBPHY_HOST_CLK_EN (1 << 1)
#define USBPHY_DEV_CLK_EN  (1 << 0)
#define CLK_ENABLE	   0x1000000

#define CLK_CHANGE_R	 (0)
#define UART_CLK_LP_EN_R (0x04)
#define P1BUS_CLK_CFG_R	 (0x08)
#define DRAM_CLK_CFG_R	 (0x0c)
#define CPU_CLK_CFG_R	 (0x10)
#define XB2_CLK_CFG_R	 (0x14)
#define BUS_CLK_CFG_R	 (0x18)
#define I2S_CLK_CFG_R	 (0x1c)
#define CIPHER_CLK_CFG_R (0x20)
#define UART_CLK_CFG_R	 (0x28)
#define I2C_CLK_CFG_R	 (0x2c)

#define RTC32K_DIV_CFG0_R (0x3c)
#define RTC32K_DIV_CFG1_R (0x40)
#define RTC32K_DIV_CFG2_R (0x44)
#define RTC_CLK_CFG_R	  (0x48)
#define USBPHY_CLK_CFG_R  (0x4c)
#define JPEG_CLK_CFG_R	  (0x50)

#define ISP_SCAN_CLK_CFG_R  (0x58)
#define MIPI_SCAN_CLK_CFG_R (0x5c)
#define SPDIF_CLK_CFG_R	    (0x60)

#define CODEC_CLK_CFG_R (0x68)

#define GE_CLK_EN_R	       (0x78)
#define BWT_CLK_EN_R	       (0x7c)
#define H265_ACLK_CFG_R	       (0x80)
#define H265_BCLK_CFG_R	       (0x84)
#define H265_CCLK_CFG_R	       (0x88)
#define SSOR_HCLK_CFG_R	       (0x8C)
#define SSOR_CLK_OE_R	       (0x90)
#define RSA_CLK_EN_R	       (0xA0)
#define SHA_CLK_EN_R	       (0xA4)
#define NN_BUS_CLK_CFG_R       (0xB0)
#define NN_CORE_CLK_CFG_R      (0xB4)
#define NN_SH_CLK_CFG_R	       (0xB8)
#define TRNG_CLK_CFG_R	       (0xBC)
#define LCDC_DRAM_CLK_CFG_R    (0xC0)
#define ETHERNET_CLK_CFG_R     (0xC4)
#define EFUSE_CLK_CFG_R	       (0xC8)
#define MAC_BYPASS_CLK_CFG_R   (0xCC)
#define JPEG_DRAM_CLK_CFG_R    (0xD0)
#define MIPI_TX_CFG_R	       (0xD4)
#define DMA_CLK_CFG_R	       (0xD8)
#define MIPI_TX_LOW_CLK_CFG_R  (0xDC)
#define SD0_CRC_CLK_CFG_REG    (0xE0)
#define SD0_SAMPLE_CLK_CFG_REG (0xE4)
#define SD0_PUSH_CLK_CFG_REG   (0xE8)
#define SD0_DDR_CLK_CFG_REG    (0xEC)
#define SD1_CRC_CLK_CFG_REG    (0xF0)
#define SD1_SAMPLE_CLK_CFG_REG (0xF4)
#define SD1_PUSH_CLK_CFG_REG   (0xF8)
#define SD1_DDR_CLK_CFG_REG    (0xFC)

#define UART1_CLK_CFG_R	     (0x104)
#define UART2_CLK_CFG_R	     (0x108)
#define I2C1_CLK_CFG_R	     (0x10C)
#define ISP_ZOOM_CLK_CFG_REG (0x110)
#define CPU_TRC_CLK_CFG_REG  (0x114)
#define SSI_CLK_CFG_REG	     (0x118)

#define BSP_CLK_GPLL0_BASE_R (0x000)
#define BSP_CLK_GPLL1_BASE_R (0x100)
#define BSP_CLK_GPLL2_BASE_R (0x200)
#define BSP_CLK_GPLL3_BASE_R (0x300)

#define GPLL_CTRL      0x00
#define GPLL_CFG       0x04
#define GPLL_SCCG_CFG0 0x08
#define GPLL_SCCG_CFG1 0x0C
#define GPLL_STATUS    0x10
#define GPLL_SCCG_CFG2 0x14
#define GPLL_SCCG_CFG3 0x18

#define PPOW_LDO      (1 << 1)
#define GPLL_EN	      (1 << 0)
#define SYSPLL_CK_RDY (1 << 0)
#define REG_EN_SSC    (1 << 31)

#define REG_PIF_EN_LV_LDO (1 << 8)
#define REG_PIF_H_CMU_POW (1 << 0)
#define REG_POW_PIF	  (1 << 5)

#define SD1_CK_CHANGE	0x9
#define SD0_CK_CHANGE	0x8
#define BUS_CK_CHANGE	0x7
#define XB2_CK_CHANGE	0x6
#define CPU_CK_CHANGE	0x5
#define DRAM_CK_CHANGE	0x4
#define P1BUS_CK_CHANGE 0x3
#define CK_CHANGE_NULL	0

#define BIG_SHORT_NUM 2
#define BIG_LONG_NUM  4

#define PLL0_1G	  1000000000
#define PLL0_800M 800000000

static const char *rlx_root_parent_names[] = {
	"clk25mhz",
};

static const char *rlx_names_p1bus_div[] = { "usb_pll_2", "gpll0_3", "gpll1_3",
					     "gpll2_3" };

static const char *rlx_names_p1bus_dec[] = { "p1bus_ck" };

static const char *rlx_names_bus_div[] = { "usb_pll_2", "gpll0_2", "gpll1_3",
					   "gpll2_2" };

static const char *rlx_names_bus_dec[] = { "bus_ck" };

static const char *rlx_names_cpu_div[] = {
	"usb_pll",
	"gpll0",
	"gpll1",
	"gpll2",
};

static const char *rlx_names_cpu_dec[] = { "cpu_ck" };

static const char *rlx_names_dram_div[] = { "usb_pll_2", "gpll0_3", "gpll1_3",
					    "gpll2_3" };

static const char *rlx_names_dram_dec[] = { "dram_ck" };

static const char *rlx_names_h265_aclk[] = { "dram_ck" };

static const char *rlx_names_h265_bclk_div[] = { "usb_pll_2", "gpll0_2",
						 "gpll1_3", "gpll2_2" };

static const char *rlx_names_h265_bclk_dec[] = { "h265_bclk_ck" };

static const char *rlx_names_h265_cclk_div[] = { "usb_pll_2", "gpll0_2",
						 "gpll1_3", "gpll2_2" };

static const char *rlx_names_h265_cclk_dec[] = { "h265_cclk_ck" };

static const char *rlx_names_nncore_div[] = { "usb_pll_2", "gpll0", "usb_pll",
					      "gpll1_2" };

static const char *rlx_names_nncore_dec[] = { "nncore_ck" };

static const char *rlx_names_isp_div[] = { "usb_pll_3", "gpll0_3", "gpll1_3",
					   "gpll0_5" };

static const char *rlx_names_isp_dec[] = { "isp_ck" };

static const char *rlx_names_jpeg_div[] = { "usb_pll", "gpll0_3", "gpll1_3",
					    "gpll2_2" };

static const char *rlx_names_jpeg_dec[] = { "jpeg_ck" };

static const char *rlx_names_mipi_div[] = { "usb_pll", "gpll0_3", "gpll1_3",
					    "gpll2_2" };

static const char *rlx_names_mipi_dec[] = { "mipi_ck" };

static const char *rlx_names_ssor_hclk_div[] = { "usb_pll_5", "gpll1_5",
						 "gpll1_2" };

static const char *rlx_names_codec_div[] = { "usb_pll_5", "gpll2_2", "gpll2_5",
					     "usb_pll_3" };

static const char *rlx_names_i2s_div[] = {
	"usb_pll_5",
	"gpll2_2",
	"gpll2_5",
	"usb_pll_3",
};

static const char *rlx_names_spdif_div[] = { "usb_pll_5", "gpll2_2", "gpll2_5",
					     "usb_pll_3" };

static const char *rlx_names_i2c_div[] = { "usb_pll_5", "gpll2_2", "gpll2_5",
					   "usb_pll_3" };

static const char *rlx_names_uart_div[] = { "usb_pll_5", "gpll0_2", "gpll0_3",
					    "usb_pll_2" };

static const char *rlx_names_xb2_div[] = { "usb_pll_2", "gpll0_2", "gpll0_3" };

static const char *rlx_names_macbypass_div[] = { "gpll0_2", "gpll1", "gll2_2",
						 "gpll3_2" };

static const char *rlx_names_mipitx_lowdiv[] = { "usb_pll", "gpll0", "gpll1_2",
						 "gpll1_3" };

static const char *rlx_names_isp_zoom_div[] = { "usb_pll", "gpll0_3", "gpll1_3",
						"gpll2_3" };

static const char *rlx_names_isp_zoom_dec[] = { "isp_zoom_ck" };

static const char *rlx_names_sd_crc_clk_div[] = { "usb_pll_5", "gpll0_3",
						  "gpll0_5", "usb_pll_3" };

static const char *rlx_names_sd_sam_clk_div[] = { "usb_pll_5", "gpll0_3",
						  "gpll0_5", "usb_pll_3" };

static const char *rlx_names_sd_pu_clk_div[] = { "usb_pll_5", "gpll0_3",
						 "gpll0_5", "usb_pll_3" };

static const char *rlx_names_i2c1_div[] = { "usb_pll_5", "gpll2_2", "gpll2_5",
					    "usb_pll_3" };

static const char *rlx_names_ssi_div[] = { "usb_pll_5", "gpll0_2", "gpll0_3",
					   "gpll0_5" };

static const char *rlx_names_v[] = { "dummy" };

struct rts3917_clk_priv {
	void __iomem *clk_mapped_addr;
	void __iomem *pll_mapped_addr;
	int num_clks;
};

struct clk_rlx {
	const char *name;
	const char *const *parent_names;
	const char *const *mux_parent_names;
	const struct clk_div_table *div_array;
	u8 num_parents;
	u8 mux_num_parents;
	u32 clkreg;
	u32 clk_change;
	u32 rate;
	u32 *reg_v;
	u32 reg_i;
	u32 gate_id;
	u32 mux_id;
	u32 div_id;
	u32 bit_idx;
};

struct rts_divider {
	struct clk clk;
	void __iomem *reg;
	u8 shift;
	u8 width;
	u8 flags;
	const struct clk_div_table *table;
	void __iomem *base_addr;
	u32 clk_change_bit;
};

#define to_rts_divider(_clk) container_of(_clk, struct rts_divider, clk)

static u32 clk_reg_v[RLX_CLK_NUM_SIZE];

static const struct clk_div_table div_array_short[] = { { 0x0, 1 },
							{ 0x1, 2 },
							{ 0x2, 4 },
							{ 0x3, 6 },
							{ 0 } };

static const struct clk_div_table div_array[] = {
	{ 0x0, 1 },  { 0x1, 2 },  { 0x2, 4 },  { 0x3, 6 }, { 0x4, 8 },
	{ 0x5, 10 }, { 0x6, 12 }, { 0x7, 14 }, { 0 }
};

static const struct clk_div_table div_array_long[] = {
	{ 0x0, 1 },  { 0x1, 2 },  { 0x2, 4 },  { 0x3, 6 },  { 0x4, 8 },
	{ 0x5, 10 }, { 0x6, 12 }, { 0x7, 14 }, { 0x8, 16 }, { 0x9, 18 },
	{ 0xA, 20 }, { 0xB, 22 }, { 0xC, 24 }, { 0xD, 26 }, { 0xE, 28 },
	{ 0xF, 30 }, { 0 }
};

#define RTS_CLK_EN_SHIFT      24
#define RTS_CLK_DIV_SHIFT     2
#define RTS_CLK_SRC_SEL_SHIFT 0

#define NO_RTS_MUX  1
#define NO_RTS_DIV  1
#define NO_RTS_GATE 1

#define DEFINE_CLK_RLX(_name, _parent_names, _mux_parent_names, _div_array, \
		       _clk_reg, _clk_change, _bit_idx)                     \
	static struct clk_rlx _name = {                                     \
		.name = #_name,                                             \
		.parent_names = _parent_names,                              \
		.num_parents = ARRAY_SIZE(_parent_names),                   \
		.mux_parent_names = _mux_parent_names,                      \
		.mux_num_parents = ARRAY_SIZE(_mux_parent_names),           \
		.div_array = _div_array,                                    \
		.clkreg = _clk_reg,                                         \
		.clk_change = _clk_change,                                  \
		.reg_v = clk_reg_v,                                         \
		.reg_i = (((u32)_clk_reg & 0x1ff) >> 2),                    \
		.gate_id = 0,                                               \
		.mux_id = 0,                                                \
		.div_id = 0,                                                \
		.bit_idx = _bit_idx                                         \
	}

#define DEFINE_CLK_RLX_GATE_ONLY(_name, _parent_names, _clk_reg, _clk_change, \
				 _bit_idx)                                    \
	static struct clk_rlx _name = {                                       \
		.name = #_name,                                               \
		.parent_names = _parent_names,                                \
		.num_parents = ARRAY_SIZE(_parent_names),                     \
		.clkreg = _clk_reg,                                           \
		.clk_change = _clk_change,                                    \
		.reg_v = clk_reg_v,                                           \
		.reg_i = (((u32)_clk_reg & 0x1ff) >> 2),                      \
		.gate_id = 0,                                                 \
		.mux_id = NO_RTS_MUX,                                         \
		.div_id = NO_RTS_DIV,                                         \
		.bit_idx = _bit_idx                                           \
	}

#define DEFINE_CLK_RLX_NO_MUX(_name, _parent_names, _div_array, _clk_reg, \
			      _clk_change, _bit_idx)                      \
	static struct clk_rlx _name = {                                   \
		.name = #_name,                                           \
		.parent_names = _parent_names,                            \
		.num_parents = ARRAY_SIZE(_parent_names),                 \
		.div_array = _div_array,                                  \
		.clkreg = _clk_reg,                                       \
		.clk_change = _clk_change,                                \
		.reg_v = clk_reg_v,                                       \
		.reg_i = (((u32)_clk_reg & 0x1ff) >> 2),                  \
		.gate_id = 0,                                             \
		.mux_id = NO_RTS_MUX,                                     \
		.div_id = 0,                                              \
		.bit_idx = _bit_idx                                       \
	}

#define DEFINE_CLK_RLX_GPLL(_name, _parent_names, _clk_reg) \
	static struct clk_rlx _name = {                     \
		.name = #_name,                             \
		.parent_names = _parent_names,              \
		.num_parents = ARRAY_SIZE(_parent_names),   \
		.clkreg = _clk_reg,                         \
		.reg_v = clk_reg_v,                         \
		.reg_i = (((u32)_clk_reg & 0x1ff) >> 2),    \
		.gate_id = 0,                               \
		.mux_id = NO_RTS_MUX,                       \
		.div_id = 0,                                \
	}

DEFINE_CLK_RLX_GPLL(gpll0, rlx_root_parent_names, BSP_CLK_GPLL0_BASE_R);
DEFINE_CLK_RLX_GPLL(gpll1, rlx_root_parent_names, BSP_CLK_GPLL1_BASE_R);
DEFINE_CLK_RLX_GPLL(gpll2, rlx_root_parent_names, BSP_CLK_GPLL2_BASE_R);
DEFINE_CLK_RLX_GPLL(gpll3, rlx_root_parent_names, BSP_CLK_GPLL3_BASE_R);

DEFINE_CLK_RLX_GATE_ONLY(dma_ck, rlx_root_parent_names, DMA_CLK_CFG_R,
			 CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX_GATE_ONLY(usbphy_host_ck, rlx_root_parent_names,
			 USBPHY_CLK_CFG_R, CK_CHANGE_NULL, 1);
DEFINE_CLK_RLX_GATE_ONLY(usbphy_dev_ck, rlx_root_parent_names, USBPHY_CLK_CFG_R,
			 CK_CHANGE_NULL, 0);
DEFINE_CLK_RLX_GATE_ONLY(ethernet_ck, rlx_root_parent_names, ETHERNET_CLK_CFG_R,
			 CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_NO_MUX(p1bus_ck_dec, rlx_names_p1bus_dec, div_array_short,
		      P1BUS_CLK_CFG_R, P1BUS_CK_CHANGE, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX(p1bus_ck, rlx_names_v, rlx_names_p1bus_div, div_array_short,
	       P1BUS_CLK_CFG_R, P1BUS_CK_CHANGE, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_NO_MUX(cpu_ck_dec, rlx_names_cpu_dec, div_array_short,
		      CPU_CLK_CFG_R, CPU_CK_CHANGE, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX(cpu_ck, rlx_names_v, rlx_names_cpu_div, div_array_short,
	       CPU_CLK_CFG_R, CPU_CK_CHANGE, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_NO_MUX(jpeg_ck_dec, rlx_names_jpeg_dec, div_array_short,
		      JPEG_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX(jpeg_ck, rlx_names_v, rlx_names_jpeg_div, div_array_short,
	       JPEG_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_NO_MUX(bus_ck_dec, rlx_names_bus_dec, div_array_short,
		      BUS_CLK_CFG_R, BUS_CK_CHANGE, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX(bus_ck, rlx_names_v, rlx_names_bus_div, div_array_short,
	       BUS_CLK_CFG_R, BUS_CK_CHANGE, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_NO_MUX(dram_ck_dec, rlx_names_dram_dec, div_array_short,
		      DRAM_CLK_CFG_R, DRAM_CK_CHANGE, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX(dram_ck, rlx_names_v, rlx_names_dram_div, div_array_short,
	       DRAM_CLK_CFG_R, DRAM_CK_CHANGE, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_NO_MUX(isp_ck_dec, rlx_names_isp_dec, div_array_short,
		      ISP_SCAN_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX(isp_ck, rlx_names_v, rlx_names_isp_div, div_array_short,
	       ISP_SCAN_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_NO_MUX(mipi_ck_dec, rlx_names_mipi_dec, div_array_short,
		      MIPI_SCAN_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX(mipi_ck, rlx_names_v, rlx_names_mipi_div, div_array_short,
	       MIPI_SCAN_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(i2c_ck, rlx_names_v, rlx_names_i2c_div, div_array_short,
	       I2C_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(xb2_ck, rlx_names_v, rlx_names_xb2_div, div_array, XB2_CLK_CFG_R,
	       XB2_CK_CHANGE, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(uart_ck, rlx_names_v, rlx_names_uart_div, div_array,
	       UART_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(i2s_ck, rlx_names_v, rlx_names_i2s_div, div_array_long,
	       I2S_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(spdif_ck, rlx_names_v, rlx_names_spdif_div, div_array_long,
	       SPDIF_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(codec_ck, rlx_names_v, rlx_names_codec_div, div_array_long,
	       CODEC_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_GATE_ONLY(h265_ck, rlx_names_v, H265_ACLK_CFG_R, CK_CHANGE_NULL,
			 RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_NO_MUX(h265_bclk_dec, rlx_names_h265_bclk_dec, div_array_short,
		      H265_BCLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX(h265_bclk_ck, rlx_names_v, rlx_names_h265_bclk_div,
	       div_array_short, H265_BCLK_CFG_R, CK_CHANGE_NULL,
	       RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_NO_MUX(h265_cclk_dec, rlx_names_h265_cclk_dec, div_array_short,
		      H265_CCLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX(h265_cclk_ck, rlx_names_v, rlx_names_h265_cclk_div,
	       div_array_short, H265_CCLK_CFG_R, CK_CHANGE_NULL,
	       RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(ssor_hclk_ck, rlx_names_v, rlx_names_ssor_hclk_div,
	       div_array_long, SSOR_HCLK_CFG_R, CK_CHANGE_NULL,
	       RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_GATE_ONLY(ecc_ck, rlx_names_v, RSA_CLK_EN_R, CK_CHANGE_NULL,
			 RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX_GATE_ONLY(sha_ck, rlx_names_v, SHA_CLK_EN_R, CK_CHANGE_NULL,
			 RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX_GATE_ONLY(nnbus_ck, rlx_names_v, NN_BUS_CLK_CFG_R,
			 CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_NO_MUX(nncore_ck_dec, rlx_names_nncore_dec, div_array_short,
		      NN_CORE_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX(nncore_ck, rlx_names_v, rlx_names_nncore_div, div_array_short,
	       NN_CORE_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_GATE_ONLY(ge_ck, rlx_names_v, GE_CLK_EN_R, CK_CHANGE_NULL,
			 RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX_GATE_ONLY(bwt_ck, rlx_names_v, BWT_CLK_EN_R, CK_CHANGE_NULL,
			 RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX_GATE_ONLY(trng_ck, rlx_names_v, TRNG_CLK_CFG_R, CK_CHANGE_NULL,
			 RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX_GATE_ONLY(efuse_ck, rlx_names_v, EFUSE_CLK_CFG_R, CK_CHANGE_NULL,
			 RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(macbypass_ck, rlx_names_v, rlx_names_macbypass_div,
	       div_array_short, MAC_BYPASS_CLK_CFG_R, CK_CHANGE_NULL,
	       RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_GATE_ONLY(mipitx_ck, rlx_names_v, MIPI_TX_CFG_R, CK_CHANGE_NULL,
			 RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX_GATE_ONLY(jpegdram_ck, rlx_names_v, JPEG_DRAM_CLK_CFG_R,
			 CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX_GATE_ONLY(cipher_ck, rlx_names_v, CIPHER_CLK_CFG_R,
			 CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(mipitx_lowck, rlx_names_v, rlx_names_mipitx_lowdiv,
	       div_array_long, MIPI_TX_LOW_CLK_CFG_R, CK_CHANGE_NULL,
	       RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX_NO_MUX(isp_zoom_ck_dec, rlx_names_isp_zoom_dec, div_array_short,
		      ISP_ZOOM_CLK_CFG_REG, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);
DEFINE_CLK_RLX(isp_zoom_ck, rlx_names_v, rlx_names_isp_zoom_div,
	       div_array_short, ISP_ZOOM_CLK_CFG_REG, CK_CHANGE_NULL,
	       RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(sd0_crc_clk, rlx_names_v, rlx_names_sd_crc_clk_div,
	       div_array_long, SD0_CRC_CLK_CFG_REG, SD0_CK_CHANGE,
	       RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(sd0_sample_clk, rlx_names_v, rlx_names_sd_sam_clk_div,
	       div_array_long, SD0_SAMPLE_CLK_CFG_REG, SD0_CK_CHANGE,
	       RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(sd0_push_clk, rlx_names_v, rlx_names_sd_pu_clk_div,
	       div_array_long, SD0_PUSH_CLK_CFG_REG, SD0_CK_CHANGE,
	       RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(sd1_crc_clk, rlx_names_v, rlx_names_sd_crc_clk_div,
	       div_array_long, SD1_CRC_CLK_CFG_REG, SD1_CK_CHANGE,
	       RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(sd1_sample_clk, rlx_names_v, rlx_names_sd_sam_clk_div,
	       div_array_long, SD1_SAMPLE_CLK_CFG_REG, SD1_CK_CHANGE,
	       RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(sd1_push_clk, rlx_names_v, rlx_names_sd_pu_clk_div,
	       div_array_long, SD1_PUSH_CLK_CFG_REG, SD1_CK_CHANGE,
	       RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(uart1_ck, rlx_names_v, rlx_names_uart_div, div_array,
	       UART1_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(uart2_ck, rlx_names_v, rlx_names_uart_div, div_array,
	       UART2_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(i2c1_ck, rlx_names_v, rlx_names_i2c1_div, div_array_short,
	       I2C1_CLK_CFG_R, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

DEFINE_CLK_RLX(ssi_ck, rlx_names_v, rlx_names_ssi_div, div_array_short,
	       SSI_CLK_CFG_REG, CK_CHANGE_NULL, RTS_CLK_EN_SHIFT);

/**
 * divider_get_val() - get the clock divider value
 *
 * @rate: requested clock rate.
 * @parent_rate: parent clock rate.
 * @table: a pointer to clock divider table.
 * @width: width of the divider bit field.
 * @flags: common clock framework flags.
 * Return: divider value on success, or a negative error code.
 */
int divider_get_val(unsigned long rate, unsigned long parent_rate,
		    const struct clk_div_table *table, u8 width,
		    unsigned long flags);

#endif
