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

#if defined (_WIN32) || defined (_WIN64)
#include <windows.h>
#else
#include <unistd.h>
#endif

typedef struct string_t
{
    char* data;
    size_t data_size;
    size_t memory_size;
}string_t;

typedef struct string_list_t
{
    string_t* strings;
    size_t num_of_strings;
    size_t current_index;
}string_list_t;

string_t* string_internal_adjust_storage(string_t* string_ptr, size_t sz);

string_t* string_allocate(const char* data)
{
    string_t* nd = (string_t*)calloc(1, sizeof(string_t));

    if(nd != NULL)
    {
        #if defined (_WIN32) || defined (_WIN64)
                SYSTEM_INFO siSysInfo;
                GetSystemInfo(&siSysInfo);
                nd->memory_size = siSysInfo.dwPageSize;
        #else
                nd->memory_size = sysconf(_SC_PAGESIZE);
        #endif
        nd->data_size = strlen(data);
        nd->data = (char*)calloc(nd->memory_size, sizeof (char));

        if(nd->data != NULL)
        {
            memcpy(nd->data, data, strlen(data));
        }
    }
    return nd;
}

string_t* string_allocate_default(void)
{
    string_t* nd = (string_t*)calloc(1, sizeof(string_t));

    if(nd != NULL)
    {
        #if defined (_WIN32) || defined (_WIN64)
                SYSTEM_INFO siSysInfo;
                GetSystemInfo(&siSysInfo);
                nd->memory_size = siSysInfo.dwPageSize;
        #else
                nd->memory_size = sysconf(_SC_PAGESIZE);
        #endif
        nd->data_size = 0;
        nd->data = (char*)calloc(nd->memory_size, sizeof (char));
    }
    return nd;
}

void string_free(string_t* str)
{
    free(str);
    str = NULL;
}

const char* string_c_str(string_t* str)
{
    return str->data;
}

wchar_t *string_to_wstr(const char *str)
{
    return NULL;
}

char* string_from_wstr(const wchar_t* wstr)
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

char* string_from_int(long num)
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

char* string_from_double(double num)
{
	return NULL;
}

char* string_reverse(char* ptr)
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

char* string_segment_reverse(char* str, long start, long term)
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

long string_index_of_substr(const char* str, const char* substr)
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

long string_index_of_char(const char* str, const char ch)
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

long string_count_substr(const char* str, const char* substr)
{
    long ctr = 0;

    long offset = (long)strlen(substr);

    const char* ptr = str;

	bool contiue_scan = true;

	while (contiue_scan)
	{
        long long index = string_index_of_substr(ptr, substr);

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

long string_count_char(char* str, const char ch)
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

extern char* string_to_lower(char* str)
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

extern char* string_to_upper(char* str)
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

char* string_left_trim(char* str)
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

char* string_right_trim(char* str)
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

char* string_all_trim(char* str)
{
    string_right_trim(str);
    string_left_trim(str);
    return str;
}

char* string_remove_substr_first(char* str, const char* substr)
{
    long pos = -1;
    long offset = (long)strlen(substr);

    pos = string_index_of_substr(str, substr);

    if(pos >= 0)
    {
        strcpy(str+pos, str+pos+offset);
        str[strlen(str) - (unsigned long)offset] = 0;
    }
    return str;
}

char* string_remove_substr_all(char* str, const char* substr)
{
    long pos = -1;
    long offset = (long)strlen(substr);

    pos = string_index_of_substr(str, substr);

    while(pos >= 0)
    {
        strcpy(str+pos, str+pos+offset);
        str[strlen(str) - (unsigned long)offset] = 0;
        pos = string_index_of_substr(str, substr);
    }
    return str;
}

char* string_remove_substr_at(char* str, long pos, long len)
{
    if(pos >= 0 && pos <= (long)(strlen(str)-1) )
    {
        strcpy(str+pos, str+pos+len);
        str[strlen(str) - (unsigned long)len] = 0;
    }
    return str;
}

char* string_remove_char_first(char* str, const char oldchar)
{
    long pos = string_index_of_char(str, oldchar);

    if(pos < 0)
    {
        return str;
    }

    size_t oldlen = strlen(str);

    strcpy(str+pos, str+pos+1);
    str[oldlen] = 0;
    return str;
}

char* string_remove_char_all(char* str, const char oldchar)
{
    long pos = string_index_of_char(str, oldchar);

    while(pos >= 0)
    {
        strcpy(str+pos, str+pos+1);
        str[strlen(str) - 1] = 0;
        pos = string_index_of_char(str, oldchar);
    }
    return str;
}

char* string_remove_char_at(char* str, long pos)
{
    strcpy(str+pos, str+pos+1);
    str[strlen(str) - 1] = 0;
    return str;
}

char* string_replace_substr_first(char* str, const char* oldsubstr, const char* newsubstr)
{
    if(str == NULL || oldsubstr == NULL || newsubstr == NULL)
    {
        return NULL;
    }

    char* buffer = NULL;

    long pos = string_index_of_substr(str, oldsubstr);

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

char* string_replace_substr_all(char* str, const char* oldsubstr, const char* newsubstr)
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

    long numsubstr = string_count_substr(str, oldsubstr);

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

    long pos = string_index_of_substr(str, oldsubstr);

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

        pos = string_index_of_substr(str, oldsubstr);
	}

	return buffer;
}

char* string_replace_char_first(char* str, const char oldchar, const char newchar)
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

char* string_replace_char_all(char* str, const char oldchar, const char newchar)
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

char* string_replace_char_at(char* str, const char newchar, long pos)
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

void string_split_key_value_by_substr(const char* str, const char* delimiter, char **key, char **value)
{
    if(str == NULL || delimiter == NULL)
    {
        return;
    }

    long pos = string_index_of_substr(str, delimiter);

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

void string_split_key_value_by_char(const char* str, const char delimiter, char **key, char **value)
{
    if(str == NULL || delimiter == 0)
    {
        return;
    }

    long pos = string_index_of_char(str, delimiter);

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

char** string_split_by_substr(const char* str, const char* delimiter)
{
	if(str == NULL || delimiter == NULL)
	{
		return NULL;
	}

    long substr_count = string_count_substr(str, delimiter);
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

char** string_split_by_char(const char* str, const char delimiter)
{
	char temp_delimiter[2] = {delimiter, 0};

    return string_split_by_substr(str, temp_delimiter);
}

char* string_join_list_with_substr(const char** strlist, const char* delimiter)
{
	return NULL;
}

char* string_join_list_with_char(const char** strlist, const char delimiter)
{
	char temp_delimiter[2] = { delimiter, 0 };

    return string_join_list_with_substr(strlist, temp_delimiter);
}

char* string_merge_list_with_substr(const char **strlist, const char* delimiter)
{
    return NULL;

}

char* string_merge_list_with_char(const char** strlist, const char delimite)
{
    return NULL;
}

void  string_sort_list(char** strlist)
{

}

void string_free_list(char** strlist)
{
    long index = 0;

    while(strlist[index] != NULL)
    {
        free(strlist[index]);
        index++;
    }

	free(strlist);
}

void  string_add_to_list(char** strlist, const char* str)
{

}

char*  string_get_first_from_list(const char** strlist)
{
    return NULL;
}

char*  string_get_next_from_list(const char** strlist)
{
    return NULL;
}


///////////////////////////////////////////////////////////

string_t* string_internal_adjust_storage(string_t* string_ptr, size_t sz)
{
    if(string_ptr == NULL)
    {
        return NULL;
    }

    size_t buffer_remaining = string_ptr->memory_size - string_ptr->data_size;

    if(buffer_remaining < sz)
    {
        void* ptr = (char*)calloc(string_ptr->memory_size*2, sizeof (char));

        if (ptr)
        {
            string_ptr->memory_size = string_ptr->memory_size*2;
            memcpy(ptr, string_ptr->data, string_ptr->data_size);
            free(string_ptr->data);
            string_ptr->data = ptr;
        }

    }

    return  string_ptr;
}
