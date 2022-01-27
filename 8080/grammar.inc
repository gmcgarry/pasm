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
	: KILL REG		{ }
	| NOOPOP		{ emit1($1); }
	| D8OP expr		{
					emit1($1);
#ifdef RELOCATION
					newrelo($2.typ, RELO1);
#endif
					emit1($2.val);
				}
	| D16OP expr		{
					emit1($1);
#ifdef RELOCATION
					newrelo($2.typ, RELO2);
#endif
					emit2($2.val);
				}
	| R16OP r16		{ emit1($1 | ($2 << 3)); }
	| MOV r8 ',' r8		{
					if ($2 == M && $4 == M)
						serror("register error");
					emit1($1 | ($2 << 3) | $4);
				}
	| MVI r8 ',' expr	{
					emit1($1 | ($2 << 3));
#ifdef RELOCATION
					newrelo($4.typ, RELO1);
#endif
					emit1($4.val);
				}
	| LXI r16 ',' expr	{
					emit1($1 | ($2 << 3));
#ifdef RELOCATION
					newrelo($4.typ, RELO2);
#endif
					emit2($4.val);
				}
	| SRCOP r8		{ emit1($1 | $2); }
	| DSTOP r8		{ emit1($1 | ($2 << 3)); }
	| RST absexp		{
					fit(fit3($2));
					emit1($1 | (low3($2) << 3));
				}
	| STLDAX r16		{
					if ($2 != B && $2 != D)
						serror("register error");
					emit1($1 | (($2 & 02) << 3));
				}
	;

r16	: REG			{
					if ($1 & ~06)
						serror("register error");
					$$ = $1 & 06;
				}
	;

r8	: REG
				{
					if (($1 & ~07) != 0)
						serror("register error");
					$$ = $1 & 07;
				}
	;
