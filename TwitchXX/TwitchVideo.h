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
		Property<unsigned long long> Id;

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

		///Channel
		TwitchChannel Channel;

		///Less than operator
		bool operator<(const TwitchVideo& other) const
		{
			return BroadcastId.Get() < other.BroadcastId.Get();
		}

		///Equals operator
		bool operator==(const TwitchVideo& other) const
		{
			return BroadcastId.Get() == other.BroadcastId.Get();
		}
	};
	
}
