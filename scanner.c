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

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "as.h"
#include "error.h"
#include "out.h"

#include "y.tab.h"

extern YYSTYPE yylval;

static void readcode(int);
static int induo(int);
static int inident(int);
static int innumber(int);
static int instring(int);
static int inescape(void);
static int infbsym(const char*);

static int nextchar(void);
static void putval(int c);
static int getval(int c);

item_t   *hashtab[H_TOTAL];
short    hashindex;      /* see item_search() */
static int hash(const char* p);

static int maxstring;
static int curr_token;

void
lexinit()
{
	extern item_t keytab[];

	item_t *ip;
	for (ip = keytab; ip->i_type; ip++)
		item_insert(ip, H_KEY+hash(ip->i_name));
}

int
yylex(void)
{
	int c, c0, c1;

	if (pass == PASS_1) {
		/* scan the input file */
		do {
			c = nextchar();
		} while (isspace(c) && c != '\n');
		if (ISALPHA(c)) {
			c = inident(c);
		} else if (isdigit(c)) {
			c = innumber(c);
		} else {
			switch (c)
			{
				case '=':
				case '<':
				case '>':
				case '|':
				case '&':
					c = induo(c);
					break;
				case '\'':
				case '\"':
					c = instring(c);
					break;
#ifdef ASC_COMMENT
				case ASC_COMMENT:
					do
						c = nextchar();
					while (c != '\n' && c != '\0');
					break;
#endif
#ifdef HEXPREFIX
				case HEXPREFIX:
					c = innumber(c);
					break;;
#endif
				case CTRL('A'):
					c = CODE1;
					readcode(1);
					break;
				case CTRL('B'):
					c = CODE2;
					readcode(2);
					break;
				case CTRL('C'):
					c = CODE4;
					readcode(4);
					break;
			}
		}

		/* produce the intermediate token file */
		if (c <= 0)
			return 0;
		if (c < 256) {
			putc(c, tempfile);
			putc(0, tempfile);
		} else {
			putval(c);
		}
	} else {
		/* read from intermediate token file */
		c0 = getc(tempfile);
		if (c0 == EOF)
			return 0;
		c1 = getc(tempfile);
		if (c1 == EOF)
			return 0;

		c = c0 + (c1 << 8);
		if (c >= 256)
			c = getval(c);
	}
	curr_token = c;
	return c;
}

static void
putval(int c)
{
	int64_t v;
	int n = 0;
	char* p = 0;

	assert(c == (c & 0xffff));
	switch (c)
	{
		case CODE1:
			n = 1;
			v = yylval.y_valu;
			goto putnum;
		case CODE2:
			n = 2;
			v = yylval.y_valu;
			goto putnum;
		case CODE4:
			n = 4;
			v = yylval.y_valu;
			goto putnum;
		case NUMBER8:
			v = yylval.y_valu;
			for (n = 0; n < sizeof(v); n++) {
				if (v == 0)
					break;
				v >>= 8;
			}
			if (n <= 4)
				c = NUMBER0 + n;
			else
				n = 8;
			v = yylval.y_valu;
		putnum:
			putc(c, tempfile);
			putc(c >> 8, tempfile);
			while (--n >= 0)
				putc((int)(v >> (n * 8)), tempfile);
			return;
		case IDENT:
		case FBSYM:
			n = sizeof(item_t*);
			p = (char*)&yylval.y_item;
			break;
		case STRING:
		case NUMBERF:
			v = stringlen;
			putc(c, tempfile);
			putc(c >> 8, tempfile);
			for (n = 0; n < sizeof(v); n++) {
				if (v == 0)
					break;
				v >>= 8;
			}
			assert(n <= 4);
			putc(n, tempfile);
			v = stringlen;
			while (--n >= 0)
				putc((int)(v >> (n * 8)), tempfile);
			p = stringbuf;
			n = stringlen;
			while (--n >= 0)
				putc(*p++, tempfile);
			return;
		case OP_EQ:
		case OP_NE:
		case OP_LE:
		case OP_GE:
		case OP_LL:
		case OP_RR:
		case OP_OO:
		case OP_AA:
			break;
		default:
			n = sizeof(word_t);
			p = (char*)&yylval.y_word;
			break;
	}
	putc(c, tempfile);
	putc(c >> 8, tempfile);
	while (--n >= 0)
		putc(*p++, tempfile);
}

static int
getval(int c)
{
	int64_t v;
	int n = 0;
	char* p = 0;

	switch (c) {
		case CODE1:
			n = 1;
			goto getnum;
		case CODE2:
			n = 2;
			goto getnum;
		case CODE4:
			n = 4;
			goto getnum;
		case NUMBER0:
			c = NUMBER8;
			goto getnum;
		case NUMBER1:
			n = 1;
			c = NUMBER8;
			goto getnum;
		case NUMBER2:
			n = 2;
			c = NUMBER8;
			goto getnum;
		case NUMBER3:
			n = 3;
			c = NUMBER8;
			goto getnum;
		case NUMBER4:
			n = 4;
			c = NUMBER8;
			goto getnum;
		case NUMBER8:
			n = 8;
		getnum:
			v = 0;
			while (--n >= 0)
			{
				v <<= 8;
				v |= getc(tempfile);
			}
			yylval.y_valu = v;
			return c;
		case IDENT:
		case FBSYM:
			n = sizeof(item_t*);
			p = (char*)&yylval.y_item;
			break;
		case STRING:
		case NUMBERF:
			getval(getc(tempfile) + NUMBER0);
			stringlen = n = yylval.y_valu;
			p = stringbuf;
			p[n] = '\0';
			break;
		case OP_EQ:
		case OP_NE:
		case OP_LE:
		case OP_GE:
		case OP_LL:
		case OP_RR:
		case OP_OO:
		case OP_AA:
			break;
		default:
			n = sizeof(word_t);
			p = (char*)&yylval.y_word;
			break;
	}
	while (--n >= 0)
		*p++ = getc(tempfile);
	return c;
}

/* ---------- lexical scan in pass 1 ---------- */

static int
nextchar(void)
{
	int c;

	if (peekc != -1) {
		c = peekc;
		peekc = -1;
		return c;
	}
	if ((c = getc(input)) == EOF)
		return 0;
#if 0
	if (!isascii(c))
		fatal("non-ascii character");
#endif
#ifdef LISTING
	if (listflag & 0440)
		putc(c, listfile);
#endif
	return c;
}

static void
readcode(int n)
{
	int c;

	yylval.y_valu = 0;
	do {
		if ((c = getc(input)) == EOF)
			fatal("unexpected EOF in compact input");
		yylval.y_valu <<= 8;
		yylval.y_valu |= c;
	} while (--n);
}

static int
induo(int c)
{
	static short duo[] = {
		('=' << 8) | '=',
		OP_EQ,
		('<' << 8) | '>',
		OP_NE,
		('<' << 8) | '=',
		OP_LE,
		('>' << 8) | '=',
		OP_GE,
		('<' << 8) | '<',
		OP_LL,
		('>' << 8) | '>',
		OP_RR,
		('|' << 8) | '|',
		OP_OO,
		('&' << 8) | '&',
		OP_AA,
		0 /* terminates array */
	};
	short* p;

	c = (c << 8) | nextchar();
	for (p = duo; *p; p++)
		if (*p++ == c)
			return (*p++);
	peekc = c & 0377;
	return (c >> 8);
}

static char name[NAMEMAX + 1];

static int
inident(int c)
{
	char* p = name;
	item_t* ip;
	int n = NAMEMAX;

	do {
		if (--n >= 0)
			*p++ = c;
		c = nextchar();
	} while (ISALNUM(c));
	*p = '\0';
	peekc = c;
	ip = item_search(name);
#if 1
	printf("looking up identifier \"%s\"\n", name);
	printf("%s ip=%p\n", name, ip);
#endif
	if (ip == 0) {
		ip = item_alloc(S_UND);
		ip->i_name = remember(name);
#if 0
		printf("adding ident %s %p\n", ip->i_name, ip);
#endif
		unresolved++;
		item_insert(ip, H_LOCAL + (hashindex % H_SIZE));
	} else if (hashindex < H_SIZE) {
		assert(H_KEY == 0);
		yylval.y_word = (word_t)ip->i_valu;
		return (ip->i_type);
	}
	yylval.y_item = ip;
	return IDENT;
}


#ifdef ASLD
char*
readident(int c)
{
	int n = NAMEMAX;
	char* p = name;

	do
	{
		if (--n >= 0)
			*p++ = c;
		c = nextchar();
	} while (ISALNUM(c));
	*p++ = '\0';
	peekc = c;
	return (name);
}
#endif

static void
need_stringbuf()
{
	if (!maxstring) {
		maxstring = STRINGMAX;
		if ((stringbuf = malloc(maxstring)) == 0) {
			fatal("out of memory");
		}
	}
}

static int
innumber(int c)
{
	ADDR_T v;
	char* p;
	int radix;
	static char num[40 + 1];

	p = num;
	radix = 40;
	if (c == '.')
		goto floatconstant;
	do {
		if (--radix < 0)
			fatal("number too long");
		if (isupper(c))
			c += ('a' - 'A');
		*p++ = c;
		c = nextchar();
		if (c == '.')
			goto floatconstant;
	} while (isalnum(c));
	peekc = c;
	*p = '\0';
	c = *--p;
	p = num;
	radix = 10;
	if (*p == '0') {
		radix = 8;
		p++;
		if (*p == 'x') {
			radix = 16;
			p++;
		} else if (*p == 'b') {
			radix = 2;
			p++;
		}
#ifdef HEXPREFIX
	} else if (*p == HEXPREFIX) {
		radix = 16;
		p++;
#endif
	}
	if (radix != 16 && (c == 'f' || c == 'b'))
		return infbsym(num);
	v = 0;
	while ((c = *p++)) {
		if (c > '9')
			c -= ('a' - '9' - 1);
		c -= '0';
		if ((unsigned)c >= radix)
			serror("digit exceeds radix");
		v = v * radix + c;
	}
	yylval.y_valu = v;
	return NUMBER8;

floatconstant:
	do {
		if (--radix < 0)
			fatal("number too long");
		*p++ = c;
		c = nextchar();
		if (isupper(c))
			c = tolower(c);
	} while (isdigit(c) || (c == '.') || (c == 'e') || (c == '+') || (c == '-'));
	peekc = c;

	*p = '\0';
	stringlen = p - num;
	need_stringbuf();
	assert(stringlen < maxstring);
	strcpy(stringbuf, num);

	return NUMBERF;
}

static int
instring(int termc)
{
	char* p;
	int c;

	need_stringbuf();
	p = stringbuf;
	for (;;)
	{
		c = nextchar();
		if (c == '\n' || c == '\0')
		{
			peekc = c;
			serror("non-terminated string");
			break;
		}
		if (c == termc)
			break;
		if (c == '\\')
			c = inescape();
		if (p >= &stringbuf[maxstring - 1])
		{
			int cnt = p - stringbuf;

			if ((stringbuf = realloc(stringbuf, maxstring += 256)) == 0)
			{
				fatal("out of memory");
			}
			p = stringbuf + cnt;
		}
		*p++ = c;
	}
	stringlen = p - stringbuf;
	*p = '\0';
	return STRING;
}

static int
inescape(void)
{
	int c, j, r;

	c = nextchar();
	if (c >= '0' && c <= '7')
	{
		r = c - '0';
		for (j = 0; j < 2; j++)
		{
			c = nextchar();
			if (c < '0' || c > '7')
			{
				peekc = c;
				return r;
			}
			r <<= 3;
			r += (c - '0');
		}
		return r;
	}
	switch (c)
	{
		case 'b':
			return '\b';
		case 'f':
			return '\f';
		case 'n':
			return '\n';
		case 'r':
			return '\r';
		case 't':
			return '\t';
		case '\'':
			return '\'';
		case '"':
			return '"';
	}
	return c;
}

static int
infbsym(const char* p)
{
	int lab;
	item_t* ip;

	lab = *p++ - '0';
	if ((unsigned)lab < 10)
	{
		if (*p++ == 'f')
		{
			ip = fb_ptr[FB_FORW + lab];
			if (ip == 0)
			{
				ip = fb_alloc(lab);
				fb_ptr[FB_FORW + lab] = ip;
			}
			goto ok;
		}
		ip = fb_ptr[FB_BACK + lab];
		if (ip != 0 && *p == 0)
			goto ok;
	}
	serror("bad numeric label");
	ip = fb_alloc(0);
ok:
	yylval.y_item = ip;
	return FBSYM;
}

static int
hash(const char* p)
{
	unsigned short h;
	int c;

	h = 0;
	while ((c = *p++)) {
		h <<= 2;
#ifdef IGNORECASE
		h += tolower(c);
#else
		h += c;
#endif
	}
	return (h % H_SIZE);
}


static int
strcompare(const char *s1, const char *s2)
{
#ifdef IGNORECASE
	printf("comparing \"%s\" with \"%s\"\n", s1, s2);
	while (*s1 && *s2) {
		int a = tolower(*s1++);
		int b = tolower(*s2++);
		if (a != b)
			return (a - b);
	}
	return (*s1 - *s2);
#else
	return strcmp(s1, s2);
#endif
}

item_t*
item_search(const char* p)
{
	int h;
	item_t* ip;

	for (h = hash(p); h < H_TOTAL; h += H_SIZE) {
		ip = hashtab[h];
		while (ip != 0) {
			if (strcompare(p, ip->i_name) == 0)
				goto done;
			ip = ip->i_next;
		}
	}
done:
	hashindex = h;
	return ip;
}

void
item_insert(item_t* ip, int h)
{
	ip->i_next = hashtab[h];
	hashtab[h] = ip;
}

item_t*
item_alloc(int typ)
{
	item_t* ip;
	static int nleft = 0;
	static item_t* next;

	if (--nleft < 0)
	{
		next = (item_t*)malloc(MEMINCR);
		if (next == 0)
			fatal("out of memory");
		nleft += (MEMINCR / sizeof(item_t));
	}
	ip = next++;
	ip->i_next = 0;
	ip->i_type = typ;
	ip->i_name = 0;
	ip->i_valu = 0;
	return ip;
}

item_t*
fb_alloc(int lab)
{
	item_t *ip, *p;

	ip = item_alloc(S_UND);
	p = fb_ptr[FB_TAIL + lab];
	if (p == 0)
		fb_ptr[FB_HEAD + lab] = ip;
	else
		p->i_next = ip;
	fb_ptr[FB_TAIL + lab] = ip;
	return ip;
}

item_t*
fb_shift(int lab)
{
	item_t* ip;

	ip = fb_ptr[FB_FORW + lab];
	if (ip == 0) {
		if (pass == PASS_1)
			ip = fb_alloc(lab);
		else
			ip = fb_ptr[FB_HEAD + lab];
	}
	fb_ptr[FB_BACK + lab] = ip;
	fb_ptr[FB_FORW + lab] = ip->i_next;
	return ip;
}
