#pragma once

#include <cpprest/json.h>
#include "TwitchChannel.h"
#include "TwitchRequest.h"
#include "TwitchDef.h"
#include "TwitchUser.h"
#include "TwitchTeam.h"

namespace TwitchXX
{
	///Twitch channels request object
	/** This class encapsulates all requests that are related to twitch channel operations (excluding channel feed. See TwitchChannelFeed. )*/
	class TwitchChannels : public TwitchRequest<TwitchChannel>
	{
	public:
		///Constructor
		///@param request transport object
		explicit TwitchChannels(std::shared_ptr<MakeRequest> request);

		///Get channel object
		///@param name requested channel name. If empty - returns a channel object of authenticated user.
		///@return TwitchChannel object
		TwitchChannel GetChannel(const std::wstring& name = std::wstring()) const;

		///Returns a list of user objects who are editors of requested channel
		///@param name channel name
		///@return TwitchUser collection
		TwitchUsersContainer GetChannelEditors(const std::wstring& name) const;

		///Update channel's properties.
		///@param name channel name
		///@param op channel properties collection. The keys for the collection can be as follows (all are optional)
		/**
		* Name				   | Description
		* -------------		   | -------------
		* status			   | Channel's title. 
		* game				   | Game category to be classified as.
		* delay				   | Channel delay in seconds. Requires the channel owner's OAuth token.
		* channel_feed_enabled | Whether the channel's feed is enabled. Requires the channel owner's OAuth token.
		*/
		///@return TwitchChannel object with updated values
		TwitchChannel UpdateChannel(const std::wstring& name, const options& op) const;

		///Resets channel's stream key.
		///@param channel_name channel name
		///@return new channel's stream key
		std::wstring ResetStreamKey(const std::wstring& channel_name) const;

		///Start commercial on channel.
		///@param channel_name channel name
		/**@param length Length of commercial break in seconds. Default value is 30. 
		* Valid values are 30, 60, 90, 120, 150, and 180. You can only trigger a commercial once every 8 minutes.*/
		///@return true if operation was successfull, false otherwise.
		bool StartCommercial(const std::wstring& channel_name, size_t length = 30) const;

		///Returns a list of team objects channel belongs to.
		///@param channel_name channel name
		TwitchTeamsContainer GetTeams(const std::wstring& channel_name) const;

		///Returns a list of followers for given channel
		///@param channel_name channel name
		TwitchFollowersContainer GetChannelFollows(const std::wstring& channel_name) const;

		///Returns a list of subscription objects sorted by subscription relationship creation date which contain users subscribed to channel.
		///required scope: AuthScope::CHANNEL_SUBSCRIPTIONS
		///@param channel_name channel name
		///@return subscription objects collection
		TwitchFollowersContainer GetChannelSubscriptions(const std::wstring& channel_name) const;

		///Returns a list of subscription objects sorted by subscription relationship creation date which contain users subscribed to channel
		///required scope: AuthScope::CHANNEL_CHECK_SUBSCRIPTION
		///@param channel_name channel name
		///@param user_name user name to check subscription for
		///@return subscription object for user if he is subscribed to given channel
		TwitchFollower GetChannelSubscriptionForUser(const std::wstring& channel_name, const std::wstring& user_name) const;
	};

	template<> TwitchChannel Create<TwitchChannel>(const web::json::value& value); ///< Constructs TwitchChannel object from json
	template<> TwitchFollower Create<TwitchFollower>(const web::json::value& value); ///< Constructs follower object from json
}

