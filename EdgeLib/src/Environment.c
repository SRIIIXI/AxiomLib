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
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

string_t* env_get_current_process_name()
{
    string_t* retval = NULL;
    size_t ln = 0;
    bool fnd = false;
    int ctr = 0;


    pid_t proc_id = getpid();
    char buffer[1025] = {0};

    char* procfilename = (char*)calloc(1, 32);
    sprintf(procfilename, "/proc/%d/cmdline", proc_id);
    FILE* fp = fopen(procfilename, "r");
    free(procfilename);
    procfilename = NULL;

    if(fp)
    {
        if(fgets(buffer, 1024, fp))
        {
            ln = strlen(buffer);
            fnd = false;

            for(ctr = 0; ctr < ln; ctr++)
            {

                if(fnd)
                {
                    buffer[ctr] = 0;
                }
                else
                {
                    if(isspace(buffer[ctr]))
                    {
                        fnd = true;
                        buffer[ctr] = 0;
                    }                    
                }
            }

            ln = strlen(buffer);
            fnd = false;

            for(ctr = ln -1 ; ctr > -1; ctr--)
            {

                if(fnd)
                {
                    buffer[ctr] = 32;
                }
                else
                {
                    if(buffer[ctr] == '/')
                    {
                        fnd = true;
                        buffer[ctr] = 32;
                    }                    
                }
            }

            retval = string_allocate(buffer);
            retval = string_all_trim(retval);
        }

        fclose(fp);
    }

    return retval;
}

string_t* env_get_current_user_name()
{
    string_t* ptr = string_allocate(getenv("USER"));
    return ptr;
}

string_t* env_get_lock_filename()
{
    string_t* lock_filename = string_allocate_default();
    string_t* temp = NULL;

    if (lock_filename == NULL)
    {
        return NULL;
    }
    
    temp = dir_get_temp_directory();
    string_append_string(lock_filename, temp);
    free(temp);
    string_append_char(lock_filename, '/');

    temp = env_get_current_process_name();
    string_append_string(lock_filename, temp);
    free(temp);
    string_append_char(lock_filename, '.');

    temp = env_get_current_user_name();
    string_append_string(lock_filename, temp);
    free(temp);

    string_append(lock_filename, ".lock");

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
