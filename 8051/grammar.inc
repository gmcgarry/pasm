/*-
 * Copyright (c) 1990 Ken Stauffer (University of Calgary)
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

/*
 * Mostly taken for parser.y:
 *
 * as31 - 8031/8051 Assembler
 *
 * Maintained at:  http://www.pjrc.com/tech/8051/
 * Please report problems to:  paul@pjrc.com
 */

#define fitx(x, d)      ((((x) + (1<<(d-1))) & ~((int)(1<<(d))-1)) == 0)
#define fitu(x, d)	(((x) & ~((int)(1<<(d))-1)) == 0)

#define isbit8(v)	fitu(v, 8)
#define isbit11(v)	fitx(v, 11)
#define isbit16(v)	fitx(v, 16)
#define isbmram(a)	(((a)&0xf0) == 0x20)
#define isbmsfr(a)	(((a)&0x80) && !((a)&0x07))


operation	: NOP			{ emit1($1); }
		| ACALL addr11		{ emitop($1); }
		| AJMP addr11		{ emitop($1); }
		| ADD two_op1		{ addop(0); }
		| ADDC two_op1		{ addcop(0); }
		| SUBB two_op1		{ xrlop(0); }
		| XRL two_op1		{ xrlop(0); }
		| XRL two_op2		{ xrlop(4); }
		| ANL two_op1		{ anlop(0); }
		| ANL two_op2		{ anlop(4); }
		| ANL two_op3		{ anlop(6); }
		| ORL two_op1		{ orlop(0); }
		| ORL two_op2		{ orlop(4); }
		| ORL two_op3		{ orlop(6); }
		| XCH two_op1		{ if (get_md(mode) == 3) warning("Immediate mode is illegal"); xchop(0); }
		| INC single_op1	{ incop(0); }
		| INC DPTR		{ incop(4); }
		| DEC single_op1	{ decop(0); }
		| DA A			{ emit1($1); }
		| DIV AB		{ emit1($1); }
		| JMP '@' A '+' DPTR	{ emit1($1); }
		| JMP '@' DPTR '+' A	{ emit1($1); }
		| MUL AB		{ emit1($1); }
		| RET			{ emit1($1); }
		| RETI			{ emit1($1); }
		| RL A			{ emit1($1); }
		| RLC A			{ emit1($1); }
		| RR A			{ emit1($1); }
		| RRC A			{ emit1($1); }
		| SWAP A		{ emit1($1); }
		| XCHD two_op1		{ if (get_md(mode) != 2) warning("Invalid addressing mode"); xchop(-2); }
		| CLR single_op2	{ clrop(0); }
		| CPL single_op2	{ cplop(0); }
		| SETB single_op2	{ if (get_md(mode) == 0) warning("Invalid addressing mode"); setbop(-1); }
		| PUSH data8		{ set_md(mode,0); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$2); emitop($1); }
		| POP data8		{ set_md(mode,0); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$2); emitop($1); }
		| LJMP addr16		{ emitop($1); }
		| LCALL addr16		{ emitop($1); }
		| JC relative		{ emitop($1); }
		| JNC relative		{ emitop($1); }
		| JNZ relative		{ emitop($1); }
		| JZ relative		{ emitop($1); }
		| SJMP relative		{ emitop($1); }
		| CJNE three_op1	{ cjneop(0); }
		| JB two_op4		{ emitop($1); }
		| JNB two_op4		{ emitop($1); }
		| JBC two_op4		{ emitop($1); }
		| DJNZ two_op5		{ djnzop(0); }
		| MOV two_op1		{ movop(0); }
		| MOV two_op2		{ movop(4); }
		| MOV two_op6		{ movop(6); }
		| MOVC A ',' '@' A '+' PC	{ emit1($1); }
		| MOVC A ',' '@' PC '+' A	{ emit1($1); }
		| MOVC A ',' '@' A '+' DPTR	{ emit1($1|0x10); }
		| MOVC A ',' '@' DPTR '+' A	{ emit1($1|0x10); }
		| MOVX A ',' '@' regi		{ movxop($5); }
		| MOVX A ',' '@' DPTR		{ movxop(2); }
		| MOVX '@' regi ',' A		{ movxop($3+3); }
		| MOVX '@' DPTR ',' A		{ movxop(5); }
		| IDENT BIT bit			{ newequate($1, S_ABS); store($1, $3); }
		| PSEUDOOP_AREA IDENT '(' flags ')'	{ newsect($2, 0, NULL); }
		;

flags		: IDENT			{ }
		| flags ',' IDENT	{ }
		;

two_op1		: A ',' reg		{ set_md(mode,0); set_ov(mode, $3); set_sz(mode, 0); }
		| A ',' data8		{ set_md(mode,1); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$3); }
		| A ',' '@' regi	{ set_md(mode,2); set_ov(mode,$4); set_sz(mode,0); }
		| A ',' const8		{ set_md(mode,3); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$3); }
		;

two_op2		: data8 ',' A		{ set_md(mode,0); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$1); }
		| data8 ',' const8	{ set_md(mode,1); set_ov(mode,0); set_sz(mode,2); set_b1(mode,$1); set_b2(mode,$3); }
		;

two_op3		: C ',' bit		{ set_md(mode,0); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$3); }
		| C ',' '/' bit		{ set_md(mode,1); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$4); }
		| C ',' '!' bit		{ set_md(mode,1); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$4); }
		;

two_op4		: bit ',' rel		{ set_md(mode,0); set_ov(mode,0); set_sz(mode,2); set_b1(mode,$1); set_b2(mode,$3); }
		;

two_op5		: reg ',' rel2		{ set_md(mode,0); set_ov(mode,$1); set_sz(mode,1); set_b1(mode,$3); }
		| data8 ',' rel		{ set_md(mode,1); set_ov(mode,0); set_sz(mode,2); set_b1(mode,$1); set_b2(mode,$3); }
		;

two_op6		: reg ',' A		{ set_md(mode,0); set_ov(mode,$1); set_sz(mode,0); }
		| reg ',' data8		{ set_md(mode,1); set_ov(mode,$1); set_sz(mode,1); set_b1(mode,$3); }
		| reg ',' const8	{ set_md(mode,2); set_ov(mode,$1); set_sz(mode,1); set_b1(mode,$3); }
		| data8 ',' reg		{ set_md(mode,3); set_ov(mode,$3); set_sz(mode,1); set_b1(mode,$1); }
		| data8 ',' data8	{ set_md(mode,4); set_ov(mode,0); set_sz(mode,2); set_b1(mode,$3); set_b2(mode,$1); }
		| data8 ',' '@' regi	{ set_md(mode,5); set_ov(mode,$4); set_sz(mode,1); set_b1(mode,$1); }
		| '@' regi ',' A	{ set_md(mode,6); set_ov(mode,$2); set_sz(mode,0); }
		| '@' regi ',' data8	{ set_md(mode,7); set_ov(mode,$2); set_sz(mode,1); set_b1(mode,$4); }
		| '@' regi ',' const8	{ set_md(mode,8); set_ov(mode,$2); set_sz(mode,1); set_b1(mode,$4); }
		| DPTR ',' const16	{ set_md(mode,9); set_ov(mode,0); set_sz(mode,2); set_b1(mode, ($3 & 0xff00) >> 8); set_b2(mode, ($3 & 0x00ff)); }
		| C ',' bit		{ set_md(mode,10); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$3); }
		| data8 ',' C		{ set_md(mode,11); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$1); }
		| data8 BITPOS ',' C
{
	if(pass == PASS_2) {
		if (!isbit8($1))
			warning("Bit address exceeds 8-bits");
	}
	if (isbmram($1))
		set_b1(mode, ($1-0x20)*8 + $2);
	else if(isbmsfr($1))
		set_b1(mode, $1 + $2);
	else
		warning("Invalid bit addressable RAM location");
	set_md(mode,11);
	set_ov(mode,0);
	set_sz(mode,1);
}
		;

single_op1	: A				{ set_md(mode,0); set_ov(mode,0); set_sz(mode,0); }
		| reg				{ set_md(mode,1); set_ov(mode,$1); set_sz(mode,0); }
		| data8				{ set_md(mode,2); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$1); }
		| '@' regi			{ set_md(mode,3); set_ov(mode,$2); set_sz(mode,0); }
		;

single_op2	: A				{ set_md(mode,0); set_ov(mode,0); set_sz(mode,0); }
		| C				{ set_md(mode,1); set_ov(mode,0); set_sz(mode,0); }
		| bit				{ set_md(mode,2); set_ov(mode,0); set_sz(mode,2); set_b1(mode,$1); }
		;

three_op1	: A ',' data8 ',' rel		{ set_md(mode,0); set_ov(mode,0); set_sz(mode,2); set_b1(mode,$3); set_b2(mode,$5); }
		| A ',' const8 ',' rel		{ set_md(mode,1); set_ov(mode,0); set_sz(mode,2); set_b1(mode,$3); set_b2(mode,$5); }
		| reg ',' const8 ',' rel	{ set_md(mode,2); set_ov(mode,$1); set_sz(mode,2); set_b1(mode,$3); set_b2(mode,$5); }
		| '@' regi ',' const8 ',' rel	{ set_md(mode,3); set_ov(mode,$2); set_sz(mode,2); set_b1(mode,$4); set_b2(mode,$6); }
		;

rel		: expr
{
		ADDR_T offset = $1.val - (DOTVAL + 3);
		if (pass == PASS_2) {
			if (offset > 127 || offset < -128)
			   warning("Relative offset exceeds -128 / +127");
		}
		$$ = offset;
}
		;

rel2		: expr
{
		long offset = $1.val - (DOTVAL + 2);
		if (pass == PASS_2) {
			if (offset > 127 || offset < -128)
			   warning("Relative offset exceeds -128 / +127");
		}
		$$ = offset;
}
		;

bit		: bitv BITPOS
{
	if (pass == PASS_2) {
		if (!isbit8($1))
			warning("Bit address exceeds 8-bits");
	}
	if (isbmram($1))
		$$ = ($1 - 0x20)*8 + $2;
	else if (isbmsfr($1))
		$$ = $1 + $2;
	else
		warning("Invalid bit addressable RAM location");
}
		| bitv		{ if( pass == PASS_2 ) { if (!isbit8($1) ) warning("Bit address exceeds 8-bits"); } $$ = $1; }
		;

bitv		: SFR		{ $$ = $1; }
		| absexp	{ $$ = $1; }
		;

reg		: AREG		{ $$ = $1; }
		;

regi		: AREG		{ $$ = $1; if ($1 > 1) warning("Illegal indirect register: @r2"); }
		;

data8		: expr		{ if (pass == PASS_2) { if (!isbit8($1.val)) warning("Expression greater than 8-bits"); } $$ = $1.val; }
		;

data16		: expr		{ if (pass == PASS_2) { if (!isbit16($1.val)) warning("Expression greater than 16-bits"); } $$ = $1.val; }
		;

const8		: '#' expr	{ $$ = $2.val; }
		| expr		{ if (pass == PASS_2 && $1.typ != S_ABS) serror("non-const expressions"); $$ = $1.val; }
		;

const16		: '#' expr	{ $$ = $2.val; }
		| expr		{ if (pass == PASS_2 && $1.typ != S_ABS) serror("non-const expressions"); $$ = $1.val; }
		;

expr		: '#' expr	{ $$.typ = S_ABS; $$.val = $2.val; }
		| SFR		{ $$.typ = S_ABS; $$.val = $1; }
		;

addr11		: expr
{
		if (pass == PASS_2) {
			if (!isbit16($1.val))
				warning("Address greater than 16-bits");
			if (($1.val & ~0x7FF) != ((DOTVAL+2) & ~0x7FF))
				warning("Address outside current 2K page");
		}
		set_md(mode,0);
		set_ov(mode, ($1.val & 0x0700) >> 3);
		set_sz(mode,1);
		set_b1(mode,$1.val & 0x00ff);
}
		;

addr16		: expr
{
		if( pass == PASS_2 ) {
			if( !isbit16($1.val)  )
				warning("Address greater than 16-bits");
		}
		set_md(mode,0);
		set_ov(mode, 0 );
		set_sz(mode,2);
		set_b1(mode, ($1.val & 0xff00 ) >> 8 );
		set_b2(mode, ($1.val & 0x00ff ) );
}
		;

relative	: expr
{
		long offset = $1.val - (DOTVAL+2);
		if (pass == PASS_2) {
			if (offset>127 || offset<-128)
			   warning("Relative offset exceeds -128 / +127");
		}
		set_md(mode, 0);
		set_ov(mode, 0);
		set_sz(mode, 1);
		set_b1(mode, offset);
}
		;
