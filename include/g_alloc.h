#ifndef AALOC_H
#define AALOC_H

#include <stdint.h>
#include <stdlib.h>

/* Struct to keep track of allocated blocks */
typedef struct {
    void** pointers;  // Array of references to allocated memory regions
    size_t count;     // Number of allocated blocks
    size_t capacity;  // Capacity of the pointers array
} GroupedAllocator;

void g_alloc_init(GroupedAllocator* allocator, size_t initial_capacity);
void* g_alloc(GroupedAllocator* allocator, size_t size);
void g_free(GroupedAllocator* allocator);

#endif