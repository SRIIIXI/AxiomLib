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
#include "List.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <limits.h>

typedef struct queue_t
{
    list_t* list;
}queue_t;

queue_t* queue_allocate(queue_t* qptr)
{
    qptr = (queue_t*)calloc(1, sizeof(queue_t));

    if (qptr)
    {
        qptr->list = list_allocate(qptr->list);
    }

    return qptr;
}

void queue_clear(queue_t* qptr)
{
    if (qptr == NULL)
    {
        return;
    }

    if (qptr->list == NULL)
    {
        return;
    }

    list_lock(qptr->list);
    list_clear(qptr->list);
    list_unlock(qptr->list);
}

void queue_free(queue_t* qptr)
{
    if (qptr == NULL)
    {
        return;
    }

    if (qptr->list == NULL)
    {
        return;
    }

    list_free(qptr->list);
    free(qptr);
}

void queue_enqueue(queue_t* qptr, void* data, size_t sz)
{
    if (qptr == NULL)
    {
        return;
    }

    if (qptr->list == NULL)
    {
        return;
    }

    list_lock(qptr->list);
    list_add_to_head(qptr->list, data, sz);
    list_unlock(qptr->list);
}

void* queue_denqueue(queue_t* qptr)
{
    if (qptr == NULL)
    {
        return NULL;
    }

    if (qptr->list == NULL)
    {
        return NULL;
    }

    void* ptr = NULL;

    list_lock(qptr->list);
    ptr = list_get_last(qptr->list);
    list_remove_from_tail(qptr->list);
    list_unlock(qptr->list);

    return ptr;
}

long queue_item_count(queue_t* qptr)
{
    if (qptr != NULL)
    {
        if (qptr->list != NULL)
        {
            return list_item_count(qptr->list);
        }
    }

    return -1;
}

