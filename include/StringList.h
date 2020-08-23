/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#ifndef STRING_LIST_C
#define STRING_LIST_C

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIBRARY_EXPORT __attribute__((visibility("default")))

extern LIBRARY_EXPORT void* str_list_allocate(void* lptr);
extern LIBRARY_EXPORT void* str_list_allocate_from_string(void* lptr, const char* str, const char* delimiter);
extern LIBRARY_EXPORT void str_list_clear(void* lptr);

extern LIBRARY_EXPORT void str_list_add_to_head(void* lptr, char* data);
extern LIBRARY_EXPORT void str_list_add_to_tail(void* lptr, char* data);
extern LIBRARY_EXPORT void str_list_insert(void* lptr, char* data, size_t pos);

extern LIBRARY_EXPORT void str_list_remove_from_head(void* lptr);
extern LIBRARY_EXPORT void str_list_remove_from_tail(void* lptr);
extern LIBRARY_EXPORT void str_list_remove(void* lptr, const char* node);
extern LIBRARY_EXPORT void str_list_remove_at(void* lptr, size_t pos);
extern LIBRARY_EXPORT void str_list_remove_value(void* lptr, char* data);

extern LIBRARY_EXPORT size_t str_list_item_count(void* lptr);
extern LIBRARY_EXPORT long long str_list_index_of(void* lptr, const char* data);
extern LIBRARY_EXPORT long long str_list_index_of_like(void* lptr, const char* data);
extern LIBRARY_EXPORT char* str_list_get_at(void* lptr, size_t atpos);

extern LIBRARY_EXPORT char* str_list_get_first(void* lptr);
extern LIBRARY_EXPORT char* str_list_get_next(void* lptr);
extern LIBRARY_EXPORT char* str_list_get_last(void* lptr);
extern LIBRARY_EXPORT char* str_list_get_previous(void* lptr);

extern LIBRARY_EXPORT void str_list_sort(void* lptr);
extern LIBRARY_EXPORT void str_list_merge(void* lptrFirst, void* lptrSecond);
extern LIBRARY_EXPORT void str_list_join(void* lptrFirst, void* lptrSecond);

#ifdef __cplusplus
}
#endif

#endif
