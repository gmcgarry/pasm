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

#define fitb(x)		fitx(x,8)
#define fitw(x)		fitx(x,16)

operation
	: PSEUDOOP_DEVICE IDENT		{ setdevice($2->i_name); }

	| RM reg			{ emit1($1); emit1($2); }
	| RM '@' reg			{ emit1($1|0x01); emit1($3); }

	| RMW REG ',' imm8		{ emit1($1|0x06); emit1($2); emit1($4); }
	| RMW REG ',' REG		{ emit1($1|0x02); emit1($2<<4|$4); }
	| RMW REG ',' '@' REG		{ emit1($1|0x03); emit1($2<<4|$5); }
	| RMW REG ',' direct		{ emit1($1|0x04); emit1($4); emit1($2); }
	| RMW REG ',' '@' direct	{ emit1($1|0x05); emit1($5); emit1($2); }
	| RMW direct ',' reg		{ emit1($1|0x04); emit1($4); emit1($2); }
	| RMW direct ',' '@' reg	{ emit1($1|0x05); emit1($5); emit1($2); }
	| RMW direct ',' imm8		{ emit1($1|0x06); emit1($2); emit1($4); }

	| LD REG ',' imm8		{ emit1($2<<4|0x0C); emit1($4); }
	| LD REG ',' reg		{ emit1($2<<4|0x08); emit1($4); }
	| LD REG ',' '@' REG		{ emit1(0xC7); emit1($1<<4|$5); }
	| LD REG ',' '@' direct		{ emit1(0xE5); emit1($5); emit1($2); }
	| LD REG ',' imm8 '[' REG ']'	{ emit1(0x87); emit1($2<<4|$6); emit1($4); }

	| LD direct ',' imm8		{ emit1(0xE6); emit1($2); emit1($4); }
	| LD direct ',' REG		{ emit1($4<<4|0x09); emit1($2); }
	| LD direct ',' direct		{ emit1(0xE4); emit1($4); emit1($2); }
	| LD direct ',' '@' reg		{ emit1(0xE5); emit1($5); emit1($2); }

	| LD '@' REG ',' imm8		{ emit1(0xD6); emit1($3); emit1($5); }
	| LD '@' REG ',' REG		{ emit1(0xD7); emit1($3<<4|$5); }
	| LD '@' REG ',' direct		{ emit1(0xF5); emit1($3); emit1($5); }

	| LD '@' direct ',' imm8	{ emit1(0xD6); emit1($3); emit1($5); }
	| LD '@' direct ',' reg		{ emit1(0xF5); emit1($3); emit1($5); }

	| LD imm8 '[' REG ']' ',' REG	{ emit1(0x97); emit1($7<<4|$4); emit1($2); }

	| LDC REG ',' '@' REGW		{ emit1(0xC3); emit1($2<<4|$5); }
	| LDC REG ',' imm '[' REGW ']'	{
						if (fitb($4)) {
							emit1(0xE7); emit1($1<<4|$6); emit1($4);
						} else {
							emit1(0xA7); emit1($1<<4|$6); emit2($4);
						}
					}
	| LDC REG ',' directw		{ emit1(0xA7); emit1($2<<4|$1); emit2($4); }
	| LDC directw ',' REG		{ emit1(0xB7); emit1($4<<4|$1); emit2($2); }
	| LDC '@' REGW ',' REG		{ emit1(0xD3); emit1($5<<4|$3); }
	| LDC imm '[' REGW ']' ',' REG	{
						if (fitb($1)) {
							emit1(0xE7); emit1($4<<4|$7); emit1($2);
						} else {
							emit1(0xA7); emit1($4<<4|$7); emit2($2);
						}
					}

	| LDCI REG ',' REGW		{ emit1($1); emit1($2<<4|$4); }

	| IMPL				{ emit1($1); }

	| INC REG			{ emit1($2<<4|0x0E); }
	| INC direct			{ emit1(0x20); emit1($2); }
	| INC '@' reg			{ emit1(0x21); emit1($3); }

#ifndef SAM88RC
	| INCW REG16			{ emit1($1|0x00); emit1($3); }
	| INCW '@' reg			{ emit1($1|0x01); emit1($3); }
#endif

#ifndef SAM88RC
	| SRP imm8			{ emit1($1); emit1($2); }
#endif

	| CALL expr			{ emit1($1|0x06); emit2($2.val); }
	| CALL '@' REGW			{ emit1($1|0x04); emit1($3); }

	| BRANCH optcond address	{ emit1($2<<4|$1); emit2($3); }
	| BRANCH '@' REGW		{ emit1(0x30); emit1($3); }

	| RBRANCH optcond offset	{ emit1($2<<4|$1); emit1($3); }
	;

reg	: REG		{ $$ = $1; }
	| direct	{ $$ = $1; }
	;

direct	: absexp	{ $$ = $1; fit(fitb($1)); }
	| SFR		{ $$ = $1; fit(fitb($1)); }
	;

directw	: absexp	{ $$ = $1; fit(fitw($1)); }
	;

imm8	: '#' absexp	{ $$ = $2; fit(fitb($2)); }
	;

imm	: '#' absexp	{ $$ = $2; }
	;

address	: expr		{ $$ = $1.val; }
	;

offset	: expr		{ $$ = $1.val - DOT; fit(fitw($$+32768)); }
	;

optcond	:		{ $$ = 0; }
	| COND ','	{ $$ = $1; }
	;
