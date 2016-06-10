#pragma once
#include "TwitchRequest.h"
#include "TwitchEmoticon.h"

namespace TwitchXX
{
	class TwitchChat : public TwitchRequest<TwitchEmoticon>
	{
	public:
		struct EmoticonImage
		{
			size_t Id;
			std::wstring Code;
			size_t EmoticoneSet;

			bool operator<(const EmoticonImage& image) const { return Id < image.Id; }

		};
		struct ChannelBadge
		{
			std::wstring Type;
			std::wstring Alpha;
			std::wstring Image;
			std::wstring Svg;

			bool operator<(const ChannelBadge& badge) const { return Type < badge.Type; }
		};

		TwitchEmoticonsContainer GetEmoticons() const;
		std::set<EmoticonImage> GetEmoticoneImages(std::set<size_t> sets = std::set<size_t>()) const;
		std::set<ChannelBadge> GetChannelBadges(std::wstring& channel_name) const;

	private:
		std::set<EmoticonImage> GetEmoticonsImagesAll() const;
		std::set<EmoticonImage> GetEmoticonsImagesBySets(const std::set<unsigned>& sets) const;
	};


	template<> TwitchEmoticon Create<TwitchEmoticon>(const web::json::value& value);
	std::set<TwitchEmoticon::EmoticoneImageDescriptor> GetImages(const web::json::value& value);


}
