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

int isa = ARMv4T;

extern sect_t sect[];

extern sect_t sect[];
extern int hash(const char *);

static item_t cseg = { 0, S_UND, 0, ".text" };

void
mflag(const char* flag)
{
	if (strncasecmp(flag, "cpu=", 4) == 0)
		setcpu(&flag[4]);
	else if (strncasecmp(flag, "arch=", 4) == 0)
		setarch(&flag[5]);
	else if (strncasecmp(flag, "fpu=", 4) == 0)
		setfpu(&flag[4]);
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

void
setcpu(const char* cpu)
{
	static const struct { const char *name; int isa; } Cpus[] = {
		{ "arm7tdmi", ARMv4T },
		{ "arm9tdmi", ARMv4T },
		{ "arm720t", ARMv4T },
		{ "arm740t", ARMv4T },
		{ "arm920t", ARMv4T },
		{ "arm922t", ARMv4T },
		{ "arm940t", ARMv4T },
		{ "sc100", ARMv4T },
		{ "arm9e", ARMv5T },
		{ "arm946e", ARMv5T },
		{ "arm966e", ARMv5T },
		{ "arm926ej", ARMv5T },
		{ "arm1026ej", ARMv5T },
		{ "sc200", ARMv5T },
		{ "arm1136j", ARMv6 },
		{ "arm1136jf", ARMv6 },
		{ "cortex-m0", ARMv6M },
		{ "cortex-m0plus", ARMv6M },
		{ "cortex-m1", ARMv6M },
		{ "cortex-m3", ARMv7 },
		{ "cortex-m4", ARMv7 },
		{ "cortex-m7", ARMv7 },
		{ "sc000", ARMv6 },
		{ "arm1156t2", ARMv6T2 },
		{ "arm1156t2f", ARMv6T2 },
		{ "cortex-a5", ARMv7 },
		{ "cortex-a7", ARMv7 },
		{ "cortex-a8", ARMv7 },
		{ "cortex-a9", ARMv7 },
		{ "cortex-a15", ARMv6 },
	};
	int i;

	for (i = 0; i < (int)(sizeof(Cpus)/sizeof(Cpus[0])); i++)
		if (strcasecmp(Cpus[i].name, cpu) == 0)
			isa = Cpus[i].isa;
}

void
setarch(const char* arch)
{
	/*
	 * armv4t
	 * armv5t armv5te
	 * armv6-m armv6s-m armv6t2
	 * armv7-m armv7e-m
	 */
	if (strcmp(arch, "armv4t") == 0)
		isa = ARMv4T;
	else if (strcmp(arch, "arm5t") == 0)
		isa = ARMv5T;
	else if (strcmp(arch, "armv6") == 0)
		isa = ARMv6;
	else if (strcmp(arch, "armv6-m") == 0 || strcmp(arch, "armv6m") == 0)
		isa = ARMv6M;
	else if (strncmp(arch, "armv7", 5) == 0)
		isa = ARMv7;
	else
		fatal("unsupported '%s' ISA", arch);
}

void
setfpu(const char* fpu)
{
	if (pass == PASS_1) 
		warning("ignoring .fpu directive (%s)", fpu);
}



static ADDR_T literals_address;
static ADDR_T literals[1024];
static int nliterals;

ADDR_T
add_literal(ADDR_T v)
{
	DPRINTF(("adding literal[%d]=0x%x @ 0x%x\n", nliterals, v, literals_address+nliterals*4));
	literals[nliterals] = v;
	return literals_address + nliterals++ * 4;
}

void
emit_literals()
{
	int i = 0;

	align(4,0,0);
	literals_address = DOTVAL;
	for (i = 0; i < nliterals; i++) {
		DPRINTF(("emitting literal[%d]=0x%x @ 0x%x\n", i, literals[i], literals_address+(i*4)));
		emit4(literals[i]);
	}
	nliterals = 0;
}
