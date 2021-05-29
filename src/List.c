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

#include "List.h"
#include "Buffer.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node_t
{
    void* data;
    size_t size;
    struct node_t* next;
    struct node_t* previous;
}node_t;

typedef struct list_t
{
    long count;
    node_t* head;
    node_t* tail;
    node_t* iterator;
    lock_t lock;
}list_t;

void* list_internal_remove_from_head(list_t* lptr);
void* list_internal_remove_from_tail(list_t* lptr);
void list_internal_add_to_head(list_t* lptr, node_t *ptr);
void list_internal_add_to_tail(list_t* lptr, node_t* ptr);

list_t * list_allocate(list_t* lptr)
{
    lptr = (list_t*)calloc(1, sizeof(list_t));
    lptr->count = 0;
    lptr->head = lptr->tail = NULL;
    lptr->iterator = NULL;
    lock_create(lptr->lock);
    return lptr;
}

void list_clear(list_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }
    else
    {
        lock_acquire(lptr->lock);

        while(lptr->count > 0)
        {
            void* ptr = list_internal_remove_from_tail(lptr);
            free(ptr);
        }

        lock_release(lptr->lock);
    }
}

void list_free(list_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }
    else
    {
        lock_acquire(lptr->lock);

        while(lptr->count > 0)
        {
            void* ptr = list_internal_remove_from_tail(lptr);
            free(ptr);
        }

        lock_release(lptr->lock);
        lock_destroy(lptr->lock);
        free(lptr);
    }
}

void list_lock_iterator(list_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    lock_acquire(lptr->lock);
}

void list_unlock_iterator(list_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    lock_release(lptr->lock);
}

void list_add_to_head(list_t* lptr, void* data, size_t sz)
{
    list_insert(lptr, data, sz, 0);
}

void list_add_to_tail(list_t* lptr, void* data, size_t sz)
{
    list_insert(lptr, data, sz, LONG_MAX);
}

void list_insert(list_t* lptr, void* data, size_t sz, long pos)
{
	if (lptr == NULL)
	{
        return;
	}

    lock_acquire(lptr->lock);

    node_t* ptr = NULL;

    ptr = (node_t*)calloc(1, sizeof(node_t));
    ptr->data = calloc(1, sz);
    memcpy(ptr->data, data, sz);
    ptr->size = sz;

    if(pos <= 0)
    {
        list_internal_add_to_head(lptr, ptr);
        lock_release(lptr->lock);
        return;
    }

    if (pos >= lptr->count)
    {
        list_internal_add_to_tail(lptr, ptr);
        lock_release(lptr->lock);
        return;
    }

    int idx = 1;
    for(node_t* curptr = lptr->head ; curptr->next != NULL; curptr = curptr->next, idx++)
    {
        if(pos == idx)
        {
            node_t* prev = curptr->previous;
            node_t* next = curptr->next;

            prev->next = ptr;
            ptr->previous = prev;

            next->previous = ptr;
            ptr->next = next;

            lptr->count++;
            break;
        }

        idx++;
    }

    lock_release(lptr->lock);
}

void list_remove_from_head(list_t* lptr)
{
    list_remove_at(lptr, 0);
}

void list_remove_from_tail(list_t* lptr)
{
    list_remove_at(lptr, LONG_MAX);
}

void list_remove(list_t* lptr, const void *node)
{
    if(lptr == NULL || node == NULL)
    {
        return;
    }

    lock_acquire(lptr->lock);

    for(node_t* curptr = lptr->head ; curptr->next != NULL; curptr = curptr->next)
    {
        if(node == curptr->data)
        {
            if(curptr->next == NULL)
            {
                void* ptr = list_internal_remove_from_tail(lptr);
                free(ptr);
            }

            if(curptr->previous == NULL)
            {
                void* ptr = list_internal_remove_from_head(lptr);
                free(ptr);
            }

            node_t* prev = curptr->previous;
            node_t* next = curptr->next;

			if (prev != NULL)
			{
                prev->next = next;
			}

            next->previous = prev;

            free(curptr->data);
            free(curptr);

            lptr->count--;
            break;
        }
    }

    lock_release(lptr->lock);
}

void list_remove_at(list_t* lptr, long pos)
{
    if(lptr == NULL || pos < 0)
    {
        return;
    }

    if(pos > lptr->count -1)
    {
        return;
    }

    lock_acquire(lptr->lock);

    if(pos >= lptr->count -1)
    {
        void* ptr = list_internal_remove_from_tail(lptr);
        free(ptr);
    }
    else
    {
        if(pos == 0)
        {
            void* ptr = list_internal_remove_from_head(lptr);
            free(ptr);
        }
        else
        {
            int idx = 1;
            for(node_t* curptr = lptr->head ; curptr->next != NULL; curptr = curptr->next, idx++)
            {
                if(idx == pos)
                {
                    node_t* prev = curptr->previous;
                    node_t* next = curptr->next;

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

    lock_release(lptr->lock);
}

void list_remove_value(list_t* lptr, void* data, size_t sz)
{
    if(lptr == NULL)
    {
        return;
    }

    lock_acquire(lptr->lock);

    node_t* ptr = NULL;

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
                void* ptr = list_internal_remove_from_tail(lptr);
                free(ptr);
                break;
            }

            if(idx == 0)
            {
                void* ptr = list_internal_remove_from_head(lptr);
                free(ptr);
                break;
            }

            node_t* prev = ptr->previous;
            node_t* next = ptr->next;

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

    lock_release(lptr->lock);

    return;
}

long list_item_count(list_t* lptr)
{
    if(lptr != NULL)
    {
        return lptr->count;
    }

    return 0;
}

long list_index_of(list_t *lptr, const void *node)
{
    if(lptr == NULL)
    {
        return -1;
    }

    lock_acquire(lptr->lock);

    node_t* ptr = NULL;

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
            lock_release(lptr->lock);
            return idx;
        }
    }

    lock_release(lptr->lock);
    return -1;
}

long list_index_of_value(list_t* lptr, void* data, size_t sz)
{
    if(lptr == NULL)
    {
        return -1;
    }

    lock_acquire(lptr->lock);

    node_t* ptr = NULL;

    ptr = lptr->head;

    long idx = 0;

    if(memcmp(ptr->data, data, ptr->size) == 0 && ptr->size == sz)
    {
        lock_release(lptr->lock);
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

    lock_release(lptr->lock);
    return -1;
}

void *list_get_at(list_t* lptr, long atpos)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    if(atpos > (lptr->count - 1) || atpos < 0)
    {
        return NULL;
    }

    lock_acquire(lptr->lock);

    node_t* ptr = NULL;

    ptr = lptr->head;

    if(atpos > 0)
    {
        for(int idx = 0; idx < atpos; idx++)
        {
            ptr = ptr->next;
        }
    }

    lock_release(lptr->lock);

    return ptr->data;
}

void* list_get_first(list_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->iterator = lptr->head;
    return lptr->iterator->data;
}

void* list_get_next(list_t* lptr)
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

void* list_get_last(list_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->iterator = lptr->tail;
    return lptr->iterator->data;
}

void* list_get_previous(list_t* lptr)
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

list_t* list_sort(list_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    return NULL;
}

list_t* list_merge(list_t* lptrFirst, list_t* lptrSecond)
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

list_t* list_join(list_t* lptrFirst, list_t* lptrSecond)
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

void* list_internal_remove_from_head(list_t* lptr)
{
    node_t* oldhead = lptr->head;
    void* ptr = oldhead->data;
    lptr->head = lptr->head->next;

    if(lptr->head != NULL)
    {
        lptr->head->previous = NULL;
    }

    free(oldhead->data);
    free(oldhead);

    lptr->count--;
    return ptr;
}

void* list_internal_remove_from_tail(list_t* lptr)
{
    node_t* oldtail = lptr->tail;
    void* ptr = oldtail->data;

    lptr->tail = oldtail->previous;

    if(lptr->tail != NULL)
    {
        lptr->tail->next = NULL;
    }

    free(oldtail);
    lptr->count--;

    return ptr;
}

void list_internal_add_to_head(list_t* lptr, node_t* ptr)
{
    if(lptr->count == 0)
    {
        lptr->iterator = lptr->head = lptr->tail = ptr;
    }
    else
    {
        lptr->head->previous = ptr;
        ptr->next = lptr->head;
        lptr->head = ptr;
    }

    lptr->count++;
}

void list_internal_add_to_tail(list_t* lptr, node_t* ptr)
{
    if(lptr->count == 0)
    {
        lptr->iterator = lptr->head = lptr->tail = ptr;
    }
    else
    {
        lptr->tail->next = ptr;
        ptr->previous = lptr->tail;
        lptr->tail = ptr;
    }

    lptr->count++;
}
