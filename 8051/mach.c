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

item_t cseg = { 0, S_UND, 0, ".cseg" };
item_t dseg = { 0, S_UND, 0, ".dseg" };

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
		item_insert(&dseg, H_GLOBAL+hash(dseg.i_name));
		unresolved++;
	}
	newsect(&cseg, 0, NULL);
}

void
machfinish(int pass)
{
}

struct mode mode;

void
emitop(int opc)
{
	unsigned int newop = opc | get_ov(mode);
	emit1(newop);
	if (get_sz(mode) > 0)
		emit1(get_b1(mode));
	if (get_sz(mode) > 1)
		emit1(get_b2(mode));
	if (get_sz(mode) > 2)
		emit1(get_b3(mode));
}

void
movop(int add)
{
	static unsigned char opcodes[] = { 0xe8, 0xe5, 0xe6, 0x74, 0xf5, 0x75, 0xf8, 0xa8, 0x78, 0x88, 0x85, 0x86, 0xf6, 0xa6, 0x76, 0x90, 0xa2, 0x92 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
anlop(int add)
{
	static unsigned char opcodes[] = { 0x58, 0x55, 0x56, 0x54, 0x52, 0x53, 0x82, 0xb0 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
orlop(int add)
{
	static unsigned char opcodes[] = { 0x48, 0x45, 0x46, 0x44, 0x42, 0x43, 0x72, 0xa0 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
addop(int add)
{
	static unsigned char opcodes[] = { 0x28, 0x25, 0x26, 0x24 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
addcop(int add)
{
	static unsigned char opcodes[] = { 0x38, 0x35, 0x36, 0x34 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
cjneop(int add)
{
	static unsigned char opcodes[] = { 0xb5, 0xb4, 0xb8, 0xb6 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
decop(int add)
{
	static unsigned char opcodes[] = { 0x14, 0x18, 0x15, 0x16 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
subbop(int add)
{
	static unsigned char opcodes[] = { 0x98, 0x95, 0x96, 0x94 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
movxop(int add)
{
	static unsigned char opcodes[] = { 0xe2, 0xe3, 0xe0, 0xf2, 0xf3, 0xf0 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}
	
void
xrlop(int add)
{
	static unsigned char opcodes[] =  { 0x68, 0x65, 0x66, 0x64, 0x62, 0x63 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
incop(int add)
{
	static unsigned char opcodes[] = { 0x04, 0x08, 0x05, 0x06, 0xa3 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
xchop(int add)
{
	static unsigned char opcodes[] = { 0xc8, 0xc5, 0xc6 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
djnzop(int add)
{
	static unsigned char opcodes[] = { 0xd8, 0xd5 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
clrop(int add)
{
	static unsigned char opcodes[] = { 0xe4, 0xc3, 0xc2 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
cplop(int add)
{
	static unsigned char opcodes[] = { 0xf4, 0xb3, 0xb2 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}

void
setbop(int add)
{
	static unsigned char opcodes[] = { 0xd3, 0xd2 };
	unsigned int newop = opcodes[ get_md(mode) + add ];
	emitop(newop);
}
