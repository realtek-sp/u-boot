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

#ifndef __PINCTRL_RTS493XA_H_
#define __PINCTRL_RTS493XA_H_

#define GPIO_OE		       0x0000
#define GPIO_VALUE	       0x0004
#define GPIO_PULLCTRL	       0x0008
#define GPIO_INT_EN	       0x000c
#define GPIO_INT	       0x0010
#define GPIO_DRV_SEL	       0x0014
#define GPIO_SR_CTRL	       0x0018
#define GPIO_0_15_PAD_CFG      0x001c
#define UART0_GPIO_OE	       0x0020
#define UART0_GPIO_VALUE       0x0024
#define UART0_PULLCTRL	       0x0028
#define UART0_GPIO_INT_EN      0x002c
#define UART0_GPIO_INT	       0x0030
#define UART0_DRV_SEL	       0x0034
#define UART0_SR_CTRL	       0x0038
#define UART0_PAD_CFG	       0x003C
#define UART1_GPIO_OE	       0x0040
#define UART1_GPIO_VALUE       0x0044
#define UART1_PULLCTRL	       0x0048
#define UART1_GPIO_INT_EN      0x004c
#define UART1_GPIO_INT	       0x0050
#define UART1_DRV_SEL	       0x0054
#define UART1_SR_CTRL	       0x0058
#define UART1_PAD_CFG	       0x005C
#define UART2_GPIO_OE	       0x0060
#define UART2_GPIO_VALUE       0x0064
#define UART2_PULLCTRL	       0x0068
#define UART2_GPIO_INT_EN      0x006c
#define UART2_GPIO_INT	       0x0070
#define UART2_DRV_SEL	       0x0074
#define UART2_SR_CTRL	       0x0078
#define UART2_PAD_CFG	       0x007C
#define PWM_GPIO_OE	       0x0080
#define PWM_GPIO_VALUE	       0x0084
#define PWM_PULLCTRL	       0x0088
#define PWM_GPIO_INT_EN	       0x008C
#define PWM_GPIO_INT	       0x0090
#define PWM_DRV_SEL	       0x0094
#define PWM_SR_CTRL	       0x0098
#define PWM_PAD_CFG	       0x009C
#define XB2_I2C_GPIO_OE	       0x00a0
#define XB2_I2C_GPIO_VALUE     0x00a4
#define XB2_I2C_PULLCTRL       0x00a8
#define XB2_I2C_GPIO_INT_EN    0x00ac
#define XB2_I2C_GPIO_INT       0x00b0
#define XB2_I2C_GPIO_DRV_SEL   0x00b4
#define XB2_I2C_GPIO_SR_CTRL   0x00b8
#define XB2_I2C_PAD_CFG	       0x00bC
#define SD0_GPIO_OE	       0x00c0
#define SD0_GPIO_VALUE	       0x00c4
#define SD0_PULLCTRL	       0x00c8
#define SD0_GPIO_INT_EN	       0x00cc
#define SD0_GPIO_INT	       0x00d0
#define SD0_GPIO_DRV_SEL       0x00d4
#define SD0_GPIO_SR_CTRL       0x00d8
#define SD0_PAD_CFG	       0x00dC
#define SD1_GPIO_OE	       0x00e0
#define SD1_GPIO_VALUE	       0x00e4
#define SD1_PULLCTRL	       0x00e8
#define SD1_GPIO_INT_EN	       0x00ec
#define SD1_GPIO_INT	       0x00f0
#define SD1_GPIO_DRV_SEL       0x00f4
#define SD1_GPIO_SR_CTRL       0x00f8
#define SD1_PAD_CFG	       0x00fC
#define VIDEO_GPIO_OE	       0x0100
#define VIDEO_GPIO_VALUE       0x0104
#define VIDEO_PULLCTRL	       0x0108
#define VIDEO_GPIO_INT_EN      0x010c
#define VIDEO_GPIO_INT	       0x0110
#define VIDEO_DRV_SEL	       0x0114
#define VIDEO_SR_CTRL	       0x0118
#define VIDEO_PAD_CFG	       0x011c
#define DMIC_GPIO_OE	       0x0130
#define DMIC_GPIO_VALUE	       0x0134
#define DMIC_PULLCTRL	       0x0138
#define DMIC_GPIO_INT_EN       0x013c
#define DMIC_GPIO_INT	       0x0140
#define DMIC_DRV_SEL	       0x0144
#define DMIC_SR_CTRL	       0x0148
#define DMIC_PAD_CFG	       0x014C
#define AUDIO_ADDA_GPIO_OE     0x0150
#define AUDIO_ADDA_GPIO_VALUE  0x0154
#define AUDIO_ADDA_PULLCTRL    0x0158
#define AUDIO_ADDA_GPIO_INT_EN 0x015c
#define AUDIO_ADDA_GPIO_INT    0x0160
#define AUDIO_ADDA_DRV_SEL     0x0164
#define AUDIO_ADDA_SR_CTRL     0x0168
#define AUDIO_ADDA_PAD_CFG     0x016C
#define I2S_GPIO_OE	       0x0170
#define I2S_GPIO_VALUE	       0x0174
#define I2S_PULLCTRL	       0x0178
#define I2S_GPIO_INT_EN	       0x017C
#define I2S_GPIO_INT	       0x0180
#define I2S_DRV_SEL	       0x0184
#define I2S_SR_CTRL	       0x0188
#define I2S_PAD_CFG	       0x018C
#define SARADC_GPIO_OE	       0x0190
#define SARADC_GPIO_VALUE      0x0194
#define SARADC_PULLCTRL	       0x0198
#define SARADC_GPIO_INT_EN     0x019c
#define SARADC_GPIO_INT	       0x01a0
#define SARADC_DRV_SEL	       0x01a4
#define SARADC_SR_CTRL	       0x01a8
#define SARADC_PAD_CFG	       0x01aC
#define USB0_GPIO_OE	       0x01f0
#define USB0_GPIO_VALUE	       0x01f4
#define USB0_PULLCTRL	       0x01f8
#define USB0_GPIO_INT_EN       0x01fc
#define USB0_GPIO_INT	       0x0200
#define USB0_DRV_SEL	       0x0204
#define USB0_SR_CTRL	       0x0208
#define USB0_PAD_CFG	       0x020c
#define USB1_GPIO_OE	       0x0210
#define USB1_GPIO_VALUE	       0x0214
#define USB1_PULLCTRL	       0x0218
#define USB1_GPIO_INT_EN       0x021c
#define USB1_GPIO_INT	       0x0220
#define USB1_DRV_SEL	       0x0224
#define USB1_SR_CTRL	       0x0228
#define USB1_PAD_CFG	       0x022C
#define USB2_GPIO_OE	       0x0230
#define USB2_GPIO_VALUE	       0x0234
#define USB2_PULLCTRL	       0x0238
#define USB2_GPIO_INT_EN       0x023c
#define USB2_GPIO_INT	       0x0240
#define USB2_DRV_SEL	       0x0244
#define USB2_SR_CTRL	       0x0248
#define USB2_PAD_CFG	       0x024C
#define SPI_GPIO_OE	       0x0250
#define SPI_GPIO_VALUE	       0x0254
#define SPI_PULLCTRL	       0x0258
#define SPI_GPIO_INT_EN	       0x025c
#define SPI_GPIO_INT	       0x0260
#define SPI_DRV_SEL	       0x0264
#define SPI_SR_CTRL	       0x0268
#define SPI_PAD_CFG	       0x026C
#define SSOR_I2C_GPIO_OE       0x0270
#define SSOR_I2C_GPIO_VALUE    0x0274
#define SSOR_I2C_PULLCTRL      0x0278
#define SSOR_I2C_GPIO_INT_EN   0x027c
#define SSOR_I2C_GPIO_INT      0x0280
#define SSOR_I2C_DRV_SEL       0x0284
#define SSOR_I2C_SR_CTRL       0x0288
#define SSOR_I2C_PAD_CFG       0x028c
#define ASIC_DBG_EN	       0x0290
#define ASIC_DBG_SEL	       0x0294
#define PAD_V18_EN	       0x0298
#define PWM_LED_SEL	       0x02a0

#define GPIO_FUNC_SELECT      0
#define SDIO0_FUNC_SELECT     1
#define SDIO1_FUNC_SELECT     2
#define UART_FUNC_SELECT      3
#define PWM_FUNC_SELECT	      4
#define AUDIO_FUNC_SELECT     5
#define USBD_FUNC_SELECT      6
#define ETNLED_FUNC_SELECT    7
#define USBHST_FUNC_SELECT    8
#define SARADC_FUNC_SELECT    9
#define SSOR_FUNC_SELECT      10
#define SSI_FUNC_SELECT	      11
#define I2C_FUNC_SELECT	      12
#define SPI_FUNC_SELECT	      13
#define H265_UART_FUNC_SELECT 14

#define RTS_PINRANGE(a, b, c)		 { .gpio_base = a, .pin_base = b, .pins = c }
#define RTS_GETFIELD(val, width, offset) ((val >> offset) & ((1 << width) - 1))
#define RTS_SETFIELD(reg, field, width, offset)      \
	((reg & (~(((1 << width) - 1) << offset))) | \
	 ((field & ((1 << width) - 1)) << offset))

#define RTS_MAX_NGPIO 89

struct rts_pinctrl {
	struct gpio_chip *gpio_chip;
	struct device *dev;
	unsigned int *irq_type;
	struct pinctrl_dev *rtspctl_dev;
	struct irq_domain *irq_domain;
	spinlock_t irq_lock;
	void __iomem *addr;
	void __iomem *addr_sdio0;
	void __iomem *addr_sdio1;
	void __iomem *addr_i2s;
	struct platform_device *pdev;
	int irq;
	u64 pinsmask[2];
	int devt;
	u8 audio_adda_gpio_value;
	u8 usb0_gpio_value;
	u8 usb1_gpio_value;
};

struct rts_pin_group {
	const char *name;
	const unsigned int *pins;
	const unsigned int num_pins;
};

struct rts_func {
	const char *name;
	const char *const *groups;
	const unsigned int num_groups;
};

struct rts_pinpair {
	unsigned int gpio_base;
	unsigned int pin_base;
	unsigned int pins;
};

struct sharepin_cfg_addr {
	int pinl;
	int pinh;
	int pint;
	int pinaddr;
};

struct pinregs {
	int gpio_oe;
	int gpio_value;
	int pullctrl;
	int gpio_int_en;
	int gpio_int;
	int drv_sel;
	int sr_ctrl;
	int pad_cfg;
};

enum {
	GPIO_TYPE_GENERIC,
	GPIO_TYPE_UART0,
	GPIO_TYPE_UART1,
	GPIO_TYPE_UART2,
	GPIO_TYPE_PWM,
	GPIO_TYPE_I2C,
	GPIO_TYPE_SDIO0,
	GPIO_TYPE_SDIO1,
	GPIO_TYPE_SSOR,
	GPIO_TYPE_DMIC,
	GPIO_TYPE_ADDA,
	GPIO_TYPE_I2S,
	GPIO_TYPE_SARADC,
	GPIO_TYPE_USBH,
	GPIO_TYPE_USBD,
	GPIO_TYPE_USB3,
	GPIO_TYPE_SSORI2C,
	GPIO_TYPE_SPI,
};
#define PINCTRL_PIN(a, b) { .number = a, .name = b }

struct pinctrl_pin_desc {
	unsigned int number;
	const char *name;
};

/* number, name, drv_data */
static struct pinctrl_pin_desc rts_gpio_pins[] = {
	PINCTRL_PIN(0, "GPIO0"),
	PINCTRL_PIN(1, "GPIO1"),
	PINCTRL_PIN(2, "GPIO2"),
	PINCTRL_PIN(3, "GPIO3"),
	PINCTRL_PIN(4, "GPIO4"),
	PINCTRL_PIN(5, "GPIO5"),
	PINCTRL_PIN(6, "GPIO6"),
	PINCTRL_PIN(7, "GPIO7"),
	PINCTRL_PIN(8, "GPIO8"),
	PINCTRL_PIN(9, "GPIO9"),
	PINCTRL_PIN(10, "GPIO10"),
	PINCTRL_PIN(11, "GPIO11"),
	PINCTRL_PIN(12, "GPIO12"),
	PINCTRL_PIN(13, "GPIO13"),
	PINCTRL_PIN(14, "GPIO14"),
	PINCTRL_PIN(15, "GPIO15"),
	PINCTRL_PIN(16, "UART0RXD"),
	PINCTRL_PIN(17, "UART0TXD"),
	PINCTRL_PIN(18, "UART0RTS"),
	PINCTRL_PIN(19, "UART0CTS"),
	PINCTRL_PIN(20, "UART1RXD"),
	PINCTRL_PIN(21, "UART1TXD"),
	PINCTRL_PIN(22, "UART2RXD"),
	PINCTRL_PIN(23, "UART2TXD"),
	PINCTRL_PIN(24, "UART2RTS"),
	PINCTRL_PIN(25, "UART2CTS"),
	PINCTRL_PIN(26, "PWMGPIO0"),
	PINCTRL_PIN(27, "PWMGPIO1"),
	PINCTRL_PIN(28, "PWMGPIO2"),
	PINCTRL_PIN(29, "PWMGPIO3"),
	PINCTRL_PIN(30, "I2CSCL"),
	PINCTRL_PIN(31, "I2CSDA"),
	PINCTRL_PIN(32, "SDIO0_CMD"),
	PINCTRL_PIN(33, "SDIO0_DATA0"),
	PINCTRL_PIN(34, "SDIO0_DATA1"),
	PINCTRL_PIN(35, "SDIO0_DATA2"),
	PINCTRL_PIN(36, "SDIO0_DATA3"),
	PINCTRL_PIN(37, "SDIO0_CLK"),
	PINCTRL_PIN(38, "SDIO0_WP"),
	PINCTRL_PIN(39, "SDIO0_CD"),
	PINCTRL_PIN(40, "SDIO1_CMD"),
	PINCTRL_PIN(41, "SDIO1_DATA0"),
	PINCTRL_PIN(42, "SDIO1_DATA1"),
	PINCTRL_PIN(43, "SDIO1_DATA2"),
	PINCTRL_PIN(44, "SDIO1_DATA3"),
	PINCTRL_PIN(45, "SDIO1_CLK"),
	PINCTRL_PIN(46, "SDIO1_WP"),
	PINCTRL_PIN(47, "SDIO1_CD"),
	PINCTRL_PIN(48, "PAD_SSOR_PIXDIN_EXT_0"),
	PINCTRL_PIN(49, "PAD_SSOR_PIXDIN_EXT_1"),
	PINCTRL_PIN(50, "PAD_SSOR_PIXDIN_0"),
	PINCTRL_PIN(51, "PAD_SSOR_PIXDIN_1"),
	PINCTRL_PIN(52, "PAD_SSOR_PIXDIN_2"),
	PINCTRL_PIN(53, "PAD_SSOR_PIXDIN_3"),
	PINCTRL_PIN(54, "PAD_SSOR_PIXDIN_6"),
	PINCTRL_PIN(55, "PAD_SSOR_PIXDIN_7"),
	PINCTRL_PIN(56, "PAD_SSOR_PIXDIN_8"),
	PINCTRL_PIN(57, "PAD_SSOR_PIXDIN_9"),
	PINCTRL_PIN(58, "PAD_SSOR_HSYNC"),
	PINCTRL_PIN(59, "PAD_SSOR_VSYNC"),
	PINCTRL_PIN(60, "PAD_SSOR_PIXCLK"),
	PINCTRL_PIN(61, "PAD_CLK_DMIC1"),
	PINCTRL_PIN(62, "PAD_DMIC1_IN"),
	PINCTRL_PIN(63, "PAD_CLK_DMIC2"),
	PINCTRL_PIN(64, "PAD_DMIC2_IN"),
	PINCTRL_PIN(65, "LINE_OUTL"),
	PINCTRL_PIN(66, "LINE_OUTR"),
	PINCTRL_PIN(67, "MIC_INL"),
	PINCTRL_PIN(68, "MIC_INR"),
	PINCTRL_PIN(69, "PAD_I2S_MCLK"),
	PINCTRL_PIN(70, "PAD_I2S_SCK"),
	PINCTRL_PIN(71, "PAD_I2S_WS"),
	PINCTRL_PIN(72, "PAD_I2S_SD_IN"),
	PINCTRL_PIN(73, "PAD_I2S_SD_OUT"),
	PINCTRL_PIN(74, "CH_SAR_PAD0"),
	PINCTRL_PIN(75, "CH_SAR_PAD1"),
	PINCTRL_PIN(76, "CH_SAR_PAD2"),
	PINCTRL_PIN(77, "CH_SAR_PAD3"),
	PINCTRL_PIN(78, "USB_HOST_DP"),
	PINCTRL_PIN(79, "USB_HOST_DM"),
	PINCTRL_PIN(80, "USB_DEV_DP"),
	PINCTRL_PIN(81, "USB_DEV_DM"),
	PINCTRL_PIN(82, "USB_HOST_PWREN"),
	PINCTRL_PIN(83, "USB_HOST_OCD"),
	PINCTRL_PIN(84, "USB_DEV_VBUS"),
	PINCTRL_PIN(85, "SSOR_I2C_SCL"),
	PINCTRL_PIN(86, "SSOR_I2C_SDA"),
	PINCTRL_PIN(87, "SPI_HOLD"),
	PINCTRL_PIN(88, "SPI_WP"),
	PINCTRL_PIN(89, "SPI_SO"), //pin is not gpio
	PINCTRL_PIN(90, "SPI_SI"), //pin is not gpio
	PINCTRL_PIN(91, "SPI_SCK"), //pin is not gpio
	PINCTRL_PIN(92, "SPI_CSN"), //pin is not gpio
};

static struct sharepin_cfg_addr pincfgaddr[] = {
	{ .pinl = 0, .pinh = 15, .pint = GPIO_TYPE_GENERIC, .pinaddr = GPIO_OE },
	{ .pinl = 16,
	  .pinh = 19,
	  .pint = GPIO_TYPE_UART0,
	  .pinaddr = UART0_GPIO_OE },
	{ .pinl = 20,
	  .pinh = 21,
	  .pint = GPIO_TYPE_UART1,
	  .pinaddr = UART1_GPIO_OE },
	{ .pinl = 22,
	  .pinh = 25,
	  .pint = GPIO_TYPE_UART2,
	  .pinaddr = UART2_GPIO_OE },
	{ .pinl = 26,
	  .pinh = 29,
	  .pint = GPIO_TYPE_PWM,
	  .pinaddr = PWM_GPIO_OE },
	{ .pinl = 30,
	  .pinh = 31,
	  .pint = GPIO_TYPE_I2C,
	  .pinaddr = XB2_I2C_GPIO_OE },
	{ .pinl = 32,
	  .pinh = 39,
	  .pint = GPIO_TYPE_SDIO0,
	  .pinaddr = SD0_GPIO_OE },
	{ .pinl = 40,
	  .pinh = 47,
	  .pint = GPIO_TYPE_SDIO1,
	  .pinaddr = SD1_GPIO_OE },
	{ .pinl = 48,
	  .pinh = 60,
	  .pint = GPIO_TYPE_SSOR,
	  .pinaddr = VIDEO_GPIO_OE },
	{ .pinl = 61,
	  .pinh = 64,
	  .pint = GPIO_TYPE_DMIC,
	  .pinaddr = DMIC_GPIO_OE },
	{ .pinl = 65,
	  .pinh = 68,
	  .pint = GPIO_TYPE_ADDA,
	  .pinaddr = AUDIO_ADDA_GPIO_OE },
	{ .pinl = 69,
	  .pinh = 73,
	  .pint = GPIO_TYPE_I2S,
	  .pinaddr = I2S_GPIO_OE },
	{ .pinl = 74,
	  .pinh = 77,
	  .pint = GPIO_TYPE_SARADC,
	  .pinaddr = SARADC_GPIO_OE },
	{ .pinl = 78,
	  .pinh = 79,
	  .pint = GPIO_TYPE_USBH,
	  .pinaddr = USB0_GPIO_OE },
	{ .pinl = 80,
	  .pinh = 81,
	  .pint = GPIO_TYPE_USBD,
	  .pinaddr = USB1_GPIO_OE },
	{ .pinl = 82,
	  .pinh = 84,
	  .pint = GPIO_TYPE_USB3,
	  .pinaddr = USB2_GPIO_OE },
	{ .pinl = 85,
	  .pinh = 86,
	  .pint = GPIO_TYPE_SSORI2C,
	  .pinaddr = SSOR_I2C_GPIO_OE },
	{ .pinl = 87,
	  .pinh = 88,
	  .pint = GPIO_TYPE_SPI,
	  .pinaddr = SPI_GPIO_OE },
};

static const unsigned int gpio_pins[] = {
	0,  1,	2,  3,	4,  5,	6,  7,	8,  9,	10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
	36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53,
	54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71,
	72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88
};

static const unsigned int uart0_pins[] = { 16, 17, 18, 19 };

static const unsigned int ssi_pins[] = { 16, 17, 18, 19 };

static const unsigned int uart1_pins[] = { 20, 21 };

static const unsigned int uart2_pins[] = { 22, 23, 24, 25 };

static const unsigned int pwm0_pins[] = { 26 };

static const unsigned int pwm1_pins[] = { 27 };

static const unsigned int pwm2_pins[] = { 28 };

static const unsigned int pwm3_pins[] = { 29 };

static const unsigned int i2c0_pins[] = { 30, 31 };

static const unsigned int i2cpwm_pins[] = { 26, 27 };

static const unsigned int sdio0_pins[] = { 32, 33, 34, 35, 36, 37 };

static const unsigned int sdio0_wp_pins[] = { 38 };

static const unsigned int sdio0_cd_pins[] = { 39 };

static const unsigned int sdio1_pins[] = { 40, 41, 42, 43, 44, 45 };

static const unsigned int sdio1_video_pins[] = {
	8, 48, 49, 58, 59, 60,
};

static const unsigned int sdio1_wp_pins[] = { 46 };

static const unsigned int sdio1_cd_pins[] = { 47 };

static const unsigned int dvp_pins[] = { 48, 49, 50, 51, 52, 53, 54,
					 55, 56, 57, 58, 59, 60 };

static const unsigned int mipi_pins[] = { 50, 51, 52, 53, 54, 55, 56, 57 };

static const unsigned int dmic1_pins[] = { 61, 62 };

static const unsigned int dmic2_pins[] = { 63, 64 };

static const unsigned int lineout_pins[] = { 65, 66 };

static const unsigned int amic_pins[] = { 65, 66 };

static const unsigned int dmic_pins[] = { 67, 68 };

static const unsigned int i2s_pins[] = { 69, 70, 71, 72, 73 };

static const unsigned int i2sxb2_pins[] = { 16, 17, 18, 19, 29 };

static const unsigned int i2sdvp_pins[] = { 8, 48, 49, 58, 59 };

static const unsigned int saradc0_pins[] = { 74 };

static const unsigned int saradc1_pins[] = { 75 };

static const unsigned int saradc2_pins[] = { 76 };

static const unsigned int saradc3_pins[] = { 77 };

static const unsigned int usbh_pins[] = { 78, 79, 82, 83 };

static const unsigned int usbd_pins[] = { 80, 81, 84 };

static const unsigned int etnled0_pins[] = { 26 };

static const unsigned int etnled1_pins[] = { 27 };

static const unsigned int etnled2_pins[] = { 28 };

static const unsigned int usbd_uart2_pins[] = { 80, 81 };

static const unsigned int i2c1_pins[] = { 85, 86 };

static const unsigned int spi_pins[] = { 87, 88, 89, 90, 91, 92 };

static const unsigned int h265_uart_pins[] = { 0, 1 };

static const unsigned int pdm_pins[] = { 70, 73 };

static const unsigned int spdifout_pins[] = { 69 };

static const unsigned int pwmsd_pins[] = { 41, 42, 42, 44 };

static const unsigned int default_pins[] = {};

#define GPIO_GROUP_SELECT	0
#define UART0_GROUP_SELECT	1
#define UART1_GROUP_SELECT	2
#define UART2_GROUP_SELECT	3
#define PWM0_GROUP_SELECT	4
#define PWM1_GROUP_SELECT	5
#define PWM2_GROUP_SELECT	6
#define PWM3_GROUP_SELECT	7
#define DMIC1_GROUP_SELECT	8
#define DMIC2_GROUP_SELECT	9
#define I2S_GROUP_SELECT	10
#define I2SXB2_GROUP_SELECT	11
#define I2SDVP_GROUP_SELECT	12
#define AMIC_GROUP_SELECT	13
#define LINEOUT_GROUP_SELECT	14
#define USBD_GROUP_SELECT	15
#define ETNLED0_GROUP_SELECT	16
#define ETNLED1_GROUP_SELECT	17
#define ETNLED2_GROUP_SELECT	18
#define USBH_GROUP_SELECT	19
#define SARADC0_GROUP_SELECT	20
#define SARADC1_GROUP_SELECT	21
#define SARADC2_GROUP_SELECT	22
#define SARADC3_GROUP_SELECT	23
#define MIPI_GROUP_SELECT	24
#define DVP_GROUP_SELECT	25
#define SSI_GROUP_SELECT	26
#define SDIO0_GROUP_SELECT	27
#define SDIO0WP_GROUP_SELECT	28
#define SDIO0CD_GROUP_SELECT	29
#define SDIO1_GROUP_SELECT	30
#define SDIO1VIDEO_GROUP_SELECT 31
#define SDIO1WP_GROUP_SELECT	32
#define SDIO1CD_GROUP_SELECT	33
#define I2C0_GROUP_SELECT	34
#define I2CPWM_GROUP_SELECT	35
#define UART2_USB_GROUP_SELECT	36
#define DMIC_GROUP_SELECT	37
#define I2C1_GROUP_SELECT	38
#define SPI_GROUP_SELECT	39
#define H265_UART_GROUP_SELECT	40
#define PDM_GROUP_SELECT	41
#define SPDIF_OUT_GROUP_SELECT	42
#define PWMSD_GROUP_SELECT	43
#define DEFAULT_GROUP_SELECT	44

static const struct rts_pin_group rts_pin_groups[] = {
	{
		.name = "gpiogrp",
		.pins = gpio_pins,
		.num_pins = ARRAY_SIZE(gpio_pins),
	},
	{
		.name = "uart0grp",
		.pins = uart0_pins,
		.num_pins = ARRAY_SIZE(uart0_pins),
	},
	{
		.name = "uart1grp",
		.pins = uart1_pins,
		.num_pins = ARRAY_SIZE(uart1_pins),
	},
	{
		.name = "uart2grp",
		.pins = uart2_pins,
		.num_pins = ARRAY_SIZE(uart2_pins),
	},
	{
		.name = "pwm0grp",
		.pins = pwm0_pins,
		.num_pins = ARRAY_SIZE(pwm0_pins),
	},
	{
		.name = "pwm1grp",
		.pins = pwm1_pins,
		.num_pins = ARRAY_SIZE(pwm1_pins),
	},
	{
		.name = "pwm2grp",
		.pins = pwm2_pins,
		.num_pins = ARRAY_SIZE(pwm2_pins),
	},
	{
		.name = "pwm3grp",
		.pins = pwm3_pins,
		.num_pins = ARRAY_SIZE(pwm3_pins),
	},
	{
		.name = "dmic1grp",
		.pins = dmic1_pins,
		.num_pins = ARRAY_SIZE(dmic1_pins),
	},
	{
		.name = "dmic2grp",
		.pins = dmic2_pins,
		.num_pins = ARRAY_SIZE(dmic2_pins),
	},
	{
		.name = "i2sgrp",
		.pins = i2s_pins,
		.num_pins = ARRAY_SIZE(i2s_pins),
	},
	{
		.name = "i2sxb2grp",
		.pins = i2sxb2_pins,
		.num_pins = ARRAY_SIZE(i2sxb2_pins),
	},
	{
		.name = "i2sdvpgrp",
		.pins = i2sdvp_pins,
		.num_pins = ARRAY_SIZE(i2sdvp_pins),
	},
	{
		.name = "amicgrp",
		.pins = amic_pins,
		.num_pins = ARRAY_SIZE(amic_pins),
	},
	{
		.name = "lineoutgrp",
		.pins = lineout_pins,
		.num_pins = ARRAY_SIZE(lineout_pins),
	},
	{
		.name = "usbdgrp",
		.pins = usbd_pins,
		.num_pins = ARRAY_SIZE(usbd_pins),
	},
	{
		.name = "etnled0grp",
		.pins = etnled0_pins,
		.num_pins = ARRAY_SIZE(etnled0_pins),
	},
	{
		.name = "etnled1grp",
		.pins = etnled1_pins,
		.num_pins = ARRAY_SIZE(etnled1_pins),
	},
	{
		.name = "etnled2grp",
		.pins = etnled2_pins,
		.num_pins = ARRAY_SIZE(etnled2_pins),
	},
	{
		.name = "usbhgrp",
		.pins = usbh_pins,
		.num_pins = ARRAY_SIZE(usbh_pins),
	},
	{
		.name = "saradc0grp",
		.pins = saradc0_pins,
		.num_pins = ARRAY_SIZE(saradc0_pins),
	},
	{
		.name = "saradc1grp",
		.pins = saradc1_pins,
		.num_pins = ARRAY_SIZE(saradc1_pins),
	},
	{
		.name = "saradc2grp",
		.pins = saradc2_pins,
		.num_pins = ARRAY_SIZE(saradc2_pins),
	},
	{
		.name = "saradc3grp",
		.pins = saradc3_pins,
		.num_pins = ARRAY_SIZE(saradc3_pins),
	},
	{
		.name = "mipigrp",
		.pins = mipi_pins,
		.num_pins = ARRAY_SIZE(mipi_pins),
	},
	{
		.name = "dvpgrp",
		.pins = dvp_pins,
		.num_pins = ARRAY_SIZE(dvp_pins),
	},
	{
		.name = "ssigrp",
		.pins = ssi_pins,
		.num_pins = ARRAY_SIZE(ssi_pins),
	},
	{
		.name = "sdio0grp",
		.pins = sdio0_pins,
		.num_pins = ARRAY_SIZE(sdio0_pins),
	},
	{
		.name = "sdio0wpgrp",
		.pins = sdio0_wp_pins,
		.num_pins = ARRAY_SIZE(sdio0_wp_pins),
	},
	{
		.name = "sdio0cdgrp",
		.pins = sdio0_cd_pins,
		.num_pins = ARRAY_SIZE(sdio0_cd_pins),
	},
	{
		.name = "sdio1grp",
		.pins = sdio1_pins,
		.num_pins = ARRAY_SIZE(sdio1_pins),
	},
	{
		.name = "sdio1videogrp",
		.pins = sdio1_video_pins,
		.num_pins = ARRAY_SIZE(sdio1_video_pins),
	},
	{
		.name = "sdio1wpgrp",
		.pins = sdio1_wp_pins,
		.num_pins = ARRAY_SIZE(sdio1_wp_pins),
	},
	{
		.name = "sdio1cdgrp",
		.pins = sdio1_cd_pins,
		.num_pins = ARRAY_SIZE(sdio1_cd_pins),
	},
	{
		.name = "i2c0grp",
		.pins = i2c0_pins,
		.num_pins = ARRAY_SIZE(i2c0_pins),
	},
	{
		.name = "i2cpwmgrp",
		.pins = i2cpwm_pins,
		.num_pins = ARRAY_SIZE(i2cpwm_pins),
	},
	{
		.name = "uart2usbdgrp",
		.pins = usbd_uart2_pins,
		.num_pins = ARRAY_SIZE(usbd_uart2_pins),
	},
	{
		.name = "dmicgrp",
		.pins = dmic_pins,
		.num_pins = ARRAY_SIZE(dmic_pins),
	},
	{
		.name = "i2c1grp",
		.pins = i2c1_pins,
		.num_pins = ARRAY_SIZE(i2c1_pins),
	},
	{
		.name = "spigrp",
		.pins = spi_pins,
		.num_pins = ARRAY_SIZE(spi_pins),
	},
	{
		.name = "h265uartgrp",
		.pins = h265_uart_pins,
		.num_pins = ARRAY_SIZE(h265_uart_pins),
	},
	{
		.name = "pdmgrp",
		.pins = pdm_pins,
		.num_pins = ARRAY_SIZE(pdm_pins),
	},
	{
		.name = "spdifoutgrp",
		.pins = spdifout_pins,
		.num_pins = ARRAY_SIZE(spdifout_pins),
	},
	{
		.name = "pwmsdgrp",
		.pins = pwmsd_pins,
		.num_pins = ARRAY_SIZE(pwmsd_pins),
	},
	{
		.name = "default",
		.pins = default_pins,
		.num_pins = ARRAY_SIZE(default_pins),
	},
};

static const char *const gpiogrps[] = { "gpiogrp" };

static const char *const uartgrps[] = { "uart0grp", "uart1grp", "uart2grp",
					"uart2usbdgrp" };

static const char *const pwmgrps[] = { "pwm0grp", "pwm1grp", "pwm2grp",
				       "pwm3grp", "pwmsdgrp" };

static const char *const audiogrps[] = { "dmic1grp",	"dmic2grp",   "dmicgrp",
					 "amicgrp",	"lineoutgrp", "i2sgrp",
					 "i2sxb2grp",	"i2sdvpgrp",  "pdmgrp",
					 "spdifoutgrp", "default" };
static const char *const usbdgrps[] = { "usbdgrp", "default" };

static const char *const etnledgrps[] = { "etnled0grp", "etnled1grp",
					  "etnled2grp" };

static const char *const saradcgrps[] = {
	"saradc0grp",
	"saradc1grp",
	"saradc2grp",
	"saradc3grp",
};

static const char *const usbhgrps[] = { "usbhgrp" };

static const char *const ssorgrps[] = { "mipigrp", "dvpgrp", "default" };

static const char *const ssigrps[] = { "ssigrp" };

static const char *const sdio0grps[] = { "sdio0grp", "sdio0wpgrp",
					 "sdio0cdgrp" };

static const char *const sdio1grps[] = { "sdio1grp", "sdio1wpgrp", "sdio1cdgrp",
					 "sdio1videogrp" };

static const char *const i2cgrps[] = { "i2c0grp", "i2cpwmgrp", "i2c1grp" };

static const char *const spigrps[] = { "spigrp" };

static const char *const h265uartgrps[] = { "h265uartgrp" };

static const struct rts_func rts_functions[] = {
	{
		.name = "gpiofunc",
		.groups = gpiogrps,
		.num_groups = ARRAY_SIZE(gpiogrps),
	},
	{
		.name = "sdio0func",
		.groups = sdio0grps,
		.num_groups = ARRAY_SIZE(sdio0grps),
	},
	{
		.name = "sdio1func",
		.groups = sdio1grps,
		.num_groups = ARRAY_SIZE(sdio1grps),
	},
	{
		.name = "uartfunc",
		.groups = uartgrps,
		.num_groups = ARRAY_SIZE(uartgrps),
	},
	{
		.name = "pwmfunc",
		.groups = pwmgrps,
		.num_groups = ARRAY_SIZE(pwmgrps),
	},
	{
		.name = "audiofunc",
		.groups = audiogrps,
		.num_groups = ARRAY_SIZE(audiogrps),
	},
	{
		.name = "usbdfunc",
		.groups = usbdgrps,
		.num_groups = ARRAY_SIZE(usbdgrps),
	},
	{
		.name = "etnledfunc",
		.groups = etnledgrps,
		.num_groups = ARRAY_SIZE(etnledgrps),
	},
	{
		.name = "usbhfunc",
		.groups = usbhgrps,
		.num_groups = ARRAY_SIZE(usbhgrps),
	},
	{
		.name = "saradcfunc",
		.groups = saradcgrps,
		.num_groups = ARRAY_SIZE(saradcgrps),
	},
	{
		.name = "ssorfunc",
		.groups = ssorgrps,
		.num_groups = ARRAY_SIZE(ssorgrps),
	},
	{
		.name = "ssifunc",
		.groups = ssigrps,
		.num_groups = ARRAY_SIZE(ssigrps),
	},
	{
		.name = "i2cfunc",
		.groups = i2cgrps,
		.num_groups = ARRAY_SIZE(i2cgrps),
	},
	{
		.name = "spifunc",
		.groups = spigrps,
		.num_groups = ARRAY_SIZE(spigrps),
	},
	{
		.name = "h265uartfunc",
		.groups = h265uartgrps,
		.num_groups = ARRAY_SIZE(h265uartgrps),
	},
};

#define HAIMR		  0x10
#define HAIMR_START	  BIT(31)
#define HAIMR_WRITE	  BIT(30)
#define HAIMR_START_WRITE (HAIMR_START | HAIMR_WRITE)

#define H_SD_LDO_CFG0	   0xFF52
#define SD_LDO_TUNE33	   0x71
#define H_SD_LDO_CTRL	   0xFF54
#define SD_LDO_LDO3318_POW 0x01

#define REG_RW_RETRY_CNT 3

#define rts_pinctrl_readl_sdio(addr, reg) ioread32((addr) + (reg))
#define rts_pinctrl_writel_sdio(addr, reg, value) \
	iowrite32(value, (addr) + (reg))

#endif