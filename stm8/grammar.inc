/*
 * Copyright (c) 1987, 1990, 1993, 2005 Vrije Universiteit, Amsterdam, The Netherlands.
 * All rights reserved.
 * 
 * Redistribution and use of the Amsterdam Compiler Kit in source and
 * binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 * 
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 * 
 *    * Neither the name of Vrije Universiteit nor the names of the
 *      software authors or contributors may be used to endorse or
 *      promote products derived from this software without specific
 *      prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS, AUTHORS, AND
 * CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL VRIJE UNIVERSITEIT OR ANY AUTHORS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define fitb(x)		fitx(x, 8)
#define fitw(x)		fitx(x+32768, 16)

#define check(x)	do { if (deviceid < x) serror("invalid instruction or addressing mode for device"); } while (0)
#define stm8()		check(DEVICE_STM8)
#define st7()		check(DEVICE_ST7)
#define mc6805()	check(DEVICE_MC6805)

expr	: '{' expr '}'		{ $$  = $2; }
	;

bitexp
	: '#' absexp		{ fit((unsigned)$2 <= 7); $$ = $2 & 07; }
	;

operation
	: optlabel instr
	| PSEUDOOP_DEVICE	{ deviceid = $1; }
	| PSEUDOOP_SEGMENT STRING
				{
					item_t *ip = item_search(stringbuf);
					DPRINTF(("looking up identifier \"%s\"\n", stringbuf));
					DPRINTF(("%s ip=%p\n", stringbuf, ip));
					if (ip == 0) {
						ip = item_alloc(S_UND);
						ip->i_name = remember(stringbuf);
						DPRINTF(("adding ident %s %p\n", ip->i_name, ip));
						unresolved++;
						item_insert(ip, H_LOCAL + (hashindex % H_SIZE));
					}
					newsect(ip, 0, NULL);
				}
	;

optlabel
	: /* empty */
	| IDENT					{ newident($1, DOTSCT); newlabel($1); }
	;

instr
	: /* empty */
	| IMPL					{ emit1($1); }
	| BRANCH expr				{ expr_t expr = {0,0}; branch($1,$2,expr); }
	| BBRANCH expr ',' bitexp ',' expr	{ branch($1+($4 << 1), $6, $2); }
	| BIT expr ',' bitexp			{
							emit2($1+($4 << 1));
							if (deviceid == DEVICE_STM8) {
								newrelo($2.typ, RELO2);
								emit2($2.val);
							} else {
								newrelo($2.typ, RELO1);
								emit1($2.val);
							}
						}
#if 0
	// cpl, neg, call, clr, dec, inc, rlc, rrc, srl, sll, sra, sla, swap, tnz
	| RMW A							0x43			- not for call/jp			- register
	| RMW expr8						0x33	mem8		- not for call/jp			- direct
	| RMW expr16					0x72 	0x53	ms	ls						- direct
	| RMW '(' X ')'						0x73			(use prefix 0x90 for Y)			- indexed
	| RMW '(' expr8 ',' X ')'				0x63	mem8		(use prefix 0x90 for Y)			- indexed
	| RMW '(' expr16 ',' X ')'			0x72	0x43	ms	ls	(swap prefix 0x72 with 0x90 for Y)	- indexed

	| RMW '(' expr8 ',' SP ')'				0x03	mem8		- not for call/jp/neg			- sp indexed
	| RMW '[' expr8 WIDTH ']'			0x92	0x33	mem8							- indirect
	| RMW '[' expr16 WIDTH ']'			0x72	0x33	ms	ls						- indirect
	| RMW '(' '[' expr8 WIDTH']' ',' X ')'	0x92	0x63	xx							- indirect indexed 
	| RMW '(' '[' expr16 WIDTH ']' ',' X ')'	0x72	0x63	ms	ls						- indirect indexed
	| RMW '(' '[' expr8 WIDTH']' ',' Y ')'	0x91	0x63	xx							- indirect inedexed

	// adc, add, sbc, sub, and, or, xor, bcp, cp, ld
	| RM A ',' '#' expr8					0xa9	xx		- not for reverse direction of LD
	| RM A ',' expr8					0xb9	xx
	| RM A ',' expr16					0xc9	ms	ls
	| RM A ',' '(' X ')'					0xf9			(use prefix 0x90 for Y)
	| RM A ',' '(' expr8 ',' X ')'				0xe9	xx		(use prefix 0x90 for Y)
	| RM A ',' '(' expr16 ',' X ')'				0xd9	ms	ls	(use prefix 0x90 for Y)

	| RM A ',' '(' expr8 ',' SP ')'				0x19	xx
	| RM A ',' '[' expr8 WIDTH ']'				0x92	0xc9	xx
	| RM A ',' '[' expr16 WIDTH ']'				0x72	0xc9	ms	ls
	| RM A ',' '(' '[' expr8 WIDTH ']' ',' X ')'		0x92	0xd9	xx
	| RM A ',' '(' '[' expr16 WIDTH ']' ',' X ')'		0x72	0xd9	ms	ls
	| RM A ',' '(' '[' expr8 WIDTH ']' ',' Y ')'		0x91	0xd9	xx

	| SUB SP ',' '#' expr8					0x52	xx
	| ADD SP ',' '#' expr8					8x5b	xx

	// addw, subw
	| RM X ',' '#' expr16					0x1c	ms	ls
	| RM X ',' expr16				0x72	0xbb	ms	ls
	| RM X ',' '(' expr8 ',' SP ')'			0x72	0xfb	xx
	| RM Y ',' '#' expr16				0x72	0xa9	ms	ls
	| RM Y ',' expr16				0x72	0xb9	ms	ls
	| RM Y ',' '(' expr8 ',' SP ')'			0x72	0xf9	xx
	| RM SP ',' '#' expr8					0x5b	xx

	// ldw/cpw has everything!
	| CPW X ',' immediate					0xa3	ms	ls	(use prefix 0x90 for Y)
	| CPW X ',' direct8					0xb3	xx		(use prefix 0x90 for Y)
	| CPW X ',' direct16					0xc3	ms	ls	(use prefix 0x90 for Y)
	| CPW X ',' '(' Y ')'				0x90	0xf3			(remove prefix 0x90 for X)
	| CPW X ',' '(' expr8 ',' Y ')'			0x90	0xe3	xx		(remove prefix 0x90 for X)
	| CPW X ',' '(' expr16 ',' Y ')'		0x90	0xd3	ms	ls	(remove prefix 0x90 for X)
	| CPW X ',' '(' expr8 ',' SP ')'			0x13	xx		- not present for dst=Y
	| CPW X ',' '[' expr8 WIDTH ']'			0x92	0xc3	xx		(replace 0x92 with 0x91 for Y)
	| CPW X ',' '[' expr16 WIDTH ']'		0x72	0xc3	ms	ls	(replace 0x92 for 0x72 for Y)
	| CPW X ',' '(' '[' expr8 WIDTH ']' ',' Y ')'	0x91	0xd3	xx		(replace 0x91 for 0x92 for Y)
	| CPW Y ',' '(' '[' expr16 WIDTH ']' ',' X ')'	0x72	0xd3	ms	ls

	// div, mul, rlwa, rrwa
	| RM X, A		0x62
	| RM Y, A	0x90	0x62

	// divw, exgw
	| RM X, Y		0x65
	| RM X, Y		0x51

	// exg
	| RM A, XL		0x41
	| RM A, YL		0x61
	| RM A, expr16		0x31	ms	ls

	// relative jumps
	| JRxx expr		0x20	mem8



#endif

	| MOV direct ',' immediate	{ emit1($1+0x30); emit1($4.val); emit2($2.val); }
	| MOV direct ',' direct		{ if (fitx($2.val,8) && fitx($4.val,8)) { emit1($1+0x40); emit1($2.val); emit1($4.val); } else { emit1($1+0x50); emit2($2.val); emit2($4.val); } }

	/* iregular addressing modes */
	| LDW SP ',' X			{ stm8(); emit1(0x94); }
	| LDW SP ',' Y			{ stm8(); emit2(0x9094); }
	| LDW reg16 ',' SP		{ stm8(); if ($2 == Y) emit1(0x90); emit1(0x96); }
	| LDW reg16 ',' reg16		{ stm8(); if ($2 == $4) fatal("invalid registers"); if ($1 == Y) emit1(0x90); emit1(0x93); }
	| LDW expr ',' X		{
						stm8();
						if (small(PASS_RELO, fitb($2.val) ? 1 : 2)) {
							emit1(0xbf);
							emit1($2.val);
						} else {
							emit1(0xcf);
							emit2($2.val);
						}
					}
	| LDW '(' optoff X ')' ',' Y	{
						stm8();
						int opt = (($3.typ & S_SCTMASK) == DOTSCT) || (($3.typ & S_SCTMASK) == S_ABS);
						if (small($3.val == 0 && opt && PASS_RELO, 1)) {
							emit1(0xff);
						} else if (small(opt && PASS_RELO, fitb($3.val) ? 1 : 2)) {
							emit1(0xef);
							newrelo($3.typ, RELO1);
							emit1($3.val);
						} else {
							emit2(0xdf);
							newrelo($3.typ, RELO2);
							emit2($3.val);
						}
					}

	/* regular addressing modes */
	| LDW reg16 ',' immediate	{ stm8(); if ($2 == Y) emit1(0x90); emit1($1); emit2($4.val); }
	| LDW reg16 ',' direct		{
						stm8();
						if ($2 == Y) emit1(0x90);
						if (fitb($4.val)) {
							emit1($1+0x10);
							emit1($4.val);
						} else {
							emit1($1+0x30);
							emit2($4.val);
						}
					}
	| LDW reg16 ',' '(' optoff reg16 ')'
					{
						stm8();
						if ($6 == Y) emit1(0x90);
						int opt = (($5.typ & S_SCTMASK) == DOTSCT) || (($5.typ & S_SCTMASK) == S_ABS);
						if (small($5.val == 0 && opt && PASS_RELO, 1)) {
							emit1($1+0x40);
						} else if (small(opt && PASS_RELO, fitb($5.val) ? 1 : 2)) {
							emit1($1+0x30);
							newrelo($5.typ, RELO1);
							emit1($5.val);
						} else {
							emit2(0x72);
							emit1($1+0x30);
							newrelo($5.typ, RELO2);
							emit2($5.val);
						}
					}
	| LDW reg16 ',' indirect
					{
						stm8();
						int opt = (($4.typ & S_SCTMASK) == DOTSCT) || (($4.typ & S_SCTMASK) == S_ABS);
						if (small(opt && PASS_RELO, fitb($4.val) ? 1 : 2)) {
							if ($2 == Y)
								emit1(0x91);
							else
								emit1(0x92);
							emit1($1+0x30);
							newrelo($4.typ, RELO1);
							emit1($4.val);
						} else {
							if ($2 == Y) fatal("bad addressing with Y");
							emit1(0x72);
							emit1($1+0x30);
							newrelo($4.typ, RELO2);
							emit2($4.val);
						}
					}
	| LDW reg16 ',' '(' indirect ',' reg16 ')'
					{
						stm8();
						if ($2 != $7) fatal("mismatched registers");
						int opt = (($5.typ & S_SCTMASK) == DOTSCT) || (($5.typ & S_SCTMASK) == S_ABS);
						if (small(opt && PASS_RELO, fitb($5.val) ? 1 : 2)) {
							if ($2 == Y)
								emit1(0x91);
							else
								emit1(0x92);
							emit1($1+0x40);
							newrelo($5.typ, RELO1);
							emit1($5.val);
						} else {
							if ($2 == Y) fatal("bad addressing with Y");
							emit1(0x72);
							emit1($1+0x40);
							newrelo($5.typ, RELO2);
							emit2($5.val);
						}
					}
	| LDW reg16 ',' '(' expr ',' SP ')'
					{
						stm8();
						if ($2 == Y) emit1(0x16); else emit1(0x1E);
						emit1($5.val);
					}

#if 0
	| CPW X ',' immediate					0xa3	ms	ls	(use prefix 0x90 for Y)
	| CPW X ',' direct8					0xb3	xx		(use prefix 0x90 for Y)
	| CPW X ',' direct16					0xc3	ms	ls	(use prefix 0x90 for Y)
	| CPW X ',' '(' Y ')'				0x90	0xf3			(remove prefix 0x90 for X)
	| CPW X ',' '(' expr8 ',' Y ')'			0x90	0xe3	xx		(remove prefix 0x90 for X)
	| CPW X ',' '(' expr16 ',' Y ')'		0x90	0xd3	ms	ls	(remove prefix 0x90 for X)
	| CPW X ',' '(' expr8 ',' SP ')'			0x13	xx		- not present for dst=Y
	| CPW X ',' '[' expr8 WIDTH ']'			0x92	0xc3	xx		(replace 0x92 with 0x91 for Y)
	| CPW X ',' '[' expr16 WIDTH ']'		0x72	0xc3	ms	ls	(replace 0x92 for 0x72 for Y)
	| CPW X ',' '(' '[' expr8 WIDTH ']' ',' Y ')'	0x91	0xd3	xx		(replace 0x91 for 0x92 for Y)
	| CPW Y ',' '(' '[' expr16 WIDTH ']' ',' X ')'	0x72	0xd3	ms	ls
#endif

	| CPW X ',' immediate		{ stm8(); emit1($1-0x10); emit2($4.val); }
	| CPW X ',' direct		{ stm8(); if (fitb($4.val)) { emit1($1); emit1($4.val); } else { emit1($1+0x20); emit2($4.val); } }

	| CPW Y ',' immediate		{ stm8(); emit2((0x9000|$1)-0x10); emit2($4.val); }
	| CPW Y ',' direct		{ stm8(); if (fitb($4.val)) { emit2(0x9000|$1); emit1($4.val); } else { emit2((0x9000|$1)+0x20); emit2($4.val); } }

	// call, clr, dec, inc, rlc, rrc, srl, sll, sra, sla, swap, tnz
	// WTF com lsr ror asr lsl rol tst
	// regular addressing modes
	| RMW A				{ emit1($1 - 0x30 + 0x40); }
	| RMW direct			{
						int opt = (($2.typ & S_SCTMASK) == DOTSCT) || (($2.typ & S_SCTMASK) == S_ABS);
						if (small($2.val == 0 && opt && PASS_RELO, fitb($2.val) ? 1 : 2)) {
							emit1($1);
							newrelo($2.typ, RELO1);
							emit1($2.val);
						} else {
							if ($1 != 0xad) emit2(0x72);	/* not for call/jp */
							emit1($1 - 0x20 + 0x40);
							newrelo($2.typ, RELO2);
							emit2($2.val);
						}
					}
	| RMW '(' optoff reg16 ')'
					{
						if ($4 == Y) emit1(0x90);
						int opt = (($3.typ & S_SCTMASK) == DOTSCT) || (($3.typ & S_SCTMASK) == S_ABS);
						if (small($3.val == 0 && opt && PASS_RELO, 1)) {
							emit1($1+0x40);
						} else if (small(opt && PASS_RELO, fitb($3.val) ? 1 : 2)) {
							emit1($1+0x30);
							newrelo($3.typ, RELO1);
							emit1($3.val);
						} else {
							if ($4 != Y) emit2(0x72);
							emit1($1+0x30);
							newrelo($3.typ, RELO2);
							emit2($3.val);
						}
					}

	// irregular addressing modes
	| RMW '(' expr ',' SP ')'
					{
						stm8();
						/* XXXGJM: not for call/jp/neg  */
						emit1($1 - 0x30);
						emit1($3.val);
					}
	| RMW indirect
					{
						stm8();
						int opt = (($2.typ & S_SCTMASK) == DOTSCT) || (($2.typ & S_SCTMASK) == S_ABS);
						if (small(opt && PASS_RELO, fitb($2.val) ? 1 : 2)) {
							emit1($1+0x30);
							newrelo($2.typ, RELO1);
							emit1($2.val);
						} else {
							emit1(0x72);
							emit1($1+0x30);
							newrelo($2.typ, RELO2);
							emit2($2.val);
						}
					}
	| RMW '(' indirect ',' reg16 ')'
					{
						stm8();
						int opt = (($3.typ & S_SCTMASK) == DOTSCT) || (($3.typ & S_SCTMASK) == S_ABS);
						if (small(opt && PASS_RELO, fitb($3.val) ? 1 : 2)) {
							if ($5 == Y)
								emit1(0x91);
							else
								emit1(0x92);
							emit1($1+0x40);
							newrelo($3.typ, RELO1);
							emit1($3.val);
						} else {
							if ($5 == Y) fatal("bad addressing with Y");
							emit1(0x72);
							emit1($1+0x40);
							newrelo($3.typ, RELO2);
							emit2($3.val);
						}
					}

	// irregular addressing modes (LD)
	| RM XH ',' A			{ if ($1 != 0xa6) serror("bad operands"); emit1(0x95); }
	| RM YH ',' A			{ if ($1 != 0xa6) serror("bad operands"); emit2(0x9095); }
	| RM XL ',' A			{ if ($1 != 0xa6) serror("bad operands"); emit1(0x97); }
	| RM YL ',' A			{ if ($1 != 0xa6) serror("bad operands"); emit2(0x9097); }

	| RM A ',' XH 			{ if ($1 != 0xa6) serror("bad operands"); emit1(0x9E); }
	| RM A ',' YH 			{ if ($1 != 0xa6) serror("bad operands"); emit2(0x909E); }
	| RM A ',' XL 			{ if ($1 != 0xa6) serror("bad operands"); emit1(0x9F); }
	| RM A ',' YL 			{ if ($1 != 0xa6) serror("bad operands"); emit2(0x909F); }

	// sub cmp sbc cpx and bit lda sta eor adc ora add jmp jsr ldx stx, cpl, neg
	// regular addressing modes
	| RM A ',' immediate		{
						switch($1) {
							case 0xa7:
							case 0xac:
							case 0xad:
							case 0xaf:
								serror("mode error");
							default:
								emit1($1);
						}
						newrelo($4.typ, RELO1);
						emit1($4.val);
					}
	| RM A ',' direct		{
						if (small(pass == PASS_2 && ($4.typ & S_SCTMASK) == DOTSCT && fitb($4.val),1)) {
							emit1($1+0x10);
							newrelo($4.typ, RELO1);
							emit1($4.val);
						} else {
							emit1($1+0x20);
							newrelo($4.typ, RELO2|RELBR);
							emit2($4.val);
						}
					}
	| RM A ',' '(' optoff reg16 ')'
					{
						if ($6 == Y) emit1(0x90); 
						if (small(pass == PASS_2 && ($5.typ & S_SCTMASK) == DOTSCT && fitb($5.val),1)) {
							if (small(pass == PASS_2 && ($5.typ & S_SCTMASK) == DOTSCT && $5.val == 0,1)) {
								emit1($1+0x50);
							} else {
								emit1($1+0x40);
								newrelo($5.typ, RELO1);
								emit1($5.val);
							}
						} else {
							small(0,1);  /* dummy */
							emit1($1+0x30);
							newrelo($5.typ, RELO2|RELBR);
							emit2($5.val);
						}
					}

	| PUSH A			{ stm8(); emit1(0x88); }
	| PUSH CC			{ stm8(); emit1(0x8A); }
	| PUSH immediate		{ emit1(0x4B); emit1($2.val); }
	| PUSH direct			{ emit1(0x3B); emit2($2.val); }
	| POP A				{ stm8(); emit1(0x84); }
	| POP CC			{ stm8(); emit1(0x86); }
	| POP direct			{ emit1(0x32); emit2($2.val); }

	// clrw, cplw, decw, incw, negw, pushw, popw, rlcw, rrcw, sllw, srlw, swapw, tnzw
	| OPW reg16			{ if ($2 == Y) emit1(0x90); emit1($1); }
	;

reg16
	: X		{ $$ = $1; }
	| Y		{ $$ = $1; }
	;

optw
	: /* empty */
	| WIDE
	;

optoff
	: /* empty */	{ $$.typ = S_ABS; $$.val = 0; }
	| expr ','	{ $$ = $1; }
	;

immediate
	: '#' expr	{ $$ = $2; }
	;

direct
	: expr		{ $$ = $1; }
	;

indirect
	: '[' expr optw ']'		{ $$ = $2; }
	;
