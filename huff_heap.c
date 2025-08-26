#include <stdlib.h>
#include "huffman.h"
#include "util.h"

/*
 * "PRIVATE" FUNCTIONS
 */

// For below indexing functions - we do Level Order Traversal.
// e.g:
//           a=1   
//     b=2         c=3
// d=4     e=5 f=6     g=7
//    ... and so on

// In array:
// [ root, l, r, ll, lr, rl, rr]

static inline int lchild(int i) {
    return 2*i+1;
}

static inline int rchild(int i) {
    return 2*i+2;
}

static inline int parent(int i) {
    return i > 0 ? (i - 1) / 2 : i;
}

static void heapify(MinHeap *h, int i) {

    if (h->size <= 1)
        return;
    
    int left = lchild(i); 
    int right = rchild(i); 

    // "Subtree" root 
    int smallest = i; 

    // If the left child is smaller than this element, it is
    // the smallest
    if (left < h->size && h->data[left].probability < h->data[i].probability)
        smallest = left; 
    
    // Similarly for the right, but we are updating the smallest element
    // so that it will definitely give the least element of the subtree
    if (right < h->size && h->data[right].probability < h->data[smallest].probability)
        smallest = right; 

    // Now if the current element is not the smallest,
    // swap with the current element. The min heap property
    // is now satisfied for this subtree. We now need to
    // recursively keep doing this until we reach the root node,
    // the point at which there will be no change!
    if (smallest != i) 
    { 
        swap(&h->data[i], &h->data[smallest], sizeof(HuffmanNode));
        heapify(h, smallest); 
    }

}

static void huff_minheap_delete_min(MinHeap *h) {
    // Deletes the minimum element, at the root
    if (!h || h->size == 0)
        return;

    int size = h->size;
    HuffmanNode last_element = h->data[size-1];
    
    // Update root value with the last element
    h->data[0] = last_element;

    // Now remove the last element, by decreasing the size
    h->size--;
    size--;

    // We need to call heapify(), to maintain the min-heap
    // property
    heapify(h, 0);
}

/*
 * As this implementation is heavily huffman specific, 
 * we only expose necessary functions to build a huffman tree.
 */

// Allow user to create on stack or heap, whatever suits their needs.
void huff_minheap_init(MinHeap *h) {
    h->size = 0;
}

void huff_minheap_insert(MinHeap *h, HuffmanNode n) {
    
    if (h->size == MINHEAP_SIZE - 1) {
        fprintf(stderr, "Cannot insert ASCII(%u). Heap is already full!\n", n.symbol);
    }

    h->data[h->size] = n;

    int cur = h->size;
    
    // As long as you aren't in the root node, and while the 
    // parent probability is greater, we swap.
    while (cur > 0 && h->data[cur].probability < h->data[parent(cur)].probability) {
        swap(&h->data[cur], &h->data[parent(cur)], sizeof(HuffmanNode));
        cur = parent(cur);
    }
    
    h->size++; 
};

int huff_minheap_pop(HuffmanNode *node, MinHeap *h) {
    
    if (h->size == 0) {
        return MINHEAP_STATUS_EMPTY;
    }

    *node = huff_minheap_get_min(h);
    huff_minheap_delete_min(h);
    
    return MINHEAP_STATUS_SUCCESS;
}

HuffmanNode huff_minheap_get_min(MinHeap *h) {
    return h->data[0];
};

void huff_minheap_print(MinHeap* h) {
    // Simply print the array. This is an
    // inorder traversal of the tree
    printf("Min Heap:\n");
    for (int i=0; i<h->size; i++) {
        printf("0x%X ('%c') -> ", h->data[i].symbol, h->data[i].symbol);
    }
    printf("\n");
}
