#include <fstream>
#include "TwitchXX.h"
#include "MongoLogger.h"
#include "MongoDB.h"
#include "TwitchGames.h"

namespace TwitchXX
{
	auto Options = std::make_shared<std::map<std::wstring, std::wstring>>();
	std::string DatabaseName = "TwitchSpy";
	std::shared_ptr<Logger> Log;
	std::shared_ptr<MakeRequest> Request;

	extern void trim(std::wstring& s);
}

TwitchXX::Api::Api():
	_db(std::make_shared<MongoDB>())
{
	//reading options
	std::wifstream options_file("twitchxx.cfg");
	std::wstring line;
	while(std::getline(options_file,line))
	{
		std::wstringstream iss(line);
		std::wstring name, value;
		std::getline(iss, name, L'=');
		std::getline(iss, value);
		trim(name);
		trim(value);

		Options->insert(std::make_pair(name, value));
	}
	Request = std::make_shared<MakeRequest>(L"application/vnd.twitchtv.v2+json", L"8a1txctbv1nykj76c98vn7t4d66pmhe");
	Log = std::make_shared<MongoLogger>(std::static_pointer_cast<MongoDB>(_db)->GetDb(DatabaseName));
	Log->Log(U("Api created"));
}


TwitchXX::Api::~Api()
{
	Log->Log(U("Api destroyed"));
}

TwitchXX::TwitchGamesContainer TwitchXX::Api::TopGames(size_t top_count)
{
	TwitchGames games(100);
	return games.GetTopGames(top_count);
}
