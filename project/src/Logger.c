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
#include "Map.h"
#include "Directory.h"
#include "File.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#include <process.h>
#define getcwd(s, i) _getcwd(s, i)
#define getpid() _getpid()
#endif

char log_level_names[5][16] = {"Information", "Error", "Warning", "Critical", "Panic"};

typedef struct Logger
{
    size_t LogFileSizeMB;
    char FileName[1025];
    FILE* FileHandle;
    bool IsOpen;
    int PID;
}Logger;

Logger *loggers[512] = {0};

size_t	logger_allocate_default()
{
    char owner[33] = {0};
    char wd_path[1025] = {0};
    int wd_len = 0;
    getcwd(wd_path, wd_len);
    sprintf(owner, "%d", getpid());

    return logger_allocate(10, owner, wd_path);
}

size_t	logger_allocate(size_t flszmb, const char* mname, const char* dirpath)
{
    size_t index = 0;
    while(loggers[index] != NULL) { index++; }

    loggers[index] = (Logger*)calloc(1, sizeof(Logger));

    if(loggers[index] == NULL)
    {
        return -1;
    }

    loggers[index]->PID = getpid();

    loggers[index]->IsOpen = false;
    loggers[index]->FileHandle = NULL;

    if(flszmb < 1 || flszmb > 10)
    {
        flszmb = 10;
    }

    loggers[index]->LogFileSizeMB = flszmb;

    if(dirpath != NULL)
    {
        if(!dir_is_exists(dirpath))
        {
            dir_create_directory(dirpath);
        }

        strcat(loggers[index]->FileName, dirpath);
    }
    else
    {
        char wd_path[1025] = { 0 };
        int wd_len = 0;
        getcwd(wd_path, wd_len);
        strcat(loggers[index]->FileName, wd_path);
    }

    if(mname != NULL)
    {
        strcat(loggers[index]->FileName, mname);
    }
    else
    {
        char owner[33] = { 0 };
        sprintf(owner, "%d", getpid());
        strcat(loggers[index]->FileName, owner);
    }

    strcat(loggers[index]->FileName, ".log");

    return index;
}

void logger_release(size_t loggerid)
{
    if(loggers[loggerid] == NULL)
    {
        return;
    }

    if(loggers[loggerid]->IsOpen)
    {
        fflush(loggers[loggerid]->FileHandle);
        fclose(loggers[loggerid]->FileHandle);
    }

    free(loggers[loggerid]);
}

void logger_start_logging(size_t loggerid)
{
    if(loggers[loggerid] == NULL)
    {
        return;
    }

   loggers[loggerid]->FileHandle = fopen(loggers[loggerid]->FileName, "w");

   if(loggers[loggerid]->FileHandle != NULL)
   {
       loggers[loggerid]->IsOpen = true;
   }

   return;
}

void logger_stop_logging(size_t loggerid)
{
    if(loggers[loggerid] == NULL)
    {
        return;
    }
    
    if(loggers[loggerid]->IsOpen)
    {
        fflush(loggers[loggerid]->FileHandle);
        fclose(loggers[loggerid]->FileHandle);
        loggers[loggerid]->IsOpen = false;
    }
}

void logger_write(size_t loggerid, const char* logentry, LogLevel llevel, const char* func, const char* file, int line)
{
    if(loggers[loggerid] == NULL)
    {
        return;
    }

    // Check the file size
    size_t sz = ftell(loggers[loggerid]->FileHandle);

    // If it exceeds the set size
    if(sz*1024*1024 >= loggers[loggerid]->LogFileSizeMB)
    {
        // Stop logging
        logger_stop_logging(loggers[loggerid]);

        // Rename the file
        char old_log_filename[1025] = {0};
        strcat(old_log_filename, loggers[loggerid]->FileName);
        strcat(old_log_filename, ".old");

        int rc = rename(loggers[loggerid]->FileName, old_log_filename);

        // Reopen the log file with original name
        logger_start_logging(loggers[loggerid]);
    }
}

size_t logger_get_instance()
{
    return 0;
}

