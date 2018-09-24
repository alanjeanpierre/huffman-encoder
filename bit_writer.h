#include <fstream>

#ifndef _BIT_WRITER_H_
#define _BIT_WRITER_H_

typedef unsigned char byte;

/* bit_writer uses an internal byte butter that fills
 * before writing to the output stream because one can only
 * write full bytes. It writes bits in big endian format
 */
class bit_writer {
private:
    byte buffer;
    int count;
    std::ofstream file;
public:
    bit_writer(const char* fileName);
    ~bit_writer();

    // Write a single bit to the buffer
    // bit is ANDed against 1 to ensure it is
    // a single bit
    bool write_bit(byte bit);

    // Used to fill up the buffer with 0s to write
    // a complete byte
    void flush_buf();

    // Write a set of bits contained in the long, with the int
    // describing how many bits of that to write
    void write_code(std::pair<int, long> code);
};

#endif