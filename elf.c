#include <string.h>

#include "as.h"
#include "file.h"
#include "error.h"

#include "elf.h"

extern sect_t sect[];
extern int nsect;

extern int nsymb;
extern int nstrtab;
extern int nshstrtab;

extern int nrelo;

extern char *aoutpath;

static int reloc_partno;
static int symtab_partno;
static int strtab_partno;
static int shstrtab_partno;

static char shstrtab[MEMINCR];
static int shstrtab_offset = 0;

const int
newstr(const char* s)
{
	int r = shstrtab_offset;
	do {
		shstrtab[shstrtab_offset++] = *s;
	} while (*s++);
	return r;
}

void
elfstart(void)
{
	int i;
	long off = 0;

	if (wr_open(aoutpath, nsect) < 0)
		fatal("cannot create %s", aoutpath);

	printf("---------------------------------------\n");
	int offset = 0;
	for (i = 0; i < nsect; i++) {
		DPRINTF(("%d: %s, address=%ld, file-offset=%d, size=%ld\n", i, sect[i].s_item ? sect[i].s_item->i_name : "<null>", sect[i].s_base, offset, sect[i].s_size));
		offset += sect[i].s_size;
	}
	printf("---------------------------------------\n");

	printf("---------------------------------------\n");
	printf("nsect = %d\n", nsect);
	printf("nrelo = %d (entsize=%ld)\n", nrelo, sizeof(Elf_Rel));
	printf("nsymb = %d,(entsize=%ld)\n", nsymb, sizeof(Elf_Sym));
	printf("nstrtab = %d,%d\n", nstrtab, nshstrtab);
	printf("---------------------------------------\n");

	long nesect = nsect + 3; /* + symtab, strtab, shstrab */

#ifdef RELOCATIONS
	if (nreloc > 0)
		nesect++
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
		.e_shnum = nesect,
		.e_shstrndx = nesect,
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
	off += nesect * sizeof(Elf_Shdr);

	/* sections */
	for (i = 1; i < nsect; i++) {
		sect_t *sp = &sect[i];
		wr_seek(i, off);
		off += sp->s_size - sp->s_zero;
	}

	/* relocations */
	reloc_partno = i;
	wr_seek(reloc_partno, off);
	off += nrelo * sizeof(Elf_Rel);

	/* symtab */
	symtab_partno = i++;
	wr_seek(symtab_partno, off);
	off += (nsymb+1) * sizeof(Elf_Sym);

	/* string table */
	strtab_partno = i++;
	wr_seek(strtab_partno, off);
	off += nstrtab;
	
	/* section string table */
	shstrtab_partno = i++;
	wr_seek(strtab_partno, off);
	off += nstrtab;

	/* null symbol */
	Elf_Sym symb;
	memset(&symb, 0, sizeof(Elf_Sym));
	wr_write(symtab_partno, &symb, sizeof(Elf_Sym));

	newstr("");
}

void
elffinish()
{
	int i;
	long off = 0;

	printf("---------------------------------------\n");
	int offset = 0;
	for (i = 0; i < nsect; i++) {
		DPRINTF(("%d: %s, address=%ld, file-offset=%d, size=%ld\n", i, sect[i].s_item ? sect[i].s_item->i_name : "<null>", sect[i].s_base, offset, sect[i].s_size));
		offset += sect[i].s_size;
	}
	printf("---------------------------------------\n");

	off += sizeof(Elf_Ehdr);
	off += (long)nsect * sizeof(Elf_Shdr);

	for (i = 1; i < nsect; i++) {

		sect_t *sp = &sect[i];
		DPRINTF(("SECTION %d: offset=%ld, size=%ld, nameidx=%d, link=%ld, info=%ld\n", i, off, sp->s_size - sp->s_zero, sp->s_item ? sp->s_item->i_type : 0, sp->s_link, sp->s_info));

		Elf_Shdr shdr = {
			.sh_name = newstr(sp->s_item->i_name),
			.sh_type = sp->s_type,
			.sh_flags = sp->s_eflags,
			.sh_addr = sp->s_base,
			.sh_offset = off,
			.sh_size = sp->s_size /* + sp->s_comm */,
			.sh_link = sp->s_link,
			.sh_info = sp->s_info,
			.sh_addralign = sp->s_align,
			.sh_entsize = sp->s_entsize,
		};
		wr_write(0, &shdr, sizeof(Elf_Shdr));
		off += sp->s_size - sp->s_zero;

	}

	/* relocations */
	{
		Elf_Shdr shdr = {
			.sh_name = newstr(".relo"),
			.sh_type = SHT_RELA,
			.sh_flags = SHF_INFO_LINK,
			.sh_addr = 0,
			.sh_offset = off,
			.sh_size = nrelo * sizeof(Elf_Rel),
			.sh_link = symtab_partno,
			.sh_info = reloc_partno - 1,
			.sh_addralign = ALIGNSECT,
			.sh_entsize = sizeof(Elf_Rel)
		};
		wr_write(0, &shdr, sizeof(Elf_Shdr));
		off += nrelo * sizeof(Elf_Rel);
	}

	/* symtab */
	{
		Elf_Shdr shdr = {
			.sh_name = newstr(".symtab"),
			.sh_type = SHT_SYMTAB,
			.sh_flags = 0,
			.sh_addr = 0,
			.sh_offset = off,
			.sh_size = nrelo * sizeof(Elf_Sym),
			.sh_link = nsect + 3,
			.sh_info = 0,
			.sh_addralign = ALIGNSECT,
			.sh_entsize = sizeof(Elf_Sym)
		};
		wr_write(0, &shdr, sizeof(Elf_Shdr));
		off += nsymb * sizeof(Elf_Sym);
	}

	/* strtab */
	{
		Elf_Shdr shdr = {
			.sh_name = newstr(".strtab"),
			.sh_type = SHT_STRTAB,
			.sh_flags = 0,
			.sh_addr = 0,
			.sh_offset = off,
			.sh_size = nstrtab,
			.sh_link = 0,
			.sh_info = 0,
			.sh_addralign = ALIGNSECT,
			.sh_entsize = 0
		};
		wr_write(0, &shdr, sizeof(Elf_Shdr));
		off += nstrtab;
	}

	/* shstrtab */
	{
		Elf_Shdr shdr = {
			.sh_name = newstr(".shstrtab"),
			.sh_type = SHT_STRTAB,
			.sh_flags = 0,
			.sh_addr = 0,
			.sh_offset = off,
			.sh_size = nshstrtab,
			.sh_link = 0,
			.sh_info = 0,
			.sh_addralign = ALIGNSECT,
			.sh_entsize = 0
		};
		wr_write(0, &shdr, sizeof(Elf_Shdr));
		off += nshstrtab;
	}

	wr_write(shstrtab_partno, shstrtab, shstrtab_offset);

	wr_close();
}
