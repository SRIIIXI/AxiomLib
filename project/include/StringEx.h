/*
BSD 2-Clause License

Copyright (c) 2017, Subrato Roy (subratoroy@hotmail.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _STRING_EX_C
#define _STRING_EX_C

#include <stddef.h>
#include <stdbool.h>

#if defined(_WIN32) || defined(WIN32) || defined (_WIN64) || defined (WIN64)
#define strtoull(str, endptr, base) _strtoui64(str, endptr, base)
#endif

extern wchar_t* strtowstr(const char* str);
extern char* strfromwstr(const wchar_t* wstr);

extern char* strfromint(size_t num);
extern char* strfromdouble(double num);

#if !defined(_WIN32) && !defined(WIN32) && !defined (_WIN64) && !defined (WIN64)
extern char* strrev(char* ptr);
#endif

extern char* strsegrev(char* str, size_t start, size_t term);

extern long long strindexofsubstr(char* str, const char* substr);
extern long long strindexofchar(char* str, const char ch);

extern size_t strcountsubstr(char* str, const char* substr);
extern size_t strcountchar(char* str, const char ch);

extern char* strtolower(char* str);
extern char* strtoupper(char* str);

extern char* strlefttrim(char* str);
extern char* strrighttrim(char* str);
extern char* stralltrim(char* str);

extern char* strremsubstrfirst(char* str, const char* substr);
extern char* strremsubstrall(char* str, const char* substr);
extern char* strremsubstrat(char* str, size_t pos, size_t len);

extern char* strremcharfirst(char* str, const char oldchar);
extern char* strremcharall(char* str, const char oldchar);
extern char* strremcharat(char* str, size_t pos);

extern char* strrepsubstrfirst(char* str, const char* substr);
extern char* strrepsubstrall(char* str, const char* substr);
extern char* strrepsubstrat(char* str, size_t pos, size_t len);

extern char* strrepcharfirst(char* str, const char oldchar, const char newchar);
extern char* strrepcharall(char* str, const char oldchar, const char newchar);
extern char* strrepcharat(char* str, const char newchar, size_t pos);

//extern List* strsplitsubstr(char* str, const char* substr);
extern char* strsplitchar(char* str, const char ch);
//extern char* strjoin(List *strlist);

#endif
