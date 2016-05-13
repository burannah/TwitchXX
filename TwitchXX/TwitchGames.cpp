#include "TwitchGames.h"
#include <cpprest/uri_builder.h>
#include <cpprest/json.h>
#include "Logger.h"

namespace TwitchXX
{
	extern std::shared_ptr<Logger> Log;
	extern std::shared_ptr<MakeRequest> Request;
	size_t TwitchGames::_total_size = 0;
}



TwitchXX::TwitchGames::~TwitchGames()
{
}

TwitchXX::TwitchGamesContainer TwitchXX::TwitchGames::GetTopGames(size_t n)
{
	_requested_size = n;
	auto offset = 0;
	auto max_games = n == 0 ? _total_size : n;
	const auto max_retries = 3;
	auto retries = 0;
	while (_games.size() < max_games)
	{
		int games_count = _games.size();
		auto chunk = FetchChunk(_limit,_offset);
		_games.insert(chunk.begin(), chunk.end());
		if (chunk.size() == 0 || _games.size() == games_count)
		{
			++retries;
		}
		else
		{
			retries = 0;
		}
		// "Trembling" protection
		_offset = games_count + static_cast<size_t>(chunk.size() * 0.6);
		_offset = std::min(_games.size(), _offset);
		if(_offset + _limit > _total_size)
		{
			_offset = _total_size - _limit;
		}
		if (retries >= max_retries)
		{
			break;
		}
		std::wcout << "Before=" << games_count << " After=" << _games.size() << " Chunk=" << chunk.size() << " Offset=" << _offset << " Total=" << _total_size << " Retries = " << retries << std::endl;
	}

	// Games are sorted by names. We need to return mast watched of the == sorted by the number of viewers.
	// So here comes some trick
	std::vector<TwitchGamesContainer::value_type> v(_games.begin(),_games.end());
	std::sort(v.begin(), v.end(), [](const TwitchGamesContainer::value_type& a, const TwitchGamesContainer::value_type& b) { return a.Viewers() > b.Viewers(); });
	return TwitchGamesContainer{ v.begin(), std::next(v.begin(), std::min(v.size(),max_games)) };
}

TwitchXX::TwitchGamesContainer TwitchXX::TwitchGames::FetchChunk(size_t limit, size_t offset)
{
	auto value = (*Request)(GetBuilder(limit, offset).to_uri());
	if(value.is_null())
	{
		throw std::runtime_error("No games were returned");
	}

	UpdateTotalGamesNumber(value);

	auto top = value.at(L"top");
	TwitchGamesContainer chunk;
	if (top.is_array())
	{
		for each (auto& game_descriptor in top.as_array())
		{
			auto game = CreateGame(game_descriptor);
			auto existing_game = std::find_if(_games.begin(), _games.end(), [&](const TwitchGame& item) { return game.Name() == item.Name(); });
			if (existing_game != _games.end() && *existing_game != game)
			{
				std::wcout << "Cache hit for game: " << existing_game->Name() << " , updating..." << std::endl;
				_games.erase(existing_game);
			}
			chunk.insert(game);
			std::wstringstream stream(L"");
			stream << "Added game: " << game.Name() << " Current viewers: " << game.Viewers() << std::endl;
			Log->Log(stream.str());
		}
	}

	std::wcout << "Games fetched: " << chunk.size() << std::endl;
	return chunk;
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

web::uri_builder TwitchXX::TwitchGames::GetBuilder(size_t limit, size_t offset)
{
	web::uri_builder builder(U("/games/top"));
	builder.append_query(U("limit"), limit);
	builder.append_query(U("offset"), offset);
	return builder;
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
	_offset(0),
	_limit(limit)
{
	//Just to get the totoal number
	FetchChunk(0, 1);
}
