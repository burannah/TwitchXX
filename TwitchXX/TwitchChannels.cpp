#include "TwitchChannels.h"
#include "JsonWrapper.h"
#include "TwitchException.h"
#include "TwitchUsers.h"
#include "TwitchFollower.h"


TwitchXX::TwitchChannels::TwitchChannels(std::shared_ptr<MakeRequest> request)
	: TwitchRequest<TwitchXX::TwitchChannel>(request) 
{

}

TwitchXX::TwitchChannel TwitchXX::TwitchChannels::GetChannel(const std::wstring & name) const
{
	//TODO: add test for getting channel of authenticated user
	std::wstring request_string = U("/channel");
	if (name.length() > 0)
	{
		request_string += U("s/") + name + U("/");
	}

	web::uri_builder builder (U("/channels/") + name + U("/"));
	auto value = (*_request)(builder.to_uri());
	if (value.is_null())
	{
		throw std::runtime_error("No objects were returned");
	}

	return Create<TwitchChannel>(value);

}
TwitchXX::TwitchUsersContainer TwitchXX::TwitchChannels::GetChannelEditors(const std::wstring & name) const
{
	web::uri_builder builder(U("/channels/") + name + U("/editors"));
	auto value = (*_request)(builder.to_uri());
	if (value.is_null())
	{
		throw std::runtime_error("No objects were returned");
	}


	auto users = value.at(U("users"));
	TwitchUsersContainer result;

	if (!users.is_null() && users.is_array())
	{
		for each (const auto& user_desciptor in users.as_array())
		{
			result.insert(Create<TwitchUser>(user_desciptor));
		}

	}
	return result;
}

TwitchXX::TwitchChannel TwitchXX::TwitchChannels::UpdateChannel(const std::wstring& name, const options& op) const
{
	auto channel = GetChannel(name);
	auto o(op);
	if(o.find(U("status")) == o.end())
	{
		o[U("status")] = channel.Status.Get();
	}
	if(o.find(U("game")) == o.end())
	{
		o[U("game")] = channel.Game.Get();
	}
	if(o.find(U("delay"))== o.end())
	{
		o[U("delay")] = std::to_wstring(channel.Delay.Get());
	}

	web::json::value channelJSON,requestJSON;

	web::uri_builder builder(U("/channels/") + name + U("/"));
	for (const auto& option : o)
	{
		channelJSON[option.first] = web::json::value::string(option.second);
	}
	requestJSON[U("channel")] = channelJSON;

	auto value = (*_request)(builder.to_uri(), web::http::methods::PUT,requestJSON);
	if (value.is_null() || _request->status_code() == 422)
	{
		throw std::runtime_error("The channel is not partnered!");
	}

	return Create<TwitchChannel>(value);
}

std::wstring TwitchXX::TwitchChannels::ResetStreamKey(const std::wstring& channel_name) const
{
	web::uri_builder builder(U("/channels/") + channel_name + U("/stream_key"));
	auto value = (*_request)(builder.to_uri(),web::http::methods::DEL);

	if(value.is_null())
	{
		throw std::runtime_error("Unable to reset stream key.");
	}

	return value.at(U("stream_key")).as_string();
}

bool TwitchXX::TwitchChannels::StartCommercial(const std::wstring& channel_name, size_t length) const
{
	web::uri_builder builder(U("/channels/") + channel_name + U("/commercial"));
	static std::set<size_t> valid_lengths{ 30, 60, 90 , 120, 150, 180 };
	if (valid_lengths.find(length) == valid_lengths.end())
	{
		length = 30;
	}
	builder.append_query(U("length"), length);
	auto value = (*_request)(builder.to_uri(), web::http::methods::POST);

	switch(_request->status_code())
	{
		case 204: return true;
		case 422: return false; //A commercial was ran less than 8 minutes ago, or the channel is not partnered.
		default: TwitchException("Unable to start commercial for this channel!",_request->status_code());
	}
	return false;
}

TwitchXX::TwitchTeamsContainer TwitchXX::TwitchChannels::GetTeams(const std::wstring& channel_name) const
{
	web::uri_builder builder(U("/channels/") + channel_name + U("/teams"));
	TwitchTeamsContainer chunk;
	auto value = (*_request)(builder.to_uri());
	auto teams = value.at(U("teams"));
	if(!teams.is_null() && teams.is_array())
	{
		for (const auto& team : teams.as_array())
		{
			chunk.insert(Create<TwitchTeam>(team));
		}
	}
	return chunk;
}

TwitchXX::TwitchFollowersContainer TwitchXX::TwitchChannels::GetChannelFollows(const std::wstring& channel_name) const
{
	web::uri_builder builder(U("/channels/") + channel_name + U("/follows"));
	builder.append_query(U("limit"), 100);
	auto current_builder = builder;

	TwitchFollowersContainer result;

	while(true)
	{
		auto value = (*_request)(current_builder.to_uri());
		auto followers = value.at(U("follows"));
		if (!followers.is_null() && followers.is_array())
		{
			for (const auto& follower : followers.as_array())
			{
				result.insert(Create<TwitchFollower>(follower));
			}
		}
		else
		{
			break;
		}

		if(value.has_field(U("_cursor")) && value.at(U("_cursor")).is_string())
		{
			current_builder = builder;
			current_builder.append_query(U("cursor"), value.at(U("_cursor")).as_string());
		}
		else
		{
			break;
		}
	}


	return result;
}

template<>
TwitchXX::TwitchChannel TwitchXX::Create(const web::json::value & value)
{
	TwitchChannel channel;
	JsonWrapper wrapper(value);

	channel.Mature.Set(*wrapper[U("mature")]);
	channel.Status.Set(*wrapper[U("status")]);
	channel.Broadcaster_Language.Set(*wrapper[U("broadcaster_language")]);
	channel.Display_Name.Set(*wrapper[U("display_name")]);
	channel.Game.Set(*wrapper[U("game")]);
	channel.Delay.Set(*wrapper[U("delay")]);
	channel.Language.Set(*wrapper[U("language")]);
	channel.Id.Set(*wrapper[U("_id")]);
	channel.Name.Set(*wrapper[U("name")]);
	channel.Created.from_string(*wrapper[U("created_at")]);
	channel.Updated.from_string(*wrapper[U("updated_at")]);
	channel.Logo.Set(*wrapper[U("logo")]);
	channel.Banner.Set(*wrapper[U("banner")]);
	channel.Video_Banner.Set(*wrapper[U("video_banner")]);
	channel.Background.Set(*wrapper[U("background")]);
	channel.Profile_Banner.Set(*wrapper[U("profile_banner")]);
	channel.Profile_Banner_Background_Color.Set(*wrapper[U("profile_banner_background_color")]);
	channel.Partner.Set(*wrapper[U("partner")]);
	channel.Url.Set(*wrapper[U("url")]);
	channel.Views.Set(*wrapper[U("views")]);
	channel.Followers.Set(*wrapper[U("followers")]);
	channel.Stream_Key.Set(*wrapper[U("stream_key")]);

	return channel;
}

template <>
TwitchXX::TwitchFollower TwitchXX::Create<TwitchXX::TwitchFollower>(const web::json::value& value)
{
	TwitchFollower follower;
	JsonWrapper wrapper(value);

	follower.Created.from_string(*wrapper[U("created_at")]);
	follower.Notifications.Set(*wrapper[U("notifications")]);
	
	follower.User = Create<TwitchUser>(value.at(U("user")));

	return  follower;
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
