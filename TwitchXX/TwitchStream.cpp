#include "TwitchStream.h"
#include <string>


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
