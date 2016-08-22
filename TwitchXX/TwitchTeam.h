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
		Property<size_t> Id{ 0 };
		///Team name
		Property<std::wstring> Name;
		///Team info
		Property<std::wstring> Info;
		///Display name
		Property<std::wstring> Display_Name;
		///Created
		Property<Date> Created;
		///Updated
		Property<Date> Updated;
		///Team logo
		Property<std::wstring> Logo;
		///Team banner
		Property<std::wstring> Banner;
		///Background
		Property<std::wstring> Background;

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
