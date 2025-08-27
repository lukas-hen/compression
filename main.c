#include <string.h>
#include <unistd.h>
#include <assert.h> 

#include "file.h"
#include "statistic.h"
#include "huffman.h"

char *get_argument(int argc, char **argv, unsigned char argn);

int main(int argc, char **argv) {

    unsigned char *poem;
    size_t size;
    FILE *fp;

    if (!isatty(fileno(stdin))) { // Hacky way to check if any input is piped in.
        fp = stdin;
    } else if(argc == 2) {
        char *fname = get_argument(argc, argv, 1);
        fp = fopen(fname, "rb");
    } 
    else {
        fprintf(stderr, "No data was provided.\nUSAGE: shan <filename>\n");
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
    byte_freqs_print(&bf);

    ByteSamplingDistribution bd;
    byte_freqs_to_distr(&bd, &bf);
    //byte_distr_print(&bd);

    HuffmanNode *root = huffman_tree_create(&bd);
    //printf("%f\n", root->left->probability);
    huffman_tree_to_dot_file("./resources/generated.dot", root);
    
    return 0;
}


char *get_argument(int argc, char **argv, unsigned char argn) {
    assert(argc > argn);
    return argv[argn];
}