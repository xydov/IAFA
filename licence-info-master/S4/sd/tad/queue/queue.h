#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <stdlib.h>
typedef struct s_queue *Queue;

Queue init_queue();
Queue queue_push(Queue q, int v);
Queue queue_pop(Queue q);
int queue_top(Queue q);
bool queue_empty(Queue q);


#endif