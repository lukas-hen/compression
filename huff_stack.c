#include <stdlib.h>
#include "huffman.h"
#include "util.h"


void huff_stack_init(Stack *s) {
    s->size = 0;
}

void huff_stack_push(Stack *s, HuffmanNode *n) {
    
    if (s->size == 0) {
        s->data[0] = n;
    }

    s->data[++s->size] = n;
};

HuffmanNode *huff_stack_pop(Stack *s) {
    if (s->size == 0) {
        return NULL;
    }

    return s->data[s->size--];
}