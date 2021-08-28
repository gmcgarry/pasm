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

{ 0,	PSEUDOOP_LITPOS,	0,		".literal_position" },
{ 0,	PSEUDOOP_LITERAL,	0,		".literal" },

{ 0,	REG,			0,		"a0" },
{ 0,	REG,			1,		"a1" }, /* aka SP */
{ 0,	REG,			1,		"sp" },
{ 0,	REG,			2,		"a2" },
{ 0,	REG,			3,		"a3" },
{ 0,	REG,			4,		"a4" },
{ 0,	REG,			5,		"a5" },
{ 0,	REG,			6,		"a6" },
{ 0,	REG,			7,		"a7" },
{ 0,	REG,			8,		"a8" },
{ 0,	REG,			9,		"a9" },
{ 0,	REG,			10,		"a10" },
{ 0,	REG,			11,		"a11" },
{ 0,	REG,			12,		"a12" },
{ 0,	REG,			13,		"a13" },
{ 0,	REG,			14,		"a14" },
{ 0,	REG,			15,		"a15" },

{ 0,	FORMAT_RRR,		0x000000,	"ill" },	/* 000000	-		*/

/*
 * base architecture
 */
{ 0,	FORMAT_RRR_RST,		0x100000,	"and" },	/* 10rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0x200000,	"or" },		/* 20rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0x300000,	"xor" },	/* 30rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0x800000,	"add" },	/* 80rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0xC00000,	"sub" },	/* C0rst0	ar,as,at	*/

{ 0,	FORMAT_RRR_RS,		0xA10000,	"sll" },	/* A1rs00	ar,as		*/
{ 0,	FORMAT_RRR_RT,		0x910000,	"srl" },	/* 91r0t0	ar,at		*/
{ 0,	FORMAT_RRR_RT,		0xB10000,	"sra" },	/* B1r0t0	ar,at		*/

{ 0,	FORMAT_RRR_RSI5,	0x010000,	"slli" },	/* 01rsa0	ar,as,(1..31)	*/
{ 0,	FORMAT_RRR_RTI4,	0x410000,	"srli" },	/* 41rat0	ar,at,(0..15)	*/
{ 0,	FORMAT_RRR_RTI5,	0x210000,	"srai" },	/* 21rat0	ar,at,(0..31)	*/
{ 0,	FORMAT_RRR_RST,		0x810000,	"src" },	/* 81rst0	ar,as,at	*/

{ 0,	FORMAT_RRR_S,		0x400000,	"ssr" },	/* 400s00	as		*/
{ 0,	FORMAT_RRR_S,		0x401000,	"ssl" },	/* 401s00	as		*/
{ 0,	FORMAT_RRR_S,		0x402000,	"ssa8l" },	/* 402s00	as		*/
{ 0,	FORMAT_RRR_S,		0x403000,	"ssa8b" },	/* 403s00	as		*/
{ 0,	FORMAT_RRR_A,		0x404000,	"ssai" },	/* 404a00	(0..31)		*/

{ 0,	FORMAT_RRR_STmm,	0x040000,	"extui" },	/* o4rst0	ar,at,0..31,1..16 */

/*
 * addx option
 */
{ 0,	FORMAT_RRR_RST,		0x900000,	"addx2" },	/* 90rst0 	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0xA00000,	"addx4" },	/* A0rst0	ar,as,at	*/	
{ 0,	FORMAT_RRR_RST,		0xB00000,	"addx8" },	/* B0rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0xD00000,	"subx2" },	/* D0rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0xE00000,	"subx4" },	/* E0rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0xF00000,	"subx8" },	/* F0rst0	ar,as,at	*/

/*
 * min/max option
 */
{ 0,	FORMAT_RRR_RST,		0x430000,	"min" },	/* 43rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0x530000,	"max" },	/* 53rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0x630000,	"minu" },	/* 63rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0x730000,	"maxu" },	/* 73rst0	ar,as,at	*/

/*
 * mul32 option
 */
{ 0,	FORMAT_RRR_RST,		0x820000,	"mull" },	/* 82rst0	ar,as,at	*/

/*
 * mul16 option
 */
{ 0,	FORMAT_RRR_RST,		0xC10000,	"mul16u" },	/* C1rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0xD10000,	"mul16s" },	/* D1rst0	ar,as,at	*/

/*
 * mul32 high option
 */
{ 0,	FORMAT_RRR_RST,		0xA20000,	"muluh" },	/* A2rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0xB20000,	"mulsh" },	/* B2rst0	ar,as,at	*/

/*
 * div32 option
 */
{ 0,	FORMAT_RRR_RST,		0xC20000,	"quou" },	/* C2rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0xD20000,	"quos" },	/* D2rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0xE20000,	"remu" },	/* E2rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0xF20000,	"rems" },	/* F2rst0	ar,as,at	*/

/*
 * abs option
 */
{ 0,	FORMAT_RRR_RT,		0x600100,	"abs" },	/* 60r1t0 	ar,at		*/

{ 0,	FORMAT_RRR_RT,		0x600000,	"neg" },	/* 60r0t0	ar,at		*/

{ 0,	FORMAT_RRR_RST,		0x0A0000,	"add.s" },	/* 0Arst0	fr,fs,ft	*/
{ 0,	FORMAT_RRR_RST,		0x1A0000,	"sub.s" },	/* 1Arst0	fr,fs,ft	*/
{ 0,	FORMAT_RRR_RST,		0x2A0000,	"mul.s" },	/* 2Arst0	fr,fs,ft	*/
{ 0,	FORMAT_RRR_RST,		0x4A0000,	"madd.s" },	/* 4Arst0	fr,fs,ft	*/
{ 0,	FORMAT_RRR_RST,		0x5A0000,	"msub.s" },	/* 5Arst0	fr,fs,ft	*/

{ 0,	FORMAT_RRR_RS,		0xFA0000,	"mov.s" },	/* FArs00	fr,fs		*/
{ 0,	FORMAT_RRR_RS,		0xFA0010,	"abs.s" },	/* FArs10	fr,fs		*/
{ 0,	FORMAT_RRR_RS,		0xFA0060,	"neg.s" },	/* FArs60	fr,fs		*/ 

{ 0,	FORMAT_RRR_RST,		0x020000,	"andb" },	/* 02rst0	br,bs,bt	*/
{ 0,	FORMAT_RRR_RST,		0x120000,	"andbc" },	/* 12rst0	br,bs,bt	*/
{ 0,	FORMAT_RRR_RST,		0x220000,	"orb" },	/* 22rst0	br,bs,bt	*/
{ 0,	FORMAT_RRR_RST,		0x320000,	"orbc" },	/* 32rst0	br,bs,bt	*/
{ 0,	FORMAT_RRR_RST,		0x420000,	"xorb" },	/* 42rst0	br,bs,bt	*/

{ 0,	FORMAT_RRI8_TSI,	0x00C002,	"addi" },	/* iiCst2	at,as,imm8 (-128..127) */
{ 0,	FORMAT_RRI8_TSIx256,	0x00D002,	"addmi" },	/* iiDst2	at,as,imm8 256*(-128..127) */

{ 0,	FORMAT_RRR_TS,		0x009000,	"all4" },	/* 009st0	bt,bs		*/
{ 0,	FORMAT_RRR_TS,		0x00B000,	"all8" },	/* 00Bst0	bt,bs		*/
{ 0,	FORMAT_RRR_TS,		0x008000,	"any4" },	/* 008st0	bt,bs		*/
{ 0,	FORMAT_RRR_TS,		0x00A000,	"any8" },	/* 00Ast0	bt,bs		*/

{ 0,	FORMAT_RRI8_STI,	0x004007,	"ball" },	/* ii4st7	as,at,label	*/
{ 0,	FORMAT_RRI8_STI,	0x00C007,	"bnall" },	/* iiCst7	as,at,label	*/
{ 0,	FORMAT_RRI8_STI,	0x008007,	"bany" },	/* ii8st7	as,at,label	*/
{ 0,	FORMAT_RRI8_STI,	0x000007,	"bnone" },	/* ii0st7	as,at,label	*/
{ 0,	FORMAT_RRI8_STI,	0x005007,	"bbc" },	/* ii5st7	as,at,label	*/
{ 0,	FORMAT_RRI8_STI,	0x00D007,	"bbs" },	/* iiDst7	as,at,label	*/
{ 0,	FORMAT_RRI8_STI,	0x001007,	"beq" },	/* ii1st7	as,at,label	*/
{ 0,	FORMAT_RRI8_STI,	0x009007,	"bne" },	/* ii9st7	as,at,label	*/
{ 0,	FORMAT_RRI8_STI,	0x00A007,	"bge" },	/* iiAst7	as,at,label	*/
{ 0,	FORMAT_RRI8_STI,	0x002007,	"blt" },	/* ii2st7	as,at,label	*/
{ 0,	FORMAT_RRI8_STI,	0x00B007,	"bgeu" },	/* iiBst7	as,at,label	*/
{ 0,	FORMAT_RRI8_STI,	0x003007,	"bltu" },	/* ii3st7	as,at,label	*/
{ 0,	FORMAT_BRI12_SI,	0x000016,	"beqz" },	/* iixs16	as,label	*/
{ 0,	FORMAT_BRI12_SI,	0x000056,	"bnez" },	/* iixs56	as,label	*/
{ 0,	FORMAT_BRI12_SI,	0x0000D6,	"bgez" },	/* iixsD6	as,label	*/
{ 0,	FORMAT_BRI12_SI,	0x000096,	"bltz" },	/* iixs96	as,label	*/
{ 0,	FORMAT_RRI8_SI,		0x000076,	"bf" },		/* ii0s76	bs,label	*/
{ 0,	FORMAT_RRI8_SI,		0x001076,	"bt" },		/* ii1s76	bs,label	*/
{ 0,	FORMAT_BRI8_RSI,	0x000026,	"beqi" },	/* iirs26	as,imm4,label	*/
{ 0,	FORMAT_BRI8_RSI,	0x000066,	"bnei" },	/* iirs66	as,imm4,label	*/
{ 0,	FORMAT_BRI8_RSI,	0x0000e6,	"bgei" },	/* iirsE6	as,imm4,label	*/
{ 0,	FORMAT_BRI8_RSI,	0x0000A6,	"blti" },	/* iirsA6	as,imm4,label	*/
{ 0,	FORMAT_BRI8_RSI,	0x0000F6,	"bgeui" },	/* iirsF6	as,imm4,label	*/
{ 0,	FORMAT_BRI8_RSI,	0x0000B6,	"bltui" },	/* iirsB6	as,imm4,label	*/
{ 0,	FORMAT_RRI8_ST5I,	0x006007,	"bbci" },	/* ii(6,7)st7	as,0..31,label - t is 5-bits */
{ 0,	FORMAT_RRI8_ST5I,	0x00E007,	"bbsi" },	/* ii(E,F)st7	as,0.31,label - t is 5-bits */

{ 0,	CALLOP,			0x000005,	"call0" },	/* iiii05 	label/4 - imm18	*/
{ 0,	JUMPOP,			0x000006,	"j" },		/* iiii06	label - imm18	*/
{ 0,	CALLXOP,		0x0000C0,	"callx0" },	/* 000sC0	as		*/
{ 0,	CALLXOP,		0x0000A0,	"jx" },		/* 000sA0	as		*/
{ 0,	CALLX,			0x000080,	"ret" },	/* 000080	-		*/

/*
 * debug option
 */
{ 0,	FORMAT_RRR_ST,		0x004000,	"break" },	/* 004st0	0..15, 0..15 - XXX S=immediate, T=immediate */

{ 0,	FORMAT_RRI8_TSI,	0x000002,	"l8ui" }, 	/* ii0st2	at,as,(0..255)	*/
{ 0,	FORMAT_RRI8_TSI,	0x004002,	"s8i" },	/* ii4st2	at,as,(0..255)	*/

{ 0,	FORMAT_RRI8_TSIx2,	0x001002,	"l16ui" }, 	/* ii1st2	at,as,2*(0..255)*/
{ 0,	FORMAT_RRI8_TSIx2,	0x009002,	"l16si" }, 	/* ii9st2	at,as,2*(0..255)*/
{ 0,	FORMAT_RRI8_TSIx2,	0x005002,	"s16i" },	/* ii5st2	at,as,2*(0..255)*/

{ 0,	FORMAT_RRI8_TSIx4,	0x002002,	"l32i" },	/* ii2xt2	at,as,4*(0..255)*/
{ 0,	FORMAT_RRI8_TSIx4,	0x006002,	"s32i" },	/* ii6st2	at,as,4*(0..255)*/

/*
 * L32R option, absolute literals
 */
{ 0,	FORMAT_RII6_TI,		0x000001,	"l32r" },	/* iiiit1	at,label - imm16 */

{ 0,	FORMAT_RRI8_TSIx4,	0x00B002,	"l32ai" }, 	/* iiBst2	at,as,4*(0..255)*/
{ 0,	FORMAT_RRI8_TSIx4,	0x00F002,	"s32ri" },	/* iifst2	at,as,4*(0..255) */
{ 0,	FORMAT_RRI8_TSIx2,	0x00E002,	"s32c1i" },	/* iiEst2	at,as,4*(0..255)*/

{ 0,	FORMAT_RRR_MS,		0x900004,	"lddec" },	/* 90(0|w)s04	mw,as		*/
{ 0,	FORMAT_RRR_MS,		0x800004,	"ldinc" },	/* 80(0|w)s04	mw,as		*/

{ 0,	FORMAT_RRR_SI,		0x008076,	"loop" },	/* ii8s76	as,label - imm8	*/
{ 0,	FORMAT_RRI8_SI,		0x00A076,	"loopgtz" },	/* iiAs76	as,label - imm8	*/
{ 0,	FORMAT_RRI8_SI,		0x009076,	"loopnez" },	/* ii9s76	as,label - imm8	*/

{ 0,	FORMAT_RRI8_TSIx4,	0x000003,	"lsi" },	/* ii0st3	ft,as,4*(0..255)*/
{ 0,	FORMAT_RRI8_TSIx4,	0x008003,	"lsiu" },	/* ii8st3	ft,as,4*(0..255)*/
{ 0,	FORMAT_RRR_TSI,		0x004003,	"ssi" },	/* ii4st3	ft,as,4*(0..255)*/
{ 0,	FORMAT_RRR_TSI,		0x00C003,	"ssiu" },	/* iiCst3	ft,as,4*(0..255)*/

{ 0,	FORMAT_RRR_RST,		0x080000,	"lsx" },	/* 08rst0	fr,as,at	*/
{ 0,	FORMAT_RRR_RST,		0x480000,	"ssx" },	/* 48rst0	fr,as,at	*/
{ 0,	FORMAT_RRR_RST,		0x180000,	"lsxu" },	/* 18rst0	fr,as,at	*/
{ 0,	FORMAT_RRR_RST,		0x580000,	"ssxu" },	/* 58rst0	fr,as,at	*/

{ 0,	FORMAT_RRR_RSS,		0x200000,	"mov" },	/* 20rss0	ar,as		*/ /* alias for OR ar,as,as */
{ 0,	FORMAT_RRI8_TI,		0x00A002,	"movi" },	/* iiAxt2	at,(-2048..2047)*/

{ 0,	FORMAT_RRR_RST,		0x830000,	"moveqz" },	/* 83rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0x930000,	"movnez" },	/* 93rst0	ar,as,at	*/

{ 0,	FORMAT_RRR_RST,		0xB30000,	"movgez" },	/* B3rst0	ar,as,at	*/
{ 0,	FORMAT_RRR_RST,		0xA30000,	"movltz" },	/* A3rst0	ar,as,at	*/

{ 0,	FORMAT_RRR_RST,		0x8B0000,	"moveqz.s" },	/* 8Brst0	fr,fs,at	*/
{ 0,	FORMAT_RRR_RST,		0x9B0000,	"movnez.s" },	/* 9Brst0	fr,fs,at	*/

{ 0,	FORMAT_RRR_RST,		0xC30000,	"movf" },	/* C3rst0 	ar,as,bt	*/
{ 0,	FORMAT_RRR_RST,		0xD30000,	"movt" },	/* D3rst0	ar,as,bt	*/

{ 0,	FORMAT_RRR_RST,		0xCB0000,	"movf.s" },	/* CBrst0	fr,fs,bt	*/
{ 0,	FORMAT_RRR_RST,		0xDB0000,	"movt.s" },	/* DBrst0	fr,fs,bt	*/

{ 0,	FORMAT_RRR_RST,		0xBB0000,	"movgez.s" },	/* BBrst0	fr,fs,at	*/
{ 0,	FORMAT_RRR_RST,		0xAB0000,	"movltz.s" },	/* ABrst0	fr,fs,at	*/

{ 0,	FORMAT_RRR_RST,		0x1B0000,	"un.s" },	/* 1Brst0	br,fs,ft	*/ 
{ 0,	FORMAT_RRR_RST,		0x2B0000,	"oeq.s" },	/* 2Brst0	br,fs,ft	*/
{ 0,	FORMAT_RRR_RST,		0x3D0000,	"ueq.s" },	/* 3Drst0	br,fs,ft	*/
{ 0,	FORMAT_RRR_RST,		0x5B0000,	"ult.s" },	/* 5Brst0	br,fs,ft	*/
{ 0,	FORMAT_RRR_RST,		0x6B0000,	"ole.s" },	/* 6Brst0	br,fs,ft	*/
{ 0,	FORMAT_RRR_RST,		0x7B0000,	"ule.s" },	/* 7Brst0	br,fs,ft	*/


/*
 * windowed option (available of 
 */
#if 0
{ 0,	FORMAT_RRR_TS,		0x001000,	"movsp" },	/* 001st0	at,as		*/
{ 0,	FORMAT_RRR_Tm4,		0x408000,	"rotw" },	/* 4080x0	(-8..7)		*/
{ 0,	FORMAT_RRR,		0x003400,	"rfwo" },	/* 003400	-		*/
{ 0,	FORMAT_RRR,		0x003500,	"rfwu" },	/* 003500	-		*/
{ 0,	CALLOP,			0x000015,	"call4" },	/* iiii15	label/4 - imm18	*/
{ 0,	CALLOP,			0x000025,	"call8" },	/* iiii25	label/4 - imm18	*/
{ 0,	CALLOP,			0x000035,	"call12" },	/* iiii35	label/4 - imm18	*/
{ 0,	CALLXOP,		0x0000D0,	"callx4" },	/* 000sD0	as		*/
{ 0,	CALLXOP,		0x0000E0,	"callx8" },	/* 000sE0	as		*/
{ 0,	CALLXOP,		0x0000F0,	"callx12" },	/* 000sF0	as		*/
{ 0,	CALLX,			0x000090,	"retw" },	/* 000090	-		*/
{ 0,	FORMAT_BRI12,		0x000036,	"entry" },	/* iixs36	as,8*(0..4095)	*/
{ 0,	FORMAT_RRI4_TSRx4,	0x09B000,	"l32e" }, 	/* 09rst0	at,as,4*(-16..-1,1) */
{ 0,	FORMAT_RRI4_TSRx4,	0x490000,	"s32e" },	/* 49rst0	at,as,4*(-16..-1,1) */
#endif

/*
 * code-density option
 */
{ 0,	FORMAT_RRRN_TSIx4,	0x0008,		"l32i.n" },	/* xst8		at,as,4*(0..15) - reloc		*/
{ 0,	FORMAT_RRRN_TSIx4,	0x0009,		"s32i.n" },	/* xst9		at,as,4*(0..15) - reloc		*/
{ 0,	FORMAT_RRRN_RST,	0x000A,		"add.n" },	/* rstA 	ar,as,at			*/
{ 0,	FORMAT_RRRN_RSI,	0x000B,		"addi.n" },	/* rstB		ar,as,imm4 (0=-1, 1..15)	*/
{ 0,	FORMAT_RRRN_TS,		0x000D,		"mov.n" },	/* 0stD		at,as				*/
{ 0,	FORMAT_RRRN,		0xF00D,		"ret.n" },	/* F00D		-				*/
{ 0,	FORMAT_RRRN,		0xF03D,		"nop.n" },	/* F03D		-				*/
{ 0,	FORMAT_RRRN,		0xF06D,		"ill.n" },	/* F06D		-				*/
{ 0,	FORMAT_RI7,		0x000C,		"movi.n" },	/* xsxC		as,imm7 (0..127)-32		*/
#if 0
/* these don't seem to work on L106 */
{ 0,	FORMAT_RI6,		0x008C,		"beqz.n" },	/* xsxC		as,label	*/
{ 0,	FORMAT_RI6,		0x00CC,		"bnez.n" },	/* xs(C+x)C	as,label	*/
#endif
/* and windowed */
{ 0,	FORMAT_RRRN,		0xF01D,		"retw.n" },	/* F01D		-		*/

{ 0,	FORMAT_RRRN_S,		0xF02D,		"break.n" },	/* Fs2D		0..15 - XXX S=immediate */

#if 0

{ 0,	FORMAT_RRI8_SIx4,	0x007062,	"dhi" },	/* ii7s62	as,4*(0..255)	*/
{ 0,	FORMAT_RRI4_SIx16,	0x027082,	"dhu" },	/* x27s82	as,16*(0..15)	*/
{ 0,	FORMAT_RRI8_SIx4,	0x007042,	"dhwb" },	/* ii7s42	as,4*(0..255)	*/
{ 0,	FORMAT_RRI8_SIx4,	0x007052,	"dhwbi" },	/* ii7s52	as,4*(0..255)	*/
{ 0,	FORMAT_RRI8_SIx4,	0x007072,	"dii" },	/* ii7s72	as,4*(0..255)	*/
{ 0,	FORMAT_RRI4_SIx16,	0x037082,	"diu" },	/* x37s82	as,16*(0..15)	*/
{ 0,	FORMAT_RRI4_SIx16,	0x047082,	"diwb" },	/* x47s82	as,16*(0..15)	*/
{ 0,	FORMAT_RRI4_SIx16,	0x057082,	"diwbi" },	/* x57s82	as,16*(0..15)	*/

{ 0,	FORMAT_RRI4_SIx16,	0x007082,	"dpfl" },	/* x07s82	as,16*(0..15)	*/
{ 0,	FORMAT_RRI8_SIx4,	0x007002,	"dpfr" },	/* ii7s02	as,4*(0..255)	*/
{ 0,	FORMAT_RRI8_SIx4,	0x007012,	"dpfw" },	/* ii7s12	as,4*(0..255)	*/

{ 0,	FORMAT_RRI8_SIx4,	0x007022,	"dpfro" },	/* ii7s22	as,4*(0..255)	*/
{ 0,	FORMAT_RRI8_SIx4,	0x007032,	"dpfwo" },	/* ii7s32	as,4*(0..255)	*/

{ 0,	FORMAT_RRR_S,		0x50C000,	"idtlb" },	/* 50Cs00	as		*/
{ 0,	FORMAT_RRR_S,		0x504000,	"iitlb" },	/* 504s00	as		*/

{ 0,	FORMAT_RRR_ST,		0x50B000,	"rdtlb0" },	/* 50Bst0	at,as		*/
{ 0,	FORMAT_RRR_ST,		0x50F000,	"rdtlb1" },	/* 50Fst0	at,as		*/
{ 0,	FORMAT_RRR_ST,		0x503000,	"ritlb0" },	/* 503st0	ar,as		*/
{ 0,	FORMAT_RRR_ST,		0x507000,	"ritlb1" },	/* 507st0	ar,as		*/
{ 0,	FORMAT_RRR_ST,		0x50D000,	"pdtlb" },	/* 50Dst0	at,as		*/
{ 0,	FORMAT_RRR_ST,		0x50E000,	"wdtlb" },	/* 50Est0	at,as		*/
{ 0,	FORMAT_RRR_ST,		0x505000,	"pitlb" },	/* 505st0	at,as		*/
{ 0,	FORMAT_RRR_ST,		0x506000,	"witlb" },	/* 506st0	at,as		*/

{ 0,	FORMAT_RRI8_SI,		0x0070F2,	"iii" },	/* ii7sF2	as,4*(0..255)	*/
{ 0,	FORMAT_RRI8_Sx4,	0x0070E2,	"ihi" },	/* ii7sE2	as,4*(0..255)	*/

{ 0,	FORMAT_RRI4_Sx16,	0x0370D2,	"iiu" },	/* x37sD2	as,4*(0..255)	*/
{ 0,	FORMAT_RRI4_Sx16,	0x0270D2,	"ihu" },	/* x27sD2	as,4*(0..255)	*/

{ 0,	FORMAT_RRI8,		0x0070C2,	"ipf" },	/* ii7sC2	as,4*(0..255)	*/
{ 0,	FORMAT_RRI4_Sx16,	0x0070C2,	"ipfl" },	/* x07sD2	as,4*(0..255)	*/

{ 0,	FORMAT_RRR_TS,		0xF18000,	"ldct" },	/* F18st0	at,as		*/
{ 0,	FORMAT_RRR_TS,		0xF19000,	"sdct" },	/* F19st0	at,as		*/

{ 0,	FORMAT_RRR_TS,		0xF10000,	"lict" },	/* F10st0	at,as		*/
{ 0,	FORMAT_RRR_TS,		0xF11000,	"sict" },	/* F11st0	at,as		*/

{ 0,	FORMAT_RRR_TS,		0xF12000,	"licw" },	/* F12st0	at,as		*/
{ 0,	FORMAT_RRR_TS,		0xF13000,	"sicw" },	/* F13st0	at,as		*/

{ 0,	FORMAT_RRR_TS,		0x40E000,	"nsa" },	/* 40Est0	at,as		*/
{ 0,	FORMAT_RRR_TS,		0x40F000,	"nsau" },	/* 40Fst0	at,as		*/

{ 0,	FORMAT_RRR_TS,		0x406000,	"rer" },	/* 406st0	at,as		*/
{ 0,	FORMAT_RRR_TS,		0x407000,	"wer" },	/* 407st0	at,as		*/

{ 0,	FORMAT_RUR,		0xe30000,	"rur" },	/* e3rst0	ar,16*(s+t)	*/
{ 0,	FORMAT_RUR,		0xf30000,	"wur" },	/* e3sst0	at,16*(r+s)	*/

{ 0,	FORMAT_RSR,		0x030000,	"rsr" },	/* 03rrt0	at,(0..255)	*/
{ 0,	FORMAT_RSR,		0x130000,	"wsr" },	/* 13rrt0	at,(0..255)	*/
{ 0,	FORMAT_RSR,		0x610000,	"xsr" },	/* 61srt0	at,(0..255)	*/

{ 0,	FORMAT_RRR_RS,		0xFA0040,	"rfr" },	/* FArs40	ar,fs		*/
{ 0,	FORMAT_RRR_RS,		0xFA0050,	"wfr" },	/* FArs50	fr,as		*/

{ 0,	FORMAT_RRR,		0xF1E010,	"rfdd" },	/* F1E010 	-		*/
{ 0,	FORMAT_RRR,		0x003200,	"rfde" },	/* 003200	-		*/
{ 0,	FORMAT_RRR,		0xF1E000,	"rfdo" },	/* F1E000	-		*/
{ 0,	FORMAT_RRR,		0x003000,	"rfe" },	/* 003000	-		*/
{ 0,	FORMAT_RRR_L,		0x003010,	"rfi" },	/* 003010	-		*/
{ 0,	FORMAT_RRR,		0x003020,	"rfme" },	/* 003020	-		*/
{ 0,	FORMAT_RRR,		0x003100,	"rfue" },	/* 003100	-		*/

{ 0,	FORMAT_RRR,		0x002000,	"isync" },	/* 002000	-		*/
{ 0,	FORMAT_RRR,		0x002010,	"rsync" },	/* 002010	-		*/
{ 0,	FORMAT_RRR,		0x002020,	"esync" },	/* 002020	-		*/
{ 0,	FORMAT_RRR,		0x002030,	"dsync" },	/* 002030	-		*/

{ 0,	FORMAT_RRR,		0x002080,	"excw" },	/* 002080	-		*/
{ 0,	FORMAT_RRR,		0x0020c0,	"memw" },	/* 0020C0	-		*/
{ 0,	FORMAT_RRR,		0x0020D0,	"extw" },	/* 0020D0	-		*/

{ 0,	FORMAT_RRR,		0x0020F0,	"nop" },	/* 0020F0	-		*/

{ 0,	FORMAT_RRR,		0x005000,	"syscall" },	/* 005000	-		*/

{ 0,	FORMAT_RRR_TI4,		0x006000,	"rsil" },	/* 006xt0	at,(0..15)	*/

{ 0,	FORMAT_RRR_RSIp7,	0x230000,	"sext" },	/* 23rst0	ar,as,7..22	*/

/*
 * clamps option
 */
{ 0,	FORMAT_RRR_RSIp7,	0x330000,	"clamps" },	/* 33rst0	ar,as,7..22	*/

{ 0,	FORMAT_RRR_I4,		0x007000,	"waiti" },	/* 007x00	(0..15)		*/

{ 0,	FORMAT_RRR_RST,		0x9A0000,	"trunc.s" },	/* 9Arst0	ar,fs,(0..15)	*/
{ 0,	FORMAT_RRR_RST,		0xEA0000,	"utrunc.s" },	/* EArst0	ar,fs,(0..15)	*/ 
{ 0,	FORMAT_RRR_RST,		0x8A0000,	"round.s" },	/* 8Arst0	ar,fs,(0..15)	*/
{ 0,	FORMAT_RRR_RSI,		0xAA0000,	"floor.s" },	/* AArst0	ar,fs,(0..15)	*/
{ 0,	FORMAT_RRR_RSI,		0xCA0000,	"ceil.s" },	/* CArst0	ar,fs,(0..15)	*/
{ 0,	FORMAT_RRR_RSI,		0xCA0000,	"float.s" },	/* CArst0	fr,as,(0..15)	*/
{ 0,	FORMAT_RRR_RST,		0xDA0000,	"ufloat.s" },	/* DArst0	fr,as,(0..15)	*/

#endif


/* special registers */
{ 0,	SREG,			0,		"lbeg" },
{ 0,	SREG,			1,		"lend" },
{ 0,	SREG,			2,		"lcount" },
{ 0,	SREG,			3,		"sar" },	/* shift amount register */
{ 0,	SREG,			4,		"br" },		/* boolean register file */
{ 0,	SREG,			5,		"litbase" },	/* litbase */
{ 0,	SREG,			12,		"scompare1" },
{ 0,	SREG,			16,		"acclo" },	/* MAC16 accumulator */
{ 0,	SREG,			17,		"acchi" },
{ 0,	SREG,			32,		"m0" },		/* MAC16 registers */
{ 0,	SREG,			33,		"m1" },
{ 0,	SREG,			34,		"m2" },
{ 0,	SREG,			35,		"m3" },
{ 0,	SREG,			72,		"WindowBase" },
{ 0,	SREG,			73,		"WindowStart" },
{ 0,	SREG,			83,		"ptevaddr" },
{ 0,	SREG,			89,		"mmid" },
{ 0,	SREG,			90,		"rasid" },
{ 0,	SREG,			91,		"itlbcfg" },	/* instruction TLB */
{ 0,	SREG,			92,		"dtlbcfg" },	/* data TLB */
{ 0,	SREG,			96,		"ibreakenable" },
{ 0,	SREG,			98,		"cacheattr" },
{ 0,	SREG,			99,		"atomctl" },
{ 0,	SREG,			104,		"ddr" },	/* data debug register */
{ 0,	SREG,			106,		"mepc" },	/* memory error PC register */
{ 0,	SREG,			107,		"meps" },	/* memory error PS register */
{ 0,	SREG,			108,		"mesave" },	/* memory error save register */
{ 0,	SREG,			109,		"mesr" },	/* memory error status register */
{ 0,	SREG,			110,		"mecr" },	/* memory error check register */
{ 0,	SREG,			111,		"mevaddr" },	/* memory error VADDR register */
{ 0,	SREG,			128,		"ibreak0" },
{ 0,	SREG,			129,		"ibreak1" },
{ 0,	SREG,			130,		"dbreak0" },
{ 0,	SREG,			131,		"dbreak1" },
{ 0,	SREG,			177,		"epc1" },	/* exception PC */
{ 0,	SREG,			178,		"epc2" },	/* exception PC */
{ 0,	SREG,			179,		"epc3" },	/* exception PC */
{ 0,	SREG,			180,		"epc4" },	/* exception PC */
{ 0,	SREG,			181,		"epc5" },	/* exception PC */
{ 0,	SREG,			182,		"epc6" },	/* exception PC */
{ 0,	SREG,			183,		"epc7" },	/* exception PC */
{ 0,	SREG,			184,		"depc" },	/* double exception PC */
{ 0,	SREG,			224,		"cpenable" },	/* coprocessor disable */
{ 0,	SREG,			226,		"interrupt" },	/* interrupt request bits */
{ 0,	SREG,			228,		"intenable" },	/* interrupt enable */
{ 0,	SREG,			230,		"ps" },		/* processor state */
{ 0,	SREG,			231,		"vecbase" },
{ 0,	SREG,			232,		"exccause" },
{ 0,	SREG,			234,		"ccount" },	/* CPU cycle counter */
{ 0,	SREG,			235,		"prid" },	/* processor id */
{ 0,	SREG,			236,		"icount" },	/* instruction count */
{ 0,	SREG,			237,		"icountlevel" },
{ 0,	SREG,			238,		"excvaddr" },
{ 0,	SREG,			240,		"ccompore0" },	/* compare CPU cycle counter */
{ 0,	SREG,			244,		"misc0" },
{ 0,	SREG,			245,		"misc1" },
{ 0,	SREG,			246,		"misc2" },
{ 0,	SREG,			247,		"misc3" },
