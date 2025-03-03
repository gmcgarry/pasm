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
 * INTEL 80386 options
 */

#define	THREE_PASS	/* branch and offset optimization */
#define	LISTING		/* enable listing facilities */

#define ADDR_T		long

#define ALIGNWORD	1
#define ALIGNSECT	1

#define IGNORECASE	1

/* ========== Machine independent type declarations ========== */

#define	PASS_1		0
#define	PASS_2		1
#define	PASS_3		2

#define	PASS_SYMB	(pass != PASS_1)
#define	PASS_RELO	(pass != PASS_1)

/* Some character constants for scanner*/
#define ASC_COMMENT     '#'
#define	CTRL(x)		((x) & 037)
#define ISALPHA(c)	(isalpha(c) || (c) == '_' || (c) == '.' || (c) == '@' || (c) == '%')
#if 0
/* XXXGJM: allowing '-' in identifiers causes problems with expressions, but GCC does this for its section name */
#define ISALNUM(c)	(isalnum(c) || (c) == '_' || (c) == '.' || (c) == '-')
#endif
#define ISALNUM(c)	(isalnum(c) || (c) == '_' || (c) == '.')
