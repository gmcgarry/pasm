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

/*
 *  Pre-UAL syntax.
 */

#define MASK(val,nbits)				((val)&((1<<(nbits))-1))
#define BITS(val,nbits,shift)			(MASK((val),(nbits))<<(shift))

#define ISA(val)				do { if (isa < val) serror("invalid instruction for ISA"); } while(0)

operation
	: PSEUDOOP_ARCH IDENT			{ setarch($2->i_name); }
	| PSEUDOOP_CPU IDENT 			{ setcpu($2->i_name); }
	| PSEUDOOP_FPU IDENT			{ setfpu($2->i_name); }
	| PSEUDOOP_MODE				{ if (pass == PASS_1) warning("ignoring .thumb directive"); }
	| PSEUDOOP_THUMBFUNC			{ if (pass == PASS_1) warning("ignoring .thumb_func directive"); }
	| PSEUDOOP_POOL				{ emit_literals(); }
#ifdef COMPAT_GAS
	| PSEUDOOP_EABIATTR NUMBER8 ',' NUMBER8	{ if (pass == PASS_1) warning("ignoring .eabi directive"); }
	| PSEUDOOP_SYNTAX IDENT			{ if (pass == PASS_1) warning("ignoring .syntax directive"); }
	| PSEUDOOP_CODE NUMBER8			{ if (pass == PASS_1) warning("ignoring .code directive"); }
#endif
#ifdef notyet
	| PSEUDOOP_FUNC				{ if (pass == PASS_1) warning("ignoring .fnstart/.fnend directive"); }
	| PSEUDOOP_CANTUNWIND			{ if (pass == PASS_1) warning("ignoring .cantunwind directive"); }
#endif

	| IMPL					{ emit2($1); }

	| SHIFT format_01			{ emit2($1|$2); }
	| SHIFT format_04			{ emit2(0x4000|BITS($1>>12,1,8)|BITS(~($1>>12),1,7)|BITS($1>>11,1,6)|$2); }

	| ADD format_02				{ emit2($1|$2); }
	| ADD format_03				{ ISA(ARMv6); emit2(0x3000|BITS($1>>9,1,11)|$2); }		/* XXXGJM: thumb2 */
	| ADD format_13				{ emit2(0xB000|BITS($1>>9,1,7)|$2); }

	| MOV format_03				{ emit2(0x2000|$2); }
	| MOV format_04				{ emit2(0x0000|$2); }
	| MOV format_05				{ ISA(ARMv6); emit2(0x4600|$2); }	/* thumb2 */

	| CMP format_03				{ emit2(0x2800|$2); }
	| CMP format_04				{ emit2(0x4280|$2); }
	| CMP format_05				{ ISA(ARMv6); emit2(0x4500|$2); }	/* thumb2 */

	| ADR format_12				{ emit2($1|$2); }

	| DATA1 format_04			{ emit2($1|$2); }

	| LDST format_07			{ emit2(0x5000|BITS($1,1,11)|$2); }
	| LDST format_09			{ emit2(0x6000|BITS($1,1,11)|$2); }
	| LDST format_11			{ emit2(0x9000|BITS($1,1,11)|$2); }
	| LDST format_12			{ emit2(0x4800|$2); if ($1 != 1) serror("invalid format"); }
	| LDST format_06			{ emit2(0x4800|$2); if ($1 != 1) serror("invalid format"); }

	| LDSTB format_07			{ emit2(0x5400|BITS($1,1,11)|$2); }
	| LDSTB format_09b			{ emit2(0x7000|BITS($1,1,11)|$2); }

	| LDSTH format_08			{ emit2(0x5200|BITS($1,1,11)|$2); }
	| LDSTH format_10			{ emit2(0x8000|BITS($1,1,11)|$2); }

	| LDRS format_08			{ emit2(0x5600|BITS($1,1,11)|$2); }

	| STACK format_14			{ emit2($1|$2); }

	| LDM format_15				{ emit2($1|$2); }

	| BREXCH REG				{ emit2($1|BITS($2,4,3)); }
	| BREXCH PC				{ emit2($1|BITS($2,4,3)); }
	| BREXCH LR				{ emit2($1|BITS($2,4,3)); }
	| LBRANCH offset			{
							/* if (pass == PASS_2 && $2&1) serror("bad alignment"); */
							int off = $2>>1;
							emit2(0xf000|BITS(off>>21,1,10)|BITS(off>>11,10,0));
							emit2(0xf800|BITS(off,11,0));
						}
#if 0
	| BREXCH offset				{ XXXX }
#endif
	| BRANCH format_16			{ emit2($1|BITS($2,8,0)); }
	| UBRANCH format_18			{ emit2($1|BITS($2,11,0)); }

	| SVC format_17				{ emit2($1|BITS($2,8,0)); }
	| SWI absexp				{ emit2($1|BITS($2,8,0)); }
	| IT					{ emit2(0xBF08); }
	| IT COND				{
							int opc = 0xBF00|BITS($2&0xe,4,4);
							int mask = 0x1;
							int v = $2&mask;
							while ($1&mask == 0) {
								mask <<= 1;
								v <<= 1;
							}
							opc |= mask;
							mask <<= 1;
							v <<= 1;
							while (mask != 0x10) {
								opc |= ($1&mask) ^ v;
								mask <<= 1;
								v <<= 1;
							}
						}

	| MSR PSR ',' REG			{ ISA(ARMv6M); if ($1&0x8000) ISA(ARMv6M); emit2(0xF380|BITS($2>>15,1,4)|BITS($4,4,0)); emit2(0x8800|BITS($2,8,0)); }
	| MSR REG ',' PSR			{ ISA(ARMv6M); if ($1&0x8000) ISA(ARMv6M); emit2(0xF3EF|BITS($4>>15,1,4)|BITS($4,0,0)); emit2(0x8000|BITS($2,4,8)|BITS($4,8,0)); }

	| CBNZ format_20			{ ISA(ARMv6T2); emit2($1|$2); }
	;

format_01
	: REG ',' REG ',' '#' absexp		{ $$ = BITS($6,5,6)|BITS($3,3,3)|BITS($1,3,0); }
	;

format_02
	: REG ',' REG ',' REG			{ $$ = BITS(0,1,10)|BITS($5,3,6)|BITS($3,3,3)|BITS($1,3,0); }
	| REG ',' REG ',' '#' absexp		{ $$ = BITS(1,1,10)|BITS($6,3,6)|BITS($3,3,3)|BITS($1,3,0); }
	;

format_03
	: REG ',' '#' absexp			{ $$ = BITS($1,3,8)|BITS($4,8,0); }
	;

format_04
	: REG ',' REG				{ $$ = BITS($3,3,3)|BITS($1,3,0); }
#ifdef COMPAT_GAS
	| REG ',' REG ',' REG			{ $$ = BITS($5,3,3)|BITS($1,3,0); if ($1 != $3) serror("bad operands"); }
#endif
	;

format_05
	: reghi ',' reg				{ $$ = BITS(1,1,7)|BITS($1,4,3)|BITS($3,3,0); }
	| REG ',' reghi				{ $$ = BITS(0,1,7)|BITS($3,4,3)|BITS($1,3,0); }
	;


format_06
	: REG ',' '=' expr			{
							ADDR_T addr = add_literal($4.val);
							ADDR_T offset = addr - DOTVAL;
							if (pass == PASS_2 && offset&3)
								serror("bad alignment");
							$$ = BITS($1,3,8)|BITS(offset>>2,8,0);
						}
	;

format_07
	: REG ',' '[' REG ',' REG ']'		{ $$ = BITS($6,3,6)|BITS($4,3,3)|BITS($1,3,0); }
	;

format_08
	: format_07				{ $$ = $1; }
	;

format_09
	: REG ',' '[' REG ',' '#' absexp ']'	{ $$ = BITS($7>>2,5,6)|BITS($4,3,3)|BITS($1,3,0); }
	| REG ',' '[' REG ']'			{ $$ = BITS($4,3,3)|BITS($1,3,0); }
	;

format_09b
	: REG ',' '[' REG ',' '#' absexp ']'	{ $$ = BITS($7,5,6)|BITS($4,3,3)|BITS($1,3,0); }
	| REG ',' '[' REG ']'			{ $$ = BITS($4,3,3)|BITS($1,3,0); }
	;

format_10
	: REG ',' '[' REG ',' '#' absexp ']'	{ $$ = BITS($7>>1,5,6)|BITS($4,3,3)|BITS($1,3,0); }
	| REG ',' '[' REG ']'			{ $$ = BITS($4,3,3)|BITS($1,3,0); }
	;

format_11
	: REG ',' '[' SP ',' '#' absexp ']'	{ $$ = BITS($1,3,8)|BITS($7>>2,8,0); }
	| REG ',' '[' SP ']'			{ $$ = BITS($1,3,8); }
	;

format_12
	: REG ',' '[' PC ',' '#' absexp ']'	{ $$ = BITS($1,3,8)|BITS($7>>2,8,0);}
	| REG ',' offset32			{ $$ = BITS($1,3,8)|BITS($3>>2,8,0); }
	;

format_13
	: SP ',' '#' absexp			{ $$ = BITS($4>>2,7,0); }
	;

format_14
	: reg					{ if ($1 == 14 || $1 == 15) $1 = 8; $$ = (1<<$1); }
	| reglist				{ $$ = $1; }
	;

format_15
	: REG ',' reglist			{ $$ = BITS($1,3,8)|BITS($3,8,0); }
	| REG '!' ',' reglist			{ $$ = BITS($1,3,8)|BITS($4,8,0); if ((1<<$1)&$4) serror("bad register list"); }
	;

format_16
	: offset				{ $$ = $1>>1; /* if (pass == PASS_2 && ($1&1)) serror("bad branch alignment"); */ }
	;

format_17
	: '#' absexp				{ $$ = $2; /* 8-bit immediate */ }
	;

format_18
	: offset				{ $$ = $1>>1; /* 11-bit offset */ }
	;

format_20
	: REG ',' '#' absexp			{ $$ = BITS($4>>6,1,9)|BITS($4,5,3)|BITS($1,3,0); }

offset	: expr					{ $$ = ($1.val - (DOTVAL+4)); }
	;

offset32: expr					{ if (pass == PASS_1 && $1.val&3) serror("bad word alignment"); $$ = ($1.val - ((DOTVAL+4)&~3)); }
	;

reglist	: '{' rlist '}'				{ $$ = $2; }
	;

rlist	: reg					{ if ($1 == 14 || $1 == 15) $1 = 8; $$ = 1<<$1; }
	| rlist ',' reg				{ if ($3 == 14 || $3 == 15) $3 = 8; $$ = $1|1<<$3; }
	| REG '-' REG				{ for ($$ = 0; $1 <= $3; $1++) { $$ |= (1<<$1); } }
	;

reg	: REG					{ $$ = $1; }
	| LR					{ $$ = $1; }
	| PC					{ $$ = $1; }
	;

reghi	: REGHI					{ $$ = $1; }
	| SP					{ $$ = $1; }
	;
