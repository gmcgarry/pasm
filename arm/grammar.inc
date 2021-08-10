
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

operation: BRANCH optlink expr					{branch($1, $2, $3.val);}
	| DATA1 optcond opts optp REG ',' REG ',' operand	{data($1,$2|$3|$4|$5<<12|$7<<16,$9.val,$9.typ);}
	| DATA2 optcond opts optp REG ',' operand		{data($1,$2|$3|$4|$5<<12,$7.val,$7.typ);}
	| DATA3 optcond opts optp REG ',' operand		{data($1,$2|$3|$4|$5<<16,$7.val,$7.typ);}
	| SDT optcond optb optt REG ',' address			{strldr($1,$2|$3|$4|$5<<12,$7);}
	| BDT optcond REG optexc ',' reglist optpsr		{emit4($1|$2|$3<<16|$4|$6|$7);}
	| SWI optcond expr					{emit4($1|$2|$3.val);}
	| ADR optcond REG ',' expr				{calcadr($2,$3,$5.val,$5.typ);}
	| MUL optcond REG ',' REG ',' REG			{emit4($1|$2|$3<<16|$5|$7<<8);}
	| MLA optcond REG ',' REG ',' REG ',' REG		{emit4($1|$2|$3<<16|$5|$7<<8|$9<<12);}
	;

optlink	: 			{$$=0;}
	| LINK			{$$=$1;}
	;

optcond	: 			{$$=0xE0000000;}
	| COND			{$$=$1;}
	;

opts	: 			{$$=0;}
	| SET			{$$=$1;}
	;

optt	: 			{$$=0;}
	| TRANS			{$$=$1;}
	;

optp	: 			{$$=0;}
	| PEE			{$$=$1;}
	;

optb	: 			{$$=0;}
	| BYTE			{$$=$1;}
	;

optexc	: 			{$$=0;}
	| '!'			{$$=0x00200000;}
	;

optpsr	: 			{$$=0;}
	| '^'			{$$=0x00400000;}
	;

operand	: REG optshift		{$$.val = $1|$2; $$.typ = S_REG;}
	| '#'expr		{$$ = $2;}
	;

optshift: ',' SHIFT shftcnt	{$$ = $2|$3;}
	| ',' RRX		{$$ = $2;}
	|			{$$ = 0;}
	;

aoptshift: ',' SHIFT '#' expr	{$$ = $2|calcshft($4.val, $4.typ, $<y_word>0);}
	| ',' RRX		{$$ = $2;}
	|			{$$ = 0;}
	;

shftcnt	: '#' expr			{$$ = calcshft($2.val, $2.typ, $<y_word>0);}
	| REG				{$$ = $1<<8|0x10;}
	;

address	: expr					{success = 0; $$ = $1.val;}
	| '[' REG ']'				{success = 1; $$ = 0x01000000|$2<<16;}
	| '[' REG ',' offset ']' optexc		{success = 1; $$ = $2<<16|$4|$6|0x01000000;}
	| '[' REG ']' ',' offset		{success = 1; $$ = $2<<16|$5;}
	;

offset	: '#' expr			{$$ = calcoffset($2.val);}
	| optsign REG aoptshift		{$$ = 0x02000000|$1|$2|$3;}
	;
	
optsign	:				{$$ = 0x00800000;}
	| '+'				{$$ = 0x00800000;}
	| '-'				{$$ = 0x0;}
	;

reglist	: '{' rlist '}'			{$$ = $2;}
	;

rlist	: REG				{$$ = 1<<$1;}
	| rlist ',' REG			{$$ = $1|1<<$3;}
	| REG '-' REG			{ for ($$ = 0; $1 <= $3; $1++) $$ |= (1<<$1); }
	;
