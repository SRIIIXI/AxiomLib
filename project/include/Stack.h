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

extern Stack* stack_allocate(Stack* sptr);
extern void stack_clear(Stack* sptr);

extern Node* stack_push(Stack* sptr, void* data, size_t sz);
extern Node* stack_pop(Stack* sptr);
extern size_t stack_item_count(Stack* sptr);

#endif

