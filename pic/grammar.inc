operation
	: label
	| label instr
	| instr
	;

label	: IDENT			{ newident($1, DOTSCT); newlabel($1); }
	;

instr	: NOOP			{ emit2($1); }
	| BYTEOP f ',' D	{ emit2($1 | $4 | $2); }
	| ONEOP f 		{ emit2($1 | $2); }
	| BITOP f ',' b		{ emit2($1 | $4 | $2); }
	| LITOP k8		{ emit2($1 | $2); }
	| JMPOP k11		{ emit2($1 | $2); }
	;

b	: expr			{ $$ = ($1.val & 0x07) << 7; }
	;

f	: expr			{ $$ = $1.val & 0x7f; }
	;

k8	: expr			{ $$ = $1.val & 0xff; }
	;

k11	: expr 			{ $$ = ($1.val >> 1) & 0x7ff; }
	;

expr	: '$' absexp		{ $$.typ = S_ABS; $$.val = $2; }
	;
