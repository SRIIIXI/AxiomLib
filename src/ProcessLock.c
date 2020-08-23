/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#include "ProcessLock.h"
#include "StringEx.h"
#include "StringList.h"
#include "Directory.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

char* process_lock_get_current_process_name(char* ptr)
{
    if(ptr == NULL)
    {
        return NULL;
    }

    char buffer[1025] = {0};
    pid_t proc_id = getpid();
    void* cmd_args = NULL;
    void* dir_tokens = NULL;

    sprintf(buffer, "/proc/%d/cmdline", proc_id);

    FILE* fp = fopen(buffer, "r");

    if(fp)
    {
        memset(buffer, 0, 1025);

        if(fgets(buffer, 1024, fp))
        {
            cmd_args = str_list_allocate_from_string(cmd_args, buffer, " ");

            if(cmd_args && str_list_item_count(cmd_args) > 0)
            {
                str_list_allocate_from_string(dir_tokens, str_list_get_first(cmd_args), "/");

                if(dir_tokens && str_list_item_count(dir_tokens) > 0)
                {
                    strcpy(ptr, str_list_get_last(dir_tokens));
                }
            }
            else
            {
                dir_tokens = str_list_allocate_from_string(dir_tokens, buffer, "/");

                if(dir_tokens && str_list_item_count(dir_tokens) > 0)
                {
                    strcpy(ptr, str_list_get_last(dir_tokens));
                }
            }
        }

        fclose(fp);
    }

    if(cmd_args)
    {
        str_list_clear(cmd_args);
    }

    if(dir_tokens)
    {
        str_list_clear(dir_tokens);
    }

    return ptr;
}

char* process_lock_get_current_user_name()
{
    return getenv("USER");
}

char* process_lock_get_lock_filename()
{
    char* lock_filename = (char*)calloc(1, 1025);
    char process_name[64] = {0};

    char temp[33] = {0};

    strcat(lock_filename, dir_get_temp_directory(temp));
    strcat(lock_filename, "/");
    strcat(lock_filename, process_lock_get_current_process_name(process_name));
    strcat(lock_filename, ".");
    strcat(lock_filename, process_lock_get_current_user_name());
    strcat(lock_filename, ".lock");

    return  lock_filename;
}

bool process_lock_lock(const char* lock_filename)
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
