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
#include "TwitchVideos.h"

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
		explicit Api(const utility::string_t& clinet_id = {}, Version version = Version::v3, std::shared_ptr<Logger> = nullptr);
		Api(const Api&) = default;
		Api(Api&& ) = default;
		virtual ~Api();
		//Log
		static void AddLogger(std::shared_ptr<Logger>log);

		//Games
		TwitchGamesContainer TopGames(unsigned int top_count = 0) const;

		//Streams
		TwitchStream GetStream(const utility::string_t& name) const;
		TwitchStreamsContainer TopStreams(unsigned int top_count = {}, const options& op = {}) const;
		TwitchFeaturedStreamsContainer GetFeaturedStreams() const;
		std::tuple<unsigned int, unsigned int> GetSummary(const utility::string_t& game = {}) const;
		TwitchStreamsContainer FollowedStreams() const;

		//Channels
		TwitchChannel GetChannel(const utility::string_t& name) const;
		TwitchUsersContainer GetChannelEditors(const utility::string_t& channel_name) const;
		TwitchChannel UpdateChannel(const utility::string_t& channel_name, const options& op) const;
		utility::string_t ResetStreamKey(const utility::string_t& channel_name) const;
		bool StartCommercial(const utility::string_t& channel_name, unsigned int length) const;
		TwitchTeamsContainer GetTeams(const utility::string_t& channel_name) const;
		TwitchFollowersContainer GetChannelFollows(const utility::string_t& channel_name) const;
		TwitchFollowersContainer GetChannelSubscriptions(const utility::string_t& channel_name) const;
		TwitchFollower GetChannelSubscriptionForUser(const utility::string_t& channel_name, const utility::string_t& user_name) const;
		TwitchVideosContainer GetChannelVideos(const utility::string_t& channel_name, bool broadcasts = false, bool hls = false) const;

		//Channel Feed
		TwitchPostsContainer GetPosts(const utility::string_t& channel_name, unsigned int count = 0) const;
		TwitchPost GetPost(const utility::string_t& channel_name, unsigned long long id) const;
		TwitchPost Post(const utility::string_t& channel_name, const utility::string_t& body, bool share = false) const;
		bool DeletePost(const utility::string_t& channel_name, unsigned long long id) const;
		bool AddReaction(const utility::string_t& channel_name, unsigned long long id, unsigned int emote_id) const;
		bool RemoveReaction(const utility::string_t& channel_name, unsigned long long id, unsigned int emote_id) const;

		//Chat
		TwitchEmoticonsContainer GetEmoticons() const;
		std::set<EmoticonImage> GetEmoticoneImages(std::set<unsigned int> sets = {}) const;
		std::set<ChannelBadge> GetChannelBadges(const utility::string_t &channel_name) const;

		//Users
		TwitchBlockedUsersContainer GetBlockedUsers(const utility::string_t& user_name) const;
		TwitchBlockedUser BlockUser(const utility::string_t& user_name, const utility::string_t& target_name) const;
		bool UnblockUser(const utility::string_t& user_name, const utility::string_t& target_name) const;
		TwitchFollowedChannelsContainer GetChannelsFollowedByUser(const utility::string_t& user_name, Sort_Order order = Sort_Order::Created) const;
		TwitchFollowedChannel GetFollowingChannel(const utility::string_t& user_name, const utility::string_t& channel_name) const;
		TwitchFollowedChannel FollowChannel(const utility::string_t& user_name, const utility::string_t& channel_name, bool notification = false) const;
		void UnfollowChannel(const utility::string_t& user_name, const utility::string_t& channel_name) const;
		AuthToken GetCurrentUserStatus() const;
		TwitchFollowedChannel GetUserSubscribedChannel(const utility::string_t& channel_name, const utility::string_t& user_name) const;
		TwitchUser GetUser(const utility::string_t& user_name) const;
		std::set<EmoticonImage> GetUserEmoticons(const utility::string_t& user_name) const;
		TwitchUser GetCurrentUser() const;

		//Ingests
		TwitchIngestsContainer GetIngetst() const;

		//Teams
		TwitchTeamsContainer GetTeams() const;
		TwitchTeam GetTeam(const utility::string_t& team) const;

		//Videos
		TwitchVideo GetVideo(unsigned long long id) const;
		TwitchVideosContainer GetTopVideo(const utility::string_t& game = U(""), const utility::string_t& period = U("week")) const;
		TwitchVideosContainer GetFollowedVideo(const utility::string_t& broadcast_type) const;


	private:
		static std::map<Version, utility::string_t> _version;
	};
}
