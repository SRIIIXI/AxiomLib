#include "Queue.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>

Queue *queueAllocate(Queue* qptr)
{
    qptr = (Queue*)calloc(1, sizeof(Queue));
    return qptr;
}

void queueClear(Queue *qptr)
{
    if(qptr == NULL)
    {
        return;
    }
}

Node* queueEnqueue(Queue *qptr, void* data, size_t sz)
{
    if(qptr == NULL)
    {
        qptr = queueAllocate(qptr);
    }

    Node* ptr = nodeAllocate(data, sz);

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

Node* queueDenqueue(Queue *qptr)
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

size_t queueItemCount(Queue *qptr)
{
    if(qptr != NULL)
    {
        return qptr->Count;
    }

    return -1;
}
