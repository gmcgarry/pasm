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

/* CSKY ISA User Guide_v1.15.17-opensource.doc */
/* CSKY Architecture user_guide.pdf */

#define MASK(x,n)       (((1<<(n))-1)&(x))
#define BITS(x,n,s)     (MASK(x,n)<<(s))

#define JTYPE(op,offset)			0x0000|BITS(op,4,10)|BITS(offset,10,0)
#define ITYPE3(op,rx,rz,imm3,sop)		0x4000|BITS(op,3,11)|BITS(rx,3,8)|BITS(rz,3,5)|BITS(imm3,3,2)|BITS(sop,2,0)

#define ITYPE5(op,rx,rz,imm5)			0x4000|BITS(op,3,11)|BITS(rx,3,8)|BITS(rz,3,5)|BITS(imm5,5,0)

#define ITYPE5_1(op,rx,rz,imm5)			0x4000|BITS(op,3,11)|BITS(rx,3,8)|BITS(rz,3,5)|BITS(imm5,5,0)
#define ITYPE5_2(op,rx,rz,imm5)			0x8000|BITS(op,3,11)|BITS(rx,3,8)|BITS(rz,3,5)|BITS(imm5,5,0)
#define ITYPE5_3(op,rx,sop,imm5)		0x0000|BITS(op,3,11)|BITS(rx,3,8)|BITS(sop,3,5)|BITS(imm5,5,0)

#define ITYPE7(op,soprz,imm7)			0x0000|BITS(op,4,10)|BITS((imm7)>>5,2,8)|BITS(soprz,3,5)|BITS(imm7,5,0)
#define ITYPE8_1(op,rxrz,imm8)			0x0000|BITS(op,3,11)|BITS(rxrz,3,8)|BITS(imm8,8,0)
#define ITYPE8_2(op,rz,imm8)			0x8000|BITS(op,3,11)|BITS((imm8)>>5,3,8)|BITS(rz,3,5)|BITS(imm8,5,0)

#define RTYPE3(op,rx,rz,ry,sop)			0x4000|BITS(op,3,11)|BITS(rx,3,8)|BITS(rz,3,5)|BITS(ry,3,2)|BITS(sop,2,0)
#define RTYPE2(op,rzry,rx,sop)			0x4000|BITS(op,4,10)|BITS(rzry,4,6)|BITS(rx,4,2)|BITS(sop,2,0)

operation
	: PSEUDOOP_LITERALS			{ emit_literals(); }
	| IMPL					{ emit2($1); }
	| LRW LOREG ',' expr			{
							ADDR_T addr = add_literal($4.val);	
							ADDR_T off = addr - (DOTVAL - 2);
							fit(fitx(off+0x100, 10));
							// if (pass == PASS_2 && off & 0x3) serror("alignment error");
							if (off < 0)
								emit2(ITYPE7(0,$2,~(off>>2)));
							else
								emit2(ITYPE7(4,$2,off>>2));
						}
	| MTCR reg ',' CREG			{ emit2(0xC000|($4&0x3e0)|$2); emit2(0x6420|($4&0x1F)); }
	| TWOOP reg ',' reg 			{ emit2($1|RTYPE2(0,$2,$4,0)); }
	| TWOOPI LOREG ',' expr			{ fit(fitx($2,3)); fit(fitx($4.val,8)); emit2($1|ITYPE8_1(0,$2,$4.val)); }
	| TWOOPIO LOREG ',' expr		{ fit(fitx($2,3)); fit(fitx($4.val-1,8)); emit2($1|ITYPE8_1(0,$2,$4.val-1)); }
	| JSR reg				{ emit2(RTYPE2($1,0xF,$2,0x1)); }
	| JTYPE offset				{ fit(fitx($2+0x400,11)); emit2(JTYPE($1,$2>>1)); }
	| LDST LOREG ',' '(' reg ',' expr ')'	{
							int shift = $1 & 0x03;
							if ($5 == 14) /* SP */ {
								if (shift != 0x2) serror("bad load/store syntax");
								fit(fitx($7.val>>shift,8));
								emit2(ITYPE8_2($1+1,$2,$7.val>>shift));
							} else {
								fit(fitx($5,3));
								fit(fitx(($7.val>>shift),5));
								emit2(ITYPE5_2($1,$5,$2,$7.val>>shift));
							}
						}
	| BIT LOREG ',' expr			{ fit(fitx($4.val, 5)); fit(fitx($2,3)); emit2($1|ITYPE5_3(0,$2,0,$4.val)); }
	| BITO LOREG ',' expr			{ fit(fitx($4.val-1, 5)); fit(fitx($2,3)); emit2($1|ITYPE5_3(0,$2,0,$4.val-1)); }
	| TWOOP reg ',' reg			{ emit2($1|RTYPE2(0,$2,$4,0)); }
	;

offset
	: expr					{ $$ = $1.val - DOTVAL; }
	;

reg
	: LOREG					{ $$ = $1; }
	| HIREG					{ $$ = $1; }
	;
