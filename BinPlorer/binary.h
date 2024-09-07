#ifndef BINARY_H
#define BINARY_H

#include <QObject>
#include <bfd.h>
#include "symbol.h"
#include "section.h"

class binary
{
public:
    enum BinaryType {
        BIN_TYPE_AUTO = 0,
        BIN_TYPE_ELF = 1,
        BIN_TYPE_PE = 2
    };
    enum BinaryArch {
        ARCH_NONE = 0,
        ARCH_X86 = 1
    };

    binary();
    int load_binary_bfd(std::string &fname, binary *bin);
    bfd* open_bfd(std::string &fname);

    int load_binary(std::string &fname, binary *bin);
    void unload_binary(binary *bin);

    std::vector<section> sections;
    std::vector<symbol> symbols;
    std::string filename;
    std::string type_str;
    std::string arch_str;
    unsigned bits;
    uint64_t entry;
private:
    BinaryType type;
    BinaryArch arch;
};

#endif // BINARY_H
