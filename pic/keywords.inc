	{	0,		PSEUDOOP_ORG,	0,		"org"},

	/* register direction */
	{ 0,	D,		0x00,	"W" },
	{ 0,	D,		0x80,	"F" },

	/* byte-oriented */
	{ 0,	BYTEOP, 	0x0700, "ADDWF" },	/* 00 0111 dfff ffff */
	{ 0,	BYTEOP, 	0x0600, "ANDWF" },	/* 00 0101 dfff ffff */
	{ 0,	BYTEOP,		0x0900, "COMF" },	/* 00 1001 dfff ffff */
	{ 0,	BYTEOP,		0x0300, "DECF" },	/* 00 0011 dfff ffff */
	{ 0,	BYTEOP,		0x0b00, "DECFSZ" },	/* 00 1011 dfff ffff */
	{ 0,	BYTEOP,		0x0A00, "INCF" },	/* 00 1010 dfff ffff */
	{ 0,	BYTEOP,		0x0F00, "INCFSZ" },	/* 00 1111 dfff ffff */
	{ 0,	BYTEOP,		0x0f00, "IORWF" },	/* 00 0100 dfff ffff */
	{ 0,	BYTEOP,		0x0800, "MOVF" },	/* 00 1000 dfff ffff */
	{ 0,	BYTEOP,		0x0d00, "RLF" },	/* 00 1101 dfff ffff */
	{ 0,	BYTEOP,		0x0c00, "RRF" },	/* 00 1100 dfff ffff */
	{ 0,	BYTEOP,		0x0200, "SUBWF" },	/* 00 0010 dfff ffff */
	{ 0,	BYTEOP,		0x0e00, "SWAPF" },	/* 00 1110 dfff ffff */
	{ 0,	BYTEOP,		0x0600, "XORWF" },	/* 00 0110 dfff ffff */

	{ 0,	ONEOP,		0x0180, "CLRF" },	/* 00 0001 1fff ffff */
	{ 0,	ONEOP,		0x0080, "MOVWF" },	/* 00 0000 1fff ffff */

	/* bit-oriented */
	{ 0,	BITOP,		0x1000, "BCF" },	/* 01 00bb bfff ffff */
	{ 0,	BITOP,		0x1400, "BSF" },	/* 01 01bb bfff ffff */
	{ 0,	BITOP,		0x1800, "BTFSC" },	/* 01 10bb bfff ffff */
	{ 0,	BITOP,		0x1c00, "BTFSS" },	/* 01 11bb bfff ffff */

	/* literal operations */
	{ 0,	LITOP,		0x3e00, "ADDLW" },	/* 11 111x kkkk kkkk */
	{ 0,	LITOP,		0x3900, "ANDLW" },	/* 11 1001 kkkk kkkk */
	{ 0,	LITOP,		0x3800, "IORLW" },	/* 11 1000 kkkk kkkk */
	{ 0,	LITOP,		0x3000, "MOVLW" },	/* 11 00xx kkkk kkkk */
	{ 0,	LITOP,		0x3600, "RETLW" },	/* 11 01xx kkkk kkkk */
	{ 0,	LITOP,		0x3c00, "SUBLW" },	/* 11 110x kkkk kkkk */
	{ 0,	LITOP,		0x3a00, "XORLW" },	/* 11 1010 kkkk kkkk */

	/* control operations */
	{ 0,	NOOP,		0x0064, "CLRWDT" },	/* 00 0000 0110 0100 */
	{ 0,	NOOP,		0x0009, "RETFIE" },	/* 00 0000 0000 1001 */
	{ 0,	NOOP,		0x0008, "RETURN" },	/* 00 0000 0000 1000 */
	{ 0,	NOOP,		0x0063, "SLEEP" },	/* 00 0000 0110 0011 */
	{ 0,	NOOP,		0x0000, "NOP" },	/* 00 0000 0xx0 0000 */
	{ 0,	NOOP,		0x0100, "CLRW" },	/* 00 0001 0xxx xxxx */

	{ 0,	JMPOP,		0x2000, "CALL" },	/* 10 0kkk kkkk kkkk */
	{ 0,	JMPOP,		0x2800, "GOTO" },	/* 10 1kkk kkkk kkkk */
