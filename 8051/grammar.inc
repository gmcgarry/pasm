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

#define size8		(~0x00ff)
#define size11		(~0x07ff)
#define size15		(~0x7fff)
#define size16		(~0xffff)
#define isbit8(v)	(!(((v)>=0) ? (v)&size8 : -(v)>=128))
#define isbit11(v)	(!(((v)>=0) ? (v)&size11 : (-(v))&size10))
#define isbit16(v)	(!(((v)>=0) ? (v)&size16 : (-(v))&size15))
#define isbmram(a)	(((a)&0xf0)==0x20)
#define isbmsfr(a)	(((a)&0x80) && !((a)&0x07))


operation	: NOP			{ makeop($1,NULL,0); }
		| ACALL addr11		{ makeop($1,&mode,0); }
		| AJMP addr11		{ makeop($1,&mode,0); }
		| ADD two_op1		{ makeop($1,&mode,0); }
		| ADDC two_op1		{ makeop($1,&mode,0); }
		| SUBB two_op1		{ makeop($1,&mode,0); }
		| XRL two_op1		{ makeop($1,&mode,0); }
		| XRL two_op2		{ makeop($1,&mode,4); }
		| ANL two_op1		{ makeop($1,&mode,0); }
		| ANL two_op2		{ makeop($1,&mode,4); }
		| ANL two_op3		{ makeop($1,&mode,6); }
		| ORL two_op1		{ makeop($1,&mode,0); }
		| ORL two_op2		{ makeop($1,&mode,4); }
		| ORL two_op3		{ makeop($1,&mode,6); }
		| XCH two_op1		{ if (get_md(mode) == 3) warning("Immediate mode is illegal"); makeop($1,&mode,0); }
		| INC single_op1	{ makeop($1,&mode,0); }
		| INC DPTR		{ makeop($1,NULL,4); }
		| DEC single_op1	{ makeop($1,&mode,0); }
		| DA A			{ makeop($1,NULL,0); }
		| DIV AB		{ makeop($1,NULL,0); }
		| JMP '@' A '+' DPTR	{ makeop($1,NULL,0); }
		| JMP '@' DPTR '+' A	{ makeop($1,NULL,0); }
		| MUL AB		{ makeop($1,NULL,0); }
		| RET			{ makeop($1,NULL,0); }
		| RETI			{ makeop($1,NULL,0); }
		| RL A			{ makeop($1,NULL,0); }
		| RLC A			{ makeop($1,NULL,0); }
		| RR A			{ makeop($1,NULL,0); }
		| RRC A			{ makeop($1,NULL,0); }
		| SWAP A		{ makeop($1,NULL,0); }
		| XCHD two_op1		{ if (get_md(mode) != 2) warning("Invalid addressing mode"); makeop($1,&mode,-2); }
		| CLR single_op2	{ makeop($1,&mode,0); }
		| CPL single_op2	{ makeop($1,&mode,0); }
		| SETB single_op2	{ if (get_md(mode) == 0) warning("Invalid addressing mode"); makeop($1,&mode,-1); }
		| PUSH data8		{ set_md(mode,0); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$2); makeop($1,&mode,0); }
		| POP data8		{ set_md(mode,0); set_ov(mode,0); set_sz(mode,1); set_b1(mode,$2); makeop($1,&mode,0); }
		| LJMP addr16		{ makeop($1,&mode,0); }
		| LCALL addr16		{ makeop($1,&mode,0); }
		| JC relative		{ makeop($1,&mode,0); }
		| JNC relative		{ makeop($1,&mode,0); }
		| JNZ relative		{ makeop($1,&mode,0); }
		| JZ relative		{ makeop($1,&mode,0); }
		| SJMP relative		{ makeop($1,&mode,0); }
		| CJNE three_op1	{ makeop($1,&mode,0); }
		| JB two_op4		{ makeop($1,&mode,0); }
		| JNB two_op4		{ makeop($1,&mode,0); }
		| JBC two_op4		{ makeop($1,&mode,0); }
		| DJNZ two_op5		{ makeop($1,&mode,0); }
		| MOV two_op1		{ makeop($1,&mode,0); }
		| MOV two_op2		{ makeop($1,&mode,4); }
		| MOV two_op6		{ makeop($1,&mode,6); }
		| MOVC A ',' '@' A '+' PC	{ makeop($1,NULL,0); }
		| MOVC A ',' '@' PC '+' A	{ makeop($1,NULL,0); }
		| MOVC A ',' '@' A '+' DPTR	{ makeop($1|0x10,NULL,0); }
		| MOVC A ',' '@' DPTR '+' A	{ makeop($1|0x10,NULL,0); }
		| MOVX A ',' '@' regi		{ makeop($1,NULL,$5); }
		| MOVX A ',' '@' DPTR		{ makeop($1,NULL,2); }
		| MOVX '@' regi ',' A		{ makeop($1,NULL,$3+3); }
		| MOVX '@' DPTR ',' A		{ makeop($1,NULL,5); }
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
		| bitv			{ if( pass == PASS_2 ) { if (!isbit8($1) ) warning("Bit address exceeds 8-bits"); } $$ = $1; }
		;

bitv		: SREG			{ $$ = $1; }
		| absexp		{ $$ = $1; }
		;

reg		: R0		{ $$ = $1; }
		| R1		{ $$ = $1; }
		| R2		{ $$ = $1; }
		| R3		{ $$ = $1; }
		| R4		{ $$ = $1; }
		| R5		{ $$ = $1; }
		| R6		{ $$ = $1; }
		| R7		{ $$ = $1; }
		;

regi		: R0		{ $$ = $1; }
		| R1		{ $$ = $1; }
		| R2		{ $$ = $1; warning("Illegal indirect register: @r2"); }
		| R3		{ $$ = $1; warning("Illegal indirect register: @r3"); }
		| R4		{ $$ = $1; warning("Illegal indirect register: @r4"); }
		| R5		{ $$ = $1; warning("Illegal indirect register: @r5"); }
		| R6		{ $$ = $1; warning("Illegal indirect register: @r6"); }
		| R7		{ $$ = $1; warning("Illegal indirect register: @r7"); }
		;

data8		: expr		{ if (pass == PASS_2) { if( !isbit8($1.val)) warning("Expression greater than 8-bits"); } $$ = $1.val; }
		| SREG		{ $$ = $1; }
		;

data16		: expr		{ if (pass == PASS_2) { if( !isbit16($1.val)) warning("Expression greater than 16-bits"); } $$ = $1.val; }
		;

const8		: expr		{ $$ = $1.val; }
		| SREG		{ $$ = $1; }
		;

expr		: '#' expr	{ $$.typ = S_ABS; $$.val = $2.val; }
		;

const16		:  expr		{ $$ = $1.val; }
		;

addr11		: expr
{
		if (pass == PASS_2) {
			if (!isbit16($1.val))
				warning("Address greater than 16-bits");
			if (($1.val & size11) != ((DOTVAL+2) & size11))
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
