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

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "as.h"
#include "error.h"

extern sect_t sect[];

extern sect_t sect[];
extern int hash(const char *);

static item_t cseg = { 0, S_UND, 0, ".text" };

void
mflag(const char* flag)
{
}

void
machstart(int pass)
{
	if (pass == PASS_1) {
		item_insert(&cseg, H_GLOBAL+hash(cseg.i_name));
		unresolved++;
	}
	newsect(&cseg, 0, NULL);
}

void
machfinish(int pass)
{
}


static ADDR_T literals_address;
static ADDR_T literals[1024];
static int nliterals;

ADDR_T
add_literal(ADDR_T v)
{
	int i;

	DPRINTF(("pass %d, adding literal[%d]=0x%x @ 0x%x\n", pass, nliterals, v, literals_address+nliterals*4));
	for (i = 0; i < nliterals; i++) {
		if (literals[i] == v)
			return literals_address + i * 4;
	}
	literals[nliterals] = v;
	return literals_address + nliterals++ * 4;
}

void
emit_literals()
{
	int i = 0;

	if (nliterals == 0)
		return;

	align(4,0,0);
	literals_address = DOTVAL;
	for (i = 0; i < nliterals; i++) {
		DPRINTF(("pass %d, emitting literal[%d]=0x%x @ 0x%x\n", pass, i, literals[i], literals_address+(i*4)));
		emit4(literals[i]);
	}
	nliterals = 0;
}
