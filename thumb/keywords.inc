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

{ 0,	PSEUDOOP_CPU,		0,		".cpu"		},
{ 0,	PSEUDOOP_ARCH,		0,		".arch"		},
{ 0,	PSEUDOOP_FPU,		0,		".fpu"		},
{ 0,	PSEUDOOP_MODE,		0,		".thumb"	},	/* UAL syntax */
{ 0,	PSEUDOOP_MODE,		0,		".thumbx"	},	/* UAL syntax */
{ 0,	PSEUDOOP_MODE,		0,		".code16"	},	/* pre-UAL syntax */
{ 0,	PSEUDOOP_THUMBFUNC,	0,		".thumb_func"	},
#if notyet
{ 0,	PSEUDOOP_EABIATTR,	0,		".eabi_attribute"	},
{ 0,	PSEUDOOP_SYNTAX,	0,		".syntax"	},
{ 0,	PSEUDOOP_CODE,		0,		".code"		},
{ 0,	PSEUDOOP_FUNC,		0,		".fnstart"	},
{ 0,	PSEUDOOP_FUNC,		1,		".fnend"	},
{ 0,	PSEUDOOP_POOL,		0,		".pool"		},
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
{ 0,	REG,			8,		"R8"	},
{ 0,	REGHI,			9,		"R9"	},
{ 0,	REGHI,			10,		"R10"	},
{ 0,	REGHI,			11,		"R11"	},
{ 0,	REGHI,			12,		"R12"	},
{ 0,	SP,			13,		"SP"	},
{ 0,	LR,			14,		"LR"	},
{ 0,	PC,			15,		"PC"	},

{ 0,	SHIFT,			0x0000,		"LSL"	},	/* register or immediate */
{ 0,	SHIFT,			0x0800,		"LSR"	},	/* register or immediate */
{ 0,	SHIFT,			0x1000,		"ASR"	},	/* register or immediate */
{ 0,	ADD,			0x1800,		"ADD"	},	/* register or immediate */
{ 0,	ADD,			0x1a00,		"SUB"	},	/* register or immediate */

{ 0,	MOV,			0,		"MOV"	},	/* register or immediate */
{ 0,	CMP,			0,		"CMP"	},	/* register or immediate */

{ 0,	DATA1,			0x4140,		"ADC"	},	/* add with carry */
{ 0,	DATA1,			0x4000,		"AND"	},	/* logical and */
{ 0,	DATA1,			0x4380,		"BIC"	},	/* bit clear */
{ 0,	DATA1,			0x4040,		"EOR"	},	/* exclusive or */
{ 0,	DATA1,			0x4300,		"ORR"	},	/* logical or */
{ 0,	DATA1,			0x41c0,		"ROR"	},	/* rotate right */
{ 0,	DATA1,			0x4240,		"RSB"	},	/* reverse subtract */
{ 0,	DATA1,			0x4180,		"SBC"	},	/* subtract with carry */
{ 0,	DATA1,			0x43c0,		"MVN"	},	/* negate */
{ 0,	DATA1,			0x42c0,		"CMN"	},	/* compare negative */
{ 0,	DATA1,			0x4200,		"TST"	},	/* test bits */
{ 0,	DATA1,			0x4340,		"MUL"	},	/* multiply */

{ 0,	BREXCH,			0x4700,		"BX"	},	/* only available in 5T? */
{ 0,	BREXCH,			0x4780,		"BLX"	},	/* only available in 5T? */

{ 0,	UBRANCH,		0xE000,		"B"	},
{ 0,	LBRANCH,		0,		"BL"	},

{ 0,	BRANCH,			0xD000,		"BEQ"	},
{ 0,	BRANCH,			0xD100,		"BNE"	},
{ 0,	BRANCH,			0xD200,		"BCS"	},
{ 0,	BRANCH,			0xD300,		"BCC"	},
{ 0,	BRANCH,			0xD400,		"BMI"	},
{ 0,	BRANCH,			0xD500,		"BPL"	},
{ 0,	BRANCH,			0xD6A0,		"BVS"	},
{ 0,	BRANCH,			0xD700,		"BVC"	},
{ 0,	BRANCH,			0xD800,		"BHI"	},
{ 0,	BRANCH,			0xD900,		"BLS"	},	/* less or same */
{ 0,	BRANCH,			0xDA00,		"BGE"	},	/* greater or equal */
{ 0,	BRANCH,			0xDB00,		"BLT"	},	/* less than */
{ 0,	BRANCH,			0xDC00,		"BGT"	},	/* greater than */
{ 0,	BRANCH,			0xDD00,		"BLE"	},	/* less or equal */

{ 0,	LDST,			0,		"STR"	},
{ 0,	LDST,			1,		"LDR"	},
{ 0,	LDSTB,			0,		"STRB"	},
{ 0,	LDSTB,			1,		"LDRB"	},
{ 0,	LDSTH,			0,		"STRH"	},
{ 0,	LDSTH,			1,		"LDRH"	},
{ 0,	LDRS,			0,		"LDRSB"	},
{ 0,	LDRS,			1,		"LDRSH"	},

/* block data transfers */
{ 0,	STACK,			0xB400,		"PUSH"	},
{ 0,	STACK,			0xBC00,		"POP"	},
{ 0,	LDM,			0xC800,		"LDMIA"	},	/* load multiple, increment after */
{ 0,	LDM,			0xC000,		"STMIA"	},	/* store multiple, increment after */

#if 0
{ 0,	BDT,			0xE9100000,	"LDMDB"	},	/* aka POP */ /* thumb2 */
{ 0,	BDT,			0xE9000000,	"STMDB"	},	/* aka PUSH */ /* thumb2 */
#endif

{ 0,	ADR,			0xA000,		"ADR"	},

{ 0,	SWI,			0xDF00,		"SWI"	},
{ 0,	SVC,			0xDF00,		"SVC"	},

