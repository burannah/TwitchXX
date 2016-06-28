#pragma once
#include <set>
#include <map>
#include <chrono>
#include <functional>
#include <vector>


namespace TwitchXX
{
	///@{ \addgroup class_forwardes Forward declaratoins for basic Twitch objects classes
	class TwitchGame;
	class TwitchStream;
	class TwitchChannel;
	class TwitchFeaturedStream;
	class TwitchUser;
	class TwitchTeam;
	class TwitchPost;
	class TwitchEmoticon;
	///@}

	template <typename T>
		using TwitchContainer = std::set<T>; ///< Default container type
	using TwitchGamesContainer = TwitchContainer<TwitchGame>; ///< TwitchGame collection
	using TwitchGamesVector = std::vector<TwitchGame>; ///< TwitchGame vector (explicit)
	using TwitchStreamsContainer = TwitchContainer<TwitchStream>; ///< TwitchStream collection
	using TwitchFeaturedStreamsContainer = TwitchContainer<TwitchFeaturedStream>; ///< TwitchFeaturedStreams collection
	using TwitchUsersContainer = TwitchContainer<TwitchUser>; ///< TwitchUser collection
	using TwitchStreamsVector = std::vector<TwitchStream>; ///< TwitchStream vector (explicit)
	using TwitchChannelsContainer = TwitchContainer<TwitchChannel>; ///< TwitchChannel collection
	using TwitchTeamsContainer = TwitchContainer<TwitchTeam>; ///< TwitchTeam collection
	using TwitchPostsContainer = TwitchContainer<TwitchPost>; ///< TwitchPost collection
	using TwitchEmoticonsContainer = TwitchContainer<TwitchEmoticon>; ///< TwitchEmoticon collection
	using ImageCollection = std::map<std::wstring, std::wstring>; ///< image collection (image key, image url)
	using options = std::map<std::wstring, std::wstring>; ///< options collection (option key, option value)
	using Date = std::chrono::time_point<std::chrono::system_clock>; ///< default date type

	///Date from string
	///@param cs string represetnaion of ISO 8601 format time
	///@return Date value
	Date DateFromString(const std::wstring& cs);

	///Date to string
	///@param tp Date object
	///@return date string in ISO 8601 format
	std::wstring DateToString(const Date& tp);

	/// EmoticonImage descriptor
	struct EmoticonImage
	{
		size_t Id;
		std::wstring Code;
		size_t EmoticoneSet;

		//EmoticonImage(size_t id, const std::wstring& code, size_t set) :Id{ id }, Code{ code }, EmoticoneSet{ set } {}

		///Less then operator
		bool operator<(const EmoticonImage& image) const { return Id < image.Id; }

	};

	/// ChannelBadge descriptor
	struct ChannelBadge
	{
		std::wstring Type;
		std::wstring Alpha;
		std::wstring Image;
		std::wstring Svg;

		///Less than operator
		bool operator<(const ChannelBadge& badge) const { return Type < badge.Type; }
	};

}
