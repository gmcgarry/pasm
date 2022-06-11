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

extern int dpvalue INIT(0);	/* for setdp pseudo-op */

#ifndef extern
extern int regbit[];
#else
int regbit[] = {	/* push-pull coding */
	6,	/* D */
	0x10,	/* X */
	0x20,	/* Y */
	0x40,	/* U */
	0x40,	/* S */
	0x80,	/* PC */
	-1, -1,
	2,	/* A */
	4,	/* B */
	1,	/* CC */
	8,	/* DP */
};
#endif

/*
 * Motorola 6809 register names
 */
#define D	0
#define X	1
#define Y	2
#define U	3
#define S	4
#define PC	5
#define A	8
#define B	9
#define CC	10
#define DP	11

/*
 * Motorola 6809 specific routines
 */
void branch(register int opc, expr_t exp);
int regno(register int r);
void emit1or2(int n);
void offset(register int reg, expr_t exp, register int ind);
