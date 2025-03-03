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

/*
 *  Motorola 68000/68010 syntax rules
 */

operation
	: { curr_instr = curr_token; }
		_operation
	| optlabel cdatalist
	;

optlabel
	: /* empty */
	| IDENT		{	newident($1, DOTSCT); newlabel($1); }
	;

cdatalist
	: cdata datalist
	| DEFZERO sizedef absexp
			{ int n = (1 << ($2 >> 6)); int i; for (i = 0; i < $3; i++) emitx(0x00,n); }
	| DEFBLOCK sizedef absexp ',' absexp
			{ int n = (1 << ($2 >> 6)); int i; for (i = 0; i < $3; i++) emitx($5,n); }
	;

cdata
	: DEFCONST SIZE	{	$$ = (1 << ($2 >> 6)); } 
	;

_operation
	: bcdx DREG ',' DREG
			{	emit2($1 | $2 | $4<<9); }
	| bcdx '-' '(' AREG ')' ',' '-' '(' AREG ')'
			{	emit2($1 | $4 | $9<<9 | 010); }
	| ADD sizedef ea_ea
			{	add($1, $2); }
	| AND sizenon ea_ea
			{	and($1, $2); }
	| SHIFT sizedef ea_ea
			{	shift_op($1, $2); }
	| BR expr
			{	branch($1, $2); }
	| DBR DREG ',' expr
			{	$4.val -= (DOTVAL+2);
				fit(fitw($4.val));
				emit2($1 | $2);
#ifdef RELOCATION
				newrelo($4.typ, RELPC|RELO2|RELBR|RELWR);
#endif
				emit2(loww($4.val));
			}
#ifdef COMPAT
	| BITOP sizedef ea_ea
			{	bitop($1); }
#else
	| BITOP ea_ea
			{	bitop($1); }
#endif
	| OP_EA_D sizedef ea ',' DREG		/* chk, divu, divs, mulu, muls */
			{	checksize($2, 2|4);
				if ($2 == SIZE_W) {
					emit2($1 | mrg_2 | $5<<9);
					ea_2($2, DTA);
				} else {
					extern int model;
					if ($1 == 040600 ||model < MODEL_68020)
						serror("illegal size");
					emit2($1 | mrg_2 | $5<<9);
					ea_2($2, DTA);
// 4c 00 10 01 : 001 001 100 : 0114
// 4c 00 24 01 : 
				}
			}

	| DIVMUL sizedef ea ',' DREG
			{	checksize($2, 2|4);
				if ($2 == SIZE_W) {
					emit2((0140300^($1<<8))|mrg_2|$5<<9);
					ea_2(SIZE_W, DTA);
				} else {  /* 32 bit dividend or product */
					extern int model;
					if ($1 == 040600 || model < MODEL_68020)
						serror("illegal size");
					emit2((046000 | ($1 & ~1)) | mrg_2);
					emit2(($1&1)<<11 | $5<<12 | $5);
					ea_2(SIZE_L, DTA);
				}
			}
	| DIVMUL sizedef ea ',' DREG ':' DREG
			{	/* 64 bit dividend or product */
				extern int model;
				if ($1 == 040600 || model < MODEL_68020)
					serror("illegal size");
				checksize($2, 4);
				emit2((046000 | ($1 & ~1)) | mrg_2);
				emit2(($1&1)<<11 | $7<<12 | $5 | 02000);
				ea_2(SIZE_L, DTA);
			}
	| DIVL sizedef ea ',' DREG ':' DREG
			{	/* 32 bit long division with remainder */
				extern int model;
				if ($1 == 040600 || model < MODEL_68020)
					serror("illegal size");
				checksize($2, 4);
				emit2(($1 & ~1) | mrg_2);
				emit2(($1 & 1)<<11 | $7<<12 | $5);
				ea_2(SIZE_L, DTA);
			}
	| LEA ea ',' AREG
			{	emit2(040700 | mrg_2 | $4<<9);
				ea_2(SIZE_L, CTR);
			}
	| op_ea ea
			{	emit2(($1&0177700) | mrg_2);
				ea_2($1&0300, $1&017);
			}
	| OP_NOOP
			{	emit2($1); }
	| CMP sizedef ea_ea
			{	cmp($2); }
	| MOVE sizenon ea_ea
			{	move($2); }
	| MOVEP sizedef ea_ea
			{	movep($2); }
	| MOVEM sizedef regs ',' notimmreg
			{	movem(0, $2, $3); }
	| MOVEM sizedef notimmreg ',' regs
			{	movem(1, $2, $5); }
	| MOVES sizedef ea_ea
			{	testmodel(MODEL_68010);
				if (mrg_1 <= 017) {
					emit2(007000 | $2 | mrg_2);
					emit2(mrg_1 << 12 | 04000);
					ea_2($2,ALT|MEM);
				} else if (mrg_2 <= 017) {
					emit2(007000 | $2 | mrg_1);
					emit2(mrg_2 << 12);
					ea_1($2,ALT|MEM);
				} else
					badoperand();
			}
	| MOVEC creg ',' reg
			{	testmodel(MODEL_68010);
				emit2(047172); emit2($2 | $4<<12);
			}
	| MOVEC reg ',' creg
			{	testmodel(MODEL_68010);
				emit2(047173); emit2($4 | $2<<12);
			}
	| EXG reg ',' reg
			{	if (($2 & 010) == 0)
					emit2(
						(0140500|$4|$2<<9)
						+
						(($4&010)<<3)
					);
				else
					emit2(
						(0140610|$2|($4&07)<<9)
						-
						(($4&010)<<3)
					);
			}
	| OP_EXT sizedef DREG
			{	if ($1 == 1) {
					testmodel(MODEL_68020);
					checksize($2, 4); emit2(044700 | $3);
				} else {
					checksize($2, 2|4); emit2(044000 | ($2+0100) | $3);
				}
			}
	| SWAP DREG
			{	emit2(044100 | $2); }
	| STOP imm
			{	emit2($1); ea_2(SIZE_W, 0); }
	| LINK sizedef AREG ',' imm
			{	if ($2 != SIZE_W)
					serror("illegal size");
				emit2(047120 | $3); ea_2(SIZE_W, 0);
			}
	| UNLK AREG
			{	emit2(047130 | $2); }
	| TRAP '#' absexp
			{	fit(fit4($3)); emit2(047100|low4($3)); }
	| RTD imm
			{	testmodel(MODEL_68010);
				emit2(047164);
				ea_2(SIZE_W, 0);
			}
	| CALLM	'#' absexp ',' ea
			{
				testmodel(MODEL_68020);
				emit2(003300 | mrg_2);
				emit2($3 & 0xFF);
				ea_2(SIZE_W, 0);
			}
	| RTM reg
			{	testmodel(MODEL_68020);
				emit2(003300 | $2);
			}

	/* M68030 MMU instructions */
	|	PFLUSHA
			{	emit2(0170000);
				emit2($1);
			}
	|	PFLUSH fcregs ',' mask
			{	emit2(0170000);
				emit2($1|010000|($4<<5)|$2);
			}
	|	PFLUSH fcregs ',' mask ',' ea
			{	emit2(0170000|mrg_2);
				emit2($1|014000|($4<<5)|$2);
				ea_2(SIZE_L, DTA|CTR);
			}
	|	PTEST fcregs ',' ea ',' mask
			{	emit2(0170000|mrg_2);
				emit2($1|($6<<10)|$2);
				ea_2(SIZE_L, DTA|CTR);
			}
	|	PTEST fcregs ',' ea ',' mask ',' AREG
			{	emit2(0170000|mrg_2);
				emit2($1|($6<<10)|$2|0400|($8<<5));
				ea_2(SIZE_L, DTA|CTR);
			}
	|	PLOAD fcregs ',' ea
			{	emit2(0170000|mrg_2);
				emit2($1|$2);
				ea_2(SIZE_L, DTA|CTR);
			}
	|	PMOVE MREG ',' ea
			{	emit2(0170000|mrg_2);
				emit2($1|$2|01000);
				ea_2(SIZE_L, DTA|CTR);
			}
	|	PMOVE ea ',' MREG
			{	emit2(0170000|mrg_2);
				emit2($1|$4);
				ea_2(SIZE_L, DTA|CTR);
			}
	| MODEL
			{	setmodel($1); }
	| fp_op
	;
bcdx	: ABCD
	| ADDX sizedef
			{	$$ = $1 | $2; }
	;
creg	: CREG
	| SPEC		{	if ($1 != 075) badoperand(); $$ = 04000; }
	;
op_ea	: OP_EA
	| SZ_EA sizedef
			{	$$ = $1 | $2; }
	;
regs	: rrange
	| regs '/' rrange
			{	$$ = $1 | $3; }
	| '#' absexp	{	$$ = $2; }
	;
rrange	: reg
			{	$$ = 1<<$1; }
	| reg '-' reg
			{	if ($1 > $3)
					badoperand();
				for ($$ = 0; $1 <= $3; $1++)
					$$ |= (1<<$1);
			}
	;
ea	: DREG
			{	mrg_2 = $1; }
	| AREG
			{	mrg_2 = 010 | $1; }
	| SPEC
			{	mrg_2 = $1; }
	| notimmreg
	| imm
	;

notimmreg
	: '(' AREG ')'
			{	mrg_2 = 020 | $2; }
	| '(' AREG ')' '+'
			{	mrg_2 = 030 | $2; }
	| '-' '(' AREG ')'
			{	mrg_2 = 040 | $3; }
	| expr sizenon
			{	exp_2 = $1; ea707172($2);
				RELOMOVE(rel_2, relonami);
			}
	| expr '(' reg sizenon ')'
			{	exp_2 = $1; ea5x73($3, $4);
				RELOMOVE(rel_2, relonami);
			}
#ifdef COMPAT
	| '(' expr ',' reg sizenon ')'
			{	exp_2 = $2; ea5x73($4, $5);
				RELOMOVE(rel_2, relonami);
			}
#endif
	| expr '(' AREG ',' reg sizedef ')'
			{	exp_2 = $1; ea6x($3, $5, $6);
				RELOMOVE(rel_2, relonami);
			}
#ifdef COMPAT
	| '(' AREG ',' reg sizedef ')'
			{	exp_2.val = 0; exp_2.typ = S_ABS; ea6x($2, $4, $5);
				RELOMOVE(rel_2, relonami);
			}
#endif
	| expr '(' PC ')'
			{	exp_2 = $1; ea72();
				RELOMOVE(rel_2, relonami);
			}
#ifdef COMPAT
	| '(' expr ',' PC ')'
			{	exp_2 = $2; ea72();
				RELOMOVE(rel_2, relonami);
			}
#endif
	| expr '(' PC ',' reg sizedef ')'
			{	exp_2 = $1; ea73($5, $6);
				RELOMOVE(rel_2, relonami);
			}
	;
imm	: '#' expr
			{	mrg_2 = 074; exp_2 = $2;
				RELOMOVE(rel_2, relonami);
			}
	;
reg	: DREG
	| AREG
			{	$$ = $1 | 010; }
	;

sizedef	: /* empty */
			{	$$ = SIZE_DEF; }
	| SIZE
	;

sizenon	: /* empty */
			{	$$ = SIZE_NON; }
	| SIZE
	;

ea_ea	: ea ','
			{	mrg_1 = mrg_2; exp_1 = exp_2;
				RELOMOVE(rel_1, rel_2);
			}
		ea
	;
fp_op	: CP
			{	co_id = $1; }
		fp_op1
	| 	{	co_id = DEF_FP; }
		fp_op1
	;

fp_op1	: FMOVE fsize ea ',' FPCR
			{	check_fsize($2, FSIZE_L);
				if ((mrg_2&070) == 010 && $5 != 001)
					badoperand();
				emit2((0170000|co_id|mrg_2));
				emit2((0100000|($5<<10)));
				ea_2(SIZE_L, 0);
			}
	| FMOVE fsize FPCR ',' ea
			{	check_fsize($2, FSIZE_L);
				if ((mrg_2&070) == 010 && $3 == 001)
					badoperand();
				emit2((0170000|co_id|mrg_2));
				emit2((0120000|($3<<10)));
				ea_2(SIZE_L, ALT);
			}
	| FMOVE fsize FPREG ',' FPREG
			{	emit2(0170000|co_id);
				emit2(($3<<10)|($5<<7));
			}
	| FMOVE fsize ea ',' FPREG
			{	ch_sz_dreg($2, mrg_2&070);
				emit2((0170000|co_id|mrg_2));
				emit2((0040000|($2<<10)|($5<<7)));
				ea_2(SIZE_L, DTA);
			}
	| FMOVE fsize FPREG ',' ea
			{	ch_sz_dreg($2, mrg_2&070);
				if ($2 == FSIZE_P)
					serror("packed decimal needs k-factor");
				emit2((0170000|co_id|mrg_2));
				emit2((0060000|($2<<10)|($3<<7)));
				ea_2(SIZE_L, DTA|ALT);
			}
	| FMOVE fsize FPREG ',' ea '{' '#' absexp '}'
			{	check_fsize($2, FSIZE_P);
				fit(sfit7($8));
				emit2((0170000|co_id|mrg_2));
				emit2((0066000|($3<<7)|low7($8)));
				ea_2(SIZE_L, MEM|DTA|ALT);
			}
	| FMOVE fsize FPREG ',' ea '{' DREG '}'
			{	check_fsize($2, FSIZE_P);
				emit2((0170000|co_id|mrg_2));
				emit2((0076000|($3<<7)|($7<<4)));
				ea_2(SIZE_L, MEM|DTA|ALT);
			}
	| FMOVECR fsize '#' absexp ',' FPREG
			{	fit(fit7($4));
				check_fsize($2, FSIZE_X);
				emit2(0170000|co_id);
				emit2(056000|($6<<7)|low7($4));
			} 
	| FMOVEM fsize fregs ',' notimmreg
			{	check_fsize($2, FSIZE_X);
				if ((mrg_2&070) == 030)
					serror("bad addressing category");
				emit2((0170000|co_id|mrg_2));
				emit2(0160000 | (((mrg_2&070)==040 || ($3&04000)) ?  $3 : (010000|reverse($3,8))));
				ea_2(SIZE_L, MEM|ALT);
			}
	| FMOVEM fsize notimmreg ',' fregs
			{	check_fsize($2, FSIZE_X);
				if ((mrg_2&070) == 040)
					serror("bad addressing category");
				emit2((0170000|co_id|mrg_2));
				emit2((0150000|(($5&04000)?$5:reverse($5,8))));
				ea_2(SIZE_L, MEM);
			}
	| FMOVEM SIZE fcregs ',' ea
			{	checksize($2, 4);
				if ((mrg_2&070) && $3 != 02000)
					serror("bad addressing category");
				if ((mrg_2 & 070) == 0 && $3 != 02000 && $3 != 04000 && $3 != 010000)
					serror("bad addressing category");
				emit2((0170000|co_id|mrg_2));
				emit2((0120000|$3));
				ea_2(SIZE_L, ALT);
			}
	| FMOVEM SIZE ea ',' fcregs
			{	checksize($2, 4);
				if ((mrg_2&070) && $5!= 02000)
					serror("bad addressing category");
				if ((mrg_2 & 070) == 0 && $5 != 02000 && $5 != 04000 && $5 != 010000)
					serror("bad addressing category");
				emit2((0170000|co_id|mrg_2));
				emit2((0100000|$5));
				ea_2(SIZE_L, 0);
			}
	| FDYADIC fsize ea ',' FPREG
			{	emit2((0170000|co_id|mrg_2));
				emit2((0040000|($2<<10)|($5<<7)|$1));
				ch_sz_dreg($2, mrg_2&070);
				ea_2(SIZE_L, DTA);
			}
	| FDYADIC fsize FPREG ',' FPREG
			{	check_fsize($2, FSIZE_X);
				emit2(0170000|co_id);
				emit2(($3<<10)|($5<<7)|$1);
			}
	| FMONADIC fsize ea ',' FPREG
			{	emit2((0170000|co_id|mrg_2));
				emit2((0040000|($2<<10)|($5<<7)|$1));
				ch_sz_dreg($2, mrg_2&070);
				ea_2(SIZE_L, DTA);
			}
	| FMONADIC fsize FPREG ',' FPREG
			{	check_fsize($2, FSIZE_X);
				emit2(0170000|co_id);
				emit2(($3<<10)|($5<<7)|$1);
			}
	| FMONADIC fsize FPREG
			{	check_fsize($2, FSIZE_X);
				emit2(0170000|co_id);
				emit2(($3<<10)|($3<<7)|$1);
			}
	| FSINCOS fsize ea ',' FPREG ':' FPREG
			{	emit2(0170000|co_id|mrg_2);
				emit2(0040000|($2<<10)|($7<<7)|$1|$5);
				ea_2(SIZE_L, DTA);
			}
	| FSINCOS fsize FPREG ',' FPREG ':' FPREG
			{	check_fsize($2, FSIZE_X);
				emit2(0170000|co_id);
				emit2(($3<<10)|($7<<7)|$1|$5);
			}
	| FBCC expr
			{	fbranch($1, $2); }
	| FDBCC DREG ',' expr
			{	emit2(0170110|co_id|$2);
				emit2($1);
				$4.val -= DOTVAL;
				fit(fitw($4.val));
#ifdef RELOCATION
				newrelo($4.typ, RELPC|RELO2|RELBR|RELWR);
#endif
				emit2(loww($4.val));
			}
	| FNOP
			{	emit2(0170200|co_id);
				emit2(0);
			}
	| FSCC ea
			{	emit2(0170100|co_id|mrg_2);
				emit2($1);
				ea_2(SIZE_B, DTA|ALT);
			}
	| FTST fsize ea
			{	emit2((0170000|co_id|mrg_2));
				emit2((0040072|($2<<10)));
				ch_sz_dreg($2, mrg_2&070);
				ea_2(SIZE_L, DTA);
			}
	| FTST fsize FPREG
			{	check_fsize($2, FSIZE_X);
				emit2(0170000|co_id);
				emit2(($3<<10)|072);
			}
	| FSAVRES ea
			{	if ((mrg_2&070) == ($1&070))
					badoperand();
				emit2((0170000|co_id|($1&0700)|mrg_2));
				ea_2(0, $1&07);
			}
	| FTRAPCC
			{	emit2(0170174|co_id);
				emit2($1);
			}
	| FTRAPCC SIZE imm
			{	checksize($2, 2|4);
				emit2((0170170|co_id|($2==SIZE_L?03:02)));
				emit2($1);
				ea_2($2,0);
			}
	;

fregs	: DREG
			{	$$ = 04000 | $1 << 4; }
	| frlist
	| '#' absexp	{	$$ = $2; }
	;

frlist	: frrange
	| frlist '/' frrange
			{	$$ = $1 | $3; }
	;

frrange	: FPREG
			{	$$ = 1 << $1; }
	| FPREG '-' FPREG
			{	if ($1 > $3)
					badoperand();
				for ($$ = 0; $1 <= $3; $1++)
					$$ |= (1 << $1);
			}
	;

mask	: '#' absexp
			{	fit(fit3($2));
				$$ = low3($2);
			}
	;

fcregs	: FPCR
			{	$$ = $1 << 10; }
	| fcregs '/' FPCR
			{	$$ = $1 | ($3 << 10); }
	| '#' absexp	{	$$ = $2; }
	;

fsize	: /*	empty */
			{	$$ = FSIZE_X; }
	| SIZE
			{	if ($1 == SIZE_L)
					$$ = FSIZE_L;
				else if ($1 == SIZE_W)
					$$ = FSIZE_W;
				else	$$ = FSIZE_B;
			}
	| FSIZE
	;
