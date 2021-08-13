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

void
machstart(int pass)
{
	if (pass == PASS_1) {
		item_t *ip;
		ip = item_alloc(S_UND);
		ip->i_name = ".literals";
		item_insert(ip, hash(ip->i_name));
	}
}

void
machfinish(int pass)
{
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
