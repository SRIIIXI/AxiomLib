#include "DateTime.hpp"
#include "StringEx.hpp"
#include <memory.h>
#include <time.h>

namespace CoreLib
{
	DateTime::DateTime()
	{
		time_t rawtime;
		time(&rawtime);
		timeinfo = *localtime(&rawtime);
	}

	DateTime::DateTime(long long tinfo)
	{
		timeinfo = *localtime((const time_t*)&tinfo);
	}

	DateTime::DateTime(const DateTime& other)
	{
		timeinfo = other.timeinfo;
	}

	DateTime::DateTime(const std::string &str, const std::string &format)
	{
		time_t rawtime;
		time(&rawtime);
		timeinfo = *localtime(&rawtime);

		if (str.length() != 14)
		{
			if (str.length() != 12)
			{
				return;
			}
		}

		size_t pos;
		pos = format.find("yyyy");
		if (pos == -1)
		{
			pos = format.find("yy");
			if (pos != -1)
			{
				timeinfo.tm_year = strextractint(str, pos, 2) + 100;
			}
		}
		else
		{
			timeinfo.tm_year = strextractint(str, pos, 4) - 1900;
		}

		pos = format.find("MM");
		if (pos != -1)
		{
			timeinfo.tm_mon = strextractint(str, pos, 2) - 1;
		}

		pos = format.find("dd");
		if (pos != -1)
		{
			timeinfo.tm_mday = strextractint(str, pos, 2);
		}

		pos = format.find("hh");
		if (pos != -1)
		{
			timeinfo.tm_hour = strextractint(str, pos, 2);
		}

		pos = format.find("mm");
		if (pos != -1)
		{
			timeinfo.tm_min = strextractint(str, pos, 2);
		}

		pos = format.find("ss");
		if (pos != -1)
		{
			timeinfo.tm_sec = strextractint(str, pos, 2);
		}
	}

	void DateTime::BuildFromTime(const time_t& tinfo)
	{
		timeinfo = *localtime(&tinfo);
	}

	void DateTime::BuildFromString(const std::string &str, const std::string &format)
	{
		time_t rawtime;
		time(&rawtime);
		timeinfo = *localtime(&rawtime);

		if (str.length() != 14)
		{
			if (str.length() != 12)
			{
				return;
			}
		}

		size_t pos;
		pos = format.find("yyyy");
		if (pos == -1)
		{
			pos = format.find("yy");
			if (pos != -1)
			{
				timeinfo.tm_year = strextractint(str, pos, 2) + 100;
			}
		}
		else
		{
			timeinfo.tm_year = strextractint(str, pos, 4) - 1900;
		}

		pos = format.find("MM");
		if (pos != -1)
		{
			timeinfo.tm_mon = strextractint(str, pos, 2) - 1;
		}

		pos = format.find("dd");
		if (pos != -1)
		{
			timeinfo.tm_mday = strextractint(str, pos, 2);
		}

		pos = format.find("hh");
		if (pos != -1)
		{
			timeinfo.tm_hour = strextractint(str, pos, 2);
		}

		pos = format.find("mm");
		if (pos != -1)
		{
			timeinfo.tm_min = strextractint(str, pos, 2);
		}

		pos = format.find("ss");
		if (pos != -1)
		{
			timeinfo.tm_sec = strextractint(str, pos, 2);
		}
	}

	DateTime::~DateTime()
	{
	}

	void DateTime::operator=(const DateTime& other)
	{
		timeinfo = other.timeinfo;
		return;
	}

	bool DateTime::operator!=(const DateTime& other)
	{
		time_t t1 = mktime(&timeinfo);
		time_t t2 = mktime((tm*)&other.timeinfo);

		if (t1 != t2)
		{
			return true;
		}
		return false;
	}

	bool DateTime::operator==(const DateTime& other)
	{
		time_t t1 = mktime(&timeinfo);
		time_t t2 = mktime((tm*)&other.timeinfo);

		if (t1 == t2)
		{
			return true;
		}
		return false;
	}

	bool DateTime::operator>=(const DateTime& other)
	{
		time_t t1 = mktime(&timeinfo);
		time_t t2 = mktime((tm*)&other.timeinfo);

		if (t1 >= t2)
		{
			return true;
		}
		return false;
	}

	bool DateTime::operator<=(const DateTime& other)
	{
		time_t t1 = mktime(&timeinfo);
		time_t t2 = mktime((tm*)&other.timeinfo);

		if (t1 <= t2)
		{
			return true;
		}
		return false;
	}

	bool DateTime::operator>(const DateTime& other)
	{
		time_t t1 = mktime(&timeinfo);
		time_t t2 = mktime((tm*)&other.timeinfo);

		if (t1 > t2)
		{
			return true;
		}
		return false;
	}

	bool DateTime::operator<(const DateTime& other)
	{
		time_t t1 = mktime(&timeinfo);
		time_t t2 = mktime((tm*)&other.timeinfo);

		if (t1 < t2)
		{
			return true;
		}
		return false;
	}

	DateTime& DateTime::operator+=(const DateTime& other)
	{
		time_t t1 = mktime(&timeinfo);
		time_t t2 = mktime((tm*)&other.timeinfo);

		t1 = t1 + t2;

		timeinfo = *localtime(&t1);

		return *this;
	}

	DateTime DateTime::operator+(const DateTime& other)
	{
		time_t t1 = mktime(&timeinfo);
		time_t t2 = mktime((tm*)&other.timeinfo);

		time_t t3 = t1 + t2;

		return DateTime(t3);
	}

	DateTime& DateTime::operator-=(const DateTime& other)
	{
		time_t t1 = mktime(&timeinfo);
		time_t t2 = mktime((tm*)&other.timeinfo);

		t1 = t1 - t2;

		timeinfo = *localtime(&t1);

		return *this;
	}

	DateTime DateTime::operator-(const DateTime& other)
	{
		time_t t1 = mktime(&timeinfo);
		time_t t2 = mktime((tm*)&other.timeinfo);

		time_t t3 = t1 - t2;

		return DateTime(t3);
	}

	time_t DateTime::GetTime()
	{
		time_t t = mktime(&timeinfo);
		return t;
	}

	std::string DateTime::GetDateString(const std::string& format)
	{
		std::string str = format;
		size_t pos = 0;
		bool ap = false;

		char buffer[256];
		memset((char*)&buffer[0], 0, 256);

		pos = str.find("ss");
		if (pos != -1)
		{
			strreplace(str, "ss", "%S");
		}

		pos = str.find("mm");
		if (pos != -1)
		{
			strreplace(str, "mm", "%M");
		}

		pos = str.find("hh");
		if (pos != -1)
		{
			strreplace(str, "hh", "%H");
		}
		else
		{
			pos = str.find("h");
			if (pos != -1)
			{
				strreplace(str, "h", "%I");
				ap = true;
			}
		}

		pos = str.find("dd");
		if (pos != -1)
		{
			strreplace(str, "dd", "%d");
		}

		pos = str.find("MMMM");
		if (pos != -1)
		{
			strreplace(str, "MMMM", "%B");
		}
		else
		{
			pos = str.find("MM");
			if (pos != -1)
			{
				strreplace(str, "MM", "%m");
			}
		}

		pos = str.find("yyyy");
		if (pos != -1)
		{
			strreplace(str, "yyyy", "%Y");
		}
		else
		{
			pos = str.find("yy");
			if (pos != -1)
			{
				strreplace(str, "yy", "%y");
			}
		}

		if (ap)
		{
			str += "%p";

		}

		if (timeinfo.tm_year < 100)
		{
			timeinfo.tm_year += 100;
		}

		strftime(buffer, 256, str.c_str(), &timeinfo);

		return buffer;
	}

	std::string DateTime::GetDateString()
	{
		std::string str = "yyyy/MM/dd hh:mm:ss";
		size_t pos = 0;
		bool ap = false;

		char buffer[256];
		memset((char*)&buffer[0], 0, 256);

		pos = str.find("ss");
		if (pos != -1)
		{
			strreplace(str, "ss", "%S");
		}

		pos = str.find("mm");
		if (pos != -1)
		{
			strreplace(str, "mm", "%M");
		}

		pos = str.find("hh");
		if (pos != -1)
		{
			strreplace(str, "hh", "%H");
		}
		else
		{
			pos = str.find("h");
			if (pos != -1)
			{
				strreplace(str, "h", "%I");
				ap = true;
			}
		}

		pos = str.find("dd");
		if (pos != -1)
		{
			strreplace(str, "dd", "%d");
		}

		pos = str.find("MMMM");
		if (pos != -1)
		{
			strreplace(str, "MMMM", "%B");
		}
		else
		{
			pos = str.find("MM");
			if (pos != -1)
			{
				strreplace(str, "MM", "%m");
			}
		}

		pos = str.find("yyyy");
		if (pos != -1)
		{
			strreplace(str, "yyyy", "%Y");
		}
		else
		{
			pos = str.find("yy");
			if (pos != -1)
			{
				strreplace(str, "yy", "%y");
			}
		}

		if (ap)
		{
			str += "%p";

		}

		if (timeinfo.tm_year < 100)
		{
			timeinfo.tm_year += 100;
		}

		strftime(buffer, 256, str.c_str(), &timeinfo);

		return buffer;
	}


	void DateTime::AddDays(int val)
	{
		AddSeconds(val * 60 * 60 * 24);
	}

	void DateTime::AddHours(int val)
	{
		AddSeconds(val * 60 * 60);
	}

	void DateTime::AddMinutes(int val)
	{
		AddSeconds(val * 60);
	}

	void DateTime::AddSeconds(int val)
	{
		// Commented due to GCC non POSIX behaviour
		//time_t t = mktime(&timeinfo);
		//t = t + val;
		//timeinfo = *localtime(&t);

		timeinfo.tm_sec = timeinfo.tm_sec + val;
		time_t t = mktime(&timeinfo);
		timeinfo = *localtime(&t);
	}

	int DateTime::GetDays()
	{
		return timeinfo.tm_mday;
	}

	int DateTime::GetMonths()
	{
		return timeinfo.tm_mon + 1;
	}

	int DateTime::GetYears()
	{
		return timeinfo.tm_year + 1900;
	}

	int DateTime::GetHours()
	{
		return timeinfo.tm_hour;
	}

	int DateTime::GetMinutes()
	{
		return timeinfo.tm_min;
	}

	int DateTime::GetSeconds()
	{
		return timeinfo.tm_sec;
	}

	void DateTime::SetDay(int val)
	{
		timeinfo.tm_mday = val;
	}

	void DateTime::SetMonth(int val)
	{
		timeinfo.tm_mon = val - 1;
	}

	void DateTime::SetYear(int val)
	{
		timeinfo.tm_year = val - 1900;
	}

	void DateTime::SetHour(int val)
	{
		timeinfo.tm_hour = val;
	}

	void DateTime::SetMinute(int val)
	{
		timeinfo.tm_min = val;
	}

	void DateTime::SsetSecond(int val)
	{
		timeinfo.tm_sec = val;
	}
}
