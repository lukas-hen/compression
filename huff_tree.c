#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "huffman.h"

HuffmanNode *huffman_node_create(double probability, uint8_t symbol) {
    HuffmanNode *node = malloc(sizeof(HuffmanNode));
    node->probability = probability;
    node->symbol = symbol;
    node->left = NULL;
    node->right = NULL;
};

HuffmanNode *huffman_tree_create(ByteSamplingDistribution *bd) {

    assert(bd->sorted == true); // Only works if sorted ASC.

    MinHeap heap;
    huff_minheap_init(&heap);

    // loop through all pairs except last elem if odd.
    for(int i = 0; i < bd->size - 1; i += 2) {

        HuffmanNode *lchild = huffman_node_create(bd->probability[i], bd->byte[i]);
        HuffmanNode *rchild = huffman_node_create(bd->probability[i + 1], bd->byte[i]);
        HuffmanNode *curr = huffman_node_create(bd->probability[i] + bd->probability[i + 1], NULL);
        
        // Set relationships.
        curr->left = lchild;
        curr->right = rchild;

    }

    if (bd->size % 2 != 0) {
        printf("Last unpaired element: %d\n", bd->size - 1);
    }

};

HuffmanNode *huffman_tree_free(HuffmanNode *root);

Encoding huffman_get_encoding(uint8_t symbol);

uint8_t *huffman_tree_serialize();
HuffmanNode *huffman_tree_deserialize();
