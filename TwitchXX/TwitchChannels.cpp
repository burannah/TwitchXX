#include "TwitchChannels.h"
#include "JsonWrapper.h"
#include "TwitchException.h"


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
		o[U("status")] = channel.Status();
	}
	if(o.find(U("game")) == o.end())
	{
		o[U("game")] = channel.Game();
	}
	if(o.find(U("delay"))== o.end())
	{
		o[U("delay")] = std::to_wstring(channel.Delay());
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

template<>
TwitchXX::TwitchChannel TwitchXX::Create(const web::json::value & value)
{
	TwitchChannel channel;
	JsonWrapper wrapper(value);

	channel.Mature(*wrapper[U("mature")]);
	channel.Status(*wrapper[U("status")]);
	channel.BroadcasterLanguage(*wrapper[U("broadcaster_language")]);
	channel.DisplayName(*wrapper[U("display_name")]);
	channel.Game(*wrapper[U("game")]);
	channel.Delay(*wrapper[U("delay")]);
	channel.Language(*wrapper[U("language")]);
	channel.Id(*wrapper[U("_id")]);
	channel.Name(*wrapper[U("name")]);
	channel.Created(*wrapper[U("created_at")]);
	channel.Updated(*wrapper[U("updated_at")]);
	channel.Logo(*wrapper[U("logo")]);
	channel.Banner(*wrapper[U("banner")]);
	channel.VideoBanner(*wrapper[U("video_banner")]);
	channel.Background(*wrapper[U("background")]);
	channel.ProfileBanner(*wrapper[U("profile_banner")]);
	channel.ProfileBannerBkColor(*wrapper[U("profile_banner_background_color")]);
	channel.Partner(*wrapper[U("partner")]);
	channel.Url(*wrapper[U("url")]);
	channel.Views(*wrapper[U("views")]);
	channel.Followers(*wrapper[U("followers")]);
	channel.StreamKey(*wrapper[U("stream_key")]);

	return channel;
}

template<>
TwitchXX::TwitchUser TwitchXX::Create(const web::json::value & value)
{
	TwitchUser user;
	JsonWrapper wrapper(value);

	user.Created(*wrapper[U("created_at")]);
	user.Name(*wrapper[U("name")]);
	user.Updated(*wrapper[U("updated_at")]);
	user.Id(*wrapper[U("_id")]);
	user.DisplayName(*wrapper[U("display_name")]);
	user.Logo(*wrapper[U("logo")]);
	user.Type(*wrapper[U("type")]);
	user.Bio(*wrapper[U("bio")]);

	return user;
}

template <>
TwitchXX::TwitchTeam TwitchXX::Create<TwitchXX::TwitchTeam>(const web::json::value& value)
{
	TwitchTeam team;
	JsonWrapper wrapper(value);

	team.Created(*wrapper[U("created_at")]);
	team.Updated(*wrapper[U("updated_at")]);
	team.Id(*wrapper[U("_id")]);
	team.Background(*wrapper[U("background")]);
	team.Name(*wrapper[U("name")]);
	team.Info(*wrapper[U("info")]);
	team.DisplayName(*wrapper[U("display_name")]);
	team.Logo(*wrapper[U("logo")]);
	team.Banner(*wrapper[U("banner")]);

	return team;
}
