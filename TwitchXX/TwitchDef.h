#pragma once
#include <set>
#include <map>


namespace TwitchXX
{
	class TwitchGame;
	class TwitchStream;
	class TwitchChannel;
	template <typename T>
		using TwitchContainer = std::set<T>;
	using TwitchGamesContainer = TwitchContainer<TwitchGame>;
	using TwitchStreamsContainer = TwitchContainer<TwitchStream>;
	using TwitchChannelsContainer = TwitchContainer<TwitchChannel>;
	using ImageCollection = std::map<std::wstring, std::wstring>;
	using options = std::map<std::wstring, std::wstring>;
}
