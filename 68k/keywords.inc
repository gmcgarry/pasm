/*
 * Copyright (c) 1987, 1990, 1993, 2005 Vrije Universiteit, Amsterdam, The Netherlands.
 * All rights reserved.
 * 
 * Redistribution and use of the Amsterdam Compiler Kit in source and
 * binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 *    * Redistributions of source code must retain the above copyright
 *      notice,	this list of conditions and the following disclaimer.
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
 * WHETHER IN CONTRACT,	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Motorola 68000/68010 keywords
 */

/* compatibility */
#ifdef COMPAT
{ 0,	'=',		0,		"equ"	},
{ 0,	PSEUDOOP_ORG,	0,		"org"	},
{ 0,	PSEUDOOP_END,	0,		"end"	},

{ 0,	PSEUDOOP_DATA,	1,		"db"	},
{ 0,	PSEUDOOP_DATA,	2,		"dw"	},
{ 0,	PSEUDOOP_DATA,	4,		"dl"	},
#endif

{ 0,	DEFZERO,	0,		"ds"	},	 /* define storage */
{ 0,	DEFCONST,	0,		"dc"	},
{ 0,	DEFBLOCK,	0,		"dcb"   },

{ 0,	PSEUDOOP_DATA,	1,		"fcb"	},	/* form constant byte */
{ 0,	PSEUDOOP_DATA,	2,		"fdb"	},	/* form double byte */
{ 0,	PSEUDOOP_DATA,	1,		"fcc"	},	/* form constant character */
{ 0,	PSEUDOOP_ASCII,	0,		"fcs"	},	/* form constant character */
{ 0,	PSEUDOOP_ZERO,	1,		"rmb"	},	/* reserve memory byte */

{ 0,	MOVE,		0,		"movea"	},	/* alias */
{ 0,	MOVE,		0,		"moveq"	},	/* alias */

{ 0,	MODEL,		MODEL_68000,	".68000"	},
{ 0,	MODEL,		MODEL_68010,	".68010"	},
{ 0,	MODEL,		MODEL_68020,	".68020"	},
{ 0,	MODEL,		MODEL_68030,	".68030"	},
{ 0,	MODEL,		MODEL_68040,	".68040"	},

{ 0,	SIZE,		SIZE_B,		".b"	},
{ 0,	SIZE,		SIZE_W,		".w"	},
{ 0,	SIZE,		SIZE_L,		".l"	},

{ 0,	DREG,		00,		"d0"	},
{ 0,	DREG,		01,		"d1"	},
{ 0,	DREG,		02,		"d2"	},
{ 0,	DREG,		03,		"d3"	},
{ 0,	DREG,		04,		"d4"	},
{ 0,	DREG,		05,		"d5"	},
{ 0,	DREG,		06,		"d6"	},
{ 0,	DREG,		07,		"d7"	},

{ 0,	AREG,		00,		"a0"	},
{ 0,	AREG,		01,		"a1"	},
{ 0,	AREG,		02,		"a2"	},
{ 0,	AREG,		03,		"a3"	},
{ 0,	AREG,		04,		"a4"	},
{ 0,	AREG,		05,		"a5"	},
{ 0,	AREG,		06,		"a6"	},
{ 0,	AREG,		06,		"fp"	},
{ 0,	AREG,		07,		"a7"	},
{ 0,	AREG,		07,		"sp"	},

{ 0,	PC,		8,		"pc"	},

{ 0,	CREG,		04001,		"vbr"	},
{ 0,	CREG,		0,		"sfc"	},
{ 0,	CREG,		00001,		"dfc"	},

{ 0,	SPEC,		075,		"usp"	},
{ 0,	SPEC,		076,		"ccr"	},
{ 0,	SPEC,		077,		"sr"	},

#ifdef COMPAT_GAS
{ 0,	DREG,		00,		"%d0"	},
{ 0,	DREG,		01,		"%d1"	},
{ 0,	DREG,		02,		"%d2"	},
{ 0,	DREG,		03,		"%d3"	},
{ 0,	DREG,		04,		"%d4"	},
{ 0,	DREG,		05,		"%d5"	},
{ 0,	DREG,		06,		"%d6"	},
{ 0,	DREG,		07,		"%d7"	},

{ 0,	AREG,		00,		"%a0"	},
{ 0,	AREG,		01,		"%a1"	},
{ 0,	AREG,		02,		"%a2"	},
{ 0,	AREG,		03,		"%a3"	},
{ 0,	AREG,		04,		"%a4"	},
{ 0,	AREG,		05,		"%a5"	},
{ 0,	AREG,		06,		"%a6"	},
{ 0,	AREG,		06,		"%fp"	},
{ 0,	AREG,		07,		"%a7"	},
{ 0,	AREG,		07,		"%sp"	},
{ 0,	PC,		8,		"%pc"	},

{ 0,	CREG,		04001,		"%vbr"	},
{ 0,	CREG,		0,		"%sfc"	},
{ 0,	CREG,		00001,		"%dfc"	},

{ 0,	SPEC,		075,		"%usp"	},
{ 0,	SPEC,		076,		"%ccr"	},
{ 0,	SPEC,		077,		"%sr"	},
#endif

{ 0,	ABCD,		0140400,	"abcd"	},
{ 0,	ABCD,		0100400,	"sbcd"	},

{ 0,	ADDX,		0150400,	"addx"	},
{ 0,	ADDX,		0110400,	"subx"	},

{ 0,	ADD,		0153300,	"add"	},
#ifdef  COMPAT
{ 0,	ADD,		0153300,	"adda"	},
{ 0,	ADD,		0153300,	"addi"	},
{ 0,	ADD,		0153300,	"addq"	},
#endif
{ 0,	ADD,		0112700,	"sub"	},
#ifdef  COMPAT
{ 0,	ADD,		0112700,	"subi"	},
{ 0,	ADD,		0112700,	"subq"	},
#endif

{ 0,	AND,		0141000,	"and"	},
#ifdef  COMPAT
{ 0,	AND,		0141000,	"andi"	},
#endif
{ 0,	AND,		0135000,	"eor"	},
#ifdef  COMPAT
{ 0,	AND,		0135000,	"eori"	},
#endif
{ 0,	AND,		0100000,	"or"	},
#ifdef  COMPAT
{ 0,	AND,		0100000,	"ori"	},
#endif

{ 0,	BITOP,		0000,		"btst"	},
{ 0,	BITOP,		0100,		"bchg"	},
{ 0,	BITOP,		0200,		"bclr"	},
{ 0,	BITOP,		0300,		"bset"	},

{ 0,	SHIFT,		0160340,	"asr"	},
{ 0,	SHIFT,		0160740,	"asl"	},
{ 0,	SHIFT,		0161350,	"lsr"	},
{ 0,	SHIFT,		0161750,	"lsl"	},
{ 0,	SHIFT,		0162360,	"roxr"	},
{ 0,	SHIFT,		0162760,	"roxl"	},
{ 0,	SHIFT,		0163370,	"ror"	},
{ 0,	SHIFT,		0163770,	"rol"	},

{ 0,	SZ_EA,		041000|DTA|ALT,	"clr"	},
{ 0,	SZ_EA,		042000|DTA|ALT,	"neg"	},
{ 0,	SZ_EA,		040000|DTA|ALT,	"negx"	},
{ 0,	SZ_EA,		043000|DTA|ALT,	"not"	},
{ 0,	SZ_EA,		045000|DTA|ALT,	"tst"	},

{ 0,	OP_EA,		044000|DTA|ALT,	"nbcd"	},
{ 0,	OP_EA,		045300|DTA|ALT,	"tas"	},
{ 0,	OP_EA,		047200|CTR,	"jsr"	},
{ 0,	OP_EA,		047300|CTR,	"jmp"	},
{ 0,	OP_EA,		044100|CTR,	"pea"	},

{ 0,	CALLM,		0003300,	"callm"	},		/* 68020 - #<data>,<ea> */
{ 0,	RTM,		0,		"rtm"	},		/* 68020 - Rn */

{ 0,	MOVE16,		0173000,	"move16"	},	/* 68040 */

{ 0,	PMOVE,		0170000,	"pmove"	},		/* 68030 */

{ 0,	OP_EA,		050300,		"st"	},
{ 0,	OP_EA,		050700,		"sf"	},
{ 0,	OP_EA,		051300,		"shi"	},
{ 0,	OP_EA,		051700,		"sls"	},
{ 0,	OP_EA,		052300,		"scc"	},
{ 0,	OP_EA,		052700,		"scs"	},
{ 0,	OP_EA,		053300,		"sne"	},
{ 0,	OP_EA,		053700,		"seq"	},
{ 0,	OP_EA,		054300,		"svc"	},
{ 0,	OP_EA,		054700,		"svs"	},
{ 0,	OP_EA,		055300,		"spl"	},
{ 0,	OP_EA,		055700,		"smi"	},
{ 0,	OP_EA,		056300,		"sge"	},
{ 0,	OP_EA,		056700,		"slt"	},
{ 0,	OP_EA,		057300,		"sgt"	},
{ 0,	OP_EA,		057700,		"sle"	},

{ 0,	OP_NOOP,	047160,		"reset"	},
{ 0,	OP_NOOP,	047161,		"nop"	},
{ 0,	OP_NOOP,	047163,		"rte"	},
{ 0,	OP_NOOP,	047165,		"rts"	},
{ 0,	OP_NOOP,	047166,		"trapv"	},
{ 0,	OP_NOOP,	047167,		"rtr"	},
{ 0,	OP_NOOP,	045374,		"illegal"	},

#if 0
{ 0,	OP_EA_D,	040600,		"chk"	},
{ 0,	OP_EA_D,	0100300,	"divu"	},
{ 0,	OP_EA_D,	0100700,	"divs"	},
{ 0,	OP_EA_D,	0140300,	"mulu"	},
{ 0,	OP_EA_D,	0140700,	"muls"	},
#endif

{ 0,	DIVMUL,		0100,		"divu"	},
{ 0,	DIVMUL,		0101,		"divs"	},
{ 0,	DIVMUL,		0000,		"mulu"	},
{ 0,	DIVMUL,		0001,		"muls"	},

{ 0,	DIVL,		046100,		"divul" },
{ 0,	DIVL,		046101,		"divsl" },

{ 0,	BR,		060000,		"bra"	},
{ 0,	BR,		060400,		"bsr"	},
{ 0,	BR,		061000,		"bhi"	},
{ 0,	BR,		061400,		"bls"	},
{ 0,	BR,		062000,		"bcc"	},
{ 0,	BR,		062400,		"bcs"	},
#ifdef COMPAT
{ 0,	BR,		062400,		"blo"	},
#endif
{ 0,	BR,		063000,		"bne"	},
{ 0,	BR,		063400,		"beq"	},
{ 0,	BR,		064000,		"bvc"	},
{ 0,	BR,		064400,		"bvs"	},
{ 0,	BR,		065000,		"bpl"	},
{ 0,	BR,		065400,		"bmi"	},
{ 0,	BR,		066000,		"bge"	},
{ 0,	BR,		066400,		"blt"	},
{ 0,	BR,		067000,		"bgt"	},
{ 0,	BR,		067400,		"ble"	},

/* apparently from the SUN tools */
#ifdef COMPAT_GAS
{ 0,	BR,		060000,		"jra"	},
{ 0,	BR,		060400,		"jbsr"	},
{ 0,	BR,		061000,		"jhi"	},
{ 0,	BR,		061400,		"jls"	},
{ 0,	BR,		062000,		"jcc"	},
{ 0,	BR,		062400,		"jcs"	},
{ 0,	BR,		063000,		"jne"	},
{ 0,	BR,		063400,		"jeq"	},
{ 0,	BR,		064000,		"jvc"	},
{ 0,	BR,		064400,		"jvs"	},
{ 0,	BR,		065000,		"jpl"	},
{ 0,	BR,		065400,		"jmi"	},
{ 0,	BR,		066000,		"jge"	},
{ 0,	BR,		066400,		"jlt"	},
{ 0,	BR,		067000,		"jgt"	},
{ 0,	BR,		067400,		"jle"	},
#endif

{ 0,	DBR,		050310,		"dbt"	},
{ 0,	DBR,		050710,		"dbf"	},
{ 0,	DBR,		050710,		"dbra"	},
{ 0,	DBR,		051310,		"dbhi"	},
{ 0,	DBR,		051710,		"dbls"	},
{ 0,	DBR,		052310,		"dbcc"	},
{ 0,	DBR,		052710,		"dbcs"	},
{ 0,	DBR,		053310,		"dbne"	},
{ 0,	DBR,		053710,		"dbeq"	},
{ 0,	DBR,		054310,		"dbvc"	},
{ 0,	DBR,		054710,		"dbvs"	},
{ 0,	DBR,		055310,		"dbpl"	},
{ 0,	DBR,		055710,		"dbmi"	},
{ 0,	DBR,		056310,		"dbge"	},
{ 0,	DBR,		056710,		"dblt"	},
{ 0,	DBR,		057310,		"dbgt"	},
{ 0,	DBR,		057710,		"dble"	},

{ 0,	CMP,		0,		"cmp"	},
#ifdef COMPAT
{ 0,	CMP,		0,		"cmpi"	},
{ 0,	CMP,		0,		"cmpa"	},
{ 0,	CMP,		0,		"cmpm"	},
#endif

{ 0,	MOVE,		0,		"move"	},
{ 0,	MOVEP,		0,		"movep"	},
{ 0,	MOVEM,		0,		"movem"	},
{ 0,	MOVES,		0,		"moves"	},
{ 0,	MOVEC,		0,		"movec"	},

{ 0,	SWAP,		0,		"swap"	},

{ 0,	LINK,		0,		"link"	},

{ 0,	UNLK,		0,		"unlk"	},

{ 0,	TRAP,		0,		"trap"	},

{ 0,	STOP,		047162,		"stop"	},

{ 0,	EXG,		0,		"exg"	},

{ 0,	OP_EXT,		0,		"ext"	},
{ 0,	OP_EXT,		1,		"extb"	},

{ 0,	LEA,		0,		"lea"	},

{ 0,	RTD,		0,		"rtd"	},

/* M68030 MMU registers */
{ 0,	MREG,		0040000,	"tc" },
{ 0,	MREG,		0044000,	"srp" },
{ 0,	MREG,		0046000,	"crp" },
{ 0,	MREG,		0060000,	"mmusr" },
{ 0,	MREG,		0060000,	"psr" },
{ 0,	MREG,		0004000,	"tt0" },
{ 0,	MREG,		0006000,	"tt1" },

#ifdef COMPAT_GAS
{ 0,	MREG,		0040000,	"%tc" },
{ 0,	MREG,		0044000,	"%srp" },
{ 0,	MREG,		0046000,	"%crp" },
{ 0,	MREG,		0060000,	"%mmusr" },
{ 0,	MREG,		0060000,	"%psr" },
{ 0,	MREG,		0004000,	"%tt0" },
{ 0,	MREG,		0006000,	"%tt1" },

#endif

/* M68030 MMU instructions */

{ 0,	PFLUSHA,	0022000,	"pflusha" },
{ 0,	PFLUSH,		0020000,	"pflush" },
{ 0,	PLOAD,		0021000,	"ploadr" },
{ 0,	PLOAD,		0020000,	"ploadw" },
{ 0,	PTEST,		0101000,	"ptestr" },
{ 0,	PTEST,		0100000,	"ptestw" },
{ 0,	PMOVE,		0000000,	"pmove" },
{ 0,	PMOVE,		0000400,	"pmovefd" },

/* floating point coprocessor ... */

{ 0,	FSIZE,		FSIZE_S,	".s"	},
{ 0,	FSIZE,		FSIZE_X,	".x"	},
{ 0,	FSIZE,		FSIZE_P,	".p"	},
{ 0,	FSIZE,		FSIZE_D,	".d"	},

{ 0,	FPREG,		0,		"fp0"	},
{ 0,	FPREG,		1,		"fp1"	},
{ 0,	FPREG,		2,		"fp2"	},
{ 0,	FPREG,		3,		"fp3"	},
{ 0,	FPREG,		4,		"fp4"	},
{ 0,	FPREG,		5,		"fp5"	},
{ 0,	FPREG,		6,		"fp6"	},
{ 0,	FPREG,		7,		"fp7"	},

{ 0,	FPCR,		1,		"fpiar"	},
{ 0,	FPCR,		2,		"fpsr"	},
{ 0,	FPCR,		4,		"fpcr"	},

#ifdef COMPAT_GAS
{ 0,	FPREG,		0,		"%fp0"	},
{ 0,	FPREG,		1,		"%fp1"	},
{ 0,	FPREG,		2,		"%fp2"	},
{ 0,	FPREG,		3,		"%fp3"	},
{ 0,	FPREG,		4,		"%fp4"	},
{ 0,	FPREG,		5,		"%fp5"	},
{ 0,	FPREG,		6,		"%fp6"	},
{ 0,	FPREG,		7,		"%fp7"	},

{ 0,	FPCR,		1,		"%fpiar"	},
{ 0,	FPCR,		2,		"%fpsr"		},
{ 0,	FPCR,		4,		"%fpcr"		},
#endif

{ 0,	FMOVE,		0,		"fmove"		},
{ 0,	FMOVECR,	0,		"fmovecr"	},
{ 0,	FMOVEM,		0,		"fmovem"	},

{ 0,	FDYADIC,	042,		"fadd"		},
{ 0,	FDYADIC,	070,		"fcmp"		},
{ 0,	FDYADIC,	040,		"fdiv"		},
{ 0,	FDYADIC,	041,		"fmod"		},
{ 0,	FDYADIC,	043,		"fmul"		},
{ 0,	FDYADIC,	045,		"frem"		},
{ 0,	FDYADIC,	046,		"fscale"	},
{ 0,	FDYADIC,	044,		"fsgldiv"	},
{ 0,	FDYADIC,	047,		"fsglmul"	},
{ 0,	FDYADIC,	050,		"fsub"		},

{ 0,	FMONADIC,	030,		"fabs"		},
{ 0,	FMONADIC,	034,		"facos"		},
{ 0,	FMONADIC,	014,		"fasin"		},
{ 0,	FMONADIC,	012,		"fatan"		},
{ 0,	FMONADIC,	015,		"fatanh"	},
{ 0,	FMONADIC,	035,		"fcos"		},
{ 0,	FMONADIC,	031,		"fcosh"		},
{ 0,	FMONADIC,	020,		"fetox"		},
{ 0,	FMONADIC,	010,		"fetoxm1"	},
{ 0,	FMONADIC,	036,		"fgetexp"	},
{ 0,	FMONADIC,	037,		"fgetman"	},
{ 0,	FMONADIC,	001,		"fint"		},
{ 0,	FMONADIC,	003,		"fintrz"	},
{ 0,	FMONADIC,	024,		"flogn"		},
{ 0,	FMONADIC,	006,		"flognp1"	},
{ 0,	FMONADIC,	025,		"flog10"	},
{ 0,	FMONADIC,	026,		"flog2"		},
{ 0,	FMONADIC,	032,		"fneg"		},
{ 0,	FMONADIC,	016,		"fsin"		},
{ 0,	FMONADIC,	002,		"fsinh"		},
{ 0,	FMONADIC,	004,		"fsqrt"		},
{ 0,	FMONADIC,	017,		"ftan"		},
{ 0,	FMONADIC,	011,		"ftanh"		},
{ 0,	FMONADIC,	022,		"ftentox"	},
{ 0,	FMONADIC,	021,		"ftwotox"	},

{ 0,	FSINCOS,	060,		"fsincos"	},

{ 0,	FBCC,		001,		"fbeq"		},
{ 0,	FBCC,		016,		"fbne"		},
{ 0,	FBCC,		022,		"fbgt"		},
{ 0,	FBCC,		035,		"fbngt"		},
{ 0,	FBCC,		023,		"fbge"		},
{ 0,	FBCC,		034,		"fbnge"		},
{ 0,	FBCC,		024,		"fblt"		},
{ 0,	FBCC,		033,		"fbnlt"		},
{ 0,	FBCC,		025,		"fble"		},
{ 0,	FBCC,		032,		"fbnle"		},
{ 0,	FBCC,		026,		"fbgl"		},
{ 0,	FBCC,		031,		"fbngl"		},
{ 0,	FBCC,		027,		"fbgle"		},
{ 0,	FBCC,		030,		"fbngle"	},
{ 0,	FBCC,		002,		"fbogt"		},
{ 0,	FBCC,		015,		"fbule"		},
{ 0,	FBCC,		003,		"fboge"		},
{ 0,	FBCC,		014,		"fbult"		},
{ 0,	FBCC,		004,		"fbolt"		},
{ 0,	FBCC,		013,		"fbuge"		},
{ 0,	FBCC,		005,		"fbole"		},
{ 0,	FBCC,		012,		"fbugt"		},
{ 0,	FBCC,		006,		"fbogl"		},
{ 0,	FBCC,		011,		"fbueq"		},
{ 0,	FBCC,		007,		"fbor"		},
{ 0,	FBCC,		010,		"fbun"		},
{ 0,	FBCC,		000,		"fbf"		},
{ 0,	FBCC,		017,		"fbt"		},
{ 0,	FBCC,		020,		"fbsf"		},
{ 0,	FBCC,		037,		"fbst"		},
{ 0,	FBCC,		021,		"fbseq"		},
{ 0,	FBCC,		036,		"fbsne"		},

#ifdef COMPAT_GAS
{ 0,	FBCC,		001,		"fjeq"		},
{ 0,	FBCC,		016,		"fjne"		},
{ 0,	FBCC,		022,		"fjgt"		},
{ 0,	FBCC,		035,		"fjngt"		},
{ 0,	FBCC,		023,		"fjge"		},
{ 0,	FBCC,		034,		"fjnge"		},
{ 0,	FBCC,		024,		"fjlt"		},
{ 0,	FBCC,		033,		"fjnlt"		},
{ 0,	FBCC,		025,		"fjle"		},
{ 0,	FBCC,		032,		"fjnle"		},
{ 0,	FBCC,		026,		"fjgl"		},
{ 0,	FBCC,		031,		"fjngl"		},
{ 0,	FBCC,		027,		"fjgle"		},
{ 0,	FBCC,		030,		"fjngle"	},
{ 0,	FBCC,		002,		"fjogt"		},
{ 0,	FBCC,		015,		"fjule"		},
{ 0,	FBCC,		003,		"fjoge"		},
{ 0,	FBCC,		014,		"fjult"		},
{ 0,	FBCC,		004,		"fjolt"		},
{ 0,	FBCC,		013,		"fjuge"		},
{ 0,	FBCC,		005,		"fjole"		},
{ 0,	FBCC,		012,		"fjugt"		},
{ 0,	FBCC,		006,		"fjogl"		},
{ 0,	FBCC,		011,		"fjueq"		},
{ 0,	FBCC,		007,		"fjor"		},
{ 0,	FBCC,		010,		"fjun"		},
{ 0,	FBCC,		000,		"fjf"		},
{ 0,	FBCC,		017,		"fjt"		},
{ 0,	FBCC,		020,		"fjsf"		},
{ 0,	FBCC,		037,		"fjst"		},
{ 0,	FBCC,		021,		"fjseq"		},
{ 0,	FBCC,		036,		"fjsne"		},
#endif

{ 0,	FDBCC,		001,		"fdbeq"		},
{ 0,	FDBCC,		016,		"fdbne"		},
{ 0,	FDBCC,		022,		"fdbgt"		},
{ 0,	FDBCC,		035,		"fdbngt"	},
{ 0,	FDBCC,		023,		"fdbge"		},
{ 0,	FDBCC,		034,		"fdbnge"	},
{ 0,	FDBCC,		024,		"fdblt"		},
{ 0,	FDBCC,		033,		"fdbnlt"	},
{ 0,	FDBCC,		025,		"fdble"		},
{ 0,	FDBCC,		032,		"fdbnle"	},
{ 0,	FDBCC,		026,		"fdbgl"		},
{ 0,	FDBCC,		031,		"fdbngl"	},
{ 0,	FDBCC,		027,		"fdbgle"	},
{ 0,	FDBCC,		030,		"fdbngle"	},
{ 0,	FDBCC,		002,		"fdbogt"	},
{ 0,	FDBCC,		015,		"fdbule"	},
{ 0,	FDBCC,		003,		"fdboge"	},
{ 0,	FDBCC,		014,		"fdbult"	},
{ 0,	FDBCC,		004,		"fdbolt"	},
{ 0,	FDBCC,		013,		"fdbuge"	},
{ 0,	FDBCC,		005,		"fdbole"	},
{ 0,	FDBCC,		012,		"fdbugt"	},
{ 0,	FDBCC,		006,		"fdbogl"	},
{ 0,	FDBCC,		011,		"fdbueq"	},
{ 0,	FDBCC,		007,		"fdbor"		},
{ 0,	FDBCC,		010,		"fdbun"		},
{ 0,	FDBCC,		000,		"fdbf"		},
{ 0,	FDBCC,		017,		"fdbt"		},
{ 0,	FDBCC,		020,		"fdbsf"		},
{ 0,	FDBCC,		037,		"fdbst"		},
{ 0,	FDBCC,		021,		"fdbseq"	},
{ 0,	FDBCC,		036,		"fdbsne"	},

{ 0,	FNOP,		0,		"fnop"		},

{ 0,	FSCC,		001,		"fseq"		},
{ 0,	FSCC,		016,		"fsne"		},
{ 0,	FSCC,		022,		"fsgt"		},
{ 0,	FSCC,		035,		"fsngt"		},
{ 0,	FSCC,		023,		"fsge"		},
{ 0,	FSCC,		034,		"fsnge"		},
{ 0,	FSCC,		024,		"fslt"		},
{ 0,	FSCC,		033,		"fsnlt"		},
{ 0,	FSCC,		025,		"fsle"		},
{ 0,	FSCC,		032,		"fsnle"		},
{ 0,	FSCC,		026,		"fsgl"		},
{ 0,	FSCC,		031,		"fsngl"		},
{ 0,	FSCC,		027,		"fsgle"		},
{ 0,	FSCC,		030,		"fsngle"	},
{ 0,	FSCC,		002,		"fsogt"		},
{ 0,	FSCC,		015,		"fsule"		},
{ 0,	FSCC,		003,		"fsoge"		},
{ 0,	FSCC,		014,		"fsult"		},
{ 0,	FSCC,		004,		"fsolt"		},
{ 0,	FSCC,		013,		"fsuge"		},
{ 0,	FSCC,		005,		"fsole"		},
{ 0,	FSCC,		012,		"fsugt"		},
{ 0,	FSCC,		006,		"fsogl"		},
{ 0,	FSCC,		011,		"fsueq"		},
{ 0,	FSCC,		007,		"fsor"		},
{ 0,	FSCC,		010,		"fsun"		},
{ 0,	FSCC,		000,		"fsf"		},
{ 0,	FSCC,		017,		"fst"		},
{ 0,	FSCC,		020,		"fssf"		},
{ 0,	FSCC,		037,		"fsst"		},
{ 0,	FSCC,		021,		"fsseq"		},
{ 0,	FSCC,		036,		"fssne"		},

{ 0,	FTST,		0,		"ftst"		},

{ 0,	FSAVRES,	MEM|ALT|0430,	"fsave"		},
{ 0,	FSAVRES,	MEM|0540,	"frestore"	},

{ 0,	FTRAPCC,	001,		"ftrapeq"	},
{ 0,	FTRAPCC,	016,		"ftrapne"	},
{ 0,	FTRAPCC,	022,		"ftrapgt"	},
{ 0,	FTRAPCC,	035,		"ftrapngt"	},
{ 0,	FTRAPCC,	023,		"ftrapge"	},
{ 0,	FTRAPCC,	034,		"ftrapnge"	},
{ 0,	FTRAPCC,	024,		"ftraplt"	},
{ 0,	FTRAPCC,	033,		"ftrapnlt"	},
{ 0,	FTRAPCC,	025,		"ftraple"	},
{ 0,	FTRAPCC,	032,		"ftrapnle"	},
{ 0,	FTRAPCC,	026,		"ftrapgl"	},
{ 0,	FTRAPCC,	031,		"ftrapngl"	},
{ 0,	FTRAPCC,	027,		"ftrapgle"	},
{ 0,	FTRAPCC,	030,		"ftrapngle"	},
{ 0,	FTRAPCC,	002,		"ftrapogt"	},
{ 0,	FTRAPCC,	015,		"ftrapule"	},
{ 0,	FTRAPCC,	003,		"ftrapoge"	},
{ 0,	FTRAPCC,	014,		"ftrapult"	},
{ 0,	FTRAPCC,	004,		"ftrapolt"	},
{ 0,	FTRAPCC,	013,		"ftrapuge"	},
{ 0,	FTRAPCC,	005,		"ftrapole"	},
{ 0,	FTRAPCC,	012,		"ftrapugt"	},
{ 0,	FTRAPCC,	006,		"ftrapogl"	},
{ 0,	FTRAPCC,	011,		"ftrapueq"	},
{ 0,	FTRAPCC,	007,		"ftrapor"	},
{ 0,	FTRAPCC,	010,		"ftrapun"	},
{ 0,	FTRAPCC,	000,		"ftrapf"	},
{ 0,	FTRAPCC,	017,		"ftrapt"	},
{ 0,	FTRAPCC,	020,		"ftrapsf"	},
{ 0,	FTRAPCC,	037,		"ftrapst"	},
{ 0,	FTRAPCC,	021,		"ftrapseq"	},
{ 0,	FTRAPCC,	036,		"ftrapsne"	},

{ 0,	CP,		00000,		"c0"	},
{ 0,	CP,		01000,		"c1"	},
{ 0,	CP,		02000,		"c2"	},
{ 0,	CP,		03000,		"c3"	},
{ 0,	CP,		04000,		"c4"	},
{ 0,	CP,		05000,		"c5"	},
{ 0,	CP,		06000,		"c6"	},
{ 0,	CP,		07000,		"c7"	},
