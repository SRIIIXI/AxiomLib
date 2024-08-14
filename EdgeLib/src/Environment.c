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

#include "Environment.h"
#include "StringEx.h"
#include "Directory.h"

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#if defined (_WIN32) || defined (_WIN64)
#include <psapi.h>
#else
#include <fcntl.h>
#include <unistd.h>
#endif

char* env_get_current_process_name(char* ptr)
{
    if(ptr == NULL)
    {
        return NULL;
    }

    pid_t proc_id = getpid();

    #if defined (_WIN32) || defined (_WIN64)

    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, proc_id);

    // Get the process name.

    if (NULL != hProcess)
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
        {
            GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
            strcpy(ptr, szProcessName);
        }

        CloseHandle(hProcess);
    }

    #else

        char* buffer = (char*)calloc(1, 32);
        char** cmd_args = NULL;
        char** dir_tokens = NULL;

        sprintf(buffer, "/proc/%d/cmdline", proc_id);

        FILE* fp = fopen(buffer, "r");
        free(buffer);
        buffer = NULL;

        if(fp)
        {
            buffer = (char*)calloc(1, 1025);

            if(fgets(buffer, 1024, fp))
            {
                long dir_sep_pos = string_index_of_char(buffer, '/');

                if(dir_sep_pos < 0)
                {
                    strcpy(ptr, buffer);
                    free(buffer);
                    fclose(fp);
                    return ptr;
                }

                cmd_args = string_split_by_char(buffer, ' ');

                if(cmd_args != NULL)
                {
                    dir_tokens = string_split_by_char(cmd_args[0], '/');
                }
                else
                {
                    dir_tokens = string_split_by_char(buffer, '/');
                }

                if(dir_tokens != NULL)
                {
                    char* last_str = NULL;
                    for(int index = 0; dir_tokens[index] != 0; index++)
                    {
                        last_str = dir_tokens[index];
                    }

                    if (last_str != NULL)
                    {
                        strcpy(ptr, last_str);
                    }
                }

                if(cmd_args)
                {
                    string_free_list(cmd_args);
                }

                if(dir_tokens)
                {
                    string_free_list(dir_tokens);
                }
            }
            else
            {
                printf("Could not read process commandline\n");
            }

            fclose(fp);
        }    
        
        if(buffer)
        {
            free(buffer);
        }

    #endif

    return ptr;
}

char* env_get_current_user_name(char* ptr)
{
    if (ptr == NULL)
    {
        return NULL;
    }

    #if defined (_WIN32) || defined (_WIN64)

        TCHAR szUserName[65] = { 0 };
        DWORD slen = 64;

        if (GetUserNameA(szUserName, &slen))
        {
            strcpy(ptr, szUserName);
        }

    #else
        strcpy(ptr, getenv("USER"));
    #endif

    return ptr;
}

char* env_get_lock_filename(char* ptr)
{
    if (ptr == NULL)
    {
        return NULL;
    }

    char* lock_filename = (char*)calloc(1, 1025);

    if (lock_filename == NULL)
    {
        return NULL;
    }

    char temp[65] = {0};

    memset(temp, 0, 65);
    strcat(lock_filename, dir_get_temp_directory(temp));
    strcat(lock_filename, "/");

    memset(temp, 0, 65);
    strcat(lock_filename, env_get_current_process_name(temp));
    strcat(lock_filename, ".");

    memset(temp, 0, 65);
    strcat(lock_filename, env_get_current_user_name(temp));
    strcat(lock_filename, ".lock");

    return  lock_filename;
}

/*
bool env_lock_process(const char* lock_filename)
{
    int lock_file = 0;

    if (lock_file != 0 && lock_file != -1)
    {
        //File is already open
        return false;
    }

    lock_file = open(lock_filename, O_CREAT | O_RDWR, 0666);
    if (lock_file != -1)
    {
        off_t sz = 0;
        int rc = lockf(lock_file, F_TLOCK, sz);
        if (rc == -1)
        {
            close(lock_file);
            lock_file = 0;
            return false;
        }

        // Okay! We got a lock
        return true;
    }
    else
    {
        lock_file = 0;
        return false;
    }

    return true;
}

bool env_unlock_process(const char* lock_filename)
{

}
*/
