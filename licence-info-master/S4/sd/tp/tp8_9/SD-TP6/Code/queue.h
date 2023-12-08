/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)
 
 Implantation du TAD Queue étudié en cours.
 
 */

/*-----------------------------------------------------------------*/
#ifndef __QUEUE__H__
#define __QUEUE__H__
#include <stdio.h>
#include <stdbool.h>

/** \defgroup ADTQueue Queue
 Documentation of the implementation of the abstract data type BinarySearchTree.
 @{
 */

/** \defgroup QueueType Type definition.
 @{
 */
/** Opaque definition of the type Queue */
typedef struct s_queue Queue;
typedef Queue *ptrQueue;
/** @} */

/** \defgroup QueueBase Mandatory functions for using Queues.
 * @{
 *
*/
/** Constructor : builds an empty queue
	queue : -> Queue
*/
Queue *createQueue();

/** Constructor : add an element to the queue
	queue_push : Queue x int -> Queue
	@note : side effect on the queue q
*/
Queue *queuePush(Queue *q, const void *v);

/** Destructor : delete the queue.
 */
void deleteQueue(ptrQueue *q);

/** Operator : pop an element from the queue
	queue_pop : Queue -> Queue
	@pre !queue_empty(q)
*/
Queue *queuePop(Queue *q);

/** Operator : acces to the frist element of the queue
	queue_top : Queue -> int
	@pre !queue_empty(q)
*/
const void *queueTop(Queue *q);

/** Operator : is the queue empty ?
	queue_empty : Queue -> boolean
*/
bool queueEmpty(Queue *q);

/** Operator : size of the queue ?
 size : Queue -> int
 */
unsigned int queueSize(Queue *q);

/** @} */

/** @} */
#endif
