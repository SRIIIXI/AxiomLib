/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#ifndef BASE_64_C
#define BASE_64_C

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIBRARY_EXPORT __attribute__((visibility("default")))

extern LIBRARY_EXPORT char* base64_encode(const unsigned char *data, unsigned long inputlength, char *encodedString, unsigned long *outputlength);
extern LIBRARY_EXPORT unsigned char* base64_decode(const char *encodedString, unsigned long inputlength, unsigned char *decodedData, unsigned long *outputlength);

#ifdef __cplusplus
}
#endif

#endif
