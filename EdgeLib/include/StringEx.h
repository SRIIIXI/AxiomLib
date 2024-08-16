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

#ifndef STRING_EX_C
#define STRING_EX_C

#include "Defines.h"
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct string_t string_t;
typedef struct string_list_t string_list_t;

extern LIBRARY_EXPORT string_t* string_allocate(const char* data);
extern LIBRARY_EXPORT string_t* string_allocate_default(void);
extern LIBRARY_EXPORT string_t* string_allocate_length(size_t len);
extern LIBRARY_EXPORT void string_free(string_t* str);
extern LIBRARY_EXPORT void string_clear(string_t* str);

extern LIBRARY_EXPORT bool string_is_equal(string_t* first, string_t* second);
extern LIBRARY_EXPORT bool string_is_greater(string_t* first, string_t* second);
extern LIBRARY_EXPORT bool string_is_less(string_t* first, string_t* second);
extern LIBRARY_EXPORT bool string_is_null(string_t* ptr);

extern LIBRARY_EXPORT size_t string_get_length(string_t* str);
extern LIBRARY_EXPORT const char* string_c_str(string_t* str);

extern LIBRARY_EXPORT wchar_t* string_to_wstr(const char* str);
extern LIBRARY_EXPORT string_t* string_from_wstr(const wchar_t* wstr);

extern LIBRARY_EXPORT char* string_from_int(long num);
extern LIBRARY_EXPORT char* string_from_double(double num);

extern LIBRARY_EXPORT string_t* string_copy(string_t* dest, string_t* orig);
extern LIBRARY_EXPORT string_t* string_append(string_t* dest, const char* data);
extern LIBRARY_EXPORT string_t* string_append_string(string_t* dest, const string_t* str);
extern LIBRARY_EXPORT string_t* string_append_integer(string_t* dest, const long data);
extern LIBRARY_EXPORT string_t* string_append_real(string_t* dest, const double data);
extern LIBRARY_EXPORT string_t* string_append_real_scientific(string_t* dest, const double data);

extern LIBRARY_EXPORT string_t* string_append_char(string_t* dest, const char data);
extern LIBRARY_EXPORT string_t* string_append_boolean(string_t* dest, const bool data);
extern LIBRARY_EXPORT string_t* string_append_curr_timestamp(string_t* dest);

extern LIBRARY_EXPORT string_t* string_reverse(string_t* str);
extern LIBRARY_EXPORT string_t* string_segment_reverse(string_t* str, long start, long term);

extern LIBRARY_EXPORT long string_index_of_substr(const string_t* str, const string_t* substr);
extern LIBRARY_EXPORT long string_index_of_char(const string_t* str, const char ch);

extern LIBRARY_EXPORT long string_count_substr(const string_t* str, const string_t* substr);
extern LIBRARY_EXPORT long string_count_char(const string_t* str, const char ch);

extern LIBRARY_EXPORT string_t* string_to_lower(string_t* str);
extern LIBRARY_EXPORT string_t* string_to_upper(string_t* str);

extern LIBRARY_EXPORT string_t* string_left_trim(string_t* str);
extern LIBRARY_EXPORT string_t* string_right_trim(string_t* str);
extern LIBRARY_EXPORT string_t* string_all_trim(string_t* str);

extern LIBRARY_EXPORT string_t* string_remove_substr_first(string_t* str, const string_t* substr);
extern LIBRARY_EXPORT string_t* string_remove_substr_all(string_t* str, const string_t* substr);
extern LIBRARY_EXPORT string_t *string_remove_substr_at(string_t* str, long pos, long len);
extern LIBRARY_EXPORT void string_remove_end(string_t* ptr, size_t len);
extern LIBRARY_EXPORT void string_remove_start(string_t* ptr, size_t len);

extern LIBRARY_EXPORT string_t* string_remove_char_first(string_t* str, const char oldchar);
extern LIBRARY_EXPORT string_t* string_remove_char_all(string_t* str, const char oldchar);
extern LIBRARY_EXPORT string_t* string_remove_char_at(string_t* str, long pos);

extern LIBRARY_EXPORT string_t* string_replace_substr_first(string_t* str, const string_t* oldsubstr, const string_t* newsubstr);
extern LIBRARY_EXPORT string_t* string_replace_substr_all(string_t* str, const string_t* oldsubstr, const string_t* newsubstr);

extern LIBRARY_EXPORT string_t* string_replace_char_first(string_t* str, const char oldchar, const char newchar);
extern LIBRARY_EXPORT string_t* string_replace_char_all(string_t* str, const char oldchar, const char newchar);
extern LIBRARY_EXPORT string_t* string_replace_char_at(string_t* str, const char newchar, long pos);

extern LIBRARY_EXPORT void string_split_key_value_by_char(const char* str, const char delimiter, char **key, char **value);
extern LIBRARY_EXPORT void string_split_key_value_by_substr(const char* str, const char* delimiter, char **key, char **value);
extern LIBRARY_EXPORT char** string_split_by_substr(const char* str, const char* delimiter);
extern LIBRARY_EXPORT char** string_split_by_char(const char* str, const char delimiter);
extern LIBRARY_EXPORT char* string_join_list_with_substr(const char **strlist, const char* delimiter);
extern LIBRARY_EXPORT char* string_join_list_with_char(const char** strlist, const char delimiter);
extern LIBRARY_EXPORT char* string_merge_list_with_substr(const char **strlist, const char* delimiter);
extern LIBRARY_EXPORT char* string_merge_list_with_char(const char** strlist, const char delimiter);
extern LIBRARY_EXPORT void  string_sort_list(char** strlist);
extern LIBRARY_EXPORT void  string_free_list(char** strlist);
extern LIBRARY_EXPORT void  string_add_to_list(char** strlist, const char* str);
extern LIBRARY_EXPORT char*  string_get_first_from_list(const char** strlist);
extern LIBRARY_EXPORT char*  string_get_next_from_list(const char** strlist);

#ifdef __cplusplus
}
#endif

#endif
