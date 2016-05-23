#include "TwitchStreams.h"



TwitchXX::TwitchStreams::TwitchStreams()
{
}


TwitchXX::TwitchStreams::~TwitchStreams()
{
}

TwitchXX::TwitchStream TwitchXX::TwitchStreams::GetStream(const std::wstring & chanel)
{
	return TwitchStream();
}

TwitchXX::TwitchStreamsContainer TwitchXX::TwitchStreams::GetStreams(const options & opt)
{
	return TwitchStreamsContainer();
}

web::uri_builder TwitchXX::TwitchStreams::GetBuilder(size_t limit, size_t offset)
{
	return web::uri_builder();
}
