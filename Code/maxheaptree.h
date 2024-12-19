/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)
 
 Interface pour l'implantation du TAD MaxHeapTree.



 */
/*-----------------------------------------------------------------*/
#ifndef __MAXHEAPTREE__H__
#define __MAXHEAPTREE__H__
#include <stdbool.h>

/*------------------------  MaxHeapTreeType  -----------------------------*/

/** Opaque definition of the type MaxHeapTree */
typedef struct _maxheaptree MaxHeapTree;
typedef MaxHeapTree *ptrMaxHeapTree;

/** Node : abstract binary tree with its (restricted) public interface */
typedef struct _treeNode Node;
int node_root(const Node * const n);
const Node * const node_left(const Node * const n);
const Node * const node_right(const Node * const n);
bool node_empty(const Node *const n);

/*------------------------  BaseMaxHeap  -----------------------------*/

/** Constructor : builds an empty BinarySearchTree
 */
ptrMaxHeapTree mhtree_create();

/** Operator : is the tree empty ?
 * bstree_empty : BinarySearchTree -> boolean
 */
bool mhtree_empty(const MaxHeapTree *t);

/*------------------------  MaxHeapDictionary  -----------------------------*/

/** Constructor : add a new value to the BinarySearchTree.
 *
 * @param t
 * @param v
 */
void mhtree_add(ptrMaxHeapTree t, int v);

/*------------------------  MaxHeapVisitors  -----------------------------*/

/** Functor with user data to be used with the several visitors that can run on trees.
 *  This functor receive as argument subtree from which the root node must be processes and an opaque
 *  pointer to user provided data.
 */
typedef void(*OperateFunctor)(const Node * const, void *);

/** Depth first, prefix visitor */
void mhtree_depth_prefix(const MaxHeapTree *t, OperateFunctor f, void *userData);


#endif /* __MAXHEAPTREE__H__ */
