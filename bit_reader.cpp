#include "bit_reader.h"


bit_reader::bit_reader(const char* fileName) {
    buffer = 0;
    index = 0;
    file.open(fileName, std::ifstream::binary);
}

bit_reader::~bit_reader() {
    file.close();
}

byte bit_reader::read_bit() {
    if (index == 0) {
        file.read((char*)&buffer, 1);
        index = 8;
    }

    index--;
    return (buffer >> index) & 1;
}

char bit_reader::read_byte() {
    char b = 0;
    for (int i = 0; i < 8; i++) {
        b = b << 1;
        b |= read_bit(); 
    }
    return b;
}

int bit_reader::read_int() {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        int c = read_byte() & 0xFF;
        count |= ((int)c << (8*(3-i)));
    }
    return count;
}

long bit_reader::read_long() {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int c = read_byte() & 0xFF;
        count |= ((int)c << (8*(7-i)));
    }
    return count;
}

bool bit_reader::eof() {
    return file.eof();
}