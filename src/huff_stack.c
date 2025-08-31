#include <stdlib.h>

#include "huffman.h"
#include "util.h"

typedef struct Stack {
    HuffmanNode* data[STACK_SIZE];
    size_t size;
} Stack;

Stack* huff_stack_create() {
    Stack* s = malloc(sizeof(Stack));
    s->size = 0;
    return s;
}

void huff_stack_destroy(Stack* s) { free(s); };

void huff_stack_push(Stack* s, HuffmanNode* n) {
    if (s->size == 0) {
        s->data[0] = n;
    }

    s->data[++s->size] = n;
};

HuffmanNode* huff_stack_pop(Stack* s) {
    if (s->size == 0) {
        return NULL;
    }

    return s->data[s->size--];
}