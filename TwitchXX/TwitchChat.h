#pragma once
#include "TwitchRequest.h"
#include "TwitchEmoticon.h"

namespace TwitchXX
{
	class TwitchChat : public TwitchRequest<TwitchEmoticon>
	{
	public:
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
