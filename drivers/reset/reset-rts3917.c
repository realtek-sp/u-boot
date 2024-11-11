// SPDX-License-Identifier: GPL-2.0-or-later
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

#include <common.h>
#include <dm.h>
#include <log.h>
#include <misc.h>
#include <reset.h>
#include <reset-uclass.h>
#include <linux/err.h>
#include <asm/io.h>
#include <dt-bindings/reset/rts3917-reset.h>

#define FORCE_DRAM_OSD_RESET BIT(10)
#define FORCE_BUS_SD1_RESET BIT(9)
#define FORCE_BUS_VIDEO_RESET BIT(8)
#define FORCE_BUS_SD0_RESET BIT(7)
#define FORCE_BUS_I2S_RESET BIT(6)
#define FORCE_BUS_U2DEV_RESET BIT(5)
#define FORCE_BUS_U2HOST_RESET BIT(4)
#define FORCE_BUS_RESET BIT(3)
#define FORCE_XB2_RESET BIT(2)
#define FORCE_CPU_RESET BIT(1)
#define FORCE_DRAM_RESET BIT(0)

#define FORCE_DRAM_LCDC_RESET BIT(13)
#define FORCE_BUS_SHA256_RESET BIT(12)
#define FORCE_DRAM_RSA_RESET BIT(11)
#define FORCE_DRAM_H265PP_RESET BIT(10)
#define FORCE_FEPHY_RESET BIT(5)
#define FORCE_LCDC_RESET BIT(4)
#define FORCE_RTC32K_RESET BIT(3)
#define FORCE_U2DEV_UTMI_RESET BIT(2)
#define FORCE_U2HOST_UTMI_RESET BIT(1)

#define FORCE_ZOOM_ISP_CLK_ASYNC_RESET BIT(24)
#define FORCE_UART2_CLK_ASYNC_RESET BIT(23)
#define FORCE_UART1_CLK_ASYNC_RESET BIT(22)
#define FORCE_MIPI_TX_CLK_ASYNC_RESET BIT(21)
#define FORCE_DRAM_JPG_CLK_ASYNC_RESET BIT(20)
#define FORCE_NN_CORE_CLK_ASYNC_RESET BIT(19)
#define FORCE_DRAM_NN_CLK_ASYNC_RESET BIT(18)
#define FORCE_OTP_CLK_ASYNC_RESET BIT(17)
#define FORCE_TRNG_CLK_ASYNC_RESET BIT(16)
#define FORCE_SD1_CLK_ASYNC_RESET BIT(15)
#define FORCE_H265_CCLK_ASYNC_RESET BIT(14)
#define FORCE_H265_BCLK_ASYNC_RESET BIT(13)
#define FORCE_H265_ACLK_ASYNC_RESET BIT(12)
#define FORCE_CODEC_CLK_ASYNC_RESET BIT(11)
#define FORCE_SPDIF_CLK_ASYNC_RESET BIT(10)
#define FORCE_I2C1_CLK_ASYNC_RESET BIT(9)
#define FORCE_I2C0_CLK_ASYNC_RESET BIT(8)
#define FORCE_UART0_CLK_ASYNC_RESET BIT(7)
#define FORCE_ETHERNET_CLK_ASYNC_RESET BIT(6)
#define FORCE_SD0_CLK_ASYNC_RESET BIT(5)
#define FORCE_CIPHER_CLK_ASYNC_RESET BIT(4)
#define FORCE_I2S_CLK_ASYNC_RESET BIT(3)
#define FORCE_ISP_CLK_ASYNC_RESET BIT(2)
#define FORCE_JPG_CLK_ASYNC_RESET BIT(1)
#define FORCE_MIPI_CLK_ASYNC_RESET BIT(0)

#define FORCE_REG_RESET_FWC 4
#define FORCE_REG_ASYNC_RESET 8

struct rts_reset_data {
	struct mutex lock;
	u32 base_addr;
};

#define RTS_FRR_SET(addr, mask)      \
	do {                         \
		u32 val;             \
		val = readl((addr)); \
		val |= (mask);       \
		writel(val, (addr)); \
	} while (0)

#define RTS_FRR_CLR(addr, mask)      \
	do {                         \
		u32 val;             \
		val = readl((addr)); \
		val &= ~(mask);      \
		writel(val, (addr)); \
	} while (0)

#define RTS_FORCE_RESET(addr, mask)      \
	do {                             \
		RTS_FRR_SET(addr, mask); \
		RTS_FRR_CLR(addr, mask); \
	} while (0)

static int rts3917_reset_request(struct reset_ctl *reset_ctl)
{
	struct rts_reset_data *rdata = dev_get_priv(reset_ctl->dev);

	debug("%s: reset_ctl->id: %lu\n", __func__, reset_ctl->id);
	if (reset_ctl->id >= FORCE_RESET_MAX)
		return -EINVAL;

	mutex_lock(&rdata->lock);
	switch (reset_ctl->id) {
	case FORCE_RESET_VIDEO:
		RTS_FRR_SET(rdata->base_addr, FORCE_BUS_VIDEO_RESET);
		break;

	case FORCE_RESET_JPG:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_JPG_CLK_ASYNC_RESET);
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_DRAM_JPG_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_MIPI:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_MIPI_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_SDIO0:
		RTS_FRR_SET(rdata->base_addr, FORCE_BUS_SD0_RESET);
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_SD0_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_SDIO1:
		RTS_FRR_SET(rdata->base_addr, FORCE_BUS_SD1_RESET);
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_SD1_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_CIPHER:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_CIPHER_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_CODEC:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_CODEC_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_I2S:
		RTS_FRR_SET(rdata->base_addr, FORCE_BUS_I2S_RESET);
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_I2S_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_SPDIF:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_SPDIF_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_I2C0:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_I2C0_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_I2C1:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_I2C1_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_U2DEV:
		RTS_FRR_SET(rdata->base_addr, FORCE_BUS_U2DEV_RESET);
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_RESET_FWC,
				FORCE_U2DEV_UTMI_RESET);
		break;

	case FORCE_RESET_U2HOST:
		RTS_FRR_SET(rdata->base_addr, FORCE_BUS_U2HOST_RESET);
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_RESET_FWC,
				FORCE_U2HOST_UTMI_RESET);
		break;

	case FORCE_RESET_ISP:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_ISP_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_UART0:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_UART0_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_UART1:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_UART1_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_UART2:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_UART2_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_ETHERNET:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_ETHERNET_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265_AXI:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_H265_ACLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265_BPU:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_H265_BCLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265_CORE:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_H265_CCLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_H265_ACLK_ASYNC_RESET);
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_H265_BCLK_ASYNC_RESET);
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_H265_CCLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265PP:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_RESET_FWC,
				FORCE_DRAM_H265PP_RESET);
		break;

	case FORCE_RESET_RSA:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_RESET_FWC,
				FORCE_DRAM_RSA_RESET);
		break;

	case FORCE_RESET_SHA256:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_RESET_FWC,
				FORCE_BUS_SHA256_RESET);
		break;

	case FORCE_RESET_TRNG:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_TRNG_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_FEPHY:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_RESET_FWC,
				FORCE_FEPHY_RESET);
		break;

	case FORCE_RESET_OTP:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_OTP_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_MIPI_TX:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_MIPI_TX_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_OSD:
		RTS_FRR_SET(rdata->base_addr, FORCE_DRAM_OSD_RESET);
		break;

	case FORCE_RESET_ZOOM:
		RTS_FORCE_RESET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
				FORCE_ZOOM_ISP_CLK_ASYNC_RESET);
		break;

	default:
		debug("ERROR: invalid reset model %ld\n", reset_ctl->id);
		break;
	}

	mutex_unlock(&rdata->lock);
	return 0;
}

static int rts3917_reset_deassert(struct reset_ctl *reset_ctl)
{
	struct rts_reset_data *rdata = dev_get_priv(reset_ctl->dev);

	debug("%s: reset_ctl->id: %lu\n", __func__, reset_ctl->id);

	mutex_lock(&rdata->lock);
	switch (reset_ctl->id) {
	case FORCE_RESET_ETHERNET:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_ETHERNET_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_FEPHY:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_RESET_FWC,
			    FORCE_FEPHY_RESET);
		break;

	case FORCE_RESET_H265_AXI:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_H265_ACLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265_BPU:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_H265_BCLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265_CORE:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_H265_CCLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_H265_ACLK_ASYNC_RESET);
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_H265_BCLK_ASYNC_RESET);
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_H265_CCLK_ASYNC_RESET);
		break;

	case FORCE_RESET_CIPHER:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_CIPHER_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265PP:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_RESET_FWC,
			    FORCE_DRAM_H265PP_RESET);
		break;

	case FORCE_RESET_RSA:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_RESET_FWC,
			    FORCE_DRAM_RSA_RESET);
		break;

	case FORCE_RESET_SHA256:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_RESET_FWC,
			    FORCE_BUS_SHA256_RESET);
		break;

	case FORCE_RESET_MIPI_TX:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_MIPI_TX_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_CODEC:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_CODEC_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_I2S:
		RTS_FRR_SET(rdata->base_addr, FORCE_BUS_I2S_RESET);
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_I2S_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_SPDIF:
		RTS_FRR_CLR(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_SPDIF_CLK_ASYNC_RESET);
		break;

	default:
		debug("ERROR: invalid deassert model %ld\n", reset_ctl->id);
		break;
	}

	mutex_unlock(&rdata->lock);

	return 0;
}

static int rts3917_reset_assert(struct reset_ctl *reset_ctl)
{
	struct rts_reset_data *rdata = dev_get_priv(reset_ctl->dev);

	debug("%s: reset_ctl->id: %lu\n", __func__, reset_ctl->id);

	mutex_lock(&rdata->lock);
	switch (reset_ctl->id) {
	case FORCE_RESET_ETHERNET:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_ETHERNET_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_FEPHY:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_RESET_FWC,
			    FORCE_FEPHY_RESET);
		break;

	case FORCE_RESET_H265_AXI:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_H265_ACLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265_BPU:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_H265_BCLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265_CORE:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_H265_CCLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_H265_ACLK_ASYNC_RESET);
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_H265_BCLK_ASYNC_RESET);
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_H265_CCLK_ASYNC_RESET);
		break;

	case FORCE_RESET_CIPHER:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_CIPHER_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_H265PP:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_RESET_FWC,
			    FORCE_DRAM_H265PP_RESET);
		break;

	case FORCE_RESET_RSA:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_RESET_FWC,
			    FORCE_DRAM_RSA_RESET);
		break;

	case FORCE_RESET_SHA256:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_RESET_FWC,
			    FORCE_BUS_SHA256_RESET);
		break;

	case FORCE_RESET_MIPI_TX:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_MIPI_TX_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_CODEC:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_CODEC_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_I2S:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_I2S_CLK_ASYNC_RESET);
		break;

	case FORCE_RESET_SPDIF:
		RTS_FRR_SET(rdata->base_addr + FORCE_REG_ASYNC_RESET,
			    FORCE_SPDIF_CLK_ASYNC_RESET);
		break;

	default:
		debug("ERROR: invalid assert model %ld\n", reset_ctl->id);
		break;
	}

	mutex_unlock(&rdata->lock);

	return 0;
}

static void rts_force_reset_hw_init(u32 base_addr)
{
	RTS_FRR_SET(base_addr + FORCE_REG_RESET_FWC,
		    FORCE_FEPHY_RESET | FORCE_U2DEV_UTMI_RESET |
			    FORCE_U2HOST_UTMI_RESET);
}

static int rts3917_reset_probe(struct udevice *dev)
{
	struct rts_reset_data *rdata = dev_get_priv(dev);

	mutex_init(&rdata->lock);
	rdata->base_addr = dev_read_addr(dev);
	if (!rdata->base_addr)
		return -ENOMEM;

	rts_force_reset_hw_init(rdata->base_addr);

	return 0;
}

static const struct udevice_id rts3917_reset_ids[] = {
	{ .compatible = "realtek,rts3917-reset" },
	{}
};

struct reset_ops rts3917_reset_ops = {
	.request = rts3917_reset_request,
	.rst_assert = rts3917_reset_assert,
	.rst_deassert = rts3917_reset_deassert,
};

U_BOOT_DRIVER(rts3917_reset) = {
	.name = "rts3917_reset",
	.id = UCLASS_RESET,
	.of_match = rts3917_reset_ids,
	.probe = rts3917_reset_probe,
	.ops = &rts3917_reset_ops,
	.priv_auto = sizeof(struct rts_reset_data),
};
