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

operation: BASICOP				{ emit2($1); }
	| BRANCHOP expr				{ branch($1, $2); }
	| ONEOP reg8				{ emit2($1 | ($2 << 4)); }
	| ONEOPI reg8 ',' imm8			{ emit2($1 | (($2 & 0x0f) << 4) | (($4 & 0xf0) << 4) | ($4 & 0x0f)); }
	| TWOOP reg8 ',' reg8			{ emit2($1 | ($2 << 4) | (($4 & 0x0f) << 0) | (($4 & 0x10) << 5)); }
	| BITOP reg8 ',' imm3			{ emit2($1 | ($2 << 4) | $4); }

	| MNEMONIC_RJMP expr			{ reljump($1, $2); }
	| MNEMONIC_JMP expr			{ absjump($1, $2); }

	| MNEMONIC_IN reg8 ',' port		{ emit2($1 | ($2 << 4) | ($4 & 0x0f) | (($4 & 0x30) << 5)); }
        | MNEMONIC_OUT port ',' reg8		{ emit2($1 | ($4 << 4) | ($2 & 0x0f) | (($2 & 0x30) << 5)); }

	/* non-core instructions */
        | MNEMONIC_ADIW regw ',' imm6
        | MNEMONIC_SBIW regw ',' imm6		{ emit2($1 | ($2 << 4) | ($4 & 0x0f) | (($4 & 0x30) << 2)); }
	| MNEMONIC_MOVW reg8 ',' reg8		{ if (($2 | $4) & 1) serror("invalid register"); emit2($1 | (($2 & 0x1e) << 3) | ($4 >> 1)); }

	| MNEMONIC_LPM_Z reg8 ',' REG16		{ if ($4 != ZREG) serror("bad 16-bit register"); emit2($1 | ($2 << 4)); }
	| MNEMONIC_LPM_ZP reg8 ',' REG16 '+'	{ if ($4 != ZREG) serror("bad 16-bit register"); emit2($1 | ($2 << 4)); }

	| MNEMONIC_ST REG16 ',' reg8		{ emit2(0x8200 | ($2 << 2) | ($4 << 4) | (($2 & 1) << 12)); }
	| MNEMONIC_ST REG16 '+' ',' reg8	{ emit2(0x9201 | ($2 << 2) | ($5 << 4)); }
	| MNEMONIC_ST '-' REG16 ',' reg8	{ emit2(0x9202 | ($3 << 2) | ($5 << 4)); }

	| MNEMONIC_LD reg8 ',' REG16		{ emit2(0x8000 | ($4 << 2) | ($2 << 4) | (($4 & 1) << 12)); }
	| MNEMONIC_LD reg8 ',' REG16 '+'	{ emit2(0x9001 | ($4 << 2) | ($2 << 4)); }
	| MNEMONIC_LD reg8 ',' '-' REG16 	{ emit2(0x9002 | ($5 << 2) | ($2 << 4)); }

	/* aliases */
        | MNEMONIC_CLR reg8			{ emit2($1 | ($2 << 4) | (($2 & 0x0f) << 0) | (($2 & 0x10) << 5)); }
        | MNEMONIC_TST reg8			{ emit2($1 | ($2 << 4) | (($2 & 0x0f) << 0) | (($2 & 0x10) << 5)); }
        | MNEMONIC_SER reg8			{ emit2($1 | ($2 << 4)); }
        | MNEMONIC_LSL reg8 			{ emit2($1 | ($2 << 4) | (($2 & 0x0f) << 0) | (($2 & 0x10) << 5)); }
        | MNEMONIC_ROL reg8           		{ emit2($1 | ($2 << 4) | (($2 & 0x0f) << 0) | (($2 & 0x10) << 5)); }

	| DIRECTIVE_DEVICE IDENT		{ setdevice($2->i_name); }
	| DIRECTIVE_DEFINE IDENT '=' REG8	{ $2->i_type = S_ABS; $2->i_valu = $4; }
	| DIRECTIVE_SEGMENT			{
							static const char *Names[] = { ".text", ".data" };
							if ($1 >= (int)(sizeof(Names) / sizeof(Names[0]))) fatal("internal error, bad segment");
							struct item *ip = item_search(Names[$1]);
							if (!ip) {
								ip = item_alloc(S_UND);
								ip->i_name = Names[$1];
								item_insert(ip, H_LOCAL + (hashindex % H_SIZE));
								unresolved++;
							}
							assert(ip);
							newsect(ip, 0, NULL);
						}
        ;

port:	expr					{ $$ = $1.val; if ($$ < -64|| $$ > 64) serror("6-bit constant out of range"); }
	;

imm3:	expr					{ $$ = $1.val; if ($$ < 0 || $$ > 7) serror("3-bit constant out of range"); }
	;

imm6:	expr					{ $$ = $1.val; if ($$ < -63 || $$ > 63) serror("8-bit constant out of range"); }
	;

imm8:	expr					{ $$ = $1.val; if ($$ < -255 || $$ > 255) serror("8-bit constant out of range"); }
	| SHIFTFUNC '(' expr ')'		{ $$ = ($3.val >> $1) & 0xff; }
	;

reg8:	REG8					{ if ($1 < 0 && $1 > 31) serror("bad register"); $$ = $1; }
	| IDENT					{ if (($1->i_type & S_SCTMASK) != S_ABS) serror("bad register alias"); $$ = $1->i_valu; }
	;

regw:	REG8					{ if ($1 != 24 && $1 != 26 && $1 != 28 && $1 != 30) serror("bad register"); $$ = ($1 - 24) / 2; }
	| IDENT					{ if (($1->i_type & S_SCTMASK) != S_ABS) serror("bad register alias"); $$ = ($1->i_valu - 24) / 2; }
	;
