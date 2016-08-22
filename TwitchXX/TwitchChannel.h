#pragma once
#include "TwitchDef.h"
#include "Property.h"

namespace TwitchXX
{
	///Twitch channel class
	/** Twitch channel object descriptor*/
	class TwitchChannel
	{
	public:
		Property<bool> Mature;							///Mature content
		Property<std::wstring> Status;					///Channel's status
		Property<std::wstring> Broadcaster_Language;	///Broadcaster's language
		Property<std::wstring> Language;				///Channel's language
		Property<std::wstring> Display_Name;			///Display name
		Property<std::wstring> Game;					///Game name
		Property<size_t> Delay;							///Delay
		Property<size_t> Id;							///Channel Id
		Property<std::wstring> Name;					///Channel name
		Property<Date> Created;							///Creation date
		Property<Date> Updated;							///Last updated
		Property<std::wstring> Logo;					///Channel's logo
		Property<std::wstring> Banner;					///Banner
		Property<std::wstring> Video_Banner;			///Video banner
		Property<std::wstring> Url;						///Url
		Property<std::wstring> Background;				///Background
		Property<std::wstring> Profile_Banner;			///Profile banner
		Property<std::wstring> Profile_Banner_Background_Color; ///Profile banner background color
		Property<bool> Partner;							///Is partner channel
		Property<unsigned long long> Views;				///Number of views
		Property<unsigned long long> Followers;			///Number of followers
		Property<std::wstring> Stream_Key;				///Stream's key (Only for authorized channels)

		///Equal operator
		/**
		* Channels are distinguished by id.
		*/
		bool operator==(const TwitchChannel& other) const
		{
			return Id == Id;
		}
		///Operator less then
		/**
		* If two channels has the same number of followers - number of views considered.
		*/
		bool operator<(const TwitchChannel& other) const
		{
			return Followers == other.Followers ? Views < other.Views : Followers < other.Followers;
		}
	};
	///Default container for channels
	using TwitchChannelContainer = std::set<TwitchChannel>;

}
