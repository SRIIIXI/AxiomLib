#ifndef _LIST_C
#define _LIST_C

#include "Node.h"

typedef struct List
{
    size_t Count;
    Node* Head;
    Node* Tail;
    Node* IteratorPosition;
}List;

extern List* listAllocate(List* lptr);
extern void listClear(List* lptr);

extern Node* listAddToHead(List* lptr, void* data, size_t sz);
extern Node* listAddToTail(List* lptr, void* data, size_t sz);
extern Node* listInsert(List* lptr, void* data, size_t sz, int pos);

extern void listRemoveFromHead(List* lptr);
extern void listRemoveFromTail(List* lptr);
extern void listRemove(List* lptr, const Node* node);
extern void listRemoveAt(List* lptr, int pos);
extern void listRemoveValue(List* lptr, void* data, size_t sz);

extern size_t listItemCount(List* lptr);
extern size_t listIndexOf(List* lptr, const Node* node);
extern size_t listIndexOfValue(List* lptr, void* data, size_t sz);
extern Node* listGetAt(List* lptr, int atpos);

extern Node* listGetFirst(List* lptr);
extern Node* listGetLast(List* lptr);
extern Node* listGetNext(List* lptr);
extern Node* listGetPrevious(List* lptr);

extern List* listSort(List* lptr);
extern List* listMerge(List* lptrFirst, List* lptrSecond);
extern List* listJoin(List* lptrFirst, List* lptrSecond);

#endif
