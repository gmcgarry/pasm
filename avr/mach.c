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

#define fitx(x, d)	((((x) + (1<<(d-1))) & ~((int)(1<<(d))-1)) == 0)
#define fit7(x)		fitx(x, 7)
#define fit12(x)	fitx(x, 12)

void
machstart(int pass)
{
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
	int sm;

	/* k        1111 00kk kkkk k001 */

	if (pass == PASS_2 && distw > 0 && !(exp.typ & S_DOT))
		distw -= sect[DOTSCT].s_gain;
	sm = distw > 0 ? fit7(distw) : fit7(-distw);
	if (sm) {
		emit2(opc | ((distw & 0x7f) << 3));
	} else {
		emit2(opc | ((distw & 0x7f) << 3));
#if 0
sbrc	skip if bit in register cleared
sbrs	skip if bit in register set
		emit2("sbrs r0,3");
		dist += (dist < 0 ? 2 : -2);
		emit("rjmp dist");
#endif
	}
}

void
reljump(int opc, expr_t exp)
{
	int distw = (exp.val - (DOTVAL + 2)) / 2;
	int sm;

        /* k        1100 kkkk kkkk kkkk */
        /* k        1101 kkkk kkkk kkkk */

	if (pass == PASS_2 && distw > 0 && !(exp.typ & S_DOT))
		distw -= sect[DOTSCT].s_gain;
	sm = distw > 0 ? fit12(distw) : fit12(-distw);
	if (sm) {
		emit2(opc | (distw & 0x0fff));
	} else {
		if (opc == 0xc000) /* RJMP */
			opc = 0x940c;
		else if (opc == 0xd00) /* RCALL */
			opc = 0x940e;
		absjump(opc, exp);
	}
}

void
absjump(int opc, expr_t exp)
{
	int distw = exp.val / 2;

       	/* k        1001 010k kkkk 110k + 16k */
        /* k        1001 010k kkkk 111k + 16k */

	if (!fitx(distw, 22))
		fatal("target address too large");
	emit2(opc | ((distw >> 13) & 0x1f0) | ((distw >> 16) & 0x01));
	emit2(distw & 0xffff);
}
