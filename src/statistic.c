#include "statistic.h"

#include <stdint.h>
#include <stdlib.h>

#include "util.h"

void byte_freqs_count(ByteFrequencies* bf, uint8_t* data, size_t size) {
    bf->total_num_bytes = size;

    // Makeshift byte dictionary.
    int freq_buf[UINT8_MAX] = {0};

    for (int i = 0; i < size; i++) {
        freq_buf[data[i]]++;
    }

    uint8_t buf_size = 0;

    for (uint8_t j = 0; j < UINT8_MAX; j++) {
        if (freq_buf[j] > 0) {
            bf->byte[buf_size] = j;
            bf->freq[buf_size] = freq_buf[j];
            buf_size++;
        }
    }

    bf->size = buf_size;
    bf->sorted = false;
}

void byte_freqs_sort_desc(ByteFrequencies* bf) {
    // Bubble sort. Keeping it simple as we won't sort more elements
    // then there are acii chars. (At the very most 255, but usually less.)
    int swapped;

    do {
        swapped = 0;
        for (int i = 0; i < bf->size - 1; i++) {
            if (bf->freq[i] > bf->freq[i + 1]) {
                swap(&bf->freq[i], &bf->freq[i + 1], 1);
                swap(&bf->byte[i], &bf->byte[i + 1], 1);
                swapped++;
            }
        }

    } while (swapped > 0);

    bf->sorted = true;
}

void byte_freqs_print(ByteFrequencies* bf) {
    for (int i = 0; i < bf->size; i++) {
        if (bf->byte[i] == '\n') {
            printf("0x10 (\'\\n\'): %u\n", bf->freq[i]);
        } else {
            printf("0x%X (\'%c\'): %u\n", bf->byte[i], bf->byte[i],
                   bf->freq[i]);
        }
    }
}

void byte_freqs_to_distr(ByteFrequencies* bf, ByteSamplingDistribution* bd) {
    bd->size = bf->size;
    bd->sorted = bf->sorted;

    // set probabilities & copy bytes.
    for (int i = 0; i < bf->size; i++) {
        bd->byte[i] = bf->byte[i];
        bd->probability[i] = (double)bf->freq[i] / bf->total_num_bytes;
    }
}

void byte_distr_print(ByteSamplingDistribution* bd) {
    for (int i = 0; i < bd->size; i++) {
        if (bd->byte[i] == '\n') {
            printf("0x10 (\'\\n\'): %0.3f%%\n", bd->probability[i] * 100.0);
        } else {
            printf("0x%X (\'%c\') : %0.3f%%\n", bd->byte[i], bd->byte[i],
                   bd->probability[i] * 100.0);
        }
    }
}

double byte_distr_entropy(ByteSamplingDistribution* bd) {
    // H(X) := -1 * SUM for all xEX { p(x)*log2[p(x)] }
    // This not a true entropy but appro

    float entropy = 0;
    double prob = 0;

    for (int i = 0; i < bd->size; i++) {
        prob = bd->probability[i];
        entropy += prob * log2(prob);
    }

    return -entropy;
}
