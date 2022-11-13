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
#include "error.h"

extern sect_t sect[];
extern int hash(const char *);

static item_t cseg = { 0, S_UND, 0, ".text" };

void
mflag(const char* flag)
{
	fatal("unrecognised option \"-m%s\"", flag);
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
op1(int mode)
{
	int relpc = 0;
	if (im1flag)	{
		if (mode == 067 || mode == 077) {
			exp_1.val = adjust(exp_1);
			relpc = RELPC;
		}
#ifdef RELOCATION
		RELOMOVE(relonami, rel_1);
		if (rflag != 0 && PASS_RELO)
			newrelo(exp_1.typ, RELO2|relpc);
#endif
		emit2(exp_1.val);
		im1flag = 0;
	}
}

void
op2(int mode)
{
	int relpc = 0;
	if (im2flag)	{
		if (mode == 067 || mode == 077) {
			relpc = RELPC;
			exp_2.val = adjust(exp_2);
		}
#ifdef RELOCATION
		RELOMOVE(relonami, rel_2);
		if (rflag != 0 && PASS_RELO)
			newrelo(exp_2.typ, RELO2|relpc);
#endif
		emit2(exp_2.val);
		im2flag = 0;
	}
}

void
branch(int opc,expr_t exp)
{
	int eval;
	int sm;

	eval = adjust(exp) >> 1;
	sm = fitb(eval);
	if (((exp.typ & S_SCTMASK) != DOTSCT) && pass >= PASS_2)
		 sm = 0;
	if (!sm && pass >= PASS_2) {
		serror("label too far");
	}
	emit2(opc | lowb(eval));
}

void
ejump(int opc, expr_t exp)
{
	int sm,eval;
	int gain;

#ifdef THREE_PASS
	eval = adjust(exp) >> 1;
	sm = fitb(eval);
	if ((exp.typ & S_SCTMASK) != DOTSCT) {
		sm = 0;
	}
	gain = (opc == OPBRA ? 2 : 4);
	if (small(sm,gain))	{
		emit2( opc | lowb(eval));
	}
	else	{
#endif
		if (opc != OPBRA)	{
			emit2((opc^0400) | 02);
		}

		exp_1 = exp;
		im1flag = 1;
		emit2(0100|067);
		op1(067);
#ifdef THREE_PASS
	}
#endif
}

void
sob(int reg, expr_t exp)
{
	if ((exp.typ & S_SCTMASK) != DOTSCT) {
		serror("error in sob-label");
	}
	exp.val = ( - adjust(exp) ) >> 1;
	fit(fit6(exp.val));
	emit2( OPSOB | (reg << 6) | exp.val);
}

int
jump(int opc,int opr)
{
	int val;

#ifdef THREE_PASS
	if (opr==067) {
		int sm = 0;

		val = adjust(exp_1) >> 1;
		if (fitb(val) && (exp_1.typ & S_SCTMASK) == DOTSCT) {
			sm = 1;
		}
		if (small(sm,2)) {
			emit2(OPBRA | lowb(val));
			im1flag = 0;
			return(0);
		}
	}
#endif
	emit2(opc | opr);
	op1(opr);
	return(0);
}

VALUE_T
adjust(expr_t exp)
{
	VALUE_T val;

	val = exp.val - DOTVAL - 2;
#ifdef THREE_PASS
	if (pass == PASS_2 && val > 0) val -= sect[DOTSCT].s_gain;
#endif
	return(val);
}
