#pragma once
#include "TwitchRequest.h"
#include "AuthToken.h"

namespace TwitchXX
{
	///Twitch user properties request object
	/** This class encapsulates all requests that are related to twitch user operations */
	class TwitchUsers : public TwitchRequest
	{
	public:
		static std::map<AuthScope, utility::string_t> Scopes;
		static std::map<utility::string_t, AuthScope> Rscopes;

		///Constructor
		explicit TwitchUsers(const std::shared_ptr<MakeRequest>& request)
			: TwitchRequest(request)
		{
		}

		///Get a list of blcoked users
		///@param user_name a user for which this request is performed
		TwitchXX::TwitchBlockedUsersContainer GetBlocked(const utility::string_t& user_name) const;

		///Block users
		///@param user_name self name
		///@param target_name whom to block
		///@return blocked user record from server
		TwitchXX::TwitchBlockedUser BlockUser(const utility::string_t& user_name, const utility::string_t& target_name) const;

		///Remove user from blocked list
		///@param user_name self name
		///@param target_name whom to unblock
		///@return true if ok
		bool UblockUser(const utility::string_t& user_name, const utility::string_t& target_name) const;

		///Get list of channels that user is subscribed to
		///@param user_name user name
		///@param order results sorting order (TwitchXX::Sort_order - by created date, last broadcast time or last login)
		///@return collection of followed channels
		TwitchFollowedChannelsContainer GetFollowingChannels(const utility::string_t& user_name, Sort_Order order = Sort_Order::Created) const;

		///Get channel follow object if user follows target channel
		///@param user_name self name
		///@param channel_name channel to follow
		///@return channle follow object
		TwitchFollowedChannel GetFollowingChannel(const utility::string_t&  user_name, const utility::string_t& channel_name) const;

		///Follow channel for user
		///Required scope: AuthScope::USER_FOLLOWS_EDIT
		///@param user_name self name
		///@param channel_name channel to follow
		///@return channel follow object
		TwitchFollowedChannel FollowChannel(const utility::string_t& user_name, const utility::string_t& channel_name, bool notification = false) const;

		///Unfollow channel for user
		///Required scope: AuthScope::USER_FOLLOWS_EDIT
		///@param user_name self name
		///@param channel_name channel to follow
		void UnfollowChannel(const utility::string_t& user_name, const utility::string_t& channel_name) const;

		///Get current user status
		///@return user status object(UserStatus)
		AuthToken GetCurrentUserStatus() const;

		///Returns a channel object that user subscribes to. Requires authentication for user.
		///Requires auth scope: AuthScope::USER_SUBSCRIPTIONS
		///@param channel_name channel name
		///@param user_name
		///@return channel object in case user is subscribed to given channel
		TwitchFollowedChannel GetUserSubscribedChannel(const utility::string_t& channel_name, const utility::string_t& user_name) const;

		///Request user object by name
		///@param user_name requested user name
		///@return user object
		TwitchUser GetUser(const utility::string_t& user_name) const;

		///Get a list of emoticons that user is authorized to use
		///Requires AuthScope::USER_SUBSCRIPTIONS
		///@param user_name requested user_name
		///@return emoticon collection
		std::set<EmoticonImage> GetUserEmoticons(const utility::string_t& user_name) const;


		///Get current user
		///Requires AuthScope::USER_READ
		///@return user object
		TwitchUser GetCurrentUser() const;
	};

	template<> TwitchUser Create<TwitchUser>(const web::json::value& value); ///< Constructs TwitchUser object from json
	template<> TwitchBlockedUser Create<TwitchBlockedUser>(const web::json::value& value); ///< Create TwitchBlockedUser object from Json
	template<> TwitchFollowedChannel Create<TwitchFollowedChannel>(const web::json::value& value); ///< Create descriptor on followed channel 
	template<> AuthToken Create<AuthToken>(const web::json::value& value); ///< Create user status object;
	
}
