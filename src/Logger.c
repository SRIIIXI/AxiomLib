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

#include "Logger.h"
#include "Directory.h"
#include "File.h"
#include "StringEx.h"
#include "StringList.h"
#include "Environment.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>

#define END_OF_LINE "\n"
#define MAX_LOGGERS 512

static char log_level_names[5][16] = {"Information", "Error", "Warning", "Critical", "Panic"};

void normalize_function_name(char* func_name);

#pragma pack(1)
typedef struct Logger
{
    size_t LogFileSizeMB;
    char FileName[1025];
    FILE* FileHandle;
}Logger;

void*	logger_allocate_default()
{
    return logger_allocate(10, NULL);
}

void*	logger_allocate(size_t flszmb, const char* dirpath)
{   
    Logger* logger_ptr = (Logger*)calloc(1, sizeof (Logger));

    if(!logger_ptr)
    {
        return NULL;
    }

    logger_ptr->FileHandle = NULL;

    if(flszmb < 1 || flszmb > 10)
    {
        flszmb = 10;
    }

    logger_ptr->LogFileSizeMB = flszmb;

    if(dirpath != NULL)
    {
        strcat(logger_ptr->FileName, dirpath);

        if(dirpath[strlen(dirpath) - 1] != '/')
        {
            strcat(logger_ptr->FileName, "/");
        }
    }
    else
    {
        pid_t parent = getppid();

        if(parent == 0)
        {
            strcat(logger_ptr->FileName, "/var/log/");
        }
        else
        {
            char wd_path[1025] = { 0 };
            size_t wd_len = 1024;
            getcwd(wd_path, wd_len);
            char* parent_dir = dir_get_parent_directory(wd_path);
            strcat(logger_ptr->FileName, parent_dir);
            strcat(logger_ptr->FileName, "log/");
            free(parent_dir);
        }
    }

    if(!dir_is_exists(logger_ptr->FileName))
    {
        dir_create_directory(logger_ptr->FileName);
    }

    char temp[1024] = {0};
    env_get_current_process_name(&temp[0]);
    strcat(logger_ptr->FileName, temp);
    strcat(logger_ptr->FileName, ".log");

    return logger_ptr;
}

void logger_release(void* loggerptr)
{
    Logger* logger_ptr = (Logger*)loggerptr;

    if(!logger_ptr)
    {
        return;
    }

    if(logger_ptr->FileHandle)
    {
        fflush(logger_ptr->FileHandle);
        fclose(logger_ptr->FileHandle);
    }

    free(logger_ptr);
}

bool logger_write(void* loggerptr, const char* logentry, LogLevel llevel, const char* func, const char* file, int line)
{
    Logger* logger_ptr = (Logger*)loggerptr;

    if(!logger_ptr)
    {
        return false;
    }

    if(logger_ptr->FileHandle == NULL)
    {
        logger_ptr->FileHandle = fopen(logger_ptr->FileName, "w");

        if(logger_ptr->FileHandle == NULL)
        {
            return false;
        }
    }

    // Check the file size
    size_t sz = (size_t)ftell(logger_ptr->FileHandle);

    // If it exceeds the set size
    if(sz >= logger_ptr->LogFileSizeMB*1024*1024)
    {
        // Stop logging
        fflush(logger_ptr->FileHandle);
        fclose(logger_ptr->FileHandle);

        // Rename the file
        char old_log_filename[1025] = {0};
        strcat(old_log_filename, logger_ptr->FileName);
        strcat(old_log_filename, ".old");

        rename(logger_ptr->FileName, old_log_filename);

        // Reopen the log file with original name
        logger_ptr->FileHandle = fopen(logger_ptr->FileName, "w");

        if(logger_ptr->FileHandle == NULL)
        {
            return false;
        }
    }

    time_t t ;
    struct tm *tmp ;
    time(&t);
    tmp = localtime(&t);

    // Timestamp
    fprintf(logger_ptr->FileHandle, "%02d-%02d-%04d %02d:%02d:%02d\t",
             tmp->tm_mday, (tmp->tm_mon+1), (tmp->tm_year+1900),
             tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

    // Level
    fprintf(logger_ptr->FileHandle, "%s\t", log_level_names[llevel]);

    // File
    char* base_file_name = file_get_basename(file);
    fprintf(logger_ptr->FileHandle, "%s\t", base_file_name);
    free(base_file_name);

    // Line
    fprintf(logger_ptr->FileHandle, "%d\t", line);

    // Function
    normalize_function_name(func);
    fprintf(logger_ptr->FileHandle, "%s\t", func);

    // Message
    fprintf(logger_ptr->FileHandle, "%s", logentry);

    // End of line
    fprintf(logger_ptr->FileHandle, END_OF_LINE);

    // Flush th contents
    fflush(logger_ptr->FileHandle);

    return true;
}

void normalize_function_name(char* func_name)
{
    
}
