#include <fstream>
#include "TwitchXX.h"
#include "TwitchGames.h"
#include "TwitchStreams.h"
#include "TwitchChannels.h"
#include "TwitchChannelFeed.h"
#include "TwitchChat.h"
#include "TwitchIngests.h"
#include "TwitchUsers.h"
#include "TwitchTeams.h"
#include "TwitchVideos.h"

namespace TwitchXX
{
	std::shared_ptr<Logger> Log;
	extern void trim(utility::string_t& s);
    std::shared_ptr<MakeRequest> _request;
}
TwitchXX::Api3::Api3(std::weak_ptr<Logger> log,const utility::string_t& client_id)
{
	//reading options
	utility::ifstream_t options_file("twitchxx.cfg");
	utility::string_t line;
    std::map<utility::string_t,utility::string_t> options;
	while(std::getline(options_file,line))
	{
		utility::stringstream_t iss(line);
		utility::string_t name, value;
		std::getline(iss, name, U('='));
		std::getline(iss, value);
		trim(name);
		trim(value);
        options[name] = value;
	}

    if(client_id.size())
    {
        // Api_key will be overridden by the input parameter
        options[U("api_key")] = client_id;
    }

    options[U("version")] = GetApiVersionString(TwitchXX::Version::v3);

	_request = std::make_shared<MakeRequest>(options);

	Log = std::make_shared<Logger>();
	Log->Subscribe(log);
}

void TwitchXX::Api3::AddLogger(std::shared_ptr<Logger>log)
{
	if(log != nullptr)
	{
		Log->Subscribe(log);
	}
}

TwitchXX::TwitchGamesContainer TwitchXX::Api3::TopGames(unsigned int top_count) const
{
    TwitchGames _games(*_request);
	return _games.GetTopGames(top_count);
}

TwitchXX::TwitchStream TwitchXX::Api3::GetStream(const utility::string_t& name) const
{
    TwitchStreams _streams(*_request);
	return  _streams.GetStream(name);
}

TwitchXX::TwitchStreamsContainer TwitchXX::Api3::TopStreams(unsigned int top_count, const options& op) const
{
    TwitchStreams _streams(*_request);
	return _streams.GetStreams(top_count, op);
}

TwitchXX::TwitchFeaturedStreamsContainer TwitchXX::Api3::GetFeaturedStreams() const
{
    TwitchStreams _streams(*_request);
	return _streams.GetFeaturedStreams();
}

std::tuple<unsigned int, unsigned int> TwitchXX::Api3::GetSummary(const utility::string_t& game) const
{
    TwitchStreams _streams(*_request);
	return _streams.GetSummary(game);
}

TwitchXX::TwitchStreamsContainer TwitchXX::Api3::FollowedStreams() const
{
    TwitchStreams _streams(*_request);
	return _streams.GetFollowedStreams();
}

TwitchXX::TwitchChannel TwitchXX::Api3::GetChannel(const utility::string_t & name) const
{
    TwitchChannels _channels(*_request);
	return _channels.GetChannel(name);
}

TwitchXX::TwitchUsersContainer TwitchXX::Api3::GetChannelEditors(const utility::string_t& channel_name) const
{
    TwitchChannels _channels(*_request);
	return _channels.GetChannelEditors(channel_name);
}

TwitchXX::TwitchChannel TwitchXX::Api3::UpdateChannel(const utility::string_t& channel_name, const TwitchXX::options& op) const
{
    TwitchChannels _channels(*_request);
	return _channels.UpdateChannel(channel_name, op);
}

utility::string_t TwitchXX::Api3::ResetStreamKey(const utility::string_t& channel_name) const
{
    TwitchChannels _channels(*_request);
	return _channels.ResetStreamKey(channel_name);
}

bool TwitchXX::Api3::StartCommercial(const utility::string_t& channel_name, unsigned int length) const
{
    TwitchChannels _channels(*_request);
	return _channels.StartCommercial(channel_name, length);
}

TwitchXX::TwitchTeamsContainer TwitchXX::Api3::GetTeams(const utility::string_t& channel_name) const
{
    TwitchChannels _channels(*_request);
	return _channels.GetTeams(channel_name);
}

TwitchXX::TwitchFollowersContainer TwitchXX::Api3::GetChannelFollows(const utility::string_t& channel_name) const
{
    TwitchChannels _channels(*_request);
	return _channels.GetChannelFollows(channel_name);
}

TwitchXX::TwitchFollowersContainer TwitchXX::Api3::GetChannelSubscriptions(const utility::string_t& channel_name) const
{
    TwitchChannels _channels(*_request);
	return _channels.GetChannelSubscriptions(channel_name);
}

TwitchXX::TwitchFollower TwitchXX::Api3::GetChannelSubscriptionForUser(const utility::string_t& channel_name, const utility::string_t& user_name) const
{
    TwitchChannels _channels(*_request);
	return _channels.GetChannelSubscriptionForUser(channel_name, user_name);
}

TwitchXX::TwitchVideosContainer TwitchXX::Api3::GetChannelVideos(const utility::string_t& channel_name, bool broadcasts, bool hls) const
{
	options op;
	if(broadcasts)
	{
		op[U("broadcasts")] = U("true");
	}
	if(hls)
	{
		op[U("hls")] = U("true");
	}
	op[U("limit")] = U("100");
    TwitchChannels _channels(*_request);
	return _channels.GetChannelVideos(channel_name, op);
}

TwitchXX::TwitchPostsContainer TwitchXX::Api3::GetPosts(const utility::string_t &channel_name, unsigned int limit) const
{
    TwitchChannelFeed _channel_feed(*_request);
	return _channel_feed.GetPosts(channel_name, limit);
}

TwitchXX::TwitchPost TwitchXX::Api3::GetPost(const utility::string_t &channel_name, const utility::string_t &id) const
{
    TwitchChannelFeed _channel_feed(*_request);
	return _channel_feed.GetPost(channel_name, id);
}

TwitchXX::TwitchPost TwitchXX::Api3::Post(const utility::string_t& channel_name, const utility::string_t& body, bool share) const
{
    TwitchChannelFeed _channel_feed(*_request);
	return _channel_feed.Post(channel_name, body, share);
}

bool TwitchXX::Api3::DeletePost(const utility::string_t & channel_name, const utility::string_t& id) const
{
    TwitchChannelFeed _channel_feed(*_request);
	return _channel_feed.DeletePost(channel_name, id);
}

bool TwitchXX::Api3::AddReaction(const utility::string_t& channel_name, const utility::string_t& id, unsigned int emote_id) const
{
    TwitchChannelFeed _channel_feed(*_request);
	return _channel_feed.AddReaction(channel_name, id, emote_id);
}

bool TwitchXX::Api3::RemoveReaction(const utility::string_t &channel_name, const utility::string_t &id,
								   unsigned int emote_id) const
{
    TwitchChannelFeed _channel_feed(*_request);
	return _channel_feed.RemoveReaction(channel_name, id, emote_id);
}

TwitchXX::TwitchEmoticonsContainer TwitchXX::Api3::GetEmoticons() const
{
    TwitchChat _chat(*_request);
	return _chat.GetEmoticons();
}

std::set<TwitchXX::EmoticonImage> TwitchXX::Api3::GetEmoticoneImages(std::set<unsigned int> sets) const
{
    TwitchChat _chat(*_request);
	return _chat.GetEmoticoneImages(sets);
}

std::set<TwitchXX::ChannelBadge> TwitchXX::Api3::GetChannelBadges(const utility::string_t &channel_name) const
{
    TwitchChat _chat(*_request);
	return _chat.GetChannelBadges(channel_name);
}

TwitchXX::TwitchBlockedUsersContainer TwitchXX::Api3::GetBlockedUsers(const utility::string_t& user_name) const
{
    TwitchUsers _users(*_request);
	return _users.GetBlocked(user_name);
}

TwitchXX::TwitchUser TwitchXX::Api3::BlockUser(const utility::string_t &user_name, const utility::string_t &target_name) const
{
    TwitchUsers _users(*_request);
	return _users.BlockUser(user_name, target_name);
}

bool TwitchXX::Api3::UnblockUser(const utility::string_t& user_name, const utility::string_t& target_name) const
{
    TwitchUsers _users(*_request);
	return _users.UblockUser(user_name, target_name);
}

TwitchXX::TwitchFollowedChannelsContainer TwitchXX::Api3::GetChannelsFollowedByUser(const utility::string_t& user_name, Sort_Order order) const
{
    TwitchUsers _users(*_request);
	return _users.GetFollowingChannels(user_name, order);
}

TwitchXX::TwitchFollowedChannel TwitchXX::Api3::GetFollowingChannel(const utility::string_t& user_name, const utility::string_t& channel_name) const
{
    TwitchUsers _users(*_request);
	return _users.GetFollowingChannel(user_name, channel_name);
}

TwitchXX::TwitchFollowedChannel TwitchXX::Api3::FollowChannel(const utility::string_t& user_name, const utility::string_t& channel_name, bool notification) const
{
    TwitchUsers _users(*_request);
	return _users.FollowChannel(user_name, channel_name, notification);
}

void TwitchXX::Api3::UnfollowChannel(const utility::string_t & user_name, const utility::string_t & channel_name) const
{
    TwitchUsers _users(*_request);
	_users.UnfollowChannel(user_name, channel_name);
}

TwitchXX::AuthToken TwitchXX::Api3::GetCurrentUserStatus() const
{
    TwitchUsers _users(*_request);
	return _users.GetCurrentUserStatus();
}

TwitchXX::TwitchFollowedChannel TwitchXX::Api3::GetUserSubscribedChannel(const utility::string_t& channel_name, const utility::string_t& user_name) const
{
    TwitchUsers _users(*_request);
	return _users.GetUserSubscribedChannel(channel_name, user_name);
}

TwitchXX::TwitchUser TwitchXX::Api3::GetUser(const utility::string_t& user_name) const
{
    TwitchUsers _users(*_request);
	return _users.GetUser(user_name);
}

std::set<TwitchXX::EmoticonImage> TwitchXX::Api3::GetUserEmoticons(const utility::string_t& user_name) const
{
    TwitchUsers _users(*_request);
	return _users.GetUserEmoticons(user_name);
}

TwitchXX::TwitchUser TwitchXX::Api3::GetCurrentUser() const
{
    TwitchUsers _users(*_request);
	return _users.GetCurrentUser();
}

TwitchXX::TwitchIngestsContainer TwitchXX::Api3::GetIngetst() const
{
    TwitchIngests _ingests(*_request);
	return _ingests.GetIngests();
}

TwitchXX::TwitchTeamsContainer TwitchXX::Api3::GetTeams() const
{
    TwitchTeams _teams(*_request);
	return _teams.GetTeams();
}

TwitchXX::TwitchTeam TwitchXX::Api3::GetTeam(const utility::string_t& team) const
{
    TwitchTeams _teams(*_request);
	return _teams.GetTeam(team);
}

TwitchXX::TwitchVideo TwitchXX::Api3::GetVideo(unsigned long long id) const
{
    TwitchVideos _videos(*_request);
	return _videos.GetVideo(id);
}

TwitchXX::TwitchVideosContainer TwitchXX::Api3::GetTopVideo(const utility::string_t& game, const utility::string_t& period) const
{
	options op;
	if(game.size())
	{
		op[U("game")] = game;
	}
	if(period.size())
	{
		op[U("period")] = period;
	}
    TwitchVideos _videos(*_request);
	return _videos.GetTopVideos(op);
}

TwitchXX::TwitchVideosContainer TwitchXX::Api3::GetFollowedVideo(const utility::string_t& broadcast_type) const
{
	options op;
	op[U("limit")] = U("100");
	if(broadcast_type.size())
	{
		op[U("broadcast_type")] = broadcast_type;
	}

    TwitchVideos _videos(*_request);
	return _videos.GetFollowedVideos(op);
}

utility::string_t TwitchXX::Api3::GetApiVersionString(TwitchXX::Version v)
{
    switch (v)
    {
        case Version::v2:
            return U("application/vnd.twitchtv.v2+json");
        case Version::v3:
            return U("application/vnd.twitchtv.v3+json");
        default:
            return U("UNSUPPORTED API VERSION!");
    }
}
