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

{ 0,	PSEUDOOP_DEVICE,	0,	".device" },
{ 0,	PSEUDOOP_DT,		0,	".dt" },

{ 0,	SHIFTFUNC,		0,	"low" },
{ 0,	SHIFTFUNC,		8,	"high" },
{ 0,	SHIFTFUNC,		0,	"lo8" },
{ 0,	SHIFTFUNC,		8,	"hi8" },

/* mpasm compatibility */
#ifdef COMPAT_MPASM
{ 0,	PSEUDOOP_ORG,		0,	"ORG" },
{ 0,	PSEUDOOP_END,		0,	"END" },
{ 0,	PSEUDOOP_DATA,		1,	"DS" },
{ 0,	PSEUDOOP_DT,		0,	"DT" },
{ 0,	'=',			0,	"EQU" },
{ 0,	PSEUDOOP_INCLUDE,	0,	"INCLUDE" },
{ 0,	PSEUDOOP_DEVICE,	0,	"PROCESSOR" },
{ 0,	PSEUDOOP_BANKSEL,	0,	"BANKSEL" },
{ 0,	PSEUDOOP_BANKMASK,	0,	"BANKMASK" },
{ 0,	PSEUDOOP_PAGESEL,	0,	"PAGESEL" },
{ 0,	PSEUDOOP_CONFIG,	0,	"CONFIG" },
{ 0,	PSEUDOOP_GLOBAL,	0,	"GLOBAL" },
{ 0,	PSEUDOOP_LIST,	  	0,	"NOLIST" },
{ 0,	PSEUDOOP_LIST,	  	1,	"LIST" },
{ 0,	DOT,	  		0,	"$" },
{ 0,	PSEUDOOP_MAXRAM,	0,	"__MAXRAM" },
{ 0,	PSEUDOOP_BADRAM,	0,	"__BADRAM" },
{ 0,	PSEUDOOP_CONFIG,	0,	"__CONFIG" },
#endif

/* pic-as compability */
#ifdef COMPAT_PICAS
{ 0,	PSEUDOOP_PSECT,		0,	"PSECT" },
{ 0,	IDENT,	  		1,	"CODE" },
#endif

#if PIC_ISA == PIC14

/* register direction */
{ 0,	D,			0x00,	"W" },
{ 0,	D,			0x80,	"F" },

/* byte-oriented */
{ 0,	BYTEOP, 		0x0700, "ADDWF" },	/* 00 0111 dfff ffff */
{ 0,	BYTEOP, 		0x0500, "ANDWF" },	/* 00 0101 dfff ffff */
{ 0,	BYTEOP,			0x0900, "COMF" },	/* 00 1001 dfff ffff */
{ 0,	BYTEOP,			0x0300, "DECF" },	/* 00 0011 dfff ffff */
{ 0,	BYTEOP,			0x0b00, "DECFSZ" },	/* 00 1011 dfff ffff */
{ 0,	BYTEOP,			0x0a00, "INCF" },	/* 00 1010 dfff ffff */
{ 0,	BYTEOP,			0x0f00, "INCFSZ" },	/* 00 1111 dfff ffff */
{ 0,	BYTEOP,			0x0400, "IORWF" },	/* 00 0100 dfff ffff */
{ 0,	BYTEOP,			0x0800, "MOVF" },	/* 00 1000 dfff ffff */
{ 0,	BYTEOP,			0x0d00, "RLF" },	/* 00 1101 dfff ffff */
{ 0,	BYTEOP,			0x0c00, "RRF" },	/* 00 1100 dfff ffff */
{ 0,	BYTEOP,			0x0200, "SUBWF" },	/* 00 0010 dfff ffff */
{ 0,	BYTEOP,			0x0e00, "SWAPF" },	/* 00 1110 dfff ffff */
{ 0,	BYTEOP,			0x0600, "XORWF" },	/* 00 0110 dfff ffff */

{ 0,	ONEOP,			0x0180, "CLRF" },	/* 00 0001 1fff ffff */
{ 0,	ONEOP,			0x0080, "MOVWF" },	/* 00 0000 1fff ffff */

/* bit-oriented */
{ 0,	BITOP,			0x1000, "BCF" },	/* 01 00bb bfff ffff */
{ 0,	BITOP,			0x1400, "BSF" },	/* 01 01bb bfff ffff */
{ 0,	BITOP,			0x1800, "BTFSC" },	/* 01 10bb bfff ffff */
{ 0,	BITOP,			0x1c00, "BTFSS" },	/* 01 11bb bfff ffff */

/* literal operations */
{ 0,	LITOP,			0x3e00, "ADDLW" },	/* 11 111x kkkk kkkk */
{ 0,	LITOP,			0x3900, "ANDLW" },	/* 11 1001 kkkk kkkk */
{ 0,	LITOP,			0x3800, "IORLW" },	/* 11 1000 kkkk kkkk */
{ 0,	LITOP,			0x3000, "MOVLW" },	/* 11 0000 kkkk kkkk */
{ 0,	LITOP,			0x3400, "RETLW" },	/* 11 0100 kkkk kkkk */
{ 0,	LITOP,			0x3c00, "SUBLW" },	/* 11 1100 kkkk kkkk */
{ 0,	LITOP,			0x3a00, "XORLW" },	/* 11 1010 kkkk kkkk */

/* control operations */
{ 0,	NOOP,			0x0064, "CLRWDT" },	/* 00 0000 0110 0100 */
{ 0,	NOOP,			0x0009, "RETFIE" },	/* 00 0000 0000 1001 */
{ 0,	NOOP,			0x0008, "RETURN" },	/* 00 0000 0000 1000 */
{ 0,	NOOP,			0x0063, "SLEEP" },	/* 00 0000 0110 0011 */
{ 0,	NOOP,			0x0000, "NOP" },	/* 00 0000 0xx0 0000 */
{ 0,	NOOP,			0x0100, "CLRW" },	/* 00 0001 0xxx xxxx */

{ 0,	JMPOP,			0x2000, "CALL" },	/* 10 0kkk kkkk kkkk */
{ 0,	JMPOP,			0x2800, "GOTO" },	/* 10 1kkk kkkk kkkk */

/* enhanced devices */
{ 0,	BYTEOP, 		0x3d00, "ADDWFC" },	/* 11 1101 dfff ffff */
{ 0,	BYTEOP, 		0x3700, "ASRF" },	/* 11 0111 dfff ffff */
{ 0,	BYTEOP, 		0x3500, "LSLF" },	/* 11 0101 dfff ffff */
{ 0,	BYTEOP, 		0x3600, "LSRF" },	/* 11 0110 dfff ffff */
{ 0,	BYTEOP, 		0x3b00, "SUBWFB" },	/* 11 1011 dfff ffff */
#ifdef  notyet
{ 0,	MOVLB,			0x0020, "MOVLB" },	/* 00 0000 001k kkkk */
{ 0,	MOVLP,			0x3180, "MOVLP" },	/* 11 0001 1kkk kkkk */
{ 0,	BRA,			0x2800, "BRA" },	/* 11 001k kkkk kkkk */
#endif
{ 0,	NOOP,			0x000b, "BRW" },	/* 00 0000 0000 1011 */
{ 0,	NOOP,			0x000a, "CALLW" },	/* 00 0000 0000 1010 */
{ 0,	NOOP,			0x0062, "OPTION" },	/* 00 0000 0110 0010 */
{ 0,	NOOP,			0x0001, "RESET" },	/* 00 0000 0000 0001 */
#ifdef notyet
{ 0,	TRIS,			0x0060, "TRIS" },	/* 00 0000 0110 0fff */
{ 0,	ADDFSR,			0x3100, "ADDFSR" },	/* 11 0001 0nkk kkkk */
{ 0,	MOVIW,			0x0010, "MOVIW" },	/* 00 0000 0001 0nmm */
{ 0,	MOVIW,			0x3f00, "MOVIW" },	/* 11 1111 0nkk kkkk */
{ 0,	MOVIW,			0x0018, "MOVWI" },	/* 00 0000 0001 1nmm */
{ 0,	MOVIW,			0x3f80, "MOVWI" },	/* 11 1111 1nkk kkkk */
#endif

#elif PIC_ISA == PIC12

/* register direction */
{ 0,	D,			0x00,	"W" },
{ 0,	D,			0x20,	"F" },

/* byte-oriented */
{ 0,	BYTEOP, 		0x1C0, "ADDWF" },	/* 0001 11df ffff */
{ 0,	BYTEOP, 		0x140, "ANDWF" },	/* 0001 01df ffff */
{ 0,	BYTEOP,			0x240, "COMF" },	/* 0010 01df ffff */
{ 0,	BYTEOP,			0x0C0, "DECF" },	/* 0000 11df ffff */
{ 0,	BYTEOP,			0x2C0, "DECFSZ" },	/* 0010 11df ffff */
{ 0,	BYTEOP,			0x280, "INCF" },	/* 0010 10df ffff */
{ 0,	BYTEOP,			0x3C0, "INCFSZ" },	/* 0011 11df ffff */
{ 0,	BYTEOP,			0x100, "IORWF" },	/* 0001 00df ffff */
{ 0,	BYTEOP,			0x200, "MOVF" },	/* 0010 00df ffff */
{ 0,	BYTEOP,			0x340, "RLF" },		/* 0011 01df ffff */
{ 0,	BYTEOP,			0x300, "RRF" },		/* 0011 00df ffff */
{ 0,	BYTEOP,			0x080, "SUBWF" },	/* 0000 10df ffff */
{ 0,	BYTEOP,			0x380, "SWAPF" },	/* 0011 10df ffff */
{ 0,	BYTEOP,			0x180, "XORWF" },	/* 0001 10df ffff */

{ 0,	ONEOP,			0x060, "CLRF" },	/* 0000 011f ffff */
{ 0,	ONEOP,			0x020, "MOVWF" },	/* 0000 001f ffff */

/* bit-oriented */
{ 0,	BITOP,			0x400, "BCF" },		/* 0100 bbbf ffff */
{ 0,	BITOP,			0x500, "BSF" },		/* 0101 bbbf ffff */
{ 0,	BITOP,			0x600, "BTFSC" },	/* 0110 bbbf ffff */
{ 0,	BITOP,			0x700, "BTFSS" },	/* 0111 bbbf ffff */

/* literal operations */
{ 0,	LITOP,			0xE00, "ANDLW" },	/* 1110 kkkk kkkk */
{ 0,	LITOP,			0xD00, "IORLW" },	/* 1101 kkkk kkkk */
{ 0,	LITOP,			0xC00, "MOVLW" },	/* 1100 kkkk kkkk */
{ 0,	LITOP,			0x800, "RETLW" },	/* 1000 kkkk kkkk */
{ 0,	LITOP,			0xF00, "XORLW" },	/* 1111 kkkk kkkk */

/* control operations */
{ 0,	NOOP,			0x004, "CLRWDT" },	/* 0000 0000 0100 */
{ 0,	NOOP,			0x003, "SLEEP" },	/* 0000 0000 0011 */
{ 0,	NOOP,			0x000, "NOP" },		/* 0000 0000 0000 */
{ 0,	NOOP,			0x040, "CLRW" },	/* 0000 0100 0000 */

{ 0,	LITOP,			0x900, "CALL" },	/* 1001 kkkk kkkk */
{ 0,	JMPOP,			0xA00, "GOTO" },	/* 101k kkkk kkkk */

#else

#error undefined ISA

#endif
