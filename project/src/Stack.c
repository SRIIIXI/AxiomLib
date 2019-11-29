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

Stack *stack_allocate(Stack* sptr)
{
    sptr = (Stack*)calloc(1, sizeof(Stack));
    return sptr;
}

void stack_clear(Stack* sptr)
{
    if(sptr == NULL)
    {
        return;
    }
}

Node* stack_push(Stack* sptr, void* data, size_t sz)
{
    if(sptr == NULL)
    {
        sptr = stack_allocate(sptr);
    }

    Node* ptr = node_allocate(data, sz);

    if(sptr->Count == 0)
    {
        sptr->Data = sptr->Head = sptr->Tail = ptr;
    }
    else
    {
        sptr->Tail->Next = ptr;
        ptr->Previous = sptr->Tail;
        sptr->Tail = ptr;
    }

    sptr->Count++;

    return ptr;
}

Node *stack_pop(Stack* sptr)
{
    if(sptr == NULL)
    {
        return NULL;
    }

    Node* oldtail = sptr->Tail;
    sptr->Tail = oldtail->Previous;
    sptr->Tail->Next = NULL;
    sptr->Count--;

    //nodeFree(oldtail);
    return oldtail;
}

size_t stack_item_count(Stack *sptr)
{
    if(sptr != NULL)
    {
        return sptr->Count;
    }

    return -1;
}
