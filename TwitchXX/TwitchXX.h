#pragma once

#include <memory>
#include "Logger.h"
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

		TwitchGamesContainer Games();
	};

}
