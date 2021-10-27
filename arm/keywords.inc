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

#define THUMB	(MODE_THUMB<<17 | 0x10000)
#define ARM	(MODE_ARM<<17 | 0x10000)

{ 0,	PSEUDOOP_CPU,		0,		".cpu"	},
{ 0,	PSEUDOOP_ARCH,		0,		".arch"	},
{ 0,	PSEUDOOP_EABIATTR,	0,		".eabi_attribute"	},
{ 0,	PSEUDOOP_SYNTAX,	0,		".syntax"	},
{ 0,	PSEUDOOP_FPU,		0,		".fpu"	},
{ 0,	PSEUDOOP_MODE,		MODE_ARM,	".arm"	},
{ 0,	PSEUDOOP_MODE,		MODE_THUMB,	".thumb"	},
{ 0,	PSEUDOOP_CODE,		0,		".code"	},
{ 0,	PSEUDOOP_THUMBFUNC,	0,		".thumb_func"	},
#if notyet
{ 0,	PSEUDOOP_FUNC,		0,		".fnstart" },
{ 0,	PSEUDOOP_FUNC,		1,		".fnend" },
{ 0,	PSEUDOOP_POOL,		0,		".pool" },
{ 0,	PSEUDOOP_CANTUNWIND,	0,		".cantunwind"	},
#endif

{ 0,	REG,			0,		"R0"	},
{ 0,	REG,			1,		"R1"	},
{ 0,	REG,			2,		"R2"	},
{ 0,	REG,			3,		"R3"	},
{ 0,	REG,			4,		"R4"	},
{ 0,	REG,			5,		"R5"	},
{ 0,	REG,			6,		"R6"	},
{ 0,	REG,			7,		"R7"	},
{ 0,	ARM|REG,		8,		"R8"	},	/* not thumb */
{ 0,	ARM|REG,		9,		"R9"	},	/* not thumb */
{ 0,	ARM|REG,		10,		"R10"	},	/* not thumb */
{ 0,	ARM|REG,		11,		"R11"	},	/* not thumb */
{ 0,	ARM|REG,		11,		"FP"	},	/* not thumb */
{ 0,	ARM|REG,		12,		"R12"	},	/* not thumb */
{ 0,	ARM|REG,		12,		"IP"	},	/* not thumb */
{ 0,	REG,			13,		"R13"	},
{ 0,	REG,			13,		"SP"	},
{ 0,	REG,			14,		"R14"	},
{ 0,	REG,			14,		"LR"	},
{ 0,	REG,			15,		"R15"	},
{ 0,	REG,			15,		"PC"	},

{ 0,	ARM|COND,		0x00000000,	".EQ"	},
{ 0,	ARM|COND,		0x10000000,	".NE"	},
{ 0,	ARM|COND,		0x20000000,	".CS"	},
{ 0,	ARM|COND,		0x20000000,	".HS"	},
{ 0,	ARM|COND,		0x30000000,	".CC"	},
{ 0,	ARM|COND,		0x30000000,	".LO"	},
{ 0,	ARM|COND,		0x40000000,	".MI"	},
{ 0,	ARM|COND,		0x50000000,	".PL"	},
{ 0,	ARM|COND,		0x60000000,	".VS"	},
{ 0,	ARM|COND,		0x70000000,	".VC"	},
{ 0,	ARM|COND,		0x80000000,	".HI"	},
{ 0,	ARM|COND,		0x90000000,	".LS"	},
{ 0,	ARM|COND,		0xA0000000,	".GE"	},
{ 0,	ARM|COND,		0xB0000000,	".LT"	},
{ 0,	ARM|COND,		0xC0000000,	".GT"	},
{ 0,	ARM|COND,		0xD0000000,	".LE"	},
{ 0,	ARM|COND,		0xE0000000,	".AL"	},
{ 0,	ARM|COND,		0xF0000000,	".NV"	},

{ 0,	ARM|LINK,		0x01000000,	".L"	},
{ 0,	EXCHANGE,		1,		".X"	},

#if 0
{ 0,	ARM|BRANCH,		0xEA000000,	"B"	},
#endif
{ 0,	ARM|DATA1,		0x0A000000,	"B"	},

#if 0
{ 0,	BX,			0xEA000000,	"BX"	},
{ 0,	BX,			0xEB000000,	"BLX"	},
#endif

#ifdef COMPAT_GAS
{ 0,	ARM|BRANCH,		0x0A000000,	"BEQ"	},
{ 0,	ARM|BRANCH,		0x1A000000,	"BNE"	},
{ 0,	ARM|BRANCH,		0x2A000000,	"BCS"	},
{ 0,	ARM|BRANCH,		0x2A000000,	"BHS"	},
{ 0,	ARM|BRANCH,		0x3A000000,	"BCC"	},
{ 0,	ARM|BRANCH,		0x3A000000,	"BLO"	},
{ 0,	ARM|BRANCH,		0x4A000000,	"BMI"	},
{ 0,	ARM|BRANCH,		0x5A000000,	"BPL"	},
{ 0,	ARM|BRANCH,		0x6A000000,	"BVS"	},
{ 0,	ARM|BRANCH,		0x7A000000,	"BVC"	},
{ 0,	ARM|BRANCH,		0x8A000000,	"BHI"	},
{ 0,	ARM|BRANCH,		0x9A000000,	"BLS"	},
{ 0,	ARM|BRANCH,		0xAA000000,	"BGE"	},
{ 0,	ARM|BRANCH,		0xBA000000,	"BLT"	},
{ 0,	ARM|BRANCH,		0xCA000000,	"BGT"	},
{ 0,	ARM|BRANCH,		0xDA000000,	"BLE"	},
{ 0,	ARM|BRANCH,		0xEA000000,	"BAL"	},
{ 0,	ARM|BRANCH,		0xFA000000,	"BNV"	},

{ 0,	ARM|BRANCH,		0x0B000000,	"BLEQ"	},
{ 0,	ARM|BRANCH,		0x1B000000,	"BLNE"	},
{ 0,	ARM|BRANCH,		0x2B000000,	"BLCS"	},
{ 0,	ARM|BRANCH,		0x2B000000,	"BLHS"	},
{ 0,	ARM|BRANCH,		0x3B000000,	"BLCC"	},
{ 0,	ARM|BRANCH,		0x3B000000,	"BLLO"	},
{ 0,	ARM|BRANCH,		0x4B000000,	"BLMI"	},
{ 0,	ARM|BRANCH,		0x5B000000,	"BLPL"	},
{ 0,	ARM|BRANCH,		0x6B000000,	"BLVS"	},
{ 0,	ARM|BRANCH,		0x7B000000,	"BLVC"	},
{ 0,	ARM|BRANCH,		0x8B000000,	"BLHI"	},
{ 0,	ARM|BRANCH,		0x9B000000,	"BLLS"	},
{ 0,	ARM|BRANCH,		0xAB000000,	"BLGE"	},
{ 0,	ARM|BRANCH,		0xBB000000,	"BLLT"	},
{ 0,	ARM|BRANCH,		0xCB000000,	"BLGT"	},
{ 0,	ARM|BRANCH,		0xDB000000,	"BLLE"	},
{ 0,	ARM|BRANCH,		0xEB000000,	"BLAL"	},
{ 0,	ARM|BRANCH,		0xEB000000,	"BL"	},
{ 0,	ARM|BRANCH,		0xFB000000,	"BLNV"	},
#endif

{ 0,	ARM|DATA1,		ADC,		"ADC"	},
{ 0,	ARM|DATA1,		ADD,		"ADD"	},
{ 0,	ARM|DATA1,		AND,		"AND"	},
{ 0,	ARM|DATA1,		BIC,		"BIC"	},
{ 0,	ARM|DATA1,		EOR,		"EOR"	},
{ 0,	ARM|DATA1,		ORR,		"ORR"	},
{ 0,	ARM|DATA1,		RSB,		"RSB"	},
{ 0,	ARM|DATA1,		RSC,		"RSC"	},
{ 0,	ARM|DATA1,		SBC,		"SBC"	},
{ 0,	ARM|DATA1,		SUB,		"SUB"	},
{ 0,	ARM|DATA2,		MOV,		"MOV"	},
{ 0,	ARM|DATA2,		MVN,		"MVN"	},
{ 0,	ARM|DATA3,		CMN,		"CMN"	},
{ 0,	ARM|DATA3,		CMP,		"CMP"	},
{ 0,	ARM|DATA3,		TEQ,		"TEQ"	},
{ 0,	ARM|DATA3,		TST,		"TST"	},

#ifdef COMPAT_GAS
{ 0,	ARM|DATA1,		0x00100000|ADC,	"ADCS"	},
{ 0,	ARM|DATA1,		0x00100000|ADD,	"ADDS"	},
{ 0,	ARM|DATA1,		0x00100000|AND,	"ANDS"	},
{ 0,	ARM|DATA1,		0x00100000|BIC,	"BICS"	},
{ 0,	ARM|DATA1,		0x00100000|EOR,	"EORS"	},
{ 0,	ARM|DATA1,		0x00100000|ORR,	"ORRS"	},
{ 0,	ARM|DATA1,		0x00100000|RSB,	"RSBS"	},
{ 0,	ARM|DATA1,		0x00100000|RSC,	"RSCS"	},
{ 0,	ARM|DATA1,		0x00100000|SBC,	"SBCS"	},
{ 0,	ARM|DATA1,		0x00100000|SUB,	"SUBS"	},
{ 0,	ARM|DATA2,		0x00100000|MOV,	"MOVS"	},
{ 0,	ARM|DATA2,		0x00100000|MVN,	"MVNS"	},
{ 0,	ARM|DATA3,		0x00100000|CMN,	"CMNS"	},
{ 0,	ARM|DATA3,		0x00100000|CMP,	"CMPS"	},
{ 0,	ARM|DATA3,		0x00100000|TEQ,	"TEQS"	},
{ 0,	ARM|DATA3,		0x00100000|TST,	"TSTS"	},
#endif

{ 0,	ARM|DATA2,		0xB0000000|MOV,	"MOVLT"	},
{ 0,	ARM|DATA2,		0xA0000000|MOV,	"MOVGE"	},
{ 0,	ARM|DATA2,		0xC0000000|MOV,	"MOVGT"	},

{ 0,	ARM|SET,		0x00100000,	".S"	},	/* thumb? */
{ 0,	ARM|PEE,		0x0010F000,	".P"	},

{ 0,	ARM|SHIFT,		0x00000000,	"LSL"	},
{ 0,	ARM|SHIFT,		0x00000000,	"ASL"	},
{ 0,	ARM|SHIFT,		0x00000020,	"LSR"	},
{ 0,	ARM|SHIFT,		0x00000040,	"ASR"	},
{ 0,	ARM|SHIFT,		0x00000060,	"ROR"	},

{ 0,	ARM|RRX,		0x00000060,	"RRX"	},

{ 0,	ARM|SDT,		0x04100000,	"LDR"	},
{ 0,	ARM|SDT,		0x04000000,	"STR"	},

{ 0,	ARM|BYTE,		0x00400000,	".B"	},
{ 0,	ARM|HALF,		0x004000B0,	".H"	}, /* XXXGJM need to clear some bits */
{ 0,	ARM|TRANS,		0x00200000,	".T"	},
#if 0
{ 0,	ARM|DOUBLE,		0x000000F0,	".D"	}, /* XXXGJM different for LDR and STR */
#endif

#if 1
{ 0,	ARM|SDT,		0x04500000,	"LDRB"	},
{ 0,	ARM|SDT,		0x04400000,	"STRB"	},
{ 0,	ARM|SDT,		0x005000B0,	"LDRH"	}, /* XXXGJM needs special handling */
{ 0,	ARM|SDT,		0x004000B0,	"STRH"	}, /* XXXGJM needs special handling */
{ 0,	ARM|SDT,		0x000000D0,	"LDRD"	}, /* ARMv5TE */
{ 0,	ARM|SDT,		0x000000F0,	"STRD"	}, /* ARMv5TE */
#endif

{ 0,	ARM|BDT,		0x09100000,	"LDMDB"	},
{ 0,	ARM|BDT,		0x08100000,	"LDMDA"	},
{ 0,	ARM|BDT,		0x09900000,	"LDMIB"	},
{ 0,	ARM|BDT,		0x08900000,	"LDMIA"	},
{ 0,	ARM|BDT,		0x08900000,	"LDMFD"	},
{ 0,	ARM|BDT,		0x08100000,	"LDMFA"	},
{ 0,	ARM|BDT,		0x09900000,	"LDMED"	},
{ 0,	ARM|BDT,		0x09100000,	"LDMEA"	},
{ 0,	ARM|BDT,		0x09000000,	"STMDB"	},
{ 0,	ARM|BDT,		0x08000000,	"STMDA"	},
{ 0,	ARM|BDT,		0x09800000,	"STMIB"	},
{ 0,	ARM|BDT,		0x08800000,	"STMIA"	},
{ 0,	ARM|BDT,		0x09000000,	"STMFD"	},
{ 0,	ARM|BDT,		0x09800000,	"STMFA"	},
{ 0,	ARM|BDT,		0x08000000,	"STMED"	},
{ 0,	ARM|BDT,		0x08800000,	"STMEA"	},

{ 0,	ARM|SWI,		0x0F000000,	"SWI"	},
{ 0,	ARM|SWI,		0x0F000000,	"SVC"	},

{ 0,	ARM|ADR,		0x00000000,	"ADR"	},

{ 0,	ARM|MUL,		0x00000090,	"MUL"	},
{ 0,	ARM|MLA,		0x00200090,	"MLA"	},

/* thumb instructions */
{ 0,	THUMB|STACK,		0xB400,		"PUSH"	},	/* thumb */
{ 0, 	THUMB|STACK,		0xBC00,		"POP"	},	/* thumb */
