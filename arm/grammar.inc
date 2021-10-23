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

#define thumbonly()	do { if (mode != MODE_THUMB) serror("invalid thumb instruction in arm mode"); } while (0)
#define armonly()	do { if (mode != MODE_ARM) serror("invalid arm instruction in thumb mode"); } while (0)

operation
	: PSEUDOOP_ARCH IDENT					{ setarch($2->i_name); }
	| PSEUDOOP_CPU IDENT 					{ setcpu($2->i_name); }
	| PSEUDOOP_FPU IDENT					{ setfpu($2->i_name); }
	| PSEUDOOP_EABIATTR NUMBER8 ',' NUMBER8			{ warning("ignoring .eabi directive"); }
	| PSEUDOOP_MODE						{ setmode($1); }
	| PSEUDOOP_CODE NUMBER8					{ warning("ignoring .code directive"); }
	| PSEUDOOP_SYNTAX IDENT					{ warning("ignoring .syntax directive"); }
	| PSEUDOOP_THUMBFUNC					{ warning("ignoring .thumb_func directive"); }
#ifdef notyet
	| PSEUDOOP_FUNC						{ warning("ignoring .fnstart/.fnend directive"); }
	| PSEUDOOP_POOL						{ warning("ignoring .pool directive"); }
	| PSEUDOOP_CANTUNWIND					{ warning("ignoring .cantunwind directive"); }
#endif
	| BRANCH optlink optexch expr				{ branch($1, $2, $4.val|$3); }
	| DATA1 optcond opts optp REG ',' REG ',' operand	{ data($1,$2|$3|$4|$5<<12|$7<<16,$9.val,$9.typ); }
#ifdef COMPAT_GAS /* XXXGJM probably thumb */
	| DATA1 optcond opts optp REG ',' operand		{ data($1,$2|$3|$4|$5<<12|$5<<16,$7.val,$7.typ); }
#endif
	| DATA2 optcond opts optp REG ',' operand		{ data($1,$2|$3|$4|$5<<12,$7.val,$7.typ); }
	| DATA3 optcond opts optp REG ',' operand		{ data($1,$2|$3|$4|$5<<16,$7.val,$7.typ); }
	| SDT optcond optb optt REG ',' address			{ strldr($1,$2|$3|$4|$5<<12,$7); }
#if 0
	/* LDRD/STRD */
	| SDT optcond optb optt REG ',' REG ',' address		{ if ($5 != $7+1) serror("bad registers"); strldr($1,$2|$3|$4|$5<<12,$9); }
#endif
	| BDT optcond REG optexc ',' reglist optpsr		{ armonly(); emit4($1|$2|$3<<16|$4|$6|$7); }
	| SWI optcond expr					{ armonly(); emit4($1|$2|$3.val); }
	| ADR optcond REG ',' expr				{ calcadr($2,$3,$5.val,$5.typ); }
	| MUL optcond REG ',' REG ',' REG			{ armonly(); emit4($1|$2|$3<<16|$5|$7<<8); }
	| MLA optcond REG ',' REG ',' REG ',' REG		{ armonly(); emit4($1|$2|$3<<16|$5|$7<<8|$9<<12); }
	/* thumb */
	| STACK loreglist					{ thumbonly(); emit2($1|$2); }
	;

optlink	: 			{ $$ = 0; }
	| LINK			{ $$ = $1; }
	;

optcond	: 			{ $$ = 0xE0000000; }
	| COND			{ $$ = $1; }
	;

/* thumb */
optexch	:			{ $$ = 0; }
	| EXCHANGE		{ $$ = $1; }
	;

opts	: 			{ $$ = 0; }
	| SET			{ $$ = $1; if (mode == MODE_THUMB) serror("S postfix not supported for thumb"); }
	;

optt	: 			{ $$ = 0; }
	| TRANS			{ $$ = $1; }
	;

optp	: 			{ $$ = 0; }
	| PEE			{ $$ = $1; }
	;

optb	: 			{ $$ = 0; }
	| BYTE			{ $$ = $1; }
	| HALF			{ $$ = $1; }
	;

optexc	: 			{ $$ = 0; }
	| '!'			{ $$ = 0x00200000; }
	;

optpsr	: 			{ $$ = 0; }
	| '^'			{ $$ = 0x00400000; }
	;

operand	: REG optshift		{ $$.val = $1|$2; $$.typ = S_REG; }
	| '#' expr		{ $$ = $2; }
	;

optshift: ',' SHIFT shftcnt	{ $$ = $2|$3; }
	| ',' RRX		{ $$ = $2; }
	|			{ $$ = 0; }
	;

aoptshift: ',' SHIFT '#' expr	{ $$ = $2|calcshft($4.val, $4.typ, $<y_word>0); }
	| ',' RRX		{ $$ = $2; }
	|			{ $$ = 0; }
	;

shftcnt	: '#' expr			{ $$ = calcshft($2.val, $2.typ, $<y_word>0); }
	| REG				{ $$ = $1<<8|0x10; }
	;

address	: expr					{ success = 0; $$ = $1.val; }
#ifdef notyet
	| '=' expr				{ success = 0; $$ = $2.val; }
#endif
	| '[' REG ']'				{ success = 1; $$ = 0x01000000|$2<<16; }
	| '[' REG ',' offset ']' optexc		{ success = 1; $$ = $2<<16|$4|$6|0x01000000; }
	| '[' REG ']' ',' offset		{ success = 1; $$ = $2<<16|$5; }
	;

offset	: '#' expr			{ $$ = calcoffset($2.val); }
	| optsign REG aoptshift		{ $$ = 0x02000000|$1|$2|$3; }
	;
	
optsign	:				{ $$ = 0x00800000; }
	| '+'				{ $$ = 0x00800000; }
	| '-'				{ $$ = 0x0; }
	;

reglist	: '{' rlist '}'			{ $$ = $2; }
	;

rlist	: REG				{ $$ = 1<<$1; }
	| rlist ',' REG			{ $$ = $1|1<<$3; }
	| REG '-' REG			{ for ($$ = 0; $1 <= $3; $1++) $$ |= (1<<$1); }
	;

#define thumbreg(x)			do { if (x > 7 && x < 14) serror("invalid register"); } while(0)

loreglist
	: REG				{ thumbreg($1); if ($1 == 14 || $1 == 15) $1 = 8; $$ = (1<<$1); }
	| '{' lorlist '}'		{ $$ = $2; }
	;

lorlist	: REG				{ thumbreg($1); if ($1 == 14 || $1 == 15) $1 = 8; $$ = 1<<$1; }
	| rlist ',' REG			{ thumbreg($1); if ($3 == 14 || $3 == 15) $3 = 8; $$ = $1|1<<$3; }
	| REG '-' REG			{ for ($$ = 0; $1 <= $3; $1++) { thumbreg($1); $$ |= (1<<$1); } }
	;
