#include <stdint.h>

#include "huff.h"

void huff_distribution(CharDistribution *distribution, unsigned char *data, size_t size) {
    
    // Makeshift ascii dictionary.
    int freq_buf[UINT8_MAX] = { 0 };

    for(int i = 0; i < size; i++) {
        printf("%c: %d\t", data[i], data[i]);
        freq_buf[data[i]]++;
    }
    
    uint8_t buf_size = 0;

    for(int j = 0; j < UINT8_MAX; j++) {
        if (freq_buf[j] > 0) {
            distribution->chars[buf_size] = (unsigned char)j;
            distribution->frequencies[buf_size] = freq_buf[j];
            buf_size++;
        }
    }

    distribution->size = buf_size;
}

void print_huff_distribution(CharDistribution *distribution) {

    printf("Total number of chars used: %d\n", distribution->size);

    for(int i = 0; i < distribution->size; i++) {
        if (distribution->chars[i] == '\n') {
            printf("\'\\n\': %d\n", distribution->frequencies[i]);
        } else {
            printf("\'%c\': %d\n", distribution->chars[i], distribution->frequencies[i]);
        }
    }
}

int sort_huff_distribution_desc(CharDistribution *distribution) {

}

int huff_encode() {
    return 1;
}

int huff_decode() {
    return 1;
}
