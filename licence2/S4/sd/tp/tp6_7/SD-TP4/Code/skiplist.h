#ifndef __DESKIPLIST_H__
#define __DESKIPLIST_H__
#include <stdbool.h>

/**
 *	@defgroup SkipListAT SkipList abstract type
 *  @brief Definition of the SkipList type and operators
 *  @{
 */


/**
 *	@brief Opaque definition of the SkipList abstract data type.
 */
typedef struct s_SkipList *SkipList;

/**
 *	@brief Type of the operator that one may map on a SkipList.
 */
typedef void(*ScanOperator)(int, void*);

/** 
 *  @brief Constructor of an empty SkipList.
 *
 * @par Profile
 * @parblock
 *	skiplist_create : -> SkipList.
 * @endparblock
 *	@param nblevels the number of levels in the skip list.
 *  @return a correctly initialized SkipList.
 */
SkipList skiplist_create(int nblevels);

/**
 *  @brief Destructor of a SkipList.
 *
 * @par Profile
 * @parblock
 *	skiplist_delete : SkipList -> void.
 * @endparblock
 *	@param d the skiplist to delete.
 *
 */
void skiplist_delete(SkipList d);

/**
 *  @brief Access to the size of the SkipList.
 *
 * @par Profile
 * @parblock
 *	skiplist_size : SkipList -> unsigned int
 * @endparblock
 *	@param d the SkipList to access
 *  @return the number of elements in the SkipList.
 * @par Axioms
 * @parblock
 * skiplist_size(skiplist_create) = 0 \n
 * (skiplist_search(d, x) = true)  -> skiplist_size(skiplist_insert(d, x)) = skiplist_size(d)  \n
 * (skiplist_search(d, x) = false) -> skiplist_size(skiplist_insert(d, x)) = 1 + skiplist_size(d) \n
 * @endparblock
 */
unsigned int skiplist_size(SkipList d);


/**
 *  @brief Access to the \f$i^{th}\f$ element of the SkipList.
 *
 * @par Profile
 * @parblock
 *	skiplist_ith : SkipList \f$\times\f$ unsigned int \f$\rightarrow\f$ int
 * @endparblock
 *	@param d the SkipList to access
 *	@param i the index of the required value
 *  @return the number of elements in the SkipList.
 * @pre
 *	0 \f$\le\f$  i \f$<\f$  skiplist_size(d)
 * @par Axioms
 * @parblock
 * (skiplist_ith(d, i) = x) \f$\wedge\f$ ( (\f$\nu\f$ y : ( (skiplist_search(d, y) = true) \f$\wedge\f$  (y \f$\le\f$ x) )) = i ) 
 * @endparblock
 */
int skiplist_ith(SkipList d, unsigned int i);


/**
 *	@brief Insert the value v in the skip list d.
 
 *	@param d the SkipList to search into
 *	@param value the value to search for
 *  @return the eventually modified skiplist.
 *
 *  @invariant The list is always ordered by ascending order
 *	@invariant \f$ \forall i : (0 \le i < skiplist\_size(d) - 1) \rightarrow (skiplist\_ith(d, i) < skiplist\_ith(d, i+1)) \f$
 *	@note the parameter d is modified by side effect and is returned by the function
 *
 */
SkipList skiplist_insert(SkipList d, int value);


/**
 *	@brief Remove the value v from the skip list d.
 
 *	@param d the SkipList to remove from
 *	@param value the value to remove
 *  @return the eventually modified skiplist.
 *
 *  @invariant The list is always ordered by ascending order
 *	@invariant \f$ \forall i : (0 \le i < skiplist\_size(d) - 1) \rightarrow (skiplist\_ith(d, i) < skiplist\_ith(d, i+1)) \f$
 *	@note the parameter d is modified by side effect and is returned by the function
 *
 */
SkipList skiplist_remove(SkipList d, int value);


/**
 *  @brief Search for the presence of a value in a SkipList.
 *
 * @par Profile
 * @parblock
 *	skiplist_search_and_count : SkipList \f$\times\f$ int \f$\rightarrow\f$ unsigned int
 * @endparblock
 *	@param d the SkipList to search into
 *	@param value the value to search for
 *	@param nb_operations The number of tested nodes during the search
 *  @return true if the value was found, false otherwise.
 *
 */
bool skiplist_search(SkipList d, int value, unsigned int *nb_operations);

/**
 *  @brief Apply an operator on each member of the SkipList, from the begining to the end.
 *
 * @par Profile
 * @parblock
 *	skiplist_map : SkipList \f$\times\f$ ScanOperator \f$\rightarrow void\f$
 * @endparblock
 *	@param d the SkipList to access
 *	@param f the operator to apply
 *	@param user_data user supplied parameter for calling the operator.
 */
void skiplist_map(SkipList d, ScanOperator f, void *user_data);



/*-----------------------*/
/* Iterateur             */
/*-----------------------*/
/**
 * @addtogroup  SkipListBidirIterator SkipList bidirectional iterator
 *  @brief Definition of the SkipListIterator type and operators
 * @{
 */
/// Iterator from the begining to the end
#define FORWARD_ITERATOR 1
/// Iterator from the end to the beginning
#define BACKWARD_ITERATOR 0

/**
 *	@brief Opaque definition of the SkipListIterator abstract data type.
 */
typedef struct s_SkipListIterator *SkipListIterator;

/**
 *	@brief Constructor of an iterator.
 * @param d the SkipList to iterate
 * @param w the way the iterator will go (FORWARD_ITERATOR or BACKWARD_ITERATOR)
 * @return the correcly initialized iterator
 */
SkipListIterator skiplist_iterator_create(SkipList d, unsigned char w);

/**
 *	@brief Destructor of an iterator.
 *  @param it the iterator to delete
 */
void skiplist_iterator_delete(SkipListIterator it);

/**
 *	@brief Put the iterator at the beginning of its collection.
 *  @param it the iterator to modify
 *	@return the modified iterator
 *	@note the parameter it is modified by side effect and is returned by the function
 */
SkipListIterator skiplist_iterator_begin(SkipListIterator it);

/**
 *	@brief Test if the iterator is at the end of its collection.
 *  @param it the iterator to test
 *  @return true if the iterator is at the end
 */
bool skiplist_iterator_end(SkipListIterator it);

/**
 *	@brief Increment the iterator to the next position according to its direction.
 *  @param it the iterator to modify
 *	@return the modified iterator
 *	@note the parameter it is modified by side effect and is returned by the function
 */
SkipListIterator skiplist_iterator_next(SkipListIterator it);

/**
 *	@brief Acces to the value of the iterator.
 *  @param it the iterator to delete
 *  @return the value designed by the iterator
 */
int skiplist_iterator_value(SkipListIterator it);


/** @} */



/** @} */

#endif
