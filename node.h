#include "bit_writer.h"
#include "bit_reader.h"
#include <vector>
#ifndef _NODE_H_
#define _NODE_H_

typedef unsigned char byte;

class Node {
protected:
    long weight;
    Node *parent;
public:
    long getWeight() const { return weight; }
    Node *getParent() const { return parent; }
    void setParent(Node *parent) { this->parent = parent;}
    virtual bool isLeaf() {return false;};
    Node(long weight) { this->parent = nullptr; this->weight = weight;}

    virtual long writeTree(bit_writer *w) {return 0;}
    virtual long getNumNodes() {return 0;}
    virtual void print() { ;};
    virtual byte search(bit_reader *r) { return 0;}
};

class InteriorNode : public Node {
private:
    Node *left, *right;
public:
    InteriorNode(long weight, Node *left, Node *right);

    Node *getLeft() { return left;}
    Node *getRight() {return right;}

    long writeTree(bit_writer *w);
    long getNumNodes() {return 1 + left->getNumNodes() + right->getNumNodes();}
    void print();
    byte search(bit_reader *r);
    
};

class LeafNode : public Node {
private:
    byte value;
public:
    bool isLeaf() { return true;}
    byte getValue() { return value;}
    LeafNode(long weight, byte value);
    void increment() { weight += 1; }
    long writeTree(bit_writer *w);
    long getNumNodes() {return 1;}
    void print();
    byte search(bit_reader *r);
};

#endif

Node *readTree(bit_reader *r); 
Node *createTree(std::vector<Node*> frequency);
