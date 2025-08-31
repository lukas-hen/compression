#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "huffman.h"
#include "util.h"

#define TREE_SUCCESS (1 << 0)
#define TREE_EOT (1 << 1)  // end of tree

static inline void write_huffman_dot_nodes(HuffmanNode* root, FILE* fp) {
    if (root == NULL) {
        return;
    }

    fprintf(fp, "    n%d [ label = \"%c\" ];\n", root->id,
            root->symbol == NULL ? '.' : root->symbol);

    write_huffman_dot_nodes(root->left, fp);
    write_huffman_dot_nodes(root->right, fp);
};

static inline void write_huffman_dot_edges(HuffmanNode* root, FILE* fp) {
    if (root == NULL) {
        return;
    } else if (root->left == NULL && root->right == NULL) {
        return;
    }

    fprintf(fp, "    n%d -> { ", root->id);
    if (root->left != NULL) fprintf(fp, "n%d ", root->left->id);
    if (root->right != NULL) fprintf(fp, "n%d", root->right->id);
    fprintf(fp, " };\n");
    if (root->left != NULL) write_huffman_dot_edges(root->left, fp);
    if (root->right != NULL) write_huffman_dot_edges(root->right, fp);
};

void huffman_tree_to_dot_file(HuffmanNode* root, char* file_path) {
    FILE* fp = fopen(file_path, "w");

    char* header = "digraph BST {\n    node [fontname=\"Arial\" ];\n";
    char* padding = "    ";

    fprintf(fp, header);
    write_huffman_dot_nodes(root, fp);
    fprintf(fp, "\n");
    write_huffman_dot_edges(root, fp);
    fprintf(fp, "\n}");
}

HuffmanNode* huffman_tree_create(ByteSamplingDistribution* bd) {
    // Heap is only used locally in this func.
    // Stack/current scope lifetime is enough.
    MinHeap heap;
    huff_minheap_init(&heap);

    // add all nodes to heap.
    int i;  // used later aswell. keep incrementing when creating tree.
    for (i = 0; i < bd->size; i++) {
        HuffmanNode* node = malloc(sizeof(HuffmanNode));

        node->id = i;
        node->symbol = bd->byte[i];
        node->probability = bd->probability[i];
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        node->is_l_child = NULL;  // defaults to 0 which is false. Should always
                                  // be explicitly set.

        huff_minheap_insert(&heap, node);
    }

    uint8_t minheap_op_status = MINHEAP_STATUS_SUCCESS;
    HuffmanNode *n1, *n2, *cur;

    for (;;) {
        n1 = huff_minheap_pop(&heap);
        if (n1 == NULL) {
            // Finish early, only one node left this iteration.
            break;
        }
        cur = n1;

        n2 = huff_minheap_pop(&heap);
        if (n2 == NULL) {
            // Finish early, only one node left this iteration.
            break;
        }
        cur = n2;

        HuffmanNode* parent = malloc(sizeof(HuffmanNode));

        // Perhaps break-out to function.
        parent->id = ++i;
        parent->probability = n1->probability + n2->probability;
        parent->symbol = NULL;
        parent->left = n1;
        parent->right = n2;
        parent->parent = NULL;
        parent->is_l_child = NULL;

        // printf("Set parent of %c to %c\n", n1->symbol, parent->id)
        n1->parent = parent;
        n1->is_l_child = true;

        n2->parent = parent;
        n2->is_l_child = false;

        // Put parent on heap.
        huff_minheap_insert(&heap, parent);
    }

    return cur;
};

// Depth-first traversal
// Returns TREE_SUCCESS if successfully taking n_steps
// Returns TREE_EOT if reaching the end before
uint8_t huffman_tree_traverse(HuffmanNode** root, int n_steps) {
    if (root == NULL) return TREE_EOT;

    Stack* s = huff_stack_create();
    huff_stack_push(&s, *root);

    HuffmanNode* cur;
    for (int i = 0; i < n_steps; i++) {
        cur = huff_stack_pop(&s);
        if (cur == NULL)  // Tree ended before n_steps.
            return TREE_EOT;

        if (cur->right != NULL) huff_stack_push(&s, cur->right);
        if (cur->left != NULL) huff_stack_push(&s, cur->left);
    }

    *root = cur;

    huff_stack_destroy(s);

    return TREE_SUCCESS;
}

void huffman_tree_print_prefix(HuffmanNode* node) {
    if (node == NULL) {
        return;
    }

    int size = 100;
    uint8_t reverse_buf[size];

    int i = 0;

    do {
        if (node->is_l_child) {
            reverse_buf[i] = 'l';
        } else {
            reverse_buf[i] = 'r';
        }

        node = node->parent;
        i++;
    } while (node->parent != NULL &&
             i < size - 1);  // -1 only for strings. Need delim.

    for (int j = 0; j < i; j++)
      {
            printf("%c", reverse_buf[i - 1 - j]);
        }
    printf("\n");
}

size_t huffman_tree_serialize(HuffmanNode* root, uint8_t* byte_buffer,
                              size_t buffer_size) {
    huffman_tree_traverse(&root, 6);
    huffman_tree_print_prefix(root);
    printf("Node Sz: %d\n", sizeof(HuffmanNode));

    return 0;
};

HuffmanNode* huffman_tree_free(HuffmanNode* root);
HuffmanNode* huffman_tree_deserialize();
