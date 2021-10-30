operation
	: RTYPE REG ',' REG ',' REG		{ emit4($1|RD($2)|RS1($4)|RS2($6)); }
	| ITYPE REG ',' imm12 '(' REG ')'	{ emit4($1|RD($2)|RS1($6)|IMM12I($4.val)); }
	| ITYPE REG ',' '(' REG ')'		{ emit4($1|RD($2)|RS1($5)|IMM12I(0)); }
	| ITYPE REG ',' REG ',' imm12		{ emit4($1|RD($2)|RS1($4)|IMM12I($6.val)); }
	| STYPE REG ',' imm12 '(' REG ')'	{ emit4($1|RS1($6)|RS2($2)|IMM12S($4.val)); }
	| STYPE REG ',' '(' REG ')'		{ emit4($1|RS1($5)|RS2($2)|IMM12S(0)); }

	| UTYPE REG ',' imm21			{ emit4($1|RD($2)|IMM20U($4.val)); }

	| LI REG ',' expr			{ emit4(0x37|RD($2)|($4.val&0xFFFFF000)); emit4(0x13|RD($2)|RS1($2)|IMM12I($4.val&0xFFF)); }
	| LA REG ',' expr			{ emit4(0x17|RD($2)|($4.val&0xFFFFF000)); emit4(0x13|RD($2)|RS1($2)|IMM12I($4.val&0xFFF)); }
	| CSR REG				{ /* csrrs($2, $2, x0) */ }

	| IMPLICIT				{ emit4($1); }
	| CSRW CSR ',' imm5			{ emit4($1|FUNC3(4)|RS1($4.val)|IMM12I($2)); }
	| CSRW CSR ',' REG			{ emit4($1|RS1($4)|IMM12I($2)); }
	| CSRR REG ',' CSR			{ emit4($1|RD($2)|IMM12I($4)); }
	| JALR REG ',' imm12 '(' REG ')'	{ emit4($1|RD($2)|RS1($6)|IMM12I($4.val)); }
	| JALR imm12 '(' REG ')'		{ emit4($1|RD(1)|RS1($4)|IMM12I($2.val)); }
	| JALR REG				{ emit4($1|RD(1)|RS1($2)|IMM12I(0)); }
	| JR imm12 '(' REG ')'			{ emit4($1|RD(0)|RS1($4)|IMM12I($2.val)); }
	| JR REG				{ emit4($1|RD(0)|RS1($2)|IMM12I(0)); }
	| JAL REG ',' offset21			{ emit4($1|RD($2)|IMM20J($4.val)); }
	| JAL offset21				{ emit4($1|RD(1)|IMM20J($2.val)); }
	| JUMP offset21				{ emit4($1|RD(0)|IMM20J($2.val)); }
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

imm13	: expr		{ $$.typ = S_ABS; $$.val = ($1.val - DOTVAL); }
	;

imm20	: expr		{ $$ = $1; }
	;

imm21	: expr		{ $$ = $1; /* LSB must be 0 */}
	;

offset21
	: expr		{ $$.typ = S_ABS; $$.val = ($1.val - DOTVAL); }
	;
