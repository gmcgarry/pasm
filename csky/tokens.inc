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

%token PSEUDOOP_LITERALS

%token <y_word> LOREG HIREG CREG

%token <y_word> IMPL
%token <y_word> JTYPE
%token <y_word> ITYPE3
%token <y_word> ITYPE5_1 ITYPE5_2 ITYPE5_3 
%token <y_word> ITYPE7
%token <y_word> ITYPE8_1 ITYPE8_2
%token <y_word> RTYPE2 RTYPE3
%token <y_word> XXX

%token <y_word> LRW
%token <y_word> MTCR
%token <y_word> MOVI
%token <y_word> JSR
%token <y_word> LDST
%token <y_word> BIT BITO
%token <y_word> TWOOP TWOOPI TWOOPIO

%token <y_word> BRANCH

%type <y_valu> offset
%type <y_word> reg
