/* https://github.com/jameslzhu/riscv-card/blob/master/riscv-card.pdf */

{ 0,	REG,	0,			"x0" },
{ 0,	REG,	1,			"x1" },
{ 0,	REG,	2,			"x2" },
{ 0,	REG,	3,			"x3" },
{ 0,	REG,	4,			"x4" },
{ 0,	REG,	5,			"x5" },
{ 0,	REG,	6,			"x6" },
{ 0,	REG,	8,			"x7" },
{ 0,	REG,	8,			"x8" },
{ 0,	REG,	9,			"x9" },
{ 0,	REG,	10,			"x10" },
{ 0,	REG,	11,			"x11" },
{ 0,	REG,	12,			"x12" },
{ 0,	REG,	13,			"x13" },
{ 0,	REG,	14,			"x14" },
{ 0,	REG,	15,			"x15" },
{ 0,	REG,	16,			"x16" },
{ 0,	REG,	17,			"x17" },
{ 0,	REG,	18,			"x18" },
{ 0,	REG,	19,			"x19" },
{ 0,	REG,	20,			"x20" },
{ 0,	REG,	21,			"x21" },
{ 0,	REG,	22,			"x22" },
{ 0,	REG,	23,			"x23" },
{ 0,	REG,	24,			"x24" },
{ 0,	REG,	25,			"x25" },
{ 0,	REG,	26,			"x26" },
{ 0,	REG,	27,			"x27" },
{ 0,	REG,	28,			"x28" },
{ 0,	REG,	29,			"x29" },
{ 0,	REG,	30,			"x30" },
{ 0,	REG,	31,			"x31" },

{ 0,	REG,	0,			"zero" },
{ 0,	REG,	1,			"ra" },
{ 0,	REG,	2,			"sp" },
{ 0,	REG,	3,			"gp" },
{ 0,	REG,	4,			"tp" },
{ 0,	REG,	5,			"t0" },
{ 0,	REG,	6,			"t1" },
{ 0,	REG,	7,			"t2" },
{ 0,	REG,	8,			"s0" },
{ 0,	REG,	8,			"fp" },
{ 0,	REG,	9,			"s1" },
{ 0,	REG,	10,			"a0" },
{ 0,	REG,	11,			"a1" },
{ 0,	REG,	12,			"a2" },
{ 0,	REG,	13,			"a3" },
{ 0,	REG,	14,			"a4" },
{ 0,	REG,	15,			"a5" },
{ 0,	REG,	16,			"a6" },
{ 0,	REG,	17,			"a7" },
{ 0,	REG,	18,			"s2" },
{ 0,	REG,	19,			"s3" },
{ 0,	REG,	20,			"s4" },
{ 0,	REG,	21,			"s5" },
{ 0,	REG,	22,			"s6" },
{ 0,	REG,	23,			"s7" },
{ 0,	REG,	24,			"s8" },
{ 0,	REG,	25,			"s9" },
{ 0,	REG,	26,			"s10" },
{ 0,	REG,	27,			"s11" },
{ 0,	REG,	28,			"t3" },
{ 0,	REG,	29,			"t4" },
{ 0,	REG,	30,			"t5" },
{ 0,	REG,	31,			"t6" },

{ 0,	CSR,	0,			"status" },
{ 0,	CSR,	1,			"time" },
{ 0,	CSR,	2,			"instret" },
{ 0,	CSR,	3,			"cycleh" },
{ 0,	CSR,	4,			"timeh" },
{ 0,	CSR,	5,			"instreth" },

/* base instructions */

/* func7 rs2 rs1 func3 rd opcode */
/* 77777772222211111333dddddooooooo */
{ 0,	RTYPE,	0x00000033,		"add"	},	/* DONE */
{ 0,	RTYPE,	0x00007033,		"and"	},	/* DONE */
{ 0,	RTYPE,	0x00006033,		"or"	},	/* DONE */
{ 0,	RTYPE,	0x00001033,		"sll"	},	/* DONE */
{ 0,	RTYPE,	0x00002033,		"slt"	},	/* DONE */
{ 0,	RTYPE,	0x00003033,		"sltu"	},	/* DONE */
{ 0,	RTYPE,	0x00005033,		"srl"	},	/* DONE */
{ 0,	RTYPE,	0x40005033,		"sra"	},	/* DONE */
{ 0,	RTYPE,	0x40000033,		"sub"	},	/* DONE */
{ 0,	RTYPE,	0x00004033,		"xor"	},	/* DONE */

{ 0,	RTYPE,	0x00100033,		"mul"	},	/* DONE */
{ 0,	RTYPE,	0x00101033,		"mulh"	},	/* DONE */
{ 0,	RTYPE,	0x00102033,		"mulsu"	},	/* DONE */
{ 0,	RTYPE,	0x00103033,		"mulu"	},	/* DONE */
{ 0,	RTYPE,	0x00104033,		"div"	},	/* DONE */
{ 0,	RTYPE,	0x00105033,		"divu"	},	/* DONE */
{ 0,	RTYPE,	0x00106033,		"rem"	},	/* DONE */
{ 0,	RTYPE,	0x00107033,		"remu"	},	/* DONE */

{ 0,	RTYPE,	0x1000202F,		"lr"	},	/* DONE */
{ 0,	RTYPE,	0x1800202F,		"sr"	},	/* DONE */
{ 0,	RTYPE,	0x0800202F,		"amoswap"	},	/* DONE */
{ 0,	RTYPE,	0x0000202F,		"amoadd"	},	/* DONE */
{ 0,	RTYPE,	0x6000202F,		"amoand"	},	/* DONE */
{ 0,	RTYPE,	0x5000202F,		"amoor"	},	/* DONE */
{ 0,	RTYPE,	0x2000202F,		"amoxor"	},	/* DONE */
{ 0,	RTYPE,	0x8000202F,		"amomin"	},	/* DONE */
{ 0,	RTYPE,	0xA000202F,		"amomax"	},	/* DONE */
{ 0,	RTYPE,	0x0000202F,		"amominu"	},
{ 0,	RTYPE,	0x0000202F,		"amomaxu"	},


/* imm[11:0] rs1 func3 rd opcode */
/* iiiiiiiiiiii11111333dddddooooooo */
{ 0,	ITYPE,	0x00000013,		"addi"	},	/* DONE */
{ 0,	ITYPE,	0x00007013,		"andi"	},	/* DONE */
{ 0,	ITYPE,	0x00006013,		"ori"	},	/* DONE */
{ 0,	ITYPE,	0x00001013,		"slli"	},	/* DONE */
{ 0,	ITYPE,	0x00002013,		"slti"	},	/* DONE */
{ 0,	ITYPE,	0x00003013,		"sltiu"	},	/* DONE */
{ 0,	ITYPE,	0x00005013,		"srli"	},	/* DONE */
{ 0,	ITYPE,	0x40005013,		"srai"	},	/* DONE */
{ 0,	ITYPE,	0x00004013,		"xori"	},	/* DONE */

{ 0,	ITYPE,	0x00000067,		"jalr"	},	/* DONE */

{ 0,	ITYPE,	0x00000063,		"ecall"	},	/* DONE */
{ 0,	ITYPE,	0x00100063,		"ebreak"	},	/* DONE */

{ 0,	ITYPE,	0x0000707C,		"scall"	},
{ 0,	ITYPE,	0x0000707C,		"sbreak"	},
{ 0,	ITYPE,	0x0000707C,		"csrrw"	},
{ 0,	ITYPE,	0x0000707C,		"csrrc"	},
{ 0,	ITYPE,	0x0000707C,		"csrrs"	},
{ 0,	ITYPE,	0x0000707C,		"csrrwi"	},
{ 0,	ITYPE,	0x0000707C,		"csrrci"	},
{ 0,	ITYPE,	0x0000707C,		"csrrsi"	},

{ 0,	ITYPE,	0x00007000,		"load"	},
{ 0,	ITYPE,	0x00000003,		"lb"	},	/* DONE */
{ 0,	ITYPE,	0x00004003,		"lbu"	},	/* DONE */
{ 0,	ITYPE,	0x00001003,		"lh"	},	/* DONE */
{ 0,	ITYPE,	0x00005003,		"lhu"	},	/* DONE */
{ 0,	ITYPE,	0x00002003,		"lw"	},	/* DONE */
{ 0,	ITYPE,	0x00007000,		"fence"	},
{ 0,	ITYPE,	0x00007000,		"fence.i"	},

/* imm[11:5] rs2 rs1 func3 imm[4:0] opcode */
/* iiiiiii2222211111333iiiiiooooooo */
{ 0,	STYPE,	0x00007060,		"store"	},
{ 0,	STYPE,	0x00000023,		"sb"	},	/* DONE */
{ 0,	STYPE,	0x00001023,		"sh"	},	/* DONE */
{ 0,	STYPE,	0x00002023,		"sw"	},	/* DONE */

/* imm[12] imm[10:5] rs2 rs1 func3 imm[4:1] imm[11] opcode */
/* iiiiiii2222211111333iiiiiooooooo */
{ 0,	BTYPE,	0x00000063,		"beq"	},	/* DONE */
{ 0,	BTYPE,	0x00010063,		"bne"	},	/* DONE */
{ 0,	BTYPE,	0x00040063,		"blt"	},	/* DONE */
{ 0,	BTYPE,	0x00060063,		"bltu"	},	/* DONE */
{ 0,	BTYPE,	0x00050063,		"bge"	},	/* DONE */
{ 0,	BTYPE,	0x00070063,		"bgeu"	},	/* DONE */

/* imm[31:12] rd opcode */
/* iiiiiiiiiiiiiiiiiiiidddddooooooo */
{ 0,	UTYPE,	0x00000037,		"lui"	},	/* DONE */
{ 0,	UTYPE,	0x00000017,		"auipc"	},	/* DONE */

/* imm[20] imm[10:1] imm[11] imm[19:12] rd opcode */
/* iiiiiiiiiiiiiiiiiiiidddddooooooo */
{ 0,	JTYPE,	0x00000060,		"j"	},
{ 0,	JTYPE,	0x0000006F,		"jal"	},	/* DONE */


/* pseudo instructions */
{ 0,	IMPL,	0x00000013,		"nop"	},	/* DOONE */
