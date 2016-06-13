#pragma once

#include <memory>
#include "TwitchGame.h"
#include "TwitchStream.h"
#include "TwitchFeaturedStream.h"

namespace TwitchXX
{

	class Logger;
	class TwitchStreams;
	class TwitchChannels;

	class Api
	{
	public:
		enum class Version
		{
			v2,
			v3
		};
		explicit Api(const std::wstring& clinet_id = std::wstring(), Version version = Version::v3, std::shared_ptr<Logger> = nullptr);
		virtual ~Api();

		//Log
		void AddLogger(std::shared_ptr<Logger>log);

		//Games
		TwitchGamesVector TopGames(size_t top_count = 0);

		//Streams
		TwitchStream GetStream(const std::wstring& name);
		TwitchStreamsVector TopStreams(size_t top_count = 0, const options& op = options());
		TwitchFeaturedStreamsContainer GetFeaturedStreams();
		std::tuple<size_t, size_t> GetSummary(const std::wstring& game = std::wstring());
		TwitchStreamsContainer FollowedStreams();

		//Channels
		TwitchChannel GetChannel(const std::wstring& name);

	private:
		static std::map<Version, std::wstring> _version;
		std::unique_ptr<TwitchStreams> _streams;
		std::unique_ptr<TwitchChannels> _channels;


	};
}
