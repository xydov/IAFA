/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)
 
 Interface pour l'implantation du TAD BinarySearchTree vu en cours.
 */
/*-----------------------------------------------------------------*/
#ifndef __BSTREE__H__
#define __BSTREE__H__
#include <stdbool.h>
#include <stdio.h>

/*------------------------  BSTreeType  -----------------------------*/

/** \defgroup ADTBStree BinarySearchTree
 * Documentation of the implementation of the abstract data type BinarySearchTree.
 * @{
 */

/** \defgroup BSTreeType Type definition.
 * @{
 */
/** Opaque definition of the type BinaryTree */
typedef struct _bstree BinarySearchTree;
typedef BinarySearchTree *ptrBinarySearchTree;
/** @} */

/*------------------------  BaseBSTree  -----------------------------*/

/** \defgroup BaseBSTree General function on binary trees.
 * @{
 *
*/
/** Constructor : builds an empty BinarySearchTree
 */
BinarySearchTree *bstree_create();

/** Destructor : Delete the tree.
 */
void bstree_delete(ptrBinarySearchTree *t);

/** Operator : is the tree empty ?
 * bstree_empty : BinarySearchTree -> boolean
 */
bool bstree_empty(const BinarySearchTree *t);

/** Operator : returns the value of the root of the tree.
 * @pre !bstree_empty(t)
 */
int bstree_root(const BinarySearchTree *t);

/** Operator : returns the left subtree.
 * @pre !bstree_empty(t)
 */
BinarySearchTree *bstree_left(const BinarySearchTree *t);

/** Operator : returns the right subtree.
 * @pre !bstree_empty(t)
 */
BinarySearchTree *bstree_right(const BinarySearchTree *t);

/** Operator : returns the parent subtree
 * @pre !bstree_empty(t)
 */
BinarySearchTree *bstree_parent(const BinarySearchTree *t);

/** @} */

/*------------------------  BSTreeDictionary  -----------------------------*/

/** \defgroup BSTreeDictionary Dictionary operators on BinarySearchTree.
 @{
 */
/** Constructor : add a new value to the BinarySearchTree.
 *
 * @param t
 * @param v
 */
void bstree_add(ptrBinarySearchTree *t, int v);

/** Operator : search for a value in a BinarySearchTree.
 */
bool bstree_search(const BinarySearchTree *t, int v);

/** Operator : remove a value from a BinarySearchTree.
 */
void bstree_remove(ptrBinarySearchTree *t, int v);

/** @} */


/*------------------------  BSTreeVisitors  -----------------------------*/

/** \defgroup BSTreeVisitors Some visitors that could be used on BinarySearchTree.
 @{
 */
/** Functor with user data to be used with the several visitors that can run on trees.
 *  This functor receive as argument subtree from which the root node must be processes and an opaque
 *  pointer to user provided data.
 */
typedef void(*OperateFunctor)(const BinarySearchTree *, void *);

/** \defgroup BSTreeDepthFirstVisitors Depth first visitor and their different implementation.
 @{
*/
/** Visitor : prefix, depth first visitor.
 * This is the recursive implementation of the visitor.
 * @param t the tree to visit.
 * @param f the functor to apply on each node of the tree.
 * @param userData user defined parameters to forward to the functor.
 */
void bstree_depth_prefix(const BinarySearchTree *t, OperateFunctor f, void *userData);

/** Visitor : infix, depth first visitor.
 * This is the recursive implementation of the visitor.
 * @param t the tree to visit.
 * @param f the functor to apply on each node of the tree.
 * @param userData user defined parameters to forward to the functor.
 */
void bstree_depth_infix(const BinarySearchTree *t, OperateFunctor f, void *userData);

/** Visitor : postfix, depth first visitor.
 * This is the recursive implementation of the visitor.
 * @param t the tree to visit.
 * @param f the functor to apply on each node of the tree.
 * @param userData user defined parameters to forward to the functor.
 */
void bstree_depth_postfix(const BinarySearchTree *t, OperateFunctor f, void *userData);

/** Visitor : infix, depth first visitor.
 * This is the iterative implementation of the visitor.
 * @param t the tree to visit.
 * @param f the functor to apply on each node of the tree.
 * @param userData user defined parameters to forward to the functor.
 */
void bstree_iterative_depth_infix(const BinarySearchTree *t, OperateFunctor f, void *userData);
/** @} */

/** \defgroup BSTreeBreathFirstVisitors Breadth first visitor and their different implementation.
 * @{
*/

/** Visitor : prefix, breadth first visitor.
 * This is the iterative implementation of the visitor.
 * @param t the tree to visit.
 * @param f the functor to apply on each node of the tree.
 * @param userData user defined parameters to forward to the functor.
 */
void bstree_iterative_breadth_prefix(const BinarySearchTree *t, OperateFunctor f, void *userData);
/** @} */

/** @} */

/*------------------------  BSTreeIterator  -----------------------------*/

/** \defgroup BSTreeIterator Iterators on BinarySearchTree.
 * @{
 */
/** \defgroup BSTreeIteratorType BSTreeIterator related types.
 @{
 * Using a BSTreeIterator, a BinarySearchTree can be scanned in increasing or decreasing order of the keys.
 *
*/
/**
 * Define the direction the iterator walks on the tree.
 */
typedef enum {
    forward, backward
} IteratorDirection;
/**
 * Opaque definition of the BSTreeIterator type.
 */
typedef struct _BSTreeIterator BSTreeIterator;
typedef BSTreeIterator *ptrBSTreeIterator;
/** @} */

/** Constructor : builds an iterator on the collection c, going in the direction d.
 */
BSTreeIterator *bstree_iterator_create(const BinarySearchTree *c, IteratorDirection d);

/**
 * Destructor : delete the iterator
 */
void bstree_iterator_delete(ptrBSTreeIterator *i);

/**
 * Operator : puts the iterator at the beginning, with respect to its direction, of the collection.
 */
BSTreeIterator *bstree_iterator_begin(BSTreeIterator *i);

/**
 * Operator : tests if the iterator at the end, with respect to its direction, of the collection.
 */
bool bstree_iterator_end(const BSTreeIterator *i);

/**
 * Operator : advance the iterator on the next element, with respect to its direction, of the collection.
 */
BSTreeIterator *bstree_iterator_next(BSTreeIterator *i);

/**
 * Operator : returns the iterator value, i.e, the root of the currently visited subtree.
 */
const BinarySearchTree *bstree_iterator_value(const BSTreeIterator *i);
/** @} */

/*---------------------------  RBTSpecific  -------------------------------*/
void rbtree_export_dot(const BinarySearchTree *t, FILE *file);
void testrotateleft(BinarySearchTree *t);
void testrotateright(BinarySearchTree *t);

/** @} */
#endif
