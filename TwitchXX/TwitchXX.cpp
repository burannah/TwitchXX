#include "TwitchXX.h"
#include "MongoDB.h"



TwitchXX::TwitchXX():
	_db{std::make_unique<MongoDB>()}
{
	_db->Log("Twitch++ started.");
}


TwitchXX::~TwitchXX()
{
	_db->Log("Twitch++ stopped!");
}
