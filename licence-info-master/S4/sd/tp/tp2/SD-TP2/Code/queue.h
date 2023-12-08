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

/* Opaque definition of the type Queue */
typedef struct s_queue Queue;
typedef Queue *ptrQueue;

/** Constructor : build an empty queue 
	queue : -> Queue
*/
Queue *createQueue();

/** Delete the queue.
 */
void deleteQueue(ptrQueue *q);

/** Constructor : add an element to the queue 
	queue_push : Queue x int -> Queue
	@note : side effect on the queue q
*/
Queue *queuePush(Queue *q, void *v);

/** Operator : pop an element from the queue 
	queue_pop : Queue -> Queue
	@pre !queue_empty(q)
*/
Queue *queuePop(Queue *q);

/** Operator : acces to the frist element of the queue
	queue_top : Queue -> int
	@pre !queue_empty(q)
*/
void *queueTop(Queue *q);

/** Operator : is the queue empty ?
	queue_empty : Queue -> boolean
*/
bool queueEmpty(Queue *q);

/** Operator : size of the queue ?
 size : Queue -> int
 */
unsigned int queueSize(Queue *q);

/** Dump the queue (print it) on the given FILE*
 */
void queueDump(FILE *f, Queue *s, void(*dumpfunction)(FILE *f, void *e));

#endif
