#pragma once
#include <set>


namespace TwitchXX
{
	class TwitchGame;
	template <typename T>
		using TwitchContainer = std::set<T>;
		using TwitchGamesContainer = TwitchContainer<TwitchGame>;
}
