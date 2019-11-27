#ifndef _QUEUE_C
#define _QUEUE_C

#include "Node.h"

typedef struct Queue
{
    size_t Count;
    Node* Data;
    Node* Head;
    Node* Tail;
}Queue;

extern Queue* queueAllocate(Queue *qptr);
extern void queueClear(Queue* qptr);

extern Node* queueEnqueue(Queue* qptr, void* data, size_t sz);
extern Node* queueDenqueue(Queue* qptr);
extern size_t queueItemCount(Queue* qptr);

#endif
