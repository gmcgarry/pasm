/*
 * Copyright (c) 1987, 1990, 1993, 2005 Vrije Universiteit, Amsterdam, The Netherlands.
 * All rights reserved.
 * 
 * Redistribution and use of the Amsterdam Compiler Kit in source and
 * binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 * 
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 * 
 *    * Neither the name of Vrije Universiteit nor the names of the
 *      software authors or contributors may be used to endorse or
 *      promote products derived from this software without specific
 *      prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS, AUTHORS, AND
 * CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL VRIJE UNIVERSITEIT OR ANY AUTHORS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "as.h"
#include "mach.h"
#include "error.h"

#define lowb(z)		((int)(z) & 0xFF)
#define fitb(x)		((((x) + 0x80) & ~((int)0xFF)) == 0)

extern sect_t sect[];
extern int hash(const char *);

static item_t cseg = { 0, S_UND, 0, ".text" };

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
	}
	newsect(&cseg, 0, NULL);
}

void
machfinish(int pass)
{
}

void
branch(int opc, expr_t exp)
{
	int sm, dist;
	int saving;

	if (opc == 0x8D || opc == 0x20)
		saving = 1;
	else
		saving = 2;

	dist = exp.val - (DOTVAL + 2);

	if (PASS_RELO && dist > 0 && !(exp.typ & S_DOT))
                dist -= sect[DOTSCT].s_gain;
#if 1
	sm = dist > 0 ? fitb(dist - saving) : fitb(dist);
#else
	sm = fitb(dist);
#endif
	if ((exp.typ & S_SCTMASK) != DOTSCT)
		sm = 0;
	if ((sm = small(sm,saving)) == 0) {
		dist--;
		if (opc == 0x8D)	/* bsr */
			opc = 0x17;
		else if (opc == 0x20)	/* bra */
			opc = 0x16;
		else {
			emit1(0x10);
			dist--;
		}
	}
	emit1(opc);
	if (sm == 0) {
#ifdef RELOCATION
		if (rflag != 0 && PASS_RELO)
			newrelo(exp.typ, RELPC|RELO2|RELBR);
#endif
		emit2(dist);
	} else {
		emit1(lowb(dist));
	}
}

int
regno(int r)
{
	switch (r) {
	case X:	return 0;
	case Y:	return 0x20;
	case U:	return 0x40;
	case S:	return 0x60;
	}
	return -1;
}

void
emit1or2(int n)
{
	if (n & ~0xFF)
		emit1(n >> 8);
	emit1(n);
}

void
offset(int reg, expr_t exp, int ind)
{
	if (reg == PC) {
		int	sm, dist;

		dist = exp.val - (DOTVAL + 2);
		if (PASS_RELO && dist > 0 && !(exp.typ & S_DOT))
                	dist -= sect[DOTSCT].s_gain;
		sm = fitb(dist);
		if ((exp.typ & S_SCTMASK) != DOTSCT)
			sm = 0;
		if (small(sm,1)) {
			emit1(0x8C + ind);
			emit1(dist);
		} else {
			emit1(0x8D + ind);
			emit1((dist-1)>>8);
			emit1(dist - 1);
		}
	} else if ((reg = regno(reg)) < 0)
		serror("register error");
	else if ((exp.typ & S_SCTMASK) == S_ABS && exp.val == 0)
		emit1(0x84 + reg + ind);	/* XOP 0, REG == XOP , REG */
	else if (ind == 0 && (exp.typ & S_SCTMASK) == S_ABS && -16 <= exp.val && exp.val <= 15)
		emit1(reg + ind + (exp.val & 037));
	else if ((exp.typ&S_SCTMASK)==S_ABS && -128<=exp.val && exp.val<=127) {
		emit1(0x88 + reg + ind);
		emit1(exp.val);
	} else {
		emit1(0x89 + reg + ind);
#ifdef RELOCATION
		if (rflag != 0 && PASS_RELO)
			newrelo(exp.typ, RELO2|RELBR);
#endif
		emit2(exp.val);
	}
}
