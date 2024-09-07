#include "symbol.h"
#include "binary.h"

symbol::symbol(): type(SYM_TYPE_UKN), name(), addr(0) {}

// This function loads the static symbol of the binary file
int symbol::load_symbols_bfd(bfd *bfd_h, binary *bin)
{
    int ret;
    long n, nsyms, i;
    asymbol **bfd_symtab;
    symbol *sym;

    bfd_symtab = NULL;

    /*Before you can load any symbol pointers, you need to allocate enough space to store all of them in.
     * The bfd_get_symtab_upper_bound function tells you how many bytes to allocate for this purpose
    */
    n = bfd_get_symtab_upper_bound(bfd_h);
    if(n < 0)
    {
        fprintf(stderr, "failed to read symtab (%s)\n", bfd_errmsg(bfd_get_error()));
        goto fail;
    }
    else if(n)
    {
        /*If all is well and the symbol table contains a positive number of bytes, you allocate enough
         * space to keep all the asymbol pointers.*/
        bfd_symtab = (asymbol**)malloc(n);
        if(!bfd_symtab)
        {
            fprintf(stderr, "out of memory\n");
            goto fail;
        }

        // ask libbfd to populate the symbol table.
        nsyms = bfd_canonicalize_symtab(bfd_h, bfd_symtab);
        if(nsyms < 0)
        {
            fprintf(stderr, "failed to read symtab (%s)\n", bfd_errmsg(bfd_get_error()));
            goto fail;
        }

        // We now have a populated symbol table, let's loop over all the symbols it contains
        for(i = 0; i < nsyms; i++)
        {
            if(bfd_symtab[i]->flags & BSF_FUNCTION)
            {
                bin->symbols.push_back(symbol());
                sym = &bin->symbols.back();
                sym->type = symbol::SYM_TYPE_FUNC;
                sym->name = std::string(bfd_symtab[i]->name);
                sym->addr = bfd_asymbol_value(bfd_symtab[i]);
            }
        }
    }
    ret = 0;
    goto cleanup;

fail: ret = -1;

cleanup: if(bfd_symtab) free(bfd_symtab);
    return ret;
}

// This function loads the dynamic symbol of the binary file
int symbol::load_dynsym_bfd(bfd *bfd_h, binary *bin)
{
    int ret;
    long n, nsyms, i;
    asymbol **bfd_dynsym;
    symbol *sym;

    bfd_dynsym = NULL;

    n = bfd_get_dynamic_symtab_upper_bound(bfd_h);
    if(n < 0)
    {
        fprintf(stderr, "failed to read dynamic symtab (%s)\n", bfd_errmsg(bfd_get_error()));
        goto fail;
    }
    else if(n)
    {
        bfd_dynsym = (asymbol**)malloc(n);
        if(!bfd_dynsym)
        {
            fprintf(stderr, "out of memory\n");
            goto fail;
        }
        nsyms = bfd_canonicalize_dynamic_symtab(bfd_h, bfd_dynsym);
        if(nsyms < 0)
        {
            fprintf(stderr, "failed to read dynamic symtab (%s)\n", bfd_errmsg(bfd_get_error()));
            goto fail;
        }
        for(i = 0; i < nsyms; i++)
        {
            if(bfd_dynsym[i]->flags & BSF_FUNCTION)
            {
                bin->symbols.push_back(symbol());
                sym = &bin->symbols.back();
                sym->type = symbol::SYM_TYPE_FUNC;
                sym->name = std::string(bfd_dynsym[i]->name);
                sym->addr = bfd_asymbol_value(bfd_dynsym[i]);
            }
        }
    }
    ret = 0;
    goto cleanup;

fail: ret = -1;

cleanup: if(bfd_dynsym) free(bfd_dynsym);
    return ret;
}
