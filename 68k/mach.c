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

/*
 * Motorola 68000/68010 auxiliary functions
 */

#include <strings.h>	/* strncasecmp */

#include "as.h"
#include "error.h"

#include "y.tab.h"

int model;		/* 680x0 */

#if 0
int co_id;
int mrg_1,mrg_2;
expr_t exp_1, exp_2;
#ifndef ASLD
VALUE_T	rel_1,rel_2;
#endif
int curr_instr;
#endif


unsigned short eamode[] = {
/* 00A */	DTA	|ALT,
/* 01A */		    ALT,
/* 02A */	DTA|MEM|CTR|ALT,
/* 03A */	DTA|MEM    |ALT,
/* 04A */	DTA|MEM    |ALT,
/* 05A */	DTA|MEM|CTR|ALT|FITW|PUTW | (RELO2      )<<8,
/* 06A */	DTA|MEM|CTR|ALT     |PUTW | (RELO1      )<<8,
/* 07x */	0,
/* 070 */	DTA|MEM|CTR|ALT|FITW|PUTW | (RELO2      )<<8,
/* 071 */	DTA|MEM|CTR|ALT     |PUTL | (RELO4      )<<8,
#if 0 	/* until relocations are fixed */
/* 072 */	DTA|MEM|CTR    |FITW|PUTW | (RELO2|RELPC)<<8,
/* 073 */	DTA|MEM|CTR	 |PUTW | (RELO1|RELPC)<<8,
#else
/* 072 */	DTA|MEM|CTR    |FITW|PUTW | (RELO2)<<8,	
/* 073 */	DTA|MEM|CTR	 |PUTW | (RELO1)<<8,
#endif
/* 074x */	0,
/* 074B */	DTA|MEM	|FITB|PUTW | (RELO1      )<<8,
/* 074W */	DTA|MEM	|FITW|PUTW | (RELO2      )<<8,
/* 074L */	DTA|MEM	     |PUTL | (RELO4      )<<8,
};

extern sect_t sect[];
extern int hash(const char *);

static item_t cseg = { 0, S_UND, 0, ".text" };

void
mflag(const char* flag)
{
	static const struct { const char *name; int id; } Models[] = {
		{ "m68000", MODEL_68000 },
		{ "m68008", MODEL_68000 },
		{ "m68010", MODEL_68010 },
		{ "m68020", MODEL_68020 },
		{ "m68030", MODEL_68030 },
		{ "m68040", MODEL_68040 },
	};
#define NMODELS	(int)(sizeof(Models)/sizeof(Models[0]))

	if (strncasecmp(flag, "cpu=", 4) == 0) {
		int i;
		for (i = 0; i < NMODELS; i++)
			if (strcasecmp(Models[i].name, &flag[4]) == 0)
				model = Models[i].id;
		if (i == NMODELS)
			fatal("unsupported model \"%s\"\n", &flag[4]);
	}
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

static int
extension_offset(void)
{
	switch(curr_instr) {
	case MOVEM:
	case FMOVE:
	case FMOVEM:
	case FDYADIC:
	case FMONADIC:
	case FSINCOS:
	case FSCC:
	case FTST:
		return 4;
	}
	return 2;
}

void
ea_1(int sz, int bits)
{
	int flag;

//	printf("ea_1(%d,0x%x)\n", sz, bits);
//	printf("	mrg_1=%o\n", mrg_1);

	if (mrg_1 > 074)
		serror("no specials");
	if ((flag = eamode[mrg_1>>3]) == 0) {
//		printf("flag0 = 0x%x\n", flag);
		if ((flag = eamode[010 + (mrg_1&07)]) == 0) {
//			printf("flag1 = 0x%x\n", flag);
			flag = eamode[015 + (sz>>6)];
		}
	}
//	printf("flag2 = 0x%x\n", flag);
	if ((mrg_1 & 070) == 010)
		checksize(sz, 2|4);
//	printf("bits=0x%x, flag=0x%x\n", bits, flag);
	bits &= ~flag;
#ifdef RELOCATION
	// by default, the assembler assumes relocatable code with
	// the following code.  Absolute addressing will not be used.
	// So disable this.
	if (bits)
		serror("bad addressing category");
#endif
	if (flag & FITW)
		fit(fitw(exp_1.val) || (mrg_1 == 074 && fit16(exp_1.val)));
	if (flag & FITB) {
		fit(fitb(exp_1.val) || (mrg_1 == 074 && fit8(exp_1.val)));
		if (mrg_1 == 074)
			exp_1.val &= 0xFF;
	}
#ifdef RELOCATION
	RELOMOVE(relonami, rel_1);
	if (flag & ~0xFF)
		newrelo(exp_1.typ, (flag>>8) | RELBR | RELWR);
#endif
	if (flag & PUTL)
		emit4(exp_1.val);
	if (flag & PUTW)
		emit2(loww(exp_1.val));
}

void
ea_2(int sz, int bits)
{ 
	mrg_1 = mrg_2;
	exp_1 = exp_2;
	RELOMOVE(rel_1, rel_2);
	ea_1(sz, bits);
}

void
indexmode(int hibyte)
{
	fit(fitb(exp_2.val));
	exp_2.val = hibyte | lowb(exp_2.val);
}

void
checksize(int sz, int bits)
{
	if ((bits & (1 << (sz>>6))) == 0)
		serror("bad size");
}

void
setmodel(int mdl)
{
	model = mdl;
}

void
testmodel(int mdl)
{
	if (model < mdl && pass == PASS_3)
		warning("680%d0 instruction", mdl);
}

void
badoperand(void)
{
	serror("bad operands");
}

void
shift_op(int opc, int sz)
{
	if (mrg_1 < 010 && mrg_2 < 010) {
		emit2((opc&0170470) | sz | mrg_1<<9 | mrg_2);
		return;
	}
	if (exp_1.typ != S_ABS || mrg_1 != 074) {
		badoperand();
		return;
	}
	if (mrg_2 < 010) {
		fit(fit3(exp_1.val));
		emit2((opc&0170430) | sz | low3(exp_1.val)<<9 | mrg_2);
		return;
	}
	checksize(sz, 2);
	fit(exp_1.val == 1);
	emit2((opc&0177700) | mrg_2);
	ea_2(SIZE_W, MEM|ALT);
}

void
bitop(int opc)
{
	int bits;

	bits = DTA|ALT;
	if (opc == 0 && (mrg_1 < 010 || mrg_2 != 074))
		bits = DTA;
	if (mrg_1 < 010) {
		emit2(opc | 0400 | mrg_1<<9 | mrg_2);
		ea_2(0, bits);
		return;
	}
	if (mrg_1 == 074) {
		emit2(opc | 04000 | mrg_2);
		ea_1(SIZE_W, 0);
		ea_2(0, bits);
		return;
	}
	badoperand();
}

void
add(int opc, int sz)
{
	if ((mrg_2 & 070) == 010)
		checksize(sz, 2|4);
	if (
		mrg_1 == 074
		&&
		small(
			exp_1.typ==S_ABS && fit3(exp_1.val),
			sz==SIZE_L ? 4 : 2
		)
	) {
		emit2((opc&0400) | 050000 | low3(exp_1.val)<<9 | sz | mrg_2);
		ea_2(sz, ALT);
		return;
	}
	if (mrg_1 == 074 && (mrg_2 & 070) != 010) {
		emit2((opc&03000) | sz | mrg_2);
		ea_1(sz, 0);
		ea_2(sz, DTA|ALT);
		return;
	}
	if ((mrg_2 & 070) == 010) {
		emit2((opc&0170300) | (mrg_2&7)<<9 | sz<<1 | mrg_1);
		ea_1(sz, 0);
		return;
	}
	if (to_dreg(opc, sz, 0))
		return;
	if (from_dreg(opc, sz, ALT|MEM))
		return;
	badoperand();
}

void
and(int opc, int sz)
{
	if (mrg_1 == 074 && mrg_2 >= 076) {	/* ccr or sr */
		if (sz != SIZE_NON)
			checksize(sz, mrg_2==076 ? 1 : 2);
		else
			sz = (mrg_2==076 ? SIZE_B : SIZE_W);
		emit2((opc&07400) | sz | 074);
		ea_1(sz, 0);
		return;
	}
	if (sz == SIZE_NON)
		sz = SIZE_DEF;
	if (mrg_1 == 074) {
		emit2((opc&07400) | sz | mrg_2);
		ea_1(sz, 0);
		ea_2(sz, DTA|ALT);
		return;
	}
	if ((opc & 010000) == 0 && to_dreg(opc, sz, DTA))
		return;
	if (from_dreg(opc, sz, (opc & 010000) ? DTA|ALT : ALT|MEM))
		return;
	badoperand();
}

int
to_dreg(int opc, int sz, int bits)
{
	if ((mrg_2 & 070) != 000)
		return(0);
	emit2((opc & 0170000) | sz | (mrg_2&7)<<9 | mrg_1);
	ea_1(sz, bits);
	return(1);
}

int
from_dreg(int opc, int sz, int bits)
{
	if ((mrg_1 & 070) != 000)
		return(0);
	emit2((opc & 0170000) | sz | (mrg_1&7)<<9 | 0400 | mrg_2);
	ea_2(sz, bits);
	return(1);
}

void
cmp(int sz)
{
	int opc;

	if ((mrg_1&070) == 030 && (mrg_2&070) == 030) {
		emit2(0130410 | sz | (mrg_1&7) | (mrg_2&7)<<9);
		return;
	}
	if (mrg_1 == 074 && (mrg_2 & 070) != 010) {
		if (mrg_2 == 072) {
			/* In this case, the ea707172 routine changed the
			   addressing mode to PC-relative. However, this is
			   not allowed for this instruction. Change it back
			   to absolute, but also correct for the optimization
			   that the ea707172 routine thought it made.
			*/
			if (pass == PASS_1) {
				/* In this case, the user wrote it PC-relative.
				   Error.
				*/
				badoperand();
			}
			mrg_2 = 071;
			exp_2.val += DOTVAL+2;
			if (pass == PASS_2) {
				sect[DOTSCT].s_gain -= 2;
			}
		}
		emit2(06000 | sz | mrg_2);
		ea_1(sz, 0);
		ea_2(sz, DTA|ALT);
		return;
	}
	if (mrg_2 < 020) {
		if (mrg_2 >= 010) {
			checksize(sz, 2|4);
			opc = 0130300 | sz<<1;
			mrg_2 &= 7;
		} else
			opc = 0130000 | sz;
		emit2(opc | mrg_2<<9 | mrg_1);
		ea_1(sz, 0);
		return;
	}
	badoperand();
}

void
move(int sz)
{
	int opc;

//	printf("move %d %o %x\n", sz, sz, sz);
//	printf("	mrg_1 = %o, mrg_2 = %o\n", mrg_1, mrg_2);

	if (mrg_1 > 074 || mrg_2 > 074) {
		move_special(sz);
		return;
	}
	if (sz == SIZE_NON)
		sz = SIZE_DEF;
	if (mrg_2 < 010 && mrg_1 == 074 && sz == SIZE_L && small(exp_1.typ == S_ABS && fitb(exp_1.val), 4)) {
		emit2(070000 | mrg_2<<9 | lowb(exp_1.val));
		return;
	}
	switch (sz) {
	case SIZE_B:	opc = 010000; break;
	case SIZE_W:	opc = 030000; break;
	case SIZE_L:	opc = 020000; break;
	}
	emit2(opc | mrg_1 | (mrg_2&7)<<9 | (mrg_2&070)<<3);
	ea_1(sz, 0);
	ea_2(sz, ALT);
}

void
move_special(int sz)
{
	if (mrg_2 >= 076) {
		if (sz != SIZE_NON)
			checksize(sz, 2);
		emit2(042300 | (mrg_2==076?0:01000) | mrg_1);
		ea_1(SIZE_W, DTA);
		return;
	}
	if (mrg_1 >= 076) {
		if (mrg_1 == 076)
			testmodel(MODEL_68010);
		if (sz != SIZE_NON)
			checksize(sz, 2);
		emit2(040300 | (mrg_1==076?01000:0) | mrg_2);
		ea_2(SIZE_W, DTA|ALT);
		return;
	}
	if (sz != SIZE_NON)
		checksize(sz, 4);
	if (mrg_1==075 && (mrg_2&070)==010) {
		emit2(047150 | (mrg_2&7));
		return;
	}
	if (mrg_2==075 && (mrg_1&070)==010) {
		emit2(047140 | (mrg_1&7));
		return;
	}
	badoperand();
}

int
reverse(int regs, int max)
{
	int r, i;

	r = regs; regs = 0;
	for (i = max; i > 0; i--) {
		regs <<= 1;
		if (r & 1) regs++;
		r >>= 1;
	}
	return regs;
}

void
movem(int dr, int sz, int regs)
{
	int i;

	if ((mrg_2>>3) == 04) {
		regs = reverse(regs, 16);
	}
	checksize(sz, 2|4);
	if ((mrg_2>>3)-3 == dr)
		badoperand();
	emit2(044200 | dr<<10 | (sz & 0200) >> 1 | mrg_2);
	emit2(regs);
	i = CTR;
	if (dr == 0 && (mrg_2&070) == 040)
		i = MEM;
	if (dr != 0 && (mrg_2&070) == 030)
		i = MEM;
	if (dr == 0)
		i |= ALT;
	ea_2(sz, i);
}

void
movep(int sz)
{
	checksize(sz, 2|4);
	if (mrg_1<010 && (mrg_2&070)==050) {
		emit2(0610 | (sz & 0200)>>1 | mrg_1<<9 | (mrg_2&7));
		ea_2(sz, 0);
		return;
	}
	if (mrg_2<010 && (mrg_1&070)==050) {
		emit2(0410 | (sz & 0200)>>1 | mrg_2<<9 | (mrg_1&7));
		ea_1(sz, 0);
		return;
	}
	badoperand();
}

void
branch(int opc, expr_t exp)
{
	int sm;

	exp.val -= (DOTVAL + 2);
	if ((pass == PASS_2) && (exp.val > 0) && ((exp.typ & S_SCTMASK) != DOTSCT))
		exp.val -= sect[DOTSCT].s_gain;
	sm = fitb(exp.val);
	if ((exp.typ & S_SCTMASK) != DOTSCT)
		sm = 0;
	if (small(sm,2)) {
		fit(fitb(exp.val));
		if (exp.val == 0)
			emit2(047161);	/* NOP */
		else
			emit2(opc | lowb(exp.val));
	} else {
		fit(fitw(exp.val));
		emit2(opc);
#ifdef RELOCATION
		newrelo(exp.typ, RELPC|RELO2|RELBR|RELWR);
#endif
		emit2(loww(exp.val));
	}
}

void
ea5x73(int rg, int sz)
{
	if ((exp_2.typ & S_SCTMASK) == DOTSCT) {
		/* pc relative with index */
		if (sz == SIZE_NON)
			sz = SIZE_DEF;
		exp_2.val -= (DOTVAL + extension_offset());
		mrg_2 = 073;
		checksize(sz, 2|4);
		indexmode(rg<<12 | (sz&0200)<<4);
		return;
	}
	/* displacement */
	mrg_2 = 050 | rg;
	if (pass == PASS_1)	/* tricky, maybe 073 in next passes */
		return;
	if ((rg & 010) == 0 || sz != SIZE_NON)
		badoperand();
}

void
ea707172(int sz)
{
	int sm;

//	printf("ea707172, sz=%d\n", sz);

	mrg_2 = 071;
	switch (sz) {
	case SIZE_B:
		badoperand();
	case SIZE_W:
		mrg_2 = 070;
	case SIZE_L:
		return;
	case SIZE_NON:
		break;
	}
	if (pass == PASS_1) {
		/*
		 * reserve a bit in the bittable
		 * in the following passes one call to small()
		 * will be done, but we don't know which one
		 * since exp_2.typ cannot be trusted
		 */
		small(0, 2);
		return;
	}
	if ((exp_2.typ & S_SCTMASK) == DOTSCT) {
		int off = extension_offset();
//		printf("same section\n");
		sm = fitw(exp_2.val-(DOTVAL+off));
		sm = small(sm, 2);
		if (sm) {	/* pc relative */
//			printf("converting to pc relative, mrg_2 = 072\n");
			exp_2.val -= (DOTVAL+off);
			mrg_2 = 072;
		}
	} else {
		sm = fitw(exp_2.val);
#ifdef ASLD
		if (exp_2.typ & S_VAR)
			sm = 0;
#else
		if (exp_2.typ != S_ABS)
			sm = 0;
#endif /* ASLD */
		sm = small(sm, 2);
		if (sm)
			mrg_2 = 070;
	}
}

void
ea6x(int rg, int ir, int sz)
{
	mrg_2 = 060 | rg;
	checksize(sz, 2|4);
	indexmode(ir<<12 | (sz&0200)<<4);
}

void
ea72(void)
{
	mrg_2 = 072;
	exp_2.val -= (DOTVAL + extension_offset());
}

void
ea73(int ri, int sz)
{
	mrg_2 = 073;
	exp_2.val -= (DOTVAL + extension_offset());
	checksize(sz, 2|4);
	indexmode(ri<<12 | (sz&0200)<<4);
}

void
fbranch(int opc, expr_t exp)
{
	int sm;

	exp.val -= (DOTVAL + 2);
	if ((pass == PASS_2) && (exp.val > 0) && ((exp.typ & S_SCTMASK) == DOTSCT))
		exp.val -= sect[DOTSCT].s_gain;
	sm = fitw(exp.val);
	if ((exp.typ & S_SCTMASK) != DOTSCT)
		sm = 0;
	if (small(sm,2)) {
		emit2(0170200|co_id|opc);
		emit2(loww(exp.val));
		return;
	}
	emit2(0170300|co_id|opc); /* 4 byte offset */
#ifdef RELOCATION
	newrelo(exp.typ, RELPC|RELO4|RELBR|RELWR);
#endif
	emit4(exp.val);
}

void
ch_sz_dreg(int size, int mode)
{
	if (mode == 0 &&
	    (size == FSIZE_X || size == FSIZE_P || size == FSIZE_D))
		serror("illegal size for data register");
}

void
check_fsize(int sz, int size)
{
	if (sz != size) serror("bad size");
}
