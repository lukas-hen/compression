#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lz77.h"

#define WINDOW_SIZE 16
#define LOOKAHEAD_SIZE 8 // Same a s length.

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

// in mem repr, needs to be serialized for actual compressed data.
typedef struct {
    // Offset & Size for recurring substring should fit in 1 byte for now. 
    // To make it simple we allow 2^4 = 16 chars window with a max len of 16 aswell.
    // Making lookahead smaller and window larger would likely be beneficial.
    uint8_t offset; // MAXVAL IS UINT8_MAX
    uint8_t length; // MAXVAL IS UINT8_MAX

} lz77_token;

typedef struct {
    
    size_t w_idx;

    uint8_t window_sz;
    uint8_t lookahead_sz;

    size_t file_sz; // Can index/compress up to 2^32 ~= 4.2 GB. 64 bit int could index ~= 9000PB but better to chunk implementation then.

} lz77_state;


// Compare two buffers byte per byte. Return 0 if no match or n for how many bytes match in sequence.
int bytecmp(const void *a, const void *b, size_t n_bytes) {
    
    // Interpret as bytes.
    const unsigned char* _a = (const unsigned char*) &a;
    const unsigned char* _b = (const unsigned char*) &b; 
    int i;


    for(i = 0; i < n_bytes; i++, _a++, _b++) {
        if ( *_a != *_b ) {
            break;
        }
    }

    return i;

}


CompressionResult lz77_encode(char **dst, const char *src, size_t size) {

    lz77_state s = {
        w_idx: 0,
        window_sz: 12,     // Must be < UINT8_MAX
        lookahead_sz: 4,   // Must be < UINT8_MAX
        file_sz: size
    };

    uint8_t window_sz = 12;
    uint8_t lookahead_sz = 4;
    size_t w_idx = window_sz; // Start with full window.
    size_t file_sz = size; 

    do {
        
        uint8_t cur_window_sz = MIN(window_sz, w_idx); // Not required atm as we start at idx = window_sz.
        uint8_t cur_lookahead_sz = MIN(file_sz - w_idx, lookahead_sz);

        int n_matching_bytes, largest_matching_bytes, largest_matching_byte_offset;
        
        largest_matching_bytes = 0;
        largest_matching_byte_offset = 0;

        for (int i = 0; i < cur_window_sz; i++) {
            
            n_matching_bytes = bytecmp(src[w_idx - cur_window_sz], src[w_idx], cur_lookahead_sz);
            
            if (n_matching_bytes > largest_matching_bytes) {
                largest_matching_byte_offset = i - n_matching_bytes;
                largest_matching_bytes = n_matching_bytes;
            }

        };

        if (largest_matching_bytes > 1) {
            printf("IDX: %d, OFFSET: %d, SZ: %d\n", w_idx, largest_matching_byte_offset, largest_matching_bytes);
        }
        
        //printf("W_IDX %d, W_SZ: %d, LH_SZ: %d\n", w_idx, cur_window_sz, cur_lookahead_sz);

        w_idx++;


    } while( w_idx < file_sz);
    
    *dst = src;
    return SUCCESS;
}






CompressionResult lz77_decode(char **dst, const char *src) {
    *dst = src;
    return SUCCESS;
}