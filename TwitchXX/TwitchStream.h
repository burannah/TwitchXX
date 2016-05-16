#pragma once

#include <set>

namespace TwitchXX
{
	class TwitchStream
	{
	public:
		enum class Type
		{
			all,
			playlist,
			live
		};
		TwitchStream();
		virtual ~TwitchStream();
	};

	using TwitchStreamsContainer = std::set<TwitchStream>;
}