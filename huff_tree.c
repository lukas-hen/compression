#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "huffman.h"

static void write_huffman_dot_nodes(HuffmanNode *root, FILE *fp) {
    if (root == NULL) {
        return;
    }
    
    fprintf(fp, "    n%d [ label = \"%0.4f\" ];\n", root->id, root->probability);

    write_huffman_dot_nodes(root->left, fp);
    write_huffman_dot_nodes(root->right, fp);
};

static void write_huffman_dot_edges(HuffmanNode *root, FILE *fp) {
    if (root == NULL || root->left == NULL || root->right == NULL) {
        return;
    }

    fprintf(fp, "    n%d -> { n%d n%d };\n", root->id, root->left->id, root->right->id);

    write_huffman_dot_edges(root->left, fp);
    write_huffman_dot_edges(root->right, fp);
};

HuffmanNode *huffman_tree_create(ByteSamplingDistribution *bd) {

    // Heap is only used locally in this func.
    // Stack/current scope lifetime is enough.
    MinHeap heap;
    huff_minheap_init(&heap);

    // add all nodes to heap.
    int i; // used later aswell. keep incrementing when creating tree.
    for(i = 0; i < bd->size; i++) {

        HuffmanNode node = {
            .id = i,
            .symbol = bd->byte[i],
            .probability = bd->probability[i],
            .left = NULL,
            .right = NULL
        };

        huff_minheap_insert(&heap, node); // copy
    }

    uint8_t minheap_op_status = MINHEAP_STATUS_SUCCESS;
    HuffmanNode *n1, *n2;

    while(
        minheap_op_status != MINHEAP_STATUS_ERROR_EMPTY || 
        minheap_op_status != MINHEAP_STATUS_LAST_ELEM
        ) {
        
        // Heap alloc nodes now as these need to persist past the current scope.
        // Arena alloc would prob be a better approach.
        n1 = malloc(sizeof(HuffmanNode));
        n2 = malloc(sizeof(HuffmanNode));

        minheap_op_status = huff_minheap_pop(&heap, n1);
        if(minheap_op_status == MINHEAP_STATUS_LAST_ELEM) {
            //printf("'%c' (last)\n", n1->symbol);
            break;
            // Finish early, only one node left this iteration.
        }

        minheap_op_status = huff_minheap_pop(&heap, n2);
        //printf("'%c', '%c'\n", n1->symbol, n2->symbol);

        // Create composite/parent node.
        HuffmanNode parent = {
            .id = ++i,
            .probability = n1->probability + n2->probability,
            .symbol = NULL,
            .left = n1, // n1 < n2
            .right = n2,
        };
    
        // Put parent on heap.
        huff_minheap_insert(&heap, parent);
    }

    return n1;
};

void huffman_tree_to_dot_file(char *file_path, HuffmanNode *root) {
    
    FILE *fp = fopen(file_path, "w");

    char *header = "digraph BST {\n    node [fontname=\"Arial\" ];\n";
    char *padding = "    ";

    fprintf(fp, header);    
    write_huffman_dot_nodes(root, fp);
    fprintf(fp, "\n");
    write_huffman_dot_edges(root, fp);
    fprintf(fp, "\n}");
}


HuffmanNode *huffman_tree_free(HuffmanNode *root);

Encoding huffman_get_encoding(uint8_t symbol);

uint8_t *huffman_tree_serialize();
HuffmanNode *huffman_tree_deserialize();
