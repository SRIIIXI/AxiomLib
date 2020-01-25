#ifndef __STRING
#define __STRING

#include "List.hpp"

namespace CoreLib
{
	class StringList;

	class String
	{
	public:
		String();
		String(size_t len);
		String(const String &obj);
		String(const String *ptr);
		String(const char* ptr);
		String(const wchar_t* ptr);
		String(const char* ptr, size_t startpos, size_t endpos);
		~String();

		size_t length() const;
		void clear();
		void assign(const char *ptr);
		void assign(const char *ptr, size_t startpos, size_t endpos);
		const char* buffer() const;
		size_t indexOf(const String &obj, size_t startpos = 0) const;
		size_t indexOf(const char* ptr, size_t startpos = 0) const;
		size_t indexOf(const char ch, size_t startpos = 0) const;
		void getSubString(size_t pos, size_t len, String &substr) const;

		int getInt(size_t pos, size_t len) const;
		long getLong(size_t pos, size_t len) const;
		long long getLongLong(size_t pos, size_t len) const;
		unsigned int getUnsignedInt(size_t pos, size_t len) const;
		unsigned long getUnsignedLong(size_t pos, size_t len) const;
		unsigned long long getUnsignedLongLong(size_t pos, size_t len) const;
		double getDouble(size_t pos, size_t len) const;

		int getInt() const;
		long getLong() const;
		long long getLongLong() const;
		unsigned int getUnsignedInt() const;
		unsigned long getUnsignedLong() const;
		unsigned long long getUnsignedLongLong() const;
		double getDouble() const;

		size_t countOf(const String &obj) const;
		size_t countOf(const char* ptr) const;
		size_t countOf(const char ch) const;

		void toLower();
		void toUpper();
		void leftTrim();
		void rightTrim();
		void trim();
		void reverse();
		void reverse(size_t start, size_t len);

		void replace(const String &oldpattern, const String &newpattern);
		void replace(const char oldchar, const char newchar);
		void replace(const String &oldpattern, const long npattern);
		void replace(const String &oldpattern, const double npattern);
		void replace(const String &oldpattern, const int npattern);

		void remove(const String &oldpattern);
		void remove(const char oldchar);
		void removeAll(const char oldchar);
		bool removeFirst(const char oldchar);
		void removeAt(size_t pos, size_t len);

		void getKeyValuePair(String &key, String &value, const char delimiter);
		void getKeyValuePair(String &key, String &value, const String &delimiter);

		void getSubStringList(List<String> &tokens, const char delimiter = ' ');
		void getSubStringList(List<String> &tokens, const String &delimiter = " ");

		char getAt(const size_t atpos) const;
		void SetAt(const size_t atpos, const char ch);

		wchar_t* toWideCharacter();

		static void join(List<String> &tokens, String &newString, const char delimiter = ' ');
		static void join(List<String> &tokens, String &newString, const String &delimiter = " ");

		void operator=(const String& other);
		bool operator!=(const String& other);
		bool operator==(const String& other);
		bool operator>(const String& other);
		bool operator<(const String& other);

		String& operator+=(const String& other);
		String& operator+=(const char& other);
		String& operator+=(const int& other);
		String& operator+=(const long& other);
		String& operator+=(const double& other);

		String operator+(const String& other);
		String operator+(const char& other);
		String operator+(const int& other);
		String operator+(const long& other);
		String operator+(const double& other);

		char& operator[](const size_t index);
	private:
		char*	_Buffer;
		size_t	_BufferLen;
		size_t	_StringLen;
	};
}

#endif
