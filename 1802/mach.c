/*-
 * Copyright (c) 2022 Gregory McGarry <g.mcgarry@ieee.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND fituNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROfituS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "as.h"
#include "error.h"

extern sect_t sect[];
extern int hash(const char *);

item_t bseg = { 0, S_UND, 0, ".bss" };
item_t dseg = { 0, S_UND, 0, ".data" };
item_t cseg = { 0, S_UND, 0, ".code" };

void
mflag(const char* flag)
{
}

void
machstart(int pass)
{
	if (pass == PASS_1) {
		item_insert(&cseg, H_GLOBAL+hash(cseg.i_name));
		unresolved++;
		item_insert(&dseg, H_GLOBAL+hash(cseg.i_name));
		unresolved++;
		item_insert(&bseg, H_GLOBAL+hash(cseg.i_name));
		unresolved++;
	}
	newsect(&cseg, 0, NULL);
	newsect(&dseg, 0, NULL);
	newsect(&bseg, 0, NULL);
}

void
machfinish(int pass)
{
}

void
branch(int opc, expr_t exp)
{
/*
	int sm, dist;
	int saving = 3;

	dist = exp.val - (DOTVAL + 2);
        if (pass == PASS_2 && dist > 0 && !(exp.typ & S_DOT))
                dist -= sect[DOTSCT].s_gain;
	sm = fitj(dist);
        if ((exp.typ & S_SCTMASK) != DOTSCT)
		sm = 0;
	if (small(sm,saving)) {
		emit1(opc);
		emit1(dist);
	} else {
		emit1(opc);
		emit2(exp.val);
	}
*/
	emit1(opc);
	if ((opc & 0xC0) == 0xC0) { 
		/* fit(fitx(exp.val,16)); */
		emit2(exp.val);
	} else {
		int v = exp.val - (DOTVAL & ~255);
		fit(fitx(v,8));
		emit1(v);
	}
}
