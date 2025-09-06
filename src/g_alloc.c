#include "g_alloc.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

void g_alloc_init(GroupedAllocator* allocator, size_t initial_capacity) {
    allocator->pointers = malloc(initial_capacity * sizeof(void*));
    allocator->count = 0;
    allocator->capacity = initial_capacity;
}

void* g_alloc(GroupedAllocator* allocator, size_t size) {
    if (allocator->count == allocator->capacity) {
        // Reallocate the pointers array to hold more references
        allocator->capacity *= 2;
        allocator->pointers =
            realloc(allocator->pointers, allocator->capacity * sizeof(void*));
        if (allocator->pointers == NULL) {
            perror("Failed to expand allocator's metadata array");
            exit(EXIT_FAILURE);
        }
    }

    // Allocate the actual memory block
    void* block = malloc(size);
    if (block == NULL) {
        perror("Failed to allocate memory block");
        exit(EXIT_FAILURE);
    }

    // Store a reference to this block in the allocator's structure
    allocator->pointers[allocator->count++] = block;

    return block;
}

void g_free(GroupedAllocator* allocator) {
    // Free all allocated memory blocks
    for (size_t i = 0; i < allocator->count; i++) {
        free(allocator->pointers[i]);
    }

    // Free the pointers array
    free(allocator->pointers);
}