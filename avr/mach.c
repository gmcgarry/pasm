/*-
 * Copyright (c) 2021 Gregory McGarry <g.mcgarry@ieee.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "as.h"
#include "error.h"

#include "mach.h"

extern sect_t sect[];
extern int hash(const char *);

#define fitx(x, d)	((((x) + (1<<(d-1))) & ~((int)(1<<(d))-1)) == 0)
#define fit7(x)		fitx(x, 7)
#define fit12(x)	fitx(x, 12)

static item_t cseg = { 0, 0, S_UND, ".text" };

void
mflag(const char* flag)
{
}

void
machstart(int pass)
{
	if (pass == PASS_1) {
		item_insert(&cseg, hash(cseg.i_name));
		unresolved++;
	}
	newsect(&cseg, 0, NULL);
}

void
machfinish(int pass)
{
}

void
setdevice(const char *name)
{
}

void
branch(int opc, expr_t exp)
{
	int distw = (exp.val - (DOTVAL + 2)) / 2;
	int sm1, sm2;

	/* k	1111 00kk kkkk k001 */

	if (pass == PASS_2 && distw > 0 && !(exp.typ & S_DOT))
		distw -= sect[DOTSCT].s_gain;
	sm1 = distw > 0 ? fit7(distw) : fit7(-distw);
	sm2 = distw > 0 ? fit12(distw - 1) : fit12(-(distw - 1));
	if (sm1 && small(sm1, 4)) {
		emit2(opc | ((distw & 0x7f) << 3));
	} else if (sm2 && small(sm2, 2)) {
		emit2((opc ^ 0x400) | (0x1 << 3));
		emit2(0xc000 | ((distw - 1) & 0x0fff)); /* RJMP */
	} else {
		emit2((opc ^ 0x400) | (0x02 << 3));
		newrelo(exp.typ, RELO4); /* XXXGJM: fixme, a different reloc type */
		emit2(0x940c | ((exp.val >> 13) & 0x1f0) | ((exp.val >> 16) & 0x01));
		emit2(exp.val & 0xffff);
	}
}

void
jump(int opc, expr_t exp)
{
	int distw = (exp.val - (DOTVAL + 2)) / 2;
	int sm;

	/* k	1100 kkkk kkkk kkkk */
	/* k	1101 kkkk kkkk kkkk */

	if (pass == PASS_2 && distw > 0 && !(exp.typ & S_DOT))
		distw -= sect[DOTSCT].s_gain;
	sm = distw > 0 ? fit12(distw) : fit12(-distw);
	if (small(sm, 2)) { /* XXXGJM: don't convert to rjmp if target is external */
		if (opc == 0xc000 || opc == 0x940c) /* RJMP/JMP */
			opc = 0xc000;
		else if (opc == 0xd000 || opc == 0x940e) /* RCALL/CALL */
			opc = 0xd000;
		emit2(opc | (distw & 0x0fff));
	} else {
		if (opc == 0xc000 || opc == 0x940c) /* RJMP/JMP */
			opc = 0x940c;
		else if (opc == 0xd000 || opc == 0x940e) /* RCALL/CALL */
			opc = 0x940e;
		newrelo(exp.typ, RELO4); /* XXXGJM: fixme, a different reloc type */
		emit2(opc | ((exp.val >> 13) & 0x1f0) | ((exp.val >> 16) & 0x01));
		emit2(exp.val & 0xffff);
	}
}
