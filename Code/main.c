#include "maxheaptree.h"
#include <stdio.h>
#include <memory.h>

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
 // style=dashed,
void node_to_dot(const Node * const t, void *userData) {
    FILE *file = (FILE *) userData;
/*
    printf("%d ", node_root(t));
    fprintf(file, "\tn%d [label=\"{{<parent>}|%d|{<left>|<right>}}\"];\n",
            node_root(t), node_root(t));


        if (node_left(t)) {
            fprintf(file, "\tn%d:left:c -> n%d:parent:c [headclip=false, tailclip=false]\n",
                    node_root(t), node_root(node_left(t)));
        } else {
            fprintf(file, "\tlnil%d [style=filled, fillcolor=dodgerblue, label=\"NIL\"];\n", node_root(t));
            fprintf(file, "\tn%d:left:c -> lnil%d:n [headclip=false, tailclip=false, color=dodgerblue]\n",
                    node_root(t), node_root(t));
        }

        if (node_right(t)) {
            fprintf(file, "\tn%d:right:c -> n%d:parent:c [headclip=false, tailclip=false]\n",
                    node_root(t), node_root(node_right(t)));
        } else {
            fprintf(file, "\trnil%d [style=filled, fillcolor=dodgerblue, label=\"NIL\"];\n", node_root(t));
            fprintf(file, "\tn%d:right:c -> rnil%d:n [headclip=false, tailclip=false, color=dodgerblue]\n",
                    node_root(t), node_root(t));
        }
*/
     printf("%d ", node_root(t));
     fprintf(file, "\tn%p [label=\"{{<parent>}|%d|{<left>|<right>}}\"];\n",
             (void *)t, node_root(t));


     if (node_left(t)) {
         fprintf(file, "\tn%p:left:c -> n%p:parent:c [headclip=false, tailclip=false]\n",
                 (void*)t, (void*)node_left(t));
     } else {
         fprintf(file, "\tlnil%p [style=filled, fillcolor=dodgerblue, label=\"NIL\"];\n", (void*)t);
         fprintf(file, "\tn%p:left:c -> lnil%p:n [headclip=false, tailclip=false, color=dodgerblue]\n",
                 (void *)t, (void *)t);
     }

     if (node_right(t)) {
         fprintf(file, "\tn%p:right:c -> n%p:parent:c [headclip=false, tailclip=false]\n",
                 (void *)t, (void *)node_right(t));
     } else {
         fprintf(file, "\trnil%p [style=filled, fillcolor=dodgerblue, label=\"NIL\"];\n", (void *)t);
         fprintf(file, "\tn%p:right:c -> rnil%p:n [headclip=false, tailclip=false, color=dodgerblue]\n",
                 (void *)t, (void *)t);
     }
}

/**
 * Print the value of a node.
 * @param t the tree node to output
 * @param userData unused pointer.
 */
void print_node(const Node * const t, void *userData) {
    (void) userData;
    printf("%d ", node_root(t));
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

    MaxHeapTree *theTree = mhtree_create();
    printf("Heap created : empty = %s.\n", mhtree_empty(theTree) ? "true" : "false");

    printf("Adding values to the heap.\n");
    int n;
    fscanf(input, "%d", &n);

    for (int i = 0; i < n; ++i) {
        int v;
        fscanf(input, "%d", &v);
        mhtree_add(theTree, v);
    }
    printf("Done.\n");


    char dotname[strlen(argv[1])+1];
    strcpy(dotname, argv[1]);
    strcpy(dotname+strlen(dotname)-3, "dot");
    printf("Exporting the tree to %s.\n\t", dotname);
    FILE *output = fopen(dotname, "w");
    fprintf(output, "digraph MaxHeapTree {\n\tgraph [ranksep=0.75, nodesep = 0.75];\n\tnode [shape = record];\n\n");
    mhtree_depth_prefix(theTree, node_to_dot, output);
    fprintf(output, "\n}\n");
    fclose(output);
    printf("\nDone.\n");


    fclose(input);
    return 0;
}
