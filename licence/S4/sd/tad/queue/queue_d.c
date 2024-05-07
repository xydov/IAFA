/** Dynamic implementation of the TAD Queue
 */

#include "queue.h"
#include <assert.h>

typedef struct s_internalQueue
{
    int value;
    struct s_internalQueue *next;
} InternalQueue;

struct s_queue
{
    InternalQueue *head;
    InternalQueue *tail;
    unsigned int size;
};

/** Constructor : build an empty queue
 * init_queue : -> Queue
 */
Queue init_queue()
{
    Queue q = malloc(sizeof(struct s_queue));
    q->head = q->tail = NULL;
    q->size = 0;    
    return q;
}

/** Constructor : add element to queue
 * queue_push : Queue x int -> Queue
 */
Queue queue_push(Queue q, int v)
{
    // if queue empty ,add to head, else to tail
    InternalQueue **insert_at = (q->size ? &(q->tail->next): &(q->head));
    InternalQueue *new = malloc(sizeof(InternalQueue));
    new->value = v;
    new->next = NULL;
    *insert_at = new;
    q->tail = new;
    ++(q->size);
    return q;
}

/** Operator : pop an element fro mthe queue
 * queue_pop : Queue -> Queue
 * @pre !queue_empty(q)
 */
Queue queue_pop(Queue q)
{
    assert(q->size > 0);
    InternalQueue *old = q->head;
    q->head = q->head->next;
    --q->size;
    free(old);
    return q;
}

/** Operator : acces the first element of the queue
 * queue_top : Queue -> int
 * @pre !queue_empty(q)
 */
int queue_top(Queue q)
{
    assert(q->size > 0);
    return q->head->value;
}

/** Operator : is the queue empty
 * queue_empty : Queue -> boolean
 */
bool queue_empty(Queue q)
{
    return q->size == 0;
}