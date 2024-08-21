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

#include "Directory.h"
#include "StringEx.h"

#define DIRECTORY_SEPARATOR '/'

#include <stdlib.h>
#include <memory.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

char* dir_get_parent_directory(const char* dirname)
{
	size_t origlen = strlen(dirname);

	char* parent_dir = (char*)calloc(1, sizeof(char) * (origlen + 1));

	if(parent_dir == NULL)
	{
		return NULL;
	}

	memcpy(parent_dir, dirname, origlen);

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

	return parent_dir;
}

bool dir_is_exists(const char* dirname)
{
    DIR* dirp;

    dirp = opendir(dirname);

    if(dirp == NULL)
    {
        closedir(dirp);
        return false;
    }

    closedir(dirp);

    return true;
}

bool dir_create_directory(const char* dirname)
{
    if (dir_is_exists(dirname))
    {
        return true;
    }

    return mkdir(dirname, S_IRWXU);
}

char* dir_get_temp_directory(char *dirname)
{
    if(!dirname)
    {
        return NULL;
    }

    strcpy(dirname, "/tmp");

    return dirname;
}

char* dir_get_log_directory(char *dirname)
{
    if(!dirname)
    {
        return NULL;
    }

    char wd_path[1025] = { 0 };
    size_t wd_len = 1024;
    char* temp_ptr = NULL;

    temp_ptr = getcwd(wd_path, wd_len);

    if (temp_ptr == NULL)
    {
        return NULL;
    }

    if(strstr(wd_path, "/root"))
    {
        strcpy(dirname, "/var/log/");
    }
    else
    {
        strcat(dirname, getenv("HOME"));
        strcat(dirname, "/log/");
    }

    return dirname;
}

char* dir_get_config_directory(char *dirname)
{
    if(!dirname)
    {
        return NULL;
    }

    char config_dir[1025] = { 0 };
    size_t wd_len = 1024;
    char* temp_ptr = NULL;

    temp_ptr = getcwd(config_dir, wd_len);

    if (temp_ptr == NULL)
    {
        return NULL;
    }

    if(strstr(config_dir, "/root"))
    {
        strcpy(dirname, "/etc/");
    }
    else
    {
        size_t pos = 0;
        pos = (size_t)strstr(config_dir, "/bin");

        if(pos < 1)
        {
            for(int idx = strlen(config_dir)-1; config_dir[idx] != '/'; idx--)
            {
                config_dir[idx] = 0;
            }
        }
        else
        {
            for(size_t idx = pos; idx <= 1024; idx++)
            {
                config_dir[idx] = 0;
            }
        }
        strcat(config_dir, "etc/");
        strcpy(dirname, config_dir);
    }

    return dirname;
}
