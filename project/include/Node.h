#ifndef _NODE_C
#define _NODE_C

#include <stddef.h>

typedef struct Node
{
    void* Data;
    size_t Size;
    struct Node* Next;
    struct Node* Previous;
}Node;

extern Node* nodeAllocate(void* data, size_t sz);

extern void nodeFree(Node* ptr);
extern void nodeCopy(Node* dest, Node* orig);

extern int nodeAreEqual(Node* first, Node* second);
extern int nodeIsGreater(Node* first, Node* second);
extern int nodeIsLess(Node* first, Node* second);

#endif
