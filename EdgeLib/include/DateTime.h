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

#ifndef DATE_TIME
#define DATE_TIME

#include "Defines.h"
#include <string.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct date_time_t date_time_t;

extern LIBRARY_EXPORT char* date_time_get_default_string(char* ptr);

/*
namespace CoreLib
{
	class DateTime
	{
	public:
		DateTime();
		DateTime(const DateTime& other);
		DateTime(const std::string &str, const std::string &format);
		DateTime(long long tinfo);
		~DateTime();

		void operator=(const DateTime& other);
		bool operator!=(const DateTime& other);
		bool operator==(const DateTime& other);
		bool operator>=(const DateTime& other);
		bool operator<=(const DateTime& other);
		bool operator>(const DateTime& other);
		bool operator<(const DateTime& other);
		DateTime& operator+=(const DateTime& other);
		DateTime operator+(const DateTime& other);
		DateTime& operator-=(const DateTime& other);
		DateTime operator-(const DateTime& other);

		void BuildFromString(const std::string &str, const std::string &format);
		void BuildFromTime(const time_t &tinfo);

		std::string GetDateString(const std::string& format);
		std::string GetDateString();
		time_t GetTime();

		void AddDays(int val);
		void AddHours(int val);
		void AddMinutes(int val);
		void AddSeconds(int val);

		int GetDays();
		int GetMonths();
		int GetYears();
		int GetHours();
		int GetMinutes();
		int GetSeconds();

		void SetDay(int val);
		void SetMonth(int val);
		void SetYear(int val);
		void SetHour(int val);
		void SetMinute(int val);
		void SsetSecond(int val);

	private:
        struct tm timeinfo;
	};
}
*/

#ifdef __cplusplus
}
#endif

#endif

