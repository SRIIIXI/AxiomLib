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

extern LIBRARY_EXPORT dictionary_t* dictionary_allocate();
extern LIBRARY_EXPORT void dictionary_free(dictionary_t* dict_ptr);
extern LIBRARY_EXPORT void dictionary_set_value(dictionary_t* dict_ptr, const char* key, const size_t key_size, const void* value, const size_t value_size);
extern LIBRARY_EXPORT void* dictionary_get_value(dictionary_t* dict_ptr, const char* key, const size_t key_size);

#ifdef __cplusplus
}
#endif

#endif
