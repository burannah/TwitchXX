#pragma once

#include <memory>
#include "DBAdapter.h"
#include "TwitchGame.h"

namespace TwitchXX
{
	class Api
	{
		std::shared_ptr<DBAdapter> _db;
	public:
		Api();
		~Api();

		TwitchGamesContainer TopGames(size_t top_count = 0);
	};
}
