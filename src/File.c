/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#include "File.h"

#define DIRECTORY_SEPARATOR '/'
#include <sys/stat.h>

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

bool file_is_exists(const char* filename)
{
	FILE* fp = fopen(filename, "r");

	if(fp)
	{
		fclose(fp);
		return true;
	}

	return false;
}

char* file_get_parent_directory(const char* filename)
{
	size_t origlen = strlen(filename);

	char* parent_dir = (char*)calloc(1, sizeof(char) * (origlen + 1));

	if(parent_dir == NULL)
	{
		return NULL;
	}

	memcpy(parent_dir, filename, origlen);

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

char* file_get_basename(const char* filename)
{
	size_t origlen = strlen(filename);
	size_t index = 0;

	char* basename = (char*)calloc(1, sizeof(char) * (origlen + 1));

	if(basename == NULL)
	{
		return NULL;
	}

	for(index = origlen - 1; filename[index] != '/' && filename[index] != '\\'; index--) { }

	memcpy(basename, &filename[index + 1], index);

	return basename;
}

char* file_get_extension(const char* filename)
{
    size_t origlen = strlen(filename);
    size_t index = 0;

    char* extension = (char*)calloc(1, sizeof(char) * (origlen + 1));

    if(extension == NULL)
    {
        return NULL;
    }

    for(index = origlen - 1; filename[index] != '.'; index--) { }

    memcpy(extension, &filename[index+1], index-1);

    return extension;
}
