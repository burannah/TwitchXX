#pragma once
#include "TwitchRequest.h"
#include "TwitchEmoticon.h"
#include "../../../.CLion2016.2/system/cmake/generated/TwitchSpy-4ecddfcf/4ecddfcf/Debug0/cpprestsdk/src/cpprestsdk/Release/include/cpprest/details/basic_types.h"

namespace TwitchXX
{
	///Twitch chat request object
	/** This class encapsulates all requests that are related to twitch chat emoticons and badges operations*/
	class TwitchChat : public TwitchRequest
	{
	public:
		///Constructor
		///@param request transport object
		explicit TwitchChat(std::shared_ptr<MakeRequest> request) : TwitchRequest(request) {};


		///Returns a list of all emoticon objects for Twitch.
		/** Important: Current size of response for this request is ~9Mb. It requires ~120Mb for JSON library to parse such response.
		* And it takes some time! (And it takes 3x more memory in debug). I would not recomend to abuse this request.
		* TODO: use alternate JSON library
		*/
		TwitchEmoticonsContainer GetEmoticons() const;

		///Returns a list of emoticons.
		///@param sets sets ids to request
		///@return a collection of EmoticonImage objects 
		std::set<EmoticonImage> GetEmoticoneImages(std::set<unsigned int> sets = {}) const;

		///Returns a list of chat badges that can be used in the channel's chat.
		///@param channel_name channel name
		///@return a collection of ChannelBadge objects (Note: empty badges are not returned) 
		std::set<ChannelBadge> GetChannelBadges(const utility::string_t &channel_name) const;

		static std::set<EmoticonImage> ParseEmoticonSets(web::json::value emoticon_sets);
	private:
		std::set<EmoticonImage> GetEmoticonsImagesAll() const;
		std::set<EmoticonImage> GetEmoticonsImagesBySets(const std::set<unsigned>& sets) const;
	};

	template<> TwitchEmoticon Create<TwitchEmoticon>(const web::json::value& value); ///< Constructs TwitchEmoticon object from json
	std::set<TwitchEmoticon::EmoticoneImageDescriptor> GetImages(const web::json::value& value); ///< Constructs TwitchEmoticon object from json
}
