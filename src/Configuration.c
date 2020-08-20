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
