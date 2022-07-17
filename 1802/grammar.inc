/*-
 * Copyright (c) 2022 Gregory McGarry <g.mcgarry@ieee.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND fituNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROfituS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

program
	: program IDENT		{ newident($2, DOTSCT); newlabel($2); /* RELODONE; */ }
	;

operation
	: NOARG			{ emit1($1); }
	| IOP expr		{ emit1($1); emit1($2.val); }
	| XOP reg		{ fit(fitx($2.val,4)); emit1($1|$2.val); }
	| IO expr		{ fit(fitx($2.val,3)); emit1($1|$2.val); }
	| BRANCH expr		{ branch($1,$2); }
	| PSEU expr		{ emit1($1); emit2($2.val); }
	;

expr
	: SHIFTFUNC expr	{ $$.val = ($2.val >> $1) & 0xFF; if (PASS_RELO) fit(fitx($$.val,8)); }
	;

reg
	: expr
	| REG			{ $$.val = $1; $$.typ = S_ABS; }
	;
