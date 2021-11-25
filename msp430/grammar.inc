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

/* values for As bits */
#define OPR_REGISTER	0x00
#define OPR_INDEXED	0x10
#define OPR_INDIRECT	0x20
#define OPR_INDIRECTINC	0x30

#define SRCOP(x)	((((x) & 0x30) == OPR_INDEXED || ((x) & 0x0f30) == OPR_INDIRECTINC) && (((x)>>8) != 2 && (((x)>>8) != 3)))
#define DSTOP(x)	(((x) & 0x80) != 0)

#define NOTCGR(x)	do { if ((x) == 2 || (x) == 3) serror("bad use of CG register"); } while(0)

/* O O O O | S S S S | Ad | B/W | As As | D D D D | 16-bit source/destination | 16-bit destination */
/* O O O O O O O O | O | As As | D D D D | 16-bit distination */
/* O O O O | C C C | 10-bit offset */

operation
	: optlabel instr		{ }
	| PSEUDOOP_SECT STRING		{
						item_t *ip = item_search(stringbuf);
						if (ip == NULL) {
							ip = item_alloc(S_UND);
                					ip->i_name = remember(stringbuf);
                					DPRINTF(("adding ident %s %p\n", ip->i_name, ip));
                					unresolved++;
                					item_insert(ip, H_GLOBAL + (hashindex % H_SIZE));
						}
				 		newsect(ip, 0, NULL);
					}
	| PSEUDOOP_CDECLS IDENT ',' IDENT ',' STRING	{ }
	| PSEUDOOP_RETAIN		{ if (pass == PASS_1) warning("ignoring .retain/.retainrfs directive"); }
	| PSEUDOOP_USECT STRING ',' expr ',' expr
					{ warning("ignoring .usect directive"); }
	;
	
optlabel
	: /* empty */
	| IDENT				{ newident($1, DOTSCT); newlabel($1); }
	;

instr
	: IMPL				{ emit2($1); }
	| RM optsiz dst			{ emit2($1|$2|($3&0xFFFF)); if (SRCOP($3)) emit2($3>>16); }
	| RMW optsiz src ',' dst	{ emit2($1|$2|($3&0xFFFF)|($5&0xFFFF)); if (SRCOP($3)) emit2($3>>16); if (DSTOP($5)) emit2($5>>16); }
	| RBRANCH offset10		{ emit2($1|$2); }
	| BRANCH src			{ emit2($1|($2&0xFFFF)); if (SRCOP($2)) emit2($2>>16); }
	;

src
	: '#' expr			{ $$ = constant($2); }
	| REG				{ $$ = ($1<<8)|OPR_REGISTER; }
	| '&' expr			{ $$ = ($2.val<<16)|(0x2<<8)|OPR_INDEXED; }
	| '@' REG			{ $$ = ($2<<8)|OPR_INDIRECT; NOTCGR($2); }
	| '@' REG '+'			{ $$ = ($2<<8)|OPR_INDIRECTINC; NOTCGR($2); }
	| expr '(' REG ')'		{
						NOTCGR($3);
						if (small($1.val == 0, 2)) 
							$$ = ($3<<8)|OPR_INDIRECT;
						else 
							$$ = ($1.val<<16)|($3<<8)|OPR_INDEXED;
					}
	| offset			{ $$ = ($1<<16)|(0x0<<8)|OPR_INDEXED; }	
	;

dst
	: REG				{ $$ = $1; }
	| '&' expr 			{ $$ = ($2.val<<16)|0x80|0x02; }		/* expr (SR) */
	| expr '(' REG ')'		{ $$ = ($1.val<<16)|$3|0x80; NOTCGR($3); }	/* expr (REG) */
	| offset			{ $$ = ($1<<16)|0x80; }				/* offset (PC) */
	;

offset
	: expr				{ $$ = $1.val - (DOTVAL + 2); }
	;

offset10
	: offset			{ fit(fitx($1+1024,11)); $$ = ($1>>1) & 0x3FF; }
	;

optsiz
	: /* empty */			{ $$ = 2; }
	| DATASIZE			{ $$ = $1; }
	;
