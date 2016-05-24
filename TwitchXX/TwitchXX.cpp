#include <fstream>
#include "TwitchXX.h"
#include "MongoLogger.h"
#include "MongoDB.h"
#include "TwitchGames.h"
#include "TwitchStreams.h"

namespace TwitchXX
{
	class TwitchStreams;
	std::shared_ptr<std::map<std::wstring,std::wstring>> Options = std::make_shared<std::map<std::wstring, std::wstring>>();
	std::string DatabaseName = "TwitchSpy";
	std::shared_ptr<Logger> Log;
	extern void trim(std::wstring& s);
}

std::map<TwitchXX::Api::Version,std::wstring> TwitchXX::Api::_version =
{
	{ TwitchXX::Api::Version::v2, L"application/vnd.twitchtv.v2+json" },
	{ TwitchXX::Api::Version::v3, L"application/vnd.twitchtv.v3+json" }
};

TwitchXX::Api::Api(const std::wstring& client_id, Version version) :
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
	Options->insert(std::make_pair(U("api_key"), client_id));
	Options->insert(std::make_pair(U("version"), _version[version]));

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

TwitchXX::TwitchStream TwitchXX::Api::GetStream(const std::wstring& name)
{
	TwitchStreams streams;
	return  streams.GetStream(name);
}

TwitchXX::TwitchStreamsContainer TwitchXX::Api::TopStreams(size_t top_count, const options& op)
{
	TwitchStreams streams;
	return streams.GetStreams(top_count, op);
}
