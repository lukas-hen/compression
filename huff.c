#include <stdint.h>

#include "huff.h"

/*
 * "PRIVATE"...
 */
static void swapc(unsigned char *a, unsigned char *b) {
    unsigned char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

static void swapi(int *a, int *b) {
    
    // int tmp;
    // tmp = *a;
    // *a = *b;
    // *b = tmp;
    
    // High tech shit
    *a = *b ^ *a;
    *b = *a ^ *b;
    *a = *b ^ *a;
}

/*
 * API
 */

void huff_distr(CharDistribution *d, unsigned char *data, size_t size) {
    
    // Makeshift ascii dictionary.
    int freq_buf[UINT8_MAX] = { 0 };

    for(int i = 0; i < size; i++) {
        freq_buf[data[i]]++;
    }
    
    uint8_t buf_size = 0;

    for(int j = 0; j < UINT8_MAX; j++) {
        if (freq_buf[j] > 0) {
            d->chars[buf_size] = (unsigned char)j;
            d->freqs[buf_size] = freq_buf[j];
            buf_size++;
        }
    }

    d->size = buf_size;
}

// TODO:
// int huff_encode() {
//     return 1;
// }

// int huff_decode() {
//     return 1;
// }

void sort_huff_distr_asc(CharDistribution *d) {
    
    int swapped;

    do {
        
        swapped = 0;
        for(int i = 0; i < d->size - 1; i++) {
        
            if(d->freqs[i] > d->freqs[i + 1]) {
                swapi(&d->freqs[i], &d->freqs[i + 1]);
                swapc(&d->chars[i], &d->chars[i + 1]);
                swapped++;
            }

        }

    } while (swapped > 0);

}

void print_huff_distr(CharDistribution *d) {

    printf("Total number of chars used: %d\n", d->size);

    for(int i = 0; i < d->size; i++) {
        if (d->chars[i] == '\n') {
            printf("\'\\n\': %d\n", d->freqs[i]);
        } else {
            printf("\'%c\': %d\n", d->chars[i], d->freqs[i]);
        }
    }
}