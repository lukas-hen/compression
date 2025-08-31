#ifndef SHANNON_H
#define SHANNON_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct ByteFrequencies {
    uint8_t size;
    bool sorted;
    int total_num_bytes;

    uint8_t byte[UINT8_MAX];
    int freq[UINT8_MAX];

} ByteFrequencies;

typedef struct ByteSamplingDistribution {
    uint8_t size;
    bool sorted;
    uint8_t byte[UINT8_MAX];
    double probability[UINT8_MAX];

} ByteSamplingDistribution;

void byte_freqs_count(ByteFrequencies* bf, unsigned char* data, size_t size);
void byte_freqs_sort_desc(ByteFrequencies* bf);
void byte_freqs_print(ByteFrequencies* bf);
void byte_freqs_to_distr(ByteFrequencies* bf, ByteSamplingDistribution* bd);
void byte_distr_print(ByteSamplingDistribution* bd);
double byte_distr_entropy(ByteSamplingDistribution* bd);

#endif