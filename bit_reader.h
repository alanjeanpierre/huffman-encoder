#include <fstream>

#ifndef _BIT_READER_H_
#define _BIT_READER_H_

typedef unsigned char byte;

/* Class to read bits from a file in big endian format
 * Comes with convenience functions to read raw datatypes
 * 
 * bit_reader uses an internal byte buffer to read single bytes,
 * but returns each bit in sequence from the file
 *
 */
class bit_reader {
private:
    byte buffer;
    int index;
    std::ifstream file;
public:
    bit_reader(const char* fileName);
    ~bit_reader();
    byte read_bit();
    char read_byte();
    int read_int();
    long read_long();
    bool eof();
};

#endif