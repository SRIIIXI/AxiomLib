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

extern __attribute__((visibility("default"))) unsigned dictionary_hash(const char * key);
extern __attribute__((visibility("default"))) void* dictionary_new(size_t size);
extern __attribute__((visibility("default"))) void dictionary_del(void * vd);
extern __attribute__((visibility("default"))) const char * dictionary_get(const void * d, const char * key, const char * def);
extern __attribute__((visibility("default"))) int dictionary_set(void * vd, const char * key, const char * val);
extern __attribute__((visibility("default"))) void dictionary_unset(void * d, const char * key);
extern __attribute__((visibility("default"))) void dictionary_dump(const void * d, FILE * out);

#ifdef __cplusplus
}
#endif

#endif
