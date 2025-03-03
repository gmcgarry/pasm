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

{ 0,	SETDP,		0,		".setdp"	},
{ 0,	NOARG,		0x10,		".page2"	},
{ 0,	NOARG,		0x11,		".page3"	},

/* compatibility */
#ifdef COMPAT
{ 0,	'=',		0,		"equ"	},
{ 0,	PSEUDOOP_ORG,	0,		"org"	},
{ 0,	PSEUDOOP_END,	0,		"end"	},

{ 0,	PSEUDOOP_DATA,  1,		"fcb"	},	/* form constant byte */
{ 0,	PSEUDOOP_DATA,  2,		"fdb"	},	/* form double byte */
{ 0,	PSEUDOOP_DATA,  1,		"fcc"	},	/* form constant character */
{ 0,	PSEUDOOP_ASCII, 0,		"fcs"	},	/* form constant character */
{ 0,	PSEUDOOP_ZERO,  1,		"rmb"	},	/* reserve memory byte */

{ 0,	PSEUDOOP_ZERO,  1,		"ds"	},	/* define storage */
{ 0,	PSEUDOOP_DATA,  1,		"db"	},
{ 0,	PSEUDOOP_DATA,  2,		"dw"	},
{ 0,	PSEUDOOP_ASCII, 0,		"asc"	},
#endif

{ 0,	REG,		A,		"a"	},
{ 0,	REG,		B,		"b"	},
{ 0,	REG,		CC,		"cc"	},
{ 0,	REG,		CC,		"ccr"	},	/* alias */
{ 0,	REG,		DP,		"dp"	},
{ 0,	REG,		D,		"d"	},
{ 0,	REG,		X,		"x"	},
{ 0,	REG,		Y,		"y"	},
{ 0,	REG,		U,		"u"	},
{ 0,	REG,		S,		"s"	},
{ 0,	REG,		PC,		"pc"	},
#ifdef COMPAT
{ 0,	REG, 		PC,		"pcr"	},
#endif

{ 0,	ALL,		0xFF,		"all"	},
{ 0,	NOARG,		0x3A,		"abx"	},
{ 0,	NOARG,		0x19,		"daa"	},
{ 0,	NOARG,		0x3D,		"mul"	},
{ 0,	NOARG,		0x12,		"nop"	},
{ 0,	NOARG,		0x3B,		"rti"	},
{ 0,	NOARG,		0x4F,		"clra"	},
{ 0,	NOARG,		0x5F,		"clrb"	},
{ 0,	NOARG,		0x4A,		"deca"	},
{ 0,	NOARG,		0x5A,		"decb"	},
{ 0,	NOARG,		0x43,		"coma"	},
{ 0,	NOARG,		0x53,		"comb"	},
{ 0,	NOARG,		0x44,		"lsra"	},
{ 0,	NOARG,		0x54,		"lsrb"	},
{ 0,	NOARG,		0x40,		"nega"	},
{ 0,	NOARG,		0x50,		"negb"	},
{ 0,	NOARG,		0x46,		"rora"	},
{ 0,	NOARG,		0x56,		"rorb"	},
{ 0,	NOARG,		0x47,		"asra"	},
{ 0,	NOARG,		0x57,		"asrb"	},
{ 0,	NOARG,		0x49,		"rola"	},
{ 0,	NOARG,		0x59,		"rolb"	},
{ 0,	NOARG,		0x48,		"asla"	},
{ 0,	NOARG,		0x58,		"aslb"	},
{ 0,	NOARG,		0x48,		"lsla"	},
{ 0,	NOARG,		0x58,		"lslb"	},
{ 0,	NOARG,		0x4C,		"inca"	},
{ 0,	NOARG,		0x5C,		"incb"	},
{ 0,	NOARG,		0x4D,		"tsta"	},
{ 0,	NOARG,		0x5D,		"tstb"	},
{ 0,	NOARG,		0x39,		"rts"	},
{ 0,	NOARG,		0x1D,		"sex"	},
{ 0,	NOARG,		0x3F,		"swi"	},
{ 0,	NOARG,		0x103F,		"swi2"	},
{ 0,	NOARG,		0x113F,		"swi3"	},
{ 0,	NOARG,		0x13,		"sync"	},
{ 0,	BRANCH,		0x20,		"bra"	},
{ 0,	BRANCH,		0x21,		"brn"	},
{ 0,	BRANCH,		0x22,		"bhi"	},
{ 0,	BRANCH,		0x23,		"bls"	},
{ 0,	BRANCH,		0x24,		"bhs"	},
{ 0,	BRANCH,		0x24,		"bcc"	},
{ 0,	BRANCH,		0x25,		"blo"	},
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
{ 0,	STACK,		0x34,		"pshs"	},
{ 0,	STACK,		0x35,		"puls"	},
{ 0,	STACK,		0x36,		"pshu"	},
{ 0,	STACK,		0x37,		"pulu"	},
{ 0,	IMMED,		0x1A,		"orcc"	},
{ 0,	IMMED,		0x1C,		"andcc"	},
{ 0,	IMMED,		0x3C,		"cwai"	},
{ 0,	TWOREG,		0x1E,		"exg"	},
{ 0,	TWOREG,		0x1F,		"tfr"	},
{ 0,	XOP,		0xA0,		"suba"	},
{ 0,	XOP,		0xA1,		"cmpa"	},
{ 0,	XOP,		0xA2,		"sbca"	},
{ 0,	XOP,		0xA4,		"anda"	},
{ 0,	XOP,		0xA5,		"bita"	},
{ 0,	XOP,		0xA6,		"lda"	},
{ 0,	XOP,		0xA8,		"eora"	},
{ 0,	XOP,		0xA9,		"adca"	},
{ 0,	XOP,		0xAA,		"ora"	},
{ 0,	XOP,		0xAB,		"adda"	},
{ 0,	XOP,		0xE0,		"subb"	},
{ 0,	XOP,		0xE1,		"cmpb"	},
{ 0,	XOP,		0xE2,		"sbcb"	},
{ 0,	XOP,		0xE4,		"andb"	},
{ 0,	XOP,		0xE5,		"bitb"	},
{ 0,	XOP,		0xE6,		"ldb"	},
{ 0,	XOP,		0xE8,		"eorb"	},
{ 0,	XOP,		0xE9,		"adcb"	},
{ 0,	XOP,		0xEA,		"orb"	},
{ 0,	XOP,		0xEB,		"addb"	},
{ 0,	XOP,		0x30,		"leax"	},
{ 0,	XOP,		0x31,		"leay"	},
{ 0,	XOP,		0x32,		"leas"	},
{ 0,	XOP,		0x33,		"leau"	},
{ 0,	XOP,		0x60,		"neg"	},
{ 0,	XOP,		0x63,		"com"	},
{ 0,	XOP,		0x64,		"lsr"	},
{ 0,	XOP,		0x66,		"ror"	},
{ 0,	XOP,		0x67,		"asr"	},
{ 0,	XOP,		0x68,		"asl"	},
{ 0,	XOP,		0x68,		"lsl"	},
{ 0,	XOP,		0x69,		"rol"	},
{ 0,	XOP,		0x6A,		"dec"	},
{ 0,	XOP,		0x6C,		"inc"	},
{ 0,	XOP,		0x6D,		"tst"	},
{ 0,	XOP,		0x6F,		"clr"	},
{ 0,	XOP,		0x6E,		"jmp"	},
{ 0,	XOP,		0xA3,		"subd"	},
{ 0,	XOP,		0x10A3,		"cmpd"	},
{ 0,	XOP,		0x11A3,		"cmpu"	},
{ 0,	XOP,		0xAC,		"cmpx"	},
{ 0,	XOP,		0x10AC,		"cmpy"	},
{ 0,	XOP,		0x11AC,		"cmps"	},
{ 0,	XOP,		0xAE,		"ldx"	},
{ 0,	XOP,		0x10AE,		"ldy"	},
{ 0,	XOP,		0xE3,		"addd"	},
{ 0,	XOP,		0xEC,		"ldd"	},
{ 0,	XOP,		0xEE,		"ldu"	},
{ 0,	XOP,		0x10EE,		"lds"	},
{ 0,	XOP,		0xA7,		"sta"	},
{ 0,	XOP,		0xAD,		"jsr"	},
{ 0,	XOP,		0xAF,		"stx"	},
{ 0,	XOP,		0x10AF,		"sty"	},
{ 0,	XOP,		0xE7,		"stb"	},
{ 0,	XOP,		0xED,		"std"	},
{ 0,	XOP,		0xEF,		"stu"	},
{ 0,	XOP,		0x10EF,		"sts"	},
{ 0,	LBRNCH,		0x21,		"lbrn"	},
{ 0,	LBRNCH,		0x22,		"lbhi"	},
{ 0,	LBRNCH,		0x23,		"lbls"	},
{ 0,	LBRNCH,		0x24,		"lbhs"	},
{ 0,	LBRNCH,		0x24,		"lbcc"	},
{ 0,	LBRNCH,		0x25,		"lblo"	},
{ 0,	LBRNCH,		0x25,		"lbcs"	},
{ 0,	LBRNCH,		0x26,		"lbne"	},
{ 0,	LBRNCH,		0x27,		"lbeq"	},
{ 0,	LBRNCH,		0x28,		"lbvc"	},
{ 0,	LBRNCH,		0x29,		"lbvs"	},
{ 0,	LBRNCH,		0x2A,		"lbpl"	},
{ 0,	LBRNCH,		0x2B,		"lbmi"	},
{ 0,	LBRNCH,		0x2C,		"lbge"	},
{ 0,	LBRNCH,		0x2D,		"lblt"	},
{ 0,	LBRNCH,		0x2E,		"lbgt"	},
{ 0,	LBRNCH,		0x2F,		"lble"	},
{ 0,	SBRNCH,		0x16,		"lbra"	},
{ 0,	SBRNCH,		0x17,		"lbsr"	},

/* simulated 6800 instructions */
{ 0,	NOARG,		0x1CFE,		"clc"	},	/* ANDCC #$FE */
{ 0,	NOARG,		0x1CEF,		"cli"	},	/* ANDCC #$EF */
{ 0,	NOARG,		0x1CFD,		"clv"	},	/* ANDCC #$FD */
{ 0,	XOP,		0xAC,		"cpx"	},	/* CMPX */
{ 0,	NOARG,		0x327F,		"des"	},	/* LEAS -1,S */
{ 0,	NOARG,		0x301F,		"dex"	},	/* LEAX -1,X */
{ 0,	NOARG,		0x3261,		"ins"	},	/* LEAS 1,X */
{ 0,	NOARG,		0x3001,		"inx"	},	/* LEAX 1,X */
{ 0,	XOP,		0xA6,		"ldaa"	},	/* LDA */
{ 0,	XOP,		0xE6,		"ldab"	},	/* LDB */
{ 0,	XOP,		0xAA,		"oraa"	},	/* ORA */
{ 0,	XOP,		0xEA,		"orab"	},	/* ORB */
{ 0,	NOARG,		0x3402,		"psha"	},	/* PSHS A */
{ 0,	NOARG,		0x3404,		"pshb"	},	/* PSHS B */
{ 0,	NOARG,		0x3502,		"pula"	},	/* PULS A */
{ 0,	NOARG,		0x3504,		"pulb"	},	/* PULS B */
{ 0,	NOARG,		0x1A01,		"sec"	},	/* ORCC #$01 */
{ 0,	NOARG,		0x1A10,		"sei"	},	/* ORCC #$10 */
{ 0,	NOARG,		0x1A02,		"sev"	},	/* ORCC #$02 */
{ 0,	XOP,		0xA7,		"staa"	},	/* STA */
{ 0,	XOP,		0xE7,		"stab"	},	/* STB */
{ 0,	NOARG,		0x1F8A,		"tap"	},	/* TFR A,CC */
{ 0,	NOARG,		0x1FA8,		"tpa"	},	/* TFR CC,A */
{ 0,	NOARG,		0x1F41,		"tsx"	},	/* TFR S,X */
{ 0,	NOARG,		0x1F14,		"txs"	},	/* TFR X,S */
{ 0,	NOARG,		0x3CFF,		"wai"	},	/* CWAI #$FF */
{ 0,	PUSHB_NOARG,	0xABE0,		"aba"	},	/* PSHS B; ADDA ,S+ */
{ 0,	PUSHB_NOARG,	0xA1E0,		"cba"	},	/* PSHS B; CMPA ,S+ */
{ 0,	PUSHB_NOARG,	0xA0E0,		"sba"	},	/* PSHS B; SUBA ,S+ */
{ 0,	NOARG_TSTA,	0x1F89,		"tab"	},	/* TFR A,B; TSTA */
{ 0,	NOARG_TSTA,	0x1F98,		"tba"	},	/* TFR B,A; TSTA */

/* simulated 6801 instructions */
	/* LSRD */
	/* PSHX - 3410 */
{ 0,	NOARG,		0x3410,		"pshx"	},	/* PSHS X */
{ 0,	NOARG,		0x3510,		"pulx"	},	/* PULS X */
	/* LDAD */
	/* STAD */

/* convenience instructions */
	/* BEC */
	/* LBEC */
	/* CLF - 1cbf */
	/* CLZ */
	/* SEF - 1a40 */
	/* SEZ */
