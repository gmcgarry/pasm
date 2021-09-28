/*-
 * Copyright (c) 1990 Ken Stauffer (University of Calgary)
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
 * Mostly taken for symbol.c:
 *
 * as31 - 8031/8051 Assembler
 *
 * Maintained at:  http://www.pjrc.com/tech/8051/
 * Please report problems to:  paul@pjrc.com
 */

#define B(a)		(0xF0+(a))
#define ACC(a)		(0xE0+(a))
#define PSW(a)		(0xD0+(a))
#define T2CON(a)	(0xC8+(a))
#define IP(a)		(0xB8+(a))
#define P3(a)		(0xB0+(a))
#define IE(a)		(0xA8+(a))
#define P2(a)		(0xA0+(a))
#define SCON(a)		(0x98+(a))
#define P1(a)		(0x90+(a))
#define TCON(a)		(0x88+(a))
#define P0(a)		(0x80+(a))

/* intel syntax compatibility */
{ 0,	PSEUDOOP_ORG,		0,		"org"	},
{ 0,	PSEUDOOP_END,		0,		"end"	},
{ 0,	'=',			0,		"equ"	},
{ 0,	BIT,			0,		"bit"	},
{ 0,	PSEUDOOP_DATA,		1,		"db"	},
{ 0,	DOT,			0,		"$"	},

{ 0,	PSEUDOOP_DATA,		1,		".db"	},
{ 0,	PSEUDOOP_DATA,		2,		".dw"	},
{ 0,	PSEUDOOP_DATA,		2,		".ds"	},
{ 0,	PSEUDOOP_AREA,		0,		".area" },
{ 0,	PSEUDOOP_FILE,		0,		".module" },

{ 0,	SHIFTFUNC,		0,		"low" },
{ 0,	SHIFTFUNC,		8,		"high" },

{ 0,	BITPOS,			0,		".0"	},
{ 0,	BITPOS,			1,		".1"	},
{ 0,	BITPOS,			2,		".2"	},
{ 0,	BITPOS,			3,		".3"	},
{ 0,	BITPOS,			4,		".4"	},
{ 0,	BITPOS,			5,		".5"	},
{ 0,	BITPOS,			6,		".6"	},
{ 0,	BITPOS,			7,		".7"	},

/* registers */
{ 0,	A,			0,		"a"	},
{ 0,	AB,			0,		"ab"	},
{ 0,	C,			0,		"c"	},
{ 0,	DPTR,			0,		"dptr"	},
{ 0,	PC,			0,		"pc"	},
{ 0,	AREG,			0,		"r0"	},
{ 0,	AREG,			1,		"r1"	},
{ 0,	AREG,			2,		"r2"	},
{ 0,	AREG,			3,		"r3"	},
{ 0,	AREG,			4,		"r4"	},
{ 0,	AREG,			5,		"r5"	},
{ 0,	AREG,			6,		"r6"	},
{ 0,	AREG,			7,		"r7"	},

#ifndef DISABLE_SFR
/* common special function registers */
{ 0,	SFR,			PSW(6),		"AC"	},
{ 0,	SFR,			ACC(0),		"ACC"	},
{ 0,	SFR,			B(0),		"B"	},
{ 0,	SFR,			PSW(7),		"CY"	},
{ 0,	SFR,			0x83,		"DPH"	},
{ 0,	SFR,			0x82,		"DPL"	},
{ 0,	SFR,			IE(7),		"EA"	},
{ 0,	SFR,			IE(4),		"ES"	},
{ 0,	SFR,			IE(1),		"ET0"	},
{ 0,	SFR,			IE(3),		"ET1"	},
{ 0,	SFR,			IE(5),		"ET2"	},
{ 0,	SFR,			IE(0),		"EX0"	},
{ 0,	SFR,			IE(2),		"EX1"	},
{ 0,	SFR,			T2CON(3),	"EXEN2"	},
{ 0,	SFR,			T2CON(6),	"EXF2"	},
{ 0,	SFR,			PSW(5),		"F0"	},
{ 0,	SFR,			IE(0),		"IE"	},
{ 0,	SFR,			TCON(1),	"IE0"	},
{ 0,	SFR,			TCON(3),	"IE1"	},
{ 0,	SFR,			P3(2),		"INT0"	},
{ 0,	SFR,			P3(3),		"INT1"	},
{ 0,	SFR,			IP(0),		"IP"	},
{ 0,	SFR,			TCON(0),	"IT0"	},
{ 0,	SFR,			TCON(2),	"IT1"	},
{ 0,	SFR,			PSW(2),		"OV"	},
{ 0,	SFR,			PSW(0),		"P"	},
{ 0,	SFR,			P0(0),		"P0"	},
{ 0,	SFR,			P1(0),		"P1"	},
{ 0,	SFR,			P2(0),		"P2"	},
{ 0,	SFR,			P3(0),		"P3"	},
{ 0,	SFR,			0x87,		"PCON"	},
{ 0,	SFR,			IP(4),		"PS"	},
{ 0,	SFR,			PSW(0),		"PSW"	},
{ 0,	SFR,			IP(1),		"PT0"	},
{ 0,	SFR,			IP(3),		"PT1"	},
{ 0,	SFR,			IP(5),		"PT2"	},
{ 0,	SFR,			IP(0),		"PX0"	},
{ 0,	SFR,			IP(2),		"PX1"	},
{ 0,	SFR,			SCON(2),	"RB8"	},
{ 0,	SFR,			0xCB,		"RCAP2H"	},
{ 0,	SFR,			0xCA,		"RCAP2L"	},
{ 0,	SFR,			T2CON(5),	"RCLK"	},
{ 0,	SFR,			SCON(4),	"REN"	},
{ 0,	SFR,			P3(7),		"RD"	},
{ 0,	SFR,			SCON(0),	"RI"	},
{ 0,	SFR,			T2CON(0),	"RL2"	},
{ 0,	SFR,			PSW(3),		"RS0"	},
{ 0,	SFR,			PSW(4),		"RS1"	},
{ 0,	SFR,			P3(0),		"RXD"	},
{ 0,	SFR,			0x99,		"SBUF"	},
{ 0,	SFR,			SCON(0),	"SCON"	},
{ 0,	SFR,			SCON(7),	"SM0"	},
{ 0,	SFR,			SCON(6),	"SM1"	},
{ 0,	SFR,			SCON(5),	"SM2"	},
{ 0,	SFR,			0x81,		"SP"	},
{ 0,	SFR,			P3(4),		"T0"	},
{ 0,	SFR,			P3(5),		"T1"	},
{ 0,	SFR,			P0(0),		"T2"	},
{ 0,	SFR,			T2CON(0),	"T2CON"	},
{ 0,	SFR,			P0(1),		"T2EX"	},
{ 0,	SFR,			SCON(3),	"TB8"	},
{ 0,	SFR,			T2CON(4),	"TCLK"	},
{ 0,	SFR,			TCON(0),	"TCON"	},
{ 0,	SFR,			TCON(5),	"TF0"	},
{ 0,	SFR,			TCON(7),	"TF1"	},
{ 0,	SFR,			T2CON(7),	"TF2"	},
{ 0,	SFR,			0x8C,		"TH0"	},
{ 0,	SFR,			0x8D,		"TH1"	},
{ 0,	SFR,			0xCD,		"TH2"	},
{ 0,	SFR,			SCON(1),	"TI"	},
{ 0,	SFR,			0x8A,		"TL0"	},
{ 0,	SFR,			0x8B,		"TL1"	},
{ 0,	SFR,			0xCC,		"TL2"	},
{ 0,	SFR,			0x89,		"TMOD"	},
{ 0,	SFR,			TCON(4),	"TR0"	},
{ 0,	SFR,			TCON(6),	"TR1"	},
{ 0,	SFR,			T2CON(2),	"TR2"	},
{ 0,	SFR,			P3(1),		"TXD"	},
{ 0,	SFR,			P3(6),		"WR"	},
#endif

/* opcodes */
{ 0,	ACALL,			0x11,		"acall"	},
{ 0,	ADD,			0,		"add"	},
{ 0,	ADDC,			0,		"addc"	},
{ 0,	AJMP,			0x01,		"ajmp"	},
{ 0,	ANL,			0,		"anl"	},
{ 0,	CJNE,			0,		"cjne"	},
{ 0,	CLR,			0,		"clr"	},
{ 0,	CPL,			0,		"cpl"	},
{ 0,	DA,			0xd4,		"da"	},
{ 0,	DEC,			0,		"dec"	},
{ 0,	DIV,			0x84,		"div"	},
{ 0,	DJNZ,			0,		"djnz"	},
{ 0,	INC,			0,		"inc"	},
{ 0,	JB,			0x20,		"jb"	},
{ 0,	JBC,			0x10,		"jbc"	},
{ 0,	JC,			0x40,		"jc"	},
{ 0,	JMP,			0x73,		"jmp"	},
{ 0,	JNB,			0x30,		"jnb"	},
{ 0,	JNC,			0x50,		"jnc"	},
{ 0,	JNZ,			0x70,		"jnz"	},
{ 0,	JZ,			0x60,		"jz"	},
{ 0,	LCALL,			0x12,		"lcall"	},
{ 0,	LJMP,			0x2,		"ljmp"	},
{ 0,	MOV,			0,		"mov"	},
{ 0,	MOVC,			0x83,		"movc"	},
{ 0,	MOVX,			0,		"movx"	},
{ 0,	MUL,			0xa4,		"mul"	},
{ 0,	NOP,			0x0,		"nop"	},
{ 0,	ORL,			0,		"orl"	},
{ 0,	POP,			0xd0,		"pop"	},
{ 0,	PUSH,			0xc0,		"push"	},
{ 0,	RET,			0x22,		"ret"	},
{ 0,	RETI,			0x32,		"reti"	},
{ 0,	RL,			0x23,		"rl"	},
{ 0,	RLC,			0x33,		"rlc"	},
{ 0,	RR,			0x03,		"rr"	},
{ 0,	RRC,			0x13,		"rrc"	},
{ 0,	SETB,			0,		"setb"	},
{ 0,	SJMP,			0x80,		"sjmp"	},
{ 0,	SUBB,			0,		"subb"	},
{ 0,	SWAP,			0xc4,		"swap"	},
{ 0,	XCH,			0,		"xch"	},
{ 0,	XCHD,			0xd6,		"xchd"	},
{ 0,	XRL,			0,		"xrl"	},
