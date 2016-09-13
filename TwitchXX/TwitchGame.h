#pragma once
#include <set>
#include <map>
#include "TwitchDef.h"
#include "Property.h"

namespace TwitchXX
{
	///Twitch featured stream object
	/** This class represents twitch featured stream object. Almost like normal stream object, but with some additional fields*/
	class TwitchGame
	{
	public:
		Property<utility::string_t> Name;  ///Game's name
		Property<unsigned int> Channels;	  ///Number of broadcasting channgels
		Property<unsigned int> Viewers;	  ///Numeber of viewers
		Property<unsigned int> Id;		  ///Game's Id
		Property<unsigned int> Giantbomb_Id; ///Giantbomb id
		ImageCollection	Box;		  ///Box images
		ImageCollection Logo;		  ///Game logos



		///Less than operator
		bool operator<(const TwitchGame& other) const
		{
			return Id.Get() < other.Id.Get();
		}

		///Equals operator
		bool operator==(const TwitchGame& other) const
		{
			return Id.Get() == other.Id.Get();
		}
	};
}

