#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "bits.h"
#include "file.h"
#include "huffman.h"
#include "statistic.h"
#include "util.h"

char* get_argument(int argc, char** argv, unsigned char argn);

int main(int argc, char** argv) {
    unsigned char* poem;
    size_t size;
    FILE* fp;

    if (!isatty(
            fileno(stdin))) {  // Hacky way to check if any input is piped in.
        fp = stdin;
    } else if (argc == 2) {
        char* fname = get_argument(argc, argv, 1);
        fp = fopen(fname, "rb");
    } else {
        fprintf(stderr, "No data was provided.\nUSAGE: compress <filename>\n");
        return 0;
    }

    FileReadResult res = f_readall(fp, &poem, &size);
    if (res != READ_SUCCESSFUL) {
        perror("Error reading file");
        return -1;
    }

    ByteFrequencies bf;
    byte_freqs_count(&bf, poem, size);
    byte_freqs_sort_desc(&bf);
    // byte_freqs_print(&bf);

    ByteSamplingDistribution bd;
    byte_freqs_to_distr(&bf, &bd);
    // byte_distr_print(&bd);

    HuffmanNode* root = huffman_tree_create(&bd);
    huffman_tree_to_dot_file(root, "./resources/generated.dot");

    // huffman_tree_serialize(root);
    // huffman_tree_free();

    BitBuffer* b = bb_create(256);
    bb_write(b, 0xFF, 4);
    bb_write(b, 0, 3);
    bb_write(b, 1, 1);
    bb_write(b, UINT64_MAX, 4);
    bb_write(b, 0, 4);
    bb_write(b, UINT64_MAX, 4);
    bb_write(b, 0, 1);
    bb_write(b, 0, 3);
    bb_write(b, UINT64_MAX, 4);
    bb_write(b, 0, 4);
    bb_write(b, 0xFFFFFFFF, 4 * 8 - 1);
    bb_show(b);
    bb_free(b);

    return 0;
}

char* get_argument(int argc, char** argv, unsigned char argn) {
    assert(argc > argn);
    return argv[argn];
}