#include "section.h"
#include "binary.h"

section::section(): init_binary(NULL), type(SEC_TYPE_NONE), vma(0), size(0) {}

int section::load_sections_bfd(bfd *bfd_h, binary *bin)
{
    int bfd_flags;
    uint64_t vma, size;
    const char *secname;
    asection *bfd_sec;
    section *sec;
    section::SectionType sectype;

    for(bfd_sec = bfd_h->sections; bfd_sec; bfd_sec = bfd_sec->next)
    {
        bfd_flags = bfd_sec->flags;

        sectype = section::SEC_TYPE_NONE;
        if(bfd_flags & SEC_CODE)
        {
            sectype = section::SEC_TYPE_CODE;
        }
        else if(bfd_flags & SEC_DATA)
        {
            sectype = section::SEC_TYPE_DATA;
        }
        else
        {
            continue;
        }

        vma = bfd_section_vma(bfd_sec);
        size = bfd_section_size(bfd_sec);
        secname = bfd_section_name(bfd_sec);

        if(!secname) secname = "<unnamed>";

        bin->sections.push_back(section());
        sec = &bin->sections.back();

        sec->init_binary = bin;
        sec->name = std::string(secname);
        sec->type = sectype;
        sec->vma = vma;
        sec->size = size;
        sec->bytes = (uint8_t*)malloc(size);
        if(!sec->bytes)
        {
            fprintf(stderr, "out of memory\n");
            return -1;
        }

        if(!bfd_get_section_contents(bfd_h, bfd_sec, sec->bytes, 0, size))
        {
            fprintf(stderr, "failed to read section '%s' (%s)\n", secname, bfd_errmsg(bfd_get_error()));
            return -1;
        }
    }

    return 0;
}
