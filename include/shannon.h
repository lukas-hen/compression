#ifndef SHANNON_H
#define SHANNON_H

#define TRUE 1
#define FALSE 0

#include <math.h>
#include <stdio.h>

typedef u_int8_t bool;

typedef struct ByteFrequencies {

    uint8_t size;
    bool sorted;
    int total_num_bytes;
    
    uint8_t byte[UINT8_MAX];
    int freq[UINT8_MAX];

} ByteFrequencies;

typedef struct ByteProbabilityDistr {
    
    uint8_t size;
    bool sorted;
    uint8_t byte[UINT8_MAX];
    double probability[UINT8_MAX];

} ByteProbabilityDistr;


void byte_freqs_count(ByteFrequencies *bf, unsigned char *data, size_t size);
void byte_freqs_sort_desc(ByteFrequencies *bf);
void byte_freqs_print(ByteFrequencies *bf);
void byte_freqs_to_distr(ByteProbabilityDistr *bd, ByteFrequencies *bf);
void byte_distr_print(ByteProbabilityDistr *bd);
double byte_distr_entropy(ByteProbabilityDistr *bd);

//void shan_encode(unsigned char *dst, unsigned char *src);
//void shan_decode(unsigned char *dst, unsigned char *src);

//void shan_tree_serialize(HuffmanTree *tree);
//void shan_tree_deserialize(unsigned char *data);


#endif