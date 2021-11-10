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


static int config_addr = 0x2007;
static int config = 0x3fff;

#define CFG_FOSC_LP		0x0000		/* low-power crystal */
#define CFG_FOSC_XT		0x0001		/* crystal/resonator */
#define CFG_FOSC_HS		0x0002		/* high-speed crystal/resonator */
#define CFG_FOSC_RC		0x0003		/* resistor/capacitor */
#define CFG_FOSC_EC		0x0003		/* external clock on CLKIN pin, I/O on CLKOUT pin */
#define CFG_FOSC_INTRCIO	0x0010		/* internal RC oscillator; I/O functions on CLKIN/CLKOUT pins */
#define CFG_FOSC_INTRCCLK	0x0011		/* internal RC oscillator; I/O function on CLKIN */
#define CFG_FOSC_EXTRCIO	0x0012		/* external RC oscillator on CLKIN pin; I/O function on CLKOUT pin */
#define CFG_FOSC_EXTRCCLK	0x0013		/* external RC oscillator on CLKIN; clock out on CLKOUT pin */

#define CFG_WDTE		(1<<2)		/* watchdog timer enable */
#define CFG_PWRTE		(1<<3)		/* powerup timer enable */
#define CFG_MCLRE		(1<<5)
#define CFG_BOREN		(1<<6)		/* brown-out reset enable */
#define CFG_LVP			(1<<7)		/* low-voltage programming enable */
#define CFG_IESO		(1<<7)
#define CFG_CPD			(1<<8)		/* data code protection */
#define CFG_FCMEN		(1<<8)

#define CFG_CP_F84A		0x3ff0		/* PIC16F84A */
#define CFG_CP			(1<<13)		/* PIC16F628A */

void
setconfig(const char *s, const char *v)
{
#define ISTRUE(v) (strcasecmp(v, "ON") == 0 || strcasecmp(v, "TRUE") == 0 || strcasecmp(v, "ENABLED") == 0)

	DPRINTF(("%s = %s\n", s, v));
	if (strcasecmp(s, "FOSC") == 0) {		/* Oscillator Selection bits */
		if (strcasecmp(v, "LP") == 0)
			config |= CFG_FOSC_LP;
		else if (strcasecmp(v, "XT") == 0)
			config |= CFG_FOSC_XT;
		else if (strcasecmp(v, "HS") == 0)
			config |= CFG_FOSC_HS;
		else if (strcasecmp(v, "EXTRC") == 0 || strcasecmp(v, "RC") == 0)
			config |= CFG_FOSC_RC;
		else if (strcasecmp(v, "INTRC") == 0 || strcasecmp(v, "INTOSC") == 0 || strcasecmp(v, "INTOSCIO") == 0 || strcasecmp(v, "INTRCIO") == 0)
			config |= CFG_FOSC_INTRCIO;
 		else if (strcasecmp(v, "INTRCCLK") == 0 || strcasecmp(v, "INTOSCCLK") == 0)
			config |= CFG_FOSC_INTRCCLK;
		else if (strcasecmp(v, "EXTRC") == 0 || strcasecmp(v, "EXTOSC") == 0 || strcasecmp(v, "EXTRCIO") == 0 || strcasecmp(v, "EXTOSCIO") == 0)
			config |= CFG_FOSC_EXTRCIO;
 		else if (strcasecmp(v, "EXTRCCLK") == 0 || strcasecmp(v, "EXTOSCCLK") == 0)
			config |= CFG_FOSC_EXTRCCLK;
		else
			fatal("unrecognised FOSC value \"%s\"", v);
	} else if (strcasecmp(s, "WDTE") == 0) {	/* Watchdog Timer Enable bit */
		config |= ISTRUE(v) ? CFG_WDTE : 0;
	} else if (strcasecmp(s, "PWRTE") == 0) {	/* Power-up Timer Enable bit */
		config |= ISTRUE(v) ? 0 : CFG_PWRTE;
	} else if (strcasecmp(s, "MCLRE") == 0) {	/* MCLR Pin Function Select bit */
		config |= ISTRUE(v) ? CFG_MCLRE : 0;
	} else if (strcasecmp(s, "CP") == 0) {		/* Program Memory Code Protection bit */
		config |= ISTRUE(v) ? 0 : CFG_CP;
	} else if (strcasecmp(s, "CPD") == 0) {		/* Data Memory Code Protection bit */
		config |= ISTRUE(v) ? 0 : CFG_CPD;
	} else if (strcasecmp(s, "BOREN") == 0) {	/* Brown-out Reset Selection bits */
		config |= ISTRUE(v) ? CFG_BOREN : 0;
	} else if (strcasecmp(s, "IESO") == 0) {	/* Internal/External Switchover bit */
		config |= ISTRUE(v) ? 0 : CFG_IESO;
	} else if (strcasecmp(s, "LVP") == 0) {		/* Low-Voltage Programming Enable bit */
		config |= ISTRUE(v) ? CFG_LVP : 0;
	} else if (strcasecmp(s, "FCMEN") == 0) {	/* Fail-Safe Clock Monitor Enabled bit */
		config |= ISTRUE(v) ? 0 : CFG_FCMEN;
	} else {
		fatal("unrecognised config option \"%s\"", s);
	}

#undef ISTRUE
}

void
banksel(int regno)
{
	if (regno & ~0x7F) {
		/* bsf STATUS, 5: 01 01bb bfff ffff */
		emit2(0x1683);
	} else {
		/* bcf STATUS, 5: 01 00bb bfff ffff */
		emit2(0x1283);
	}
}

static const struct { int id; const char* name; } devices[] = {
	{ DEVICE_PIC16F84, "p16f84" },
	{ DEVICE_PIC16F84A, "p16f84a" },
	{ DEVICE_PIC16F630, "p16f630" },
	{ DEVICE_PIC16F676, "p16f676" },
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
#if 0
	/* XXXGJM: called too late afte rthe sections have been cleared */
	/* write config */
	DOTVAL = config_addr;
	emit2(config);
#endif
}
