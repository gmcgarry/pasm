#define RS1(x)		((x) << 14)
#define RS2(x)		((x) << 19)
#define RD(x)		((x) << 6)
#define FUNC3(x)	((x) << 11)
#define FUNC7(x)	((x) << 24)

#define IMM12I(x)	((x) << 19)
#define IMM12S(x)	((((x) & 0xfe0) << 19) | (((x) & 0x1f) << 6))
#define IMM13B(x)	((((x) & 0x1000) << 19) | (((x) & 0x3e0) << 19) | (((x) & 0x1e) << 6) | (((x) & 0x800) >> 4))
#define IMM20U(x)	((x) << 11)
#define IMM20J(x)	((((x) & 0x100000) << 7) | (((x) & 0x3fe) << 20) | (((x) & 0x800) << 8) | ((x) & 0xff000))


/* func7 rs2 rs1 func3 rd opcode */
/* 77777772222211111333dddddooooooo */
#define rtype(func7, rs2, rs1, func3, rd, opcode) \
	FUNC7(func7) | RS2(rs2) | RS1(rs1) | FUNC3(func3) | RD(rd) | opcode

/* imm[11:0] rs1 func3 rd opcode */
/* iiiiiiiiiiii11111333dddddooooooo */
#define itype(imm12, rs1, func3, rd, opcode) \
	IMM12I(imm12) | RS1(rs1) | FUNC3(func3) | RD(rd) | opcode

/* imm[11:5] rs2 rs1 func3 imm[4:0] opcode */
/* iiiiiii2222211111333iiiiiooooooo */
#define stype(imm12, rs2, rs1, func3, opcode) \
	IMM12S(imm12) | RS2(rs2) | RS1(rs1) | FUNC3(func3) | opcode

/* imm[12] imm[10:5] rs2 rs1 func3 imm[4:1] imm[11] opcode */
/* iiiiiii2222211111333iiiiiooooooo */
#define btype(imm13, rs2, rs1, func3, opcode) \
	IMM13B(imm13) | RS2(rs2) | RS1(rs1) | FUNC3(func3) | opcode

/* imm[31:12] rd opcode */
/* iiiiiiiiiiiiiiiiiiiidddddooooooo */
#define utype(imm20, rd, opcode) \
	IMM20U(imm20) | RD(rd) | opcode

/* imm[20] imm[10:1] imm[11] imm[19:12] rd opcode */
/* iiiiiiiiiiiiiiiiiiiidddddooooooo */
#define jtype(imm20, rd, opcode) \
		IMM20J(imm20) | RD(rd) | opcode
