/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#ifndef LOGGER_C
#define LOGGER_C

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIBRARY_EXPORT __attribute__((visibility("default")))

typedef enum LogLevel
{
	LOG_INFO = 0,
	LOG_ERROR = 1,
	LOG_WARNING = 2,
	LOG_CRITICAL = 3,
	LOG_PANIC = 4
}LogLevel;

extern LIBRARY_EXPORT void*  logger_allocate_default();
extern LIBRARY_EXPORT void*  logger_allocate(size_t flszmb, const char* dirpath);
extern LIBRARY_EXPORT void    logger_release(void* loggerptr);
extern LIBRARY_EXPORT bool    logger_write(void* loggerptr, const char* logentry, LogLevel llevel, const char* func, const char* file, int line);

#define WriteLog(lptr, str, level) \
    logger_write(lptr, str, level, __PRETTY_FUNCTION__, __FILE__, __LINE__)

#define WriteInformation(lptr, str) \
    logger_write(lptr, str, LOG_INFO, __PRETTY_FUNCTION__, __FILE__, __LINE__);

#ifdef __cplusplus
}
#endif

#endif

