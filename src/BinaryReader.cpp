#include "BinaryReader.hpp"

// #define DEBUG 1

namespace OpenTouhou {

/**
 * @brief Read a C string of size len
 *
 * @return char*
 */
char *BinaryReader::read_cstring(size_t len) {
    char *result = new char[len + 1];
    result[len] = '\0';

    file.read(result, len);
    return result;
}

std::string BinaryReader::read_string() {
    file.unsetf(std::ios::skipws);

    std::istream_iterator<char> start(file), end(file);
    std::size_t len = 0;

    while (*end != '\0') {
        ++end;
        ++len;
    }

    std::cout << len << std::endl;

    std::string buf;
    buf.reserve(len);
    buf.insert(buf.begin(), start, end);

    std::cout << buf << std::endl;

    return buf;
}

const char *to_bin(unsigned a) {
    std::string s = std::bitset<8>(a).to_string();

    return s.c_str();
}

/**
 * @brief Read a variable length PBG3 formatted integer.
 * The first two bits signify the length (in terms of how many bytes to read).
 *
 * This function performs the bitwise fuckery, and returns an unsigned int.
 *
 * @return unsigned int
 */
unsigned int BinaryReader::read_int() {
    unsigned char byte;

    unsigned int read_byte_size = 0;
    unsigned int read_bits = 0;
    std::vector<unsigned int> final_buf;
    std::vector<unsigned int> buffer;

    do {
        file.read((char *)&byte, sizeof(char));
        for (unsigned int mask = 1 << 7; mask != 0; mask >>= 1) {
            unsigned int bit = (byte & mask) > 1;

            std::cout << "bit: " << (int)bit << std::endl;

            buffer.push_back(bit);

            if (read_byte_size == 0 and buffer.size() == 2) {
                read_byte_size = (buffer[0] << 1) + buffer[1] + 1;
                buffer.clear();
                std::cout << "read_byte_size: " << read_byte_size << std::endl;
            } else if (read_byte_size > 0) {
                read_bits++;
                if (read_bits % 4 == 0) {
                    int num = (buffer[0] << 3) + (buffer[1] << 2) +
                              (buffer[2] << 1) + buffer[3];
                    final_buf.push_back(num);
                    buffer.clear();
                }
                if (read_bits == read_byte_size * 8) {

                    std::cout << "pass" << std::endl;
                    for (char i : buffer)
                        std::cout << "-> " << i << std::endl;

                    int num, final = 0;
                    for (int j = 0; j < final_buf.size(); j++) {
                        num = final_buf[j];
                        final += num * pow(10, (final_buf.size() - j) - 1);
                    }
                    return final;
                }
            }
        }

    } while (file.peek() != EOF);
    std::cout << "byte was null!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    return NULL;
}

}; // namespace OpenTouhou
