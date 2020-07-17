#ifndef _VARIANT_TYPE
#define _VARIANT_TYPE

namespace CoreLib
{
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
}
#endif

