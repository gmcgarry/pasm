#define  fitx(v,n)	(((v) & ~((1<<(n))-1)) == 0)

operation
	: OP_MOV gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21)); }
	| OP_ADD gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_ADDI gpr ',' gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 21) | (($6 & 0xffff) << 0)); }
	| OP_ADDIU gpr ',' gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 21) | (($6 & 0xffff) << 0)); }
	| OP_ADDU gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_AND gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_ANDI gpr ',' gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 21) | (($6 & 0xffff) << 0)); }
	| OP_B offset16					{ emit4($1 | (($2 & 0xffff) << 0)); }
	| OP_BAL offset16					{ emit4($1 | (($2 & 0xffff) << 0)); }
	| OP_BEQ gpr ',' gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16) | (($6 & 0xffff) << 0)); }
	| OP_BEQL gpr ',' gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16) | (($6 & 0xffff) << 0)); }
	| OP_BGEZ gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_BGEZAL gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_BGEZALL gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_BGEZL gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_BGTZ gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_BGTZL gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_BLEZ gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_BLEZL gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_BLTZ gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_BLTZAL gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_BLTZALL gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_BLTZL gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_BNE gpr ',' gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16) | (($6 & 0xffff) << 0)); }
	| OP_BNEL gpr ',' gpr ',' offset16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16) | (($6 & 0xffff) << 0)); }
	| OP_CACHE u5 ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_CACHEE u5 ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_CLO gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 21)); }
	| OP_CLZ gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 21)); }
	| OP_DERET					{ emit4($1); }
	| OP_DI gpr					{ emit4($1 | (($2 & 0x1f) << 16)); }
	| OP_DI					{ emit4($1); }
	| OP_DIV gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_DIVU gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_EHB					{ emit4($1); }
	| OP_EI gpr					{ emit4($1 | (($2 & 0x1f) << 16)); }
	| OP_EI					{ emit4($1); }
	| OP_EXT gpr ',' gpr ',' extmsblsb					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 21)); }
	| OP_INS gpr ',' gpr ',' insmsblsb					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 21)); }
	| OP_J abs26					{ emit4($1 | (($2 & 0x3ffffff) << 0)); }
	| OP_JAL abs26					{ emit4($1 | (($2 & 0x3ffffff) << 0)); }
	| OP_JALR gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21)); }
	| OP_JALR gpr					{ emit4($1 | (($2 & 0x1f) << 21)); }
	| OP_JALR_DOT_HB gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21)); }
	| OP_JALR_DOT_HB gpr					{ emit4($1 | (($2 & 0x1f) << 21)); }
	| OP_JALX abs26					{ emit4($1 | (($2 & 0x3ffffff) << 0)); }
	| OP_JR gpr					{ emit4($1 | (($2 & 0x1f) << 21)); }
	| OP_JR_DOT_HB gpr					{ emit4($1 | (($2 & 0x1f) << 21)); }
	| OP_LB gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_LBE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_LBU gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_LBUE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_LH gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_LHE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_LHU gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_LHUE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_LL gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_LLE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_LUI gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0)); }
	| OP_LW gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_LWE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_LWL gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_LWLE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_LWR gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_LWRE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_MADD gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_MADDU gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_MFHI gpr					{ emit4($1 | (($2 & 0x1f) << 11)); }
	| OP_MFLO gpr					{ emit4($1 | (($2 & 0x1f) << 11)); }
	| OP_MOVN gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_MOVZ gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_MSUB gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_MSUBU gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_MTHI gpr					{ emit4($1 | (($2 & 0x1f) << 21)); }
	| OP_MTLO gpr					{ emit4($1 | (($2 & 0x1f) << 21)); }
	| OP_MUL gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_MULT gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_MULTU gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_NOP					{ emit4($1); }
	| OP_NOR gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_OR gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_ORI gpr ',' gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 21) | (($6 & 0xffff) << 0)); }
	| OP_PAUSE					{ emit4($1); }
	| OP_PREF u5 ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_PREFE u5 ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_PREFX u5 ',' gpr '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 21)); }
	| OP_RDHWR gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 11)); }
	| OP_RDPGPR gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16)); }
	| OP_ROTR gpr ',' gpr ',' u5					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 6)); }
	| OP_ROTRV gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 21)); }
	| OP_SB gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_SBE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_SC gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_SCE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_SDBBP u20					{ emit4($1 | (($2 & 0xfffff) << 6)); }
	| OP_SEB gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16)); }
	| OP_SEH gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16)); }
	| OP_SH gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_SHE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_SLL gpr ',' gpr ',' u5					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 6)); }
	| OP_SLLV gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 21)); }
	| OP_SLT gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_SLTI gpr ',' gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 21) | (($6 & 0xffff) << 0)); }
	| OP_SLTIU gpr ',' gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 21) | (($6 & 0xffff) << 0)); }
	| OP_SLTU gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_SRA gpr ',' gpr ',' u5					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 6)); }
	| OP_SRAV gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 21)); }
	| OP_SRL gpr ',' gpr ',' u5					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 6)); }
	| OP_SRLV gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 21)); }
	| OP_SSNOP					{ emit4($1); }
	| OP_SUB gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_SUBU gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_SW gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_SWE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_SWL gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_SWLE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_SWR gpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_SWRE gpr ',' e9 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1ff) << 7) | (($6 & 0x1f) << 21)); }
	| OP_SYNCI e16 '(' gpr ')'					{ emit4($1 | (($2 & 0xffff) << 0) | (($4 & 0x1f) << 21)); }
	| OP_SYSCALL u20					{ emit4($1 | (($2 & 0xfffff) << 6)); }
	| OP_TEQ gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_TEQI gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_TGE gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_TGEI gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_TGEIU gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_TGEU gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_TLBINV					{ emit4($1); }
	| OP_TLBINVF					{ emit4($1); }
	| OP_TLBP					{ emit4($1); }
	| OP_TLBR					{ emit4($1); }
	| OP_TLBWI					{ emit4($1); }
	| OP_TLBWR					{ emit4($1); }
	| OP_TLT gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_TLTI gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_TLTIU gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_TLTU gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_TNE gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0x1f) << 16)); }
	| OP_TNEI gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 21) | (($4 & 0xffff) << 0)); }
	| OP_WAIT					{ emit4($1); }
	| OP_WRPGPR gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16)); }
	| OP_WSBH gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 16)); }
	| OP_XOR gpr ',' gpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x1f) << 16)); }
	| OP_XORI gpr ',' gpr ',' e16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 21) | (($6 & 0xffff) << 0)); }
	| OP_ABS fmt fpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11)); }
	| OP_ADD fmt fpr ',' fpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x1f) << 16)); }
	| OP_ALNV OP__DOT_PS fpr ',' fpr ',' fpr ',' gpr					{ emit4($1 | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x1f) << 16) | (($9 & 0x1f) << 21)); }
	| OP_C fcond fmt u3 ',' fpr ',' fpr					{ emit4($1 | (($2 & 0xf) << 0) | (($3 & 0x1f) << 21) | (($4 & 0x7) << 8) | (($6 & 0x1f) << 11) | (($8 & 0x1f) << 16)); }
	| OP_CEIL OP__DOT_L fmt fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 21) | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11)); }
	| OP_CEIL OP__DOT_W fmt fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 21) | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11)); }
	| OP_CFC1 gpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 11)); }
	| OP_CTC1 gpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 11)); }
	| OP_CVT OP__DOT_D fmt fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 21) | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11)); }
	| OP_CVT OP__DOT_L fmt fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 21) | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11)); }
	| OP_CVT OP__DOT_PS OP__DOT_S fpr ',' fpr ',' fpr					{ emit4($1 | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11) | (($8 & 0x1f) << 16)); }
	| OP_CVT OP__DOT_S fmt fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 21) | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11)); }
	| OP_CVT OP__DOT_S OP__DOT_PL fpr ',' fpr					{ emit4($1 | (($4 & 0x1f) << 11) | (($6 & 0x1f) << 6)); }
	| OP_CVT OP__DOT_S OP__DOT_PU fpr ',' fpr					{ emit4($1 | (($4 & 0x1f) << 11) | (($6 & 0x1f) << 6)); }
	| OP_CVT OP__DOT_W fmt fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 21) | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11)); }
	| OP_DIV fmt fpr ',' fpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x1f) << 16)); }
	| OP_FLOOR OP__DOT_L fmt fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 21) | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11)); }
	| OP_FLOOR OP__DOT_W fmt fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 21) | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11)); }
	| OP_LDC1 fpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_LDXC1 fpr ',' gpr '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 6) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 21)); }
	| OP_LUXC1 fpr ',' gpr '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 6) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 21)); }
	| OP_LWC1 fpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_LWXC1 fpr ',' gpr '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 6) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 21)); }
	| OP_MADD fmt3 fpr ',' fpr ',' fpr ',' fpr					{ emit4($1 | (($2 & 0x7) << 0) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 21) | (($7 & 0x1f) << 11) | (($9 & 0x1f) << 16)); }
	| OP_MFC1 gpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 11)); }
	| OP_MFHC1 gpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 11)); }
	| OP_MOV fmt fpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11)); }
	| OP_MOVF gpr ',' gpr ',' u3					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x7) << 18)); }
	| OP_MOVF fmt fpr ',' fpr ',' u3					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x7) << 18)); }
	| OP_MOVN fmt fpr ',' fpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x1f) << 16)); }
	| OP_MOVT gpr ',' gpr ',' u3					{ emit4($1 | (($2 & 0x1f) << 11) | (($4 & 0x1f) << 21) | (($6 & 0x7) << 18)); }
	| OP_MOVT fmt fpr ',' fpr ',' u3					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x7) << 18)); }
	| OP_MOVZ fmt fpr ',' fpr ',' gpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x1f) << 16)); }
	| OP_MSUB fmt3 fpr ',' fpr ',' fpr ',' fpr					{ emit4($1 | (($2 & 0x7) << 0) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 21) | (($7 & 0x1f) << 11) | (($9 & 0x1f) << 16)); }
	| OP_MTC1 gpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 11)); }
	| OP_MTHC1 gpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 11)); }
	| OP_MUL fmt fpr ',' fpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x1f) << 16)); }
	| OP_NEG fmt fpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11)); }
	| OP_NMADD fmt3 fpr ',' fpr ',' fpr ',' fpr					{ emit4($1 | (($2 & 0x7) << 0) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 21) | (($7 & 0x1f) << 11) | (($9 & 0x1f) << 16)); }
	| OP_NMSUB fmt3 fpr ',' fpr ',' fpr ',' fpr					{ emit4($1 | (($2 & 0x7) << 0) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 21) | (($7 & 0x1f) << 11) | (($9 & 0x1f) << 16)); }
	| OP_PLL OP__DOT_PS fpr ',' fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x1f) << 16)); }
	| OP_PLU OP__DOT_PS fpr ',' fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x1f) << 16)); }
	| OP_PUL OP__DOT_PS fpr ',' fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x1f) << 16)); }
	| OP_PUU OP__DOT_PS fpr ',' fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x1f) << 16)); }
	| OP_RECIP_DOT_ fmt fpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11)); }
	| OP_ROUND OP__DOT_L fmt fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 21) | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11)); }
	| OP_ROUND OP__DOT_W fmt fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 21) | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11)); }
	| OP_RSQRT fmt fpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11)); }
	| OP_SDC1 fpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_SDXC1 fpr ',' gpr '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 6) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 21)); }
	| OP_SQRT fmt fpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11)); }
	| OP_SUB fmt fpr ',' fpr ',' fpr					{ emit4($1 | (($2 & 0x1f) << 21) | (($3 & 0x1f) << 6) | (($5 & 0x1f) << 11) | (($7 & 0x1f) << 16)); }
	| OP_SUXC1 fpr ',' gpr '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 6) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 21)); }
	| OP_SWC1 fpr ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_SWXC1 fpr ',' gpr '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 6) | (($4 & 0x1f) << 16) | (($6 & 0x1f) << 21)); }
	| OP_TRUNC OP__DOT_L fmt fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 21) | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11)); }
	| OP_TRUNC OP__DOT_W fmt fpr ',' fpr					{ emit4($1 | (($3 & 0x1f) << 21) | (($4 & 0x1f) << 6) | (($6 & 0x1f) << 11)); }
	| OP_BC1F u3 ',' offset16					{ emit4($1 | (($2 & 0x7) << 18) | (($4 & 0xffff) << 0)); }
	| OP_BC1F offset16					{ emit4($1 | (($2 & 0xffff) << 0)); }
	| OP_BC1FL u3 ',' offset16					{ emit4($1 | (($2 & 0x7) << 18) | (($4 & 0xffff) << 0)); }
	| OP_BC1FL offset16					{ emit4($1 | (($2 & 0xffff) << 0)); }
	| OP_BC1T u3 ',' offset16					{ emit4($1 | (($2 & 0x7) << 18) | (($4 & 0xffff) << 0)); }
	| OP_BC1T offset16					{ emit4($1 | (($2 & 0xffff) << 0)); }
	| OP_BC1TL u3 ',' offset16					{ emit4($1 | (($2 & 0x7) << 18) | (($4 & 0xffff) << 0)); }
	| OP_BC1TL offset16					{ emit4($1 | (($2 & 0xffff) << 0)); }
	| OP_BC2F u3 ',' offset16					{ emit4($1 | (($2 & 0x7) << 18) | (($4 & 0xffff) << 0)); }
	| OP_BC2F offset16					{ emit4($1 | (($2 & 0xffff) << 0)); }
	| OP_BC2FL u3 ',' offset16					{ emit4($1 | (($2 & 0x7) << 18) | (($4 & 0xffff) << 0)); }
	| OP_BC2FL offset16					{ emit4($1 | (($2 & 0xffff) << 0)); }
	| OP_BC2T u3 ',' offset16					{ emit4($1 | (($2 & 0x7) << 18) | (($4 & 0xffff) << 0)); }
	| OP_BC2T offset16					{ emit4($1 | (($2 & 0xffff) << 0)); }
	| OP_BC2TL u3 ',' offset16					{ emit4($1 | (($2 & 0x7) << 18) | (($4 & 0xffff) << 0)); }
	| OP_BC2TL offset16					{ emit4($1 | (($2 & 0xffff) << 0)); }
	| OP_CFC2 gpr ',' u16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0)); }
	| OP_CTC2 gpr ',' u16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0)); }
	| OP_COP2 u25					{ emit4($1 | (($2 & 0x1ffffff) << 0)); }
	| OP_LDC2 u5 ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_LWC2 u5 ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_MFC0 gpr ',' u5 ',' u3					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 11) | (($6 & 0x7) << 0)); }
	| OP_MFC2 gpr ',' u16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0)); }
	| OP_MFHC0 gpr ',' u5 ',' u3					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 11) | (($6 & 0x7) << 0)); }
	| OP_MFHC2 gpr ',' u16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0)); }
	| OP_MTC0 gpr ',' u5 ',' u3					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 11) | (($6 & 0x7) << 0)); }
	| OP_MTC2 gpr ',' u16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0)); }
	| OP_MTHC0 gpr ',' u5 ',' u3					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0x1f) << 11) | (($6 & 0x7) << 0)); }
	| OP_MTHC2 gpr ',' u16					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0)); }
	| OP_SDC2 u5 ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_SWC2 u5 ',' e16 '(' gpr ')'					{ emit4($1 | (($2 & 0x1f) << 16) | (($4 & 0xffff) << 0) | (($6 & 0x1f) << 21)); }
	| OP_LI GPR ',' extabsexp
	{
		word_t reg = $2;
		uint32_t val = $4;

		if (((int32_t)val >= -0x8000) && ((int32_t)val <= 0x7fff))
			emit4(0x24000000 | (reg<<16) | (val & 0xffff)); 
		else if (val <= 0xffff)
			emit4(0x34000000 | (reg<<16) | val); 
		else
		{
			emit4(0x3c000000 | (reg<<16) | (val>>16)); 
			emit4(0x34000000 | (reg<<16) | (reg<<21) | (val & 0xffff)); 
		}
	}

extabsexp
	: absexp
	| LO16 '(' expr ')'
	{
		newrelo($3.typ, RELO2 | FIXUPFLAGS);
		$$ = $3.val;
	}
	| HI16 '(' expr ')'
	{
		newrelo($3.typ, RELO2HI | FIXUPFLAGS);
		if ($3.val & 0xffff0000)
			fatal("relocation offset in hi16[] too big");
		$$ = $3.val;
	}
	| HA16 '(' expr ')'
	{
		newrelo($3.typ, RELO2HISAD | FIXUPFLAGS);
		if ($3.val & 0xffff0000)
			fatal("relocation offset in ha16[] too big");
		$$ = $3.val;
	}
	;

gpr: GPR
fpr: FPR

fmt3
	: OP__DOT_S  { $$ = 0; }
	| OP__DOT_D  { $$ = 1; }
	| OP__DOT_W  { $$ = 4; }
	| OP__DOT_L  { $$ = 5; }
	| OP__DOT_PS { $$ = 6; }
	;

fmt
	: fmt3       { $$ = $1 + 16; }
    ;

fcond
	: OP__DOT_F    { $$ = 0; }
	| OP__DOT_UN   { $$ = 1; }
	| OP__DOT_EQ   { $$ = 2; }
	| OP__DOT_UEQ  { $$ = 3; }
	| OP__DOT_OLT  { $$ = 4; }
	| OP__DOT_ULT  { $$ = 5; }
	| OP__DOT_OLE  { $$ = 6; }
	| OP__DOT_ULE  { $$ = 7; }
	| OP__DOT_SF   { $$ = 8; }
	| OP__DOT_NGLE { $$ = 9; }
	| OP__DOT_SEQ  { $$ = 10; }
	| OP__DOT_NGL  { $$ = 11; }
	| OP__DOT_LT   { $$ = 12; }
	| OP__DOT_NGE  { $$ = 13; }
	| OP__DOT_LE   { $$ = 14; }
	| OP__DOT_NGT  { $$ = 15; }
	;

e16
	: extabsexp
	{
		
		if (($1 < -0x8000) || ($1 > 0xffff))
			serror("16-bit signed value out of range");
		$$ = (uint16_t) $1;
	}
	;

e9
	: absexp
	{
		
		if (($1 < -0x100) || ($1 > 0x1ff))
			serror("9-bit signed value out of range");
		$$ = (uint16_t) $1;
	}
	;

u25
	: absexp
	{
		if (($1 < 0) || ($1 > 0x1ffffff))
			serror("25-bit unsigned value out of range");
		$$ = $1;
	}
	;

u20
	: absexp
	{
		if (($1 < 0) || ($1 > 0xfffff))
			serror("20-bit unsigned value out of range");
		$$ = $1;
	}
	;

u16
	: extabsexp
	{
		if (($1 < 0) || ($1 > 0xffff))
			serror("16-bit unsigned value out of range");
		$$ = $1;
	}
	;

u5
	: absexp
	{
		if (($1 < 0) || ($1 > 0x1f))
			serror("5-bit unsigned value out of range");
		$$ = $1;
	}
	;

u3
	: absexp
	{
		if (($1 < 0) || ($1 > 0x7))
			serror("3-bit unsigned value out of range");
		$$ = $1;
	}
	;

offset16
	: expr
	{
		int dist = $1.val - DOTVAL - 4;
		fit(fitx(dist, 18));

		if (dist & 0x3)
			serror("jump targets must be 4-aligned");

		newrelo($1.typ, RELOMIPS | RELPC | FIXUPFLAGS);
		$$ = (dist >> 2) & 0x0000ffff;
	}
	;

abs26
	: expr
	{
		int target = $1.val;
		fit(fitx(target, 28));

		if (target & 0x3)
			serror("jump targets must be 4-aligned");

		newrelo($1.typ, RELOMIPS | FIXUPFLAGS);
		$$ = (target >> 2) & 0x03ffffff;
	}
	;

extmsblsb
	: u5 ',' u5
	{
		int pos = $1;
		int size = $3;
		$$ = ((size-1) << 5) | pos;
	}
	;

insmsblsb
	: u5 ',' u5
	{
		int pos = $1;
		int size = $3;
		$$ = ((pos+size-1) << 5) | pos;
	}
	;
