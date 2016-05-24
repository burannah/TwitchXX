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
	};

	template<> TwitchChannel Create(const web::json::value& value);
}

