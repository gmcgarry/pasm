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

#include <assert.h>
#include <stdio.h>
#include <strings.h> /* strncasecmp() */

#include "as.h"
#include "error.h"

#include "mach.h"

extern sect_t sect[];
extern int hash(const char *);

static item_t cseg = { 0, S_UND, 0, ".cseg" };

static int config_addr = 0x400E;
static int config_word = 0x3fff;

static const struct { const char* name; int config_address; } devices[] = {
	{ "p12f508", 0xFFF },
	{ "p16f84", 0x400E },
	{ "p16f84a", 0x400E },
	{ "p16f627", 0x400E },
	{ "p16f628", 0x400E },
	{ "p16f628a", 0x400E },
	{ "p16f630", 0x400E },
	{ "p16f676", 0x400E },
};

#ifndef __TABLE_SIZE
#define __TABLE_SIZE(x)	(sizeof(x)/sizeof((x)[0]))
#endif

void
setdevice(const char *name)
{
	int i;

	for (i = 0; i < (int)__TABLE_SIZE(devices); i++) {
		if (strcasecmp(name, devices[i].name) == 0) {
			config_addr = devices[i].config_address;
			return;
		}
	}
	fatal("unrecognised device \"%s\"", name);
}

void
setconfig(int word)
{
	config_word = word;
	printf("config => 0x%04x\n", config_word);
}

void
banksel(int regno)
{
	int bank = regno & 0x80;

	if (bank)
		emit2(0x1683);	/* bsf STATUS, 5: 01 01bb bfff ffff */
	else
		emit2(0x1283);	/* bcf STATUS, 5: 01 00bb bfff ffff */
}

void
mflag(const char *flag)
{
	if (strncasecmp(flag, "cpu=", 4) == 0)
		setdevice(&flag[4]);
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
	/* write config */
	DOTVAL = config_addr;
	emit2(config_word);
}
