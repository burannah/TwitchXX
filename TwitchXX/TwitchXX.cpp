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
	std::shared_ptr<std::map<std::wstring,std::wstring>> Options = std::make_shared<std::map<std::wstring, std::wstring>>();
	std::string DatabaseName = "TwitchSpy";
	std::shared_ptr<Logger> Log = std::make_shared<Logger>();
	extern void trim(std::wstring& s);
}

std::map<TwitchXX::Api::Version,std::wstring> TwitchXX::Api::_version =
{
	{ Version::v2, L"application/vnd.twitchtv.v2+json" },
	{ Version::v3, L"application/vnd.twitchtv.v3+json" }
};

TwitchXX::Api::Api(const std::wstring& client_id, Version version, std::shared_ptr<Logger> log)
{
	//reading options
	std::wifstream options_file("twitchxx.cfg");
	std::wstring line;
	while(std::getline(options_file,line))
	{
		std::wstringstream iss(line);
		std::wstring name, value;
		std::getline(iss, name, L'=');
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

TwitchXX::TwitchGamesContainer TwitchXX::Api::TopGames(size_t top_count) const
{
	return _games->GetTopGames(top_count);
}

TwitchXX::TwitchStream TwitchXX::Api::GetStream(const std::wstring& name) const
{
	return  _streams->GetStream(name);
}

TwitchXX::TwitchStreamsContainer TwitchXX::Api::TopStreams(size_t top_count, const options& op) const
{
	return _streams->GetStreams(top_count, op);
}

TwitchXX::TwitchFeaturedStreamsContainer TwitchXX::Api::GetFeaturedStreams() const
{
	return _streams->GetFeaturedStreams();
}

std::tuple<size_t, size_t> TwitchXX::Api::GetSummary(const std::wstring& game) const
{
	return _streams->GetSummary(game);
}

TwitchXX::TwitchStreamsContainer TwitchXX::Api::FollowedStreams() const
{
	return _streams->GetFollowedStreams();
}

TwitchXX::TwitchChannel TwitchXX::Api::GetChannel(const std::wstring & name) const
{
	return _channels->GetChannel(name);
}

TwitchXX::TwitchUsersContainer TwitchXX::Api::GetChannelEditors(const std::wstring& channel_name) const
{
	return _channels->GetChannelEditors(channel_name);
}

TwitchXX::TwitchChannel TwitchXX::Api::UpdateChannel(const std::wstring& channel_name, const TwitchXX::options& op) const
{
	return _channels->UpdateChannel(channel_name, op);
}

std::wstring TwitchXX::Api::ResetStreamKey(const std::wstring& channel_name) const
{
	return _channels->ResetStreamKey(channel_name);
}

bool TwitchXX::Api::StartCommercial(const std::wstring& channel_name, size_t length) const
{
	return _channels->StartCommercial(channel_name, length);
}

TwitchXX::TwitchTeamsContainer TwitchXX::Api::GetTeams(const std::wstring& channel_name) const
{
	return _channels->GetTeams(channel_name);
}

TwitchXX::TwitchFollowersContainer TwitchXX::Api::GetChannelFollows(const std::wstring& channel_name) const
{
	return _channels->GetChannelFollows(channel_name);
}

TwitchXX::TwitchFollowersContainer TwitchXX::Api::GetChannelSubscriptions(const std::wstring& channel_name) const
{
	return _channels->GetChannelSubscriptions(channel_name);
}

TwitchXX::TwitchFollower TwitchXX::Api::GetChannelSubscriptionForUser(const std::wstring& channel_name, const std::wstring& user_name) const
{
	return _channels->GetChannelSubscriptionForUser(channel_name, user_name);
}

TwitchXX::TwitchPostsContainer TwitchXX::Api::GetPosts(const std::wstring& channel_name, size_t count) const
{
	return _channel_feed->GetPosts(channel_name, count);
}

TwitchXX::TwitchPost TwitchXX::Api::GetPost(const std::wstring& channel_name, unsigned long long id) const
{
	return _channel_feed->GetPost(channel_name, id);
}

TwitchXX::TwitchPost TwitchXX::Api::Post(const std::wstring& channel_name, const std::wstring& body, bool share) const
{
	return _channel_feed->Post(channel_name, body, share);
}

bool TwitchXX::Api::DeletePost(const std::wstring & channel_name, unsigned long long id) const
{
	return _channel_feed->DeletePost(channel_name, id);
}

bool TwitchXX::Api::AddReaction(const std::wstring & channel_name, unsigned long long id, size_t emote_id) const
{
	return _channel_feed->AddReaction(channel_name, id, emote_id);
}

bool TwitchXX::Api::RemoveReaction(const std::wstring & channel_name, unsigned long long id, size_t emote_id) const
{
	return _channel_feed->RemoveReaction(channel_name, id, emote_id);
}

TwitchXX::TwitchEmoticonsContainer TwitchXX::Api::GetEmoticons() const
{
	return _chat->GetEmoticons();
}

std::set<TwitchXX::EmoticonImage> TwitchXX::Api::GetEmoticoneImages(std::set<size_t> sets) const
{
	return _chat->GetEmoticoneImages(sets);
}

std::set<TwitchXX::ChannelBadge> TwitchXX::Api::GetChannelBadges(std::wstring& channel_name) const
{
	return _chat->GetChannelBadges(channel_name);
}

TwitchXX::TwitchBlockedUsersContainer TwitchXX::Api::GetBlockedUsers(const std::wstring& user_name) const
{
	return _users->GetBlocked(user_name);
}

TwitchXX::TwitchBlockedUser TwitchXX::Api::BlockUser(const std::wstring& user_name, const std::wstring& target_name) const
{
	return _users->BlockUser(user_name, target_name);
}

bool TwitchXX::Api::UnblockUser(const std::wstring& user_name, const std::wstring& target_name) const
{
	return _users->UblockUser(user_name, target_name);
}

TwitchXX::TwitchFollowedChannelsContainer TwitchXX::Api::GetChannelsFollowedByUser(const std::wstring& user_name, Sort_Order order) const
{
	return _users->GetFollowingChannels(user_name, order);
}

TwitchXX::TwitchFollowedChannel TwitchXX::Api::GetFollowingChannel(const std::wstring& user_name, const std::wstring& channel_name) const
{
	return _users->GetFollowingChannel(user_name, channel_name);
}

TwitchXX::TwitchFollowedChannel TwitchXX::Api::FollowChannel(const std::wstring& user_name, const std::wstring& channel_name, bool notification) const
{
	return _users->FollowChannel(user_name, channel_name, notification);
}

void TwitchXX::Api::UnfollowChannel(const std::wstring & user_name, const std::wstring & channel_name) const
{
	_users->UnfollowChannel(user_name, channel_name);
}

TwitchXX::AuthToken TwitchXX::Api::GetCurrentUserStatus() const
{
	return _users->GetCurrentUserStatus();
}

TwitchXX::TwitchFollowedChannel TwitchXX::Api::GetUserSubscribedChannel(const std::wstring& channel_name, const std::wstring& user_name) const
{
	return _users->GetUserSubscribedChannel(channel_name, user_name);
}

TwitchXX::TwitchUser TwitchXX::Api::GetUser(const std::wstring& user_name) const
{
	return _users->GetUser(user_name);
}

std::set<TwitchXX::EmoticonImage> TwitchXX::Api::GetUserEmoticons(const std::wstring& user_name) const
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

TwitchXX::TwitchTeam TwitchXX::Api::GetTeam(const std::wstring& team) const
{
	return _teams->GetTeam(team);
}

TwitchXX::TwitchVideo TwitchXX::Api::GetVideo(unsigned long long id) const
{
	return _videos->GetVideo(id);
}

TwitchXX::TwitchVideosContainer TwitchXX::Api::GetTopVideo(const std::wstring& game, const std::wstring& period) const
{
	return _videos->GetTopVideos(game, period);
}
