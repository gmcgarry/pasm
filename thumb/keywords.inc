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
 * Note: Only 16-bit opcodes are supported on all architectures.
 * (BL is the only case of fused instructions.)
 */

{ 0,	PSEUDOOP_CPU,		0,		".cpu"		},
{ 0,	PSEUDOOP_ARCH,		0,		".arch"		},
{ 0,	PSEUDOOP_FPU,		0,		".fpu"		},
{ 0,	PSEUDOOP_MODE,		0,		".thumb"	},	/* UAL syntax */
{ 0,	PSEUDOOP_MODE,		0,		".thumbx"	},	/* UAL syntax */
{ 0,	PSEUDOOP_MODE,		0,		".code16"	},	/* pre-UAL syntax */
{ 0,	PSEUDOOP_THUMBFUNC,	0,		".thumb_func"	},
{ 0,	PSEUDOOP_POOL,		0,		".pool"		},
#ifdef COMPAT_GAS
{ 0,	PSEUDOOP_EABIATTR,	0,		".eabi_attribute"	},
{ 0,	PSEUDOOP_SYNTAX,	0,		".syntax"	},
{ 0,	PSEUDOOP_CODE,		0,		".code"		},
#endif
#ifdef notyet
{ 0,	PSEUDOOP_FUNC,		0,		".fnstart"	},
{ 0,	PSEUDOOP_FUNC,		1,		".fnend"	},
{ 0,	PSEUDOOP_CANTUNWIND,	0,		".cantunwind"	},
#endif

{ 0,	REG,			0,		"R0"		},
{ 0,	REG,			1,		"R1"		},
{ 0,	REG,			2,		"R2"		},
{ 0,	REG,			3,		"R3"		},
{ 0,	REG,			4,		"R4"		},
{ 0,	REG,			5,		"R5"		},
{ 0,	REG,			6,		"R6"		},
{ 0,	REG,			7,		"R7"		},
{ 0,	REGHI,			8,		"R8"		},
{ 0,	REGHI,			9,		"R9"		},
{ 0,	REGHI,			10,		"R10"		},
{ 0,	REGHI,			11,		"R11"		},
{ 0,	REGHI,			12,		"R12"		},
{ 0,	REGHI,			13,		"R13"		},
{ 0,	REGHI,			14,		"R14"		},
{ 0,	REGHI,			15,		"R15"		},
#ifdef  COMPAT_GAS
{ 0,	REGHI,			11,		"FP"		},
{ 0,	REGHI,			12,		"IP"		},
#endif
{ 0,	SP,			13,		"SP"		},
{ 0,	LR,			14,		"LR"		},
{ 0,	PC,			15,		"PC"		},

{ 0,	SHIFT,			0x0000,		"LSL"		},	/* register or immediate */
{ 0,	SHIFT,			0x0800,		"LSR"		},	/* register or immediate */
{ 0,	SHIFT,			0x1000,		"ASR"		},	/* register or immediate */
{ 0,	ADD,			0x1800,		"ADD"		},	/* register or immediate */
{ 0,	ADD,			0x1a00,		"SUB"		},	/* register or immediate */

{ 0,	MOV,			0,		"MOV"		},	/* register or immediate */
{ 0,	MOV,			0,		"CPY"		},	/* alias in pre-UAL */
{ 0,	CMP,			0,		"CMP"		},	/* register or immediate */

{ 0,	DATA1,			0x4140,		"ADC"		},	/* add with carry */
{ 0,	DATA1,			0x4000,		"AND"		},	/* logical and */
{ 0,	DATA1,			0x4380,		"BIC"		},	/* bit clear */
{ 0,	DATA1,			0x4040,		"EOR"		},	/* exclusive or */
{ 0,	DATA1,			0x4300,		"ORR"		},	/* logical or */
{ 0,	DATA1,			0x41c0,		"ROR"		},	/* rotate right */
{ 0,	DATA1,			0x4240,		"RSB"		},	/* reverse subtract */
{ 0,	DATA1,			0x4180,		"SBC"		},	/* subtract with carry */
{ 0,	DATA1,			0x43c0,		"MVN"		},	/* negate */
{ 0,	DATA1,			0x42c0,		"CMN"		},	/* compare negative */
{ 0,	DATA1,			0x4200,		"TST"		},	/* test bits */
{ 0,	DATA1,			0x4340,		"MUL"		},	/* multiply */
{ 0,	DATA1,			0xB240,		"UXTH"		},	/* unsigned extend */ /* ARMv6 */
{ 0,	DATA1,			0xB2C0,		"UXTB"		},	/* unsigned extend */ /* ARMv6 */

{ 0,	BREXCH,			0x4700,		"BX"		},
{ 0,	BREXCH,			0x4780,		"BLX"		},	/* ARMv5T */

{ 0,	UBRANCH,		0xE000,		"B"		},
{ 0,	LBRANCH,		0,		"BL"		},

{ 0,	BRANCH,			0xD000,		"BEQ"		},
{ 0,	BRANCH,			0xD100,		"BNE"		},
{ 0,	BRANCH,			0xD200,		"BCS"		},
{ 0,	BRANCH,			0xD300,		"BCC"		},
{ 0,	BRANCH,			0xD400,		"BMI"		},
{ 0,	BRANCH,			0xD500,		"BPL"		},
{ 0,	BRANCH,			0xD6A0,		"BVS"		},
{ 0,	BRANCH,			0xD700,		"BVC"		},
{ 0,	BRANCH,			0xD800,		"BHI"		},
{ 0,	BRANCH,			0xD900,		"BLS"		},	/* less or same */
{ 0,	BRANCH,			0xDA00,		"BGE"		},	/* greater or equal */
{ 0,	BRANCH,			0xDB00,		"BLT"		},	/* less than */
{ 0,	BRANCH,			0xDC00,		"BGT"		},	/* greater than */
{ 0,	BRANCH,			0xDD00,		"BLE"		},	/* less or equal */

{ 0,	LDST,			0,		"STR"		},
{ 0,	LDST,			1,		"LDR"		},
{ 0,	LDSTB,			0,		"STRB"		},
{ 0,	LDSTB,			1,		"LDRB"		},
{ 0,	LDSTH,			0,		"STRH"		},
{ 0,	LDSTH,			1,		"LDRH"		},
{ 0,	LDRS,			0,		"LDRSB"		},
{ 0,	LDRS,			1,		"LDRSH"		},

/* block data transfers */
{ 0,	STACK,			0xB400,		"PUSH"		},
{ 0,	STACK,			0xBC00,		"POP"		},
{ 0,	LDM,			0xC800,		"LDMIA"		},	/* load multiple, increment after */
{ 0,	LDM,			0xC000,		"STMIA"		},	/* store multiple, increment after */

{ 0,	ADR,			0xA000,		"ADR"		},

{ 0,	SWI,			0xDF00,		"SWI"		},
{ 0,	SVC,			0xDF00,		"SVC"		},

{ 0,	SVC,			0xBF00,		"BKPT"		},	/* ARMv5T */
{ 0,	CBNZ,			0xB900,		"CBNZ"		},	/* ARMv6T2, except ARMv6-M */
{ 0,	CBNZ,			0xB100,		"CBZ"		},	/* ARMv6T2, except ARMv6-M */

{ 0,	IMPL,			0xBF40,		"SEV"		},
{ 0,	IMPL,			0xB658,		"SETENDBE"	},	/* ARMv6 except ARMv6-M and ARMv7-M */
{ 0,	IMPL,			0xB650,		"SETENDLE"	},	/* ARMv6 except ARMv6-M and ARMv7-M */
{ 0,	IMPL,			0xBf20,		"WFE"		},	/* ARMv6 */
{ 0,	IMPL,			0xBf30,		"WFI"		},	/* ARMv6 */
{ 0,	IMPL,			0xBf10,		"YIELD"		},	/* ARMv6 */
{ 0,	IMPL,			0xBF00,		"NOP"		},	/* ARMV6 */

{ 0,	DATA1,			0xBA00,		"REV"		},	/* ARMv6 */
{ 0,	DATA1,			0xBA40,		"REV16"		},	/* ARMv6 */
{ 0,	DATA1,			0xBAC0,		"REVSH"		},	/* ARMv6 */
{ 0,	DATA1,			0xB662,		"CPSIE"		},	/* ARMv6 */
{ 0,	DATA1,			0xB672,		"CPSID"		},	/* ARMv6 */

{ 0,	MSR,			0,		"MSR"		},	/* ARMv6T2 */
{ 0,	MSR,			0,		"MRS"		},	/* ARMv6T2 */

{ 0,	APSR,			0x0000,		"APSR"		},	/* application psr */ /* ARMv6M */
{ 0,	APSR,			0x8000,		"SPSR"		},	/* system psr */ /* ARMv6M */
{ 0,	PSR,			0x0001,		"IAPSR"		},	/* I and A psrs */ /* ARMv6M */
{ 0,	PSR,			0x0002,		"EAPSR"		},	/* E and A psrs */ /* ARMv6M */
{ 0,	PSR,			0x0003,		"XPSR"		},	/* A, I and E psrs */ /* ARMv6M */
{ 0,	PSR,			0x0005,		"IPSR"		},	/* interrupt psr */ /* ARMv6M */
{ 0,	PSR,			0x0006,		"EPSR"		},	/* execution psr */ /* ARMv6M */
{ 0,	PSR,			0x0007,		"IEPSR"		},	/* I and E psrs */ /* ARMv6M */
{ 0,	PSR,			0x0008,		"MSP"		},	/* main stack pointer */ /* ARMv6M */
{ 0,	PSR,			0x0009,		"PSP"		},	/* process stack pointer */ /* ARMv6M */
{ 0,	PSR,			0x0010,		"PRIMASK"	},	/* mask out configurable exceptions */ /* ARMv6M */
{ 0,	PSR,			0x0000,		"BASEPRI"	},	/* ARMv6M */
{ 0,	PSR,			0x0000,		"BASEPRI_MAX"	},	/* ARMv6M */
{ 0,	PSR,			0x0000,		"FAULTMASK"	},	/* ARMv6M */
{ 0,	PSR,			0x0014,		"CONTROL"	},	/* ARMv6M */
{ 0,	PSR,			0x0000,		"SCTLR"		},	/* CP15 register */ /* ARMv6M */

/* 1 0 1 1  1 1 1 1  firstcond(3) mask(5) */
{ 0,	IT,			0x4,		"IT"		},	/* ARMv6T2 */
{ 0,	IT,			0x2,		"ITT"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0xC,		"ITE"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0x2,		"ITTT"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0xA,		"ITET"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0x6,		"ITTE"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0xE,		"ITEE"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0x1,		"ITTTT"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0x9,		"ITETT"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0x5,		"ITTET"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0xD,		"ITEET"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0x3,		"ITTTE"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0xB,		"ITETE"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0x7,		"ITTEE"		},	/* ARMv6T2, except ARMV6-M */
{ 0,	IT,			0xF,		"ITEEE"		},	/* ARMv6T2, except ARMV6-M */

{ 0,	COND,			0,		"EQ"		},
{ 0,	COND,			1,		"NE"		},
{ 0,	COND,			2,		"CS"		},
{ 0,	COND,			3,		"CC"		},
{ 0,	COND,			4,		"MI"		},
{ 0,	COND,			5,		"PL"		},
{ 0,	COND,			6,		"VS"		},
{ 0,	COND,			7,		"VC"		},
{ 0,	COND,			8,		"HI"		},
{ 0,	COND,			9,		"LS"		},
{ 0,	COND,			10,		"GE"		},
{ 0,	COND,			11,		"LT"		},
{ 0,	COND,			12,		"GT"		},

#if 0
/* signal processing */
{ 0,	DATA1,			0,		"SMULxy"	},	/* ARMv5TE - 32b */
{ 0,	DATA1,			0,		"SMLAxy"	},	/* ARMv5TE - 32b */
{ 0,	DATA1,			0,		"SMULWy"	},	/* ARMv5TE - 32b */
{ 0,	DATA1,			0,		"SMLAWy"	},	/* ARMv5TE - 32b */
{ 0,	DATA1,			0,		"SMLALxy "	},

{ 0,	DATA1,			0,		"QADD"		},	/* ARMv5TE - 32b */
{ 0,	DATA1,			0,		"QSUB"		},	/* ARMv5TE - 32b */
{ 0,	DATA1,			0,		"QDADD"		},	/* ARMv5TE - 32b */
{ 0,	DATA1,			0,		"QDSUB"		},	/* ARMv5TE - 32b */
#endif

/* unified syntax */
#ifdef COMPAT_GAS
{ 0,	SHIFT,			0x0000,		"LSLS"		},	/* register or immediate */
{ 0,	SHIFT,			0x0800,		"LSRS"		},	/* register or immediate */
{ 0,	SHIFT,			0x1000,		"ASRS"		},	/* register or immediate */
{ 0,	ADD,			0x1800,		"ADDS"		},	/* register or immediate */
{ 0,	ADD,			0x1a00,		"SUBS"		},	/* register or immediate */
{ 0,	MOV,			0,		"MOVS"		},	/* register or immediate */
{ 0,	DATA1,			0x4140,		"ADCS"		},	/* add with carry */
{ 0,	DATA1,			0x4180,		"SBCS"		},	/* subtract with carry */
{ 0,	DATA1,			0x4000,		"ANDS"		},	/* logical and */
{ 0,	DATA1,			0x4380,		"BICS"		},	/* bit clear */
{ 0,	DATA1,			0x4040,		"EORS"		},	/* exclusive or */
{ 0,	DATA1,			0x4300,		"ORRS"		},	/* logical or */
{ 0,	DATA1,			0x4240,		"RSBS"		},	/* reverse subtract */
{ 0,	DATA1,			0x4340,		"MULS"		},	/* multiply */
#endif
