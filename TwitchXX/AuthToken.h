#pragma once
#include "TwitchDef.h"
#include "Property.h"

namespace TwitchXX
{
	///Authorization scopes
	enum class AuthScope : unsigned
	{
		NO_SCOPE = 0,
		USER_READ = 1 << 0,
		USER_BLOCKS_EDIT = 1 << 1,
		USER_BLOCKS_READ = 1 << 2,
		USER_FOLLOWS_EDIT = 1 << 3,
		CHANNEL_READ = 1 << 4,
		CHANNEL_EDITOR = 1 << 5,
		CHANNEL_COMMERCIAL = 1 << 6,
		CHANNEL_STREAM = 1 << 7,
		CHANNEL_SUBSCRIPTIONS = 1 << 8,
		USER_SUBSCRIPTIONS = 1 << 9,
		CHANNEL_CHECK_SUBSCRIPTION = 1 << 10,
		CHAT_LOGIN = 1 << 11,
		CHANNEL_FEED_READ = 1 << 12,
		CHANNEL_FEED_EDIT = 1 << 13
	};

	using T = std::underlying_type_t<AuthScope>;
	inline AuthScope operator|(AuthScope lhs, AuthScope rhs)
	{
		return static_cast<AuthScope>((static_cast<T>(lhs)) | (static_cast<T>(rhs)));
	}

	inline AuthScope operator|=(AuthScope lhs, AuthScope rhs)
	{
		lhs = static_cast<AuthScope>(static_cast<T>(lhs) | static_cast<T>(rhs));
		return lhs;
	}

	inline bool operator&(AuthScope lhs, AuthScope rhs)
	{
		return (static_cast<T>(lhs) & static_cast<T>(rhs)) != 0;
	}

	struct AuthToken
	{

		///User's name
		Property<std::wstring> Name;

		///Is user valid flag
		Property<bool> Valid;

		///User creation date
		Property<Date> Created;

		///Last updated date
		Property<Date> Updated;

		///Security permissions
		Property<AuthScope> AuthorizationScopes;
	};

}
