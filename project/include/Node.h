#ifndef _NODE_C
#define _NODE_C

#include <stddef.h>
#include <stdbool.h>

typedef struct Node
{
    void* Data;
    size_t Size;
    struct Node* Next;
    struct Node* Previous;
}Node;

extern Node* node_allocate(void* data, size_t sz);

extern void node_free(Node* ptr);
extern void node_copy(Node* dest, Node* orig);

extern bool node_is_equal(Node* first, Node* second);
extern bool node_is_greater(Node* first, Node* second);
extern bool node_is_less(Node* first, Node* second);

#endif
