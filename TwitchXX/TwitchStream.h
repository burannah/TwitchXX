#pragma once

#include <set>

namespace TwitchXX
{
	class TwitchStream
	{
	public:
		TwitchStream();
		virtual ~TwitchStream();
	};

	using TwitchStreamsContainer = std::set<TwitchStream>;
}