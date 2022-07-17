/*
#define ELF
#define ELF64
*/

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
 * All preprocessor based options/constants/functions
 */

#include <stdint.h>
#include <stdio.h>

/* ========== ON/OFF options (use #define in machdef.h) ========== */

/*
 * The following options are available, to be set/removed in "machdef.h":
 *	THREE_PASS:	three passes needed for branch optimization
 *	BYTES_REVERSED:	lowest target address for word high-order byte
 *	WORDS_REVERSED:	lowest target address for long high-order byte
 *	LISTING:	include listing facilities
 *	DEBUG:		for debugging purposes only
 *	TMPDIR:		directory for temporary files
 *      ASLD:           combined assembler/linker
 */

/* ========== Machine dependent option/constant settings ========== */

#include	"machdef.h"

/* ====================== default constants ======================= */

/* table sizes */

#ifndef STRINGMAX
#define	STRINGMAX	200	/* <= 256 */
#endif

#ifndef SECTMAX
#define	SECTMAX		64
#endif

#ifndef NAMEMAX
#define	NAMEMAX		80
#endif

#ifndef MEMINCR
#define	MEMINCR		2048
#endif

/* Some character constants for parsing */

#ifndef GENLAB
#define	GENLAB		".L"		/* compiler generated labels */
#endif

#ifndef ADDR_T
#define	ADDR_T		unsigned short	/* type of dot */
#endif

#ifndef VALUE_T
#define VALUE_T		long		/* type for local math */
#endif

#define VALWIDTH	2*sizeof(ADDR_T)

/*
 * NOTE: word_t is introduced to reduce the tokenfile size for machines
 * with large expressions but smaller opcodes (68000)
 */

#ifndef word_t
#define	word_t		short		/* type of keyword value */
#endif

#ifndef ALIGNWORD
#define	ALIGNWORD	1
#endif

#ifndef ALIGNSECT
#define	ALIGNSECT	1
#endif

#ifndef BYTESIZE
#define BYTESIZE	1
#endif

#ifndef WORDSIZE
#define WORDSIZE	2
#endif

#ifndef DWORDSIZE
#define DWORDSIZE	4
#endif

#ifndef LONGSIZE
#define LONGSIZE	4
#endif

#ifndef QUADSIZE
#define QUADSIZE	8
#endif

/* ========== type declarations ========== */

struct expr {
	short typ;
	VALUE_T val;
};
typedef	struct expr expr_t;

struct item {
	struct item *i_next;	/* linked lists with same hash value */
	unsigned int i_type;
	/*
	 * the i_type field is used for two different purposes:
	 *	- the token type for keywords, returned by yylex()
	 *	- the symbol type for IDENT and FBSYM tokens
	 */
	VALUE_T i_valu;		/* symbol value */
	const char *i_name;	/* symbol name */
};
typedef	struct item item_t;

struct common {
	struct common *c_next;
	item_t *c_it;
	ADDR_T c_size;
};
typedef struct common common_t;

struct sect {
	short	s_type;		/* section type */
	short	s_flag;		/* some flag bits */
	ADDR_T	s_base;		/* section base */
	ADDR_T	s_size;		/* section size */
	ADDR_T	s_comm;		/* length of commons */
	ADDR_T	s_zero;		/* delayed emit1(0) */
	ADDR_T	s_align;	/* section alignment */
	long	s_foff;		/* section file offset */
	item_t	*s_item;	/* points to section name */
	long	s_entsize;	/* ELF */
	long	s_link;		/* ELF */
	long	s_info;		/* ELF */
	long	s_eflags;	/* ELF */
#ifdef THREE_PASS
	ADDR_T	s_gain;		/* gain in PASS_2 */
#endif
};
typedef	struct sect sect_t;

#ifndef DEFAULT_SECTION
#define DEFAULT_SECTION		S_UND
#endif

/* ========== flag field bits ========== */

/* s_flag bits: */
#define	BASED		1	/* at fixed position */
#define	SOUGHT		2	/* did a .seek in the section */

/* sflag bits: */
#define	SYM_EXT		001	/* external symbols */
#define	SYM_LOC		002	/* local symbols */
#define	SYM_LAB		004	/* local, compiler-generated labels */
#define	SYM_SMB		010	/* .symb symbols */
#define	SYM_LIN		020	/* .line and .file */
#define	SYM_SCT		040	/* section names */
#define	SYM_DEF		073	/* default value */

/*
 * extra type bits, internal use only
 * S_VAR:
 *  - type not known at end of PASS_1 (S_VAR|S_UND)
 *  - value not known at end of PASS_2 (S_VAR|S_ABS)
 * S_DOT:
 *  - dot expression
 */
#define S_SCTMASK	0x00FFU
#define S_UND		0x0000U
#define S_ABS		(S_SCTMASK - 1)

#define S_TYPEMASK	0x0F00U
#define S_COMMON	0x0100U
#define S_SECTION	0x0200U
#define S_FILE		0x0300U
#define S_OBJECT	0x0400U
#define S_FUNC		0x0500U

#define S_EXTERN        0x1000U
#define S_DOT		0x2000U
#define S_VAR		0x3000U

#ifdef BYTES_REVERSED
#ifdef WORDS_REVERSED
#define MACHREL_BWR	(RELBR|RELWR)
#else
#define	MACHREL_BWR	(RELBR)
#endif
#else
#ifdef WORDS_REVERSED
#define	MACHREL_BWR	(RELWR)
#else
#define	MACHREL_BWR	(0)
#endif
#endif

/*
 * variable declarations
 */

#ifdef extern
#define	INIT(x)		= x
#else
#define	INIT(x)		/* empty */
#endif

extern int	curr_token;	/* accessed by target-specific backend */

extern short	pass INIT(PASS_1);
				/* PASS 1, 2 or 3 */
extern short	peekc;		/* push back symbol (PASS_1) */
extern short	unresolved;	/* number of unresolved references */
extern long	lineno;		/* input line number */
extern short	hllino;		/* high-level language line number */
extern short	nerrors;	/* terminate at end of pass if set */
extern short	sflag INIT(SYM_DEF);
				/* -s option (symbol table info) */
extern const char	*progname;	/* for error messages */
extern char	*modulename;	/* for error messages */
extern common_t	*commons;	/* header of commons list */

extern short	uflag;		/* if 1 make undefineds extern */
				/* symbol table index for last S_UND */

#ifdef LISTING
extern short	dflag;		/* -d option (list mode) */
#endif

#define RELO_UNDEF	0
extern ADDR_T relonami INIT(RELO_UNDEF);

#ifdef THREE_PASS
extern short	bflag;		/* -b option (no optimizations) */
#endif

extern FILE	*input;
extern FILE	*tempfile;

extern char	*stringbuf;	/* contains last string value */
extern int	stringlen;	/* contains length of last string value */

/*
 * specials for the location counter
 */
extern ADDR_T	DOTVAL;		/* &sect[DOTSCT]->s_size + &sect[DOTSCT]->s_base */
extern short	DOTSCT;

/* symbol table management */
#define H_SIZE          307             /* hash size, must be odd */
#define H_KEY           (0*H_SIZE)      /* keywords */
#define H_LOCAL         (1*H_SIZE)      /* module symbols */
#define H_GLOBAL        (2*H_SIZE)      /* external symbols */
#define H_TOTAL         (3*H_SIZE)

/* numeric label table management */
#define FB_SIZE         10
#define FB_HEAD         (0*FB_SIZE)
#define FB_TAIL         (1*FB_SIZE)
#define FB_BACK         (2*FB_SIZE)
#define FB_FORW         (3*FB_SIZE)

extern item_t	*fb_ptr[4*FB_SIZE];

#ifdef THREE_PASS
#define BITCHUNK	(8 * MEMINCR)
extern int	nbits;
extern int	bitindex;	/* bitindex * MEMINCR * 8 + nbits gives number of decisions so far */
#endif

#ifdef LISTING
extern short	listmode;	/* -d option for current pass */
extern short	listtemp;	/* listmode if .list seen */
extern short	listflag;	/* copied from listtemp at '\n' */
extern short	listcolm;	/* column on output */
extern short	listeoln INIT(1); /* set by endline, tested by emit1 */
extern FILE	*listfile;	/* copy of source text */
#endif

/* scanner.c */
#ifdef ASLD
char*	readident(int c);
#endif
item_t	*item_search(const char *);
void	 item_insert(item_t *, int);
void	 item_remove(item_t *);
item_t	*item_alloc(int);
item_t	*fb_alloc(int);
item_t	*fb_shift(int);

/* pseuodo.c -> main.c */
void	 newmodule(char *);
void	 newequate(item_t *, int);
void	 newident(item_t *, int);
void	 newlabel(item_t *);
void	 newsect(item_t *, int, const char*);
void	 newbase(ADDR_T);
void	 newcomm(item_t *, ADDR_T);
void	 switchsect(int);
void	 align(int, int, int);
void	 newrelo(int, int);
long	 new_string(const char *);
void	 newsymb(const char *, int, VALUE_T);

void	push_include(const char* filename);
int	pop_include();


/* misc.c */
VALUE_T	 load(const item_t *);
int	 store(item_t *, VALUE_T);
const char *remember(const char *);
int	 combine(int, int, int);
#ifdef LISTING
int	 printx(int, VALUE_T);
void	 listline(int);
#endif
#ifdef THREE_PASS
int	 small(int, int);
#endif
void	 emit1(int);
void	 emit2(int);
void	 emit4(long);
void	 emitx(ADDR_T, int);
void	 emit8(int64_t);
void	 emitstr(int);
void	 emitf(int size, int negative);

/* mach.c */
void mflag(const char *flag);
void machstart(int pass);
void machfinish(int pass);

/* out.c */
void outstart();
void outfinish();

#define fitx(x,n)	(((x)&~((1<<(n))-1)) == 0)

/* =============== Output C declarations ================ */

#define RELO1        1		/* 1 byte */
#define RELO2        2		/* 2 bytes */
#define RELO4        4		/* 4 bytes */
#define RELPC   0x2000 		/* pc relative */
#define RELBR   0x4000		/* High order byte lowest address. */
#define RELWR   0x8000		/* High order word lowest address. */

#ifdef RELOCATIONS
#define RELOMOVE(a,b)	{ a = b; b = 0; }
#else
#define RELOMOVE(a,b)	/* empty */
#endif

#include "elf.h"

#ifndef ELFM
#define ELFM	"@"
#endif

#ifdef ELF64
typedef Elf64_Ehdr Elf_Ehdr;
typedef Elf64_Shdr Elf_Shdr;
typedef Elf64_Rela Elf_Rel;
typedef Elf64_Sym Elf_Sym;
#define ELFCLASS ELFCLASS64
#define ELF_R_INFO(S,T) ELF64_R_INFO(S,T)
#define ELF_ST_INFO(B,T)        ELF64_ST_INFO(B,T)
#else
typedef Elf32_Ehdr Elf_Ehdr;
typedef Elf32_Shdr Elf_Shdr;
typedef Elf32_Rel Elf_Rel;
typedef Elf32_Sym Elf_Sym;
#define ELFCLASS ELFCLASS32
#define ELF_R_INFO(S,T) ELF32_R_INFO(S,T)
#define ELF_ST_INFO(B,T)        ELF32_ST_INFO(B,T)
#endif

#ifdef ELF64
#define ELFMACHINE EM_AMD64
#else
#define ELFMACHINE EM_386
#endif

/* ========== Machine dependent C declarations ========== */

#include "mach.h"

#if YYDEBUG && 0
#define DPRINTF(x)	do { printf("line %ld: ", lineno); printf x; } while(0)
#else
#define DPRINTF(x)	/* nothing */
#endif
