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

#define FIT(x,b)		(((x) & ~((1 << (b))-1)) == 0)	/* XXXGJM only works for positive values */

#define emit3(x)		do { emit1((x) >> 0); emit1((x) >> 8); emit1((x) << 16); } while (0)
#define encodeRRRN(x,r,s,t)	((x) | ((r) << 8) | ((s) << 4) | ((t) << 0))
#define encodeRRR(x,r,s,t)	((x) | ((r) << 12) | ((s) << 8) | ((t) << 4))

operation: PSEUDOOP_LITPOS				{ }
	| PSEUDOOP_LITERAL IDENT ',' expr ',' expr	{ emit2($4.val); emit2($6.val); }
	| PSEUDOOP_LITERAL IDENT ',' expr		{ literal($2, $4); }
	| insn24					{ emit3($1); }
	| insn16					{ emit2($1); }
	;

insn16	: FORMAT_RRRN					{ $$ = $1; }
	| FORMAT_RRRN_RST	REG ',' REG ',' REG	{ $$ = encodeRRRN($1, $2, $4, $6); }
	| FORMAT_RRRN_S		REG			{ $$ = encodeRRRN($1, 0, $2, 0); }
	| FORMAT_RRRN_TS	REG ',' REG		{ $$ = encodeRRRN($1, 0, $4, $2); }			/* _st_ */
	| FORMAT_RRRN_TSIx4	REG ',' REG ',' absexp	{ $$ = encodeRRRN($1, $6/4, $2, $4); }			/* rst_	*/
	| FORMAT_RRRN_RSI	REG ',' REG ',' imm4_n1	{ $$ = encodeRRRN($1, $2, $4, $6); }			/* rst_ */
	| FORMAT_RI7		REG ',' imm7_m32	{ $$ = encodeRRRN($1, $4&0xf, $2, ($4>>4)&0x7); }	/* xsx_ */
	| FORMAT_RI6		REG ',' imm16		{ $$ = encodeRRRN($1, $4&0xf, $2, ($4>>4)&0x3); }	/* xsx_ */
	;

insn24	: FORMAT_RRR					{ $$ = encodeRRR($1, 0, 0, 0); }			/*_______ */
	| FORMAT_RRR_S		REG			{ $$ = encodeRRR($1, 0, $2, 0); }			/* -__s__ */
	| FORMAT_RRR_RSS	REG ',' REG		{ $$ = encodeRRR($1, $2, $4, $4); }			/* __rss_ */
	| FORMAT_RRR_RS		REG ',' REG		{ $$ = encodeRRR($1, $2, $4, 0); }			/* __rs__ */
	| FORMAT_RRR_RT		REG ',' REG		{ $$ = encodeRRR($1, $2, 0, $4); }			/* __r_t_ */
	| FORMAT_RRR_RST	REG ',' REG ',' REG	{ $$ = encodeRRR($1, $2, $4, $6); }			/* __rst_ */
	| FORMAT_RSR		REG ',' SREG 		{ $$ = encodeRRR($1, $2, $2, $4); }			/* __sst_ */
	| FORMAT_RRI8_TI	REG ',' imm12		{ $$ = encodeRRR($1, 0, ($4>>16)&0xf, $2) | (($4&0xff)<< 16); }		/* ii_xt_ */
	| FORMAT_RRR_RSI5	REG ',' REG ',' imm5_p	{ $$ = encodeRRR($1, $2, $4, $6&0xf) | (($6&0x10) << 16); }	/* i_rsi_ */
	| FORMAT_RRR_RTI4	REG ',' REG ',' imm4	{ $$ = encodeRRR($1, $2, $4, $6); }			/* __rot_ */
	| FORMAT_RRR_RTI5	REG ',' REG ',' imm5	{ $$ = encodeRRR($1, $2, $4, $6&0x4) | (($6&0x10) << 16); }	/* i_rit_ */
	| FORMAT_RRR_SI		REG ',' imm8		{ $$ = encodeRRR($1, 0, $2, 0) | ($4 << 16); }		/* ii_s__ */
	| FORMAT_RRI8_TSIx2	REG ',' REG ',' imm8	{ $$ = encodeRRR($1, 0, $2, $4) | (($6 / 2) << 16); }	/* ii_st_ */
	| FORMAT_RRI8_TSIx4	REG ',' REG ',' imm8_x4	{ $$ = encodeRRR($1, 0, $4, $2) | ($6 << 16); }		/* ii2xt2 */
	| FORMAT_RRI8_TSI	REG ',' REG ',' imm8	{ $$ = encodeRRR($1, 0, $4, $2) | ($6 << 16); }		/* ii_st_ */
	| FORMAT_RRI8_RSI	REG ',' imm4 ',' imm8	{ $$ = encodeRRR($1, $4, $2, 0) | ($6 << 16); }		/* iirs__ */
	| FORMAT_RRI8_STI	REG ',' REG ',' imm8	{ $$ = encodeRRR($1, 0, $2, $4) | ($6 << 16); }		/* ii_st_ */
	| FORMAT_RII6_TI	REG ',' imm16		{ $$ = encodeRRR($1, 0, 0, $2) | (($4&0xff) << 16) | (($4&0xff00) >> 4); }	/* iiiit_ */
	| FORMAT_RRR_STmm	REG ',' REG ',' imm5 ',' imm4_p1	{ $$ = encodeRRR($1, $2, $6&0xf, $4) | (($6&0x10)<<12) | ($8<<20); }	/* o_rst_ */
	| FORMAT_BRI8_RSI	REG ',' b4const ',' imm8	{ $$ = encodeRRR($1, $4, $2, 0) | ($6 << 16); }	/* iirs__ */
	| FORMAT_BRI12		REG ',' imm12_x8	{ $$ = encodeRRR($1, $4>>8, $2, 0) | (($4 & 0xff) << 16); }	/* iixs__ */
	| FORMAT_BRI12_SI	REG ',' imm12		{ $$ = encodeRRR($1, $4>>8, $2, 0) | (($4 & 0xff) << 16); }	/* iixs__ */
	| FORMAT_RRI8_TSIx256	REG ',' REG ',' imm8_x256	{ $$ = encodeRRR($1, 0, $4, $2) | ($6 << 16); }	/* ii_st_ */
	| CALLOP		expr			{ $$ = encodeRRR($1, $2.val>>8, $2.val>>12, 0) | ($2.val << 16); newrelo($2.typ, RELO2); }	/* iiii__ */
	| CALLXOP		REG			{ $$ = encodeRRR($1, 0, $2, 0);	}			/* ___s__ */
	;

reg	: REG				{ $$ = $1; }
	| SREG				{ $$ = $1; }
	| FREG				{ $$ = $1; }
	| BREG				{ $$ = $1; }
	;

imm4	: expr				{ $$ = $1.val; if (!FIT($$,4)) serror("invalid 4-bit alue"); }
	;

imm4_n1	: expr				{ int imm = $1.val;  if (imm < -1 || imm > 15 || imm == 0) serror("bad immediate value"); $$ = (imm > 0 ? imm : 0); }
	;

imm4_p1	: absexp			{ $$ = $1-1; if (!FIT($$,4)) serror("mask too large"); }
	;

b4const: absexp				{ $$ = b4const($1); }
	;

imm5	: absexp			{ $$ = $1; if (!FIT($$,5)) serror("immediate too large"); };
	;

imm5_p	: absexp			{ $$ = $1; if (!FIT($$,5) || $$ == 0) serror("too large for 5-bit immediate"); };
	;


imm7_m32: expr				{ $$ = 32 + $1.val; if (!FIT($$,7)) serror("too large for 7-bit immediate"); }
	;

imm8	: expr				{ $$ = $1.val; }
	;

imm8_x4	: absexp			{ $$ = $1 / 4;  if (!FIT($$,8)) serror("too large for 8-bit immediate"); }
	;

imm8_x256 : absexp			{ $$ = ($1 >> 8) & 0xff; }
	;

imm12	: expr				{ $$ = $1.val & 0xfff; }
	;

imm12_x8: absexp			{ $$ = $1 / 8; }
	;

imm16	: expr				{ $$ = $1.val; if (!FIT($$,16)) serror("value too large"); }
	;

imm18	: expr				{ $$ = $1.val; if (!FIT($$,18)) serror("value too large"); }
	;
