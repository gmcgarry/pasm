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


/*
 * Encode specific source constants.
 */
word_t
constant(expr_t exp)
{
	int val = exp.val & 0xFFFF;
	int sm = (val == 0xFFFF || val == 0 || val == 1 || val == 2 || val == 4 || val == 8);

	if (small(sm, 2)) {
		if (val == 4)
			return 0x0220;
		else if (val == 8)
			return 0x0230;
		else if (val == 0)
			return 0x0300;
		else if (val == 1)
			return 0x0310;
		else if (val == 2)
			return 0x0320;
		else if (val == 0xFFFF)
			return 0x0330;
		fatal("something went wrong");
	}
	/* encoded as @PC+ val */
	return (exp.val<<16)|(0x0<<8)|0x30;
}
