#ifndef _LIST_C
#define _LIST_C

#include "Node.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct List
{
    size_t Count;
    Node* Head;
    Node* Tail;
    Node* IteratorPosition;
}List;

extern List* list_allocate(List* lptr);
extern void list_clear(List* lptr);

extern Node* list_add_to_head(List* lptr, void* data, size_t sz);
extern Node* list_add_to_tail(List* lptr, void* data, size_t sz);
extern Node* list_insert(List* lptr, void* data, size_t sz, int pos);

extern void list_remove_from_head(List* lptr);
extern void list_remove_from_tail(List* lptr);
extern void list_remove(List* lptr, const Node* node);
extern void list_remove_at(List* lptr, int pos);
extern void list_remove_value(List* lptr, void* data, size_t sz);

extern size_t list_item_count(List* lptr);
extern size_t list_index_of(List* lptr, const Node* node);
extern size_t list_index_of_value(List* lptr, void* data, size_t sz);
extern Node* list_get_at(List* lptr, int atpos);

extern Node* list_get_first(List* lptr);
extern Node* list_get_next(List* lptr);
extern Node* list_get_last(List* lptr);
extern Node* list_get_previous(List* lptr);

extern List* list_sort(List* lptr);
extern List* list_merge(List* lptrFirst, List* lptrSecond);
extern List* list_join(List* lptrFirst, List* lptrSecond);

#endif
