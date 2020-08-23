/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#ifndef CONFIGURATION_INI
#define CONFIGURATION_INI

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

extern __attribute__((visibility("default"))) void*       configuration_ini_load(const char *filename);
extern __attribute__((visibility("default"))) void        configuration_ini_free(void *ptr);
extern __attribute__((visibility("default"))) const char* configuration_ini_get(void *ptr, const char *section, const char *key);
extern __attribute__((visibility("default"))) const char* configuration_ini_get_string(void *ptr, const char *section, const char *key);
extern __attribute__((visibility("default"))) long        configuration_ini_get_number(void *ptr, const char *section, const char *key);
extern __attribute__((visibility("default"))) float       configuration_ini_get_real(void *ptr, const char *section, const char *key);
extern __attribute__((visibility("default"))) bool        configuration_ini_get_boolean(void *ptr, const char *section, const char *key);
extern __attribute__((visibility("default"))) int         configuration_ini_sget(void *ptr, const char *section, const char *key, const char *scanfmt, void *dst);

#ifdef __cplusplus
}
#endif

#endif
