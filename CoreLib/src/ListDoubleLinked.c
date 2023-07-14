/*
BSD 2-Clause License

Copyright (c) 2017, Subrato Roy (subratoroy@hotmail.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "ListDoubleLinked.h"
#include "Buffer.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <limits.h>


typedef struct node_double_linked_t
{
    void* data;
    size_t size;
    struct node_double_linked_t* next;
    struct node_double_linked_t* previous;
}node_double_linked_t;

typedef struct list_double_linked_t
{
    long count;
    node_double_linked_t* head;
    node_double_linked_t* tail;
    node_double_linked_t* iterator;
    lock_t lock;
}list_double_linked_t;

void list_double_linked_internal_remove_from_head(list_double_linked_t* lptr);
void list_double_linked_internal_remove_from_tail(list_double_linked_t* lptr);
void list_double_linked_internal_add_to_head(list_double_linked_t* lptr, node_double_linked_t *ptr);
void list_double_linked_internal_add_to_tail(list_double_linked_t* lptr, node_double_linked_t* ptr);

list_double_linked_t * list_double_linked_allocate(list_double_linked_t* lptr)
{
    lptr = (list_double_linked_t*)calloc(1, sizeof(list_double_linked_t));

    if (!lptr)
    {
        return NULL;
    }

    lptr->count = 0;
    lptr->head = lptr->tail = NULL;
    lptr->iterator = NULL;
    lock_create(lptr->lock);
    return lptr;
}

void list_double_linked_clear(list_double_linked_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }
    else
    {
        while(lptr->count > 0)
        {
            list_double_linked_internal_remove_from_tail(lptr);
        }
    }
}

void list_double_linked_free(list_double_linked_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }
    else
    {
        while(lptr->count > 0)
        {
            list_double_linked_internal_remove_from_tail(lptr);
        }

        lock_destroy(lptr->lock);
        free(lptr);
    }
}

void list_double_linked_lock(list_double_linked_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    lock_acquire(lptr->lock);
}

void list_double_linked_unlock(list_double_linked_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    lock_release(lptr->lock);
}

void list_double_linked_add_to_head(list_double_linked_t* lptr, void* data, size_t sz)
{
    list_double_linked_insert(lptr, data, sz, 0);
}

void list_double_linked_add_to_tail(list_double_linked_t* lptr, void* data, size_t sz)
{
    list_double_linked_insert(lptr, data, sz, LONG_MAX);
}

void list_double_linked_insert(list_double_linked_t* lptr, void* data, size_t sz, long pos)
{
	if (lptr == NULL)
	{
        return;
	}

    node_double_linked_t* ptr = NULL;

    ptr = (node_double_linked_t*)calloc(1, sizeof(node_double_linked_t));

    if (!ptr)
    {
        return;
    }

    ptr->data = calloc(1, sz);

    if (!ptr->data)
    {
        free(ptr);
        return;
    }

    memcpy(ptr->data, data, sz);
    ptr->size = sz;

    if(pos <= 0)
    {
        list_double_linked_internal_add_to_head(lptr, ptr);
        return;
    }

    if (pos >= lptr->count)
    {
        list_double_linked_internal_add_to_tail(lptr, ptr);
        return;
    }

    int idx = 1;
    for(node_double_linked_t* curptr = lptr->head ; curptr->next != NULL; curptr = curptr->next, idx++)
    {
        if(pos == idx)
        {
            node_double_linked_t* oldnext = curptr->next;

            curptr->next = ptr;
            ptr->next = oldnext;

            lptr->count++;
            break;
        }

        idx++;
    }
}

void list_double_linked_remove_from_head(list_double_linked_t* lptr)
{
    list_double_linked_remove_at(lptr, 0);
}

void list_double_linked_remove_from_tail(list_double_linked_t* lptr)
{
    list_double_linked_remove_at(lptr, LONG_MAX);
}

void list_double_linked_remove(list_double_linked_t* lptr, const void *data)
{
    if(lptr == NULL || data == NULL)
    {
        return;
    }

    for(node_double_linked_t* curptr = lptr->head ; curptr->next != NULL; curptr = curptr->next)
    {
        if(memcmp(data, curptr->data, curptr->size) == 0)
        {
            if(curptr->next == NULL)
            {
                list_double_linked_internal_remove_from_tail(lptr);
                break;
            }

            if(curptr == lptr->head)
            {
                list_double_linked_internal_remove_from_head(lptr);
                break;
            }

            node_double_linked_t* targetnode = curptr->next;

            free(curptr->data);
            free(curptr);

            lptr->count--;
            break;
        }
    }
}

void list_double_linked_remove_at(list_double_linked_t* lptr, long pos)
{
    if(lptr == NULL || pos < 0)
    {
        return;
    }

    if(pos > lptr->count -1)
    {
        return;
    }

    if(pos >= lptr->count -1)
    {
        list_double_linked_internal_remove_from_tail(lptr);
    }
    else
    {
        if(pos == 0)
        {
            list_double_linked_internal_remove_from_head(lptr);
        }
        else
        {
            int idx = 1;
            for(node_double_linked_t* curptr = lptr->head ; curptr->next != NULL; curptr = curptr->next, idx++)
            {
                if(idx == pos)
                {
                    node_double_linked_t* prev = curptr->previous;
                    node_double_linked_t* next = curptr->next;

                    prev->next = next;
                    next->previous = prev;

                    free(curptr->data);
                    free(curptr);

                    lptr->count--;
                    break;
                }
            }
        }
    }
}

void list_double_linked_remove_value(list_double_linked_t* lptr, void* data, size_t sz)
{
    if(lptr == NULL)
    {
        return;
    }

    node_double_linked_t* ptr = NULL;

    ptr = lptr->head;

    int idx = 0;

    while(true)
    {
        if(ptr == NULL)
        {
            break;
        }

        if(memcmp(ptr->data, data, ptr->size) == 0 && ptr->size == sz)
        {
            if(idx >= lptr->count - 1)
            {
                list_double_linked_internal_remove_from_tail(lptr);
                break;
            }

            if(idx == 0)
            {
                list_double_linked_internal_remove_from_head(lptr);
                break;
            }

            node_double_linked_t* prev = ptr->previous;
            node_double_linked_t* next = ptr->next;

            prev->next = next;
            next->previous = prev;

            free(ptr->data);
            free(ptr);

            lptr->count--;
            break;
        }

        ptr = ptr->next;
        idx++;
    }

    return;
}

long list_double_linked_item_count(list_double_linked_t* lptr)
{
    if(lptr != NULL)
    {
        return lptr->count;
    }

    return 0;
}

long list_double_linked_index_of(list_double_linked_t *lptr, const void *node)
{
    if(lptr == NULL)
    {
        return -1;
    }

    node_double_linked_t* ptr = NULL;

    ptr = lptr->head;

    long idx = 0;

    if(ptr->data == node)
    {
        return idx;
    }

    while(true)
    {
        if(ptr == NULL)
        {
            break;
        }

        ptr = ptr->next;
        idx++;

        if(ptr->data == node)
        {
            return idx;
        }
    }

    return -1;
}

long list_double_linked_index_of_value(list_double_linked_t* lptr, void* data, size_t sz)
{
    if(lptr == NULL)
    {
        return -1;
    }

    node_double_linked_t* ptr = NULL;

    ptr = lptr->head;

    long idx = 0;

    if(memcmp(ptr->data, data, ptr->size) == 0 && ptr->size == sz)
    {
        return idx;
    }

    while(true)
    {
        if(ptr == NULL)
        {
            break;
        }

        ptr = ptr->next;
        idx++;

        if(memcmp(ptr->data, data, ptr->size) == 0)
        {
            lock_release(lptr->lock);
            return idx;
        }
    }

    return -1;
}

void *list_double_linked_get_at(list_double_linked_t* lptr, long atpos)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    if(atpos > (lptr->count - 1) || atpos < 0)
    {
        return NULL;
    }

    node_double_linked_t* ptr = NULL;

    ptr = lptr->head;

    if(atpos > 0)
    {
        for(int idx = 0; idx < atpos; idx++)
        {
            ptr = ptr->next;
        }
    }

    return ptr->data;
}

void* list_double_linked_get_first(list_double_linked_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->iterator = lptr->head;
    return lptr->iterator->data;
}

void* list_double_linked_get_next(list_double_linked_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    if(lptr->iterator->next == NULL)
    {
        return NULL;
    }

    lptr->iterator = lptr->iterator->next;

    return lptr->iterator->data;
}

void* list_double_linked_get_last(list_double_linked_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->iterator = lptr->tail;
    return lptr->iterator->data;
}

void* list_double_linked_get_previous(list_double_linked_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    if(lptr->iterator->previous == NULL)
    {
        return NULL;
    }

    lptr->iterator = lptr->iterator->previous;

    return lptr->iterator->data;
}

list_double_linked_t* list_double_linked_sort(list_double_linked_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    return NULL;
}

list_double_linked_t* list_double_linked_merge(list_double_linked_t* lptrFirst, list_double_linked_t* lptrSecond)
{
    if(lptrFirst == NULL)
    {
        return lptrSecond;
    }

    if(lptrSecond == NULL)
    {
        return lptrFirst;
    }

    return NULL;
}

list_double_linked_t* list_double_linked_join(list_double_linked_t* lptrFirst, list_double_linked_t* lptrSecond)
{
    if(lptrFirst == NULL)
    {
        return lptrSecond;
    }

    if(lptrSecond == NULL)
    {
        return lptrFirst;
    }

    return NULL;
}

void list_double_linked_internal_remove_from_head(list_double_linked_t* lptr)
{
    node_double_linked_t* oldhead = lptr->head;
    lptr->head = lptr->head->next;

    free(oldhead->data);
    free(oldhead);

    lptr->count--;
}

void list_double_linked_internal_remove_from_tail(list_double_linked_t* lptr)
{
    node_double_linked_t* oldtail = lptr->tail;

    if(lptr->tail != NULL)
    {
        lptr->tail->next = NULL;
    }

    free(oldtail->data);
    free(oldtail);
    oldtail = NULL;
    lptr->count--;
}

void list_double_linked_internal_add_to_head(list_double_linked_t* lptr, node_double_linked_t* ptr)
{
    if(lptr->count == 0)
    {
        lptr->iterator = lptr->head = lptr->tail = ptr;
    }
    else
    {
        ptr->next = lptr->head;
        lptr->head = ptr;
    }

    lptr->count++;
}

void list_double_linked_internal_add_to_tail(list_double_linked_t* lptr, node_double_linked_t* ptr)
{
    if(lptr->count == 0)
    {
        lptr->iterator = lptr->head = lptr->tail = ptr;
    }
    else
    {
        lptr->tail->next = ptr;
        lptr->tail = ptr;
    }

    lptr->count++;
}
