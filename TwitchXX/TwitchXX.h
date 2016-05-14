#pragma once

#include <memory>
#include "DBAdapter.h"
#include "TwitchGame.h"

namespace TwitchXX
{
	class Api
	{
	public:
		enum class Version
		{
			v2,
			v3
		};
		explicit Api(const std::wstring& clinet_id,Version version = Version::v3);
		virtual ~Api();

		TwitchGamesContainer TopGames(size_t top_count = 0);
	private:
		std::map<Version, std::wstring> _version =
		{
			{ TwitchXX::Api::Version::v2, L"application/vnd.twitchtv.v2+json" },
			{ TwitchXX::Api::Version::v3, L"application/vnd.twitchtv.v3+json" }
		};
		std::shared_ptr<DBAdapter> _db;
	};
}
