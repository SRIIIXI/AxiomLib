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

#include "Configuration.h"
#include "StringEx.h"
#include "Environment.h"
#include "Directory.h"
#include <pthread.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct key_value_t
{
    char* key;
    char* value;
    struct key_value_t* next;
}key_value_t;

typedef struct section_t
{
    char* section_name;
    long key_value_count;
    key_value_t* key_value_list;
    struct section_t* next;
}section_t;

typedef struct configuration_t
{
    long section_count;
    section_t* section_list;
    pthread_mutex_t mutex;
}configuration_t;

void configuration_internal_add_section(configuration_t* conf_ptr, char* section_name);
void configuration_internal_add_key_value(configuration_t* conf_ptr, char* section_name, char* key, char* value);

configuration_t* configuration_allocate_default()
{
    char* path_str = (char*)calloc(1024, sizeof(char));
    path_str = dir_get_config_directory(path_str);

    char* proces_name = (char*)calloc(1024, sizeof(char));
    proces_name = env_get_current_process_name(proces_name);

    strcat(path_str, proces_name);
    strcat(path_str, ".conf");
    free(proces_name);

    configuration_t* ptr = configuration_allocate(path_str);

    free(path_str);

    return ptr;
}

configuration_t* configuration_allocate(const char* filename)
{
    configuration_t* ptr = NULL;
    FILE* fp = fopen(filename, "r");

    if(fp)
    {
        ptr = (configuration_t*)calloc(1, sizeof (configuration_t));
        ptr->section_list = NULL;
        ptr->section_count = 0;
        pthread_mutex_init(&ptr->mutex, 0);

        char current_section[65] = {0};

        while(!feof(fp))
        {
            char buffer[1025] = {0};

            if(fgets(buffer, 1024, fp))
            {
                stralltrim(buffer);

                if(buffer[0] == 0 || buffer[0] == ';' || buffer[0] == '#')
                {
                    continue;
                }

                if(buffer[0] == '[')
                {
                    strremcharfirst(buffer, '[');
                    strremcharfirst(buffer, ']');
                    configuration_internal_add_section(ptr, buffer);
                    memset(current_section, 0, 65);
                    strcpy(current_section, buffer);
                    continue;
                }

                char* key = (char*)calloc(65, sizeof(char));
                char* value = (char*)calloc(513, sizeof(char));

                strsplitkeyvaluechar(buffer, '=', &key, &value);
                stralltrim(key);
                stralltrim(value);

                configuration_internal_add_key_value(ptr, current_section, key, value);
                free(key);
                free(value);
            }
        }
        fclose(fp);
    }

    return ptr;
}

void  configuration_release(configuration_t* config)
{
    return;
}

char**  configuration_get_all_sections(configuration_t* config)
{
    if(config == NULL)
    {
        return NULL;
    }

    char** buffer = NULL;

    buffer = (char **)calloc(1, (unsigned long)(config->section_count + 1) * sizeof(char*));

    if(buffer == NULL)
    {
        return NULL;
    }

    section_t* curr_section = NULL;

    long index = 0;
    for(curr_section = config->section_list; curr_section != NULL; curr_section = curr_section->next)
    {
        long temp_str_len = (long)strlen(curr_section->section_name);

        if(temp_str_len < 1)
        {
            continue;
        }

        buffer[index] = (char*)calloc(1, sizeof(char) * (unsigned long)(temp_str_len + 1));

        if(buffer[index] != NULL)
        {
            strcpy(buffer[index], curr_section->section_name);
        }

        index++;
    }

    return buffer;
}

char**  configuration_get_all_keys(configuration_t* config, const char* section)
{
    return NULL;
}

bool  configuration_has_section(configuration_t* config, const char* section)
{
    return false;
}

bool  configuration_has_key(configuration_t* config, const char* section, char* key)
{
    return false;
}


long  configuration_get_value_as_integer(configuration_t* config, const char* section, const char* key)
{
    return 0;
}

bool  configuration_get_value_as_boolean(configuration_t* config, const char* section, const char* key)
{
    return false;
}

double configuration_get_value_as_real(configuration_t* config, const char* section, const char* key)
{
    return 0;
}

char* configuration_get_value_as_string(configuration_t* config, const char* section, const char* key)
{
    return NULL;
}

void configuration_internal_add_section(configuration_t* conf_ptr, char* section_name)
{
    if(conf_ptr == NULL)
    {
        return;
    }

    section_t* new_section = (section_t*)calloc(1, sizeof(section_t));
    new_section->next = NULL;
    new_section->key_value_list = NULL;
    new_section->key_value_count = 0;
    new_section->section_name = (char*)calloc(1, strlen(section_name)+1);
    strcpy(new_section->section_name, section_name);

    if(conf_ptr->section_list == NULL)
    {
        conf_ptr->section_list = new_section;
    }
    else
    {
        section_t* temp = NULL;
        for(temp = conf_ptr->section_list; temp->next != NULL; temp = temp->next) {}
        temp->next = new_section;
    }

    conf_ptr->section_count++;
}

void configuration_internal_add_key_value(configuration_t* conf_ptr, char* section_name, char* key, char* value)
{
    if(conf_ptr == NULL)
    {
        return;
    }

    section_t* curr_section = NULL;

    for(curr_section = conf_ptr->section_list; curr_section != NULL; curr_section = curr_section->next)
    {
        if(strcmp(curr_section->section_name, section_name) == 0)
        {
            key_value_t* new_kv = (key_value_t*)calloc(1, sizeof (key_value_t));
            new_kv->next = NULL;
            new_kv->key = (char*)calloc(1, strlen(key)+1);
            strcpy(new_kv->key, key);
            new_kv->value = (char*)calloc(1, strlen(value)+1);
            strcpy(new_kv->value, value);

            if(curr_section->key_value_list == NULL)
            {
                curr_section->key_value_list = new_kv;
            }
            else
            {
                key_value_t* temp = NULL;
                for(temp = curr_section->key_value_list; temp->next != NULL; temp = temp->next) {}
                temp->next = new_kv;
            }

            curr_section->key_value_count++;

            break;
        }
    }
}

