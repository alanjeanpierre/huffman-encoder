#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "node.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include <map>
#include <algorithm>

#define ALPHABET 256

void compress(const char* input, const char* output);
void decompress(const char* input, const char* output);
std::vector<Node*> buildFrequencyList(const char* input);
void populate_map(std::map<byte, std::pair<int, long>> *m, Node* root, std::pair<int, long> level);

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " -c/d <outputfile> <inputfile>" <<std::endl;
        exit(1);
    }

    if (argv[1][1] == 'c') {
        compress(argv[3], argv[2]);
    } else if (argv[1][1] == 'd') {
        decompress(argv[3], argv[2]);
    } else {
        std::cerr << "Flag needs to be either -c or -d" << std::endl;
    }
}

void decompress(const char* input, const char* output) {
    
    bit_reader r(input);
    std::ofstream out(output, std::fstream::binary);
    Node *root = readTree(&r);
    unsigned long count = r.read_long();

    for (unsigned long i = 0; i < count; i++) {
        char c = root->search(&r);
        out << c;
    }
}


void compress(const char* input, const char* output) {

    std::map<byte, std::pair<int, long>> map;
    bit_writer w(output);
    unsigned long count = 0;

    auto frequency = buildFrequencyList(input);
    std::for_each(frequency.begin(), frequency.end(), [&](Node *n) { count += n->getWeight();});
    Node *root = createTree(frequency);
    populate_map(&map, root, std::pair<int, long>(0, 0));    
    root->writeTree(&w);
    w.write_code(std::pair<int, unsigned long>(64, count));

    std::ifstream in(input, std::fstream::binary);
    char c;
    while(in.get(c)) {
        w.write_code(map.at(c));
    }

    in.close();
}

/* Populates a dictionary of bytes->encodings based on a frequency tree
 * It is encoded such that the left child constitutes a 0 bit and the right child a 1 bit
 * The code 001 means that the traversal went left, left, right
 */
void populate_map(std::map<byte, std::pair<int, long>> *m, Node* root, std::pair<int, long> level) {
    if (root == nullptr) return;
    static int n = 0;
    static int n2 = 0;
    if (root->isLeaf()) {
        LeafNode *leaf = static_cast<LeafNode*>(root);
        m->insert(std::pair<byte, std::pair<int, long>>(leaf->getValue(), std::pair<int, long>(level.first, level.second))); 
    } else {
        InteriorNode *node = static_cast<InteriorNode*>(root);       

        level.first += 1;
        level.second = level.second << 1;
        auto left = level;
        auto right = level;
        right.second = right.second | 1;
        populate_map(m, node->getLeft(), left);
        populate_map(m, node->getRight(), right);
    }
}

std::vector<Node*> buildFrequencyList(const char* input) {
    std::ifstream in;
    in.open(input, std::ifstream::binary);
    if (!in) {
        std::cerr << "Unable to open file " << input << std::endl;
        exit(1);
    }

    std::vector<Node*> frequency(ALPHABET);
    for (int i = 0; i < ALPHABET; i++) {
        frequency[i] = new LeafNode(0, (byte)i);
    }

    char c;
    while (in.get(c)) {
        static_cast<LeafNode*>(frequency[(unsigned char)c])->increment();
    }
    in.close();
    
    return frequency;
}