#pragma once
#include <set>
#include <map>
#include <chrono>
#include <exception>
#include <vector>
#include <functional>
#include <cpprest/details/basic_types.h> //TODO: CPPRESTSDK dependency
#ifdef _WIN32
#define to_ustring(x) std::to_wstring(x)
#else
#define to_ustring(x) std::to_string(x)
#endif



namespace TwitchXX
{
	using options = std::map<utility::string_t, utility::string_t>; ///< options collection (option key, option value)
	using Date = std::chrono::time_point<std::chrono::system_clock>; ///< default date type
}
