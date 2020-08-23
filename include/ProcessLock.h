/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#ifndef PROCESS_LOCK_C
#define PROCESS_LOCK_C

#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

extern __attribute__((visibility("default"))) char*   process_lock_get_current_process_name(char* ptr);
extern __attribute__((visibility("default"))) char*   process_lock_get_current_user_name();
extern __attribute__((visibility("default"))) char*   process_lock_get_lock_filename();
extern __attribute__((visibility("default"))) bool    process_lock_lock(const char* lock_filename);

#ifdef __cplusplus
}
#endif

#endif
