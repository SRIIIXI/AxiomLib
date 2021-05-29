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

#include "Queue.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node_t
{
    void* data;
    struct node_t* next;
}node_t;

typedef struct queue_t
{
    long count;
    node_t* head;
    node_t* tail;
    lock_t lock;
}queue_t;

void* queue_internal_remove_tail(queue_t* qptr);

queue_t *queue_allocate(queue_t* qptr)
{
    qptr = (queue_t*)calloc(1, sizeof(queue_t));
    qptr->count = 0;
    qptr->head = qptr->tail = NULL;
    lock_create(qptr->lock);
    return qptr;
}

void queue_clear(queue_t *qptr)
{
    if(qptr == NULL)
    {
        return;
    }
    else
    {
        lock_acquire(qptr->lock);

        while(qptr->count > 0)
        {
            void* ptr = queue_internal_remove_tail(qptr);
            free(ptr);
        }

        lock_release(qptr->lock);
    }
}

void queue_free(queue_t* qptr)
{
    if(qptr == NULL)
    {
        return;
    }
    else
    {
        lock_acquire(qptr->lock);

        while(qptr->count > 0)
        {
            void* ptr = queue_internal_remove_tail(qptr);
            free(ptr);
        }

        lock_release(qptr->lock);
        lock_destroy(qptr->lock);

        free(qptr);
    }
}

void queue_enqueue(queue_t *qptr, void* data, size_t sz)
{
    if(qptr == NULL)
    {
        return;
    }

    lock_acquire(qptr->lock);

    node_t* ptr = (node_t*)calloc(1, sizeof(node_t));
    ptr->data = calloc(1, sz);
    memcpy(ptr->data, data, sz);

    if(qptr->count == 0)
    {
        qptr->head = qptr->tail = ptr;
    }
    else
    {
        ptr->next = qptr->head;
        qptr->head = ptr;
    }

    qptr->count++;

    lock_release(qptr->lock);
}

void* queue_denqueue(queue_t *qptr)
{
    if(qptr == NULL)
    {
        return NULL;
    }
    else
    {
        if(qptr->head == NULL)
        {
            return NULL;
        }
    }

    lock_acquire(qptr->lock);

    void* ptr = queue_internal_remove_tail(qptr);

    lock_release(qptr->lock);

    return ptr;
}

long queue_item_count(queue_t *qptr)
{
    if(qptr != NULL)
    {
        return qptr->count;
    }

    return -1;
}

void* queue_internal_remove_tail(queue_t* qptr)
{
    void* ptr = NULL;

    node_t* second_last = qptr->head;
    while (second_last->next->next != NULL)
    {
        second_last = second_last->next;
    }

    ptr = second_last->next->data;
    free(second_last->next);

    qptr->count--;

    return ptr;
}
