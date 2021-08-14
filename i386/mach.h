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

#define low6(z)		(z & 0x3f)
#define fit6(z)		(low6(z) == z)
#define low3(z)		(z & 07)
#define fit3(z)		(low3(z) == z)

#define RELOMOVE(a,b)   {a = b; b = 0;}

#define FESC		0xD8		/* escape for 80[23]87 processor */

#define ufitb(z)	((unsigned)(z) <= 255)

#define IS_R8		0x0100
#define IS_R16		0x0200
#define IS_R32		0x0400
#define IS_EXPR		0x0800
#define IS_RSEG		0x1000
#define IS_R64		0x2000

#define is_expr(reg)	((reg)&IS_EXPR)
#define is_segreg(reg)	((reg)&IS_RSEG)
#define is_reg(reg)	(((reg)&(IS_R8|IS_R16|IS_R32|IS_R64)) != 0)
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

extern int	use32;
extern int	address_long;
extern int	operand_long;

extern char	regindex_ind[8][8];
extern char	sr_m[8];
extern char	dr_m[8][8];

/* i386-specific routines */
void ea_1_16(int param);
void ea_1(int param);
void ea_2(int param);
int checkscale(ADDR_T val);
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

void opprefix(void);
void argprefix(void);
