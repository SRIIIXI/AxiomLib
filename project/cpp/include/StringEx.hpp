#ifndef _STRING_EX
#define _STRING_EX

#include <string>
#include <list>
#include <vector>
#include <sstream>

void strsplit(const std::string &str, std::vector<std::string> &tokens, const std::string &delimiters = " ", bool trim = false);
void strsplit(const std::string &str, std::vector<std::string> &tokens, char delim=' ', bool trim = false);
void strsplit(const std::string &str, std::list<std::string> &tokens, const std::string &delimiters = " ", bool trim = false);
void strsplit(const std::string &str, std::list<std::string> &tokens, char delim=' ', bool trim = false);
void strsplit(const std::string &str, char delim, std::string &keystr, std::string &valuestr, bool trim = false);
size_t strsplit(const std::string &str, const std::string &delim, std::string &keystr, std::string &valuestr, bool trim = false);

void strreplace(std::string &srcstr, const std::string &oldpattern, const char newchar);
void strreplace(std::string &srcstr, const std::string& oldpattern, const std::string &newpattern);
void strreplace(std::string &srcstr, const char oldchar, const char newchar);
void strremove(std::string &srcstr, const char oldchar);

void stralltrim(std::string &str);
bool charisspace(int in);

size_t strcharcount(const std::string& str, char ch);
size_t strsubstringpos(const std::string& str, const std::string& substr);
size_t strcharacterpos(const std::string& str,const char ch);

bool strcontains(const std::string& str, const std::string& substr);
bool strcontains(const std::string& str, const char ch);

void strlower(std::string &srcstr);
void strupper(std::string &srcstr);

void strrealtostring(std::string &str, const double val);
void strtimestamp(std::string &srcstr);

int strextractint(const std::string &str, size_t pos, size_t len);
int strextractint(const std::string& str);

#endif

