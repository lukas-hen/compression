#include <stdlib.h>

typedef enum {
    SUCCESS,
    FAILED
} CompressionResult;

CompressionResult lz77_encode(char **dst, const char *src, size_t size);
CompressionResult lz77_decode(char **dst, const char *src);