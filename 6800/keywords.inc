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
{ 0,	PSEUDOOP_END,	0,		"end"	},
{ 0,	PSEUDOOP_DATA,	1,		"fcb"	},	/* form constant byte */
{ 0,	PSEUDOOP_DATA,	2,		"fdb"	},	/* form double byte */
{ 0,	PSEUDOOP_ZERO,	1,		"rmb"	},	/* reserve memory byte */
{ 0,	PSEUDOOP_ASCII,	0,		"fcc"	},	/* form constant character */

/* The X register */
{ 0,	X,		0,		"x"	},

#if defined(MC6805) || defined(MC68HC08)
/* Bit test and branch */
{ 0,	BBRANCH,	0x00,		"brset"	},
{ 0,	BBRANCH,	0x01,		"brclr"	},

/* Bit manipulation */
{ 0,	BIT,		0x10,		"bset"	},
{ 0,	BIT,		0x11,		"bclr"	},
#endif

/* Branches */
{ 0,	BRANCH,		0x20,		"bra"	},
#if defined(MC6805) || defined(MC68HC08)
{ 0,	BRANCH,		0x21,		"brn"	},
#endif
{ 0,	BRANCH,		0x22,		"bhi"	},
{ 0,	BRANCH,		0x23,		"bls"	},
{ 0,	BRANCH,		0x24,		"bhs"	},
{ 0,	BRANCH,		0x24,		"bcc"	},
{ 0,	BRANCH,		0x25,		"blo"	},
{ 0,	BRANCH,		0x25,		"bcs"	},
{ 0,	BRANCH,		0x26,		"bne"	},
{ 0,	BRANCH,		0x27,		"beq"	},
#if defined(MC6805) || defined(MC68HC08)
{ 0,	BRANCH,		0x28,		"bhcc"	},
{ 0,	BRANCH,		0x29,		"bhcs"	},
#else
{ 0,	BRANCH,		0x28,		"bvc"	},
{ 0,	BRANCH,		0x29,		"bhs"	},
#endif
{ 0,	BRANCH,		0x2a,		"bpl"	},
{ 0,	BRANCH,		0x2b,		"bmi"	},
#if defined(MC6805) || defined(MC68HC08)
{ 0,	BRANCH,		0x2c,		"bmc"	},
{ 0,	BRANCH,		0x2d,		"bms"	},
{ 0,	BRANCH,		0x2e,		"bil"	},
{ 0,	BRANCH,		0x2f,		"bih"	},
#else
{ 0,	BRANCH,		0x2c,		"bge"	},
{ 0,	BRANCH,		0x2d,		"blt"	},
{ 0,	BRANCH,		0x2e,		"bgt"	},
{ 0,	BRANCH,		0x2f,		"ble"	},
#endif

/* unconditional branches */
#if defined(MC6805) || defined(MC68HC08)
{ 0,	RM,		0xac,		"jmp"	},
{ 0,	BRANCH,		0xad,		"bsr"	},
#else
{ 0,	RM,		0x6E,		"jmp"	},
{ 0,	BRANCH,		0x8D,		"bsr"	},	/* pc-relative jmp to subroutine */
#endif
{ 0,	RM,		0xad,		"jsr"	},	/* absolute jump to subroutine */

/* Read modify write on anything but registers */
{ 0,	RMW,		0x30,		"neg"	},
{ 0,	RMW,		0x33,		"com"	},
{ 0,	RMW,		0x34,		"lsr"	},
{ 0,	RMW,		0x36,		"ror"	},
{ 0,	RMW,		0x36,		"asr"	},
{ 0,	RMW,		0x38,		"lsl"	},
{ 0,	RMW,		0x39,		"rol"	},
{ 0,	RMW,		0x3a,		"dec"	},
{ 0,	RMW,		0x3c,		"inc"	},
{ 0,	RMW,		0x3d,		"tst"	},
{ 0,	RMW,		0x3f,		"clr"	},

/* Implied stuff */
{ 0,	CTL,		0x80,		"rti"	},
{ 0,	CTL,		0x81,		"rts"	},
{ 0,	CTL,		0x83,		"swi"	},
{ 0,	CTL,		0x97,		"tax"	},
{ 0,	CTL,		0x98,		"clc"	},
{ 0,	CTL,		0x99,		"sec"	},
{ 0,	CTL,		0x9a,		"cli"	},
{ 0,	CTL,		0x9b,		"sei"	},
{ 0,	CTL,		0x9c,		"rsp"	},
{ 0,	CTL,		0x9d,		"nop"	},
{ 0,	CTL,		0x9f,		"txa"	},
#if defined(MC6805) || defined(MC68HC08)
#else
{ 0,	CTL,		0x3B,		"rti"	},
{ 0,	CTL,		0x39,		"rts"	},
{ 0,	CTL,		0x3F,		"swi"	},
{ 0,	CTL,		0x0C,		"clc"	},
{ 0,	CTL,		0x0D,		"sec"	},
{ 0,	CTL,		0x0E,		"cli"	},
{ 0,	CTL,		0x0F,		"sei"	},
{ 0,	CTL,		0x01,		"nop"	},
#endif

/* Register memory. Warning. Some imediate opcodes excluded in parser actions. */
#if defined(MC6805) || defined(MC68HC08)
{ 0,	RM,		0xa0,		"sub"	},
{ 0,	RM,		0xa1,		"cmp"	},
{ 0,	RM,		0xa2,		"sbc"	},
{ 0,	RM,		0xa3,		"cpx"	},
{ 0,	RM,		0xa4,		"and"	},
{ 0,	RM,		0xa5,		"bit"	},
{ 0,	RM,		0xa6,		"lda"	},
{ 0,	RM,		0xa7,		"sta"	},
{ 0,	RM,		0xa8,		"eor"	},
{ 0,	RM,		0xa9,		"adc"	},
{ 0,	RM,		0xaa,		"ora"	},
{ 0,	RM,		0xab,		"add"	},
#else
{ 0,	RM,		0xA0,		"suba"	},
{ 0,	RM,		0xA1,		"cmpa"	},
{ 0,	RM,		0xA2,		"sbca"	},
{ 0,	RM,		0xA4,		"anda"	},
{ 0,	RM,		0xA5,		"bita"	},
{ 0,	RM,		0xA6,		"ldaa"	},
{ 0,	RM,		0xA7,		"staa"	},
{ 0,	RM,		0xA8,		"eora"	},
{ 0,	RM,		0xA9,		"adca"	},
{ 0,	RM,		0xAA,		"oraa"	},
{ 0,	RM,		0xAB,		"adda"	},
#endif
#if !defined(MC6805) && !defined(MC68HC08)
{ 0,	RM,		0xAC,		"cpx"	},
{ 0,	RM,		0xE0,		"subb"	},
{ 0,	RM,		0xE1,		"cmpb"	},
{ 0,	RM,		0xE2,		"sbcb"	},
{ 0,	RM,		0xE4,		"andb"	},
{ 0,	RM,		0xE5,		"bitb"	},
{ 0,	RM,		0xE6,		"ldab"	},
{ 0,	RM,		0xE8,		"eorb"	},
{ 0,	RM,		0xE9,		"adcb"	},
{ 0,	RM,		0xEA,		"orab"	},
{ 0,	RM,		0xEB,		"addb"	},
#endif
{ 0,	RM,		0xae,		"ldx"	},
{ 0,	RM,		0xaf,		"stx"	},

/* Brain damaged concatenated opcodes for RMW on registers */
{ 0,	CTL,		0x40,		"nega"	},
{ 0,	CTL,		0x43,		"coma"	},
{ 0,	CTL,		0x44,		"lsra"	},
{ 0,	CTL,		0x46,		"rora"	},
{ 0,	CTL,		0x47,		"asra"	},
{ 0,	CTL,		0x48,		"lsla"	},
{ 0,	CTL,		0x48,		"asla"	},	/* alias */
{ 0,	CTL,		0x49,		"rola"	},
{ 0,	CTL,		0x4a,		"deca"	},
{ 0,	CTL,		0x4c,		"inca"	},
{ 0,	CTL,		0x4d,		"tsta"	},
{ 0,	CTL,		0x4f,		"clra"	},

#ifdef MC6805
{ 0,	CTL,		0x50,		"negx"	},
{ 0,	CTL,		0x53,		"comx"	},
{ 0,	CTL,		0x54,		"lsrx"	},
{ 0,	CTL,		0x56,		"rorx"	},
{ 0,	CTL,		0x57,		"asrx"	},
{ 0,	CTL,		0x58,		"lslx"	},
{ 0,	CTL,		0x58,		"aslx"	},	/* alias */
{ 0,	CTL,		0x59,		"rolx"	},
{ 0,	CTL,		0x5a,		"decx"	},
{ 0,	CTL,		0x5c,		"incx"	},
{ 0,	CTL,		0x5d,		"tstx"	},
{ 0,	CTL,		0x5f,		"clrx"	},
#else
{ 0,	CTL,		0x50,		"negb"	},
{ 0,	CTL,		0x53,		"comb"	},
{ 0,	CTL,		0x54,		"lsrb"	},
{ 0,	CTL,		0x56,		"rorb"	},
{ 0,	CTL,		0x57,		"asrb"	},
{ 0,	CTL,		0x58,		"lslb"	},
{ 0,	CTL,		0x58,		"aslb"	},	/* alias */
{ 0,	CTL,		0x59,		"rolb"	},
{ 0,	CTL,		0x5A,		"decb"	},
{ 0,	CTL,		0x5C,		"incb"	},
{ 0,	CTL,		0x5D,		"tstb"	},
{ 0,	CTL,		0x5F,		"clrb"	},

{ 0,	CTL,		0x19,		"daa"	},
{ 0,	CTL,		0x0A,		"clv"	},
{ 0,	CTL,		0x0B,		"sev"	},
{ 0,	CTL,		0x3E,		"wai"	},
{ 0,	CTL,		0x06,		"tap"	},
{ 0,	CTL,		0x07,		"tpa"	},
{ 0,	CTL,		0x1B,		"aba"	},
{ 0,	CTL,		0x11,		"cba"	},
{ 0,	CTL,		0x10,		"sba"	},
{ 0,	CTL,		0x16,		"tab"	},
{ 0,	CTL,		0x17,		"tba"	},
{ 0,	CTL,		0x09,		"dex"	},
{ 0,	CTL,		0x08,		"inx"	},
#endif

/* stack operations */
#if !defined(MC6805) && !defined(MC68HC08)
{ 0,	RM,		0xEE,		"lds"	},
{ 0,	RM,		0xEF,		"sts"	},
{ 0,	CTL,		0x34,		"des"	},
{ 0,	CTL,		0x31,		"ins"	},
{ 0,	CTL,		0x35,		"txs"	},
{ 0,	CTL,		0x30,		"tsx"	},
#endif

#ifdef MC6802
/* XXXGJM check opcodes */
{ 0,	CTL,		0x34,		"psha"	},
{ 0,	CTL,		0x35,		"pshb"	},
{ 0,	CTL,		0x36,		"pula"	},
{ 0,	CTL,		0x37,		"pulb"	},
#endif

#if defined(MC6805) || defined(MC68HC08)
/* CMOS support */
{ 0,	CMOS,		0,		".cmos"	},
{ 0,	CMOS,		0x8e,		"stop"	},
{ 0,	CMOS,		0x8f,		"wait"	},
#endif
