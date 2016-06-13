#include <cpprest/uri_builder.h>
#include <cpprest/json.h>
#include "Logger.h"
#include "TwitchGames.h"
#include "TwitchDef.h"
#include "JsonWrapper.h"

namespace TwitchXX
{
	extern std::shared_ptr<Logger> Log;
	size_t TwitchGames::_total_size = 0;
}



TwitchXX::TwitchGames::~TwitchGames()
{
}

TwitchXX::ImageCollection TwitchXX::CreateCollection(const web::json::value& json)
{
	ImageCollection col = { { L"small", L"" },{ L"medium", L"" },{ L"large", L"" },{ L"template",L"" } };
	if (!json.is_null())
	{
		for (auto& entry : col)
		{
			entry.second = json.at(entry.first).as_string();
		}
	}

	return col;
}

template <>
TwitchXX::TwitchGame TwitchXX::Create<TwitchXX::TwitchGame>(const web::json::value& json)
{
	TwitchGame game;
	JsonWrapper j(json);
	game.Channels(*j[U("channels")]);
	game.Viewers(*j[U("viewers")]);
	auto game_descriptor = json.at(L"game");
	if (game_descriptor.is_null())
	{
		throw std::runtime_error("Not a valid game description json");
	}

	JsonWrapper game_wrapper(game_descriptor);
	game.Name(*game_wrapper[U("name")]);
	game.Id(*game_wrapper[U("_id")]);
	game.Giantbomb_Id(*game_wrapper[U("giantbomb_id")]);

	game.Box(CreateCollection(game_descriptor.at(L"box")));
	game.Logo(CreateCollection(game_descriptor.at(L"logo")));

	return game;
}

TwitchXX::TwitchGamesVector TwitchXX::TwitchGames::GetTopGames(size_t n)
{
	auto offset = 0;
	//Updating limit
	_limit = n < max_limit ? n : max_limit;
	auto max_objects = n == 0 ? _total_size : n;
	const auto max_retries = 3;
	auto retries = 0;
	while (_objects.size() < max_objects)
	{
		int count = _objects.size();
		auto chunk = FetchChunk(GetBuilder(_limit,_offset).to_uri(),U("top"));
		_objects.insert(chunk.begin(), chunk.end());
		if (chunk.size() == 0 || _objects.size() == count)
		{
			++retries;
		}
		else
		{
			retries = 0;
		}
		// "Trembling" protection
		_offset = count + static_cast<size_t>(chunk.size() * 0.8);
		_offset = std::min(_objects.size(), _offset);
		if (_offset + _limit > _total_size)
		{
			_offset = _total_size < _limit ? 0 : _total_size - _limit;
		}
		if (retries >= max_retries)
		{
			break;
		}
		std::wcout << "Before=" << count << " After=" << _objects.size() << " Chunk=" << chunk.size() << " Offset=" << _offset << " Total=" << _total_size << " Retries = " << retries << std::endl;
	}

	// Objects are sorted by names. We need to return mast watched of them == sorted by the number of viewers.
	// So here comes some trick
	std::vector<TwitchGame> v(_objects.begin(), _objects.end());
	std::sort(v.begin(), v.end(), [](const TwitchGame& a, const TwitchGame& b) { return a.Viewers() > b.Viewers(); });
	return v;
}

web::uri_builder TwitchXX::TwitchGames::GetBuilder(size_t limit, size_t offset)
{
	web::uri_builder builder(U("/games/top"));
	builder.append_query(U("limit"), limit);
	builder.append_query(U("offset"), offset);
	return builder;
}
