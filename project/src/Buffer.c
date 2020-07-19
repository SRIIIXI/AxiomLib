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

Buffer* buffer_allocate(void* data, size_t sz)
{
    Buffer* nd = (Buffer*)calloc(1, sizeof(Buffer));

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

Buffer* buffer_copy(Buffer* dest, Buffer* orig)
{
    if(orig != NULL)
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

Buffer *buffer_append(Buffer* dest, void* data, size_t sz)
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

void buffer_free(Buffer* ptr)
{
    free(ptr->Data);
    free(ptr);
}

bool buffer_is_equal(Buffer* first, Buffer* second)
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

bool buffer_is_greater(Buffer* first, Buffer* second)
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

bool buffer_is_less(Buffer* first, Buffer* second)
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

