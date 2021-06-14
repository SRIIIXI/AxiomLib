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
#include <stdio.h>
#include <time.h>

#if defined (_WIN32) || defined (_WIN64)
#include <windows.h>
#else
#include <unistd.h>
#endif

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
        #if defined (_WIN32) || defined (_WIN64)
            SYSTEM_INFO siSysInfo;
            GetSystemInfo(&siSysInfo);
            nd->memory_size = siSysInfo.dwPageSize;
        #else
                nd->memory_size = sysconf(_SC_PAGESIZE);
        #endif
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
        #if defined (_WIN32) || defined (_WIN64)
            SYSTEM_INFO siSysInfo;
            GetSystemInfo(&siSysInfo);
            nd->memory_size = siSysInfo.dwPageSize;
        #else
                nd->memory_size = sysconf(_SC_PAGESIZE);
        #endif
        nd->data_size = 0;
        nd->data = (char*)calloc(nd->memory_size, sizeof (char));
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

buffer_t* buffer_append_string(buffer_t* dest, const char* data)
{
    return buffer_append(dest, data, strlen(data));
}

buffer_t* buffer_append_integer(buffer_t* dest, const long data)
{
    char buffer[17] = {0};
    sprintf(buffer, "%ld", data);
    return buffer_append(dest, buffer, strlen(buffer));
}

buffer_t* buffer_append_real(buffer_t* dest, const double data)
{
    char buffer[17] = {0};
    sprintf(buffer, "%f", data);
    return buffer_append(dest, buffer, strlen(buffer));
}

buffer_t* buffer_append_real_scientific(buffer_t* dest, const double data)
{
    char buffer[17] = {0};
    sprintf(buffer, "%.3e", data);
    return buffer_append(dest, buffer, strlen(buffer));
}

buffer_t* buffer_append_char(buffer_t* dest, const char data)
{
    char buffer[2] = {data, 0};
    return buffer_append(dest, buffer, strlen(buffer));
}

buffer_t* buffer_append_boolean(buffer_t* dest, const bool data)
{
    char buffer[6] = {0};

    if(data)
    {
        strcpy(buffer, "true");
    }
    else
    {
        strcpy(buffer, "false");
    }

    return buffer_append(dest, buffer, strlen(buffer));
}

buffer_t* buffer_append_curr_timestamp(buffer_t* dest)
{
    if(dest == NULL)
    {
        return NULL;
    }

    char buffer[15] = {0};
    time_t t ;
    struct tm *tmp ;
    time(&t);
    tmp = localtime(&t);

    sprintf(buffer, "%04d%02d%02d%02d%02d%02d",
             (tmp->tm_year+1900), (tmp->tm_mon+1), tmp->tm_mday,
             tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

    return buffer_append(dest, buffer, strlen(buffer));
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
        for(size_t i = 0; i < sizeof ptr->data; ++i)
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

const void *buffer_get_data(buffer_t* ptr)
{
    if(ptr == NULL)
    {
        return NULL;
    }

    return ptr->data;
}

size_t buffer_get_size(buffer_t* ptr)
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
