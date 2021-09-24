#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "as.h"
#include "error.h"

int nrelo = 0;

void
newrelo(int s, int typ)
{
#define RELOCATIONS
#ifdef RELOCATIONS

#if 0
	int or_nami;
#endif
	int iscomm;

	if (PASS_RELO == 0) {
		DPRINTF(("newrelo: wrong pass, ignoring relocation\n"));
		return;
	}

	DPRINTF(("--- newrelo(s=0x%x,n=%d) ---\n", s, typ));

	s &= ~S_DOT;
	assert((s & ~(S_TYPEMASK|S_VAR|S_SCTMASK)) == 0);

	/*
	 * always relocation info if S_VAR to solve problems with:
	 *	move	b,d0
	 *	b=a
	 *  a:	.data2	0
	 * but no relocation info if S_VAR is set, but type is S_ABS.
	 */
	iscomm = ((s & S_TYPEMASK) == S_COMMON);
	s &= ~S_TYPEMASK;
	if ((typ & RELPC) == 0 && ((s & ~S_VAR) == S_ABS)) {
		DPRINTF(("newrelo: skipping constant relocation\n"));
		return;
	}
	if ((typ & RELPC) != 0 && s == DOTSCT && !iscomm) {
		DPRINTF(("newrelo: skipping this too\n"));
		return;
	}
	if (pass != PASS_3) {
		DPRINTF(("newrelo: not the last pass, reserving space and returning\n"));
		nrelo++;
		return;
	}

	s &= ~S_VAR;
	DPRINTF(("newrelo: s=%x\n", s));
	if (s == S_UND || iscomm) {
		assert(relonami != RELO_UNDEF);
#if 0
		or_nami = relonami;
#endif
		relonami = RELO_UNDEF;
		printf("using relonami\n");
	} else if (s == S_ABS) {
		/*
		 * use first non existing entry (argh)
		 */
#if 0
		or_nami = nsymb;
#endif
		DPRINTF(("using first non-existing entry\n"));
	} else {
		/*
		 * section symbols are at the end
		 */
		/* XXXGJM not anymore */
#if 0
		or_nami = nsymb - nsect + s;
		or_nami = 8;
#endif
		DPRINTF(("using section entry\n"));
	}

#if 0
	int elftype = (typ & 0) + 1;

	Elf_Rel rel = {
		.r_offset = DOTVAL,					/* location to apply relocation to */
#if 0
		.r_info = ELF_R_INFO(or_nami, n),	/* type+section for relocation */
#endif
		.r_info = ELF_R_INFO(or_nami, elftype),	/* type+section for relocation */
#ifdef  ELF64
		.r_addend = -4,
#endif
	};
	wr_write(DOTSCT+1, &rel, sizeof(Elf_Rel));
	sect[DOTSCT+1].s_size += sizeof(Elf_Rel);
#endif

	DPRINTF(("--- newrelo() ---\n"));

#endif
}
