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

extern Queue* queue_allocate(Queue *qptr);
extern void queue_clear(Queue* qptr);

extern Node* queue_enqueue(Queue* qptr, void* data, size_t sz);
extern Node* queue_denqueue(Queue* qptr);
extern size_t queue_item_count(Queue* qptr);

#endif
