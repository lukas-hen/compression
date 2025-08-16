#include <string.h>

#include "file.h"
#include "lz77.h"

int main() {

    unsigned char *poem;
    size_t size;
    
    FileReadResult res = f_readall("./resources/poem.txt", &poem, &size);
    if (res != READ_SUCCESSFUL) {
        perror("Error reading file");
        return -1;
    }
    printf("%s\n", poem);
    
    CompressionResult c_res;
    char *encoded, *decoded;

    c_res = lz77_encode(&encoded, poem, size);
    if (c_res != SUCCESS) {
        perror("Error during lz77 encoding");
        return -1;
    }

    c_res = lz77_decode(&decoded, encoded);
        if (c_res != SUCCESS) {
        perror("Error during lz77 decoding");
        return -1;
    }

    if (strncmp(encoded, decoded, size) != 0) {
        printf("TEST FAILED: decoded string did not match source.\n\nSRC:\n%s\n\nDEC:\n%s\n\n\n", poem, decoded);
        return -1;
    };

    return 0;
}