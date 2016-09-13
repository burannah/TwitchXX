#include "TwitchChat.h"
#include "JsonWrapper.h"

TwitchXX::TwitchEmoticonsContainer TwitchXX::TwitchChat::GetEmoticons() const
{
	web::uri_builder builder(U("/chat/emoticons"));
	return GetObjectsArrayOnce<TwitchEmoticon>(builder, U("emoticons"));
}

std::set<TwitchXX::EmoticonImage> TwitchXX::TwitchChat::GetEmoticoneImages(std::set<unsigned int> sets) const
{
	if(sets.size() == 0)
	{
		return GetEmoticonsImagesAll();
	}
	else
	{
		return GetEmoticonsImagesBySets(sets);
	}
}

std::set<TwitchXX::ChannelBadge> TwitchXX::TwitchChat::GetChannelBadges(const utility::string_t &channel_name) const
{
	web::uri_builder builder(U("/chat/") + channel_name + U("/badges"));
	auto response = _request->get(builder.to_uri());
	std::set<ChannelBadge> result;
	if(response.is_null())
	{
		return result;
	}

	for (const auto& it : response.as_object())
	{
		if (it.second.is_null() || it.first == U("_links")) continue;;
		JsonWrapper wrapper(it.second);
		result.insert({it.first, *wrapper[U("alpha")],*wrapper[U("image")],*wrapper[U("svg")]});
	}

	return result;
}

std::set<TwitchXX::EmoticonImage> TwitchXX::TwitchChat::GetEmoticonsImagesAll() const
{
	web::uri_builder builder(U("/chat/emoticon_images"));
	auto resposne = _request->get(builder.to_uri());
	auto emoticons = resposne.at(U("emoticons"));
	std::set<EmoticonImage> result;
	if(emoticons.is_null() || !emoticons.is_array())
	{
		return result;
	}

	for (const auto& emoticone_image_descriptor : emoticons.as_array())
	{
		JsonWrapper wrapper(emoticone_image_descriptor);
		result.insert({ *wrapper[U("id")], *wrapper[U("code")], *wrapper[U("emoticone_set")] });
	}

	return result;
}

std::set<TwitchXX::EmoticonImage> TwitchXX::TwitchChat::ParseEmoticonSets(web::json::value emoticon_sets)
{
	std::set<TwitchXX::EmoticonImage> result;
	if (emoticon_sets.is_null())
	{
		return result;
	}
	for(const auto& it: emoticon_sets.as_object())
	{
		unsigned int set_id = std::stoi(it.first);
		for(const auto& emoticone: it.second.as_array())
		{
			JsonWrapper wrapper(emoticone);
			result.insert({*wrapper[U("id")],*wrapper[U("code")], set_id});
		}
	}

	return result;
}

std::set<TwitchXX::EmoticonImage> TwitchXX::TwitchChat::GetEmoticonsImagesBySets(const std::set<unsigned int>& sets) const
{
	web::uri_builder builder(U("/chat/emoticon_images"));
	utility::stringstream_t ss;
	std::copy(sets.begin(),sets.end(),std::ostream_iterator<unsigned int,utility::char_t>(ss,U(",")));
	builder.append_query(U("emotesets"), ss.str());
	auto resposne = _request->get(builder.to_uri());
	auto emoticon_sets = resposne.at(U("emoticon_sets"));
	return ParseEmoticonSets(emoticon_sets);
}

template <>
TwitchXX::TwitchEmoticon TwitchXX::Create<TwitchXX::TwitchEmoticon>(const web::json::value& value)
{
	TwitchEmoticon emoticon;
	JsonWrapper wrapper(value);

	emoticon.Regex.Set(*wrapper[U("regex")]);
	emoticon.Images = GetImages(value.at(U("images")));

	return emoticon;
	
}

std::set<TwitchXX::TwitchEmoticon::EmoticoneImageDescriptor> TwitchXX::GetImages(const web::json::value& value)
{
	std::set<TwitchEmoticon::EmoticoneImageDescriptor> result;
	if(value.is_null() || !value.is_array())
	{
		return  result;
	}

	for (const auto& image_descriptor : value.as_array())
	{
		JsonWrapper wrapper(image_descriptor);
		result.insert(TwitchEmoticon::EmoticoneImageDescriptor{ (unsigned int)(*wrapper[U("emoticon_set")]), (unsigned int)*wrapper[U("height")], (unsigned int)*wrapper[U("width")], (utility::string_t)*wrapper[U("url")] });
	}

	return result;
}
