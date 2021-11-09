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

%token PSEUDOOP_DEVICE

%token <y_word> REG REGW SFR
%token <y_word> RMW RM
%token <y_word> LD LDC LDCI
%token <y_word> IMPL CALL INC INCW SRP
%token <y_word> BRANCH RBRANCH

%token <y_word> COND

%type <y_word> optcond
%type <y_word> reg
%type <y_valu> direct directw
%type <y_valu> imm imm8
%type <y_valu> address offset
