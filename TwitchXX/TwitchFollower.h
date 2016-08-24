#pragma once
#include "TwitchUser.h"
#include "TwitchChannel.h"

namespace TwitchXX
{
	///Class describing user that follows a channel
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


	///Class that describes a channel, subscribed by a user
	class TwitchFollowedChannel
	{
	public:
		///Date of staring following
		Property<Date> Created;
		///Is notifications are on
		Property<bool> Notifications;

		///User object
		TwitchChannel Channel;

		///Less than operator
		bool operator<(const TwitchFollowedChannel& other) const
		{
			return Created.Get() < other.Created.Get();
		}

		///Equals operator
		bool operator==(const TwitchFollowedChannel& other) const
		{
			return Channel == other.Channel;
		}
	};
}

