#include "PBG3.hpp"

namespace OpenTouhou {

/**
 * @brief Load a Touhou PBG3 archive
 *
 * @param path
 */
void PBG3::load(const std::string &path) {
    reader = new BinaryReader(path);
    std::cout << "[PBG3::load] loading archive " << path << std::endl;

    // Read header data
    PBG_Header header;
    char *magic = reader->read_cstring(4);
    unsigned int entries = reader->read_int();
    unsigned int ft_offset = reader->read_int();

    std::cout << "[PBG3::load] magic: " << magic << std::endl;
    std::printf("[PBG3::load] entries: %zu\n", entries);
    std::printf("[PBG3::load] ft_offset: %x\n", ft_offset);

    // std::strncpy(header.magic, magic, 4);

    // header.entries = entries;
    // header.ft_offset = ft_offset;

    // Read file table

    // Bruteforce the ft_offset to see if anything is valid
    reader->file.seekg(ft_offset);
    for (int n = 0; n < entries; n++) {
        read_ft_entry();
    }
    // reader->file.seekg(0, std::ios::end);
    // std::cout << "[PBG3::load] seeking to end of file" << std::endl;
    // std::cout << "[PBG3::load] fp is at: " << std::hex << reader->file.tellg() << std::endl;
}

void PBG3::read_ft_entry() {
    // Read unknown1 and unknown2
    unsigned int unk1 = reader->read_int();
    unsigned int unk2 = reader->read_int();

    // Read the checksum of the compressed data
    unsigned int checksum = reader->read_int();

    // Read the size of the uncompressed data
    unsigned int un_size = reader->read_int();

    // // Read the name of the file, no idea how long exactly
    std::string name = reader->read_string();

    std::printf("[PBG3::read_ft_e] unk1: %x\n", unk1);
    std::printf("[PBG3::read_ft_e] unk2: %x\n", unk2);
    std::printf("[PBG3::read_ft_e] checksum: 0x%08x\n", checksum);
    std::printf("[PBG3::read_ft_e] un_size: 0x%08x\n", un_size);
    std::printf("[PBG3::read_ft_e] name: %s\n", name.c_str());
}

// Null terminated strcpy routine

}; // namespace OpenTouhou