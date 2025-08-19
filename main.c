#include <string.h>
#include <unistd.h>
#include <assert.h> 

#include "file.h"
#include "shannon.h"

char *get_argument(int argc, char **argv, unsigned char argn);

int main(int argc, char **argv) {

    if(argc < 2) {
        printf("You need at least one argument!\n");
        return 1;
    }

    char *fname = get_argument(argc, argv, 1);
    unsigned char *poem;
    size_t size;
    
    FileReadResult res = f_readall(fname, &poem, &size);
    if (res != READ_SUCCESSFUL) {
        perror("Error reading file");
        return -1;
    }
    
    ByteFrequencies bf;
    byte_freqs_count(&bf, poem, size);
    byte_freqs_sort_desc(&bf);
    byte_freqs_print(&bf); // sorted

    ByteProbabilityDistr bd;
    byte_freqs_to_distr(&bd, &bf);
    byte_distr_print(&bd);

    printf("Entropy: %lf\n", byte_distr_entropy(&bd));
    
    return 0;
}


char *get_argument(int argc, char **argv, unsigned char argn) {
    assert(argc > argn);
    return argv[argn];
}