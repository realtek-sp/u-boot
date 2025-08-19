// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (c) 2025 Realtek Semiconductor Corp. All rights reserved.
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

#include <dm.h>
#include <errno.h>
#include <log.h>
#include <wdt.h>
#include <asm/io.h>
#include <dm/device_compat.h>
#include <linux/delay.h>
#include <linux/err.h>

#define WATCHDOG_CFG_REG  0
#define WATCHDOG_CTL	  0x4
#define WATCHDOG_INT_EN	  0x8
#define WATCHDOG_INT_FLAG 0xc

#define WDOG_TIME		 16
#define WDOG_RST_PAD_PUE	 9
#define WDOG_RST_PAD_PDE	 8
#define WDOG_RST_PAD_SR_SLOW	 7
#define WDOG_RST_PAD_DRV_8MA	 6
#define WDOG_RST_PMU_VOLTAGE_3V3 5
#define WDOG_RST_PMU_ENABLE	 4
#define WDOG_RST_EN		 1
#define WDOG_EN			 0

#define WDT_DEFAULT_TIMEOUT 8

#define RTS_GETFIELD(val, width, offset) ((val >> offset) & ((1 << width) - 1))
#define RTS_SETFIELD(reg, field, width, offset)      \
	((reg & (~(((1 << width) - 1) << offset))) | \
	 ((field & ((1 << width) - 1)) << offset))

struct rts_wdt_priv {
	void __iomem *wdt_reg;
	bool external_reset;
};

static void rts_set_field(void __iomem *reg, unsigned int field,
			  unsigned int width, unsigned int offset)
{
	unsigned int val = readl(reg);

	val = RTS_SETFIELD(val, field, width, offset);
	writel(val, reg);
}

static int rts_wdt_reset(struct udevice *dev)
{
	struct rts_wdt_priv *priv = dev_get_priv(dev);

	rts_set_field(priv->wdt_reg + WATCHDOG_CTL, 1, 1, 0);

	return 0;
}

static void rts_wdt_set_timeout(struct udevice *dev, u64 timeout_ms)
{
	struct rts_wdt_priv *priv = dev_get_priv(dev);
	u32 time;

	/*
	 * Watchdog timeout mapping (3-bit field):
	 * 0: 1s
	 * 1: 2s
	 * 2: 4s
	 * 3: 8s
	 * 4: 16s
	 * 5: 32s
	 * 6: 64s
	 */

	if (timeout_ms >= 64 * 1000)
		time = 6;
	else if (timeout_ms >= 32 * 1000)
		time = 5;
	else if (timeout_ms >= 16 * 1000)
		time = 4;
	else if (timeout_ms >= 8 * 1000)
		time = 3;
	else if (timeout_ms >= 4 * 1000)
		time = 2;
	else if (timeout_ms >= 2 * 1000)
		time = 1;
	else
		time = 0;

	rts_set_field(priv->wdt_reg + WATCHDOG_CFG_REG, time, 3, WDOG_TIME);
}

static int rts_wdt_start(struct udevice *dev, u64 timeout_ms, ulong flags)
{
	struct rts_wdt_priv *priv = dev_get_priv(dev);

	rts_wdt_set_timeout(dev, timeout_ms);

	if (priv->external_reset) {
		rts_set_field(priv->wdt_reg + WATCHDOG_CFG_REG, 1, 1,
			      WDOG_RST_PMU_ENABLE);
	} else {
		rts_set_field(priv->wdt_reg + WATCHDOG_CFG_REG, 1, 1,
			      WDOG_RST_EN);
	}

	rts_set_field(priv->wdt_reg + WATCHDOG_CFG_REG, 1, 1, WDOG_EN);

	dev_info(dev, "Started watchdog timer\n");

	return 0;
}

static int rts_wdt_stop(struct udevice *dev)
{
	struct rts_wdt_priv *priv = dev_get_priv(dev);

	rts_set_field(priv->wdt_reg + WATCHDOG_CFG_REG, 0, 1, WDOG_EN);

	dev_info(dev, "Stopped watchdog timer\n");

	return 0;
}

static int rts_wdt_expire_now(struct udevice *dev, ulong flags)
{
	struct rts_wdt_priv *priv = dev_get_priv(dev);

	int ret = rts_wdt_start(dev, 1000, flags);
	if (ret) {
		dev_err(dev,
			"Failed to start watchdog timer for immediate expiration\n");
		return ret;
	}

	mdelay(2000);

	return 0;
}

static int rts_wdt_probe(struct udevice *dev)
{
	struct rts_wdt_priv *priv = dev_get_priv(dev);

	priv->wdt_reg = dev_read_addr_ptr(dev);
	if (!priv->wdt_reg) {
		dev_err(dev, "Failed to get watchdog register address\n");
		return -EINVAL;
	}

	priv->external_reset = dev_read_bool(dev, "external-reset");

	return 0;
}

static const struct wdt_ops rts_wdt_ops = {
	.expire_now = rts_wdt_expire_now,
	.start = rts_wdt_start,
	.reset = rts_wdt_reset,
	.stop = rts_wdt_stop,
};

static const struct udevice_id rts_wdt_ids[] = {
	{ .compatible = "realtek,rts493xa-wdt" },
	{}
};

U_BOOT_DRIVER(rts_wdt) = {
	.name = "rts493xa_wdt",
	.id = UCLASS_WDT,
	.of_match = rts_wdt_ids,
	.probe = rts_wdt_probe,
	.priv_auto = sizeof(struct rts_wdt_priv),
	.ops = &rts_wdt_ops,
};
