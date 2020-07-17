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

#ifndef LIST_C
#define LIST_C

#include "Node.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct List
{
    size_t Count;
    Node* Head;
    Node* Tail;
    Node* IteratorPosition;
}List;

extern __attribute__((visibility("default"))) List* list_allocate(List* lptr);
extern __attribute__((visibility("default"))) void list_clear(List* lptr);

extern __attribute__((visibility("default"))) Node* list_add_to_head(List* lptr, void* data, size_t sz);
extern __attribute__((visibility("default"))) Node* list_add_to_tail(List* lptr, void* data, size_t sz);
extern __attribute__((visibility("default"))) Node* list_insert(List* lptr, void* data, size_t sz, int pos);

extern __attribute__((visibility("default"))) void list_remove_from_head(List* lptr);
extern __attribute__((visibility("default"))) void list_remove_from_tail(List* lptr);
extern __attribute__((visibility("default"))) void list_remove(List* lptr, const Node* node);
extern __attribute__((visibility("default"))) void list_remove_at(List* lptr, int pos);
extern __attribute__((visibility("default"))) void list_remove_value(List* lptr, void* data, size_t sz);

extern __attribute__((visibility("default"))) size_t list_item_count(List* lptr);
extern __attribute__((visibility("default"))) size_t list_index_of(List* lptr, const Node* node);
extern __attribute__((visibility("default"))) size_t list_index_of_value(List* lptr, void* data, size_t sz);
extern __attribute__((visibility("default"))) Node* list_get_at(List* lptr, int atpos);

extern __attribute__((visibility("default"))) Node* list_get_first(List* lptr);
extern __attribute__((visibility("default"))) Node* list_get_next(List* lptr);
extern __attribute__((visibility("default"))) Node* list_get_last(List* lptr);
extern __attribute__((visibility("default"))) Node* list_get_previous(List* lptr);

extern __attribute__((visibility("default"))) List* list_sort(List* lptr);
extern __attribute__((visibility("default"))) List* list_merge(List* lptrFirst, List* lptrSecond);
extern __attribute__((visibility("default"))) List* list_join(List* lptrFirst, List* lptrSecond);

#endif
