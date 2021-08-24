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

#define REX(W,R,X,B)	emit1(0x40 | (W?8:0) | (R&8?4:0) | (X&8?2:0) | (B&8?1:0))

operation
	: PSEUDOOP_USE16		{ use32 = 0; address_long = 0; operand_long = 0; }
	| PSEUDOOP_USE32		{ use32 = 1; address_long = 1; operand_long = 1; }
	| PSEUDOOP_USE64		{ use32 = 2; address_long = 2; operand_long = 2; }
	| PSEUDOOP_CPU IDENT		{ }
	| PSEUDOOP_CPU NUMBER8		{ }
	| prefix oper			{ address_long = use32; operand_long = use32; }
	| prefix1			/* to allow for only prefixes on a line */
	;

prefix	: /* empty */
	| prefix1
	;

prefix1	: prefix PREFIX			{ emit1($2); }
	;

oper	: NOOP_1			{ emit1($1); }
	| NOOP_2			{ emit2($1); }
	| JOP expr			{ branch($1,$2); }
	| JOP2 expr			{ ebranch($1,$2); }
	| PUSHOP ea_1			{ pushop($1); }
	| IOOP const 			{ emit1($1); fit(ufitb($2)); emit1((int)$2); }
	| IOOP R32			{ if ($2!=2) serror("register error"); emit1($1+010); }
	| BITTEST ea_ea			{ bittestop($1); }
	| ADDOP ea_ea			{ rex(); addop($1); }
	| ROLOP ea_ea			{ rex(); rolop($1); } 
	| INCOP ea_1			{ rex(); incop($1); }
	| NOTOP ea_1			{ rex(); regsize($1); emit1(0366|($1&1)); ea_1($1&070); }
	| CALLOP ea_1 			{ callop($1&0xFFFF); }
	| CALLOP '*' ea_1		{ emit1(0xFF); ea_2($1&0xFF); }
	| CALFOP expr ',' expr		{ emit1($1>>8); adsize_exp($4, 0); newrelo($2.typ, RELO2); emit2((int)($2.val)); }
	| CALFOP '*' mem		{ emit1(0xFF); ea_2($1&0xFF); }
	| ENTER const ',' const		{ fit(fitw($2)); fit(fitb($4)); emit1($1); emit2((int)$2); emit1((int)$4); }
	| LEAOP mem ',' XREG		{ rex(); emit1($1); ea_2($4<<3); }
	| LEAOP2 mem ',' XREG		{ rex(); emit1(0xF); emit1($1); ea_2($4<<3); }
	| ARPLOP R32 ',' ea_2 		{ emit1($1); ea_2($2<<3); }
	| LSHFT	ea_1 ',' XREG ',' ea_2	{ extshft($1, $4); }
	| LSHFT	ea_1 ',' ea_2		{ extshft($1, 0 /* XXXGJM */); }
	| EXTEND ea_2 ',' XREG		{ emit1(0xF); emit1($1); ea_2($4<<3); }
	| EXTOP ea_2 ',' XREG 		{ emit1(0xF); emit1($1); ea_2($4<<3); }
	| EXTOP1 ea_1			{ emit1(0xF); emit1($1&07); ea_1($1&070); }
	| IMULB	ea_1			{ regsize(0); emit1(0366); ea_1($1&070); }
	| IMUL ea_2			{ reg_1 = IS_R32 | (address_long ? 0 : 0310); imul(0); }
	| IMUL ea_2 ',' XREG		{ reg_1 = $4 | IS_R32 | (address_long ? 0 : 0310); imul($4|0x10); }
	| IMUL ea_ea ',' XREG		{ imul($4|0x10); }
	| INT const  			{ if ($2 == 3) emit1(0314); else { fit(ufitb($2)); emit1(0315); emit1((int)$2); } }
	| RET				{ emit1($1); }
	| RET expr			{ emit1($1-1); newrelo($2.typ, RELO2); emit2((int)($2.val)); }
	| SETCC ea_2			{ if (reg_2 & (IS_R32|IS_RSEG)) { serror("register error"); } emit1(0xF); emit1($1|0x90); ea_2(0); }
	| XCHG ea_ea			{ rex(); xchg($1); }
	| TEST ea_ea			{ rex(); test($1); }
	| MOV ea_ea			{ rex(); mov($1); }
	| MOV ea_1 ',' RSYSCR		{ if ($1 != 1 || !(reg_1 & IS_R32)) serror("syntax error"); emit1(0xF); emit1(0x20); emit1(0300|($4<<3)|(reg_1&07)); }
	| MOV ea_1 ',' RSYSDR		{ if ($1 != 1 || !(reg_1 & IS_R32)) serror("syntax error"); emit1(0xF); emit1(0x21); emit1(0300|($4<<3)|(reg_1&07)); }
	| MOV ea_1 ',' RSYSTR		{ if ($1 != 1 || !(reg_1 & IS_R32)) serror("syntax error"); emit1(0xF); emit1(0x24); emit1(0300|($4<<3)|(reg_1&07)); }
	| MOV RSYSCR ',' XREG		{ if ($1 != 1) serror("syntax error"); emit1(0xF); emit1(0x22); emit1(0300|($2<<3)|$4); }
	| MOV RSYSDR ',' XREG		{ if ($1 != 1) serror("syntax error"); emit1(0xF); emit1(0x23); emit1(0300|($2<<3)|$4); }
	| MOV RSYSTR ',' XREG		{ if ($1 != 1) serror("syntax error"); emit1(0xF); emit1(0x26); emit1(0300|($2<<3)|$4); }
/* Intel 80[23]87 coprocessor instructions */
	| FNOOP				{ emit1($1); emit1($1>>8); }
	| FMEM mem			{ emit1($1); ea_2(($1>>8)&070); }
	| FMEM_AX mem			{ emit1($1); ea_2(($1>>8)&070); }
	| FMEM_AX R32			{ if ($2 != 0) { serror("illegal register"); } emit1(FESC|7); emit1(7<<5); }
	| FST_I st_i			{ emit1($1); emit1(($1>>8)|$2); }
	| FST_I ST			{ emit1($1); emit1($1>>8); }
	| FST_ST ST ',' st_i		{ emit1($1|4); emit1(($1>>8)|$4); }
	| FST_ST2 ST ',' st_i		{ emit1($1|4); emit1(($1>>8)|$4); }
	| FST_ST st_i ',' ST		{ emit1($1); emit1((($1>>8)|$2)); }
	| FST_ST2 st_i ',' ST		{ emit1($1); emit1((($1>>8)|$2)^010); }
	| FST_I 			{ emit1($1|4); emit1(($1>>8)|1); }
	| FST_ST 			{ emit1($1|4); emit1(($1>>8)|1); } 
	| FST_ST2			{ emit1($1|4); emit1(($1>>8)|1); }
/* 486 instructions */
	| BSWAP R32			{ emit1(0xF); emit1($1|$2); }
	| BSWAP R64			{ REX(1,0,0,$2); emit1(0xF); emit1($1|$2); }
	| EXTOPBW ea_2 ',' reg		{ regsize($1); emit1(0xF); emit1($1); ea_2($4<<3); }
	;

st_i	: ST '(' absexp ')'		{ if (!fit3($3)) { serror("illegal index in FP stack"); } $$ = $3; }
	;

mem	: expr				{ reg_2 = IS_EXPR | (address_long ? 05 : 06); mod_2 = 0; rm_2 = 05; exp_2 = $1; RELOMOVE(rel_2, relonami); }
	| expr PLT			{ reg_2 = IS_EXPR | (address_long ? 05 : 06); mod_2 = 0; rm_2 = 05; exp_2 = $1; RELOMOVE(rel_2, relonami); }
	| bases				{ exp_2.val = 0; exp_2.typ = S_ABS; indexed(); }
	| expr bases			{ exp_2 = $1; indexed(); RELOMOVE(rel_2, relonami); }
	| expr '(' RIP ')'		{ if (use32 != 2) serror("bad register"); reg_2 = 5; mod_2 = 0; rm_2 = 05; exp_2.typ = $1.typ; exp_2.val = $1.val - DOTVAL; RELOMOVE(rel_2, relonami); }
	;

bases	: '(' XREG ')'			{ reg_2 = (address_long ? $2 : sr_m[$2]); sib_2 = 0; rm_2 = 0; }
	| '(' XREG ',' XREG ',' scale ')' { reg_2 = (address_long ? $2 : dr_m[$2][$4]); rm_2 = 04; sib_2 |= regindex_ind[$2][$4]; }
	| '(' XREG ',' XREG ')'		{ reg_2 = (address_long ? $2 : dr_m[$2][$4]); rm_2 = 04; sib_2 = regindex_ind[$2][$4]; }
	| '(' ',' XREG ',' absexp ')'	{ if ($5 == 1) { reg_2 = $3; sib_2 = 0; rm_2 = 0; } else { rm_2 = 04; sib_2 = checkscale($5) | regindex_ind[05][$3]; reg_2 = 015; } }
	;

XREG	: R16				{ $$ = $1; }
	| R32				{ $$ = $1; }
	| R64				{ $$ = $1; }
	;

scale	: /* empty */			{ sib_2 = 0; }
	| absexp			{ sib_2 = checkscale($1); }
	;

const	: '$' absexp			{ $$ = $2; }
	;

ea_2	: mem
	| R8				{ reg_2 = ($1 | IS_R8) | (address_long ? 0 : 0xc0); rm_2 = 0; }
	| R16 				{ reg_2 = ($1 | IS_R16 | IS_R32) | (address_long ? 0 : 0xc8); rm_2 = 0; }
	| R32 				{ if (use32 == 0) serror("bad register"); reg_2 = ($1 | IS_R32) | (address_long ? 0 : 0xc8); rm_2 = 0; }
	| R32X				{ if (use32 != 2) serror("bad register"); reg_2 = ($1 | IS_R32) | (address_long ? 0 : 0xc8); rm_2 = 0; }
	| R64 				{ if (use32 != 2) serror("bad register"); reg_2 = ($1 | IS_R32 | IS_R64); rm_2 = 0; }
	| RSEG				{ reg_2 = ($1 | IS_RSEG) | (address_long ? 0 : 0x10); rm_2 = 0; }
	| '$' expr 			{ reg_2 = IS_EXPR | (address_long ? 0 : 0x20); exp_2 = $2; rm_2 = 0; RELOMOVE(rel_2, relonami); }
	| RSEG ':' expr			{ static const int prefix[] = { 0x26, 0x2e, 0x36, 0x3e, 0x64, 0x65 }; emit1(prefix[$1]); reg_2 = (address_long ? 5 : 6); mod_2 = 0; rm_2 = 5; exp_2 = $3; RELOMOVE(rel_2, relonami); }
	;

reg	: R8				{ reg_1 = ($1 | IS_R8) | (address_long ? 0 : 0xc0); rm_1 = 0; $$ = $1; }
	| R16				{ reg_1 = ($1 | IS_R16 | IS_R32) | (address_long ? 0 : 0xc8); rm_1 = 0; $$ = $1; }
	| R32				{ if (use32 == 0) serror("bad register"); reg_1 = ($1 | IS_R32) | (address_long ? 0 : 0xc8); rm_1 = 0; $$ = $1; }
	| R32X				{ if (use32 != 2) serror("bad register"); reg_1 = ($1 | IS_R32) | (address_long ? 0 : 0xc8); rm_1 = 0; $$ = $1; }
	| R64				{ if (use32 != 2) serror("bad register"); reg_1 = ($1 | IS_R32 | IS_R64) | (address_long ? 0 : 0xc8); rm_1 = 0; $$ = $1; }
	;

ea_1	: ea_2				{ op_1 = op_2; RELOMOVE(rel_1, rel_2); }
	;

ea_ea	: ea_1 ',' ea_2			{ reverse(); /* swapping operand order; intel to MIT format */ }
	;
