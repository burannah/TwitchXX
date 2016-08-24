#pragma once
#include "TwitchRequest.h"

namespace TwitchXX
{
	///Twitch user properties request object
	/** This class encapsulates all requests that are related to twitch user operations */
	class TwitchUsers : public TwitchRequest<TwitchUser>
	{
	public:
		///Constructor
		explicit TwitchUsers(const std::shared_ptr<MakeRequest>& request)
			: TwitchRequest<TwitchUser>(request)
		{
		}

		///Get a list of blcoked users
		///@param user_name a user for which this request is performed
		TwitchXX::TwitchBlockedUsersContainer GetBlocked(const std::wstring& user_name) const;

		///Block users
		///@param user_name self name
		///@param target_name whom to block
		///@return blocked user record from server
		TwitchXX::TwitchBlockedUser BlockUser(const std::wstring& user_name, const std::wstring& target_name) const;

		///Remove user from blocked list
		///@param user_name self name
		///@param target_name whom to unblock
		///@return true if ok
		bool UblockUser(const std::wstring& user_name, const std::wstring& target_name) const;

		///Get list of channels that user is subscribed to
		TwitchFollowedChannelsContainer GetFollowingChannels(const std::wstring& user_name, Sort_Order order = Sort_Order::Created) const;

	};

	template<> TwitchUser Create(const web::json::value& value); ///< Constructs TwitchUser object from json
	template <> TwitchBlockedUser Create<TwitchBlockedUser>(const web::json::value& value); ///< Create TwitchBlockedUser object from Json
	template <> TwitchFollowedChannel Create<TwitchFollowedChannel>(const web::json::value& value); ///< Create descriptor on followed channel 
	
}
