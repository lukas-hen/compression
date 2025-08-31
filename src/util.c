#include "util.h"

#include <string.h>

void swap(void* a, void* b, size_t size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

void swapp(void** a, void** b) {
    void* tmp = *a;
    *a = *b;
    *b = tmp;
}
