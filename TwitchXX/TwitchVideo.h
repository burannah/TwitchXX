#pragma once
#include "Property.h"
#include "TwitchChannel.h"

namespace TwitchXX
{
	class TwitchVideo
	{
	public:
		///Title
		Property<std::wstring> Title;

		///Description
		Property<std::wstring> Description;

		///Broadcast Id
		Property<unsigned long long> BroadcastId;

		///Id
		Property<unsigned long long> Id;

		///Status
		Property<std::wstring> Status; //TODO: Not sure about string;

		///Tag list
		Property<std::wstring> TagList; //TODO: Not sure about string

		///Recording date
		Property<Date> Recorded;

		///Game
		Property<std::wstring> Game;

		///Length
		Property<unsigned long long> Length;

		///Preview
		Property<std::wstring> Preview;

		///Url
		Property<std::wstring> Url;

		///Views
		Property<unsigned long long> Views;

		///Broadcast type
		Property<std::wstring> BroadcastType;

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
