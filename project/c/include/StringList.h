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

#ifndef _STRING_LIST_C
#define _STRING_LIST_C

#include <stddef.h>
#include <stdbool.h>

typedef struct string
{
    char* Buffer;
    size_t BufferSize;
    size_t StringLength;
}string;

typedef struct string_node
{
    string* NodeData;
    struct string_node* Next;
    struct string_node* Previous;
}string_node;

typedef struct string_list
{
    size_t Count;
    string_node* Head;
    string_node* Tail;
    string_node* IteratorPosition;
}string_list;

extern string_list* strlist_allocate(string_list* lptr);
extern void strlist_clear(string_list* lptr);

extern string_list* strlist_allocate_from_splitsubstr(const char* str, const char* delimiter, size_t* numsubstr);
extern string_list* strlist_allocate_from_strsplitchar(const char* str, const char delimiter, size_t* numsubstr);
extern char* strlist_joinwithsubstr(const string_list* strlist, const char* delimiter);
extern char* strlist_joinwithchar(const string_list* strlist, const char delimiter);
extern void  strlist_freelist(string_list* strlist, size_t numsubstr);

extern string_node* strlist_add_to_head(string_list* lptr, char* str, size_t sz);
extern string_node* strlist_add_to_tail(string_list* lptr, char* str, size_t sz);
extern string_node* strlist_insert(string_list* lptr, char* str, size_t sz, int pos);

extern void strlist_remove_from_head(string_list* lptr);
extern void strlist_remove_from_tail(string_list* lptr);
extern void strlist_remove(string_list* lptr, const string_node* node);
extern void strlist_remove_at(string_list* lptr, int pos);
extern void strlist_remove_value(string_list* lptr, char* str, size_t sz);

extern size_t strlist_item_count(string_list* lptr);
extern size_t strlist_index_of(string_list* lptr, const string_node* node);
extern size_t strlist_index_of_value(string_list* lptr, char* str, size_t sz);
extern string_node* strlist_get_at(string_list* lptr, int atpos);

extern string_node* strlist_get_first(string_list* lptr);
extern string_node* strlist_get_next(string_list* lptr);
extern string_node* strlist_get_last(string_list* lptr);
extern string_node* strlist_get_previous(string_list* lptr);

extern string_list* strlist_sort(string_list* lptr);
extern string_list* strlist_merge(string_list* lptrFirst, string_list* lptrSecond);
extern string_list* strlist_join(string_list* lptrFirst, string_list* lptrSecond);


#endif