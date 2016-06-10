#pragma once
#include <string>
#include <set>

namespace TwitchXX
{

	class TwitchEmoticon
	{
	public:
		struct EmoticoneImageDescriptor
		{
			size_t SetId;
			size_t Height;
			size_t Width;
			std::wstring Url;

			bool operator<(const EmoticoneImageDescriptor& desc) const { return SetId < desc.SetId; }
		};

		bool operator<(const TwitchEmoticon& emoticon) const { return _regex < emoticon._regex; }

		void RegEx(const std::wstring& regex) { _regex = regex; }
		const std::wstring& RegEx() const { return _regex; }

		void Images(const std::set<EmoticoneImageDescriptor>& images) { _images = images; }
		const std::set<EmoticoneImageDescriptor>& Images() const { return _images; }

	private:
		std::wstring _regex;
		std::set<EmoticoneImageDescriptor> _images;
	};

}
