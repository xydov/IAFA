/** Static implementation of the TAD Queue
 */

#include "queue.h"
#include <assert.h>

#define SIZE_MAX_QUEUE 32

struct s_queue 
{
    int queue[SIZE_MAX_QUEUE];
    int head;
    int tail;
    unsigned int size;
};

Queue init_queue()
{
    Queue q = malloc(sizeof(struct s_queue));
    q->head = 0;
    q->tail = -1;
    q->size = 0;
    return q;
}

Queue queue_push(Queue q, int v)
{
    assert(q->size < SIZE_MAX_QUEUE);
    q->tail = (q->tail + 1) % SIZE_MAX_QUEUE;
    q->queue[q->tail] = v;
    ++q->size;
    return q;
}

/** Operator : pop element from queue
 * queue_pop : Queue -> Queue
 * @pre !queue_empty(q)
 */
Queue queue_pop(Queue q)
{
    assert(q->size > 0);
    q->head = (q->head + 1) % SIZE_MAX_QUEUE;
    --q->size;
    return q;
}

/** Operator : get first element from queue
 * queue_top : Queue -> int
 * @pre !queue_empty(q)
 */
int queue_top(Queue q)
{
    assert(q->size > 0);
    return q->queue[q->head];
}

/** Operator : is the queue empty?
 * queue_empty : boolean
 */
bool queue_empty(Queue q)
{
    return q->size == 0;
}