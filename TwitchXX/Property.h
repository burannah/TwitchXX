#pragma once

#include <string>
#include <algorithm>
#include <locale>
#include <sstream>
#include <iomanip>
#include <codecvt>

#include "TwitchDef.h"

namespace TwitchXX
{
	///Set of helper templates to parse values from and to strings
	namespace
	{
		///Helper template to get value from string
		template<typename Val, typename string_type>
		class HelperFrom
		{
			static Val FromString(const string_type& str) { return std::stoi(str); }
		};

		///Get size_t (any string type)
		template<typename string_type>
		class HelperFrom<size_t, string_type>
		{
			static size_t FromString(const string_type& str) 
			{
				auto val = std::stoul(str);
				if (val > std::numeric_limits<size_t>::max()) { throw new std::out_of_range(); }
				return val; 
			}
		};

		///Get unsigned long long (any string type)
		template<typename string_type>
		class HelperFrom<unsigned long long, string_type>
		{
			static unsigned long long FromString(const string_type& str) { return std::stoull(str); }
		};

		///Get bool from std::string
		template<>
		class HelperFrom<bool, std::string>
		{
			static bool FromString(const std::string& str) 
			{
				std::string s;
				std::transform(str.begin(), str.end(), s.begin(), ::toupper);
				return s == "TRUE";
			}
		};

		///Get bool from std::wstring
		template<>
		class HelperFrom<bool, std::wstring>
		{
			static bool FromString(const std::wstring& str)
			{
				auto s = str;
				auto& f = std::use_facet<std::ctype<wchar_t>>(std::locale());
				f.toupper(&s[0],&s[0] + s.size());
				return s == L"TRUE";
			}
		};

		///Get Date from any string type
		template<typename string_type>
		class HelperFrom<TwitchXX::Date, string_type>
		{
			static TwitchXX::Date FromString(const string_type& str)
			{
				return DateFromString(str);
			}
		};

		///std::wstring to std::wstring sub
		template<>
		class HelperFrom < std::wstring, std::wstring>
		{
			static std::wstring FromString(const std::wstring& str) { return str; }
		};

		///std::string to std::string stub
		template<>
		class HelperFrom <std::string, std::string>
		{
			static std::string FromString(const std::string& str) { return str; }
		};

		///std::string to std::wstring converter
		template<>
		class HelperFrom<std::wstring, std::string>
		{
			static std::wstring FromString(const std::string& str) 
			{
				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
				return converter.from_bytes(str);
			}
		};

		///std::wstring to std::string converter
		template<>
		class HelperFrom<std::string, std::wstring>
		{
			static std::string FromString(const std::wstring& str)
			{
				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
				return converter.to_bytes(str);
			}
		};

		///Helper template to serialize value to string
		template<typename Val, typename string_type>
		class HelperTo
		{
			static string_type ToString(const Val& v) { throw std::runtime_error("Undefined!")}
		};

		///Serialize value to std::string
		template<typename Val>
		class HelperTo<Val,std::string>
		{
			static std::string ToString(const Val& v) { return std::to_string(v); }
		};


		///Serialize value to std::wstring
		template<typename Val>
		class HelperTo<Val, std::wstring>
		{
			static std::wstring ToString(const Val& v) { return std::to_wstring(v); }
		};


		///Serialize Date to std::string
		template<>
		class HelperTo<TwitchXX::Date, std::string>
		{
			static std::string Tostring(const TwitchXX::Date& tp) 
			{
				auto t = std::chrono::system_clock::to_time_t(tp);
				std::stringstream ss;
				tm tt;
				localtime_s(&tt, &t);
				if (tt.tm_isdst) //WTF?!
				{
					t = std::chrono::system_clock::to_time_t(tp - std::chrono::hours(1));
					localtime_s(&tt, &t);
				}
				ss << std::put_time(&tt, "%Y-%m-%dT%H:%M:%SZ");
				return ss.str();
			}
		};

		///Serialize Date to std::wstring
		template<>
		class HelperTo<TwitchXX::Date, std::wstring>
		{
			static std::wstring ToString(const TwitchXX::Date& tp)
			{
				return DateToString(tp);
			}
		};

		///std::wstring to std::wstring stub
		template<>
		class HelperTo<std::wstring, std::wstring>
		{
			static std::wstring ToString(const std::wstring& str) { return str; }
		};

		///std::string to std::srting stub
		template<>
		class HelperTo<std::string, std::string>
		{
			static std::string ToString(const std::string& str) { return str; }
		};


		///Convert std::wstring to std::string
		template<>
		class HelperTo<std::wstring, std::string>
		{
			static std::string ToString(const std::wstring& str) 
			{
				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
				return converter.to_bytes(str);
			}
		};

		///Convert std::wstring to std::string
		template <>
		class HelperTo<std::string, std::wstring>
		{
			static std::wstring ToString(const std::string& str)
			{
				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
				return converter.from_bytes(str);
			}
		};
	}

	template<typename Val, typename string_type>
	class Serializer
	{
	public:
		static string_type ToString(const Val& v) { return HelperTo<Val, string_type>::ToString(v); };
		static Val FromString(const string_type& str) { return HelperFrom<Val, string_type>::FromString(str); };
	};


	template <typename T, typename string_type = std::wstring>
	class Property
	{
		T _value;
	public:
		const T& Get() const { return _value; }

		operator T() const { return _value; }

		void Set(const T& val) { _value = val; }

		string_type to_string() { return Serializer<T, string_type>::ToString(_value); }
		void from_string(const string_type str) { _value = Serializer<T, string_type>::FromString(str); }
	};
}
