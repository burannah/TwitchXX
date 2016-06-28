#pragma once
#include <string>
#include <set>

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
			size_t SetId;
			size_t Height;
			size_t Width;
			std::wstring Url;

			///Less than operator
			bool operator<(const EmoticoneImageDescriptor& desc) const { return SetId < desc.SetId; }
			///Equals opeartor
			bool operator==(const EmoticoneImageDescriptor& desc) const { return Url == desc.Url; }
		};

		///Equals operator
		bool operator==(const TwitchEmoticon& other) const { return _regex == other._regex && _images == other._images; }
		///Less than
		bool operator<(const TwitchEmoticon& emoticon) const { return _regex < emoticon._regex; }

		///@{
		///Regular expression
		void RegEx(const std::wstring& regex) { _regex = regex; }
		const std::wstring& RegEx() const { return _regex; }
		///@}

		///@{
		///Images
		void Images(const std::set<EmoticoneImageDescriptor>& images) { _images = images; }
		const std::set<EmoticoneImageDescriptor>& Images() const { return _images; }
		///@}
	private:
		std::wstring _regex;
		std::set<EmoticoneImageDescriptor> _images;
	};

}
