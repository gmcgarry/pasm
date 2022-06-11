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

operation
	: optlabel instr
	| optlabel pseudoop
	;

optlabel
	: /* empty */
	| IDENT				{ newident($1, DOTSCT); newlabel($1); }
	;

pseudoop
	: PSEUDOOP_ZERO absexp		{ int i; for (i = 0; i < $2; i++) emit1(0); }
	| PSEUDOOP_ASCII STRING		{ emitstr($1); }
	| PSEUDOOP_DATA datalist
	;

instr
	: SETDP expr		{ dpvalue = $2.val; }
	| NOARG			{ emit1or2($1); }
	| PUSHB_NOARG		{ emit2(0x3404); emit2($1); }
	| NOARG_TSTA		{ emit2($1); emit1(0x4d); }
	| BRANCH expr		{ branch($1,$2); }
	| LBRNCH expr		{
					emit1(0x10); emit1($1);
					$2.val -= (DOTVAL+2);
#ifdef RELOCATION
					if (rflag != 0 && PASS_RELO)
						newrelo($2.typ, RELPC|RELO2|RELBR);
#endif
					emit2($2.val);
				}
	| SBRNCH expr		{
					emit1($1);
					$2.val -= (DOTVAL+2);
#ifdef RELOCATION
					if (rflag != 0 && PASS_RELO)
						newrelo($2.typ, RELPC|RELO2|RELBR);
#endif
					emit2($2.val);
				}
	|IMMED '#' expr		{
					emit1($1);
#ifdef RELOCATION
					if (rflag != 0 && PASS_RELO)
						newrelo($3.typ, RELO1);
#endif
					emit1($3.val);
				}
	| XOP '#' expr		{
					emit1or2($1 - 0x20);
					switch ($1 & 0x0F) {
					case 0x03:
					case 0x0C:
					case 0x0E:
#ifdef RELOCATION
						if (rflag != 0 && PASS_RELO)
							newrelo($3.typ, RELO2|RELBR);
#endif
						emit2($3.val);
						break;
					default:
#ifdef RELOCATION
						if (rflag != 0 && PASS_RELO)
							newrelo($3.typ, RELO1);
#endif
						emit1($3.val);
						break;
					}
				}
	| XOP '<' expr		{
					if (0 <= $1 && $1 < 0x80)
						emit1(($1-0x10) & 0x3F);
					else
						emit1or2($1 - 0x10);
#ifdef RELOCATION
					if (rflag != 0 && PASS_RELO)
						newrelo($3.typ, RELO1);
#endif
					emit1($3.val);
				}
	| XOP '>' expr		{
					emit1or2($1 + 0x10);
#ifdef RELOCATION
					if (rflag != 0 && PASS_RELO)
						newrelo($3.typ, RELO2|RELBR);
#endif
					emit2($3.val);
				}
	| STACK reglist		{ emit1($1); emit1($2); }
	| TWOREG REG ',' REG	{ emit1($1); emit1($2 << 4 | $4); }
	| XOP REG		{
					switch ($2) {
					case A:	emit1($1 - 0x20);
						break;
					case B:	emit1($1 - 0x10);
						break;
					default:serror("register error");
					}
				}
	| XOP expr ',' REG	{ emit1or2($1); offset($4,$2,0); }
	| XOP lbrac expr ',' REG rbrac { emit1or2($1); offset($5,$3,0x10); }
	| XOP lbrac expr rbrac 	{
					emit1or2($1);
					emit1(0x9F);
#ifdef RELOCATION
					if (rflag != 0 && PASS_RELO)
						newrelo($3.typ, RELO2|RELBR);
#endif
					emit2($3.val);
				}
	| XOP xmode		{ emit1or2($1); emit1($2); }
	| XOP lbrac xmode rbrac	{
					if (($3 & 0x8D) == 0x80)
						serror("invalid index mode");
					emit1or2($1);
					emit1($3 + 0x10);
				}
	| XOP expr		{
					int is_abs = ($2.typ & S_SCTMASK & ~S_VAR) == S_ABS;
					int is_local = ($2.typ & S_SCTMASK) == DOTSCT;
					if ((is_abs || is_local) && ((unsigned)$2.val >> 8) == dpvalue) {
						if (0 <= $1 && $1 < 0x80)
							emit1(($1-0x20) & 0x3F);
						else
							emit1or2($1 - 0x10);
						emit1($2.val);
					} else {
						emit1or2($1 + 0x10);
#ifdef RELOCATION
						if (rflag != 0 && PASS_RELO)
							newrelo($2.typ, RELO2|RELBR);
#endif
						emit2($2.val);
					}
				}
	;

reglist
	: ALL
	| REG			{ if (($$ = regbit[$1]) < 0) serror("register error");}
	| reglist ',' REG	{
					int i;
					if ((i = regbit[$3]) < 0 || ($1 & i) != 0)
						serror("register error");
					$$ = $1 | i;
				}
	;

xyus
	:	REG		{ if (($$ = regno($1)) < 0) serror("register error");}
	;

xmode
	: ',' xyus '+' '+'	{ $$ = 0x81 + $2; }
	| ',' xyus '+'		{ $$ = 0x80 + $2; }
	| ',' xyus		{ $$ = 0x84 + $2; }
	| ',' '-' '-' xyus	{ $$ = 0x83 + $4; }
	| ',' '-' xyus		{ $$ = 0x82 + $3; }
	| REG ',' xyus		{
					switch($1) {
					case A:	$$ = 0x86 + $3; break;
					case B: $$ = 0x85 + $3; break;
					case D:	$$ = 0x8B + $3; break;
					default: serror("register error");
					}
				}
	;

lbrac
	: '['
	| '('
	;

rbrac
	: ']'
	| ')'
