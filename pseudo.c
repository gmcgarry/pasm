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

#include "as.h"
#include "error.h"

sect_t sect[SECTMAX];
int nsect = 1;		/* skip S_UND */
#if 0
int nsymb = 1;		/* skip S_UND */
int nrelo = 0;
int nstrtab = 0;
int nshstrtab = 0;

int strtab_sectno;
int shstrtab_sectno;
int symtab_sectno;
#endif

static void new_common(item_t *);


void
newequate(item_t *ip, int typ)
{
	typ &= ~S_EXTERN;
	if ((typ & S_TYPEMASK) == S_COMMON)
		typ = S_UND;
	else if ((typ & S_VAR) && (typ & S_SCTMASK) != S_ABS)
		typ = S_UND;
#ifdef THREE_PASS
	else if (pass == PASS_1 && typ == S_UND)
		typ = S_VAR;
	else if (pass == PASS_2 && (ip->i_type & S_SCTMASK) == S_UND)
		ip->i_type |= typ;
#endif /* THREE_PASS */
	if (typ == S_UND)
		serror("illegal equate");
	if (pass == PASS_3)
		assert((ip->i_type & S_SCTMASK) == (typ & S_SCTMASK));
	newident(ip, typ);
}

void
newident(item_t *ip, int typ)
{
	int flag;
#ifdef GENLAB
	static char genlab[] = GENLAB;
#endif /* GENLAB */

	DPRINTF(("newident(%s,type=0x%x)\n", ip->i_name, typ));

	if (pass == PASS_1) {
		/* DPRINTF(("declare %s: %o\n", ip->i_name, typ)); */
		if (ip->i_type & ~S_EXTERN)
			serror("multiple declared");
		else
			--unresolved;
		ip->i_type |= typ;
	}
	if (!PASS_SYMB)
		return;
#ifdef THREE_PASS
	if (ip->i_type & S_EXTERN)
		flag = SYM_EXT;
	else
		flag = SYM_LOC;
#else
	flag = SYM_EXT|SYM_LOC;	/* S_EXTERN not stable in PASS_1 */
#endif /* THREE_PASS */
#ifdef GENLAB
	if (!(flag & SYM_EXT) && strncmp(ip->i_name, genlab, sizeof(genlab)-1) == 0)
		flag = SYM_LAB;
#endif /* GENLAB */
	if (sflag & flag)
		newsymb(ip->i_name, ip->i_type & (S_EXTERN|S_TYPEMASK|S_SCTMASK), load(ip));

	DPRINTF(("done with newident()\n"));
}

void
newlabel(item_t *ip)
{
#if defined(THREE_PASS) && !defined(NDEBUG)
	ADDR_T oldval = ip->i_valu;
#endif

	DPRINTF(("newlabel: (%s) lineno=%ld, pass=%d, section=%d oldval=%ld, DOTVAL=%ld, gain=%ld\n", ip->i_name, lineno, pass, DOTSCT, oldval, DOTVAL, sect[DOTSCT].s_gain));

	if (DOTSCT == S_UND)
		nosect();
	ip->i_type &= ~S_SCTMASK;
	ip->i_type |= DOTSCT;
	if (store(ip, (ADDR_T) DOTVAL) == 0)
		return;
#ifdef THREE_PASS
	DPRINTF(("oldval = %lu, ip->i_valu = %lu, gain = %lu\n", oldval, (ADDR_T) ip->i_valu, sect[DOTSCT].s_gain));
	assert(pass != PASS_2 || oldval - (ADDR_T) ip->i_valu == sect[DOTSCT].s_gain);
#endif
}

void
newsect(item_t *ip, int type, const char* flags)
{
	int sectno;
#if 0
	int eflags = 0;
#endif
	sect_t *sp = NULL;

	DPRINTF(("newsect(%s,)\n", ip->i_name));
/*
	DPRINTF(("name=%s, type=%x, valu=%lx\n", ip->i_name, ip->i_type, ip->i_valu));
	DPRINTF(("flags=%s\n", flags ? flags : "<none>"));
	DPRINTF(("type=%d\n", type));
*/
#if 0
	if (type == 0) 
		type = SHT_PROGBITS;

	if (flags) {
		while (*flags) {
			switch (*flags) {
				case 'a': eflags |= SHF_ALLOC; break;
				case 'w': eflags |= SHF_WRITE; break;
				case 'x': eflags |= SHF_EXECINSTR; break;
				case 'M': eflags |= SHF_MERGE; break;
				case 'S': eflags |= SHF_STRINGS; break;
				case 'T': eflags |= SHF_TLS; break;
				default: fatal("unrecognised section flag '%s'", *flags); break;
			}
			flags++;
		}
	} else {
		static const struct {
			const char *name;
			int flags;
		} DefaultSectionFlags[] = {
			{ ".text", SHF_ALLOC | SHF_EXECINSTR },
			{ ".data", SHF_ALLOC | SHF_WRITE },
			{ ".rodata", SHF_ALLOC },
		};
		int i;
		for (i = 0; i < (int)(sizeof(DefaultSectionFlags)/sizeof(DefaultSectionFlags[0])); i++) {
			if (strcmp(DefaultSectionFlags[i].name, ip->i_name) == 0) {
				eflags |= DefaultSectionFlags[i].flags;
				break;
			}
		}
	}
#endif

	sectno = ip->i_type & S_SCTMASK;
	if (sectno == S_UND) {
		/* new section */
		assert(pass == PASS_1);
		--unresolved;
		sectno = nsect++;
		if (nsect > SECTMAX)
			fatal("too many sections");
		sp = &sect[sectno];
		sp->s_type = type & 0xffffffff;
		sp->s_flag = 0;
		sp->s_item = ip;
		sp->s_align = ALIGNSECT;
		sp->s_zero = 0;
#ifdef ASLD
		ip->i_type = S_EXTERN | S_SECTION | sectno;
#else
		ip->i_type = S_SECTION | sectno;
#endif
		ip->i_valu = 0;
#if 0
		sp->s_eflags = eflags;
		/* create relocation table for section */
		if (eflags & SHF_ALLOC) {
			static char tmp[256];
#ifdef ELF64
			strcpy(tmp, ".rela");
#else
			strcpy(tmp, ".rel");
#endif
			strcat(tmp, ip->i_name);
			sp = &sect[nsect];
#ifdef ELF64
			sp->s_type = SHT_RELA;
#else
			sp->s_type = SHT_REL;
#endif
			sp->s_eflags = SHF_INFO_LINK;
			sp->s_flag = 0;
			sp->s_entsize = sizeof(Elf_Rel);
			sp->s_link = symtab_sectno;
			sp->s_info = sectno;
			sp->s_align = ALIGNSECT;
			sp->s_item = item_alloc(S_SECTION|nsect);
			sp->s_item->i_name = remember(tmp);
			nsect++;
		}
#endif
	} else {
		sp = &sect[sectno];
		if (sp->s_item != ip)
			sp = NULL;
	}
	if (sp == NULL)
		serror("multiple declared");
	else
		switchsect(sectno);
}

void
newbase(ADDR_T base)
{
	sect_t *sp = &sect[DOTSCT];

	if (DOTSCT == S_UND)
		nosect();
	if (sp->s_flag & BASED)
		serror("already based");
	if (sp->s_flag & SOUGHT)
		serror("cannot rebase section after a seek");
	sp->s_base = base;
	sp->s_flag |= BASED;
	DOTVAL += base;
}

/*
 * local commons:
 *   -	maximum length of .comm is recorded in i_valu during PASS_1
 *   -	address of .comm is recorded in i_valu in later passes:
 *	assigned at end of PASS_1, corrected for s_gain at end of PASS_2
 *   -	maximum length of .comm is recorded in i_valu during PASS_1
 *   -	i_valu is used for relocation info during PASS_3
 */
void
newcomm(item_t *ip, ADDR_T val)
{
	if (pass == PASS_1) {
		if (DOTSCT == S_UND)
			nosect();
		if (val == 0)
			serror("bad size");
		DPRINTF(("declare %s in section %d\n", ip->i_name, DOTSCT));
		if ((ip->i_type & ~S_EXTERN) == S_UND) {
			--unresolved;
			ip->i_type = S_COMMON|DOTSCT|(ip->i_type&S_EXTERN);
			ip->i_valu = val;
			new_common(ip);
		} else if (ip->i_type == (S_COMMON|DOTSCT|(ip->i_type&S_EXTERN))) {
			if (ip->i_valu < val)
				ip->i_valu = val;
		} else
			serror("multiple declared");
	}
}

void
switchsect(int sectno)
{
	sect_t *sp;

	DPRINTF(("switchsect(section %d)\n", sectno));

	if (DOTSCT != S_UND) {
		sp = &sect[DOTSCT];
		sp->s_size = DOTVAL - sp->s_base;
		DPRINTF(("switchsect(): closing section %d at %ld (pass=%d)\n", DOTSCT, sp->s_size, pass));
	}
	if (sectno == S_UND) {
		DOTSCT = S_UND;
		return;
	}
	sp = &sect[sectno];
	DOTVAL = sp->s_size + sp->s_base;
	DOTSCT = sectno;
	DPRINTF(("switchsect(): starting section %d at %ld (size=%ld,base=%ld,pass=%d)\n", DOTSCT, DOTVAL, sp->s_size, sp->s_base, pass));
}

void
align(ADDR_T bytes)
{
	ADDR_T gap;
	sect_t *sp;

	if (DOTSCT == S_UND)
		nosect();
	sp = &sect[DOTSCT];
	if (bytes == 0)
		bytes = ALIGNWORD;
	if (sp->s_align % bytes) {
		if (bytes % sp->s_align)
			serror("illegal alignment");
		else
			sp->s_align = bytes;
	}
	if (pass == PASS_1) {
		/*
		 * be pessimistic: biggest gap possible
		 */
		gap = bytes - 1;
	} else {
		/*
		 * calculate gap correctly;
		 * will be the same in PASS_2 and PASS_3
		 */
		if ((gap = DOTVAL % bytes) != 0)
			gap = bytes - gap;
#ifdef THREE_PASS
		if (pass == PASS_2)
			/*
			 * keep track of gain with respect to PASS_1
			 */
			sect[DOTSCT].s_gain += (bytes - 1) - gap;
#endif
	}
	DOTVAL += gap;
	sp->s_zero += gap;
}


static void
new_common(item_t *ip)
{
	common_t *cp;
	static int nleft = 0;
	static common_t *next;

	if (--nleft < 0) {
		next = (common_t *) malloc(MEMINCR);
		if (next == 0) {
			fatal("out of memory");
		}
		nleft += (MEMINCR / sizeof (common_t));
	}
	cp = next++;
	cp->c_next = commons;
	cp->c_it = ip;
	commons = cp;
}
