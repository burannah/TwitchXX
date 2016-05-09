#include "TwitchGames.h"
#include <cpprest/uri_builder.h>
#include <cpprest/json.h>
#include "Logger.h"

namespace TwitchXX
{
	extern std::shared_ptr<Logger> Log;
}


TwitchXX::TwitchGames::~TwitchGames()
{
}

TwitchXX::TwitchGames::TwitchGames(const std::shared_ptr<MakeRequest>& request) :
	_request(request),
	_size(0),
	_offset(0),
	_limit(10)
{
	//Making a first request on creation
	web::uri_builder builder(U("/games/top"));
	builder.append_query(U("limit"), _limit);
	builder.append_query(U("offset"), _offset);
	auto value = (*_request)(builder.to_uri());
	if (value.at(L"top") == web::json::value())
	{
		std::wcout << "No games were returned" << std::endl;
		return;
	}
	auto top = value.at(L"top");
	if (top.is_array())
	{
		for each (auto& game_descriptor in top.as_array())
		{
			auto name = game_descriptor.at(L"game").at(L"name").as_string();
			_games[name] = TwitchGame(game_descriptor);
			std::wstringstream stream(L"");
			stream << "Added game: " << game_descriptor.at(L"game").at(L"name") << " Current viewers: " << game_descriptor.at(L"viewers") << std::endl;
			Log->Log(stream.str());
		}
	}
}
