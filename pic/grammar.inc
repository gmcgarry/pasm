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
	| PSEUDOOP_DEVICE IDENT			{ setdevice($2->i_name); }
	| PSEUDOOP_CONFIG cfglist
	| PSEUDOOP_MAXRAM NUMBER8
	| PSEUDOOP_BADRAM NUMBER8
	| PSEUDOOP_BADRAM NUMBER8 '-' NUMBER8
	| PSEUDOOP_BANKSEL expr			{ banksel($2.val); }
	| PSEUDOOP_PAGESEL expr			{ }
	| PSEUDOOP_PSECT IDENT optflags		{ newsect($2, 0, NULL); }
	| PSEUDOOP_END IDENT			{ }
	;

cfglist: cfglist ',' cfg
	| cfg
	;

cfg	: IDENT '=' IDENT			{ setconfig($1->i_name, $3->i_name); }
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

optdir	: /* empty  */				{ $$ = 0x80; }
	| ',' d					{ $$ = $2; }
	;

d	: expr					{ $$ = $1.val ? 0x80 : 0; }
	| D					{ $$ = $1; }
	;

b	: expr					{ $$ = ($1.val & 0x07) << 7; }
	;

f	: expr							{ $$ = $1.val; }
	| PSEUDOOP_BANKMASK '(' expr ')'			{ $$ = $3.val&0x7f; }
	;

k8	: expr					{ $$ = $1.val & 0xff; }
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
