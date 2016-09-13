#include <cpprest/uri_builder.h>
#include <cpprest/json.h>
#include "Logger.h"
#include "TwitchGames.h"
#include "TwitchDef.h"
#include "JsonWrapper.h"

namespace TwitchXX
{
	extern std::shared_ptr<Logger> Log;
}



TwitchXX::ImageCollection TwitchXX::CreateCollection(const web::json::value& json)
{
	ImageCollection col = { { U("small"), U("") },{ U("medium"), U("") },{ U("large"), U("") },{ U("template"),U("") } };
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
	game.Channels.Set(*j[U("channels")]);
	game.Viewers.Set(*j[U("viewers")]);
	auto game_descriptor = json.at(U("game"));
	if (game_descriptor.is_null())
	{
		throw std::runtime_error("Not a valid game description json");
	}

	JsonWrapper game_wrapper(game_descriptor);
	game.Name.Set(*game_wrapper[U("name")]);
	game.Id.Set(*game_wrapper[U("_id")]);
	game.Giantbomb_Id.Set(*game_wrapper[U("giantbomb_id")]);

	game.Box = CreateCollection(game_descriptor.at(U("box")));
	game.Logo = CreateCollection(game_descriptor.at(U("logo")));

	return game;
}

TwitchXX::TwitchGamesContainer TwitchXX::TwitchGames::GetTopGames(size_t n) const
{
	static const size_t limit = 100; //TODO: To some global constants
	web::uri_builder builder(U("/games/top"));
	builder.append_query(U("limit"), limit);
	return GetObjectsArrayByNext<TwitchGame>(builder, U("top"));
}

size_t TwitchXX::TwitchGames::UpdateTotal() const
{

	web::uri_builder builder(U("/games/top"));
	builder.append_query(U("limit"), 1);
	auto value = _request->get(builder.to_uri());
	TotalSize.Set(value.at(U("_total")).as_number().to_uint32());
	return TotalSize.Get();
}