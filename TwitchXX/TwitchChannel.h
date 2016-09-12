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
		Property<utility::string_t> Status;					///Channel's status
		Property<utility::string_t> Broadcaster_Language;	///Broadcaster's language
		Property<utility::string_t> Language;				///Channel's language
		Property<utility::string_t> Display_Name;			///Display name
		Property<utility::string_t> Game;					///Game name
		Property<unsigned int> Delay;							///Delay
		Property<unsigned int> Id;							///Channel Id
		Property<utility::string_t> Name;					///Channel name
		Property<Date> Created;							///Creation date
		Property<Date> Updated;							///Last updated
		Property<utility::string_t> Logo;					///Channel's logo
		Property<utility::string_t> Banner;					///Banner
		Property<utility::string_t> Video_Banner;			///Video banner
		Property<utility::string_t> Url;						///Url
		Property<utility::string_t> Background;				///Background
		Property<utility::string_t> Profile_Banner;			///Profile banner
		Property<utility::string_t> Profile_Banner_Background_Color; ///Profile banner background color
		Property<bool> Partner;							///Is partner channel
		Property<unsigned long long> Views;				///Number of views
		Property<unsigned long long> Followers;			///Number of followers
		Property<utility::string_t> Stream_Key;				///Stream's key (Only for authorized channels)

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
