#include "TwitchGame.h"


TwitchXX::TwitchGame::TwitchGame(): _channels(0), _viewers(0), _id(0), _giantbomb_id(0)
{
}

TwitchXX::TwitchGame::TwitchGame(web::json::value json)
	:_box({ {L"small", L""},{L"medium", L""}, {L"large", L""},{L"template",L""}}),
	_logo({ { L"small", L"" },{ L"medium", L"" },{ L"large", L"" },{ L"template",L"" }})
{
	_channels = json.at(L"channels").as_integer();
	_viewers = json.at(L"viewers").as_integer();
	auto game = json.at(L"game");
	if(game.is_null())
	{
		throw std::runtime_error("Not a valid game description json");
	}
	_name = game.at(L"name").as_string();
	_id = game.at(L"id").as_integer();
	_giantbomb_id = game.at(L"giantbomb_id").as_integer();
	
	FillCollection(_box, game.at(L"box"));
	FillCollection(_logo, game.at(L"logo"));
}

TwitchXX::TwitchGame::~TwitchGame()
{
}

void TwitchXX::TwitchGame::FillCollection(ImageCollection& col, const web::json::value& json)
{
	if(!json.is_null())
	{
		for (auto& entry : col)
		{
			entry.second = json.at(entry.first).as_string();
		}
	}

}
