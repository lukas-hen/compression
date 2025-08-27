#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>
#include <stdbool.h>
#include "statistic.h"

// For now we know we wont exceed 256 as we are only using ascii symbols.
#define MINHEAP_SIZE 256

#define MINHEAP_STATUS_SUCCESS (1 << 0)
#define MINHEAP_STATUS_LAST_ELEM (1 << 1) 
#define MINHEAP_STATUS_ERROR_EMPTY (1 << 2)

/*
    HUFFMAN TREES
*/

typedef struct HuffmanNode {

    // only ascii symbols for now.
    // all nodes do not contain symbols - only leaves.
    uint8_t symbol; // can be null
    double probability;

    // As symbols are optional, and probabilities non-unique,
    // creating a unique id per node helps with visualization.
    unsigned int id;

    struct HuffmanNode *left;
    struct HuffmanNode *right;

} HuffmanNode;

typedef struct Encoding {
    uint8_t bits;
    uint8_t mask;
} Encoding;

HuffmanNode *huffman_tree_create(ByteSamplingDistribution *bd);
HuffmanNode *huffman_tree_free(HuffmanNode *root);

void huffman_tree_to_dot_file(char *file_path, HuffmanNode *root);

uint8_t huffman_get_symbol(Encoding symbol);
Encoding huffman_get_encoding(uint8_t symbol);

uint8_t *huffman_tree_serialize();
HuffmanNode *huffman_tree_deserialize();

/*
    MINHEAP
*/

typedef struct MinHeap {
    
    HuffmanNode data[MINHEAP_SIZE];
    uint8_t size;
    // Add capacity if allocating size dynamically.
    
} MinHeap;

void huff_minheap_init(MinHeap *h);
void huff_minheap_insert(MinHeap *h, HuffmanNode n);
void huff_minheap_print(MinHeap* h);
uint8_t huff_minheap_pop(MinHeap *h, HuffmanNode *node);
HuffmanNode huff_minheap_get_min(MinHeap *h);

#endif