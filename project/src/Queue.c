#include "Queue.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>

Queue *queue_allocate(Queue* qptr)
{
    qptr = (Queue*)calloc(1, sizeof(Queue));
    return qptr;
}

void queue_clear(Queue *qptr)
{
    if(qptr == NULL)
    {
        return;
    }
}

Node* queue_enqueue(Queue *qptr, void* data, size_t sz)
{
    if(qptr == NULL)
    {
        qptr = queue_allocate(qptr);
    }

    Node* ptr = node_allocate(data, sz);

    if(qptr->Count == 0)
    {
        qptr->Data = qptr->Head = qptr->Tail = ptr;
    }
    else
    {
        qptr->Head->Previous = ptr;
        ptr->Next = qptr->Head;
        qptr->Head = ptr;
    }

    qptr->Count++;

    return ptr;
}

Node* queue_denqueue(Queue *qptr)
{
    if(qptr == NULL)
    {
        return NULL;
    }

    Node* oldtail = qptr->Tail;
    qptr->Tail = oldtail->Previous;
    qptr->Tail->Next = NULL;
    qptr->Count--;

    //nodeFree(oldtail);
    return oldtail;
}

size_t queue_item_count(Queue *qptr)
{
    if(qptr != NULL)
    {
        return qptr->Count;
    }

    return -1;
}
