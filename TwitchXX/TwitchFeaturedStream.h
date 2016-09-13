#pragma once
#include <string>
#include "TwitchStream.h"
#include "Property.h"

namespace TwitchXX
{
	///Twitch featured stream object
	/** This class represents twitch featured stream object. Almost like normal stream object, but with some additional fields*/
	class TwitchFeaturedStream
	{
	public:
		///Image
		Property<utility::string_t> Image;
		///Text
		Property<utility::string_t> Text;
		///Title
		Property<utility::string_t> Title;
		///Sponsored
		Property<bool> Sponsored{ false };
		///Scheduled
		Property<bool> Scheduled{ false };
		///Stream
		TwitchXX::TwitchStream Stream;

		///Less than opeartor
		bool operator<(const TwitchFeaturedStream& other) const { return Stream < other.Stream; }
		///Equals operator
		bool operator==(const TwitchFeaturedStream& other) const { return Stream == other.Stream; }

	};
	
}
