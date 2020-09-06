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

#include "Buffer.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>

typedef struct buffer_t
{
    void* Data;
    size_t Size;
    size_t Memory;
}buffer_t;

buffer_t* buffer_allocate(void* data, size_t sz)
{
    buffer_t* nd = (buffer_t*)calloc(1, sizeof(buffer_t));

    if(nd != NULL)
    {
        nd->Data = (char*)calloc(1, sz);

        if(nd->Data != NULL)
        {
            nd->Size = sz;
            nd->Memory = sz;
            memcpy(nd->Data, data, sz);
        }
    }
    return nd;
}

buffer_t* buffer_copy(buffer_t* dest, buffer_t* orig)
{
    if(orig != NULL && dest != NULL)
    {
        if(orig->Data != NULL)
        {
            if(dest->Data != NULL)
            {
                free(dest->Data);
            }

            dest->Size = orig->Size;
            dest->Data = (char*)calloc(1, dest->Size);
            memcpy(dest->Data, orig->Data, dest->Size);
        }
    }

    return  dest;
}

buffer_t *buffer_append(buffer_t* dest, void* data, size_t sz)
{
    if(data == NULL || sz < 1)
    {
        return NULL;
    }

    if(dest == NULL)
    {
        dest = buffer_allocate(data, sz);
        return dest;
    }
    else
    {


    }

    return dest;
}

void buffer_free(buffer_t* ptr)
{
    free(ptr->Data);
    free(ptr);
}

bool buffer_is_equal(buffer_t* first, buffer_t* second)
{
    if(first != NULL && second != NULL)
    {
       if (first->Data != NULL && second->Data != NULL)
        {
            if(first->Size != second->Size)
            {
                return false;
            }

            if(memcmp(first->Data, second->Data, first->Size) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool buffer_is_greater(buffer_t* first, buffer_t* second)
{
    if(first != NULL && second != NULL)
    {
        if(first->Data != NULL && second->Data != NULL)
        {
            if(first->Size != second->Size)
            {
                return false;
            }

            if(memcmp(first->Data, second->Data, first->Size) > 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool buffer_is_less(buffer_t* first, buffer_t* second)
{
    if(first != NULL && second != NULL)
    {
        if(first->Data != NULL && second->Data != NULL)
        {
            if(first->Size != second->Size)
            {
                return false;
            }

            if(memcmp(first->Data, second->Data, first->Size) < 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool buffer_is_null(buffer_t* ptr)
{
    if(ptr == NULL)
    {
        return true;
    }
    else
    {
        if(ptr->Data == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

const void *data(buffer_t* ptr)
{
    if(ptr == NULL)
    {
        return NULL;
    }

    return ptr->Data;
}

size_t size(buffer_t* ptr)
{
    if(ptr == NULL)
    {
        return 0;
    }

    return ptr->Size;
}
