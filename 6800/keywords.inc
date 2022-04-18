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

/* compatibility */
{ 0,	'=',		0,		"equ"	},
{ 0,	PSEUDOOP_ORG,	0,		"org"	},
{ 0,	PSEUDOOP_BOOT,	0,		"boot"	},
{ 0,	PSEUDOOP_ENDB,	0,		"endb"	},

{ 0,	PSEUDOOP_END,	0,		"end"	},
{ 0,	PSEUDOOP_DATA,	1,		"fcb"	},	/* form constant byte */
{ 0,	PSEUDOOP_DATA,	2,		"fdb"	},	/* form double byte */
{ 0,	PSEUDOOP_DATA,	1,		"fcc"	},	/* form constant character */
{ 0,	PSEUDOOP_ASCII,	0,		"fcs"	},	/* form constant character */
{ 0,	PSEUDOOP_ZERO,	1,		"rmb"	},	/* reserve memory byte */

{ 0,	PSEUDOOP_ZERO,	1,		"ds"	},	/* define storage */
{ 0,	PSEUDOOP_DATA,	1,		"db"	},
{ 0,	PSEUDOOP_DATA,	2,		"dw"	},
{ 0,	PSEUDOOP_ASCII,	0,		"asc"	},

/* The X register */
{ 0,	X,		0,		"x"	},

{ 0,	BRANCH,		0x20,		"bra"	},
{ 0,	BRANCH,		0x22,		"bhi"	},
{ 0,	BRANCH,		0x23,		"bls"	},
{ 0,	BRANCH,		0x24,		"bhs"	},	/* bcc */
{ 0,	BRANCH,		0x24,		"bcc"	},
{ 0,	BRANCH,		0x25,		"blo"	},	/* bcs */
{ 0,	BRANCH,		0x25,		"bcs"	},
{ 0,	BRANCH,		0x26,		"bne"	},
{ 0,	BRANCH,		0x27,		"beq"	},
{ 0,	BRANCH,		0x28,		"bvc"	},
{ 0,	BRANCH,		0x29,		"bvs"	},
{ 0,	BRANCH,		0x2A,		"bpl"	},
{ 0,	BRANCH,		0x2B,		"bmi"	},
{ 0,	BRANCH,		0x2C,		"bge"	},
{ 0,	BRANCH,		0x2D,		"blt"	},
{ 0,	BRANCH,		0x2E,		"bgt"	},
{ 0,	BRANCH,		0x2F,		"ble"	},
{ 0,	BRANCH,		0x8D,		"bsr"	},
{ 0,	XOP,		0xA0,		"suba"	},
{ 0,	XOP,		0xA1,		"cmpa"	},
{ 0,	XOP,		0xA2,		"sbca"	},
{ 0,	XOP,		0xA4,		"anda"	},
{ 0,	XOP,		0xA5,		"bita"	},
{ 0,	XOP,		0xA6,		"ldaa"	},
{ 0,	XOP,		0xA8,		"eora"	},
{ 0,	XOP,		0xA9,		"adca"	},
{ 0,	XOP,		0xAA,		"oraa"	},
{ 0,	XOP,		0xAB,		"adda"	},
{ 0,	XOP,		0xE0,		"subb"	},
{ 0,	XOP,		0xE1,		"cmpb"	},
{ 0,	XOP,		0xE2,		"sbcb"	},
{ 0,	XOP,		0xE4,		"andb"	},
{ 0,	XOP,		0xE5,		"bitb"	},
{ 0,	XOP,		0xE6,		"ldab"	},
{ 0,	XOP,		0xE8,		"eorb"	},
{ 0,	XOP,		0xE9,		"adcb"	},
{ 0,	XOP,		0xEA,		"orab"	},
{ 0,	XOP,		0xEB,		"addb"	},
{ 0,	AOP,		0x60,		"neg"	},
{ 0,	NOARG,		0x40,		"nega"	},
{ 0,	NOARG,		0x50,		"negb"	},
{ 0,	AOP,		0x63,		"com"	},
{ 0,	NOARG,		0x43,		"coma"	},
{ 0,	NOARG,		0x53,		"comb"	},
{ 0,	AOP,		0x64,		"lsr"	},
{ 0,	NOARG,		0x44,		"lsra"	},
{ 0,	NOARG,		0x54,		"lsrb"	},
{ 0,	AOP,		0x66,		"ror"	},
{ 0,	NOARG,		0x46,		"rora"	},
{ 0,	NOARG,		0x56,		"rorb"	},
{ 0,	AOP,		0x67,		"asr"	},
{ 0,	NOARG,		0x47,		"asra"	},
{ 0,	NOARG,		0x57,		"asrb"	},
{ 0,	AOP,		0x68,		"asl"	},
{ 0,	NOARG,		0x48,		"asla"	},
{ 0,	NOARG,		0x58,		"aslb"	},
{ 0,	AOP,		0x68,		"lsl"	},
{ 0,	NOARG,		0x48,		"lsla"	},
{ 0,	NOARG,		0x58,		"lslb"	},
{ 0,	AOP,		0x69,		"rol"	},
{ 0,	NOARG,		0x49,		"rola"	},
{ 0,	NOARG,		0x59,		"rolb"	},
{ 0,	AOP,		0x6A,		"dec"	},
{ 0,	NOARG,		0x4A,		"deca"	},
{ 0,	NOARG,		0x5A,		"decb"	},
{ 0,	AOP,		0x6C,		"inc"	},
{ 0,	NOARG,		0x4C,		"inca"	},
{ 0,	NOARG,		0x5C,		"incb"	},
{ 0,	AOP,		0x6D,		"tst"	},
{ 0,	NOARG,		0x4D,		"tsta"	},
{ 0,	NOARG,		0x5D,		"tstb"	},
{ 0,	AOP,		0x6F,		"clr"	},
{ 0,	NOARG,		0x4F,		"clra"	},
{ 0,	NOARG,		0x5F,		"clrb"	},
{ 0,	XOP,		0x6E,		"jmp"	},
{ 0,	XOP,		0xAD,		"jsr"	},
{ 0,	XOP,		0xAC,		"cpx"	},
{ 0,	XOP,		0xAE,		"lds"	},
{ 0,	XOP,		0xEE,		"ldx"	},
{ 0,	XOP,		0xA7,		"staa"	},
{ 0,	XOP,		0xE7,		"stab"	},
{ 0,	XOP,		0xEF,		"stx"	},
{ 0,	XOP,		0xAF,		"sts"	},
{ 0,	NOARG,		0x19,		"daa"	},
{ 0,	NOARG,		0x01,		"nop"	},
{ 0,	NOARG,		0x3B,		"rti"	},
{ 0,	NOARG,		0x39,		"rts"	},
{ 0,	NOARG,		0x3F,		"swi"	},
{ 0,	NOARG,		0x0C,		"clc"	},
{ 0,	NOARG,		0x0D,		"sec"	},
{ 0,	NOARG,		0x0E,		"cli"	},
{ 0,	NOARG,		0x0F,		"sei"	},
{ 0,	NOARG,		0x0A,		"clv"	},
{ 0,	NOARG,		0x0B,		"sev"	},
{ 0,	NOARG,		0x3E,		"wai"	},
{ 0,	NOARG,		0x06,		"tap"	},
{ 0,	NOARG,		0x07,		"tpa"	},
{ 0,	NOARG,		0x1B,		"aba"	},
{ 0,	NOARG,		0x11,		"cba"	},
{ 0,	NOARG,		0x10,		"sba"	},
{ 0,	NOARG,		0x16,		"tab"	},
{ 0,	NOARG,		0x17,		"tba"	},
{ 0,	NOARG,		0x09,		"dex"	},
{ 0,	NOARG,		0x08,		"inx"	},

{ 0,	NOARG,		0x34,		"des"	},
{ 0,	NOARG,		0x31,		"ins"	},
{ 0,	NOARG,		0x35,		"txs"	},
{ 0,	NOARG,		0x30,		"tsx"	},
{ 0,	NOARG,		0x32,		"pula"	},
{ 0,	NOARG,		0x36,		"psha"	},
{ 0,	NOARG,		0x33,		"pulb"	},
{ 0,	NOARG,		0x37,		"pshb"	},
