#include "bits.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define LEFTMOST_BIT_U64 ((uint64_t)1 << 63)

BitBuffer* bb_create(size_t size_bytes) {
    BitBuffer* b = malloc(sizeof(BitBuffer));
    b->bytes = calloc(size_bytes, 1);
    b->capacity = size_bytes;
    b->pos = 0;
    return b;
}

static inline uint64_t byte_idx(size_t pos) { return floor(pos / 8); }

static inline uint8_t bit_idx(size_t pos) { return pos % 8; }

void bb_write(BitBuffer* b, uint64_t bits, int n_bits) {
    for (int i = 0; i < n_bits; i++) {
        // printf("byte: %d, bit: %d\n", byte_idx(b->pos), bit_idx(b->pos));
        b->bytes[byte_idx(b->pos)] |= (bits & (1 << (8 - bit_idx(b->pos) - 1)));
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
void bb_free(BitBuffer* b, uint64_t bits, uint8_t n_bits);

static inline uint64_t get_bitmask(uint64_t n_bits) {
    uint64_t bits = 0;

    for (int i = 0; i < n_bits; i++) {
        bits |= 1 << i;
    }

    return bits;
}

// void bits_writer_init(BitIo *b, FILE * fp) {
//     b->fp = fp;
//     b->bit_remainder = 0;
//     b->bit_remainder_sz = 0;
// }

// void bits_write(BitIo *b, uint64_t bits, uint64_t n_bits) {
//     size_t n_prev_remaining_bits = b->bit_remainder_sz;
//     size_t n_remaining_bits = (n_prev_remaining_bits + n_bits) % 8;
//     size_t bytes_to_write = floor((n_prev_remaining_bits +
//     n_bits)/(uint64_t)8);

//     uint64_t prev_remainder_bitmask = get_bitmask(n_prev_remaining_bits);
//     uint64_t remainder_bitmask = get_bitmask(n_remaining_bits) >>
//     (bytes_to_write * 8);

//     uint64_t prev_remaining_bits = b->bit_remainder & prev_remainder_bitmask;
//     uint64_t bits_shifted = bits >> n_prev_remaining_bits;
//     uint64_t bytes_out = (prev_remaining_bits | bits_shifted);
//     if(bytes_to_write > 0)
//         printf("0x%X\n", bytes_out);
//     fwrite(&bytes_out, 1, bytes_to_write, b->fp);

//     b->bit_remainder = 0;
//     b->bit_remainder = bits & remainder_bitmask;
//     b->bit_remainder_sz = n_remaining_bits;
// }
