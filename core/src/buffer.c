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

#include "buffer.h"
#include "stringex.h"

#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef struct buffer_t
{
    char* data;
    size_t data_size;
    size_t memory_size;
}buffer_t;

buffer_t* buffer_internal_adjust_storage(buffer_t* buffer_ptr, size_t sz);

buffer_t* buffer_allocate(const void *data, size_t sz)
{
    buffer_t* nd = (buffer_t*)calloc(1, sizeof(buffer_t));

    if(nd != NULL)
    {
        nd->memory_size = sysconf(_SC_PAGESIZE);
        nd->data_size = sz;
        nd->data = (char*)calloc(nd->memory_size, sizeof (char));

        if(nd->data != NULL)
        {
            memcpy(nd->data, data, sz);
        }
    }
    return nd;
}

buffer_t* buffer_allocate_default(void)
{
    buffer_t* nd = (buffer_t*)calloc(1, sizeof(buffer_t));

    if(nd != NULL)
    {
        nd->memory_size = sysconf(_SC_PAGESIZE);
        nd->data_size = 0;
        nd->data = (char*)calloc(nd->memory_size, sizeof (char));
    }
    return nd;
}

buffer_t* buffer_allocate_length(size_t len)
{
    buffer_t* nd = (buffer_t*)calloc(1, sizeof(buffer_t));

    if(nd != NULL)
    {
        nd->memory_size = len;
        nd->data_size = 0;
        nd->data = (char*)calloc(len, sizeof (char));
    }
    return nd;
}

buffer_t* buffer_copy(buffer_t* dest, buffer_t* orig)
{
    if(orig != NULL && dest != NULL)
    {
        if(orig->data != NULL)
        {
            if(dest->data != NULL)
            {
                free(dest->data);
                dest->data = NULL;
                dest->data_size = 0;
            }

            dest->data = (char*)calloc(1, dest->data_size);
            if (dest->data)
            {
                memcpy(dest->data, orig->data, dest->data_size);
                dest->data_size = orig->data_size;
            }
        }
    }

    return  dest;
}

buffer_t *buffer_append(buffer_t* dest, const void *data, size_t sz)
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
        dest = buffer_internal_adjust_storage(dest, sz);
        memcpy(&dest->data[dest->data_size], data, sz);
        dest->data_size = dest->data_size + sz;
    }

    return dest;
}

void buffer_remove(buffer_t* ptr, size_t start, size_t len)
{
    if(ptr == NULL || len < 1 || start < 0)
    {
        return;
    }

    if(start >= 0 && start <= ptr->data_size)
    {
        memcpy(ptr->data+start, ptr->data+start+len, ptr->data_size-len);
        buffer_remove_end(ptr, len);
    }
}

void buffer_remove_end(buffer_t* ptr, size_t len)
{
    if(ptr == NULL || len < 1)
    {
        return;
    }

    size_t pos = 0;

    pos = ptr->data_size - len;

    for(size_t index = ptr->data_size; index > pos; index--)
    {
        ptr->data[index] = 0;
    }

    ptr->data_size = ptr->data_size - len;

    return;
}

void buffer_remove_start(buffer_t* ptr, size_t len)
{
    buffer_remove(ptr, 0, len);
    buffer_remove_end(ptr, len);
}

void buffer_free(buffer_t* ptr)
{
    if(ptr == NULL)
    {
        return;
    }

    if(ptr->data)
    {
        free(ptr->data);
    }

    free(ptr);
}

void buffer_clear(buffer_t* ptr)
{
    if(ptr == NULL)
    {
        return;
    }

    if(ptr->data)
    {
        for(size_t i = 0; i <  ptr->data_size; ++i)
          ptr->data[i] = 0;
    }
    ptr->data_size = 0;
}

bool buffer_is_equal(buffer_t* first, buffer_t* second)
{
    if(first != NULL && second != NULL)
    {
       if (first->data != NULL && second->data != NULL)
        {
            if(first->data_size != second->data_size)
            {
                return false;
            }

            if(memcmp(first->data, second->data, first->data_size) == 0)
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
        if(first->data != NULL && second->data != NULL)
        {
            if(first->data_size != second->data_size)
            {
                return false;
            }

            if(memcmp(first->data, second->data, first->data_size) > 0)
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
        if(first->data != NULL && second->data != NULL)
        {
            if(first->data_size != second->data_size)
            {
                return false;
            }

            if(memcmp(first->data, second->data, first->data_size) < 0)
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
        if(ptr->data == NULL)
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

const void *buffer_get_data(const buffer_t* ptr)
{
    if(ptr == NULL)
    {
        return NULL;
    }

    return ptr->data;
}

size_t buffer_get_size(const buffer_t* ptr)
{
    if(ptr == NULL)
    {
        return 0;
    }

    return ptr->data_size;
}

buffer_t* buffer_internal_adjust_storage(buffer_t* buffer_ptr, size_t sz)
{
    if(buffer_ptr == NULL)
    {
        return NULL;
    }

    size_t buffer_remaining = buffer_ptr->memory_size - buffer_ptr->data_size;

    if(buffer_remaining < sz)
    {
        void* ptr = (char*)calloc(buffer_ptr->memory_size*2, sizeof (char));

        if (ptr)
        {
            buffer_ptr->memory_size = buffer_ptr->memory_size*2;
            memcpy(ptr, buffer_ptr->data, buffer_ptr->data_size);
            free(buffer_ptr->data);
            buffer_ptr->data = ptr;
        }

    }

    return  buffer_ptr;
}

string_t* buffer_convert_to_string(buffer_t* ptr)
{
    if(ptr == NULL)
    {
        return false;
    }

    //The caller must be absolutely sure that the buffer contains a string

    char term[2] = {0};
    buffer_append(ptr, term, 1);
    
    string_t* resp = string_allocate(buffer_get_data(ptr));

    return resp;
}
