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
 * INTEL 80386 C declarations
 */

#define fitx(x, d)	((((x) + (1<<(d-1))) & ~((int)(1<<(d))-1)) == 0)
#define fitb(x)         ((((x) + 0x80) & ~((int)0xFF)) == 0)
#define fitw(x)         ((((x) + 0x8000L) & ~0xFFFFL) == 0)
#define fit(x)          if (!(x)) nofit()

#define low6(z)		(z & 077)
#define fit6(z)		(low6(z) == z)
#define low3(z)		(z & 07)
#define fit3(z)		(low3(z) == z)

#define RELOMOVE(a,b)   {a = b; b = 0;}

#define FESC		0xD8		/* escape for 80[23]87 processor */

#define ufitb(z)	((unsigned)(z) <= 255)

#define IS_R8		0x0100
#define IS_R32		0x0200
#define IS_R64		0x0400
#define IS_EXPR		0x0800
#define IS_RSEG		0x1000

#define is_expr(reg)	((reg)&IS_EXPR)
#define is_segreg(reg)	((reg)&IS_RSEG)
#define is_reg(reg)	(((reg)&(IS_R8|IS_R32|IS_R64)) != 0)
#define is_acc(reg)	(is_reg(reg) && ((reg & 07) == 0))

struct operand {
	int	mod;
	int	rm;
	int	reg;
	int	sib;		/* scale-index-base */
	expr_t	exp;
};

extern struct operand	op_1, op_2;

#define mod_1	op_1.mod
#define mod_2	op_2.mod
#define rm_1	op_1.rm
#define rm_2	op_2.rm
#define reg_1	op_1.reg
#define reg_2	op_2.reg
#define sib_1	op_1.sib
#define sib_2	op_2.sib
#define exp_1	op_1.exp
#define exp_2	op_2.exp

extern int	rel_1, rel_2;

#ifndef extern
extern char	regindex_ind[8][8];
#else
/*	First index is base register; second index is index register;
	sp cannot be an index register.
	For base and index register indirect mode, bp cannot be the
	base register, but this info is not included in this array.
	This can always be handled by using the base and index register with
	displacement mode.
*/
char	regindex_ind[8][8] = {
	{ 000,	010,	020,	030,	-1,	050,	060,	070 },
	{ 001,	011,	021,	031,	-1,	051,	061,	071 },
	{ 002,	012,	022,	032,	-1,	052,	062,	072 },
	{ 003,	013,	023,	033,	-1,	053,	063,	073 },
	{ 004,	014,	024,	034,	-1,	054,	064,	074 },
	{ 005,	015,	025,	035,	-1,	055,	065,	075 },
	{ 006,	016,	026,	036,	-1,	056,	066,	076 },
	{ 007,	017,	027,	037,	-1,	057,	067,	077 },
};
#endif

extern int	address_long INIT(1), operand_long INIT(1);
extern int	use32 INIT(1);

/* For 16-bit addressing: copied from i86 assembler */
#ifndef extern
extern char sr_m[8];
#else
char sr_m[8] = {
        -1,     -1,     -1,     7,      -1,     6,      4,      5
};
#endif

#ifndef extern
extern char dr_m[8][8];
#else
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
#endif

/* 80386 specific routines */
void ea_1_16(int param);
void ea_1(int param);
void ea_2(int param);
int checkscale(valu_t val);
void reverse(void);
void badsyntax(void);
void regsize(int sz);
void indexed(void);
void ebranch(register int opc,expr_t exp);
void branch(register int opc,expr_t exp);
void pushop(register int opc);
void opsize_exp(expr_t exp, int nobyte);
void adsize_exp(expr_t exp, int relpc);
void addop(register int opc);
void rolop(register int opc);
void incop(register int opc);
void callop(register int opc);
void xchg(register int opc);
void test(register int opc);
void mov(register int opc);
void extshft(int opc, int reg);
void bittestop(int opc);
void imul(int reg);
