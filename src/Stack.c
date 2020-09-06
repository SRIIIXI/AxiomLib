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
#include <pthread.h>
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
    pthread_mutex_t mutex;
}stack_t;

stack_t *stack_allocate(stack_t* sptr)
{
    sptr = (stack_t*)calloc(1, sizeof(stack_t));
    sptr->count = 0;
    sptr->head = sptr->tail = NULL;
    pthread_mutex_init(&sptr->mutex, NULL);
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
        pthread_mutex_lock(&sptr->mutex);

        while(sptr->count > 0)
        {
            node_t* oldtail = sptr->tail;
            sptr->tail->next = NULL;
            sptr->count--;
            free(oldtail);
        }

        pthread_mutex_unlock(&sptr->mutex);
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
        pthread_mutex_lock(&sptr->mutex);

        while(sptr->count > 0)
        {
            node_t* oldtail = sptr->tail;
            sptr->tail->next = NULL;
            sptr->count--;
            free(oldtail);
        }

        pthread_mutex_unlock(&sptr->mutex);
        pthread_mutex_destroy(&sptr->mutex);

        free(sptr);
    }
}

void stack_push(stack_t* sptr, void* data, size_t sz)
{
    if(sptr == NULL)
    {
        sptr = stack_allocate(sptr);
    }

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
}

void* stack_pop(stack_t* sptr)
{
    if(sptr == NULL)
    {
        return NULL;
    }

    node_t* oldtail = sptr->tail;
    void* ptr = oldtail->data;
    sptr->tail->next = NULL;
    free(oldtail);
    sptr->count--;

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
