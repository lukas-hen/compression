#include <string.h>
#include <unistd.h>
#include <assert.h> 

#include "file.h"
#include "huff.h"

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
    
    CharDistribution distr;
    huff_distribution(&distr, poem, size);
    print_huff_distribution(&distr);

    return 0;
}


char *get_argument(int argc, char **argv, unsigned char argn) {
    assert(argc > argn);
    return argv[argn];
}