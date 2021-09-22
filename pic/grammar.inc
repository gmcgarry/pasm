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
	| PSEUDOOP_CONFIG IDENT '=' IDENT	{ setconfig($2->i_name, $4->i_name); }
	| PSEUDOOP_MAXRAM NUMBER8
	| PSEUDOOP_BADRAM NUMBER8
	| PSEUDOOP_BADRAM NUMBER8 '-' NUMBER8
	| PSEUDOOP_BANKSEL expr		{ banksel($2.val); }
	;

label	: IDENT			{ newident($1, DOTSCT); newlabel($1); }
	;

instr	: NOOP			{ emit2($1); }
	| BYTEOP f ',' D	{ emit2($1 | $4 | $2); }
	| BYTEOP f		{ emit2($1 | 0x80 | $2); }
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
