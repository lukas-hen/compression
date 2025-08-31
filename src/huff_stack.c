#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "util.h"

#define STACK_SIZE 1024

/*
 * Global stack/state-machine.
 * Used to store temporary state when traversing a tree.
 */

typedef struct Stack {
    HuffmanNode* data[STACK_SIZE];
    size_t size;
} Stack;

Stack _s;

void huff_stack_reset() { _s.size = 0; }

void huff_stack_push(HuffmanNode* n) { _s.data[_s.size++] = n; };

HuffmanNode* huff_stack_pop() {
    if (_s.size <= 0) {
        return NULL;
    }
    return _s.data[--_s.size];
}