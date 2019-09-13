#include "Stack.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>

Stack *stackAllocate(Stack* sptr)
{
    sptr = (Stack*)malloc(sizeof(Stack));
    memset(sptr, 0, sizeof(Stack));
    return sptr;
}

void stackClear(Stack* sptr)
{
    if(sptr == NULL)
    {
        return;
    }
}

Node* stackPush(Stack* sptr, void* data, size_t sz)
{
    if(sptr == NULL)
    {
        sptr = stackAllocate(sptr);
    }

    Node* ptr = nodeAllocate(data, sz);

    if(sptr->Count == 0)
    {
        sptr->Data = sptr->Head = sptr->Tail = ptr;
    }
    else
    {
        sptr->Tail->Next = ptr;
        ptr->Previous = sptr->Tail;
        sptr->Tail = ptr;
    }

    sptr->Count++;

    return ptr;
}

Node *stackPop(Stack* sptr)
{
    if(sptr == NULL)
    {
        return NULL;
    }

    Node* oldtail = sptr->Tail;
    sptr->Tail = oldtail->Previous;
    sptr->Tail->Next = NULL;
    sptr->Count--;

    //nodeFree(oldtail);
    return oldtail;
}

size_t stackItemCount(Stack *sptr)
{
    if(sptr != NULL)
    {
        return sptr->Count;
    }

    return -1;
}
