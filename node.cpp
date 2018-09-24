#include "node.h"
#include <iostream>
#include <queue>

InteriorNode::InteriorNode(long weight, Node *left, Node *right) : Node(weight), left(left), right(right){
    right->setParent(this);
    left->setParent(this);
}

long InteriorNode::writeTree(bit_writer *w) {
    w->write_bit(0);
    return 1 + left->writeTree(w) + right->writeTree(w);
}

void InteriorNode::print() {
    left->print();
    right->print();
}

byte InteriorNode::search(bit_reader *r) {
    byte bit = r->read_bit();
    if (bit) {
        return right->search(r);
    } else {
        return left->search(r);
    }
}

LeafNode::LeafNode(long weight, byte value) : Node(weight), value(value) {
}


long LeafNode::writeTree(bit_writer *w) {
    w->write_bit(1);
    w->write_code(std::pair<int, long>(8, value));
    return 9;
}

void LeafNode::print() {
    std::cout << value << std::endl;
}

byte LeafNode::search(bit_reader *r) {
    return value;
}

Node *readTree(bit_reader *r) {
    byte bit = r->read_bit();
    if (bit) {
        char val = r->read_byte();
        Node *leaf = new LeafNode(0, val);
        return leaf;
    } else {
        Node *left = readTree(r);
        Node *right = readTree(r);
        Node *interior = new InteriorNode(0, left, right);
        return interior;
    }
}

Node *createTree(std::vector<Node*> frequency) {
    auto comp = [](const Node* e1, const Node* e2) { return e1->getWeight() > e2->getWeight();}; 

    std::priority_queue<Node*, std::vector<Node*>, decltype(comp)> q(comp);
    while(!frequency.empty()) {
        q.push(frequency.back());
        frequency.pop_back();
    }

    // don't add 0s to dictionary
    while (!q.empty() && q.top()->getWeight() == 0) q.pop();
    while(q.size() > 1) {
        auto l = q.top();
        q.pop();
        auto r = q.top();
        q.pop();
        int weight = l->getWeight() + r->getWeight();
        q.push(new InteriorNode(weight, l, r));
    }
    
    Node* root = q.top();
    q.pop();

    return root;
}