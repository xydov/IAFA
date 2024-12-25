#include "bstree.h"
#include <stdio.h>

/* Define this for solving the exercice 1 - coloring the tree. */
#define EXERCICE_1
/* Define this for solving the exercice 2. - test rotations on nodes */
#define EXERCICE_2
/* Define this for solving the exercice 3. - fix rb property after add*/
#define EXERCICE_3
/* Define this for solving the exercice 4. - nothing to do, just to verify that search is still operational */
#define EXERCICE_4
/* Define this for solving the exercice 5. - fix rb property after remove */
#define EXERCICE_5



#ifdef EXERCICE_3
#undef EXERCICE_2
#endif

/**
 * Print the value of a node.
 * @param t the tree node to output
 * @param userData unused pointer.
 */
void print_tree(const BinarySearchTree *t, void *userData) {
    (void) userData;
    printf("%d ", bstree_root(t));
}

/** Main function for testing the Tree implementation.
 * The main function expects one parameter that is the file where values added to the tree, searched into the
 * tree and removed from the tree are to be read.
 *
 * This file must contain the following informations :
 * - on the first line, the number of values to be added to the tree,
 * - on the second line, the values to be added, separated by a space (or tab).
 * - on the third line, the number of values to be searched into the tree.
 * - on the fourth line, the values to be searched, separated by a space (or tab).
 * - on the fifth line, the number of values to be removed from the tree.
 * - on the sixth line, the values to be removed, separated by a space (or tab).
 *
 * The values will be added, searched and remove in the order they are read from the file.
 */
int main(int argc, char **argv) {
    // to silence compiler
    int fprintf_ret = 0;
    fprintf_ret ++;

    if (argc < 2) {
        fprintf(stderr, "usage : %s filename\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (!input) {
        perror(argv[1]);
        return 1;
    }


    BinarySearchTree *theTree = bstree_create();

    /* Exercice 1 : add values to the BinarySearchTree */
    printf("Adding values to the tree.\n\t");
    int n;
    fprintf_ret = fscanf(input, "%d", &n);

    for (int i = 0; i < n; ++i) {
        int v;
        fprintf_ret = fscanf(input, "%d", &v);
        printf("%d ", v);
        bstree_add(&theTree, v);
    }
    printf("\nDone.\n");

#ifdef EXERCICE_1
    /* Exercice 1 : exporting the colored tree */
    printf("Exporting the tree.\n\t");
    FILE *output = fopen("redblacktree_0.dot", "w");
    rbtree_export_dot(theTree, output);
    fclose(output);
    printf("\nDone.\n");

#ifdef EXERCICE_2
    /* Exercice 2 : rotate left */
    printf("Rotating the tree left around %d.\n\t", bstree_root(theTree));
    testrotateleft(theTree);
    theTree = bstree_parent(theTree);
    output = fopen("redblacktree_0_leftrotateroot.dot", "w");
    rbtree_export_dot(theTree, output);
    fclose(output);
    printf("Done.\n");

    printf("Rotating the tree right around %d.\n\t", bstree_root(bstree_left(theTree)));
    testrotateright(bstree_left(theTree));
    output = fopen("redblacktree_0_rightrotateleftrotatedroot.dot", "w");
    rbtree_export_dot(theTree, output);
    fclose(output);
    printf("\nDone.\n");
#endif

#ifdef EXERCICE_4
    /* Exercice 4 : search for values on the tree */
    printf("Searching into the tree.");
    fprintf_ret = fscanf(input, "%d", &n);
    for (int i = 0; i < n; ++i) {
        int v;
        fprintf_ret = fscanf(input, "%d", &v);
        printf("\n\tSearching for value %d in the tree : %s", v, bstree_search(theTree, v) ? "true" : "false");
    }
    printf("\nDone.\n");

#ifdef EXERCICE_5
    /* Exercice 5 : remove a value from the tree */
    printf("Removing from the tree.");
    fprintf_ret = fscanf(input, "%d", &n);
    for (int i = 0; i < n; ++i) {
        int v;
        fprintf_ret = fscanf(input, "%d", &v);
        printf("\n\tRemoving the value %d from the tree : \t", v);
        bstree_remove(&theTree, v);

        char filename[256];
        sprintf(filename, "thetree-%d.dot", i + 1);
        output = fopen(filename, "w");
        rbtree_export_dot(theTree, output);
        fclose(output);
    }
    printf("\nDone.\n");
#endif
#endif
#endif

    bstree_delete(&theTree);
    fclose(input);
    return 0;
}
