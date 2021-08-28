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

/*
 * INTEL 80386 keywords
 *
 * No system registers for now ...
 */

	/* some intel compatibility */
	{ 0,	PSEUDOOP_DATA,	2,		"dw" },
	{ 0,	PSEUDOOP_DATA,	1,		"db" },
	{ 0,	PSEUDOOP_CPU,	0,		"cpu" },
	{ 0,	'=',		0,		"equ" },

	{ 0,	PSEUDOOP_USE16,	0,		".code16" },
	{ 0,	PSEUDOOP_USE32,	0,		".code32" },
	{ 0,	PSEUDOOP_USE64,	0,		".code64" },

	{ 0,	R16,		0,		"%ax" },
	{ 0,	R16,		1,		"%cx" },
	{ 0,	R16,		2,		"%dx" },
	{ 0,	R16,		3,		"%bx" },
	{ 0,	R16,		4,		"%sp" },
	{ 0,	R16,		5,		"%bp" },
	{ 0,	R16,		6,		"%si" },
	{ 0,	R16,		7,		"%di" },
	{ 0,	R32,		0,		"%eax" },
	{ 0,	R32,		1,		"%ecx" },
	{ 0,	R32,		2,		"%edx" },
	{ 0,	R32,		3,		"%ebx" },
	{ 0,	R32,		4,		"%esp" },
	{ 0,	R32,		5,		"%ebp" },
	{ 0,	R32,		6,		"%esi" },
	{ 0,	R32,		7,		"%edi" },
	{ 0,	R8,		0,		"%al" },
	{ 0,	R8,		1,		"%cl" },
	{ 0,	R8,		2,		"%dl" },
	{ 0,	R8,		3,		"%bl" },
	{ 0,	R8,		4,		"%ah" },
	{ 0,	R8,		5,		"%ch" },
	{ 0,	R8,		6,		"%dh" },
	{ 0,	R8,		7,		"%bh" },
	{ 0,	RSEG,		0,		"%es" },
	{ 0,	RSEG,		1,		"%cs" },
	{ 0,	RSEG,		2,		"%ss" },
	{ 0,	RSEG,		3,		"%ds" },
	{ 0,	RSEG,		4,		"%fs" },
	{ 0,	RSEG,		5,		"%gs" },

	{ 0,	R64,		0,		"%rax" },
	{ 0,	R64,		1,		"%rcx" },
	{ 0,	R64,		2,		"%rdx" },
	{ 0,	R64,		3,		"%rbx" },
	{ 0,	R64,		4,		"%rsp" },
	{ 0,	R64,		5,		"%rbp" },
	{ 0,	R64,		6,		"%rsi" },
	{ 0,	R64,		7,		"%rdi" },
	{ 0,	R64,		8,		"%r8" },
	{ 0,	R64,		9,		"%r9" },
	{ 0,	R64,		10,		"%r10" },
	{ 0,	R64,		11,		"%r11" },
	{ 0,	R64,		12,		"%r12" },
	{ 0,	R64,		13,		"%r13" },
	{ 0,	R64,		14,		"%r14" },
	{ 0,	R64,		15,		"%r15" },

	{ 0,	R32X,		8,		"%r8b" },
	{ 0,	R32X,		9,		"%r9b" },
	{ 0,	R32X,		10,		"%r10b" },
	{ 0,	R32X,		11,		"%r11b" },
	{ 0,	R32X,		12,		"%r12b" },
	{ 0,	R32X,		13,		"%r13b" },
	{ 0,	R32X,		14,		"%r14b" },
	{ 0,	R32X,		15,		"%r15b" },

	{ 0,	RIP,		0,		"%rip" },

	{ 0,	RSYSCR,		0,		"%cr0" },
	{ 0,	RSYSCR,		2,		"%cr2" },
	{ 0,	RSYSCR,		3,		"%cr3" },
	{ 0,	RSYSDR,		0,		"%dr0" },
	{ 0,	RSYSDR,		1,		"%dr1" },
	{ 0,	RSYSDR,		2,		"%dr2" },
	{ 0,	RSYSDR,		3,		"%dr3" },
	{ 0,	RSYSDR,		6,		"%dr6" },
	{ 0,	RSYSDR,		7,		"%dr7" },
	{ 0,	RSYSTR,		3,		"%tr3" },	/* i486 */
	{ 0,	RSYSTR,		4,		"%tr4" },	/* i486 */
	{ 0,	RSYSTR,		5,		"%tr5" },	/* i486 */
	{ 0,	RSYSTR,		6,		"%tr6" },
	{ 0,	RSYSTR,		7,		"%tr7" },

	{ 0,	PREFIX,		0xf2,		"repne" },
	{ 0,	PREFIX,		0xf2,		"repnz" },
	{ 0,	PREFIX,		0xf3,		"rep" },
	{ 0,	PREFIX,		0xf3,		"repe" },
	{ 0,	PREFIX,		0xf3,		"repz" },
	{ 0,	PREFIX,		0xf0,		"lock" },

	{ 0,	PREFIX,		0x26,		"eseg" },
	{ 0,	PREFIX,		0x2e,		"cseg" },
	{ 0,	PREFIX,		0x36,		"sseg" },
	{ 0,	PREFIX,		0x3e,		"dseg" },
	{ 0,	PREFIX,		0x64,		"fseg" },
	{ 0,	PREFIX,		0x65,		"gseg" },

	{ 0,	OTOGGLE,	0x66,		"data16" },	/* while in 32-bit mode */
	{ 0,	ATOGGLE,	0x67,		"addr16" },
	{ 0,	OTOGGLE,	0x66,		"data32" },	/* while in 16-bit mode */
	{ 0,	ATOGGLE,	0x67,		"addr32" },

	{ 0,	ADDOP,		000,		"addb" },
	{ 0,	ADDOP,		001,		"add" },
	{ 0,	ADDOP,		010,		"orb" },
	{ 0,	ADDOP,		011,		"or" },
	{ 0,	ADDOP,		020,		"adcb" },
	{ 0,	ADDOP,		021,		"adc" },
	{ 0,	ADDOP,		030,		"sbbb" },
	{ 0,	ADDOP,		031,		"sbb" },
	{ 0,	ADDOP,		040,		"andb" },
	{ 0,	ADDOP,		041,		"and" },

	{ 0,	ADDOP,		050,		"subb" },
	{ 0,	ADDOP,		051,		"sub" },
	{ 0,	ADDOP,		060,		"xorb" },
	{ 0,	ADDOP,		061,		"xor" },
	{ 0,	ADDOP,		070,		"cmpb" },
	{ 0,	ADDOP,		071,		"cmp" },
	{ 0,	BITTEST,	04,		"bt" },
	{ 0,	BITTEST,	05,		"bts" },
	{ 0,	BITTEST,	06,		"btr" },
	{ 0,	BITTEST,	07,		"btc" },

	{ 0,	CALFOP,		030+(0232<<8),	"lcall" }, /* 0x9a 0x18 - far segmented call, address in operand */
	{ 0,	CALFOP,		050+(0352<<8),	"ljmp" },  /* 0xea 0x28 */
	{ 0,	CALLOP,		020+(0350<<8),	"call" },  /* 0xe8 0x10 - near call, relative displacement in operand */
	{ 0,	CALLOP,		040+(0351<<8),	"jmp" },	  /* 0xe9 0x20 */

	{ 0,	ENTER,		0310,		"enter" },
	{ 0,	EXTEND,		0267,		"movzx" },
	{ 0,	EXTEND,		0266,		"movzxb" },
	{ 0,	EXTEND,		0277,		"movsx" },
	{ 0,	EXTEND,		0276,		"movsxb" },
	{ 0,	EXTOP,		0002,		"lar" },
	{ 0,	EXTOP,		0003,		"lsl" },
	{ 0,	EXTOP,		0274,		"bsf" },
	{ 0,	EXTOP,		0275,		"bsr" },
	{ 0,	EXTOP1,		0000,		"sldt" },
	{ 0,	EXTOP1,		0001,		"sgdt" },
#if 0
	{ 0,	EXTOP1,		0010,		"str" },
#endif
	{ 0,	EXTOP1,		0011,		"sidt" },
	{ 0,	EXTOP1,		0020,		"lldt" },
	{ 0,	EXTOP1,		0021,		"lgdt" },
	{ 0,	EXTOP1,		0030,		"ltr" },
	{ 0,	EXTOP1,		0031,		"lidt" },
	{ 0,	EXTOP1,		0040,		"verr" },
	{ 0,	EXTOP1,		0041,		"smsw" },
	{ 0,	EXTOP1,		0050,		"verw" },
	{ 0,	EXTOP1,		0061,		"lmsw" },
	{ 0,	IMUL,		0,		"imul" },
	{ 0,	IMULB,		050,		"imulb" },
	{ 0,	INCOP,		000,		"incb" },
	{ 0,	INCOP,		001,		"inc" },
	{ 0,	INCOP,		010,		"decb" },
	{ 0,	INCOP,		011,		"dec" },
	{ 0,	INT,		0,		"int" },
	{ 0,	IOOP,		0344,		"inb" },
	{ 0,	IOOP,		0345,		"in" },
	{ 0,	IOOP,		0346,		"outb" },
	{ 0,	IOOP,		0347,		"out" },
	{ 0,	JOP,		0340,		"loopne" },
	{ 0,	JOP,		0340,		"loopnz" },
	{ 0,	JOP,		0341,		"loope" },
	{ 0,	JOP,		0341,		"loopz" },
	{ 0,	JOP,		0342,		"loop" },
	{ 0,	JOP,		0343,		"jcxz" },
	{ 0,	JOP,		0343,		"jecxz" },
	{ 0,	JOP2,		0000,		"jo" },
	{ 0,	JOP2,		0001,		"jno" },
	{ 0,	JOP2,		0002,		"jb" },
	{ 0,	JOP2,		0002,		"jc" },
	{ 0,	JOP2,		0002,		"jnae" },
	{ 0,	JOP2,		0003,		"jae" },
	{ 0,	JOP2,		0003,		"jnb" },
	{ 0,	JOP2,		0003,		"jnc" },
	{ 0,	JOP2,		0004,		"je" },
	{ 0,	JOP2,		0004,		"jz" },
	{ 0,	JOP2,		0005,		"jne" },
	{ 0,	JOP2,		0005,		"jnz" },
	{ 0,	JOP2,		0006,		"jbe" },
	{ 0,	JOP2,		0006,		"jna" },
	{ 0,	JOP2,		0007,		"ja" },
	{ 0,	JOP2,		0007,		"jnbe" },
	{ 0,	JOP2,		0010,		"js" },
	{ 0,	JOP2,		0011,		"jns" },
	{ 0,	JOP2,		0012,		"jp" },
	{ 0,	JOP2,		0012,		"jpe" },
	{ 0,	JOP2,		0013,		"jnp" },
	{ 0,	JOP2,		0013,		"jpo" },
	{ 0,	JOP2,		0014,		"jl" },
	{ 0,	JOP2,		0014,		"jnge" },
	{ 0,	JOP2,		0015,		"jge" },
	{ 0,	JOP2,		0015,		"jnl" },
	{ 0,	JOP2,		0016,		"jle" },
	{ 0,	JOP2,		0016,		"jng" },
	{ 0,	JOP2,		0017,		"jg" },
	{ 0,	JOP2,		0017,		"jnle" },
	{ 0,	LEAOP,		0142,		"bound" },
	{ 0,	LEAOP,		0215,		"lea" },
	{ 0,	LEAOP,		0304,		"les" },
	{ 0,	LEAOP,		0305,		"lds" },
	{ 0,	LEAOP2,		0262,		"lss" },
	{ 0,	LEAOP2,		0264,		"lfs" },
	{ 0,	LEAOP2,		0265,		"lgs" },
	{ 0,	LSHFT,		0244,		"shld" },
	{ 0,	LSHFT,		0254,		"shrd" },
	{ 0,	MOV,		0,		"movb" },
	{ 0,	MOV,		1,		"mov" },
	{ 0,	NOOP_1,		0140,		"pusha" },
	{ 0,	NOOP_1,		0140,		"pushad" },
	{ 0,	NOOP_1,		0141,		"popa" },
	{ 0,	NOOP_1,		0141,		"popad" },
	{ 0,	NOOP_1,		0156,		"outsb" },
	{ 0,	NOOP_1,		0157,		"outs" },
	{ 0,	NOOP_1,		0220,		"nop" },
	{ 0,	NOOP_1,		0230,		"cbw" },
	{ 0,	NOOP_1,		0230,		"cwde" }, /* same opcode as cbw! */
	{ 0,	NOOP_1,		0231,		"cdq" },	/* same opcode as cwd! */
	{ 0,	NOOP_1,		0231,		"cwd" },


	{ 0,	NOOP_1,		0233,		"wait" },
	{ 0,	NOOP_1,		0234,		"pushf" },
	{ 0,	NOOP_1,		0235,		"popf" },
	{ 0,	NOOP_1,		0236,		"sahf" },
	{ 0,	NOOP_1,		0237,		"lahf" },
	{ 0,	NOOP_1,		0244,		"movsb" },
	{ 0,	NOOP_1,		0245,		"movs" },
	{ 0,	NOOP_1,		0246,		"cmpsb" },
	{ 0,	NOOP_1,		0154,		"insb" },
	{ 0,	NOOP_1,		0247,		"cmps" },
	{ 0,	NOOP_1,		0155,		"ins" },
	{ 0,	NOOP_1,		0252,		"stosb" },
	{ 0,	NOOP_1,		0253,		"stos" },
	{ 0,	NOOP_1,		0254,		"lodsb" },
	{ 0,	NOOP_1,		0255,		"lods" },
	{ 0,	NOOP_1,		0256,		"scasb" },
	{ 0,	NOOP_1,		0257,		"scas" },
	{ 0,	NOOP_1,		0311,		"leave" },
	{ 0,	NOOP_1,		0316,		"into" },
	{ 0,	NOOP_1,		0317,		"iret" },
	{ 0,	NOOP_1,		0317,		"iretd" },
	{ 0,	NOOP_1,		0327,		"xlat" },
	{ 0,	NOOP_1,		0364,		"hlt" },
	{ 0,	NOOP_1,		0365,		"cmc" },
	{ 0,	NOOP_1,		0370,		"clc" },
	{ 0,	NOOP_1,		0371,		"stc" },
	{ 0,	NOOP_1,		0372,		"cli" },
	{ 0,	NOOP_1,		0373,		"sti" },
	{ 0,	NOOP_1,		0374,		"cld" },
	{ 0,	NOOP_1,		0375,		"std" },
	{ 0,	NOOP_1,		047,		"daa" },
	{ 0,	NOOP_1,		057,		"das" },
	{ 0,	NOOP_1,		067,		"aaa" },
	{ 0,	NOOP_1,		077,		"aas" },
	{ 0,	NOOP_2,		017+(06<<8),	"clts" },
	{ 0,	NOOP_2,		0324+(012<<8),	"aam" },
	{ 0,	NOOP_2,		0325+(012<<8),	"aad" },
	{ 0,	NOTOP,		020,		"notb" },
	{ 0,	NOTOP,		021,		"not" },
	{ 0,	NOTOP,		030,		"negb" },
	{ 0,	NOTOP,		031,		"neg" },
	{ 0,	NOTOP,		040,		"mulb" },
	{ 0,	NOTOP,		041,		"mul" },
	{ 0,	NOTOP,		060,		"divb" },
	{ 0,	NOTOP,		061,		"div" },
	{ 0,	NOTOP,		070,		"idivb" },
	{ 0,	NOTOP,		071,		"idiv" },


	{ 0,	PUSHOP,		0,		"push" },
	{ 0,	PUSHOP,		1,		"pop" },
	{ 0,	RET,		0303,		"ret" },
	{ 0,	RET,		0313,		"retf" },
	{ 0,	ROLOP,		000,		"rolb" },
	{ 0,	ROLOP,		001,		"rol" },
	{ 0,	ROLOP,		010,		"rorb" },
	{ 0,	ROLOP,		011,		"ror" },
	{ 0,	ROLOP,		020,		"rclb" },
	{ 0,	ROLOP,		021,		"rcl" },
	{ 0,	ROLOP,		030,		"rcrb" },
	{ 0,	ROLOP,		031,		"rcr" },
	{ 0,	ROLOP,		040,		"salb" },
	{ 0,	ROLOP,		040,		"shlb" },
	{ 0,	ROLOP,		041,		"sal" },
	{ 0,	ROLOP,		041,		"shl" },
	{ 0,	ROLOP,		050,		"shrb" },
	{ 0,	ROLOP,		051,		"shr" },
	{ 0,	ROLOP,		070,		"sarb" },
	{ 0,	ROLOP,		071,		"sar" },
	{ 0,	SETCC,		0000,		"seto" },
	{ 0,	SETCC,		0001,		"setno" },
	{ 0,	SETCC,		0002,		"setb" },
	{ 0,	SETCC,		0002,		"setnae" },
	{ 0,	SETCC,		0003,		"setae" },
	{ 0,	SETCC,		0003,		"setnb" },
	{ 0,	SETCC,		0004,		"sete" },
	{ 0,	SETCC,		0004,		"setz" },
	{ 0,	SETCC,		0005,		"setne" },
	{ 0,	SETCC,		0005,		"setnz" },
	{ 0,	SETCC,		0006,		"setbe" },
	{ 0,	SETCC,		0006,		"setna" },
	{ 0,	SETCC,		0007,		"seta" },
	{ 0,	SETCC,		0007,		"setnbe" },
	{ 0,	SETCC,		0010,		"sets" },
	{ 0,	SETCC,		0011,		"setns" },
	{ 0,	SETCC,		0012,		"setp" },
	{ 0,	SETCC,		0012,		"setpe" },
	{ 0,	SETCC,		0013,		"setnp" },
	{ 0,	SETCC,		0013,		"setpo" },
	{ 0,	SETCC,		0014,		"setl" },
	{ 0,	SETCC,		0014,		"setnge" },
	{ 0,	SETCC,		0015,		"setge" },
	{ 0,	SETCC,		0015,		"setnl" },
	{ 0,	SETCC,		0016,		"setle" },
	{ 0,	SETCC,		0016,		"setng" },
	{ 0,	SETCC,		0017,		"setg" },
	{ 0,	SETCC,		0017,		"setnle" },
	{ 0,	TEST,		0,		"testb" },
	{ 0,	TEST,		1,		"test" },
	{ 0,	XCHG,		0,		"xchgb" },
	{ 0,	XCHG,		1,		"xchg" },
	{ 0,	ARPLOP,		0143,		"arpl" },

/* Intel 80[23]87 coprocessor keywords */

	{ 0,	ST,		0,			"%st" },

	{ 0,	FNOOP,		FESC+1+(0xF0<<8),	"f2xm1" },
	{ 0,	FNOOP,		FESC+1+(0xE1<<8),	"fabs" },
	{ 0,	FNOOP,		FESC+1+(0xE0<<8),	"fchs" },
	{ 0,	FNOOP,		FESC+3+(0xE2<<8),	"fclex" },

	{ 0,	FNOOP,		FESC+6+(0xD9<<8),	"fcompp" },
	{ 0,	FNOOP,		FESC+2+(0xE9<<8),	"fucompp" }, /* DA E9 */

	{ 0,	FNOOP,		FESC+1+(0xF6<<8),	"fdecstp" },
	{ 0,	FNOOP,		FESC+3+(0xE1<<8),	"fdisi" },
	{ 0,	FNOOP,		FESC+3+(0xE0<<8),	"feni" },
	{ 0,	FNOOP,		FESC+1+(0xF7<<8),	"fincstp" },
	{ 0,	FNOOP,		FESC+3+(0xE3<<8),	"finit" },
	{ 0,	FNOOP,		FESC+1+(0xE8<<8),	"fld1" },
	{ 0,	FNOOP,		FESC+1+(0xEA<<8),	"fldl2e" },
	{ 0,	FNOOP,		FESC+1+(0xE9<<8),	"fldl2t" },
	{ 0,	FNOOP,		FESC+1+(0xEC<<8),	"fldlg2" },
	{ 0,	FNOOP,		FESC+1+(0xED<<8),	"fldln2" },
	{ 0,	FNOOP,		FESC+1+(0xEB<<8),	"fldpi" },
	{ 0,	FNOOP,		FESC+1+(0xEE<<8),	"fldz" },
	{ 0,	FNOOP,		FESC+1+(0xD0<<8),	"fnop" },
	{ 0,	FNOOP,		FESC+1+(0xF3<<8),	"fpatan" },
	{ 0,	FNOOP,		FESC+1+(0xFF<<8),	"fcos" },
	{ 0,	FNOOP,		FESC+1+(0xFE<<8),	"fsin" },
	{ 0,	FNOOP,		FESC+1+(0xFB<<8),	"fsincos" },
	{ 0,	FNOOP,		FESC+1+(0xF8<<8),	"fprem" },
	{ 0,	FNOOP,		FESC+1+(0xF5<<8),	"fprem1" },
	{ 0,	FNOOP,		FESC+1+(0xF2<<8),	"fptan" },
	{ 0,	FNOOP,		FESC+1+(0xFC<<8),	"frndint" },
	{ 0,	FNOOP,		FESC+1+(0xFD<<8),	"fscale" },
	{ 0,	FNOOP,		FESC+1+(0xFA<<8),	"fsqrt" },
	{ 0,	FNOOP,		FESC+1+(0xE4<<8),	"ftst" },
	{ 0,	FNOOP,		FESC+1+(0xE5<<8),	"fxam" },
	{ 0,	FNOOP,		FESC+1+(0xF4<<8),	"fxtract" },
	{ 0,	FNOOP,		FESC+1+(0xF1<<8),	"fyl2x" },
	{ 0,	FNOOP,		FESC+1+(0xF9<<8),	"fyl2xp1" },

	{ 0,	FMEM,		FESC+6+(0<<11),		"fiadds" },
	{ 0,	FMEM,		FESC+2+(0<<11),		"fiaddl" },
	{ 0,	FMEM,		FESC+0+(0<<11),		"fadds" },
	{ 0,	FMEM,		FESC+4+(0<<11),		"faddd" },
	{ 0,	FMEM,		FESC+7+(4<<11),		"fbld" },
	{ 0,	FMEM,		FESC+7+(6<<11),		"fbstp" },
	{ 0,	FMEM,		FESC+6+(2<<11),		"ficoms" },
	{ 0,	FMEM,		FESC+2+(2<<11),		"ficoml" },
	{ 0,	FMEM,		FESC+0+(2<<11),		"fcoms" },
	{ 0,	FMEM,		FESC+4+(2<<11),		"fcomd" },
	{ 0,	FMEM,		FESC+6+(3<<11),		"ficomps" },
	{ 0,	FMEM,		FESC+2+(3<<11),		"ficompl" },
	{ 0,	FMEM,		FESC+0+(3<<11),		"fcomps" },
	{ 0,	FMEM,		FESC+4+(3<<11),		"fcompd" },
	{ 0,	FMEM,		FESC+6+(6<<11),		"fidivs" },
	{ 0,	FMEM,		FESC+2+(6<<11),		"fidivl" },
	{ 0,	FMEM,		FESC+0+(6<<11),		"fdivs" },
	{ 0,	FMEM,		FESC+4+(6<<11),		"fdivd" },
	{ 0,	FMEM,		FESC+6+(7<<11),		"fidivrs" },
	{ 0,	FMEM,		FESC+2+(7<<11),		"fidivrl" },
	{ 0,	FMEM,		FESC+0+(7<<11),		"fdivrs" },
	{ 0,	FMEM,		FESC+4+(7<<11),		"fdivrd" },
	{ 0,	FMEM,		FESC+7+(5<<11),		"fildq" },
	{ 0,	FMEM,		FESC+7+(0<<11),		"filds" },
	{ 0,	FMEM,		FESC+3+(0<<11),		"fildl" },
	{ 0,	FMEM,		FESC+1+(0<<11),		"flds" },
	{ 0,	FMEM,		FESC+5+(0<<11),		"fldd" },
	{ 0,	FMEM,		FESC+3+(5<<11),		"fldx" },
	{ 0,	FMEM,		FESC+1+(5<<11),		"fldcw" },
	{ 0,	FMEM,		FESC+1+(4<<11),		"fldenv" },
	{ 0,	FMEM,		FESC+6+(1<<11),		"fimuls" },
	{ 0,	FMEM,		FESC+2+(1<<11),		"fimull" }, 
	{ 0,	FMEM,		FESC+0+(1<<11),		"fmuls" }, /* aka fmull */
	{ 0,	FMEM,		FESC+4+(1<<11),		"fmuld" }, /* aka fmulq */
	{ 0,	FMEM,		FESC+5+(4<<11),		"frstor" },
	{ 0,	FMEM,		FESC+5+(6<<11),		"fsave" },
	{ 0,	FMEM,		FESC+7+(2<<11),		"fists" },
	{ 0,	FMEM,		FESC+3+(2<<11),		"fistl" },
	{ 0,	FMEM,		FESC+1+(2<<11),		"fsts" }, /* aka fstl */
	{ 0,	FMEM,		FESC+5+(2<<11),		"fstd" }, /* aka fstq */

	{ 0,	FMEM,		FESC+7+(3<<11),		"fistps" }, /* DF/3 */
	{ 0,	FMEM,		FESC+3+(3<<11),		"fistpl" }, /* DB/3 */
	{ 0,	FMEM,		FESC+7+(7<<11),		"fistpq" }, /* DF/7 */

	{ 0,	FMEM,		FESC+1+(3<<11),		"fstps" }, /* D9/3 */
	{ 0,	FMEM,		FESC+5+(3<<11),		"fstpl" }, /* DD/3 */
	{ 0,	FMEM,		FESC+3+(7<<11),		"fstpt" }, /* DB/7 */

	{ 0,	FMEM,		FESC+1+(7<<11),		"fstcw" },
	{ 0,	FMEM,		FESC+1+(6<<11),		"fstenv" },
	{ 0,	FMEM_AX,	FESC+5+(7<<11),		"fstsw" },
	{ 0,	FMEM,		FESC+6+(4<<11),		"fisubs" },
	{ 0,	FMEM,		FESC+2+(4<<11),		"fisubl" },
	{ 0,	FMEM,		FESC+0+(4<<11),		"fsubs" },
	{ 0,	FMEM,		FESC+4+(4<<11),		"fsubd" },
	{ 0,	FMEM,		FESC+6+(5<<11),		"fisubrs" },
	{ 0,	FMEM,		FESC+2+(5<<11),		"fisubrl" },
	{ 0,	FMEM,		FESC+0+(5<<11),		"fsubrs" },
	{ 0,	FMEM,		FESC+4+(5<<11),		"fsubrd" },

	{ 0,	FST_I,		FESC+1+(0xC0<<8),	"fld" },
	{ 0,	FST_I,		FESC+5+(0xD0<<8),	"fst" },
	{ 0,	FST_I,		FESC+5+(0xD8<<8),	"fstp" },
	{ 0,	FST_I,		FESC+1+(0xC8<<8),	"fxch" },

	{ 0,	FST_I,		FESC+0+(0xD0<<8),	"fcom" },
	{ 0,	FST_I,		FESC+5+(0xE0<<8),	"fucom" },  /* DD E0+i */
	{ 0,	FST_I,		FESC+0+(0xD8<<8),	"fcomp" },
	{ 0,	FST_I,		FESC+5+(0xE8<<8),	"fucomp" }, /* DD E8+i */

	{ 0,	FST_I,		FESC+5+(0xC0<<8),	"ffree" },

	{ 0,	FST_ST,		FESC+0+(0xC0<<8),	"fadd" },
	{ 0,	FST_ST,		FESC+2+(0xC0<<8),	"faddp" },
	{ 0,	FST_ST2,	FESC+0+(0xF0<<8),	"fdiv" },
	{ 0,	FST_ST2,	FESC+2+(0xF0<<8),	"fdivp" },
	{ 0,	FST_ST2,	FESC+0+(0xF8<<8),	"fdivr" },
	{ 0,	FST_ST2,	FESC+2+(0xF8<<8),	"fdivrp" },
	{ 0,	FST_ST,		FESC+0+(0xC8<<8),	"fmul" },
	{ 0,	FST_ST,		FESC+2+(0xC8<<8),	"fmulp" }, /* DA C8+i */
	{ 0,	FST_ST2,	FESC+0+(0xE0<<8),	"fsub" },
	{ 0,	FST_ST2,	FESC+2+(0xE0<<8),	"fsubp" },
	{ 0,	FST_ST2,	FESC+0+(0xE8<<8),	"fsubr" },
	{ 0,	FST_ST2,	FESC+2+(0xE8<<8),	"fsubrp" },

	{ 0,	FST_ST2,	FESC+3+(0xF0<<8),	"fcomi" },  /* DB F0+i */
	{ 0,	FST_ST2,	FESC+7+(0xF0<<8),	"fcomip" }, /* DF F0+i */
	{ 0,	FST_ST2,	FESC+3+(0xE8<<8),	"fucomi" }, /* DB E8+i */
	{ 0,	FST_ST2,	FESC+7+(0xE8<<8),	"fucomip" },/* DF E8+i */

/* Intel 486 instructions */
	{ 0,	EXTOPBW,	0xC0,		"xaddb" },
	{ 0,	EXTOPBW,	0xC1,		"xadd" },
	{ 0,	EXTOPBW,	0xB0,		"cmpxchgb" },
	{ 0,	EXTOPBW,	0xB1,		"cmpxchg" },
	{ 0,	BSWAP,		0xC8,		"bswap" },
	{ 0,	NOOP_2,		017+(010<<8),	"invd" },
	{ 0,	EXTOP1,		071,		"invlpg" },
	{ 0,	NOOP_2,		017+(011<<8),	"wbinvd" },

/* AMD64 instructions */

	{ 0,	NOOP_2,		0x0F+(0x05<<8),		"syscall" },

	{ 0,	PUSHOP,		0,		"pushl" },	/* done */
	{ 0,	PUSHOP,		0,		"pushq" },	/* done */
	{ 0,	PUSHOP,		1,		"popl" },	/* done */
	{ 0,	PUSHOP,		1,		"popq" },	/* done */


/* with postfixes */

	{ 0,	MOV,		1,		"movl" },
	{ 0,	MOV,		1,		"movq" },
	{ 0,	LEAOP,		0215,		"leal" },
	{ 0,	LEAOP,		0215,		"leaq" },
	{ 0,	ADDOP,		061,		"xorl" },
	{ 0,	ADDOP,		061,		"xorq" },
	{ 0,	ADDOP,		041,		"andw" },
	{ 0,	ADDOP,		041,		"andl" },
	{ 0,	ADDOP,		041,		"andq" },
	{ 0,	ADDOP,		001,		"addl" },
	{ 0,	ADDOP,		001,		"addq" },
	{ 0,	ADDOP,		051,		"subl" },
	{ 0,	ADDOP,		051,		"subq" },
	{ 0,	ADDOP,		071,		"cmpl" },
	{ 0,	ADDOP,		071,		"cmpq" },
	{ 0,	EXTEND,		0266,		"movzbw" },
	{ 0,	EXTEND,		0266,		"movzbl" },
	{ 0,	EXTEND,		0266,		"movzbq" },
	{ 0,	EXTEND,		0266,		"movzwl" },
	{ 0,	EXTEND,		0266,		"movzwq" },
	{ 0,	ROLOP,		041,		"sall" },
	{ 0,	ROLOP,		041,		"salq" },
	{ 0,	ADDOP,		011,		"orl" },
	{ 0,	ADDOP,		011,		"orq" },
	{ 0,	ROLOP,		071,		"sarl" },
	{ 0,	ROLOP,		071,		"sarq" },
	{ 0,	MOV,		1,		"movw" },
	{ 0,	INCOP,		001,		"incl" },
	{ 0,	INCOP,		001,		"incq" },
	{ 0,	INCOP,		011,		"decl" },
	{ 0,	INCOP,		011,		"decq" },
	{ 0,	EXTEND,		0x63,		"movslq" },

	{ 0,	NOOP_2,		017+(06<<8),	"cltq" },
	{ 0,	TEST,		1,		"testl" },
	{ 0,	CALLOP,		020+(0350<<8),	"callq" },
	{ 0,	NOOP_1,		0311,		"leaveq" },
	{ 0,	RET,		0303,		"retq" },
	{ 0,	RET,		0303,		"retl" },
	{ 0,	ROLOP,		051,		"shrl" },
	{ 0,	NOTOP,		031,		"negl" },
	{ 0,	IMUL,		00,		"imull" },
	{ 0,	NOTOP,		041,		"mull" },
	{ 0,	NOOP_2,		017+(06<<8),	"cltd" },
	{ 0,	NOTOP,		061,		"divl" },
	{ 0,	NOTOP,		071,		"idivl" },
	{ 0,	EXTEND,		0x63,		"movsbl" },
	{ 0,	EXTEND,		0277,		"movswl" },
	{ 0,	LSHFT,		0244,		"shldl" },
	{ 0,	LSHFT,		0254,		"shrdl" },
	{ 0,	ADDOP,		021,		"adcl" },
	{ 0,	ADDOP,		031,		"sbbl" },
	{ 0,	ADDOP,		001,		"addw" },
	{ 0,	PUSHOP,		0,		"pushw" },
	{ 0,	ADDOP,		051,		"subw" },
	{ 0,	PUSHOP,		1,		"popw" },
	{ 0,	ADDOP,		071,		"cmpw" },
	{ 0,	INCOP,		001,		"incw" },
	{ 0,	INCOP,		011,		"decw" },
	{ 0,	NOOP_1,		0231,		"cwtd" },

	{ 0,	FMEM,		FESC+0+(1<<11),		"fmull" }, /* or is this fmuls? */
