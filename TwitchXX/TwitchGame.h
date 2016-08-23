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
		Property<std::wstring> Name;  ///Game's name
		Property<size_t> Channels;	  ///Number of broadcasting channgels
		Property<size_t> Viewers;	  ///Numeber of viewers
		Property<size_t> Id;		  ///Game's Id
		Property<size_t> Giantbomb_Id; ///Giantbomb id
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

