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
 * delay inclusion of machine dependent stuff
 */

#define	_include	#include

%{

#include "machdef.h"

_include <assert.h>
_include <stdio.h>
_include <string.h>

_include "as.h"
_include "out.h"
_include "error.h"

extern int yylex();

extern sect_t sect[SECTMAX];	/* XXXGJM remove */
extern short hashindex;		/* XXXGJM remove */

static item_t	*last_it;

%}

/* ========== Machine independent Yacc definitions ========== */

%union {
	word_t y_word;
	ADDR_T y_valu;
	expr_t y_expr;
	item_t *y_item;
};

%token STRING
%token <y_item> IDENT
%token <y_item> FBSYM
%token <y_valu> CODE1
%token <y_valu> CODE2
%token <y_valu> CODE4
%token NUMBER0		/* keep NUMBER[0-4] in this order */
%token NUMBER1
%token NUMBER2
%token NUMBER3
%token NUMBER4
%token <y_valu> NUMBER8
%token NUMBERF
%token DOT
%token PSEUDOOP_EXTERN
%token <y_word> PSEUDOOP_DATA
%token PSEUDOOP_DATA8
#ifdef USE_FLOAT
%token <y_word> PSEUDOOP_DATAF
#endif
%token <y_word> PSEUDOOP_ASCII
%token PSEUDOOP_SECTION
%token PSEUDOOP_END
%token PSEUDOOP_GLOBAL
%token PSEUDOOP_LOCAL
%token PSEUDOOP_TYPE
%token PSEUDOOP_SIZE
%token PSEUDOOP_IDENT
%token PSEUDOOP_COMMON
%token PSEUDOOP_BASE
%token PSEUDOOP_ORG
%token PSEUDOOP_EQU
%token PSEUDOOP_SET
%token PSEUDOOP_MESSAGE
%token <y_word> PSEUDOOP_ALIGN
%token PSEUDOOP_ASSERT
%token PSEUDOOP_SPACE
%token PSEUDOOP_SEEK
%token PSEUDOOP_CFI_IGNORE
%token <y_word> PSEUDOOP_LINE
%token PSEUDOOP_FILE
%token <y_word> PSEUDOOP_LIST
%token <y_word> ELF_SHTYPE
%token <y_word> ELF_SYMTYPE
%token <y_wrod> PLT

%left OP_OO
%left OP_AA
%left '|'
%left '^'
%left '&'
%left OP_EQ OP_NE
%left '<' '>' OP_LE OP_GE
%left OP_LL OP_RR
%left '+' '-'
%left '*' '/' '%'
%nonassoc '~'

%type <y_valu> absexp optabs optsize
%type <y_expr> expr
%type <y_item> id_fb

/* ========== Machine dependent Yacc definitions ========== */

#include	"tokens.inc"

%%

/* ========== Machine independent rules ========== */

#ifdef LISTING
#define	LISTLINE(n)	if (listflag) listline(n); else if (listtemp) { listflag = listtemp; listeoln = 1; }
#else
#define	LISTLINE(n)	/* empty */
#endif /* LISTING */

#define	RELODONE	{ assert(relonami == RELO_UNDEF); } while (0)

program	: /* empty */
	| program IDENT ':'			{ newident($2, DOTSCT); newlabel($2); RELODONE; }
	| program NUMBER8 ':'			{ if ($2 < 0 || $2 > 9) { serror("bad f/b label"); $2 = 0; } newlabel(fb_shift((int)$2)); RELODONE; }
	| program CODE1				{ emit1((int)$2); LISTLINE(0); }
	| program CODE2				{ emit2((int)$2); LISTLINE(0); }
	| program CODE4				{ emit4((long)$2); LISTLINE(0); }
	| program operation ';'
	| program operation '\n'		{ lineno++; LISTLINE(1); RELODONE; }
	| program '#' NUMBER8 STRING '\n'	{ lineno = $3; /* long = int64_t */ if (modulename) strncpy(modulename, stringbuf, STRINGMAX-1); LISTLINE(1); RELODONE; }
	| program error '\n'			{ serror("syntax error"); yyerrok; lineno++; LISTLINE(1); RELODONE; }
	;
#undef LISTLINE
#undef RELODONE

operation: /* empty */
#ifdef LISTING
	| PSEUDOOP_LIST				{ if ($1) listtemp = listmode; else if ((dflag & 01000) == 0) listtemp = 0; }
#endif
        | IDENT '=' expr			{
#ifdef LISTING
                                			if (listflag & 1)
                                        			listcolm += printx(VALWIDTH, $3.val);
#endif
                                			newequate($1, $3.typ);
                                			store($1, $3.val);
                        			}
	| PSEUDOOP_MESSAGE STRING		{ puts(stringbuf); }
	| PSEUDOOP_SECTION IDENT		{ newsect($2, 0, NULL); }
	| PSEUDOOP_SECTION IDENT ',' STRING ',' ELF_SHTYPE	{ newsect($2, $<y_word>6, stringbuf); }
	| PSEUDOOP_END				{ }
	| PSEUDOOP_GLOBAL IDENT		{ $2->i_type |= S_EXTERN; }
	| PSEUDOOP_LOCAL IDENT			{ $2->i_type &= ~S_EXTERN; }
	| PSEUDOOP_SIZE IDENT ',' expr		{ /* if (PASS_SYMB) $2->i_size = $4.valu; */ }
	| PSEUDOOP_TYPE IDENT ',' ELF_SYMTYPE	{ if (PASS_SYMB) $2->i_type |= $4; }
	| PSEUDOOP_IDENT STRING			{ }
	| PSEUDOOP_COMMON IDENT ',' absexp optsize 	{ newcomm($2, $4);}
	| PSEUDOOP_BASE absexp			{ if (pass == PASS_1) newbase($2); }
	| PSEUDOOP_ORG absexp			{
							if (DOTSCT == S_UND)
								nosect();
							if ($2 < DOTVAL)
								serror("cannot move location counter backwards");
							if ((sect[DOTSCT].s_flag & BASED) == 0) {
								newbase($2);
							} else {
								if (pass == PASS_1)
									sect[DOTSCT].s_flag |= SOUGHT;
								sect[DOTSCT].s_zero += $2 - DOTVAL;
								DOTVAL = $2;
							}
							sect[DOTSCT].s_gain = 0;
						}
#if 0
	| PSEUDOOP_LINE optabs			{
							if ((sflag & SYM_LIN) && PASS_SYMB) {
								if ($2)
									hllino = (short)$2;
								else
									hllino++;
								/* XXXGJM: these go in the dwarf section, not the symtab, like in coff file */
								newsymb((char *)0, (DOTSCT | S_LIN), (ADDR_T)DOTVAL);
							}
						}
#endif
	| PSEUDOOP_FILE STRING			{ if ((sflag & SYM_LIN) && PASS_SYMB) newsymb(stringbuf, (S_ABS | S_FILE), (ADDR_T)DOTVAL); }
	| PSEUDOOP_EQU IDENT '=' absexp		{ $2->i_type = S_ABS; $2->i_valu = $4; }
	| PSEUDOOP_SET IDENT ',' absexp		{ $2->i_type = S_ABS; $2->i_valu = $4; }
	| PSEUDOOP_EXTERN externlist
	| PSEUDOOP_ALIGN optabs			{ if (!($1)) align($2); else align(0x1<<$2); }
	| PSEUDOOP_SPACE absexp			{ if (DOTSCT == S_UND) nosect(); DOTVAL += $2; (&sect[DOTSCT])->s_zero += $2; }
	| PSEUDOOP_SEEK absexp			{
							if (DOTSCT == S_UND)
								nosect();
							if ($2 < DOTVAL)
								serror("cannot move location counter backwards");
							if (pass == PASS_1)
								sect[DOTSCT].s_flag |= SOUGHT;
							sect[DOTSCT].s_zero += $2 - DOTVAL;
							DOTVAL = $2;
						}
	| PSEUDOOP_DATA datalist
	| PSEUDOOP_DATA8 data8list
#ifdef USE_FLOAT
	| PSEUDOOP_DATAF dataflist
#endif
	| PSEUDOOP_ASCII STRING			{ emitstr($1); }
	| PSEUDOOP_CFI_IGNORE optabs		{ }
	| PSEUDOOP_CFI_IGNORE absexp ',' absexp { }
	;

externlist
	: IDENT					{ $1->i_type |= S_EXTERN; }
	| externlist ',' IDENT			{ $3->i_type |= S_EXTERN; }
	;

datalist: expr					{ if (PASS_RELO) newrelo($1.typ, (int)$<y_word>0|MACHREL_BWR); emitx($1.val, (int)$<y_word>0); }
	| STRING				{ int i; for (i = 0; i < stringlen; i++) emit1(stringbuf[i]); }
	| datalist ',' expr			{ if (PASS_RELO) newrelo($3.typ, (int)$<y_word>0|MACHREL_BWR); emitx($3.val, (int)$<y_word>0); }
	;

data8list
	: absexp				{ emit8($1); }
	| data8list ',' absexp			{ emit8($3); }
	;

#ifdef USE_FLOAT
numberf
	: NUMBERF				{ emitf((int)$<y_word>-1, 0); }
	| '-' NUMBERF				{ emitf((int)$<y_word>-1, 1); }
	;

dataflist
	: numberf
	| dataflist ',' numberf
	;
#endif

expr	: error					{ serror("expr syntax err"); $$.val = 0; $$.typ = S_UND; }
	| NUMBER8				{ $$.val = $1; /* ADDR_T = int64_t */ $$.typ = S_ABS; }
	| id_fb					{ $$.val = load($1); last_it = $1; $$.typ = $1->i_type & S_SCTMASK; }
	| STRING				{ if (stringlen != 1) serror("too many chars"); $$.val = stringbuf[0]; $$.typ = S_ABS; }
#if 1
	| '(' expr ')'				{ $$ = $2; }
#endif
	| expr OP_OO expr			{ $$.val = ($1.val || $3.val); $$.typ = combine($1.typ, $3.typ, 0); }
	| expr OP_AA expr			{ $$.val = ($1.val && $3.val); $$.typ = combine($1.typ, $3.typ, 0); }
	| expr '|' expr				{ $$.val = ($1.val | $3.val); $$.typ = combine($1.typ, $3.typ, 0); }
	| expr '^' expr				{ $$.val = ($1.val ^ $3.val); $$.typ = combine($1.typ, $3.typ, 0); }
	| expr '&' expr				{ $$.val = ($1.val & $3.val); $$.typ = combine($1.typ, $3.typ, 0); }
	| expr OP_EQ expr			{ $$.val = ($1.val == $3.val); $$.typ = combine($1.typ, $3.typ, '>'); }
	| expr OP_NE expr			{ $$.val = ($1.val != $3.val); $$.typ = combine($1.typ, $3.typ, '>'); }
	| expr '<' expr				{ $$.val = ($1.val < $3.val); $$.typ = combine($1.typ, $3.typ, '>'); }
	| expr '>' expr				{ $$.val = ($1.val > $3.val); $$.typ = combine($1.typ, $3.typ, '>'); }
	| expr OP_LE expr			{ $$.val = ($1.val <= $3.val); $$.typ = combine($1.typ, $3.typ, '>'); }
	| expr OP_GE expr			{ $$.val = ($1.val >= $3.val); $$.typ = combine($1.typ, $3.typ, '>'); }
	| expr OP_RR expr			{ $$.val = ($1.val >> $3.val); $$.typ = combine($1.typ, $3.typ, 0); }
	| expr OP_LL expr			{ $$.val = ($1.val << $3.val); $$.typ = combine($1.typ, $3.typ, 0); }
	| expr '+' expr				{ $$.val = ($1.val + $3.val); $$.typ = combine($1.typ, $3.typ, '+'); }
	| expr '-' expr				{ $$.val = ($1.val - $3.val); $$.typ = combine($1.typ, $3.typ, '-'); }
	| expr '*' expr				{ $$.val = ($1.val * $3.val); $$.typ = combine($1.typ, $3.typ, 0); }
	| expr '/' expr				{ if ($3.val == 0) { if (pass == PASS_3) serror("divide by zero"); $$.val = 0; } else $$.val = ($1.val / $3.val); $$.typ = combine($1.typ, $3.typ, 0); }
	| expr '%' expr				{ if ($3.val == 0) { if (pass == PASS_3) serror("divide by zero"); $$.val = 0; } else $$.val = ($1.val % $3.val); $$.typ = combine($1.typ, $3.typ, 0); }
	| '+' expr %prec '*'			{ $$.val = $2.val; $$.typ = combine(S_ABS, $2.typ, 0); }
	| '-' expr %prec '*'			{ $$.val = -$2.val; $$.typ = combine(S_ABS, $2.typ, 0); }
	| '~' expr				{ $$.val = ~$2.val; $$.typ = combine(S_ABS, $2.typ, 0); }
	| DOT					{ $$.val = DOTVAL; $$.typ = DOTSCT | S_DOT; }
	;

id_fb	: IDENT
	| FBSYM
	;

absexp	: expr					{ if (($1.typ & S_SCTMASK) != S_ABS) serror("must be absolute"); $$ = $1.val; }
	;

optabs : /* empty */				{ $$ = 0; }
	| absexp				{ $$ = $1; }
	;

optsize : /* empty */				{ $$ = 1; }
	| ',' absexp				{ $$ = $2; }

/* ========== Machine dependent rules ========== */

#include	"grammar.inc"

%%
