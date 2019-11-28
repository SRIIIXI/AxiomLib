#ifndef _STRING_EX_C
#define _STRING_EX_C

#include "List.h"
#include <stddef.h>

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

extern size_t strindexofsubstr(char* str, const char* substr);
extern size_t strindexofchar(char* str, const char ch);

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

extern List* strsplitsubstr(char* str, const char* substr);
extern List* strsplitchar(char* str, const char ch);
extern char* strjoin(List *strlist);

#endif
