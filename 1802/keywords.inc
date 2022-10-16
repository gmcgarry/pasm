/*-
 * Copyright (c) 2022 Gregory McGarry <g.mcgarry@ieee.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND fituNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROfituS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

{ 0,	'=',		0,		"equ"	},
{ 0,	PSEUDOOP_ORG,	0,		"org"	},
{ 0,	PSEUDOOP_END,	0,		"end"	},
{ 0,	PSEUDOOP_DATA,	1,		"db"	},
{ 0,	PSEUDOOP_DATA,	2,		"dw"	},
{ 0,	SHIFTFUNC,	0,		"low"	},
{ 0,	SHIFTFUNC,	8,		"high"	},

{ 0,	REG,		0,		"R0"	},
{ 0,	REG,		1,		"R1"	},
{ 0,	REG,		2,		"R2"	},
{ 0,	REG,		3,		"R3"	},
{ 0,	REG,		4,		"R4"	},
{ 0,	REG,		5,		"R5"	},
{ 0,	REG,		6,		"R6"	},
{ 0,	REG,		7,		"R7"	},
{ 0,	REG,		8,		"R8"	},
{ 0,	REG,		9,		"R9"	},
{ 0,	REG,		10,		"RA"	},
{ 0,	REG,		11,		"RB"	},
{ 0,	REG,		12,		"RC"	},
{ 0,	REG,		13,		"RD"	},
{ 0,	REG,		14,		"RE"	},
{ 0,	REG,		15,		"RF"	},

/* register operations */
{ 0,	XOP,		0x10,		"inc"	},	/* INC Rn - increment */
{ 0,	XOP,		0x20,		"dec"	},	/* DEC Rn - decrement */
{ 0,	NOARG,		0x60,		"inx"	},	/* INX - increment Rx */
{ 0,	XOP,		0x80,		"glo"	},	/* GLO Rn - get low byte in D */
{ 0,	XOP,		0x90,		"ghi"	},	/* GHI Rn - get high byte in D */
{ 0,	XOP,		0xA0,		"plo"	},	/* PLO Rn - put D in low byte */
{ 0,	XOP,		0xB0,		"phi"	},	/* PHI Rn - put D in high byte */

/* memory load/store */
{ 0,	XOP,		0x00,		"ldn"	},	/* LDN Rn - indirect load into D (n not 0) */
{ 0,	XOP,		0x40,		"lda"	},	/* LDA Rn - indirect load into D, post-increment Rn */
{ 0,	XOP,		0x50,		"str"	},	/* STR Rn - indirect store D */
{ 0,	IOP,		0xF8,		"ldi"	},	/* LDI nn - load from memory in current page */
{ 0,	NOARG,		0xF0,		"ldx"	},	/* LDX - indirect load of Rx */
{ 0,	NOARG,		0x72,		"ldxa"	},	/* LDXA - indirect load, post-increment Rx */
{ 0,	NOARG,		0x73,		"stxd"	},	/* STXD - store D, post-decrement Rx */

/* short branches -- within current page */
{ 0,	BRANCH,		0x30,		"br"	},	/* BR nn - branch always */
{ 0,	BRANCH,		0x31,		"bq"	},	/* BQ nn - branch if q flag */
{ 0,	BRANCH,		0x32,		"bz"	},	/* BZ nn - branch if zero flag */
{ 0,	BRANCH,		0x33,		"bdf"	},	/* BDF nn - branch if data flag (carry) */
{ 0,	BRANCH,		0x33,		"bpz"	},	/* BPZ nn - branch if positive */
{ 0,	BRANCH,		0x33,		"bge"	},	/* BGE nn - branch if equal or greater */
{ 0,	BRANCH,		0x34,		"b1"	},	/* B1 nn - branch EF1 set */
{ 0,	BRANCH,		0x35,		"b2"	},	/* B2 nn - branch EF2 set */
{ 0,	BRANCH,		0x36,		"b3"	},	/* B3 nn - branch EF3 set */
{ 0,	BRANCH,		0x37,		"b4"	},	/* B4 nn - branch EF4 set */

#if 0
{ 0,	NOARG,		0x30|0x08,	"nbr"	},	/* NBR - branch never */
#endif
{ 0,	NOARG,		0x30|0x08,	"skp"	},	/* SKP - skip next byte */
{ 0,	BRANCH,		0x31|0x08,	"bnq"	},	/* BNQ nn - branch if not q flag */
{ 0,	BRANCH,		0x32|0x08,	"bnz"	},	/* BNZ nn - branch if not zero flag */
{ 0,	BRANCH,		0x33|0x08,	"bnf"	},	/* BNF nn - branch if not data flag (carry) */
{ 0,	BRANCH,		0x33|0x08,	"bm"	},	/* BM nn - branch if minus */
{ 0,	BRANCH,		0x33|0x08,	"bl"	},	/* BL nn - branch if less than */
{ 0,	BRANCH,		0x34|0x08,	"bn1"	},	/* B1 nn - branch EF1 not set */
{ 0,	BRANCH,		0x35|0x08,	"bn2"	},	/* B2 nn - branch EF2 not set */
{ 0,	BRANCH,		0x36|0x08,	"bn3"	},	/* B3 nn - branch EF3 not set */
{ 0,	BRANCH,		0x37|0x08,	"bn4"	},	/* B4 nn - branch EF4 not set */

/* long branches & skip */
{ 0,	BRANCH,		0xC0,		"lbr"	},	/* LBR hhll - branch to hhll */
{ 0,	BRANCH,		0xC1,		"lbq"	},	/* LBQ hhll - branch if q flag */
{ 0,	BRANCH,		0xC2,		"lbz"	},	/* LBZ hhll - branch if zero flag */
{ 0,	BRANCH,		0xC3,		"lbdf"	},	/* LBDF hhll - branch if data flag (carry) */
{ 0,	NOARG,		0xC4,		"nop"	},	/* NOP */
{ 0,	NOARG,		0xC5,		"lsnq"	},	/* LSNQ - skip if not q flag */
{ 0,	NOARG,		0xC6,		"lsnz"	},	/* LSNZ - skip if not zero flag */
{ 0,	NOARG,		0xC7,		"lsnf"	},	/* LSNF - skip if not data flag (carry) */

#if 0
{ 0,	NOARG,		0xC0|0x08,	"nlbr"	},	/* NLBR - never branch */
#endif
{ 0,	NOARG,		0xC0|0x08,	"lskp"	},	/* LSKP - skip next word */
{ 0,	BRANCH,		0xC1|0x08,	"lbnq"	},	/* LBNQ hhll - branch if q flag */
{ 0,	BRANCH,		0xC2|0x08,	"lbnz"	},	/* LBNZ hhll - branch if zero flag */
{ 0,	BRANCH,		0xC3|0x08,	"lbnf"	},	/* LBNF hhll - branch if data flag (carry) */
{ 0,	NOARG,		0xCC,		"lsie"	},	/* LSIE - skip if IE */
{ 0,	NOARG,		0xC5|0x08,	"lsq"	},	/* LSQ - skip if q flag */
{ 0,	NOARG,		0xC6|0x08,	"lsz"	},	/* LSZ - skip if zero flag */
{ 0,	NOARG,		0xC7|0x08,	"lsdf"	},	/* LSDF - skip if data flag (carry) */

/* logic, arithmetic and shift */
{ 0,	NOARG,		0xF1,		"or"	},	/* OR - or memory Rx with D */
{ 0,	NOARG,		0xF2,		"and"	},	/* AND - and memory Rx with D */
{ 0,	NOARG,		0xF3,		"xor"	},	/* XOR - xor memory Rx with D */
{ 0,	NOARG,		0xF4,		"add"	},	/* ADD - add memory Rx with D */
{ 0,	NOARG,		0x74,		"adc"	},	/* ADC - add memory Rx with D and carry */
{ 0,	NOARG,		0xF5,		"sd"	},	/* SD - subtract D from memory Rx */
{ 0,	NOARG,		0x75,		"sdb"	},	/* SDB - subtract D from memory Rx with borrow */
{ 0,	NOARG,		0xF7,		"sm"	},	/* SM - subtract memory Rx from D */
{ 0,	NOARG,		0x77,		"smb"	},	/* SMB - subtract memory Rx from D wth borrow */

{ 0,	IOP,		0xF9,		"ori"	},	/* ORI nn - or immediate wiht */
{ 0,	IOP,		0xFA,		"ani"	},	/* ANI nn - and immediate with D */
{ 0,	IOP,		0xFB,		"xri"	},	/* XRI nn - xor immediate with D */
{ 0,	IOP,		0xFC,		"adi"	},	/* ADI nn - add immeidate with D */
{ 0,	IOP,		0x7C,		"adci"	},	/* ADCI nn - add immediate with D and carry */
{ 0,	IOP,		0xFD,		"sdi"	},	/* SDI nn - subtract D from immediate */
{ 0,	IOP,		0x7D,		"sdbi"	},	/* SDBI nn - subtract D from immediate with borrow */
{ 0,	IOP,		0xFF,		"smi"	},	/* SMI nn - subtract immediate from D */
{ 0,	IOP,		0x7F,		"smbi"	},	/* SMBI nn - subtract immediate from D wth borrow */

{ 0,	NOARG,		0xF6,		"shr"	},	/* SHR - shift D right, LSB into DF */
{ 0,	NOARG,		0xFE,		"shl"	},	/* SHL - shift D left, MSB into DF */
{ 0,	NOARG,		0x76,		"shrc"	},	/* SHRC - shift D right with carry */
{ 0,	NOARG,		0x76,		"rshr"	},	/* RSHR - shift D right with carry - alias rotate */
{ 0,	NOARG,		0x7E,		"shlc"	},	/* SHLC - shift D left with carry */
{ 0,	NOARG,		0x7E,		"rshl"	},	/* RSHL - shift D left with carry - alias rotate */

/* control */
{ 0,	NOARG,		0x00,		"idl"	},	/* IDL - wait for interrupt */
{ 0,	NOARG,		0x70,		"ret"	},	/* RET - X,P = M(Rx), post-increment Rx, IE=1 */
{ 0,	NOARG,		0x71,		"dis"	},	/* DIS - X,P = M(Rx), post-increment Rx, IE=0 */
{ 0,	NOARG,		0x78,		"sav"	},	/* SAV - M(Rx)=T */
{ 0,	NOARG,		0x79,		"mark"	},	/* MARK - T=X,P, M(Rx)=X,P, X=P, post-decrement Rx */
{ 0,	NOARG,		0x7A,		"req"	},	/* REQ - reset Q */
{ 0,	NOARG,		0x7B,		"seq"	},	/* SEQ - set Q */
{ 0,	XOP,		0xD0,		"sep"	},	/* SEP n - P=n */
{ 0,	XOP,		0xE0,		"sex"	},	/* SEX n - X=n */

/* input/output */
{ 0,	IO,		0x60,		"out"	},	/* OUT n - bus=M(Rx), post-increment Rx */
{ 0,	IO,		0x68,		"in"	},	/* IN n - M(Rx)=bus */

/* AVOCET XASM18 compatibility */
#ifdef COMPAT_XASM18
#if 0
{ 0,	PSEU,		0xD4,		"CALL"	},	/* SEP R4, DW ADDR */
{ 0,	NOARG,		0xD5,		"EXIT"	},	/* SEP R5 */
{ 0,	IO,		0x68,		"INP"	},	/* IN n - M(Rx)=bus */
#endif
{ 0,	NOARG,		0x60,		"IRX"	},	/* INX */
{ 0,	NOARG,		0x72,		"POP"	},	/* LDXA */
{ 0,	NOARG,		0x73,		"PUSH"	},	/* STXD */
{ 0,	NOARG,		0xF7,		"SDM"	},	/* SM */
#endif

#ifdef COMPAT_A18
{ 0,	PSEU,		0xD4,		"LOAD"	},	/* LDI LOW($2); PLO $3; LDI HIGH($2); PHI $3 */
#endif
