#pragma once
#include <set>
#include <map>
#include <chrono>
#include <exception>
#include <vector>
#include <functional>
#include <cpprest/details/basic_types.h> //TODO: CPPRESTSDK dependency
#ifdef _WIN32
#define to_ustring(x) std::to_wstring(x)
#else
#define to_ustring(x) std::to_string(x)
#endif



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
	class TwitchBlockedUser;
	class TwitchFollower;
	class TwitchFollowedChannel;
	class TwitchIngest;
	class TwitchVideo;
	///@}

	template <typename T>
	using TwitchContainer = std::set<T>; ///< Default container type
	using TwitchGamesContainer = TwitchContainer<TwitchGame>; ///< TwitchGame collection
	using TwitchGamesVector = std::vector<TwitchGame>; ///< TwitchGame vector (explicit)
	using TwitchStreamsContainer = TwitchContainer<TwitchStream>; ///< TwitchStream collection
	using TwitchFeaturedStreamsContainer = TwitchContainer<TwitchFeaturedStream>; ///< TwitchFeaturedStreams collection
	using TwitchUsersContainer = TwitchContainer<TwitchUser>; ///< TwitchUser collection
	using TwitchBlockedUsersContainer = TwitchContainer<TwitchBlockedUser>; ///< Collection of blocked users
	using TwitchStreamsVector = std::vector<TwitchStream>; ///< TwitchStream vector (explicit)
	using TwitchChannelsContainer = TwitchContainer<TwitchChannel>; ///< TwitchChannel collection
	using TwitchTeamsContainer = TwitchContainer<TwitchTeam>; ///< TwitchTeam collection
	using TwitchPostsContainer = TwitchContainer<TwitchPost>; ///< TwitchPost collection
	using TwitchEmoticonsContainer = TwitchContainer<TwitchEmoticon>; ///< TwitchEmoticon collection
	using TwitchFollowersContainer = TwitchContainer<TwitchFollower>; ///< Twitch channel followers 
	using TwitchFollowedChannelsContainer = TwitchContainer<TwitchFollowedChannel>; ///< Channels followed collection
	using TwitchIngestsContainer = TwitchContainer<TwitchIngest>; ///< Ingests collection
	using TwitchVideosContainer = TwitchContainer<TwitchVideo>; ///< Video collection
	using ImageCollection = std::map<utility::string_t, utility::string_t>; ///< image collection (image key, image url)
	using options = std::map<utility::string_t, utility::string_t>; ///< options collection (option key, option value)
	using Date = std::chrono::time_point<std::chrono::system_clock>; ///< default date type

	///Date from string
	///@param cs string represetnaion of ISO 8601 format time
	///@return Date value
	Date DateFromString(const utility::string_t& cs);

	///Date to string
	///@param tp Date object
	///@return date string in ISO 8601 format
	utility::string_t DateToString(const Date& tp);

	/// EmoticonImage descriptor
	struct EmoticonImage
	{
        unsigned int       Id;
		utility::string_t  Code;
		unsigned int       EmoticoneSet;

		//EmoticonImage(size_t id, const string_t& code, size_t set) :Id{ id }, Code{ code }, EmoticoneSet{ set } {}

		///Less then operator
		bool operator<(const EmoticonImage& image) const { return Id < image.Id; }
	};

	/// ChannelBadge descriptor
	struct ChannelBadge
	{
		utility::string_t Type;
        utility::string_t Alpha;
        utility::string_t Image;
        utility::string_t Svg;

		///Less than operator
		bool operator<(const ChannelBadge& badge) const { return Type < badge.Type; }
	};

	///Followers list request order
	enum class Direction
	{
		desc, ///< Descending 
		asc ///< Ascending
	};


	///Followed streams request order
	enum class Sort_Order
	{
		Created, ///< By creation date
		Last_Broadcast, ///< By last updated
		Login ///< By last login time
	};


	///Sort_Order enum value as a string
	inline std::wstring Sort_Order_To_string(Sort_Order order)
	{
		switch (order)
		{
		case Sort_Order::Created:
			return L"created_at";
		case Sort_Order::Last_Broadcast:
			return L"last_broadcast";
		case Sort_Order::Login:
			return L"login";
		default:
			throw std::out_of_range("Order parameter is out of range!");
		}
	}
}
