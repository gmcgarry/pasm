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

{ 0,	PSEUDOOP_DEVICE,	0,		".device" },
{ 0,	PSEUDOOP_DEFINE,	0,		".def" },
{ 0,	PSEUDOOP_DATA,		1,		".db" },

{ 0,	PSEUDOOP_SEGMENT,	CSEG,		".cseg" },
{ 0,	PSEUDOOP_SEGMENT,	DSEG,		".dseg" },

{ 0,	SHIFTFUNC,		0,		"low" },
{ 0,	SHIFTFUNC,		8,		"high" },
{ 0,	SHIFTFUNC,		0,		"lo8" },
{ 0,	SHIFTFUNC,		8,		"hi8" },
{ 0,	SHIFTFUNC,		16,		"hlo8" },
{ 0,	SHIFTFUNC,		24,		"hhi8" },

{ 0,	REG8,			0,		"r0" },
{ 0,	REG8,			1,		"r1" },
{ 0,	REG8,			2,		"r2" },
{ 0,	REG8,			3,		"r3" },
{ 0,	REG8,			4,		"r4" },
{ 0,	REG8,			5,		"r5" },
{ 0,	REG8,			6,		"r6" },
{ 0,	REG8,			7,		"r7" },
{ 0,	REG8,			8,		"r8" },
{ 0,	REG8,			9,		"r9" },
{ 0,	REG8,			10,		"r10" },
{ 0,	REG8,			11,		"r11" },
{ 0,	REG8,			12,		"r12" },
{ 0,	REG8,			13,		"r13" },
{ 0,	REG8,			14,		"r14" },
{ 0,	REG8,			15,		"r15" },
{ 0,	REG8,			16,		"r16" },
{ 0,	REG8,			17,		"r17" },
{ 0,	REG8,			18,		"r18" },
{ 0,	REG8,			19,		"r19" },
{ 0,	REG8,			20,		"r20" },
{ 0,	REG8,			21,		"r21" },
{ 0,	REG8,			22,		"r22" },
{ 0,	REG8,			23,		"r23" },
{ 0,	REG8,			24,		"r24" },
{ 0,	REG8,			25,		"r25" },
{ 0,	REG8,			26,		"r26" },
{ 0,	REG8,			27,		"r27" },
{ 0,	REG8,			28,		"r28" },
{ 0,	REG8,			29,		"r29" },
{ 0,	REG8,			30,		"r30" },
{ 0,	REG8,			31,		"r31" },
{ 0,	REG16,			ZREG,		"Z" },
{ 0,	REG16,			XREG,		"X" },
{ 0,	REG16,			YREG,		"Y" },

{ 0,	MNEMONIC_ST,		0x0,		"st" },		/* __, Rr   dummy */
#if 0
{ 0,	MNEMONIC_ST,		0x920c,		"st" },		/* X, Rr    1001 001d dddd 1100 */
{ 0,	MNEMONIC_ST,		0x920d,		"st" },		/* X+, Rr   1001 001d dddd 1101 */
{ 0,	MNEMONIC_ST,		0x920e,		"st" },		/* -X, Rr   1001 001d dddd 1110 */
{ 0,	MNEMONIC_ST,		0x8208,		"st" },		/* Y, Rr    1000 001d dddd 1000 */
{ 0,	MNEMONIC_ST,		0x9209,		"st" },		/* Y+, Rr   1001 001d dddd 1001 */
{ 0,	MNEMONIC_ST,		0x920a,		"st" },		/* -Y, Rr   1001 001d dddd 1010 */
{ 0,	MNEMONIC_ST,		0x8200,		"st" },		/* Z, Rr    1000 001d dddd 0000 */
{ 0,	MNEMONIC_ST,		0x9201,		"st" },		/* Z+, Rr   1001 001d dddd 0001 */
{ 0,	MNEMONIC_ST,		0x9202,		"st" },		/* -Z, Rr   1001 001d dddd 0010 */
#endif

{ 0,	MNEMONIC_STS,		0x9200,		"sts" },	/* k, Rr    1001 001d dddd 0000 + 16k */
#if notyet
{ 0,	MNEMONIC_STS_AVR8L,	0xa800,		"sts" },	/* Rd, k    1010 1kkk dddd kkkk */
#endif

{ 0,	MNEMONIC_STD,		0x8200,		"std" },	/* _+q, Rr  dummy */
#if 0
{ 0,	MNEMONIC_STD_Y,		0x8208,		"std" },	/* Y+q, Rr  10q0 qq1r rrrr 1qqq */
{ 0,	MNEMONIC_STD_Z,		0x8200,		"std" },	/* Z+q, Rr  10q0 qq1r rrrr 0qqq */
#endif

{ 0,	MNEMONIC_LD,		0x0,		"ld" },		/* Rd, __   dummy */
#if 0
{ 0,	MNEMONIC_LD,		0x900c,		"ld" },		/* Rd, X    1001 000d dddd 1100 */
{ 0,	MNEMONIC_LD,		0x900d,		"ld" },		/* Rd, X+   1001 000d dddd 1101 */
{ 0,	MNEMONIC_LD,		0x900e,		"ld" },		/* Rd, -X   1001 000d dddd 1110 */
{ 0,	MNEMONIC_LD,		0x8008,		"ld" },		/* Rd, Y    1000 000d dddd 1000 */
{ 0,	MNEMONIC_LD,		0x9009,		"ld" },		/* Rd, Y+   1001 000d dddd 1001 */
{ 0,	MNEMONIC_LD,		0x900a,		"ld" },		/* Rd, -Y   1001 000d dddd 1010 */
{ 0,	MNEMONIC_LD,		0x8000,		"ld" },		/* Rd, Z    1000 000d dddd 0000 */
{ 0,	MNEMONIC_LD,		0x9001,		"ld" },		/* Rd, Z+   1001 000d dddd 0001 */
{ 0,	MNEMONIC_LD,		0x9002,		"ld" },		/* Rd, -Z   1001 000d dddd 0010 */
#endif

{ 0,	MNEMONIC_LDS,		0x9000,		"lds" },	/* Rd, k    1001 000d dddd 0000 + 16k */
#if notyet
{ 0,	MNEMONIC_LDS_AVR8L,	0xa000,		"lds" },	/* Rd, k    1010 0kkk dddd kkkk */
#endif

{ 0,	MNEMONIC_LDD,		0x8000,		"ldd" },	/* Rd, _+q  dummy */
#if 0
{ 0,	MNEMONIC_LDD_Y,		0x8008,		"ldd" },	/* Rd, Y+q  10q0 qq0d dddd 1qqq */
{ 0,	MNEMONIC_LDD_Z,		0x8000,		"ldd" },	/* Rd, Z+q  10q0 qq0d dddd 0qqq */
#endif

{ 0,	MNEMONIC_LPM,		0,		"lpm" },	/* dummy */
{ 0,	MNEMONIC_LPM,		1,		"elpm" },	/* dummy */
#if 0
{ 0,	MNEMONIC_LPM,		0x95c8,		"lpm" },	/*          1001 0101 1100 1000 */
{ 0,	MNEMONIC_LPM,		0x9004,		"lpm" },	/* Rd, Z    1001 000d dddd 0100 */
{ 0,	MNEMONIC_LPM,		0x9005,		"lpm" },	/* Rd, Z+   1001 000d dddd 0101 */
{ 0,	MNEMONIC_LPM,		0x95d8,		"elpm" },	/*          1001 0101 1101 1000 */
{ 0,	MNEMONIC_LPM,		0x9006,		"elpm" },	/* Rd, Z    1001 000d dddd 0110 */
{ 0,	MNEMONIC_LPM,		0x9007,		"elpm" },	/* Rd, Z+   1001 000d dddd 0111 */
#endif

{ 0,	BASICOP,		0x0000,		"nop" },	/*          0000 0000 0000 0000 */
{ 0,	BASICOP,		0x9408,		"sec" },	/*          1001 0100 0000 1000 */
{ 0,	BASICOP,		0x9488,		"clc" },	/*          1001 0100 1000 1000 */
{ 0,	BASICOP,		0x9428,		"sen" },	/*          1001 0100 0010 1000 */
{ 0,	BASICOP,		0x94a8,		"cln" },	/*          1001 0100 1010 1000 */
{ 0,	BASICOP,		0x9418,		"sez" },	/*          1001 0100 0001 1000 */
{ 0,	BASICOP,		0x9498,		"clz" },	/*          1001 0100 1001 1000 */
{ 0,	BASICOP,		0x9478,		"sei" },	/*          1001 0100 0111 1000 */
{ 0,	BASICOP,		0x94f8,		"cli" },	/*          1001 0100 1111 1000 */
{ 0,	BASICOP,		0x9448,		"ses" },	/*          1001 0100 0100 1000 */
{ 0,	BASICOP,		0x94c8,		"cls" },	/*          1001 0100 1100 1000 */
{ 0,	BASICOP,		0x9438,		"sev" },	/*          1001 0100 0011 1000 */
{ 0,	BASICOP,		0x94b8,		"clv" },	/*          1001 0100 1011 1000 */
{ 0,	BASICOP,		0x9468,		"set" },	/*          1001 0100 0110 1000 */
{ 0,	BASICOP,		0x94e8,		"clt" },	/*          1001 0100 1110 1000 */
{ 0,	BASICOP,		0x9458,		"seh" },	/*          1001 0100 0101 1000 */
{ 0,	BASICOP,		0x94d8,		"clh" },	/*          1001 0100 1101 1000 */
{ 0,	BASICOP,		0x9588,		"sleep" },	/*          1001 0101 1000 1000 */
{ 0,	BASICOP,		0x95a8,		"wdr" },	/*          1001 0101 1010 1000 */
{ 0,	BASICOP,		0x9409,		"ijmp" },	/*          1001 0100 0000 1001 */
{ 0,	BASICOP,		0x9509,		"icall" },	/*          1001 0101 0000 1001 */
{ 0,	BASICOP,		0x9419,		"eijmp" },	/*          1001 0100 0001 1001 */
{ 0,	BASICOP,		0x9519,		"eicall"},	/*          1001 0101 0001 1001 */
{ 0,	BASICOP,		0x9508,		"ret" },	/*          1001 0101 0000 1000 */
{ 0,	BASICOP,		0x9518,		"reti" },	/*          1001 0101 0001 1000 */
{ 0,	BASICOP,		0x95e8,		"spm" },	/*          1001 0101 1110 1000 */
{ 0,	BASICOP,		0x95f8,		"espm" },	/*          1001 0101 1111 1000 */
{ 0,	BASICOP,		0x9598,		"break" },	/*          1001 0101 1001 1000 */

{ 0,	BRANCHOP,		0xf001,		"breq" },	/* k        1111 00kk kkkk k001 */ /* equal */
{ 0,	BRANCHOP,		0xf401,		"brne" },	/* k        1111 01kk kkkk k001 */ /* not equal */
{ 0,	BRANCHOP,		0xf000,		"brcs" },	/* k        1111 00kk kkkk k000 */ /* carry cleared */
{ 0,	BRANCHOP,		0xf400,		"brcc" },	/* k        1111 01kk kkkk k000 */ /* carry set */
{ 0,	BRANCHOP,		0xf400,		"brsh" },	/* k        1111 01kk kkkk k000 */ /* same or higher */
{ 0,	BRANCHOP,		0xf000,		"brlo" },	/* k        1111 00kk kkkk k000 */ /* lower */
{ 0,	BRANCHOP,		0xf002,		"brmi" },	/* k        1111 00kk kkkk k010 */ /* minus */
{ 0,	BRANCHOP,		0xf402,		"brpl" },	/* k        1111 01kk kkkk k010 */ /* plus */
{ 0,	BRANCHOP,		0xf404,		"brge" },	/* k        1111 01kk kkkk k100 */ /* greater or equal */
{ 0,	BRANCHOP,		0xf004,		"brlt" },	/* k        1111 00kk kkkk k100 */ /* less than */
{ 0,	BRANCHOP,		0xf005,		"brhs" },	/* k        1111 00kk kkkk k101 */ /* half carry set */
{ 0,	BRANCHOP,		0xf405,		"brhc" },	/* k        1111 01kk kkkk k101 */ /* half carry clear */
{ 0,	BRANCHOP,		0xf006,		"brts" },	/* k        1111 00kk kkkk k110 */ /* t flag set */
{ 0,	BRANCHOP,		0xf406,		"brtc" },	/* k        1111 01kk kkkk k110 */ /* t flag clear */
{ 0,	BRANCHOP,		0xf003,		"brvs" },	/* k        1111 00kk kkkk k011 */ /* overflow set */
{ 0,	BRANCHOP,		0xf403,		"brvc" },	/* k        1111 01kk kkkk k011 */ /* overflow clear */
{ 0,	BRANCHOP,		0xf007,		"brie" },	/* k        1111 00kk kkkk k111 */ /* interrupt enabled */
{ 0,	BRANCHOP,		0xf407,		"brid" },	/* k        1111 01kk kkkk k111 */ /* interrupt disabled */

{ 0,	BRANCHOP_SREG,		0xf000,		"brbs" },	/* s, k     1111 00kk kkkk ksss */ /* bit set in SREG */
{ 0,	BRANCHOP_SREG,		0xf400,		"brbc" },	/* s, k     1111 01kk kkkk ksss */ /* bit clear in SREG */

{ 0,	ONEOP,			0x9400,		"com" },	/* Rd       1001 010d dddd 0000 */
{ 0,	ONEOP,			0x9401,		"neg" },	/* Rd       1001 010d dddd 0001 */
{ 0,	ONEOP,			0x9403,		"inc" },	/* Rd       1001 010d dddd 0011 */
{ 0,	ONEOP,			0x940a,		"dec" },	/* Rd       1001 010d dddd 1010 */
{ 0,	ONEOP,			0x9406,		"lsr" },	/* Rd       1001 010d dddd 0110 */
{ 0,	ONEOP,			0x9407,		"ror" },	/* Rd       1001 010d dddd 0111 */
{ 0,	ONEOP,			0x9405,		"asr" },	/* Rd       1001 010d dddd 0101 */
{ 0,	ONEOP,			0x9402,		"swap" },	/* Rd       1001 010d dddd 0010 */
{ 0,	ONEOP,			0x900f,		"pop" },	/* Rd       1001 000d dddd 1111 */
{ 0,	ONEOP,			0x920f,		"push" },	/* Rr       1001 001r rrrr 1111 */

{ 0,	ONEOPI,			0x5000,		"subi" },	/* Rd, K    0101 KKKK dddd KKKK */
{ 0,	ONEOPI,			0x4000,		"sbci" },	/* Rd, K    0100 KKKK dddd KKKK */
{ 0,	ONEOPI,			0x7000,		"andi" },	/* Rd, K    0111 KKKK dddd KKKK */
{ 0,	ONEOPI,			0x6000,		"ori" },	/* Rd, K    0110 KKKK dddd KKKK */
{ 0,	ONEOPI,			0x6000,		"sbr" },	/* Rd, K    0110 KKKK dddd KKKK */
{ 0,	ONEOPI,			0x3000,		"cpi" },	/* Rd, K    0011 KKKK dddd KKKK */
{ 0,	ONEOPI,			0xe000,		"ldi" },	/* Rd, K    1110 KKKK dddd KKKK */

{ 0,	TWOOP,			0xc00,		"add" },	/* Rd, Rr   0000 11rd dddd rrrr */
{ 0,	TWOOP,			0x1c00,		"adc" },	/* Rd, Rr   0001 11rd dddd rrrr */
{ 0,	TWOOP,			0x1800,		"sub" },	/* Rd, Rr   0001 10rd dddd rrrr */
{ 0,	TWOOP,			0x800,		"sbc" },	/* Rd, Rr   0000 10rd dddd rrrr */
{ 0,	TWOOP,			0x2000,		"and" },	/* Rd, Rr   0010 00rd dddd rrrr */
{ 0,	TWOOP,			0x2800,		"or" },		/* Rd, Rr   0010 10rd dddd rrrr */
{ 0,	TWOOP,			0x2400,		"eor" },	/* Rd, Rr   0010 01rd dddd rrrr */
{ 0,	TWOOP,			0x1400,		"cp" },		/* Rd, Rr   0001 01rd dddd rrrr */
{ 0,	TWOOP,			0x400,		"cpc" },	/* Rd, Rr   0000 01rd dddd rrrr */
{ 0,	TWOOP,			0x1000,		"cpse" },	/* Rd, Rr   0001 00rd dddd rrrr */
{ 0,	TWOOP,			0x2c00,		"mov" },	/* Rd, Rr   0010 11rd dddd rrrr */
{ 0,	TWOOP,			0x9c00,		"mul" },	/* Rd, Rr   1001 11rd dddd rrrr */

{ 0,	SKIPBITOP,		0xfc00,		"sbrc" },	/* Rr, b    1111 110r rrrr 0bbb */
{ 0,	SKIPBITOP,		0xfe00,		"sbrs" },	/* Rr, b    1111 111r rrrr 0bbb */

{ 0,	MNEMONIC_RJMP,		0xc000,		"rjmp" },	/* k        1100 kkkk kkkk kkkk */
{ 0,	MNEMONIC_RJMP,		0xd000,		"rcall" },	/* k        1101 kkkk kkkk kkkk */

{ 0,	MNEMONIC_JMP,		0x940c,		"jmp" },	/* k        1001 010k kkkk 110k + 16k */
{ 0,	MNEMONIC_JMP,		0x940e,		"call" },	/* k        1001 010k kkkk 111k + 16k */

{ 0,	MNEMONIC_IN,		0xb000,		"in" },		/* Rd, P    1011 0PPd dddd PPPP */
{ 0,	MNEMONIC_OUT,		0xb800,		"out" },	/* P, Rr    1011 1PPr rrrr PPPP */

{ 0,	TWOOP_1,		0x2400,		"clr" },	/* Rd       0010 01dd dddd dddd */ /* eor alias */
{ 0,	TWOOP_1,		0x2000,		"tst" },	/* Rd       0010 00dd dddd dddd */ /* and alias */
{ 0,	TWOOP_1,		0xc00,		"lsl" },	/* Rd       0000 11dd dddd dddd */ /* add alias */
{ 0,	TWOOP_1,		0x1c00,		"rol" },	/* Rd       0001 11dd dddd dddd */ /* adc alias */

{ 0,	MNEMONIC_SER,		0xef0f,		"ser" },	/* Rd       1110 1111 dddd 1111 */ /* ldi alias */
{ 0,	MNEMONIC_CBR,		0x7000,		"cbr" },	/* Rd, K    0111 KKKK dddd KKKK ~K */

/* non-core instructions */
{ 0,	MNEMONIC_MOVW,		0x100,		"movw" },	/* Rd, Rr   0000 0001 dddd rrrr */
{ 0,	MNEMONIC_OPIW,		0x9600,		"adiw" },	/* Rd, K    1001 0110 KKdd KKKK */
{ 0,	MNEMONIC_OPIW,		0x9700,		"sbiw" },	/* Rd, K    1001 0111 KKdd KKKK */

{ 0,	MNEMONIC_MULS,		0x200,		"muls" },	/* Rd, Rr   0000 0010 dddd rrrr */
{ 0,	MNEMONIC_FMUL,		0x300,		"mulsu" },	/* Rd, Rr   0000 0011 0ddd 0rrr */
{ 0,	MNEMONIC_FMUL,		0x308,		"fmul" },	/* Rd, Rr   0000 0011 0ddd 1rrr */
{ 0,	MNEMONIC_FMUL,		0x380,		"fmuls" },	/* Rd, Rr   0000 0011 1ddd 0rrr */
{ 0,	MNEMONIC_FMUL,		0x388,		"fmulsu"},	/* Rd, Rr   0000 0011 1ddd 1rrr */

{ 0,	BITSET,			0x9408,		"bset" },	/* s        1001 0100 0sss 1000 */
{ 0,	BITSET,			0x9488,		"bclr" },	/* s        1001 0100 1sss 1000 */
{ 0,	BITLOAD,		0xfa00,		"bst" },	/* Rr, b    1111 101d dddd 0bbb */
{ 0,	BITLOAD,		0xf800,		"bld" },	/* Rd, b    1111 100d dddd 0bbb */

{ 0,	IOBITSET,		0x9900,		"sbic" },	/* P, b     1001 1001 PPPP Pbbb */
{ 0,	IOBITSET,		0x9b00,		"sbis" },	/* P, b     1001 1011 PPPP Pbbb */
{ 0,	IOBITSET,		0x9a00,		"sbi" },	/* P, b     1001 1010 PPPP Pbbb */
{ 0,	IOBITSET,		0x9800,		"cbi" },	/* P, b     1001 1000 PPPP Pbbb */
