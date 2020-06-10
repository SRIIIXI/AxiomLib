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

#include "StringList.h"
#include "StringEx.h"
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


////////////////////////////////////////////////////////////////////////
//================================List Operaqtions=====================
///////////////////////////////////////////////////////////////////////

string_list* strlist_allocate(string_list* lptr)
{
	return NULL;
}

void strlist_clear(string_list* lptr)
{
	return;
}

string_list* strlist_allocate_from_splitsubstr(const char* str, const char* delimiter, size_t* numsubstr)
{
	return NULL;
}

string_list* strlist_allocate_from_strsplitchar(const char* str, const char delimiter, size_t* numsubstr)
{
	return NULL;
}

char* strlist_joinwithsubstr(const string_list* strlist, const char* delimiter)
{
	return NULL;
}

char* strlist_joinwithchar(const string_list* strlist, const char delimiter)
{
	return NULL;
}

void  strlist_freelist(string_list* strlist, size_t numsubstr)
{
	return;
}


string_node* strlist_add_to_head(string_list* lptr, char* str, size_t sz)
{
	return NULL;
}

string_node* strlist_add_to_tail(string_list* lptr, char* str, size_t sz)
{
	return NULL;
}

string_node* strlist_insert(string_list* lptr, char* str, size_t sz, int pos)
{
	return NULL;
}


void strlist_remove_from_head(string_list* lptr)
{
	return;
}

void strlist_remove_from_tail(string_list* lptr)
{
	return;
}

void strlist_remove(string_list* lptr, const string_node* node)
{
	return;
}

void strlist_remove_at(string_list* lptr, int pos)
{
	return;
}

void strlist_remove_value(string_list* lptr, char* str, size_t sz)
{
	return;
}


size_t strlist_item_count(string_list* lptr)
{
	return -1;
}

size_t strlist_index_of(string_list* lptr, const string_node* node)
{
	return -1;
}

size_t strlist_index_of_value(string_list* lptr, char* str, size_t sz)
{
	return  -1;
}

string_node* strlist_get_at(string_list* lptr, int atpos)
{
	return NULL;
}


string_node* strlist_get_first(string_list* lptr)
{
	return NULL;
}

string_node* strlist_get_next(string_list* lptr)
{
	return NULL;
}

string_node* strlist_get_last(string_list* lptr)
{
	return NULL;
}

string_node* strlist_get_previous(string_list* lptr)
{
	return NULL;
}


string_list* strlist_sort(string_list* lptr)
{
	return NULL;
}

string_list* strlist_merge(string_list* lptrFirst, string_list* lptrSecond)
{
	return NULL;
}

string_list* strlist_join(string_list* lptrFirst, string_list* lptrSecond)
{
	return NULL;
}

