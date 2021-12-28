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

#ifndef STRING_LIST_C
#define STRING_LIST_C

#include "Defines.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct string_list_t string_list_t;

extern LIBRARY_EXPORT string_list_t* str_list_allocate(string_list_t* lptr);
extern LIBRARY_EXPORT string_list_t* str_list_allocate_from_string(string_list_t* lptr, const char* str, const char* delimiter);
extern LIBRARY_EXPORT void str_list_clear(string_list_t* lptr);
extern LIBRARY_EXPORT void str_list_free(string_list_t* lptr);

extern LIBRARY_EXPORT void str_list_lock_iterator(string_list_t* lptr);
extern LIBRARY_EXPORT void str_list_unlock_iterator(string_list_t* lptr);

extern LIBRARY_EXPORT void str_list_add(string_list_t* lptr, char* data);
extern LIBRARY_EXPORT void str_list_insert(string_list_t* lptr, char* data, long pos);

extern LIBRARY_EXPORT void str_list_remove(string_list_t* lptr, const char* data);
extern LIBRARY_EXPORT void str_list_remove_at(string_list_t* lptr, long pos);

extern LIBRARY_EXPORT long str_list_item_count(string_list_t* lptr);
extern LIBRARY_EXPORT long str_list_index_of(string_list_t* lptr, const char* data);
extern LIBRARY_EXPORT long str_list_index_of_like(string_list_t* lptr, const char* data);
extern LIBRARY_EXPORT char* str_list_get_at(string_list_t* lptr, long atpos);

extern LIBRARY_EXPORT char* str_list_get_first(string_list_t* lptr);
extern LIBRARY_EXPORT char* str_list_get_next(string_list_t* lptr);
extern LIBRARY_EXPORT char* str_list_get_last(string_list_t* lptr);
extern LIBRARY_EXPORT char* str_list_get_previous(string_list_t* lptr);

extern LIBRARY_EXPORT void str_list_sort(string_list_t* lptr);
extern LIBRARY_EXPORT void str_list_merge(string_list_t* lptrFirst, string_list_t* lptrSecond);
extern LIBRARY_EXPORT void str_list_join(string_list_t* lptrFirst, string_list_t* lptrSecond);

#ifdef __cplusplus
}
#endif

#endif
