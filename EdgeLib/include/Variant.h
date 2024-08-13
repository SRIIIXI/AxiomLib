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

#ifndef VARIANT_C
#define VARIANT_C

#include "Defines.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum VariantType
{
    Void = 0,
    Char = 1,
    UnsignedChar = 2,
    String = 3,
    Boolean = 4,
    Number = 5,
    UnsignedNumber = 6,
    Decimal = 7,
    DateTimeStamp = 8,
    Raw = 9
}VariantType;

typedef struct variant_t
{
    VariantType DataType;
    unsigned char RawBuffer[256];
    size_t DataSize;
}variant_t;

/*
	class Variant
	{
	public:
		Variant();
		~Variant();
		Variant(const Variant& other);
		Variant(const char val);
		Variant(const unsigned char val);
		Variant(const std::string &val);
		Variant(const char*  val, size_t len);
		Variant(const bool val);
		Variant(const long val);
		Variant(const unsigned long val);
		Variant(const double val);
		Variant(const std::chrono::system_clock::time_point& val);

		const void* getData();
		void getString(std::string &str);
		long getSignedNumber();
		unsigned long getUnsignedNumber();
		double getReal();
		bool getBoolean();
		std::chrono::system_clock::time_point getTimestamp();
		char getSignedChar();

		VariantType getType();
		void setType(VariantType vtype);
		unsigned int getSize();

		void setData(const char val);
		void setData(const unsigned char val);
		void setData(const std::string &val);
		void setData(const char* val, size_t len);
		void setData(const bool val);
		void setData(const long val);
		void setData(const unsigned long val);
		void setData(const double val);
		void setData(const std::chrono::system_clock::time_point& val);

	private:
		VariantType _DataType;
		unsigned char _RawBuffer[256];
		size_t _DataSize;
	};
*/

#ifdef __cplusplus
}
#endif

#endif

