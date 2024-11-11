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
#include <stdio.h>
#include <time.h>
#include <unistd.h>

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
char* string_internal_from_int(long num);
char* string_internal_from_double(double num);

string_t* string_allocate(const char* data)
{
    if(data == NULL)
    {
        return NULL;
    }

    string_t* nd = (string_t*)calloc(1, sizeof(string_t));

    if(nd != NULL)
    {
        size_t slen = strlen(data);
        size_t psize = sysconf(_SC_PAGESIZE);

        size_t pcount = slen/psize;

        if(slen%psize != 0)
        {
            pcount++;
        }

        nd->memory_size = psize*pcount;
        nd->data_size = slen;
        nd->data = (char*)calloc(nd->memory_size, sizeof (char));

        if(nd->data != NULL)
        {
            memcpy(nd->data, data, slen);
        }
    }
    return nd;
}

string_t* string_allocate_default(void)
{
    string_t* nd = (string_t*)calloc(1, sizeof(string_t));

    if(nd != NULL)
    {
        nd->memory_size = sysconf(_SC_PAGESIZE);
        nd->data_size = 0;
        nd->data = (char*)calloc(nd->memory_size, sizeof (char));
    }
    return nd;
}

string_t* string_allocate_length(size_t slen)
{
    string_t* nd = (string_t*)calloc(1, sizeof(string_t));
    if(nd != NULL)
    {
        size_t psize = sysconf(_SC_PAGESIZE);

        size_t pcount = slen/psize;

        if(slen%psize != 0)
        {
            pcount++;
        }

        nd->memory_size = psize*pcount;

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

void string_clear(string_t* str)
{
    if(str == NULL)
    {
        return;
    }

    if(str->data)
    {
        for(size_t i = 0; i < str->data_size; ++i)
            str->data[i] = 0;
    }
    str->data_size = 0;
}

bool string_is_equal(string_t* first, string_t* second)
{
    if(first != NULL && second != NULL)
    {
        if (first->data != NULL && second->data != NULL)
        {
            if(first->data_size != second->data_size)
            {
                return false;
            }

            if(memcmp(first->data, second->data, first->data_size) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool string_is_greater(string_t* first, string_t* second)
{
    if(first != NULL && second != NULL)
    {
        if(first->data != NULL && second->data != NULL)
        {
            if(first->data_size != second->data_size)
            {
                return false;
            }

            if(memcmp(first->data, second->data, first->data_size) > 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool string_is_less(string_t* first, string_t* second)
{
    if(first != NULL && second != NULL)
    {
        if(first->data != NULL && second->data != NULL)
        {
            if(first->data_size != second->data_size)
            {
                return false;
            }

            if(memcmp(first->data, second->data, first->data_size) < 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool string_is_null(string_t* ptr)
{
    if(ptr == NULL)
    {
        return true;
    }
    else
    {
        if(ptr->data == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

size_t string_get_length(string_t* str)
{
    return str->data_size;
}

const char* string_c_str(string_t* str)
{
    return str->data;
}

wchar_t *string_c_to_wstr(const char *str)
{
    return NULL;
}

wchar_t* string_to_wstr(const string_t* str)
{
    return NULL;
}

string_t *string_from_wstr(const wchar_t *wstr)
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

    string_t* ptr = string_allocate(str);

    free(str);

    return ptr;
}


string_t* string_copy(string_t* dest, string_t* orig)
{
    if(orig->data_size > dest->data_size)
    {
        string_internal_adjust_storage(dest, orig->data_size);
    }

    for(int x = 0; x < dest->memory_size; x++)
    {
        dest->data[x] = 0;
    }

    for(int x = 0; x < dest->memory_size; x++)
    {
        dest->data[x] = orig->data[x];
    }

    return NULL;
}

string_t* string_append(string_t* dest, const char *data)
{
    if(data == NULL)
    {
        return NULL;
    }

    if(strlen(data) < 1)
    {
        return NULL;
    }

    if(dest == NULL)
    {
        dest = string_allocate(data);
        return dest;
    }
    else
    {
        size_t sz = strlen(data);
        dest = string_internal_adjust_storage(dest, sz);
        memcpy(&dest->data[dest->data_size], data, sz);
        dest->data_size = dest->data_size + sz;
    }

    return dest;
}

string_t* string_append_string(string_t* dest, const string_t *str)
{
    return string_append(dest, str->data);
}

string_t* string_append_integer(string_t* dest, const long data)
{
    char buffer[17] = {0};
    sprintf(buffer, "%ld", data);
    return string_append(dest, buffer);
}

string_t* string_append_real(string_t* dest, const double data)
{
    char buffer[17] = {0};
    sprintf(buffer, "%f", data);
    return string_append(dest, buffer);
}

string_t* string_append_real_scientific(string_t* dest, const double data)
{
    char buffer[17] = {0};
    sprintf(buffer, "%.3e", data);
    return string_append(dest, buffer);
}

string_t* string_append_char(string_t* dest, const char data)
{
    char buffer[2] = {data, 0};
    return string_append(dest, buffer);
}

string_t* string_append_boolean(string_t* dest, const bool data)
{
    char buffer[6] = {0};

    if(data)
    {
        strcpy(buffer, "true");
    }
    else
    {
        strcpy(buffer, "false");
    }

    return string_append(dest, buffer);
}

string_t* string_append_curr_timestamp(string_t* dest)
{
    if(dest == NULL)
    {
        return NULL;
    }

    char buffer[129] = {0};
    time_t t ;
    struct tm *tmp ;
    time(&t);
    tmp = localtime(&t);

    sprintf(buffer, "%04d%02d%02d%02d%02d%02d",
            (tmp->tm_year+1900), (tmp->tm_mon+1), tmp->tm_mday,
            tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

    return string_append(dest, buffer);
}

string_t *string_reverse(string_t *str)
{
	size_t start = 0;

    size_t term = str->data_size - 1;

	while (start < term)
	{
        char temp = str->data[start];
        str->data[start] = str->data[term];
        str->data[term] = temp;
		start++;
		term--;
	}

    return str;
}

string_t *string_segment_reverse(string_t *str, size_t start, size_t term)
{
	while (start < term)
	{
        char temp = str->data[start];
        str->data[start] = str->data[term];
        str->data[term] = temp;
		start++;
		term--;
	}

    return str;
}

long string_index_of_substr(const string_t *str, const string_t *substr)
{
    long result = -1;

    char* pdest = (char*)strstr( str->data, substr->data);

    if(pdest == 0)
    {
        return -1;
    }

    result = (long)(pdest - str->data);

    return result;
}

long string_index_of_char(const string_t *str, const char ch)
{
    for (int ctr = 0; str->data[ctr] != '\0'; ctr++)
    {
        if (str->data[ctr] == ch)
        {
            return ctr;
        }
    }

    return -1;
}

long string_count_substr(const string_t *str, const string_t *substr)
{
    long ctr = 0;

    long offset = substr->data_size;

    const char* ptr = str->data;

	bool contiue_scan = true;

	while (contiue_scan)
	{
        long long index = string_index_of_substr(str, substr);

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

long string_count_char(const string_t *str, const char ch)
{
    long ctr = 0;

    for (long index = 0; str->data[index] != '\0'; index++)
	{
        if (str->data[index] == ch)
		{
			ctr++;
		}
	}

	return ctr;
}

string_t *string_to_lower(string_t *str)
{
    for (long ctr = 0; str->data[ctr] != '\0'; ctr++)
    {
        if (str->data[ctr] >= 65 && str->data[ctr] <= 90)
        {
            str->data[ctr] = str->data[ctr] + 32;
        }
    }

    return str;
}

extern string_t *string_to_upper(string_t *str)
{
    for (long ctr = 0; str->data[ctr] != '\0'; ctr++)
    {
        if (str->data[ctr] >= 97 && str->data[ctr] <= 122)
        {
            str->data[ctr] = str->data[ctr] - 32;
        }
    }

    return str;
}

string_t *string_left_trim(string_t *str)
{
    char *ptr = str->data;

    long ctr = 0;

    while (isspace(*ptr))
    {
        ptr++;
    }

    while (*ptr)
    {
        str->data[ctr] = *ptr;
        ctr++;
        ptr++;
    }

    while (str->data[ctr] != '\0')
	{
        str->data[ctr] = '\0';
		ctr++;
	}

    return str;
}

string_t *string_right_trim(string_t *str)
{
    long len = str->data_size;

    for (long ctr = len - 1; ctr > -1; ctr--)
    {
        if (isspace(str->data[ctr]))
        {
            str->data[ctr] = '\0';
        }
        else
        {
            break;
        }
    }

    return str;
}

string_t *string_all_trim(string_t *str)
{
    string_right_trim(str);
    string_left_trim(str);
    return str;
}

string_t *string_remove_substr_first(string_t *str, const string_t *substr)
{
    long pos = -1;
    long offset = substr->data_size;

    pos = string_index_of_substr(str, substr);

    if(pos >= 0)
    {
        strcpy(str->data + pos, str->data + pos + offset);
        str->data[str->data_size - (unsigned long)offset] = 0;
    }
    return str;
}

string_t *string_remove_substr_all(string_t *str, const string_t *substr)
{
    long pos = -1;
    long offset = substr->data_size;

    pos = string_index_of_substr(str, substr);

    while(pos >= 0)
    {
        strcpy(str->data + pos, str->data + pos + offset);
        str->data[str->data_size - (unsigned long)offset] = 0;
        pos = string_index_of_substr(str, substr);
    }
    return str;
}

string_t* string_remove_substr_at(string_t *str, size_t pos, size_t len)
{
    if(pos >= 0 && pos <= (str->data_size-1) )
    {
        strcpy(str->data + pos, str->data + pos + len);
        str->data[str->data_size - len] = 0;
    }
    return str;
}

void string_remove_end(string_t* ptr, size_t len)
{

}

void string_remove_start(string_t* ptr, size_t len)
{

}

string_t *string_remove_char_first(string_t *str, const char oldchar)
{
    long pos = string_index_of_char(str, oldchar);

    if(pos < 0)
    {
        return str;
    }

    size_t oldlen = str->data_size;

    strcpy(str->data + pos, str->data + pos + 1);
    str->data[oldlen] = 0;
    return str;
}

string_t *string_remove_char_all(string_t *str, const char oldchar)
{
    long pos = string_index_of_char(str, oldchar);

    while(pos >= 0)
    {
        strcpy(str->data + pos, str->data+pos + 1);
        str->data[str->data_size - 1] = 0;
        pos = string_index_of_char(str, oldchar);
    }
    return str;
}

string_t *string_remove_char_at(string_t *str, size_t pos)
{
    strcpy(str->data + pos, str->data + pos + 1);
    str->data[str->data_size - 1] = 0;
    return str;
}

string_t *string_replace_substr_first(string_t *str, const string_t *oldsubstr, const string_t *newsubstr)
{
    if(str == NULL || oldsubstr == NULL || newsubstr == NULL)
    {
        return NULL;
    }

    string_t* buffer = NULL;

    long pos = string_index_of_substr(str, oldsubstr);

    if(pos < 0)
    {
        return NULL;
    }

    long slen = str->data_size;
    long oldslen = oldsubstr->data_size;
    long newslen = newsubstr->data_size;

    if(oldslen < 1 || newslen < 1)
    {
        return NULL;
    }

    long new_buffer_len = slen + (newslen - oldslen);

    buffer = string_allocate_length(new_buffer_len + 1);

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
        buffer->data[copy_pos] = str->data[ctr];
        copy_pos++;
        ctr++;
    }

    ctr = 0;

    while(ctr < newslen)
    {
        buffer->data[copy_pos] = newsubstr->data[ctr];
        copy_pos++;
        ctr++;
    }

    ctr = pos + oldslen;

    while(str->data[ctr] != 0)
    {
        buffer->data[copy_pos] = str->data[ctr];
        copy_pos++;
        ctr++;
    }

    return buffer;
}

string_t *string_replace_substr_all(string_t *str, const string_t *oldsubstr, const string_t *newsubstr)
{
    string_t* buffer = NULL;

	if(str == NULL || oldsubstr == NULL || newsubstr == NULL)
	{
		return NULL;
	}

    long slen = str->data_size;
    long oldslen = oldsubstr->data_size;
    long newslen = newsubstr->data_size;

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
        buffer = string_allocate_length(slen + (newslen - oldslen)*numsubstr + 1);

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

string_t *string_replace_char_first(string_t *str, const char oldchar, const char newchar)
{
	if(str != NULL)
	{
        for(size_t pos = 0; str->data[pos] != 0; pos++)
		{
            if(str->data[pos] == oldchar)
			{
                str->data[pos] = newchar;
				return str;
			}
		}
		return str;
	}
	return NULL;
}

string_t *string_replace_char_all(string_t *str, const char oldchar, const char newchar)
{
    if(str != NULL)
    {
        for(size_t pos = 0; str->data[pos] != 0; pos++)
        {
            if(str->data[pos] == oldchar)
            {
                str->data[pos] = newchar;
            }
        }
        return str;
    }
    return NULL;
}

string_t *string_replace_char_at(string_t *str, const char newchar, size_t pos)
{
    if(str != NULL)
    {
        if(pos < str->data_size)
        {
            str->data[pos] = newchar;
            return str;
        }
    }

    return NULL;
}

void string_split_key_value_by_char(const string_t *str, const char delimiter, string_t **key, string_t **value)
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
    long val_end = str->data_size;

    if(pos > 0)
    {
        *key = string_allocate_length(pos+1);
        memcpy((*key)->data, str->data, pos);
    }

    *value = (string_allocate_length(val_end - val_start + 1));
    strcpy((*value)->data, &str->data[val_start]);
}

void string_split_key_value_by_substr(const string_t *str, const char* delimiter, string_t **key, string_t **value)
{
    if(str == NULL || delimiter == NULL)
    {
        return;
    }

    string_t* delimeter_data = string_allocate(delimiter);

    long pos = string_index_of_substr(str, delimeter_data);

    if(pos < 0)
    {
        string_free(delimeter_data);
        return;
    }

    long val_start = pos + delimeter_data->data_size;
    long val_end = str->data_size;

    if(pos > 0)
    {
        *key = string_allocate_length(pos + 1);
        memcpy((*key)->data, str, pos);
    }

    *value = string_allocate_length(val_end - val_start + 1);
    strcpy((*value)->data, &str->data[val_start]);

    string_free(delimeter_data);
}

 string_list_t* string_list_allocate_default(void)
 {
    string_list_t* retval = (string_list_t*)calloc(1, sizeof(string_list_t));
    return retval;
 }

string_list_t *string_split_by_substr(const string_t *str, const char *delimiter)
{
    string_list_t* retval = NULL;

	if(str == NULL || delimiter == NULL)
	{
		return NULL;
	}

    string_t* delimeter_data = string_allocate(delimiter);

    long substr_count = string_count_substr(str, delimeter_data);
    long str_len = str->data_size;

	if(substr_count < 1)
	{
        string_free(delimeter_data);
        return NULL;
	}

    char* ptr = (char*)calloc(1, (unsigned long)str_len+1);

	if(ptr == NULL)
	{
        string_free(delimeter_data);
        return NULL;
	}

    memcpy(ptr, str->data, (unsigned long)str_len);

	char** buffer = NULL;

    buffer = (char **)calloc(1, (unsigned long)(substr_count + 1) * sizeof(char*));

	if(buffer == NULL)
	{
        free(ptr);
        string_free(delimeter_data);
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
            string_free(delimeter_data);
            return NULL;
        }

        strcpy(buffer[index], temp_ptr);
		temp_ptr = strtok(NULL, delimiter);
		index++;
	}

    free(ptr);
    string_free(delimeter_data);

	return retval;
}

string_list_t* string_split_by_char(const string_t* str, const char delimiter)
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

void  string_sort_list(string_list_t *strlist)
{

}

void string_free_list(string_list_t *strlist)
{
    long index = 0;

    if(strlist != NULL)
    {
        for(int x = 0; x < strlist->num_of_strings; x++)
        {
            string_free(&strlist->strings[x]);
        }
        free(strlist);
    }
}

void  string_append_to_list(string_list_t *strlist, const char *str)
{

}

void  string_append_string_to_list(string_list_t* strlist, const string_t* str)
{

}

string_t* string_get_first_from_list(string_list_t* strlist)
{
    if(strlist != NULL)
    {
        if(strlist->num_of_strings > 0)
        {
            strlist->current_index = 0;
            return &strlist->strings[0];
        }
    }

    return NULL;
}

string_t *string_get_next_from_list(string_list_t *strlist)
{
    if(strlist != NULL)
    {
        if(strlist->num_of_strings > 1)
        {
            strlist->current_index++;
            return &strlist->strings[strlist->current_index];
        }
    }

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

char* string_internal_from_int(long num)
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

char* string_internal_from_double(double num)
{
    return NULL;
}
