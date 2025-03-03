/*
 * Copyright (c) 1987, 1990, 1993, 2005 Vrije Universiteit, Amsterdam, The Netherlands.
 * All rights reserved.
 * 
 * Redistribution and use of the Amsterdam Compiler Kit in source and
 * binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 * 
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 * 
 *    * Neither the name of Vrije Universiteit nor the names of the
 *      software authors or contributors may be used to endorse or
 *      promote products derived from this software without specific
 *      prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS, AUTHORS, AND
 * CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL VRIJE UNIVERSITEIT OR ANY AUTHORS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*,
 * PDP 11 keywords,
 */

{ 0,	PSEUDOOP_ZERO,	2,		".blkb" },
{ 0,	PSEUDOOP_ZERO,	2,		".blkw" },
{ 0, 	PSEUDOOP_EVEN,	0,		".even" },

{ 0,	REG,		00,		"r0" },
{ 0,	REG,		01,		"r1" },
{ 0,	REG,		02,		"r2" },
{ 0,	REG,		03,		"r3" },
{ 0,	REG,		04,		"r4" },
{ 0,	REG,		05,		"r5" },
{ 0,	REG,		06,		"r6" },
{ 0,	REG,		06,		"sp" },
{ 0,	REG,		07,		"r7" },
{ 0,	REG,		07,		"pc" },

{ 0,	FREG,		00,		"fr0" },
{ 0,	FREG,		01,		"fr1" },
{ 0,	FREG,		02,		"fr2" },
{ 0,	FREG,		03,		"fr3" },
{ 0,	FRSP,		04,		"fr4" },
{ 0,	FRSP,		05,		"fr5" },

{ 0,	OP_SO,		05000,		"clr" },
{ 0,	OP_SO,		0105000,	"clrb" },
{ 0,	OP_SO,		05100,		"com" },
{ 0,	OP_SO,		0105100,	"comb" },
{ 0,	OP_SO,		005200,		"inc" },
{ 0,	OP_SO,		0105200,	"incb" },
{ 0,	OP_SO,		005300,		"dec" },
{ 0,	OP_SO,		0105300,	"decb" },
{ 0,	OP_SO,		005400,		"neg" },
{ 0,	OP_SO,		0105400,	"negb" },
{ 0,	OP_SO,		005700,		"tst" },
{ 0,	OP_SO,		0105700,	"tstb" },
{ 0,	OP_SO,		006200,		"asr" },
{ 0,	OP_SO,		0106200,	"asrb" },
{ 0,	OP_SO,		006300,		"asl" },
{ 0,	OP_SO,		0106300,	"aslb" },
{ 0,	OP_SO,		006000,		"ror" },
{ 0,	OP_SO,		0106000,	"rorb" },
{ 0,	OP_SO,		006100,		"rol" },
{ 0,	OP_SO,		0106100,	"rolb" },
{ 0,	OP_SO,		000300,		"swab" },
{ 0,	OP_SO,		005500,		"adc" },
{ 0,	OP_SO,		0105500,	"adcb" },
{ 0,	OP_SO,		005600,		"sbc" },
{ 0,	OP_SO,		0105600,	"sbcb" },
{ 0,	OP_SO,		006700,		"sxt" },
{ 0,	OP_DO,		010000,		"mov" },
{ 0,	OP_DO,		0110000,	"movb" },
{ 0,	OP_DO,		020000,		"cmp" },
{ 0,	OP_DO,		0120000,	"cmpb" },
{ 0,	OP_DO,		060000,		"add" },
{ 0,	OP_DO,		0160000,	"sub" },
{ 0,	OP_DO,		030000,		"bit" },
{ 0,	OP_DO,		0130000,	"bitb" },
{ 0,	OP_DO,		040000,		"bic" },
{ 0,	OP_DO,		0140000,	"bicb" },
{ 0,	OP_DO,		050000,		"bis" },
{ 0,	OP_DO,		0150000,	"bisb" },
{ 0,	OP_R_SO,	074000,		"xor" },
{ 0,	JMP,		0100,		"jmp" },
{ 0,	BR,		0400,		"br" },
{ 0,	BR,		01000,		"bne" },
{ 0,	BR,		01400,		"beq" },
{ 0,	BR,		0100000,	"bpl" },
{ 0,	BR,		0100400,	"bmi" },
{ 0,	BR,		0102000,	"bvc" },
{ 0,	BR,		0102400,	"bvs" },
{ 0,	BR,		0103000,	"bcc" },
{ 0,	BR,		0103400,	"bcs" },
{ 0,	BR,		002000,		"bge" },
{ 0,	BR,		002400,		"blt" },
{ 0,	BR,		003000,		"bgt" },
{ 0,	BR,		003400,		"ble" },
{ 0,	BR,		0101000,	"bhi" },
{ 0,	BR,		0101400,	"blos" },
{ 0,	BR,		0103000,	"bhis" },
{ 0,	BR,		0103400,	"blo" },
{ 0,	EJMP,		0400,		"jbr" },
{ 0,	EJMP,		01000,		"jne" },
{ 0,	EJMP,		01400,		"jeq" },
{ 0,	EJMP,		0100000,	"jpl" },
{ 0,	EJMP,		0100400,	"jmi" },
{ 0,	EJMP,		0102000,	"jvc" },
{ 0,	EJMP,		0102400,	"jvs" },
{ 0,	EJMP,		0103000,	"jcc" },
{ 0,	EJMP,		0103400,	"jcs" },
{ 0,	EJMP,		02000,		"jge" },
{ 0,	EJMP,		02400,		"jlt" },
{ 0,	EJMP,		03000,		"jgt" },
{ 0,	EJMP,		03400,		"jle" },
{ 0,	EJMP,		0101000,	"jhi" },
{ 0,	EJMP,		0101400,	"jlos" },
{ 0,	EJMP,		0103000,	"jhis" },
{ 0,	EJMP,		0103400,	"jlo" },
{ 0,	JSR,		004000,		"jsr" },
{ 0,	RTS,		000200,		"rts" },
{ 0,	MARK,		006400,		"mark" },
{ 0,	SOB,		077000,		"sob" },
{ 0,	SPL,		0230,		"spl" },
{ 0,	OP_NO,		0240,		"nop" },
{ 0,	TRAP,		0104000,	"emt" },
{ 0,	TRAP,		0104400,	"trap" },
{ 0,	TRAP,		0104400,	"sys" },
{ 0,	OP_NO,		03,		"bpt" },
{ 0,	OP_NO,		04,		"iot" },
{ 0,	OP_NO,		02,		"rti" },
{ 0,	OP_NO,		06,		"rtt" },
{ 0,	OP_NO,		0,		"halt" },
{ 0,	OP_NO,		01,		"wait" },
{ 0,	OP_NO,		05,		"reset" },

/* PDP-11/45, 11/70 floating point processor */
{ 0,	OP_NO,		0170000,	"cfcc" },
{ 0,	OP_NO,		0170001,	"setf" },
{ 0,	OP_NO,		0170002,	"seti" },
{ 0,	OP_NO,		0170011,	"setd" },
{ 0,	OP_NO,		0170012,	"setl" },
{ 0,	FOP_SO,		0170100,	"ldfps" },
{ 0,	FOP_SO,		0170200,	"stfps" },
{ 0,	FOP_SO,		0170300,	"stst" },
{ 0,	FOP_FSO,	0170400,	"clrf" },
{ 0,	FOP_FSO,	0170500,	"tstf" },
{ 0,	FOP_FSO,	0170600,	"absf" },
{ 0,	FOP_FSO,	0170700,	"negf" },
{ 0,	FOP_FSO_FR,	0171000,	"mulf" },
{ 0,	FOP_FSO_FR,	0171400,	"modf" },
{ 0,	FOP_FSO_FR,	0172000,	"addf" },
{ 0,	FOP_FSO_FR,	0173000,	"subf" },
{ 0,	FOP_FSO_FR,	0173400,	"cmpf" },
{ 0,	FOP_FSO_FR,	0174400,	"divf" },

{ 0,	CLEARCC,	0241,		"clc" },
{ 0,	CLEARCC,	0242,		"clv" },
{ 0,	CLEARCC,	0244,		"clz" },
{ 0,	CLEARCC,	0250,		"cln" },
{ 0,	SETCC,		0261,		"sec" },
{ 0,	SETCC,		0262,		"sev" },
{ 0,	SETCC,		0264,		"sez" },
{ 0,	SETCC,		0270,		"sen" },

/* Extended Arithmatic (EAE) */
{ 0,	OP_SO_R,	070000,		"mul" },
{ 0,	OP_SO_R,	071000,		"div" },
{ 0,	OP_SO_R,	072000,		"ash" },
{ 0,	OP_SO_R,	073000,		"ashc" },

{ 0,	MFP,		006500,		"mfpi" },
{ 0,	MFP,		0106500,	"mfpd" },
{ 0,	MFP,		006600,		"mtpi" },
{ 0,	MFP,		0106600,	"mtpd" },

{ 0,	MOVF,		0,		"movf" },
{ 0,	FOP_SO_FR,	0177000,	"movif" },
{ 0,	FOP_SO_FR,	0176400,	"movie" },
{ 0,	FOP_FR_SO,	0175400,	"movfi" },
{ 0,	FOP_FR_SO,	0175000,	"movei" },
{ 0,	FOP_FSO_FR,	0177400,	"movof" },
{ 0,	FOP_FR_FSO,	0176000,	"movfo" },
