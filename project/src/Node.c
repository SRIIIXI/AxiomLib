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

#include "Node.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>

Node* node_allocate(void* data, size_t sz)
{
    Node* nd = (Node*)calloc(1, sizeof(Node));

	if (nd != NULL)
	{
        nd->NodeData = buffer_allocate(data, sz);
 
        if(nd->NodeData != NULL)
        {
            nd->Next = NULL;
            nd->Previous = NULL;
        }
	}

    return nd;
}

void node_free(Node* ptr)
{
    free(ptr->NodeData->Data);
    free(ptr->NodeData);
    free(ptr);
}

void node_copy(Node* dest, Node* orig)
{
    if(dest != NULL && orig != NULL)
    {
        if(dest->NodeData != NULL && orig->NodeData != NULL)
        {
            if(dest->NodeData->Data != NULL && orig->NodeData->Data != NULL)
            {
                free(dest->NodeData->Data);
                dest = node_allocate(orig->NodeData->Data, orig->NodeData->Size);
            }
        }
    }
}

bool node_is_equal(Node* first, Node* second)
{
    if(first != NULL && second != NULL)
    {
        if(first->NodeData != NULL && second->NodeData != NULL)
        {
            if(first->NodeData->Data != NULL && second->NodeData->Data != NULL)
            {
                if(first->NodeData->Size != second->NodeData->Size)
                {
                    return false;
                }

                if(memcmp(first->NodeData->Data, second->NodeData->Data, first->NodeData->Size) == 0)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool node_is_greater(Node* first, Node* second)
{
    if(first != NULL && second != NULL)
    {
        if(first->NodeData != NULL && second->NodeData != NULL)
        {
            if(first->NodeData->Data != NULL && second->NodeData->Data != NULL)
            {
                if(first->NodeData->Size != second->NodeData->Size)
                {
                    return false;
                }

                if(memcmp(first->NodeData->Data, second->NodeData->Data, first->NodeData->Size) > 0)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool node_is_less(Node* first, Node* second)
{
    if(first != NULL && second != NULL)
    {
        if(first->NodeData != NULL && second->NodeData != NULL)
        {
            if(first->NodeData->Data != NULL && second->NodeData->Data != NULL)
            {
                if(first->NodeData->Size != second->NodeData->Size)
                {
                    return false;
                }

                if(memcmp(first->NodeData->Data, second->NodeData->Data, first->NodeData->Size) < 0)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

