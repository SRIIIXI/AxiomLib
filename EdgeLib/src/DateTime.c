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

#include "DateTime.h"
#include "StringEx.h"
#include <memory.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct date_time_t
{
    struct tm timeinfo;

}date_time_t;

char* date_time_get_default_string(char* ptr)
{
    if(!ptr)
    {
        return  NULL;
    }

    char buffer[33] = {0};

    time_t t ;
    struct tm *tmp ;
    time(&t);
    tmp = localtime(&t);

    sprintf(buffer, "%04d%02d%02d%02d%02d%02d",
             (tmp->tm_year+1900), (tmp->tm_mon+1),tmp->tm_mday,
             tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

    strcpy(ptr, buffer);

    return ptr;
}

void date_time_release(date_time_t* ptr)
{
	if(!ptr)
    {
        return;
    }

	free(ptr);
	ptr = NULL;
}

date_time_t* date_time_allocate_default()
{
	date_time_t* retval = (date_time_t*)calloc(1, sizeof(date_time_t));

	time_t t ;
    struct tm *tmp ;
    time(&t);
    tmp = localtime(&t);
	retval->timeinfo = *tmp;

	return retval;
}

date_time_t* date_time_allocate_from_string(const char* strts, const char* strformat)
{
	date_time_t* retval = NULL;

	return retval;
}

date_time_t* date_time_allocate_from_unix_epoch(const unsigned long long unixtsval)
{
	date_time_t* retval = (date_time_t*)calloc(1, sizeof(date_time_t));

	if(retval == NULL)
	{
		return NULL;
	}

	struct tm *tmp ;
    time(&unixtsval);
    tmp = localtime(&unixtsval);
	retval->timeinfo = *tmp;

	return retval;
}

date_time_t* date_time_allocate_from_time(const time_t tsval)
{
	return date_time_allocate_from_unix_epoch(tsval);
}

date_time_t* date_time_allocate_from_time_struct(const struct tm* tsval)
{
	if(tsval == NULL)
	{
		return NULL;
	}

	date_time_t* retval = (date_time_t*)calloc(1, sizeof(date_time_t));

	if(retval == NULL)
	{
		return NULL;
	}

	retval->timeinfo = *tsval;

	return retval;
}

char* date_time_get_string(date_time_t* ptr)
{
	char* retval = NULL;
	return retval;
}

char* date_time_get_formatted_string(date_time_t* ptr, const char* strformat)
{
	char* retval = NULL;
	return retval;
}

unsigned long long date_time_get_unix_epoch(date_time_t* ptr)
{
	unsigned long long retval = 0;
	return retval;
}

time_t date_time_get_time(date_time_t* ptr)
{
	time_t retval;
	return retval;
}

date_time_t* date_time_add_days(date_time_t* ptr, unsigned long val)
{
	date_time_t* retval = NULL;
	return retval;
}

date_time_t* date_time_add_hours(date_time_t* ptr, unsigned long val)
{
	date_time_t* retval = NULL;
	return retval;
}

date_time_t* date_time_add_minutes(date_time_t* ptr, unsigned long val)
{
	date_time_t* retval = NULL;
	return retval;
}

date_time_t* date_time_add_seconds(date_time_t* ptr, unsigned long val)
{
	date_time_t* retval = NULL;
	return retval;
}

unsigned long date_time_get_hours(date_time_t* ptr)
{
	if(ptr == NULL)
	{
		return 0;
	}

	return ptr->timeinfo.tm_hour;
}

unsigned long date_time_get_minutes(date_time_t* ptr)
{
	if(ptr == NULL)
	{
		return 0;
	}

	return ptr->timeinfo.tm_min;
}

unsigned long date_time_get_seconds(date_time_t* ptr)
{
	if(ptr == NULL)
	{
		return 0;
	}

	return ptr->timeinfo.tm_sec;
}

unsigned long date_time_get_miliseconds(date_time_t* ptr)
{
	if(ptr == NULL)
	{
		return 0;
	}

	return ptr->timeinfo.tm_sec;
}

unsigned long date_time_get_year(date_time_t* ptr)
{
	if(ptr == NULL)
	{
		return 0;
	}

	return ptr->timeinfo.tm_year+1900;
}

unsigned long date_time_get_month(date_time_t* ptr)
{
	if(ptr == NULL)
	{
		return 0;
	}

	return ptr->timeinfo.tm_mon+1;
}

unsigned long date_time_get_days(date_time_t* ptr)
{
	if(ptr == NULL)
	{
		return 0;
	}

	return ptr->timeinfo.tm_yday;
}

unsigned long date_time_get_day_of_month(date_time_t* ptr)
{
	if(ptr == NULL)
	{
		return 0;
	}

	return ptr->timeinfo.tm_mday;
}

unsigned long date_time_get_day_of_week(date_time_t* ptr)
{
	if(ptr == NULL)
	{
		return 0;
	}

	return ptr->timeinfo.tm_wday;
}

unsigned long date_time_get_week_of_year(date_time_t* ptr)
{
	return 0;
}

void date_time_set_year(date_time_t* ptr, unsigned long val)
{

}

void date_time_set_month(date_time_t* ptr, unsigned long val)
{

}

void date_time_set_day(date_time_t* ptr, unsigned long val)
{

}

void date_time_set_hour(date_time_t* ptr, unsigned long val)
{

}

void date_time_set_minute(date_time_t* ptr, unsigned long val)
{

}

void date_time_set_second(date_time_t* ptr, unsigned long val)
{
	
}

bool date_time_are_equal(date_time_t* first, date_time_t* second)
{
	bool retval = false;
	return retval;
}

bool date_time_is_first_greater(date_time_t* first, date_time_t* second)
{
	bool retval = false;
	return retval;
}

bool date_time_is_first_lower(date_time_t* first, date_time_t* second)
{
	bool retval = false;
	return retval;
}

unsigned long date_time_diff_miliseconds(date_time_t* first, date_time_t* second)
{
	unsigned long retval = false;
	return retval;
}


/*
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
*/
