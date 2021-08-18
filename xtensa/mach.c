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

#include "as.h"
#include "error.h"

extern int hash(const char* p);


/* XXXGJM still cannot use sections with the same names as keywords */
static item_t literals = { 0, 0, S_UND, ".literals" };


void
mflag(const char* flag)
{
}

void
machstart(int pass)
{
	if (pass == PASS_1) {
                item_insert(&literals, hash(literals.i_name));
		unresolved++;
	}
        newsect(&literals, SHT_PROGBITS, "ax");
}

void
machfinish(int pass)
{
}

void
literal(item_t *ident, expr_t e)
{
	int sct = DOTSCT;
	printf("=====> DOTSCT = %d\n", DOTSCT);
	newsect(&literals, SHT_PROGBITS, "ax");
	printf("<===== DOTSCT = %d\n", DOTSCT);
	newident(ident, DOTSCT);
	newlabel(ident);
	if (PASS_RELO)
		newrelo(e.typ, RELO4);
	emit4(e.val);
	switchsect(sct);
}

int
b4const(ADDR_T imm4)
{
	if (imm4 == -1)
		return 0;
	if (imm4 >= 1 && imm4 <= 10)
		return (int)(imm4 - 1);
	if (imm4 == 12)
		return 10;
	if (imm4 == 16)
		return 11;
	if (imm4 == 32)
		return 12;
	if (imm4 == 64)
		return 13;
	if (imm4 == 128)
		return 14;
	if (imm4 == 256)
		return 15;
	serror("invalid constant operand");
	return 0;
}

int
b4constu(ADDR_T imm4)
{
	if (imm4 == 0x08000)
		return 0;
	if (imm4 == 0x10000)
		return 1;
	if (imm4 >= 2 && imm4 <= 8)
		return (int)imm4;
	if (imm4 == 10)
		return 9;
	if (imm4 == 12)
		return 10;
	if (imm4 == 16)
		return 11;
	if (imm4 == 32)
		return 12;
	if (imm4 == 64)
		return 13;
	if (imm4 == 128)
		return 14;
	if (imm4 == 256)
		return 15;
	serror("invalid constant operand");
	return 0;
}
