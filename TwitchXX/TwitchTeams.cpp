#include "TwitchTeams.h"
#include "JsonWrapper.h"
#include "TwitchException.h"

TwitchXX::TwitchTeamsContainer TwitchXX::TwitchTeams::GetTeams() const
{
	static const size_t limit = 100; //TODO: To some global constants
	web::uri_builder builder(U("/teams"));
	builder.append_query(U("limit"), 100);
	//builder.append_query(U("direction"), Direction::asc);

	TwitchTeamsContainer result;

	while (true)
	{
		TwitchTeamsContainer chunk;
		auto value = (*_request)(builder.to_uri());
		auto subscriptions = value.at(U("teams"));
		if (!subscriptions.is_null() && subscriptions.is_array())
		{
			for (const auto& subs : subscriptions.as_array())
			{
				chunk.insert(Create<TwitchTeam>(subs));
			}
		}
		else
		{
			break;
		}

		result.insert(chunk.begin(), chunk.end());

		auto next = value.at(U("_links")).at(U("next"));
		if (chunk.size() == limit && !next.is_null() && next.is_string())
		{
			builder = web::uri_builder(next.as_string());
		}
		else
		{
			break;
		}
	}


	return result;

}

TwitchXX::TwitchTeam TwitchXX::TwitchTeams::GetTeam(const std::wstring& team_name) const
{
	web::uri_builder builder{ U("/teams/") + team_name + U("/")};

	auto response = (*_request)(builder.to_uri());
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
