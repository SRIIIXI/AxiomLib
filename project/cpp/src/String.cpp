#include "String.hpp"
#include "Base64.hpp"
#include <ctype.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

namespace CoreLib
{
#if defined(_WIN32) || defined(WIN32) || defined (_WIN64) || defined (WIN64)
#define strtoull(str, endptr, base) _strtoui64(str, endptr, base)
#endif

	const size_t PAGE_SIZE = 1024 * sizeof(void*);
	size_t numPages(size_t x);

	String::String()
	{
		_Buffer = nullptr;
		_BufferLen = 0;
		_StringLen = 0;

		_BufferLen = PAGE_SIZE;
		
		_Buffer = new char[_BufferLen];
		memset(_Buffer, 0, _BufferLen);
	}

	String::String(size_t len)
	{
		_StringLen = len;
		_BufferLen = numPages(_StringLen + 1)*PAGE_SIZE;
		_Buffer = new char[_BufferLen];
		memset(_Buffer, 0, _BufferLen);
	}

	String::String(const String &obj)
	{
		if (obj._StringLen > 0 && obj._Buffer != nullptr)
		{
			_StringLen = obj._StringLen;
			_BufferLen = obj._BufferLen;
			_Buffer = new char[_BufferLen];
			memset(_Buffer, 0, _BufferLen);
			strcpy(_Buffer, obj._Buffer);
		}
	}

	String::String(const String *ptr)
	{
		if (ptr != nullptr)
		{
			if (ptr->_StringLen > 0 && ptr->_Buffer != nullptr)
			{
				_StringLen = ptr->_StringLen;
				_BufferLen = ptr->_BufferLen;
				_Buffer = new char[_BufferLen];
				memset(_Buffer, 0, _BufferLen);
				strcpy(_Buffer, ptr->_Buffer);
			}
		}
	}

	String::String(const wchar_t* ptr)
	{
		if (ptr != nullptr)
		{
			for (_StringLen = 0; ptr[_StringLen] != '\0'; _StringLen++) {}

			_BufferLen = numPages(_StringLen + 1)*PAGE_SIZE;
			_Buffer = new char[_BufferLen];
			memset(_Buffer, 0, _BufferLen);

			for (int idx = 0; idx < _StringLen; idx++)
			{
				_Buffer[idx] = ptr[idx];
			}
		}
	}

	String::String(const char* ptr)
	{
		if (ptr != nullptr)
		{
			_StringLen = strlen(ptr);
			_BufferLen = numPages(_StringLen + 1)*PAGE_SIZE;
			_Buffer = new char[_BufferLen];
			memset(_Buffer, 0, _BufferLen);
			strcpy(_Buffer, ptr);
		}
	}

	String::String(const char* ptr, size_t startpos, size_t endpos)
	{
		if (ptr != nullptr)
		{
			_StringLen = endpos - startpos;
			_BufferLen = numPages(_StringLen + 1)*PAGE_SIZE;
			_Buffer = new char[_BufferLen];
			memset(_Buffer, 0, _BufferLen);
			strcpy(_Buffer, &ptr[startpos]);
		}
	}

	String::~String()
	{
		if (_Buffer != nullptr)
		{
			delete[]_Buffer;
			_Buffer = nullptr;
		}

		_BufferLen = 0;
		_StringLen = 0;
	}

	bool String::operator!=(const String& other)
	{
		int complen = (_StringLen > other._StringLen) ? other._StringLen : _StringLen;

		if (strcmp(_Buffer, other._Buffer) != 0)
		{
			return true;
		}

		return false;
	}

	bool String::operator==(const String& other)
	{
		int complen = (_StringLen > other._StringLen) ? other._StringLen : _StringLen;

		if (strcmp(_Buffer, other._Buffer) == 0)
		{
			return true;
		}

		return false;
	}

	bool String::operator>(const String& other)
	{
		int complen = (_StringLen > other._StringLen) ? other._StringLen : _StringLen;

		if (strcmp(_Buffer, other._Buffer) > 0)
		{
			return true;
		}

		return false;
	}

	bool String::operator<(const String& other)
	{
		int complen = (_StringLen > other._StringLen) ? other._StringLen : _StringLen;

		if (strcmp(_Buffer, other._Buffer) < 0)
		{
			return true;
		}

		return false;
	}

	void String::operator=(const String& other)
	{
		clear();
		_StringLen = other._StringLen;
		_BufferLen = other._BufferLen;
		_Buffer = new char[_BufferLen];
		memset(_Buffer, 0, _BufferLen);
		strcpy(_Buffer, other._Buffer);
		_Buffer[_StringLen] = 0;

		return;
	}

	String& String::operator+=(const String& other)
	{
		size_t len = _StringLen + other._StringLen;

		if (len < _BufferLen)
		{
			strcpy(_Buffer + _StringLen, other._Buffer);
			_StringLen = len;
		}
		else
		{
			size_t bufferlen = numPages(len + 1)*PAGE_SIZE;
			char *buffer = new char[bufferlen];
			memset(buffer, 0, bufferlen);
			strcpy(buffer, _Buffer);
			strcpy(buffer + _StringLen, other._Buffer);

			_StringLen = len;
			_BufferLen = bufferlen;
			delete[]_Buffer;
			_Buffer = buffer;
		}

		return *this;
	}

	String& String::operator+=(const char& other)
	{
		size_t len = _StringLen + 1;

		if (len < _BufferLen)
		{
			_Buffer[_StringLen] = other;
			_StringLen++;
			_Buffer[_StringLen] = '\0';
		}
		else
		{
			size_t bufferlen = numPages(len + 1)*PAGE_SIZE;
			char *buffer = new char[bufferlen];
			memset(buffer, 0, bufferlen);
			strcpy(buffer, _Buffer);
			_Buffer[_StringLen] = other;

			_StringLen++;
			_BufferLen = bufferlen;
			delete[]_Buffer;
			_Buffer = buffer;
		}

		return *this;
	}

	String& String::operator+=(const long& other)
	{
		char tempbuffer[32] = { 0 };
		sprintf(tempbuffer, "%lld", (long long)other);

		int len = _StringLen + strlen(tempbuffer);

		if (len < _BufferLen)
		{
			strcpy(_Buffer + _StringLen, tempbuffer);
			_StringLen = len;
		}
		else
		{
			int bufferlen = numPages(len + 1)*PAGE_SIZE;
			char *buffer = new char[bufferlen];
			memset(buffer, 0, bufferlen);
			strcpy(buffer, _Buffer);
			strcpy(buffer + _StringLen, tempbuffer);

			_StringLen = len;
			_BufferLen = bufferlen;
			delete[]_Buffer;
			_Buffer = buffer;
		}

		return *this;
	}

	String& String::operator+=(const int& other)
	{
		char tempbuffer[32] = { 0 };
		sprintf(tempbuffer, "%lld", (long long)other);

		int len = _StringLen + strlen(tempbuffer);

		if (len < _BufferLen)
		{
			strcpy(_Buffer + _StringLen, tempbuffer);
			_StringLen = len;
		}
		else
		{
			int bufferlen = numPages(len + 1)*PAGE_SIZE;
			char *buffer = new char[bufferlen];
			memset(buffer, 0, bufferlen);
			strcpy(buffer, _Buffer);
			strcpy(buffer + _StringLen, tempbuffer);

			_StringLen = len;
			_BufferLen = bufferlen;
			delete[]_Buffer;
			_Buffer = buffer;
		}

		return *this;
	}

	String& String::operator+=(const double& other)
	{
		char tempbuffer[32] = { 0 };
		sprintf(tempbuffer, "%f", (double)other);

		size_t len = _StringLen + strlen(tempbuffer);

		if (len < _BufferLen)
		{
			strcpy(_Buffer + _StringLen, tempbuffer);
			_StringLen = len;
		}
		else
		{
			size_t bufferlen = numPages(len + 1)*PAGE_SIZE;
			char *buffer = new char[bufferlen];
			memset(buffer, 0, bufferlen);
			strcpy(buffer, _Buffer);
			strcpy(buffer + _StringLen, tempbuffer);

			_StringLen = len;
			_BufferLen = bufferlen;
			delete[]_Buffer;
			_Buffer = buffer;
		}

		return *this;
	}

	String String::operator+(const String& other)
	{
		String returnvalue;

		returnvalue._StringLen = _StringLen + other._StringLen;
		returnvalue._BufferLen = numPages(returnvalue._StringLen + 1)*PAGE_SIZE;
		returnvalue._Buffer = new char[returnvalue._BufferLen];
		memset(returnvalue._Buffer, 0, returnvalue._BufferLen);
		strcpy(returnvalue._Buffer, _Buffer);
		strcpy(returnvalue._Buffer + _StringLen, other._Buffer);

		return returnvalue;
	}

	String String::operator+(const char& other)
	{
		String returnvalue;

		returnvalue._StringLen = _StringLen + 1;
		returnvalue._BufferLen = numPages(returnvalue._StringLen + 1)*PAGE_SIZE;
		returnvalue._Buffer = new char[returnvalue._BufferLen];
		memset(returnvalue._Buffer, 0, returnvalue._BufferLen);
		strcpy(returnvalue._Buffer, _Buffer);
		returnvalue._Buffer[_StringLen] = other;

		return returnvalue;
	}

	String String::operator+(const long& other)
	{
		char tempbuffer[32] = { 0 };
		sprintf(tempbuffer, "%lld", (long long)other);

		String returnvalue;

		returnvalue._StringLen = _StringLen + strlen(tempbuffer);
		returnvalue._BufferLen = numPages(returnvalue._StringLen + 1)*PAGE_SIZE;
		returnvalue._Buffer = new char[returnvalue._BufferLen];
		memset(returnvalue._Buffer, 0, returnvalue._BufferLen);
		strcpy(returnvalue._Buffer, _Buffer);
		strcpy(returnvalue._Buffer + _StringLen, tempbuffer);

		return returnvalue;
	}

	String String::operator+(const int& other)
	{
		char tempbuffer[32] = { 0 };
		sprintf(tempbuffer, "%lld", (long long)other);

		String returnvalue;

		returnvalue._StringLen = _StringLen + strlen(tempbuffer);
		returnvalue._BufferLen = numPages(returnvalue._StringLen + 1)*PAGE_SIZE;
		returnvalue._Buffer = new char[returnvalue._BufferLen];
		memset(returnvalue._Buffer, 0, returnvalue._BufferLen);
		strcpy(returnvalue._Buffer, _Buffer);
		strcpy(returnvalue._Buffer + _StringLen, tempbuffer);

		return returnvalue;
	}

	String String::operator+(const double& other)
	{
		char tempbuffer[32] = { 0 };
		sprintf(tempbuffer, "%f", (double)other);

		String returnvalue;

		returnvalue._StringLen = _StringLen + strlen(tempbuffer);
		returnvalue._BufferLen = numPages(returnvalue._StringLen + 1)*PAGE_SIZE;
		returnvalue._Buffer = new char[returnvalue._BufferLen];
		memset(returnvalue._Buffer, 0, returnvalue._BufferLen);
		strcpy(returnvalue._Buffer, _Buffer);
		strcpy(returnvalue._Buffer + _StringLen, tempbuffer);

		return returnvalue;
	}

	char String::getAt(const size_t atpos) const
	{
		return _Buffer[atpos];
	}

	void String::SetAt(const size_t atpos, const char ch)
	{
		_Buffer[atpos] = ch;
	}

	char& String::operator[](const size_t index)
	{
		if (index < 0 || index >(_StringLen - 1))
		{
			throw;
		}

		return _Buffer[index];
	}

	wchar_t* String::toWideCharacter()
	{
		return nullptr;
	}

	void String::clear()
	{
		if(_BufferLen > PAGE_SIZE)
		{ 
			if (_Buffer != nullptr)
			{
				_Buffer = nullptr;
			}

			_BufferLen = PAGE_SIZE;
			_Buffer = new char[_BufferLen];
		}

		_StringLen = 0;
		memset(_Buffer, 0, _BufferLen);
	}

	void String::assign(const char *ptr)
	{
		if (ptr != nullptr)
		{
			clear();
			_StringLen = strlen(ptr);
			_BufferLen = numPages(_StringLen + 1)*PAGE_SIZE;
			_Buffer = new char[_BufferLen];
			memset(_Buffer, 0, _BufferLen);
			strcpy(_Buffer, ptr);
		}
	}

	void String::assign(const char *ptr, size_t startpos, size_t endpos)
	{
		if (ptr != nullptr)
		{
			clear();
			_StringLen = endpos - startpos;
			_BufferLen = numPages(_StringLen + 1)*PAGE_SIZE;
			_Buffer = new char[_BufferLen];
			memset(_Buffer, 0, _BufferLen);
			strcpy(_Buffer, &ptr[startpos]);
		}
	}

	size_t String::length() const
	{
		return _StringLen;
	}

	const char* String::buffer() const
	{
		return _Buffer;
	}

	size_t String::indexOf(const String &obj, size_t startpos) const
	{
		return indexOf(obj._Buffer, startpos);
	}

	size_t String::indexOf(const char* ptr, size_t startpos) const
	{
		int result = -1;

		if (ptr != nullptr)
		{

			char* pdest = (char*)strstr(_Buffer + startpos, (char*)ptr);

			if (pdest == 0)
			{
				return -1;
			}

			result = pdest - _Buffer;
		}

		return result;
	}

	size_t String::indexOf(const char ch, size_t startpos) const
	{
		for (int ctr = startpos; _Buffer[ctr] != '\0'; ctr++)
		{
			if (_Buffer[ctr] == ch)
			{
				return ctr;
			}
		}

		return -1;
	}

	void String::getSubString(size_t pos, size_t len, String &substr) const
	{
		if (_StringLen - pos < len)
		{
			len = _StringLen - pos;
		}

		char* ptr = new char[len + 1];
		memset(ptr, 0, len + 1);
		strcpy(_Buffer + pos, ptr);
		substr.assign(ptr);
		delete[]ptr;
	}

	int String::getInt(size_t pos, size_t len) const
	{
		if (_StringLen - pos < len)
		{
			len = _StringLen - pos;
		}

		String str;

		str.assign(_Buffer, pos, pos + len);
		int res = atoi(str._Buffer);
		return res;
	}

	long String::getLong(size_t pos, size_t len) const
	{
		if (_StringLen - pos < len)
		{
			len = _StringLen - pos;
		}

		String str;

		str.assign(_Buffer, pos, pos + len);
		long res = atol(str._Buffer);
		return res;
	}

	long long String::getLongLong(size_t pos, size_t len) const
	{
		if (_StringLen - pos < len)
		{
			len = _StringLen - pos;
		}

		String str;

		str.assign(_Buffer, pos, pos + len);
		long long res = strtoull(str._Buffer, NULL, 0);
		return res;
	}

	unsigned int String::getUnsignedInt(size_t pos, size_t len) const
	{
		return (unsigned int)getInt(pos, len);
	}

	unsigned long String::getUnsignedLong(size_t pos, size_t len) const
	{
		return (unsigned long)getLong(pos, len);
	}

	unsigned long long String::getUnsignedLongLong(size_t pos, size_t len) const
	{
		return (unsigned long long)getLongLong(pos, len);
	}


	double String::getDouble(size_t pos, size_t len) const
	{
		if (_StringLen - pos < len)
		{
			len = _StringLen - pos;
		}

		String str;

		str.assign(_Buffer, pos, pos + len);
		double res = atof(str._Buffer);
		return res;
	}

	int String::getInt() const
	{
		return getInt(0, _StringLen);
	}

	long String::getLong() const
	{
		return getLong(0, _StringLen);
	}

	long long String::getLongLong() const
	{
		return getLongLong(0, _StringLen);
	}

	unsigned int String::getUnsignedInt() const
	{
		return getUnsignedInt(0, _StringLen);
	}

	unsigned long String::getUnsignedLong() const
	{
		return getUnsignedLong(0, _StringLen);
	}

	unsigned long long String::getUnsignedLongLong() const
	{
		return getUnsignedLongLong(0, _StringLen);
	}

	double String::getDouble() const
	{
		return getDouble(0, _StringLen);
	}

	size_t String::countOf(const String &obj) const
	{
		return countOf(obj._Buffer);
	}

	size_t String::countOf(const char* ptr) const
	{
		int count = 0;

		char* str = &_Buffer[0];

		char* token = strtok(str, ptr);

		while (token != nullptr)
		{
			count++;

			token = strtok(NULL, ptr);
		}

		return count;
	}

	size_t String::countOf(const char ch) const
	{
		size_t c = 0;
		for (size_t i = 0; _Buffer[i] != '\0'; i++)
		{
			if (_Buffer[i] == ch)
			{
				c++;
			}
		}

		return c;
	}

	void String::toLower()
	{
		for (size_t ctr = 0; _Buffer[ctr] != '\0'; ctr++)
		{
			if (_Buffer[ctr] >= 65 && _Buffer[ctr] <= 90)
			{
				_Buffer[ctr] = _Buffer[ctr] + 32;
			}
		}
	}

	void String::toUpper()
	{
		for (size_t ctr = 0; _Buffer[ctr] != '\0'; ctr++)
		{
			if (_Buffer[ctr] >= 97 && _Buffer[ctr] <= 122)
			{
				_Buffer[ctr] = _Buffer[ctr] - 32;
			}
		}
	}

	void String::leftTrim()
	{
		char *ptr = _Buffer;

		int ctr = 0;

		int trimlen = 0;

		while (isspace(*ptr))
		{
			ptr++;
			trimlen++;
		}

		while (*ptr)
		{
			_Buffer[ctr] = *ptr;
			ctr++;
			ptr++;
		}
		_Buffer[ctr] = '\0';
		_StringLen -= trimlen;
	}

	void String::rightTrim()
	{
		for (int ctr = _StringLen - 1; ctr > -1; ctr--)
		{
			if (isspace(_Buffer[ctr]))
			{
				_Buffer[ctr] = '\0';
			}
			else
			{
				break;
			}
		}
	}

	void String::trim()
	{
		rightTrim();
		leftTrim();
	}

	void String::replace(const String &oldpattern, const String &newpattern)
	{
		int substrpos = 0;
		int diff = newpattern._StringLen - oldpattern._StringLen;

		if (diff >= 0)
		{
			int count = countOf(oldpattern);
			int oldlen = _StringLen;

			int newstringlen = count*diff + _StringLen;
			int newbufferlen = numPages(_StringLen + 1)*PAGE_SIZE;

			if (newbufferlen > _BufferLen)
			{
				_BufferLen = newbufferlen;
				char *ptr = new char[_BufferLen];
				memset(ptr, 0, _BufferLen);
				strcpy(ptr, _Buffer);
				delete[]_Buffer;
				_Buffer = ptr;
			}
		}

		while (true)
		{
			substrpos = indexOf(oldpattern);

			if (substrpos == -1)
			{
				break;
			}

			memmove(_Buffer + substrpos + newpattern._StringLen, _Buffer + substrpos + oldpattern._StringLen, _StringLen + diff);
			strcpy(_Buffer + substrpos, newpattern._Buffer);
		}

		_StringLen = strlen(_Buffer);
	}

	void String::replace(const char oldchar, const char newchar)
	{
		for (int ctr = 0; _Buffer[ctr] != '\0'; ctr++)
		{
			if (_Buffer[ctr] == oldchar)
			{
				_Buffer[ctr] = newchar;
			}
		}
	}

	void String::replace(const String &oldpattern, const long npattern)
	{
		char buffer[32] = { 0 };
		sprintf(buffer, "%lld", (long long)npattern);
		replace(oldpattern, buffer);
	}

	void String::replace(const String &oldpattern, const double npattern)
	{
		char buffer[32] = { 0 };
		sprintf(buffer, "%f", (double)npattern);
		replace(oldpattern, buffer);
	}

	void String::replace(const String &oldpattern, const int npattern)
	{
		char buffer[32] = { 0 };
		sprintf(buffer, "%lld", (long long)npattern);
		replace(oldpattern, buffer);
	}

	void String::remove(const String &oldpattern)
	{
		int idxToDel = -1;

		while (true)
		{
			idxToDel = indexOf(oldpattern);

			if (idxToDel < 0)
			{
				break;
			}

			memmove(&_Buffer[idxToDel], &_Buffer[idxToDel + oldpattern._StringLen], _StringLen - idxToDel);
			_Buffer[_StringLen - oldpattern._StringLen] = 0;
			_StringLen = _StringLen - oldpattern._StringLen;
		}
	}

	void String::remove(const char oldchar)
	{
		int idxToDel = -1;

		while (true)
		{
			idxToDel = indexOf(oldchar);

			if (idxToDel < 0)
			{
				break;
			}

			memmove(&_Buffer[idxToDel], &_Buffer[idxToDel + 1], _StringLen - idxToDel);
			_Buffer[_StringLen - 1] = 0;
			_StringLen--;
		}
	}

	bool String::removeFirst(const char oldchar)
	{
		int ctr = 0;

		bool found = false;

		for (; _Buffer[ctr] != '\0'; ctr++)
		{
			if (_Buffer[ctr] == oldchar)
			{
				found = true;
				break;
			}
		}

		if (found)
		{
			for (; _Buffer[ctr] != '\0'; ctr++)
			{
				_Buffer[ctr] = _Buffer[ctr + 1];
			}
		}

		return found;
	}

	void String::removeAll(const char oldchar)
	{
		while (removeFirst(oldchar)) {}
	}

	void String::removeAt(size_t pos, size_t len)
	{
		memmove(&_Buffer[pos], &_Buffer[pos + len], _StringLen - len);
		_Buffer[_StringLen - len] = 0;
		_StringLen = _StringLen - len;
	}

	void String::getKeyValuePair(String &key, String &value, const char delimiter)
	{
		size_t pos = indexOf(delimiter);

		if (pos < 0)
			return;

		if ((pos - 0) > 0)
			key.assign(_Buffer, 0, pos);

		if (((_StringLen - 1) - (pos + 1)) > 0)
			value.assign(_Buffer, pos + 1, _StringLen - 1);
	}

	void String::getKeyValuePair(String &key, String &value, const String &delimiter)
	{
		size_t pos = indexOf(delimiter);

		if (pos > 0)
		{
			key.assign(_Buffer, 0, pos);
			value.assign(_Buffer, pos + delimiter._StringLen, _StringLen);
		}
	}

	void String::getSubStringList(List<String> &tokens, const char delimiter)
	{
		size_t delimpos = -1;
		size_t offset = 1;
		size_t startpos = 0;

		while (true)
		{
			delimpos = indexOf(delimiter, startpos);

			if (delimpos == -1)
			{
				if (_StringLen > startpos)
				{
					tokens.append(String(_Buffer, startpos, _StringLen));
				}

				break;
			}

			if ((delimpos != 0) && (delimpos >= startpos) && (delimpos != (_StringLen - 1)))
			{
				tokens.append(String(_Buffer, startpos, delimpos));
			}

			startpos = delimpos + offset;
		}
	}

	void String::getSubStringList(List<String> &tokens, const String &delimiter)
	{
		size_t delimpos = -1;
		size_t offset = delimiter._StringLen;
		size_t startpos = 0;

		while (true)
		{
			delimpos = indexOf(delimiter, startpos);

			if (delimpos == -1)
			{
				if (_StringLen > startpos)
				{
					tokens.append(String(_Buffer, startpos, _StringLen));
				}

				break;
			}

			if ((delimpos != 0) && (delimpos >= startpos) && (delimpos != (_StringLen - 1)))
			{
				tokens.append(String(_Buffer, startpos, delimpos));
			}

			startpos = delimpos + offset;
		}
	}

	void String::join(List<String> &tokens, String &newString, const char delimiter)
	{
		size_t count = tokens.count();

		for (size_t idx = 0; idx < count; idx++)
		{
			newString += tokens.getAt(idx);

			if (idx < count - 1)
			{
				newString += delimiter;
			}
		}
	}

	void String::join(List<String> &tokens, String &newString, const String &delimiter)
	{
		size_t count = tokens.count();

		for (size_t idx = 0; idx < count; idx++)
		{
			newString += tokens.getAt(idx);

			if (idx < count - 1)
			{
				newString += delimiter;
			}
		}
	}

	void String::reverse()
	{
		reverse(0, _StringLen);
	}

	void String::reverse(size_t start, size_t len)
	{
		int term = len - 1;

		while (start < term)
		{
			char temp = _Buffer[start];
			_Buffer[start] = _Buffer[term];
			_Buffer[term] = temp;
			start++;
			term--;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	size_t numPages(size_t x)
	{
		size_t d = x / PAGE_SIZE;
		size_t m = x % PAGE_SIZE;

		if (m != 0)
		{
			m = 1;
		}

		return (d + m);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
