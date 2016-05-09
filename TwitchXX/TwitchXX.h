#pragma once

#include <memory>
#include "Logger.h"
#include "DBAdapter.h"
#include "TwitchGames.h"

namespace TwitchXX
{
	class Api
	{
		std::shared_ptr<DBAdapter> _db;
		std::shared_ptr<MakeRequest> _request;
	public:
		Api();
		~Api();

		TwitchGames Games();
	};
	
}
