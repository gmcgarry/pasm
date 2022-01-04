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

#define ISTRUE(v)	(strcasecmp(v, "ON") == 0 || strcasecmp(v, "TRUE") == 0 || strcasecmp(v, "ENABLED") == 0)
#define SET_IF_FALSE(v,f)	do { if (ISTRUE(v)) config_word &= ~(f); } while (0)
#define SET_IF_TRUE(v,f)	do { if (!ISTRUE(v)) config_word &= ~(f); } while (0)

/* PIC16F630/PIC16F676 */
static void
setconfig_630(const char *s, const char *v)
{
#define P630_CFG_FOSC_LP	0x0000		/* low-power crystal */
#define P630_CFG_FOSC_XT	0x0001		/* crystal/resonator */
#define P630_CFG_FOSC_HS	0x0002		/* high-speed crystal/resonator */
#define P630_CFG_FOSC_EC	0x0003		/* external clock on CLKIN pin, I/O on CLKOUT pin */
#define P630_CFG_FOSC_INTOSCIO	0x0004		/* internal RC oscillator; I/O functions on CLKIN/CLKOUT pins */
#define P630_CFG_FOSC_INTOSCCLK	0x0005		/* internal RC oscillator; I/O function on CLKIN */
#define P630_CFG_FOSC_RCIO	0x0006		/* external RC oscillator on CLKIN pin; I/O function on CLKOUT pin */
#define P630_CFG_FOSC_RCCLK	0x0007		/* external RC oscillator on CLKIN; clock out on CLKOUT pin */

#define P630_CFG_WDTE		(1<<3)
#define P630_CFG_PWRTE		(1<<4)		/* active low */
#define P630_CFG_MCLRE		(1<<5)
#define P630_CFG_BODEN		(1<<6)
#define P630_CFG_CP		(1<<7)		/* active low */
#define P630_CFG_CPD		(1<<8)		/* active low */

	if (strcasecmp(s, "FOSC") == 0) {		/* Oscillator Selection bits */
		config_word &= ~0x0007;
		if (strcasecmp(v, "LP") == 0)
			config_word |= P630_CFG_FOSC_LP;
		else if (strcasecmp(v, "XT") == 0)
			config_word |= P630_CFG_FOSC_XT;
		else if (strcasecmp(v, "HS") == 0)
			config_word |= P630_CFG_FOSC_HS;
		else if (strcasecmp(v, "EC") == 0)
			config_word |= P630_CFG_FOSC_EC;
		else if (strcasecmp(v, "INTOSC") == 0 || strcasecmp(v, "INTOSCCLK") == 0)
			config_word |= P630_CFG_FOSC_INTOSCCLK;
		else if (strcasecmp(v, "INTOSCIO") == 0)
			config_word |= P630_CFG_FOSC_INTOSCIO;
		else if (strcasecmp(v, "RC") == 0 || strcasecmp(v, "RCCLK") == 0)
			config_word |= P630_CFG_FOSC_RCCLK;
		else if (strcasecmp(v, "RCIO") == 0)
			config_word |= P630_CFG_FOSC_RCIO;
	else
		fatal("unrecognised FOSC value \"%s\"", v);
	} else if (strcasecmp(s, "WDTE") == 0) {	/* Watchdog Timer Enable bit */
		SET_IF_TRUE(v, P630_CFG_WDTE);
	} else if (strcasecmp(s, "PWRTE") == 0) {	/* Power-up Timer Enable bit */
		SET_IF_FALSE(v, P630_CFG_PWRTE);
	} else if (strcasecmp(s, "MCLRE") == 0) {	/* MCLR Pin Function Select bit */
		SET_IF_TRUE(v, P630_CFG_MCLRE);
	} else if (strcasecmp(s, "BOREN") == 0 || strcasecmp(s, "BODEN") == 0) {	/* Brown-out Reset Selection bits */
		SET_IF_TRUE(v, P630_CFG_BODEN);
	} else if (strcasecmp(s, "CP") == 0) {		/* Program Memory Code Protection bit */
		SET_IF_FALSE(v, P630_CFG_CP);
	} else if (strcasecmp(s, "CPD") == 0) {		/* Data Memory Code Protection bit */
		SET_IF_FALSE(v, P630_CFG_CPD);
	} else {
		fatal("unrecognised config option \"%s\"", s);
	}
}

/* PIC16F84/PIC16F84A */
static void
setconfig_84(const char *s, const char *v)
{
#define P84_CFG_FOSC_LP		0x0000		/* low-power crystal */
#define P84_CFG_FOSC_XT		0x0001		/* crystal/resonator */
#define P84_CFG_FOSC_HS		0x0002		/* high-speed crystal/resonator */
#define P84_CFG_FOSC_RC		0x0003		/* resistor/capacitor */
#define P84_CFG_WDTE		(1<<2)		/* watchdog timer enable */
#define P84_CFG_PWRTE		(1<<3)		/* powerup timer enable */
#define P84_CFG_CP		0x3ff0		/* PIC16F84A */

	if (strcasecmp(s, "FOSC") == 0) {		/* Oscillator Selection bits */
		config_word &= ~0x0003;
		if (strcasecmp(v, "LP") == 0)
			config_word |= P84_CFG_FOSC_LP;
		else if (strcasecmp(v, "XT") == 0)
			config_word |= P84_CFG_FOSC_XT;
		else if (strcasecmp(v, "HS") == 0)
			config_word |= P84_CFG_FOSC_HS;
		else if (strcasecmp(v, "RC") == 0)
			config_word |= P84_CFG_FOSC_RC;
		else
			fatal("unrecognised FOSC value \"%s\"", v);
	} else if (strcasecmp(s, "WDTE") == 0) {	/* Watchdog Timer Enable bit */
		SET_IF_TRUE(v, P84_CFG_WDTE);
	} else if (strcasecmp(s, "PWRTE") == 0) {	/* Power-up Timer Enable bit */
		SET_IF_FALSE(v, P84_CFG_PWRTE);
	} else if (strcasecmp(s, "CP") == 0) {		/* Program Memory Code Protection bit */
		SET_IF_FALSE(v, P84_CFG_CP);
	} else {
		fatal("unrecognised config option \"%s\"", s);
	}
}


/* PIC16F627/PIC16F628A */
static void
setconfig_62x(const char *s, const char *v)
{
#define P62x_CFG_FOSC_LP	0x0000		/* low-power crystal */
#define P62x_CFG_FOSC_XT	0x0001		/* crystal/resonator */
#define P62x_CFG_FOSC_HS	0x0002		/* high-speed crystal/resonator */
#define P62x_CFG_FOSC_EC	0x0003		/* external clock on CLKIN pin, I/O on CLKOUT pin */
#define P62x_CFG_FOSC_INTRCIO	0x0010		/* internal RC oscillator; I/O functions on CLKIN/CLKOUT pins */
#define P62x_CFG_FOSC_INTRCCLK	0x0011		/* internal RC oscillator; I/O function on CLKIN */
#define P62x_CFG_FOSC_ERIO	0x0012		/* external RC oscillator on CLKIN pin; I/O function on CLKOUT pin */
#define P62x_CFG_FOSC_ERCLK	0x0013		/* external RC oscillator on CLKIN; clock out on CLKOUT pin */

#define P62x_CFG_WDTE		(1<<2)		/* watchdog timer enable */
#define P62x_CFG_PWRTE		(1<<3)		/* powerup timer enable */
#define P62x_CFG_MCLRE		(1<<5)		/* memory clear (reset) pin enable */
#define P62x_CFG_BODEN		(1<<6)		/* brown-out reset enable */
#define P62x_CFG_LVP		(1<<7)		/* low-voltage programming enable */
#define P62x_CFG_CPD		(1<<8)		/* data code protection */
#define P62x_CFG_CP		0x3C00

	if (strcasecmp(s, "FOSC") == 0) {		/* Oscillator Selection bits */
		config_word &= ~0x0013;
		if (strcasecmp(v, "LP") == 0)
			config_word |= P62x_CFG_FOSC_LP;
		else if (strcasecmp(v, "XT") == 0)
			config_word |= P62x_CFG_FOSC_XT;
		else if (strcasecmp(v, "HS") == 0)
			config_word |= P62x_CFG_FOSC_HS;
		else if (strcasecmp(v, "EC") == 0)
			config_word |= P62x_CFG_FOSC_EC;
		else if (strcasecmp(v, "INTRC") == 0 || strcasecmp(v, "INTRCCLK") == 0)
			config_word |= P62x_CFG_FOSC_INTRCCLK;
		else if (strcasecmp(v, "ER") == 0 || strcasecmp(v, "ERCLK") == 0)
			config_word |= P62x_CFG_FOSC_ERCLK;
		else if (strcasecmp(v, "EXTRCIO") == 0)
			config_word |= P62x_CFG_FOSC_ERIO;
		else
			fatal("unrecognised FOSC value \"%s\"", v);
	} else if (strcasecmp(s, "WDTE") == 0) {	/* Watchdog Timer Enable bit */
		SET_IF_TRUE(v, P62x_CFG_WDTE);
	} else if (strcasecmp(s, "PWRTE") == 0) {	/* Power-up Timer Enable bit */
		SET_IF_FALSE(v, P62x_CFG_PWRTE);
	} else if (strcasecmp(s, "MCLRE") == 0) {	/* MCLR Pin Function Select bit */
		SET_IF_TRUE(v, P62x_CFG_MCLRE);
	} else if (strcasecmp(s, "BOREN") == 0 || strcasecmp(s, "BODEN") == 0) {	/* Brown-out Reset Selection bits */
		SET_IF_TRUE(v, P62x_CFG_BODEN);
	} else if (strcasecmp(s, "LVP") == 0) {		/* Low-Voltage Programming Enable bit */
		SET_IF_TRUE(v, P62x_CFG_LVP);
	} else if (strcasecmp(s, "CPD") == 0) {		/* Data Memory Code Protection bit */
		SET_IF_FALSE(v, P62x_CFG_CPD);
	} else if (strcasecmp(s, "CP") == 0) {		/* Program Memory Code Protection bit */
		SET_IF_TRUE(v, P62x_CFG_CP);
	} else {
		fatal("unrecognised config option \"%s\"", s);
	}
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

static const struct {
	int id;
	const char* name;
	void (*setconfig)(const char *s, const char *v);
} devices[] = {
	{ DEVICE_PIC16F84, "p16f84", setconfig_84 },
	{ DEVICE_PIC16F84A, "p16f84a", setconfig_84 },
	{ DEVICE_PIC16F84A, "p16f627", setconfig_62x },
	{ DEVICE_PIC16F84A, "p16f628", setconfig_62x },
	{ DEVICE_PIC16F630, "p16f630", setconfig_630 },
	{ DEVICE_PIC16F676, "p16f676", setconfig_630 },
};

#ifndef __TABLE_SIZE
#define __TABLE_SIZE(x)	(sizeof(x)/sizeof((x)[0]))
#endif

static int device = DEVICE_UNDEF;
static void (*setconfig_p)(const char *s, const char *v) = NULL;

void
setdevice(const char *name)
{
	int i;

	for (i = 0; i < (int)__TABLE_SIZE(devices); i++) {
		if (strcasecmp(name, devices[i].name) == 0) {
			device = devices[i].id;
			setconfig_p = devices[i].setconfig;
			break;
		}
	}
	if (device == DEVICE_UNDEF)
		fatal("unrecognised device \"%s\"", name);
}

void
setconfig(const char *s, const char *v)
{
	DPRINTF(("%s = %s\n", s, v));

	if (!setconfig_p)
		fatal("device/processor not specified");
	(*setconfig_p)(s,v);

	printf("setconfig(%s,%s) => 0x%04x\n", s, v, config_word);
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
