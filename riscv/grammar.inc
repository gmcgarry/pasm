operation
	: RTYPE REG ',' REG ',' REG		{ emit4($2); }
	| ITYPE REG ',' imm12 '(' REG ')'	{ emit4($1); }
	| STYPE REG ',' REG ',' imm12		{ emit4($1); }
	| BTYPE REG ',' REG ',' imm13		{ emit4($1); }
	| UTYPE REG ',' imm20			{ emit4($1); }
	| JTYPE REG ',' imm20			{ emit4($1); }
	| IMPL					{ emit4($1); }
	;

imm12	: '#' expr		{ $$ = $2; }
	;

imm13	: '#' expr		{ $$ = $2; }
	;

imm20	: '#' expr		{ $$ = $2; }
	;
