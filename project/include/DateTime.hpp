#ifndef _DATE_TIME
#define _DATE_TIME

#include <string>
#include <time.h>

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
		struct tm timeinfo;;
	};
}
#endif

