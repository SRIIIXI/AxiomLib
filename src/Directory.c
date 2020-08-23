/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#include "Directory.h"

#define DIRECTORY_SEPARATOR '/'

#include <sys/stat.h>

#include <stdlib.h>
#include <memory.h>
#include <dirent.h>
#include <unistd.h>

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
		if(parent_dir[ctr] == '/' || parent_dir[ctr] == '\\')
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

    pid_t parent = getppid();

    if(parent == 0)
    {
        strcpy(dirname, "/var/log/");
    }
    else
    {
        char wd_path[1025] = { 0 };
        size_t wd_len = 1024;
        getcwd(wd_path, wd_len);
        char* parent_dir = dir_get_parent_directory(wd_path);
        strcat(dirname, parent_dir);
        strcat(dirname, "log/");
        free(parent_dir);
    }

    return dirname;
}

char* dir_get_config_directory(char *dirname)
{
    if(!dirname)
    {
        return NULL;
    }

    char *config_dir = (char*)calloc(2049, 1);
    config_dir = getcwd(config_dir, 2048);

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
        for(int idx = pos; idx <= 2049; idx++)
        {
            config_dir[idx] = 0;
        }
    }

    strcat(config_dir, "etc/");
    strcpy(dirname, config_dir);
    free(config_dir);

    return dirname;
}
