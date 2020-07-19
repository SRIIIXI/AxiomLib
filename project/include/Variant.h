#ifndef VARIANT_C
#define VARIANT_C

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

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

typedef struct Variant
{
    VariantType DataType;
    unsigned char RawBuffer[256];
    size_t DataSize;
}Variant;

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

#endif

