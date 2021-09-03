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

#define COMPAT_C64

/*
 * Mostek 6500 parsing tables.
 */

expr: expr EXTENSION		{
			$$.val = ($1.val >> $2) & 0xFF;
#ifdef RELOCATION
			$$.typ = combine($1.typ, S_ABS, '&');
					    /* This will generate an 'invalid operator'      */
					    /* error if $1.typ is not absolute after pass 1. */
#else
			$$.typ = $1.typ;  /* Even if $1.typ is relocatable, it should be   */
					    /* absolute by the final pass.		   */
#endif /* RELOCATION */
				}
	;

operation: optlabel instr
	| PSEUDOOP_SCR STRING	{ machscr(); }
	;

/* for compatibility with asl assembler */
optlabel:	/* empty */
	| IDENT			{ newident($1, DOTSCT); newlabel($1); }

instr	:	/* empty */
	| NOPOP			{ emit1($1); }
	| BITOP expr		{ code($2,$1,$1+8); }
	| JMPOP expr		{ emit1($1); newrelo($2.typ, RELO2); emit2($2.val); }
	| JMPOP '(' expr ')'	{ emit1($1+0x20); newrelo($3.typ, RELO2); emit2($3.val); }
	| JSROP expr		{ emit1($1); newrelo($2.typ, RELO2); emit2($2.val); }
	| LDXOP '#' expr	{ emit1(0xA2); newrelo($3.typ, RELO1); emit1($3.val); }
#ifdef COMPAT_C64
	| LDXOP '#' '<' expr	{ emit1(0xA2); newrelo($4.typ, RELO1); emit1($4.val); }
	| LDXOP '#' '>' expr	{ emit1(0xA2); newrelo($4.typ, RELO1); emit1($4.val>>8); }
#endif
	| LDXOP expr		{ code($2,0xA6,0xAE); }
	| LDXOP expr ',' Y	{ code($2,0xB6,0xBE); }
	| LDYOP	'#' expr	{ emit1(0xA0); newrelo($3.typ, RELO1); emit1($3.val); }
#ifdef COMPAT_C64
	| LDYOP	'#' '<' expr	{ emit1(0xA0); newrelo($4.typ, RELO1); emit1($4.val); }
	| LDYOP	'#' '>' expr	{ emit1(0xA0); newrelo($4.typ, RELO1); emit1($4.val>>8); }
#endif
	| LDYOP	expr		{ code($2,0xA4,0xAC); }
	| LDYOP	expr ',' X	{ code($2,0xB4,0xBC); }
	| STXOP	expr		{ code($2,$1+0x06,$1+0x0E); }
	| STXOP	expr ',' Y	{ emit1($1+0x16); newrelo($2.typ, RELO1); emit1(lowb($2.val)); }
	| STYOP	expr		{ code($2,$1+0x04,$1+0x0C); }
	| STYOP	expr ',' X	{ emit1($1+0x14); newrelo($2.typ, RELO1); emit1(lowb($2.val)); }
#ifdef COMPAT_C64
	| addop '#' '<' expr	{ if ($1 == 0x80) serror("no store immediate"); emit1($1+0x09); emit1($4.val); }
	| addop '#' '>' expr	{ if ($1 == 0x80) serror("no store immediate"); emit1($1+0x09); emit1($4.val >> 8); }
#endif
	| addop	'#' expr	{
				if ($1==0x80)
					serror("no store immediate");
			  	emit1($1+0x09);
			  	newrelo($3.typ, RELO1);
			  	emit1($3.val);
				}
	| addop	expr		{ code($2,$1+0x05,$1+0x0D); }
	| addop	expr ',' X	{ code($2,$1+0x15,$1+0x1D); }
	| addop	expr ',' Y	{ emit1($1+0x19); newrelo($2.typ, RELO2); emit2($2.val); }
	| addop	'(' expr ',' X ')'	{ emit1($1+0x01); newrelo($3.typ, RELO1); emit1(lowb($3.val)); }
	| addop	'(' expr ')' ',' Y	{ emit1($1+0x11); newrelo($3.typ, RELO1); emit1(lowb($3.val)); }
	| ROLOP	/* Default is A. */	{ emit1($1+0x0A); }
	| ROLOP	A		{ emit1($1+0x0A); }
	| ROLOP	expr		{ code($2,$1+0x06,$1+0x0E); }
	| ROLOP	expr ',' X	{ code($2,$1+0x16,$1+0x1E); }
	| BRAOP	expr		{ branch($1,$2); }
	| CPXOP	'#' expr	{ emit1($1+0x00); newrelo($3.typ, RELO1); emit1($3.val); }
	| CPXOP	expr		{ code($2,$1+0x04,$1+0x0C); }
	| INCOP	expr		{ code($2,$1+0x06,$1+0x0E); }
	| INCOP	expr ',' X	{ code($2,$1+0x16,$1+0x1E); }
	;

addop: ADDOP
	| PSEU			{ emit1($1>>8); $$ = $1 & 0xFF; }
	;
