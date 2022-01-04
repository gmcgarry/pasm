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

#define fitb(x)		((((x) + 0x80) & ~((int)0xFF)) == 0)
#define fitw(x)		((((x) + 0x8000) & ~((int)0xFFFF)) == 0)

bitexp
	: absexp				{ fit((unsigned) $1 <= 7); $$ = $1 & 07; }
	;

operation
	: optlabel instr
	| optlabel pseudoop
	;

optlabel
	: /* empty */
	| IDENT					{ newident($1, DOTSCT); newlabel($1); }
	;

pseudoop
	: PSEUDOOP_ZERO absexp			{ int i; for (i = 0; i < $2; i++) emit1(0); }
	| PSEUDOOP_ASCII STRING			{ emitstr($1); }
	| PSEUDOOP_DATA datalist 
	| PSEUDOOP_ENDB IDENT			{ }
	| PSEUDOOP_BOOT				{ }
	;

instr
	: CTL					{ emit1($1); }
	| BRANCH expr				{ expr_t expr = {0,0}; branch($1,$2,expr); }
#ifdef MC6805
	| BBRANCH bitexp ',' expr ',' expr	{ fit(fitb($4.val)); branch($1+($2 << 1), $6, $4); }
	| BIT bitexp ',' expr			{ fit(fitb($4.val)); emit1($1+($2 << 1)); newrelo($4.typ, RELO1); emit1($4.val); }
#endif
#ifdef MC68HC08
	| CBRANCH expr ',' expr			{ emit1($1); emit1($2.val); emit1($4.val - DOTVAL); }
	| CBRANCH '#' expr ',' expr		{ emit1($1); emit1($3.val); emit1($5.val - DOTVAL); }
	| CBRANCH expr ',' X '+' ',' expr	{ emit1($1+0x30); emit1($2.val); emit1($7.val - DOTVAL); }
	| CBRANCH X '+' ',' expr		{ emit1($1+0x40); emit1($5.val - DOTVAL); }
	| CBRANCH expr ',' SP ',' expr		{ emit2(0x9e61); emit1($2.val); emit1($6.val - DOTVAL); }

	| DBNZ expr ',' expr			{ fit(fitb($2.val)); emit1($1); emit1($2.val); emit1($4.val - DOTVAL); }
	| DBNZ expr				{ emit1($1); emit1($2.val - DOTVAL); }
	| DBNZ expr ',' X ',' expr		{ fit(fitb($2.val)); emit1($1+0x30); emit1($2.val); emit1($6.val - DOTVAL); }
	| DBNZ X ',' expr			{ emit1($1+0x40); emit1($4.val - DOTVAL); }
	| DBNZ expr ',' SP ',' expr		{ emit2(0x9e6b); emit1($2.val); emit1($6.val - DOTVAL); }

	| MOV expr ',' expr			{ fit(fitb($2.val)); fit(fitb($4.val)); emit1(0x4e); emit1($2.val); emit1($4.val); }
	| MOV expr ',' X '+'			{ emit1(0x5e); emit1($2.val); }
	| MOV '#' expr ',' expr			{ emit1(0x6e); emit1($3.val); emit1($5.val); }
	| MOV X '+' ',' expr			{ emit1(0x6f); emit1($5.val); }
#endif
	| RMW expr				{ fit(fitb($2.val)); emit1($1); newrelo($2.typ, RELO1); emit1($2.val); }
	| RMW expr ',' X			{
							int opt = (($2.typ & S_SCTMASK) == DOTSCT) || (($2.typ & S_SCTMASK) == S_ABS);
							if (small($2.val == 0 && opt && PASS_RELO, 1)) {
								emit1($1+0x40);
							} else {
								emit1($1+0x30);
								newrelo($2.typ, RELO1);
								emit1($2.val);
							}
						}
	| RMW ',' X				{ emit1($1+0x40); }
#ifdef MC68HC08
	| RMW expr ',' SP			{ fit(fitb($2.val)); emit1(0x9e); emit1($1+0x30); }
#endif

	| RM '#' expr		{
					switch($1) {
						case 0xa7:
						case 0xad:
#ifdef MACH_6805
						case 0xac:
						case 0xaf:
#endif
							serror("mode error");
						default:
							emit2($1);
					}
#ifndef MACH_6805
					if ($1 == 0xac || $1 == 0xae || $1 == 0xaf) {
						fit(fitw($3.val));
						newrelo($3.typ, RELO2);
						emit2($3.val);
					} else
#endif
					{
						fit(fitb($3.val));
						newrelo($3.typ, RELO1);
						emit1($3.val);
					}
				}
	| RM expr		{
					int opt = (($2.typ & S_SCTMASK) == DOTSCT) || (($2.typ & S_SCTMASK) == S_ABS);
					if (small(PASS_RELO && opt && fitb($2.val), 1)) {
						emit1($1+0x10);
						newrelo($2.typ, RELO1);
						emit1($2.val);
					} else {
						emit1($1+0x20);
						newrelo($2.typ, RELO2|RELBR);
						emit2($2.val);
					}
				}
	| RM expr ',' X		{
					int opt = (($2.typ & S_SCTMASK) == DOTSCT) || (($2.typ & S_SCTMASK) == S_ABS);
					if (small(PASS_RELO && opt && fitb($2.val),1)) {
						if (small(PASS_RELO && opt && $2.val == 0,1)) {
							emit1($1+0x50);
						} else {
							emit1($1+0x40);
							newrelo($2.typ, RELO1);
							emit1($2.val);
						}
					} else {
						small(0,1);  /* dummy */
						emit1($1+0x30);
						newrelo($2.typ, RELO2|RELBR);
						emit2($2.val);
					}
				}
	| RM ',' X		{ emit1($1+0x50); }
#ifdef MC6805
	| CMOS			{
					switch($1) {
						case 0:
							opt_cmos = 1;
							break;
						case 0x8e:
						case 0x8f:
							if (!opt_cmos)
								serror("bad opcode");
							emit1($1);
					}
				}
#endif
	;
