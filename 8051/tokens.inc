/*-
 * Copyright (c) 1990 Ken Stauffer (University of Calgary)
 * Copyright (c) 2021 Gregory McGarry <g.mcgarry@ieee.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* %left '#' */

%type <y_word> const8
%type <y_word> const16
%type <y_word> data8
%type <y_word> data16
%type <y_word> regi
%type <y_word> reg
%type <y_word> bit
%type <y_word> bitv
%type <y_word> rel
%type <y_word> rel2

%token <y_word> ACALL
%token <y_word> ADD
%token <y_word> ADDC
%token <y_word> AJMP
%token <y_word> ANL
%token <y_word> CJNE
%token <y_word> CLR
%token <y_word> CPL
%token <y_word> DA
%token <y_word> DEC
%token <y_word> DIV
%token <y_word> DJNZ
%token <y_word> INC
%token <y_word> JB
%token <y_word> JBC
%token <y_word> JC
%token <y_word> JMP
%token <y_word> JNB
%token <y_word> JNC
%token <y_word> JNZ
%token <y_word> JZ
%token <y_word> LCALL
%token <y_word> LJMP
%token <y_word> MOV
%token <y_word> MOVC
%token <y_word> MOVX
%token <y_word> NOP
%token <y_word> MUL
%token <y_word> ORL
%token <y_word> POP
%token <y_word> PUSH
%token <y_word> RET
%token <y_word> RETI
%token <y_word> RL
%token <y_word> RLC
%token <y_word> RR
%token <y_word> RRC
%token <y_word> SETB
%token <y_word> SJMP
%token <y_word> SUBB
%token <y_word> SWAP
%token <y_word> XCH
%token <y_word> XCHD
%token <y_word> XRL

%token <y_word> AB
%token <y_word> A
%token <y_word> C
%token <y_word> PC
%token <y_word> DPTR
%token <y_word> BITPOS

%token <y_word> AREG
%token <y_word> SFR
%token <y_word> PSEUDOOP_AREA

%token BIT
