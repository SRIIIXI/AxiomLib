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


/*
namespace CoreLib
{
	Configuration::Configuration()
	{
		_ConfigFileName = "";
	}

	Configuration::~Configuration()
	{
	}

	void Configuration::SetFileName(std::string fname)
	{
		_ConfigFileName = fname;
	}

	bool Configuration::IsSection(const std::string &section)
	{
		if (_Configuration.find(section) == _Configuration.end())
		{
			return false;
		}

		return true;
	}

	std::string Configuration::GetValue(const std::string &section, const std::string &settingKey, const std::string defval)
	{
		std::string str = defval;

		if (IsSection(section))
		{
			std::map<std::string, std::string> sub_section = _Configuration[section];

			if (sub_section.find(settingKey) != sub_section.end())
			{
				str = sub_section[settingKey];
			}
		}

		return str;
	}

	bool Configuration::LoadConfiguration(const std::string &configFile)
	{
		_ConfigFileName = configFile;
		return LoadConfiguration();
	}

	bool Configuration::LoadConfiguration()
	{
		std::string line, key, value;
		std::string current_section_header = "";
		std::map<std::string, std::string> kvlist;

		std::ifstream file;

		file.open(_ConfigFileName);

		while (file.good())
		{
			line.clear();
			std::getline(file, line);
			//Section header line
			if (line[0] == '[' && line[line.length() - 1] == ']')
			{
				//Check whether this is the first instance of a section header
				if (_Configuration.size() < 1)
				{
					//Don't need to do anything
					if (current_section_header.length() > 1)
					{
						//We reach here when a section is being read for the first time
						AddSection(current_section_header, kvlist);
					}
				}
				else
				{
					//Before staring a new section parsing we need to store the last one
					AddSection(current_section_header, kvlist);
				}

				//Store the string as current section header and clear the key value list
				current_section_header = line;
				kvlist.clear();
			}
			else
			{
				key = "";
				value = "";
				strsplit(line, '=', key, value);
				kvlist[key] = value;
			}

		}
		AddSection(current_section_header, kvlist);
		file.close();
		return true;
	}

	void Configuration::AddSection(std::string &str, const std::map<std::string, std::string> &list)
	{
		strremove(str, '[');
		strremove(str, ']');
		_Configuration[str] = list;
	}
}
*/

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
    return NULL;
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

}

void configuration_internal_add_key_value(configuration_t* conf_ptr, char* section_name, char* key, char* value)
{

}

