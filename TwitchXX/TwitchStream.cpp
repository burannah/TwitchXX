#include "TwitchStream.h"
#include <string>
#include <cpprest\details\basic_types.h>


TwitchXX::TwitchStream::TwitchStream()
	:_offline(false), _viewers(0), _avg_fps(0), _delay(0), _video_height(0), _is_playlist(false), _id(0)
{
}


TwitchXX::TwitchStream::~TwitchStream()
{
}

void TwitchXX::TwitchStream::Created(const std::wstring& ccs)
{
	_created = DateFromString(ccs);
}

std::wstring TwitchXX::TwitchStream::CreatedAsString() const
{
	return DateToString(_created);
}

std::wstring TwitchXX::type_to_string(TwitchStream::Type t)
{
	switch (t)
	{
	case TwitchStream::Type::all:
		return U("all");
	case TwitchStream::Type::live:
		return U("live");
	case TwitchStream::Type::playlist:
		return U("playlist");
	default:
		throw std::range_error("Stream type is not supported");
	}
}
