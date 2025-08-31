#include "file.h"

/*
 * Read entire file into dynamically sized buffer.
 */
FileReadResult f_readall(FILE* fd, unsigned char** data, size_t* out_size) {
    size_t len = 0;
    size_t cap = INTIAL_CAPACITY;

    // One byte extra for null terminator
    unsigned char* buf = (unsigned char*)malloc(cap + 1);
    if (buf == NULL) {
        perror("malloc() failed");
        fclose(fd);
        return MEMORY_ALLOCATION_ERROR;
    }

    size_t space;
    size_t n_read;

    for (;;) {
        space = cap - len;
        n_read = fread(buf + len, 1, space, fd);
        len += n_read;

        if (n_read < space) {
            if (ferror(fd)) {
                free(buf);
                fclose(fd);
                perror("ferror() caught file error");
                return FILE_READ_ERROR;
            }

            // EOF reached
            break;
        }

        // Double the buffer capacity.
        cap *= 2;

        unsigned char* tmp = (unsigned char*)realloc(
            buf, cap + 1);  // +1 for null terminator here too.
        if (!tmp) {
            free(buf);
            fclose(fd);
            perror("realloc() failed");
            return MEMORY_ALLOCATION_ERROR;
        }

        buf = tmp;
    }

    buf[len] = '\0';  // NULL-terminate

    *out_size = len;
    *data = buf;

    fclose(fd);

    return READ_SUCCESSFUL;
}