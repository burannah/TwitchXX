#pragma once

#include <map>
#include "TwitchStream.h"

namespace TwitchXX
{
	class TwitchStreams
	{
	public:
		using options = std::map<std::wstring, std::wstring>;
		TwitchStreams();
		virtual ~TwitchStreams();

		TwitchStreamsContainer GetStreams(const options& opt = options());
	};
}

