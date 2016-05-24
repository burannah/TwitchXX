#include "TwitchChannels.h"



TwitchXX::TwitchChannels::TwitchChannels()
{
}

TwitchXX::TwitchChannels::~TwitchChannels()
{
}
template<>
TwitchXX::TwitchChannel TwitchXX::Create(const web::json::value & value)
{
	return TwitchChannel();
}
