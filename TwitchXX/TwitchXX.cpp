#include "TwitchXX.h"
#include "MongoLogger.h"
#include "MongoDB.h"

namespace TwitchXX
{
	std::string DatabaseName = "TwitchSpy";
	std::shared_ptr<Logger> Log;
}

TwitchXX::Api::Api():
	_db(std::make_shared<MongoDB>()),
	_request(std::make_shared<MakeRequest>(L"application/vnd.twitchtv.v2+json",L"8a1txctbv1nykj76c98vn7t4d66pmhe"))
{
	Log = std::make_shared<MongoLogger>(std::static_pointer_cast<MongoDB>(_db)->GetDb(DatabaseName));
	Log->Log(U("Api created"));
}


TwitchXX::Api::~Api()
{
	Log->Log(U("Api destroyed"));
}

TwitchXX::TwitchGames TwitchXX::Api::Games()
{
	return TwitchGames(_request);
}
