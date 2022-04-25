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
 * Mostek 6500 keywords
 */

{0,	PSEUDOOP_SCR,	0,		".scr"},

/* compatibility */
{0,	PSEUDOOP_ORG,	0,		"org"},

/* C64-specific compatibility */
#ifdef COMPAT_C64
{0,	PSEUDOOP_EQU,	0,		".const"},
{0,	PSEUDOOP_EQU,	0,		".la"},
{0,	PSEUDOOP_DATA,	1,		".by"},
{0,	PSEUDOOP_DATA,	2,		".wo"},
{0,	PSEUDOOP_BASE,	2,		".ba"},
{0,	PSEUDOOP_FILL,	0,		".br"},
{0,	PSEUDOOP_ASCII,	1,		".tx"},
{0,	PSEUDOOP_ASCII,	1,		".text"},
#endif

#define COMPAT_APPLE
#ifdef COMPAT_APPLE
{0,	'=',		0,		".eq"},
{0,	PSEUDOOP_ORG,	0,		".or"},
{0,	PSEUDOOP_DATA,	WORDSIZE,	".da"},
#endif

{0,	EXTENSION,	0,		".l"},
{0,	EXTENSION,	8,		".h"},
{0,	A,		0,		"a"},
{0,	X,		0,		"x"},
{0,	Y,		0,		"y"},
{0,	ADDOP,		0x60,		"adc"},
{0,	ADDOP,		0x20,		"and"},
{0,	ADDOP,		0xC0,		"cmp"},
{0,	ADDOP,		0x40,		"eor"},
{0,	ADDOP,		0xA0,		"lda"},
{0,	ADDOP,		0x00,		"ora"},
{0,	ADDOP,		0xE0,		"sbc"},
{0,	ADDOP,		0x80,		"sta"},
{0,	ROLOP,		0x00,		"asl"},
{0,	ROLOP,		0x40,		"lsr"},
{0,	ROLOP,		0x20,		"rol"},
{0,	ROLOP,		0x60,		"ror"},
{0,	BRAOP,		0x90,		"bcc"},
{0,	BRAOP,		0xB0,		"bcs"},
{0,	BRAOP,		0xF0,		"beq"},
{0,	BRAOP,		0x30,		"bmi"},
{0,	BRAOP,		0xD0,		"bne"},
{0,	BRAOP,		0x10,		"bpl"},
{0,	BRAOP,		0x50,		"bvc"},
{0,	BRAOP,		0x70,		"bvs"},
{0,	BITOP,		0x24,		"bit"},
{0,	NOPOP,		0x00,		"brk"},
{0,	NOPOP,		0x18,		"clc"},
{0,	NOPOP,		0xD8,		"cld"},
{0,	NOPOP,		0x58,		"cli"},
{0,	NOPOP,		0xB8,		"clv"},
{0,	NOPOP,		0xCA,		"dex"},
{0,	NOPOP,		0x88,		"dey"},
{0,	NOPOP,		0xE8,		"inx"},
{0,	NOPOP,		0xC8,		"iny"},
{0,	NOPOP,		0xEA,		"nop"},
{0,	NOPOP,		0x48,		"pha"},
{0,	NOPOP,		0x08,		"php"},
{0,	NOPOP,		0x68,		"pla"},
{0,	NOPOP,		0x28,		"plp"},
{0,	NOPOP,		0x40,		"rti"},
{0,	NOPOP,		0x60,		"rts"},
{0,	NOPOP,		0x38,		"sec"},
{0,	NOPOP,		0xF8,		"sed"},
{0,	NOPOP,		0x78,		"sei"},
{0,	NOPOP,		0xAA,		"tax"},
{0,	NOPOP,		0xA8,		"tay"},
{0,	NOPOP,		0x98,		"tya"},
{0,	NOPOP,		0xBA,		"tsx"},
{0,	NOPOP,		0x8A,		"txa"},
{0,	NOPOP,		0x9A,		"txs"},
{0,	CPXOP,		0xE0,		"cpx"},
{0,	CPXOP,		0xC0,		"cpy"},
{0,	INCOP,		0xC0,		"dec"},
{0,	INCOP,		0xE0,		"inc"},
{0,	JMPOP,		0x4C,		"jmp"},
{0,	JSROP,		0x20,		"jsr"},
{0,	LDXOP,		0xA0,		"ldx"},
{0,	LDYOP,		0xA0,		"ldy"},
{0,	STXOP,		0x80,		"stx"},
{0,	STYOP,		0x80,		"sty"},
{0,	PSEU,		0x1860,		"add"},
{0,	PSEU,		0x38E0,		"sub"},
