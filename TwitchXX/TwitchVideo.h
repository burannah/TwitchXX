#pragma once
#include "Property.h"
#include "TwitchChannel.h"

namespace TwitchXX
{
	class TwitchVideo
	{
	public:
		///Title
		Property<utility::string_t> Title;

		///Description
		Property<utility::string_t> Description;

		///Broadcast Id
		Property<unsigned long long> BroadcastId;

		///Id
		Property<utility::string_t> Id;

		///Status
		Property<utility::string_t> Status; //TODO: Not sure about string;

		///Tag list
		Property<utility::string_t> TagList; //TODO: Not sure about string

		///Recording date
		Property<Date> Recorded;

		///Game
		Property<utility::string_t> Game;

		///Length
		Property<unsigned long long> Length;

		///Preview
		Property<utility::string_t> Preview;

		///Url
		Property<utility::string_t> Url;

		///Views
		Property<unsigned long long> Views;

		///Broadcast type
		Property<utility::string_t> BroadcastType;

		///Channel name
		Property<utility::string_t> ChannelName;

		///Channel display name
		Property<utility::string_t> ChannelDisplayName;

		///Less than operator
		bool operator<(const TwitchVideo& other) const
		{
			return Id.Get() < other.Id.Get();
		}

		///Equals operator
		bool operator==(const TwitchVideo& other) const
		{
			return Id.Get() == other.Id.Get();
		}
	};
	
}
