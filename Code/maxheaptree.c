#include "maxheaptree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/** Node : abstract binary tree with its private interface */
struct _treeNode {
    Node *parent;
    Node *left;
    Node *right;
    int root;
};
typedef Node *ptrNode;

Node *node_cons(Node *left, Node *right, int root) {
    Node *t = malloc(sizeof(struct _treeNode));
    t->parent = NULL;
    t->left = left;
    t->right = right;
    t->root = root;
    return t;
}

bool node_empty(const Node *const n) {
    return n ==NULL;
}

int node_root(const Node *const n) {
    assert(!node_empty(n));
    return n->root;
}

const Node * const node_left(const Node *const n) {
    assert(!node_empty(n));
    return n->left;
}

const Node * const node_right(const Node *const n) {
    assert(!node_empty(n));
    return n->right;
}

/***************************************************************************************/
/**                               Control start here                                  **/
/***************************************************************************************/
/**
 *  Nom         :
 *  Prenom      :
 *  Num Etud    :
 **/

/* Exercice 1  */
struct _maxheaptree {
    Node* tree_root;
    Node* last_node;
    int size;
};


bool mhtree_empty(const MaxHeapTree *t) {
    return t->size == 0;
}

MaxHeapTree *mhtree_create() {
    MaxHeapTree* the_tree = malloc(sizeof(MaxHeapTree));
    the_tree->last_node = NULL;
    the_tree->tree_root = NULL;
    the_tree->size = 0;
    return the_tree;
}

/* Exercice 4 */
void percolate_up(ptrNode x) {
    if (x->parent != NULL && x->root > x->parent->root)
    {
        int val =  x->root;
        x->root = x->parent->root;
        x->parent->root = val;
        percolate_up(x->parent);
    }
    
}

/* Exercice 2  */
bool node_is_leftchild_p(Node* x, Node*p){
    return p->left != NULL && p->left == x;
}
bool node_is_rightchild_p(Node* x, Node*p){
    return p->right != NULL && p->right == x;
}

    
ptrNode search_free_node(ptrNode last) {
    if (last->parent == NULL)
    {
        return last;
    }else{
        Node* p =  last->parent;
        if (node_is_leftchild_p(last, p))
        {
            printf("last is left child\n");
            printf("last =%i \n", p->root);
            return p;
        }else{
            Node* pp = p->parent;
            while (node_is_rightchild_p(p, pp) && pp!= NULL)
            {
                pp = pp->parent;
                p = p->parent;
            }
            // end of while loop, pp == NULL, p is the raccine of tree
            // find leftmost node
            Node* left_most = p->left;
            while (left_most != NULL)
            {
                left_most = left_most->left;
            }
            return left_most;
                        
        }
    }
    
}

/* Exercice 2 et 4 */
void mhtree_add(ptrMaxHeapTree t, int v) {
    printf("Adding %i\n", v);
    Node* new_node = node_cons(NULL, NULL, v);
    if (mhtree_empty(t))
    {
        printf("create first node %i\n", v);
        t->tree_root = new_node;
        t->last_node = new_node;
        t->size +=1;
        printf("created first node %i\n", v);
    }else{
        printf("finding free node\n");
        Node* free_node = search_free_node(t->last_node);
        printf("found a free node %i\n", free_node->root);
        if (free_node->left == NULL)
        {
            free_node->left = new_node;
            
        }else{
            free_node->right = new_node;
        }
        new_node->parent = free_node;
        t->last_node = new_node;
        printf("new_last_node =  %i\n", t->last_node->root);
        printf("new_last_node_parent =  %i\n", t->last_node->parent->root);
    }
    printf("percolating\n");
    percolate_up(new_node); 
    printf("END\n");
}

/* Exercice 3 : Parcours et affichage de l'arbre */
void node_depth_prefix(const Node *n, OperateFunctor f, void *userData) {
}

void mhtree_depth_prefix(const MaxHeapTree *t, OperateFunctor f, void *userData) {
}
