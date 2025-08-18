#ifndef HUFF_H
#define HUFF_H

#include <stdio.h>

typedef struct CharDistribution {
    uint8_t size;
    unsigned char chars[UINT8_MAX];
    int freqs[UINT8_MAX];
} CharDistribution;

void huff_distr(CharDistribution *distribution, unsigned char *data, size_t size);
void sort_huff_distr_asc(CharDistribution *distribution);
void print_huff_distr(CharDistribution *distribution);

#endif