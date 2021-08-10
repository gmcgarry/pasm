
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

#define LISTING
#define ASLD
#define THREE_PASS

/* ========== Machine independent type declarations ========== */

#define PASS_1          0
#define PASS_2          1
#define PASS_3          2

#define PASS_SYMB       (pass != PASS_1)
#define PASS_RELO       (pass != PASS_1)

#define IGNORECASE

/*
#define WORDS_REVERSED
#define BYTES_REVERSED
*/

#undef ADDR_T
#define ADDR_T long

#undef word_t
#define word_t	long

#define ALIGNWORD	4
#define ALIGNSECT	4
#define VALWIDTH	8

/* Some character constants for scanner*/
#define ASC_COMMENT     '@'
#define CTRL(x)         ((x) & 037)
#define ISALPHA(c)      (isalpha(c) || (c) == '_' || (c) == '.' || (c) == '%')
#define ISALNUM(c)      (isalnum(c) || (c) == '_' || (c) == '.')

#define ELFM	"%"

#define S_REG		0xF
#define S_NUM		0x8

#define	ADC	0x00A00000
#define	ADD	0x00800000
#define	AND	0x00000000
#define	BIC	0x01C00000
#define	EOR	0x00200000
#define	ORR	0x01800000
#define	RSB	0x00600000
#define	RSC	0x00E00000
#define	SBC	0x00C00000
#define	SUB	0x00400000
#define	MOV	0x01A00000
#define	MVN	0x01E00000
#define	CMN	0x01700000
#define	CMP	0x01500000
#define	TEQ	0x01300000
#define	TST	0x01100000
#define LDR	0x04100000
#define STR	0x04000000
