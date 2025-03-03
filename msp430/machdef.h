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

#define COMPAT_NAKEN

#define LISTING
#define THREE_PASS

/* ========== Machine independent type declarations ========== */

#define PASS_1          0
#define PASS_2          1
#define PASS_3          2

#define PASS_SYMB       (pass != PASS_1)
#define PASS_RELO       (pass != PASS_1)

#define IGNORECASE

/*
#define WORDS_REVERSED
#define BYTES_REVERSED
*/

#define ADDR_T		short
#define word_t		unsigned int

#define WORDSIZE	2
#define DWORDSIZE	4
#define ALIGNWORD	4
#define ALIGNSECT	4

/* Some character constants for scanner*/
#define ASC_COMMENT     ';'
#define CTRL(x)         ((x) & 037)
#define ISALPHA(c)      (isalpha(c) || (c) == '_' || (c) == '.' || (c) == '$')
#define ISALNUM(c)      (isalnum(c) || (c) == '_')

#define DEFAULT_SECTION (1)
