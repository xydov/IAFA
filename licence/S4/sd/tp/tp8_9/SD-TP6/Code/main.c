#include "bstree.h"
#include <stdio.h>

/* Define this for solving the exercice 1. */
#define EXERCICE_1
/* Define this for solving the exercice 2. */
#define EXERCICE_2
/* Define this for solving the exercice 3. */
#define EXERCICE_3
/* Define this for solving the exercice 4. */
#define EXERCICE_4
/* Define this for solving the exercice 5. */
#define EXERCICE_5
/* Define this for solving the exercice 6. */
#define EXERCICE_6
/* Define this for solving the exercice 7. */
#define EXERCICE_7

/**
 * This function output one node using the <a href="https://www.graphviz.org/documentation/">dot</a> syntax.
 * A node must defined its shape and its links to the left and righet subtrees. If one of this subtree is NULL,
 * a grey box with the label NIL is drawn.
 * @dot
 * digraph node_example {
 *      node [shape = record];
 *      parent [label="bstree_parent()"]
 *      treeroot [label="{{<parent>}|root|{<left>|<right>}}"];
 *      left [label="bstree_left()"];
 *      right [label="bstree_right()"];
 *      parent:s ->treeroot:parent:c [headclip=false, tailclip=false]
 *      treeroot:left:c -> left:n [headclip=false, tailclip=false]
 *      treeroot:right:c -> right:n [headclip=false, tailclip=false]
 * }
 * @enddot
 * @param t the tree node to draw.
 * @param userData the file to output the dot commands. Concretely, this parameter will be of type FILE * when the functor is called.
 */
void node_to_dot(const BinarySearchTree *t, void *userData) {
    FILE *file = (FILE *) userData;

    printf("%d ", bstree_root(t));
    fprintf(file, "\tn%d [label=\"{{<parent>}|%d|{<left>|<right>}}\"];\n",
            bstree_root(t), bstree_root(t));

    if (bstree_left(t)) {
        fprintf(file, "\tn%d:left:c -> n%d:parent:c [headclip=false, tailclip=false]\n",
                bstree_root(t), bstree_root(bstree_left(t)));
    } else {
        fprintf(file, "\tlnil%d [style=filled, fillcolor=grey, label=\"NIL\"];\n", bstree_root(t));
        fprintf(file, "\tn%d:left:c -> lnil%d:n [headclip=false, tailclip=false]\n",
                bstree_root(t), bstree_root(t));
    }
    if (bstree_right(t)) {
        fprintf(file, "\tn%d:right:c -> n%d:parent:c [headclip=false, tailclip=false]\n",
                bstree_root(t), bstree_root(bstree_right(t)));
    } else {
        fprintf(file, "\trnil%d [style=filled, fillcolor=grey, label=\"NIL\"];\n", bstree_root(t));
        fprintf(file, "\tn%d:right:c -> rnil%d:n [headclip=false, tailclip=false]\n",
                bstree_root(t), bstree_root(t));
    }
}

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

    if (argc < 2) {
        fprintf(stderr, "usage : %s filename\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (!input) {
        perror(argv[1]);
        return 1;
    }

#ifdef EXERCICE_1
    BinarySearchTree *theTree = bstree_create();
	
    /* Exercice 1 : add values to the BinarySearchTree */
    printf("Adding values to the tree.\n\t");
    int n;
    int err = 0;
    err++;

    err = fscanf(input, "%d", &n);

    for (int i = 0; i < n; ++i) {
        int v;
        err = fscanf(input, "%d", &v);
        printf("%d ", v);
        bstree_add(&theTree, v);
    }
    printf("\nDone.\n");

#ifdef EXERCICE_2
    /* exercice 2 : recursive traversal of the tree to apply a given functor */
    printf("Visiting the tree.");
    printf("\n\tPrefix visitor = ");
    bstree_depth_prefix(theTree, print_tree, NULL);
    printf("\n\tInfix visitor = ");
    bstree_depth_infix(theTree, print_tree, NULL);
    printf("\n\tPostfix visitor = ");
    bstree_depth_postfix(theTree, print_tree, NULL);
    printf("\nDone.\n");

#ifdef EXERCICE_3
    /* Exercice 3 : iterative breadfirst and depth-first traversal of the tree to visualize the tree */
    printf("Exporting the tree.\n\t");
    FILE *output = fopen("FullTree.dot", "w");
    fprintf(output, "digraph BinarySearchTree {\n\tgraph [ranksep=0.5];\n\tnode [shape = record];\n\n");
    bstree_iterative_breadth_prefix(theTree, node_to_dot, output);
    fprintf(output, "\n}\n");
    fclose(output);
    printf("\nDone.\n");

#ifdef EXERCICE_4
    /* Exercice 4 : search for values on the tree */
    printf("Searching into the tree.");
    err = fscanf(input, "%d", &n);
    for (int i = 0; i < n; ++i) {
        int v;
        err = fscanf(input, "%d", &v);
        printf("\n\tSearching for value %d in the tree : %s", v, bstree_search(theTree, v) ? "true" : "false");
    }
    printf("\nDone.\n");

#ifdef EXERCICE_5
    /* Exercice 5 : remove a value from the tree */
    printf("Removing from the tree.");
    err = fscanf(input, "%d", &n);
    for (int i = 0; i < n; ++i) {
        int v;
        err = fscanf(input, "%d", &v);
        printf("\n\tRemoving the value %d from the tree : \t", v);
        bstree_remove(&theTree, v);

        char filename[256];
        sprintf(filename, "Tree-%d.dot", i + 1);
        output = fopen(filename, "w");
        fprintf(output, "digraph BinarySearchTree%d {\n\tgraph [ranksep=0.5];\n\tnode [shape = record];\n\n", i);
        bstree_iterative_depth_infix(theTree, node_to_dot, output);
        fprintf(output, "\n}\n");
        fclose(output);
    }
    printf("\nDone.\n");

#ifdef EXERCICE_6
    /* Exercice 6 : Iterate in descenfing order on the tree */
    printf("Iterate descending onto the tree.\n\tvalues : ");
    BSTreeIterator *i = bstree_iterator_create(theTree, backward);
    for (i = bstree_iterator_begin(i); !bstree_iterator_end(i); i = bstree_iterator_next(i))
        printf("%d ", bstree_root(bstree_iterator_value(i)));
    bstree_iterator_delete(&i);
    printf("\nDone.\n");

#ifdef EXERCICE_7
    /* Exercice 7 : free all used memory */
    printf("Deleting the tree.");
    bstree_delete(&theTree);
    printf("\nDone.\n");
#endif

#endif
#endif
#endif
#endif
#endif
#endif

    fclose(input);
    return 0;
}
