#include "TwitchTeams.h"
#include "JsonWrapper.h"
#include "TwitchException.h"

TwitchXX::TwitchTeamsContainer TwitchXX::TwitchTeams::GetTeams() const
{
	static const size_t limit = 100; //TODO: To some global constants
	web::uri_builder builder(U("/teams"));
	builder.append_query(U("limit"), 100);
	//builder.append_query(U("direction"), Direction::asc);
	return GetObjectsArrayByNext<TwitchTeam>(builder, U("teams"));
}

TwitchXX::TwitchTeam TwitchXX::TwitchTeams::GetTeam(const utility::string_t& team_name) const
{
	web::uri_builder builder{ U("/teams/") + team_name + U("/")};

	auto response = _request->get(builder.to_uri());
	return Create<TwitchTeam>(response);
}

template <>
TwitchXX::TwitchTeam TwitchXX::Create<TwitchXX::TwitchTeam>(const web::json::value& value)
{
	TwitchTeam team;
	JsonWrapper wrapper(value);

	team.Created.from_string(*wrapper[U("created_at")]);
	team.Updated.from_string(*wrapper[U("updated_at")]);
	team.Id.Set(*wrapper[U("_id")]);
	team.Background.Set(*wrapper[U("background")]);
	team.Name.Set(*wrapper[U("name")]);
	team.Info.Set(*wrapper[U("info")]);
	team.Display_Name.Set(*wrapper[U("display_name")]);
	team.Logo.Set(*wrapper[U("logo")]);
	team.Banner.Set(*wrapper[U("banner")]);

	return team;
}
