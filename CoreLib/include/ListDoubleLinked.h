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

#ifndef LIST_DL_C
#define LIST_DL_C

#include "Defines.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct list_dl_t list_dl_t;

extern LIBRARY_EXPORT list_dl_t* list_dl_allocate(list_dl_t* lptr);
extern LIBRARY_EXPORT void list_dl_clear(list_dl_t* lptr);
extern LIBRARY_EXPORT void list_dl_free(list_dl_t* lptr);

extern LIBRARY_EXPORT void list_dl_lock(list_dl_t* lptr);
extern LIBRARY_EXPORT void list_dl_unlock(list_dl_t* lptr);

extern LIBRARY_EXPORT void list_dl_add_to_head(list_dl_t* lptr, void* data, size_t sz);
extern LIBRARY_EXPORT void list_dl_add_to_tail(list_dl_t* lptr, void* data, size_t sz);
extern LIBRARY_EXPORT void list_dl_insert(list_dl_t* lptr, void* data, size_t sz, long pos);

extern LIBRARY_EXPORT void list_dl_remove_from_head(list_dl_t* lptr);
extern LIBRARY_EXPORT void list_dl_remove_from_tail(list_dl_t* lptr);
extern LIBRARY_EXPORT void list_dl_remove(list_dl_t* lptr, const void* node);
extern LIBRARY_EXPORT void list_dl_remove_at(list_dl_t* lptr, long pos);
extern LIBRARY_EXPORT void list_dl_remove_value(list_dl_t* lptr, void* data, size_t sz);

extern LIBRARY_EXPORT long list_dl_item_count(list_dl_t* lptr);
extern LIBRARY_EXPORT long list_dl_index_of(list_dl_t* lptr, const void* node);
extern LIBRARY_EXPORT long list_dl_index_of_value(list_dl_t* lptr, void* data, size_t sz);
extern LIBRARY_EXPORT void* list_dl_get_at(list_dl_t* lptr, long atpos);

extern LIBRARY_EXPORT void* list_dl_get_first(list_dl_t* lptr);
extern LIBRARY_EXPORT void* list_dl_get_next(list_dl_t* lptr);
extern LIBRARY_EXPORT void* list_dl_get_last(list_dl_t* lptr);
extern LIBRARY_EXPORT void* list_dl_get_previous(list_dl_t* lptr);

extern LIBRARY_EXPORT list_dl_t* list_dl_sort(list_dl_t* lptr);
extern LIBRARY_EXPORT list_dl_t* list_dl_merge(list_dl_t* lptrFirst, list_dl_t* lptrSecond);
extern LIBRARY_EXPORT list_dl_t* list_dl_join(list_dl_t* lptrFirst, list_dl_t* lptrSecond);

#ifdef __cplusplus
}
#endif

#endif
