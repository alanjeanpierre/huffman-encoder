#include "bit_writer.h"

bit_writer::bit_writer(const char *fileName) {
    buffer = 0;
    count = 0;
    file.open(fileName, std::fstream::binary);
}

bit_writer::~bit_writer() {
    if (count != 0) flush_buf();
    file.close();
}

bool bit_writer::write_bit(byte bit) {
    bit &= 1;

    buffer = (buffer << 1) | bit;
    count += 1;

    if (count == 8) {
        file << buffer;
        buffer = 0;
        count = 0;
        return true;
    }

    return false;
}

void bit_writer::flush_buf() {
    while (!write_bit(0));
}

void bit_writer::write_code(std::pair<int, long> code) {
    for (int i = code.first; i > 0; i--) {
        write_bit(code.second >> i-1);
    }
}
