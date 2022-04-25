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

#define fitb(x)		(((x) & ~((int)0xFF)) == 0)

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
	: NOARG					{ emit1($1); }
	| BRANCH expr				{ branch($1,$2); }
	| XOP '#' expr				{
							emit1($1 - 0x20);
							switch ($1 & 0x0F) {
							case 0x03:
							case 0x0C:
							case 0x0E:
#ifdef RELOCATION
								newrelo($3.typ, RELBR | RELO2);
#endif
								emit2($3.val);
								break;
							default:
#ifdef RELOCATION
								newrelo($3.typ, RELO1);
#endif
								emit1($3.val);
							}
						}
	| XOP '<' expr				{
							emit1($1 - 0x10);
#ifdef RELOCATION
							newrelo($3.typ, RELO1);
#endif
							emit1($3.val);
						}
	| memref expr				{
							int opt = ($1 & 0xF0) != 0x60;
							if (opt && small(fitb($2.val),1)) {
								emit1($1 - 0x10);
#ifdef RELOCATION
								newrelo($2.typ, RELO1);
#endif
								emit1($2.val);
							} else {
								emit1($1 + 0x10);
#ifdef RELOCATION
								newrelo($2.typ, RELO2);
#endif
								emit2($2.val);
							}
						}
	| memref optexpr ',' X			{
							emit1($1);
#ifdef RELOCATION
							newrelo($2.typ, RELO1);
#endif
							emit1($2.val);
						}
	;

memref	: AOP
	| XOP
	;

optexpr	: /* empty */				{ $$.typ = S_ABS; $$.val = 0; }
	| expr					{ $$ = $1; }
	;
