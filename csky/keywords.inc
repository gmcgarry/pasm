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

/* there's a V1 and V2 architecture */
/* 16-bit opcodes, 32-bit address space */

{ 0,	PSEUDOOP_LITERALS,	0,	".literals"	},
{ 0,	PSEUDOOP_LITERALS,	0,	".pool"		},

/* 16-bit opcodes only access 16 registers */
{ 0,	LOREG,		0,		"r0"		},
{ 0,	LOREG,		1,		"r1"		},
{ 0,	LOREG,		2,		"r2"		},
{ 0,	LOREG,		3,		"r3"		},
{ 0,	LOREG,		4,		"r4"		},
{ 0,	LOREG,		5,		"r5"		},
{ 0,	LOREG,		6,		"r6"		},
{ 0,	LOREG,		7,		"r7"		},
{ 0,	HIREG,		8,		"r8"		},
{ 0,	HIREG,		8,		"r8"		},
{ 0,	HIREG,		9,		"r9"		},
{ 0,	HIREG,		9,		"r9"		},
{ 0,	HIREG,		10,		"r10"		},
{ 0,	HIREG,		11,		"r11"		},
{ 0,	HIREG,		12,		"r12"		},
{ 0,	HIREG,		13,		"r13"		},
{ 0,	HIREG,		14,		"r14"		},
{ 0,	HIREG,		15,		"r15"		},

/* aliases for V2 architecture */
{ 0,	LOREG,		4,		"a0"		},
{ 0,	LOREG,		5,		"a1"		},
{ 0,	LOREG,		6,		"a2"		},
{ 0,	LOREG,		7,		"a3"		},
{ 0,	HIREG,		8,		"a4"		},
{ 0,	HIREG,		9,		"a5"		},
{ 0,	HIREG,		10,		"a6"		},
{ 0,	HIREG,		11,		"a7"		},
{ 0,	HIREG,		14,		"sp"		},
{ 0,	HIREG,		15,		"lr"		},

/* co-processor registers */
{ 0,	CREG,		0,		"psr",		},
{ 0,	CREG,		1,		"vbr",		},
{ 0,	CREG,		2,		"epsr",		},
{ 0,	CREG,		3,		"fpsr",		},
{ 0,	CREG,		4,		"epc",		},
{ 0,	CREG,		5,		"fpc",		},
{ 0,	CREG,		6,		"ss0",		},
{ 0,	CREG,		7,		"ss1",		},
{ 0,	CREG,		8,		"ss2",		},
{ 0,	CREG,		9,		"ss3",		},
{ 0,	CREG,		10,		"ss4",		},
{ 0,	CREG,		11,		"gcr",		},
{ 0,	CREG,		12,		"gsr",		},
{ 0,	CREG,		13,		"cpidr",	},
{ 0,	CREG,		14,		"cr14",		},
{ 0,	CREG,		15,		"cr15",		},
{ 0,	CREG,		16,		"cr16",		},
{ 0,	CREG,		17,		"cfr",		},
{ 0,	CREG,		18,		"ccr",		},
{ 0,	CREG,		19,		"capr",		},
{ 0,	CREG,		20,		"pacr",		},
{ 0,	CREG,		21,		"prsr",		},
{ 0,	CREG,		22,		"cr22",		},
{ 0,	CREG,		23,		"cr23",		},
{ 0,	CREG,		24,		"cr24",		},
{ 0,	CREG,		25,		"cr25",		},
{ 0,	CREG,		26,		"cr26",		},
{ 0,	CREG,		27,		"cr27",		},
{ 0,	CREG,		28,		"cr28",		},
{ 0,	CREG,		29,		"cr29",		},
{ 0,	CREG,		30,		"cr30",		},
{ 0,	CREG,		30,		"cr31",		},

/* instructions */
{ 0,	MTCR,		0xc006,		"mtcr"		},	/* 32-bit */
{ 0,	MTCR,		1,		"mfcr"		},	/* 32-bit */

{ 0,	IMPL,		0x1460,		"nie"		},
{ 0,	IMPL,		0x1461,		"nir"		},
{ 0,	IMPL,		0x0000,		"bkpt"		},

/* op reg,imm8 */
{ 0,	TWOOPIO,	0x2000,		"addi"		},	/* addi LOREG,imm8 */
{ 0,	TWOOPIO,	0x2800,		"subi"		},	/* subi LOREG,imm8 */
{ 0,	TWOOPI,		0x3000,		"movi"		},	/* movi LOREG,imm8 */

#if 0
{ 0,	ITYPE3,		0x5802,		"addi"		},	/* addi LOREG,LOREG,imm3 */
{ 0,	ITYPE3,		0x5803,		"subi"		},	/* subi LOREG,LOREG,imm3 */

{ 0,	ITYPE8_2,	0x1400,		"addi"		},	/* addi SP,SP,imm */
{ 0,	ITYPE8_2,	0x1420,		"subi"		},	/* subi SP,SP,imm */

{ 0,	ITYPE8_1,	0x1800,		"addi"		},	/* addi r0,sp,1 */

{ 0,	ITYPE5_1,	0x3880,		"bclri"		},	/* bclri LOREG,imm5 */
#endif

/* op reg,imm5 */
{ 0,	BIT,		0x3840,		"cmpnei"	},	/* cmpnei LOREG,imm5 */		/* ITYPE5_3 */
{ 0,	BIT,		0x38A0,		"bseti"		},	/* bseti LOREG,imm5 */		/* ITYPE5_3 */
{ 0,	BIT,		0x38C0,		"btsti"		},	/* btsti LOREG,imm5 */		/* ITYPE5_3 */

{ 0,	BITO,		0x3800,		"cmphsi"	},	/* cmphsi LOREG,offset5 */	/* ITYPE5_3 */
{ 0,	BITO,		0x3820,		"cmplti"	},	/* cmplti LOREG,offset5 */	/* ITYPE5_3 */

/* op reg,reg,imm */
{ 0,	ITYPE5_1,	0x5000,		"asri"		},	/* asri r0,r1,1 */
{ 0,	ITYPE5_1,	0,		"lsli"		},
{ 0,	ITYPE5_1,	0,		"lsri"		},

{ 0,	XXX,		0,		"ixh"		},	/* 32-bit */

{ 0,	RTYPE2,		0x6001,		"addc"		},	/* addc REG,REG */
{ 0,	XXX,		0x6003,		"subc"		},	/* subc REG,REG */

/* op r1,imm */
{ 0,	XXX,		0,		"lr"		},

/* op r1,addr */
{ 0,	LRW,		0,		"lrw"		},	/* relative */			// ITYPE7
{ 0,	LDST,		0x0,		"ld.b"		},	/* ld.b LOREG,(LOREG,disp) */
{ 0,	LDST,		0x1,		"ld.h"		},	/* ld.h LOREG,(LOREG,disp) */
{ 0,	LDST,		0x2,		"ld.w"		},	/* ld.w LOREG,(LOREG,disp) */
{ 0,	LDST,		0x4,		"st.b"		},	/* st.b LOREG,(LOREG,disp) */
{ 0,	LDST,		0x5,		"st.h"		},	/* st.h LOREG,(LOREG,disp) */
{ 0,	LDST,		0x6,		"st.w"		},	/* st.h LOREG,(LOREG,disp) */
{ 0,	XXX,		0,		"movl"		}, 

/* op r1,r2 */
{ 0,	TWOOP,		0x6000,		"addu"		},	/* addu REG,REG */
{ 0,	TWOOP,		0x6001,		"addc"		},	/* addc REG,REG */
{ 0,	TWOOP,		0x6002,		"subu"		},	/* subu REG,REG */
{ 0,	TWOOP,		0x6003,		"subc"		},	/* subc REG,REG */

{ 0,	TWOOP,		0x6400,		"cmphs"		}, 
{ 0,	TWOOP,		0x6401,		"cmplt"		}, 
{ 0,	TWOOP,		0x6402,		"cmpne"		}, 

{ 0,	TWOOP,		0x6800,		"and"		},	/* and REG,REG */
{ 0,	TWOOP,		0x6801,		"andn"		},	/* andn REG,REG */

{ 0,	TWOOP,		0x6C00,		"or"		},
{ 0,	TWOOP,		0x6C01,		"xor"		},
{ 0,	TWOOP,		0x6C02,		"nor"		},
{ 0,	TWOOP,		0x6C03,		"mov"		}, 	/* mov REG,REG */

{ 0,	TWOOP,		0x7000,		"lsl"		},
{ 0,	TWOOP,		0x7001,		"lsr"		},
{ 0,	TWOOP,		0x7002,		"asr"		},	/* asr REG,REG */
{ 0,	TWOOP,		0x7003,		"rotl"		},
{ 0,	TWOOP,		0x7C00,		"mult"		},
{ 0,	TWOOP,		0x7C01,		"mulsh"		},

{ 0,	XXX,		0,		"mvcv"		}, 	/* C bit reverse move */ /* mvcv rz */
{ 0,	XXX,		0,		"ixw"		},	/* 32-bit */

{ 0,	RTYPE3,		0x5800,		"add"		},	/* add LOREG,LOREG,LOREG */ 
{ 0,	RTYPE3,		0x5801,		"sub"		},	/* sub LOREG,LOREG,LOREG */

/* op r1 */
{ 0,	XXX,		0,		"tst"		},
{ 0,	XXX,		0,		"tstnbz"	},
{ 0,	XXX,		0,		"not"		},
{ 0,	XXX,		0,		"inct"		},	/* 32-bit */
{ 0,	XXX,		0,		"dect"		},	/* 32-bit */
{ 0,	XXX,		0,		"jmp"		},
{ 0,	JSR,		0xE,		"jsr"		},
{ 0,	XXX,		0,		"mthi"		},	/* 32-bit */
{ 0,	XXX,		0,		"mtlo"		},	/* 32-bit */
{ 0,	IMPL,		0,		"mfhi"		},	/* 32-bit */
{ 0,	IMPL,		0,		"mflo"		},	/* 32-bit */
{ 0,	IMPL,		0,		"mfhis"		},	/* 32-bit */
{ 0,	IMPL,		0,		"mflos"		},	/* 32-bit */
{ 0,	XXX,		0,		"zextb"		},
{ 0,	XXX,		0,		"zexth"		},
{ 0,	XXX,		0,		"sextb"		},
{ 0,	XXX,		0,		"sexth"		},
{ 0,	XXX,		0,		"revb"		},
{ 0,	XXX,		0,		"revh"		},
{ 0,	XXX,		0,		"push"		},
{ 0,	XXX,		0,		"pop"		},
{ 0,	XXX,		0x14E0,		"bpush.h"	},
{ 0,	XXX,		0x14E2,		"bpush.w"	},
{ 0,	XXX,		0x14A0,		"bpop.h"	},	/* bpop.h r0 */
{ 0,	XXX,		0x14A2,		"bpop.w"	},	/* bpop.w r0 */
{ 0,	XXX,		0,		"ipush"		},
{ 0,	XXX,		0,		"ipop"		},

/* branch */
/* op label */
{ 0,	JTYPE,		0x3,		"bf"		},	/* branch if carry false */
{ 0,	JTYPE,		0x1,		"br"		},	/* unconditional, relative */

{ 0,	BRANCH,		0,		"bt"		},	/* branch if carry true */
{ 0,	BRANCH,		0,		"bsr"		},	/* relative */ /* 32-bit */
{ 0,	BRANCH,		0,		"jbf"		},
{ 0,	BRANCH,		0,		"jsri"		},	/* absolute */
{ 0,	BRANCH,		0,		"jmpi"		},	/* absolute */
{ 0,	BRANCH,		0,		"jmpix"		},	/* absolute */

/* pseudo instructions */
{ 0,	BRANCH,		0,		"clrc"		},	/* cmpne */
{ 0,	BRANCH,		0,		"cmplei"	},	/* cmplti */
{ 0,	XXX,		0,		"cmpls"		}, 
{ 0,	XXX,		0,		"cmpgt"		}, 
{ 0,	XXX,		0,		"jbsr"		}, 	/* bsr or jsri */

{ 0,	XXX,		0,		"jbr"		}, 	/* br or jmpi */

{ 0,	XXX,		0,		"jbf"		}, 	/* bf, bt, jmpi */
{ 0,	XXX,		0,		"jbt"		}, 	/* bt, bf, jmpi */
{ 0,	XXX,		0,		"neg"		}, 	/* rsubi */
{ 0,	XXX,		0,		"rotlc"		}, 	/* addc */
{ 0,	XXX,		0,		"rotri"		}, 	/* rotli */
{ 0,	IMPL,		0x783C,		"rts"		}, 	/* jmp LR */
{ 0,	XXX,		0,		"setc"		}, 	/* cmphs */
{ 0,	XXX,		0,		"tstle"		}, 	/* cmplti */
{ 0,	XXX,		0,		"tstlt"		}, 	/* btsti */
{ 0,	XXX,		0,		"tstne"		}, 	/* cmpnei */
{ 0,	IMPL,		0x6C03,		"nop"		},	/* mov R0,R0 */
