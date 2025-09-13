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

#include "directory.h"
#include "stringex.h"

#include <stdlib.h>
#include <memory.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

bool dir_is_exists(const string_t* dirname)
{
    DIR* dirp;

    dirp = opendir(string_c_str((string_t*)dirname));

    if(dirp == NULL)
    {
        closedir(dirp);
        return false;
    }

    closedir(dirp);

    return true;
}

bool dir_create_directory(const string_t* dirname)
{
    if (dir_is_exists(dirname))
    {
        return true;
    }

    return mkdir(string_c_str((string_t*)dirname), S_IRWXU);
}

string_t* dir_get_parent_directory(const string_t* dirname)
{
	size_t origlen = string_get_length((string_t*)dirname);

	char* parent_dir = (char*)calloc(1, sizeof(char) * (origlen + 1));

	if(parent_dir == NULL)
	{
		return NULL;
	}

	memcpy(parent_dir, string_c_str((string_t*)dirname), origlen);

	int len = (int)strlen(parent_dir);

	if(len < 2)
    {
        free(parent_dir);
		return NULL;
    }

	int ctr = len - 1;

	while(true)
	{
		parent_dir[ctr] = 0;
		ctr--;
        if(parent_dir[ctr] == '/')
		{
			break;
		}
	}

    string_t* retval = string_allocate(parent_dir);

	return retval;
}

string_t* dir_get_temp_directory()
{
    char* ptr = getenv("USER");
    string_t* retval = NULL;

    if(strcmp(ptr, "root") ==0)
    {
        retval = string_allocate("/tmp/");
    }
    else
    {
        retval = string_allocate(ptr);
        string_append(retval, "/.tmp/");
    }

    return retval;
}

string_t* dir_get_log_directory()
{
    char* ptr = getenv("USER");
    string_t* retval = NULL;

    if(strcmp(ptr, "root") ==0)
    {
        retval = string_allocate("/var/log/");
    }
    else
    {
        retval = string_allocate(ptr);
        string_append(retval, "/.local/log/");
    }

    return retval;
}

string_t* dir_get_config_directory()
{
    char* ptr = getenv("USER");
    string_t* retval = NULL;

    if(strcmp(ptr, "root") ==0)
    {
        retval = string_allocate("/etc/");
    }
    else
    {
        retval = string_allocate(ptr);
        string_append(retval, "/.config/");
    }

    return retval;
}
