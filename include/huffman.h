#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>
#include <statistic.h>

// For now we know we wont exceed 256 as we are only using ascii symbols.
#define INIT_MINHEAP_SIZE 256

typedef struct HuffmanNode {
    
    // only ascii symbols for now.
    // all nodes do not contain symbols - only leaves.
    uint8_t symbol;

    double probability;

    // struct HuffmanNode *parent; // might not be req.
    // struct HuffmanNode *left;
    // struct HuffmanNode *right;

} HuffmanNode;

typedef struct Encoding {
    uint8_t bits;
    uint8_t mask;
} Encoding;

HuffmanNode *huffman_tree_create(ByteSamplingDistribution *bd);
HuffmanNode *huffman_tree_free(HuffmanNode *root);

uint8_t huffman_get_symbol(Encoding symbol);
Encoding huffman_get_encoding(uint8_t symbol);

uint8_t *huffman_tree_serialize();
HuffmanNode *huffman_tree_deserialize();

typedef struct MinHeap {
    HuffmanNode data[INIT_MINHEAP_SIZE];
    uint8_t size;
    // Add capacity if allocating size dynamically.
} MinHeap;

void huff_minheap_init(MinHeap *h);
void huff_minheap_insert(MinHeap *h, HuffmanNode n);
HuffmanNode huff_minheap_get_min(MinHeap *h);
void huff_minheap_insert(MinHeap *h, HuffmanNode n);
void huff_minheap_delete(MinHeap *h, HuffmanNode n);
void huff_minheap_print(MinHeap* h);

#endif