#ifndef HUFF_H
#define HUFF_H

#include <stdio.h>

typedef struct {
    uint8_t size;
    unsigned char chars[UINT8_MAX];
    int frequencies[UINT8_MAX];
} CharDistribution;

void huff_distribution(CharDistribution *distribution, unsigned char *data, size_t size);
void print_huff_distribution(CharDistribution *distribution);

#endif