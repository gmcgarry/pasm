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

expr8
	: expr			{ fit(fitb($1.val)); }
	;

bitexp
	: absexp		{ fit((unsigned) $1 <= 7); $$ = $1 & 07; }
	;

operation
	: NOARG			{ emit1($1); }
	| BRANCH expr		{ expr_t expr = {0,0}; branch($1,$2,expr); }
	| BBRANCH expr8 ',' bitexp ',' expr {  branch($1+($4 << 1), $6, $2); }
	| BIT expr8 ',' bitexp	{ emit2($1+($4 << 1)); newrelo($2.typ, RELO1); emit1($2.val); }
	| RMR '<' expr8
	| RMR expr8		{ emit1($1); newrelo($2.typ, RELO1); emit1($2.val); }
	| RMR expr8 ',' ireg	{
				if (small($2.val == 0 && ($2.typ & S_SCTMASK) == DOTSCT && pass == PASS_2, 1)) {
					emit1($1+0x40);
				} else {
					emit1($1+0x30);
					newrelo($2.typ, RELO1);
					emit1($2.val);
				}
				}
	| RMR ',' ireg		{ emit1($1+0x40); }
	| RM '#' expr8		{
				switch($1) {
					case 0xa7:
					case 0xac:
					case 0xad:
					case 0xaf:
						serror("mode error");
					default:
						emit1($1);
				}
				newrelo($3.typ, RELO1);
				emit1($3.val);
				}
	| RM '<' expr8		{ emit1($1+0x10); newrelo($3.typ, RELO1); emit1($3.val); }
	| RM '<' expr8 ',' ireg	{ emit1($1+0x40); newrelo($3.typ, RELO1); emit1($3.val); }
	| RM '>' expr		{ emit1($1+0x20); newrelo($3.typ, RELO2|RELBR); emit2($3.val); }
	| RM '>' expr ',' ireg	{ emit1($1+0x30); newrelo($3.typ, RELO2|RELBR); emit2($3.val); }
	| RM expr		{
				if (small(pass == PASS_2 && ($2.typ & S_SCTMASK) == DOTSCT && fitb($2.val),1)) {
					emit1($1+0x10);
					newrelo($2.typ, RELO1);
					emit1($2.val);
				} else {
					emit1($1+0x20);
					newrelo($2.typ, RELO2|RELBR);
					emit2($2.val);
				}
				}
	| RM expr ',' ireg	{
				if (small(pass == PASS_2 && ($2.typ & S_SCTMASK) == DOTSCT && fitb($2.val),1)) {
					if (small(pass == PASS_2 && ($2.typ & S_SCTMASK) == DOTSCT && $2.val == 0,1)) {
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
	| RM ',' ireg		{ emit1($1+0x50); }
	;


acc	: REG			{ if ($1 != A) serror("bad register"); }
	;

ireg	: REG			{ if ($1 != X || $1 != Y) serror("bad register");  if ($1 == Y) emit1(0x90); }
	;
