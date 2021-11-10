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
 * Currently only supports opcodes in the SAM88RC MCUs based
 * on Samsung's SAM88R implementation.
 */

{ 0,	PSEUDOOP_DEVICE,	0,	".device"	},
{ 0,	DOT,			0,	"$"		},

{ 0,	REG,	0,	"R0"		},
{ 0,	REG,	1,	"R1"		},
{ 0,	REG,	2,	"R2"		},
{ 0,	REG,	3,	"R3"		},
{ 0,	REG,	4,	"R4"		},
{ 0,	REG,	5,	"R5"		},
{ 0,	REG,	6,	"R6"		},
{ 0,	REG,	7,	"R7"		},
{ 0,	REG,	8,	"R8"		},
{ 0,	REG,	9,	"R9"		},
{ 0,	REG,	10,	"R10"		},
{ 0,	REG,	11,	"R11"		},
{ 0,	REG,	12,	"R12"		},
{ 0,	REG,	13,	"R13"		},
{ 0,	REG,	14,	"R14"		},
{ 0,	REG,	15,	"R15"		},

{ 0,	REGW,	0,	"RR0"		},	/* does this exist? */
{ 0,	REGW,	2,	"RR2"		},
{ 0,	REGW,	4,	"RR4"		},
{ 0,	REGW,	6,	"RR6"		},
{ 0,	REGW,	8,	"RR8"		},
{ 0,	REGW,	10,	"RR10"		},
{ 0,	REGW,	12,	"RR12"		},
{ 0,	REGW,	14,	"RR14"		},

/* load instructions */
{ 0,	RM,	0xB0,	"CLR"		},
{ 0,	LD,	0,	"LD"		},
{ 0,	LDC,	0,	"LDC"		},	/* code */
{ 0,	LDC,	1,	"LDE"		},	/* external */ /* alias */
{ 0,	LDCI,	0xE3,	"LDCI"		},	/* code and increment */
{ 0,	LDCI,	0xE3,	"LDEI"		},	/* external and increment */
#ifdef SAM88RC
{ 0,	LDCI,	0xE2,	"LDCD"		},	/* code and decrement */
{ 0,	LDCI,	0xE2,	"LDED"		},	/* external and decrement */
#endif
{ 0,	RM,	0x50,	"POP"		},
{ 0,	RM,	0x70,	"PUSH"		},

/* arithmetic instructions */
{ 0,	RMW,	0x10,	"ADC",		},
{ 0,	RMW,	0x00,	"ADD",		},
{ 0,	RMW,	0xA0,	"CP",		},
{ 0,	RM,	0x00,	"DEC",		},
{ 0,	INC,	0,	"INC",		},
{ 0,	RMW,	0x30,	"SBC",		},
{ 0,	RMW,	0x20,	"SUB",		},
#ifndef SAM88RC
{ 0,	RMW,	0x40,	"DA"		},	/* decimal adjust */
{ 0,	INCW,	0xA0,	"INCW",		},
{ 0,	INCW,	0x80,	"DECW",		},
#endif

/* logic instructions */
{ 0,	RMW,	0x50,	"AND",		},
{ 0,	RM,	0x60,	"COM",		},
{ 0,	RMW,	0x40,	"OR",		},
{ 0,	RMW,	0xB0,	"XOR",		},

/* program control */
{ 0,	CALL,	0xF0,	"CALL"		},
{ 0,	IMPL,	0xBF,	"IRET"		},
{ 0,	IMPL,	0xAF,	"RET"		},
{ 0,	BRANCH,	0x0D,	"JP"		},
{ 0,	RBRANCH,0x0B,	"JR"		},
#ifndef SAM88RC
{ 0,	RBRANCH,0x0A,	"DJNZ"		},
#endif

{ 0,	COND,	0x0,	"F"		},
{ 0,	COND,	0x8,	"T"		},
{ 0,	COND,	0x1,	"LT"		},
{ 0,	COND,	0x9,	"GE"		},
{ 0,	COND,	0x2,	"LE"		},
{ 0,	COND,	0xa,	"GT"		},
{ 0,	COND,	0x3,	"ULE"		},
{ 0,	COND,	0xB,	"UGT"		},
{ 0,	COND,	0x4,	"OV"		},
{ 0,	COND,	0xc,	"NOV"		},
{ 0,	COND,	0x5,	"MI"		},
{ 0,	COND,	0xd,	"PL"		},
{ 0,	COND,	0x6,	"EQ"		},
{ 0,	COND,	0x6,	"Z"		},
{ 0,	COND,	0xe,	"NE"		},
{ 0,	COND,	0xe,	"NZ"		},
{ 0,	COND,	0x7,	"C"		},
{ 0,	COND,	0x7,	"ULT"		},
{ 0,	COND,	0xF,	"NC"		},
{ 0,	COND,	0xF,	"UGE"		},

{ 0,	BRANCH,	0x0D,	"JF"		},
{ 0,	BRANCH,	0x8D,	"JT"		},
{ 0,	BRANCH,	0x1D,	"JLT"		},
{ 0,	BRANCH,	0x9D,	"JGE"		},
{ 0,	BRANCH,	0x2D,	"JLE"		},
{ 0,	BRANCH,	0xAD,	"JGT"		},
{ 0,	BRANCH,	0x3D,	"JULE"		},
{ 0,	BRANCH,	0xBD,	"JUGT"		},
{ 0,	BRANCH,	0x4D,	"JOV"		},
{ 0,	BRANCH,	0xCD,	"JNOV"		},
{ 0,	BRANCH,	0x5D,	"JMI"		},
{ 0,	BRANCH,	0xdD,	"JPL"		},
{ 0,	BRANCH,	0x6D,	"JEQ"		},
{ 0,	BRANCH,	0x6D,	"JZ"		},
{ 0,	BRANCH,	0xED,	"JNE"		},
{ 0,	BRANCH,	0xED,	"JNZ"		},
{ 0,	BRANCH,	0x7D,	"JC"		},
{ 0,	BRANCH,	0x7D,	"JULT"		},
{ 0,	BRANCH,	0xFD,	"JNC"		},
{ 0,	BRANCH,	0xFD,	"JUGE"		},

/* bit manipulation */
{ 0,	RMW,	0x60,	"TCM"		},	/* test and complement under mask */
{ 0,	RMW,	0x70,	"TM"		},	/* test under mask */

/* rotate and shift */
{ 0,	RM,	0x90,	"RL"		},
{ 0,	RM,	0x10,	"RLC"		},
{ 0,	RM,	0xE0,	"RR"		},
{ 0,	RM,	0xC0,	"RRC"		},
{ 0,	RM,	0xD0,	"SRA"		},
#ifndef SAM88RC
{ 0,	RM,	0xF0,	"SWAP"		},	/* swap nibbles */
#endif

/* cpu instructions */
{ 0,	IMPL,	0xEF,	"CCF"		},	/* complement carry flag */
{ 0,	IMPL,	0x8F,	"DI"		},	/* disable interrupts */
{ 0,	IMPL,	0x9F,	"EI"		},	/* enable interrupts */
{ 0,	IMPL,	0x6F,	"IDLE"		},
{ 0,	IMPL,	0xFF,	"NOP"		},
{ 0,	IMPL,	0xCF,	"RCF"		},	/* reset carry flag */
{ 0,	IMPL,	0xDF,	"SCF"		},	/* set carry flag */
#ifdef SAM88RC
{ 0,	IMPL,	0x7F,	"STOP"		},
#endif
#ifndef SAM88RC
{ 0,	SRP,	0x31,	"SRP"		},	/* set register pointer */
#endif

#ifdef SAM88RC
/* special function registers */
{ 0,	SFR,	0xD0,	"T0CNT"		},	/* Timer0 counter register */
{ 0,	SFR,	0xD1,	"T0DATA"	},	/* Timer0 data register */
{ 0,	SFR,	0xD2,	"T0CON"		},	/* Timer0 control register */

{ 0,	SFR,	0xD4,	"CLKCON"	},	/* clock control register */
{ 0,	SFR,	0xD5,	"FLAGS"		},	/* system flags register */

{ 0,	SFR,	0xD9,	"SP"		},	/* stack pointer register */

{ 0,	SFR,	0xDB,	"MDSREG"	},	/* MDS special register */
{ 0,	SFR,	0xDC,	"BTCON"		},	/* basic timer control register */
{ 0,	SFR,	0xDD,	"BTCNT"		},	/* basic timer counter */
{ 0,	SFR,	0xDE,	"FTSTCON"	},	/* test mode control register */
{ 0,	SFR,	0xDF,	"SYM"		},	/* systme mode register */

{ 0,	SFR,	0xE0,	"P0"		},
{ 0,	SFR,	0xE1,	"P1"		},
{ 0,	SFR,	0xE2,	"P2"		},

{ 0,	SFR,	0xE6,	"P0CONH"	},	/* Port0 control register (high) */
{ 0,	SFR,	0xE7,	"P0CONL"	},	/* Port0 control register (low) */
{ 0,	SFR,	0xE8,	"P0PND"		},	/* Port0 interrupt pending register */

{ 0,	SFR,	0xE9,	"P1CON"		},	/* Port1 control register (high) */

{ 0,	SFR,	0xEA,	"P2CONH"	},	/* Port2 control register (high) */
{ 0,	SFR,	0xEB,	"P2CONL"	},	/* Port2 control register (low) */

{ 0,	SFR,	0xEC,	"FMCON"		},	/* flash memory control register */
{ 0,	SFR,	0xED,	"FMUSR"		},	/* flash memory user programming enable register */
{ 0,	SFR,	0xEE,	"RMSECH"	},	/* flash memory sector address register (high) */
{ 0,	SFR,	0xEF,	"RMSECL"	},	/* flash memory sector address register (low) */

{ 0,	SFR,	0xF0,	"PWMDATA1"	},	/* PWM data register 1 */
{ 0,	SFR,	0xF1,	"PWMEX"		},	/* PWM extension register */
{ 0,	SFR,	0xF2,	"PWMDATA"	},	/* PWM data register */
{ 0,	SFR,	0xF3,	"PWMCON"	},	/* PWM control register */
{ 0,	SFR,	0xF4,	"STOPCON"	},	/* STOP control register */

{ 0,	SFR,	0xF7,	"ADCON"		},	/* ADC control register */
{ 0,	SFR,	0xF8,	"ADDATAH"	},	/* ADC data register (high) */
{ 0,	SFR,	0xF9,	"ADDATAL"	},	/* ADC data register (low) */
#endif
