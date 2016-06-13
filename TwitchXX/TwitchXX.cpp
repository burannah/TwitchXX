#include <fstream>
#include "TwitchXX.h"
#include "TwitchGames.h"
#include "TwitchStreams.h"
#include "TwitchChannels.h"

namespace TwitchXX
{
	class TwitchStreams;
	std::shared_ptr<std::map<std::wstring,std::wstring>> Options = std::make_shared<std::map<std::wstring, std::wstring>>();
	std::string DatabaseName = "TwitchSpy";
	std::shared_ptr<Logger> Log = std::make_shared<Logger>();
	extern void trim(std::wstring& s);
}

std::map<TwitchXX::Api::Version,std::wstring> TwitchXX::Api::_version =
{
	{ Version::v2, L"application/vnd.twitchtv.v2+json" },
	{ Version::v3, L"application/vnd.twitchtv.v3+json" }
};

TwitchXX::Api::Api(const std::wstring& client_id, Version version, std::shared_ptr<Logger> log)
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
	if (client_id.size() && Options->find(U("api_key")) != Options->end())
	{
		//Do not override config file's api_key parameter event if explicitly provided by parameter
		Options->insert(std::make_pair(U("api_key"), client_id));
	}
	Options->insert(std::make_pair(U("version"), _version[version]));

	_streams = std::make_unique<TwitchStreams>();
	_channels = std::make_unique<TwitchChannels>();


	if(log != nullptr)
	{
		Log->Subscribe(log);
	}
	Log->Log(U("Api created"));
}


TwitchXX::Api::~Api()
{
	Log->Log(U("Api destroyed"));
}

void TwitchXX::Api::AddLogger(std::shared_ptr<Logger>log)
{
	if(log != nullptr)
	{
		Log->Subscribe(log);
	}
}

TwitchXX::TwitchGamesVector TwitchXX::Api::TopGames(size_t top_count)
{
	TwitchGames games(100);
	return games.GetTopGames(top_count);
}

TwitchXX::TwitchStream TwitchXX::Api::GetStream(const std::wstring& name)
{
	return  _streams->GetStream(name);
}

TwitchXX::TwitchStreamsVector TwitchXX::Api::TopStreams(size_t top_count, const options& op)
{
	try
	{
		return _streams->GetStreams(top_count, op);
	}
	catch(std::runtime_error& e)
	{
		std::wcout << e.what() << "\n";
	}

	return TwitchStreamsVector();

}

TwitchXX::TwitchFeaturedStreamsContainer TwitchXX::Api::GetFeaturedStreams()
{
	return _streams->GetFeaturedStreams();
}

std::tuple<size_t, size_t> TwitchXX::Api::GetSummary(const std::wstring& game)
{
	return _streams->GetSummary(game);
}

TwitchXX::TwitchStreamsContainer TwitchXX::Api::FollowedStreams()
{
	return _streams->GetFollowedStreams();
}

TwitchXX::TwitchChannel TwitchXX::Api::GetChannel(const std::wstring & name)
{
	return _channels->GetChannel(name);
}
