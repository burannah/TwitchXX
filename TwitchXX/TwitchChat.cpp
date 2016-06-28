#include "TwitchChat.h"
#include "JsonWrapper.h"

TwitchXX::TwitchEmoticonsContainer TwitchXX::TwitchChat::GetEmoticons() const
{
	web::uri_builder builder(U("/chat/emoticons"));

	auto resposne = (*_request)(builder.to_uri());
	auto emoticons = resposne.at(U("emoticons"));
	TwitchEmoticonsContainer result;
	if(!emoticons.is_null() && emoticons.is_array())
	{
		for (const auto& emoticone_descriptor : emoticons.as_array())
		{
			result.insert(Create<TwitchEmoticon>(emoticone_descriptor));
		}
	}

	return result;
}

std::set<TwitchXX::EmoticonImage> TwitchXX::TwitchChat::GetEmoticoneImages(std::set<size_t> sets) const
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

std::set<TwitchXX::ChannelBadge> TwitchXX::TwitchChat::GetChannelBadges(std::wstring& channel_name) const
{
	web::uri_builder builder(U("/chat/") + channel_name + U("/badges"));
	auto response = (*_request)(builder.to_uri());
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
	auto resposne = (*_request)(builder.to_uri());
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

std::set<TwitchXX::EmoticonImage> TwitchXX::TwitchChat::GetEmoticonsImagesBySets(const std::set<unsigned>& sets) const
{
	web::uri_builder builder(U("/chat/emoticon_images"));
	std::wstringstream ss;
	std::transform(sets.begin(), sets.end(), std::ostream_iterator<std::wstring, wchar_t>(ss, U(",")), [](size_t set_id) { return std::to_wstring(set_id); }); //TODO: Not sure about NULL set id
	builder.append_query(U("emotesets"), ss.str());
	auto resposne = (*_request)(builder.to_uri());
	auto emoticon_sets = resposne.at(U("emoticon_sets"));
	std::set<EmoticonImage> result;

	if (emoticon_sets.is_null()) return result;
	for(const auto& it: emoticon_sets.as_object())
	{
		size_t set_id = std::stoi(it.first);
		for(const auto& emoticone: it.second.as_array())
		{
			JsonWrapper wrapper(emoticone);
			result.insert({*wrapper[U("id")],*wrapper[U("code")], set_id});
		}
	}

	return result;
}

template <>
TwitchXX::TwitchEmoticon TwitchXX::Create<TwitchXX::TwitchEmoticon>(const web::json::value& value)
{
	TwitchEmoticon emoticon;
	JsonWrapper wrapper(value);

	emoticon.RegEx(*wrapper[U("regex")]);
	emoticon.Images(GetImages(value.at(U("images"))));

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
		result.insert({ *wrapper[U("emoticon_set")],*wrapper[U("height")], *wrapper[U("width")], *wrapper[U("url")] });
	}

	return result;
}
