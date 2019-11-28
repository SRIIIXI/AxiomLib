#include "Stack.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>

Stack *stack_allocate(Stack* sptr)
{
    sptr = (Stack*)calloc(1, sizeof(Stack));
    return sptr;
}

void stack_clear(Stack* sptr)
{
    if(sptr == NULL)
    {
        return;
    }
}

Node* stack_push(Stack* sptr, void* data, size_t sz)
{
    if(sptr == NULL)
    {
        sptr = stack_allocate(sptr);
    }

    Node* ptr = node_allocate(data, sz);

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

Node *stack_pop(Stack* sptr)
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

size_t stack_item_count(Stack *sptr)
{
    if(sptr != NULL)
    {
        return sptr->Count;
    }

    return -1;
}
