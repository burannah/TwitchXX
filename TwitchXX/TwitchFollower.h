#pragma once
#include "TwitchUser.h"

namespace TwitchXX
{
	class TwitchFollower
	{
	public:
		///Date of staring following
		Property<Date> Created;
		///Is notifications are on
		Property<bool> Notifications;

		///User object
		TwitchUser User;

		///Less than operator
		bool operator<(const TwitchFollower& other) const
		{
			return Created.Get() < other.Created.Get();
		}

		///Equals operator
		bool operator==(const TwitchFollower& other) const
		{
			return User == other.User;
		}
	};
}

