/*
BSD 2-Clause License

Copyright (c) 2017, SRIIIXI (subratoroy@hotmail.com)
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

Queue *queue_allocate(Queue* qptr)
{
    qptr = (Queue*)calloc(1, sizeof(Queue));
    return qptr;
}

void queue_clear(Queue *qptr)
{
    if(qptr == NULL)
    {
        return;
    }
}

Node* queue_enqueue(Queue *qptr, void* data, size_t sz)
{
    if(qptr == NULL)
    {
        qptr = queue_allocate(qptr);
    }

    Node* ptr = node_allocate(data, sz);

    if(qptr->Count == 0)
    {
        qptr->Data = qptr->Head = qptr->Tail = ptr;
    }
    else
    {
        qptr->Head->Previous = ptr;
        ptr->Next = qptr->Head;
        qptr->Head = ptr;
    }

    qptr->Count++;

    return ptr;
}

Node* queue_denqueue(Queue *qptr)
{
    if(qptr == NULL)
    {
        return NULL;
    }

    Node* oldtail = qptr->Tail;
    qptr->Tail = oldtail->Previous;
    qptr->Tail->Next = NULL;
    qptr->Count--;

    //nodeFree(oldtail);
    return oldtail;
}

size_t queue_item_count(Queue *qptr)
{
    if(qptr != NULL)
    {
        return qptr->Count;
    }

    return -1;
}
