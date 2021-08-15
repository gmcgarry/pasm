/*-
 * Copyright (c) 1990 Ken Stauffer (University of Calgary)
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

extern int hash(const char *);

static item_t cseg = { 0, 0, S_UND, ".cseg" };

void
mflag(const char* flag)
{
}

void
machstart(int pass)
{
	if (pass == PASS_1)
		item_insert(&cseg, hash(cseg.i_name));
	newsect(&cseg, 0, NULL);
}

void
machfinish(int pass)
{
}

struct mode mode;

void
makeop(int opc, struct mode *m, int add)
{
	unsigned int newop;

	if (m == NULL) {
		/* emit1(op->bytes[0+add]); */
		emit1(opc);
		return;
	}

#if 0
	if (get_md(*m) != 0 || add != 0)
		fatal("not implemented");
#endif

#if 0
	newop = op->bytes[ get_md(*m) + add ] | get_ov(*m);
#else
	newop = opc | get_ov(*m);
#endif
	emit1(newop);
	if (get_sz(*m) > 0)
		emit1(get_b1(*m));
	if (get_sz(*m) > 1)
		emit1(get_b2(*m));
}

#if 0

target: accumulator
md 0: reg operand
md 1: memory operand, address in following byte
md 2: indirect register operand
md 3: immedia operand in following byte


static unsigned char mov[]=     { 0xe8, 0xe5, 0xe6, 0x74,  0xf5, 0x75, 0xf8, 0xa8,  0x78, 0x88, 0x85, 0x86,  0xf6, 0xa6, 0x76, 0x90,  0xa2, 0x92 };
static unsigned char anl[]=     { 0x58, 0x55, 0x56, 0x54,  0x52, 0x53, 0x82, 0xb0 };
static unsigned char orl[]=     { 0x48, 0x45, 0x46, 0x44,  0x42, 0x43, 0x72, 0xa0 };

static unsigned char add[]=     { 0x28, 0x25, 0x26, 0x24 };
static unsigned char addc[]=    { 0x38, 0x35, 0x36, 0x34 };
static unsigned char cjne[]=    { 0xb5, 0xb4, 0xb8, 0xb6 };
static unsigned char dec[]=     { 0x14, 0x18, 0x15, 0x16 };
static unsigned char subb[]=    { 0x98, 0x95, 0x96, 0x94 };

static unsigned char movx[]=    { 0xe2, 0xe3, 0xe0, 0xf2, 0xf3, 0xf0 };
static unsigned char xrl[]=     { 0x68, 0x65, 0x66, 0x64, 0x62, 0x63 };

static unsigned char inc[]=     { 0x04, 0x08, 0x05, 0x06, 0xa3 };

static unsigned char xch[]=     { 0xc8, 0xc5, 0xc6 };

static unsigned char djnz[]=    { 0xd8, 0xd5 };

# single_op2
static unsigned char clr[]=     { 0xe4, 0xc3, 0xc2 };	1110 0100 , 1100 0011 , 1100 0010
static unsigned char cpl[]=     { 0xf4, 0xb3, 0xb2 };	1111 0100 , 1011 0011 , 1011 0010
static unsigned char setb[]=    { 0x00, 0xd3, 0xd2 };

#endif
