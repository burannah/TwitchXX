#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <cpprest/details/basic_types.h>
#include <TwitchDef.h>

namespace TwitchXX
{
	///Left trim
	///@details Trim left part of the string
	///@param s - string to be trimmed
	void ltrim(utility::string_t& s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int,int>(std::isspace))));
	}

	///Right trim
	///@details Trim right part of the string
	///@param s - string to be trimmed
	void rtrim(utility::string_t& s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int,int>(std::isspace))).base(),s.end());
	}

	///Trim string
	///@details Trim both endings of the string
	///@param s - string to be trimmed
	void trim(utility::string_t& s)
	{
		ltrim(s);
		rtrim(s);
	}

	Date DateFromString(const utility::string_t& cs)
	{
		std::tm t = {};
		utility::stringstream_t ss(cs);
		ss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S");
		if (ss.fail())
		{
			throw std::runtime_error("Can't parse channel creation time!");
		}
		return std::chrono::system_clock::from_time_t(std::mktime(&t));
	}

	utility::string_t DateToString(const Date& tp)
	{
		auto t = std::chrono::system_clock::to_time_t(tp);
		utility::stringstream_t ss;
		tm* tt = localtime(&t);
		if (tt->tm_isdst) //WTF?!
		{
			t = std::chrono::system_clock::to_time_t(tp - std::chrono::hours(1));
			tt = localtime(&t);
		}
		ss << std::put_time(tt, "%Y-%m-%dT%H:%M:%SZ");
		return ss.str();
	}
}

