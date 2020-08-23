/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#ifndef DIRECTORY_C
#define DIRECTORY_C

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIBRARY_EXPORT __attribute__((visibility("default")))

extern LIBRARY_EXPORT bool dir_is_exists(const char* dirname);
extern LIBRARY_EXPORT bool dir_create_directory(const char* dirname);
extern LIBRARY_EXPORT char* dir_get_parent_directory(const char* dirname);
extern LIBRARY_EXPORT char* dir_get_temp_directory(char* dirname);
extern LIBRARY_EXPORT char* dir_get_log_directory(char *dirname);
extern LIBRARY_EXPORT char* dir_get_config_directory(char *dirname);

#ifdef __cplusplus
}
#endif

#endif
