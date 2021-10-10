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

#define XXX 0xff

/* for compatibility */
{ 0,	'=',		0,		"equ"	},
{ 0,	PSEUDOOP_STM8,	0,		".stm8"	},
{ 0,	DOT,		0,		"$"	},
{ 0,	PSEUDOOP_SEGMENT, 0,		"segment"	},

/* registers */
{ 0,	REG,		A,		"A"	}, /* DONE */
{ 0,	REG,		X,		"X"	}, /* DONE */
{ 0,	REG,		Y,		"Y"	}, /* DONE */
{ 0,	REG,		XL,		"XL"	}, /* DONE */
{ 0,	REG,		YL,		"YL"	}, /* DONE */
{ 0,	REG,		SP,		"SP"	}, /* DONE */

/* Bit test and branch */
{ 0,	BBRANCH,	0x9000,		"btjt"	}, /* DONE */
{ 0,	BBRANCH,	0x9001,		"btjf"	}, /* DONE */

/* Bit manipulation */
{ 0,	BIT,		0x7210,		"bset"	}, /* DONE */ /* bit set */
{ 0,	BIT,		0x7211,		"bres"	}, /* DONE */ /* bit reset */
{ 0,	BIT,		0x9010,		"bcpl"	}, /* DONE */ /* bit complement */
{ 0,	BIT,		0x9011,		"bccm"	}, /* DONE */ /* copy carry bit to memory */

/* Branches */
{ 0,	BRANCH,		0x20,		"jra"	}, /* always */
{ 0,	BRANCH,		0x20,		"jrt"	}, /* true */
{ 0,	BRANCH,		0x21,		"jrf"	}, /* false */
{ 0,	BRANCH,		0x22,		"jrugt"	}, /* unsigned greater-than */
{ 0,	BRANCH,		0x23,		"jrule"	}, /* unsigned less-than-equal */
{ 0,	BRANCH,		0x24,		"jruge"	}, /* unsigned greater-than-equal */
{ 0,	BRANCH,		0x24,		"jrnc"	}, /* no carry */
{ 0,	BRANCH,		0x25,		"jrult"	}, /* unsigned less-than */
{ 0,	BRANCH,		0x25,		"jrc"	}, /* carry */
{ 0,	BRANCH,		0x26,		"jrne"	}, /* not equal */
{ 0,	BRANCH,		0x27,		"jreq"	}, /* equal */
{ 0,	BRANCH,		0x28,		"jrnv"	}, /* not overflow */
{ 0,	BRANCH,		0x29,		"jrv"	}, /* overflow */
{ 0,	BRANCH,		0x2a,		"jrpl"	}, /* positive/plus */
{ 0,	BRANCH,		0x2b,		"jrmi"	}, /* negative/minus */
{ 0,	BRANCH,		0x2c,		"jrsgt"	}, /* signed greater-than */ /* XXX swapped with 0x2e? */
{ 0,	BRANCH,		0x2d,		"jrsle"	}, /* signed less-than-equal */
{ 0,	BRANCH,		0x2e,		"jrsge"	}, /* signed greater-than-equal */ /* XXX swapped with 0x2c? */
{ 0,	BRANCH,		0x2f,		"jrslt"	}, /* signed less-than */
{ 0,	BRANCH,		0x8D,		"callf"	}, /* call far */

{ 0,	BRANCH,		0x9028,		"bhcc"	}, /* not half-carry */ /* PREFIX */
{ 0,	BRANCH,		0x9029,		"bhcs"	}, /* half-carry */ /* PREFIX */
{ 0,	BRANCH,		0x902c,		"jrnm"	}, /* not interrupt mask */ /* PREFIX */
{ 0,	BRANCH,		0x902d,		"jrm"	}, /* interrupt mask */ /* PREFIX */
{ 0,	BRANCH,		0x902e,		"jril"	}, /* interrupt low */ /* PREFIX */
{ 0,	BRANCH,		0x902f,		"jrih"	}, /* interrupt high */ /* PREFIX */

/* unconditional branches */
{ 0,	RM,		0xac,		"jpf"	}, /* DONE */ /* SAME OPCODE */ /* jump far */
{ 0,	BRANCH,		0xcd,		"call"	}, /* YES */ 
{ 0,	BRANCH,		0x0c,		"jp"	}, /* YES */
{ 0,	BRANCH,		0xad,		"callr"	}, /* DONE */ /* SAME OPCODE */

/* Read modify write on anything but registers */
{ 0,	RMR,		0x30,		"neg"	}, /* YES */
{ 0,	RMR,		XXX,		"negw"	}, /* YES */
{ 0,	RMR,		0x33,		"cpl"	}, /* YES */
{ 0,	RMR,		0x33,		"cplw"	}, /* YES */
{ 0,	RMR,		0x34,		"srl"	}, /* YES */
{ 0,	RMR,		0x34,		"srlw"	}, /* YES */
{ 0,	RMR,		0x36,		"rrc"	}, /* YES */
{ 0,	RMR,		0x36,		"rrcw"	}, /* YES */
{ 0,	RMR,		0x36,		"sra"	}, /* YES */
{ 0,	RMR,		0x36,		"sraw"	}, /* YES */
{ 0,	RMR,		0x38,		"sll"	}, /* YES */
{ 0,	RMR,		0x38,		"sla"	}, /* YES */ /* alias */
{ 0,	RMR,		0x38,		"sllw"	}, /* YES */
{ 0,	RMR,		0x38,		"slaw"	}, /* YES */ /* alias */
{ 0,	RMR,		0x39,		"rlc"	}, /* YES */
{ 0,	RMR,		XXX,		"rlw"	}, /* YES */
{ 0,	RMR,		0x3a,		"dec"	}, /* YES */
{ 0,	RMR,		XXX,		"decw"	}, /* YES */
{ 0,	RMR,		0x3c,		"inc"	}, /* YES */
{ 0,	RMR,		XXX,		"incw"	}, /* YES */
{ 0,	RMR,		0x3d,		"cp"	}, /* YES */
{ 0,	RMR,		XXX,		"cpw"	}, /* YES */
{ 0,	RMR,		0x3f,		"clr"	}, /* YES */
{ 0,	RMR,		XXX,		"clrw"	}, /* YES */

/* load/store/transfer */
{ 0,	MOV,		0x00,		"mov"	}, /* YES */
{ 0,	MOV,		0x01,		"swap"	}, /* YES */ /* swap low and high nibbles */
{ 0,	TWOREG,		0x5e,		"swapw"	}, /* YES */ /* swap low and high bytes */

{ 0,	LD,		0x00,		"ld"	}, /* YES */
{ 0,	LDF,		0x00,		"ldf"	}, /* YES */
{ 0,	LDW,		0x00,		"ldw"	}, /* YES */

{ 0,	TWOREG,		0x41,		"exg"	}, /* YES */
{ 0,	TWOREG,		0x51,		"exgw"	}, /* YES */

/* implied stuff */
{ 0,	NOARG,		0x80,		"iret"	}, /* DONE */ /* SAME OPCODE!! */
{ 0,	NOARG,		0x81,		"ret"	}, /* DONE */ /* SAME OPCODE!! */
{ 0,	BRANCH,		0x82,		"int"	}, /* DONE */ /* SAME OPCODE!! */
{ 0,	NOARG,		0x87,		"retf"	}, /* DONE */
{ 0,	NOARG,		0x83,		"trap"	}, /* DONE */ /* SAME OPCODE!! */
{ 0,	NOARG,		0x8C,		"ccf"	}, /* DONE */ /* complement carry flag */
{ 0,	NOARG,		0x98,		"rcf"	}, /* DONE */ /* SAME OPCODE!! */
{ 0,	NOARG,		0x99,		"scf"	}, /* DONE */ /* SAME OPCODE!! */
{ 0,	NOARG,		0x9a,		"rim"	}, /* DONE */ /* SAME OPCODE!! */
{ 0,	NOARG,		0x9b,		"sim"	}, /* DONE */ /* SAME OPCODE!! */
{ 0,	NOARG,		0x9c,		"rvf"	}, /* DONE */ /* SAME OPCODE!! */
{ 0,	NOARG,		0x9d,		"nop"	}, /* DONE */ /* SAME OPCODE!! */
{ 0,	NOARG,		0x9f,		"txa"	},

/* Register memory. Warning. Some imediate opcodes excluded in parser actions. */
{ 0,	RM,		0xa0,		"sub"	}, /* YES */
{ 0,	RM,		XXX,		"subw"	}, /* YES */
{ 0,	RM,		0xa1,		"cmp"	},
{ 0,	RM,		0xa2,		"sbc"	}, /* YES */
{ 0,	RM,		0xa3,		"cpx"	}, /* YES */
{ 0,	RM,		0xa4,		"and"	}, /* YES */
{ 0,	RM,		0xa5,		"bcp"	}, /* YES */
{ 0,	RM,		0xa6,		"lda"	}, /* YES */
{ 0,	RM,		0xa7,		"sta"	},
{ 0,	RM,		0xa8,		"xor"	}, /* YES */
{ 0,	RM,		0xa9,		"adc"	}, /* YES */
{ 0,	RM,		0xaa,		"or"	}, /* YES */
{ 0,	RM,		0xab,		"add"	}, /* YES */
{ 0,	RM,		XXX,		"addw"	}, /* YES */
{ 0,	RM,		0xae,		"ldx"	}, /* YES */
{ 0,	RM,		0xaf,		"stx"	},

{ 0,	TWOREG,		0x62,		"div"	}, /* YES */ /* PREFIX FOR Y */ /* div X,A */
{ 0,	TWOREG,		0x65,		"divw"	}, /* YES */ /* div X,Y */
{ 0,	TWOREG,		0x42,		"mul"	}, /* YES */ /* PREFIX FOR Y */ /* mul X,A */


/* Brain damaged concatenated opcodes for RMR on registers */
{ 0,	NOARG,		0x40,		"nega"	}, /* YES */
#ifdef MC6800
{ 0,	NOARG,		0x50,		"negb"	}, /* YES */
#endif
{ 0,	NOARG,		0x43,		"coma"	},
#ifdef MC6800
{ 0,	NOARG,		0x53,		"comb"	},
#endif
{ 0,	NOARG,		0x44,		"lsra"	},
#ifdef MC6800
{ 0,	NOARG,		0x54,		"lsrb"	},
#endif
{ 0,	NOARG,		0x46,		"rora"	},
#ifdef MC6800
{ 0,	NOARG,		0x56,		"rorb"	},
#endif
{ 0,	NOARG,		0x47,		"asra"	},
#ifdef MC6800
{ 0,	NOARG,		0x57,		"asrb"	},
#endif
{ 0,	NOARG,		0x48,		"lsla"	},
{ 0,	NOARG,		0x48,		"asla"	},	/* alias */
#ifdef MC6800
{ 0,	NOARG,		0x58,		"lslb"	},
{ 0,	NOARG,		0x58,		"aslb"	},	/* alias */
#endif
{ 0,	NOARG,		0x49,		"rola"	},
#ifdef MC6800
{ 0,	NOARG,		0x59,		"rolb"	},
#endif
{ 0,	NOARG,		0x4a,		"deca"	},
#ifdef MC6800
{ 0,	NOARG,		0x5A,		"decb"	},
#endif
{ 0,	NOARG,		0x4c,		"inca"	},
#ifdef MC6800
{ 0,	NOARG,		0x5C,		"incb"	},
#endif
{ 0,	NOARG,		0x4d,		"tnz"	}, /* YES */ /* test not zero */
{ 0,	NOARG,		0x4f,		"clra"	},
#ifdef MC6800
{ 0,	NOARG,		0x5F,		"clrb"	},
#endif
{ 0,	NOARG,		0x50,		"negx"	},
{ 0,	NOARG,		0x53,		"comx"	},
{ 0,	NOARG,		0x54,		"lsrx"	},

{ 0,	RM,		0x02,		"rlwa"	}, /* YES */  /* PREFIX FOR Y */
{ 0,	RM,		0x01,		"rrwa"	}, /* YES */  /* PREFIX FOR Y */

{ 0,	NOARG,		0x57,		"asrx"	},
{ 0,	NOARG,		0x58,		"lslx"	},
{ 0,	NOARG,		0x58,		"aslx"	},	/* alias */
{ 0,	NOARG,		0x59,		"rolx"	},
{ 0,	NOARG,		0x5a,		"decx"	},
{ 0,	NOARG,		0x5c,		"incx"	},
{ 0,	NOARG,		0x5d,		"tnzw"	}, /* YES */ /* test not zero */
{ 0,	NOARG,		0x5f,		"clrx"	},

#ifdef MC6800
{ 0,	NOARG,		0x19,		"daa"	},
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
#endif

/* stack operations */
#ifdef MC6800
{ 0,	RM,		0xEE,		"lds"	},
{ 0,	RM,		0xEF,		"sts"	},
{ 0,	NOARG,		0x34,		"des"	},
{ 0,	NOARG,		0x31,		"ins"	},
{ 0,	NOARG,		0x35,		"txs"	},
{ 0,	NOARG,		0x30,		"tsx"	},
#endif

{ 0,	RM,		0x88,		"push"	}, /* YES */
{ 0,	RM,		0x89,		"pushw"	}, /* DONE */ /* PREFIX FOR Y */
{ 0,	RM,		0x84,		"pop"	}, /* YES */
{ 0,	RM,		0x85,		"popw"	}, /* DONE */ /* PREFIX FOR Y */

{ 0,	NOARG,		0x8b,		"break"	}, /* DONE */
{ 0,	NOARG,		0x8e,		"halt"	}, /* DONE */ /* SAME OPCODE!! */
{ 0,	NOARG,		0x8f,		"wfi"	}, /* DONE */ /* SAME OPCODE!! */
{ 0,	NOARG,		0x728f,		"wfe"	}, /* DONE */ /* SAME OPCODE */ /* PREFIX */
