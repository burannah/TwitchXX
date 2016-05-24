#include "TwitchStream.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <cpprest/details/basic_types.h>


TwitchXX::TwitchStream::TwitchStream()
	:_offline(false), _viewers(0), _avg_fps(0), _delay(0), _video_height(0), _is_playlist(false), _id(0)
{
}


TwitchXX::TwitchStream::~TwitchStream()
{
}

void TwitchXX::TwitchStream::Created(const std::wstring& cs)
{
	std::tm t = {};
	std::wistringstream ss(cs);
	ss >> std::get_time(&t, U("%Y-%m-%dT%H:%M:%SZ")); //TODO: Add time zone handling here
	if(ss.fail())
	{
		throw std::runtime_error("Can't parse channel creation time!");
	}
	_created = std::chrono::system_clock::from_time_t(std::mktime(&t));
}

std::wstring TwitchXX::TwitchStream::CreatedAsString() const
{
	auto t = std::chrono::system_clock::to_time_t(_created);
	std::wstringstream ss;
	tm tt;
	localtime_s(&tt, &t);
	ss << std::put_time(&tt, U("%c %Z"));
	return ss.str();
}
