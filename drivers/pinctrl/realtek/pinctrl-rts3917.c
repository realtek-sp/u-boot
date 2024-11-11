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

#include <dm.h>
#include <errno.h>
#include <regmap.h>
#include <syscon.h>
#include <asm/io.h>
#include <dm/device_compat.h>
#include <dm/pinctrl.h>

#include "pinctrl-rts3917.h"

struct rts3917_pinctrl_priv {
	void __iomem *addr;
};

#if CONFIG_IS_ENABLED(PINCONF)

static const struct pinconf_param rts3917_conf_params[] = {
	{ "bias-disable", PIN_CONFIG_BIAS_DISABLE, 0 },
	{ "bias-pull-up", PIN_CONFIG_BIAS_PULL_UP, 1 },
	{ "bias-pull-down", PIN_CONFIG_BIAS_PULL_DOWN, 1 },
	{ "drive-strength", PIN_CONFIG_DRIVE_STRENGTH, 0 },
	{ "input-disable", PIN_CONFIG_INPUT_ENABLE, 0 },
	{ "input-enable", PIN_CONFIG_INPUT_ENABLE, 1 },
	{ "output-disable", PIN_CONFIG_OUTPUT_ENABLE, 0 },
	{ "output-enable", PIN_CONFIG_OUTPUT_ENABLE, 1 },
	{ "slew-rate", PIN_CONFIG_SLEW_RATE, 0 },
};

static enum pin_config_param pinconf_to_config_param(unsigned long config)
{
	return (enum pin_config_param)(config & 0xffUL);
}

static void rts_gpio_set_field(void __iomem *reg, unsigned int field,
			       unsigned int width, unsigned int offset)
{
	unsigned int val = readl(reg);

	val = RTS_SETFIELD(val, field, width, offset);
	writel(val, reg);
}

static struct sharepin_cfg_addr *rts_get_pinaddr(int pin)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(pincfgaddr); i++)
		if (pincfgaddr[i].pinl <= pin && pincfgaddr[i].pinh >= pin)
			return &pincfgaddr[i];

	return 0;
}

static int rts3917_pinconf_set(struct udevice *dev, unsigned int pin,
			       unsigned int param, unsigned int arg)
{
	struct rts3917_pinctrl_priv *priv = dev_get_priv(dev);
	struct pinregs *regs;
	struct sharepin_cfg_addr *sc;
	int bf;
	unsigned int config, value;

	config = pinconf_to_config_param(param);

	sc = rts_get_pinaddr(pin);
	regs = (struct pinregs *)sc->pinaddr;
	bf = pin - sc->pinl;

	dev_dbg(dev, "set pinconf config %#x, param %#x\n", config, param);

	switch (config) {
	case PIN_CONFIG_BIAS_DISABLE:
		rts_gpio_set_field(priv->addr + (int)&(regs->pullctrl), 0, 2,
				   bf << 1);
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		rts_gpio_set_field(priv->addr + (int)&(regs->pullctrl), 2, 2,
				   bf << 1);
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		rts_gpio_set_field(priv->addr + (int)&(regs->pullctrl), 1, 2,
				   bf << 1);
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		dev_read_u32(dev, "drive-strength", &value);
		dev_dbg(dev, "%s, %d, value %u\n", __func__, __LINE__, value);
		rts_gpio_set_field(priv->addr + (int)&(regs->drv_sel),
				   (value >> 2) - 1, 1, bf);
		break;
	case PIN_CONFIG_SLEW_RATE:
		rts_gpio_set_field(priv->addr + (int)&(regs->sr_ctrl), value, 1,
				   bf);
		break;
	case PIN_CONFIG_INPUT_ENABLE:
		if (pin < RTS_MAX_NGPIO) {
			rts_gpio_set_field(priv->addr + (int)&(regs->gpio_oe),
					   0, 1, bf);
		}
		break;
	case PIN_CONFIG_OUTPUT_ENABLE:
		if (pin < RTS_MAX_NGPIO) {
			rts_gpio_set_field(priv->addr + (int)&(regs->gpio_oe),
					   1, 1, bf);
		}
		break;
	default:
		dev_err(dev, "illegal configuration requested\n");
		return -EINVAL;
	}
	return 0;
}

/* set the pin config settings for a specified pin group */
static int rts3917_pinconf_group_set(struct udevice *dev,
				     unsigned int num_configs,
				     unsigned int configs, unsigned int arg)
{
	const unsigned int *pins;
	unsigned int cnt;

	dev_dbg(dev, "num_configs %#x, configs %#x\n", num_configs, configs);
	pins = rts_pin_groups[num_configs].pins;
	for (cnt = 0; cnt < rts_pin_groups[num_configs].num_pins; cnt++)
		rts3917_pinconf_set(dev, pins[cnt], configs, arg);

	return 0;
}

#endif

static int rts3917_get_pins_count(struct udevice *dev)
{
	return ARRAY_SIZE(rts_gpio_pins);
}

static const char *rts3917_get_pin_name(struct udevice *dev,
					unsigned int selector)
{
	return rts_gpio_pins[selector].name;
}

static int rts3917_get_functions_count(struct udevice *dev)
{
	return ARRAY_SIZE(rts_functions);
}

static const char *rts3917_get_function_name(struct udevice *dev,
					     unsigned int selector)
{
	return rts_functions[selector].name;
}

static int rts3917_get_groups_count(struct udevice *dev)
{
	return ARRAY_SIZE(rts_pin_groups);
}

static const char *rts3917_get_group_name(struct udevice *dev,
					  unsigned int selector)
{
	return rts_pin_groups[selector].name;
}

static int rts3917_pinmux_group_set(struct udevice *dev,
				    unsigned int group_selector,
				    unsigned int func_selector)
{
	struct rts3917_pinctrl_priv *priv = dev_get_priv(dev);

	dev_dbg(dev, "set_mux [grp %s][func %s]\n",
		rts_pin_groups[group_selector].name,
		rts_functions[func_selector].name);

	switch (func_selector) {
	case H265_UART_FUNC_SELECT:
		if (group_selector == H265_UART_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + GPIO_0_15_PAD_CFG, 2, 4,
					   0);
			rts_gpio_set_field(priv->addr + GPIO_0_15_PAD_CFG, 2, 4,
					   4);
		}
		break;
	case I2C_FUNC_SELECT:
		if (group_selector == I2C0_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + XB2_I2C_PAD_CFG, 2, 2,
					   0);
			rts_gpio_set_field(priv->addr + XB2_I2C_PAD_CFG, 2, 2,
					   4);
		} else if (group_selector == I2CPWM_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + PWM_PAD_CFG, 8, 4, 0);
			rts_gpio_set_field(priv->addr + PWM_PAD_CFG, 8, 4, 4);
		} else if (group_selector == I2C1_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + SSOR_I2C_PAD_CFG, 2, 2,
					   0);
		}
		break;
	case PWM_FUNC_SELECT:
		if (group_selector == PWM0_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + PWM_PAD_CFG, 2, 4, 0);
		else if (group_selector == PWM1_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + PWM_PAD_CFG, 2, 4, 4);
		else if (group_selector == PWM2_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + PWM_PAD_CFG, 2, 4, 8);
		else if (group_selector == PWM3_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + PWM_PAD_CFG, 2, 4, 12);
		else if (group_selector == PWMSD_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + SD1_PAD_CFG, 4, 4, 0);
		break;
	case UART_FUNC_SELECT:
		if (group_selector == UART0_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + UART0_PAD_CFG, 2, 4, 0);
			rts_gpio_set_field(priv->addr + UART0_PAD_CFG, 2, 4, 4);
			rts_gpio_set_field(priv->addr + UART0_PAD_CFG, 2, 4, 8);
			rts_gpio_set_field(priv->addr + UART0_PAD_CFG, 2, 4,
					   12);
		} else if (group_selector == UART1_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + UART1_PAD_CFG, 2, 4, 8);
			rts_gpio_set_field(priv->addr + UART1_PAD_CFG, 2, 4,
					   12);
		} else if (group_selector == UART2_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + UART2_PAD_CFG, 2, 4, 0);
			rts_gpio_set_field(priv->addr + UART2_PAD_CFG, 2, 4, 4);
			rts_gpio_set_field(priv->addr + UART2_PAD_CFG, 2, 4, 8);
			rts_gpio_set_field(priv->addr + UART2_PAD_CFG, 2, 4,
					   12);
		} else if (group_selector == UART2_USB_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + USB1_PAD_CFG, 4, 4, 0);
			rts_gpio_set_field(priv->addr + USB1_PAD_CFG, 4, 4, 4);
		}
		break;
	case AUDIO_FUNC_SELECT:
		if (group_selector == AMIC_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + AUDIO_ADDA_PAD_CFG, 1,
					   3, 4);
		else if (group_selector == DMIC_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + AUDIO_ADDA_PAD_CFG, 4,
					   3, 4);
		else if (group_selector == LINEOUT_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + AUDIO_ADDA_PAD_CFG, 1,
					   2, 0);
		else if (group_selector == DMIC1_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + DMIC_PAD_CFG, 2, 2, 0);
		else if (group_selector == DMIC2_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + DMIC_PAD_CFG, 2, 2, 4);
		else if (group_selector == I2S_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + I2S_PAD_CFG, 2, 4, 0);
			rts_gpio_set_field(priv->addr + I2S_PAD_CFG, 2, 4, 4);
			rts_gpio_set_field(priv->addr + I2S_PAD_CFG, 2, 4, 8);
			rts_gpio_set_field(priv->addr + I2S_PAD_CFG, 2, 4, 12);
			rts_gpio_set_field(priv->addr + I2S_PAD_CFG, 2, 4, 16);
		} else if (group_selector == PDM_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + I2S_PAD_CFG, 4, 4, 4);
			rts_gpio_set_field(priv->addr + I2S_PAD_CFG, 4, 4, 16);
		} else if (group_selector == SPDIF_OUT_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + I2S_PAD_CFG, 4, 4, 0);
		else if (group_selector == I2SXB2_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + PWM_PAD_CFG, 8, 4, 12);
			rts_gpio_set_field(priv->addr + UART0_PAD_CFG, 8, 4, 0);
			rts_gpio_set_field(priv->addr + UART0_PAD_CFG, 8, 4, 4);
			rts_gpio_set_field(priv->addr + UART0_PAD_CFG, 8, 4, 8);
			rts_gpio_set_field(priv->addr + UART0_PAD_CFG, 8, 4,
					   12);
		} else if (group_selector == I2SDVP_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 8, 4, 0);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 8, 4,
					   24);
			rts_gpio_set_field(priv->addr + GPIO_0_15_PAD_CFG, 2, 4,
					   8);
		}
		break;
	case USBD_FUNC_SELECT:
		rts_gpio_set_field(priv->addr + USB1_PAD_CFG, 1, 3, 4);
		rts_gpio_set_field(priv->addr + USB1_PAD_CFG, 1, 3, 0);
		rts_gpio_set_field(priv->addr + USB2_PAD_CFG, 2, 2, 8);
		break;
	case ETNLED_FUNC_SELECT:
		if (group_selector == ETNLED0_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + PWM_PAD_CFG, 4, 4, 0);
		else if (group_selector == ETNLED1_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + PWM_PAD_CFG, 4, 4, 4);
		else if (group_selector == ETNLED2_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + PWM_PAD_CFG, 4, 3, 8);
		break;
	case USBHST_FUNC_SELECT:
		rts_gpio_set_field(priv->addr + USB0_PAD_CFG, 1, 2, 4);
		rts_gpio_set_field(priv->addr + USB0_PAD_CFG, 1, 2, 0);
		rts_gpio_set_field(priv->addr + USB2_PAD_CFG, 2, 2, 4);
		rts_gpio_set_field(priv->addr + USB2_PAD_CFG, 2, 2, 0);
		break;
	case SARADC_FUNC_SELECT:
		if (group_selector == SARADC0_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + SARADC_PAD_CFG, 1, 2,
					   0);
		else if (group_selector == SARADC1_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + SARADC_PAD_CFG, 1, 2,
					   4);
		else if (group_selector == SARADC2_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + SARADC_PAD_CFG, 1, 2,
					   8);
		else
			rts_gpio_set_field(priv->addr + SARADC_PAD_CFG, 1, 2,
					   12);
		break;
	case SSOR_FUNC_SELECT:
		if (group_selector == MIPI_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 4, 4, 4);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 4, 4, 8);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 4, 4,
					   12);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 4, 4,
					   16);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 4, 4,
					   20);
		} else if (group_selector == DVP_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 2, 4, 0);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 2, 4, 4);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 2, 4, 8);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 2, 4,
					   12);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 2, 4,
					   16);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 2, 4,
					   20);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 2, 4,
					   24);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 2, 4,
					   28);
			rts_gpio_set_field(priv->addr + PAD_V18_EN, 0, 2, 0);
		}
		break;
	case SSI_FUNC_SELECT:
		rts_gpio_set_field(priv->addr + UART0_PAD_CFG, 4, 3, 0);
		rts_gpio_set_field(priv->addr + UART0_PAD_CFG, 4, 3, 4);
		rts_gpio_set_field(priv->addr + UART0_PAD_CFG, 4, 3, 8);
		rts_gpio_set_field(priv->addr + UART0_PAD_CFG, 4, 3, 12);
		break;
	case SDIO0_FUNC_SELECT:
		rts_gpio_set_field(priv->addr + SD0_PAD_CFG, 2, 2, 0);
		if (group_selector == SDIO0WP_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + SD0_PAD_CFG, 2, 2, 4);
		else if (group_selector == SDIO0CD_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + SD0_PAD_CFG, 2, 2, 2);
		break;
	case SDIO1_FUNC_SELECT:
		if (group_selector == SDIO1_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + SD1_PAD_CFG, 2, 4, 0);
			rts_gpio_set_field(priv->addr + SD1_PAD_CFG, 0, 1, 12);
		} else if (group_selector == SDIO1WP_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + SD1_PAD_CFG, 2, 4, 8);
		else if (group_selector == SDIO1CD_GROUP_SELECT)
			rts_gpio_set_field(priv->addr + SD1_PAD_CFG, 2, 4, 4);
		else if (group_selector == SDIO1VIDEO_GROUP_SELECT) {
			rts_gpio_set_field(priv->addr + GPIO_0_15_PAD_CFG, 4, 4,
					   8);
			rts_gpio_set_field(priv->addr + SD1_PAD_CFG, 1, 1, 12);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 4, 4, 0);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 4, 4,
					   24);
			rts_gpio_set_field(priv->addr + VIDEO_PAD_CFG, 4, 4,
					   28);
			rts_gpio_set_field(priv->addr + PAD_V18_EN, 3, 2, 0);
		}
		break;
	case SPI_FUNC_SELECT:
		rts_gpio_set_field(priv->addr + SPI_PAD_CFG, 2, 4, 0);
		break;
	default:
		dev_err(dev, "not known function selector %d\n", func_selector);
		break;
	}

	return 0;
}

static struct pinctrl_ops rts3917_pinctrl_ops = {
	.set_state = pinctrl_generic_set_state,
	.get_pins_count = rts3917_get_pins_count,
	.get_pin_name = rts3917_get_pin_name,
	.get_groups_count = rts3917_get_groups_count,
	.get_group_name = rts3917_get_group_name,
	.get_functions_count = rts3917_get_functions_count,
	.get_function_name = rts3917_get_function_name,
	// .pinmux_set = rts3917_pinmux_set,
	.pinmux_group_set = rts3917_pinmux_group_set,
#if CONFIG_IS_ENABLED(PINCONF)
	.pinconf_num_params = ARRAY_SIZE(rts3917_conf_params),
	.pinconf_params = rts3917_conf_params,
	.pinconf_set = rts3917_pinconf_set,
	.pinconf_group_set = rts3917_pinconf_group_set,
#endif
};

static const struct udevice_id rts3917_pinctrl_ids[] = {
	{ .compatible = "realtek,rts3917-pinctrl" },
	{}
};

static int rts3917_pinctrl_probe(struct udevice *dev)
{
	struct rts3917_pinctrl_priv *priv = dev_get_priv(dev);

	priv->addr = dev_read_addr_ptr(dev);
	if (!priv->addr)
		return -EINVAL;

	return 0;
}

U_BOOT_DRIVER(rts3917_pinctrl) = {
	.name = "rts3917_pinctrl",
	.id = UCLASS_PINCTRL,
	.of_match = rts3917_pinctrl_ids,
	.priv_auto = sizeof(struct rts3917_pinctrl_priv),
	.ops = &rts3917_pinctrl_ops,
	.probe = rts3917_pinctrl_probe,
};
