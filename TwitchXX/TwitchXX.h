#pragma once

#include <memory>
#include "DBAdapter.h"
#include "TwitchGame.h"
#include "TwitchStream.h"

namespace TwitchXX
{
	class TwitchStream;

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
		TwitchStream GetStream(const std::wstring& name);
		TwitchStreamsContainer TopStreams(size_t top_count = 0, const options& op = options());
	private:
		static std::map<Version, std::wstring> _version;
		std::shared_ptr<DBAdapter> _db;
	};
}
