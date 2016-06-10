#pragma once

#include <cpprest/json.h>
#include "TwitchChannel.h"
#include "TwitchRequest.h"
#include "TwitchDef.h"
#include "TwitchUser.h"
#include "TwitchTeam.h"

namespace TwitchXX
{
	class TwitchChannels : public TwitchRequest<TwitchChannel>
	{
	public:
		TwitchChannels();
		virtual ~TwitchChannels();

		TwitchChannel GetChannel(const std::wstring& name = std::wstring()) const;
		TwitchUsersContainer GetChannelEditors(const std::wstring& name) const;
		TwitchChannel UpdateChannel(const std::wstring& name, const options& op) const;
		std::wstring ResetStreamKey(const std::wstring& channel_name) const;
		bool StartCommercial(const std::wstring& channel_name, size_t length = 30) const;
		TwitchTeamsContainer GetTeams(const std::wstring& channel_name) const;


	};

	template<> TwitchChannel Create(const web::json::value& value);
	template<> TwitchUser Create(const web::json::value& value);
	template<> TwitchTeam Create(const web::json::value& value);
}

