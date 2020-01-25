#include "Buffer.hpp"
#include "Base64.hpp"

#include <memory.h>
#include <string.h>
#include <stdlib.h>

namespace CoreLib
{
	const long PAGE_SIZE = 1024 * sizeof(void*);

	int numMemPages(int x);

	Buffer::Buffer()
	{
		_Buffer = nullptr;
		_BufferLen = 0;
		_DataLen = 0;
	}

	Buffer::Buffer(const Buffer & obj)
	{
		if (obj._DataLen > 0 && obj._Buffer != nullptr)
		{
			_DataLen = obj._DataLen;
			_BufferLen = obj._BufferLen;
			_Buffer = new char[_BufferLen];
			memset(_Buffer, 0, _BufferLen);
			memcpy(_Buffer, obj._Buffer, _DataLen);
		}
	}

	Buffer::Buffer(const wchar_t* ptr, int len)
	{
		if (ptr != nullptr)
		{
			for (_DataLen = 0; _DataLen <= len; _DataLen++) {}

			_BufferLen = numMemPages(_DataLen + 1)*PAGE_SIZE;
			_Buffer = new char[_BufferLen];
			memset(_Buffer, 0, _BufferLen);

			for (int idx = 0; idx < _DataLen; idx++)
			{
				_Buffer[idx] = (char)ptr[idx];
			}
		}
	}

	Buffer::Buffer(const char* ptr, int len)
	{
		if (ptr != nullptr)
		{
			_DataLen = len;
			_BufferLen = numMemPages(_DataLen + 1)*PAGE_SIZE;
			_Buffer = new char[_BufferLen];
			memset(_Buffer, 0, _BufferLen);
			memcpy(_Buffer, ptr, _DataLen);
		}
	}

	Buffer::Buffer(const char* ptr, int startpos, int endpos)
	{
		if (ptr != nullptr)
		{
			_DataLen = endpos - startpos;
			_BufferLen = numMemPages(_DataLen + 1)*PAGE_SIZE;
			_Buffer = new char[_BufferLen];
			memset(_Buffer, 0, _BufferLen);
			memcpy(_Buffer, &ptr[startpos], _DataLen);
		}
	}

	Buffer::~Buffer()
	{
		if (_Buffer != nullptr)
		{
			delete[]_Buffer;
			_Buffer = nullptr;
		}

		_BufferLen = 0;
		_DataLen = 0;
	}

	bool Buffer::operator!=(const Buffer& other)
	{
		int complen = (_DataLen > other._DataLen) ? other._DataLen : _DataLen;

		if (memcmp(_Buffer, other._Buffer, complen) != 0)
		{
			return true;
		}

		return false;
	}

	bool Buffer::operator==(const Buffer& other)
	{
		int complen = (_DataLen > other._DataLen) ? other._DataLen : _DataLen;

		if (memcmp(_Buffer, other._Buffer, complen) == 0)
		{
			return true;
		}

		return false;
	}

	void Buffer::operator=(const Buffer& other)
	{
		clear();

		_DataLen = other._DataLen;
		_BufferLen = other._BufferLen;
		_Buffer = new char[_BufferLen];
		memset(_Buffer, 0, _BufferLen);
		memcpy(_Buffer, other._Buffer, _DataLen);

		return;
	}

	// Check !
	Buffer& Buffer::operator+=(const Buffer& other)
	{
		int len = _DataLen + other._DataLen;

		if (len < _BufferLen)
		{
			memcpy(_Buffer + _DataLen, other._Buffer, other._DataLen);
			_DataLen = len + other._DataLen;
		}
		else
		{
			int bufferlen = numMemPages(len + 1)*PAGE_SIZE;
			char *buffer = new char[bufferlen];
			memset(buffer, 0, bufferlen);
			memcpy(buffer, _Buffer, _DataLen);
			memcpy(buffer + _DataLen, other._Buffer, other._DataLen);

			_DataLen = len;
			_BufferLen = bufferlen;
			delete[]_Buffer;
			_Buffer = buffer;
		}

		return *this;
	}

	// Check !
	Buffer& Buffer::operator+=(const char& other)
	{
		int len = _DataLen + 1;

		if (len < _BufferLen)
		{
			_Buffer[_DataLen] = other;
			_DataLen++;
			_Buffer[_DataLen] = '\0';
		}
		else
		{
			int bufferlen = numMemPages(len + 1)*PAGE_SIZE;
			char *buffer = new char[bufferlen];
			memset(buffer, 0, bufferlen);
			memcpy(buffer, _Buffer, _DataLen);
			_Buffer[_DataLen] = other;

			_DataLen++;
			_BufferLen = bufferlen;
			delete[]_Buffer;
			_Buffer = buffer;
		}

		return *this;
	}

	Buffer Buffer::operator+(const Buffer& other)
	{
		Buffer returnvalue;

		returnvalue._DataLen = _DataLen + other._DataLen;
		returnvalue._BufferLen = numMemPages(returnvalue._DataLen + 1)*PAGE_SIZE;
		returnvalue._Buffer = new char[returnvalue._BufferLen];
		memset(returnvalue._Buffer, 0, returnvalue._BufferLen);
		memcpy(returnvalue._Buffer, _Buffer, _DataLen);
		memcpy(returnvalue._Buffer + _DataLen, other._Buffer, other._DataLen);

		return returnvalue;
	}

	Buffer Buffer::operator+(const char& other)
	{
		Buffer returnvalue;

		returnvalue._DataLen = _DataLen + 1;
		returnvalue._BufferLen = numMemPages(returnvalue._DataLen + 1)*PAGE_SIZE;
		returnvalue._Buffer = new char[returnvalue._BufferLen];
		memset(returnvalue._Buffer, 0, returnvalue._BufferLen);
		memcpy(returnvalue._Buffer, _Buffer, _DataLen);
		returnvalue._Buffer[_DataLen] = other;

		return returnvalue;
	}

	char Buffer::getAt(const int atpos) const
	{
		return _Buffer[atpos];
	}

	void Buffer::SetAt(const int atpos, const char ch)
	{
		_Buffer[atpos] = ch;
	}

	char Buffer::operator[](const long index)
	{
		if (index < 0 || index >(_DataLen - 1))
		{
			return '\0';
		}

		return _Buffer[index];
	}

	void Buffer::clear()
	{
		if (_Buffer != nullptr)
		{
			_Buffer = nullptr;
		}

		_BufferLen = 0;
		_DataLen = 0;
	}

	void Buffer::assign(const char *ptr, int len)
	{
		if (ptr != nullptr)
		{
			clear();
			_DataLen = len;
			_BufferLen = numMemPages(_DataLen)*PAGE_SIZE;
			_Buffer = new char[_BufferLen];
			memset(_Buffer, 0, _BufferLen);
			memcpy(_Buffer, ptr, _DataLen);
		}
	}

	void Buffer::assign(const char *ptr, int startpos, int endpos)
	{
		if (ptr != nullptr)
		{
			clear();
			_DataLen = endpos - startpos;
			_BufferLen = numMemPages(_DataLen + 1)*PAGE_SIZE;
			_Buffer = new char[_BufferLen];
			memset(_Buffer, 0, _BufferLen);
			memcpy(_Buffer, &ptr[startpos], _DataLen);
		}
	}

	int Buffer::length() const
	{
		return _DataLen;
	}

	const char* Buffer::buffer() const
	{
		return _Buffer;
	}

	int Buffer::indexOf(const Buffer &obj, int startpos) const
	{
		return indexOf(obj._Buffer, startpos);
	}

	int Buffer::indexOf(const char* ptr, int startpos) const
	{
		int result = -1;

		if (ptr != nullptr)
		{

			char* pdest = (char*)strstr(_Buffer + startpos, ptr);

			if (pdest == 0)
			{
				return -1;
			}

			result = pdest - _Buffer;
		}

		return result;
	}

	int Buffer::indexOf(const char ch, int startpos) const
	{
		for (int ctr = startpos; ctr <= _DataLen; ctr++)
		{
			if (_Buffer[ctr] == ch)
			{
				return ctr;
			}
		}

		return -1;
	}

	void Buffer::getSubSegment(int pos, int len, Buffer &substr) const
	{
		if (_DataLen - pos < len)
		{
			len = _DataLen - pos;
		}

		char* ptr = new char[size_t(len + 1)];
		memset(ptr, 0, size_t(len + 1));
		memcpy(_Buffer + pos, ptr, len);
		substr.assign(ptr, len);
		delete[]ptr;
	}

	int Buffer::countOf(const Buffer &obj) const
	{
		return countOf(obj._Buffer);
	}

	int Buffer::countOf(const char* ptr) const
	{
		int count = 0;
		int pos = 0;
		int offset = 0;

		for (offset = 0; ptr[offset] != '\0'; offset++) {}

		while (true)
		{
			const char* temp = strstr(&_Buffer[pos], ptr);
			if (temp == nullptr)
			{
				break;
			}

			count++;

			pos = (temp - _Buffer) + offset;
		}

		return count;
	}

	int Buffer::countOf(const char ch) const
	{
		int c = 0;
		for (int i = 0; i <= _DataLen; i++)
		{
			if (_Buffer[i] == ch)
			{
				c++;
			}
		}

		return c;
	}

	void Buffer::replace(const Buffer &oldpattern, const Buffer &newpattern)
	{
		int newdatalen = 0;
		int substrpos = 0;
		int count = countOf(oldpattern);
		int diff = newpattern._DataLen - oldpattern._DataLen;

		newdatalen = count*diff + _DataLen;

		if (diff >= 0)
		{
			int newbufferlen = numMemPages(_DataLen + 1)*PAGE_SIZE;

			if (newbufferlen > _BufferLen)
			{
				_BufferLen = newbufferlen;
				char *ptr = new char[_BufferLen];
				memset(ptr, 0, _BufferLen);
				memcpy(ptr, _Buffer, _DataLen);
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

			memmove(_Buffer + substrpos + newpattern._DataLen, _Buffer + substrpos + oldpattern._DataLen, _DataLen + diff);
			memcpy(_Buffer + substrpos, newpattern._Buffer, newpattern._DataLen);
		}

		_DataLen = newdatalen;
	}

	void Buffer::replace(const char oldchar, const char newchar)
	{
		for (int ctr = 0; ctr <= _DataLen; ctr++)
		{
			if (_Buffer[ctr] == oldchar)
			{
				_Buffer[ctr] = newchar;
			}
		}
	}

	void Buffer::remove(const Buffer &oldpattern)
	{
		int idxToDel = -1;

		while (true)
		{
			idxToDel = indexOf(oldpattern);

			if (idxToDel < 0)
			{
				break;
			}

			memmove(&_Buffer[idxToDel], &_Buffer[idxToDel + oldpattern._DataLen], _DataLen - idxToDel);
			_Buffer[_DataLen - oldpattern._DataLen] = 0;
			_DataLen = _DataLen - oldpattern._DataLen;
		}
	}

	void Buffer::remove(const char oldchar)
	{
		int idxToDel = -1;

		while (true)
		{
			idxToDel = indexOf(oldchar);

			if (idxToDel < 0)
			{
				break;
			}

			memmove(&_Buffer[idxToDel], &_Buffer[idxToDel + 1], _DataLen - idxToDel);
			_Buffer[_DataLen - 1] = 0;
			_DataLen--;
		}
	}

	void Buffer::getKeyValuePair(Buffer &key, Buffer &value, const char delimiter)
	{
		int pos = indexOf(delimiter);

		if (pos < 0)
			return;

		if ((pos - 0) > 0)
			key.assign(_Buffer, 0, pos);

		if (((_DataLen - 1) - (pos + 1)) > 0)
			value.assign(_Buffer, pos + 1, _DataLen - 1);
	}

	void Buffer::getKeyValuePair(Buffer &key, Buffer &value, const Buffer &delimiter)
	{
		int pos = indexOf(delimiter);

		if (pos > 0)
		{
			key.assign(_Buffer, 0, pos);
			value.assign(_Buffer, pos + delimiter._DataLen, _DataLen);
		}
	}

	void Buffer::getSubSegmentList(std::list<Buffer> &tokens, const char delimiter)
	{
		int delimpos = -1;
		int offset = 1;
		int startpos = 0;

		while (true)
		{
			delimpos = indexOf(delimiter, startpos);

			if (delimpos == -1)
			{
				if (_DataLen > startpos)
				{
					tokens.push_back(Buffer(_Buffer, startpos, _DataLen));
				}

				break;
			}

			if ((delimpos != 0) && (delimpos >= startpos) && (delimpos != (_DataLen - 1)))
			{
				tokens.push_back(Buffer(_Buffer, startpos, delimpos));
			}

			startpos = delimpos + offset;
		}
	}

	void Buffer::getSubSegmentList(std::list<Buffer> &tokens, const Buffer &delimiter)
	{
		int delimpos = -1;
		int offset = delimiter._DataLen;
		int startpos = 0;

		while (true)
		{
			delimpos = indexOf(delimiter, startpos);

			if (delimpos == -1)
			{
				if (_DataLen > startpos)
				{
					tokens.push_back(Buffer(_Buffer, startpos, _DataLen));
				}

				break;
			}

			if ((delimpos != 0) && (delimpos >= startpos) && (delimpos != (_DataLen - 1)))
			{
				tokens.push_back(Buffer(_Buffer, startpos, delimpos));
			}

			startpos = delimpos + offset;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int numMemPages(int x)
	{
		int d = x / PAGE_SIZE;
		int m = x % PAGE_SIZE;

		if (m != 0)
		{
			m = 1;
		}

		return (d + m);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
