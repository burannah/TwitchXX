#pragma once
#include <string>
#include <set>

#include "Property.h"

namespace TwitchXX
{
	///Twitch emoticon object
	/** This class represents twitch emoticon object*/
	class TwitchEmoticon
	{
	public:
		///Emoticon image descriptor
		struct EmoticoneImageDescriptor
		{
			///Emoticon set Id
			Property<size_t> Set_Id;
			///Height
			Property<size_t> Height;
			///Url
			Property<size_t> Width;
			///Url
			Property<std::wstring> Url;

			///Less than operator
			bool operator<(const EmoticoneImageDescriptor& desc) const { return Set_Id < desc.Set_Id; }
			///Equals opeartor
			bool operator==(const EmoticoneImageDescriptor& desc) const { return Url.Get() == desc.Url.Get(); }
		};

		///Equals operator
		bool operator==(const TwitchEmoticon& other) const { return Regex.Get() == other.Regex.Get() && Images == other.Images; }
		///Less than
		bool operator<(const TwitchEmoticon& emoticon) const { return Regex.Get() < emoticon.Regex.Get(); }

		///@{
		///Regular expression
		Property<std::wstring> Regex;
		///@}

		///@{
		///Images
		std::set<EmoticoneImageDescriptor> Images;
		///@}
	};

}
