#pragma once

/** @defgroup TwitchXX
*
* This is a main module for accessing Twitch API
*
*/

#include <memory>
#include "TwitchGame.h"
#include "TwitchStream.h"
#include "TwitchFeaturedStream.h"
#include "TwitchPost.h"
#include "TwitchUsers.h"
#include "TwitchFollower.h"
#include "TwitchIngests.h"
#include "TwitchTeams.h"

namespace TwitchXX
{

	class Logger;
	class TwitchStreams;
	class TwitchChannels;
	class TwitchChannelFeed;
	class TwitchChat;
	class TwitchGames;

	class Api
	{
	public:
		enum class Version
		{
			v2,
			v3
		};
		explicit Api(const std::wstring& clinet_id = std::wstring(), Version version = Version::v3, std::shared_ptr<Logger> = nullptr);
		virtual ~Api();
		//Log
		static void AddLogger(std::shared_ptr<Logger>log);

		//Games
		TwitchGamesContainer TopGames(size_t top_count = 0) const;

		//Streams
		TwitchStream GetStream(const std::wstring& name) const;
		TwitchStreamsContainer TopStreams(size_t top_count = 0, const options& op = options()) const;
		TwitchFeaturedStreamsContainer GetFeaturedStreams() const;
		std::tuple<size_t, size_t> GetSummary(const std::wstring& game = std::wstring()) const;
		TwitchStreamsContainer FollowedStreams() const;

		//Channels
		TwitchChannel GetChannel(const std::wstring& name) const;
		TwitchUsersContainer GetChannelEditors(const std::wstring& channel_name) const;
		TwitchChannel UpdateChannel(const std::wstring& channel_name, const options& op) const;
		std::wstring ResetStreamKey(const std::wstring& channel_name) const;
		bool StartCommercial(const std::wstring& channel_name, size_t length) const;
		TwitchTeamsContainer GetTeams(const std::wstring& channel_name) const;
		TwitchFollowersContainer GetChannelFollows(const std::wstring& channel_name) const;
		TwitchFollowersContainer GetChannelSubscriptions(const std::wstring& channel_name) const;
		TwitchFollower GetChannelSubscriptionForUser(const std::wstring& channel_name, const std::wstring& user_name) const;

		//Channel Feed
		TwitchPostsContainer GetPosts(const std::wstring& channel_name, size_t count = 0) const;
		TwitchPost GetPost(const std::wstring& channel_name, unsigned long long id) const;
		TwitchPost Post(const std::wstring& channel_name, const std::wstring& body, bool share = false) const;
		bool DeletePost(const std::wstring& channel_name, unsigned long long id) const;
		bool AddReaction(const std::wstring& channel_name, unsigned long long id, size_t emote_id) const;
		bool RemoveReaction(const std::wstring& channel_name, unsigned long long id, size_t emote_id) const;

		//Chat
		TwitchEmoticonsContainer GetEmoticons() const;
		std::set<EmoticonImage> GetEmoticoneImages(std::set<size_t> sets = std::set<size_t>()) const;
		std::set<ChannelBadge> GetChannelBadges(std::wstring& channel_name) const;

		//Users
		TwitchBlockedUsersContainer GetBlockedUsers(const std::wstring& user_name) const;
		TwitchBlockedUser BlockUser(const std::wstring& user_name, const std::wstring& target_name) const;
		bool UnblockUser(const std::wstring& user_name, const std::wstring& target_name) const;
		TwitchFollowedChannelsContainer GetChannelsFollowedByUser(const std::wstring& user_name, Sort_Order order = Sort_Order::Created) const;
		TwitchFollowedChannel GetFollowingChannel(const std::wstring& user_name, const std::wstring& channel_name) const;
		TwitchFollowedChannel FollowChannel(const std::wstring& user_name, const std::wstring& channel_name, bool notification = false) const;
		void UnfollowChannel(const std::wstring& user_name, const std::wstring& channel_name) const;
		AuthToken GetCurrentUserStatus() const;
		TwitchFollowedChannel GetUserSubscribedChannel(const std::wstring& channel_name, const std::wstring& user_name) const;
		TwitchUser GetUser(const std::wstring& user_name) const;
		std::set<EmoticonImage> GetUserEmoticons(const std::wstring& user_name) const;
		TwitchUser GetCurrentUser() const;

		//Ingests
		TwitchIngestsContainer GetIngetst() const;

		//Teams
		TwitchTeamsContainer GetTeams() const;
		TwitchTeam GetTeam(const std::wstring& team) const;


	private:
		static std::map<Version, std::wstring> _version;
		std::unique_ptr<TwitchStreams> _streams;
		std::unique_ptr<TwitchChannels> _channels;
		std::unique_ptr<TwitchChannelFeed> _channel_feed;
		std::unique_ptr<TwitchChat> _chat;
		std::unique_ptr<TwitchGames> _games;
		std::unique_ptr<TwitchUsers> _users;
		std::unique_ptr<TwitchIngests> _ingests;
		std::unique_ptr<TwitchTeams> _teams;


	};
}
