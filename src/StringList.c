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

#include "StringList.h"
#include "StringEx.h"
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <limits.h>

typedef struct node_t
{
    char* data;
    size_t size;
    struct node_t* next;
    struct node_t* previous;
}node_t;

typedef struct string_list_t
{
    long count;
    node_t* head;
    node_t* tail;
    node_t* iterator;
    pthread_mutex_t mutex;
}string_list_t;

node_t* str_list_internal_create_node(char* data);

string_list_t* str_list_allocate(string_list_t* lptr)
{
    lptr = (string_list_t*)calloc(1, sizeof(string_list_t));
    lptr->count = 0;
    lptr->head = lptr->tail = NULL;
    lptr->iterator = NULL;
    pthread_mutex_init(&lptr->mutex, NULL);
    return lptr;
}

string_list_t* str_list_allocate_from_string(string_list_t* lptr, const char* str, const char* delimiter)
{
    if(str == NULL || delimiter == NULL)
    {
        return NULL;
    }

    size_t substr_count = strcountsubstr(str, delimiter);
    size_t str_len = strlen(str);

    if(substr_count < 1 || str_len < 1)
    {
        return NULL;
    }

    char* ptr = (char*)calloc(1, str_len+1);

    if(ptr == NULL)
    {
        return NULL;
    }

    memcpy(ptr, str, str_len);

    lptr = (string_list_t*)calloc(1, sizeof(string_list_t));

    if(lptr == NULL)
    {
        free(ptr);
        return NULL;
    }

    char* temp_ptr = NULL;

    temp_ptr = strtok(ptr, delimiter);

    while(temp_ptr != NULL)
    {
        str_list_add_to_tail(lptr, temp_ptr);
        temp_ptr = strtok(NULL, delimiter);
    }

    if(ptr)
    {
        free(ptr);
    }

    return lptr;
}


void str_list_clear(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }
    else
    {
        while(lptr->count > 0)
        {
            str_list_remove_from_tail(lptr);
        }

        free(lptr);
    }
}

void str_list_free(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }
    else
    {
        while(lptr->count > 0)
        {
            str_list_remove_from_tail(lptr);
        }

        free(lptr);
    }
}

void str_list_add_to_head(string_list_t* lptr, char* data)
{
    if(lptr == NULL)
    {
        return;
    }

    node_t* ptr = str_list_internal_create_node(data);

    if(lptr->count == 0)
    {
        lptr->iterator = lptr->head = lptr->tail = ptr;
    }
    else
    {
        lptr->head->previous = ptr;
        ptr->next = lptr->head;
        lptr->head = ptr;
    }

    lptr->count++;
}

void str_list_add_to_tail(string_list_t* lptr, char* data)
{
    if(lptr == NULL)
    {
        return;
    }

    node_t* ptr = str_list_internal_create_node(data);

    if(lptr->count == 0)
    {
        lptr->iterator = lptr->head = lptr->tail = ptr;
    }
    else
    {
        lptr->tail->next = ptr;
        ptr->previous = lptr->tail;
        lptr->tail = ptr;
    }

    lptr->count++;
}

void str_list_insert(string_list_t* lptr, char* data, long pos)
{
    if (lptr == NULL)
    {
        return;
    }

    if(pos <= 0)
    {
        str_list_add_to_head(lptr, data);
        return;
    }

    if (pos >= lptr->count - 1)
    {
        str_list_add_to_tail(lptr, data);
        return;
    }

    long idx = 1;

    for(node_t* curptr = lptr->head ; curptr->next != NULL; curptr = curptr->next)
    {
        if(pos == idx)
        {
            node_t* ptr = NULL;
            ptr = str_list_internal_create_node(data);

            node_t* prev = curptr->previous;
            node_t* next = curptr->next;

            prev->next = ptr;
            ptr->previous = prev;

            next->previous = ptr;
            ptr->next = next;

            lptr->count++;
            break;
        }

        idx++;
    }
}

void str_list_remove_from_head(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    node_t* oldhead = lptr->head;
    lptr->head = lptr->head->next;

    if(lptr->head != NULL)
    {
        lptr->head->previous = NULL;
    }

    free(oldhead->data);
    free(oldhead);
    lptr->count--;
}

void str_list_remove_from_tail(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    node_t* oldtail = lptr->tail;
    lptr->tail = oldtail->previous;

    if(lptr->tail != NULL)
    {
        lptr->tail->next = NULL;
    }

    free(oldtail->data);
    free(oldtail);
    lptr->count--;
}

void str_list_remove(string_list_t* lptr, const char* node)
{
    if(lptr == NULL || node == NULL)
    {
        return;
    }

    for(node_t* curptr = lptr->head ; curptr->next != NULL; curptr = curptr->next)
    {
        if(strcmp(node, curptr->data) == 0 )
        {
            if(curptr->next == NULL)
            {
                str_list_remove_from_tail(lptr);
            }

            if(curptr->previous == NULL)
            {
                str_list_remove_from_head(lptr);
            }

            node_t* prev = curptr->previous;
            node_t* next = curptr->next;

            if (prev != NULL)
            {
                prev->next = next;
            }

            next->previous = prev;

            free(curptr->data);
            free(curptr);

            lptr->count--;

            break;
        }
    }
}

void str_list_remove_at(string_list_t* lptr, long pos)
{
    if(lptr == NULL || pos < 0)
    {
        return;
    }

    if(pos > lptr->count -1)
    {
        return;
    }

    if(pos == 0)
    {
        str_list_remove_from_head(lptr);
        return;
    }    
    
    if(pos == lptr->count -1)
    {
        str_list_remove_from_tail(lptr);
        return;
    }

    long idx = 1;
    for(node_t* curptr = lptr->head ; curptr->next != NULL; curptr = curptr->next, idx++)
    {
        if(idx == pos)
        {
            node_t* prev = curptr->previous;
            node_t* next = curptr->next;

            prev->next = next;
            next->previous = prev;

            free(curptr->data);
            free(curptr);

            lptr->count--;
            break;
        }
    }
}

long str_list_index_of(string_list_t* lptr, const char* node)
{
    if(lptr == NULL)
    {
        return -1;
    }

    long long idx = 0;

    if (lptr->head == NULL)
    {
        return -1;
    }

    node_t* curptr = lptr->head;

    while (curptr)
    {
        if (strcmp(curptr->data, node) == 0)
        {
            return idx;
        }

        curptr = curptr->next;
        idx++;
    }

    return -1;
}

long str_list_index_of_like(string_list_t* lptr, const char* node)
{
    if (lptr == NULL)
    {
        return -1;
    }

    long long idx = 0;

    if (lptr->head == NULL)
    {
        return -1;
    }

    node_t* curptr = lptr->head;

    while (curptr)
    {
        if (strstr(curptr->data, node))
        {
            return idx;
        }

        curptr = curptr->next;
        idx++;
    }

    return -1;
}

void str_list_remove_value(string_list_t* lptr, char* data)
{  
    long index = str_list_index_of(lptr, data);
    str_list_remove_at(lptr, index);
}

long str_list_item_count(string_list_t* lptr)
{
    if(lptr != NULL)
    {
        return lptr->count;
    }

    return -1;
}

char* str_list_get_at(string_list_t* lptr, long atpos)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    if(atpos > lptr->count - 1 || atpos < 0)
    {
        return NULL;
    }

    char* ptr = NULL;

    ptr = str_list_get_first(lptr);

    if(atpos > 0)
    {
        for(int idx = 0; idx < atpos; idx++)
        {
            ptr = str_list_get_next(lptr);
        }
    }

    return ptr;
}

char* str_list_get_first(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->iterator = lptr->head;

    if (lptr->iterator == NULL)
    {
        return NULL;
    }

    return lptr->iterator->data;
}

char* str_list_get_next(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    if(lptr->iterator->next == NULL)
    {
        return NULL;
    }

    lptr->iterator = lptr->iterator->next;

    if (lptr->iterator == NULL)
    {
        return NULL;
    }

    return lptr->iterator->data;
}

char* str_list_get_last(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    lptr->iterator = lptr->tail;

    if (lptr->iterator == NULL)
    {
        return NULL;
    }

    return lptr->iterator->data;
}

char* str_list_get_previous(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    if(lptr->iterator->previous == NULL)
    {
        return NULL;
    }

    lptr->iterator = lptr->iterator->previous;

    if(lptr->iterator == NULL)
    {
        return NULL;
    }

    return lptr->iterator->data;
}

void str_list_sort(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    return;
}

void str_list_merge(string_list_t* lptrFirst, string_list_t* lptrSecond)
{
    if(lptrFirst == NULL)
    {
        return;
    }

    if(lptrSecond == NULL)
    {
        return;
    }

    return;
}

void str_list_join(string_list_t* lptrFirst, string_list_t* lptrSecond)
{
    if(lptrFirst == NULL)
    {
        return;
    }

    if(lptrSecond == NULL)
    {
        return;
    }

    return;
}

node_t* str_list_internal_create_node(char *data)
{
    node_t* ptr = (node_t*)calloc(1, sizeof(node_t));
    ptr->size = strlen(data);
    ptr->data = (char*)calloc(1, ptr->size+1);
    strcpy(ptr->data, data);
    ptr->next = ptr->previous = NULL;
    return ptr;
}
