#ifndef SYMBOL_H
#define SYMBOL_H

#include <QObject>
#include <bfd.h>

class binary;

class symbol
{
public:
    enum SymbolType {
        SYM_TYPE_UKN = 0,
        SYM_TYPE_FUNC = 1
    };

    symbol();
    static int load_symbols_bfd(bfd *bfd_h, binary *bin);
    static int load_dynsym_bfd(bfd *bfd_h, binary *bin);

    std::string name;
    uint64_t addr;

    SymbolType type;
};

#endif // SYMBOL_H
