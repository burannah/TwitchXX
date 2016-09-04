#pragma once
#include "TwitchRequest.h"
#include "TwitchTeam.h"

namespace TwitchXX
{
	///Teams are an organization of channels.
	class TwitchTeams : TwitchXX::TwitchRequest<TwitchXX::TwitchTeam>
	{
	public:
		explicit TwitchTeams(std::shared_ptr<TwitchXX::MakeRequest> request): TwitchRequest<TwitchXX::TwitchTeam>(request) {};


		///Returns a list of active teams.
		///@return teams collection
		TwitchTeamsContainer GetTeams() const;

		///Returns a team object for team
		///@return team object
		TwitchTeam GetTeam(const std::wstring& team_name) const;
	
	};

	template<> TwitchTeam Create(const web::json::value& value); ///< Constructs TwitchTeam object from json
	
}
