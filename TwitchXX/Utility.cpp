#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

namespace TwitchXX
{
	void ltrim(std::wstring& s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int,int>(std::isspace))));
	}
	void rtrim(std::wstring& s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int,int>(std::isspace))).base(),s.end());
	}
	void trim(std::wstring& s)
	{
		ltrim(s);
		rtrim(s);
	}

}

