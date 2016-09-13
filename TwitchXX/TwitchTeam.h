#pragma once
#include <string>
#include "TwitchDef.h"
#include "Property.h"

namespace TwitchXX
{
	///Twitch team class
	/** This class represents twitch team object.*/
	class TwitchTeam
	{
	public:
		///Id
		Property<unsigned int> Id{ 0 };
		///Team name
		Property<utility::string_t> Name;
		///Team info
		Property<utility::string_t> Info;
		///Display name
		Property<utility::string_t> Display_Name;
		///Created
		Property<Date> Created;
		///Updated
		Property<Date> Updated;
		///Team logo
		Property<utility::string_t> Logo;
		///Team banner
		Property<utility::string_t> Banner;
		///Background
		Property<utility::string_t> Background;

		///Operator equals
		/// Distinc objects by Id
		bool operator==(const TwitchTeam& other) const
		{
			return Id == other.Id;
		}


		///Operator less than
		/// Order teams by creation date and last updated date
		bool operator<(const TwitchTeam& other) const
		{
			return Created.Get() == other.Created.Get() ? Updated.Get() < other.Updated.Get() : Created.Get() < other.Created.Get();
		}

	};
	
}
