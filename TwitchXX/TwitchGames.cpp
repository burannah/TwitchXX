#include "TwitchGames.h"
#include <cpprest/uri_builder.h>
#include <cpprest/json.h>
#include "Logger.h"

namespace TwitchXX
{
	extern std::shared_ptr<Logger> Log;
	extern std::shared_ptr<MakeRequest> Request;
}


TwitchXX::TwitchGames::~TwitchGames()
{
}

void TwitchXX::TwitchGames::FetchAllGames()
{
	if(_size > _games.size())
	{
		while(_size > _games.size())
		{
			FetchGames();
		}
	}
}

// Fetches a new chunk of games from web
// Each request is limited by _limit number of games
void TwitchXX::TwitchGames::FetchGames()
{
	FetchGames(_limit);
}

// Fetches 'limit' games from web.
// Check if limit plus current number of games fetched is more 
// Then total number of games on Twitch
void TwitchXX::TwitchGames::FetchGames(size_t limit)
{
	auto request_limit = limit + _games.size() > _size ? _size - _games.size() : limit;
	FetchChunk(limit, _games.size());

}

void TwitchXX::TwitchGames::FetchChunk(size_t limit, size_t offset)
{
	web::uri_builder builder(U("/games/top"));
	builder.append_query(U("limit"), limit);
	builder.append_query(U("offset"), offset);
	auto value = (*Request)(builder.to_uri());
	if(_size == 0)
	{
		auto total = value.at(L"_total");
		_size = total.as_integer();
	}
	auto top = value.at(L"top");
	if (top == web::json::value() || top.is_null() || _size == 0)
	{
		throw std::runtime_error("No games were returned");
	}
	if (top.is_array())
	{
		for each (auto& game_descriptor in top.as_array())
		{
			auto name = game_descriptor.at(L"game").at(L"name").as_string();
			if (_games.find(name) != _games.end()) continue; 
			_games[name] = CreateGame(game_descriptor);
			std::wstringstream stream(L"");
			stream << "Added game: " << game_descriptor.at(L"game").at(L"name") << " Current viewers: " << game_descriptor.at(L"viewers") << std::endl;
			Log->Log(stream.str());
		}
	}
	std::wcout << "Games fetched: " << _games.size();
}

void TwitchXX::TwitchGames::FillCollection(TwitchGame::ImageCollection& col, const web::json::value& json)
{
	if (!json.is_null())
	{
		for (auto& entry : col)
		{
			entry.second = json.at(entry.first).as_string();
		}
	}
}

TwitchXX::TwitchGame TwitchXX::TwitchGames::CreateGame(const web::json::value& json)
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

TwitchXX::TwitchGames::TwitchGames(int limit) :
	_size(0),
	_offset(0),
	_limit(limit)
{
	//Making a first request on creation
	FetchChunk(_limit, _offset);
}
