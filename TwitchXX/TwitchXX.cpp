#include <fstream>
#include "TwitchXX.h"
#include "TwitchGames.h"
#include "TwitchStreams.h"
#include "TwitchChannels.h"
#include "TwitchChannelFeed.h"
#include "TwitchChat.h"
#include "TwitchIngests.h"

namespace TwitchXX
{
	class TwitchStreams;
	std::shared_ptr<std::map<utility::string_t,utility::string_t>> Options = {};
	std::string DatabaseName = "TwitchSpy";
	std::shared_ptr<Logger> Log = std::make_shared<Logger>();
	extern void trim(utility::string_t& s);
}

std::map<TwitchXX::Api::Version,utility::string_t> TwitchXX::Api::_version =
{
	{ Version::v2, U("application/vnd.twitchtv.v2+json") },
	{ Version::v3, U("application/vnd.twitchtv.v3+json") }
};

TwitchXX::Api::Api(const utility::string_t& client_id, Version version, std::shared_ptr<Logger> log)
{
	//reading options
	utility::ifstream_t options_file("twitchxx.cfg");
	utility::string_t line;
	while(std::getline(options_file,line))
	{
		utility::stringstream_t iss(line);
		utility::string_t name, value;
		std::getline(iss, name, U('='));
		std::getline(iss, value);
		trim(name);
		trim(value);

		Options->insert(std::make_pair(name, value));
	}
	if (client_id.size() && Options->find(U("api_key")) != Options->end())
	{
		//Do not override config file's api_key parameter event if explicitly provided by parameter
		Options->insert(std::make_pair(U("api_key"), client_id));
	}
	Options->insert(std::make_pair(U("version"), _version[version]));

	auto request = std::make_shared<MakeRequest>((*Options)[U("version")], (*Options)[U("api_key")], (*Options)[U("token")]);

	_streams = std::make_unique<TwitchStreams>(request);
	_channels = std::make_unique<TwitchChannels>(request);
	_channel_feed = std::make_unique<TwitchChannelFeed>(request);
	_chat = std::make_unique<TwitchChat>(request);
	_games = std::make_unique<TwitchGames>(request);
	_users = std::make_unique<TwitchUsers>(request);
	_ingests = std::make_unique<TwitchIngests>(request);
	_teams = std::make_unique<TwitchTeams>(request);
	_videos = std::make_unique<TwitchVideos>(request);

	if(log != nullptr)
	{
		Log->Subscribe(log);
	}
	Log->Log(U("Api created"));
}


TwitchXX::Api::~Api()
{
	Log->Log(U("Api destroyed"));
}

void TwitchXX::Api::AddLogger(std::shared_ptr<Logger>log)
{
	if(log != nullptr)
	{
		Log->Subscribe(log);
	}
}

TwitchXX::TwitchGamesContainer TwitchXX::Api::TopGames(unsigned int top_count) const
{
	return _games->GetTopGames(top_count);
}

TwitchXX::TwitchStream TwitchXX::Api::GetStream(const utility::string_t& name) const
{
	return  _streams->GetStream(name);
}

TwitchXX::TwitchStreamsContainer TwitchXX::Api::TopStreams(unsigned int top_count, const options& op) const
{
	return _streams->GetStreams(top_count, op);
}

TwitchXX::TwitchFeaturedStreamsContainer TwitchXX::Api::GetFeaturedStreams() const
{
	return _streams->GetFeaturedStreams();
}

std::tuple<unsigned int, unsigned int> TwitchXX::Api::GetSummary(const utility::string_t& game) const
{
	return _streams->GetSummary(game);
}

TwitchXX::TwitchStreamsContainer TwitchXX::Api::FollowedStreams() const
{
	return _streams->GetFollowedStreams();
}

TwitchXX::TwitchChannel TwitchXX::Api::GetChannel(const utility::string_t & name) const
{
	return _channels->GetChannel(name);
}

TwitchXX::TwitchUsersContainer TwitchXX::Api::GetChannelEditors(const utility::string_t& channel_name) const
{
	return _channels->GetChannelEditors(channel_name);
}

TwitchXX::TwitchChannel TwitchXX::Api::UpdateChannel(const utility::string_t& channel_name, const TwitchXX::options& op) const
{
	return _channels->UpdateChannel(channel_name, op);
}

utility::string_t TwitchXX::Api::ResetStreamKey(const utility::string_t& channel_name) const
{
	return _channels->ResetStreamKey(channel_name);
}

bool TwitchXX::Api::StartCommercial(const utility::string_t& channel_name, unsigned int length) const
{
	return _channels->StartCommercial(channel_name, length);
}

TwitchXX::TwitchTeamsContainer TwitchXX::Api::GetTeams(const utility::string_t& channel_name) const
{
	return _channels->GetTeams(channel_name);
}

TwitchXX::TwitchFollowersContainer TwitchXX::Api::GetChannelFollows(const utility::string_t& channel_name) const
{
	return _channels->GetChannelFollows(channel_name);
}

TwitchXX::TwitchFollowersContainer TwitchXX::Api::GetChannelSubscriptions(const utility::string_t& channel_name) const
{
	return _channels->GetChannelSubscriptions(channel_name);
}

TwitchXX::TwitchFollower TwitchXX::Api::GetChannelSubscriptionForUser(const utility::string_t& channel_name, const utility::string_t& user_name) const
{
	return _channels->GetChannelSubscriptionForUser(channel_name, user_name);
}

TwitchXX::TwitchVideosContainer TwitchXX::Api::GetChannelVideos(const utility::string_t& channel_name, bool broadcasts, bool hls) const
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
	return _channels->GetChannelVideos(channel_name, op);
}

TwitchXX::TwitchPostsContainer TwitchXX::Api::GetPosts(const utility::string_t& channel_name, unsigned int count) const
{
	return _channel_feed->GetPosts(channel_name, count);
}

TwitchXX::TwitchPost TwitchXX::Api::GetPost(const utility::string_t& channel_name, unsigned long long id) const
{
	return _channel_feed->GetPost(channel_name, id);
}

TwitchXX::TwitchPost TwitchXX::Api::Post(const utility::string_t& channel_name, const utility::string_t& body, bool share) const
{
	return _channel_feed->Post(channel_name, body, share);
}

bool TwitchXX::Api::DeletePost(const utility::string_t & channel_name, unsigned long long id) const
{
	return _channel_feed->DeletePost(channel_name, id);
}

bool TwitchXX::Api::AddReaction(const utility::string_t & channel_name, unsigned long long id, unsigned int emote_id) const
{
	return _channel_feed->AddReaction(channel_name, id, emote_id);
}

bool TwitchXX::Api::RemoveReaction(const utility::string_t & channel_name, unsigned long long id, unsigned int emote_id) const
{
	return _channel_feed->RemoveReaction(channel_name, id, emote_id);
}

TwitchXX::TwitchEmoticonsContainer TwitchXX::Api::GetEmoticons() const
{
	return _chat->GetEmoticons();
}

std::set<TwitchXX::EmoticonImage> TwitchXX::Api::GetEmoticoneImages(std::set<unsigned int> sets) const
{
	return _chat->GetEmoticoneImages(sets);
}

std::set<TwitchXX::ChannelBadge> TwitchXX::Api::GetChannelBadges(const utility::string_t &channel_name) const
{
	return _chat->GetChannelBadges(channel_name);
}

TwitchXX::TwitchBlockedUsersContainer TwitchXX::Api::GetBlockedUsers(const utility::string_t& user_name) const
{
	return _users->GetBlocked(user_name);
}

TwitchXX::TwitchBlockedUser TwitchXX::Api::BlockUser(const utility::string_t& user_name, const utility::string_t& target_name) const
{
	return _users->BlockUser(user_name, target_name);
}

bool TwitchXX::Api::UnblockUser(const utility::string_t& user_name, const utility::string_t& target_name) const
{
	return _users->UblockUser(user_name, target_name);
}

TwitchXX::TwitchFollowedChannelsContainer TwitchXX::Api::GetChannelsFollowedByUser(const utility::string_t& user_name, Sort_Order order) const
{
	return _users->GetFollowingChannels(user_name, order);
}

TwitchXX::TwitchFollowedChannel TwitchXX::Api::GetFollowingChannel(const utility::string_t& user_name, const utility::string_t& channel_name) const
{
	return _users->GetFollowingChannel(user_name, channel_name);
}

TwitchXX::TwitchFollowedChannel TwitchXX::Api::FollowChannel(const utility::string_t& user_name, const utility::string_t& channel_name, bool notification) const
{
	return _users->FollowChannel(user_name, channel_name, notification);
}

void TwitchXX::Api::UnfollowChannel(const utility::string_t & user_name, const utility::string_t & channel_name) const
{
	_users->UnfollowChannel(user_name, channel_name);
}

TwitchXX::AuthToken TwitchXX::Api::GetCurrentUserStatus() const
{
	return _users->GetCurrentUserStatus();
}

TwitchXX::TwitchFollowedChannel TwitchXX::Api::GetUserSubscribedChannel(const utility::string_t& channel_name, const utility::string_t& user_name) const
{
	return _users->GetUserSubscribedChannel(channel_name, user_name);
}

TwitchXX::TwitchUser TwitchXX::Api::GetUser(const utility::string_t& user_name) const
{
	return _users->GetUser(user_name);
}

std::set<TwitchXX::EmoticonImage> TwitchXX::Api::GetUserEmoticons(const utility::string_t& user_name) const
{
	return _users->GetUserEmoticons(user_name);
}

TwitchXX::TwitchUser TwitchXX::Api::GetCurrentUser() const
{
	return _users->GetCurrentUser();
}

TwitchXX::TwitchIngestsContainer TwitchXX::Api::GetIngetst() const
{
	return _ingests->GetIngests();
}

TwitchXX::TwitchTeamsContainer TwitchXX::Api::GetTeams() const
{
	return _teams->GetTeams();
}

TwitchXX::TwitchTeam TwitchXX::Api::GetTeam(const utility::string_t& team) const
{
	return _teams->GetTeam(team);
}

TwitchXX::TwitchVideo TwitchXX::Api::GetVideo(unsigned long long id) const
{
	return _videos->GetVideo(id);
}

TwitchXX::TwitchVideosContainer TwitchXX::Api::GetTopVideo(const utility::string_t& game, const utility::string_t& period) const
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
	return _videos->GetTopVideos(op);
}

TwitchXX::TwitchVideosContainer TwitchXX::Api::GetFollowedVideo(const utility::string_t& broadcast_type) const
{
	options op;
	op[U("limit")] = 100;
	if(broadcast_type.size())
	{
		op[U("broadcast_type")] = broadcast_type;
	}

	return _videos->GetFollowedVideos(op);
}
