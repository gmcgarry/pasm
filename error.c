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

/* ---------- Error handling ---------- */

#include <stdio.h>
#include <stdarg.h>

#include "as.h"
#include "error.h"

extern void stop();


/* ARGSUSED */
void
yyerror(const char* message)
{
	/* we will do our own error printing */
}

void
nosect(void)
{
	fatal("no sections");
}

void
nofit(void)
{
	if (pass == PASS_3)
		warning("too big");
}

static void
diag(const char* tail, const char* s, va_list ap)
{
	fflush(stdout);
	if (modulename)
		fprintf(stderr, "\"%s\", line %ld: ", modulename, lineno);
	else
		fprintf(stderr, "%s: ", progname);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "%s", tail);
}

/* VARARGS1 */
void
fatal(const char* s, ...)
{
	va_list ap;
	va_start(ap, s);

	nerrors++;
	diag(" (fatal)\n", s, ap);
	stop();

	va_end(ap);
}

/* VARARGS1 */
void
serror(const char* s, ...)
{
	va_list ap;
	va_start(ap, s);

	nerrors++;
	diag("\n", s, ap);
	stop();

	va_end(ap);
}

/* VARARGS1 */
void
warning(const char* s, ...)
{
	va_list ap;
	va_start(ap, s);

	nerrors++;
	diag(" (warning)\n", s, ap);
/*	stop(); */

	va_end(ap);
}
