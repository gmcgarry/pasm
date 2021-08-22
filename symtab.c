#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "as.h"
#include "error.h"

extern sect_t sect[SECTMAX];
extern int nsect;		/* skip S_UND */
int nsymb = 1;		/* skip S_UND */
int nstrtab = 0;
int nshstrtab = 0;

int strtab_sectno;
int shstrtab_sectno;
int symtab_sectno;

struct sym {
	struct sym* s_next;
	item_t *s_item;
};
typedef struct sym sym_t;

sym_t *symbols = NULL;

struct strtab {
	struct strtab *next;
	char buf[MEMINCR - sizeof(struct strtab *)];
	int nleft;
};
typedef struct strtab strtab_t;

strtab_t strtab;


long
new_string(int sectno, const char *s)
{
	long r = 0;
#if 0

	if (s) {
		long len = strlen(s) + 1;
		r = sect[sectno].s_size;
		if (pass == PASS_3)
			wr_write(sectno, s, len);
		nstrtab += len;
		sect[sectno].s_size += len;
	}
#if 0
	printf("wrote \"%s\" into %s at index %ld\n", s, sect[sectno].s_item->i_name, r);
#endif
#endif
	return r;
}

void
newsymb(const char *name, int type, ADDR_T valu)
{
	printf("new symbol: name=%s, type=%04x, value=%04lx\n", name, type, valu);

	if (name && *name == 0)
		name = 0;
	assert(PASS_SYMB);
	if (pass != PASS_3) {
		if ((type & S_TYPEMASK) == S_SECTION)
			new_string(shstrtab_sectno, name);
		else
			new_string(strtab_sectno, name);
		nsymb++;
#if 0
		sect[symtab_sectno].s_info++;
		sect[symtab_sectno].s_size += sizeof(Elf_Sym);
#endif
		return;
	}
	nsymb++;

#if 0
	int nameidx = 0;
	if ((type & S_TYPEMASK) == S_SECTION)
		sect[type&S_SCTMASK].s_item->i_type = new_string(shstrtab_sectno, name);
	else
		nameidx = new_string(strtab_sectno, name);
	int elftype = ((type & S_TYPEMASK) == S_SECTION ? STT_SECTION : 0)
		| ((type & S_TYPEMASK) == S_FILE ? STT_FILE : 0)
		| ((type & S_TYPEMASK) == S_FUNC ? STT_FUNC : 0)
		| ((type & S_TYPEMASK) == S_OBJECT ? STT_OBJECT : 0);
	int elfbind = (type & S_EXTERN) ? STB_GLOBAL : 0;
	int shndx = (type&S_SCTMASK) == S_ABS ? SHN_ABS : (type & S_SCTMASK);

	Elf_Sym sym = {
		.st_name = nameidx,				/* index of symbol's name */
		.st_value = valu,				/* value for the symbol */
		.st_size = 0,					/* size of associated data */
		.st_info = ELF_ST_INFO(elfbind, elftype),	/* type and binding attributes */
		.st_other = 0,					/* visibility */
		.st_shndx = shndx,				/* index of related section */
	};
	printf("writing symbol %s=%d into %s\n", name, sym.st_name, sect[symtab_sectno].s_item->i_name);
	wr_write(symtab_sectno, &sym, sizeof(Elf_Sym));
	sect[symtab_sectno].s_info++;
	sect[symtab_sectno].s_size += sizeof(Elf_Sym);
#endif
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
