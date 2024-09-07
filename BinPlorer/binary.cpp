#include "binary.h"

binary::binary() : type(BIN_TYPE_AUTO), arch(ARCH_NONE), bits(0), entry(0)
{}

bfd* binary::open_bfd(std::string &fname)
{
    static int bfd_inited = 0;
    bfd *bfd_h;

    if(!bfd_inited)
    {
        bfd_init();
        bfd_inited = 1;
    }

    bfd_h = bfd_openr(fname.c_str(), NULL);
    if(!bfd_h)
    {
        fprintf(stderr, "failed to open binary '%s' (%s)\n", fname.c_str(), bfd_errmsg(bfd_get_error()));
        return NULL;
    }

    if(!bfd_check_format(bfd_h, bfd_object))
    {
        fprintf(stderr, "file '%s' does not look like an executable (%s)\n", fname.c_str(), bfd_errmsg(bfd_get_error()));
        return NULL;
    }

    bfd_set_error(bfd_error_no_error);

    if(bfd_get_flavour(bfd_h) == bfd_target_unknown_flavour)
    {
        fprintf(stderr, "unrecognized format for binary '%s' (%s)\n", fname.c_str(), bfd_errmsg(bfd_get_error()));
        return NULL;
    }

    return bfd_h;
}

int binary::load_binary_bfd(std::string &fname, binary *bin)
{
    int ret;
    bfd *bfd_h;
    const bfd_arch_info_type *bfd_info;

    bfd_h = NULL;
    bfd_h = open_bfd(fname);
    if(!bfd_h)
    {
        goto fail;
    }

    bin->filename = std::string(fname);
    bin->entry = bfd_get_start_address(bfd_h);

    bin->type_str = std::string(bfd_h->xvec->name);
    switch(bfd_h->xvec->flavour)
    {
    case bfd_target_elf_flavour:
        bin->type = binary::BIN_TYPE_ELF;
        break;
    case bfd_target_coff_flavour:
        bin->type = binary::BIN_TYPE_PE;
        break;
    case bfd_target_unknown_flavour:
    default:
        fprintf(stderr, "unsupported binary type (%s)\n",bfd_h->xvec->name);
        goto fail;
    }

    bfd_info = bfd_get_arch_info(bfd_h);
    bin->arch_str = std::string(bfd_info->printable_name);
    switch(bfd_info->mach)
    {
    case bfd_mach_i386_i386:
        bin->arch = binary::ARCH_X86;
        bin->bits = 32;
        break;
    case bfd_mach_x86_64:
        bin->arch = binary::ARCH_X86;
        bin->bits = 64;
        break;
    default:
        fprintf(stderr, "unsupported architecture (%s)\n", bfd_info->printable_name);
        goto fail;
    }

    symbol::load_symbols_bfd(bfd_h, bin);
    symbol::load_dynsym_bfd(bfd_h, bin);

    if(section::load_sections_bfd(bfd_h, bin) < 0) goto fail;

    ret = 0;
    goto cleanup;

fail:
    ret = -1;
cleanup:
    if(bfd_h) bfd_close(bfd_h);

    return ret;
}

/*The job of load_binary is to parse a binary file specified by filename
 * and load it into the Binary object given to it. This is a bit of a tedious
 * process, so load_binary wisely defers the work to another function, called load_binary_bfd
*/
int binary::load_binary(std::string &fname, binary *bin)
{
    return load_binary_bfd(fname, bin);
}

/*unload_binary simply iterates over all Section objects and deallocates the bytes array for
 each of them.
*/
void binary::unload_binary(binary *bin)
{
    size_t i;
    section *sec;

    for(i = 0; i < bin->sections.size(); i++)
    {
        sec = &bin->sections[i];
        if(sec->bytes) free(sec->bytes);
    }
}
