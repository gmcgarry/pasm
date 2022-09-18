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
 * Motorola 680x0 dependent C declarations
 */

#define MODEL_68000	0
#define MODEL_68010	1
#define MODEL_68020	2
#define MODEL_68030	3
#define MODEL_68040	4

#define	low3(z)		((short)(z) & 07)
#define	low4(z)		((short)(z) & 017)
#define	low7(z)		((short)(z) & 0177)

#define	fit3(z)		((((z)-1) & ~((int)07)) == 0)
#define	fit4(z)		(((z) & ~((int)017)) == 0)
#define	fit7(z)		(((z) & ~((int)0177)) == 0)
#define sfit7(z)	(fit7((z)+64))
#define	fit8(z)		(((z) & ~((int)0xFF)) == 0)
#define	fit16(z)	(((z) & ~(0xFFFFL)) == 0)

#define fitw(x)		fitx((x)+0x7FFFL,16)
#define fitb(x)		fitx((x)+0x7F,8)
#define loww(x)		((x) & 0xFFFFL)
#define lowb(x)		((x) & 0x00FFL)


#define	SIZE_B		0000
#define	SIZE_W		0100
#define	SIZE_L		0200
#define	SIZE_NON	0300
#define	SIZE_DEF	SIZE_W

#define OSIZE_S		00
#define OSIZE_L		01
#define OSIZE_DEF	OSIZE_L

#define FSIZE_L		00
#define FSIZE_S		01
#define FSIZE_X		02
#define FSIZE_P		03
#define FSIZE_W		04
#define FSIZE_D		05
#define FSIZE_B		06

#define DEF_FP          01000   /* default floating point processor */
extern int	co_id;

extern int	mrg_1,mrg_2;
extern expr_t	exp_1,exp_2;
#ifndef ASLD
extern VALUE_T	rel_1,rel_2;
#endif
extern int 	model;		/* 680x0 */
extern int	curr_instr;

/* addressing mode bits */
#define	DTA		0x01
#define	MEM		0x02
#define	CTR		0x04
#define	ALT		0x08
#define	FITB		0x10
#define	FITW		0x20
#define	PUTW		0x40
#define	PUTL		0x80

#if 0
extern unsigned short eamode[];
#endif

/* 680x0 specific instructions */
void ea_1(int sz, int bits);
void ea_2(int sz, int bits);
void indexmode(int hibyte);
void checksize(int sz, int bits);
void testmodel(int model);
void badoperand(void);
void shift_op(int opc, int sz);
void bitop(int opc);
void add(int opc, int sz);
void and(int opc, int sz);
int to_dreg(int opc, int sz, int bits);
int from_dreg(int opc, int sz, int bits);
void cmp(int sz);
void move(int sz);
void move_special(int sz);
int reverse(register int regs, int max);
void movem(int dr, int sz, int regs);
void movep(int sz);
void branch(int opc, expr_t exp);
void ea5x73(int rg, int sz);
void ea707172(int sz);
void ea6x(int rg, int ir, int sz);
void ea72(void);
void ea73(int ri, int sz);
void fbranch(int opc, expr_t exp);
void ch_sz_dreg(int size, int mode);
void check_fsize(int sz, int size);
