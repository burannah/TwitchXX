#pragma once

#include <cpprest/json.h>
#include "TwitchChannel.h"
#include "TwitchRequest.h"
#include "TwitchDef.h"

namespace TwitchXX
{
	class TwitchChannels : public TwitchRequest<TwitchChannel>
	{
	public:
		TwitchChannels();
		virtual ~TwitchChannels();

		TwitchChannel GetChannel(const std::wstring& name);
	};

	template<> TwitchChannel Create(const web::json::value& value);
}

