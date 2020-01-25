#ifndef _BUFFER
#define _BUFFER

#include <list>

namespace CoreLib
{
	class Buffer
	{
	public:
		Buffer();
		Buffer(const Buffer & obj);
		Buffer(const char* ptr, int len);
		Buffer(const wchar_t* ptr, int len);
		Buffer(const char* ptr, int startpos, int endpos);
		~Buffer();

		int length() const;
		void clear();
		void assign(const char *ptr, int len);
		void assign(const char *ptr, int startpos, int endpos);
		const char* buffer() const;
		int indexOf(const Buffer &obj, int startpos = 0) const;
		int indexOf(const char* ptr, int startpos = 0) const;
		int indexOf(const char ch, int startpos = 0) const;
		void getSubSegment(int pos, int len, Buffer &substr) const;

		int countOf(const Buffer &obj) const;
		int countOf(const char* ptr) const;
		int countOf(const char ch) const;

		void replace(const Buffer &oldpattern, const Buffer &newpattern);
		void replace(const char oldchar, const char newchar);

		void remove(const Buffer &oldpattern);
		void remove(const char oldchar);

		void getKeyValuePair(Buffer &key, Buffer &value, const char delimiter);
		void getKeyValuePair(Buffer &key, Buffer &value, const Buffer &delimiter);

		void getSubSegmentList(std::list<Buffer> &tokens, const char delimiter);
		void getSubSegmentList(std::list<Buffer> &tokens, const Buffer &delimiter);

		void operator=(const Buffer& other);
		bool operator!=(const Buffer& other);
		bool operator==(const Buffer& other);

		Buffer& operator+=(const Buffer& other);
		Buffer& operator+=(const char& other);
		Buffer operator+(const Buffer& other);
		Buffer operator+(const char& other);

		char getAt(const int atpos) const;
		void SetAt(const int atpos, const char ch);
		char operator[](const long index);

	private:
		char*	_Buffer;
		int		_BufferLen;
		int		_DataLen;
	};
}
#endif
