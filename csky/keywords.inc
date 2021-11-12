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

/* 16-bit opcodes only access 16 registers */
{ 0,	REG,		0,		"r0"		},
{ 0,	REG,		1,		"r1"		},
{ 0,	REG,		2,		"r2"		},
{ 0,	REG,		3,		"r3"		},
{ 0,	REG,		4,		"r4"		},
{ 0,	REG,		5,		"r5"		},
{ 0,	REG,		6,		"r6"		},
{ 0,	REG,		7,		"r7"		},
{ 0,	REG,		8,		"r8"		},
{ 0,	REG,		8,		"r8"		},
{ 0,	REG,		9,		"r9"		},
{ 0,	REG,		9,		"r9"		},
{ 0,	REG,		10,		"r10"		},
{ 0,	REG,		11,		"r11"		},
{ 0,	REG,		12,		"r12"		},
{ 0,	REG,		13,		"r13"		},
{ 0,	REG,		14,		"r14"		},
{ 0,	REG,		15,		"r15"		},

/* these are aliases for V1 architecture */
{ 0,	REG,		0,		"sp"		},
{ 0,	REG,		2,		"a0"		},
{ 0,	REG,		3,		"a1"		},
{ 0,	REG,		4,		"a2"		},
{ 0,	REG,		5,		"a3"		},
{ 0,	REG,		6,		"a4"		},
{ 0,	REG,		7,		"a5"		},
{ 0,	REG,		8,		"l0"		},
{ 0,	REG,		9,		"l1"		},
{ 0,	REG,		10,		"l2"		},
{ 0,	REG,		11,		"l3"		},
{ 0,	REG,		12,		"l4"		},
{ 0,	REG,		13,		"l5"		},
{ 0,	REG,		14,		"l10"		},
{ 0,	REG,		14,		"gb"		},
{ 0,	REG,		15,		"lr"		},

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

{ 0,	IMPL,		0,		"mtcr"		},	/* 32-bit */
{ 0,	IMPL,		0,		"mfcr"		},	/* 32-bit */
{ 0,	IMPL,		0,		"nie"		},
{ 0,	IMPL,		0,		"nir"		},
{ 0,	IMPL,		0x0000,		"bkpt"		},


/* op r1,imm */
{ 0,	ITYPE8_1,	0x2000,		"addi"		},	/* addi r0,1 */
{ 0,	ITYPE3,		0x2000,		"addi"		},	/* addi r0,r1,1 */
{ 0,	ITYPE8_1,	0x1800,		"addi"		},	/* addi r0,sp,1 */
{ 0,	ITYPE8_2,	0x1400,		"addi"		},	/* addi sp,sp,1 */

{ 0,	ITYPE5_1,	0x5000,		"asri"		},	/* asri r0,r1,1 */
{ 0,	ITYPE5_1,	0x3880,		"bclri"		},	/* bclr r0,1 */

{ 0,	XXX,		0,		"movi"		},
{ 0,	XXX,		0,		"bgeni"		},
{ 0,	XXX,		0,		"bmaski"	},
{ 0,	XXX,		0,		"subi"		},
{ 0,	XXX,		0,		"lsli"		},
{ 0,	XXX,		0,		"lsri"		},
{ 0,	XXX,		0,		"rsubi"		},
{ 0,	XXX,		0,		"rotli"		},
{ 0,	XXX,		0,		"ixh"		},	/* 32-bit */
{ 0,	XXX,		0,		"rotli"		},
{ 0,	XXX,		0,		"cmpei"		},
{ 0,	XXX,		0,		"cmplei"	},
{ 0,	XXX,		0,		"cmpnei"	},
{ 0,	XXX,		0,		"cmphsi"	},
{ 0,	XXX,		0,		"cmplti"	},

{ 0,	XXX,		0,		"bseti"		},
{ 0,	XXX,		0,		"btsti"		},

{ 0,	RTYPE2,		0x6001,		"addc"		},
{ 0,	XXX,		0,		"subc"		},

/* op r1,imm */
{ 0,	XXX,		0,		"lr"		},

/* op r1,addr */

{ 0,	XXX,		0,		"ld.b"		},
{ 0,	XXX,		0,		"ld.h"		},
{ 0,	XXX,		0,		"ld.w"		},
{ 0,	XXX,		0,		"ldw"		},
{ 0,	XXX,		0,		"lrw"		},	/* relative */
{ 0,	XXX,		0,		"st.b"		},
{ 0,	XXX,		0,		"st.h"		},
{ 0,	XXX,		0,		"st.w"		},
{ 0,	XXX,		0,		"movl"		}, 
{ 0,	XXX,		0,		"subu"		},

/* op r1,r2 */
{ 0,	RTYPE2,		0x6000,		"addu"		},	/* addu r0,r1 - r0-r15 */
{ 0,	RTYPE3,		0x5800,		"addu"		},	/* addu r0,r1,r2 - r0-r7 */ 

{ 0,	RTYPE2,		0x6800,		"and"		},
{ 0,	RTYPE2,		0x6801,		"andn"		},
{ 0,	RTYPE2,		0x7002,		"asr"		},

{ 0,	XXX,		0,		"or"		},
{ 0,	XXX,		0,		"xor"		},
{ 0,	XXX,		0,		"nor"		},
{ 0,	XXX,		0,		"lsl"		},
{ 0,	XXX,		0,		"lsr"		},
{ 0,	XXX,		0,		"rotl"		},
{ 0,	XXX,		0,		"mult"		},
{ 0,	XXX,		0,		"mulsh"		},
{ 0,	XXX,		0,		"add"		},
{ 0,	XXX,		0,		"sub"		},
{ 0,	XXX,		0,		"mov"		}, 
{ 0,	XXX,		0,		"mvcv"		}, 	/* C bit reverse move */
{ 0,	XXX,		0,		"cmplt"		}, 
{ 0,	XXX,		0,		"cmphs"		}, 
{ 0,	XXX,		0,		"cmpne"		}, 
{ 0,	XXX,		0,		"ixw"		},	/* 32-bit */

/* op r1 */
{ 0,	XXX,		0,		"tst"		},
{ 0,	XXX,		0,		"tstnbz"	},
{ 0,	XXX,		0,		"not"		},
{ 0,	XXX,		0,		"inct"		},	/* 32-bit */
{ 0,	XXX,		0,		"dect"		},	/* 32-bit */
{ 0,	XXX,		0,		"jmp"		},
{ 0,	XXX,		0,		"jsr"		},
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
{ 0,	JTYPE,		0x0c00,		"bf"		},	/* branch if carry false */
{ 0,	JTYPE,		0x0400,		"br"		},	/* unconditional, relative */

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
{ 0,	XXX,		0,		"rts"		}, 	/* jmp */
{ 0,	XXX,		0,		"setc"		}, 	/* cmphs */
{ 0,	XXX,		0,		"tstle"		}, 	/* cmplti */
{ 0,	XXX,		0,		"tstlt"		}, 	/* btsti */
{ 0,	XXX,		0,		"tstne"		}, 	/* cmpnei */
