#ifndef _STACK_C
#define _STACK_C

#include "Node.h"

typedef struct Stack
{
    size_t Count;
    Node* Data;
    Node* Head;
    Node* Tail;
}Stack;

extern Stack* stackAllocate(Stack* sptr);
extern void stackClear(Stack* sptr);

extern Node* stackPush(Stack* sptr, void* data, size_t sz);
extern Node* stackPop(Stack* sptr);
extern size_t stackItemCount(Stack* sptr);

#endif

