#include "TwitchGames.h"
#include <cpprest/uri_builder.h>
#include <cpprest/json.h>
#include "Logger.h"

namespace TwitchXX
{
	extern std::shared_ptr<Logger> Log;
	size_t TwitchGames::_total_size = 0;
}



TwitchXX::TwitchGames::~TwitchGames()
{
}

TwitchXX::TwitchGamesContainer TwitchXX::TwitchGames::GetTopGames(size_t n)
{
	return GetTopObjects(n);
}

void TwitchXX::FillCollection(TwitchGame::ImageCollection& col, const web::json::value& json)
{
	if (!json.is_null())
	{
		for (auto& entry : col)
		{
			entry.second = json.at(entry.first).as_string();
		}
	}
}

web::uri_builder TwitchXX::TwitchGames::GetBuilder(size_t limit, size_t offset)
{
	web::uri_builder builder(U("/games/top"));
	builder.append_query(U("limit"), limit);
	builder.append_query(U("offset"), offset);
	return builder;
}

TwitchXX::TwitchGame TwitchXX::Create(const web::json::value json)
{
	TwitchGame game;
	game.Channels(json.at(L"channels").as_integer());
	game.Viewers(json.at(L"viewers").as_integer());
	auto game_descriptor = json.at(L"game");
	if (game_descriptor.is_null())
	{
		throw std::runtime_error("Not a valid game description json");
	}
	game.Name(game_descriptor.at(L"name").as_string());
	game.Id(game_descriptor.at(L"_id").as_integer());
	game.Giantbomb_Id(game_descriptor.at(L"giantbomb_id").as_integer());

	FillCollection(game.Box(), game_descriptor.at(L"box"));
	FillCollection(game.Logo(), game_descriptor.at(L"logo"));

	return game;
}