int main() {
#ifdef A // used to be __ELF__, but this is a built-in
    elf = (struct elfhdr *) buf;

    if (elf->e_ident[0] == 0x7f && strncmp((char *)elf->e_ident + 1, "ELF", 3) == 0) {
	if (elf->e_type != ET_EXEC) {
	    fprintf(stderr, "%s: %s is not an ELF executable\n",
		    prog_name, inname);
	    exit(1);
	}
	if (!elf_check_arch(elf)) {
	    fprintf(stderr, "%s: is not for this processor (e_machine=%d)\n",
		    prog_name, elf->e_machine);
	    exit(1);
	}
	if (elf->e_phnum != 1) {
	    fprintf(stderr,
		    "%s: %d program headers (forgot to link with -N?)\n",
		    prog_name, elf->e_phnum);
	}

	e_entry = elf->e_entry;

	lseek(fd, elf->e_phoff, SEEK_SET);
	if (read(fd, buf, sizeof(*elf_phdr)) != sizeof(*elf_phdr)) {
	    perror("read");
	    exit(1);
	}

	elf_phdr = (struct elf_phdr *) buf;
	offset	 = elf_phdr->p_offset;
	mem_size = elf_phdr->p_memsz;
	fil_size = elf_phdr->p_filesz;

	/* work around ELF bug: */
	if (elf_phdr->p_vaddr < e_entry) {
	    unsigned long delta = e_entry - elf_phdr->p_vaddr;
	    offset   += delta;
	    mem_size -= delta;
	    fil_size -= delta;
	    elf_phdr->p_vaddr += delta;
	}

	if (verbose) {
	    fprintf(stderr, "%s: extracting %#016lx-%#016lx (at %lx)\n",
		    prog_name, (long) elf_phdr->p_vaddr,
		    elf_phdr->p_vaddr + fil_size, offset);
	}
    } else
#endif
    {
	aout = (struct exec *) buf;

	if (!(aout->fh.f_flags & COFF_F_EXEC)) {
	    fprintf(stderr, "%s: %s is not in executable format\n",
		    prog_name, inname);
	    exit(1);
	}

	if (aout->fh.f_opthdr != sizeof(aout->ah)) {
	    fprintf(stderr, "%s: %s has unexpected optional header size\n",
		    prog_name, inname);
	    exit(1);
	}

	if (N_MAGIC(*aout) != OMAGIC) {
	    fprintf(stderr, "%s: %s is not an OMAGIC file\n",
		    prog_name, inname);
	    exit(1);
	}
	offset = N_TXTOFF(*aout);
	fil_size = aout->ah.tsize + aout->ah.dsize;
	mem_size = fil_size + aout->ah.bsize;

	if (verbose) {
	    fprintf(stderr, "%s: extracting %#016lx-%#016lx (at %lx)\n",
		    prog_name, aout->ah.text_start,
		    aout->ah.text_start + fil_size, offset);
	}
    }
}

