#pragma once

#include <memory>
#include "MakeRequest.h"
#include "TwitchGame.h"

//Twitch games collection
namespace TwitchXX
{
	class TwitchGames
	{
		std::shared_ptr<MakeRequest> _request;
		std::map<std::wstring, TwitchGame> _games;
		size_t _size;
		size_t _offset;
		size_t _limit;
	public:
		explicit TwitchGames(const std::shared_ptr<MakeRequest> & request);
		virtual ~TwitchGames();
	};
}

