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
 * miscellaneous
 */

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "as.h"
#include "error.h"

#include "y.tab.h"

extern sect_t sect[SECTMAX];  /* XXXGJM remove  */


ADDR_T
load(const item_t* ip)
{
        int sct = ip->i_type & S_SCTMASK;
	int typ = ip->i_type & S_TYPEMASK;
#ifdef ASLD
        if (sct == S_UND || sct ==  S_ABS)
                return (ip->i_valu);
        return (ip->i_valu + sect[sct].s_base);
#else
	if (sct == S_UND || typ == S_COMMON) {
#if 0
		DPRINTF(("!!!! symbol \"%s\" is undefined, needs to be relocated (type=0x%x)\n", ip->i_name, ip->i_type));
#endif
		if (pass == PASS_3) {
			if (relonami != RELO_UNDEF)
				//serror("relocation error (symbol='%s', relonami=%d, type=%08x)", ip->i_name ? ip->i_name : "<unknown>", relonami, ip->i_type);
				serror("relocation error");
			relonami = ip->i_valu;
		}
		return 0;
	}
#endif
	return ip->i_valu;
}

int
store(item_t* ip, ADDR_T val)
{
	DPRINTF(("store(%s, type=%x, val=%lx)\n", ip->i_name, ip->i_type, val));

        int sct = ip->i_type & S_SCTMASK;
#if 0 /* def ASLD */
        if (sct != S_UND && sct != S_ABS)
                val -= sect[sct].s_base;
#else
	if (sct == S_UND)
		return 0;
#endif
	assert(pass != PASS_3 || (ip->i_type & S_VAR) || ip->i_valu == val);
	ip->i_valu = val;

	DPRINTF(("storing 0x%lx into %s\n", val, ip->i_name));

	return 1;
}

const char*
remember(const char* s)
{
	const char* src;
	char *dst;
	int n;
	static int nleft = 0;
	static char* next;

	src = s;
	n = 0;
	do {
		n++;
	} while (*src++);
	if ((nleft -= n) < 0) {
		next = malloc(MEMINCR);
		if (next == 0)
			fatal("out of memory");
		nleft = (MEMINCR / sizeof(char)) - n;
		assert(nleft >= 0);
	}
	dst = next;
	while ((*dst++ = *s++))
		;
	s = next;
	next = dst;
	return s;
}

int
combine(int typ1, int typ2, int op)
{
	DPRINTF(("combine(typ1=0x%x, typ2=0x%x, op='%c' (0x%x)\n", typ1, typ2, op, op));

	switch (op) {
#ifndef NO_ASR
		case 'k':
			if (typ1 == S_ABS && typ2 == S_ABS)
				return S_ABS;
			if (typ1 == S_VAR)
				return (S_ABS | S_VAR);
			break;
#endif
		case '+':
			if (typ1 == S_ABS)
				return typ2;
			if (typ2 == S_ABS)
				return typ1;
			break;
		case '-':
			if (typ2 == S_ABS)
				return typ1;
			if ((typ1 & S_SCTMASK) == (typ2 & S_SCTMASK) && typ1 != S_UND)
				return (S_ABS | S_VAR);
			break;
		case '/':	/* used for rounding of bank addresses */
		case '*':
		case '>':
			if (typ1 == S_ABS && typ2 == S_ABS)
				return S_ABS;
			if (((typ1 & S_SCTMASK) == (typ2 & S_SCTMASK) && typ1 != S_UND) || (typ1 == S_ABS) || (typ2 == S_ABS))
				return (S_ABS | S_VAR);
			break;
		default:
			if (typ1 == S_ABS && typ2 == S_ABS)
				return S_ABS;
			break;
	}
	if (pass != PASS_1)
		serror("illegal operator '%c' ", op);
	return S_UND;
}

#ifdef LISTING
int
printx(int ndig, ADDR_T val)
{
	static char buf[8];
	char* p;
	int c, n;

	p = buf;
	n = ndig;
	do {
		*p++ = (int)val & 017;
		val >>= 4;
	} while (--n);
	do {
		c = "0123456789ABCDEF"[(unsigned char)*--p];
		putchar(c);
	} while (p > buf);
	return (ndig);
}

void
listline(int textline)
{
	int c;

	if ((listflag & 4) && (c = getc(listfile)) != '\n' && textline) {
		if (listcolm >= 24) {
			printf(" \\\n\t\t\t");
		} else {
			do {
				putchar('\t');
				listcolm += 8;
			} while (listcolm < 24);
		}
		do {
			assert(c != EOF);
			putchar(c);
		} while ((c = getc(listfile)) != '\n');
	}
	if (listflag & 7) {
		putchar('\n');
		fflush(stdout);
	}
	listeoln = 1;
	listcolm = 0;
	listflag = listtemp;
}
#endif /* LISTING */


/* ---------- code optimization ---------- */

#ifdef THREE_PASS
#define PBITTABSZ 128
static char* pbittab[PBITTABSZ];

int
small(int fitsmall, int gain)
{
	int bit;
	char* p;

	if (DOTSCT == S_UND)
		nosect();
	if (bflag)
		return 0;
	if (nbits == BITCHUNK) {
		bitindex++;
		nbits = 0;
		if (bitindex == PBITTABSZ) {
			static int w_given;
			if (pass == PASS_1 && !w_given) {
				w_given = 1;
				warning("bit table overflow");
			}
			return 0;
		}
		if (pbittab[bitindex] == 0 && pass == PASS_1) {
			if ((pbittab[bitindex] = calloc(MEMINCR, 1)) == 0) {
				static int w2_given;
				if (!w2_given) {
					w2_given = 1;
					warning("out of space for bit table");
				}
			}
		}
		if (pbittab[bitindex] == 0)
			return 0;
	}
	bit = 1 << (nbits & 7);
	p = pbittab[bitindex] + (nbits >> 3);
	nbits++;
	switch (pass) {
		case PASS_1:
			return 0;
		case PASS_2:
			if (fitsmall) {
				sect[DOTSCT].s_gain += gain;
				*p |= bit;
			}
			return fitsmall;
		case PASS_3:
			assert(fitsmall || (*p & bit) == 0);
			return (*p & bit);
		default:
			assert(0);
	}
	/*NOTREACHED*/
}
#endif
