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

#include "StringEx.h"
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

wchar_t *strtowstr(const char *str)
{
    return NULL;
}

char* strfromwstr(const wchar_t* wstr)
{
	if(wstr == NULL)
	{
		return NULL;
	}

    long wlen = 0;
    char* str = NULL;

    for (wlen = 0; wstr[wlen] != '\0'; wlen++) {}

    str = (char*)calloc(1, (unsigned long)wlen+1);

    if (str != NULL)
    {
        for (long idx = 0; idx < wlen; idx++)
        {
            str[idx] = (char)wstr[idx];
        }
    }

    return str;
}

char* strfromint(long num)
{
    char* ptr = (char*)calloc(1, (unsigned long)32);

	if (ptr == NULL)
	{
		return NULL;
	}

	int sign = 1;
    long remainder = 1;
    long dividend = num;
    long ctr = 0;

	if (num < 1)
	{
		sign = -1;
        dividend = dividend*(long)(-1);
	}

    while (dividend && ctr < 32)
	{
		remainder = dividend % 10;
		dividend = dividend / 10;

        ptr[ctr] = (char)(remainder + 48);
		ctr++;
	}

	if (sign < 1)
	{
		ptr[ctr] = '-';
	}
	else
	{
		ctr--;
	}

    long start = 0;

	while (start < ctr)
	{
		char temp = ptr[start];
		ptr[start] = ptr[ctr];
		ptr[ctr] = temp;
		start++;
		ctr--;
	}

	return ptr;
}

char* strfromdouble(double num)
{
	return NULL;
}

char* strreverse(char* ptr)
{
	size_t start = 0;

	size_t term = strlen(ptr) - 1;

	while (start < term)
	{
		char temp = ptr[start];
		ptr[start] = ptr[term];
		ptr[term] = temp;
		start++;
		term--;
	}

	return ptr;
}

char* strsegmentreverse(char* str, long start, long term)
{
	while (start < term)
	{
        char temp = str[start];
        str[start] = str[term];
        str[term] = temp;
		start++;
		term--;
	}

    return str;
}

long strindexofsubstr(const char* str, const char* substr)
{
    long result = -1;

    char* pdest = (char*)strstr( str, substr);

    if(pdest == 0)
    {
        return -1;
    }

    result = (long)(pdest - str);

    return result;
}

long strindexofchar(const char* str, const char ch)
{
    for (int ctr = 0; str[ctr] != '\0'; ctr++)
    {
        if (str[ctr] == ch)
        {
            return ctr;
        }
    }

    return -1;
}

long strcountsubstr(const char* str, const char* substr)
{
    long ctr = 0;

    long offset = (long)strlen(substr);

    const char* ptr = str;

	bool contiue_scan = true;

	while (contiue_scan)
	{
		long long index = strindexofsubstr(ptr, substr);

		if (index > -1)
		{
			ptr = ptr + index + offset;
			ctr++;
			contiue_scan = true;
		}
		else
		{
			contiue_scan = false;
		}
	}

    return ctr;
}

long strcountchar(char* str, const char ch)
{
    long ctr = 0;

    for (long index = 0; str[index] != '\0'; index++)
	{
		if (str[index] == ch)
		{
			ctr++;
		}
	}

	return ctr;
}

extern char* strtolower(char* str)
{
    for (long ctr = 0; str[ctr] != '\0'; ctr++)
    {
        if (str[ctr] >= 65 && str[ctr] <= 90)
        {
            str[ctr] = str[ctr] + 32;
        }
    }

    return str;
}

extern char* strtoupper(char* str)
{
    for (long ctr = 0; str[ctr] != '\0'; ctr++)
    {
        if (str[ctr] >= 97 && str[ctr] <= 122)
        {
            str[ctr] = str[ctr] - 32;
        }
    }

    return str;
}

char* strlefttrim(char* str)
{
    char *ptr = str;

    long ctr = 0;

    while (isspace(*ptr))
    {
        ptr++;
    }

    while (*ptr)
    {
        str[ctr] = *ptr;
        ctr++;
        ptr++;
    }

	while (str[ctr] != '\0')
	{
		str[ctr] = '\0';
		ctr++;
	}

    return str;
}

char* strrighttrim(char* str)
{
    long len = (long)strlen(str);

    for (long ctr = len - 1; ctr > -1; ctr--)
    {
        if (isspace(str[ctr]))
        {
            str[ctr] = '\0';
        }
        else
        {
            break;
        }
    }

    return str;
}

char* stralltrim(char* str)
{
    strrighttrim(str);
    strlefttrim(str);
    return str;
}

char* strremsubstrfirst(char* str, const char* substr)
{
    long pos = -1;
    long offset = (long)strlen(substr);

    pos = strindexofsubstr(str, substr);

    if(pos >= 0)
    {
        strcpy(str+pos, str+pos+offset);
        str[strlen(str) - (unsigned long)offset] = 0;
    }
    return str;
}

char* strremsubstrall(char* str, const char* substr)
{
    long pos = -1;
    long offset = (long)strlen(substr);

    pos = strindexofsubstr(str, substr);

    while(pos >= 0)
    {
        strcpy(str+pos, str+pos+offset);
        str[strlen(str) - (unsigned long)offset] = 0;
        pos = strindexofsubstr(str, substr);
    }
    return str;
}

char* strremsubstrat(char* str, long pos, long len)
{
    if(pos >= 0 && pos <= (long)(strlen(str)-1) )
    {
        strcpy(str+pos, str+pos+len);
        str[strlen(str) - (unsigned long)len] = 0;
    }
    return str;
}

char* strremcharfirst(char* str, const char oldchar)
{
    long pos = strindexofchar(str, oldchar);

    if(pos < 0)
    {
        return str;
    }

    size_t oldlen = strlen(str);

    strcpy(str+pos, str+pos+1);
    str[oldlen] = 0;
    return str;
}

char* strremcharall(char* str, const char oldchar)
{
    long pos = strindexofchar(str, oldchar);

    while(pos >= 0)
    {
        strcpy(str+pos, str+pos+1);
        str[strlen(str) - 1] = 0;
        pos = strindexofchar(str, oldchar);
    }
    return str;
}

char* strremcharat(char* str, long pos)
{
    strcpy(str+pos, str+pos+1);
    str[strlen(str) - 1] = 0;
    return str;
}

char* strrepsubstrfirst(char* str, const char* oldsubstr, const char* newsubstr)
{
    if(str == NULL || oldsubstr == NULL || newsubstr == NULL)
    {
        return NULL;
    }

    char* buffer = NULL;

    long pos = strindexofsubstr(str, oldsubstr);

    if(pos < 0)
    {
        return NULL;
    }

    long slen = (long)strlen(str);
    long oldslen = (long)strlen(oldsubstr);
    long newslen = (long)strlen(newsubstr);

    if(oldslen < 1 || newslen < 1)
    {
        return NULL;
    }

    long new_buffer_len = slen + (newslen - oldslen);

    buffer = (char*)calloc((unsigned long)(new_buffer_len + 1), sizeof(char));

    if(buffer == NULL)
    {
        return NULL;
    }

    long copy_pos;
    long ctr;

    copy_pos = 0;
    ctr = 0;

    while(ctr < pos)
    {
        buffer[copy_pos] = str[ctr];
        copy_pos++;
        ctr++;
    }

    ctr = 0;

    while(ctr < newslen)
    {
        buffer[copy_pos] = newsubstr[ctr];
        copy_pos++;
        ctr++;
    }

    ctr = pos + oldslen;

    while(str[ctr] != 0)
    {
        buffer[copy_pos] = str[ctr];
        copy_pos++;
        ctr++;
    }

    return buffer;
}

char* strrepsubstrall(char* str, const char* oldsubstr, const char* newsubstr)
{
	char* buffer = NULL;

	if(str == NULL || oldsubstr == NULL || newsubstr == NULL)
	{
		return NULL;
	}

    long slen = (long)strlen(str);
    long oldslen = (long)strlen(oldsubstr);
    long newslen = (long)strlen(newsubstr);

	if(oldslen < 1 || newslen < 1)
	{
		return NULL;
	}

    long numsubstr = strcountsubstr(str, oldsubstr);

	if(numsubstr < 1)
	{
		return NULL;
	}

	if(newslen > oldslen)
	{
        buffer = (char*)calloc((unsigned long)(slen + (newslen - oldslen)*numsubstr + 1), sizeof(char));

		if(buffer == NULL)
		{
			return NULL;
		}
	}
	else
	{
		buffer = str;
	}

    long pos = strindexofsubstr(str, oldsubstr);

	while(pos > -1)
	{
        long idx = 0;
        long ctr = 0;

		for(idx = 0; idx < slen; ++idx)
		{
			if(idx < pos)
			{
				buffer[idx] = str[idx];
			}
			else
			{
				if(idx < pos + newslen)
				{
					buffer[idx] = newsubstr[ctr];
					ctr++;
				}
				else
				{
					buffer[idx] = buffer[idx + (oldslen - newslen)];
				}
			}
		}

		pos = strindexofsubstr(str, oldsubstr);
	}

	return buffer;
}

char* strrepcharfirst(char* str, const char oldchar, const char newchar)
{
	if(str != NULL)
	{
		for(size_t pos = 0; str[pos] != 0; pos++)
		{
			if(str[pos] == oldchar)
			{
				str[pos] = newchar;
				return str;
			}
		}
		return str;
	}
	return NULL;
}

char* strrepcharall(char* str, const char oldchar, const char newchar)
{
    if(str != NULL)
    {
        for(size_t pos = 0; str[pos] != 0; pos++)
        {
            if(str[pos] == oldchar)
            {
                str[pos] = newchar;
            }
        }
        return str;
    }
    return NULL;
}

char* strrepcharat(char* str, const char newchar, long pos)
{
    if(str != NULL)
    {
        if(pos < (long)strlen(str))
        {
            str[pos] = newchar;
            return str;
        }
    }

    return NULL;
}

void strsplitkeyvaluesubstr(const char* str, const char* delimiter, char **key, char **value)
{
    if(str == NULL || delimiter == NULL)
    {
        return;
    }

    long pos = strindexofsubstr(str, delimiter);

    if(pos < 0)
    {
        return;
    }

    long val_start = pos + (long)strlen(delimiter);
    long val_end = (long)strlen(str);

    if(pos > 0)
    {
        *key = (char*)calloc(1, (unsigned long)(pos + 1));
        memcpy(*key, str, pos);
    }

    *value = (char*)calloc(1, (unsigned long)(val_end - val_start + 1));
    strcpy(*value, &str[val_start]);
}

void strsplitkeyvaluechar(const char* str, const char delimiter, char **key, char **value)
{
    if(str == NULL || delimiter == 0)
    {
        return;
    }

    long pos = strindexofchar(str, delimiter);

    if(pos < 0)
    {
        return;
    }

    long val_start = pos + 1;
    long val_end = (long)strlen(str);

    if(pos > 0)
    {
        *key = (char*)calloc(1, (unsigned long)(pos + 1));
        memcpy(*key, str, pos);
    }

    *value = (char*)calloc(1, (unsigned long)(val_end - val_start + 1));
    strcpy(*value, &str[val_start]);
}

extern char** strsplitsubstr(const char* str, const char* delimiter)
{
	if(str == NULL || delimiter == NULL)
	{
		return NULL;
	}

    long substr_count = strcountsubstr(str, delimiter);
    long str_len = (long)strlen(str);

	if(substr_count < 1)
	{
		return NULL;
	}

    char* ptr = (char*)calloc(1, (unsigned long)str_len);

	if(ptr == NULL)
	{
		return NULL;
	}

    memcpy(ptr, str, (unsigned long)str_len);

	char** buffer = NULL;

    buffer = (char **)calloc(1, (unsigned long)(substr_count + 1) * sizeof(char*));

	if(buffer == NULL)
	{
        free(ptr);
		return NULL;
	}

	char* temp_ptr = NULL;

	temp_ptr = strtok(ptr, delimiter);
    long index = 0;

	while(temp_ptr != NULL)
	{
        long temp_str_len = (long)strlen(temp_ptr);

        if(temp_str_len < 1)
        {
            continue;
        }

        buffer[index] = (char*)calloc(1, sizeof(char) * (unsigned long)(temp_str_len + 1));

		if(buffer[index] == NULL)
		{
			return NULL;
		}

        strcpy(buffer[index], temp_ptr);
		temp_ptr = strtok(NULL, delimiter);
		index++;
	}

    free(ptr);

	return buffer;
}

extern char** strsplitchar(const char* str, const char delimiter)
{
	char temp_delimiter[2] = {delimiter, 0};

    return strsplitsubstr(str, temp_delimiter);
}

extern char* strjoinwithsubstr(const char** strlist, const char* delimiter)
{
	return NULL;
}

extern char* strjoinwithchar(const char** strlist, const char delimiter)
{
	char temp_delimiter[2] = { delimiter, 0 };

	return strjoinwithsubstr(strlist, temp_delimiter);
}

void strfreelist(char** strlist)
{
    long index = 0;

    while(strlist[index] != NULL)
    {
        free(strlist[index]);
        index++;
    }

	free(strlist);
}
