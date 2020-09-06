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
    void* data;
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

    size_t substr_count = strcountsubstr((char*)str, delimiter);
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
        lptr = str_list_allocate(lptr);
    }

    StringNode* ptr = str_node_allocate(data);

    if(((StringList*)lptr)->Count == 0)
    {
        ((StringList*)lptr)->IteratorPosition = ((StringList*)lptr)->Head = ((StringList*)lptr)->Tail = ptr;
    }
    else
    {
        ((StringList*)lptr)->Head->Previous = ptr;
        ptr->Next = ((StringList*)lptr)->Head;
        ((StringList*)lptr)->Head = ptr;
    }

    ((StringList*)lptr)->Count++;
}

void str_list_add_to_tail(string_list_t* lptr, char* data)
{
    if(lptr == NULL)
    {
        lptr = str_list_allocate(lptr);
    }

    StringNode* ptr = str_node_allocate(data);
    ptr->Next = NULL;
    ptr->Previous = NULL;

    if(((StringList*)lptr)->Count == 0)
    {
        ((StringList*)lptr)->IteratorPosition = ((StringList*)lptr)->Head = ((StringList*)lptr)->Tail = ptr;
    }
    else
    {
        ((StringList*)lptr)->Tail->Next = ptr;
        ptr->Previous = ((StringList*)lptr)->Tail;
        ((StringList*)lptr)->Tail = ptr;
    }

    ((StringList*)lptr)->Count++;
}

void str_list_insert(string_list_t* lptr, char* data, size_t pos)
{
    if (lptr == NULL)
    {
        return;
    }
    else
    {
        if (pos > ((StringList*)lptr)->Count || pos < 0)
        {
            return;
        }
    }

    if(pos == 0)
    {
        str_list_add_to_head(lptr, data);
        return ;
    }

    StringNode* ptr = NULL;

    if (lptr != NULL)
    {
        if (pos == ((StringList*)lptr)->Count)
        {
            str_list_add_to_tail(lptr, data);
            return ;
        }

        size_t idx = 1;

        for(StringNode* curptr = ((StringList*)lptr)->Head ; curptr->Next != NULL; curptr = curptr->Next)
        {
            if(pos == idx)
            {
                ptr = str_node_allocate(data);

                StringNode* prev = curptr->Previous;
                StringNode* next = curptr->Next;

                prev->Next = ptr;
                ptr->Previous = prev;

                next->Previous = ptr;
                ptr->Next = next;

                ((StringList*)lptr)->Count++;
                break;
            }

            idx++;
        }
    }
}

void str_list_remove_from_head(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    StringNode* oldhead = ((StringList*)lptr)->Head;
    ((StringList*)lptr)->Head = ((StringList*)lptr)->Head->Next;

    if(((StringList*)lptr)->Head != NULL)
    {
        ((StringList*)lptr)->Head->Previous = NULL;
    }

    str_node_free(oldhead);
    ((StringList*)lptr)->Count--;
}

void str_list_remove_from_tail(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return;
    }

    StringNode* oldtail = ((StringList*)lptr)->Tail;
    ((StringList*)lptr)->Tail = oldtail->Previous;

    if(((StringList*)lptr)->Tail != NULL)
    {
        ((StringList*)lptr)->Tail->Next = NULL;
    }

    str_node_free(oldtail);
    ((StringList*)lptr)->Count--;
}

void str_list_remove(string_list_t* lptr, const char* node)
{
    if(lptr == NULL || node == NULL)
    {
        return;
    }

    for(StringNode* curptr = ((StringList*)lptr)->Head ; curptr->Next != NULL; curptr = curptr->Next)
    {
        if(strcmp(node, curptr->NodeData) == 0 )
        {
            if(curptr->Next == NULL)
            {
                str_list_remove_from_tail(lptr);
            }

            if(curptr->Previous == NULL)
            {
                str_list_remove_from_head(lptr);
            }

            StringNode* prev = curptr->Previous;
            StringNode* next = curptr->Next;

            if (prev != NULL)
            {
                prev->Next = next;
            }

            next->Previous = prev;

            str_node_free(curptr);

            ((StringList*)lptr)->Count--;

            break;
        }
    }
}

void str_list_remove_at(string_list_t* lptr, size_t pos)
{
    if(lptr == NULL || pos < 0)
    {
        return;
    }

    if(pos > ((StringList*)lptr)->Count -1)
    {
        return;
    }

    if(pos == 0)
    {
        str_list_remove_from_head(lptr);
        return;
    }    
    
    if(pos == ((StringList*)lptr)->Count -1)
    {
        str_list_remove_from_tail(lptr);
        return;
    }

    size_t idx = 1;
    for(StringNode* curptr = ((StringList*)lptr)->Head ; curptr->Next != NULL; curptr = curptr->Next, idx++)
    {
        if(idx == pos)
        {
            StringNode* prev = curptr->Previous;
            StringNode* next = curptr->Next;

            prev->Next = next;
            next->Previous = prev;

            str_node_free(curptr);

            ((StringList*)lptr)->Count--;
            break;
        }
    }
}

long long str_list_index_of(string_list_t* lptr, const char* node)
{
    if(lptr == NULL)
    {
        return -1;
    }

    char* ptr = NULL;

    long long idx = 0;

    if (((StringList*)lptr)->Head == NULL)
    {
        return -1;
    }

    StringNode* curptr = ((StringList*)lptr)->Head;

    while (curptr)
    {
        if (strcmp(curptr->NodeData, node) == 0)
        {
            return idx;
        }

        curptr = curptr->Next;
        idx++;
    }

    return -1;
}

long long str_list_index_of_like(string_list_t* lptr, const char* node)
{
    if (lptr == NULL)
    {
        return -1;
    }

    char* ptr = NULL;

    long long idx = 0;

    if (((StringList*)lptr)->Head == NULL)
    {
        return -1;
    }

    StringNode* curptr = ((StringList*)lptr)->Head;

    while (curptr)
    {
        if (strstr(curptr->NodeData, node))
        {
            return idx;
        }

        curptr = curptr->Next;
        idx++;
    }

    return -1;
}

void str_list_remove_value(string_list_t* lptr, char* data)
{  
    size_t index = str_list_index_of(lptr, data);
    str_list_remove_at(lptr, index);
}

long long str_list_item_count(string_list_t* lptr)
{
    if(lptr != NULL)
    {
        return ((StringList*)lptr)->Count;
    }

    return -1;
}

char* str_list_get_at(string_list_t* lptr, size_t atpos)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    if(atpos > (((StringList*)lptr)->Count - 1) || atpos < 0)
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

    ((StringList*)lptr)->IteratorPosition = ((StringList*)lptr)->Head;

    if (((StringList*)lptr)->IteratorPosition == NULL)
    {
        return NULL;
    }

    return ((StringList*)lptr)->IteratorPosition->NodeData;
}

char* str_list_get_next(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    if(((StringList*)lptr)->IteratorPosition->Next == NULL)
    {
        return NULL;
    }

    ((StringList*)lptr)->IteratorPosition = ((StringList*)lptr)->IteratorPosition->Next;

    if (((StringList*)lptr)->IteratorPosition == NULL)
    {
        return NULL;
    }

    return ((StringList*)lptr)->IteratorPosition->NodeData;
}

char* str_list_get_last(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    ((StringList*)lptr)->IteratorPosition = ((StringList*)lptr)->Tail;

    if (((StringList*)lptr)->IteratorPosition == NULL)
    {
        return NULL;
    }

    return ((StringList*)lptr)->IteratorPosition->NodeData;
}

char* str_list_get_previous(string_list_t* lptr)
{
    if(lptr == NULL)
    {
        return NULL;
    }

    if(((StringList*)lptr)->IteratorPosition->Previous == NULL)
    {
        return NULL;
    }

    ((StringList*)lptr)->IteratorPosition = ((StringList*)lptr)->IteratorPosition->Previous;

    if (((StringList*)lptr)->IteratorPosition == NULL)
    {
        return NULL;
    }

    return ((StringList*)lptr)->IteratorPosition->NodeData;
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

/*----------------------------------------------------------------*/

StringNode* str_node_allocate(char* data)
{
    size_t sz = strlen(data);

    StringNode* nd = (StringNode*)calloc(1, sizeof(StringNode));

    if (nd != NULL)
    {
        nd->NodeData = (char*)calloc(1, sz+1);

        if(nd->NodeData != NULL)
        {
            nd->Length = sz;
            memcpy(nd->NodeData, data, sz);
            nd->Next = NULL;
            nd->Previous = NULL;
        }
    }

    return nd;
}

void str_node_free(StringNode* ptr)
{
    free(ptr->NodeData);
    free(ptr);
}

void str_node_copy(StringNode* dest, StringNode* orig)
{
    if(dest != NULL && orig != NULL)
    {
        if(dest->NodeData != NULL && orig->NodeData != NULL)
        {
            if(dest->NodeData != NULL && orig->NodeData != NULL)
            {
                free(dest->NodeData);
                size_t sz = strlen(orig->NodeData);
                dest->NodeData = (char*)calloc(1, sz+1);
                dest->Length = sz;
                memcpy(dest->NodeData, orig->NodeData, sz);
            }
        }
    }
}

bool str_node_is_equal(StringNode* first, StringNode* second)
{
    if(first != NULL && second != NULL)
    {
        if(first->NodeData != NULL && second->NodeData != NULL)
        {
            if(first->Length != second->Length)
            {
                return false;
            }

            if(strcmp(first->NodeData, second->NodeData) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool str_node_is_greater(StringNode* first, StringNode* second)
{
    if(first != NULL && second != NULL)
    {
        if(first->NodeData != NULL && second->NodeData != NULL)
        {
            if(first->Length < second->Length)
            {
                return false;
            }

            if(strcmp(first->NodeData, second->NodeData) > 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool str_node_is_less(StringNode* first, StringNode* second)
{
    if(first != NULL && second != NULL)
    {
        if(first->NodeData != NULL && second->NodeData != NULL)
        {
            if(first->Length > second->Length)
            {
                return false;
            }

            if(strcmp(first->NodeData, second->NodeData) < 0)
            {
                return true;
            }
        }
    }

    return false;
}

