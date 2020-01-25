#ifndef _BASE_64
#define _BASE_64

#include <vector>
#include <string>

namespace CoreLib
{
	class Base64
	{
	public:
		Base64();
		std::string Encode(const std::vector<unsigned char> &data);
		std::vector<unsigned char> Decocde(const std::string &data);
	};
}
#endif
