#ifndef OPENTOUHOU_BINARY_READER
#define OPENTOUHOU_BINARY_READER

#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <sstream>
#include <vector>

namespace OpenTouhou {

/**
 * @brief Binary reader class that provides useful functions
 * for reading Touhous weird datatypes.
 *
 */
class BinaryReader {
  public:
    std::ifstream file;
    BinaryReader(const std::string &path) : file(path, std::ios::binary) {}

    char *read_cstring(size_t len);
    std::string read_string();
    unsigned int read_int();
};
}; // namespace OpenTouhou

#endif