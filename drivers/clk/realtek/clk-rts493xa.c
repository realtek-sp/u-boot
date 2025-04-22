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

#include <div64.h>
#include <dm.h>
#include <common.h>
#include <clk-uclass.h>
#include <asm/io.h>
#include <log.h>
#include <linux/compat.h>
#include <linux/delay.h>
#include <linux/bitfield.h>
#include <linux/log2.h>
#include <linux/clk-provider.h>
#include "clk.h"

#include <dt-bindings/clock/rts493xa-clock.h>
#include "clk-rts493xa.h"

static inline u32 rts_clk_readl(struct rts493xa_clk_priv *priv, u32 offset)
{
	return readl(priv->clk_mapped_addr + offset);
}

static inline void rts_clk_writel(struct rts493xa_clk_priv *priv,
				  unsigned int val, u32 offset)
{
	writel(val, priv->clk_mapped_addr + offset);
}

static void setchgbit(struct rts_divider *divider, int nr)
{
	u32 val;

	if (nr == CK_CHANGE_NULL)
		return;
	val = readl(divider->base_addr + CLK_CHANGE_R);
	val |= (1 << nr);
	writel(val, divider->base_addr + CLK_CHANGE_R);
}

static void clrchgbit(struct rts_divider *divider, int nr)
{
	u32 val;

	if (nr == CK_CHANGE_NULL)
		return;
	val = readl(divider->base_addr + CLK_CHANGE_R);
	val &= ~(1 << nr);
	writel(val, divider->base_addr + CLK_CHANGE_R);
}

static short bignumcmp(unsigned short *a, unsigned short *b)
{
	short i;

	for (i = BIG_SHORT_NUM - 1; i >= 0; i--) {
		if (a[i] > b[i])
			return 1;
		else if (a[i] < b[i])
			return -1;
	}

	return 0;
}

static short bignumsub(unsigned short *a, unsigned short *b)
{
	short i, sub = 0;

	for (i = 0; i < BIG_SHORT_NUM; i++) {
		if (a[i] < b[i]) {
			a[i] -= b[i] + sub;
			sub = 1;
		} else {
			a[i] -= b[i];
			if (!a[i] && sub) {
				a[i] = 0xffff;
				sub = 1;
			} else {
				a[i] -= sub;
				sub = 0;
			}
		}
	}

	return sub;
}

static short bignumsubs(unsigned short *a, unsigned short *b)
{
	short i, sub = 0;

	for (i = 0; i < BIG_SHORT_NUM + 1; i++) {
		if (a[i] < b[i]) {
			a[i] -= b[i];
			a[i] -= sub;
			sub = 1;
		} else {
			a[i] -= b[i];
			if (!a[i] && sub) {
				a[i] = 0xffff;
				sub = 1;
			} else {
				a[i] -= sub;
				sub = 0;
			}
		}
	}

	return sub;
}

static void bignummuls(unsigned short *c, unsigned short *a, unsigned short b)
{
	short i, k;
	unsigned short add;
	ulong m;

	for (i = 0; i < BIG_SHORT_NUM + 1; i++)
		c[i] = 0;

	for (i = 0; i < BIG_SHORT_NUM; i++) {
		m = (ulong)a[i] * (ulong)b;
		c[i] += m & 0xffff;

		if (c[i] < (m & 0xffff))
			add = (m >> 16) + 1;
		else
			add = m >> 16;
		k = i + 1;

		for (; c[k] += add, c[k] < add; add = 1, k++)
			;
	}
}

static void bignummul(unsigned short *c, unsigned short *a, unsigned short *b)
{
	short i, j, k;
	unsigned short add;
	ulong m;

	memset((void *)c, 0, BIG_LONG_NUM * 2);

	for (i = 0; i < BIG_SHORT_NUM; i++) {
		for (j = 0; j < BIG_SHORT_NUM; j++) {
			m = (ulong)a[i] * (ulong)b[j];

			c[i + j] += m & 0xffff;
			if (c[i + j] < (m & 0xffff))
				add = (m >> 16) + 1;
			else
				add = m >> 16;
			k = i + j + 1;

			for (; c[k] += add, c[k] < add; add = 1, k++)
				;
		}
	}
}

static void bignumdiv(unsigned short *a, unsigned short *c, unsigned short *b)
{
	short i, h;
	ulong m, n;
	unsigned short *d, e[BIG_SHORT_NUM + 1];

	for (i = 0; i < BIG_SHORT_NUM; i++)
		a[i] = 0;

	d = (unsigned short *)&c[BIG_SHORT_NUM];

	for (i = BIG_SHORT_NUM - 1; i >= 0; i--) {
		for (; h = bignumcmp(d, b), h >= 0; bignumsub(d, b), a[i + 1]++)
			;

		d = (unsigned short *)&c[i];

		do {
			m = ((ulong)c[i + BIG_SHORT_NUM] << 16) +
			    (ulong)c[i + BIG_SHORT_NUM - 1];
			n = m / ((ulong)b[BIG_SHORT_NUM - 1] + 1);
			if (n)
				a[i] += n;
			else {
				if (m > b[BIG_SHORT_NUM - 1]) {
					d[BIG_SHORT_NUM - 1] =
						1 - bignumsub(d, b);
					a[i]++;
				}
				break;
			}

			memset((void *)e, 0, (BIG_SHORT_NUM + 1) << 1);

			bignummuls(e, b, (unsigned short)n);
			bignumsubs(d, e);

		} while (1);
	}

	for (; h = bignumcmp(d, b), h >= 0; bignumsub(d, b), a[0]++)
		;
}

static ulong rlx_gpll_recalc(struct clk *clk)
{
	u32 reg, n, f, rate;
	u64 t;
	struct clk_divider *div = (struct clk_divider *)to_clk_divider(clk);
	struct clk_composite *composite = (struct clk_composite *)clk->data;
	ulong parent_rate;

	parent_rate = clk_get_parent_rate(&composite->clk);

	reg = readl(div->reg + GPLL_SCCG_CFG1);
	reg &= 0x1fffff;
	n = (reg & 0x1ff) + 2;
	f = reg >> 9;

	n <<= 12;
	n += f;

	debug("%s, reg %#x, n %u, f %u parent_rate: %lu\n",
	      clk_hw_get_name(clk), reg, n, f, parent_rate);

	bignummul((unsigned short *)&t, (unsigned short *)&parent_rate,
		  (unsigned short *)&n);

	rate = (t >> 12);

	debug("%s prate: %u\n", clk_hw_get_name(clk), rate);

	return rate;
}

static ulong rlx_gpll_set_rate(struct clk *clk, ulong rate)
{
	u64 t = rate;
	u32 n, f, reg;
	struct clk_divider *div = (struct clk_divider *)to_clk_divider(clk);
	struct clk_composite *composite = (struct clk_composite *)clk->data;
	ulong parent_rate;

	parent_rate = clk_get_parent_rate(&composite->clk);

	t <<= 12;
	t += (parent_rate >> 1);
	bignumdiv((unsigned short *)&n, (unsigned short *)&t,
		  (unsigned short *)&parent_rate);

	if ((n & 0xfff) != 0)
		n++;
	f = n & 0xfff;
	n >>= 12;

	reg = (f << 9) + (n - 2);
	writel(reg, div->reg + GPLL_SCCG_CFG1);

	return 0;
}

static ulong rlx_gpll_round_rate(struct clk *clk, ulong rate)
{
	// struct clk_divider *div = (struct clk_divider *)to_clk_divider(clk);
	struct clk_composite *composite = (struct clk_composite *)clk->data;
	ulong parent_rate = clk_get_parent_rate(&composite->clk);
	int n = rate / parent_rate;
	ulong round_rate;
	u64 t = rate;

	t <<= 12;
	t += (parent_rate >> 1);
	bignumdiv((unsigned short *)&n, (unsigned short *)&t,
		  (unsigned short *)&parent_rate);
	if ((n & 0xfff) != 0)
		n++;
	t = 0;
	bignummul((unsigned short *)&t, (unsigned short *)&parent_rate,
		  (unsigned short *)&n);

	round_rate = t >> 12;

	debug("%s round:%lu\n", clk_hw_get_name(clk), round_rate);

	return round_rate;
}

static int rlx_gpll_enable_clk(struct clk *clk)
{
	u32 reg;
	u32 time = 5000;
	// struct rts493xa_clk_priv *priv = dev_get_priv(clk->dev);
	struct clk_gate *gate = (struct clk_gate *)to_clk_gate(clk);

	reg = readl(gate->reg + GPLL_SCCG_CFG2);
	reg |= CMU_SSC_RSTB;
	writel(reg, gate->reg + GPLL_SCCG_CFG2);

	reg = readl(gate->reg + GPLL_SCCG_CFG3);
	reg |= CMU_SSC_EN;
	writel(reg, gate->reg + GPLL_SCCG_CFG3);

	reg = readl(gate->reg + GPLL_CTRL);
	reg |= PPOW_LDO;
	writel(reg, gate->reg + GPLL_CTRL);
	udelay(5);
	reg |= GPLL_EN;
	writel(reg, gate->reg + GPLL_CTRL);

	while (--time) {
		reg = readl(gate->reg + GPLL_STATUS);
		if (reg & SYSPLL_CK_RDY)
			break;
		udelay(1);
	}

	if (time == 0) {
		debug("%s enable failed\n", clk_hw_get_name(clk));
		return -ETIMEDOUT;
	}

	//xb2flush();
	return 0;
}

static int rlx_gpll_disable_clk(struct clk *clk)
{
	u32 reg;
	// struct rts493xa_clk_priv *priv = dev_get_priv(clk->dev);
	struct clk_gate *gate = (struct clk_gate *)to_clk_gate(clk);

	reg = readl(gate->reg + GPLL_CTRL);
	reg &= ~GPLL_EN;
	writel(reg, gate->reg + GPLL_CTRL);
	reg &= ~PPOW_LDO;
	writel(reg, gate->reg + GPLL_CTRL);

	reg = readl(gate->reg + GPLL_SCCG_CFG0);
	reg &= ~REG_EN_SSC;
	writel(reg, gate->reg + GPLL_SCCG_CFG0);

	//xb2flush();
	return 0;
}

static const struct clk_ops clk_rts_gpll0_divider_ops = {
	.get_rate = rlx_gpll_recalc,
	.round_rate = rlx_gpll_round_rate,
};

static const struct clk_ops clk_rts_gpll_divider_ops = {
	.get_rate = rlx_gpll_recalc,
	.set_rate = rlx_gpll_set_rate,
	.round_rate = rlx_gpll_round_rate,
};

static const struct clk_ops clk_rts_gpll_gate_ops = {
	.enable = rlx_gpll_enable_clk,
	.disable = rlx_gpll_disable_clk,
};

static struct clk *rlx_register_gpll_clk(struct rts493xa_clk_priv *priv,
					 struct clk_rlx *rlxclk, int flags)
{
	struct clk *clk = ERR_PTR(-ENOMEM);
	struct clk_divider *div = NULL;
	struct clk_gate *gate = NULL;
	struct clk_mux *mux = NULL;
	const struct clk_ops *div_ops = NULL;
	const struct clk_ops *gate_ops = NULL;
	const struct clk_ops *mux_ops = NULL;
	const char *const *parent_names;
	int num_parents;

	parent_names = rlxclk->parent_names;
	num_parents = 1;

	div = kzalloc(sizeof(*div), GFP_KERNEL);
	if (!div)
		goto fail;

	div->reg = priv->pll_mapped_addr + rlxclk->clkreg;
	div->shift = RTS_CLK_DIV_SHIFT;
	div->table = rlxclk->div_array;
	div->width = 4;
	if (!strcmp(rlxclk->name, "gpll0"))
		div_ops = &clk_rts_gpll0_divider_ops;
	else
		div_ops = &clk_rts_gpll_divider_ops;

	gate = kzalloc(sizeof(*gate), GFP_KERNEL);
	if (!gate)
		goto fail;

	gate->reg = priv->pll_mapped_addr + rlxclk->clkreg;
	gate->bit_idx = rlxclk->bit_idx;
	gate->flags = flags;
	gate_ops = &clk_rts_gpll_gate_ops;

	clk = clk_register_composite(NULL, rlxclk->name, parent_names,
				     num_parents, &mux->clk, mux_ops, &div->clk,
				     div_ops, &gate->clk, gate_ops, flags);
	if (IS_ERR(clk))
		goto fail;

	return clk;
fail:
	kfree(gate);
	kfree(div);
	kfree(mux);
	return ERR_CAST(clk);
}

static ulong rlx_decset_rate(struct clk *clk, ulong rate)
{
	u64 t = rate;
	u32 n, f, reg, divreg;
	ulong parent_rate;
	ulong divisor;
	int i;
	ulong flags;

	struct rts_divider *divider = to_rts_divider(clk);
	struct clk_composite *composite = (struct clk_composite *)clk->data;

	parent_rate = clk_get_parent_rate(&composite->clk);

	parent_rate <<= 6;
	parent_rate += (rate >> 1);

	bignumdiv((unsigned short *)&divisor, (unsigned short *)&parent_rate,
		  (unsigned short *)&rate);

	for (i = 7; i >= 0; i--) {
		t = ((i + 1) << 6);
		if (t <= divisor)
			break;
	}

	if (i < 0) {
		n = 0;
		f = 0;
	} else {
		n = i;
		f = 64 - (((n + 1) << 12) + (divisor >> 1)) / divisor;
	}

	divreg = (f << 16) | (i << 8);

	spin_lock_irqsave(&clk_spinlock, flags);

	reg = readl(divider->reg) & ~0x3fffff;

	setchgbit(divider, divider->clk_change_bit);

	reg |= divreg;
	writel(reg, divider->reg);

	clrchgbit(divider, divider->clk_change_bit);
	//xb2flush();

	spin_unlock_irqrestore(&clk_spinlock, flags);

	debug("setrate: %s reg:%x\n", clk_hw_get_name(clk), reg);

	return 0;
}

static ulong rlx_decrecalc(struct clk *clk)
{
	u32 reg, n, f, rate;
	u64 t, tm;
	struct clk_divider *div = (struct clk_divider *)to_clk_divider(clk);
	struct clk_composite *composite = (struct clk_composite *)clk->data;
	ulong parent_rate;

	parent_rate = clk_get_parent_rate(&composite->clk);

	reg = readl(div->reg) & 0xffff00;

	n = (reg & 0x700) >> 8;
	f = (reg & 0x3f0000) >> 16;

	debug("recalc:%s %x %x %x %ld\n", clk_hw_get_name(clk), reg, n, f,
	      parent_rate);

	tm = 0;
	t = 64 - f;
	bignummul((unsigned short *)&tm, (unsigned short *)&parent_rate,
		  (unsigned short *)&t);

	tm += ((n + 1) << 5);
	t = (n + 1) << 6;
	rate = 0;
	bignumdiv((unsigned short *)&rate, (unsigned short *)&tm,
		  (unsigned short *)&t);

	debug("recalc:%s r:%u, %x\n", clk_hw_get_name(clk), rate, n);

	return rate + 1;
}

static ulong rlx_decround_rate(struct clk *clk, ulong rate)
{
	struct clk_composite *composite = (struct clk_composite *)clk->data;
	ulong parent_rate = clk_get_parent_rate(&composite->clk);
	ulong divisor;
	ulong f = 0, n = 1, r = 0;
	int i;
	u64 t, tm;

	tm = parent_rate;
	tm <<= 6;
	// tm += (rate>>1);

	bignumdiv((unsigned short *)&divisor, (unsigned short *)&tm,
		  (unsigned short *)&rate);

	for (i = 7; i >= 0; i--) {
		t = ((i + 1) << 6);
		if (t <= divisor)
			break;
	}

	if (i < 0) {
		n = 0;
		f = 0;
	} else {
		n = i;
		f = 64 - (((n + 1) << 12) + (divisor >> 1)) / divisor;
	}

	debug("round:n %ld f %ld\n", n, f);

	tm = 0;
	t = 64 - f;
	bignummul((unsigned short *)&tm, (unsigned short *)&parent_rate,
		  (unsigned short *)&t);

	tm += ((n + 1) << 5);
	t = (n + 1) << 6;
	r = 0;
	bignumdiv((unsigned short *)&r, (unsigned short *)&tm,
		  (unsigned short *)&t);

	debug("%s round:%ld\n", clk_hw_get_name(clk), r);

	return r;
}

static const struct clk_ops clk_rts_decdivider_ops = {
	.get_rate = rlx_decrecalc,
	.set_rate = rlx_decset_rate,
	.round_rate = rlx_decround_rate,
};

static struct clk *rlx_register_decdivider_clk(struct rts493xa_clk_priv *priv,
					       struct clk_rlx *rlxclk,
					       int flags)
{
	struct clk *clk = ERR_PTR(-ENOMEM);
	struct rts_divider *div = NULL;
	struct clk_gate *gate = NULL;
	struct clk_mux *mux = NULL;
	const struct clk_ops *div_ops = NULL;
	const struct clk_ops *gate_ops = NULL;
	const struct clk_ops *mux_ops = NULL;
	const char *const *parent_names;
	int num_parents;

	parent_names = rlxclk->parent_names;
	num_parents = 1;

	div = kzalloc(sizeof(*div), GFP_KERNEL);
	if (!div)
		goto fail;

	div->reg = priv->clk_mapped_addr + rlxclk->clkreg;
	div->shift = RTS_CLK_DIV_SHIFT;
	div->table = rlxclk->div_array;
	div->width = 4;
	div->clk_change_bit = rlxclk->clk_change;
	div->base_addr = priv->clk_mapped_addr;
	div_ops = &clk_rts_decdivider_ops;

	gate = kzalloc(sizeof(*gate), GFP_KERNEL);
	if (!gate)
		goto fail;

	gate->reg = priv->clk_mapped_addr + rlxclk->clkreg;
	gate->bit_idx = rlxclk->bit_idx;
	gate->flags = flags;
	gate_ops = &clk_gate_ops;

	clk = clk_register_composite(NULL, rlxclk->name, parent_names,
				     num_parents, &mux->clk, mux_ops, &div->clk,
				     div_ops, &gate->clk, gate_ops, flags);
	if (IS_ERR(clk))
		goto fail;

	return clk;
fail:
	kfree(gate);
	kfree(div);
	kfree(mux);
	return ERR_CAST(clk);
}

static ulong clk_divider_recalc_rate(struct clk *clk)
{
	struct rts_divider *divider = to_rts_divider(clk);
	ulong parent_rate = clk_get_parent_rate(clk);
	unsigned int val;

	val = readl(divider->reg);
	val >>= divider->shift;
	val &= clk_div_mask(divider->width);

	return divider_recalc_rate(clk, parent_rate, val, divider->table,
				   divider->flags, divider->width);
}

static ulong clk_divider_set_rate(struct clk *clk, ulong rate)
{
	struct rts_divider *divider = to_clk_divider(clk);
	ulong parent_rate = clk_get_parent_rate(clk);
	int value;
	u32 val;

	value = divider_get_val(rate, parent_rate, divider->table,
				divider->width, divider->flags);
	if (value < 0)
		return value;

	if (divider->flags & CLK_DIVIDER_HIWORD_MASK) {
		val = clk_div_mask(divider->width) << (divider->shift + 16);
	} else {
		val = readl(divider->reg);
		val &= ~(clk_div_mask(divider->width) << divider->shift);
	}
	val |= (u32)value << divider->shift;
	writel(val, divider->reg);

	return clk_get_rate(clk);
}

static ulong rts_clk_set_rate(struct clk *clk, ulong rate)
{
	struct rts_divider *divider = to_rts_divider(clk);

	debug("%s clk_change_bit: %u, divider->base_addr %p, rate %lu\n",
	      clk_hw_get_name(clk), divider->clk_change_bit, divider->base_addr,
	      rate);

	setchgbit(divider, divider->clk_change_bit);

	clk_divider_set_rate(clk, rate);

	clrchgbit(divider, divider->clk_change_bit);

	return clk_get_rate(clk);
}

static const struct clk_ops rts_clk_divider_ops = {
	.get_rate = clk_divider_recalc_rate,
	.set_rate = rts_clk_set_rate,
	// .round_rate = rts_clk_round_rate,
};

static struct clk *rlx_register_common_clk(struct rts493xa_clk_priv *priv,
					   struct clk_rlx *rlxclk, int flags)
{
	struct clk *clk = ERR_PTR(-ENOMEM);
	struct rts_divider *div = NULL;
	struct clk_gate *gate = NULL;
	struct clk_mux *mux = NULL;
	const struct clk_ops *div_ops = NULL;
	const struct clk_ops *gate_ops = NULL;
	const struct clk_ops *mux_ops = NULL;
	const char *const *parent_names;
	int num_parents;

	if (rlxclk->mux_id != NO_RTS_MUX) {
		mux = kzalloc(sizeof(*mux), GFP_KERNEL);
		if (!mux)
			goto fail;

		mux->reg = priv->clk_mapped_addr + rlxclk->clkreg;
		mux->shift = RTS_CLK_SRC_SEL_SHIFT;
		mux->mask = 0x3;
		mux->flags = flags;
		mux->num_parents = rlxclk->mux_num_parents;
		mux->parent_names = rlxclk->mux_parent_names;
		parent_names = mux->parent_names;
		num_parents = mux->num_parents;
		mux_ops = &clk_mux_ops;
	} else {
		parent_names = rlxclk->parent_names;
		num_parents = 1;
	}

	if (rlxclk->div_id != NO_RTS_DIV) {
		div = kzalloc(sizeof(*div), GFP_KERNEL);
		if (!div)
			goto fail;

		div->reg = priv->clk_mapped_addr + rlxclk->clkreg;
		div->shift = RTS_CLK_DIV_SHIFT;
		div->table = rlxclk->div_array;
		div->width = 4;
		div->clk_change_bit = rlxclk->clk_change;
		div->base_addr = priv->clk_mapped_addr;
		div_ops = &rts_clk_divider_ops;
	}

	if (rlxclk->gate_id != NO_RTS_GATE) {
		gate = kzalloc(sizeof(*gate), GFP_KERNEL);
		if (!gate)
			goto fail;

		gate->reg = priv->clk_mapped_addr + rlxclk->clkreg;
		gate->bit_idx = rlxclk->bit_idx;
		gate->flags = flags;
		gate_ops = &clk_gate_ops;
	}

	clk = clk_register_composite(NULL, rlxclk->name, parent_names,
				     num_parents, &mux->clk, mux_ops, &div->clk,
				     div_ops, &gate->clk, gate_ops, flags);

	if (IS_ERR(clk))
		goto fail;

	return clk;
fail:
	kfree(gate);
	kfree(div);
	kfree(mux);
	return ERR_CAST(clk);
}

static void rlx_clock_hw_init(struct rts493xa_clk_priv *priv)
{
	u32 reg;

	/* Disable usbphy */
	reg = rts_clk_readl(priv, USBPHY_CLK_CFG_R);
	reg &= ~(USBPHY_HOST_CLK_EN | USBPHY_DEV_CLK_EN);
	rts_clk_writel(priv, reg, USBPHY_CLK_CFG_R);

	/* Disable ephy */
	reg = rts_clk_readl(priv, ETHERNET_CLK_CFG_R);
	reg &= ~CLK_ENABLE;
	rts_clk_writel(priv, reg, ETHERNET_CLK_CFG_R);

	reg = rts_clk_readl(priv, SSOR_CLK_OE_R);
	reg |= 1;
	rts_clk_writel(priv, reg, SSOR_CLK_OE_R);
}

static int rts493xa_clk_init(struct rts493xa_clk_priv *priv)
{
	int i;

	rlx_clock_hw_init(priv);

	for (i = (u32)UART_CLK_LP_EN_R; i <= (u32)SSI_CLK_CFG_REG; i += 4)
		clk_reg_v[(i & 0x1ff) >> 2] = rts_clk_readl(priv, i);

	clk_dm(RLX_CLK_DUMMY,
	       clk_register_fixed_rate(NULL, "dummy", 100000000));
	clk_dm(RLX_CLK_SYS_OSC,
	       clk_register_fixed_rate(NULL, "clk25mhz", 25000000));
	clk_dm(RLX_CLK_USB_PLL,
	       clk_register_fixed_rate(NULL, "usb_pll", 480000000));
	clk_dm(RLX_CLK_USB_PLL_2,
	       clk_register_fixed_factor(NULL, "usb_pll_2", "usb_pll",
					 CLK_SET_RATE_PARENT, 1, 2));
	clk_dm(RLX_CLK_USB_PLL_3,
	       clk_register_fixed_factor(NULL, "usb_pll_3", "usb_pll",
					 CLK_SET_RATE_PARENT, 1, 3));
	clk_dm(RLX_CLK_USB_PLL_5,
	       clk_register_fixed_factor(NULL, "usb_pll_5", "usb_pll",
					 CLK_SET_RATE_PARENT, 1, 5));
	clk_dm(RLX_CLK_USB_PLL_7,
	       clk_register_fixed_factor(NULL, "usb_pll_7", "usb_pll",
					 CLK_SET_RATE_PARENT, 1, 7));

	clk_dm(RLX_CLK_SYS_PLL0,
	       rlx_register_gpll_clk(priv, &gpll0,
				     CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_SYS_PLL1,
	       rlx_register_gpll_clk(priv, &gpll1,
				     CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_SYS_PLL2,
	       rlx_register_gpll_clk(priv, &gpll2,
				     CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_SYS_PLL3,
	       rlx_register_gpll_clk(priv, &gpll3,
				     CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_SYS_PLL0_2,
	       clk_register_fixed_factor(NULL, "gpll0_2", "gpll0",
					 CLK_SET_RATE_PARENT, 1, 2));
	clk_dm(RLX_CLK_SYS_PLL0_3,
	       clk_register_fixed_factor(NULL, "gpll0_3", "gpll0",
					 CLK_SET_RATE_PARENT, 1, 3));
	clk_dm(RLX_CLK_SYS_PLL0_5,
	       clk_register_fixed_factor(NULL, "gpll0_5", "gpll0",
					 CLK_SET_RATE_PARENT, 1, 5));
	clk_dm(RLX_CLK_SYS_PLL0_7,
	       clk_register_fixed_factor(NULL, "gpll0_7", "gpll0",
					 CLK_SET_RATE_PARENT, 1, 7));

	clk_dm(RLX_CLK_SYS_PLL1_2,
	       clk_register_fixed_factor(NULL, "gpll1_2", "gpll1",
					 CLK_SET_RATE_PARENT, 1, 2));
	clk_dm(RLX_CLK_SYS_PLL1_3,
	       clk_register_fixed_factor(NULL, "gpll1_3", "gpll1",
					 CLK_SET_RATE_PARENT, 1, 3));
	clk_dm(RLX_CLK_SYS_PLL1_5,
	       clk_register_fixed_factor(NULL, "gpll1_5", "gpll1",
					 CLK_SET_RATE_PARENT, 1, 5));
	clk_dm(RLX_CLK_SYS_PLL1_7,
	       clk_register_fixed_factor(NULL, "gpll1_7", "gpll1",
					 CLK_SET_RATE_PARENT, 1, 7));

	clk_dm(RLX_CLK_SYS_PLL2_2,
	       clk_register_fixed_factor(NULL, "gpll2_2", "gpll2",
					 CLK_SET_RATE_PARENT, 1, 2));
	clk_dm(RLX_CLK_SYS_PLL2_3,
	       clk_register_fixed_factor(NULL, "gpll2_3", "gpll2",
					 CLK_SET_RATE_PARENT, 1, 3));
	clk_dm(RLX_CLK_SYS_PLL2_5,
	       clk_register_fixed_factor(NULL, "gpll2_5", "gpll2",
					 CLK_SET_RATE_PARENT, 1, 5));
	clk_dm(RLX_CLK_SYS_PLL2_7,
	       clk_register_fixed_factor(NULL, "gpll2_7", "gpll2",
					 CLK_SET_RATE_PARENT, 1, 7));

	clk_dm(RLX_CLK_SYS_PLL3_2,
	       clk_register_fixed_factor(NULL, "gpll3_2", "gpll3",
					 CLK_SET_RATE_PARENT, 1, 2));
	clk_dm(RLX_CLK_SYS_PLL3_3,
	       clk_register_fixed_factor(NULL, "gpll3_3", "gpll3",
					 CLK_SET_RATE_PARENT, 1, 3));
	clk_dm(RLX_CLK_SYS_PLL3_5,
	       clk_register_fixed_factor(NULL, "gpll3_5", "gpll3",
					 CLK_SET_RATE_PARENT, 1, 5));
	clk_dm(RLX_CLK_SYS_PLL3_7,
	       clk_register_fixed_factor(NULL, "gpll3_7", "gpll3",
					 CLK_SET_RATE_PARENT, 1, 7));

	clk_dm(RLX_CLK_DMA_CK,
	       rlx_register_decdivider_clk(priv, &dma_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_USBPHY_HOST_CK,
	       rlx_register_common_clk(priv, &usbphy_host_ck,
				       CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_USBPHY_DEV_CK,
	       rlx_register_common_clk(priv, &usbphy_dev_ck,
				       CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_ETHERNET_CK,
	       rlx_register_common_clk(priv, &ethernet_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_P1BUS_CK,
	       rlx_register_common_clk(priv, &p1bus_ck, CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_P1BUS_CK_DEC,
	       rlx_register_decdivider_clk(priv, &p1bus_ck_dec,
					   CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_CPU_CK,
	       rlx_register_common_clk(priv, &cpu_ck, CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_CPU_CK_DEC,
	       rlx_register_decdivider_clk(priv, &cpu_ck_dec,
					   CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_JPEG_CK,
	       rlx_register_common_clk(priv, &jpeg_ck, CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_JPEG_CK_DEC,
	       rlx_register_decdivider_clk(priv, &jpeg_ck_dec,
					   CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_BUS_CK,
	       rlx_register_common_clk(priv, &bus_ck, CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_BUS_CK_DEC,
	       rlx_register_decdivider_clk(priv, &bus_ck_dec,
					   CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_DRAM_CK,
	       rlx_register_common_clk(priv, &dram_ck, CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_DRAM_CK_DEC,
	       rlx_register_decdivider_clk(priv, &dram_ck_dec,
					   CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_ISP_CK,
	       rlx_register_common_clk(priv, &isp_ck, CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_ISP_CK_DEC,
	       rlx_register_decdivider_clk(priv, &isp_ck_dec,
					   CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_MIPI_CK,
	       rlx_register_common_clk(priv, &mipi_ck, CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_MIPI_CK_DEC,
	       rlx_register_decdivider_clk(priv, &mipi_ck_dec,
					   CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_I2C_CK,
	       rlx_register_common_clk(priv, &i2c_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_XB2_CK,
	       rlx_register_common_clk(priv, &xb2_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_UART_CK,
	       rlx_register_common_clk(priv, &uart_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_I2S_CK,
	       rlx_register_common_clk(priv, &i2s_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_SPDIF_CK,
	       rlx_register_common_clk(priv, &spdif_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_CODEC_CK,
	       rlx_register_common_clk(priv, &codec_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_CIPHER_CK,
	       rlx_register_common_clk(priv, &cipher_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_H265_ACLK_CK,
	       rlx_register_common_clk(priv, &h265_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_H265_BCLK_CK,
	       rlx_register_common_clk(priv, &h265_bclk_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_H265_BCLK_CK_DEC,
	       rlx_register_decdivider_clk(priv, &h265_bclk_dec,
					   CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_H265_CCLK_CK,
	       rlx_register_common_clk(priv, &h265_cclk_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_H265_CCLK_CK_DEC,
	       rlx_register_decdivider_clk(priv, &h265_cclk_dec,
					   CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_H265_CK,
	       rlx_register_common_clk(priv, &h265_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_SSOR_HCLK,
	       rlx_register_common_clk(priv, &ssor_hclk_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_RSA,
	       rlx_register_common_clk(priv, &ecc_ck, CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_SHA,
	       rlx_register_common_clk(priv, &sha_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_NN_BUS,
	       rlx_register_common_clk(priv, &nnbus_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_NNCORE_CK,
	       rlx_register_common_clk(priv, &nncore_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_NNCORE_CK_DEC,
	       rlx_register_decdivider_clk(priv, &nncore_ck_dec,
					   CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_GE,
	       rlx_register_common_clk(priv, &ge_ck, CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_TRNG,
	       rlx_register_common_clk(priv, &trng_ck, CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_OTP,
	       rlx_register_common_clk(priv, &efuse_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_MACBYPASS_CK,
	       rlx_register_common_clk(priv, &macbypass_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_MIPITX,
	       rlx_register_common_clk(priv, &mipitx_ck, CLK_IGNORE_UNUSED));
	clk_dm(RLX_CLK_JPEGDRAM,
	       rlx_register_common_clk(priv, &jpegdram_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_MIPITX_LOW,
	       rlx_register_common_clk(priv, &mipitx_lowck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_ISP_ZOOM_CK,
	       rlx_register_common_clk(priv, &isp_zoom_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_ISP_ZOOM_CK_DEC,
	       rlx_register_decdivider_clk(priv, &isp_zoom_ck_dec,
					   CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_BWT,
	       rlx_register_common_clk(priv, &bwt_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_SD0_CRC_CK,
	       rlx_register_common_clk(priv, &sd0_crc_clk, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_SD0_SAMPLE_CK,
	       rlx_register_common_clk(priv, &sd0_sample_clk,
				       CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_SD0_PUSH_CK,
	       rlx_register_common_clk(priv, &sd0_push_clk, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_SD1_CRC_CK,
	       rlx_register_common_clk(priv, &sd1_crc_clk, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_SD1_SAMPLE_CK,
	       rlx_register_common_clk(priv, &sd1_sample_clk,
				       CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_SD1_PUSH_CK,
	       rlx_register_common_clk(priv, &sd1_push_clk, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_UART1_CK,
	       rlx_register_common_clk(priv, &uart1_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_UART2_CK,
	       rlx_register_common_clk(priv, &uart2_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_I2C1_CK,
	       rlx_register_common_clk(priv, &i2c1_ck, CLK_IGNORE_UNUSED));

	clk_dm(RLX_CLK_SSI_CK,
	       rlx_register_common_clk(priv, &ssi_ck, CLK_IGNORE_UNUSED));

	return 0;
}

static int rts493xa_clk_probe(struct udevice *dev)
{
	struct rts493xa_clk_priv *priv = dev_get_priv(dev);

	priv->clk_mapped_addr = devfdt_get_addr_index_ptr(dev, 0);
	if (!priv->clk_mapped_addr)
		return -EINVAL;
	priv->pll_mapped_addr = devfdt_get_addr_index_ptr(dev, 1);
	if (!priv->pll_mapped_addr)
		return -EINVAL;

	priv->num_clks = RLX_CLK_NUM_SIZE;
	rts493xa_clk_init(priv);

	return 0;
}

static const struct udevice_id rts493xa_clk_ids[] = {
	{ .compatible = "realtek,rts493xa-clocks" },
	{}
};

U_BOOT_DRIVER(rts493xa_clk) = {
	.name = "rts493xa_clk",
	.id = UCLASS_CLK,
	.of_match = rts493xa_clk_ids,
	.ops = &ccf_clk_ops,
	.priv_auto = sizeof(struct rts493xa_clk_priv),
	.probe = rts493xa_clk_probe,
	.flags = DM_FLAG_PRE_RELOC,
};
