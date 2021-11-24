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

#define OPR_IMMEDIATE	0x30
#define OPR_REGISTER	0x00
#define OPR_ABSOLUTE	0x90
#define OPR_SYMBOLIC	0x90
#define OPR_INDIRECT	0x20
#define OPR_INDINC	0x30

#define NOTCGR(x)	do { if ((x) == 2 || (x) == 3) serror("bad use of CG register"); } while(0)

/* O O O O | S S S S | Ad | B/W | As As | D D D D | 16-bit source/destination | 16-bit destination */
/* O O O O O O O O | O | As As | D D D D | 16-bit distination */
/* O O O O | C C C | 10-bit offset */

operation
	: IMPL				{ emit2($1); }
	| RM optsiz dst		{ emit2($1|$2|($3&0x0F)); }
	| RMW optsiz src ',' dst	{ emit2($1|$2|($3&0x0F)|($5&0x0F)); }
	| RBRANCH offset		{ emit2($1|($2&0x3F)); }
	| BRANCH absexp			{ emit2($1|($2&0x3F)); }
	;

src
	: '#' expr			{ $$ = ($2.val<<16)|OPR_IMMEDIATE; }			/* FIXME */ /* N is stored in the following word; check for -1,0,1,2,8 */
	| REG				{ $$ = ($1<<8)|OPR_REGISTER; }
	| '&' expr			{ $$ = ($2.val<<16)|OPR_ABSOLUTE; }				/* FIXME */ /* N is stored in the following word */
	| '@' REG			{ $$ = ($2<<8)|OPR_INDIRECT; NOTCGR($2); }
	| '@' REG '+'			{ $$ = ($2<<8)|OPR_INDINC; NOTCGR($2); }
	| absexp '(' REG ')'		{ $$ = ($1<<16)|($3<<8)|OPR_SYMBOLIC; NOTCGR($3); }	/* FIXME */ /* offset is stored in the following word */
	| offset			{ $$ = ($1<<16)|OPR_SYMBOLIC; }				/* FIXME */ /* offset is stored in the following word */
	;

dst
	: REG				{ $$ = $1; }
	| '&' expr 			{ $$ = $2.val; }
	| '@' REG			{ $$ = $2; NOTCGR($2); }
	| absexp '(' REG ')'		{ $$ = $1; NOTCGR($3); }
	| offset			{ $$ = 0; }
	;

offset
	: expr				{ $$ = $1.val - DOTVAL; }
	;

optsiz
	: /* empty */			{ $$ = 2; }
	| DATASIZE			{ $$ = $1; }
	;
