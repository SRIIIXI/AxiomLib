/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#ifndef FILE_C
#define FILE_C

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIBRARY_EXPORT __attribute__((visibility("default")))

extern LIBRARY_EXPORT bool file_is_exists(const char* filename);
extern LIBRARY_EXPORT char* file_get_parent_directory(const char* filename);
extern LIBRARY_EXPORT char* file_get_basename(const char* filename);
extern LIBRARY_EXPORT char* file_get_extension(const char* filename);

#ifdef __cplusplus
}
#endif

#endif
