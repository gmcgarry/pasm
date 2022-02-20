/*-
 * Copyright (c) 2021 Gregory McGarry <g.mcgarry@ieee.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* 
 * - 16-bit opcodes; 1-4 words per instruction
 * - 51 instructions with three encoding formats, seven address modes
 *	- immediate
 *	- register
 *	- absolute (aka direct)
 *	- indirect
 *	- indirect, auto-increment
 *	- indexed
 *	- pc-relative
 * - additional instructions for expanded address range
 * - instructions operate on byte or word data
 */

/*
 * Some constants are encoded in S/As using SR/CG
 */
#define VAL4	0x0220
#define VAL8	0x0230
#define VAL0	0x0300
#define VAL1	0x0310
#define VAL2	0x0320
#define VALN1	0x0330

/* compatibility with ASM430 (CCS) */
#ifdef COMPAT_CCS
{ 0,	PSEUDOOP_CDECLS,	0,		".cdecls"	},
{ 0,	PSEUDOOP_SECT,		0,		".sect"		},
{ 0,	PSEUDOOP_DATA,		WORDSIZE,	".short"	},
{ 0,	PSEUDOOP_EXTERN,	0,		".def"		},
{ 0,	PSEUDOOP_RETAIN,	0,		".retain"	},
{ 0,	PSEUDOOP_RETAIN,	1,		".retainrefs"	},
{ 0,	PSEUDOOP_USECT,		1,		".usect"	},
#endif

#ifdef COMPAT_NAKEN
{ 0,	'=',			0,		"equ"		},
{ 0,	PSEUDOOP_DATA,		1,		".db"		},
{ 0,	PSEUDOOP_DATA,		2,		".dw"		},
{ 0,	DOT,			0,		"$"		},
#endif

/* registers */
{ 0,	REG,			0,		"R0"		},	/* PC */
{ 0,	REG,			1,		"R1"		},	/* SP */
{ 0,	REG,			2,		"R2"		},	/* SR/CG1 */
{ 0,	REG,			3,		"R3"		},	/* CG2 */
{ 0,	REG,			4,		"R4"		},
{ 0,	REG,			5,		"R5"		},
{ 0,	REG,			6,		"R6"		},
{ 0,	REG,			7,		"R7"		},
{ 0,	REG,			8,		"R8"		},
{ 0,	REG,			9,		"R9"		},
{ 0,	REG,			10,		"R10"		},
{ 0,	REG,			11,		"R11"		},
{ 0,	REG,			12,		"R12"		},
{ 0,	REG,			13,		"R13"		},
{ 0,	REG,			14,		"R14"		},
{ 0,	REG,			15,		"R15"		},

{ 0,	REG,			0,		"PC"		},
{ 0,	REG,			1,		"SP"		},
{ 0,	REG,			2,		"SR"		},
{ 0,	REG,			3,		"CG"		},

{ 0,	DATASIZE,		0x0040,		".B"		},
{ 0,	DATASIZE,		0x0000,		".W"		},

#if 0
/* special function registers */
{ 0,	SFR,			0x00,		"IE1"		},	/* interrupt enable */
{ 0,	SFR,			0x01,		"IE2"		},
{ 0,	SFR,			0x02,		"IFG1"		},	/* interrupt flags */
{ 0,	SFR,			0x03,		"IFG2"		},

{ 0,	SFR,			0x21,		"P1OUT"		},
{ 0,	SFR,			0x22,		"P1DIR"		},
{ 0,	SFR,			0x29,		"P2OUT"		},
{ 0,	SFR,			0x2A,		"P2DIR"		},

{ 0,	SFR,			0x5A00,		"WDTPW"		},
{ 0,	SFR,			0x0080,		"WDTHOLD"	},
{ 0,	SFR,			0x0120,		"WDTCTL"	},
#endif

/* single operands - destination only */
/* O O O O O O O O | B/W | As As | D D D D */
{ 0,	RM,		0x6000|VAL0,	"ADC"		},	/* alias */ /* ADDC #0, dst */
{ 0,	RM,		0x1280,		"CALL"		},
{ 0,	RM,		0x4000|VAL0,	"CLR"		},	/* alias */ /* MOV #0, dst */
{ 0,	RM,		0xA000|VAL0,	"DADC"		},	/* alias */ /* DADD #0, dst */
{ 0,	RM,		0x8000|VAL1,	"DEC"		},	/* alias */ /* SUB #1, dst */
{ 0,	RM,		0x8000|VAL2,	"DECD"		},	/* alias */ /* SUB #2, dst */ /* double decrement */
{ 0,	RM,		0x5000|VAL1,	"INC"		},	/* alias */ /* ADD #1, dst */
{ 0,	RM,		0x5000|VAL2,	"INCD"		},	/* alias */ /* ADD #2, dst */ /* double increment */
{ 0,	RM,		0xE000|VALN1,	"INV"		},	/* alias */ /* XOR #0FFFFh, dst */
{ 0,	RM,		0x4130,		"POP"		},	/* alias */ /* MOV @SP+, dst */
{ 0,	RM,		0x1200,		"PUSH"		},
{ 0,	RM2,		0x5000,		"RLA"		}, 	/* alias */ /* ADD dst, dst */
{ 0,	RM2,		0x6000,		"RLC"		}, 	/* alias */ /* ADDC dst, dst */
{ 0,	RM,		0x1100,		"RRA"		}, 
{ 0,	RM,		0x1000,		"RRC"		},
{ 0,	RM,		0x7000|VAL0,	"SBC"		},	/* alias */ /* SUBC #0, dst */
{ 0,	RM,		0x1080,		"SWPB"		}, 
{ 0,	RM,		0x1180,		"SXT"		}, 
{ 0,	RM,		0x9000|VAL0,	"TST"		}, 	/* alias */ /* CMP #0, dst */

/* dual operands - source, destination */
/* O O O O | S S S S | Ad | B/W | As As | D D D D */
{ 0,	RMW,		0x5000,		"ADD"		},
{ 0,	RMW,		0x6000,		"ADDC"		},
{ 0,	RMW,		0xF000,		"AND"		},
{ 0,	RMW,		0xC000,		"BIC"		},
{ 0,	RMW,		0xD000,		"BIS"		},
{ 0,	RMW,		0xB000,		"BIT"		},
{ 0,	RMW,		0x9000,		"CMP"		},
{ 0,	RMW,		0xA000,		"DADD"		},	/* decimal add */
{ 0,	RMW,		0x4000,		"MOV"		},
{ 0,	RMW,		0x8000,		"SUB"		},
{ 0,	RMW,		0x7000,		"SUBC"		},
{ 0,	RMW,		0x7000,		"SBB"		},	/* alias for previous */
{ 0,	RMW,		0xE000,		"XOR"		},

/* branches/jumps */
/* O O O O | C C C | 10-bit offset */
{ 0,	RBRANCH,	0x2400,		"JEQ"		},
{ 0,	RBRANCH,	0x2400,		"JZ"		}, 	/* alias for previous */
{ 0,	RBRANCH,	0x2000,		"JNE"		},
{ 0,	RBRANCH,	0x2000,		"JNZ"		},	/* alias for previous */

{ 0,	RBRANCH,	0x2C00,		"JC"		},
{ 0,	RBRANCH,	0x2C00,		"JHS"		},	/* alias for previous */
{ 0,	RBRANCH,	0x2800,		"JNC"		},
{ 0,	RBRANCH,	0x2800,		"JLO"		},	/* alias for previous */

{ 0,	RBRANCH,	0x3000,		"JN"		},
{ 0,	RBRANCH,	0x3400,		"JGE"		},

{ 0,	RBRANCH,	0x3800,		"JL"		},
{ 0,	RBRANCH,	0x3C00,		"JMP"		},

{ 0,	BRANCH,		0x4000,		"BR"		},	/* alias */ /* MOV src, PC */
{ 0,	BRANCH,		0x4000,		"BRANCH"	},	/* alias for previous */

/* implicit */
{ 0,	IMPL,		0x4130,		"RET"		}, 	/* alias */ /* MOV @SP+, PC */
{ 0,	IMPL,		0x1300,		"RETI"		}, 
{ 0,	IMPL,		0xC002|VAL1,	"CLRC"		},	/* alias */ /* BIC #1, SR */
{ 0,	IMPL,		0xC002|VAL4,	"CLRN"		},	/* alias */ /* BIC #4, SR */
{ 0,	IMPL,		0xC002|VAL2,	"CLRZ"		},	/* alias */ /* BIC #2, SR */
{ 0,	IMPL,		0xC002|VAL8,	"DINT"		},	/* alias */ /* BIC #8, SR */
{ 0,	IMPL,		0xD002|VAL8,	"EINT"		},	/* alias */ /* BIS #8, SR */
{ 0,	IMPL,		0x4003|VAL0,	"NOP"		},	/* alias */ /* MOV #0, R3 */
{ 0,	IMPL,		0xD002|VAL1,	"SETC"		},	/* alias */ /* BIS #1, SR */
{ 0,	IMPL,		0xD002|VAL4,	"SETN"		},	/* alias */ /* BIS #4, SR */
{ 0,	IMPL,		0xD002|VAL2,	"SETZ"		},	/* alias */ /* BIS #2, SR */
