/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#ifndef DICTIONARY
#define DICTIONARY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIBRARY_EXPORT __attribute__((visibility("default")))

typedef struct dictionary_t dictionary_t;

//extern LIBRARY_EXPORT unsigned dictionary_hash(const char * key);
//extern LIBRARY_EXPORT void* dictionary_new(size_t size);
//extern LIBRARY_EXPORT void dictionary_del(void * vd);
//extern LIBRARY_EXPORT const char * dictionary_get(const void * d, const char * key, const char * def);
//extern LIBRARY_EXPORT int dictionary_set(void * vd, const char * key, const char * val);
//extern LIBRARY_EXPORT void dictionary_unset(void * d, const char * key);
//extern LIBRARY_EXPORT void dictionary_dump(const void * d, FILE * out);

extern LIBRARY_EXPORT dictionary_t* dictionary_allocate();
extern LIBRARY_EXPORT void dictionary_free(dictionary_t* dict_ptr);
extern LIBRARY_EXPORT void dictionary_set_value(dictionary_t* dict_ptr, const char* key, const void* value);
extern LIBRARY_EXPORT void* dictionary_get_value(dictionary_t* dict_ptr, const char* key);

#ifdef __cplusplus
}
#endif

#endif
