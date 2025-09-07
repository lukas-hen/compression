#include "bits.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

BitBuffer* bb_create(size_t size_bytes) {
    BitBuffer* b = malloc(sizeof(BitBuffer));
    b->bytes = calloc(size_bytes, 1);
    b->capacity = size_bytes;
    b->pos = 0;
    return b;
}

static inline uint64_t byte_idx(size_t pos) {
    return floor(pos / 8);
}  // TODO: Fix this cast form double -> uint64

static inline uint8_t bit_idx(size_t pos) { return pos % 8; }

void bb_write(BitBuffer* b, uint64_t bits, int n_bits) {
    for (int i = 0; i < n_bits; i++) {
        b->bytes[byte_idx(b->pos)] |=
            (bits & (1 << (CHAR_BIT - bit_idx(b->pos) - 1)));
        b->pos++;
    }
};

void bb_to_file(BitBuffer* b, FILE* fp);

void bb_show(BitBuffer* b) {
    printf("0x ");
    for (int i = 0; i < 8; i += 2) {
        printf("%X", b->bytes[i]);
        printf("%X ", b->bytes[i + 1]);
    }
    printf("\n");
}
void bb_free(BitBuffer* b) {
    free(b->bytes);
    free(b);
};
