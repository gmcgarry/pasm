/*-
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

%token <y_word> PSEUDOOP_CPU
%token <y_word> PSEUDOOP_ARCH
%token <y_word> PSEUDOOP_FPU
%token <y_word> PSEUDOOP_MODE
%token <y_word> PSEUDOOP_THUMBFUNC
#ifdef notyet
%token <y_word> PSEUDOOP_EABIATTR
%token <y_word> PSEUDOOP_CODE
%token <y_word> PSEUDOOP_SYNTAX
%token <y_word> PSEUDOOP_FUNC
%token <y_word> PSEUDOOP_POOL
%token <y_word> PSEUDOOP_CANTUNWIND
#endif

%token <y_word> SP LR PC REG REGHI

%token <y_word> IMPL
%token <y_word> STACK
%token <y_word> SHIFT
%token <y_word> ADD
%token <y_word> MOV
%token <y_word> CMP
%token <y_word> DATA1
%token <y_word> SVC SWI IT
%token <y_word> LDST LDSTB LDSTH LDRS

%token <y_word> COND
%token <y_word> BREXCH
%token <y_word> BRANCH
%token <y_word> UBRANCH
%token <y_word> LBRANCH
%token <y_word> LDM
%token <y_word> ADR
%token <y_word> CBNZ

%type <y_word> reg
%type <y_word> reghi
%type <y_word> format_01
%type <y_word> format_02
%type <y_word> format_03
%type <y_word> format_04
%type <y_word> format_05
%type <y_word> format_06
%type <y_word> format_07
%type <y_word> format_08
%type <y_word> format_09
%type <y_word> format_09b
%type <y_word> format_10
%type <y_word> format_11
%type <y_word> format_12
%type <y_word> format_13
%type <y_word> format_14
%type <y_word> format_15
%type <y_word> format_16
%type <y_word> format_17
%type <y_word> format_18
%type <y_word> format_20

%type <y_word> reglist rlist
%type <y_word> offset offset32
