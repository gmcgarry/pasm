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
 * Micro processor assembler framework written by
 *	Johan Stevenson, Vrije Universiteit, Amsterdam
 * modified by
 *	Johan Stevenson, Han Schaminee and Hans de Vries
 *		Philips S&I, T&M, PMDS, Eindhoven
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include "error.h"
#include "out.h"

#include "version.h"

/* this is _very_ dangerous and breaks system headers on macos */
/* be sure that no system headers are included after this */
#define extern  /* empty, to force storage allocation */
#include "as.h"
#undef extern

#ifdef YYDEBUG
extern int yydebug;
#endif

extern void yyparse();
extern void lexinit();

static void pass_1(int, char **);
static void parse(char *);
static void pass_23(int);
static void outstart(void);
static void outfinish(void);
static void commfinish(void);

extern item_t *hashtab[H_TOTAL];

char *aoutpath = "a.out";

extern sect_t sect[SECTMAX];
extern int nsect;
extern int symtab_sectno;
extern int strtab_sectno;
extern int shstrtab_sectno;
extern int nrelo;
extern int nsymb;
extern int nstrtab;
extern int nshstrtab;

void create_additional_sections();

void
stop(void)
{
	exit(nerrors != 0); 
}

static void
stop_on_signal(int sig)
{
	stop();
}

static void
banner()
{
#define XSTR(s) STR(s)
#define STR(s)	#s
	printf("Portable Assembler %s (%s)\n", VERSION_STR, XSTR(MACH));
}

static void
usage()
{
	banner();
	stop();
}

int
main(int argc, char **argv)
{

	char *p;
	int i;
	static char sigs[] = {
		SIGHUP, SIGINT, SIGQUIT, SIGTERM, 0
	};

	progname = *argv++; argc--;

	for (p = sigs; (i = *p++) != 0; )
		if (signal(i, SIG_IGN) != SIG_IGN)
			signal(i, stop_on_signal);

	for (i = 0; i < argc; i++) {
		p = argv[i];
		if (*p++ != '-')
			continue;
		switch (*p++) {
		case '-':
		case 'm':
			if (*p != '\0') {
				mflag(p);
				break;
			}
			if (++i < argc)
				mflag(argv[i]);
			break;
		case 'D':
#ifdef YYDEBUG
			yydebug = 1;
#endif
			break;
		case 'o':
			if (*p != '\0') {
				aoutpath = p;
				break;
			}
			argv[i] = 0;
			if (++i >= argc)
				fatal("-o needs filename");
			aoutpath = argv[i];
			break;
		case 'd':
#ifdef LISTING
			dflag = 0;
			while (*p >= '0' && *p <= '7')
				dflag = (dflag << 3) + *p++ - '0';
			if ((dflag & 0777) == 0)
				dflag |= 0700;
			dflag &= ~4;
#endif
			break;
		case 's':
			sflag = 0;
			while (*p >= '0' && *p <= '7')
				sflag = (sflag << 3) + *p++ - '0';
			break;
		case 'r':
		case 'v':
			banner();
			break;
		case 'u':
			uflag = 1;
			break;
		case 'b':
#ifdef THREE_PASS
			bflag = 1;
#endif
			break;
		case 'h':
			usage();
			break;
		default:
			continue;
		}
		argv[i] = 0;
	}
	sflag |= SYM_SCT;
	pass_1(argc, argv);
	create_additional_sections();
#ifdef THREE_PASS
	pass_23(PASS_2);
#endif
	pass_23(PASS_3);
	outfinish();
	stop();

	return 0;
}

/* ---------- pass 1: arguments, modules, archives ---------- */

static void
pass_1(int argc, char **argv)
{
	DPRINTF(("------------- start of pass %d (1) -------------\n", pass));

	char *p;

#ifdef THREE_PASS
	bitindex = -1;
	nbits = BITCHUNK;
#endif

	tempfile = tmpfile();
#ifdef LISTING
	listmode = dflag;
	if (listmode & 0440)
		listfile = tmpfile();
#endif
	lexinit();
	machstart(PASS_1);
	while (--argc >= 0) {
		p = *argv++;
		if (p == 0)
			continue;
		if (p[0] == '-' && p[1] == '\0') {
			input = stdin;
			parse("STDIN");
			continue;
		}
		if ((input = fopen(p, "r")) == NULL)
			fatal("cannot open %s", p);
		parse(p);
		fclose(input);
	}
	commfinish();
	machfinish(PASS_1);

#ifdef ASLD
	if (unresolved) {
		int i;

		nerrors++;
		fflush(stdout);
		fprintf(stderr, "%d unresolved references:\n", unresolved);
		for (i = 0; i < H_SIZE; i++) {
			item_t *ip = hashtab[H_GLOBAL+i];
			while (ip != 0) {
				if ((ip->i_type & (S_EXTERN|S_SCTMASK)) == (S_EXTERN|S_UND))
					fprintf(stderr, "\t%s\n", ip->i_name);
				ip = ip->i_next;
			}
		}
	}
#endif

	DPRINTF(("------------- end of pass %d (1) -------------\n", pass));
}

static void
parse(char *s)
{
	DPRINTF(("--- start of parse of \"%s\" ---\n", s));

	int i;
	item_t *ip;
	char *p;

	for (p = s; *p; )
		if (*p++ == '/')
			s = p;
	for (i = 0; i < FB_SIZE; i++)
		fb_ptr[FB_BACK+i] = 0;
	newmodule(s);
	peekc = -1;
	yyparse();

	/*
	 * Check for undefined symbols, convert to external symbols
	 */
	for (i = 0; i < H_SIZE; i++) {
		for (ip = hashtab[H_LOCAL+i]; ip; ip = ip->i_next) {
			if (ip->i_type & S_EXTERN)
				continue;
			if (ip->i_type != S_UND)
				continue;
			if (uflag)
				serror("undefined symbol %s", ip->i_name);
			ip->i_type |= S_EXTERN;
		}
	}

	/*
	 * Check for undefined numeric labels
	 */
	for (i = 0; i < FB_SIZE; i++) {
		if ((ip = fb_ptr[FB_FORW+i]) == 0)
			continue;
		serror("undefined label %d", i);
		fb_ptr[FB_FORW+i] = 0;
	}

	DPRINTF(("--- end of parse ---\n"));
}

static void
pass_23(int n)
{
	DPRINTF(("------------- start of pass %d (2/3) -------------\n", n));

	int i;
	sect_t *sp;
#ifdef ASLD
	ADDR_T base = 0;
#endif

	if (nerrors)
		stop();
	pass = n;
#ifdef LISTING
	listmode >>= 3;
	if (listmode & 4)
		rewind(listfile);
	listeoln = 1;
#endif
#ifdef THREE_PASS
	bitindex = -1;
	nbits = BITCHUNK;
#endif
	for (i = 0; i < FB_SIZE; i++)
		fb_ptr[FB_FORW+i] = fb_ptr[FB_HEAD+i];
#ifdef ASLD
	for (i = 1; i < nsect; i++) {
		sp = &sect[i];
		if (sp->s_flag & BASED) {
			base = sp->s_base;
			if (base % sp->s_align)
				fatal("base not aligned");
		} else {
			base += (sp->s_align - 1);
			base -= (base % sp->s_align);
			sp->s_base = base;
		}
		base += sp->s_size;
		base += sp->s_comm;
	}
#endif
	if (pass == PASS_3)
		outstart();
	for (sp = sect; sp < &sect[nsect]; sp++) {
		sp->s_size = 0;
		sp->s_zero = 0;
#ifdef THREE_PASS
		sp->s_gain = 0;
#endif
	}
	new_string(strtab_sectno, "");
	new_string(shstrtab_sectno, "");
	nsymb = 1;
	sect[symtab_sectno].s_size = sizeof(Elf_Sym);
	sect[symtab_sectno].s_info = 1;
	machstart(n);
        newmodule(modulename);
	rewind(tempfile);
	yyparse();
	commfinish();
	machfinish(n);

	DPRINTF(("----------------------------\n"));
	DPRINTF(("nsymb = %d\n", nsymb));
	DPRINTF(("size = %ld\n", sect[symtab_sectno].s_size));

	DPRINTF(("------------- end of pass %d (2/3) -------------\n", pass));
}

void
newmodule(char *s)
{
	static char nmbuf[STRINGMAX];

	switchsect(DEFAULT_SECTION);
	if (s && s != modulename) {
		strncpy(nmbuf, s, STRINGMAX-1);
		modulename = nmbuf;
	} else {
		modulename = s;
	}
	lineno = 1;
#ifdef NEEDED
	/*
	 * problem: it shows the name of the tempfile, not any name
	 * the user is familiar with. Moreover, it is not reproducable.
	 */
	if ((sflag & (SYM_EXT|SYM_LOC|SYM_LAB)) && PASS_SYMB)
		newsymb(s, S_MOD, (ADDR_T)0);
#endif
#ifdef LISTING
	listtemp = 0;
	if (dflag & 01000)
		listtemp = listmode;
	listflag = listtemp;
#endif
}

static void
commfinish(void)
{
	int i;
	common_t *cp;
	sect_t *sp;
	item_t *ip;
	ADDR_T addr;

	switchsect(S_UND);

	/*
	 * assign .comm labels and produce .comm symbol table entries
	 */
	for (cp = commons; cp; cp = cp->c_next) {
		ip = cp->c_it;
		if (!( ip->i_type & S_EXTERN)) {
			sp = &sect[ip->i_type & S_SCTMASK];
			if (pass == PASS_1) {
				addr = sp->s_size + sp->s_comm;
				sp->s_comm += ip->i_valu;
				ip->i_valu = addr;
				ip->i_type &= ~S_TYPEMASK;
			}
#ifdef ASLD
                        if ((sflag & SYM_EXT) && PASS_SYMB)
                               newsymb(ip->i_name, ip->i_type & (S_EXTERN|S_SCTMASK), load(ip));
#endif
#ifdef THREE_PASS
                        if (pass == PASS_2) {
                                ip->i_valu -= sp->s_gain;
                        }
#endif
		}
		if (pass == PASS_1)
			cp->c_size = ip->i_valu;
		if (PASS_SYMB) {
			if (pass != PASS_3 && (ip->i_type & S_EXTERN)) {
				ip->i_valu = nsymb;
			}
			newsymb(ip->i_name, ip->i_type, cp->c_size);
		}
	}
	if (!PASS_SYMB)
		return;

	/*
	 * produce symbol table entries for undefined's
	 */
	for (i = 0; i<H_SIZE; i++) {
		for (ip = hashtab[H_LOCAL+i]; ip; ip = ip->i_next) {
			if ((ip->i_type & (S_EXTERN|S_SCTMASK)) != (S_EXTERN|S_UND))
				continue;
			if (pass != PASS_3) {
				/* * save symbol table index * for possible relocation */
				ip->i_valu = nsymb;
			}
			newsymb(ip->i_name, S_EXTERN|S_UND, (ADDR_T)0);
		}
	}

	/*
	 * produce symbol table entries for sections
	 */
	if (sflag & SYM_SCT) {
		for (i = 1; i < nsect; i++) {
			ip = sect[i].s_item;
			newsymb(ip->i_name, (ip->i_type | S_SECTION), load(ip));
		}
	}

}

void
create_additional_sections()
{
	sect_t *sp;

	if (nsect > SECTMAX - 3)
		fatal("too many sections");

	symtab_sectno = nsect++;
	sp = &sect[symtab_sectno];
	sp->s_type = SHT_SYMTAB;
	sp->s_item = item_alloc(S_SECTION|symtab_sectno);
	sp->s_item->i_name = remember(".symtab");
	sp->s_entsize = sizeof(Elf_Sym);
	sp->s_link = nsect; /* the next section */
	sp->s_align = ALIGNSECT;
	sect[symtab_sectno].s_size = sizeof(Elf_Sym); /* empty symbol */

	strtab_sectno = nsect++;
	sp = &sect[strtab_sectno];
	sp->s_type = SHT_STRTAB;
	sp->s_item = item_alloc(S_SECTION|strtab_sectno);
	sp->s_item->i_name = remember(".strtab");
	sp->s_align = ALIGNSECT;

	shstrtab_sectno = nsect++;
	sp = &sect[shstrtab_sectno];
	sp->s_type = SHT_STRTAB;
	sp->s_item = item_alloc(S_SECTION|shstrtab_sectno);
	sp->s_item->i_name = remember(".shstrtab");
	sp->s_align = ALIGNSECT;
}

static void
outstart(void)
{
	int i;
	long off = 0;

	if (wr_open(aoutpath, nsect) < 0)
		fatal("cannot create %s", aoutpath);

#if 0
	printf("---------------------------------------\n");
	printf("nsect = %d\n", nsect);
	printf("nrelo = %d (entsize=%ld)\n", nrelo, sizeof(Elf_Rel));
	printf("nsymb = %d, size=%ld (entsize=%ld)\n", nsymb, sect[symtab_sectno].s_size, sizeof(Elf_Sym));
	printf("nstrtab = %d,%d size=%ld,%ld\n", nstrtab, nshstrtab, sect[strtab_sectno].s_size, sect[shstrtab_sectno].s_size);
	printf("---------------------------------------\n");
#endif

#if 0
	assert(sect[symtab_sectno].s_size == sizeof(Elf_Sym) * nsymb);
	assert(sect[strtab_sectno].s_size + sect[shstrtab_sectno].s_size == nstrtab);
	assert(sect[2].s_size == nrelo * sizeof(Elf_Rel));
#endif

	Elf_Ehdr hdr = {
		.e_ident = { ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3, ELFCLASS, ELFDATA2LSB, 1, ELFOSABI_SYSV, 0, 0, 0, 0, 0, 0, 0, 0, },
		.e_type = ET_REL,
		.e_machine = ELFMACHINE,
		.e_version = EV_CURRENT,
		.e_entry = 0,
		.e_phoff = 0,
		.e_shoff = sizeof(Elf_Ehdr),
		.e_flags = 0,
		.e_ehsize = sizeof(Elf_Ehdr),
		.e_phentsize = 0, /* sizeof(Elf_Phdr), */
		.e_phnum = 0,
		.e_shentsize = sizeof(Elf_Shdr),
		.e_shnum = nsect,
		.e_shstrndx = nsect - 1,
	};
	wr_write(0, &hdr, sizeof(Elf_Ehdr));

	/* null section */
	Elf_Shdr shdr;
	memset(&shdr, 0, sizeof(Elf_Shdr));
	wr_write(0, &shdr, sizeof(Elf_Shdr));

	/*
	 * section table generation
	 */
	off += sizeof(Elf_Ehdr);
	off += nsect * sizeof(Elf_Shdr);

	for (i = 1; i < nsect; i++) {
		sect_t *sp = &sect[i];
		wr_seek(i, off);
		off += sp->s_size - sp->s_zero;
	}

	/* null symbol */
	Elf_Sym symb;
	memset(&symb, 0, sizeof(Elf_Sym));
	wr_write(symtab_sectno, &symb, sizeof(Elf_Sym));
	sect[symtab_sectno].s_size += sizeof(Elf_Sym);
}

void
outfinish()
{
	int i;
	long off = 0;

#if 0
	printf("---------------------------------------\n");
	int offset = 0;
	for (i = 0; i < nsect; i++) {
		printf("%d: %s, address=%ld, file-offset=%d, size=%ld\n", i, sect[i].s_item ? sect[i].s_item->i_name : "<null>", sect[i].s_base, offset, sect[i].s_size);
		offset += sect[i].s_size;
	}
	printf("---------------------------------------\n");
#endif

	/*
	 * section table generation
	 */
	off += sizeof(Elf_Ehdr);
	off += (long)nsect * sizeof(Elf_Shdr);

	for (i = 1; i < nsect; i++) {

		sect_t *sp = &sect[i];
		DPRINTF(("SECTION %d: offset=%ld, size=%ld, nameidx=%d, link=%ld, info=%ld\n", i, off, sp->s_size - sp->s_zero, sp->s_item ? sp->s_item->i_type : 0, sp->s_link, sp->s_info));

		Elf_Shdr shdr = {
			.sh_name = sp->s_item ? sp->s_item->i_type : 0,
			.sh_type = sp->s_type,
			.sh_flags = sp->s_eflags,
			.sh_addr = sp->s_base,
			.sh_offset = off,
			.sh_size = sp->s_size /* + sp->s_comm */,
			.sh_link = (sp->s_type == SHT_REL || sp->s_type == SHT_RELA) ? symtab_sectno : sp->s_link,
			.sh_info = (sp->s_type ==  SHT_REL || sp->s_type == SHT_RELA) ? i-1 : sp->s_info,
			.sh_addralign = sp->s_align,
			.sh_entsize = sp->s_entsize,
		};
		wr_write(0, &shdr, sizeof(Elf_Shdr));
		off += sp->s_size - sp->s_zero;
	}

	wr_close();
}
