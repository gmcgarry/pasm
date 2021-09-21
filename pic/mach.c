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
#include "mach.h"

extern sect_t sect[];
extern int hash(const char *);

static item_t cseg = { 0, 0, S_UND, ".cseg" };


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
		item_insert(&cseg, hash(cseg.i_name));
		unresolved++;
	}
	newsect(&cseg, 0, NULL);
}

void
machfinish(int pass)
{
}

void
banksel(int regno)
{
	if (regno & ~0x7F) {
		// bsf STATUS, 5: 01 01bb bfff ffff
		emit2(0x1683);
	} else {
		// bcf STATUS, 5: 01 00bb bfff ffff
		emit2(0x1283);
	}
}

static const struct { int id; const char* name; } devices[] = {
	{ DEVICE_PIC16F84, "pic16f84" },
	{ DEVICE_PIC16F84A, "pic16f84a" },
};

#ifndef __TABLE_SIZE
#define __TABLE_SIZE(x)	(sizeof(x)/sizeof((x)[0]))
#endif

static int device = DEVICE_UNDEF;

void
setdevice(const char *name)
{
	int i;

	for (i = 0; i < (int)__TABLE_SIZE(devices); i++) {
		if (strcasecmp(name, devices[i].name) == 0) {
			device = devices[i].id;
			break;
		}
	}
	if (device == DEVICE_UNDEF)
		fatal("unrecognised device \"%s\"", name);
}


static int config = 0;

#define CFG_FOSC_INTRCIO	0
#define CFG_WDTE		1
#define CFG_PWRTE		2
#define CFG_MCLRE		3
#define CFG_CP			4
#define CFG_CPD			5
#define CFG_BOREN		6
#define CFG_IESO		7
#define CFG_FCMEN		8

void
setconfig(const char *s, const char *v)
{
#define ISTRUE(v) (strcasecmp(v, "ON") == 0 || strcasecmp(v, "TRUE") == 0)

	printf("%s = %s\n", s, v);
	if (strcasecmp(s, "FOSC") == 0) {
		/* Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN) */
		if (strcasecmp(v, "INTRCIO") == 0)
			config |= CFG_FOSC_INTRCIO;
		else
			fatal("unrecognised FOSC value \"%s\"", v);
	} else if (strcasecmp(s, "WDTE") == 0) {
		/* Watchdog Timer Enable bit */
		config |= ISTRUE(v) ? CFG_WDTE : 0;
	} else if (strcasecmp(s, "PWRTE") == 0) {
		/* Power-up Timer Enable bit */
		config |= ISTRUE(v) ? CFG_PWRTE : 0;
	} else if (strcasecmp(s, "MCLRE") == 0) {
		/* MCLR Pin Function Select bit*/
		config |= ISTRUE(v) ? CFG_MCLRE : 0;
	} else if (strcasecmp(s, "CP") == 0) {
		/* Program Memory Code Protection bit */
		config |= ISTRUE(v) ? CFG_CP : 0;
	} else if (strcasecmp(s, "CPD") == 0) {
		/* Data Memory Code Protection bit */
		config |= ISTRUE(v) ? CFG_CPD : 0;
	} else if (strcasecmp(s, "BOREN") == 0) {
		/* Brown-out Reset Selection bits (BOR enabled) */
		config |= ISTRUE(v) ? CFG_BOREN : 0;
	} else if (strcasecmp(s, "IESO") == 0) {
		/* Internal External Switchover bit */
		config |= ISTRUE(v) ? CFG_IESO : 0;
	} else if (strcasecmp(s, "FCMEN") == 0) {
		/* Fail-Safe Clock Monitor Enabled bit */
		config |= ISTRUE(v) ? CFG_FCMEN : 0;
	} else {
		fatal("unrecognise config option \"%s\"", s);
	}

#undef ISTRUE
}
