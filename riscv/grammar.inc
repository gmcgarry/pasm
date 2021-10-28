operation
	: RTYPE optsz REG ',' REG ',' REG	{ emit4($1); }

	| ITYPE optsz REG ',' imm12 '(' REG ')'	{ emit4($1); }
	| ITYPE optsz REG ',' REG ',' imm12	{ emit4($1); }

	| STYPE optsz REG ',' imm12 '(' REG ')'	{ emit4($1); }
	| UTYPE optsz REG ',' imm20		{ emit4($1); }
	| JTYPE optsz REG ',' imm20		{ emit4($1); }

	| ITYPE_NODST REG ',' imm12		{ emit4($1); }
	| LI REG ',' expr			{ emit4($1); }
	| LA REG ',' expr			{ emit4(0x27|RD($2)|($4.val&0xFFFFF000)); emit4(0x13|RD($2)|RS1($2)|IMM12I($4.val&0xFFF)); }
	| CSR REG				{ /* csrrs($2, $2, x0) */ }

	| IMPLICIT				{ emit4($1); }
	| CSRW CSR ',' imm5			{ emit4($1|FUNC3(4)|RS1($4.val)|IMM12I($2)); }
	| CSRW CSR ',' REG			{ emit4($1|RS1($4)|IMM12I($2)); }
	| CSRR REG ',' CSR			{ emit4($1|RD($2)|IMM12I($4)); }
	| JALR REG ',' imm12 '(' REG ')'	{ emit4($1|RD($2)|RS1($6)|IMM12I($4.val)); }
	| JALR imm12 '(' REG ')'		{ emit4($1|RD(1)|RS1($4)|IMM12I($2.val)); }
	| JALR REG				{ emit4($1|RD(1)|RS1($1)|IMM12I(0)); }
	| JR imm12 '(' REG ')'			{ emit4($1|RD(0)|RS1($4)|IMM12I($2.val)); }
	| JR REG				{ emit4($1|RD(0)|RS1($1)|IMM12I(0)); }
	| JAL REG ',' imm21			{ emit4($1|RD($1)|IMM20J($4.val>>1)); }
	| JAL imm21				{ emit4($1|RD(1)|IMM20J($2.val>>1)); }
	| JUMP imm21				{ emit4($1|RD(0)|IMM20J($2.val>>1)); }
	| BRANCH REG ',' REG ',' imm13		{ emit4($1|RS1($2)|RS2($4)|IMM13B($6.val)); }
	| BRANCHSW REG ',' REG ',' imm13	{ emit4($1|RS1($4)|RS2($2)|IMM13B($6.val)); }
	| BRANCHZ REG ',' imm13			{ emit4($1|RS1($2)|RS2(0)|IMM13B($4.val)); }
	| BRANCHZSW REG ',' imm13		{ emit4($1|RS1(0)|RS2($2)|IMM13B($4.val)); }

	| LOGICOP REG ',' REG			{ emit4($1|RD($2)|RS1($4)); }
	| NEG REG ',' REG			{ emit4($1|RD($2)|RS2($4)); }
	;

optsz	: /* empty */	{ $$ = 0; }
	| SIZE		{ $$ = $1; }
	;

imm5	: expr		{ $$ = $1; }
	;

imm12	: expr		{ $$ = $1; }
	;

imm13	: expr		{ $$ = $1; }
	;

imm20	: expr		{ $$ = $1; }
	;

imm21	: expr		{ $$ = $1; /* LSB must be 0 */}
	;
