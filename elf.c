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

	printf("---------------------------------------\n");
	printf("nsect = %d\n", nsect);
	printf("nrelo = %d (entsize=%ld)\n", nrelo, sizeof(Elf_Rel));
	printf("nsymb = %d, size=%ld (entsize=%ld)\n", nsymb, sect[symtab_sectno].s_size, sizeof(Elf_Sym));
	printf("nstrtab = %d,%d size=%ld,%ld\n", nstrtab, nshstrtab, sect[strtab_sectno].s_size, sect[shstrtab_sectno].s_size);
	printf("---------------------------------------\n");

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
	int offset = 0;
	int i;
	long off = 0;

	printf("---------------------------------------\n");
	for (i = 0; i < nsect; i++) {
		printf("%d: %s, address=%ld, file-offset=%d, size=%ld\n", i, sect[i].s_item ? sect[i].s_item->i_name : "<null>", sect[i].s_base, offset, sect[i].s_size);
		offset += sect[i].s_size;
	}
	printf("---------------------------------------\n");

	/*
	 * section table generation
	 */
	off += sizeof(Elf_Ehdr);
	off += (long)nsect * sizeof(Elf_Shdr);

	for (i = 1; i < nsect; i++) {

		sect_t *sp = &sect[i];
		printf("SECTION %d: offset=%ld, size=%ld, nameidx=%d, link=%ld, info=%ld\n", i, off, sp->s_size - sp->s_zero, sp->s_item ? sp->s_item->i_type : 0, sp->s_link, sp->s_info);

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
