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

%token <y_word> PSEUDOOP_CONFIG
%token <y_word> PSEUDOOP_MAXRAM PSEUDOOP_BADRAM
%token <y_word> PSEUDOOP_BANKSEL PSEUDOOP_BANKMASK
%token <y_word> PSEUDOOP_PAGESEL
%token <y_word> PSEUDOOP_DEVICE
%token <y_word> PSEUDOOP_DT

%token <y_word> W

%token <y_word> SHIFTFUNC

%token <y_word> BYTEOP
%token <y_word> BITOP
%token <y_word> LITOP
%token <y_word> NOOP
%token <y_word> ONEOP
%token <y_word> JMPOP
%token <y_word> D
%token <y_word> TRIS

%type <y_word> b d f k8 k3 off
%type <y_word> optdir
%type <y_word> dtlist
