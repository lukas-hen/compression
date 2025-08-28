#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "huffman.h"

#define TREE_SUCCESS (1 << 0)  
#define TREE_EOT     (1 << 1)  // end of tree

static inline void write_huffman_dot_nodes(HuffmanNode *root, FILE *fp) {
    if (root == NULL) {
        return;
    }
    
    fprintf(fp, "    n%d [ label = \"%c\" ];\n", root->id, root->symbol == NULL ? '.' : root->symbol);

    write_huffman_dot_nodes(root->left, fp);
    write_huffman_dot_nodes(root->right, fp);
};

static inline void write_huffman_dot_edges(HuffmanNode *root, FILE *fp) {
    
    if (root == NULL) {
        return;
    } else if (root->left == NULL && root->right == NULL) {
        return;
    }

    fprintf(fp, "    n%d -> { ", root->id);
    if (root->left != NULL)
        fprintf(fp, "n%d ", root->left->id);
    if (root->right != NULL)
        fprintf(fp, "n%d", root->right->id);
    fprintf(fp, " };\n");
    if (root->left != NULL)
        write_huffman_dot_edges(root->left, fp);
    if (root->right != NULL)
        write_huffman_dot_edges(root->right, fp);
};

void huffman_tree_to_dot_file(HuffmanNode *root, char *file_path) {
    FILE *fp = fopen(file_path, "w");

    char *header = "digraph BST {\n    node [fontname=\"Arial\" ];\n";
    char *padding = "    ";

    fprintf(fp, header);    
    write_huffman_dot_nodes(root, fp);
    fprintf(fp, "\n");
    write_huffman_dot_edges(root, fp);
    fprintf(fp, "\n}");
}

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

static void huffman_tree_traverse_pre_order(HuffmanNode *node, int target_steps, uint8_t *status, HuffmanNode **cur, int current_step) {
    
    if (node == NULL) {
        *status = TREE_EOT;
        return;
    }

    // Keep changing the pointer from outside scope to "current" node.
    //printf("%d ", node->id);
    *cur = node;

    if(current_step == target_steps) {
        *status = TREE_SUCCESS;
        return;
    }

    if (*status == TREE_EOT)
        return;

    if (node->left != NULL)
        huffman_tree_traverse_pre_order(node->left, target_steps, status, cur, ++current_step);

    // If we break recursion with EOT, no further recursion should happen.
    if (*status == TREE_EOT)
        return;

    if (node->right != NULL)
        huffman_tree_traverse_pre_order(node->right, target_steps, status, cur, ++current_step);
}

size_t huffman_tree_serialize(HuffmanNode *root, uint8_t *byte_buffer, size_t buffer_size) {
    
    HuffmanNode *cur;
    uint8_t status;

    printf("\n\n[ ");
    //for(int i = 0; i < 100; i++) {
        huffman_tree_traverse_pre_order(root, 8, &status, &cur, 0);
        printf("%c", cur->symbol);
        // if (i < 99)
        //     printf(", ");
        fflush(stdout);
    //}
    printf(" ]\n\n");
    return 0;
};


HuffmanNode *huffman_tree_free(HuffmanNode *root);
HuffmanNode *huffman_tree_deserialize();
