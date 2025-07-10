// huffman.hpp
#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>

// Node for Huffman Tree
class HuffmanNode {
public:
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr) {
        ch = c;
        freq = f;
        left = l;
        right = r;
    }
};

// Comparator for priority_queue (min-heap)
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;  // smaller frequency = higher priority
    }
};

#endif