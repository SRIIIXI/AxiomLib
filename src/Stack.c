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

#include "Stack.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <memory.h>
#include <limits.h>

typedef struct node_t
{
    void* data;
    struct node_t* next;
}node_t;

typedef struct stack_t
{
    long count;
    node_t* head;
    node_t* tail;
    lock_t lock;
}stack_t;

void* stack_internal_remove_tail(stack_t* sptr);

stack_t *stack_allocate(stack_t* sptr)
{
    sptr = (stack_t*)calloc(1, sizeof(stack_t));
    sptr->count = 0;
    sptr->head = sptr->tail = NULL;
    lock_create(sptr->lock);
    return sptr;
}

void stack_clear(stack_t* sptr)
{
    if(sptr == NULL)
    {
        return;
    }
    else
    {
        lock_acquire(sptr->lock);

        while(sptr->count > 0)
        {
            void* ptr = stack_internal_remove_tail(sptr);
            free(ptr);
        }

        lock_release(sptr->lock);
    }
}

void stack_free(stack_t* sptr)
{
    if(sptr == NULL)
    {
        return;
    }
    else
    {
        lock_acquire(sptr->lock);

        while(sptr->count > 0)
        {
            void* ptr = stack_internal_remove_tail(sptr);
            free(ptr);
        }

        lock_release(sptr->lock);
        pthread_mutex_destroy(&sptr->lock);

        free(sptr);
    }
}

void stack_push(stack_t* sptr, void* data, size_t sz)
{
    if(sptr == NULL)
    {
        return;
    }

    lock_acquire(sptr->lock);

    node_t* ptr = (node_t*)calloc(1, sizeof(node_t));
    ptr->data = calloc(1, sz);
    memcpy(ptr->data, data, sz);

    if(sptr->count == 0)
    {
        sptr->head = sptr->tail = ptr;
    }
    else
    {
        sptr->tail->next = ptr;
        sptr->tail = ptr;
    }

    sptr->count++;

    lock_release(sptr->lock);
}

void* stack_pop(stack_t* sptr)
{
    if(sptr == NULL)
    {
        return NULL;
    }

    lock_acquire(sptr->lock);

    void* ptr = stack_internal_remove_tail(sptr);

    lock_release(sptr->lock);

    return ptr;
}

long stack_item_count(stack_t *sptr)
{
    if(sptr != NULL)
    {
        return sptr->count;
    }

    return 0;
}

void* stack_internal_remove_tail(stack_t* sptr)
{
    node_t* oldtail = sptr->tail;
    void* ptr = oldtail->data;
    sptr->tail->next = NULL;
    free(oldtail);
    sptr->count--;

    return ptr;
}
