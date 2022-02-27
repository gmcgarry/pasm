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

operation
	: label
	| label instr
	| instr
	| PSEUDOOP_DEVICE IDENT			{ setdevice($2->i_name); newident($2, S_ABS); }
	| PSEUDOOP_CONFIG cfglist
	| PSEUDOOP_MAXRAM NUMBER8
	| PSEUDOOP_BADRAM rglist
	| PSEUDOOP_BANKSEL expr			{ banksel($2.val); }
	| PSEUDOOP_PAGESEL expr			{ }
	| PSEUDOOP_DT dtlist
#ifdef COMPAT_PICAS
	| PSEUDOOP_PSECT IDENT optflags		{ newsect($2, 0, NULL); }
	| PSEUDOOP_END IDENT			{ }
#endif
	;

cfglist: cfglist ',' cfg
	| cfg
	| expr					{ setconfig_word($1.val); }
	;

cfg	: IDENT '=' IDENT			{ setconfig($1->i_name, $3->i_name); $1->i_type = $3->i_type = S_ABS; }
	;

rglist:	rglist ',' rg
	| rg
	;

rg	: NUMBER8 '-' NUMBER8
	| NUMBER8
	;

dtlist: expr					{ fit(fitx($1.val,8)); emit2(0x3400|$1.val); }
	| dtlist ',' expr			{ fit(fitx($3.val,8)); emit2(0x3400|$3.val); }
	| STRING				{ int i; for (i = 0; i < stringlen; i++) emit2(0x3400|stringbuf[i]); }
	| dtlist ',' STRING			{ int i; for (i = 0; i < stringlen; i++) emit1(0x3400|stringbuf[i]); }
	;

label	: IDENT					{ newident($1, DOTSCT); newlabel($1); }
	;

instr	: NOOP					{ emit2($1); }
	| BYTEOP f optdir			{ emit2($1 | $3 | $2); }
	| ONEOP f 				{ emit2($1 | $2); }
	| BITOP f ',' b				{ emit2($1 | $4 | $2); }
	| LITOP k8				{ emit2($1 | $2); }
	| JMPOP k11				{ emit2($1 | $2); }
	;

optdir	: /* empty  */				{ $$ = 0x80; if (pass == PASS_1) warning("using default destination of 1 (file)"); }
	| ',' d					{ $$ = $2; }
	;

d	: expr					{ $$ = $1.val ? 0x80 : 0; }
	| D					{ $$ = $1; }
	;

b	: expr					{ $$ = ($1.val & 0x07) << 7; }
	;

f	: expr					{ $$ = $1.val; }
	| PSEUDOOP_BANKMASK '(' expr ')'	{ $$ = $3.val&0x7f; }
	;

k8	: expr					{ int v = $1.val; if ($1.typ != S_ABS) v >>= 1; $$ = v; fit(fitx($$, 8)||fitx($$+128, 8)); }
        | SHIFTFUNC expr			{ int v = $2.val; if ($2.typ != S_ABS) v >>= 1; $$ = (v >> $1) & 0xff; fit(fitx($$, 8)||fitx($$+128, 8)); }
	;

k11	: expr 					{ $$ = ($1.typ & S_ABS ? $1.val : $1.val >> 1) & 0x7ff; }
	;

expr	: '$' absexp				{ $$.typ = S_ABS; $$.val = $2; }
	;

optflags: /* empty */				{ }
	| ',' flags				{ }
	;

flags	: flag optflags				{ }
	;

flag	: IDENT					{ $1->i_type = S_ABS; }
	| IDENT '=' expr			{ $1->i_type = S_ABS; $3.typ = S_ABS; }
	| PSEUDOOP_GLOBAL			{ }
	;
