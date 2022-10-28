#ifndef OPENTOUHOU_PBG3
#define OPENTOUHOU_PBG3

#include "BinaryReader.hpp"

#include <bitset>
#include <fstream>
#include <iostream>
#include <string>

#include <string.h>

namespace OpenTouhou {
struct PBG_Header {
    char magic[4];
    unsigned int entries;
    unsigned int ft_offset;
} __attribute__((packed));

struct PBG_FT_Entry {
    unsigned int unknown1;
    unsigned int unknown2;
    char checksum[16];
    unsigned int size[16];
    char name[0xff];
} __attribute__((packed));

struct PBG_FileTable {
    struct PBG_FT_Entry *entries;
} __attribute__((packed));

/**
 * @brief An archive format used by Touhou for storing its game data
 *
 */
struct PBG_Archive {
    struct PBG_Header header;
    struct PBG_FileTable ft;
} __attribute__((packed));

class PBG3 {
  public:
    BinaryReader *reader;

    void load(const std::string &path);
    void read_ft_entry();
};

}; // namespace OpenTouhou
#endif