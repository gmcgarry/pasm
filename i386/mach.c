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

#include <assert.h>
#include <strings.h> /* strcasecmp() */

#include "as.h"
#include "error.h"
#include "out.h"

#include "y.tab.h"

extern sect_t sect[]; /* XXXGJM remove */

int use32  = 1;
int address_long = 1;
int operand_long = 1;

char regindex_ind[8][8] = {
	{ 000,  010,    020,    030,    -1,     050,    060,    070 },
	{ 001,  011,    021,    031,    -1,     051,    061,    071 },
	{ 002,  012,    022,    032,    -1,     052,    062,    072 },
	{ 003,  013,    023,    033,    -1,     053,    063,    073 },
	{ 004,  014,    024,    034,    -1,     054,    064,    074 },
	{ 005,  015,    025,    035,    -1,     055,    065,    075 },
	{ 006,  016,    026,    036,    -1,     056,    066,    076 },
	{ 007,  017,    027,    037,    -1,     057,    067,    077 },
};

/* For 16-bit addressing: copied from i86 assembler */
char sr_m[8] = {
	-1,     -1,     -1,     7,      -1,     6,      4,      5
};

char dr_m[8][8] = {
	{ -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1 },
	{ -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1 },
	{ -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1 },
	{ -1,     -1,     -1,     -1,     -1,     -1,     0,      1 },
	{ -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1 },
	{ -1,     -1,     -1,     -1,     -1,     -1,     2,      3 },
	{ -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1 },
	{ -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1 }
};

void
mflag(const char* str)
{
	if (strcasecmp(str, "16") == 0) {
		use32 = address_long = operand_long = 0;
	} else if (strcasecmp(str, "32") == 0) {
		use32 = address_long = operand_long = 1;
	} else if (strcasecmp(str, "64") == 0) {
		use32 = address_long = operand_long = 2;
	}
}

void
machstart(int pass)
{
}

void
machfinish(int pass)
{
}

void
ea_1_16(int param)
{
	reg_1 &= 0xFF;
	if ((reg_1 & 070) || (param & ~070)) {
		serror("bad operand");
	}
	emit1(reg_1 | param);
	switch(reg_1 >> 6) {
	case 0:
		if (reg_1 == 6 || (reg_1 & 040)) {
			RELOMOVE(relonami, rel_1);
			newrelo(exp_1.typ, RELO2);
			emit2(exp_1.val);
		}
		break;
	case 1:
		emit1(exp_1.val);
		break;
	case 2:
		RELOMOVE(relonami, rel_1);
		newrelo(exp_1.typ, RELO2);
		emit2(exp_1.val);
		break;
	}
}

void
ea_1(int param)
{
	DPRINTF(("ea_1: param=%o (reg/opcode), reg_1=0x%x, rm_1=0x%x, mod_1=0x%x, sib_1=0x%x, exp_1.val=0x%llx\n", param, reg_1, rm_1, mod_1, sib_1, exp_1.val));

	/* ea_1: param=0x20 (opcode), reg_1=0x5, rm_1=0x0, mod_1=0x2, sib_1=0x0, exp_1.val=0xfffffffc */

	if (!address_long) {
		ea_1_16(param);
		return;
	}

	if (is_expr(reg_1)) {
		serror("bad operand");
		return;
	}

	/* register addressing first */
	if (is_reg(reg_1)) {
		emit1(0300 | param | (reg_1&07));
		return;
	}

	/* sib or not */
	if (rm_1 == 04) {
		/* sib field use here */
		emit1(mod_1 << 6 | param | 04);
		emit1(sib_1 | reg_1);
	} else {
		emit1(mod_1<<6 | param | (reg_1&07));
	}

	/* and displacement */
	if ((mod_1 == 0 && reg_1 == 5) || mod_1 == 2) {
		/* 32-bit displacement follows */
		DPRINTF(("target is [ebp+offset], assuming 32-bit offset)\n"));
		/* ??? should this be protected by a call to "small" ??? */
		RELOMOVE(relonami, rel_1);
		newrelo(exp_1.typ, RELO4);
		emit4((long)(exp_1.val));
	} else if (mod_1 == 1) {
		/* 8-bit displacement */
		emit1((int)(exp_1.val));
	}
}

void
ea_2(int param)
{

	op_1 = op_2;
	RELOMOVE(rel_1, rel_2);
	ea_1(param);
}

int
checkscale(ADDR_T val)
{
	int v = val;

	if (!address_long) {
		serror("scaling not allowed in 16-bit mode");
		return 0;
	}
	if (v != val) v = 0;
	switch(v) {
	case 1:
		return 0;
	case 2:
		return 1 << 6;
	case 4:
		return 2 << 6;
	case 8:
		return 3 << 6;
	default:
		serror("bad scale");
		return 0;
	}
	/*NOTREACHED*/
}

void
reverse(void)
{
	struct operand op;
	int r = rel_1;

	rel_1 = rel_2;
	rel_2 = r;
	op = op_1;
	op_1 = op_2;
	op_2 = op;
}

void
badsyntax(void)
{

	serror("bad operands");
}

void
regsize(int sz)
{
	int bit;

	bit = (sz&1) ? 0 : IS_R8;
	if ((is_reg(reg_1) && (reg_1 & IS_R8) != bit) || (is_reg(reg_2) && (reg_2 & IS_R8) != bit)) 
		serror("register error");
	if (!address_long) {
		reg_1 &= ~010;
		reg_2 &= ~010;
	}
}

void
rex()
{
#if 0
	printf("reg_1 = %x, reg_2 = %x\n", reg_1, reg_2);
#endif

	int rex = 0x00;
	if (is_reg64(reg_1))
		rex |= 0x48 | (reg_1 & 0x08 ? REXW : 0);
#if 0
	if (is_reg64(reg_2))
		rex |= 0x48 | (reg_2 & 0x08 ? REXR : 0);
#endif
	if (rex)
		emit1(rex);
}

void
indexed(void)
{
	if (address_long) {
		mod_2 = 0;
		if (sib_2 == -1)
			serror("register error");
		if (rm_2 == 0 && reg_2 == 4) {
			/*  base register sp, no index register; use indexed mode without index register */
			rm_2 = 04;
			sib_2 = 044;
		}
		if (reg_2 == 015) {
			reg_2 = 05;
			return;
		}
		if (small(exp_2.typ == S_ABS && fitb(exp_2.val), 3)) {
			if (small(exp_2.val == 0 && reg_2 != 5, 1)) {
			} else {
				mod_2 = 01;
			}
		} else if (small(0, 1)) {
		} else {
			mod_2 = 02;
		}
	} else {
		if (reg_2 & ~7)
			serror("register error");
		if (small(exp_2.typ == S_ABS && fitb(exp_2.val), 1)) {
			if (small(exp_2.val == 0 && reg_2 != 6, 1)) {
			} else {
				reg_2 |= 0100;
			}
		} else if (small(0, 1)) {
		} else {
			reg_2 |= 0200;
		}
	}
}

void
ebranch(int opc,expr_t exp)
{
	/*	Conditional branching; Full displacements are available
		on the 80386, so the well-known trick with the reverse branch
		over a jump is not needed here.
		The only complication here is with the address size, which
		can be set with a prefix. In this case, the user gets what
		he asked for.
	*/
	int sm;
	long dist;
	int saving = address_long ? 4 : 2;

	if (opc == 0353) /* 0xeb */
		saving--;
	dist = exp.val - (DOTVAL + 2);
	if (pass == PASS_2 && dist > 0 && !(exp.typ & S_DOT))
		dist -= sect[DOTSCT].s_gain;
	sm = dist > 0 ? fitb(dist - saving) : fitb(dist);
	if ((exp.typ & ~S_DOT) != DOTSCT)
		sm = 0;
	if ((sm = small(sm, saving)) == 0) {
		if (opc == 0353) {
			emit1(0xe9);
		} else {
			emit1(0xF);
			emit1(opc | 0x80);
		}
		dist -= saving;
		exp.val = dist;
		adsize_exp(exp, RELPC);
	} else {
		if (opc == 0353)
			emit1(opc);
		else
			emit1(opc | 0x70);
		emit1((int)dist);
	}
}

void
branch(int opc,expr_t exp)
{
	/*	LOOP, JCXZ, etc. branch instructions.
		Here, the offset just must fit in a byte.
	*/
	long dist;

	dist = exp.val - (DOTVAL + 2);
	if (pass == PASS_2 && dist > 0 && !(exp.typ & S_DOT))
		dist -= sect[DOTSCT].s_gain;
	fit((exp.typ & ~S_DOT) == DOTSCT && fitb(dist));
	emit1(opc);
	emit1((int)dist);
}

void
pushop(int opc)
{
	regsize(1);
	if (is_segreg(reg_1)) {
		/* segment register */
		if ((reg_1 & 07) <= 3)
			emit1(6 | opc | (reg_1&7)<<3);
		else {
			emit1(0xF);
			emit1(0200 | opc | ((reg_1&7)<<3));
		}
	} else if (is_reg(reg_1)) {
		/* normal register */
		emit1(0120 | opc<<3 | (reg_1&7));
	} else if (opc == 0) {
		if (is_expr(reg_1)) {
			if (small(exp_1.typ == S_ABS && fitb(exp_1.val), operand_long ? 3 : 1)) {
				emit1(0152);
				emit1((int)(exp_1.val));
			} else {
				emit1(0150);
				RELOMOVE(relonami, rel_1);
				opsize_exp(exp_1, 1);
			}
		} else {
			emit1(0xFF);
			ea_1(6<<3);
		}
	} else {
		emit1(0217);
		ea_1(0<<3);
	}
}

void
opsize_exp(expr_t exp, int nobyte)
{
	if (! nobyte) {
		newrelo(exp.typ, RELO1);
		emit1((int)(exp.val));
	} else if (operand_long) {
		newrelo(exp.typ, RELO4);
		emit4((long)(exp.val));
	} else {
		newrelo(exp.typ, RELO2);
		emit2((int)(exp.val));
	}
}

void
adsize_exp(expr_t exp, int relpc)
{
	if (address_long) {
		newrelo(exp.typ, RELO4 | relpc);
		emit4((long)(exp.val));
	} else {
		newrelo(exp.typ, RELO2 | relpc);
		emit2((int)(exp.val));
	}
}

void
addop(int opc)
{
	DPRINTF(("addop: reg_1=0x%x, reg_2=0x%x\n", reg_1, reg_2));

	regsize(opc);
	if (is_reg(reg_2)) {
		/*	Add register to register or memory */
		emit1(opc);
		ea_1((reg_2&7)<<3);
	} else if (is_acc(reg_1) && is_expr(reg_2)) {
		/*	Add immediate to accumulator */
		emit1(opc | 4);
		RELOMOVE(relonami, rel_2);
		opsize_exp(exp_2, (opc&1));
	} else if (is_expr(reg_2)) {
		DPRINTF(("add immediate (ea_2) to register or memory (ea_1)\n"));
		/*	Add immediate to register or memory */
		if ((opc&1) == 0) {
			emit1(0200);
		} else if (! small(exp_2.typ == S_ABS && fitb(exp_2.val), operand_long ? 3 : 1)) {
			emit1(0201);
		} else {
			emit1(0203);
			opc &= ~1;
		}
		ea_1(opc & 070);
		RELOMOVE(relonami, rel_2);
		opsize_exp(exp_2, (opc&1));
	} else if (is_reg(reg_1)) {
		/*	Add register or memory to register */
		emit1(opc | 2);
		ea_2((reg_1&7)<<3);
	} else {
		badsyntax();
	}
}

void
rolop(int opc)
{
	int oreg;

	oreg = reg_2;
	reg_2 = reg_1;
	regsize(opc);
	if (oreg == (IS_R8 | 1 | (address_long ? 0 : 0300))) {
		/* cl register */
		emit1(0322 | (opc&1));
		ea_1(opc&070);
	} else if (is_expr(oreg)) {
	    if (small(exp_2.typ == S_ABS && exp_2.val == 1, 1)) {
		/* shift by 1 */
		emit1(0320 | (opc&1));
		ea_1(opc&070);
	    } else {
		/* shift by byte count */
		emit1(0300 | (opc & 1));
		ea_1(opc & 070);
		RELOMOVE(relonami, rel_2);
		newrelo(exp_2.typ, RELO1);
		emit1((int)(exp_2.val));
	    }
	} else {
		badsyntax();
	}
}

void
incop(int opc)
{
	regsize(opc);
	if ((opc&1) && is_reg(reg_1)) {
		/* word register */
		emit1(0100 | (opc&010) | (reg_1&7));
	} else {
		emit1(0376 | (opc&1));
		ea_1(opc & 010);
	}
}

void
callop(int opc)
{
	regsize(1);
	if (is_expr(reg_1)) {
		if (opc == (040+(0351<<8))) {
			RELOMOVE(relonami, rel_1);
			ebranch(0353,exp_1);
		} else {
			exp_1.val -= (DOTVAL+3 + (address_long ? 2 : 0));
			emit1(opc>>8);
			RELOMOVE(relonami, rel_1);
			adsize_exp(exp_1, RELPC);
		}
	} else {
		emit1(0xFF);
		ea_1(opc&070);
	}
}

void
xchg(int opc)
{
	regsize(opc);
	if (! is_reg(reg_1) || is_acc(reg_2)) {
		reverse();
	}
	if (opc == 1 && is_acc(reg_1) && is_reg(reg_2)) {
		emit1(0220 | (reg_2&7));
	} else if (is_reg(reg_1)) {
		emit1(0206 | opc);
		ea_2((reg_1&7)<<3);
	} else {
		badsyntax();
	}
}

void
test(int opc)
{
	regsize(opc);
	if (is_reg(reg_2) || is_expr(reg_1))
		reverse();
	if (is_expr(reg_2)) {
		if (is_acc(reg_1)) {
			emit1(0250 | opc);
			RELOMOVE(relonami, rel_2);
			opsize_exp(exp_2, (opc&1));
		}
		else {
			emit1(0366 | opc);
			ea_1(0<<3);
			RELOMOVE(relonami, rel_2);
			opsize_exp(exp_2, (opc&1));
		}
	} else if (is_reg(reg_1)) {
		emit1(0204 | opc);
		ea_2((reg_1&7)<<3);
	} else {
		badsyntax();
	}
}

void
mov(int opc)
{
	DPRINTF(("reg1=%x, reg2=%x, rm1=%x, rm2=%x\n", reg_1, reg_2, rm_1, rm_2));

/*		reg1=200, reg2=5, rm1=0, rm2=0 */

	regsize(opc);
	if (is_segreg(reg_1)) {
		/* to segment register */
		emit1(0216);
		ea_2((reg_1&07)<<3);
	} else if (is_segreg(reg_2)) {
		/* from segment register */
		emit1(0214);
		ea_1((reg_2&07)<<3);
	} else if (is_expr(reg_2)) {
		/* from immediate */
		if (is_reg(reg_1)) {
			/* to register */
			emit1(0260 | opc<<3 | (reg_1&7));
		} else {
			/* to memory */
			emit1(0306 | opc);
			ea_1(0<<3);
		}
		RELOMOVE(relonami, rel_2);
		opsize_exp(exp_2, (opc&1));
	} else if (rm_1 == 05 && is_acc(reg_2)) {
		/* from accumulator to memory (displacement) */
		emit1(0242 | opc);
		RELOMOVE(relonami, rel_1);
		adsize_exp(exp_1, 0);
	} else if (rm_2 == 05 && is_acc(reg_1)) {
		/* from memory (displacement) to accumulator */
		emit1(0240 | opc);
		RELOMOVE(relonami, rel_2);
		adsize_exp(exp_2, 0);
	} else if (is_reg(reg_2)) {
		/* from register to memory or register */
		emit1(0210 | opc);
		ea_1((reg_2&07)<<3);
	} else if (is_reg(reg_1)) {
		/* from memory or register to register */
		emit1(0212 | opc);
		ea_2((reg_1&07)<<3);
	} else {
		badsyntax();
	}
}

void
extshft(int opc, int reg)
{
	int oreg2 = reg_2;

	reg_2 = reg_1;
	regsize(1);

	emit1(0xF);
	if (oreg2 == (IS_R8 | 1 | (address_long ? 0 : 0300))) {
		/* cl register */
		emit1(opc|1);
		ea_1(reg << 3);
	} else if (oreg2 & IS_R32) {
		/* XXXGJM temporily hacked in here */
		emit1(opc|1);
		ea_1(reg << 3);
	} else if (is_expr(oreg2)) {
		emit1(opc);
		ea_1(reg << 3);
		RELOMOVE(relonami, rel_2);
		newrelo(exp_2.typ, RELO1);
		emit1((int)(exp_2.val));
	} else {
		badsyntax();
	}
}

void
bittestop(int opc)
{
	regsize(1);
	emit1(0xF);
	if (is_expr(reg_2)) {
		emit1(0272);
		ea_1(opc << 3);
		RELOMOVE(relonami, rel_2);
		newrelo(exp_2.typ, RELO1);
		emit1((int)(exp_2.val));
	} else if (is_reg(reg_2)) {
		emit1(0203 | (opc<<3));
		ea_1((reg_2&7)<<3);
	} else {
		badsyntax();
	}
}

void
imul(int reg)
{
	/*
	 * This instruction is more elaborate on the 80386. Its most general form is:
	 *		imul reg, reg_or_mem, immediate.
	 * This is the form processed here.
	 */

	regsize(1);
	if (is_expr(reg_1)) {
		/* To also handle
		 *	imul reg, immediate, reg_or_mem
		 */
		reverse();
	}
	if (is_expr(reg_2)) {
		/* The immediate form; two cases: */
		if (small(exp_2.typ == S_ABS && fitb(exp_2.val),
			  operand_long ? 3 : 1)) {
			/* case 1: 1 byte encoding of immediate */
			emit1(0153);
			ea_1((reg & 07) << 3);
			emit1((int)(exp_2.val));
		} else {
			/* case 2: WORD or DWORD encoding of immediate */
			emit1(0151);
			ea_1((reg & 07) << 3);
			RELOMOVE(relonami, rel_2);
			opsize_exp(exp_2, 1);
		}
	} else if (is_reg(reg_1) && ((reg_1&7) == (reg & 07))) {
		/* the "reg" field and the "reg_or_mem" field are the same,
		   and the 3rd operand is not an immediate ...
		*/
		if (reg == 0) {
			/* how lucky we are, the target is the ax register */
			/* However, we cannot make an optimization for f.i.
				imul eax, blablabla
			   because the latter does not affect edx, whereas
				imul blablabla
			   does! Therefore, "reg" is or-ed with 0x10 in the
			   former case, so that the test above fails.
			*/
			emit1(0367);
			ea_2(050);
		} else {
			/* another register ... */
			emit1(0xF);
			emit1(0257);
			ea_2((reg & 07) << 3);
		}
	} else {
		 badsyntax();
	}
}

void
argprefix()
{
	if (!use32 && address_long)
		emit1(0xe7);
	else if (use32 && !address_long)
		emit1(0x67);
}
		
void
opprefix()
{
	if (!use32 && operand_long)
		emit1(0xe6);
	else if (use32 && !operand_long)
		emit1(0x66);
}

/*
 * How prefixes work:
 *
 * operand : the size of the register
 * address : the size of the memory object
 *
 * Note that explicit opcodes for byte operands are provided in all modes.
 *
 * in x86 mode: (16-bit)
 *	0xe6: word operand
 *	0xe7: word address
 * in 386 mode: (32-bit)
 *	0x66: changes the size of the data to 16-bit			mov %dx, (%ebx), movw $1,(%ebx)
 *	0x67: changes the size of the address to 16-bit			mov %edx,(%bp,%di) - invoked with '.code16' directive
 * in x64 mode: (64-bit)
 *	0x66: changes the size of the data to 16-bit
 *	0x67: changes the size of the address to 32-bit
 *	0x4x: REX prefix : 0 1 0 0 W R X B
 *		W : REX.W changes size of the data to 64-bits		movq $0x1,(%rbx)
 *		R : REX.R extends the reg value of MODRM		mov %r9b,(%rbx)
 *		X : REX.X extends the index register			mov %rax,0x40(%r8)
 *		B : REX.B extends the RM register			mov %rdx,%r9, mov $0x1,%r9b
 */

/*
 * MOD R/M Addressing Mode
 * === === ================================
 *  00 000 [ eax ]
 *  01 000 [ eax + disp8 ]
 *  10 000 [ eax + disp32 ]
 *  11 000 register  ( al / ax / eax )
 *  00 001 [ ecx ]
 *  01 001 [ ecx + disp8 ]
 *  10 001 [ ecx + disp32 ]
 *  11 001 register  ( cl / cx / ecx )
 *  00 010 [ edx ]
 *  01 010 [ edx + disp8 ]
 *  10 010 [ edx + disp32 ]
 *  11 010 register  ( dl / dx / edx )
 *  00 011 [ ebx ]
 *  01 011 [ ebx + disp8 ]
 *  10 011 [ ebx + disp32 ]
 *  11 011 register  ( bl / bx / ebx )
 *  00 100 SIB Mode
 *  01 100 SIB + disp8 Mode
 *  10 100 SIB + disp32 Mode
 *  11 100 register  ( ah / sp / esp )
 *  00 101 32-bit Displacement-Only Mode (%rip-relative in 64-bit mode)
 *  01 101 [ ebp + disp8 ]
 *  10 101 [ ebp + disp32 ]
 *  11 101 register  ( ch / bp / ebp )
 *  00 110 [ esi ]
 *  01 110 [ esi + disp8 ]
 *  10 110 [ esi + disp32 ]
 *  11 110 register  ( dh / si / esi )
 *  00 111 [ edi ]
 *  01 111 [ edi + disp8 ]
 *  10 111 [ edi + disp32 ]
 *  11 111 register  ( bh / di / edi )
 *
 * Scale
 * =====
 * 00 index*1
 * 01 index*2
 * 10 index*4
 * 11 index*4
 *  
 * Index
 * =====
 * 000 EAX
 * 001 ECX
 * 010 EDX
 * 011 EBX
 * 100 illegal (32-bit mode), (displacement-only mode in 64-bit mode)
 * 101 EBP
 * 110 ESI
 * 111 EDI
 *
 * Base
 * ====
 * 000 EAX
 * 001 ECX
 * 010 EDX
 * 011 EBX
 * 100 ESP
 * 101 EBP (displacement-only if MOD=00)
 * 110 ESI
 * 111 EDI
 * 
 */
