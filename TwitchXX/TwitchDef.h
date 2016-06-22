#pragma once
#include <set>
#include <map>
#include <chrono>
#include <functional>
#include <vector>


namespace TwitchXX
{
	class TwitchGame;
	class TwitchStream;
	class TwitchChannel;
	class TwitchFeaturedStream;
	class TwitchUser;
	class TwitchTeam;
	class TwitchPost;
	class TwitchEmoticon;
	template <typename T>
		using TwitchContainer = std::set<T>;
	using TwitchGamesContainer = TwitchContainer<TwitchGame>;
	using TwitchGamesVector = std::vector<TwitchGame>;
	using TwitchStreamsContainer = TwitchContainer<TwitchStream>;
	using TwitchFeaturedStreamsContainer = TwitchContainer<TwitchFeaturedStream>;
	using TwitchUsersContainer = TwitchContainer<TwitchUser>;
	using TwitchStreamsVector = std::vector<TwitchStream>;
	using TwitchChannelsContainer = TwitchContainer<TwitchChannel>;
	using TwitchTeamsContainer = TwitchContainer<TwitchTeam>;
	using TwitchPostsContainer = TwitchContainer<TwitchPost>;
	using TwitchEmoticonsContainer = TwitchContainer<TwitchEmoticon>;
	using ImageCollection = std::map<std::wstring, std::wstring>;
	using options = std::map<std::wstring, std::wstring>;
	using Date = std::chrono::time_point<std::chrono::system_clock>;

	Date DateFromString(const std::wstring& cs);
	std::wstring DateToString(const Date& tp);

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

}
