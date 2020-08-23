/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#ifndef	RESPONDER_C
#define	RESPONDER_C

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIBRARY_EXPORT __attribute__((visibility("default")))

extern LIBRARY_EXPORT void* responder_create_socket(void* ptr, const char* servername, int serverport);
extern LIBRARY_EXPORT void* responder_assign_socket(void* ptr, int inSocket);
extern LIBRARY_EXPORT bool responder_connect_socket(void* ptr);
extern LIBRARY_EXPORT bool responder_close_socket(void* ptr);
extern LIBRARY_EXPORT bool responder_send_buffer(void* ptr, const char* data, size_t len);
extern LIBRARY_EXPORT bool responder_send_string(void* ptr, const char* str);
extern LIBRARY_EXPORT bool responder_receive_buffer(void* ptr, char** iobuffer, size_t len, bool alloc_buffer);
extern LIBRARY_EXPORT bool responder_receive_string(void* ptr, char** iostr, const char* delimeter);
extern LIBRARY_EXPORT size_t  responder_read_size(void* ptr);
extern LIBRARY_EXPORT bool responder_is_connected(void* ptr);
extern LIBRARY_EXPORT int  responder_get_socket(void* ptr);
extern LIBRARY_EXPORT int  responder_get_error_code(void* ptr);

#ifdef __cplusplus
}
#endif

#endif

