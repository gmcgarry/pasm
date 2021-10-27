/* https://github.com/jameslzhu/riscv-card/blob/master/riscv-card.pdf */

{ 0,	REG,		0,			"x0"	},
{ 0,	REG,		1,			"x1"	},
{ 0,	REG,		2,			"x2"	},
{ 0,	REG,		3,			"x3"	},
{ 0,	REG,		4,			"x4"	},
{ 0,	REG,		5,			"x5"	},
{ 0,	REG,		6,			"x6"	},
{ 0,	REG,		8,			"x7"	},
{ 0,	REG,		8,			"x8"	},
{ 0,	REG,		9,			"x9"	},
{ 0,	REG,		10,			"x10"	},
{ 0,	REG,		11,			"x11"	},
{ 0,	REG,		12,			"x12"	},
{ 0,	REG,		13,			"x13"	},
{ 0,	REG,		14,			"x14"	},
{ 0,	REG,		15,			"x15"	},
{ 0,	REG,		16,			"x16"	},
{ 0,	REG,		17,			"x17"	},
{ 0,	REG,		18,			"x18"	},
{ 0,	REG,		19,			"x19"	},
{ 0,	REG,		20,			"x20"	},
{ 0,	REG,		21,			"x21"	},
{ 0,	REG,		22,			"x22"	},
{ 0,	REG,		23,			"x23"	},
{ 0,	REG,		24,			"x24"	},
{ 0,	REG,		25,			"x25"	},
{ 0,	REG,		26,			"x26"	},
{ 0,	REG,		27,			"x27"	},
{ 0,	REG,		28,			"x28"	},
{ 0,	REG,		29,			"x29"	},
{ 0,	REG,		30,			"x30"	},
{ 0,	REG,		31,			"x31"	},

{ 0,	REG,		0,			"zero"	},
{ 0,	REG,		1,			"ra"	},
{ 0,	REG,		2,			"sp"	},
{ 0,	REG,		3,			"gp"	},
{ 0,	REG,		4,			"tp"	},
{ 0,	REG,		5,			"t0"	},
{ 0,	REG,		6,			"t1"	},
{ 0,	REG,		7,			"t2"	},
{ 0,	REG,		8,			"s0"	},
{ 0,	REG,		8,			"fp"	},
{ 0,	REG,		9,			"s1"	},
{ 0,	REG,		10,			"a0"	},
{ 0,	REG,		11,			"a1"	},
{ 0,	REG,		12,			"a2"	},
{ 0,	REG,		13,			"a3"	},
{ 0,	REG,		14,			"a4"	},
{ 0,	REG,		15,			"a5"	},
{ 0,	REG,		16,			"a6"	},
{ 0,	REG,		17,			"a7"	},
{ 0,	REG,		18,			"s2"	},
{ 0,	REG,		19,			"s3"	},
{ 0,	REG,		20,			"s4"	},
{ 0,	REG,		21,			"s5"	},
{ 0,	REG,		22,			"s6"	},
{ 0,	REG,		23,			"s7"	},
{ 0,	REG,		24,			"s8"	},
{ 0,	REG,		25,			"s9"	},
{ 0,	REG,		26,			"s10"	},
{ 0,	REG,		27,			"s11"	},
{ 0,	REG,		28,			"t3"	},
{ 0,	REG,		29,			"t4"	},
{ 0,	REG,		30,			"t5"	},
{ 0,	REG,		31,			"t6"	},

{ 0,	SIZE,		1,			".b"	},
{ 0,	SIZE,		2,			".w"	},
{ 0,	SIZE,		4,			".d"	},


{ 0,	CSR,		0x001,			"fflags"	},
{ 0,	CSR,		0x002,			"frm"	},
{ 0,	CSR,		0x003,			"fcsr"	},

{ 0,	CSR,		0x300,			"mstatus"	},
{ 0,	CSR,		0x301,			"misa"	},
{ 0,	CSR,		0x304,			"mie"	},
{ 0,	CSR,		0x305,			"mtvec"	},
{ 0,	CSR,		0x320,			"mcountinhibit"	},
{ 0,	CSR,		0x320,			"mucounteren"	},	/* XXXGJM: v1.1 */
/* 0x323 - 0x33F mhpmevent */
{ 0,	CSR,		0xC00,			"cycle"	},
{ 0,	CSR,		0xC01,			"time"	},
{ 0,	CSR,		0xC02,			"instret"	},
/* 0xC03 - 0xC1F hpmcounter */
{ 0,	CSR,		0xC80,			"cycleh"	},
{ 0,	CSR,		0xC81,			"timeh"	},
{ 0,	CSR,		0xC82,			"instreth"	},
/* 0xC83 - 0xC9F hpmcounter */
{ 0,	CSR,		0xF11,			"mvendorid"	},
{ 0,	CSR,		0xF12,			"marchid"	},
{ 0,	CSR,		0xF13,			"mimpid"	},
{ 0,	CSR,		0xF14,			"mhartid"	},

/*
 * Base Integer Instructions
 */

/* op rd, rs1, rs2 */
{ 0,	RTYPE,		rtype(0x00,0,0,0,0,0x33),	"add"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x10,0,0,0,0,0x33),	"sub"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x00,0,0,1,0,0x33),	"sll"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x00,0,0,2,0,0x33),	"slt"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x00,0,0,3,0,0x33),	"sltu"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x00,0,0,4,0,0x33),	"xor"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x00,0,0,5,0,0x33),	"srl"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x10,0,0,5,0,0x33),	"sra"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x00,0,0,6,0,0x33),	"or"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x00,0,0,7,0,0x33),	"and"	},	/* DONE */

/* op rd, rs1, imm12 */
{ 0,	ITYPE,		itype(0x000,0,0,0,0x13),	"addi"	},	/* DONE */
{ 0,	ITYPE,		itype(0x000,0,7,0,0x13),	"andi"	},	/* DONE */
{ 0,	ITYPE,		itype(0x000,0,6,0,0x13),	"ori"	},	/* DONE */
{ 0,	ITYPE,		itype(0x000,0,4,0,0x13),	"xori"	},	/* DONE */

/* op rd, rs1, imm5 */
{ 0,	ITYPE,		itype(0x000,0,1,0,0x13),	"slli"	},	/* DONE */
{ 0,	ITYPE,		itype(0x000,0,2,0,0x13),	"slti"	},	/* DONE */
{ 0,	ITYPE,		itype(0x000,0,3,0,0x13),	"sltiu"	},	/* DONE */
{ 0,	ITYPE,		itype(0x000,0,5,0,0x13),	"srli"	},	/* DONE */
{ 0,	ITYPE,		itype(0x400,0,5,0,0x13),	"srai"	},	/* DONE */

/* jalr rd, imm12(rs1) */
/* jalr imm12(rs1) - psuedo op */
/* jalr rs1 - psuedo op */
{ 0,	JALR,		itype(0x000,0,0,0,0x6E),	"jalr"	},	/* DONE */

/* op rs1 - pseudo op */
/* op imm12(rs1) - pseudo op */
{ 0,	JR,		itype(0x000,0,0,0,0x6E),	"jr"	},	/* DONE */

/* op rd, imm20 */
/* op imm20 - pseudo op */
{ 0,	JAL,		jtype(0x00000,0,0x6F),		"jal"	},	/* DONE */

/* op imm20 - pseudo op */
{ 0,	JUMP,		jtype(0x00000,0,0x6F),		"j"	},	/* DONE */

/* op */
{ 0,	IMPLICIT,	itype(0x000,0,0,0,0x73),	"ecall"	},	/* DONE */
{ 0,	IMPLICIT,	itype(0x001,0,0,0,0x73),	"ebreak"	},	/* DONE */

/* op rd, csr, rs1 */
{ 0,	ITYPE,		itype(0x000,0,1,0,0x73),	"csrrw"	},
{ 0,	ITYPE,		itype(0x000,0,2,0,0x73),	"csrrs"	},
{ 0,	ITYPE,		itype(0x000,0,3,0,0x73),	"csrrc"	},
{ 0,	ITYPE,		itype(0x000,0,5,0,0x73),	"csrrwi"	},
{ 0,	ITYPE,		itype(0x000,0,6,0,0x73),	"csrcsi"	},
{ 0,	ITYPE,		itype(0x000,0,7,0,0x73),	"csrcci"	},

/* op rd, imm12(rs1) */
/* op rd, symbol - pseudo op */
{ 0,	ITYPE,		itype(0x000,0,0,0,0x03),	"lb"	},	/* DONE */
{ 0,	ITYPE,		itype(0x000,0,1,0,0x03),	"lh"	},	/* DONE */
{ 0,	ITYPE,		itype(0x000,0,2,0,0x03),	"lw"	},	/* DONE */

/* op rd, imm12(rs1) */
{ 0,	ITYPE,		itype(0x000,0,4,0,0x03),	"lbu"	},	/* DONE */
{ 0,	ITYPE,		itype(0x000,0,5,0,0x03),	"lhu"	},	/* DONE */

/* op rs1, imm12(rs2) */
/* op rd, symbol, rt - pseudo op */
{ 0,	STYPE,		stype(0x000,0,0,0,0x23),	"sb"	},	/* DONE */
{ 0,	STYPE,		stype(0x000,0,0,1,0x23),	"sh"	},	/* DONE */
{ 0,	STYPE,		stype(0x000,0,0,2,0x23),	"sw"	},	/* DONE */

/* op rs1, rs2, imm13 */
{ 0,	BRANCH,		btype(0,0,0,0,0x63),		"beq"	},	/* DONE */
{ 0,	BRANCH,		btype(0,0,0,1,0x63),		"bne"	},	/* DONE */
{ 0,	BRANCH,		btype(0,0,0,4,0x63),		"blt"	},	/* DONE */
{ 0,	BRANCH,		btype(0,0,0,5,0x63),		"bge"	},	/* DONE */
{ 0,	BRANCH,		btype(0,0,0,6,0x63),		"bltu"	},	/* DONE */
{ 0,	BRANCH,		btype(0,0,0,7,0x63),		"bgeu"	},	/* DONE */

/* op rs2, rs1, imm13 - pseudo op */
{ 0,	BRANCHSW,		btype(0,0,0,4,0x63),	"bgt"	},	/* DONE */
{ 0,	BRANCHSW,		btype(0,0,0,5,0x63),	"ble"	},	/* DONE */
{ 0,	BRANCHSW,		btype(0,0,0,6,0x63),	"bgtu"	},	/* DONE */
{ 0,	BRANCHSW,		btype(0,0,0,7,0x63),	"bleu"	},	/* DONE */

/* op rs1, imm13 - pseudo ops */
{ 0,	BRANCHZ,		btype(0,0,0,0,0x63),		"beqz"	},	/* DONE */
{ 0,	BRANCHZ,		btype(0,0,0,1,0x63),		"bnez"	},	/* DONE */
{ 0,	BRANCHZ,		btype(0,0,0,4,0x63),		"bltz"	},	/* DONE */
{ 0,	BRANCHZ,		btype(0,0,0,5,0x63),		"bgez"	},	/* DONE */

/* op rs2, imm13 - pseudo ops */
{ 0,	BRANCHZSW,		btype(0,0,0,4,0x63),		"bgtz"	},	/* DONE */
{ 0,	BRANCHZSW,		btype(0,0,0,5,0x63),		"blez"	},	/* DONE */

/* op rd, imm20 - upper 20 bits */
{ 0,	UTYPE,		utype(0x00000,0,0x37),		"lui"	},	/* DONE */
{ 0,	UTYPE,		utype(0x00000,0,0x17),		"auipc"	},	/* DONE */

/* op rd, imm20 - lower 20 bits */
{ 0,	JTYPE,		jtype(0x00000,0,0x6F),		"jal"	},	/* DONE */


/*
 * Multiply Instructions
 */

/* op rd, rs1, rs2 */
{ 0,	RTYPE,		rtype(0x01,0,0,0,0,0x33),	"mul"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x01,0,0,1,0,0x33),	"mulh"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x01,0,0,2,0,0x33),	"mulsu"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x01,0,0,3,0,0x33),	"mulu"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x01,0,0,4,0,0x33),	"div"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x01,0,0,5,0,0x33),	"divu"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x01,0,0,6,0,0x33),	"rem"	},	/* DONE */
{ 0,	RTYPE,		rtype(0x01,0,0,7,0,0x33),	"remu"	},	/* DONE */

/*
 * Atomic Instructions
 */

/* op rd, rs1 */
{ 0,	RTYPE,		rtype((0x02<<2)|3,0,0,2,0,0x2F),	"lr"	},	/* DONE */

/* op rd, rs1, rs2 */
{ 0,	RTYPE,		rtype((0x03<<2)|3,0,0,2,0,0x2F),	"sr"	},	/* DONE */
{ 0,	RTYPE,		rtype((0x01<<2)|3,0,0,2,0,0x2F),	"amoswap"	},	/* DONE */
{ 0,	RTYPE,		rtype((0x00<<2)|3,0,0,2,0,0x2F),	"amoadd"	},	/* DONE */
{ 0,	RTYPE,		rtype((0x0C<<2)|3,0,0,2,0,0x2F),	"amoand"	},	/* DONE */
{ 0,	RTYPE,		rtype((0x0A<<2)|3,0,0,2,0,0x2F),	"amoor"	},	/* DONE */
{ 0,	RTYPE,		rtype((0x04<<2)|3,0,0,2,0,0x2F),	"amoxor"	},	/* DONE */
{ 0,	RTYPE,		rtype((0x10<<2)|3,0,0,2,0,0x2F),	"amomin"	},	/* DONE */
{ 0,	RTYPE,		rtype((0x14<<2)|3,0,0,2,0,0x2F),	"amomax"	},	/* DONE */

/*
 * pseudo instructions
 */

{ 0,	IMPLICIT,	itype(0x000,0,0,0,0x13),	"nop"	},	/* DONE */
{ 0,	IMPLICIT,	itype(0x000,1,0,0,0x6E),	"ret"	},	/* DONE */


/* op csr, imm12 */
{ 0,	CSRWI,		itype(0x000,0,5,0,0x73),	"csrwi"	},	/* DONE */
{ 0,	CSRWI,		itype(0x000,0,6,0,0x73),	"csrsi"	},	/* DONE */
{ 0,	CSRWI,		itype(0x000,0,7,0,0x73),	"csrci"	},	/* DONE */

/* op rd, csr */
{ 0,	CSRR,		itype(0x000,0,2,0,0x73),	"csrr"	},	/* DONE */

/* op csr, rs */
{ 0,	CSRW,		itype(0x000,0,1,0,0x73),	"csrw"	},	/* DONE */
{ 0,	CSRW,		itype(0x000,0,2,0,0x73),	"csrs"	},	/* DONE */
{ 0,	CSRW,		itype(0x000,0,3,0,0x73),	"csrc"	},	/* DONE */

/* op imm32 */
{ 0,	LI,		0x00000000,			"li"	},

/* op rd, rs */
{ 0,	LOGICOP,	itype(0x000,0,0,0,0x13),	"mv"	},	/* DONE */
{ 0,	LOGICOP,	itype(0xFFF,0,4,0,0x13),	"not"	},	/* DONE */
{ 0,	NEG,		rtype(0x10,0,0,0,0,0x33),	"neg"	},	/* DONE */
