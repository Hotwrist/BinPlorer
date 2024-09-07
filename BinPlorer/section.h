#ifndef SECTION_H
#define SECTION_H

#include <QObject>
#include <bfd.h>

class binary;

class section
{
public:
    enum SectionType {
        SEC_TYPE_NONE = 0,
        SEC_TYPE_CODE = 1,
        SEC_TYPE_DATA = 2
    };

    section();
    bool contains(uint64_t addr) { return (addr >= vma) && (addr-vma < size); }
    static int load_sections_bfd(bfd *bfd_h, binary *bin);
    uint8_t *bytes;

    std::string name;
    SectionType type;
    uint64_t vma;
    uint64_t size;
private:
    binary *init_binary;
};

#endif // SECTION_H
