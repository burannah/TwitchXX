#include "TwitchChannels.h"
#include "JsonWrapper.h"
#include "TwitchException.h"
#include "TwitchUsers.h"
#include "TwitchFollower.h"
#include "TwitchTeams.h"
#include "TwitchVideo.h"
#include "TwitchVideos.h"


TwitchXX::TwitchChannel TwitchXX::TwitchChannels::GetChannel(const std::wstring & name) const
{
	//TODO: add test for getting channel of authenticated user
	std::wstring request_string = U("/channel");
	if (name.length() > 0)
	{
		request_string += U("s/") + name + U("/");
	}

	web::uri_builder builder (U("/channels/") + name + U("/"));
	auto value = _request->get(builder.to_uri());
	if (value.is_null())
	{
		throw std::runtime_error("No objects were returned");
	}

	return Create<TwitchChannel>(value);

}
TwitchXX::TwitchUsersContainer TwitchXX::TwitchChannels::GetChannelEditors(const std::wstring & name) const
{
	web::uri_builder builder(U("/channels/") + name + U("/editors"));
	return GetObjectsArrayOnce<TwitchUser>(builder, U("users"));
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

	auto value = _request->put(builder.to_uri(),requestJSON);
	if (value.is_null() || _request->status_code() == 422)
	{
		throw std::runtime_error("The channel is not partnered!");
	}

	return Create<TwitchChannel>(value);
}

std::wstring TwitchXX::TwitchChannels::ResetStreamKey(const std::wstring& channel_name) const
{
	web::uri_builder builder(U("/channels/") + channel_name + U("/stream_key"));
	auto value = _request->del(builder.to_uri());

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
	auto value = _request->post(builder.to_uri());

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
	return GetObjectsArrayOnce<TwitchTeam>(builder, U("teams"));
}

TwitchXX::TwitchFollowersContainer TwitchXX::TwitchChannels::GetChannelFollows(const std::wstring& channel_name) const
{
	web::uri_builder builder(U("/channels/") + channel_name + U("/follows"));
	builder.append_query(U("limit"), 100);
	return GetObjectsArrayByCursor<TwitchFollower>(builder, U("follows"));
}

TwitchXX::TwitchFollowersContainer TwitchXX::TwitchChannels::GetChannelSubscriptions(const std::wstring& channel_name) const
{
	static const size_t limit = 100; //TODO: To some global constants
	web::uri_builder builder(U("/channels/") + channel_name + U("/subscriptions"));
	builder.append_query(U("limit"), 100);
	//builder.append_query(U("direction"), Direction::asc);

	return this->GetObjectsArrayByNext<TwitchFollower>(builder, U("subscriptions"));
}

TwitchXX::TwitchFollower TwitchXX::TwitchChannels::GetChannelSubscriptionForUser(const std::wstring& channel_name, const std::wstring& user_name) const
{
	web::uri_builder builder{ U("/channels/") + channel_name + U("/subscriptions/") + user_name };

	try
	{
		auto response = _request->get(builder.to_uri());
		return Create<TwitchFollower>(response);
	}
	catch (TwitchException& e)
	{
		if (e.code() == web::http::status_codes::NotFound)
		{
			throw TwitchException("User is not subscribed", 404);
		}
		else
		{
			throw;
		}
	}
}

TwitchXX::TwitchVideosContainer TwitchXX::TwitchChannels::GetChannelVideos(const std::wstring& channel_name, options& op) const
{
	web::uri_builder builder(U("/channels") + channel_name + U("videos"));
	AddOption(builder, op, U("limit"));
	AddOption(builder, op, U("offset"));
	AddOption(builder, op, U("broadcasts"));
	AddOption(builder, op, U("hls"));
	return GetObjectsArrayByNext<TwitchVideo>(builder, U("videos"));
}

template<>
TwitchXX::TwitchChannel TwitchXX::Create<TwitchXX::TwitchChannel>(const web::json::value & value)
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
