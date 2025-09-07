#ifndef BITIO_H
#define BITIO_H

#include <stdint.h>
#include <stdio.h>

typedef struct BitBuffer {
    uint8_t* bytes;
    size_t capacity;
    size_t pos;
} BitBuffer;

BitBuffer* bb_create(size_t size_bytes);
void bb_write(BitBuffer* b, uint64_t bits, int n_bits);
void bb_to_file(BitBuffer* b, FILE* fp);
void bb_free(BitBuffer* b, uint64_t bits, uint8_t n_bits);
void bb_show(BitBuffer* b);

#endif