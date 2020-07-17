#ifndef _CONFIGURATION
#define _CONFIGURATION

#include <string>
#include <fstream>
#include <map>

namespace CoreLib
{
	class Configuration
	{
	public:
		Configuration();
		~Configuration();
		void SetFileName(std::string fname);
		bool LoadConfiguration(const std::string &configFile);
		bool LoadConfiguration();
		std::string GetValue(const std::string &section, const std::string &settingKey, const std::string defval = "");
		bool IsSection(const std::string &section);
	private:
		void AddSection(std::string &str, const std::map<std::string, std::string> &list);
		std::map<std::string, std::map<std::string, std::string>> _Configuration;
		std::string _ConfigFileName;
	};
}
#endif
