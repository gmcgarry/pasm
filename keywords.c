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
 * storage allocation for variables
 */

#include "as.h"

#include "y.tab.h"

item_t	keytab[] = {
#if 0
	{ 0,	PSEUDOOP_EXTERN,	0,		".define" },
	{ 0,	PSEUDOOP_EXTERN,	0,		".extern" },
#endif

	{ 0,	DOT,			0,		"." },

	{ 0,	PSEUDOOP_DATA,		BYTESIZE,	".byte" },
	{ 0,	PSEUDOOP_DATA,		WORDSIZE,	".word" },
	{ 0,	PSEUDOOP_DATA,		DWORDSIZE,	".dword" },
	{ 0,	PSEUDOOP_DATA,		LONGSIZE,	".long" },
	{ 0,	PSEUDOOP_DATA8,		QUADSIZE,	".quad" },
	{ 0,	PSEUDOOP_ZERO,		0,		".zero" },
	{ 0,	PSEUDOOP_ASCII,		0,		".ascii" },
	{ 0,	PSEUDOOP_ASCII,		1,		".asciz" },
	{ 0,	PSEUDOOP_ASCII,		1,		".string" },
	{ 0,	PSEUDOOP_ALIGN,		0,		".align" },
	{ 0,	PSEUDOOP_ALIGN,		0,		".p2align" },
	{ 0,	PSEUDOOP_ALIGN,		1,		".balign" },
	{ 0,	PSEUDOOP_ASSERT,	0,		".assert" },
	{ 0,	PSEUDOOP_SPACE,		0,		".space" },
	{ 0,	PSEUDOOP_SEEK,		0,		".seek" },
	{ 0,	PSEUDOOP_COMMON,	0,		".comm" },
	{ 0,	PSEUDOOP_BASE,		0,		".base"},
	{ 0,	PSEUDOOP_ORG,		0,		".org" },
	{ 0,	PSEUDOOP_SECTION,	0,		".section" },
	{ 0,	PSEUDOOP_END,		0,		".end" },
	{ 0,	PSEUDOOP_GLOBAL,	1,		".globl" },
	{ 0,	PSEUDOOP_GLOBAL,	1,		".global" },
	{ 0,	PSEUDOOP_GLOBAL,	0,		".local" },
	{ 0,	PSEUDOOP_WEAK,		0,		".weak" },
	{ 0,	PSEUDOOP_EQU,		0,		".equ" },
	{ 0,	PSEUDOOP_EQU,		0,		".set" },
	{ 0,	PSEUDOOP_LINE,		0,		".line" },
	{ 0,	PSEUDOOP_FILE,		0,		".file" },
	{ 0,	PSEUDOOP_TYPE,		0,		".type" },
	{ 0,	PSEUDOOP_SIZE,		0,		".size" },
	{ 0,	PSEUDOOP_IDENT,		0,		".ident" },
#ifdef LISTING
	{ 0,	PSEUDOOP_LIST,		0,		".nolist" },
	{ 0,	PSEUDOOP_LIST,		1,		".list" },
#endif
	{ 0,	PSEUDOOP_MESSAGE,	1,		".message" },
	{ 0,	PLT,			0,		ELFM "PLT" },
	{ 0,	ELF_SYMTYPE,		S_FUNC,		ELFM "function" },
	{ 0,	ELF_SYMTYPE,		S_OBJECT,	ELFM "object" },
	{ 0,	ELF_SHTYPE,		SHT_PROGBITS,	ELFM "progbits" },
	{ 0,	ELF_SHTYPE,		SHT_NOBITS,	ELFM "nobits" },
	{ 0,	ELF_SHTYPE,		SHT_NOTE,	ELFM "note" },

	{ 0,	PSEUDOOP_CFI_IGNORE,	0,		".cfi_def_cfa" },
       	{ 0,	PSEUDOOP_CFI_IGNORE,	0,		".cfi_def_cfa_offset" },
       	{ 0,	PSEUDOOP_CFI_IGNORE,	0,		".cfi_def_cfa_register" },
 	{ 0,	PSEUDOOP_CFI_IGNORE,	0,		".cfi_endproc" },
 	{ 0,	PSEUDOOP_CFI_IGNORE,	0,		".cfi_offset" },
 	{ 0,	PSEUDOOP_CFI_IGNORE,	0,		".cfi_startproc" },

#include "keywords.inc"

	 { 0,	0,			0,		0 },
};
